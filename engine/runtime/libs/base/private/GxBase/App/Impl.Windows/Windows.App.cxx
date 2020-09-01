#include <GxBase/App.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/Flags.hxx>
#include <GxBase/String.hxx>

#include "Windows.KeyboardMapping.hxx"
#include "Windows.Window.hxx"
#include "Windows.XInput.hxx"

#include <ShellScalingApi.h>


// =================================================================================================
// Logging category.

namespace Graphyte::App
{
    GX_DEFINE_LOG_CATEGORY(LogNativeApp);
}


// -------------------------------------------------------------------------------------------------
// XInput support

namespace Graphyte::App::Impl
{
    static WindowsXInputDevice g_XInputDevice{};
}


// -------------------------------------------------------------------------------------------------
// Application variables

namespace Graphyte::App::Impl
{
    ApplicationDescriptor g_ApplicationDescriptor{};
    bool g_IsRequestingExit{ false };
    bool g_IsFirstInstance{ false };

    static ModifierKey g_ModifierKey{};
    static bool g_IsMouseAttached{ false };
    static bool g_UseHighPrecisionMouse{ false };
    static bool g_ClickWindowActivate{ false };
}


// -------------------------------------------------------------------------------------------------
// Accessibility features

namespace Graphyte::App::Impl
{
    static STICKYKEYS g_StartupStickyKeys{};
    static TOGGLEKEYS g_StartupToggleKeys{};
    static FILTERKEYS g_StartupFilterKeys{};

    void EnableAccessibilityKeys(bool enable) noexcept
    {
        STICKYKEYS sk = g_StartupStickyKeys;
        TOGGLEKEYS tk = g_StartupToggleKeys;
        FILTERKEYS fk = g_StartupFilterKeys;

        if (enable)
        {
            // Restore accessibility keys
            SystemParametersInfoW(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &sk, 0);
            SystemParametersInfoW(SPI_SETTOGGLEKEYS, sizeof(TOGGLEKEYS), &tk, 0);
            SystemParametersInfoW(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &fk, 0);
        }
        else
        {
            // Disable accessibility settings
            if ((sk.dwFlags & SKF_STICKYKEYSON) == 0)
            {
                sk.dwFlags &= ~(SKF_HOTKEYACTIVE | SKF_CONFIRMHOTKEY);
                SystemParametersInfoW(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &sk, 0);
            }

            if ((tk.dwFlags & TKF_TOGGLEKEYSON) == 0)
            {
                tk.dwFlags &= ~(TKF_HOTKEYACTIVE | TKF_CONFIRMHOTKEY);
                SystemParametersInfoW(SPI_SETTOGGLEKEYS, sizeof(TOGGLEKEYS), &tk, 0);
            }

            if ((fk.dwFlags & FKF_FILTERKEYSON) == 0)
            {
                fk.dwFlags &= ~(FKF_HOTKEYACTIVE | FKF_CONFIRMHOTKEY);
                SystemParametersInfoW(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &fk, 0);
            }
        }
    }
}


// -------------------------------------------------------------------------------------------------
// Input support

namespace Graphyte::App::Impl
{
    static void FixupShiftKeyReleaseEvents(UINT vk, ModifierKey modifier, KeyCode key) noexcept
    {
        // Check if shift key was pressed last time
        if (Flags::Has(g_ModifierKey, modifier))
        {
            // And if it was released in mean time.
            if ((GetKeyState(vk) & 0x8000) == 0)
            {
                // Emit release event.
                g_ModifierKey &= ~modifier;

                g_EventHandler->OnKeyUp(KeyEvent{
                    .Modifiers = g_ModifierKey,
                    .Key       = key,
                    .Character = {},
                    .Repeat    = false,
                });
            }
        }
    }

    static void UpdateModifierKeys() noexcept
    {
        ModifierKey modifiers{};

        if ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::LeftShift;
        }

        if ((GetAsyncKeyState(VK_RSHIFT) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::RightShift;
        }

        if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::LeftControl;
        }

