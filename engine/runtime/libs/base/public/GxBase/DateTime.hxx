#pragma once
#include <GxBase/Base.module.hxx>

// =================================================================================================
//
// DateTime implementation details.
//

namespace Graphyte::Impl
{
    static constexpr const std::int64_t g_TicksInMicrosecond{ 10 };
    static constexpr const std::int64_t g_TicksInMillisecond{ g_TicksInMicrosecond * std::int64_t{ 1000 } };
    static constexpr const std::int64_t g_TicksInSecond{ g_TicksInMillisecond * std::int64_t{ 1000 } };
    static constexpr const std::int64_t g_TicksInMinute{ g_TicksInSecond * std::int64_t{ 60 } };
    static constexpr const std::int64_t g_TicksInHour{ g_TicksInMinute * std::int64_t{ 60 } };
    static constexpr const std::int64_t g_TicksInDay{ g_TicksInHour * std::int64_t{ 24 } };

    static constexpr const std::int64_t g_MaxSeconds = std::numeric_limits<std::int64_t>::max() / g_TicksInSecond;
    static constexpr const std::int64_t g_MinSeconds = std::numeric_limits<std::int64_t>::min() / g_TicksInSecond;

    static constexpr const std::int32_t g_DaysInYear{ 365 };
    static constexpr const std::int32_t g_DaysIn4Years{ (4 * 365) + 1 };
    static constexpr const std::int32_t g_DaysIn100Years{ (100 * 365) + 24 };
    static constexpr const std::int32_t g_DaysIn400Years{ (400 * 365) + 97 };

    static constexpr const std::int32_t g_DaysTo1601{ g_DaysIn400Years * 4 };
    static constexpr const std::int32_t g_DaysTo1899{ g_DaysIn400Years * 4 + g_DaysIn100Years * 3 - 367 };
    static constexpr const std::int32_t g_DaysTo10000{ g_DaysIn400Years * 25 - 366 };

    static constexpr const std::int64_t g_TicksMinValue{ 0 };
    static constexpr const std::int64_t g_TicksMaxValue{ g_DaysTo10000 * g_TicksInDay - 1 };
    static constexpr const std::int64_t g_DateAdjustOffset{ g_DaysTo1601 * g_TicksInDay };
    static constexpr const std::int64_t g_UnixAdjustOffset{ 621355968000000000 };

    static_assert(g_DaysTo1601 == 584388, "Invalid number of days from 0001-01-01 to 1601-12-31");
    static_assert(g_DaysTo1899 == 693593, "Invalid number of days from 0001-01-01 to 1899-12-31");
    static_assert(g_DaysTo10000 == 3652059, "Invalid number of days from 0001-01-01 to 9999-12-31");
    static_assert(g_TicksInSecond == 10000000, "Invalid number of ticks in second");
    static_assert(g_DateAdjustOffset == 504911232000000000, "Invalid number of ticks for time adjustment");
}


// =================================================================================================
//
// Date Time
//

namespace Graphyte
{
    enum struct DateTimeKind
    {
        System,
        Local,
    };

    enum struct Month
    {
        First     = 1,
        January   = 1,
        February  = 2,
        March     = 3,
        April     = 4,
        May       = 5,
        June      = 6,
        July      = 7,
        August    = 8,
        September = 9,
        October   = 10,
        November  = 11,
        December  = 12,
        Count     = 12,
        Last      = 12
    };

    enum struct WeekDay
    {
        Sunday    = 0,
        Monday    = 1,
        Tuesday   = 2,
        Wednesday = 3,
        Thursday  = 4,
        Friday    = 5,
        Saturday  = 6,
        Count     = 7
    };

    enum struct DateTimeFormat
    {
        Date,
        Time,
        DateTime,
        FileSafe,
        TimeStamp,
        DateIso8601     = Date,
        DateTimeIso8601 = DateTime,
    };

    struct CalendarTime final
    {
        std::int32_t Year;
        std::int32_t Month;
        std::int32_t Day;
        std::int32_t Hour;
        std::int32_t Minute;
        std::int32_t Second;
        std::int32_t Millisecond;
        std::int32_t DayOfWeek;
        std::int32_t DayOfYear;

        [[nodiscard]] BASE_API std::int64_t ToTicks() const noexcept;
        [[nodiscard]] BASE_API bool IsValid() const noexcept;
    };

    struct TimeSpanMembers final
    {
        std::int32_t Days;
        std::int32_t Hours;
        std::int32_t Minutes;
        std::int32_t Seconds;
        std::int32_t Milliseconds;
    };

    struct DateTime;
    struct TimeSpan;
}

namespace Graphyte
{
    struct DateTime final
    {
        std::int64_t Value;

        [[nodiscard]] BASE_API static DateTime Create(
            std::int32_t year,
            std::int32_t month,
            std::int32_t day) noexcept;

        [[nodiscard]] BASE_API static DateTime Create(
            std::int32_t year,
            std::int32_t month,
            std::int32_t day,
            std::int32_t hour,
            std::int32_t minute,
            std::int32_t second) noexcept;

        [[nodiscard]] BASE_API static DateTime Create(
            std::int32_t year,
            std::int32_t month,
            std::int32_t day,
            std::int32_t hour,
            std::int32_t minute,
            std::int32_t second,
            std::int32_t millisecond) noexcept;

