#include "Base.pch.hxx"
#include <Graphyte/Modules.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Threading/Sync.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/String.hxx>

namespace Graphyte
{
    GX_DECLARE_LOG_CATEGORY(LogModuleManager, Trace, Trace);
    GX_DEFINE_LOG_CATEGORY(LogModuleManager);

    ModuleManager* ModuleManager::GInstance{};

    void ModuleManager::Initialize() noexcept
    {
        GX_ASSERT_SINGLE_CALL();
        GX_ASSERTF(ModuleManager::GInstance == nullptr, "Module manager is already initialized");

        ModuleManager::GInstance = new ModuleManager();
    }

    void ModuleManager::Finalize() noexcept
    {
        GX_ASSERT_SINGLE_CALL();
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        for (auto&[key, descriptor] : ModuleManager::GInstance->m_Modules)
        {
            GX_LOG(LogPlatform, Info,
                "Unloading module: {} ({})\n",
                descriptor.Name,
                descriptor.Path
            );

            descriptor.Instance->OnFinalize();
            descriptor.Instance->OnUnload();


            //
            // Destroy module object.
            //

            descriptor.Instance = nullptr;


            //
            // Dispose loaded shared library.
            //

            [[maybe_unused]] Status status = descriptor.ModuleLibrary.Unload();
            GX_ASSERT(status == Status::Success);
        }

        delete ModuleManager::GInstance;
        ModuleManager::GInstance = nullptr;
    }

    IModule* ModuleManager::Load(
        std::string_view name,
        Status* status
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        Status currentStatus = Status::NotFound;
        IModule* result{};

        auto it = ModuleManager::GInstance->m_Modules.find(name);
        if (it != ModuleManager::GInstance->m_Modules.end())
        {
            //
            // Get already loaded module back with proper status code.
            //

            result = it->second.Instance.get();
            currentStatus = Status::AlreadyExists;
        }
        else
        {
            using CreateModuleSignature = IModule* (void) noexcept;


            //
            // Get platform specific module file name to load.
            //

            std::string path = MakeModulePath(name);


            //
            // Load library.
            //

            System::Library library{};
            currentStatus = library.Load(path);

            if (currentStatus == Status::Success)
            {
                //
                // Get `CreateModule` function from module.
                //

                auto* createModuleFunction = library.Resolve<CreateModuleSignature>("CreateModule");

                if (createModuleFunction != nullptr)
                {
                    //
                    // Create module.
                    //

                    result = createModuleFunction();
                    if (result != nullptr)
                    {
                        //
                        // Register created module.
                        //

                        ModuleDescriptor descriptor{
                            .Name = std::string{ name },
                            .Path = path,
                            .ModuleLibrary = std::move(library),
                            .Instance = std::unique_ptr<IModule>(result),
                            .LoadOrder = 0,
                        };

                        ModuleManager::GInstance->m_Modules.insert({
                            descriptor.Name,
                            std::move(descriptor)
                        });


                        //
                        // Invoke callbacks.
                        //

                        result->OnLoad();
                        result->OnInitialize();

                        GX_LOG(LogPlatform, Info,
                            "Loading module: {} ({})\n",
                            name,
                            path
                        );
                    }
                    else
                    {
                        //
                        // This module doesn't implement `CreateModule` function.
                        //

                        currentStatus = Status::NotImplemented;
                    }
                }
                else
                {
                    //
                    // Tried to load invalid file.
                    //
                    currentStatus = Status::NotSupported;
                }
            }
        }

        if (status != nullptr)
        {
            //
            // Report loading status outside.
            //

            *status = currentStatus;
        }

        return result;
    }

    IModule& ModuleManager::LoadChecked(
        std::string_view name
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        //
        // Load module.
        //

        Status status{};
        auto* instance = ModuleManager::Load(name, &status);

        GX_ABORT_UNLESS(instance != nullptr, "Failed to load module {}: {}", name, status);

        return *instance;
    }

