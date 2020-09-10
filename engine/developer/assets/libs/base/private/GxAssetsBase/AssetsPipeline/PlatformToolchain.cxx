#include <GxAssetsBase/AssetsPipeline/PlatformToolchain.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/System.hxx>

#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#endif

namespace Graphyte::AssetsPipeline
{
    std::string PlatformToolchain::GetWindowsSdkVersion() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
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
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
        static std::string path{};

        if (path.empty())
        {
            System::Impl::QueryRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\v10.0", L"InstallationFolder", path);
            Storage::NormalizePath(path);
        }

        return path;
#else
        return {};
#endif
    }

    std::string PlatformToolchain::GetWindowsSdkBinary() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
        static std::string path = GetWindowsSdkLocation();

        if (!path.empty())
        {
            std::string version = GetWindowsSdkVersion();

            Storage::AppendPath(path, "bin");
            Storage::AppendPath(path, version);
            path.append(".0");

#if GX_CPU_X86_64
            Storage::AppendPath(path, "x64");
#elif GX_CPU_X86_32
            Storage::AppendPath(path, "x86");
#elif GX_CPU_ARM_64
            Storage::AppendPath(path, "arm64");
#elif GX_CPU_ARM_32
            Storage::AppendPath(path, "arm");
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
                Storage::NormalizePath(path);
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
                Storage::AppendPath(path, "bin/");
            }
        }

        return path;
    }
}
