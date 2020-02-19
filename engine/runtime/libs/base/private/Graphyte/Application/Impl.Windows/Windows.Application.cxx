#include <Graphyte/System.hxx>
#include <Graphyte/Flags.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/String.hxx>

#include "Windows.Window.hxx"
#include "Windows.XInput.hxx"

#include <windowsx.h>
#undef IsMaximized
#undef IsMinimized

namespace Graphyte::Application::Impl
{
    ApplicationDescriptor GApplicationDescriptor{};
    bool GIsFirstInstance{ false };

    static bool GIsRequestingExit{ false };
    static Input::ModifierKeyState GApplicationModifierKeys{};
    static WindowsXInputDevice GApplicationXInput{};
    static STICKYKEYS GApplicationStartupStickyKeys{};
    static TOGGLEKEYS GApplicationStartupToggleKeys{};
    static FILTERKEYS GApplicationStartupFilterKeys{};
    static bool GApplicationActivateByMouse{};
    static bool GApplicationHighPrecisionMouse{};
    static bool GApplicationIsMouseAttached{};
    static EventHandler* GApplicationEventHandler{};
}

namespace Graphyte::Application::Impl
{
    extern Input::KeyCode TranslateKeyCode(
        UINT vk_keycode
    ) noexcept;

    static void UpdateModifierKeys() noexcept
    {
        Input::ModifierKeyState modifiers{};

        modifiers |= ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0)
            ? Input::ModifierKeyState::LeftShift
            : Input::ModifierKeyState::None;

        modifiers |= ((GetAsyncKeyState(VK_RSHIFT) & 0x8000) != 0)
            ? Input::ModifierKeyState::RightShift
            : Input::ModifierKeyState::None;

        modifiers |= ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0)
            ? Input::ModifierKeyState::LeftControl
            : Input::ModifierKeyState::None;

        modifiers |= ((GetAsyncKeyState(VK_RCONTROL) & 0x8000) != 0)
            ? Input::ModifierKeyState::RightControl
            : Input::ModifierKeyState::None;

        modifiers |= ((GetAsyncKeyState(VK_LMENU) & 0x8000) != 0)
            ? Input::ModifierKeyState::LeftAlt
            : Input::ModifierKeyState::None;

        modifiers |= ((GetAsyncKeyState(VK_RMENU) & 0x8000) != 0)
            ? Input::ModifierKeyState::RightAlt
            : Input::ModifierKeyState::None;

        modifiers |= ((GetAsyncKeyState(VK_CAPITAL) & 0x8000) != 0)
            ? Input::ModifierKeyState::CapsLock
            : Input::ModifierKeyState::None;

        Impl::GApplicationModifierKeys = modifiers;
    }

    static void QueryInputDevices() noexcept
    {
        UINT device_count = 0;

        GetRawInputDeviceList(
            nullptr,
            &device_count,
            sizeof(RAWINPUTDEVICELIST)
        );

        if (device_count == 0)
        {
            Impl::GApplicationIsMouseAttached = false;
        }

        std::vector<RAWINPUTDEVICELIST> devices{};
        devices.resize(device_count);

        GetRawInputDeviceList(
            std::data(devices),
            &device_count,
            sizeof(RAWINPUTDEVICELIST)
        );

        size_t mouse_count = 0;

        for (auto&& device : devices)
        {

            if (device.dwType != RIM_TYPEMOUSE)
            {
                continue;
            }

            UINT name_length = 0;

            UINT copied = GetRawInputDeviceInfoA(
                device.hDevice,
                RIDI_DEVICENAME,
                nullptr,
                &name_length
            );

            if (copied == static_cast<UINT>(-1))
            {
                continue;
            }

            std::string name(name_length, '\0');

            copied = GetRawInputDeviceInfoA(
                device.hDevice,
                RIDI_DEVICENAME,
                std::data(name),
                &name_length
            );

            if (copied == static_cast<UINT>(-1))
            {
                continue;
            }

            Graphyte::ReplaceAll(name, "#", "\\");

            if (name.starts_with(R"(\??\ROOT\RDP_MOU\)") || name.starts_with(R"(\\?\ROOT\RDP_MOU\)"))
            {
                continue;
            }

            ++mouse_count;
        }

        if (mouse_count == 0)
        {
            if (GetSystemMetrics(SM_REMOTESESSION))
            {
                mouse_count++;
            }
        }

        Impl::GApplicationIsMouseAttached = (mouse_count != 0);
    }

    static void FixShiftKeyState(
        uint32_t keycode
    ) noexcept
    {
        GX_ASSERT(keycode == VK_LSHIFT || keycode == VK_RSHIFT);

        auto const mask = (keycode == VK_LSHIFT)
            ? Input::ModifierKeyState::LeftShift
            : Input::ModifierKeyState::RightShift;

        auto const key = (keycode == VK_LSHIFT)
            ? Input::KeyCode::LeftShift
            : Input::KeyCode::RightShift;

        auto const invalidated =
            Flags::Has(Impl::GApplicationModifierKeys, mask) &&
            (GetKeyState(static_cast<int>(keycode)) & 0x8000) == 0;

        if (invalidated)
        {
            //
            // Modifier key was registered in one of previous messages and it isn't hold down anymore.
            //
            // Emit event and mask it out.
            //

            Impl::GApplicationModifierKeys &= ~mask;
            Impl::GApplicationEventHandler->OnKeyUp(key, 0, false);
        }
    }

    static void ToggleAccessibility(
        bool enable
    ) noexcept
    {
        if (enable)
        {
            SystemParametersInfoW(
                SPI_SETSTICKYKEYS,
                sizeof(Impl::GApplicationStartupStickyKeys),
                &Impl::GApplicationStartupStickyKeys,
                0
            );

            SystemParametersInfoW(
                SPI_SETTOGGLEKEYS,
                sizeof(Impl::GApplicationStartupToggleKeys),
                &Impl::GApplicationStartupToggleKeys,
                0
            );

            SystemParametersInfoW(
                SPI_SETFILTERKEYS,
                sizeof(Impl::GApplicationStartupFilterKeys),
                &Impl::GApplicationStartupFilterKeys,
                0
            );
        }
        else
        {
            auto sticky = Impl::GApplicationStartupStickyKeys;

            if ((sticky.dwFlags & SKF_STICKYKEYSON) == 0)
            {
                sticky.dwFlags &= ~SKF_HOTKEYACTIVE;
                sticky.dwFlags &= ~SKF_CONFIRMHOTKEY;

                SystemParametersInfoW(
                    SPI_SETSTICKYKEYS,
                    sizeof(sticky),
                    &sticky,
                    0
                );
            }

            auto toggle = Impl::GApplicationStartupToggleKeys;

            if ((toggle.dwFlags & TKF_TOGGLEKEYSON) == 0)
            {
                toggle.dwFlags &= ~TKF_HOTKEYACTIVE;
                toggle.dwFlags &= ~TKF_CONFIRMHOTKEY;

                SystemParametersInfoW(
                    SPI_SETTOGGLEKEYS,
                    sizeof(toggle),
                    &toggle,
                    0
                );
            }

            auto filter = Impl::GApplicationStartupFilterKeys;

            if ((filter.dwFlags &= FKF_FILTERKEYSON) == 0)
            {
                filter.dwFlags &= ~FKF_HOTKEYACTIVE;
                filter.dwFlags &= ~FKF_CONFIRMHOTKEY;

                SystemParametersInfoW(
                    SPI_SETFILTERKEYS,
                    sizeof(filter),
                    &filter,
                    0
                );
            }
        }
    }

    void EnableHighPrecisionMouse(
        bool enable,
        Impl::WindowsWindow& window
    ) noexcept
    {
        HWND handle = nullptr;

        DWORD flags = RIDEV_REMOVE;

        Impl::GApplicationHighPrecisionMouse = enable;

        if (enable)
        {
            flags = 0;

            handle = window.GetHwnd();
        }

        RAWINPUTDEVICE rid{
            .usUsagePage = 0x1,
            .usUsage     = 0x2,
            .dwFlags     = flags,
            .hwndTarget  = handle,
        };

        BOOL result = RegisterRawInputDevices(&rid, 1, sizeof(rid));

        if (result == FALSE)
        {
            GX_ABORT("Cannot register input device: {}", Diagnostics::GetMessageFromSystemError());
        }
    }
}