        if ((GetAsyncKeyState(VK_RCONTROL) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::RightControl;
        }

        if ((GetAsyncKeyState(VK_LMENU) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::LeftAlt;
        }

        if ((GetAsyncKeyState(VK_RMENU) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::RightAlt;
        }

        if ((GetAsyncKeyState(VK_CAPITAL) & 0x8000) != 0)
        {
            modifiers |= ModifierKey::CapsLock;
        }

        g_ModifierKey = modifiers;
    }

    static void QueryInputDevices() noexcept
    {
        UINT devicesCount{};

        GetRawInputDeviceList(nullptr, &devicesCount, sizeof(RAWINPUTDEVICELIST));

        if (devicesCount == 0)
        {
            Impl::g_IsMouseAttached = false;
        }

        std::vector<RAWINPUTDEVICELIST> devices{};
        devices.resize(devicesCount);

        GetRawInputDeviceList(std::data(devices), &devicesCount, sizeof(RAWINPUTDEVICELIST));

        size_t mouseCount{};

        for (auto const& device : devices)
        {
            if (device.dwType != RIM_TYPEMOUSE)
            {
                continue;
            }
            UINT nameLength{};

            UINT copied = GetRawInputDeviceInfoA(
                device.hDevice,
                RIDI_DEVICENAME,
                nullptr,
                &nameLength);

            if (copied == static_cast<UINT>(-1))
            {
                continue;
            }

            std::string name(nameLength, '\0');

            copied = GetRawInputDeviceInfoA(
                device.hDevice,
                RIDI_DEVICENAME,
                std::data(name),
                &nameLength);

            if (copied == static_cast<UINT>(-1))
            {
                continue;
            }

            ReplaceAll(name, "#", "\\");

            if (name.starts_with(R"(\??\ROOT\RDP_MOU\)") || name.starts_with(R"(\\?\ROOT\RDP_MOU\)"))
            {
                continue;
            }

            ++mouseCount;
        }

        if (mouseCount == 0)
        {
            if (GetSystemMetrics(SM_REMOTESESSION))
            {
                ++mouseCount;
            }
        }

        g_IsMouseAttached = (mouseCount != 0);
    }

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

    /*static */ void EnableRawInputKeyboard(Window& window, bool enable, bool enforce) noexcept
    {
        EnableRawInputDevice(
            window.Hwnd,
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Keyboard);
    }

    static void EnableRawInputMouse(Window& window, bool enable, bool enforce) noexcept
    {
        g_UseHighPrecisionMouse = EnableRawInputDevice(
            window.Hwnd,
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Mouse);
    }
}


// -------------------------------------------------------------------------------------------------
// Window message handling

namespace Graphyte::App::Impl
{
    static void WmChar(WPARAM wparam, LPARAM lparam) noexcept
    {
        char32_t const character = static_cast<char32_t>(wparam);
        bool const repeat        = (lparam & 0x40000000) != 0;

        g_EventHandler->OnKeyChar({
            .Modifiers = g_ModifierKey,
            .Character = character,
            .Repeat    = repeat,
        });
    }

    static LRESULT WmKeyDown(WPARAM wparam, LPARAM lparam) noexcept
    {
        bool repeat = (lparam & 0x40000000) != 0;

        UINT vk  = static_cast<UINT>(wparam);
        UINT key = vk;

        switch (vk)
        {
            case VK_MENU:
                if ((lparam & 0x1000000) == 0)
                {
                    key    = VK_LMENU;
                    repeat = Flags::Has(g_ModifierKey, ModifierKey::LeftAlt);
                    g_ModifierKey |= ModifierKey::LeftAlt;
                }
                else
                {
                    key    = VK_RMENU;
                    repeat = Flags::Has(g_ModifierKey, ModifierKey::RightAlt);
                    g_ModifierKey |= ModifierKey::RightAlt;
                }

                break;

            case VK_CONTROL:
                if ((lparam & 0x1000000) == 0)
                {
                    key    = VK_LCONTROL;
                    repeat = Flags::Has(g_ModifierKey, ModifierKey::LeftControl);
                    g_ModifierKey |= ModifierKey::LeftControl;
                }
                else
                {
                    key    = VK_RCONTROL;
                    repeat = Flags::Has(g_ModifierKey, ModifierKey::RightControl);
                    g_ModifierKey |= ModifierKey::RightControl;
                }

                break;

            case VK_SHIFT:
                key = MapVirtualKeyW((lparam >> 16) & 0xFF, MAPVK_VSC_TO_VK_EX);
                if (key == VK_LSHIFT)
                {
                    repeat = Flags::Has(g_ModifierKey, ModifierKey::LeftShift);
                    g_ModifierKey |= ModifierKey::LeftShift;
                }
                else
                {
                    repeat = Flags::Has(g_ModifierKey, ModifierKey::LeftShift);
                    g_ModifierKey |= ModifierKey::LeftShift;
                }

                break;

            case VK_CAPITAL:
                if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
                {
                    g_ModifierKey |= ModifierKey::CapsLock;
                }
                else
                {
                    g_ModifierKey &= ~ModifierKey::CapsLock;
                }

                break;

            default:
                break;
        }

        char32_t character = MapVirtualKeyW(vk, MAPVK_VK_TO_CHAR);

        KeyCode const keycode = TranslateKeyCode(key);

        g_EventHandler->OnKeyDown(KeyEvent{
            .Modifiers = g_ModifierKey,
            .Key       = keycode,
            .Character = character,
            .Repeat    = repeat,
        });

        return 0;
    }

    static LRESULT WmKeyUp(WPARAM wparam, LPARAM lparam) noexcept
    {
        UINT vk  = static_cast<UINT>(wparam);
        UINT key = vk;

        switch (vk)
        {
            case VK_MENU:
                if ((lparam & 0x1000000) == 0)
                {
                    key = VK_LMENU;
                    g_ModifierKey &= ~ModifierKey::LeftAlt;
                }
                else
                {
                    key = VK_RMENU;
                    g_ModifierKey &= ~ModifierKey::RightAlt;
                }

                break;

            case VK_CONTROL:
                if ((lparam & 0x1000000) == 0)
                {
                    key = VK_LCONTROL;
                    g_ModifierKey &= ~ModifierKey::LeftControl;
                }
                else
                {
                    key = VK_RCONTROL;
                    g_ModifierKey &= ~ModifierKey::RightControl;
                }

                break;

            case VK_SHIFT:
                key = MapVirtualKeyW((lparam >> 16) & 0xFFu, MAPVK_VSC_TO_VK_EX);

                if (key == VK_LSHIFT)
                {
                    g_ModifierKey &= ~ModifierKey::LeftShift;
                }
                else
                {
                    g_ModifierKey &= ~ModifierKey::RightShift;
                }

                break;

            case VK_CAPITAL:
                if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
                {
                    g_ModifierKey |= ModifierKey::CapsLock;
                }
                else
                {
                    g_ModifierKey &= ~ModifierKey::CapsLock;
                }

                break;

            default:
                break;
        }

        char32_t character = MapVirtualKeyW(vk, MAPVK_VK_TO_CHAR);

        KeyCode const keycode = TranslateKeyCode(key);

        g_EventHandler->OnKeyUp(KeyEvent{
            .Modifiers = g_ModifierKey,
            .Key       = keycode,
            .Character = character,
            .Repeat    = false,
        });

        return 0;
    }

    static void WmMouseButton(Window& window, HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
    {
        POINT cursor{
            .x = LOWORD(lparam),
            .y = HIWORD(lparam),
        };

        ClientToScreen(hwnd, &cursor);

        bool const doubleClick = [=]() {
            switch (msg)
            {
                case WM_LBUTTONDBLCLK:
                case WM_MBUTTONDBLCLK:
                case WM_RBUTTONDBLCLK:
                case WM_XBUTTONDBLCLK:
                    return true;
            }

            return false;
        }();

        bool const upClick = [=]() {
            switch (msg)
            {
                case WM_LBUTTONUP:
                case WM_MBUTTONUP:
                case WM_RBUTTONUP:
                case WM_XBUTTONUP:
                    return true;
            }

            return false;
        }();

        MouseButton const button = [=]() {
            switch (msg)
            {
                case WM_LBUTTONDBLCLK:
                case WM_LBUTTONUP:
                case WM_LBUTTONDOWN:
                    return MouseButton::Left;

                case WM_MBUTTONDBLCLK:
                case WM_MBUTTONUP:
                case WM_MBUTTONDOWN:
                    return MouseButton::Middle;

                case WM_RBUTTONDBLCLK:
                case WM_RBUTTONUP:
                case WM_RBUTTONDOWN:
                    return MouseButton::Right;

                case WM_XBUTTONDBLCLK:
                case WM_XBUTTONUP:
                case WM_XBUTTONDOWN:
                    return (GET_XBUTTON_WPARAM(wparam) & XBUTTON1)
                               ? MouseButton::Thumb1
                               : MouseButton::Thumb2;
            }

            GX_ABORT("Wrong message button type!");
            return MouseButton::Invalid;
        }();

        MouseButtonEvent event{
            .Modifiers = g_ModifierKey,
            .Button    = button,
            .Position  = {
                .X = static_cast<float>(cursor.x),
                .Y = static_cast<float>(cursor.y),
            },
        };

        if (upClick)
        {
            g_EventHandler->OnMouseUp(window, event);
        }
        else if (doubleClick)
        {
            g_EventHandler->OnMouseDoubleClick(window, event);
        }
        else
        {
            g_EventHandler->OnMouseDown(window, event);
        }
    }

    static void WmMouseMove() noexcept
    {
        if (!g_UseHighPrecisionMouse)
        {
            g_EventHandler->OnMouseMove();
        }
    }

    static void WmMouseWheel(WPARAM wparam, bool horizontal) noexcept
    {
        constexpr float const spin = 1.0f / static_cast<float>(WHEEL_DELTA);

        float const wheelDelta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wparam));

        GX_LOG_TRACE(LogNativeApp, "WM_MOUSEWHEEL {} (horizontal = {})\n", wheelDelta * spin, horizontal);

        g_EventHandler->OnMouseWheel(MouseWheelEvent{
            .Modifiers = g_ModifierKey,
            .Delta     = wheelDelta * spin,
            .Horizontal = horizontal,
        });
    }

    static bool WmInput(LPARAM lparam) noexcept
    {
        HRAWINPUT handle = reinterpret_cast<HRAWINPUT>(lparam);

        UINT size{};
        GetRawInputData(handle, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));

        auto buffer = std::make_unique<uint8_t[]>(size);

        if (GetRawInputData(handle, RID_INPUT, buffer.get(), &size, sizeof(RAWINPUTHEADER)) == size)
        {
            RAWINPUT* input = reinterpret_cast<RAWINPUT*>(buffer.get());

            if (input->header.dwType == RIM_TYPEMOUSE)
            {
                bool const relative = ((input->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) == 0);

                if (relative)
                {
                    g_EventHandler->OnMouseMove(MouseMoveEvent{
                        .Modifiers = g_ModifierKey,
                        .Relative  = {
                            .X = static_cast<float>(input->data.mouse.lLastX),
                            .Y = static_cast<float>(input->data.mouse.lLastY),
                        },
                    });
                }
                else
                {
                    g_EventHandler->OnMouseMove();
                }

                return true;
            }
            else if (input->header.dwType == RIM_TYPEKEYBOARD)
            {
                GX_LOG_TRACE(LogNativeApp, "(kbd: vk: {:x}, msg: {:x}, mc: {:x}, flg: {:x}, ei: {:x})\n",
                    input->data.keyboard.VKey,
                    input->data.keyboard.Message,
                    input->data.keyboard.MakeCode,
                    input->data.keyboard.Flags,
                    input->data.keyboard.ExtraInformation);
            }
        }

        return false;
    }

