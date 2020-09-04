#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>

namespace Graphyte::System
{
    BASE_API void GetSystemTime(CalendarTime& time) noexcept
    {
        SYSTEMTIME st{};
        GetSystemTime(&st);
        time = System::Impl::ToCalendarTime(st);
    }

    BASE_API void GetLocalTime(CalendarTime& time) noexcept
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);
        time = System::Impl::ToCalendarTime(st);
    }

    BASE_API uint64_t GetSystemTime() noexcept
    {
        FILETIME ft{};
        GetSystemTimeAsFileTime(&ft);

        ULARGE_INTEGER const ul{
            .LowPart = ft.dwLowDateTime,
            .HighPart = ft.dwHighDateTime,
        };
        return static_cast<uint64_t>(ul.QuadPart);
    }

    BASE_API uint64_t GetLocalTime() noexcept
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);

        FILETIME ft{};
        SystemTimeToFileTime(&st, &ft);

        ULARGE_INTEGER const ul{
            .LowPart = ft.dwLowDateTime,
            .HighPart = ft.dwHighDateTime,
        };
        return static_cast<uint64_t>(ul.QuadPart);
    }

    BASE_API uint64_t GetTimestampResolution() noexcept
    {
        static std::atomic<uint64_t> g_TimestampResolutionFrequency{};

        uint64_t const value = g_TimestampResolutionFrequency.load(std::memory_order_relaxed);

        if (value == 0)
        {
            LARGE_INTEGER li{};
            QueryPerformanceFrequency(&li);
            g_TimestampResolutionFrequency.store(static_cast<uint64_t>(li.QuadPart), std::memory_order_relaxed);
        }

        return value;
    }

    BASE_API uint64_t GetTimestamp() noexcept
    {
        LARGE_INTEGER li{};
        QueryPerformanceCounter(&li);
        return static_cast<uint64_t>(li.QuadPart);
    }

    BASE_API uint64_t GetMonotonic() noexcept
    {
        return static_cast<uint64_t>(GetTickCount64());
    }

    BASE_API double GetSeconds() noexcept
    {
        LARGE_INTEGER li{};
        QueryPerformanceCounter(&li);

        return li.QuadPart * g_SecondsPerCycle;
    }
}
