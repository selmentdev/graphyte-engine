#pragma once
#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>
#include <GxBase/App.hxx>

#include <dwmapi.h>

namespace Graphyte::App::Impl
{
    class NativeWindow final : public Window
    {
    private:
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

    private:
        WINDOWPLACEMENT m_PreFullscreenPlacement{};
        WindowSizeLimits m_SizeLimits{};
        HWND m_Hwnd{ nullptr };
        WindowType m_Type{ WindowType::Game };
        WindowMode m_Mode{ WindowMode::Windowed };
        float m_DpiScale{ 1.0f };

    public:
        virtual ~NativeWindow() noexcept
        {
            GX_ASSERT(this->m_Hwnd == nullptr);
        }

        void Create(WindowType type) noexcept
        {
            this->m_Type = type;
            this->m_Mode = WindowMode::Windowed;

            this->m_Hwnd = CreateWindowExW(
                GetExStyle(this->m_Type, this->m_Mode),
                L"GraphyteWindow",
                L"Graphyte Window",
                GetStyle(this->m_Type, this->m_Mode),
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                nullptr,
                nullptr,
                System::Impl::GInstanceHandle,
                reinterpret_cast<LPVOID>(this));

            ShowWindow(this->m_Hwnd, SW_SHOWNORMAL);
        }

        void Destroy() noexcept
        {
            if (::DestroyWindow(this->m_Hwnd) == FALSE)
            {
                GX_ABORT("Failed to destroy window");
            }

            this->m_Hwnd = nullptr;
        }

        virtual bool Focus() noexcept override
        {
            if (GetFocus() != this->m_Hwnd)
            {
                SetFocus(this->m_Hwnd);

                return true;
            }

            return false;
        }

        virtual bool BringToFront(bool force) noexcept override
        {
            if (this->m_Mode == WindowMode::Windowed && this->m_Type != WindowType::Viewport)
            {
                // Only windowed, non-child windows can be brought to front

                if (IsIconic(this->m_Hwnd))
                {
                    // Restore minimized window.
                    ShowWindow(this->m_Hwnd, SW_RESTORE);
                }
                else
                {
                    // Activate non-minimized window
                    SetActiveWindow(this->m_Hwnd);
                }

                if (force)
                {
                    BringWindowToTop(this->m_Hwnd);
                }
                else
                {
                    ShowWindow(this->m_Hwnd, SW_SHOW);
                }

                return true;
            }

            return false;
        }

        virtual bool Show() noexcept override
        {
            return ShowWindow(this->m_Hwnd, SW_SHOW) != FALSE;
        }

        virtual bool Hide() noexcept override
        {
            return ShowWindow(this->m_Hwnd, SW_HIDE) != FALSE;
        }

        virtual bool Enable() noexcept override
        {
            return EnableWindow(this->m_Hwnd, TRUE) != FALSE;
        }

        virtual bool Disable() noexcept override
        {
            return EnableWindow(this->m_Hwnd, FALSE) != FALSE;
        }

        virtual bool Minimize() noexcept override
        {
            if (this->m_Mode == WindowMode::Windowed)
            {
                return ShowWindow(this->m_Hwnd, SW_MINIMIZE) != FALSE;
            }

            return false;
        }

        virtual bool Maximize() noexcept override
        {
            if (this->m_Type == WindowType::Form)
            {
                // Only form window can be maximized
                return ShowWindow(this->m_Hwnd, SW_MAXIMIZE) != FALSE;
            }

            return false;
        }

        virtual bool Restore() noexcept override
        {
            if (this->m_Type == WindowType::Form)
            {
                // Only form window can be restored
                return ShowWindow(this->m_Hwnd, SW_RESTORE) != FALSE;
            }

            return false;
        }

        virtual bool IsMinimized() const noexcept override
        {
            return IsIconic(this->m_Hwnd) != FALSE;
        }

        virtual bool IsMaximized() const noexcept override
        {
            return IsZoomed(this->m_Hwnd) != FALSE;
        }

        virtual bool IsFocused() const noexcept override
        {
            bool const result = (GetForegroundWindow() == this->m_Hwnd);
            return result;
        }

        virtual bool IsEnabled() const noexcept override
        {
            return IsWindowEnabled(this->m_Hwnd) != FALSE;
        }

        virtual bool IsVisible() const noexcept override
        {
            return IsWindowVisible(this->m_Hwnd) != FALSE;
        }