    static LRESULT WmNcCalcSize(Window& window, HWND hwnd, WPARAM wparam, LPARAM lparam) noexcept
    {
        if (wparam != 0 && window.Type == WindowType::Game && window.Mode != WindowMode::Windowed && IsMaximized(window))
        {
            // Maximized fullscreen borderless game window has visible border in multiple displays
            // scenario. Limit this by adjusting window placement to just fit display - we are still
            // render over whole area anyway.

            WINDOWINFO wi{ .cbSize = sizeof(wi) };
            GetWindowInfo(hwnd, &wi);

            NCCALCSIZE_PARAMS& params = *reinterpret_cast<LPNCCALCSIZE_PARAMS>(lparam);
            params.rgrc[0].left += wi.cxWindowBorders;
            params.rgrc[0].top += wi.cyWindowBorders;
            params.rgrc[0].right -= wi.cxWindowBorders;
            params.rgrc[0].bottom -= wi.cyWindowBorders;

            params.rgrc[1] = params.rgrc[0];

            params.lppos->x += wi.cxWindowBorders;
            params.lppos->y += wi.cyWindowBorders;
            params.lppos->cx -= 2 * wi.cxWindowBorders;
            params.lppos->cy -= 2 * wi.cyWindowBorders;

            return WVR_VALIDRECTS;
        }

        return DefWindowProcW(hwnd, WM_NCCALCSIZE, wparam, lparam);
    }

