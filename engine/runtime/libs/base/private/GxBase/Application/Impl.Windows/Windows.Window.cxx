#include "Windows.Window.hxx"
#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>
#include <GxBase/Application.hxx>

#include <dwmapi.h>

namespace Graphyte::Application::Impl
{
    const wchar_t* WindowsWindow::WindowsClassName = L"Graphyte::Window";

    WindowsWindow::WindowsWindow() noexcept
        : m_PreFullscreenPlacement{}
        , m_PreParentMinimizedPlacement{}
        , m_Handle{ nullptr }
        , m_WindowMode{ WindowMode::Windowed }
        , m_IsVisible{ false }
        , m_IsFirstTimeVisible{ true }
        , m_IsInitMinimized{ false }
        , m_IsInitMaximized{ false }
    {
        m_PreParentMinimizedPlacement.length = sizeof(WINDOWPLACEMENT);
    }

    WindowsWindow::~WindowsWindow() noexcept
    {
        GX_ASSERTF(m_Handle == nullptr, "Application::DestroyWindow was not called on this instance!");
    }

    void WindowsWindow::Create(
        const WindowDescriptor& descriptor) noexcept
    {
        m_Descriptor = descriptor;

        std::wstring wtitle = System::Impl::WidenString(descriptor.Title);

        DWORD dw_style    = 0;
        DWORD dw_style_ex = 0;

        int32_t client_x = m_Descriptor.Position.Left;
        int32_t client_y = m_Descriptor.Position.Top;
        int32_t client_w = m_Descriptor.Size.Width;
        int32_t client_h = m_Descriptor.Size.Height;

        int32_t window_x = client_x;
        int32_t window_y = client_y;
        int32_t window_w = client_w;
        int32_t window_h = client_h;


        if (m_Descriptor.SystemBorder)
        {
            dw_style_ex = WS_EX_APPWINDOW;
            dw_style    = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;

            if (m_Descriptor.Regular)
            {
                if (m_Descriptor.MaximizeButton)
                {
                    dw_style |= WS_MAXIMIZEBOX;
                }

                if (m_Descriptor.MinimizeButton)
                {
                    dw_style |= WS_MINIMIZEBOX;
                }

                if (m_Descriptor.Resizable)
                {
                    dw_style |= WS_THICKFRAME;
                }
                else
                {
                    dw_style |= WS_BORDER;
                }
            }
            else
            {
                dw_style |= WS_POPUP | WS_BORDER;
            }

            RECT rc_border{};
            AdjustWindowRectEx(
                &rc_border,
                dw_style,
                FALSE,
                dw_style_ex);

            window_x += rc_border.left;
            window_y += rc_border.top;

            window_w += (rc_border.right - rc_border.left);
            window_h += (rc_border.bottom - rc_border.top);
        }
        else
        {
            dw_style_ex = WS_EX_WINDOWEDGE;

            dw_style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

            if (m_Descriptor.Taskbar)
            {
                dw_style_ex |= WS_EX_APPWINDOW;
            }
            else
            {
                dw_style_ex |= WS_EX_TOOLWINDOW;
            }

            if (m_Descriptor.Topmost)
            {
                dw_style_ex |= WS_EX_TOPMOST;
            }

            if (!m_Descriptor.AcceptInput)
            {
                dw_style_ex |= WS_EX_TRANSPARENT;
            }
        }

        m_Handle = CreateWindowExW(
            dw_style_ex,
            WindowsClassName,
            wtitle.c_str(),
            dw_style,
            window_x,
            window_y,
            window_w,
            window_h,
            nullptr,
            nullptr,
            System::Impl::GInstanceHandle,
            reinterpret_cast<LPVOID>(this));

        GX_ASSERTF(m_Handle != nullptr, "Cannot create window: {}", GetLastError());

        GX_ASSERTF(RegisterTouchWindow(m_Handle, 0) != FALSE, "Cannot register touch window: {}", GetLastError());

        m_ClientWidth  = client_w;
        m_ClientHeight = client_h;

        // FIXME: Styling
        SetPlacement(
            { .Left     = client_x,
                .Top    = client_y,
                .Width  = client_w,
                .Height = client_h });

        if (!m_Descriptor.SystemBorder)
        {
            const DWMNCRENDERINGPOLICY rendering_policy = DWMNCRP_DISABLED;

            if (FAILED(DwmSetWindowAttribute(m_Handle, DWMWA_NCRENDERING_POLICY, &rendering_policy, sizeof(rendering_policy))))
            {
                GX_ABORT("Failed to set window rendering policy");
            }

            const BOOL allow_ncpaint = FALSE;

            if (FAILED(DwmSetWindowAttribute(m_Handle, DWMWA_ALLOW_NCPAINT, &allow_ncpaint, sizeof(allow_ncpaint))))
            {
                GX_ABORT("Failed to set window NC policy");
            }

            //MARGINS margins{ -1 };
            //GX_VERIFY(SUCCEEDED(DwmExtendFrameIntoClientArea(m_Handle, &margins)));
        }

        if (m_Descriptor.Regular && !m_Descriptor.SystemBorder)
        {
            dw_style |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

            if (m_Descriptor.MaximizeButton)
            {
                dw_style |= WS_MAXIMIZEBOX;
            }

            if (m_Descriptor.MinimizeButton)
            {
                dw_style |= WS_MINIMIZEBOX;
            }

            if (m_Descriptor.Resizable)
            {
                dw_style |= WS_THICKFRAME;
            }

            if (SetWindowLongW(m_Handle, GWL_STYLE, static_cast<LONG>(dw_style)) == 0)
            {
                GX_ABORT("Cannot set window style");
            }

            UINT swp_flags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;

            if (m_Descriptor.ActivationPolicy == WindowActivationPolicy::Never)
            {
                swp_flags |= SWP_NOACTIVATE;
            }

            SetWindowPos(
                m_Handle,
                nullptr,
                0,
                0,
                0,
                0,
                swp_flags);
        }
        else if (m_Descriptor.SystemBorder)
        {
            if (!m_Descriptor.CloseButton)
            {
                EnableMenuItem(
                    GetSystemMenu(
                        m_Handle,
                        FALSE),
                    SC_CLOSE,
                    MF_GRAYED);
            }
        }

        // For regular window, register DND
    }

