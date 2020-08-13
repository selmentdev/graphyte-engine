#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Version.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Types.hxx>

// =================================================================================================
// Application implementation

namespace Graphyte::App
{
    enum class ApplicationType : uint32_t
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
}

namespace Graphyte::App::Impl
{
    extern BASE_API bool g_IsRequestingExit;
    extern BASE_API bool g_IsFirstInstance;
    extern BASE_API ApplicationDescriptor g_ApplicationDescriptor;


    BASE_API void EnableAccessibilityKeys(bool enable) noexcept;
}

namespace Graphyte::App
{
    inline ApplicationDescriptor const& GetDescriptor() noexcept
    {
        return Impl::g_ApplicationDescriptor;
    }

    /// @brief Initialize application.
    BASE_API void Initialize() noexcept;

    /// @brief Finalize application.
    BASE_API void Finalize() noexcept;

    /// @brief Ticks application
    /// @param delta_time Provides delta time since last frame.
    /// @remarks Pumps messages since last tick, handles incoming events, pools input devices.
    BASE_API void Tick(float delta_time) noexcept;

    BASE_API void PollInput(float delta_time) noexcept;

    BASE_API void PumpMessages(float delta_time) noexcept;

    BASE_API bool IsForeground() noexcept;

    inline bool IsRequestingExit() noexcept
    {
        return Impl::g_IsRequestingExit;
    }

    inline bool IsFirstInstance() noexcept
    {
        return Impl::g_IsFirstInstance;
    }

    BASE_API void RequestExit(bool force) noexcept;
}


// =================================================================================================
// System types

namespace Graphyte::App
{
    enum class ShutdownReason
    {
        LogOff,
        Critical,
        CloseApplication,
    };
}


// =================================================================================================
// Input types

namespace Graphyte::App
{
    enum class ModifierKey
    {
        None         = 0,
        LeftAlt      = 1 << 0,
        RightAlt     = 1 << 1,
        LeftShift    = 1 << 2,
        RightShift   = 1 << 3,
        LeftControl  = 1 << 4,
        RightControl = 1 << 5,
        LeftCommand  = 1 << 6,
        RightCommand = 1 << 7,
        CapsLock     = 1 << 8,
        Alt          = LeftAlt | RightAlt,
        Shift        = LeftShift | RightShift,
        Control      = LeftControl | RightControl,
        Command      = LeftCommand | RightCommand,
    };
    GX_ENUM_CLASS_FLAGS(ModifierKey);

    enum class MouseButton
    {
        Invalid = 0,
        Left    = 1,
        Middle  = 2,
        Right   = 3,
        Thumb1  = 4,
        Thumb2  = 5,
    };

    enum class GamepadKey
    {
        Invalid               = 0,
        LeftAnalogX           = 1,
        LeftAnalogY           = 2,
        RightAnalogX          = 3,
        RightAnalogY          = 4,
        LeftTriggerAnalog     = 5,
        RightTriggerAnalog    = 6,
        LeftThumb             = 7,
        RightThumb            = 8,
        SpecialLeft           = 9,
        SpecialLeftX          = 10,
        SpecialLeftY          = 11,
        SpecialRight          = 12,
        FaceButtonBottom      = 13,
        FaceButtonRight       = 14,
        FaceButtonLeft        = 15,
        FaceButtonTop         = 16,
        LeftShoulder          = 17,
        RightShoulder         = 18,
        LeftTriggerThreshold  = 19,
        RightTriggerThreshold = 20,
        DPadUp                = 21,
        DPadDown              = 22,
        DPadRight             = 23,
        DPadLeft              = 24,
        LeftStickUp           = 25,
        LeftStickDown         = 26,
        LeftStickRight        = 27,
        LeftStickLeft         = 28,
        RightStickUp          = 29,
        RightStickDown        = 30,
        RightStickRight       = 31,
        RightStickLeft        = 32,
    };

