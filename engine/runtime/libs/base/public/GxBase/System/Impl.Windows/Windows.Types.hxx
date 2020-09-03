#pragma once
#include <GxBase/System.hxx>
#include <GxBase/DateTime.hxx>
#include <GxBase/Uuid.hxx>
#include <GxBase/Bitwise.hxx>

namespace Graphyte::System
{
    template <>
    struct TypeConverter<POINT> final
    {
        [[nodiscard]] __forceinline static System::Point ConvertPoint(POINT value) noexcept
        {
            return System::Point{
                value.x,
                value.y,
            };
        }

        [[nodiscard]] __forceinline static POINT ConvertPoint(System::Point value) noexcept
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
        [[nodiscard]] __forceinline static System::Size ConvertSize(SIZE value) noexcept
        {
            return System::Size{
                value.cx,
                value.cy,
            };
        }

        [[nodiscard]] __forceinline static SIZE ConvertSize(System::Size value) noexcept
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
        [[nodiscard]] __forceinline static System::Rect ConvertRect(RECT value) noexcept
        {
            return System::Rect{
                value.left,
                value.top,
                value.right - value.left,
                value.bottom - value.top,
            };
        }

        [[nodiscard]] __forceinline static RECT ConvertRect(System::Rect value) noexcept
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
        [[nodiscard]] __forceinline static uint64_t ConvertUInt64(LARGE_INTEGER value) noexcept
        {
            return static_cast<uint64_t>(value.QuadPart);
        }
        [[nodiscard]] __forceinline static LARGE_INTEGER ConvertUInt64(uint64_t value) noexcept
        {
            LARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }

        [[nodiscard]] __forceinline static int64_t ConvertInt64(LARGE_INTEGER value) noexcept
        {
            return static_cast<int64_t>(value.QuadPart);
        }
        [[nodiscard]] __forceinline static LARGE_INTEGER ConvertInt64(int64_t value) noexcept
        {
            LARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }
    };

    template <>
    struct TypeConverter<ULARGE_INTEGER> final
    {
        [[nodiscard]] __forceinline static uint64_t ConvertUInt64(ULARGE_INTEGER value) noexcept
        {
            return static_cast<uint64_t>(value.QuadPart);
        }
        [[nodiscard]] __forceinline static ULARGE_INTEGER ConvertUInt64(uint64_t value) noexcept
        {
            ULARGE_INTEGER result{};
            result.QuadPart = static_cast<decltype(result.QuadPart)>(value);
            return result;
        }

        [[nodiscard]] __forceinline static int64_t ConvertInt64(ULARGE_INTEGER value) noexcept
        {
            return static_cast<int64_t>(value.QuadPart);
        }

        [[nodiscard]] __forceinline static ULARGE_INTEGER ConvertInt64(int64_t value) noexcept
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
            result.Year        = value.wYear;
            result.Month       = value.wMonth;
            result.DayOfWeek   = value.wDayOfWeek;
            result.Day         = value.wDay;
            result.Hour        = value.wHour;
            result.Minute      = value.wMinute;
            result.Second      = value.wSecond;
            result.Millisecond = value.wMilliseconds;
            result.DayOfYear   = 0;
        }

        __forceinline static void Convert(SYSTEMTIME& result, const CalendarTime& value) noexcept
        {
            result.wYear         = static_cast<WORD>(value.Year);
            result.wMonth        = static_cast<WORD>(value.Month);
            result.wDayOfWeek    = static_cast<WORD>(value.DayOfWeek);
            result.wDay          = static_cast<WORD>(value.Day);
            result.wHour         = static_cast<WORD>(value.Hour);
            result.wMinute       = static_cast<WORD>(value.Minute);
            result.wSecond       = static_cast<WORD>(value.Second);
            result.wMilliseconds = static_cast<WORD>(value.Millisecond);
        }
    };

    template <>
    struct TypeConverter<FILETIME> final
    {
        [[nodiscard]] __forceinline static uint64_t ConvertUInt64(FILETIME value) noexcept
        {
            LARGE_INTEGER li{};
            li.LowPart  = static_cast<decltype(li.LowPart)>(value.dwLowDateTime);
            li.HighPart = static_cast<decltype(li.HighPart)>(value.dwHighDateTime);
            return static_cast<uint64_t>(li.QuadPart);
        }
        [[nodiscard]] __forceinline static FILETIME ConvertUInt64(uint64_t value) noexcept
        {
            LARGE_INTEGER li{};
            li.QuadPart = static_cast<decltype(li.QuadPart)>(value);

            FILETIME result{};
            result.dwLowDateTime  = static_cast<decltype(result.dwLowDateTime)>(li.LowPart);
            result.dwHighDateTime = static_cast<decltype(result.dwHighDateTime)>(li.HighPart);
            return result;
        }
        [[nodiscard]] __forceinline static int64_t ConvertInt64(FILETIME value) noexcept
        {
            return static_cast<int64_t>(ConvertUInt64(value));
        }
        [[nodiscard]] __forceinline static FILETIME ConvertInt64(int64_t value) noexcept
        {
            return ConvertUInt64(static_cast<uint64_t>(value));
        }
        [[nodiscard]] __forceinline static DateTime ConvertDateTime(FILETIME value) noexcept
        {
            return DateTime{
                ConvertInt64(value) + Graphyte::Impl::GDateAdjustOffset
            };
        }
        [[nodiscard]] __forceinline static FILETIME ConvertDateTime(DateTime value) noexcept
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

        [[nodiscard]] static GUID ConvertGuid(Uuid value) noexcept
        {
            return BitCast<GUID>(value);
            /*UuidGuid pun;

            pun.AsUuid = value;
            return pun.AsGuid;*/
        }

        [[nodiscard]] static Uuid ConvertGuid(GUID value) noexcept
        {
            return BitCast<Uuid>(value);
            /*UuidGuid pun;
            pun.AsGuid = value;
            return pun.AsUuid;*/
        }
    };
}
