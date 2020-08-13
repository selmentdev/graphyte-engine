#include <GxBase/App.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/Flags.hxx>
#include <GxBase/String.hxx>
#include "Windows.KeyboardMapping.hxx"
#include "Windows.Window.hxx"
#include "Windows.XInput.hxx"

#include <ShellScalingApi.h>

#include <windowsx.h>
#undef IsMaximized
#undef IsMinimized

namespace Graphyte::App::Impl
{
    static WindowsXInputDevice g_XInputDevice{};
}

namespace Graphyte::App::Impl
{
    static STICKYKEYS g_StartupStickyKeys{
        .cbSize = sizeof(STICKYKEYS),
    };

    static TOGGLEKEYS g_StartupToggleKeys{
        .cbSize = sizeof(TOGGLEKEYS),
    };

    static FILTERKEYS g_StartupFilterKeys{
        .cbSize = sizeof(FILTERKEYS),
    };

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

namespace Graphyte::App::Impl
{
    extern IEventHandler* g_EventHandler;
    ApplicationDescriptor g_ApplicationDescriptor{};
    static ModifierKey g_ModifierKey{};
    bool g_IsRequestingExit{ false };
    bool g_IsFirstInstance{ false };
    static bool g_ApplicationActivateByMouse{ false };
    static bool g_IsMouseAttached{ false };
    static bool g_UseHighPrecisionMouse{ false };
}

namespace Graphyte::App::Impl
{
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

    /*static */ void EnableRawInputKeyboard(WindowsWindow& window, bool enable, bool enforce) noexcept
    {
        EnableRawInputDevice(
            window.GetHandle(),
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Keyboard);
    }

    static void EnableRawInputMouse(WindowsWindow& window, bool enable, bool enforce) noexcept
    {
        g_UseHighPrecisionMouse = EnableRawInputDevice(
            window.GetHandle(),
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Mouse);
    }
}

namespace Graphyte::App::Impl
{
    struct Message final
    {
        HWND HWnd;
        UINT Msg;
        WPARAM WParam;
        LPARAM LParam;
        LRESULT Result;
    };