namespace Graphyte::Application::Impl
{
    struct Message final
    {
        HWND HWnd;
        UINT Msg;
        WPARAM WParam;
        LPARAM LParam;
        LRESULT Result;
    };

    void BaseWindowProc(
        Message& message
    ) noexcept
    {
        message.Result = DefWindowProcW(
            message.HWnd,
            message.Msg,
            message.WParam,
            message.LParam
        );
    }
}

namespace Graphyte::Application::Impl
{
    constexpr uint16_t UsagePage_Desktop = 0x01;
    constexpr uint16_t UsageId_Mouse     = 0x02;
    constexpr uint16_t UsageId_Keyboard  = 0x06;

    static void EnableRawInputDeviceImpl(
        HWND handle,
        bool enable,
        bool enforce,
        uint16_t usage_page,
        uint16_t usage_id
    ) noexcept
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
            .usUsagePage = UsagePage_Desktop,
            .usUsage     = UsageId_Mouse,
            .dwFlags     = dwFlags,
            .hwndTarget  = handle,
        };

        BOOL result = RegisterRawInputDevices(
            &device,
            1,
            sizeof(RAWINPUTDEVICE)
        );

        if (result == FALSE)
        {
            GX_ABORT_UNLESS(
                result != FALSE,
                "Cannot enable raw input for device (page: {:x}, usage: {:x}",
                usage_page,
                usage_id
            );
        }
    }

    void EnableRawInputKeyboard(
        Impl::WindowsWindow& window,
        bool enable,
        bool enforce
    )
    {
        Impl::EnableRawInputDeviceImpl(
            window.GetHwnd(),
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Keyboard
        );
    }

    void EnableRawInputMouse(
        Impl::WindowsWindow& window,
        bool enable,
        bool enforce
    )
    {
        Impl::EnableRawInputDeviceImpl(
            window.GetHwnd(),
            enable,
            enforce,
            UsagePage_Desktop,
            UsageId_Mouse
        );
    }
}

