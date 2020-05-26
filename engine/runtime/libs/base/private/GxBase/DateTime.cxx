#include <GxBase/DateTime.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>

namespace Graphyte::Impl
{
    static constexpr const std::int32_t GDaysPerMonth[12] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    static constexpr const std::int32_t GDaysToMonth365[13] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
    };
    static constexpr const std::int32_t GDaysToMonth366[13] = {
        0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366,
    };

    static constexpr const std::int32_t GDaysBeforeMonth[12] = {
        0,
        31,
        31 + 28,
        31 + 28 + 31,
        31 + 28 + 31 + 30,
        31 + 28 + 31 + 30 + 31,
        31 + 28 + 31 + 30 + 31 + 30,
        31 + 28 + 31 + 30 + 31 + 30 + 31,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
        31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30
    };

    static constexpr bool IsLeapYear(std::int32_t year) noexcept
    {
        return ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
    }

    static constexpr std::int32_t DaysInMonth(std::int32_t year, std::int32_t month) noexcept
    {
        bool const leap_year = IsLeapYear(year);
        auto const& days_to_month = leap_year ? GDaysToMonth366 : GDaysToMonth365;

        return days_to_month[month] - days_to_month[month - 1];
    }

    static constexpr std::int64_t YearToTicks(std::int32_t year) noexcept
    {
        --year;

        auto const days =
            static_cast<std::int64_t>(year) * 365 +
            static_cast<std::int64_t>(year) / 4 -
            static_cast<std::int64_t>(year) / 100 +
            static_cast<std::int64_t>(year) / 400;

        return days * Impl::GTicksInDay;
    }

    static std::int64_t DateToTicks(
        std::int32_t year,
        std::int32_t month,
        std::int32_t day
    ) noexcept
    {
        GX_ASSERT((year >= 1) && (year <= 9999));
        GX_ASSERT((month >= 1) && (month <= 12));
        GX_ASSERT((day >= 1) && (day <= 31));

        bool is_leap_year = Impl::IsLeapYear(year);
        std::int32_t days_in_month = GDaysPerMonth[month - 1];

        if ((month == 2) && is_leap_year)
        {
            ++days_in_month;
        }

        GX_ASSERT((day >= 1) && (day <= days_in_month));

        std::int64_t result = YearToTicks(year) / Impl::GTicksInDay;
        result += static_cast<std::int64_t>(Impl::GDaysBeforeMonth[month - 1]);

        if ((month > 2) && is_leap_year)
        {
            ++result;
        }

        auto const days = (result + static_cast<std::int64_t>(day) - 1);

        return days * Impl::GTicksInDay;
    }

    static std::int64_t TimeToTicks(
        std::int32_t hour,
        std::int32_t minute,
        std::int32_t second
    ) noexcept
    {
        GX_ASSERT((hour >= 0) && (hour <= 23));
        GX_ASSERT((minute >= 0) && (minute <= 59));
        GX_ASSERT((second >= 0) && (second <= 59));

        std::int64_t const seconds = (static_cast<std::int64_t>(hour) * 3600
            + static_cast<std::int64_t>(minute) * 60
            + static_cast<std::int64_t>(second));

        return seconds * Impl::GTicksInSecond;

    }

    static constexpr void GetDatePart(
        std::int64_t ticks,
        std::int32_t& year,
        std::int32_t& month,
        std::int32_t& day,
        std::int32_t& year_day,
        std::int32_t& week_day
    ) noexcept
    {
        int32_t n = static_cast<int32_t>(ticks / GTicksInDay);

        week_day = (n + 1) % 7;

        int32_t y400 = n / GDaysIn400Years;
        n -= y400 * GDaysIn400Years;
        int32_t y100 = n / GDaysIn100Years;

        if (y100 == 4)
        {
            y100 = 3;
        }

        n -= y100 * GDaysIn100Years;

        int32_t y4 = n / GDaysIn4Years;
        n -= y4 * GDaysIn4Years;

        int32_t y1 = n / GDaysInYear;

        if (y1 == 4)
        {
            y1 = 3;
        }

        year = y400 * 400 + y100 * 100 + y4 * 4 + y1 + 1;

        n -= y1 * GDaysInYear;

        year_day = n + 1;

        bool is_leap = (y1 == 3 && (y4 != 24 || y100 == 3));

        auto const& days = is_leap ? GDaysToMonth366 : GDaysToMonth365;

        int32_t m = (n >> 5) + 1;

        while (n >= days[m])
        {
            ++m;
        }

        month = m;
        day = n - days[m - 1] + 1;
    }

    static constexpr void GetTimePart(
        std::int64_t ticks,
        std::int32_t& hour,
        std::int32_t& minute,
        std::int32_t& second,
        std::int32_t& millisecond
    ) noexcept
    {
        std::int64_t n = ticks / Impl::GTicksInMillisecond;

        millisecond = static_cast<std::int32_t>(n % 1000);
        n = n / 1000;

        second = static_cast<std::int32_t>(n % 60);
        n = n / 60;

        minute = static_cast<std::int32_t>(n % 60);
        n = n / 60;

        hour = static_cast<std::int32_t>(n % 24);
    }
}