    static void BaseWindowProc(Message& m) noexcept
    {
        m.Result = ::DefWindowProcW(
            m.HWnd,
            m.Msg,
            m.WParam,
            m.LParam);
    }
}


// -------------------------------------------------------------------------------------------------
// Message handlers

namespace Graphyte::App::Impl
{
    static void WmChar([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        char32_t const character = static_cast<char32_t>(message.WParam);
        bool const repeat        = (message.LParam & 0x40000000) != 0;

        Impl::g_EventHandler->OnKeyChar(CharEvent{
            .Modifiers = g_ModifierKey,
            .Character = character,
            .Repeat    = repeat,
        });
    }

    static void WmSysChar([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        bool const is_alt_space = ((HIWORD(message.LParam) & 0x2000) != 0) && (message.WParam == VK_SPACE);

        if (is_alt_space)
        {
            // Allow Alt+Space in order to show window system menu
            BaseWindowProc(message);
        }
    }

    static void WmKeyDown([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        bool repeat = (message.LParam & 0x40000000) != 0;

        UINT winkey = static_cast<UINT>(message.WParam);
        UINT key    = winkey;

        switch (winkey)
        {
            case VK_MENU:
            {
                bool const is_left = ((message.LParam & 0x1000000) == 0);

                ModifierKey const modifier = is_left
                                                 ? ModifierKey::LeftAlt
                                                 : ModifierKey::RightAlt;

                key = (is_left) ? VK_LMENU : VK_RMENU;

                repeat = Flags::Has(g_ModifierKey, modifier);

                g_ModifierKey |= modifier;
                break;
            }

            case VK_CONTROL:
            {
                bool const is_left = ((message.LParam & 0x1000000) == 0);

                ModifierKey const modifier = is_left
                                                 ? ModifierKey::LeftControl
                                                 : ModifierKey::RightControl;

                key = (is_left) ? VK_LCONTROL : VK_RCONTROL;

                repeat = Flags::Has(g_ModifierKey, modifier);

                g_ModifierKey |= modifier;
                break;
            }

            case VK_SHIFT:
            {
                key = MapVirtualKeyW(static_cast<UINT8>(message.LParam >> 16), MAPVK_VSC_TO_VK_EX);

                bool const is_left = (key == VK_LSHIFT);

                ModifierKey const modifier = is_left
                                                 ? ModifierKey::LeftShift
                                                 : ModifierKey::RightShift;

                repeat = Flags::Has(g_ModifierKey, modifier);

                g_ModifierKey |= modifier;
                break;
            }

            case VK_CAPITAL:
            {
                if ((GetKeyState(VK_CAPITAL) & 0x1) != 0)
                {
                    g_ModifierKey |= ModifierKey::CapsLock;
                }
                else
                {
                    g_ModifierKey &= ~ModifierKey::CapsLock;
                }
                break;
            }
        }

        char32_t const character = MapVirtualKeyW(key, MAPVK_VK_TO_CHAR);

        KeyCode const keycode = Impl::TranslateKeyCode(key);

        Impl::g_EventHandler->OnKeyDown(KeyEvent{
            .Modifiers = g_ModifierKey,
            .Key       = keycode,
            .Character = character,
            .Repeat    = repeat,
        });
    }

    static void WmKeyUp([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        UINT winkey = static_cast<UINT>(message.WParam);
        UINT key    = winkey;

        switch (winkey)
        {
            case VK_MENU:
            {
                bool const is_left = ((message.LParam & 0x1000000) == 0);

                ModifierKey const modifier = is_left
                                                 ? ModifierKey::LeftAlt
                                                 : ModifierKey::RightAlt;

                key = (is_left) ? VK_LMENU : VK_RMENU;

                g_ModifierKey &= ~modifier;
                break;
            }

            case VK_CONTROL:
            {
                bool const is_left = ((message.LParam & 0x1000000) == 0);

                ModifierKey const modifier = is_left
                                                 ? ModifierKey::LeftControl
                                                 : ModifierKey::RightControl;

                key = (is_left) ? VK_LCONTROL : VK_RCONTROL;

                g_ModifierKey &= ~modifier;
                break;
            }

            case VK_SHIFT:
            {
                key = MapVirtualKeyW(static_cast<UINT8>(message.LParam >> 16), MAPVK_VSC_TO_VK_EX);

                bool const is_left = (key == VK_LSHIFT);

                ModifierKey const modifier = is_left
                                                 ? ModifierKey::LeftShift
                                                 : ModifierKey::RightShift;

                g_ModifierKey |= modifier;
                break;
            }

            case VK_CAPITAL:
            {
                if ((GetKeyState(VK_CAPITAL) & 0x1) != 0)
                {
                    g_ModifierKey |= ModifierKey::CapsLock;
                }
                else
                {
                    g_ModifierKey &= ~ModifierKey::CapsLock;
                }
                break;
            }
        }

        char32_t const character = MapVirtualKeyW(key, MAPVK_VK_TO_CHAR);

        KeyCode const keycode = Impl::TranslateKeyCode(key);

        Impl::g_EventHandler->OnKeyUp(KeyEvent{
            .Modifiers = g_ModifierKey,
            .Key       = keycode,
            .Character = character,
            .Repeat    = false,
        });
    }

    static void WmSysKeyDown(WindowsWindow& window, Message& message) noexcept
    {
        if (message.WParam == VK_F4)
        {
            GX_LOG(LogPlatform, Trace, "Alt+F4\n");
        }
        else if (message.WParam == VK_SPACE)
        {
            GX_LOG(LogPlatform, Trace, "Alt+Space\n");
        }

        if (message.WParam != VK_F4 && message.WParam != VK_SPACE)
        {
            WmKeyDown(window, message);
        }
        else
        {
            BaseWindowProc(message);
        }
    }

    static void WmMouseButton(WindowsWindow& window, Message& message) noexcept
    {
        MouseButtonEvent event{
            .Modifiers = g_ModifierKey,
        };

        POINT cursor{
            .x = GET_X_LPARAM(message.LParam),
            .y = GET_Y_LPARAM(message.LParam),
        };

        ClientToScreen(message.HWnd, &cursor);

        event.Position.X = static_cast<float>(cursor.x);
        event.Position.Y = static_cast<float>(cursor.y);

        bool double_click{ false };
        bool is_up{ false };

        switch (message.Msg)
        {
            case WM_LBUTTONDBLCLK:
                double_click = true;
                event.Button = MouseButton::Left;
                break;

            case WM_LBUTTONUP:
                is_up        = true;
                event.Button = MouseButton::Left;
                break;

            case WM_LBUTTONDOWN:
                event.Button = MouseButton::Left;
                break;

            case WM_MBUTTONDBLCLK:
                double_click = true;
                event.Button = MouseButton::Middle;
                break;

            case WM_MBUTTONUP:
                is_up        = true;
                event.Button = MouseButton::Middle;
                break;

            case WM_MBUTTONDOWN:
                event.Button = MouseButton::Middle;
                break;

            case WM_RBUTTONDBLCLK:
                double_click = true;
                event.Button = MouseButton::Right;
                break;

            case WM_RBUTTONUP:
                is_up        = true;
                event.Button = MouseButton::Right;
                break;

            case WM_RBUTTONDOWN:
                event.Button = MouseButton::Right;
                break;

            case WM_XBUTTONDBLCLK:
                double_click = true;
                event.Button = (GET_XBUTTON_WPARAM(message.WParam) & XBUTTON1)
                                   ? MouseButton::Thumb1
                                   : MouseButton::Thumb2;
                break;

            case WM_XBUTTONUP:
                is_up        = true;
                event.Button = (GET_XBUTTON_WPARAM(message.WParam) & XBUTTON1)
                                   ? MouseButton::Thumb1
                                   : MouseButton::Thumb2;
                break;

            case WM_XBUTTONDOWN:
                is_up        = true;
                event.Button = (GET_XBUTTON_WPARAM(message.WParam) & XBUTTON1)
                                   ? MouseButton::Thumb1
                                   : MouseButton::Thumb2;
                break;
        }

        if (is_up)
        {
            g_EventHandler->OnMouseUp(window, event);
        }
        else if (double_click)
        {
            g_EventHandler->OnMouseDoubleClick(window, event);
        }
        else
        {
            g_EventHandler->OnMouseDown(window, event);
        }
    }

    static void WmMouseMove([[maybe_unused]] WindowsWindow& window, [[maybe_unused]] Message& message) noexcept
    {
        if (!g_UseHighPrecisionMouse)
        {
            // Raw input uses relative cursor position change - emit event with absolute mouse movement.
            g_EventHandler->OnMouseMove();
        }
    }

    static void WmMouseWheel([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        constexpr float const spin = 1.0f / 120.0f;
        float const wheel_delta    = static_cast<float>(GET_WHEEL_DELTA_WPARAM(message.WParam));

        Float2 const position{};

        // TODO: Is position required here?
        g_EventHandler->OnMouseWheel(MouseWheelEvent{
            .Modifiers = g_ModifierKey,
            .Delta     = wheel_delta * spin,
            .Position  = {
                .X = static_cast<float>(GET_X_LPARAM(message.LParam)),
                .Y = static_cast<float>(GET_Y_LPARAM(message.LParam)),

            },
        });
    }

    static void WmInput([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        HRAWINPUT deviceHandle = reinterpret_cast<HRAWINPUT>(message.LParam);

        UINT size{};
        GetRawInputData(deviceHandle, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));

        std::vector<uint8_t> buffer{};
        buffer.resize(size);

        if (GetRawInputData(deviceHandle, RID_INPUT, std::data(buffer), &size, sizeof(RAWINPUTHEADER)) == size)
        {
            RAWINPUT* input = reinterpret_cast<RAWINPUT*>(std::data(buffer));

            if (input->header.dwType == RIM_TYPEMOUSE)
            {
                bool const is_absolute = (input->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) == MOUSE_MOVE_ABSOLUTE;

                if (is_absolute)
                {
                    g_EventHandler->OnMouseMove();
                }
                else
                {
                    MouseMoveEvent const event{
                        .Modifiers = g_ModifierKey,
                        .Position  = {
                            .X = static_cast<float>(input->data.mouse.lLastX),
                            .Y = static_cast<float>(input->data.mouse.lLastY),
                        },
                    };

                    g_EventHandler->OnMouseMove(event);
                }

                message.Result = TRUE;
                return;
            }
            else if (input->header.dwType == RIM_TYPEKEYBOARD)
            {
                GX_LOG(LogPlatform, Trace, "(kbd: vk: {:x}, msg: {:x}, mc: {:x}, flg: {:x}, ei: {:x})\n",
                    input->data.keyboard.VKey,
                    input->data.keyboard.Message,
                    input->data.keyboard.MakeCode,
                    input->data.keyboard.Flags,
                    input->data.keyboard.ExtraInformation);
            }
        }

        BaseWindowProc(message);
    }

    static void WmNcCalcSize([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        WindowDescriptor const& descriptor = window.GetDescriptor();

        if (message.WParam != 0 && !descriptor.SystemBorder && window.IsMaximized())
        {
            WINDOWINFO wi{
                .cbSize = sizeof(WINDOWINFO),
            };

            GetWindowInfo(message.HWnd, &wi);

            NCCALCSIZE_PARAMS& calcsize = *reinterpret_cast<NCCALCSIZE_PARAMS*>(message.LParam);

            calcsize.rgrc[0].left += wi.cxWindowBorders;
            calcsize.rgrc[0].top += wi.cxWindowBorders;
            calcsize.rgrc[0].right -= wi.cxWindowBorders;
            calcsize.rgrc[0].bottom -= wi.cxWindowBorders;

            calcsize.rgrc[1] = calcsize.rgrc[0];

            calcsize.lppos->x += wi.cxWindowBorders;
            calcsize.lppos->y += wi.cxWindowBorders;
            calcsize.lppos->cx -= 2 * wi.cxWindowBorders;
            calcsize.lppos->cy -= 2 * wi.cxWindowBorders;

            message.Result = WVR_VALIDRECTS;
        }
        else
        {
            BaseWindowProc(message);
        }
    }

    static void WmSize(WindowsWindow& window, Message& message) noexcept
    {
        int32_t const new_w = GET_X_LPARAM(message.LParam);
        int32_t const new_h = GET_Y_LPARAM(message.LParam);

        bool const was_minimized = (message.WParam == SIZE_MINIMIZED);
        bool const is_fullscreen = (window.GetWindowMode() == WindowMode::Fullscreen);

        if (!is_fullscreen)
        {
            g_EventHandler->OnWindowSizeChanged(
                window,
                Float2{
                    .X = static_cast<float>(new_w),
                    .Y = static_cast<float>(new_h),
                },
                was_minimized);
        }
    }

    static void WmEnterSizeMove(WindowsWindow& window, Message& message) noexcept
    {
        Impl::g_EventHandler->OnWindowSizingBegin(window);
        BaseWindowProc(message);
    }

    static void WmExitSizeMove(WindowsWindow& window, Message& message) noexcept
    {
        Impl::g_EventHandler->OnWindowSizingEnd(window);
        BaseWindowProc(message);
    }

    static void WmMove(WindowsWindow& window, Message& message) noexcept
    {
        LONG const new_x = GET_X_LPARAM(message.LParam);
        LONG const new_y = GET_Y_LPARAM(message.LParam);

        if (new_x != -32000 && new_y != -32000)
        {
            g_EventHandler->OnWindowMoved(window,
                Float2{
                    .X = static_cast<float>(new_x),
                    .Y = static_cast<float>(new_y),
                });
        }
        else
        {
            BaseWindowProc(message);
        }
    }

    static void WmActivate(WindowsWindow& window, Message& message) noexcept
    {
        WindowActivation activation = WindowActivation::Deactivate;

        WORD const flags = LOWORD(message.WParam);

        if (flags & WA_ACTIVE)
        {
            activation = g_ApplicationActivateByMouse
                             ? WindowActivation::InputActivate
                             : WindowActivation::Activate;
        }
        else if (flags & WA_CLICKACTIVE)
        {
            activation = WindowActivation::InputActivate;
        }

        g_ApplicationActivateByMouse = false;

        UpdateModifierKeys();
        g_EventHandler->OnWindowActivate(window, activation);
    }

    static void WmMouseActivate([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        Impl::g_ApplicationActivateByMouse = (LOWORD(message.LParam) & HTCLIENT) == 0;

        BaseWindowProc(message);
    }

    static void WmActivateApp([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        UpdateModifierKeys();

        bool const activated = (message.WParam != 0);

        Impl::g_EventHandler->OnApplicationActivated(activated);
        BaseWindowProc(message);
    }

    static void WmEraseBackground([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        message.Result = TRUE;
        BaseWindowProc(message);
    }

    static void WmNcPaint(WindowsWindow& window, Message& message) noexcept
    {
        if (window.GetDescriptor().SystemBorder)
        {
            // Only render border for windows with system borders.
            BaseWindowProc(message);
        }
    }

    static void WmClose(WindowsWindow& window, [[maybe_unused]] Message& message) noexcept
    {
        g_EventHandler->OnWindowClose(window);
    }

    static void WmGetMinMaxInfo(WindowsWindow& window, Message& message) noexcept
    {
        MINMAXINFO& minmax = *reinterpret_cast<MINMAXINFO*>(message.LParam);

        WindowDescriptor const& descriptor = window.GetDescriptor();

        System::Size minSize = descriptor.SizeLimits.MinSize.value_or(
            System::Size{
                .Width  = minmax.ptMinTrackSize.x,
                .Height = minmax.ptMinTrackSize.y,
            });

        System::Size maxSize = descriptor.SizeLimits.MaxSize.value_or(
            System::Size{
                .Width  = minmax.ptMaxTrackSize.x,
                .Height = minmax.ptMaxTrackSize.y,
            });

        if (window.GetDescriptor().SystemBorder)
        {
            DWORD dwStyle   = static_cast<DWORD>(GetWindowLongW(message.HWnd, GWL_STYLE));
            DWORD dwExStyle = static_cast<DWORD>(GetWindowLongW(message.HWnd, GWL_EXSTYLE));

            RECT rcBorder{};

            AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

            maxSize.Width += (rcBorder.right - rcBorder.left);
            maxSize.Height += (rcBorder.bottom - rcBorder.top);
        }

        minmax.ptMinTrackSize.x = minSize.Width;
        minmax.ptMinTrackSize.y = minSize.Height;

        minmax.ptMaxTrackSize.x = maxSize.Width;
        minmax.ptMaxTrackSize.y = maxSize.Height;
    }

    static void WmDisplayChange([[maybe_unused]] WindowsWindow& window, [[maybe_unused]] Message& message) noexcept
    {
        GX_LOG(LogPlatform, Trace,
            "Display changed: bits per pixel = {}, width = {}, height = {}\n",
            static_cast<UINT>(message.WParam),
            static_cast<UINT>(LOWORD(message.LParam)),
            static_cast<UINT>(HIWORD(message.LParam)));

        BaseWindowProc(message);
    }

    static void WmDpiChanged(WindowsWindow& window, Message& message) noexcept
    {
        window.SetDpiScale(static_cast<float>(LOWORD(message.WParam)) / 96.0f);

        RECT const& rect = *reinterpret_cast<LPRECT>(message.LParam);

        SetWindowPos(
            message.HWnd,
            nullptr,
            rect.left,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOACTIVATE);

        Impl::g_EventHandler->OnWindowDpiChanged(window);

        BaseWindowProc(message);
    }

    static void WmDeviceChange([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        QueryInputDevices();

        BaseWindowProc(message);
    }

    static void WmPowerBroadcast([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        switch (message.WParam)
        {
            case PBT_APMPOWERSTATUSCHANGE:
                GX_LOG(LogPlatform, Info, "Power Event: status changed\n");
                break;

            case PBT_APMRESUMEAUTOMATIC:
                GX_LOG(LogPlatform, Info, "Power Event: resume-automatic\n");
                break;

            case PBT_APMRESUMESUSPEND:
                GX_LOG(LogPlatform, Info, "Power Event: resume-suspend\n");
                break;

            case PBT_APMSUSPEND:
                GX_LOG(LogPlatform, Info, "Power Event: suspend\n");
                break;
        }

        message.Result = TRUE;
    }

    static void WmEndSession([[maybe_unused]] WindowsWindow& window, Message& message) noexcept
    {
        ShutdownReason reason = ShutdownReason::LogOff;

        switch (message.LParam)
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

        Impl::g_EventHandler->OnApplicationShutdown(reason);

        message.Result = 0;
    }
}


// -------------------------------------------------------------------------------------------------
// Window procedure

namespace Graphyte::App::Impl
{
    static LRESULT CALLBACK HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
    {
        GX_ABORT_UNLESS(g_EventHandler != nullptr, "Event handler not set");

        Impl::WindowsWindow* window = reinterpret_cast<Impl::WindowsWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));

        if (window == nullptr)
        {
            if (uMsg == WM_GETMINMAXINFO)
            {
                return 0;
            }

            GX_ASSERTF(uMsg == WM_NCCREATE, "Invalid message: got {}", uMsg);

            // Cache window pointer in HWND userdata
            VOID* native_window = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;

            SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(native_window));

            window = reinterpret_cast<Impl::WindowsWindow*>(native_window);
        }

        GX_ASSERT(window != nullptr);

        Impl::Message message{
            .HWnd   = hWnd,
            .Msg    = uMsg,
            .WParam = wParam,
            .LParam = lParam,
            .Result = 0,
        };

        switch (uMsg)
        {
            case WM_CHAR:
                WmChar(*window, message);
                break;

            case WM_SYSCHAR:
                WmSysChar(*window, message);
                break;

            case WM_SYSKEYDOWN:
                WmSysKeyDown(*window, message);
                break;

            case WM_KEYDOWN:
                WmKeyDown(*window, message);
                break;

            case WM_SYSKEYUP:
            case WM_KEYUP:
                WmKeyUp(*window, message);
                break;

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
                WmMouseButton(*window, message);
                break;

            case WM_MOUSEMOVE:
                WmMouseMove(*window, message);
                break;

            case WM_MOUSEWHEEL:
                WmMouseWheel(*window, message);
                break;

            case WM_INPUT:
                WmInput(*window, message);
                break;

            case WM_NCCALCSIZE:
                WmNcCalcSize(*window, message);
                break;

            case WM_SIZE:
                WmSize(*window, message);
                break;

            case WM_ENTERSIZEMOVE:
                WmEnterSizeMove(*window, message);
                break;

            case WM_EXITSIZEMOVE:
                WmExitSizeMove(*window, message);
                break;

            case WM_MOVE:
                WmMove(*window, message);
                break;

            case WM_ACTIVATE:
                WmActivate(*window, message);
                break;

            case WM_MOUSEACTIVATE:
                WmMouseActivate(*window, message);
                break;

            case WM_ACTIVATEAPP:
                WmActivateApp(*window, message);
                break;

            case WM_ERASEBKGND:
                WmEraseBackground(*window, message);
                break;

            case WM_NCPAINT:
                WmNcPaint(*window, message);
                break;

            case WM_CLOSE:
                WmClose(*window, message);
                break;

            case WM_GETMINMAXINFO:
                WmGetMinMaxInfo(*window, message);
                break;

            case WM_DISPLAYCHANGE:
                WmDisplayChange(*window, message);
                break;

            case WM_DPICHANGED:
                WmDpiChanged(*window, message);
                break;

            case WM_GETDLGCODE:
                message.Result = DLGC_WANTALLKEYS;
                break;

            case WM_DEVICECHANGE:
                WmDeviceChange(*window, message);
                break;

            case WM_POWERBROADCAST:
                WmPowerBroadcast(*window, message);
                break;

            case WM_ENDSESSION:
                WmEndSession(*window, message);
                break;

            default:
                message.Result = DefWindowProcW(hWnd, uMsg, wParam, lParam);
        }

        return message.Result;
    }
}


// -------------------------------------------------------------------------------------------------
// Application initialization

namespace Graphyte::App::Impl
{
    static void RegisterWindow(HINSTANCE instance, HICON icon) noexcept
    {
        WNDCLASSEXW wc{
            .cbSize        = sizeof(wc),
            .style         = CS_DBLCLKS | CS_OWNDC,
            .lpfnWndProc   = HandleMessage,
            .cbClsExtra    = 0,
            .cbWndExtra    = 0,
            .hInstance     = instance,
            .hIcon         = icon,
            .hCursor       = LoadCursorW(nullptr, (LPCWSTR)IDC_ARROW),
            .hbrBackground = nullptr,
            .lpszMenuName  = nullptr,
            .lpszClassName = L"GraphyteWindow",
            .hIconSm       = icon,
        };

        ATOM const result = RegisterClassExW(&wc);


        GX_ABORT_UNLESS(result != 0, "Cannot register window class");
    }

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
}


// -------------------------------------------------------------------------------------------------
// Public API

namespace Graphyte::App
{
    void Initialize() noexcept
    {
        // Capture initial accessibility settings.
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

        // Lookup for any input devices available.
        // This excludes XInput devices, which are discovered at runtime.
        Impl::QueryInputDevices();
    }

    void Finalize() noexcept
    {
        // Nothing to do right now.
    }

    void Tick(float delta_time) noexcept
    {
        // NOTE: Messages are pulled before other devices, so gamepad takes priority on input
        //       processing.
        PumpMessages(delta_time);
        PollInput(delta_time);
    }

    void PollInput([[maybe_unused]] float delta_time) noexcept
    {
        Impl::g_XInputDevice.Poll(delta_time);
    }

    void PumpMessages([[maybe_unused]] float delta_time) noexcept
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
        DWORD process_id{};

        GetWindowThreadProcessId(GetForegroundWindow(), &process_id);
        return process_id == GetCurrentProcessId();
    }

    void RequestExit(bool force) noexcept
    {
        GX_LOG(LogPlatform, Trace, "Application requesting exit\n");

        if (force)
        {
            // BUG: This function is not handled when messages are being passed around.
            PostQuitMessage(0);
        }
        else
        {
            Impl::g_IsRequestingExit = true;
        }
    }
}


// -------------------------------------------------------------------------------------------------
// Window API

namespace Graphyte::App
{
    Window* MakeWindow(WindowDescriptor const& descriptor) noexcept
    {
        Impl::WindowsWindow* window = new Impl::WindowsWindow();
        window->Create(descriptor);

        Impl::EnableRawInputMouse(*window, true, false);
        //Impl::EnableRawInputKeyboard(*window, true, false);

        return window;
    }

    void DestroyWindow(Window* window) noexcept
    {
        Impl::WindowsWindow* native_window = static_cast<Impl::WindowsWindow*>(window);

        GX_ASSERT(native_window != nullptr);

        if (native_window != nullptr)
        {
            native_window->Destroy();

            delete native_window;
        }
    }
}