    static LRESULT WmClose(Window& window) noexcept
    {
        GX_LOG_TRACE(LogNativeApp, "WM_CLOSE\n");

        g_EventHandler->OnWindowClose(window);
        return 0;
    }

    static void WmSize(Window& window, WPARAM wparam, LPARAM lparam) noexcept
    {
        bool const exclusive = (window.Mode == WindowMode::Fullscreen);
        int32_t const cx     = LOWORD(lparam);
        int32_t const cy     = HIWORD(lparam);

        GX_LOG_TRACE(LogNativeApp, "WM_SIZE (cx: {}, cy: {})\n", cx, cy);

        if constexpr (true)
        {
            [[maybe_unused]] auto const viewport = GetClientSize(window);
            GX_LOG_TRACE(LogNativeApp, "WM_SIZE (client: cx: {}, cy: {})\n", viewport.Width, viewport.Height);
        }

        if (!exclusive)
        {

            bool const minimized = (wparam == SIZE_MINIMIZED);

            g_EventHandler->OnWindowSizeChanged(
                window,
                Float2{
                    .X = static_cast<float>(cx),
                    .Y = static_cast<float>(cy),
                },
                minimized);
        }
    }

    static void WmEnterSizeMove(Window& window) noexcept
    {
        g_EventHandler->OnWindowSizingBegin(window);
    }