        [[nodiscard]] BASE_API static DateTime Now() noexcept;
        [[nodiscard]] BASE_API static DateTime Now(DateTimeKind kind) noexcept;

        [[nodiscard]] BASE_API static DateTime Today(DateTimeKind kind) noexcept;
        [[nodiscard]] BASE_API static DateTime Today() noexcept;

        [[nodiscard]] BASE_API static DateTime FromUnixTimestamp(std::int64_t seconds) noexcept;

        [[nodiscard]] BASE_API static DateTime FromCalendar(CalendarTime const& value) noexcept;

        [[nodiscard]] BASE_API bool ToCalendar(CalendarTime& result) noexcept;

        [[nodiscard]] BASE_API std::int64_t ToUnixTimestamp() noexcept;

        [[nodiscard]] BASE_API TimeSpan GetTimeOfDay() const noexcept;
        [[nodiscard]] BASE_API DateTime GetDate() const noexcept;

        [[nodiscard]] constexpr auto operator<=>(DateTime const& rhs) const noexcept = default;
    };

    static_assert(sizeof(DateTime) == sizeof(std::int64_t));

    BASE_API bool ToString(
        std::string& result,
        DateTime value,
        DateTimeFormat format = DateTimeFormat::DateTime) noexcept;

    BASE_API bool ToString(
        std::string& result,
        DateTime value,
        std::string_view format) noexcept;

    BASE_API bool FromString(
        DateTime& result,
        std::string_view value) noexcept;
}

namespace Graphyte
{
    struct TimeSpan final
    {
        std::int64_t Value;

        [[nodiscard]] BASE_API static TimeSpan Create(
            std::int32_t hours,
            std::int32_t minutes,
            std::int32_t seconds) noexcept;

        [[nodiscard]] BASE_API static TimeSpan Create(
            std::int32_t days,
            std::int32_t hours,
            std::int32_t minutes,
            std::int32_t seconds) noexcept;

        [[nodiscard]] BASE_API static TimeSpan Create(
            std::int32_t days,
            std::int32_t hours,
            std::int32_t minutes,
            std::int32_t seconds,
            std::int32_t milliseconds) noexcept;

        [[nodiscard]] constexpr static TimeSpan FromSeconds(std::int64_t seconds) noexcept
        {
            return { seconds * Impl::g_TicksInSecond };
        }

        [[nodiscard]] constexpr std::int64_t ToSeconds() const noexcept
        {
            return Value / Impl::g_TicksInSecond;
        }

        BASE_API void ToMembers(
            TimeSpanMembers& result) noexcept;

        [[nodiscard]] BASE_API static TimeSpan FromMembers(
            TimeSpanMembers const& value) noexcept;

        [[nodiscard]] TimeSpan GetDuration() const noexcept
        {
            return { std::abs(Value) };
        }

        [[nodiscard]] constexpr double GetTotalDays() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::g_TicksInDay);
        }

        [[nodiscard]] constexpr double GetTotalHours() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::g_TicksInHour);
        }

        [[nodiscard]] constexpr double GetTotalMinutes() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::g_TicksInMinute);
        }

        [[nodiscard]] constexpr double GetTotalSeconds() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::g_TicksInSecond);
        }

        [[nodiscard]] constexpr double GetTotalMilliseconds() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::g_TicksInMillisecond);
        }

        [[nodiscard]] constexpr auto operator<=>(TimeSpan const& rhs) const noexcept = default;
    };

    static_assert(sizeof(TimeSpan) == sizeof(std::int64_t));
    static_assert(alignof(TimeSpan) == alignof(std::int64_t));

    BASE_API bool ToString(
        std::string& result,
        TimeSpan value) noexcept;

    BASE_API bool ToString(
        std::string& result,
        TimeSpan value,
        std::string_view format) noexcept;
}

namespace Graphyte
{
    [[nodiscard]] constexpr TimeSpan operator-(DateTime lhs, DateTime rhs) noexcept
    {
        return { lhs.Value - rhs.Value };
    }

    [[nodiscard]] constexpr DateTime operator+(DateTime lhs, TimeSpan rhs) noexcept
    {
        return { lhs.Value + rhs.Value };
    }

    [[nodiscard]] constexpr DateTime operator-(DateTime lhs, TimeSpan rhs) noexcept
    {
        return { lhs.Value - rhs.Value };
    }

    constexpr DateTime& operator+=(DateTime& lhs, TimeSpan rhs) noexcept
    {
        lhs.Value += rhs.Value;
        return lhs;
    }

    constexpr DateTime& operator-=(DateTime& lhs, TimeSpan rhs) noexcept
    {
        lhs.Value -= rhs.Value;
        return lhs;
    }
}

namespace Graphyte
{
    [[nodiscard]] constexpr TimeSpan operator-(TimeSpan value) noexcept
    {
        return { -value.Value };
    }

    [[nodiscard]] constexpr TimeSpan operator+(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return { lhs.Value + rhs.Value };
    }

    [[nodiscard]] constexpr TimeSpan operator-(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return { lhs.Value - rhs.Value };
    }

    constexpr TimeSpan& operator+=(TimeSpan& lhs, TimeSpan rhs) noexcept
    {
        lhs.Value += rhs.Value;
        return lhs;
    }

    constexpr TimeSpan& operator-=(TimeSpan& lhs, TimeSpan rhs) noexcept
    {
        lhs.Value -= rhs.Value;
        return lhs;
    }
}
