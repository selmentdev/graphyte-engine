#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Version.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Input/Input.hxx>

// =================================================================================================
//
// Common application functionalities.
//

namespace Graphyte::Application
{
    enum struct ApplicationType : uint32_t
    {
        Game,
        UnitTest,
        ConsoleTool,
        DeveloperTool,
    };

    struct ApplicationDescriptor final
    {
        std::string_view Name;
        std::string_view Id;
        std::string_view Company;
        ApplicationType Type;
        Version AppVersion;
    };

    //! \brief Initializes application submodule.
    extern BASE_API void Initialize() noexcept;

    //! \brief Finalizes application submodule.
    extern BASE_API void Finalize() noexcept;

    //! \brief Gets descriptor of current application.
    extern BASE_API const ApplicationDescriptor& GetDescriptor() noexcept;

    //! \brief Gets value indicating whether current application is first instance.
    extern BASE_API bool IsFirstInstance() noexcept;

    //! \brief Gets value indicating whether application requested exit.
    extern BASE_API bool IsRequestingExit() noexcept;

    //! \brief Requests exit from application.
    //!
    //! \param force Provides value indicating whether application should close immediately or just
    //!              continue looping.
    extern BASE_API void RequestExit(
        bool force) noexcept;

    //! \brief Gets value indicating whether current application is in foreground.
    extern BASE_API bool IsForeground() noexcept;

    //! \brief Polls input devices.
    //!
    //! \param deltaTime Provides delta time since last frame.
    extern BASE_API void PollInputDevices(float deltaTime) noexcept;

    //! \brief Pumps messages.
    //!
    //! \param deltaTime Provides delta time since last frame.
    extern BASE_API void PumpMessages(float deltaTime) noexcept;

    //! \brief Ticks application.
    //!
    //! \param deltaTime Provides delta time since last frame.
    extern BASE_API void Tick(float deltaTime) noexcept;
}

namespace Graphyte::Application::Impl
{
    extern BASE_API ApplicationDescriptor GApplicationDescriptor;
    extern BASE_API bool GIsFirstInstance;
}


// =================================================================================================
//
// Common application types.
//

namespace Graphyte::Application
{
    enum struct ShutdownReason
    {
        LogOff,
        Critical,
        CloseApplication,
    };

    enum struct WindowType
    {
        Normal,
        GameWindow,
        Menu,
        Tooltip,
        Notification,
    };

    enum struct WindowMode
    {
        Fullscreen,
        WindowedFullscreen,
        Windowed,
    };

    enum struct WindowActivation
    {
        Activate,
        MouseActivate,
        Deactivate,
    };

    enum struct WindowAction
    {
        NonClientClick,
        Maximize,
        Minimize,
        Restore,
        WindowMenu,
    };

    enum struct DropEffect
    {
        None,
        Copy,
        Move,
        Link,
    };

    enum struct WindowActivationPolicy
    {
        Never,
        Always,
        FirstShown,
    };

    struct WindowLimits final
    {
        std::optional<int32_t> MinWidth;
        std::optional<int32_t> MinHeight;
        std::optional<int32_t> MaxWidth;
        std::optional<int32_t> MaxHeight;
    };

    struct WindowDescriptor
    {
        WindowLimits SizeLimits;
        std::string Title;
        System::Point Position;
        System::Size Size;
        System::Size ExpectedMaxSize;
        WindowType Type;
        WindowActivationPolicy ActivationPolicy;
        bool SystemBorder : 1;
        bool Taskbar : 1;
        bool Topmost : 1;
        bool AcceptInput : 1;
        bool CloseButton : 1;
        bool MinimizeButton : 1;
        bool MaximizeButton : 1;
        bool Modal : 1;
        bool Resizable : 1;
        bool Regular : 1;
        bool PreserveAspectRatio : 1;
        bool DelayResize : 1;
    };
}


// =================================================================================================
//
// Window base class.
//

namespace Graphyte::Application
{
    class BASE_API Window
    {
    protected:
        WindowDescriptor m_Descriptor{};
        float m_AspectRatio{};
        float m_DPIScale{};

    public:
        Window() noexcept = default;

        virtual ~Window() noexcept = default;

        Window(const Window&) = delete;

        Window& operator=(const Window&) = delete;

    public:
        virtual void Create(
            const WindowDescriptor& descriptor) noexcept = 0;

        virtual void Destroy() noexcept = 0;

    public:
        virtual void Move(
            System::Point location) noexcept = 0;

        virtual void Resize(
            System::Size size) noexcept = 0;

        virtual void Focus() noexcept = 0;

        virtual void BringToFront(
            bool force) noexcept = 0;

        virtual void Minimize() noexcept = 0;

        virtual void Maximize() noexcept = 0;

        virtual void Restore() noexcept = 0;

        virtual void Show() noexcept = 0;

        virtual void Hide() noexcept = 0;

        virtual void Enable() noexcept = 0;

        virtual void Disable() noexcept = 0;

        virtual void SetWindowMode(
            WindowMode value) noexcept = 0;

        virtual WindowMode GetWindowMode() noexcept = 0;

        virtual void SetCaption(
            const char* text) noexcept = 0;

        virtual void SetPlacement(
            System::Rect placement) noexcept = 0;

        //virtual void GetPlacement(System::Rect& placement) noexcept = 0;

        virtual bool IsMaximized() noexcept = 0;

        virtual bool IsMinimized() noexcept = 0;

        virtual bool IsVisible() noexcept = 0;