    static void WmExitSizeMove(Window& window) noexcept
    {
        g_EventHandler->OnWindowSizingEnd(window);
    }

    static void WmMove(Window& window, LPARAM lparam) noexcept
    {
        LONG const x = LOWORD(lparam);
        LONG const y = HIWORD(lparam);

        if (x != -32000 && y != -32000)
        {
            GX_LOG_TRACE(LogNativeApp, "WM_MOVE (x: {}, y: {})\n", x, y);

            g_EventHandler->OnWindowMoved(window,
                Float2{
                    .X = static_cast<float>(x),
                    .Y = static_cast<float>(y),
                });
        }
    }

    static void WmActivate(Window& window, WPARAM wparam) noexcept
    {
        WORD const flags = LOWORD(wparam);

        WindowActivation activation = WindowActivation::Deactivate;

        if ((flags & WA_ACTIVE) != 0)
        {
            activation = g_ClickWindowActivate ? WindowActivation::ClickActivate : WindowActivation::Activate;
        }
        else if ((flags & WA_CLICKACTIVE) != 0)
        {
            activation = WindowActivation::ClickActivate;
        }

        g_ClickWindowActivate = false;

        UpdateModifierKeys();
        g_EventHandler->OnWindowActivate(window, activation);
    }

    static void WmMouseActivate(LPARAM lparam) noexcept
    {
        g_ClickWindowActivate = ((LOWORD(lparam) & HTCLIENT) == 0);
    }
    static void WmActivateApp(WPARAM wparam) noexcept
    {
        UpdateModifierKeys();

        bool const activated = (wparam != 0);
        g_EventHandler->OnApplicationActivated(activated);
    }

