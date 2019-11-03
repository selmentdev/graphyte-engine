#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte::Threading
{
    enum class ThreadPriority
    {
        TimeCritical,
        Highest,
        AboveNormal,
        Normal,
        BelowNormal,
        Lower,
        Lowest,
    };

    enum struct ThreadAffinity : uint64_t
    {
        None = uint64_t{},
        All = ~uint64_t{},
    };

    constexpr ThreadAffinity MakeThreadAffinity(uint64_t processor) noexcept
    {
        return static_cast<ThreadAffinity>(uint64_t{ 1 } << processor);
    }
}

#if GRAPHYTE_PLATFORM_WINDOWS
#include <Graphyte/Threading/Impl.Windows/Windows.Thread.hxx>
#elif GRAPHYTE_PLATFORM_LINUX
#include <Graphyte/Threading/Impl.Linux/Linux.Thread.hxx>
#elif GRAPHYTE_PLATFORM_ANDROID
#include <Graphyte/Threading/Impl.Android/Android.Thread.hxx>
#else
#error "Unknown platform"
#endif
