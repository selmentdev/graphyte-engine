#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Version.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Types.hxx>

// =================================================================================================
// Logging category.

namespace Graphyte::App
{
    GX_DECLARE_LOG_CATEGORY(LogNativeApp, Trace, Trace);
}


// =================================================================================================
// Application types

namespace Graphyte::App
{
    enum class ApplicationType
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
    enum class ModifierKey : uint16_t
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

    enum class MouseButton : uint8_t
    {
        Invalid = 0,
        Left    = 1,
        Middle  = 2,
        Right   = 3,
        Thumb1  = 4,
        Thumb2  = 5,
    };

    enum class GamepadKey : uint8_t
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

    enum class KeyCode : uint8_t
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
    };

    struct MouseMoveEvent final
    {
        ModifierKey Modifiers;
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

    // Motion events
    struct MotionEvent final
    {
        Float2 Tilt;
        Float3 RotationRate;
        Float3 Gravity;
        Float3 Acceleration;
    };
}


// =================================================================================================
// Window types

namespace Graphyte::App
{
    enum class WindowType
    {
        /// @brief Typical game window. Has enabled fullscreen / windowed mode.
        Game,

        /// @brief Rendering window which can be embedded in application.
        Viewport,

        /// @brief Sizable window with min/max/close buttons.
        Form,

        /// @brief Non sizable dialog with just close button.
        Dialog,
    };

    enum class WindowMode
    {
        /// @brief Non-sizable desktop window with close button.
        /// Initial state of created window.
        /// Can be rendered on any display.
        Windowed,

        /// @brief Fullscreen window adjusted to current display size,
        /// without borders. Defaults to primary system display device.
        Fullscreen,

        /// @brief Fullscreen window adjusted to current display size,
        /// without borders. Defaults to nearest system display device.
        WindowedFullscreen,
    };

    enum class WindowActivation
    {
        Activate,
        Deactivate,
        ClickActivate,
    };

    struct WindowSizeLimits final
    {
        std::optional<System::Size> Min;
        std::optional<System::Size> Max;
    };

    class Window
    {
    protected:
        virtual ~Window() noexcept = default;

    public:
        virtual bool Focus() noexcept = 0;

        virtual bool BringToFront(bool force) noexcept = 0;

        virtual bool Show() noexcept = 0;

        virtual bool Hide() noexcept = 0;

        virtual bool Enable() noexcept = 0;

        virtual bool Disable() noexcept = 0;

        virtual bool Minimize() noexcept = 0;

        virtual bool Maximize() noexcept = 0;

        virtual bool Restore() noexcept = 0;

        virtual bool IsMinimized() const noexcept = 0;

        virtual bool IsMaximized() const noexcept = 0;

        virtual bool IsFocused() const noexcept = 0;

        virtual bool IsEnabled() const noexcept = 0;

        virtual bool IsVisible() const noexcept = 0;

        virtual bool SetMode(WindowMode value) noexcept = 0;

        virtual WindowMode GetMode() const noexcept = 0;

        virtual WindowType GetType() const noexcept = 0;

        virtual void* GetNativeHandle() const noexcept = 0;

        virtual System::Size GetClientSize() const noexcept = 0;

        virtual bool GetFullscreenPlacement(System::Rect& out_value) noexcept = 0;

        virtual bool SetCaption(std::string_view value) noexcept = 0;

        virtual bool GetPlacement(System::Rect& out_value) noexcept = 0;

        virtual bool SetPlacement(System::Rect value) noexcept = 0;

        virtual bool SetLocation(System::Point value) noexcept = 0;

        virtual bool SetSize(System::Size value) noexcept = 0;

        virtual float GetDpiScale() const noexcept = 0;

        virtual void SetDpiScale(float value) noexcept = 0;

        virtual void SetSizeLimits(WindowSizeLimits const& limits) noexcept = 0;

        virtual WindowSizeLimits const& GetSizeLimits() const noexcept = 0;
    };
}


// =================================================================================================
// Event handling types

namespace Graphyte::App
{
    class BASE_API IEventHandler
    {
    public:
        virtual ~IEventHandler() noexcept = 0;

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
        virtual void OnWindowSizingBegin(Window& window) noexcept;
        virtual void OnWindowSizingEnd(Window& window) noexcept;
        virtual void OnWindowDpiChanged(Window& window) noexcept;
        virtual void OnWindowMoved(Window& window, Float2 position) noexcept;
        virtual void OnWindowClose(Window& window) noexcept;
        virtual void OnWindowActivate(Window& window, WindowActivation activation) noexcept;
        virtual void OnApplicationActivated(bool active) noexcept;
        virtual void OnSystemPowerShutdown(ShutdownReason reason) noexcept;
        virtual void OnSystemPowerSuspend() noexcept;
        virtual void OnSystemPowerRestore() noexcept;
    };
}


// =================================================================================================
// External variables

namespace Graphyte::App::Impl
{
    extern BASE_API bool g_IsRequestingExit;
    extern BASE_API bool g_IsFirstInstance;
    extern BASE_API ApplicationDescriptor g_ApplicationDescriptor;
    extern BASE_API IEventHandler* g_EventHandler;
}


// =================================================================================================
// Application API

namespace Graphyte::App
{
    inline ApplicationDescriptor const& GetDescriptor() noexcept
    {
        return Impl::g_ApplicationDescriptor;
    }

    inline bool IsRequestingExit() noexcept
    {
        return Impl::g_IsRequestingExit;
    }

    inline bool IsFirstInstance() noexcept
    {
        return Impl::g_IsFirstInstance;
    }

    inline IEventHandler* GetEventHandler() noexcept
    {
        return Impl::g_EventHandler;
    }

    BASE_API void SetEventHandler(IEventHandler* eventHandler) noexcept;

    BASE_API void Initialize() noexcept;

    BASE_API void Finalize() noexcept;

    BASE_API void Tick(float deltaTime) noexcept;

    BASE_API void PollInput(float deltaTime) noexcept;

    BASE_API void ProcessMessages(float deltaTime) noexcept;

    BASE_API bool IsForeground() noexcept;

    BASE_API void RequestExit() noexcept;

    BASE_API Window* MakeWindow(WindowType type) noexcept;

    BASE_API void DestroyWindow(Window* window) noexcept;
}
