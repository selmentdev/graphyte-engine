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
        return GRAPHYTE_PLATFORM_NAME;
    }

    BASE_API bool HasPlatformFeature(
        PlatformFeature feature
    ) noexcept
    {
        return Impl::GPlatformFeatureSet.Has(feature);
    }

    BASE_API std::string_view GetFileManagerName() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        return "explorer.exe";

#elif GRAPHYTE_PLATFORM_LINUX

        return {};

#else
#   error "Unknown file manager name"
#endif
    }

    BASE_API std::string_view GetModuleExtension() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        return "dll";

#elif GRAPHYTE_PLATFORM_LINUX

        return "so";

#else
#   error "Unknown module extension"
#endif
    }

    BASE_API std::string_view GetModulePrefix() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        return "lib";

#elif GRAPHYTE_PLATFORM_LINUX

        return "lib";

#else
#   error "Unknown module prefix"
#endif
    }

    BASE_API std::string_view GetExecutableExtension() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        return "exe";

#elif GRAPHYTE_PLATFORM_LINUX

        return {};

#else
#   error "Unknown executable extension"
#endif
    }
}
