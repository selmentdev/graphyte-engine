#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/System/Library.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Threading/Sync.hxx>

namespace Graphyte
{
    /*!
     * \brief   Represents module type.
     */
    enum struct ModuleType : uint32_t
    {
        Engine,         //!< Engine module.
        Game,           //!< Game module.
        DeveloperTool,  //!< Developer tool module. Not shipped with game.
    };

    /*!
     * \brief   Represents supported module features.
     */
    enum struct ModuleFeatures : uint32_t
    {
        None                = 0,            //!< No features specified.
        DynamicReloading    = 1 << 0,       //!< Module may be reloaded at runtime.
        AutomaticShutdown   = 1 << 1,       //!< Module can be safely unloaded at shutdown.
    };

    /*!
     * \brief   Provides interface for loadable modules.
     *
     * \remarks Dynamic modules are loaded in runtime. Static modules are compiled into executable
     *          and they don't require any code to be invoked at startup. Only module initialization
     *          is invoked.
     */
    struct IModule
    {
        virtual ~IModule() noexcept = default;

        /*!
         * \brief   Invoked when module is being loaded.
         */
        virtual void OnLoad() noexcept
        {
        }

        /*!
         * \brief   Invoked when module is being initialized.
         */
        virtual void OnInitialize() noexcept
        {
        }

        /*!
         * \brief   Invoked when module is being shutdown.
         */
        virtual void OnFinalize() noexcept
        {
        }

        /*!
         * \brief   Invoked when module is being unloaded.
         *
         * \remarks On normal shutdown, this method is called in reverse order that module was
         *          being loaded.
         */
        virtual void OnUnload() noexcept
        {
        }

        /*!
         * \brief   Returns module type.
         */
        virtual ModuleType GetModuleType() const noexcept
        {
            return ModuleType::Engine;
        }

        /*!
         * \brief   Returns module supported features.
         */
        virtual ModuleFeatures GetModuleFeatures() const noexcept
        {
            return ModuleFeatures::None;
        }
    };

    /*!
     * \brief   Represents module descriptor.
     */
    struct ModuleDescriptor final
    {
        std::string Name;                   //!< Name of module.
        std::string Path;                   //!< Path to loaded module.
        System::Library ModuleLibrary;      //!< System handle of loaded library.
        std::unique_ptr<IModule> Instance;  //!< Instance of IModule created by this library.
        int32_t LoadOrder;                  //!< Load order index.
    };

    /*!
     * \brief   Represents module status for `Query` functions.
     */
    struct ModuleStatus final
    {
        std::string Name;   //!< Name of module.
        std::string Path;   //!< Path to loaded module.
        bool IsLoaded;
    };

    /*!
     * \brief   This class implements engine's module manager.
     */
    class ModuleManager final
    {
    public:
        /*!
         * \brief   Initialize module manager.
         */
        BASE_API static void Initialize() noexcept;

        /*!
         * \brief   Finalizes module manager and unloads already loaded modules.
         */
        BASE_API static void Finalize() noexcept;

    public:
        /*!
         * \brief   Loads specified module.
         *
         * \param   name    Provides name of module to load.
         * \param   status  Returns status code with failure reason.
         *
         * \return  The instance of loaded module.
         *
         * \retval  Status::Success             Module was loaded succesfully.
         * \retval  Status::AlreadyExists       Module is already loaded.
         * \retval  Status::NotImplemented      `CreateModule` function returned null module.
         * \retval  Status::NotSupported        `CreateModule` function is not supported.
         * \retval  Status::Failed              Module couldn't be loaded.
         */
        BASE_API static IModule* Load(
            std::string_view name,
            Status* status = nullptr
        ) noexcept;

        /*!
         * \brief   Loads specified module
         *
         * \remarks This function will break application execution when specified module couldn't be
         *          loaded.
         *
         * \param   name    Provides name of module to load.
         *
         *  \return The instance of loaded module.
         */
        BASE_API static IModule& LoadChecked(
            std::string_view name
        ) noexcept;

        /*!
         * \brief   Unloads specified module.
         *
         * \param   name    Provides name of module to unload.
         *
         * \return  The status of unload operation.
         */
        BASE_API static Status Unload(
            std::string_view name
        ) noexcept;

        /*!
         * \brief   Gets value indicating whether specified module is loaded.
         *
         * \param   name    Provides name of module.
         *
         * \return  \c true when module is loaded, \c false otherwise.
         */
        BASE_API static bool IsLoaded(
            std::string_view name
        ) noexcept;

        /*!
         * \brief   Queries status of module by name.
         *
         * \param   result      Returns status of module.
         * \param   name        Provides name of module.
         *
         * \return  \c true when successful, \c false otherwise.
         */
        BASE_API static bool Query(
            ModuleStatus& result, std::string_view name
        ) noexcept;

