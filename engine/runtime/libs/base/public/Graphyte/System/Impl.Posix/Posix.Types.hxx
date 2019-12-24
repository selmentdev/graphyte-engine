#pragma once
#include <Graphyte/System.hxx>
#include <Graphyte/DateTime.hxx>

namespace Graphyte::System
{
    template <>
    struct TypeConverter<struct timeval> final
    {
        __forceinline static struct timeval Subtract(struct timeval value1, struct timeval value2) noexcept
        {
            struct timeval temp {};
            temp.tv_usec = value2.tv_usec;
            temp.tv_sec = value2.tv_sec;

            //
            // Saturate.
            //
            if (value1.tv_usec < temp.tv_usec)
            {
                const auto nsec = ((value1.tv_usec - temp.tv_usec) / 1000000) + 1;
                temp.tv_usec -= 1000000 * nsec;
                temp.tv_sec += nsec;
            }

            //
            // Saturate.
            //
            if ((value1.tv_usec - temp.tv_usec) > 1000000)
            {
                const auto nsec = (value1.tv_usec - temp.tv_usec) / 1000000;
                temp.tv_usec += 1000000 * nsec;
                temp.tv_sec -= nsec;
            }

            struct timeval result {};
            result.tv_sec = value1.tv_sec - temp.tv_sec;
            result.tv_usec = value1.tv_usec - temp.tv_usec;
            return result;
        }

        __forceinline static uint64_t ConvertToTicks(struct timeval tv) noexcept
        {
#define EPOCH_ADJUST UINT64_C(11644473600)
            return ((static_cast<uint64_t>(tv.tv_sec) + EPOCH_ADJUST) * UINT64_C(1000000) + static_cast<uint64_t>(tv.tv_usec)) * UINT64_C(10);
        }
    };

    template <>
    struct TypeConverter<struct timespec> final
    {
        __forceinline static struct timespec ConvertMilliseconds(uint64_t value) noexcept
        {
            struct timespec result {};
            result.tv_sec = value / 1000;
            result.tv_nsec = (value % 1000) * 1000000;
            return result;
        }

        __forceinline static uint64_t ConvertNanoseconds(struct timespec value) noexcept
        {
            return static_cast<uint64_t>(value.tv_sec) * UINT64_C(1000000000) + static_cast<uint64_t>(value.tv_nsec);
        }

        __forceinline static DateTime ConvertDateTime(struct timespec value) noexcept
        {
            const auto ticks
                = (value.tv_sec * Impl::GTicksInSecond)
                + (value.tv_nsec / 100);
            return DateTime{ Impl::GUnixAdjustOffset + ticks };
        }
        __forceinline static struct timespec ConvertDateTime(DateTime value) noexcept
        {
            const auto ticks = value.Value;
            const auto sec = ticks / Impl::GTicksInSecond;
            const auto nsec = (ticks % Impl::GTicksInSecond) / Impl::GTicksInMicrosecond;

            struct timespec result {};
            result.tv_sec = sec;
            result.tv_nsec = nsec;
            return result;
        }
    };

    template <>
    struct TypeConverter<struct tm> final
    {
        __forceinline static void Convert(struct tm& result, const CalendarTime& value) noexcept
        {
            result.tm_year = static_cast<decltype(result.tm_year)>(value.Year);
            result.tm_mon = static_cast<decltype(result.tm_mon)>(value.Month);
            result.tm_wday = static_cast<decltype(result.tm_wday)>(value.DayOfWeek);
            result.tm_mday = static_cast<decltype(result.tm_mday)>(value.Day);
            result.tm_hour = static_cast<decltype(result.tm_hour)>(value.Hour);
            result.tm_min = static_cast<decltype(result.tm_min)>(value.Minute);
            result.tm_sec = static_cast<decltype(result.tm_sec)>(value.Second);
            result.tm_yday = static_cast<decltype(result.tm_yday)>(value.DayOfYear);
        }
        __forceinline static void Convert(CalendarTime& result, const struct tm& value) noexcept
        {
            result.Year = static_cast<decltype(result.Year)>(value.tm_year);
            result.Month = static_cast<decltype(result.Month)>(value.tm_mon);
            result.DayOfWeek = static_cast<decltype(result.DayOfWeek)>(value.tm_wday);
            result.Day = static_cast<decltype(result.Day)>(value.tm_mday);
            result.Hour = static_cast<decltype(result.Hour)>(value.tm_hour);
            result.Minute = static_cast<decltype(result.Minute)>(value.tm_min);
            result.Second = static_cast<decltype(result.Second)>(value.tm_sec);
            result.Millisecond = 0;
            result.DayOfYear = static_cast<decltype(result.DayOfYear)>(value.tm_yday);
        }
    };
}