namespace Graphyte
{
    BASE_API std::int64_t CalendarTime::ToTicks() const noexcept
    {
        std::int64_t const ticksDate = Impl::DateToTicks(this->Year, this->Month, this->Day);
        std::int64_t const ticksTime = Impl::TimeToTicks(this->Hour, this->Minute, this->Second);
        std::int64_t const ticksMillisecond = this->Millisecond * Impl::GTicksInMillisecond;

        return ticksDate + ticksTime + ticksMillisecond;
    }

    BASE_API bool CalendarTime::IsValid() const noexcept
    {
        return (this->Year >= 1)
            && (this->Year <= 9999)
            && (this->Month >= 1)
            && (this->Month <= 12)
            && (this->Day >= 1)
            && (this->Day <= Impl::DaysInMonth(this->Year, this->Month))
            && (this->Hour <= 23)
            && (this->Minute <= 59)
            && (this->Second <= 59)
            && (this->Millisecond <= 999);
    }
}

namespace Graphyte
{
    BASE_API DateTime DateTime::Create(
        std::int32_t year,
        std::int32_t month,
        std::int32_t day
    ) noexcept
    {
        return {
            Impl::DateToTicks(year, month, day)
        };
    }

    BASE_API DateTime DateTime::Create(
        std::int32_t year,
        std::int32_t month,
        std::int32_t day,
        std::int32_t hour,
        std::int32_t minute,
        std::int32_t second
    ) noexcept
    {
        return {
            Impl::DateToTicks(year, month, day) +
            Impl::TimeToTicks(hour, minute, second)
        };
    }

    BASE_API DateTime DateTime::Create(
        std::int32_t year,
        std::int32_t month,
        std::int32_t day,
        std::int32_t hour,
        std::int32_t minute,
        std::int32_t second,
        std::int32_t millisecond
    ) noexcept
    {
        return {
            Impl::DateToTicks(year, month, day) +
            Impl::TimeToTicks(hour, minute, second) +
            static_cast<std::int64_t>(millisecond)* Impl::GTicksInMillisecond
        };
    }

    BASE_API DateTime DateTime::Now() noexcept
    {
        std::int64_t ticks = Impl::GDateAdjustOffset;
        ticks += System::GetLocalTime();
        return DateTime{ ticks };
    }

    BASE_API DateTime DateTime::Now(DateTimeKind kind) noexcept
    {
        std::int64_t ticks = Impl::GDateAdjustOffset;

        if (kind == DateTimeKind::Local)
        {
            ticks += System::GetLocalTime();
        }
        else
        {
            ticks += System::GetSystemTime();
        }

        return DateTime{ ticks };
    }

    BASE_API DateTime DateTime::Today(DateTimeKind kind) noexcept
    {
        return DateTime::Now(kind).GetDate();
    }

    BASE_API DateTime DateTime::Today() noexcept
    {
        return DateTime::Now().GetDate();
    }