        /*!
         * \brief   Queries status of all modules.
         *
         * \param   modules     Returns status of all loaded modules.
         *
         * \return  \c true when successful, \c false otherwise.
         */
        BASE_API static bool Query(
            std::vector<ModuleStatus>& modules
        ) noexcept;

        /*!
         * \brief   Queries status of all modules with names matching specified pattern.
         *
         * \param   modules     Returns status of all matching modules.
         * \param   pattern     Provides pattern to match module names.
         */
        BASE_API static bool Query(
            std::vector<ModuleStatus>& modules,
            std::string_view pattern
        ) noexcept;

        /*!
         * \brief   Gets module instance by name.
         *
         * \param   name    Provides name of module.
         *
         * \return  The instance of module when successful, \c nullptr otherwise.
         */
        BASE_API static IModule* Get(
            std::string_view name
        ) noexcept;

        /*!
         * \brief   Gets module instance by name.
         *
         * \remarks This function terminates application when module couldn't be found.
         *
         * \param   name    Provides name of module.
         *
         * \return  The instance of module.
         */
        BASE_API static IModule& GetChecked(
            std::string_view name
        ) noexcept;

        /*!
         * \brief   Gets number of loaded modules.
         *
         * \return  The number of loaded modules.
         */
        BASE_API static size_t GetModulesCount() noexcept;

        /*!
         * \brief   Registers static module instance.
         *
         * \param   name        Provides name of module.
         * \param   instance    Provides instance of module to register.
         *
         * \return  The status code.
         */
        BASE_API static Status RegisterStaticModule(
            std::string_view name,
            IModule* instance
        ) noexcept;

        /*!
         * \brief   Unregisters static module instance.
         *
         * \param   name        Provides name of module.
         * \param   instance    Provides instance of module to unregister.
         *
         * \return  The status code.
         */
        BASE_API static Status UnregisterStaticModule(
            std::string_view name,
            IModule* instance
        ) noexcept;

    public:
        /*!
         * \brief   Loads module and gets interface of specified type.
         *
         * \param   name    Provides name of module to load.
         * \param   status  Returns status code with failure reason.
         *
         * \return  The instance of loaded module.
         *
         * \see     Graphyte::ModuleManager::Load
         */
        template <typename TModule>
        static TModule* Load(
            std::string_view name,
            Status* status = nullptr
        ) noexcept
        {
            static_assert(std::is_base_of_v<IModule, TModule>, "TModule must implement IModule interface!");
            return static_cast<TModule*>(ModuleManager::Load(name, status));
        }

        /*!
         * \brief   Loads module and gets interface of specified type.
         *
         * \param   name    Provides name of module to load.
         *
         * \return  The instance of loaded module.
         *
         * \see     Graphyte::ModuleManager::LoadChecked
         */
        template <typename TModule>
        static TModule& LoadChecked(
            std::string_view name
        ) noexcept
        {
            static_assert(std::is_base_of_v<IModule, TModule>, "TModule must implement IModule interface!");
            return static_cast<TModule&>(ModuleManager::LoadChecked(name));
        }

        /*!
         * \brief   Gets module of specified name and type.
         *
         * \param   name    Provides name of module.
         *
         * \return  The instance of module.
         *
         * \see     Graphyte::ModuleManager::Get
         */
        template <typename TModule>
        static TModule* Get(
            std::string_view name
        ) noexcept
        {
            static_assert(std::is_base_of_v<IModule, TModule>, "TModule must implement IModule interface!");
            return static_cast<TModule*>(ModuleManager::Get(name));
        }

        /*!
         * \brief   Gets module of specified name and type.
         *
         * \param   name    Provides name of module.
         *
         * \return  The instance of module.
         *
         * \see     Graphyte::ModuleManager::GetChecked
         */
        template <typename TModule>
        static TModule& GetChecked(
            std::string_view name
        ) noexcept
        {
            static_assert(std::is_base_of_v<IModule, TModule>, "TModule must implement IModule interface!");
            return static_cast<TModule&>(ModuleManager::GetChecked(name));
        }

    private:
        static ModuleManager* GInstance;
        std::map<std::string, ModuleDescriptor, std::less<>> m_Modules;
        Threading::CriticalSection m_CS;

    private:
        static std::string MakeModulePath(
            std::string_view name
        ) noexcept;
    };
}

#define GX_IMPLEMENT_MODULE(module_class) \
    extern "C" GX_LIB_EXPORT Graphyte::IModule* CreateModule() noexcept \
    { \
        return new module_class(); \
    }
