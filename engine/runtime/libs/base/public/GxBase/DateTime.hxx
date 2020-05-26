#pragma once
#include <GxBase/Base.module.hxx>

// =================================================================================================
//
// DateTime implementation details.
//

namespace Graphyte::Impl
{
    static constexpr const std::int64_t GTicksInMicrosecond{ 10 };
    static constexpr const std::int64_t GTicksInMillisecond{ GTicksInMicrosecond * std::int64_t{ 1000 } };
    static constexpr const std::int64_t GTicksInSecond{ GTicksInMillisecond * std::int64_t{ 1000 } };
    static constexpr const std::int64_t GTicksInMinute{ GTicksInSecond * std::int64_t{ 60 } };
    static constexpr const std::int64_t GTicksInHour{ GTicksInMinute * std::int64_t{ 60 } };
    static constexpr const std::int64_t GTicksInDay{ GTicksInHour * std::int64_t{ 24 } };

    static constexpr const std::int64_t GMaxSeconds = std::numeric_limits<std::int64_t>::max() / GTicksInSecond;
    static constexpr const std::int64_t GMinSeconds = std::numeric_limits<std::int64_t>::min() / GTicksInSecond;

    static constexpr const std::int32_t GDaysInYear{ 365 };
    static constexpr const std::int32_t GDaysIn4Years{ (4 * 365) + 1 };
    static constexpr const std::int32_t GDaysIn100Years{ (100 * 365) + 24 };
    static constexpr const std::int32_t GDaysIn400Years{ (400 * 365) + 97 };

    static constexpr const std::int32_t GDaysTo1601{ GDaysIn400Years * 4 };
    static constexpr const std::int32_t GDaysTo1899{ GDaysIn400Years * 4 + GDaysIn100Years * 3 - 367 };
    static constexpr const std::int32_t GDaysTo10000{ GDaysIn400Years * 25 - 366 };

    static constexpr const std::int64_t GTicksMinValue{ 0 };
    static constexpr const std::int64_t GTicksMaxValue{ GDaysTo10000 * GTicksInDay - 1 };
    static constexpr const std::int64_t GDateAdjustOffset{ GDaysTo1601 * GTicksInDay };
    static constexpr const std::int64_t GUnixAdjustOffset{ 621355968000000000 };

    static_assert(GDaysTo1601 == 584388, "Invalid number of days from 0001-01-01 to 1601-12-31");
    static_assert(GDaysTo1899 == 693593, "Invalid number of days from 0001-01-01 to 1899-12-31");
    static_assert(GDaysTo10000 == 3652059, "Invalid number of days from 0001-01-01 to 9999-12-31");
    static_assert(GTicksInSecond == 10000000, "Invalid number of ticks in second");
    static_assert(GDateAdjustOffset == 504911232000000000, "Invalid number of ticks for time adjustment");
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
        First = 1,
        January = 1,
        February = 2,
        March = 3,
        April = 4,
        May = 5,
        June = 6,
        July = 7,
        August = 8,
        September = 9,
        October = 10,
        November = 11,
        December = 12,
        Count = 12,
        Last = 12
    };

    enum struct WeekDay
    {
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6,
        Count = 7
    };

    enum struct DateTimeFormat
    {
        Date,
        Time,
        DateTime,
        FileSafe,
        TimeStamp,
        DateIso8601 = Date,
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

        BASE_API std::int64_t ToTicks() const noexcept;
        BASE_API bool IsValid() const noexcept;
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

        BASE_API static DateTime Create(
            std::int32_t year,
            std::int32_t month,
            std::int32_t day
        ) noexcept;

        BASE_API static DateTime Create(
            std::int32_t year,
            std::int32_t month,
            std::int32_t day,
            std::int32_t hour,
            std::int32_t minute,
            std::int32_t second
        ) noexcept;

        BASE_API static DateTime Create(
            std::int32_t year,
            std::int32_t month,
            std::int32_t day,
            std::int32_t hour,
            std::int32_t minute,
            std::int32_t second,
            std::int32_t millisecond
        ) noexcept;

        BASE_API static DateTime Now() noexcept;
        BASE_API static DateTime Now(DateTimeKind kind) noexcept;

        BASE_API static DateTime Today(DateTimeKind kind) noexcept;
        BASE_API static DateTime Today() noexcept;

        BASE_API static DateTime FromUnixTimestamp(std::int64_t seconds) noexcept;

        BASE_API static DateTime FromCalendar(CalendarTime const& value) noexcept;

        BASE_API bool ToCalendar(CalendarTime& result) noexcept;

        BASE_API std::int64_t ToUnixTimestamp() noexcept;

        BASE_API TimeSpan GetTimeOfDay() const noexcept;
        BASE_API DateTime GetDate() const noexcept;

        constexpr auto operator <=> (DateTime const& rhs) const noexcept = default;
    };

    static_assert(sizeof(DateTime) == sizeof(std::int64_t));

    BASE_API bool ToString(
        std::string& result,
        DateTime value,
        DateTimeFormat format = DateTimeFormat::DateTime
    ) noexcept;

    BASE_API bool ToString(
        std::string& result,
        DateTime value,
        std::string_view format
    ) noexcept;

    BASE_API bool FromString(
        DateTime& result,
        std::string_view value
    ) noexcept;
}

