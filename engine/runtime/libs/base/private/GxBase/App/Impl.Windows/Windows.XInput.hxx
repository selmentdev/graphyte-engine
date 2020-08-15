#pragma once
#include <GxBase/App.hxx>
#include <GxBase/System.hxx>

#include <Xinput.h>

namespace Graphyte::App::Impl
{
    class WindowsXInputDevice final
    {
    public:
        static constexpr size_t MaxControllers = 4;
        static constexpr size_t MaxButtons     = 24;

    private:
        static constexpr const GamepadKey XBoxPadInputMapping[] = {
            GamepadKey::FaceButtonBottom,
            GamepadKey::FaceButtonRight,
            GamepadKey::FaceButtonLeft,
            GamepadKey::FaceButtonTop,
            GamepadKey::LeftShoulder,
            GamepadKey::RightShoulder,
            GamepadKey::SpecialRight,
            GamepadKey::SpecialLeft,
            GamepadKey::LeftThumb,
            GamepadKey::RightThumb,
            GamepadKey::LeftTriggerThreshold,
            GamepadKey::RightTriggerThreshold,
            GamepadKey::DPadUp,
            GamepadKey::DPadDown,
            GamepadKey::DPadLeft,
            GamepadKey::DPadRight,
            GamepadKey::LeftStickUp,
            GamepadKey::LeftStickDown,
            GamepadKey::LeftStickLeft,
            GamepadKey::LeftStickRight,
            GamepadKey::RightStickUp,
            GamepadKey::RightStickDown,
            GamepadKey::RightStickLeft,
            GamepadKey::RightStickRight,
        };

        struct ControllerState final
        {
            std::array<bool, MaxButtons> Button;
            std::array<double, MaxButtons> RepeatTime;
            int16_t LeftXAnalog;
            int16_t LeftYAnalog;
            int16_t RightXAnalog;
            int16_t RightYAnalog;
            int16_t LeftTriggerAnalog;
            int16_t RightTriggerAnalog;
            uint32_t ControllerId;
            bool Connected;
        };

        std::array<ControllerState, MaxControllers> m_Controllers{};
        float m_ButtonRepeatDelay{ 0.1f };
        float m_ButtonInitialDelay{ 0.2f };
        bool m_NeedsUpdate{ true };

    private:
        void ControllerAnalog(
            GamepadKey key,
            uint32_t controller,
            int16_t value,
            float normalized,
            int16_t& previous,
            int32_t deadzone) noexcept
        {
            if (previous != value || std::abs(static_cast<int32_t>(value)) > deadzone)
            {
                g_EventHandler->OnControllerAnalog(GamepadAnalogEvent{
                    .Controller = controller,
                    .Key   = key,
                    .Value = normalized,
                });
            }

            previous = value;
        }

        constexpr float NormalizeAnalog(int16_t value) noexcept
        {
            float const length = (value <= 0 ? 32768.0f : 32767.0f);
            return static_cast<float>(value) / length;
        }

    public:
        void RequestUpdate() noexcept
        {
            this->m_NeedsUpdate = true;
        }

