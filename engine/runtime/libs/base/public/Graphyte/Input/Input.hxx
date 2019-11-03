#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Maths/Types.hxx>

namespace Graphyte::Input
{
    enum struct ModifierKeyState
    {
        None = 0,
        LeftAlt = 1 << 0,
        RightAlt = 1 << 1,
        LeftShift = 1 << 2,
        RightShift = 1 << 3,
        LeftControl = 1 << 4,
        RightControl = 1 << 5,
        LeftCommand = 1 << 6,
        RightCommand = 1 << 7,
        CapsLock = 1 << 8,
        Alt = LeftAlt | RightAlt,
        Shift = LeftShift | RightShift,
        Control = LeftControl | RightControl,
        Command = LeftCommand | RightCommand,
    };
    GX_ENUM_CLASS_FLAGS(ModifierKeyState);

    enum struct MouseButton
    {
        Invalid = 0,
        Left = 1,
        Middle = 2,
        Right = 3,
        Thumb01 = 4,
        Thumb02 = 5,
    };

    enum struct GamepadKey
    {
        Invalid             = 0,
        LeftAnalogX         = 1,
        LeftAnalogY         = 2,
        RightAnalogX        = 3,
        RightAnalogY        = 4,
        LeftTriggerAnalog   = 5,
        RightTriggerAnalog  = 6,
        LeftThumb           = 7,
        RightThumb          = 8,
        SpecialLeft         = 9,
        SpecialLeftX        = 10,
        SpecialLeftY        = 11,
        SpecialRight        = 12,
        FaceButtonBottom    = 13,
        FaceButtonRight     = 14,
        FaceButtonLeft      = 15,
        FaceButtonTop       = 16,
        LeftShoulder        = 17,
        RightShoulder       = 18,
        LeftTriggerThreshold    = 19,
        RightTriggerThreshold   = 20,
        DPadUp                  = 21,
        DPadDown                = 22,
        DPadRight               = 23,
        DPadLeft                = 24,
        LeftStickUp             = 25,
        LeftStickDown           = 26,
        LeftStickRight          = 27,
        LeftStickLeft           = 28,
        RightStickUp            = 29,
        RightStickDown          = 30,
        RightStickRight         = 31,
        RightStickLeft          = 32,
    };

    enum struct KeyCode
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

    enum struct GestureType
    {
        None = 0,
        Scroll = 1,
        Zoom = 2,
        Swipe = 3,
        Rotate = 4,
        LongPress = 5,
    };

    enum class TouchIndex
    {
        Touch1      = 0,
        Touch2      = 1,
        Touch3      = 2,
        Touch4      = 3,
        Touch5      = 4,
        Touch6      = 5,
        Touch7      = 6,
        Touch8      = 7,
        Touch9      = 8,
        Touch10     = 9,
    };

    struct InputEvent
    {
    protected:
        ModifierKeyState m_KeyState;
        uint32_t m_UserIndex;
        bool m_IsRepeat;

    public:
        InputEvent() noexcept = default;
        InputEvent(ModifierKeyState state, uint32_t user_index, bool is_repeat) noexcept
            : m_KeyState{ state }
            , m_UserIndex{ user_index }
            , m_IsRepeat{ is_repeat }
        {
        }

    public:
        ModifierKeyState GetKeyState() const noexcept
        {
            return m_KeyState;
        }
        uint32_t GetUserIndex() const noexcept
        {
            return m_UserIndex;
        }
        bool IsRepeat() const noexcept
        {
            return m_IsRepeat;
        }
    };

    struct KeyEvent final : public InputEvent
    {
    private:
        KeyCode m_KeyCode;
        char32_t m_Character;

    public:
        KeyEvent() noexcept = default;
        KeyEvent(ModifierKeyState state, uint32_t user_index, bool is_repeat, KeyCode keycode, char32_t character) noexcept
            : InputEvent{ state, user_index, is_repeat }
            , m_KeyCode{ keycode }
            , m_Character{ character }
        {
        }

    public:
        KeyCode GetKeyCode() const noexcept
        {
            return m_KeyCode;
        }

        char32_t GetCharacter() const noexcept
        {
            return m_Character;
        }
    };

    struct CharacterEvent final : public InputEvent
    {
    private:
        char32_t m_Character;

    public:
        CharacterEvent() noexcept = default;
        CharacterEvent(ModifierKeyState state, uint32_t user_index, bool is_repeat, char32_t character) noexcept
            : InputEvent{ state, user_index, is_repeat }
            , m_Character{ character }
        {
        }

    public:
        char32_t GetCharacter() const noexcept
        {
            return m_Character;
        }
    };

    struct PointerEvent final : public InputEvent
    {
    private:
        Maths::float2 m_ScreenSpacePosition;
        Maths::float2 m_CursorDelta;
        MouseButton m_Button;

    public:
        PointerEvent() noexcept = default;
        PointerEvent(ModifierKeyState state, uint32_t user_index, bool is_repeat, Maths::float2 screen_space_position, Maths::float2 cursor_delta, MouseButton mouse_button) noexcept
            : InputEvent{ state, user_index, is_repeat }
            , m_ScreenSpacePosition{ screen_space_position }
            , m_CursorDelta{ cursor_delta }
            , m_Button{ mouse_button }
        {
        }

    public:
        Maths::float2 GetScreenSpacePosition() const noexcept
        {
            return m_ScreenSpacePosition;
        }

        Maths::float2 GetCursorDelta() const noexcept
        {
            return m_CursorDelta;
        }

        MouseButton GetMouseButton() const noexcept
        {
            return m_Button;
        }
    };

    struct MotionEvent final : public InputEvent
    {
    private:
        Maths::float2 m_Tilt;
        Maths::float3 m_RotationRate;
        Maths::float3 m_Gravity;
        Maths::float3 m_Acceleration;

    public:
        MotionEvent() noexcept = default;
        MotionEvent(ModifierKeyState state, uint32_t user_index, bool is_repeat, Maths::float2 tilt, Maths::float3 rotation_rate, Maths::float3 gravity, Maths::float3 acceleration) noexcept
            : InputEvent{ state, user_index, is_repeat }
            , m_Tilt{ tilt }
            , m_RotationRate{ rotation_rate }
            , m_Gravity{ gravity }
            , m_Acceleration{ acceleration }
        {
        }

    public:
        Maths::float2 GetTilt() const noexcept
        {
            return m_Tilt;
        }

        Maths::float3 GetRotationRate() const noexcept
        {
            return m_RotationRate;
        }

        Maths::float3 GetGravity() const noexcept
        {
            return m_Gravity;
        }

        Maths::float3 GetAcceleration() const noexcept
        {
            return m_Acceleration;
        }
    };
}
