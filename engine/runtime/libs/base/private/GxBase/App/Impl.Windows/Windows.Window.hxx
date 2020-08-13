#pragma once
#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>
#include <GxBase/App.hxx>

#include <dwmapi.h>

namespace Graphyte::App::Impl
{
    class WindowsWindow final : public Window
    {
    private:
        WINDOWPLACEMENT m_PreFullscreenPlacement{};
        HWND m_Hwnd{};
        float m_AspectRatio{ 1.0f };
        int32_t m_ClientWidth{};
        int32_t m_ClientHeight{};
        bool m_IsVisible{ false };
        bool m_IsInitMinimized{ false };
        bool m_isInitMaximized{ false };
        bool m_IsFirstTimeVisible{ false };

    public:
        WindowsWindow() noexcept = default;

        virtual ~WindowsWindow() noexcept
        {
            GX_ASSERT(this->m_Hwnd == nullptr);
        }

        void Create(WindowDescriptor const& descriptor) noexcept
        {
            this->m_Descriptor = descriptor;

            std::wstring wtitle = System::Impl::WidenString(descriptor.Title);

            DWORD dwStyle{};
            DWORD dwStyleEx{};

            System::Rect rcClient{
                .Left   = descriptor.Position.Left,
                .Top    = descriptor.Position.Top,
                .Width  = descriptor.Size.Width,
                .Height = descriptor.Size.Height,
            };

            System::Rect rcWindow = rcClient;

            if (descriptor.SystemBorder)
            {
                dwStyle   = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
                dwStyleEx = WS_EX_APPWINDOW;

                if (descriptor.Regular)
                {
                    if (descriptor.MaximizeButton)
                    {
                        dwStyle |= WS_MAXIMIZEBOX;
                    }

                    if (descriptor.MinimizeButton)
                    {
                        dwStyle |= WS_MINIMIZEBOX;
                    }

                    if (descriptor.Resizable)
                    {
                        dwStyle |= WS_THICKFRAME;
                    }
                    else
                    {
                        dwStyle |= WS_BORDER;
                    }
                }
                else
                {
                    dwStyle |= WS_POPUP | WS_BORDER;
                }

                RECT rcBorder{};
                AdjustWindowRectEx(&rcBorder, dwStyle, FALSE, dwStyleEx);

                rcWindow.Left += rcBorder.left;
                rcWindow.Top += rcBorder.top;

                rcWindow.Width += (rcBorder.right - rcBorder.left);
                rcWindow.Height += (rcBorder.bottom - rcBorder.top);
            }
            else
            {
                dwStyleEx = WS_EX_WINDOWEDGE;
                dwStyle   = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

                if (descriptor.Taskbar)
                {
                    dwStyleEx |= WS_EX_APPWINDOW;
                }
                else
                {
                    dwStyleEx |= WS_EX_TOOLWINDOW;
                }

                if (descriptor.Topmost)
                {
                    dwStyleEx |= WS_EX_TOPMOST;
                }

                if (!descriptor.AcceptInput)
                {
                    dwStyleEx |= WS_EX_TRANSPARENT;
                }
            }


            m_Hwnd = CreateWindowExW(
                dwStyleEx,
                L"GraphyteWindow",
                wtitle.c_str(),
                dwStyle,
                rcWindow.Left,
                rcWindow.Top,
                rcWindow.Width,
                rcWindow.Height,
                nullptr,
                nullptr,
                System::Impl::GInstanceHandle,
                reinterpret_cast<LPVOID>(this));

            GX_ASSERTF(this->m_Hwnd != nullptr, "Cannot create window: {}", GetLastError());

            SetPlacement(rcClient);

            if (!descriptor.SystemBorder)
            {
                DWMNCRENDERINGPOLICY const dwmRenderingPolicy = DWMNCRP_DISABLED;

                if (FAILED(DwmSetWindowAttribute(this->m_Hwnd, DWMWA_NCRENDERING_POLICY, &dwmRenderingPolicy, sizeof(dwmRenderingPolicy))))
                {
                    GX_ABORT("Failed to set DWM window rendering policy");
                }

                BOOL const dwmAllowNcPaint{ FALSE };

                if (FAILED(DwmSetWindowAttribute(this->m_Hwnd, DWMWA_ALLOW_NCPAINT, &dwmAllowNcPaint, sizeof(dwmAllowNcPaint))))
                {
                    GX_ABORT("Failed to set DWM window NC paint");
                }

                MARGINS margins{
                    -1,
                    -1,
                    -1,
                    -1,
                };
                if (FAILED(DwmExtendFrameIntoClientArea(this->m_Hwnd, &margins)))
                {
                    GX_ABORT("Failed to extend DWM frame into client area");
                }
            }

            if (descriptor.Regular && !descriptor.SystemBorder)
            {
                dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

                if (descriptor.MaximizeButton)
                {
                    dwStyle |= WS_MAXIMIZEBOX;
                }

                if (descriptor.MinimizeButton)
                {
                    dwStyle |= WS_MINIMIZEBOX;
                }

                if (descriptor.Resizable)
                {
                    dwStyle |= WS_THICKFRAME;
                }

                if (SetWindowLongW(this->m_Hwnd, GWL_STYLE, static_cast<LONG>(dwStyle)) == 0)
                {
                    GX_ABORT("Cannot set window style");
                }

                UINT swpFlags = SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED;

                SetWindowPos(this->m_Hwnd, nullptr, 0, 0, 0, 0, swpFlags);
            }
            else if (descriptor.SystemBorder)
            {
                if (!descriptor.CloseButton)
                {
                    EnableMenuItem(GetSystemMenu(this->m_Hwnd, FALSE), SC_CLOSE, MF_GRAYED);
                }
            }
        }