    static void WmDisplayChange(WPARAM wparam, LPARAM lparam) noexcept
    {
        GX_LOG_TRACE(LogNativeApp,
            "Display changed: {}x{}x{}\n",
            static_cast<UINT>(wparam),
            static_cast<UINT>(LOWORD(lparam)),
            static_cast<UINT>(HIWORD(lparam)));
    }

    static void WmGetMinMaxInfo(Window& window, LPARAM lparam) noexcept
    {
        if (window.Type == WindowType::Form || window.Type == WindowType::Dialog)
        {
            WindowSizeLimits const& limits = GetSizeLimits(window);

            if (limits.Min.has_value() || limits.Max.has_value())
            {
                MINMAXINFO& minmax = *reinterpret_cast<MINMAXINFO*>(lparam);

                System::Size minSize = limits.Min.value_or(
                    System::Size{
                        .Width  = minmax.ptMinTrackSize.x,
                        .Height = minmax.ptMinTrackSize.y,
                    });

                System::Size maxSize = limits.Max.value_or(
                    System::Size{
                        .Width  = minmax.ptMaxTrackSize.x,
                        .Height = minmax.ptMaxTrackSize.y,
                    });

                DWORD const dwStyle   = static_cast<DWORD>(GetWindowLongW(window.Hwnd, GWL_STYLE));
                DWORD const dwExStyle = static_cast<DWORD>(GetWindowLongW(window.Hwnd, GWL_EXSTYLE));

                RECT rcBorder{};
                AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);
                maxSize.Width += (rcBorder.right - rcBorder.left);
                maxSize.Height += (rcBorder.bottom - rcBorder.top);

                minmax.ptMinTrackSize.x = minSize.Width;
                minmax.ptMinTrackSize.y = minSize.Height;
                minmax.ptMaxTrackSize.x = maxSize.Width;
                minmax.ptMaxTrackSize.y = maxSize.Height;
            }
        }
    }

    static void WmDpiChanged(Window& window, HWND hwnd, WPARAM wparam, LPARAM lparam) noexcept
    {
        GX_LOG_TRACE(LogNativeApp, "WM_DPICHANGED\n");

        window.DpiScale = static_cast<float>(LOWORD(wparam)) / 96.0f;

        RECT const& rc = *reinterpret_cast<LPRECT>(lparam);

        SetWindowPos(
            hwnd,
            nullptr,
            rc.left,
            rc.top,
            rc.right - rc.left,
            rc.bottom - rc.top,
            SWP_NOZORDER | SWP_NOACTIVATE);

        g_EventHandler->OnWindowDpiChanged(window);
    }

    static void WmDeviceChange() noexcept
    {
        GX_LOG_TRACE(LogNativeApp, "WM_DEVICECHANGE\n");

        g_XInputDevice.RequestUpdate();
        QueryInputDevices();
    }

    static void WmPowerBroadcast(WPARAM wparam) noexcept
    {
        switch (wparam)
        {
            case PBT_APMRESUMEAUTOMATIC:
                GX_LOG_TRACE(LogNativeApp, "Power Event: resume-automatic\n");
                g_EventHandler->OnSystemPowerRestore();
                break;

            case PBT_APMRESUMESUSPEND:
                GX_LOG_TRACE(LogNativeApp, "Power Event: resume-suspend\n");
                g_EventHandler->OnSystemPowerRestore();
                break;

            case PBT_APMSUSPEND:
                GX_LOG_TRACE(LogNativeApp, "Power Event: suspend\n");
                g_EventHandler->OnSystemPowerSuspend();
                break;
        }
    }

    static void WmEndSession(LPARAM lparam) noexcept
    {
        ShutdownReason reason{};

        switch (lparam)
        {
            case ENDSESSION_CLOSEAPP:
                reason = ShutdownReason::CloseApplication;
                break;
            case ENDSESSION_CRITICAL:
                reason = ShutdownReason::Critical;
                break;
            case ENDSESSION_LOGOFF:
                reason = ShutdownReason::LogOff;
                break;
        }

        g_EventHandler->OnSystemPowerShutdown(reason);
    }

    static LRESULT CALLBACK WinHandleMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) noexcept
    {
        // Event handler is required in order to proceed.
        GX_ASSERT(g_EventHandler != nullptr);


        // Set pointer to window in HWND storage.
        Window* window = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

        if (window == nullptr)
        {
            if (msg == WM_GETMINMAXINFO)
            {
                return 0;
            }

            GX_ASSERT(msg == WM_NCCREATE);

            CREATESTRUCTW* const createparams = reinterpret_cast<CREATESTRUCTW*>(lparam);
            window = reinterpret_cast<Window*>(createparams->lpCreateParams);
            window->Hwnd = hwnd;

            SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
        }

        GX_ASSERT(window != nullptr);

        // Process supported messages
        switch (msg)
        {
            case WM_CHAR:
                WmChar(wparam, lparam);
                return 0;

            case WM_SYSKEYDOWN:
                // Allow Alt+F4 or Alt+Space to be processed by default handler
                if (wparam == VK_F4 || wparam == VK_SPACE)
                {
                    break;
                }

                [[fallthrough]];

            case WM_KEYDOWN:
                return WmKeyDown(wparam, lparam);

            case WM_SYSKEYUP:
            case WM_KEYUP:
                return WmKeyUp(wparam, lparam);

            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_LBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_RBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            case WM_XBUTTONDBLCLK:
                WmMouseButton(*window, hwnd, msg, wparam, lparam);
                break;

            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE:
                WmMouseMove();
                break;

            case WM_MOUSEWHEEL:
                WmMouseWheel(wparam, false);
                break;

            case WM_MOUSEHWHEEL:
                WmMouseWheel(wparam, true);
                break;

            case WM_INPUT:
                if (WmInput(lparam))
                {
                    return TRUE;
                }

                break;

            case WM_NCCALCSIZE:
                return WmNcCalcSize(*window, hwnd, wparam, lparam);

            case WM_NCACTIVATE:
                if (window->Mode != WindowMode::Windowed)
                {
                    return TRUE;
                }
                break;

            case WM_NCPAINT:
                if (window->Mode != WindowMode::Windowed)
                {
                    // Don't repaint non-client area for fullscreen window.
                    return 0;
                }

                break;

            case WM_CLOSE:
                return WmClose(*window);

            case WM_SIZE:
                WmSize(*window, wparam, lparam);
                break;

            case WM_ENTERSIZEMOVE:
                WmEnterSizeMove(*window);
                break;

            case WM_EXITSIZEMOVE:
                WmExitSizeMove(*window);
                break;

            case WM_MOVE:
                WmMove(*window, lparam);
                break;

            case WM_ACTIVATE:
                WmActivate(*window, wparam);
                break;
            case WM_MOUSEACTIVATE:
                WmMouseActivate(lparam);
                break;

            case WM_ACTIVATEAPP:
                WmActivateApp(wparam);
                break;

            case WM_ERASEBKGND:
                // There is no need to erase backogrund in rendering window
                return 0;

            case WM_GETMINMAXINFO:
                WmGetMinMaxInfo(*window, lparam);
                return 0;

            case WM_DISPLAYCHANGE:
                WmDisplayChange(wparam, lparam);
                break;

            case WM_DPICHANGED:
                WmDpiChanged(*window, hwnd, wparam, lparam);
                break;

            case WM_GETDLGCODE:
                return DLGC_WANTALLKEYS;

            case WM_DEVICECHANGE:
                WmDeviceChange();
                break;

            case WM_POWERBROADCAST:
                WmPowerBroadcast(wparam);
                return TRUE;

            case WM_ENDSESSION:
                WmEndSession(lparam);
                return 0;
        }

        return DefWindowProcW(hwnd, msg, wparam, lparam);
    }
}


