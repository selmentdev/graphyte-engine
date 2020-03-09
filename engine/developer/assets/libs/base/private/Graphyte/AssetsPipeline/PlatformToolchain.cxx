#include <Graphyte/AssetsPipeline/PlatformToolchain.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/System.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#endif

namespace Graphyte::AssetsPipeline
{
    std::string PlatformToolchain::GetWindowsSdkVersion() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        static std::string version{};

        if (version.empty())
        {
            System::Impl::QueryRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\v10.0", L"ProductVersion", version);
        }

        return version;
#else
        return {};
#endif
    }

    std::string PlatformToolchain::GetWindowsSdkLocation() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        static std::string path{};

        if (path.empty())
        {
            System::Impl::QueryRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\v10.0", L"InstallationFolder", path);
            Storage::Path::Normalize(path);
        }

        return path;
#else
        return {};
#endif
    }

    std::string PlatformToolchain::GetWindowsSdkBinary() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        static std::string path = GetWindowsSdkLocation();

        if (!path.empty())
        {
            std::string version = GetWindowsSdkVersion();

            Storage::Path::Append(path, "bin");
            Storage::Path::Append(path, version);
            path.append(".0");

#if GRAPHYTE_CPU_X86_64
            Storage::Path::Append(path, "x64");
#elif GRAPHYTE_CPU_X86_32
            Storage::Path::Append(path, "x86");
#elif GRAPHYTE_CPU_ARM_64
            Storage::Path::Append(path, "arm64");
#elif GRAPHYTE_CPU_ARM_32
            Storage::Path::Append(path, "arm");
#else
#error "Unknown"
#endif
        }

        return path;
#else
        return {};
#endif
    }

    std::string PlatformToolchain::GetVulkanSdkLocation() noexcept
    {
        static std::string path{};

        if (path.empty())
        {
            if (System::GetEnvironmentVariable(path, "VULKAN_SDK") == Status::Success)
            {
                Storage::Path::Normalize(path);
            }
        }

        return path;
    }

    std::string PlatformToolchain::GetVulkanSdkBinary() noexcept
    {
        static std::string path{};

        if (path.empty())
        {
            path = GetVulkanSdkLocation();

            if (!path.empty())
            {
                Storage::Path::Append(path, "bin/");
            }
        }

        return path;
    }
}