        void Destroy() noexcept
        {
            if (DestroyWindow(this->m_Hwnd) == FALSE)
            {
                GX_ABORT("Failed to destroy window");
            }

            this->m_Hwnd = nullptr;
        }

    public:
        virtual void Move(System::Point location) noexcept override
        {
            if (this->m_Descriptor.SystemBorder)
            {
                // Adjust window position to match location with client window area
                DWORD dwStyle   = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_STYLE));
                DWORD dwStyleEx = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_EXSTYLE));

                RECT rc{};

                AdjustWindowRectEx(&rc, dwStyle, FALSE, dwStyleEx);

                location.Left += rc.left;
                location.Top += rc.top;
            }

            SetWindowPos(this->m_Hwnd, nullptr, location.Left, location.Top, 0, 0,
                SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
        }

        virtual void Resize(System::Size size) noexcept override
        {
            (void)size;
        }

        virtual void Focus() noexcept override
        {
            if (GetFocus() != this->m_Hwnd)
            {
                SetFocus(this->m_Hwnd);
            }
        }

        virtual void BringToFront(bool force) noexcept override
        {
            if (this->m_Descriptor.Regular)
            {
                if (IsIconic(this->m_Hwnd))
                {
                    ShowWindow(this->m_Hwnd, SW_RESTORE);
                }
                else
                {
                    SetActiveWindow(this->m_Hwnd);
                }
            }
            else
            {
                HWND hInsertAfter = HWND_TOP;
                UINT flags        = SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER;

                if (!force)
                {
                    flags |= SWP_NOACTIVATE;
                }

                if (this->m_Descriptor.Topmost)
                {
                    hInsertAfter = HWND_TOPMOST;
                }

                SetWindowPos(this->m_Hwnd, hInsertAfter, 0, 0, 0, 0, flags);
            }

            if (force)
            {
                BringWindowToTop(this->m_Hwnd);
            }
            else
            {
                ShowWindow(this->m_Hwnd, SW_SHOW);
            }
        }

        virtual void Minimize() noexcept override
        {
            if (!this->m_IsFirstTimeVisible)
            {
                ShowWindow(this->m_Hwnd, SW_MINIMIZE);
            }
            else
            {
                this->m_IsInitMinimized = true;
                this->m_isInitMaximized = false;
            }
        }

        virtual void Maximize() noexcept override
        {
            if (!this->m_IsFirstTimeVisible)
            {
                ShowWindow(this->m_Hwnd, SW_MAXIMIZE);
            }
            else
            {
                this->m_IsInitMinimized = false;
                this->m_isInitMaximized = true;
            }
        }

        virtual void Restore() noexcept override
        {
            if (!this->m_IsFirstTimeVisible)
            {
                ShowWindow(this->m_Hwnd, SW_RESTORE);
            }
            else
            {
                this->m_IsInitMinimized = false;
                this->m_isInitMaximized = false;
            }
        }

        virtual void Show() noexcept override
        {
            if (!this->m_IsVisible)
            {
                this->m_IsVisible = true;

                int showCommand = SW_SHOW;

                if (this->m_IsFirstTimeVisible)
                {
                    this->m_IsFirstTimeVisible = false;

                    if (this->m_IsInitMinimized)
                    {
                        showCommand = SW_MINIMIZE;
                    }
                    else
                    {
                        showCommand = SW_SHOWMAXIMIZED;
                    }
                }

                ShowWindow(this->m_Hwnd, showCommand);
            }
        }

        virtual void Hide() noexcept override
        {
            if (this->m_IsVisible)
            {
                this->m_IsVisible = false;
                ShowWindow(this->m_Hwnd, SW_HIDE);
            }
        }

        virtual void Enable() noexcept override
        {
            EnableWindow(this->m_Hwnd, TRUE);
        }

        virtual void Disable() noexcept override
        {
            EnableWindow(this->m_Hwnd, FALSE);
        }

        virtual void SetWindowMode(WindowMode value) noexcept override
        {
            WindowMode const previousMode = this->m_Descriptor.Mode;

            if (previousMode != value)
            {
                this->m_Descriptor.Mode = value;

                bool const exclusiveFullscreen = (value == WindowMode::Fullscreen);

                DWORD dwStyle                 = static_cast<DWORD>(GetWindowLongW(this->m_Hwnd, GWL_STYLE));
                DWORD const dwFullscreenStyle = WS_POPUP;
                DWORD dwWindowedStyle         = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;

                if (this->m_Descriptor.Regular)
                {
                    if (this->m_Descriptor.MinimizeButton)
                    {
                        dwWindowedStyle |= WS_MINIMIZEBOX;
                    }

                    if (this->m_Descriptor.MaximizeButton)
                    {
                        dwWindowedStyle |= WS_MAXIMIZEBOX;
                    }

                    if (this->m_Descriptor.Resizable)
                    {
                        dwWindowedStyle |= WS_THICKFRAME;
                    }
                    else
                    {
                        dwWindowedStyle |= WS_BORDER;
                    }
                }
                else
                {
                    dwWindowedStyle |= WS_POPUP | WS_BORDER;
                }

                if (value == WindowMode::Fullscreen || value == WindowMode::WindowedFullscreen)
                {
                    if (previousMode == WindowMode::Windowed)
                    {
                        this->m_PreFullscreenPlacement.length = sizeof(WINDOWPLACEMENT);
                        GetWindowPlacement(this->m_Hwnd, &m_PreFullscreenPlacement);
                    }

                    dwStyle &= ~dwWindowedStyle;
                    dwStyle |= dwFullscreenStyle;

                    SetWindowLongW(this->m_Hwnd, GWL_STYLE, static_cast<LONG>(dwStyle));

                    SetWindowPos(this->m_Hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                    if (!exclusiveFullscreen)
                    {
                        ShowWindow(this->m_Hwnd, SW_RESTORE);
                    }

                    RECT rcClient{};

                    GetClientRect(this->m_Hwnd, &rcClient);

                    DWORD targetMonitor = static_cast<DWORD>(exclusiveFullscreen
                                                                 ? MONITOR_DEFAULTTOPRIMARY
                                                                 : MONITOR_DEFAULTTONEAREST);

                    HMONITOR hMonitor = MonitorFromWindow(this->m_Hwnd, targetMonitor);

                    MONITORINFO mi{
                        .cbSize = sizeof(mi),
                    };

                    GetMonitorInfoW(hMonitor, &mi);

                    LONG const monitorWidth  = (mi.rcMonitor.right - mi.rcMonitor.left);
                    LONG const monitorHeight = (mi.rcMonitor.bottom - mi.rcMonitor.top);

                    LONG const targetWidth = exclusiveFullscreen
                                                 ? std::min(monitorWidth, rcClient.right - rcClient.left)
                                                 : monitorWidth;

                    LONG const targetHeight = exclusiveFullscreen
                                                  ? std::min(monitorHeight, rcClient.bottom - rcClient.top)
                                                  : monitorHeight;

                    SetPlacement(
                        System::Rect{
                            .Left   = mi.rcMonitor.left,
                            .Top    = mi.rcMonitor.top,
                            .Width  = targetWidth,
                            .Height = targetHeight,
                        });
                }
                else
                {
                    dwStyle &= ~dwFullscreenStyle;
                    dwStyle |= dwWindowedStyle;

                    SetWindowLongW(this->m_Hwnd, GWL_STYLE, static_cast<LONG>(dwStyle));

                    SetWindowPos(this->m_Hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

                    if (this->m_PreFullscreenPlacement.length != 0)
                    {
                        SetWindowPlacement(this->m_Hwnd, &this->m_PreFullscreenPlacement);
                    }
                }
            }
        }

        virtual void SetCaption(std::string_view caption) noexcept override
        {
            std::wstring wcaption = System::Impl::WidenString(caption);
            SetWindowTextW(this->m_Hwnd, wcaption.c_str());
        }

        virtual void SetPlacement(System::Rect placement) noexcept override
        {
            WINDOWINFO wi{
                .cbSize = sizeof(wi),
            };

            GetWindowInfo(this->m_Hwnd, &wi);

            this->m_AspectRatio = static_cast<float>(placement.Width) / static_cast<float>(placement.Height);

            if (this->m_Descriptor.SystemBorder)
            {
                RECT rcBorder{};
                AdjustWindowRectEx(&rcBorder, wi.dwStyle, FALSE, wi.dwExStyle);

                placement.Left += rcBorder.left;
                placement.Top += rcBorder.top;
                placement.Width += rcBorder.right - rcBorder.left;
                placement.Height += rcBorder.bottom - rcBorder.top;
            }

            this->m_ClientWidth  = placement.Width;
            this->m_ClientHeight = placement.Height;

            if (this->IsMaximized())
            {
                this->Restore();
            }

            UINT flags = SWP_NOZORDER | SWP_NOACTIVATE;

            if (this->m_Descriptor.Mode == WindowMode::Fullscreen)
            {
                flags |= SWP_NOSENDCHANGING;
            }

            SetWindowPos(
                this->m_Hwnd,
                nullptr,
                placement.Left,
                placement.Top,
                placement.Width,
                placement.Height,
                flags);
        }

        virtual bool IsMaximized() const noexcept override
        {
            bool const result = !!IsZoomed(this->m_Hwnd);
            return result;
        }

        virtual bool IsMinimized() const noexcept override
        {
            bool const result = !!IsIconic(this->m_Hwnd);
            return result;
        }

        virtual bool IsVisible() const noexcept override
        {
            return this->m_IsVisible;
        }

        virtual bool IsEnabled() const noexcept override
        {
            bool const result = !!IsWindowEnabled(this->m_Hwnd);
            return result;
        }

        virtual bool IsFocused() const noexcept override
        {
            bool const result = (GetForegroundWindow() == this->m_Hwnd);
            return result;
        }

        virtual void* GetNativeHandle() const noexcept override
        {
            return reinterpret_cast<void*>(this->m_Hwnd);
        }

        virtual bool GetFullscreenRect(System::Rect& out_rect) noexcept override
        {
            // For exclusive fullscreen, get default primary monitor desktop rectangle.
            // This works for all rendering APIs, as we rely on system defaults.
            //
            // Windowed / FullscreenWindowed is specific for current monitor on window is being
            // displayed.

            bool const exclusive_fullscreen = (this->m_Descriptor.Mode == WindowMode::Fullscreen);

            DWORD const flags = exclusive_fullscreen
                                    ? MONITOR_DEFAULTTOPRIMARY
                                    : MONITOR_DEFAULTTONEAREST;

            HMONITOR hMonitor = MonitorFromWindow(this->m_Hwnd, flags);

            MONITORINFO mi{
                .cbSize = sizeof(mi),
            };

            GetMonitorInfoW(hMonitor, &mi);

            out_rect.Left   = mi.rcMonitor.left;
            out_rect.Top    = mi.rcMonitor.top;
            out_rect.Width  = mi.rcMonitor.right - mi.rcMonitor.left;
            out_rect.Height = mi.rcMonitor.bottom - mi.rcMonitor.top;

            return true;
        }

        virtual System::Size GetViewportSize() const noexcept override
        {
            RECT rcClient{};

            GetClientRect(this->m_Hwnd, &rcClient);

            return System::Size{
                .Width  = (rcClient.right - rcClient.left),
                .Height = (rcClient.bottom - rcClient.top),
            };
        }

        virtual bool IsPointInside(System::Point value) noexcept override
        {
            RECT rcWindow{};

            GetWindowRect(this->m_Hwnd, &rcWindow);

            bool const result = !!PtInRect(&rcWindow, POINT{ .x = value.Left, .y = value.Top });
            return result;
        }

        HWND GetHandle() const noexcept
        {
            return this->m_Hwnd;
        }
    };
}