    BASE_API DateTime DateTime::FromUnixTimestamp(std::int64_t seconds) noexcept
    {
        return DateTime::Create(1970, 1, 1) + TimeSpan::FromSeconds(seconds);
    }

    BASE_API std::int64_t DateTime::ToUnixTimestamp() noexcept
    {
        return (this->Value - DateTime::Create(1970, 1, 1).Value) / Impl::GTicksInSecond;
    }

    BASE_API TimeSpan DateTime::GetTimeOfDay() const noexcept
    {
        return TimeSpan
        {
            this->Value % Impl::GTicksInDay
        };
    }

    BASE_API DateTime DateTime::GetDate() const noexcept
    {
        return DateTime
        {
            this->Value - (this->Value % Impl::GTicksInDay)
        };
    }

    BASE_API DateTime DateTime::FromCalendar(CalendarTime const& value) noexcept
    {
        return DateTime::Create(
            value.Year,
            value.Month,
            value.Day,
            value.Hour,
            value.Minute,
            value.Second,
            value.Millisecond
        );
    }

    BASE_API bool DateTime::ToCalendar(CalendarTime& result) noexcept
    {
        Impl::GetDatePart(
            this->Value,
            result.Year,
            result.Month,
            result.Day,
            result.DayOfYear,
            result.DayOfWeek
        );

        Impl::GetTimePart(
            this->Value,
            result.Hour,
            result.Minute,
            result.Second,
            result.Millisecond
        );

        return true;
    }

    BASE_API bool ToString(std::string& result, DateTime value, DateTimeFormat format) noexcept
    {
        CalendarTime time;
        value.ToCalendar(time);

        switch (format)
        {
        case DateTimeFormat::Date:
            {
                result = fmt::format(
                    "{:04d}-{:02d}-{:02d}",
                    time.Year,
                    time.Month,
                    time.Day
                );
                break;
            }

        case DateTimeFormat::Time:
            {
                result = fmt::format(
                    "{:02d}:{:02d}:{:02d}",
                    time.Hour,
                    time.Minute,
                    time.Second
                );
                break;
            }

        case DateTimeFormat::FileSafe:
            {
                result = fmt::format(
                    "{:04d}.{:02d}.{:02d}-{:02d}.{:02d}.{:02d}",
                    time.Year,
                    time.Month,
                    time.Day,
                    time.Hour,
                    time.Minute,
                    time.Second
                );
                break;
            }

        case DateTimeFormat::DateTime:
            {
                result = fmt::format(
                    "{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}",
                    time.Year,
                    time.Month,
                    time.Day,
                    time.Hour,
                    time.Minute,
                    time.Second
                );
                break;
            }

        case DateTimeFormat::TimeStamp:
            {
                result = fmt::format(
                    "{:04d}.{:02d}.{:02d}-{:02d}.{:02d}.{:02d}.{:03d}",
                    time.Year,
                    time.Month,
                    time.Day,
                    time.Hour,
                    time.Minute,
                    time.Second,
                    time.Millisecond
                );
                break;
            }

        default:
            {
                GX_ASSERTF(false, "Unknown date time format `{}`", static_cast<uint32_t>(format));
                break;
            }
        }

        return true;
    }

