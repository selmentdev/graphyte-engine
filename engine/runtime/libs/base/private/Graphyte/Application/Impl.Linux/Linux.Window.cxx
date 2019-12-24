#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>

#include "Linux.Window.hxx"

namespace Graphyte::Application::Impl
{
    LinuxWindow::LinuxWindow() noexcept
        : m_Handle{ nullptr }
        , m_ClientWidth{ 1280 }
        , m_ClientHeight{ 720 }
        , m_WindowMode{ WindowMode::Windowed }
        , m_IsVisible{ true }
        , m_WasFullscreen{ false }
    {
    }

    LinuxWindow::~LinuxWindow() noexcept
    {
        GX_ASSERTF(m_Handle == nullptr, "Application::DestroyWindow was not called on this instance!");
        
    }

    void LinuxWindow::Create(
        const WindowDescriptor& descriptor
    ) noexcept
    {
        m_Descriptor = descriptor;

        uint32_t flags = SDL_WINDOW_OPENGL;

        switch (descriptor.Type)
        {
        case WindowType::GameWindow:
            {
                //flags |= SDL_WINDOW_BORDERLESS;
                break;
            }
        case WindowType::Menu:
            {
                flags |= SDL_WINDOW_POPUP_MENU;
                break;
            }
        case WindowType::Normal:
            {
                flags |= SDL_WINDOW_RESIZABLE;
                break;
            }
        case WindowType::Notification:
            {
                flags |= SDL_WINDOW_POPUP_MENU;
                break;
            }
        case WindowType::Tooltip:
            {
                flags |= SDL_WINDOW_TOOLTIP;
                break;
            }
        }

        if (descriptor.Topmost)
        {
            flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        }

        if (!descriptor.Taskbar)
        {
            flags |= SDL_WINDOW_SKIP_TASKBAR;
        }

        int32_t client_x = m_Descriptor.Position.Left;
        int32_t client_y = m_Descriptor.Position.Top;
        int32_t client_w = m_Descriptor.Size.Width;
        int32_t client_h = m_Descriptor.Size.Height;

        m_Handle = SDL_CreateWindow(
            "Graphyte Engine",
            client_x,
            client_y,
            client_w,
            client_h,
            flags
        );

        m_ClientWidth = client_w;
        m_ClientHeight = client_h;

        SetPlacement({
            client_x,
            client_y,
            client_w,
            client_h
        });

        GX_ASSERTF(m_Handle != nullptr, "Failed to create window: `{}`", SDL_GetError());
    }

    void LinuxWindow::Destroy() noexcept
    {
        SDL_DestroyWindow(m_Handle);
        m_Handle = nullptr;
    }

    void LinuxWindow::Move(
        System::Point location
    ) noexcept
    {
        SDL_SetWindowPosition(
            m_Handle,
            location.Left,
            location.Top
        );
    }

    void LinuxWindow::Resize(
        System::Size size
    ) noexcept
    {
        SDL_SetWindowSize(
            m_Handle,
            size.Width,
            size.Height
        );
    }

    void LinuxWindow::Focus() noexcept
    {
        SDL_SetWindowInputFocus(m_Handle);
    }

    void LinuxWindow::BringToFront(
        bool force
    ) noexcept
    {
        if (force)
        {
            SDL_RaiseWindow(m_Handle);
        }
        else
        {
            SDL_ShowWindow(m_Handle);
        }
    }

    void LinuxWindow::Minimize() noexcept
    {
        SDL_MinimizeWindow(m_Handle);
    }

    void LinuxWindow::Maximize() noexcept
    {
        SDL_MaximizeWindow(m_Handle);
    }

    void LinuxWindow::Restore() noexcept
    {
        SDL_RestoreWindow(m_Handle);
    }

    void LinuxWindow::Show() noexcept
    {
        if (!m_IsVisible)
        {
            SDL_ShowWindow(m_Handle);
            m_IsVisible = true;
        }
    }

    void LinuxWindow::Hide() noexcept
    {
        if (m_IsVisible)
        {
            SDL_HideWindow(m_Handle);
            m_IsVisible = false;
        }
    }

    void LinuxWindow::Enable() noexcept
    {
        ;
    }

    void LinuxWindow::Disable() noexcept
    {
        ;
    }

    void LinuxWindow::SetWindowMode(
        WindowMode value
    ) noexcept
    {
        if (value != m_WindowMode)
        {
            switch (value)
            {
            case WindowMode::Fullscreen:
            case WindowMode::WindowedFullscreen:
                {
                    if (m_WasFullscreen == false)
                    {
                        SDL_SetWindowSize(m_Handle, m_ClientWidth, m_ClientHeight);
                        SDL_SetWindowFullscreen(m_Handle, SDL_WINDOW_FULLSCREEN_DESKTOP);

                        m_WasFullscreen = true;
                    }

                    break;
                }
            case WindowMode::Windowed:
                {
                    auto width = std::max<int>(100, m_ClientWidth - 100);
                    auto height = std::max<int>(100, m_ClientHeight - 100);

                    SDL_SetWindowSize(m_Handle, width, height);
                    SDL_SetWindowFullscreen(m_Handle, 0);
                    SDL_SetWindowBordered(m_Handle, SDL_TRUE);
                    SDL_SetWindowGrab(m_Handle, SDL_FALSE);

                    m_WasFullscreen = false;

                    break;
                }
            }

            m_WindowMode = value;
        }

        //GX_VERIFYF(SDL_SetWindowFullscreen(m_Handle, flags) == 0, "Failed to set window mode: `{}`", SDL_GetError());
    }

