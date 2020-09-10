#include <GxBase/System.hxx>
#include "Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API PlatformKind GetPlatformKind() noexcept
    {
        return System::CurrentPlatformKind;
    }

    BASE_API PlatformType GetPlatformType() noexcept
    {
        return System::CurrentPlatformType;
    }

    BASE_API std::string_view GetPlatformName() noexcept
    {
        return GX_PLATFORM_NAME;
    }

    BASE_API bool HasPlatformFeature(
        PlatformFeature feature) noexcept
    {
        return Impl::g_PlatformFeatureSet.Has(feature);
    }

    BASE_API std::string_view GetFileManagerName() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        return "explorer.exe";

#elif GX_PLATFORM_LINUX

        return {};

#else
#error "Unknown file manager name"
#endif
    }

    BASE_API std::string_view GetModuleExtension() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        return "dll";

#elif GX_PLATFORM_LINUX

        return "so";

#else
#error "Unknown module extension"
#endif
    }

    BASE_API std::string_view GetModulePrefix() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        return "lib";

#elif GX_PLATFORM_LINUX

        return "lib";

#else
#error "Unknown module prefix"
#endif
    }

    BASE_API std::string_view GetExecutableExtension() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        return "exe";

#elif GX_PLATFORM_LINUX

        return {};

#else
#error "Unknown executable extension"
#endif
    }
}