    BASE_API bool ToString(std::string& result, DateTime value, std::string_view format) noexcept
    {
        CalendarTime time{};
        value.ToCalendar(time);

        bool const isMorning = time.Hour < 12;

        bool saw_percent = false;

        fmt::memory_buffer buffer{};

        for (char const ch : format)
        {
            if (ch == '%')
            {
                if (saw_percent)
                {
                    //
                    // Output percent sign as we saw `%` twice.
                    //
                    buffer.push_back('%');
                    saw_percent = false;
                }
                else
                {
                    //
                    // It's first time we saw this sign.
                    //
                    saw_percent = true;
                    continue;
                }
            }

            if (saw_percent)
            {
                saw_percent = false;

                //
                // If we saw `%` sign. `ch` contains formatter character.
                //

                switch (ch)
                {
                case 'a':
                    {
                        const char* ampm = isMorning ? "am" : "pm";
                        buffer.append(ampm, ampm + 2);
                        break;
                    }
                case 'A':
                    {
                        const char* ampm = isMorning ? "AM" : "PM";
                        buffer.append(ampm, ampm + 2);
                        break;
                    }
                case 'd':
                    {
                        fmt::format_to(buffer, "{:02}", time.Day);
                        break;
                    }
                case 'D':
                    {
                        fmt::format_to(buffer, "{:03}", time.DayOfYear);
                        break;
                    }
                case 'm':
                    {
                        fmt::format_to(buffer, "{:02}", time.Month);
                        break;
                    }
                case 'y':
                    {
                        fmt::format_to(buffer, "{:02}", time.Year % 100);
                        break;
                    }
                case 'Y':
                    {
                        fmt::format_to(buffer, "{}", time.Year);
                        break;
                    }
                case 'h':
                    {
                        fmt::format_to(buffer, "{:02}", time.Hour % 12);
                        break;
                    }
                case 'H':
                    {
                        fmt::format_to(buffer, "{:02}", time.Hour);
                        break;
                    }
                case 'M':
                    {
                        fmt::format_to(buffer, "{:02}", time.Minute);
                        break;
                    }
                case 'S':
                    {
                        fmt::format_to(buffer, "{:02}", time.Second);
                        break;
                    }
                case 's':
                    {
                        fmt::format_to(buffer, "{:03}", time.Millisecond);
                        break;
                    }
                default:
                    {
                        GX_ASSERTF(false, "Unknown format specifier: {:c}", ch);
                        buffer.push_back(ch);
                        break;
                    }
                }
            }
            else
            {
                //
                // Put character to buffer.
                //
                buffer.push_back(ch);
            }
        }

        GX_ASSERTF(saw_percent == false, "Unterminated string. Saw percent sign without specifier");

        result.assign(
            std::data(buffer),
            std::size(buffer)
        );

        return true;
    }

    BASE_API bool FromString(DateTime& result, std::string_view format) noexcept
    {
        bool valid = true;

        CalendarTime time{};
        int32_t timezone_hours{};
        int32_t timezone_minutes{};
        int32_t timezone_sign = 0;

        auto* ptr_begin = std::data(format);
        auto* ptr_end = std::data(format) + std::size(format);

        // Parse year.
        auto [sep1, ecc1] = std::from_chars(ptr_begin, ptr_end, time.Year, 10);

        if (std::distance(ptr_begin, sep1) != 4 || ecc1 != std::errc{} || *sep1 != '-')
        {
            return false;
        }


        // Parse month.
        auto [sep2, ecc2] = std::from_chars(sep1 + 1, ptr_end, time.Month, 10);

        if (std::distance(sep1 + 1, sep2) != 2 || ecc2 != std::errc{} || *sep2 != '-')
        {
            return false;
        }

        // Parse day.
        auto [sep3, ecc3] = std::from_chars(sep2 + 1, ptr_end, time.Day, 10);

        if (std::distance(sep2 + 1, sep3) != 2 || ecc3 != std::errc{})
        {
            // Cannot parse day.
            return false;
        }

        //
        // Check if we have time specifier.
        //
        if (sep3 != ptr_end && *sep3 == 'T')
        {
            // Parse hour
            auto [sep4, ecc4] = std::from_chars(sep3 + 1, ptr_end, time.Hour, 10);

            if (std::distance(sep3 + 1, sep4) != 2 || ecc4 != std::errc{} || *sep4 != ':')
            {
                return false;
            }

            // Parse minute.
            auto [sep5, ecc5] = std::from_chars(sep4 + 1, ptr_end, time.Minute, 10);

            if (std::distance(sep4 + 1, sep5) != 2 || ecc5 != std::errc{} || *sep5 != ':')
            {
                return false;
            }

            // Parse second.
            auto [sep6, ecc6] = std::from_chars(sep5 + 1, ptr_end, time.Second, 10);

            if (std::distance(sep5 + 1, sep6) != 2 || ecc6 != std::errc{})
            {
                return false;
            }

            // Parse optional milliseconds
            if (sep6 != ptr_end && *sep6 == '.')
            {
                auto [sep7, ecc7] = std::from_chars(sep6 + 1, ptr_end, time.Millisecond, 10);

                if (std::distance(sep6 + 1, sep7) != 3 || ecc7 != std::errc{})
                {
                    return false;
                }

                //
                // Copy over last location.
                //
                sep6 = sep7;
                ecc6 = ecc7;
            }

            if (sep6 != ptr_end)
            {
                //
                // Parse timezone sign.
                if (*sep6 == '+')
                {
                    timezone_sign = 1;
                }
                else if (*sep6 == '-')
                {
                    timezone_sign = -1;
                }

                if (timezone_sign != 0)
                {
                    auto [sep7, ecc7] = std::from_chars(sep6 + 1, ptr_end, timezone_hours, 10);
                    if (std::distance(sep6 + 1, sep7) != 2 || ecc7 != std::errc{} || *sep7 != ':')
                    {
                        return false;
                    }

                    auto [sep8, ecc8] = std::from_chars(sep7 + 1, ptr_end, timezone_minutes, 10);
                    if (std::distance(sep7 + 1, sep8) != 2 || ecc8 != std::errc{})
                    {
                        return false;
                    }

                    valid = (sep8 == ptr_end);
                }
            }
        }
        else
        {
            valid = (sep3 == ptr_end);
        }

        if (valid)
        {
            result = DateTime::FromCalendar(time);

            std::int32_t timezone_offset = timezone_sign * (timezone_hours * 60 + timezone_minutes);
            result.Value -= Impl::GTicksInMinute * timezone_offset;
        }

        return valid;
    }
}

