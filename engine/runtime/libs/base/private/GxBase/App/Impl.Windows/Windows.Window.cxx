#include "Windows.Window.hxx"

#include <dwmapi.h>

namespace Graphyte::App::Impl
{
    static constexpr DWORD GetStyle(WindowType type, WindowMode mode) noexcept
    {
        DWORD result{};

        switch (type)
        {
        case WindowType::Game:
            switch (mode)
            {
            case WindowMode::Windowed:
                result |= WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER;
                break;
            case WindowMode::Fullscreen:
            case WindowMode::WindowedFullscreen:
                result |= WS_BORDER;
                break;
            }
            break;

        case WindowType::Viewport:
            result |= WS_CHILD;

        case WindowType::Form:
            result |= WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
            break;

        case WindowType::Dialog:
            result |= WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER;
            break;
        }

        return result;
    }
    static constexpr DWORD GetExStyle(WindowType type, [[maybe_unused]] WindowMode mode) noexcept
    {
        DWORD result{};

        switch (type)
        {
        case WindowType::Game:
            // Game window covers taskbar?
            //result |= WS_EX_TOPMOST;
            break;
        case WindowType::Viewport:
            // Viewport window is a window embedded with external window.
            // Input is handled by parent window.
            result |= WS_EX_TRANSPARENT;
            break;
        case WindowType::Form:
            // Form window is visible on taskbar.
            result |= WS_EX_APPWINDOW;
            break;
        case WindowType::Dialog:
            // Dialog window is not visible on taskbar.
            //result |= WS_EX_TOOLWINDOW;
            break;
        }

        return result;
    }
}

namespace Graphyte::App
{
    extern Window* Create(WindowType type) noexcept
    {
        static constexpr WindowMode DefaultWindowMode = WindowMode::Windowed;

        Window* self = new Window{
            .Type = type,
            .Mode = DefaultWindowMode,
        };

        CreateWindowExW(
            Impl::GetExStyle(type, DefaultWindowMode),
            L"GraphyteWindow",
            L"Graphyte Window",
            Impl::GetStyle(type, DefaultWindowMode),
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            nullptr,
            nullptr,
            System::Impl::GInstanceHandle,
            reinterpret_cast<LPVOID>(self));

        GX_ASSERT(self->Hwnd != nullptr);

        ShowWindow(self->Hwnd, SW_SHOW);

        return self;
    }

    extern void Destroy(Window* self) noexcept
    {
        if (DestroyWindow(self->Hwnd) == FALSE)
        {
            GX_ABORT("Failed to destroy window");
        }

        delete self;
    }

    extern bool Focus(Window& self) noexcept
    {
        if (GetFocus() != self.Hwnd)
        {
            SetFocus(self.Hwnd);
            return true;
        }

        return false;
    }

    extern bool BringToFront(Window& self, bool force) noexcept
    {
        if (self.Mode == WindowMode::Windowed && self.Type != WindowType::Viewport)
        {
            // Only windowed, top-level windows can be brought to front

            if (IsIconic(self.Hwnd))
            {
                // Restore minimized window
                ShowWindow(self.Hwnd, SW_RESTORE);
            }
            else
            {
                // Activate non-minimized window
                SetActiveWindow(self.Hwnd);
            }

            if (force)
            {
                BringWindowToTop(self.Hwnd);
            }
            else
            {
                ShowWindow(self.Hwnd, SW_SHOW);
            }

            return true;
        }

        return false;
    }

    extern bool Show(Window& self) noexcept
    {
        bool const result = ShowWindow(self.Hwnd, SW_SHOW) != FALSE;
        return result;
    }

    extern bool Hide(Window& self) noexcept
    {
        bool const result = ShowWindow(self.Hwnd, SW_HIDE) != FALSE;
        return result;
    }

    extern bool Enable(Window& self) noexcept
    {
        bool const result = EnableWindow(self.Hwnd, TRUE) != FALSE;
        return result;
    }

    extern bool Disable(Window& self) noexcept
    {
        bool const result = EnableWindow(self.Hwnd, FALSE) != FALSE;
        return result;
    }

    extern bool Minimize(Window& self) noexcept
    {
        if (self.Mode == WindowMode::Windowed)
        {
            bool const result = ShowWindow(self.Hwnd, SW_MINIMIZE) != FALSE;
            return result;
        }

        return false;
    }

    extern bool Maximize(Window& self) noexcept
    {
        if (self.Mode == WindowMode::Windowed)
        {
            bool const result = ShowWindow(self.Hwnd, SW_MAXIMIZE) != FALSE;
            return result;
        }

        return false;
    }

