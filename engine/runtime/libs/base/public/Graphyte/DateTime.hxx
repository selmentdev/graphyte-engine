#pragma once
#include <Graphyte/Base.module.hxx>

// =================================================================================================
//
// DateTime implementation details.
//

namespace Graphyte::Impl
{
    static constexpr const int64_t GTicksInMicrosecond{ 10 };
    static constexpr const int64_t GTicksInMillisecond{ GTicksInMicrosecond * int64_t{ 1000 } };
    static constexpr const int64_t GTicksInSecond{ GTicksInMillisecond * int64_t{ 1000 } };
    static constexpr const int64_t GTicksInMinute{ GTicksInSecond * int64_t{ 60 } };
    static constexpr const int64_t GTicksInHour{ GTicksInMinute * int64_t{ 60 } };
    static constexpr const int64_t GTicksInDay{ GTicksInHour * int64_t{ 24 } };

    static constexpr const int32_t GDaysInYear{ 365 };
    static constexpr const int32_t GDaysIn4Years{ (4 * 365) + 1 };
    static constexpr const int32_t GDaysIn100Years{ (100 * 365) + 24 };
    static constexpr const int32_t GDaysIn400Years{ (400 * 365) + 97 };

    static constexpr const int32_t GDaysTo1601{ GDaysIn400Years * 4 };
    static constexpr const int32_t GDaysTo1899{ GDaysIn400Years * 4 + GDaysIn100Years * 3 - 367 };
    static constexpr const int32_t GDaysTo10000{ GDaysIn400Years * 25 - 366 };

    static constexpr const int64_t GTicksMinValue{ 0 };
    static constexpr const int64_t GTicksMaxValue{ GDaysTo10000 * GTicksInDay - 1 };
    static constexpr const int64_t GDateAdjustOffset{ GDaysTo1601 * GTicksInDay };
    static constexpr const int64_t GUnixAdjustOffset{ 621355968000000000 };

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
        uint16_t Year;
        uint16_t Month;
        uint16_t Day;
        uint16_t Hour;
        uint16_t Minute;
        uint16_t Second;
        uint16_t Millisecond;
        uint16_t DayOfWeek;
        uint16_t DayOfYear;

        BASE_API int64_t ToTicks() const noexcept;
        BASE_API bool IsValid() const noexcept;
    };

    struct TimeSpanMembers final
    {
        int32_t Days;
        int32_t Hours;
        int32_t Minutes;
        int32_t Seconds;
        int32_t Milliseconds;
    };

    struct DateTime;
    struct TimeSpan;
}

namespace Graphyte
{
    struct DateTime final
    {
        int64_t Value;

        BASE_API static DateTime Create(
            int year,
            int month,
            int day
        ) noexcept;

        BASE_API static DateTime Create(
            int year,
            int month,
            int day,
            int hour,
            int minute,
            int second
        ) noexcept;

        BASE_API static DateTime Create(
            int year,
            int month,
            int day,
            int hour,
            int minute,
            int second,
            int millisecond
        ) noexcept;

        BASE_API static DateTime Now() noexcept;
        BASE_API static DateTime Now(DateTimeKind kind) noexcept;

        BASE_API static DateTime Today(DateTimeKind kind) noexcept;
        BASE_API static DateTime Today() noexcept;

        BASE_API static DateTime FromUnixTimestamp(int64_t seconds) noexcept;

        BASE_API int64_t ToUnixTimestamp() noexcept;

        BASE_API TimeSpan GetTimeOfDay() const noexcept;
        BASE_API DateTime GetDate() const noexcept;
    };

    static_assert(sizeof(DateTime) == sizeof(int64_t));

    BASE_API DateTime FromCalendar(CalendarTime const& value) noexcept;

    BASE_API bool ToCalendar(CalendarTime& result, DateTime value) noexcept;

    BASE_API bool ToString(std::string& result, DateTime value, DateTimeFormat format = DateTimeFormat::DateTime) noexcept;

    BASE_API bool ToString(std::string& result, DateTime value, std::string_view format) noexcept;

    BASE_API bool FromString(DateTime& result, std::string_view value) noexcept;
}

namespace Graphyte
{
    struct TimeSpan final
    {
        int64_t Value;

        BASE_API static TimeSpan Create(
            int hours,
            int minutes,
            int seconds
        ) noexcept;

        BASE_API static TimeSpan Create(
            int days,
            int hours,
            int minutes,
            int seconds
        ) noexcept;

        BASE_API static TimeSpan Create(
            int days,
            int hours,
            int minutes,
            int seconds,
            int milliseconds
        ) noexcept;

        constexpr static TimeSpan FromSeconds(int64_t seconds) noexcept
        {
            return { seconds * Impl::GTicksInSecond };
        }

        constexpr int64_t ToSeconds() const noexcept
        {
            return Value / Impl::GTicksInSecond;
        }

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
    };

    static_assert(sizeof(TimeSpan) == sizeof(int64_t));

    BASE_API void ToMembers(TimeSpanMembers& result, TimeSpan value) noexcept;

    BASE_API TimeSpan FromMembers(TimeSpanMembers const& value) noexcept;

    BASE_API bool ToString(std::string& result, TimeSpan value) noexcept;

    BASE_API bool ToString(std::string& result, TimeSpan value, std::string_view format) noexcept;
}

namespace Graphyte
{
    constexpr bool Equals(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value == rhs.Value;
    }

    constexpr int Compare(DateTime lhs, DateTime rhs) noexcept
    {
        if (lhs.Value < rhs.Value)
        {
            return -1;
        }

        if (lhs.Value > rhs.Value)
        {
            return 1;
        }

        return 0;
    }

    constexpr bool operator==(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value == rhs.Value;
    }

    constexpr bool operator!=(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value != rhs.Value;
    }

    constexpr bool operator<=(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value <= rhs.Value;
    }

    constexpr bool operator>=(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value >= rhs.Value;
    }

    constexpr bool operator<(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value < rhs.Value;
    }

    constexpr bool operator>(DateTime lhs, DateTime rhs) noexcept
    {
        return lhs.Value > rhs.Value;
    }

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
    constexpr bool Equals(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value == rhs.Value;
    }

    constexpr int Compare(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        if (lhs.Value < rhs.Value)
        {
            return -1;
        }

        if (lhs.Value > rhs.Value)
        {
            return 1;
        }

        return 0;
    }

    constexpr bool operator==(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value == rhs.Value;
    }

    constexpr bool operator!=(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value != rhs.Value;
    }

    constexpr bool operator<=(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value <= rhs.Value;
    }

    constexpr bool operator>=(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value >= rhs.Value;
    }

    constexpr bool operator<(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value < rhs.Value;
    }

    constexpr bool operator>(TimeSpan lhs, TimeSpan rhs) noexcept
    {
        return lhs.Value > rhs.Value;
    }

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
