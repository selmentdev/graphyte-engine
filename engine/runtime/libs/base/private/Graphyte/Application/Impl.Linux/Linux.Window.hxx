#pragma once
#include <Graphyte/Application.hxx>

#include <SDL2/SDL.h>

namespace Graphyte::Application::Impl
{
    class BASE_API LinuxWindow : public Window
    {
    private:
        SDL_Window* m_Handle;
        int m_ClientWidth;
        int m_ClientHeight;
        WindowMode m_WindowMode;
        bool m_IsVisible;
        bool m_WasFullscreen;

    public:
        LinuxWindow() noexcept;
        virtual ~LinuxWindow() noexcept;

    public:
        void Create(const WindowDescriptor& descriptor) noexcept override;
        void Destroy() noexcept override;

    public:
        void Move(Platform::Point location) noexcept override;
        void Resize(Platform::Size size) noexcept override;
        void Focus() noexcept override;
        void BringToFront(bool force) noexcept override;
        void Minimize() noexcept override;
        void Maximize() noexcept override;
        void Restore() noexcept override;
        void Show() noexcept override;
        void Hide() noexcept override;
        void Enable() noexcept override;
        void Disable() noexcept override;
        void SetWindowMode(WindowMode value) noexcept override;
        WindowMode GetWindowMode() noexcept override;
        void SetCaption(const char* text) noexcept override;
        void SetPlacement(Platform::Rect placement) noexcept override;
        //void GetPlacement(Platform::Rect& placement) noexcept override;
        bool IsMaximized() noexcept override;
        bool IsMinimized() noexcept override;
        bool IsVisible() noexcept override;
        bool IsEnabled() noexcept override;
        bool IsFocused() noexcept override;
        void* GetNativeHandle() noexcept override;
        int32_t GetBorderSize() noexcept override;
        bool GetRestoredPlacement(Platform::Rect& placement) noexcept override;
        bool GetFullscreenInfo(Platform::Rect& screen_rect) noexcept override;
        Platform::Size GetViewportSize() noexcept override;
        bool IsPointInside(Platform::Point value) noexcept override;
        void OnParentWindowMinimized() noexcept override;
        void OnParentWindowRestored() noexcept override;
    };
}
