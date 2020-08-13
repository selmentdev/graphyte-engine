#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::App::Impl
{
    // TODO: constinit
    static constexpr std::array<KeyCode, 256> const c_KeyboardMapping = []() constexpr
    {
        std::array<KeyCode, 256> result{};
        result[VK_BACK]             = KeyCode::Backspace;
        result[VK_TAB]              = KeyCode::Tab;
        result[VK_CLEAR]            = KeyCode::Clear;
        result[VK_RETURN]           = KeyCode::Enter;
        result[VK_PAUSE]            = KeyCode::Pause;
        result[VK_CAPITAL]          = KeyCode::Capslock;
        result[VK_ESCAPE]           = KeyCode::Escape;
        result[VK_SPACE]            = KeyCode::Space;
        result[VK_PRIOR]            = KeyCode::PageUp;
        result[VK_NEXT]             = KeyCode::PageDown;
        result[VK_END]              = KeyCode::End;
        result[VK_HOME]             = KeyCode::Home;
        result[VK_LEFT]             = KeyCode::ArrowLeft;
        result[VK_UP]               = KeyCode::ArrowUp;
        result[VK_RIGHT]            = KeyCode::ArrowRight;
        result[VK_DOWN]             = KeyCode::ArrowDown;
        result[VK_SNAPSHOT]         = KeyCode::Print;
        result[VK_INSERT]           = KeyCode::Insert;
        result[VK_DELETE]           = KeyCode::Delete;
        result[VK_HELP]             = KeyCode::Help;
        result['0']                 = KeyCode::Alpha0;
        result['1']                 = KeyCode::Alpha1;
        result['2']                 = KeyCode::Alpha2;
        result['3']                 = KeyCode::Alpha3;
        result['4']                 = KeyCode::Alpha4;
        result['5']                 = KeyCode::Alpha5;
        result['6']                 = KeyCode::Alpha6;
        result['7']                 = KeyCode::Alpha7;
        result['8']                 = KeyCode::Alpha8;
        result['9']                 = KeyCode::Alpha9;
        result['A']                 = KeyCode::A;
        result['B']                 = KeyCode::B;
        result['C']                 = KeyCode::C;
        result['D']                 = KeyCode::D;
        result['E']                 = KeyCode::E;
        result['F']                 = KeyCode::F;
        result['G']                 = KeyCode::G;
        result['H']                 = KeyCode::H;
        result['I']                 = KeyCode::I;
        result['J']                 = KeyCode::J;
        result['K']                 = KeyCode::K;
        result['L']                 = KeyCode::L;
        result['M']                 = KeyCode::M;
        result['N']                 = KeyCode::N;
        result['O']                 = KeyCode::O;
        result['P']                 = KeyCode::P;
        result['Q']                 = KeyCode::Q;
        result['R']                 = KeyCode::R;
        result['S']                 = KeyCode::S;
        result['T']                 = KeyCode::T;
        result['U']                 = KeyCode::U;
        result['V']                 = KeyCode::V;
        result['W']                 = KeyCode::W;
        result['X']                 = KeyCode::X;
        result['Y']                 = KeyCode::Y;
        result['Z']                 = KeyCode::Z;
        result[VK_LWIN]             = KeyCode::LeftSuper;
        result[VK_RWIN]             = KeyCode::RightSuper;
        result[VK_APPS]             = KeyCode::Menu;
        result[VK_NUMPAD0]          = KeyCode::Keypad0;
        result[VK_NUMPAD1]          = KeyCode::Keypad1;
        result[VK_NUMPAD2]          = KeyCode::Keypad2;
        result[VK_NUMPAD3]          = KeyCode::Keypad3;
        result[VK_NUMPAD4]          = KeyCode::Keypad4;
        result[VK_NUMPAD5]          = KeyCode::Keypad5;
        result[VK_NUMPAD6]          = KeyCode::Keypad6;
        result[VK_NUMPAD7]          = KeyCode::Keypad7;
        result[VK_NUMPAD8]          = KeyCode::Keypad8;
        result[VK_NUMPAD9]          = KeyCode::Keypad9;
        result[VK_MULTIPLY]         = KeyCode::KeypadMultiply;
        result[VK_ADD]              = KeyCode::KeypadPlus;
        result[VK_SEPARATOR]        = KeyCode::KeypadEnter;
        result[VK_SUBTRACT]         = KeyCode::KeypadMinus;
        result[VK_DECIMAL]          = KeyCode::KeypadPeriod;
        result[VK_DIVIDE]           = KeyCode::KeypadDivide;
        result[VK_F1]               = KeyCode::F1;
        result[VK_F2]               = KeyCode::F2;
        result[VK_F3]               = KeyCode::F3;
        result[VK_F4]               = KeyCode::F4;
        result[VK_F5]               = KeyCode::F5;
        result[VK_F6]               = KeyCode::F6;
        result[VK_F7]               = KeyCode::F7;
        result[VK_F8]               = KeyCode::F8;
        result[VK_F9]               = KeyCode::F9;
        result[VK_F10]              = KeyCode::F10;
        result[VK_F11]              = KeyCode::F11;
        result[VK_F12]              = KeyCode::F12;
        result[VK_F13]              = KeyCode::F13;
        result[VK_F14]              = KeyCode::F14;
        result[VK_F15]              = KeyCode::F15;
        result[VK_F16]              = KeyCode::F16;
        result[VK_F17]              = KeyCode::F17;
        result[VK_F18]              = KeyCode::F18;
        result[VK_F19]              = KeyCode::F19;
        result[VK_F20]              = KeyCode::F20;
        result[VK_F21]              = KeyCode::F21;
        result[VK_F22]              = KeyCode::F22;
        result[VK_F23]              = KeyCode::F23;
        result[VK_F24]              = KeyCode::F24;
        result[VK_NUMLOCK]          = KeyCode::Numlock;
        result[VK_SCROLL]           = KeyCode::ScrollLock;
        result[VK_LSHIFT]           = KeyCode::LeftShift;
        result[VK_RSHIFT]           = KeyCode::RightShift;
        result[VK_LCONTROL]         = KeyCode::LeftControl;
        result[VK_RCONTROL]         = KeyCode::RightControl;
        result[VK_LMENU]            = KeyCode::LeftAlt;
        result[VK_RMENU]            = KeyCode::RightAlt;
        result[VK_VOLUME_MUTE]      = KeyCode::VolumeMute;
        result[VK_VOLUME_DOWN]      = KeyCode::VolumeDown;
        result[VK_VOLUME_UP]        = KeyCode::VolumeUp;
        result[VK_MEDIA_NEXT_TRACK] = KeyCode::MediaNextTrack;
        result[VK_MEDIA_PREV_TRACK] = KeyCode::MediaPrevTrack;
        result[VK_MEDIA_STOP]       = KeyCode::MediaStop;
        result[VK_MEDIA_PLAY_PAUSE] = KeyCode::MediaPlayPause;
        result[VK_OEM_1]            = KeyCode::Semicolon;
        result[VK_OEM_PLUS]         = KeyCode::Equals;
        result[VK_OEM_COMMA]        = KeyCode::Comma;
        result[VK_OEM_MINUS]        = KeyCode::Minus;
        result[VK_OEM_PERIOD]       = KeyCode::Period;
        result[VK_OEM_2]            = KeyCode::Slash;
        result[VK_OEM_3]            = KeyCode::BackQuote;
        result[VK_OEM_4]            = KeyCode::LeftBracket;
        result[VK_OEM_5]            = KeyCode::Backslash;
        result[VK_OEM_6]            = KeyCode::RightBracket;
        result[VK_OEM_7]            = KeyCode::Quote;

        return result;
    }();

    constexpr KeyCode TranslateKeyCode(UINT vk) noexcept
    {
        if (vk < std::size(c_KeyboardMapping))
        {
            return c_KeyboardMapping[vk];
        }

        return KeyCode::None;
    }
}
