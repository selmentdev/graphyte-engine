#include <GxBase/Input/Input.hxx>

namespace Graphyte::Application::Impl
{
    Input::KeyCode TranslateKeyCode(
        UINT vk_keycode
    ) noexcept
    {
        switch (vk_keycode)
        {
        case VK_BACK:               return Input::KeyCode::Backspace;
        case VK_TAB:                return Input::KeyCode::Tab;
        case VK_CLEAR:              return Input::KeyCode::Clear;
        case VK_RETURN:             return Input::KeyCode::Enter;
        case VK_PAUSE:              return Input::KeyCode::Pause;
        case VK_CAPITAL:            return Input::KeyCode::Capslock;
        case VK_ESCAPE:             return Input::KeyCode::Escape;
        case VK_SPACE:              return Input::KeyCode::Space;
        case VK_PRIOR:              return Input::KeyCode::PageUp;
        case VK_NEXT:               return Input::KeyCode::PageDown;
        case VK_END:                return Input::KeyCode::End;
        case VK_HOME:               return Input::KeyCode::Home;
        case VK_LEFT:               return Input::KeyCode::ArrowLeft;
        case VK_UP:                 return Input::KeyCode::ArrowUp;
        case VK_RIGHT:              return Input::KeyCode::ArrowRight;
        case VK_DOWN:               return Input::KeyCode::ArrowDown;
        case VK_SNAPSHOT:           return Input::KeyCode::Print;
        case VK_INSERT:             return Input::KeyCode::Insert;
        case VK_DELETE:             return Input::KeyCode::Delete;
        case VK_HELP:               return Input::KeyCode::Help;
        case '0':                   return Input::KeyCode::Alpha0;
        case '1':                   return Input::KeyCode::Alpha1;
        case '2':                   return Input::KeyCode::Alpha2;
        case '3':                   return Input::KeyCode::Alpha3;
        case '4':                   return Input::KeyCode::Alpha4;
        case '5':                   return Input::KeyCode::Alpha5;
        case '6':                   return Input::KeyCode::Alpha6;
        case '7':                   return Input::KeyCode::Alpha7;
        case '8':                   return Input::KeyCode::Alpha8;
        case '9':                   return Input::KeyCode::Alpha9;
        case 'A':                   return Input::KeyCode::A;
        case 'B':                   return Input::KeyCode::B;
        case 'C':                   return Input::KeyCode::C;
        case 'D':                   return Input::KeyCode::D;
        case 'E':                   return Input::KeyCode::E;
        case 'F':                   return Input::KeyCode::F;
        case 'G':                   return Input::KeyCode::G;
        case 'H':                   return Input::KeyCode::H;
        case 'I':                   return Input::KeyCode::I;
        case 'J':                   return Input::KeyCode::J;
        case 'K':                   return Input::KeyCode::K;
        case 'L':                   return Input::KeyCode::L;
        case 'M':                   return Input::KeyCode::M;
        case 'N':                   return Input::KeyCode::N;
        case 'O':                   return Input::KeyCode::O;
        case 'P':                   return Input::KeyCode::P;
        case 'Q':                   return Input::KeyCode::Q;
        case 'R':                   return Input::KeyCode::R;
        case 'S':                   return Input::KeyCode::S;
        case 'T':                   return Input::KeyCode::T;
        case 'U':                   return Input::KeyCode::U;
        case 'V':                   return Input::KeyCode::V;
        case 'W':                   return Input::KeyCode::W;
        case 'X':                   return Input::KeyCode::X;
        case 'Y':                   return Input::KeyCode::Y;
        case 'Z':                   return Input::KeyCode::Z;
        case VK_LWIN:               return Input::KeyCode::LeftSuper;
        case VK_RWIN:               return Input::KeyCode::RightSuper;
        case VK_APPS:               return Input::KeyCode::Menu;
        case VK_NUMPAD0:            return Input::KeyCode::Keypad0;
        case VK_NUMPAD1:            return Input::KeyCode::Keypad1;
        case VK_NUMPAD2:            return Input::KeyCode::Keypad2;
        case VK_NUMPAD3:            return Input::KeyCode::Keypad3;
        case VK_NUMPAD4:            return Input::KeyCode::Keypad4;
        case VK_NUMPAD5:            return Input::KeyCode::Keypad5;
        case VK_NUMPAD6:            return Input::KeyCode::Keypad6;
        case VK_NUMPAD7:            return Input::KeyCode::Keypad7;
        case VK_NUMPAD8:            return Input::KeyCode::Keypad8;
        case VK_NUMPAD9:            return Input::KeyCode::Keypad9;
        case VK_MULTIPLY:           return Input::KeyCode::KeypadMultiply;
        case VK_ADD:                return Input::KeyCode::KeypadPlus;
        case VK_SEPARATOR:          return Input::KeyCode::KeypadEnter;
        case VK_SUBTRACT:           return Input::KeyCode::KeypadMinus;
        case VK_DECIMAL:            return Input::KeyCode::KeypadPeriod;
        case VK_DIVIDE:             return Input::KeyCode::KeypadDivide;
        case VK_F1:                 return Input::KeyCode::F1;
        case VK_F2:                 return Input::KeyCode::F2;
        case VK_F3:                 return Input::KeyCode::F3;
        case VK_F4:                 return Input::KeyCode::F4;
        case VK_F5:                 return Input::KeyCode::F5;
        case VK_F6:                 return Input::KeyCode::F6;
        case VK_F7:                 return Input::KeyCode::F7;
        case VK_F8:                 return Input::KeyCode::F8;
        case VK_F9:                 return Input::KeyCode::F9;
        case VK_F10:                return Input::KeyCode::F10;
        case VK_F11:                return Input::KeyCode::F11;
        case VK_F12:                return Input::KeyCode::F12;
        case VK_F13:                return Input::KeyCode::F13;
        case VK_F14:                return Input::KeyCode::F14;
        case VK_F15:                return Input::KeyCode::F15;
        case VK_F16:                return Input::KeyCode::F16;
        case VK_F17:                return Input::KeyCode::F17;
        case VK_F18:                return Input::KeyCode::F18;
        case VK_F19:                return Input::KeyCode::F19;
        case VK_F20:                return Input::KeyCode::F20;
        case VK_F21:                return Input::KeyCode::F21;
        case VK_F22:                return Input::KeyCode::F22;
        case VK_F23:                return Input::KeyCode::F23;
        case VK_F24:                return Input::KeyCode::F24;
        case VK_NUMLOCK:            return Input::KeyCode::Numlock;
        case VK_SCROLL:             return Input::KeyCode::ScrollLock;
        case VK_LSHIFT:             return Input::KeyCode::LeftShift;
        case VK_RSHIFT:             return Input::KeyCode::RightShift;
        case VK_LCONTROL:           return Input::KeyCode::LeftControl;
        case VK_RCONTROL:           return Input::KeyCode::RightControl;
        case VK_LMENU:              return Input::KeyCode::LeftAlt;
        case VK_RMENU:              return Input::KeyCode::RightAlt;
        case VK_VOLUME_MUTE:        return Input::KeyCode::VolumeMute;
        case VK_VOLUME_DOWN:        return Input::KeyCode::VolumeDown;
        case VK_VOLUME_UP:          return Input::KeyCode::VolumeUp;
        case VK_MEDIA_NEXT_TRACK:   return Input::KeyCode::MediaNextTrack;
        case VK_MEDIA_PREV_TRACK:   return Input::KeyCode::MediaPrevTrack;
        case VK_MEDIA_STOP:         return Input::KeyCode::MediaStop;
        case VK_MEDIA_PLAY_PAUSE:   return Input::KeyCode::MediaPlayPause;
        case VK_OEM_1:              return Input::KeyCode::Semicolon;
        case VK_OEM_PLUS:           return Input::KeyCode::Equals;
        case VK_OEM_COMMA:          return Input::KeyCode::Comma;
        case VK_OEM_MINUS:          return Input::KeyCode::Minus;
        case VK_OEM_PERIOD:         return Input::KeyCode::Period;
        case VK_OEM_2:              return Input::KeyCode::Slash;
        case VK_OEM_3:              return Input::KeyCode::BackQuote;
        case VK_OEM_4:              return Input::KeyCode::LeftBracket;
        case VK_OEM_5:              return Input::KeyCode::Backslash;
        case VK_OEM_6:              return Input::KeyCode::RightBracket;
        case VK_OEM_7:              return Input::KeyCode::Quote;
        }

        return Input::KeyCode::None;
    }
}