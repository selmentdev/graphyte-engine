#include "Base.pch.hxx"
#include <Graphyte/System.hxx>
#include <Graphyte/Build.Version.hxx>

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
        // #todo Implement this properly.
        return false;
    }

    BASE_API std::string_view GetBuildId() noexcept
    {
        return GRAPHYTE_BUILD_UUID;
    }

    BASE_API std::string_view GetBuildBranch() noexcept
    {
        return GRAPHYTE_BUILD_BRANCH;
    }

    BASE_API std::string_view GetBuildCommit() noexcept
    {
        return GRAPHYTE_BUILD_COMMIT;
    }

    BASE_API Version GetBuildVersion() noexcept
    {
        return {
            GRAPHYTE_BUILD_VERSION_MAJOR,
            GRAPHYTE_BUILD_VERSION_MINOR,
            GRAPHYTE_BUILD_VERSION_RELEASE,
            GRAPHYTE_BUILD_VERSION_BUILD,
        };
    }

    BASE_API std::string_view GetBuildHostSystem() noexcept
    {
        return GRAPHYTE_BUILD_OS_PLATFORM;
    }

    BASE_API std::string_view GetBuildHostVersion() noexcept
    {
        return GRAPHYTE_BUILD_OS_VERSION;
    }

    BASE_API std::string_view GetBuildTimestamp() noexcept
    {
        return GRAPHYTE_BUILD_TIMESTAMP;
    }

    BASE_API std::string_view GetCompilerName() noexcept
    {
        return GRAPHYTE_COMPILER_NAME;
    }
}