        virtual bool IsEnabled() noexcept = 0;

        virtual bool IsFocused() noexcept = 0;

        virtual void* GetNativeHandle() noexcept = 0;

        virtual int32_t GetBorderSize() noexcept = 0;

        virtual bool GetRestoredPlacement(
            System::Rect& placement) noexcept = 0;

        virtual bool GetFullscreenInfo(
            System::Rect& screen_rect) noexcept = 0;

        virtual System::Size GetViewportSize() noexcept = 0;

        virtual bool IsPointInside(
            System::Point value) noexcept = 0;

        virtual void OnParentWindowMinimized() noexcept = 0;

        virtual void OnParentWindowRestored() noexcept = 0;

    public:
        const WindowDescriptor& GetDescriptor() const noexcept
        {
            return m_Descriptor;
        }

        float GetAspectRatio() const noexcept
        {
            return m_AspectRatio;
        }

        float GetDPIScale() const noexcept
        {
            return m_DPIScale;
        }

        void SetDPIScale(
            float value) noexcept
        {
            m_DPIScale = value;
        }
    };

    //! \brief Creates new instance of window.
    //!
    //! \param descriptor Provides window descriptor.
    //!
    //! \return The instance of new window.
    extern BASE_API Window* CreateWindow(
        const WindowDescriptor& descriptor) noexcept;

    //! \brief Destroys instance of window.
    //!
    //! \param window Provides instance of window to destroy.
    extern BASE_API void DestroyWindow(
        Window* window) noexcept;
}


// =================================================================================================
//
// Application event handler.
//

namespace Graphyte::Application
{
    class BASE_API EventHandler
    {
    public:
        virtual ~EventHandler() noexcept;

    public:
        virtual bool CanHandleInput(
            Window& window) noexcept;

        virtual bool OnKeyChar(
            char32_t character,
            bool repeat) noexcept;

        virtual bool OnKeyDown(
            Input::KeyCode key,
            char32_t character,
            bool repeat) noexcept;

        virtual bool OnKeyUp(
            Input::KeyCode key,
            char32_t character,
            bool repeat) noexcept;

        virtual bool OnMouseDown(
            Window& window,
            Input::MouseButton button,
            Float2 position) noexcept;

        virtual bool OnMouseUp(
            Window& window,
            Input::MouseButton button,
            Float2 position) noexcept;

        virtual bool OnMouseDoubleClick(
            Window& window,
            Input::MouseButton button,
            Float2 position) noexcept;

        virtual bool OnMouseWheel(
            float delta,
            Float2 position) noexcept;

        virtual bool OnMouseMove() noexcept;

        virtual bool OnMouseMove(
            Float2 position) noexcept;

        virtual bool OnControllerAnalog(
            Input::GamepadKey key,
            uint32_t controller,
            float value) noexcept;

        virtual bool OnControllerButtonPressed(
            Input::GamepadKey key,
            uint32_t controller,
            bool repeat) noexcept;

        virtual bool OnControllerButtonReleased(
            Input::GamepadKey key,
            uint32_t controller,
            bool repeat) noexcept;

        virtual void OnGestureStart() noexcept;

        virtual bool OnGestureTouch(
            Input::GestureType gesture,
            Float2 delta,
            float wheel_delta,
            bool inverted) noexcept;

        virtual void OnGestureEnd() noexcept;

        virtual bool OnTouchStarted(
            Window& window,
            Float2 position,
            Input::TouchIndex touch_index,
            uint32_t controller) noexcept;

        virtual bool OnTouchMoved(
            Float2 location,
            Input::TouchIndex touch_index,
            uint32_t controller) noexcept;

        virtual bool OnTouchEnded(
            Float2 location,
            Input::TouchIndex touch_index,
            uint32_t controller) noexcept;

        virtual bool OnMotion(
            Float3 tilt,
            Float3 rotation_rate,
            Float3 gravity,
            Float3 acceleration,
            uint32_t controller) noexcept;

    public:
        virtual bool OnWindowSizeChanged(
            Window& window,
            Float2 size,
            bool was_minimized) noexcept;

        virtual void OnWindowPaint(
            Window& window) noexcept;

        virtual WindowLimits GetSizeLimits(
            Window& window) noexcept;

        virtual void OnWindowSizing(
            Window& window) noexcept;

        virtual bool OnWindowSizingBegin(
            Window& window) noexcept;

        virtual void OnWindowSizingEnd(
            Window& window) noexcept;

        virtual void OnDPIScaleChanged(
            Window& window) noexcept;

        virtual void OnWindowMoved(
            Window& window,
            Float2 position) noexcept;

        virtual void OnWindowClose(
            Window& window) noexcept;

        virtual bool OnWindowActivated(
            Window& window,
            WindowActivation activation) noexcept;

        virtual bool OnApplicationActivated(
            bool active) noexcept;

        virtual bool OnWindowAction(
            Window& window,
            WindowAction action) noexcept;

        virtual void OnPowerSuspend() noexcept;

        virtual void OnPowerResume() noexcept;

        virtual void OnApplicationShutdown(
            ShutdownReason reason) noexcept;
    };

    //! \brief Sets current application event handler.
    //!
    //! \param handler Provides new event handler
    extern BASE_API void SetEventHandler(
        EventHandler* handler) noexcept;

    //! \brief Gets current application event handler.
    //!
    //! \return The current application event handler.
    extern BASE_API EventHandler* GetEventHandler() noexcept;
}
