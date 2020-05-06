#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Diagnostics
{
    class BASE_API Profiler final
    {
    public:
        static void Initialize() noexcept;
        static void Finalize() noexcept;

    public:
        static void ThreadName(const char* name) noexcept;

    public:
        static void PushRange(const char* name) noexcept;
        static void PushRange(const char* name, uint32_t color) noexcept;
        static void PopRange() noexcept;

    public:
        static void MarkEvent(const char* name) noexcept;
        static void MarkEvent(const char* name, uint32_t color) noexcept;
    };
}

namespace Graphyte::Diagnostics
{
    struct ProfilerScopedRegion final
    {
        ProfilerScopedRegion(const char* name) noexcept
        {
            Profiler::PushRange(name);
        }

        ProfilerScopedRegion(const char* name, uint32_t color) noexcept
        {
            Profiler::PushRange(name, color);
        }

        ~ProfilerScopedRegion() noexcept
        {
            Profiler::PopRange();
        }
    };
}


#if GX_BUILD_TYPE_RETAIL && !GRAPHYTE_ENABLE_PROFILE
#define GX_PROFILE_REGION(name, ...)
#define GX_PROFILE_MARKER(name, ...)
#else
#define GX_PROFILE_REGION(name, ...) ::Graphyte::Diagnostics::ProfilerScopedRegion GX_UNIQUE_NAME(gx_profile_region_)(name, ## __VA_ARGS__)
#define GX_PROFILE_MARKER(name, ...) ::Graphyte::Diagnostics::Profiler::MarkEvent(name, ## __VA_ARGS__)
#endif
