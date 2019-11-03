#include "Base.pch.hxx"
#include <Graphyte/Application.hxx>
#include <Graphyte/Input/Input.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Platform.hxx>

#include "Linux.Window.hxx"

#include <SDL2/SDL.h>

namespace Graphyte::Application::Impl
{
    ApplicationDescriptor GApplicationDescriptor{};
    bool GIsFirstInstance{ false };

    static bool GIsMouseAttached{ false };
    static bool GIsRequestingExit{ false };
    static EventHandler* GApplicationEventHandler{};
    static std::vector<LinuxWindow*> GApplicationWindowsCollection;

    Input::KeyCode ConvertKeyCodes(
        SDL_Keycode keycode
    ) noexcept
    {
        switch (keycode)
        {
        //SDLK_UNKNOWN
        case SDLK_RETURN: return Input::KeyCode::Enter;
        case SDLK_ESCAPE: return Input::KeyCode::Escape;
        case SDLK_BACKSPACE: return Input::KeyCode::Backspace;
        case SDLK_TAB: return Input::KeyCode::Tab;
        case SDLK_SPACE: return Input::KeyCode::Space;
        case SDLK_EXCLAIM: return Input::KeyCode::Exclaim;
        case SDLK_QUOTEDBL: return Input::KeyCode::DoubleQuote;
        case SDLK_HASH: return Input::KeyCode::Hash;
        //case SDLK_PERCENT???
        case SDLK_DOLLAR: return Input::KeyCode::Dollar;
        case SDLK_AMPERSAND: return Input::KeyCode::Ampersand;
        case SDLK_QUOTE: return Input::KeyCode::Quote;
        case SDLK_LEFTPAREN: return Input::KeyCode::LeftParen;
        case SDLK_RIGHTPAREN: return Input::KeyCode::RightParen;
        case SDLK_ASTERISK: return Input::KeyCode::Asterisk;
        case SDLK_PLUS: return Input::KeyCode::Plus;
        case SDLK_COMMA: return Input::KeyCode::Comma;
        case SDLK_MINUS: return Input::KeyCode::Minus;
        case SDLK_PERIOD: return Input::KeyCode::Period;
        case SDLK_SLASH: return Input::KeyCode::Slash;
        case SDLK_0: return Input::KeyCode::Alpha0;
        case SDLK_1: return Input::KeyCode::Alpha1;
        case SDLK_2: return Input::KeyCode::Alpha2;
        case SDLK_3: return Input::KeyCode::Alpha3;
        case SDLK_4: return Input::KeyCode::Alpha4;
        case SDLK_5: return Input::KeyCode::Alpha5;
        case SDLK_6: return Input::KeyCode::Alpha6;
        case SDLK_7: return Input::KeyCode::Alpha7;
        case SDLK_8: return Input::KeyCode::Alpha8;
        case SDLK_9: return Input::KeyCode::Alpha9;
        case SDLK_COLON: return Input::KeyCode::Colon;
        case SDLK_SEMICOLON: return Input::KeyCode::Semicolon;
        case SDLK_LESS: return Input::KeyCode::Less;
        case SDLK_EQUALS: return Input::KeyCode::Equals;
        case SDLK_GREATER: return Input::KeyCode::Greater;
        case SDLK_QUESTION: return Input::KeyCode::Question;
        case SDLK_AT: return Input::KeyCode::At;
        case SDLK_LEFTBRACKET: return Input::KeyCode::LeftBracket;
        case SDLK_BACKSLASH: return Input::KeyCode::Backslash;
        case SDLK_RIGHTBRACKET: return Input::KeyCode::RightBracket;
        case SDLK_CARET: return Input::KeyCode::Caret;
        case SDLK_UNDERSCORE: return Input::KeyCode::Underscore;
        case SDLK_BACKQUOTE: return Input::KeyCode::BackQuote;
        case SDLK_a: return Input::KeyCode::A;
        case SDLK_b: return Input::KeyCode::B;
        case SDLK_c: return Input::KeyCode::C;
        case SDLK_d: return Input::KeyCode::D;
        case SDLK_e: return Input::KeyCode::E;
        case SDLK_f: return Input::KeyCode::F;
        case SDLK_g: return Input::KeyCode::G;
        case SDLK_h: return Input::KeyCode::H;
        case SDLK_i: return Input::KeyCode::I;
        case SDLK_j: return Input::KeyCode::J;
        case SDLK_k: return Input::KeyCode::K;
        case SDLK_l: return Input::KeyCode::L;
        case SDLK_m: return Input::KeyCode::M;
        case SDLK_n: return Input::KeyCode::N;
        case SDLK_o: return Input::KeyCode::O;
        case SDLK_p: return Input::KeyCode::P;
        case SDLK_q: return Input::KeyCode::Q;
        case SDLK_r: return Input::KeyCode::R;
        case SDLK_s: return Input::KeyCode::S;
        case SDLK_t: return Input::KeyCode::T;
        case SDLK_u: return Input::KeyCode::U;
        case SDLK_v: return Input::KeyCode::V;
        case SDLK_w: return Input::KeyCode::W;
        case SDLK_x: return Input::KeyCode::X;
        case SDLK_y: return Input::KeyCode::Y;
        case SDLK_z: return Input::KeyCode::Z;
        case SDLK_CAPSLOCK: return Input::KeyCode::Capslock;
        case SDLK_F1: return Input::KeyCode::F1;
        case SDLK_F2: return Input::KeyCode::F2;
        case SDLK_F3: return Input::KeyCode::F3;
        case SDLK_F4: return Input::KeyCode::F4;
        case SDLK_F5: return Input::KeyCode::F5;
        case SDLK_F6: return Input::KeyCode::F6;
        case SDLK_F7: return Input::KeyCode::F7;
        case SDLK_F8: return Input::KeyCode::F8;
        case SDLK_F9: return Input::KeyCode::F9;
        case SDLK_F10: return Input::KeyCode::F10;
        case SDLK_F11: return Input::KeyCode::F11;
        case SDLK_F12: return Input::KeyCode::F12;
        case SDLK_PRINTSCREEN: return Input::KeyCode::Print;
        case SDLK_SCROLLLOCK: return Input::KeyCode::ScrollLock;
        case SDLK_PAUSE: return Input::KeyCode::Pause;
        case SDLK_INSERT: return Input::KeyCode::Insert;
        case SDLK_HOME: return Input::KeyCode::Home;
        case SDLK_PAGEUP: return Input::KeyCode::PageUp;
        case SDLK_DELETE: return Input::KeyCode::Delete;
        case SDLK_END: return Input::KeyCode::End;
        case SDLK_PAGEDOWN: return Input::KeyCode::PageDown;
        case SDLK_RIGHT: return Input::KeyCode::ArrowRight;
        case SDLK_LEFT: return Input::KeyCode::ArrowLeft;
        case SDLK_DOWN: return Input::KeyCode::ArrowDown;
        case SDLK_UP: return Input::KeyCode::ArrowUp;
        case SDLK_NUMLOCKCLEAR: return Input::KeyCode::Numlock;
        case SDLK_KP_DIVIDE: return Input::KeyCode::KeypadDivide;
        case SDLK_KP_MULTIPLY: return Input::KeyCode::KeypadMultiply;
        case SDLK_KP_MINUS: return Input::KeyCode::KeypadMinus;
        case SDLK_KP_PLUS: return Input::KeyCode::KeypadPlus;
        case SDLK_KP_ENTER: return Input::KeyCode::KeypadEnter;
        case SDLK_KP_1: return Input::KeyCode::Keypad1;
        case SDLK_KP_2: return Input::KeyCode::Keypad2;
        case SDLK_KP_3: return Input::KeyCode::Keypad3;
        case SDLK_KP_4: return Input::KeyCode::Keypad4;
        case SDLK_KP_5: return Input::KeyCode::Keypad5;
        case SDLK_KP_6: return Input::KeyCode::Keypad6;
        case SDLK_KP_7: return Input::KeyCode::Keypad7;
        case SDLK_KP_8: return Input::KeyCode::Keypad8;
        case SDLK_KP_9: return Input::KeyCode::Keypad9;
        case SDLK_KP_0: return Input::KeyCode::Keypad0;
        case SDLK_KP_PERIOD: return Input::KeyCode::KeypadPeriod;
        //SDLK_APPLICATION
        //SDLK_POWER
        case SDLK_KP_EQUALS: return Input::KeyCode::KeypadEquals;
        case SDLK_F13: return Input::KeyCode::F13;
        case SDLK_F14: return Input::KeyCode::F14;
        case SDLK_F15: return Input::KeyCode::F15;
        case SDLK_F16: return Input::KeyCode::F16;
        case SDLK_F17: return Input::KeyCode::F17;
        case SDLK_F18: return Input::KeyCode::F18;
        case SDLK_F19: return Input::KeyCode::F19;
        case SDLK_F20: return Input::KeyCode::F20;
        case SDLK_F21: return Input::KeyCode::F21;
        case SDLK_F22: return Input::KeyCode::F22;
        case SDLK_F23: return Input::KeyCode::F23;
        case SDLK_F24: return Input::KeyCode::F24;
        //SDLK_EXECUTE
        case SDLK_HELP: return Input::KeyCode::Help;
        case SDLK_MENU: return Input::KeyCode::Menu;
        //SDLK_SELECT
        //SDLK_STOP
        //SDLK_AGAIN
        //SDLK_UNDO
        //SDLK_CUT
        //SDLK_COPY
        //SDLK_PASTE
        //SDLK_FIND
        case SDLK_MUTE: return Input::KeyCode::VolumeMute;
        case SDLK_VOLUMEUP: return Input::KeyCode::VolumeUp;
        case SDLK_VOLUMEDOWN: return Input::KeyCode::VolumeDown;
        //SDLK_KP_COMMA
        //SDLK_KP_EQUALSAS400
        //SDLK_ALTERASE
        case SDLK_SYSREQ: return Input::KeyCode::SysReq;
        //SDLK_CANCEL
        case SDLK_CLEAR: return Input::KeyCode::Clear;
        //SDLK_PRIOR
        //SDLK_RETURN2
        //SDLK_SEPARATOR
        //SDLK_OUT
        //SDLK_OPER
        //SDLK_CLEARAGAIN
        //SDLK_CRSEL
        //SDLK_EXSEL
        //SDLK_KP_00
        //SDLK_KP_000
        //SDLK_THOUSANDSSEPARATOR
        //SDLK_DECIMALSEPARATOR
        //SDLK_CURRENCYUNIT
        //SDLK_CURRENCYSUBUNIT
        //SDLK_KP_LEFTPAREN
        //SDLK_KP_RIGHTPAREN
        //SDLK_KP_LEFTBRACE
        //SDLK_KP_RIGHTBRACE
        //SDLK_KP_TAB
        //SDLK_KP_BACKSPACE
        //SDLK_KP_A
        //SDLK_KP_B
        //SDLK_KP_C
        //SDLK_KP_D
        //SDLK_KP_E
        //SDLK_KP_F
        //SDLK_KP_XOR
        //SDLK_KP_POWER
        //SDLK_KP_PERCENT
        //SDLK_KP_LESS
        //SDLK_KP_GREATER
        //SDLK_KP_AMPERSAND
        //SDLK_KP_DBLAMPERSAND
        //SDLK_KP_VERTICALBAR
        //SDLK_KP_DBLVERTICALBAR
        //SDLK_KP_COLON
        //SDLK_KP_HASH
        //SDLK_KP_SPACE
        //SDLK_KP_AT
        //SDLK_KP_EXCLAM
        //SDLK_KP_MEMSTORE
        //SDLK_KP_MEMRECALL
        //SDLK_KP_MEMCLEAR
        //SDLK_KP_MEMADD
        //SDLK_KP_MEMSUBTRACT
        //SDLK_KP_MEMMULTIPLY
        //SDLK_KP_MEMDIVIDE
        //SDLK_KP_PLUSMINUS
        //SDLK_KP_CLEAR
        //SDLK_KP_CLEARENTRY
        //SDLK_KP_BINARY
        //SDLK_KP_OCTAL
        //SDLK_KP_DECIMAL
        //SDLK_KP_HEXADECIMAL
        case SDLK_LCTRL: return Input::KeyCode::LeftControl;
        case SDLK_LSHIFT: return Input::KeyCode::LeftShift;
        case SDLK_LALT: return Input::KeyCode::LeftAlt;
        case SDLK_LGUI: return Input::KeyCode::LeftSuper;
        case SDLK_RCTRL: return Input::KeyCode::RightControl;
        case SDLK_RSHIFT: return Input::KeyCode::RightShift;
        case SDLK_RALT: return Input::KeyCode::RightAlt;
        case SDLK_RGUI: return Input::KeyCode::RightSuper;
        //SDLK_MODE
        case SDLK_AUDIONEXT: return Input::KeyCode::MediaNextTrack;
        case SDLK_AUDIOPREV: return Input::KeyCode::MediaPrevTrack;
        case SDLK_AUDIOSTOP: return Input::KeyCode::MediaStop;
        case SDLK_AUDIOPLAY: return Input::KeyCode::MediaPlayPause;
        //SDLK_AUDIOMUTE
        //SDLK_MEDIASELECT
        //SDLK_WWW
        //SDLK_MAIL
        //SDLK_CALCULATOR
        //SDLK_COMPUTER
        //SDLK_AC_SEARCH
        //SDLK_AC_HOME
        //SDLK_AC_BACK
        //SDLK_AC_FORWARD
        //SDLK_AC_STOP
        //SDLK_AC_REFRESH
        //SDLK_AC_BOOKMARKS
        //SDLK_BRIGHTNESSDOWN
        //SDLK_BRIGHTNESSUP
        //SDLK_DISPLAYSWITCH
        //SDLK_KBDILLUMTOGGLE
        //SDLK_KBDILLUMDOWN
        //SDLK_KBDILLUMUP
        //SDLK_EJECT
        //SDLK_SLEEP
        //SDLK_APP1
        //SDLK_APP2
        //SDLK_AUDIOREWIND
        //SDLK_AUDIOFASTFORWARD
        }

        return Input::KeyCode::None;
    }

