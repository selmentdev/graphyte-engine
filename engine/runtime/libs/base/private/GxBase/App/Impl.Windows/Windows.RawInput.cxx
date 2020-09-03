#include "Windows.RawInput.hxx"
#include "Windows.Window.hxx"

namespace Graphyte::App::Impl
{
    constexpr uint16_t UsagePage_Desktop = 0x01;
    constexpr uint16_t UsageId_Mouse     = 0x02;
    constexpr uint16_t UsageId_Keyboard  = 0x06;

    static bool EnableRawInputDevice(
        HWND handle,
        bool enable,
        bool enforce,
        uint16_t usage_page,
        uint16_t usage_id) noexcept
    {
        DWORD dwFlags{};

        if (enforce && enable)
        {
            dwFlags |= RIDEV_NOLEGACY;
        }

        if (!enable)
        {
            dwFlags |= RIDEV_REMOVE;
        }

        RAWINPUTDEVICE device{
            .usUsagePage = usage_page,
            .usUsage     = usage_id,
            .dwFlags     = dwFlags,
            .hwndTarget  = handle,
        };

        BOOL const result = RegisterRawInputDevices(&device, 1, sizeof(RAWINPUTDEVICE));
        return result != FALSE;
    }

    void EnableRawInputKeyboard(Window& window, bool enable, bool enforce) noexcept
    {
        EnableRawInputDevice(
            window.Hwnd,
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Keyboard);
    }

    void EnableRawInputMouse(Window& window, bool enable, bool enforce) noexcept
    {
        g_UseHighPrecisionMouse = EnableRawInputDevice(
            window.Hwnd,
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Mouse);
    }
}