    enum class KeyCode
    {
        None,
        Backspace,
        Delete,
        Tab,
        Clear,
        Enter,
        Pause,
        Escape,
        Space,
        Keypad0,
        Keypad1,
        Keypad2,
        Keypad3,
        Keypad4,
        Keypad5,
        Keypad6,
        Keypad7,
        Keypad8,
        Keypad9,
        KeypadPeriod,
        KeypadDivide,
        KeypadMultiply,
        KeypadMinus,
        KeypadPlus,
        KeypadEnter,
        KeypadEquals,
        ArrowUp,
        ArrowDown,
        ArrowRight,
        ArrowLeft,
        Insert,
        Home,
        End,
        PageUp,
        PageDown,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        Alpha0,
        Alpha1,
        Alpha2,
        Alpha3,
        Alpha4,
        Alpha5,
        Alpha6,
        Alpha7,
        Alpha8,
        Alpha9,
        Exclaim,
        DoubleQuote,
        Hash,
        Dollar,
        Ampersand,
        Quote,
        LeftParen,
        RightParen,
        Asterisk,
        Plus,
        Comma,
        Minus,
        Period,
        Slash,
        Colon,
        Semicolon,
        Less,
        Equals,
        Greater,
        Question,
        At,
        LeftBracket,
        Backslash,
        RightBracket,
        Caret,
        Underscore,
        BackQuote,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Numlock,
        Capslock,
        ScrollLock,
        RightShift,
        LeftShift,
        RightAlt,
        LeftAlt,
        RightControl,
        LeftControl,
        RightSuper,
        LeftSuper,
        AltGr,
        Help,
        Print,
        SysReq,
        Break,
        Menu,
        VolumeMute,
        VolumeUp,
        VolumeDown,
        MediaNextTrack,
        MediaPrevTrack,
        MediaStop,
        MediaPlayPause,
    };
}


// =================================================================================================
// Input event types

namespace Graphyte::App
{
    // Keyboard events
    struct CharEvent final
    {
        ModifierKey Modifiers;
        char32_t Character;
        bool Repeat;
    };

    struct KeyEvent final
    {
        ModifierKey Modifiers;
        KeyCode Key;
        char32_t Character;
        bool Repeat;
    };

    // Mouse events
    struct MouseButtonEvent final
    {
        ModifierKey Modifiers;
        MouseButton Button;
        Float2 Position;
    };

    struct MouseWheelEvent final
    {
        ModifierKey Modifiers;
        float Delta;
        Float2 Position;
    };

    struct MouseMoveEvent final
    {
        ModifierKey Modifiers;
        Float2 Position;
        Float2 Relative;
    };

    // Gamepad events
    struct GamepadAnalogEvent final
    {
        uint32_t Controller;
        GamepadKey Key;
        float Value;
    };

    struct GamepadButtonEvent final
    {
        uint32_t Controller;
        GamepadKey Key;
        bool Repeat;
    };

    struct MotionEvent final
    {
        Float2 Tilt;
        Float3 RotationRate;
        Float3 Gravity;
        Float3 Acceleration;
    };
}


// =================================================================================================
// Application window

namespace Graphyte::App
{
    /// @brief Specifies window mode.
    enum class WindowMode
    {
        /// @brief Window covering desktop exclusively.
        Fullscreen,

        /// @brief Desktop window covering whole screen.
        WindowedFullscreen,

        /// @brief Regular desktop window.
        Windowed,
    };

    /// @brief Specifies window activation method.
    enum class WindowActivation
    {
        /// @brief Window was activated by normal interaction.
        Activate,

        /// @brief Window was activated by user action.
        InputActivate,

        /// @brief Window was deactivated
        Deactivate,
    };

    /// @brief Specifies window action.
    enum class WindowAction
    {
        NonClientClick,
        Maximize,
        Minimize,
        Restore,
        WindowMenu,
    };

    /// @brief Specifies window limits
    struct WindowLimits final
    {
        /// @brief Provides minimum size of window.
        std::optional<System::Size> MinSize;

        /// @brief Provides maximum size of window.
        std::optional<System::Size> MaxSize;
    };

    struct WindowDescriptor final
    {
        /// @brief Initial window size limits.
        WindowLimits SizeLimits;

        /// @brief Window title.
        std::string Title;

        /// @brief Window position.
        System::Point Position;

        /// @brief Window size.
        System::Size Size;

        /// @brief Window mode.
        WindowMode Mode;

        bool SystemBorder : 1;
        bool CloseButton : 1;
        bool Regular : 1;
        bool Taskbar : 1;
        bool Topmost : 1;
        bool AcceptInput : 1;
        bool Resizable : 1;
        bool MaximizeButton : 1;
        bool MinimizeButton : 1;
    };

    class BASE_API Window
    {
    protected:
        WindowDescriptor m_Descriptor{};
        float m_DpiScale;

    public:
        Window() noexcept = default;

        virtual ~Window() noexcept = default;

        Window(Window const&) = delete;

        Window& operator=(Window const&) = delete;

    public:
        virtual void Move(System::Point location) noexcept = 0;