    static bool IsMouseAttached() noexcept
    {
        char mouse[64] = "/sys/class/input/mouse0";
        size_t index = strlen(mouse) - 1;
        strncat(mouse, "/device/name", sizeof(mouse) - 1);

        for (size_t i = 0; i <= 9; ++i)
        {
            mouse[index] = static_cast<char>('0' + i);

            if (access(mouse, F_OK) == 0)
            {
                return true;
            }
        }

        return false;
    }

    static inline bool IsKeyCharMessage(
        const SDL_KeyboardEvent event
    ) noexcept
    {
        bool is_ctrl = (event.keysym.mod & static_cast<Uint16>(KMOD_LCTRL | KMOD_RCTRL)) != 0;
        auto keycode = event.keysym.sym;

        return !is_ctrl
            && (keycode < 128)
            && (keycode != SDLK_DOWN)
            && (keycode != SDLK_LEFT)
            && (keycode != SDLK_RIGHT)
            && (keycode != SDLK_UP)
            && (keycode != SDLK_DELETE);
    }

    static inline uint32_t ConvertKeyCode(
        const SDL_Keycode keycode
    ) noexcept
    {
        if ((static_cast<Uint32>(keycode) & static_cast<Uint32>(SDLK_SCANCODE_MASK)) != 0)
        {
            return 0;
        }
        else if (keycode == SDLK_DELETE)
        {
            return 0;
        }

        return static_cast<uint32_t>(keycode);
    }