    void WindowsWindow::Destroy() noexcept
    {
        if (DestroyWindow(m_Handle) == FALSE)
        {
            GX_ABORT("Failed to destroy window");
        }

        m_Handle = nullptr;
    }

    void WindowsWindow::Move(
        System::Point location) noexcept
    {
        if (m_Descriptor.SystemBorder)
        {
            DWORD style  = static_cast<DWORD>(GetWindowLongW(m_Handle, GWL_STYLE));
            DWORD stylex = static_cast<DWORD>(GetWindowLongW(m_Handle, GWL_EXSTYLE));

            RECT rc{};
            AdjustWindowRectEx(
                &rc,
                style,
                FALSE,
                stylex);

            location.Left += rc.left;
            location.Top += rc.top;
        }

        SetWindowPos(
            m_Handle,
            nullptr,
            location.Left,
            location.Top,
            0,
            0,
            SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
    }

    void WindowsWindow::Resize(
        [[maybe_unused]] System::Size size) noexcept
    {
    }

    void WindowsWindow::Focus() noexcept
    {
        if (GetFocus() != m_Handle)
        {
            SetFocus(
                m_Handle);
        }
    }

    void WindowsWindow::BringToFront(
        bool force) noexcept
    {
        if (m_Descriptor.Regular)
        {
            if (IsIconic(m_Handle))
            {
                ShowWindow(
                    m_Handle,
                    SW_RESTORE);
            }
            else
            {
                SetActiveWindow(
                    m_Handle);
            }
        }
        else
        {
            HWND insert_after = HWND_TOP;
            UINT flags        = SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER;

            if (!force)
            {
                flags |= SWP_NOACTIVATE;
            }

            if (m_Descriptor.Topmost)
            {
                insert_after = HWND_TOPMOST;
            }

            SetWindowPos(
                m_Handle,
                insert_after,
                0,
                0,
                0,
                0,
                flags);
        }


        if (force)
        {
            BringWindowToTop(
                m_Handle);
        }
        else
        {
            ShowWindow(
                m_Handle,
                SW_SHOW);
        }
    }

    void WindowsWindow::Minimize() noexcept
    {
        if (!m_IsFirstTimeVisible)
        {
            ShowWindow(
                m_Handle,
                SW_MINIMIZE);
        }
        else
        {
            m_IsInitMinimized = true;
            m_IsInitMaximized = false;
        }
    }

    void WindowsWindow::Maximize() noexcept
    {
        if (!m_IsFirstTimeVisible)
        {
            ShowWindow(
                m_Handle,
                SW_MAXIMIZE);
        }
        else
        {
            m_IsInitMinimized = false;
            m_IsInitMaximized = true;
        }
    }

    void WindowsWindow::Restore() noexcept
    {
        if (!m_IsFirstTimeVisible)
        {
            ShowWindow(
                m_Handle,
                SW_RESTORE);
        }
        else
        {
            m_IsInitMinimized = false;
            m_IsInitMaximized = false;
        }
    }

    void WindowsWindow::Show() noexcept
    {
        if (!m_IsVisible)
        {
            m_IsVisible = true;

            bool should_activate = false;

            if (m_Descriptor.AcceptInput)
            {
                should_activate = (m_Descriptor.ActivationPolicy == WindowActivationPolicy::Always);

                if (m_IsFirstTimeVisible && m_Descriptor.ActivationPolicy == WindowActivationPolicy::FirstShown)
                {
                    should_activate = true;
                }
            }

            int show_command = should_activate
                                   ? SW_SHOW
                                   : SW_SHOWNOACTIVATE;

            if (m_IsFirstTimeVisible)
            {
                m_IsFirstTimeVisible = false;

                if (m_IsInitMinimized)
                {
                    show_command = should_activate
                                       ? SW_MINIMIZE
                                       : SW_SHOWMINNOACTIVE;
                }
                else if (m_IsInitMaximized)
                {
                    //show_command = should_activate ? SW_SHOWMAXIMIZED : SW_MAXIMIZE;
                    show_command = SW_SHOWMAXIMIZED;
                }
            }


            ShowWindow(
                m_Handle,
                show_command);
        }
    }

    void WindowsWindow::Hide() noexcept
    {
        if (m_IsVisible)
        {
            m_IsVisible = false;

            ShowWindow(
                m_Handle,
                SW_HIDE);
        }
    }

    void WindowsWindow::Enable() noexcept
    {
        EnableWindow(
            m_Handle,
            TRUE);
    }

    void WindowsWindow::Disable() noexcept
    {
        EnableWindow(
            m_Handle,
            FALSE);
    }

    void WindowsWindow::SetWindowMode(
        WindowMode value) noexcept
    {
        if (m_WindowMode != value)
        {
            auto const previous_mode = m_WindowMode;
            m_WindowMode             = value;

            bool const is_true_fullscreen = (value == WindowMode::Fullscreen);

            DWORD dw_style            = static_cast<DWORD>(GetWindowLongW(m_Handle, GWL_STYLE));
            DWORD dw_fullscreen_style = WS_POPUP;

            DWORD dw_windowed_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;

            if (m_Descriptor.Regular)
            {
                if (m_Descriptor.MinimizeButton)
                {
                    dw_windowed_style |= WS_MINIMIZEBOX;
                }

                if (m_Descriptor.MaximizeButton)
                {
                    dw_windowed_style |= WS_MAXIMIZEBOX;
                }

                if (m_Descriptor.Resizable)
                {
                    dw_windowed_style |= WS_THICKFRAME;
                }
                else
                {
                    dw_windowed_style |= WS_BORDER;
                }
            }
            else
            {
                dw_windowed_style |= WS_POPUP | WS_BORDER;
            }

            if (value == WindowMode::Fullscreen || value == WindowMode::WindowedFullscreen)
            {
                if (previous_mode == WindowMode::Windowed)
                {
                    m_PreFullscreenPlacement.length = sizeof(WINDOWPLACEMENT);
                    GetWindowPlacement(m_Handle, &m_PreFullscreenPlacement);
                }

                dw_style &= ~dw_windowed_style;
                dw_style |= dw_fullscreen_style;

                SetWindowLongW(
                    m_Handle,
                    GWL_STYLE,
                    static_cast<LONG>(dw_style));

                SetWindowPos(
                    m_Handle,
                    nullptr,
                    0,
                    0,
                    0,
                    0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                if (!is_true_fullscreen)
                {
                    ShowWindow(m_Handle, SW_RESTORE);
                }

                RECT rc_client{};

                GetClientRect(
                    m_Handle,
                    &rc_client);

                DWORD target_monitor = static_cast<DWORD>(
                    is_true_fullscreen
                        ? MONITOR_DEFAULTTOPRIMARY
                        : MONITOR_DEFAULTTONEAREST);

                HMONITOR monitor = MonitorFromWindow(
                    m_Handle,
                    target_monitor);

                MONITORINFO mi{
                    .cbSize = sizeof(mi),
                };

                GetMonitorInfoW(monitor, &mi);

                LONG monitor_width  = (mi.rcMonitor.right - mi.rcMonitor.left);
                LONG monitor_height = (mi.rcMonitor.bottom - mi.rcMonitor.top);

                LONG target_width = is_true_fullscreen
                                        ? std::min(monitor_width, rc_client.right - rc_client.left)
                                        : monitor_width;

                LONG target_height = is_true_fullscreen
                                         ? std::min(monitor_height, rc_client.bottom - rc_client.top)
                                         : monitor_height;

                // FIXME: Styling
                SetPlacement({ .Left = mi.rcMonitor.left,
                    .Top             = mi.rcMonitor.top,
                    .Width           = target_width,
                    .Height          = target_height });
            }
            else
            {
                dw_style &= ~dw_fullscreen_style;
                dw_style |= dw_windowed_style;

                SetWindowLongW(
                    m_Handle,
                    GWL_STYLE,
                    static_cast<LONG>(dw_style));

                SetWindowPos(
                    m_Handle,
                    nullptr,
                    0,
                    0,
                    0,
                    0,
                    SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                if (m_PreFullscreenPlacement.length != 0)
                {
                    SetWindowPlacement(
                        m_Handle,
                        &m_PreFullscreenPlacement);
                }
            }
        }
    }

    WindowMode WindowsWindow::GetWindowMode() noexcept
    {
        return m_WindowMode;
    }

    void WindowsWindow::SetCaption(
        const char* text) noexcept
    {
        SetWindowTextA(m_Handle, text);
    }

    void WindowsWindow::SetPlacement(System::Rect placement) noexcept
    {
        WINDOWINFO wi{
            wi.cbSize = sizeof(wi),
        };

        GetWindowInfo(
            m_Handle,
            &wi);

        m_AspectRatio = static_cast<float>(placement.Width) / static_cast<float>(placement.Height);

        if (m_Descriptor.SystemBorder)
        {
            RECT rc_border{};

            AdjustWindowRectEx(
                &rc_border,
                wi.dwStyle,
                FALSE,
                wi.dwExStyle);

            placement.Left += rc_border.left;
            placement.Top += rc_border.top;

            placement.Width += rc_border.right - rc_border.left;
            placement.Height += rc_border.bottom - rc_border.top;
        }

        m_ClientWidth  = placement.Width;
        m_ClientHeight = placement.Height;

        if (m_Descriptor.DelayResize)
        {
            auto const rc_prev        = wi.rcWindow;
            int32_t const prev_width  = rc_prev.right - rc_prev.left;
            int32_t const prev_height = rc_prev.bottom - rc_prev.top;

            int32_t const min_width = (m_Descriptor.ExpectedMaxSize.Width != 0)
                                          ? m_Descriptor.ExpectedMaxSize.Width
                                          : prev_width;

            int32_t const min_height = (m_Descriptor.ExpectedMaxSize.Height != 0)
                                           ? m_Descriptor.ExpectedMaxSize.Height
                                           : prev_height;

            placement.Width = std::max(
                placement.Width,
                std::min(
                    prev_width,
                    min_width));

            placement.Height = std::max(
                placement.Height,
                std::min(
                    prev_height,
                    min_height));
        }

        if (IsMaximized())
        {
            Restore();
        }

        UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;

        if (m_WindowMode == WindowMode::Fullscreen)
        {
            flags |= SWP_NOSENDCHANGING;
        }

        SetWindowPos(
            m_Handle,
            nullptr,
            placement.Left,
            placement.Top,
            placement.Width,
            placement.Height,
            flags);
    }

    bool WindowsWindow::IsMaximized() noexcept
    {
        bool const is_minimized = !!IsZoomed(
            m_Handle);

        return is_minimized;
    }

    bool WindowsWindow::IsMinimized() noexcept
    {
        bool const is_maximized = !!IsIconic(
            m_Handle);

        return is_maximized;
    }

    bool WindowsWindow::IsVisible() noexcept
    {
        return m_IsVisible;
    }

    bool WindowsWindow::IsEnabled() noexcept
    {
        bool const is_enabled = !!IsWindowEnabled(
            m_Handle);

        return is_enabled;
    }

    bool WindowsWindow::IsFocused() noexcept
    {
        bool const is_foreground = (GetForegroundWindow() == m_Handle);
        return is_foreground;
    }

    void* WindowsWindow::GetNativeHandle() noexcept
    {
        return reinterpret_cast<void*>(m_Handle);
    }

    int32_t WindowsWindow::GetBorderSize() noexcept
    {
        if (m_Descriptor.Type == WindowType::GameWindow && !m_Descriptor.SystemBorder)
        {
            return 0;
        }

        WINDOWINFO wi{
            .cbSize = sizeof(wi)
        };

        GetWindowInfo(
            m_Handle,
            &wi);

        return static_cast<int32_t>(wi.cxWindowBorders);
    }

    bool WindowsWindow::GetRestoredPlacement(
        System::Rect& placement) noexcept
    {
        WINDOWPLACEMENT wp{
            .length = sizeof(WINDOWPLACEMENT),
        };

        if (GetWindowPlacement(m_Handle, &wp))
        {
            RECT const restored = wp.rcNormalPosition;

            placement.Left   = restored.left;
            placement.Top    = restored.top;
            placement.Width  = restored.right - restored.left;
            placement.Height = restored.bottom - restored.top;

            DWORD const dw_style_ex = GetWindowLongW(m_Handle, GWL_STYLE);

            if ((dw_style_ex & WS_EX_TOOLWINDOW) != 0)
            {
                bool const is_true_fullscreen = (m_WindowMode == WindowMode::Fullscreen);

                DWORD target_monitor = static_cast<DWORD>(
                    is_true_fullscreen
                        ? MONITOR_DEFAULTTOPRIMARY
                        : MONITOR_DEFAULTTONEAREST);

                HMONITOR monitor = MonitorFromWindow(
                    m_Handle,
                    target_monitor);

                MONITORINFO mi{
                    .cbSize = sizeof(mi),
                };

                GetMonitorInfoW(
                    monitor,
                    &mi);

                placement.Left += (mi.rcWork.left - mi.rcMonitor.left);
                placement.Top += (mi.rcWork.top - mi.rcMonitor.top);
            }

            return true;
        }

        return false;
    }

    bool WindowsWindow::GetFullscreenInfo(
        System::Rect& screen_rect) noexcept
    {
        bool const is_fullscreen = (m_WindowMode == WindowMode::Fullscreen);

        HMONITOR monitor = MonitorFromWindow(
            m_Handle,
            static_cast<DWORD>(
                is_fullscreen
                    ? MONITOR_DEFAULTTOPRIMARY
                    : MONITOR_DEFAULTTONEAREST));

        MONITORINFO mi{
            .cbSize = sizeof(mi),
        };

        GetMonitorInfoW(
            monitor,
            &mi);

        screen_rect.Left   = mi.rcMonitor.left;
        screen_rect.Top    = mi.rcMonitor.top;
        screen_rect.Width  = mi.rcMonitor.right - mi.rcMonitor.left;
        screen_rect.Height = mi.rcMonitor.bottom - mi.rcMonitor.top;

        return true;
    }

    System::Size WindowsWindow::GetViewportSize() noexcept
    {
        RECT rc{};

        GetClientRect(
            m_Handle,
            &rc);

        return {
            rc.right - rc.left,
            rc.bottom - rc.top,
        };
    }

    void WindowsWindow::OnParentWindowMinimized() noexcept
    {
        GetWindowPlacement(
            m_Handle,
            &m_PreParentMinimizedPlacement);
    }

    void WindowsWindow::OnParentWindowRestored() noexcept
    {
        SetWindowPlacement(
            m_Handle,
            &m_PreParentMinimizedPlacement);
    }

    bool WindowsWindow::IsPointInside(
        System::Point value) noexcept
    {
        RECT rc_window{};

        GetWindowRect(
            m_Handle,
            &rc_window);

        bool const result = !!PtInRect(
            &rc_window,
            POINT{
                value.Left,
                value.Top });

        return result;
    }
}
