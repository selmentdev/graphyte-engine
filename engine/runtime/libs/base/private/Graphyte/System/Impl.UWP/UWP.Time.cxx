#include <Graphyte/System.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Types.hxx>

namespace Graphyte::System
{
    BASE_API void GetSystemTime(CalendarTime& time) noexcept
    {
        SYSTEMTIME st{};
        GetSystemTime(&st);
        System::TypeConverter<SYSTEMTIME>::Convert(time, st);
    }

    BASE_API void GetLocalTime(CalendarTime& time) noexcept
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);
        System::TypeConverter<SYSTEMTIME>::Convert(time, st);
    }

    BASE_API uint64_t GetSystemTime() noexcept
    {
        FILETIME ft{};
        GetSystemTimeAsFileTime(&ft);
        return System::TypeConverter<FILETIME>::ConvertUInt64(ft);
    }

    BASE_API uint64_t GetLocalTime() noexcept
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);

        FILETIME ft{};
        SystemTimeToFileTime(&st, &ft);
        return System::TypeConverter<FILETIME>::ConvertUInt64(ft);
    }

    BASE_API uint64_t GetTimestampResolution() noexcept
    {
        LARGE_INTEGER li{};
        QueryPerformanceFrequency(&li);
        return System::TypeConverter<LARGE_INTEGER>::ConvertUInt64(li);
    }

    BASE_API uint64_t GetTimestamp() noexcept
    {
        LARGE_INTEGER li{};
        QueryPerformanceCounter(&li);
        return System::TypeConverter<LARGE_INTEGER>::ConvertUInt64(li);
    }

    BASE_API uint64_t GetMonotonic() noexcept
    {
        return static_cast<uint64_t>(GetTickCount64());
    }

    BASE_API double GetSeconds() noexcept
    {
        LARGE_INTEGER li{};
        QueryPerformanceCounter(&li);

        return li.QuadPart * GSecondsPerCycle;
    }
}