namespace Graphyte
{
    struct TimeSpan final
    {
        std::int64_t Value;

        BASE_API static TimeSpan Create(
            std::int32_t hours,
            std::int32_t minutes,
            std::int32_t seconds
        ) noexcept;

        BASE_API static TimeSpan Create(
            std::int32_t days,
            std::int32_t hours,
            std::int32_t minutes,
            std::int32_t seconds
        ) noexcept;

        BASE_API static TimeSpan Create(
            std::int32_t days,
            std::int32_t hours,
            std::int32_t minutes,
            std::int32_t seconds,
            std::int32_t milliseconds
        ) noexcept;

        constexpr static TimeSpan FromSeconds(std::int64_t seconds) noexcept
        {
            return { seconds * Impl::GTicksInSecond };
        }

        constexpr std::int64_t ToSeconds() const noexcept
        {
            return Value / Impl::GTicksInSecond;
        }

        BASE_API void ToMembers(
            TimeSpanMembers& result
        ) noexcept;

        BASE_API static TimeSpan FromMembers(
            TimeSpanMembers const& value
        ) noexcept;

        TimeSpan GetDuration() const noexcept
        {
            return { std::abs(Value) };
        }

        constexpr double GetTotalDays() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::GTicksInDay);
        }

        constexpr double GetTotalHours() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::GTicksInHour);
        }

        constexpr double GetTotalMinutes() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::GTicksInMinute);
        }

        constexpr double GetTotalSeconds() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::GTicksInSecond);
        }

        constexpr double GetTotalMilliseconds() const noexcept
        {
            return static_cast<double>(Value) / static_cast<double>(Impl::GTicksInMillisecond);
        }

        constexpr auto operator <=> (TimeSpan const& rhs) const noexcept = default;
    };

    static_assert(sizeof(TimeSpan) == sizeof(std::int64_t));
    static_assert(alignof(TimeSpan) == alignof(std::int64_t));

    BASE_API bool ToString(
        std::string& result,
        TimeSpan value
    ) noexcept;

    BASE_API bool ToString(
        std::string& result,
        TimeSpan value,
        std::string_view format
    ) noexcept;
}

namespace Graphyte
{
    constexpr TimeSpan operator-(DateTime lhs, DateTime rhs) noexcept
    {
        return { lhs.Value - rhs.Value };
    }

    constexpr DateTime operator+(DateTime lhs, TimeSpan rhs) noexcept
    {
        return { lhs.Value + rhs.Value };
    }

    constexpr DateTime operator-(DateTime lhs, TimeSpan rhs) noexcept
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
    constexpr TimeSpan operator-(TimeSpan value) noexcept
    {
        return { -value.Value };
    }

    constexpr TimeSpan operator+(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return { lhs.Value + rhs.Value };
    }

    constexpr TimeSpan operator-(TimeSpan lhs, TimeSpan rhs) noexcept
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
