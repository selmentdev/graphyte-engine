#pragma once
#include <GxBase/Application.hxx>

namespace Graphyte::Application::Impl
{
    class WindowsWindow : public Window
    {
    private:
        WINDOWPLACEMENT m_PreFullscreenPlacement;
        WINDOWPLACEMENT m_PreParentMinimizedPlacement;

        HWND m_Handle;
        WindowMode m_WindowMode;
        int32_t m_ClientWidth;
        int32_t m_ClientHeight;
        bool m_IsVisible;
        bool m_IsFirstTimeVisible;
        bool m_IsInitMinimized;
        bool m_IsInitMaximized;

    public:
        static const wchar_t* WindowsClassName;

    public:
        WindowsWindow() noexcept;
        virtual ~WindowsWindow() noexcept;

    public:
        void Create(const WindowDescriptor& descriptor) noexcept override;
        void Destroy() noexcept override;

    public:
        void Move(System::Point location) noexcept override;
        void Resize(System::Size size) noexcept override;
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
        void SetPlacement(System::Rect placement) noexcept override;
        //void GetPlacement(System::Rect& placement) noexcept override;
        bool IsMaximized() noexcept override;
        bool IsMinimized() noexcept override;
        bool IsVisible() noexcept override;
        bool IsEnabled() noexcept override;
        bool IsFocused() noexcept override;
        void* GetNativeHandle() noexcept override;
        int32_t GetBorderSize() noexcept override;
        bool GetRestoredPlacement(System::Rect& placement) noexcept override;
        bool GetFullscreenInfo(System::Rect& screen_rect) noexcept override;
        System::Size GetViewportSize() noexcept override;
        bool IsPointInside(System::Point value) noexcept override;
        void OnParentWindowMinimized() noexcept override;
        void OnParentWindowRestored() noexcept override;

        HWND GetHwnd() const noexcept
        {
            return m_Handle;
        }
    };
}
