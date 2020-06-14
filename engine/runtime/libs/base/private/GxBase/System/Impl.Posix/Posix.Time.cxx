#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Posix/Posix.Types.hxx>

namespace Graphyte::System
{
    BASE_API void GetSystemTime(
        CalendarTime& time) noexcept
    {
        time_t rawtime;
        ::time(&rawtime);
        // clang-format off
        struct tm timeinfo{};
        // clang-format on
        gmtime_r(&rawtime, &timeinfo);

        TypeConverter<struct tm>::Convert(time, timeinfo);
    }

    BASE_API void GetLocalTime(
        CalendarTime& time) noexcept
    {
        time_t rawtime;
        ::time(&rawtime);
        // clang-format off
        struct tm timeinfo{};
        // clang-format on
        localtime_r(&rawtime, &timeinfo);

        TypeConverter<struct tm>::Convert(time, timeinfo);
    }

    BASE_API uint64_t GetSystemTime() noexcept
    {
        // clang-format off
        struct timeval tv{};
        // clang-format on
        gettimeofday(&tv, nullptr);

        return TypeConverter<timeval>::ConvertToTicks(tv);
    }

    BASE_API uint64_t GetLocalTime() noexcept
    {
        // clang-format off
        struct timeval tv{};
        struct timezone tz{};
        // clang-format on
        gettimeofday(&tv, &tz);

        // Adjust for local time from timezone
        tv.tv_sec += tz.tz_minuteswest;

        return TypeConverter<timeval>::ConvertToTicks(tv);
    }

    BASE_API uint64_t GetTimestampResolution() noexcept
    {
        return GSecondsToNanoseconds;
    }

    BASE_API uint64_t GetTimestamp() noexcept
    {
        // clang-format off
        struct timespec ts{};
        // clang-format on

        if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
        {
            GX_ASSERTF(false, "Cannot get time stamp");
        }

        return TypeConverter<struct timespec>::ConvertNanoseconds(ts);
    }

    BASE_API uint64_t GetMonotonic() noexcept
    {
        // clang-format off
        struct timespec ts{};
        // clang-format on

        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        return static_cast<uint64_t>(static_cast<uint64_t>(ts.tv_sec) * 1000000U + static_cast<uint64_t>(ts.tv_nsec) / 1000U);
    }

    BASE_API double GetSeconds() noexcept
    {
        // clang-format off
        struct timespec ts{};
        // clang-format on

        clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
        return static_cast<double>(ts.tv_sec) + static_cast<double>(ts.tv_nsec) / 1.0e9;
    }
}
