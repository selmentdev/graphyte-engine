#include <GxBase/System.hxx>
#include <Graphyte/Build.Version.hxx>

namespace Graphyte::System::Impl
{
    bool g_IsBuildMachine = false;
}

namespace Graphyte::System
{
    BASE_API BuildKind GetBuildKind() noexcept
    {
        return System::CurrentBuildKind;
    }

    BASE_API BuildType GetBuildType() noexcept
    {
        return System::CurrentBuildType;
    }

    BASE_API bool IsBuildMachine() noexcept
    {
#if GX_BUILD_TYPE_RETAIL
        return false;
#else
        return Impl::g_IsBuildMachine;
#endif
    }

    BASE_API std::string_view GetBuildId() noexcept
    {
        return GX_BUILD_UUID;
    }

    BASE_API std::string_view GetBuildBranch() noexcept
    {
        return GX_BUILD_BRANCH;
    }

    BASE_API std::string_view GetBuildCommit() noexcept
    {
        return GX_BUILD_COMMIT;
    }

    BASE_API Version GetBuildVersion() noexcept
    {
        return {
            GX_BUILD_VERSION_MAJOR,
            GX_BUILD_VERSION_MINOR,
            GX_BUILD_VERSION_RELEASE,
            GX_BUILD_VERSION_BUILD,
        };
    }

    BASE_API std::string_view GetBuildHostSystem() noexcept
    {
        return GX_BUILD_OS_PLATFORM;
    }

    BASE_API std::string_view GetBuildHostVersion() noexcept
    {
        return GX_BUILD_OS_VERSION;
    }

    BASE_API std::string_view GetBuildTimestamp() noexcept
    {
        return GX_BUILD_TIMESTAMP;
    }

    BASE_API std::string_view GetCompilerName() noexcept
    {
        return GX_COMPILER_NAME;
    }
}