namespace Graphyte::Impl
{
    static bool ComputeTimeSpanTicks(
        std::int64_t& result,
        std::int32_t days,
        std::int32_t hours,
        std::int32_t minutes,
        std::int32_t seconds,
        std::int32_t milliseconds
    ) noexcept
    {
        std::int64_t const hours_as_seconds = static_cast<std::int64_t>(hours) * 3600;
        std::int64_t const minutes_as_seconds = static_cast<std::int64_t>(minutes) * 60;
        std::int64_t const as_seconds = hours_as_seconds + minutes_as_seconds + seconds;
        std::int64_t const as_milliseconds = as_seconds * std::int64_t{ 1000 };
        std::int64_t const total_milliseconds = as_milliseconds + static_cast<std::int64_t>(milliseconds);

        std::int64_t const ticks = total_milliseconds * Impl::GTicksInMillisecond;

        bool overflow = false;

        std::int64_t const ticks_per_day = Impl::GTicksInDay * days;
        std::int64_t const biased_ticks = ticks + ticks_per_day;

        if (days > 0)
        {
            if (ticks < 0)
            {
                overflow = (ticks > biased_ticks);
            }
            else
            {
                overflow = (biased_ticks < 0);
            }
        }
        else if (days < 0)
        {
            if (ticks <= 0)
            {
                overflow = (biased_ticks > 0);
            }
            else
            {
                overflow = (ticks > biased_ticks);
            }
        }

        if (overflow != false)
        {
            return false;
        }

        result = biased_ticks;
        return true;
    }
}

namespace Graphyte
{
    BASE_API TimeSpan TimeSpan::Create(
        std::int32_t hours,
        std::int32_t minutes,
        std::int32_t seconds
    ) noexcept
    {
        std::int64_t ticks{};
        Impl::ComputeTimeSpanTicks(ticks, 0, hours, minutes, seconds, 0);
        return { ticks };
    }

    BASE_API TimeSpan TimeSpan::Create(
        std::int32_t days,
        std::int32_t hours,
        std::int32_t minutes,
        std::int32_t seconds
    ) noexcept
    {
        std::int64_t ticks{};
        Impl::ComputeTimeSpanTicks(ticks, days, hours, minutes, seconds, 0);
        return { ticks };
    }

    BASE_API TimeSpan TimeSpan::Create(
        std::int32_t days,
        std::int32_t hours,
        std::int32_t minutes,
        std::int32_t seconds,
        std::int32_t milliseconds
    ) noexcept
    {
        std::int64_t ticks{};
        Impl::ComputeTimeSpanTicks(ticks, days, hours, minutes, seconds, milliseconds);
        return { ticks };
    }