// -------------------------------------------------------------------------------------------------
// Window support

namespace Graphyte::App::Impl
{
    static void RegisterWindow(HINSTANCE instance, HICON icon) noexcept
    {
        GX_LOG_TRACE(LogNativeApp, "Registering window class\n");

        WNDCLASSEX wcex{
            .cbSize        = sizeof(wcex),
            .style         = CS_DBLCLKS | CS_OWNDC,
            .lpfnWndProc   = WinHandleMessage,
            .cbClsExtra    = 0,
            .cbWndExtra    = 0,
            .hInstance     = instance,
            .hCursor       = LoadCursorW(nullptr, IDC_ARROW),
            .hbrBackground = GetSysColorBrush(COLOR_WINDOW),
            .lpszMenuName  = nullptr,
            .lpszClassName = L"GraphyteWindow",
            .hIconSm       = icon,
        };

        ATOM const result = RegisterClassExW(&wcex);

        GX_ABORT_UNLESS(result != 0, "Cannot register window class");
    }
}


// -------------------------------------------------------------------------------------------------
// Application public API

namespace Graphyte::App
{
    void Initialize() noexcept
    {
        GX_LOG_TRACE(LogNativeApp, "Initialize application\n");

        // Capture initial accessibility settings.
        Impl::g_StartupStickyKeys.cbSize = sizeof(STICKYKEYS);
        Impl::g_StartupToggleKeys.cbSize = sizeof(TOGGLEKEYS);
        Impl::g_StartupFilterKeys.cbSize = sizeof(FILTERKEYS);

        SystemParametersInfoW(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &Impl::g_StartupStickyKeys, 0);
        SystemParametersInfoW(SPI_GETSTICKYKEYS, sizeof(TOGGLEKEYS), &Impl::g_StartupToggleKeys, 0);
        SystemParametersInfoW(SPI_GETSTICKYKEYS, sizeof(FILTERKEYS), &Impl::g_StartupFilterKeys, 0);

        // Check if application is initialized properly.
        HINSTANCE const instance = System::Impl::GInstanceHandle;
        GX_ABORT_UNLESS(instance != nullptr, "Application not initialized properly");

        // Disable DWM ghosting, so system won't show "(not responding)" on window titlebar.
        DisableProcessWindowsGhosting();

        // We need to register window class
        HICON icon = LoadIconW(instance, MAKEINTRESOURCEW(System::Impl::IDI_MAIN_ICON));
        Impl::RegisterWindow(instance, icon);

        Impl::QueryInputDevices();
    }