namespace Graphyte::Application::Impl
{
    static void WmKeyDown(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (!Impl::GApplicationEventHandler->CanHandleInput(window))
        {
            Impl::UpdateModifierKeys();
        }
        else
        {
            uint32_t winkey = static_cast<uint32_t>(message.WParam);
            uint32_t key = winkey;

            bool repeat = (message.LParam & 0x40000000) != 0;

            switch (winkey)
            {
            case VK_MENU:
                {
                    if ((message.LParam & 0x1000000) == 0)
                    {
                        key = VK_LMENU;
                        repeat = Flags::Has(Impl::GApplicationModifierKeys, Input::ModifierKeyState::LeftAlt);
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::LeftAlt;
                    }
                    else
                    {
                        key = VK_RMENU;
                        repeat = Flags::Has(Impl::GApplicationModifierKeys, Input::ModifierKeyState::RightAlt);
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::RightAlt;
                    }

                    break;
                }
            case VK_CONTROL:
                {
                    if ((message.LParam & 0x1000000) == 0)
                    {
                        key = VK_LCONTROL;
                        repeat = Flags::Has(Impl::GApplicationModifierKeys, Input::ModifierKeyState::LeftControl);
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::LeftControl;
                    }
                    else
                    {
                        key = VK_RCONTROL;
                        repeat = Flags::Has(Impl::GApplicationModifierKeys, Input::ModifierKeyState::RightControl);
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::RightControl;
                    }

                    break;
                }
            case VK_SHIFT:
                {
                    key = MapVirtualKeyW(
                        static_cast<UINT8>(message.LParam >> 16),
                        MAPVK_VSC_TO_VK_EX
                    );

                    if (key == VK_LSHIFT)
                    {
                        repeat = Flags::Has(Impl::GApplicationModifierKeys, Input::ModifierKeyState::LeftShift);
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::LeftShift;
                    }
                    else
                    {
                        repeat = Flags::Has(Impl::GApplicationModifierKeys, Input::ModifierKeyState::RightShift);
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::RightShift;
                    }

                    break;
                }
            case VK_CAPITAL:
                {
                    if ((GetKeyState(VK_CAPITAL) & 0x1) != 0)
                    {
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::CapsLock;
                    }
                    else
                    {
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::CapsLock;
                    }

                    break;
                }
            }

            char32_t character = MapVirtualKeyW(key, MAPVK_VK_TO_CHAR);

            Input::KeyCode keycode = Impl::TranslateKeyCode(key);

            Impl::GApplicationEventHandler->OnKeyDown(
                keycode,
                character,
                repeat
            );
        }
    }

    static void WmSysKeyDown(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
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
            Impl::WmKeyDown(window, message);
        }
        else
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmKeyUp(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (!Impl::GApplicationEventHandler->CanHandleInput(window))
        {
            Impl::UpdateModifierKeys();
        }
        else
        {
            uint32_t winkey = static_cast<uint32_t>(message.WParam);
            uint32_t key = winkey;

            switch (winkey)
            {
            case VK_MENU:
                {
                    if ((message.LParam & 0x1000000) == 0)
                    {
                        key = VK_LMENU;
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::LeftAlt;
                    }
                    else
                    {
                        key = VK_RMENU;
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::RightAlt;
                    }

                    break;
                }
            case VK_CONTROL:
                {
                    if ((message.LParam & 0x1000000) == 0)
                    {
                        key = VK_LCONTROL;
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::LeftControl;
                    }
                    else
                    {
                        key = VK_RCONTROL;
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::RightControl;
                    }

                    break;
                }
            case VK_SHIFT:
                {
                    key = MapVirtualKeyW(
                        static_cast<UINT8>(message.LParam >> 16),
                        MAPVK_VSC_TO_VK_EX
                    );

                    if (key == VK_LSHIFT)
                    {
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::LeftShift;
                    }
                    else
                    {
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::RightShift;
                    }

                    break;
                }
            case VK_CAPITAL:
                {
                    if ((GetKeyState(VK_CAPITAL) & 0x1) != 0)
                    {
                        Impl::GApplicationModifierKeys |= Input::ModifierKeyState::CapsLock;
                    }
                    else
                    {
                        Impl::GApplicationModifierKeys &= ~Input::ModifierKeyState::CapsLock;
                    }

                    break;
                }
            }

            char32_t character = MapVirtualKeyW(key, MAPVK_VK_TO_CHAR);

            Input::KeyCode keycode = Impl::TranslateKeyCode(key);

            Impl::GApplicationEventHandler->OnKeyUp(
                keycode,
                character,
                false
            );
        }
    }

    static void WmSetCursor(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (window.GetDescriptor().SystemBorder)
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmActivateApp(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        UpdateModifierKeys();

        auto const activated = (message.WParam != 0);

        Impl::GApplicationEventHandler->OnApplicationActivated(activated);

        Impl::BaseWindowProc(message);
    }

    static void WmMouseButton(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (Impl::GApplicationEventHandler->CanHandleInput(window))
        {
            Input::MouseButton mouse_button{};
            bool double_click = false;
            bool mouse_up = false;

            switch (message.Msg)
            {
            case WM_LBUTTONDBLCLK:
                {
                    double_click = true;
                    mouse_button = Input::MouseButton::Left;
                    break;
                }
            case WM_LBUTTONUP:
                {
                    mouse_up = true;
                    mouse_button = Input::MouseButton::Left;
                    break;
                }
            case WM_LBUTTONDOWN:
                {
                    mouse_button = Input::MouseButton::Left;
                    break;
                }
            case WM_MBUTTONDBLCLK:
                {
                    double_click = true;
                    mouse_button = Input::MouseButton::Middle;
                    break;
                }
            case WM_MBUTTONUP:
                {
                    mouse_up = true;
                    mouse_button = Input::MouseButton::Middle;
                    break;
                }
            case WM_MBUTTONDOWN:
                {
                    mouse_button = Input::MouseButton::Middle;
                    break;
                }
            case WM_RBUTTONDBLCLK:
                {
                    double_click = true;
                    mouse_button = Input::MouseButton::Right;
                    break;
                }
            case WM_RBUTTONUP:
                {
                    mouse_up = true;
                    mouse_button = Input::MouseButton::Right;
                    break;
                }
            case WM_RBUTTONDOWN:
                {
                    mouse_button = Input::MouseButton::Right;
                    break;
                }
            case WM_XBUTTONDBLCLK:
                {
                    double_click = true;
                    mouse_button = (GET_XBUTTON_WPARAM(message.WParam) & XBUTTON1)
                        ? Input::MouseButton::Thumb01
                        : Input::MouseButton::Thumb02;
                    break;
                }
            case WM_XBUTTONUP:
                {
                    mouse_up = true;
                    mouse_button = (GET_XBUTTON_WPARAM(message.WParam) & XBUTTON1)
                        ? Input::MouseButton::Thumb01
                        : Input::MouseButton::Thumb02;
                    break;
                }
            case WM_XBUTTONDOWN:
                {
                    mouse_button = (GET_XBUTTON_WPARAM(message.WParam) & XBUTTON1)
                        ? Input::MouseButton::Thumb01
                        : Input::MouseButton::Thumb02;
                    break;
                }
            }

            POINT cursor{
                .x = GET_X_LPARAM(message.LParam),
                .y = GET_Y_LPARAM(message.LParam),
            };

            ClientToScreen(message.HWnd, &cursor);

            Maths::Float2 const position{
                static_cast<float>(cursor.x),
                static_cast<float>(cursor.y)
            };

            if (mouse_up)
            {
                Impl::GApplicationEventHandler->OnMouseUp(
                    window,
                    mouse_button,
                    position
                );
            }
            else if (double_click)
            {
                Impl::GApplicationEventHandler->OnMouseDoubleClick(
                    window,
                    mouse_button,
                    position
                );
            }
            else
            {
                Impl::GApplicationEventHandler->OnMouseDown(
                    window,
                    mouse_button,
                    position
                );
            }
        }
    }

    static void WmMouseMove(
        [[maybe_unused]] Impl::WindowsWindow& window,
        [[maybe_unused]] Message& message
    ) noexcept
    {
        if (!Impl::GApplicationHighPrecisionMouse)
        {
            Impl::GApplicationEventHandler->OnMouseMove();
        }
    }

    static void WmMouseWheel(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        float const spin = 1.0F / 120.0F;
        float const wheel_delta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(message.WParam));

        Maths::Float2 const position{
            static_cast<float>(GET_X_LPARAM(message.LParam)),
            static_cast<float>(GET_Y_LPARAM(message.LParam))
        };

        Impl::GApplicationEventHandler->OnMouseWheel(
            wheel_delta * spin,
            position
        );
    }