    WindowMode LinuxWindow::GetWindowMode() noexcept
    {
        return m_WindowMode;
    }

    void LinuxWindow::SetCaption(
        const char* text
    ) noexcept
    {
        SDL_SetWindowTitle(m_Handle, text);
    }

    void LinuxWindow::SetPlacement(System::Rect placement) noexcept
    {
        switch (GetWindowMode())
        {
        case WindowMode::Fullscreen:
        case WindowMode::WindowedFullscreen:
            {
                SDL_SetWindowFullscreen(m_Handle, 0);
                SDL_SetWindowSize(m_Handle, placement.Width, placement.Height);
                SDL_SetWindowFullscreen(m_Handle, SDL_WINDOW_FULLSCREEN_DESKTOP);

                break;
            }

        case WindowMode::Windowed:
            {
                SDL_SetWindowPosition(m_Handle, placement.Left, placement.Top);
                SDL_SetWindowSize(m_Handle, placement.Width, placement.Height);

                break;
            }
        }

        //SDL_SetWindowPosition(m_Handle, placement.Left, placement.Top);
        //SDL_SetWindowSize(m_Handle, placement.Width, placement.Height);

        m_ClientWidth = placement.Width;
        m_ClientHeight = placement.Height;
    }

    bool LinuxWindow::IsMaximized() noexcept
    {
        uint32_t flags = SDL_GetWindowFlags(m_Handle);
        return (flags & SDL_WINDOW_MAXIMIZED) == SDL_WINDOW_MAXIMIZED;
    }

    bool LinuxWindow::IsMinimized() noexcept
    {
        uint32_t flags = SDL_GetWindowFlags(m_Handle);
        return (flags & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED;
    }

    bool LinuxWindow::IsVisible() noexcept
    {
        uint32_t flags = SDL_GetWindowFlags(m_Handle);
        return (flags & SDL_WINDOW_SHOWN) == SDL_WINDOW_SHOWN;
    }

    bool LinuxWindow::IsEnabled() noexcept
    {
        return true;
    }

    bool LinuxWindow::IsFocused() noexcept
    {
        const uint32_t required_flags
            = SDL_WINDOW_INPUT_GRABBED
            | SDL_WINDOW_INPUT_FOCUS
            | SDL_WINDOW_MOUSE_FOCUS;

        uint32_t flags = SDL_GetWindowFlags(m_Handle);

        return (flags & required_flags) == required_flags;
    }

    void* LinuxWindow::GetNativeHandle() noexcept
    {
        return reinterpret_cast<void*>(m_Handle);
    }

    int32_t LinuxWindow::GetBorderSize() noexcept
    {
        return 0;
    }

    bool LinuxWindow::GetRestoredPlacement(
        System::Rect& placement
    ) noexcept
    {
        SDL_GetWindowPosition(m_Handle, &placement.Left, &placement.Top);
        SDL_GetWindowSize(m_Handle, &placement.Width, &placement.Height);

        return true;
    }

    bool LinuxWindow::GetFullscreenInfo(
        System::Rect& placement
    ) noexcept
    {
        SDL_Rect rc{};

        auto display = SDL_GetWindowDisplayIndex(m_Handle);

        if (display >= 0 && SDL_GetDisplayBounds(display, &rc) == 0)
        {
            placement.Left = rc.x;
            placement.Top = rc.y;
            placement.Width = rc.w;
            placement.Height = rc.h;

            return true;
        }

        return false;
    }

    System::Size LinuxWindow::GetViewportSize() noexcept
    {
        System::Size result{};

        SDL_GetWindowSize(m_Handle, &result.Width, &result.Height);

        return result;
    }

    void LinuxWindow::OnParentWindowMinimized() noexcept
    {
    }

    void LinuxWindow::OnParentWindowRestored() noexcept
    {
    }

    bool LinuxWindow::IsPointInside(
        System::Point location
    ) noexcept
    {
        SDL_Point point{ location.Left, location.Top };

        SDL_Rect rc_window;
        SDL_GetWindowPosition(m_Handle, &rc_window.x, &rc_window.y);
        SDL_GetWindowSize(m_Handle, &rc_window.w, &rc_window.h);

        return SDL_PointInRect(&point, &rc_window) != SDL_FALSE;
    }
}