    static LinuxWindow* FindWindow(
        uint32_t window_id
    ) noexcept
    {
        for (auto&& window : GApplicationWindowsCollection)
        {
            auto&& handle = reinterpret_cast<SDL_Window*>(window->GetNativeHandle());
            auto&& id = SDL_GetWindowID(handle);

            if (id == window_id)
            {
                return window;
            }
        }

        return nullptr;
    }

    static LinuxWindow* FindWindow(
        const SDL_Event& event,
        bool& windowless
    ) noexcept
    {
        uint32_t window_id = 0;
        windowless = false;

        switch (event.type)
        {
        case SDL_TEXTINPUT:
            {
                window_id = event.text.windowID;
                break;
            }
        case SDL_TEXTEDITING:
            {
                window_id = event.edit.windowID;
                break;
            }
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            {
                window_id = event.key.windowID;
                break;
            }
        case SDL_MOUSEMOTION:
            {
                window_id = event.motion.windowID;
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            {
                window_id = event.button.windowID;
                break;
            }
        case SDL_MOUSEWHEEL:
            {
                window_id = event.wheel.windowID;
                break;
            }
        case SDL_WINDOWEVENT:
            {
                window_id = event.window.windowID;
                break;
            }
        default:
            {
                windowless = true;
                return nullptr;
            }
        }

        return FindWindow(window_id);
    }

    static void ProcessMessage(
        const SDL_Event& event
    ) noexcept
    {
        (void)IsKeyCharMessage;

        auto windowless = false;
        auto current_window = FindWindow(event, windowless);

        switch (event.type)
        {
        case SDL_KEYDOWN:
            {
                auto const keycode = event.key.keysym.sym;
                auto const character = ConvertKeyCode(keycode);
                auto const repeat = event.key.repeat != 0;

                Impl::GApplicationEventHandler->OnKeyDown(ConvertKeyCodes(keycode), character, repeat);

                if (keycode == SDLK_BACKSPACE)
                {
                    Impl::GApplicationEventHandler->OnKeyChar('\b', repeat);
                }
                else if (keycode == SDLK_RETURN)
                {
                    Impl::GApplicationEventHandler->OnKeyChar('\n', repeat);
                }

                break;
            }

        case SDL_KEYUP:
            {
                auto const keycode = event.key.keysym.sym;
                auto const character = ConvertKeyCode(keycode);
                auto const repeat = event.key.repeat != 0;

                Impl::GApplicationEventHandler->OnKeyUp(ConvertKeyCodes(keycode), character, repeat);
                
                break;
            }

        case SDL_TEXTINPUT:
            {
                // XXX: Convert text to string32
                std::string_view text{ event.text.text };

                for (auto&& ch : text)
                {
                    Impl::GApplicationEventHandler->OnKeyChar(static_cast<char32_t>(static_cast<unsigned char>(ch)), false);
                }
                
                break;
            }

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            {
                auto const button_event = event.button;

                auto button = Input::MouseButton::Invalid;

                switch (button_event.button)
                {
                case SDL_BUTTON_LEFT:
                    {
                        button = Input::MouseButton::Left;
                        break;
                    }

                case SDL_BUTTON_MIDDLE:
                    {
                        button = Input::MouseButton::Middle;
                        break;
                    }

                case SDL_BUTTON_RIGHT:
                    {
                        button = Input::MouseButton::Right;
                        break;
                    }

                case SDL_BUTTON_X1:
                    {
                        button = Input::MouseButton::Thumb01;
                        break;
                    }

                case SDL_BUTTON_X2:
                    {
                        button = Input::MouseButton::Thumb02;
                        break;
                    }
                }

                if (button_event.type == SDL_MOUSEBUTTONUP)
                {
                    Impl::GApplicationEventHandler->OnMouseUp(*current_window, button, Float2{});

                    if (button_event.button == SDL_BUTTON_LEFT)
                    {
                    }
                }
                else
                {
                    /*if (!m_ActivateApp)
                    {
                        this->ActivateApplication();
                    }*/

                    if (button_event.clicks == 2)
                    {
                        Impl::GApplicationEventHandler->OnMouseDoubleClick(*current_window, button, Float2{});
                    }
                }

                break;
            }

        case SDL_MOUSEWHEEL:
            {
                auto amount = static_cast<float>(event.wheel.y);

                Impl::GApplicationEventHandler->OnMouseWheel(amount, Float2{});

                break;
            }

        case SDL_WINDOWEVENT:
            {
                auto const& window_event = event.window;

                switch (window_event.event)
                {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    {
                        auto const new_w = window_event.data1;
                        auto const new_h = window_event.data2;

                        Impl::GApplicationEventHandler->OnWindowSizeChanged(
                            *current_window,
                            Float2{
                                static_cast<float>(new_w),
                                static_cast<float>(new_h)
                            },
                            false
                        );

                        break;
                    }

                case SDL_WINDOWEVENT_RESIZED:
                    {
                        Impl::GApplicationEventHandler->OnWindowSizing(*current_window);

                        break;
                    }

                case SDL_WINDOWEVENT_CLOSE:
                    {
                        Impl::GApplicationEventHandler->OnWindowClose(*current_window);

                        break;
                    }

                case SDL_WINDOWEVENT_MOVED:
                    {
                        auto const pos_x = window_event.data1;
                        auto const pos_y = window_event.data2;
                        
                        Impl::GApplicationEventHandler->OnWindowMoved(
                            *current_window,
                            Float2{
                                static_cast<float>(pos_x),
                                static_cast<float>(pos_y)
                            }
                        );

                        break;
                    }

                case SDL_WINDOWEVENT_MAXIMIZED:
                    {
                        Impl::GApplicationEventHandler->OnWindowAction(*current_window, WindowAction::Maximize);

                        break;
                    }

                case SDL_WINDOWEVENT_RESTORED:
                    {
                        Impl::GApplicationEventHandler->OnWindowAction(*current_window, WindowAction::Restore);

                        break;
                    }
                }
                break;
            }
        }
    }
}


namespace Graphyte::Application
{
    BASE_API void Initialize() noexcept
    {
        Impl::GIsMouseAttached = Impl::IsMouseAttached();
    }

