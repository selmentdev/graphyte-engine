#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Types.hxx>

namespace Graphyte::Input
{
    enum struct ModifierKeyState
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
    GX_ENUM_CLASS_FLAGS(ModifierKeyState);

    enum struct MouseButton
    {
        Invalid = 0,
        Left    = 1,
        Middle  = 2,
        Right   = 3,
        Thumb01 = 4,
        Thumb02 = 5,
    };

    enum struct GamepadKey
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
        None      = 0,
        Scroll    = 1,
        Zoom      = 2,
        Swipe     = 3,
        Rotate    = 4,
        LongPress = 5,
    };

    enum class TouchIndex
    {
        Touch1  = 0,
        Touch2  = 1,
        Touch3  = 2,
        Touch4  = 3,
        Touch5  = 4,
        Touch6  = 5,
        Touch7  = 6,
        Touch8  = 7,
        Touch9  = 8,
        Touch10 = 9,
    };

    struct InputEvent final
    {
        ModifierKeyState KeyState;
        uint32_t Controller;
    };

    struct KeyEvent final
    {
        InputEvent Base;
        KeyCode Code;
        char32_t Character;
        bool Repeat;
    };

    struct CharacterEvent final
    {
        InputEvent Base;
        char32_t Character;
    };

    struct PointerEvent final
    {
        InputEvent Base;
        Float2 ScreenSpacePosition;
        Float2 Delta;
        MouseButton Buttons;
    };

    struct MotionEvent final
    {
        InputEvent Base;
        Float2 Tilt;
        Float3 RotationRate;
        Float3 Gravity;
        Float3 Acceleration;
    };

    struct GamepadAnalogEvent final
    {
        InputEvent Base;
        GamepadKey Key;
        float Value;
    };

    struct GamepadButtonEvent final
    {
        InputEvent Base;
        GamepadKey Key;
        bool Repeat;
    };
}