    void Finalize() noexcept
    {
        // Nothing to do right now.
    }

    void Tick(float deltaTime) noexcept
    {
        // NOTE: Messages are pulled before other devices, so gamepad takes priority on input
        //       processing.
        ProcessMessages(deltaTime);
        PollInput(deltaTime);
    }

    void PollInput(float deltaTime) noexcept
    {
        Impl::g_XInputDevice.Poll(deltaTime);
    }

    void ProcessMessages([[maybe_unused]] float deltaTime) noexcept
    {
        // Pump incoming messages from queue.
        MSG m{};

        while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE) != FALSE)
        {
            TranslateMessage(&m);
            DispatchMessageW(&m);
        }


        // VK_xSHIFT is not being reported properly when both keys was pushed.
        Impl::FixupShiftKeyReleaseEvents(VK_LSHIFT, ModifierKey::LeftShift, KeyCode::LeftShift);
        Impl::FixupShiftKeyReleaseEvents(VK_RSHIFT, ModifierKey::RightShift, KeyCode::RightShift);
    }

    bool IsForeground() noexcept
    {
        DWORD dwProcessId{};
        GetWindowThreadProcessId(GetForegroundWindow(), &dwProcessId);
        return dwProcessId == GetCurrentProcessId();
    }

    void RequestExit() noexcept
    {
        GX_LOG_TRACE(LogNativeApp, "Application requesting exit\n");

        Impl::g_IsRequestingExit = true;
    }
}