        virtual void Resize(System::Size size) noexcept = 0;

        virtual void Focus() noexcept = 0;

        virtual void BringToFront(bool force) noexcept = 0;

        virtual void Minimize() noexcept = 0;

        virtual void Maximize() noexcept = 0;

        virtual void Restore() noexcept = 0;

        virtual void Show() noexcept = 0;

        virtual void Hide() noexcept = 0;

        virtual void Enable() noexcept = 0;

        virtual void Disable() noexcept = 0;

        virtual void SetWindowMode(WindowMode value) noexcept = 0;

        WindowMode GetWindowMode() const noexcept
        {
            return this->m_Descriptor.Mode;
        }

        virtual void SetCaption(std::string_view caption) noexcept = 0;

        virtual void SetPlacement(System::Rect placement) noexcept = 0;

        virtual bool IsMaximized() const noexcept = 0;

        virtual bool IsMinimized() const noexcept = 0;

        virtual bool IsVisible() const noexcept = 0;

        virtual bool IsEnabled() const noexcept = 0;

        virtual bool IsFocused() const noexcept = 0;

        virtual void* GetNativeHandle() const noexcept = 0;

        
        virtual bool GetFullscreenRect(System::Rect& out_rect) noexcept = 0;

        virtual System::Size GetViewportSize() const noexcept = 0;

        virtual bool IsPointInside(System::Point value) noexcept = 0;

    public:
        WindowDescriptor const& GetDescriptor() const noexcept
        {
            return this->m_Descriptor;
        }

        void SetDpiScale(float scale) noexcept
        {
            this->m_DpiScale = scale;
        }

        float GetDpiScale() const noexcept
        {
            return this->m_DpiScale;
        }
    };

    BASE_API Window* MakeWindow(WindowDescriptor const& descriptor) noexcept;

    BASE_API void DestroyWindow(Window* window) noexcept;
}

// =================================================================================================
// Event handling

namespace Graphyte::App
{
    class BASE_API IEventHandler
    {
    public:
        virtual ~IEventHandler() noexcept;

    public:
        virtual void OnKeyChar(CharEvent const& event) noexcept;
        virtual void OnKeyDown(KeyEvent const& event) noexcept;
        virtual void OnKeyUp(KeyEvent const& event) noexcept;

        virtual void OnMouseDown(Window& window, MouseButtonEvent const& event) noexcept;
        virtual void OnMouseUp(Window& window, MouseButtonEvent const& event) noexcept;
        virtual void OnMouseDoubleClick(Window& window, MouseButtonEvent const& event) noexcept;
        virtual void OnMouseWheel(MouseWheelEvent const& event) noexcept;
        virtual void OnMouseMove() noexcept;
        virtual void OnMouseMove(MouseMoveEvent const& event) noexcept;

        virtual void OnControllerAnalog(GamepadAnalogEvent const& event) noexcept;
        virtual void OnControllerButtonPressed(GamepadButtonEvent const& event) noexcept;
        virtual void OnControllerButtonReleased(GamepadButtonEvent const& event) noexcept;

        virtual void OnWindowSizeChanged(Window& window, Float2 size, bool minimized) noexcept;
        virtual void OnWindowPaint(Window& window) noexcept;
        virtual void OnWindowSizeLimits(Window& window, WindowLimits& limits) noexcept;
        virtual void OnWindowSizing(Window& window) noexcept;
        virtual void OnWindowSizingBegin(Window& window) noexcept;
        virtual void OnWindowSizingEnd(Window& window) noexcept;
        virtual void OnWindowDpiChanged(Window& window) noexcept;
        virtual void OnWindowMoved(Window& window, Float2 position) noexcept;
        virtual void OnWindowClose(Window& window) noexcept;
        virtual void OnWindowActivate(Window& window, WindowActivation activation) noexcept;
        //virtual void OnWindowAction(Window& window, WindowAction action) noexcept;

        virtual void OnApplicationActivated(bool active) noexcept;
        virtual void OnApplicationShutdown(ShutdownReason reason) noexcept;

        virtual void OnSystemPowerSuspend() noexcept;
        virtual void OnSystemPowerRestore() noexcept;
    };
}

namespace Graphyte::App::Impl
{
    extern IEventHandler* g_EventHandler;
}

namespace Graphyte::App
{
    BASE_API IEventHandler* GetEventHandler() noexcept;

    BASE_API void SetEventHandler(IEventHandler* eventHandler) noexcept;
}