    Status ModuleManager::Unload(
        std::string_view name
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        Status status = Status::NotFound;

        auto it = ModuleManager::GInstance->m_Modules.find(name);
        if (it != ModuleManager::GInstance->m_Modules.end())
        {
            //
            // Module is loaded.
            //

            auto& descriptor = it->second;

            GX_ASSERT(descriptor.ModuleLibrary.IsValid());
            GX_ASSERT(descriptor.Instance != nullptr);


            //
            // Invoke callbacks.
            //

            descriptor.Instance->OnFinalize();
            descriptor.Instance->OnUnload();


            //
            // Destroy module object.
            //

            descriptor.Instance = nullptr;


            //
            // Dispose loaded shared library.
            //

            status = descriptor.ModuleLibrary.Unload();


            //
            // Remove entry for that module.
            //

            ModuleManager::GInstance->m_Modules.erase(it);

            GX_LOG(LogPlatform, Info,
                "Unloading module: {} ({})\n",
                descriptor.Name,
                descriptor.Path
            );
        }

        return status;
    }

    bool ModuleManager::IsLoaded(
        std::string_view name
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        auto it = ModuleManager::GInstance->m_Modules.find(name);
        if (it != ModuleManager::GInstance->m_Modules.end())
        {
            //
            // Check whether module is loaded.
            //

            return it->second.Instance != nullptr;
        }

        return false;
    }

    bool ModuleManager::Query(
        ModuleStatus& result,
        std::string_view name
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        auto it = ModuleManager::GInstance->m_Modules.find(name);
        if (it != ModuleManager::GInstance->m_Modules.end())
        {
            //
            // Get module status info.
            //

            result.Name = it->second.Name;
            result.Path = it->second.Path;
            result.IsLoaded = it->second.Instance != nullptr;
        }

        return false;
    }

    bool ModuleManager::Query(
        std::vector<ModuleStatus>& modules
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        for (const auto&[key, value] : ModuleManager::GInstance->m_Modules)
        {
            auto& status = modules.emplace_back();

            status.Name = value.Name;
            status.Path = value.Path;
            status.IsLoaded = value.Instance != nullptr;
        }

        return true;
    }

    bool ModuleManager::Query(
        std::vector<ModuleStatus>& modules,
        std::string_view pattern
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        for (const auto& [key, value] : ModuleManager::GInstance->m_Modules)
        {
            if (Graphyte::MatchWildcard(key, pattern))
            {
                auto& status = modules.emplace_back();

                status.Name = value.Name;
                status.Path = value.Path;
                status.IsLoaded = value.Instance != nullptr;
            }
        }

        return true;
    }

    IModule* ModuleManager::Get(
        std::string_view name
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        Threading::ScopedLock<Threading::CriticalSection> lock{ ModuleManager::GInstance->m_CS };

        IModule* result{};

        auto it = ModuleManager::GInstance->m_Modules.find(name);
        if (it != ModuleManager::GInstance->m_Modules.end())
        {
            result = it->second.Instance.get();
        }

        return result;
    }

    IModule& ModuleManager::GetChecked(
        std::string_view name
    ) noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");

        auto* instance = ModuleManager::Get(name);

        GX_ABORT_UNLESS(instance != nullptr, "Failed to load module {}", name);

        return *instance;
    }

    size_t ModuleManager::GetModulesCount() noexcept
    {
        GX_ASSERTF(ModuleManager::GInstance != nullptr, "Module manager is not initialized");
        return ModuleManager::GInstance->m_Modules.size();
    }

    Status ModuleManager::RegisterStaticModule(
        [[maybe_unused]] std::string_view name,
        [[maybe_unused]] IModule* instance
    ) noexcept
    {
        GX_ASSERT_NOT_IMPLEMENTED();
        return Status::NotImplemented;
    }

    Status ModuleManager::UnregisterStaticModule(
        [[maybe_unused]] std::string_view name,
        [[maybe_unused]] IModule* instance
    ) noexcept
    {
        GX_ASSERT_NOT_IMPLEMENTED();
        return Status::NotImplemented;
    }

    std::string ModuleManager::MakeModulePath(
        std::string_view name
    ) noexcept
    {
        return fmt::format("{}{}.{}",
            System::GetModulePrefix(),
            name,
            System::GetModuleExtension()
        );
    }
}