    static void WmTouch(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (UINT count = LOWORD(message.WParam); count != 0)
        {
            HTOUCHINPUT hInput = reinterpret_cast<HTOUCHINPUT>(message.LParam);

            std::unique_ptr<TOUCHINPUT[]> inputs = std::make_unique<TOUCHINPUT[]>(count);

            if (GetTouchInputInfo(hInput, count, inputs.get(), sizeof(TOUCHINPUT)) != FALSE)
            {
                for (UINT i = 0; i < count; ++i)
                {
                    TOUCHINPUT const& input = inputs[i];

                    Maths::Float2 const location{
                        static_cast<float>(input.x) / 100.0F,
                        static_cast<float>(input.y) / 100.0F
                    };

                    if (input.dwFlags & TOUCHEVENTF_DOWN)
                    {
                        GX_LOG(LogPlatform, Trace, "OnTouchStarted(x = {}, y = {}, id = {:x}\n",
                            location.X,
                            location.Y,
                            input.dwID
                        );
                    }
                    else if (input.dwFlags & TOUCHEVENTF_MOVE)
                    {
                        GX_LOG(LogPlatform, Trace, "OnTouchMove(x = {}, y = {}, id = {:x}\n",
                            location.X,
                            location.Y,
                            input.dwID
                        );
                    }
                    else if (input.dwFlags & TOUCHEVENTF_UP)
                    {
                        GX_LOG(LogPlatform, Trace, "OnTouchEnded(x = {}, y = {}, id = {:x}\n",
                            location.X,
                            location.Y,
                            input.dwID
                        );
                    }
                }
            }
            else
            {
                GX_LOG(LogPlatform, Error, "Failed to get touch input info: {}\n",
                    Diagnostics::GetMessageFromSystemError()
                );
            }

            CloseTouchInputHandle(
                hInput
            );
        }
    }

    static void WmClose(
        Impl::WindowsWindow& window,
        [[maybe_unused]] Message& message
    ) noexcept
    {
        Impl::GApplicationEventHandler->OnWindowClose(window);
    }