    BASE_API void Finalize() noexcept
    {
    }

    BASE_API const ApplicationDescriptor& GetDescriptor() noexcept
    {
        return Impl::GApplicationDescriptor;
    }

    BASE_API bool IsFirstInstance() noexcept
    {
        return Impl::GIsFirstInstance;
    }

    BASE_API bool IsRequestingExit() noexcept
    {
        return Impl::GIsRequestingExit;
    }

    BASE_API void RequestExit(
        bool force
    ) noexcept
    {
        GX_LOG(LogPlatform, Trace, "ApplicationProperties::RequestExit({})\n", force);

        if (force)
        {
            //
            // Forced. Flush and terminate.
            //

            Diagnostics::Exit(0);
        }

        Impl::GIsRequestingExit = true;
    }

    BASE_API bool IsForeground() noexcept
    {
        return true;
    }

    BASE_API void PollInputDevices(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
    }

    BASE_API void PumpMessages(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            Impl::ProcessMessage(event);
        }
    }

    BASE_API void Tick(
        [[maybe_unused]] float deltaTime
    ) noexcept
    {
    }

    BASE_API void SetEventHandler(
        EventHandler* handler
    ) noexcept
    {
        Impl::GApplicationEventHandler = handler;
    }

    BASE_API EventHandler* GetEventHandler() noexcept
    {
        return Impl::GApplicationEventHandler;
    }

    BASE_API Window* CreateWindow(const WindowDescriptor& descriptor) noexcept
    {
        auto window = new Impl::LinuxWindow();
        window->Create(descriptor);
        
        Impl::GApplicationWindowsCollection.push_back(window);

        return window;
    }

    BASE_API void DestroyWindow(Window* window) noexcept
    {
        GX_ASSERT(window != nullptr);

        auto it = std::find_if(std::begin(Impl::GApplicationWindowsCollection), std::end(Impl::GApplicationWindowsCollection), [&](Window* w) -> bool
        {
            return w == window;
        });

        GX_ASSERT(it != std::end(Impl::GApplicationWindowsCollection));
        Impl::GApplicationWindowsCollection.erase(it);
        
        if (window != nullptr)
        {
            window->Destroy();
        }
    }
}