    extern bool Restore(Window& self) noexcept
    {
        if (self.Mode == WindowMode::Windowed)
        {
            bool const result = ShowWindow(self.Hwnd, SW_RESTORE) != FALSE;
            return result;
        }

        return false;
    }

    extern bool IsMinimized(Window& self) noexcept
    {
        bool const result = IsIconic(self.Hwnd) != FALSE;
        return result;
    }

    extern bool IsMaximized(Window& self) noexcept
    {
        bool const result = IsZoomed(self.Hwnd) != FALSE;
        return result;

    }
    extern bool IsFocused(Window& self) noexcept
    {
        bool const result = GetForegroundWindow() == self.Hwnd;
        return result;
    }

    extern bool IsEnabled(Window& self) noexcept
    {
        bool const result = IsWindowEnabled(self.Hwnd) != FALSE;
        return result;
    }

    extern bool IsVisible(Window& self) noexcept
    {
        bool const result = IsWindowVisible(self.Hwnd) != FALSE;
        return result;
    }

    extern bool SetMode(Window& self, WindowMode value) noexcept
    {
        if (self.Mode != value)
        {
            if (self.Type == WindowType::Game)
            {
                DWORD const dwStyle = Impl::GetStyle(self.Type, value);
                DWORD const dwExStyle = Impl::GetExStyle(self.Type, value);

                if (self.Mode == WindowMode::Windowed)
                {
                    // Store window placement for going back to windowed mode.
                    self.PreFullscreenPlacement.length = sizeof(WINDOWPLACEMENT);
                    GetWindowPlacement(self.Hwnd, &self.PreFullscreenPlacement);
                }

                // Set new styles
                SetWindowLongW(self.Hwnd, GWL_STYLE, static_cast<LONG>(dwStyle));
                SetWindowLongW(self.Hwnd, GWL_EXSTYLE, static_cast<LONG>(dwExStyle));

                // Update parts of window
                SetWindowPos(self.Hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                // Restore window state
                ShowWindow(self.Hwnd, SW_RESTORE);

                if (value == WindowMode::Fullscreen || value == WindowMode::WindowedFullscreen)
                {
                    // Get hint of which device we are adjusting
                    bool const exclusive = (value == WindowMode::Fullscreen);

                    HMONITOR hMonitor = MonitorFromWindow(
                        self.Hwnd,
                        exclusive ? MONITOR_DEFAULTTOPRIMARY : MONITOR_DEFAULTTONEAREST);

                    MONITORINFO mi{
                        .cbSize = sizeof(mi),
                    };

                    GetMonitorInfoW(hMonitor, &mi);


                    // Adjust window to match border size
                    RECT rcBorder{};
                    AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

                    SetWindowPos(
                        self.Hwnd,
                        nullptr,
                        (mi.rcMonitor.left + rcBorder.left),
                        (mi.rcMonitor.top + rcBorder.top),
                        (mi.rcMonitor.right - mi.rcMonitor.left) + (rcBorder.right - rcBorder.left),
                        (mi.rcMonitor.bottom - mi.rcMonitor.top) + (rcBorder.bottom - rcBorder.top),
                        SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
                }
                else
                {
                    // Going to windowed mode.

                    if (self.PreFullscreenPlacement.length != 0)
                    {
                        // Restore placement from before window went fullscreen.
                        SetWindowPlacement(self.Hwnd, &self.PreFullscreenPlacement);
                    }
                }

                self.Mode = value;

                return true;
            }
            else
            {
                GX_LOG_WARN(LogNativeApp, "Cannot change mode of non-game window\n");
            }
        }

        return false;
    }

    extern WindowMode GetMode(Window& self) noexcept
    {
        return self.Mode;
    }

    extern WindowType GetType(Window& self) noexcept
    {
        return self.Type;
    }

    extern void* GetNativeHandle(Window& self) noexcept
    {
        return reinterpret_cast<void*>(self.Hwnd);
    }

    extern System::Size GetClientSize(Window& self) noexcept
    {
        RECT rcClient{};
        GetClientRect(self.Hwnd, &rcClient);

        return System::Size{
            .Width = (rcClient.right - rcClient.left),
            .Height = (rcClient.bottom - rcClient.top),
        };
    }

    extern bool GetFullscreenPlacement(Window& self, System::Rect& out_value) noexcept
    {
        // For exclusive fullscreen, get default primary monitor desktop rectangle.
        // This works for all rendering APIs, as we rely on system defaults.
        //
        // Windowed / FullscreenWindowed is specific for current monitor on window is being
        // displayed.

        bool const exclusive = (self.Mode == WindowMode::Fullscreen);

        HMONITOR hMonitor = MonitorFromWindow(
            self.Hwnd,
            exclusive ? MONITOR_DEFAULTTOPRIMARY : MONITOR_DEFAULTTONEAREST);

        MONITORINFO mi{ .cbSize = sizeof(mi) };

        if (GetMonitorInfoW(hMonitor, &mi) != FALSE)
        {
            out_value = System::Rect{
                .Left = mi.rcMonitor.left,
                .Top = mi.rcMonitor.top,
                .Width = mi.rcMonitor.right - mi.rcMonitor.left,
                .Height = mi.rcMonitor.bottom - mi.rcMonitor.top,
            };

            return true;
        }

        return false;
    }

    extern bool SetCaption(Window& self, std::string_view value) noexcept
    {
        std::wstring wtitle = System::Impl::WidenString(value);
        bool const result = SetWindowTextW(self.Hwnd, wtitle.c_str()) != FALSE;
        return result;
    }

    extern bool GetPlacement(Window& self, System::Rect& out_value) noexcept
    {
        (void)self;
        (void)out_value;
        return false;
    }

    extern bool SetPlacement(Window& self, System::Rect value) noexcept
    {
        if (self.Mode == WindowMode::Windowed)
        {
            // Only windowed window can be placed anywhere.
            // Fullscreen window is associated with monitor.

            WINDOWINFO wi{ .cbSize = sizeof(wi) };

            GetWindowInfo(self.Hwnd, &wi);

            RECT rcBorder{};
            AdjustWindowRectEx(&rcBorder, wi.dwStyle, FALSE, wi.dwExStyle);

            value.Left += rcBorder.left;
            value.Top += rcBorder.top;
            value.Width += (rcBorder.right - rcBorder.left);
            value.Height += (rcBorder.bottom - rcBorder.top);

            if (IsMaximized(self))
            {
                Restore(self);
            }

            SetWindowPos(
                self.Hwnd,
                nullptr,
                value.Left,
                value.Top,
                value.Width,
                value.Height,
                SWP_NOACTIVATE | SWP_NOZORDER);

            return true;
        }

        return false;
    }

    extern bool SetLocation(Window& self, System::Point value) noexcept
    {
        if (self.Mode == WindowMode::Windowed)
        {
            DWORD dwStyle = static_cast<DWORD>(GetWindowLongW(self.Hwnd, GWL_STYLE));
            DWORD dwExStyle = static_cast<DWORD>(GetWindowLongW(self.Hwnd, GWL_EXSTYLE));

            RECT rcBorder{};
            AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

            value.Left += rcBorder.left;
            value.Top += rcBorder.top;

            SetWindowPos(
                self.Hwnd,
                nullptr,
                value.Left,
                value.Top,
                0,
                0,
                SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);

            return true;
        }

        return false;
    }

    extern bool SetSize(Window& self, System::Size value) noexcept
    {
        if (self.Mode == WindowMode::Windowed)
        {
            DWORD dwStyle = static_cast<DWORD>(GetWindowLongW(self.Hwnd, GWL_STYLE));
            DWORD dwExStyle = static_cast<DWORD>(GetWindowLongW(self.Hwnd, GWL_EXSTYLE));

            RECT rcBorder{};
            AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

            value.Width += (rcBorder.right - rcBorder.left);
            value.Height += (rcBorder.bottom - rcBorder.top);

            SetWindowPos(
                self.Hwnd,
                nullptr,
                0,
                0,
                value.Width,
                value.Height,
                SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOZORDER);

            return true;
        }

        return false;
    }
    extern float GetDpiScale(Window& self) noexcept
    {
        return self.DpiScale;
    }
    extern void SetDpiScale(Window& self, float value) noexcept
    {
        self.DpiScale = value;
    }

    extern WindowSizeLimits GetSizeLimits(Window& self) noexcept
    {
        return self.SizeLimits;
    }

    extern bool SetSizeLimits(Window& self, WindowSizeLimits value) noexcept
    {
        if (self.Type == WindowType::Form)
        {
            self.SizeLimits = value;

            // Let DWM to adjust current size to new limits.
            SetWindowPos(
                self.Hwnd,
                nullptr,
                0, 0, 0, 0,
                SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);

            return true;
        }

        return false;
    }
}
