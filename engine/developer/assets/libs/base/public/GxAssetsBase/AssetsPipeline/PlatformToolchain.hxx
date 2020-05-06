#pragma once
#include <GxAssetsBase/Assets.Base.module.hxx>

namespace Graphyte::AssetsPipeline
{
    class ASSETS_BASE_API PlatformToolchain final
    {
        //
        // Windows SDK
        //
    public:
        static std::string GetWindowsSdkVersion() noexcept;
        static std::string GetWindowsSdkLocation() noexcept;
        static std::string GetWindowsSdkBinary() noexcept;

        //
        // Vulkan SDK
        //
    public:
        static std::string GetVulkanSdkLocation() noexcept;
        static std::string GetVulkanSdkBinary() noexcept;
    };
}