    BASE_API void TimeSpan::ToMembers(TimeSpanMembers& result) noexcept
    {
        result.Days         = static_cast<std::int32_t>(this->Value / Impl::GTicksInDay);
        result.Hours        = static_cast<std::int32_t>((this->Value % Impl::GTicksInDay) / Impl::GTicksInHour);
        result.Minutes      = static_cast<std::int32_t>((this->Value % Impl::GTicksInHour) / Impl::GTicksInMinute);
        result.Seconds      = static_cast<std::int32_t>((this->Value % Impl::GTicksInMinute) / Impl::GTicksInSecond);
        result.Milliseconds = static_cast<std::int32_t>((this->Value % Impl::GTicksInSecond) / Impl::GTicksInMillisecond);
    }

    BASE_API TimeSpan TimeSpan::FromMembers(const TimeSpanMembers& value) noexcept
    {
        std::int64_t ticks = value.Days * Impl::GTicksInDay;
        ticks += value.Hours * Impl::GTicksInHour;
        ticks += value.Minutes * Impl::GTicksInMinute;
        ticks += value.Seconds * Impl::GTicksInSecond;
        ticks += value.Milliseconds * Impl::GTicksInMillisecond;
        return { ticks };
    }

    BASE_API bool ToString(std::string& result, TimeSpan value) noexcept
    {
        const char* format = (value.Value < Impl::GTicksInDay)
            ? "%n%h:%m:%s.%f"
            : "%n%d.%h:%m:%s.%f";

        return ToString(result, value, format);
    }

    BASE_API bool ToString(std::string& result, TimeSpan value, std::string_view format) noexcept
    {
        TimeSpanMembers members{};
        value.ToMembers(members);

        fmt::memory_buffer buffer{};

        bool percentSign = false;

        for (const char ch : format)
        {
            if (ch == '%')
            {
                percentSign = true;
                continue;
            }

            if (percentSign)
            {
                switch (ch)
                {
                case 'n':
                    {
                        if (value.Value < 0)
                        {
                            buffer.push_back('-');
                        }
                        break;
                    }
                case 'N':
                    {
                        buffer.push_back((value.Value < 0) ? '-' : '+');
                        break;
                    }
                case 'd':
                    {
                        fmt::format_to(buffer, "{}", std::abs(members.Days));
                        break;
                    }
                case 'h':
                    {
                        fmt::format_to(buffer, "{:02d}", std::abs(members.Hours));
                        break;
                    }
                case 'm':
                    {
                        fmt::format_to(buffer, "{:02d}", std::abs(members.Minutes));
                        break;
                    }
                case 's':
                    {
                        fmt::format_to(buffer, "{:02d}", std::abs(members.Seconds));
                        break;
                    }
                case 'f':
                    {
                        fmt::format_to(buffer, "{:03d}", std::abs(members.Milliseconds));
                        break;
                    }
                case 'D':
                    {
                        fmt::format_to(buffer, "{}", std::abs(value.GetTotalDays()));
                        break;
                    }
                case 'H':
                    {
                        fmt::format_to(buffer, "{:02d}", std::abs(value.GetTotalHours()));
                        break;
                    }
                case 'M':
                    {
                        fmt::format_to(buffer, "{:02d}", std::abs(value.GetTotalMinutes()));
                        break;
                    }
                case 'S':
                    {
                        fmt::format_to(buffer, "{:02d}", std::abs(value.GetTotalSeconds()));
                        break;
                    }
                case 'F':
                    {
                        fmt::format_to(buffer, "{:03d}", std::abs(value.GetTotalMilliseconds()));
                        break;
                    }
                default:
                    {
                        buffer.push_back(ch);
                        break;
                    }
                }

                percentSign = false;
            }
            else
            {
                buffer.push_back(ch);
            }
        }

        GX_ASSERT(percentSign == false);

        result.assign(buffer.data(), buffer.size());
        return true;
    }
}