    static void WmNcPaint(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (window.GetDescriptor().SystemBorder)
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmEraseBackground(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        message.Result = TRUE;
    }

    static void WmMouseActivate(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        Impl::GApplicationActivateByMouse = !(LOWORD(message.LParam) & HTCLIENT);

        Impl::BaseWindowProc(message);
    }

    static void WmNcActivate(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        if (!window.GetDescriptor().SystemBorder)
        {
            message.Result = TRUE;
        }
        else
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmEnterSizeMove(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        Impl::GApplicationEventHandler->OnWindowSizingBegin(window);

        Impl::BaseWindowProc(message);
    }

    static void WmLeaveSizeMove(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        Impl::GApplicationEventHandler->OnWindowSizingEnd(window);

        Impl::BaseWindowProc(message);
    }

    static void WmSysCommand(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        switch (message.WParam & 0xfff0)
        {
        case SC_RESTORE:
            {
                if (IsIconic(message.HWnd))
                {
                    //
                    // Maximize window on our own, don't rely on OS in this case.
                    //

                    ShowWindow(
                        message.HWnd,
                        SW_RESTORE
                    );

                    return;
                }
                else
                {
                    Impl::GApplicationEventHandler->OnWindowAction(
                        window,
                        WindowAction::Restore
                    );
                }
                break;
            }
        case SC_MAXIMIZE:
            {
                Impl::GApplicationEventHandler->OnWindowAction(
                    window,
                    WindowAction::Maximize
                );
                break;
            }
        case SC_MINIMIZE:
            {
                Impl::GApplicationEventHandler->OnWindowAction(
                    window,
                    WindowAction::Minimize
                );
                break;
            }
        case SC_CLOSE:
            {
                //
                // Handle closing window here. We don't want WM_CLOSE to be sent later.
                //

                Impl::GApplicationEventHandler->OnWindowClose(
                    window
                );

                return;
            }
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
            {
                //
                // Disable entering screen-saver or turning monitor power off.
                //

                return;
            }
        default:
            {
                if (!Impl::GApplicationEventHandler->CanHandleInput(window))
                {
                    return;
                }
                break;
            }
        }

        Impl::BaseWindowProc(message);
    }

    static void WmChar(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        char32_t const character = static_cast<char32_t>(message.WParam);
        bool const repeat = (message.LParam & 0x40000000) != 0;

        Impl::GApplicationEventHandler->OnKeyChar(
            character,
            repeat
        );
    }

    static void WmSysChar(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        bool const is_alt_space =
            ((HIWORD(message.LParam) & 0x2000) != 0) &&
            (message.WParam == VK_SPACE);

        if (is_alt_space)
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmNcCalcSize(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        auto const& descriptor = window.GetDescriptor();

        if (message.WParam != 0 && !descriptor.SystemBorder)
        {
            if (descriptor.Type == WindowType::GameWindow && window.IsMaximized())
            {
                WINDOWINFO wi{
                    .cbSize = sizeof(wi),
                };

                GetWindowInfo(
                    message.HWnd,
                    &wi
                );

                NCCALCSIZE_PARAMS& calcsize = *reinterpret_cast<LPNCCALCSIZE_PARAMS>(message.LParam);

                calcsize.rgrc[0].left += wi.cxWindowBorders;
                calcsize.rgrc[0].top += wi.cxWindowBorders;
                calcsize.rgrc[0].right -= wi.cxWindowBorders;
                calcsize.rgrc[0].bottom -= wi.cxWindowBorders;

                calcsize.rgrc[1].left = calcsize.rgrc[0].left;
                calcsize.rgrc[1].top = calcsize.rgrc[0].top;
                calcsize.rgrc[1].right = calcsize.rgrc[0].right;
                calcsize.rgrc[1].bottom = calcsize.rgrc[0].bottom;

                calcsize.lppos->x += wi.cxWindowBorders;
                calcsize.lppos->y += wi.cxWindowBorders;
                calcsize.lppos->cx -= 2 * wi.cxWindowBorders;
                calcsize.lppos->cy -= 2 * wi.cxWindowBorders;

                message.Result = WVR_VALIDRECTS;
            }
        }
        else
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmGetMinMaxInfo(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        MINMAXINFO& minmax = *reinterpret_cast<MINMAXINFO*>(message.LParam);
        auto limits = window.GetDescriptor().SizeLimits;

        int32_t border_w = 0;
        int32_t border_h = 0;

        if (window.GetDescriptor().SystemBorder)
        {
            DWORD dwStyle = static_cast<DWORD>(GetWindowLongW(message.HWnd, GWL_STYLE));
            DWORD dwExStyle = static_cast<DWORD>(GetWindowLongW(message.HWnd, GWL_EXSTYLE));

            RECT rc_border{};

            AdjustWindowRectEx(
                &rc_border,
                dwStyle,
                FALSE,
                dwExStyle
            );

            border_w = rc_border.right - rc_border.left;
            border_h = rc_border.bottom - rc_border.top;
        }

        minmax.ptMinTrackSize.x = limits.MinWidth.value_or(minmax.ptMinTrackSize.x);
        minmax.ptMinTrackSize.y = limits.MinHeight.value_or(minmax.ptMinTrackSize.y);

        minmax.ptMaxTrackSize.x = limits.MaxWidth.value_or(minmax.ptMaxTrackSize.x) + border_w;
        minmax.ptMaxTrackSize.y = limits.MaxHeight.value_or(minmax.ptMaxTrackSize.y) + border_h;
    }

    static void WmNcButtownDown(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        switch (message.WParam)
        {
        case HTMINBUTTON:
        case HTMAXBUTTON:
        case HTCLOSE:
        case HTCAPTION:
            Impl::GApplicationEventHandler->OnWindowAction(
                window,
                WindowAction::NonClientClick
            );
            break;
        }

        Impl::BaseWindowProc(message);
    }

    static void WmShowWindow(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        switch (message.LParam)
        {
        case SW_PARENTCLOSING:
            window.OnParentWindowMinimized();
            break;
        case SW_PARENTOPENING:
            window.OnParentWindowRestored();
            break;
        default:
            break;
        }

        Impl::BaseWindowProc(message);
    }

    static void WmSize(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        int32_t const new_w = GET_X_LPARAM(message.LParam);
        int32_t const new_h = GET_Y_LPARAM(message.LParam);

        bool const was_minimized = (message.WParam == SIZE_MINIMIZED);
        bool const is_fullscreen = (window.GetWindowMode() == WindowMode::Fullscreen);

        if (!is_fullscreen)
        {
            Impl::GApplicationEventHandler->OnWindowSizeChanged(
                window,
                Maths::Float2{
                    static_cast<float>(new_w),
                    static_cast<float>(new_h)
                },
                was_minimized
            );
        }

        bool const was_restored = (message.WParam == SIZE_RESTORED);
        bool const was_maximized = (message.WParam == SIZE_MAXIMIZED);

        if (was_restored || was_maximized)
        {
            Impl::GApplicationEventHandler->OnWindowAction(
                window,
                was_maximized
                ? WindowAction::Maximize
                : WindowAction::Restore
            );
        }
    }

    static void WmSizing(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        Impl::GApplicationEventHandler->OnWindowSizing(window);

        auto const& descriptor = window.GetDescriptor();

        if (descriptor.PreserveAspectRatio)
        {
            WINDOWINFO wi{
                .cbSize = sizeof(wi),
            };

            GetWindowInfo(
                message.HWnd,
                &wi
            );

            RECT rc{};

            AdjustWindowRectEx(
                &rc,
                wi.dwStyle,
                FALSE,
                wi.dwExStyle
            );

            RECT& rc_window = *reinterpret_cast<RECT*>(message.LParam);
            rc_window.left -= rc.left;
            rc_window.right -= rc.right;
            rc_window.top -= rc.top;
            rc_window.bottom -= rc.bottom;

            float const aspect_ratio = window.GetAspectRatio();
            LONG const new_w = (rc_window.right - rc_window.left);
            LONG const new_h = (rc_window.bottom - rc_window.top);

            switch (message.WParam)
            {
            case WMSZ_LEFT:
            case WMSZ_RIGHT:
                {
                    LONG const adjust_h = static_cast<LONG>(new_w / aspect_ratio);
                    rc_window.top -= static_cast<LONG>((adjust_h - new_h) / 2);
                    rc_window.bottom += static_cast<LONG>((adjust_h - new_h) / 2);
                    break;
                }
            case WMSZ_TOP:
            case WMSZ_BOTTOM:
                {
                    LONG const adjust_w = static_cast<LONG>(new_h * aspect_ratio);
                    rc_window.left -= static_cast<LONG>((adjust_w - new_w) / 2);
                    rc_window.right += static_cast<LONG>((adjust_w - new_w) / 2);
                    break;
                }
            case WMSZ_TOPLEFT:
            case WMSZ_TOPRIGHT:
                {
                    LONG const adjust_h = static_cast<LONG>(new_w / aspect_ratio);
                    rc_window.top -= static_cast<LONG>(adjust_h - new_h);
                    break;
                }
            case WMSZ_BOTTOMLEFT:
            case WMSZ_BOTTOMRIGHT:
                {
                    LONG const adjust_h = static_cast<LONG>(new_w / aspect_ratio);
                    rc_window.bottom += static_cast<LONG>(adjust_h - new_h);
                    break;
                }
            }

            AdjustWindowRectEx(
                &rc_window,
                wi.dwStyle,
                FALSE,
                wi.dwExStyle
            );

            message.Result = TRUE;
        }
        else
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmMove(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        LONG const new_x = GET_X_LPARAM(message.LParam);
        LONG const new_y = GET_Y_LPARAM(message.LParam);

        if (new_x != -32000 && new_y != -32000)
        {
            Impl::GApplicationEventHandler->OnWindowMoved(
                window,
                Maths::Float2{
                    static_cast<float>(new_x),
                    static_cast<float>(new_y)
                }
            );
        }
        else
        {
            Impl::BaseWindowProc(message);
        }
    }

    static void WmActivate(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        auto activation = WindowActivation::Deactivate;

        WORD const flags = LOWORD(message.WParam);

        if (flags & WA_ACTIVE)
        {
            activation = Impl::GApplicationActivateByMouse
                ? WindowActivation::MouseActivate
                : WindowActivation::Activate;
        }
        else if (flags & WA_CLICKACTIVE)
        {
            activation = WindowActivation::MouseActivate;
        }

        Impl::GApplicationActivateByMouse = false;

        UpdateModifierKeys();

        Impl::GApplicationEventHandler->OnWindowActivated(
            window,
            activation
        );
    }

    static void WmInput(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        UINT size = 0;
        HRAWINPUT device_handle = reinterpret_cast<HRAWINPUT>(message.LParam);

        GetRawInputData(device_handle, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));

        std::vector<uint8_t> raw_data(size, 0);

        if (GetRawInputData(device_handle, RID_INPUT, std::data(raw_data), &size, sizeof(RAWINPUTHEADER)) == size)
        {
            RAWINPUT* data = reinterpret_cast<RAWINPUT*>(std::data(raw_data));

            if (data->header.dwType == RIM_TYPEMOUSE)
            {
                bool const is_absolute = (data->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) == MOUSE_MOVE_ABSOLUTE;

                if (is_absolute)
                {
                    Impl::GApplicationEventHandler->OnMouseMove();
                }
                else
                {
                    Maths::Float2 const position{
                        static_cast<float>(data->data.mouse.lLastX),
                        static_cast<float>(data->data.mouse.lLastY)
                    };

                    Impl::GApplicationEventHandler->OnMouseMove(
                        position
                    );
                }

                message.Result = TRUE;
                return;
            }
        }

        Impl::BaseWindowProc(message);
    }

    static void WmDisplayChange(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        GX_LOG(LogPlatform, Trace,
            "Display changed! bits per pixel = {}, width = {}, height = {}\n",
            static_cast<UINT>(message.WParam),
            static_cast<UINT>(LOWORD(message.LParam)),
            static_cast<UINT>(HIWORD(message.LParam))
        );
    }

    static void WmDpiChanged(
        Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        window.SetDPIScale(static_cast<float>(LOWORD(message.WParam)) / 96.0F);

        RECT& rect = *reinterpret_cast<LPRECT>(message.LParam);

        SetWindowPos(
            message.HWnd,
            nullptr,
            rect.left,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOZORDER | SWP_NOACTIVATE
        );

        Impl::GApplicationEventHandler->OnDPIScaleChanged(
            window
        );

        Impl::BaseWindowProc(message);
    }

    static void WmDeviceChange(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        Impl::QueryInputDevices();

        Impl::BaseWindowProc(message);
    }

    static void WmPowerBroadcast(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
    {
        switch (message.WParam)
        {
        case PBT_APMPOWERSTATUSCHANGE:
            GX_LOG(LogPlatform, Info, "Power Event: Status Changed\n");
            break;
        case PBT_APMRESUMEAUTOMATIC:
            GX_LOG(LogPlatform, Info, "Power Event: Resume-Automatic\n");
            Impl::GApplicationEventHandler->OnPowerResume();
            break;
        case PBT_APMRESUMESUSPEND:
            GX_LOG(LogPlatform, Info, "Power Event: Resume Suspend\n");
            Impl::GApplicationEventHandler->OnPowerSuspend();
            break;
        case PBT_APMSUSPEND:
            GX_LOG(LogPlatform, Info, "Power Event: Suspend\n");
            break;
        }

        message.Result = TRUE;
    }

    static void WmEndSession(
        [[maybe_unused]] Impl::WindowsWindow& window,
        Message& message
    ) noexcept
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
        }

        Impl::GApplicationEventHandler->OnApplicationShutdown(reason);

        Impl::BaseWindowProc(message);
    }

    static_assert(sizeof(LONG_PTR) == sizeof(void*));

    static LRESULT CALLBACK ProcessMessage(
        HWND hWnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam
    ) noexcept
    {
        Impl::WindowsWindow* window = reinterpret_cast<Impl::WindowsWindow*>(GetWindowLongPtrW(
            hWnd,
            GWLP_USERDATA
        ));

        if (window == nullptr)
        {
            if (uMsg == WM_GETMINMAXINFO)
            {
                // TODO: Possible bug - window should pass this message to processing loop as well.
                return 0;
            }

            GX_ASSERTF(uMsg == WM_NCCREATE, "First message is invalid: got {}", uMsg);

            auto create_params = reinterpret_cast<CREATESTRUCTW*>(lParam);
            auto native_window = reinterpret_cast<Impl::WindowsWindow*>(create_params->lpCreateParams);

            SetWindowLongPtrW(
                hWnd,
                GWLP_USERDATA,
                reinterpret_cast<LONG_PTR>(native_window)
            );
            window = native_window;
        }

        Impl::Message message{
            .HWnd = hWnd,
            .Msg = uMsg,
            .WParam = wParam,
            .LParam = lParam,
            .Result = 0
        };

        GX_ASSERT(window != nullptr);

        if (window != nullptr)
        {
            switch (uMsg)
            {
            case WM_CHAR:
                Impl::WmChar(*window, message);
                break;

            case WM_SYSCHAR:
                Impl::WmSysChar(*window, message);
                break;

            case WM_SYSKEYDOWN:
                Impl::WmSysKeyDown(*window, message);
                break;

            case WM_KEYDOWN:
                Impl::WmKeyDown(*window, message);
                break;

            case WM_SYSKEYUP:
            case WM_KEYUP:
                Impl::WmKeyUp(*window, message);
                break;

            case WM_TOUCH:
                Impl::WmTouch(*window, message);
                break;

            case WM_LBUTTONDBLCLK:
            case WM_LBUTTONDOWN:
            case WM_MBUTTONDBLCLK:
            case WM_MBUTTONDOWN:
            case WM_RBUTTONDBLCLK:
            case WM_RBUTTONDOWN:
            case WM_XBUTTONDBLCLK:
            case WM_XBUTTONDOWN:
            case WM_XBUTTONUP:
            case WM_LBUTTONUP:
            case WM_MBUTTONUP:
            case WM_RBUTTONUP:
                Impl::WmMouseButton(*window, message);
                break;

            case WM_NCMOUSEMOVE:
            case WM_MOUSEMOVE:
                Impl::WmMouseMove(*window, message);
                break;

            case WM_MOUSEWHEEL:
                Impl::WmMouseWheel(*window, message);
                break;

            case WM_SETCURSOR:
                Impl::WmSetCursor(*window, message);
                break;

            case WM_INPUT:
                Impl::WmInput(*window, message);
                break;

            case WM_NCCALCSIZE:
                Impl::WmNcCalcSize(*window, message);
                break;

            case WM_SHOWWINDOW:
                Impl::WmShowWindow(*window, message);
                break;

            case WM_SIZE:
                Impl::WmSize(*window, message);
                break;

            case WM_SIZING:
                Impl::WmSizing(*window, message);
                break;

            case WM_ENTERSIZEMOVE:
                Impl::WmEnterSizeMove(*window, message);
                break;

            case WM_EXITSIZEMOVE:
                Impl::WmLeaveSizeMove(*window, message);
                break;

            case WM_MOVE:
                Impl::WmMove(*window, message);
                break;

            case WM_ACTIVATE:
                Impl::WmActivate(*window, message);
                break;

            case WM_MOUSEACTIVATE:
                Impl::WmMouseActivate(*window, message);
                break;

            case WM_ACTIVATEAPP:
                Impl::WmActivateApp(*window, message);
                break;

            case WM_ERASEBKGND:
                Impl::WmEraseBackground(*window, message);
                break;

            case WM_NCACTIVATE:
                Impl::WmNcActivate(*window, message);
                break;

            case WM_NCPAINT:
                Impl::WmNcPaint(*window, message);
                break;

            case WM_CLOSE:
                Impl::WmClose(*window, message);
                break;

            case WM_SYSCOMMAND:
                Impl::WmSysCommand(*window, message);
                break;

            case WM_GETMINMAXINFO:
                Impl::WmGetMinMaxInfo(*window, message);
                break;

            case WM_NCLBUTTONDOWN:
            case WM_NCRBUTTONDOWN:
            case WM_NCMBUTTONDOWN:
                Impl::WmNcButtownDown(*window, message);
                break;

            case WM_DISPLAYCHANGE:
                Impl::WmDisplayChange(*window, message);
                break;

            case WM_DPICHANGED:
                Impl::WmDpiChanged(*window, message);
                break;

            case WM_GETDLGCODE:
                message.Result = DLGC_WANTALLKEYS;
                break;

            case WM_DEVICECHANGE:
                Impl::WmDeviceChange(*window, message);
                break;

            case WM_POWERBROADCAST:
                Impl::WmPowerBroadcast(*window, message);
                break;

            case WM_ENDSESSION:
                Impl::WmEndSession(*window, message);
                break;

            default:
                Impl::BaseWindowProc(message);
                break;
            }
        }

        return message.Result;
    }

    static bool RegisterWindowClass(
        HINSTANCE instance,
        HICON icon
    ) noexcept
    {
        WNDCLASSEXW wc{
            .cbSize        = sizeof(wc),
            .style         = CS_DBLCLKS | CS_OWNDC,
            .lpfnWndProc   = ProcessMessage,
            .cbClsExtra    = 0,
            .cbWndExtra    = 0,
            .hInstance     = instance,
            .hIcon         = icon,
            .hCursor       = LoadCursorW(nullptr, (LPCWSTR)IDC_ARROW),
            .hbrBackground = nullptr,
            .lpszMenuName  = nullptr,
            .lpszClassName = Impl::WindowsWindow::WindowsClassName,
            .hIconSm       = icon,
        };

        if (RegisterClassExW(&wc) == FALSE)
        {
            GX_ABORT("Cannot register window class");
            return false;
        }

        return true;
    }
}


namespace Graphyte::Application
{
    BASE_API void Initialize() noexcept
    {
        GX_ASSERT(System::Impl::GInstanceHandle != nullptr);

        DisableProcessWindowsGhosting();

        HICON icon = LoadIconW(
            System::Impl::GInstanceHandle,
            MAKEINTRESOURCEW(System::Impl::IDI_MAIN_ICON)
        );

        Impl::RegisterWindowClass(System::Impl::GInstanceHandle, icon);

        Impl::GApplicationStartupStickyKeys.cbSize = sizeof(Impl::GApplicationStartupStickyKeys);
        SystemParametersInfoW(
            SPI_GETSTICKYKEYS,
            sizeof(Impl::GApplicationStartupStickyKeys),
            &Impl::GApplicationStartupStickyKeys,
            0
        );

        Impl::GApplicationStartupToggleKeys.cbSize = sizeof(Impl::GApplicationStartupToggleKeys);
        SystemParametersInfoW(
            SPI_GETTOGGLEKEYS,
            sizeof(Impl::GApplicationStartupToggleKeys),
            &Impl::GApplicationStartupToggleKeys,
            0
        );

        Impl::GApplicationStartupFilterKeys.cbSize = sizeof(Impl::GApplicationStartupFilterKeys);
        SystemParametersInfoW(
            SPI_GETFILTERKEYS,
            sizeof(Impl::GApplicationStartupFilterKeys),
            &Impl::GApplicationStartupFilterKeys,
            0
        );

        Impl::ToggleAccessibility(false);

        Impl::QueryInputDevices();
    }

    BASE_API void Finalize() noexcept
    {
        Impl::ToggleAccessibility(false);
    }

    BASE_API const ApplicationDescriptor& GetDescriptor() noexcept
    {
        return Impl::GApplicationDescriptor;
    }

    BASE_API bool IsFirstInstance() noexcept
    {
        return Impl::GIsFirstInstance;
    }

    BASE_API bool IsRequestingExit() noexcept
    {
        return Impl::GIsRequestingExit;
    }

    BASE_API void RequestExit(
        bool force
    ) noexcept
    {
        GX_LOG(LogPlatform, Trace, "Application RequestExit({})\n", force);

        if (force)
        {
            //
            // Forced. Flush and terminate.
            //

            Diagnostics::Exit(0);
        }
        else
        {
            //
            // Post windows message queue quit message.
            //
            PostQuitMessage(0);
        }

        Impl::GIsRequestingExit = true;
    }

    BASE_API bool IsForeground() noexcept
    {
        DWORD process_id{};

        GetWindowThreadProcessId(
            GetForegroundWindow(),
            &process_id
        );

        return process_id == GetCurrentProcessId();
    }

    BASE_API void PollInputDevices(
        float deltaTime
    ) noexcept
    {
        Impl::GApplicationXInput.Poll(deltaTime);
    }

    BASE_API void PumpMessages(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
        MSG msg{};

        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) != FALSE)
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }


        //
        // WinAPI has bug where VK_SHIFT doesn't get KEY_UP message if both keys are hold down.
        // Check both keys and invoke missing callback.
        //

        Impl::FixShiftKeyState(VK_LSHIFT);
        Impl::FixShiftKeyState(VK_RSHIFT);
    }

    BASE_API void Tick(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
    }

    BASE_API void SetEventHandler(
        EventHandler* handler
    ) noexcept
    {
        Impl::GApplicationEventHandler = handler;
        Impl::GApplicationXInput.SetEventHandler(handler);
    }

    BASE_API EventHandler* GetEventHandler() noexcept
    {
        return Impl::GApplicationEventHandler;
    }

    BASE_API Window* CreateWindow(
        const WindowDescriptor& descriptor
    ) noexcept
    {
        auto* window = new Impl::WindowsWindow();
        window->Create(descriptor);

        //Impl::EnableHighPrecisionMouse(true, *window);
        //Impl::EnableRawInputMouse(*window, true, true);
        //Impl::EnableRawInputKeyboard(*window, true, true);

        return window;
    }

    BASE_API void DestroyWindow(
        Window* window
    ) noexcept
    {
        GX_ASSERT(window != nullptr);

        if (window != nullptr)
        {
            window->Destroy();

            delete window;
        }
    }
}