        virtual bool SetMode(WindowMode value) noexcept override
        {
            if (this->m_Mode != value && this->m_Type == WindowType::Game)
            {
                DWORD const dwStyle   = GetStyle(this->m_Type, value);
                DWORD const dwExStyle = GetExStyle(this->m_Type, value);

                if (this->m_Mode == WindowMode::Windowed)
                {
                    // Store window placement for going back to windowed mode.
                    this->m_PreFullscreenPlacement.length = sizeof(WINDOWPLACEMENT);
                    GetWindowPlacement(this->m_Hwnd, &this->m_PreFullscreenPlacement);
                }

                // Set new styles
                SetWindowLongW(this->m_Hwnd, GWL_STYLE, static_cast<LONG>(dwStyle));
                SetWindowLongW(this->m_Hwnd, GWL_EXSTYLE, static_cast<LONG>(dwExStyle));

                // Update parts of window
                SetWindowPos(this->m_Hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                // Restore window state
                ShowWindow(this->m_Hwnd, SW_RESTORE);

                if (value == WindowMode::Fullscreen || value == WindowMode::WindowedFullscreen)
                {
                    // Get hint of which device we are adjusting
                    bool const exclusive = (value == WindowMode::Fullscreen);

                    HMONITOR hMonitor = MonitorFromWindow(
                        this->m_Hwnd,
                        exclusive ? MONITOR_DEFAULTTOPRIMARY : MONITOR_DEFAULTTONEAREST);

                    MONITORINFO mi{
                        .cbSize = sizeof(mi),
                    };

                    GetMonitorInfoW(hMonitor, &mi);


                    // Adjust window to match border size
                    RECT rcBorder{};
                    AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

                    SetWindowPos(
                        this->m_Hwnd,
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

                    if (this->m_PreFullscreenPlacement.length != 0)
                    {
                        // Restore placement from before window went fullscreen.
                        SetWindowPlacement(this->m_Hwnd, &this->m_PreFullscreenPlacement);
                    }
                }

                this->m_Mode = value;

                return true;
            }
            else
            {
                GX_LOG_WARN(LogNativeApp, "Cannot change mode of non-game window\n");
            }

            return false;
        }

        virtual WindowMode GetMode() const noexcept override
        {
            return this->m_Mode;
        }

        virtual WindowType GetType() const noexcept override
        {
            return this->m_Type;
        }

        virtual void* GetNativeHandle() const noexcept override
        {
            return reinterpret_cast<void*>(this->m_Hwnd);
        }

        virtual System::Size GetClientSize() const noexcept override
        {
            RECT rcClient{};
            GetClientRect(this->m_Hwnd, &rcClient);

            return System::Size{
                .Width  = (rcClient.right - rcClient.left),
                .Height = (rcClient.bottom - rcClient.top),
            };
        }

        virtual bool GetFullscreenPlacement(System::Rect& out_value) noexcept override
        {
            // For exclusive fullscreen, get default primary monitor desktop rectangle.
            // This works for all rendering APIs, as we rely on system defaults.
            //
            // Windowed / FullscreenWindowed is specific for current monitor on window is being
            // displayed.

            bool const exclusive = (this->m_Mode == WindowMode::Fullscreen);

            HMONITOR hMonitor = MonitorFromWindow(
                this->m_Hwnd,
                exclusive ? MONITOR_DEFAULTTOPRIMARY : MONITOR_DEFAULTTONEAREST);

            MONITORINFO mi{ .cbSize = sizeof(mi) };

            if (GetMonitorInfoW(hMonitor, &mi) != FALSE)
            {
                out_value = System::Rect{
                    .Left   = mi.rcMonitor.left,
                    .Top    = mi.rcMonitor.top,
                    .Width  = mi.rcMonitor.right - mi.rcMonitor.left,
                    .Height = mi.rcMonitor.bottom - mi.rcMonitor.top,
                };

                return true;
            }

            return false;
        }

        virtual bool SetCaption(std::string_view value) noexcept override
        {
            std::wstring wtitle = System::Impl::WidenString(value);

            return SetWindowTextW(this->m_Hwnd, wtitle.c_str()) != FALSE;
        }

        virtual bool GetPlacement(System::Rect& out_value) noexcept override
        {
            (void)out_value;
            return false;
        }

        virtual bool SetPlacement(System::Rect value) noexcept override
        {
            if (this->m_Mode == WindowMode::Windowed)
            {
                // Only windowed window can be placed anywhere.
                // Fullscreen window is associated with monitor.

                WINDOWINFO wi{ .cbSize = sizeof(wi) };

                GetWindowInfo(this->m_Hwnd, &wi);

                RECT rcBorder{};
                AdjustWindowRectEx(&rcBorder, wi.dwStyle, FALSE, wi.dwExStyle);

                value.Left += rcBorder.left;
                value.Top += rcBorder.top;
                value.Width += (rcBorder.right - rcBorder.left);
                value.Height += (rcBorder.bottom - rcBorder.top);

                if (this->IsMaximized())
                {
                    this->Restore();
                }

                SetWindowPos(
                    this->m_Hwnd,
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

        virtual bool SetLocation(System::Point value) noexcept override
        {
            if (this->m_Mode == WindowMode::Windowed)
            {
                DWORD dwStyle   = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_STYLE));
                DWORD dwExStyle = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_EXSTYLE));

                RECT rcBorder{};
                AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

                value.Left += rcBorder.left;
                value.Top += rcBorder.top;

                SetWindowPos(
                    this->m_Hwnd,
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

        virtual bool SetSize(System::Size value) noexcept override
        {
            if (this->m_Mode == WindowMode::Windowed)
            {
                DWORD dwStyle   = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_STYLE));
                DWORD dwExStyle = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_EXSTYLE));

                RECT rcBorder{};
                AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwExStyle);

                value.Width += (rcBorder.right - rcBorder.left);
                value.Height += (rcBorder.bottom - rcBorder.top);

                SetWindowPos(
                    this->m_Hwnd,
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

        virtual float GetDpiScale() const noexcept override
        {
            return this->m_DpiScale;
        }

        virtual void SetDpiScale(float value) noexcept override
        {
            this->m_DpiScale = value;
        }

        virtual void SetSizeLimits(WindowSizeLimits const& limits) noexcept override
        {
            if (this->m_Type == WindowType::Form)
            {
                this->m_SizeLimits = limits;

                // Let DWM to adjust current size to new limits.
                SetWindowPos(
                    this->m_Hwnd,
                    nullptr,
                    0, 0, 0, 0,
                    SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
            }
        }

        virtual WindowSizeLimits const& GetSizeLimits() const noexcept override
        {
            return this->m_SizeLimits;
        }

        HWND GetHandle() const noexcept
        {
            return this->m_Hwnd;
        }
    };
}
