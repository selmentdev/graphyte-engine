#pragma once
#include <Graphyte/System.hxx>
#include <Graphyte/DateTime.hxx>
#include <Graphyte/Uuid.hxx>

namespace Graphyte::System
{
    template <>
    struct TypeConverter<POINT> final
    {
        __forceinline static System::Point ConvertPoint(POINT value) noexcept
        {
            return System::Point{
                value.x,
                value.y,
            };
        }

        __forceinline static POINT ConvertPoint(System::Point value) noexcept
        {
            return POINT{
                value.Left,
                value.Top,
            };
        }
    };

    template <>
    struct TypeConverter<SIZE> final
    {
        __forceinline static System::Size ConvertSize(SIZE value) noexcept
        {
            return System::Size{
                value.cx,
                value.cy,
            };
        }

        __forceinline static SIZE ConvertSize(System::Size value) noexcept
        {
            return SIZE{
                value.Width,
                value.Height,
            };
        }
    };

    template <>
    struct TypeConverter<RECT> final
    {
        __forceinline static System::Rect ConvertRect(RECT value) noexcept
        {
            return System::Rect{
                value.left,
                value.top,
                value.right - value.left,
                value.bottom - value.top,
            };
        }

        __forceinline static RECT ConvertRect(System::Rect value) noexcept
        {
            return RECT{
                value.Left,
                value.Top,
                value.Left + value.Width,
                value.Top + value.Height,
            };
        }
    };

    template <>
    struct TypeConverter<LARGE_INTEGER> final
    {
        __forceinline static uint64_t ConvertUInt64(LARGE_INTEGER value) noexcept
        {
            return static_cast<uint64_t>(value.QuadPart);
        }
        __forceinline static LARGE_INTEGER ConvertUInt64(uint64_t value) noexcept
        {
            LARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }

        __forceinline static int64_t ConvertInt64(LARGE_INTEGER value) noexcept
        {
            return static_cast<int64_t>(value.QuadPart);
        }
        __forceinline static LARGE_INTEGER ConvertInt64(int64_t value) noexcept
        {
            LARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }
    };

    template <>
    struct TypeConverter<ULARGE_INTEGER> final
    {
        __forceinline static uint64_t ConvertUInt64(ULARGE_INTEGER value) noexcept
        {
            return static_cast<uint64_t>(value.QuadPart);
        }
        __forceinline static ULARGE_INTEGER ConvertUInt64(uint64_t value) noexcept
        {
            ULARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }

        __forceinline static int64_t ConvertInt64(ULARGE_INTEGER value) noexcept
        {
            return static_cast<int64_t>(value.QuadPart);
        }
        __forceinline static ULARGE_INTEGER ConvertInt64(int64_t value) noexcept
        {
            ULARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }
    };

    template <>
    struct TypeConverter<SYSTEMTIME> final
    {
        __forceinline static void Convert(CalendarTime& result, const SYSTEMTIME& value) noexcept
        {
            result.Year = value.wYear;
            result.Month = value.wMonth;
            result.DayOfWeek = value.wDayOfWeek;
            result.Day = value.wDay;
            result.Hour = value.wHour;
            result.Minute = value.wMinute;
            result.Second = value.wSecond;
            result.Millisecond = value.wMilliseconds;
            result.DayOfYear = 0;
        }
        __forceinline static void Convert(SYSTEMTIME& result, const CalendarTime& value) noexcept
        {
            result.wYear = value.Year;
            result.wMonth = value.Month;
            result.wDayOfWeek = value.DayOfWeek;
            result.wDay = value.Day;
            result.wHour = value.Hour;
            result.wMinute = value.Minute;
            result.wSecond = value.Second;
            result.wMilliseconds = value.Millisecond;
        }
    };

    template <>
    struct TypeConverter<FILETIME> final
    {
        __forceinline static uint64_t ConvertUInt64(FILETIME value) noexcept
        {
            LARGE_INTEGER li{};
            li.LowPart = static_cast<decltype(li.LowPart)>(value.dwLowDateTime);
            li.HighPart = static_cast<decltype(li.HighPart)>(value.dwHighDateTime);
            return static_cast<uint64_t>(li.QuadPart);
        }
        __forceinline static FILETIME ConvertUInt64(uint64_t value) noexcept
        {
            LARGE_INTEGER li{};
            li.QuadPart = static_cast<decltype(li.QuadPart)>(value);

            FILETIME result{};
            result.dwLowDateTime = static_cast<decltype(result.dwLowDateTime)>(li.LowPart);
            result.dwHighDateTime = static_cast<decltype(result.dwHighDateTime)>(li.HighPart);
            return result;
        }
        __forceinline static int64_t ConvertInt64(FILETIME value) noexcept
        {
            return static_cast<int64_t>(ConvertUInt64(value));
        }
        __forceinline static FILETIME ConvertInt64(int64_t value) noexcept
        {
            return ConvertUInt64(static_cast<uint64_t>(value));
        }
        __forceinline static DateTime ConvertDateTime(FILETIME value) noexcept
        {
            return DateTime
            {
                ConvertInt64(value) + Graphyte::Impl::GDateAdjustOffset
            };
        }
        __forceinline static FILETIME ConvertDateTime(DateTime value) noexcept
        {
            return ConvertInt64(value.Value - Graphyte::Impl::GDateAdjustOffset);
        }
    };
}

namespace Graphyte::System
{
    template <>
    struct TypeConverter<GUID> final
    {
        union UuidGuid
        {
            GUID AsGuid;
            Uuid AsUuid;
        };
        static_assert(sizeof(UuidGuid) == sizeof(GUID));

        static GUID ConvertGuid(Uuid value) noexcept
        {
            UuidGuid pun;

            pun.AsUuid = value;
            return pun.AsGuid;
        }

        static Uuid ConvertGuid(GUID value) noexcept
        {
            UuidGuid pun;
            pun.AsGuid = value;
            return pun.AsUuid;
        }
    };
}