        void Poll([[maybe_unused]] float deltaTime) noexcept
        {
            bool connected[MaxControllers];
            bool is_attached = false;

            XINPUT_STATE xinput_states[MaxControllers];

            for (DWORD controller = 0; controller < MaxControllers; ++controller)
            {
                ControllerState& controller_state = this->m_Controllers[controller];

                connected[controller] = controller_state.Connected;

                if (controller_state.Connected || this->m_NeedsUpdate)
                {
                    XINPUT_STATE& state = xinput_states[controller];

                    state = {}; // is this really needed?

                    controller_state.Connected = XInputGetState(controller, &state) == ERROR_SUCCESS;

                    if (controller_state.Connected)
                    {
                        is_attached = true;
                    }
                }
            }

            if (is_attached)
            {
                double current_time = System::GetSeconds();

                for (uint32_t controller = 0; controller < MaxControllers; ++controller)
                {
                    ControllerState& controller_state = this->m_Controllers[controller];

                    bool was_connected = connected[controller];

                    if (controller_state.Connected && was_connected)
                    {
                        XINPUT_STATE& state = xinput_states[controller];

                        std::array<bool, MaxButtons> button_states{};

                        button_states[0]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_A));
                        button_states[1]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_B));
                        button_states[2]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_X));
                        button_states[3]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y));
                        button_states[4]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER));
                        button_states[5]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER));
                        button_states[6]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK));
                        button_states[7]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_START));
                        button_states[8]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB));
                        button_states[9]  = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB));
                        button_states[10] = (0 != (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
                        button_states[11] = (0 != (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
                        button_states[12] = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP));
                        button_states[13] = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN));
                        button_states[14] = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT));
                        button_states[15] = (0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT));
                        button_states[16] = (0 != (state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
                        button_states[17] = (0 != (state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
                        button_states[18] = (0 != (state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
                        button_states[19] = (0 != (state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
                        button_states[20] = (0 != (state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
                        button_states[21] = (0 != (state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
                        button_states[22] = (0 != (state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
                        button_states[23] = (0 != (state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));

                        ControllerAnalog(
                            GamepadKey::LeftAnalogX,
                            controller,
                            state.Gamepad.sThumbLX,
                            NormalizeAnalog(state.Gamepad.sThumbLX),
                            controller_state.LeftXAnalog,
                            XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

                        ControllerAnalog(
                            GamepadKey::LeftAnalogY,
                            controller,
                            state.Gamepad.sThumbLY,
                            NormalizeAnalog(state.Gamepad.sThumbLY),
                            controller_state.LeftYAnalog,
                            XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

                        ControllerAnalog(
                            GamepadKey::RightAnalogX,
                            controller,
                            state.Gamepad.sThumbRX,
                            NormalizeAnalog(state.Gamepad.sThumbRX),
                            controller_state.RightXAnalog,
                            XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

                        ControllerAnalog(
                            GamepadKey::RightAnalogY,
                            controller,
                            state.Gamepad.sThumbRY,
                            NormalizeAnalog(state.Gamepad.sThumbRY),
                            controller_state.RightYAnalog,
                            XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

                        ControllerAnalog(
                            GamepadKey::LeftTriggerAnalog,
                            controller,
                            state.Gamepad.bLeftTrigger,
                            static_cast<float>(state.Gamepad.bLeftTrigger) / 255.0F,
                            controller_state.LeftTriggerAnalog,
                            XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

                        ControllerAnalog(
                            GamepadKey::RightTriggerAnalog,
                            controller,
                            state.Gamepad.bRightTrigger,
                            static_cast<float>(state.Gamepad.bRightTrigger) / 255.0F,
                            controller_state.RightTriggerAnalog,
                            XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

                        for (size_t i = 0; i < MaxButtons; ++i)
                        {
                            GamepadButtonEvent event{
                                .Controller = controller,
                                .Key    = XBoxPadInputMapping[i],
                                .Repeat = false,
                            };

                            if (controller_state.Button[i] != button_states[i])
                            {
                                bool const pressed = button_states[i];

                                if (pressed)
                                {
                                    g_EventHandler->OnControllerButtonPressed(event);

                                    controller_state.RepeatTime[i] = current_time + m_ButtonInitialDelay;
                                }
                                else
                                {
                                    g_EventHandler->OnControllerButtonReleased(event);
                                }
                            }
                            else if (controller_state.Button[i] && controller_state.RepeatTime[i] <= current_time)
                            {
                                event.Repeat = true;

                                g_EventHandler->OnControllerButtonPressed(event);

                                controller_state.RepeatTime[i] = current_time + m_ButtonRepeatDelay;
                            }

                            controller_state.Button[i] = button_states[i];
                        }
                    }
                }
            }

            this->m_NeedsUpdate = true;
        }
    };
}
