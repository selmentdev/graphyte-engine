#pragma once
#include <GxBase/System.hxx>
#include <GxBase/DateTime.hxx>
#include <GxBase/Uuid.hxx>
#include <GxBase/Bitwise.hxx>

namespace Graphyte::System::Impl
{
    [[nodiscard]] constexpr System::Point ToPoint(POINT value) noexcept
    {
        return System::Point{
            .Left = value.x,
            .Top = value.y,
        };
    }

    [[nodiscard]] constexpr POINT FromPoint(System::Point value) noexcept
    {
        return POINT{
            .x = value.Left,
            .y = value.Top,
        };
    }

    [[nodiscard]] constexpr System::Size ToSize(SIZE value) noexcept
    {
        return System::Size{
            .Width = value.cx,
            .Height = value.cy,
        };
    }

    [[nodiscard]] constexpr SIZE FromSize(System::Size value) noexcept
    {
        return SIZE{
            .cx = value.Width,
            .cy = value.Height,
        };
    }

    [[nodiscard]] constexpr System::Rect ToRect(RECT value) noexcept
    {
        return System::Rect{
            .Left = value.left,
            .Top = value.top,
            .Width = value.right - value.left,
            .Height = value.bottom - value.top,
        };
    }

    [[nodiscard]] constexpr RECT FromRect(System::Rect value) noexcept
    {
        return RECT{
            .left = value.Left,
            .top = value.Top,
            .right = value.Left + value.Width,
            .bottom = value.Top + value.Height,
        };
    }

    [[nodiscard]] constexpr DateTime ToDateTime(FILETIME value) noexcept
    {
        ULARGE_INTEGER const li{
            .LowPart = value.dwLowDateTime,
            .HighPart = value.dwHighDateTime,
        };

        return DateTime{
            .Value = static_cast<int64_t>(li.QuadPart) + Graphyte::Impl::g_DateAdjustOffset,
        };
    }

    [[nodiscard]] constexpr FILETIME FromDateTime(DateTime value) noexcept
    {
        ULARGE_INTEGER const li{
            .QuadPart = static_cast<uint64_t>(value.Value - -Graphyte::Impl::g_DateAdjustOffset),
        };

        return FILETIME{
            .dwLowDateTime = li.LowPart,
            .dwHighDateTime = li.HighPart,
        };
    }

    [[nodiscard]] constexpr Uuid ToUuid(GUID const& value) noexcept
    {
        return BitCast<Uuid>(value);
    }

    [[nodiscard]] constexpr GUID FromUuid(Uuid const& value) noexcept
    {
        return BitCast<GUID>(value);
    }

    [[nodiscard]] constexpr CalendarTime ToCalendarTime(SYSTEMTIME const& value) noexcept
    {
        return CalendarTime{
            .Year = value.wYear,
            .Month = value.wMonth,
            .Day = value.wDay,
            .Hour = value.wHour,
            .Minute = value.wMinute,
            .Second = value.wSecond,
            .Millisecond = value.wMilliseconds,
            .DayOfWeek = value.wDayOfWeek,
            .DayOfYear = 0,
        };
    }

    [[nodiscard]] constexpr SYSTEMTIME FromCalendarTime(CalendarTime const& value) noexcept
    {
        return SYSTEMTIME{
            .wYear         = static_cast<WORD>(value.Year),
            .wMonth        = static_cast<WORD>(value.Month),
            .wDayOfWeek    = static_cast<WORD>(value.DayOfWeek),
            .wDay          = static_cast<WORD>(value.Day),
            .wHour         = static_cast<WORD>(value.Hour),
            .wMinute       = static_cast<WORD>(value.Minute),
            .wSecond       = static_cast<WORD>(value.Second),
            .wMilliseconds = static_cast<WORD>(value.Millisecond),
        };
    }
}
