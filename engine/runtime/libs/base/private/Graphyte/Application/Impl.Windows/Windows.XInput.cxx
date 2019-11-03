#include "Base.pch.hxx"
#include "Windows.XInput.hxx"
#include <Graphyte/System.hxx>

#include <Xinput.h>

namespace Graphyte::Application::Impl
{
    static constexpr const Input::GamepadKey XBoxPadInputMapping[] = {
        Input::GamepadKey::FaceButtonBottom,
        Input::GamepadKey::FaceButtonRight,
        Input::GamepadKey::FaceButtonLeft,
        Input::GamepadKey::FaceButtonTop,
        Input::GamepadKey::LeftShoulder,
        Input::GamepadKey::RightShoulder,
        Input::GamepadKey::SpecialRight,
        Input::GamepadKey::SpecialLeft,
        Input::GamepadKey::LeftThumb,
        Input::GamepadKey::RightThumb,
        Input::GamepadKey::LeftTriggerThreshold,
        Input::GamepadKey::RightTriggerThreshold,
        Input::GamepadKey::DPadUp,
        Input::GamepadKey::DPadDown,
        Input::GamepadKey::DPadLeft,
        Input::GamepadKey::DPadRight,
        Input::GamepadKey::LeftStickUp,
        Input::GamepadKey::LeftStickDown,
        Input::GamepadKey::LeftStickLeft,
        Input::GamepadKey::LeftStickRight,
        Input::GamepadKey::RightStickUp,
        Input::GamepadKey::RightStickDown,
        Input::GamepadKey::RightStickLeft,
        Input::GamepadKey::RightStickRight,
    };
    static_assert(std::size(XBoxPadInputMapping) == WindowsXInputDevice::MaxButtons);

    constexpr float NormalizeAnalog(
        int16_t value
    ) noexcept
    {
        float const length = (value <= 0 ? 32768.0F : 32767.0F);
        return static_cast<float>(value) / length;
    }

    WindowsXInputDevice::WindowsXInputDevice() noexcept
        : m_Handler{}
        , m_Controllers{}
        , m_ButtonRepeatDelay{ 0.1F }
        , m_ButtonInitialDelay{ 0.2F }
        , m_NeedsUpdate{ true }
    {
    }

    WindowsXInputDevice::~WindowsXInputDevice() noexcept
    {
    }

    void WindowsXInputDevice::ControllerAnalog(
        Input::GamepadKey key,
        uint32_t controller,
        int16_t value,
        float normalized,
        int16_t& previous_value,
        int32_t deadzone
    ) noexcept
    {
        if (previous_value != value || std::abs(static_cast<int32_t>(value)) > deadzone)
        {
            m_Handler->OnControllerAnalog(
                key,
                controller,
                normalized
            );
        }

        previous_value = value;
    }

    void WindowsXInputDevice::Poll(
        float delta_time
    ) noexcept
    {
        bool connected[MaxControllers];
        XINPUT_STATE input_states[MaxControllers];

        bool is_attached = false;

        for (size_t i = 0; i < MaxControllers; ++i)
        {
            auto& current_state = m_Controllers[i];
            connected[i] = current_state.IsConnected;

            if (current_state.IsConnected || m_NeedsUpdate)
            {
                XINPUT_STATE& state = input_states[i];
                state = {};

                current_state.IsConnected = XInputGetState(static_cast<DWORD>(i), &state) == ERROR_SUCCESS;

                if (current_state.IsConnected)
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
                auto& current_state = m_Controllers[controller];
                bool was_connected = connected[controller];

                if (current_state.IsConnected && was_connected)
                {
                    XINPUT_STATE& state = input_states[controller];

                    bool button_states[MaxButtons];

                    button_states[0] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_A);
                    button_states[1] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_B);
                    button_states[2] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_X);
                    button_states[3] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
                    button_states[4] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
                    button_states[5] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
                    button_states[6] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
                    button_states[7] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_START);
                    button_states[8] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
                    button_states[9] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
                    button_states[10] = 0 != (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
                    button_states[11] = 0 != (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
                    button_states[12] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
                    button_states[13] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
                    button_states[14] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
                    button_states[15] = 0 != (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
                    button_states[16] = 0 != (state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                    button_states[17] = 0 != (state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                    button_states[18] = 0 != (state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                    button_states[19] = 0 != (state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
                    button_states[20] = 0 != (state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
                    button_states[21] = 0 != (state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
                    button_states[22] = 0 != (state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
                    button_states[23] = 0 != (state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);

                    ControllerAnalog(
                        Input::GamepadKey::LeftAnalogX,
                        controller,
                        state.Gamepad.sThumbLX,
                        NormalizeAnalog(state.Gamepad.sThumbLX),
                        current_state.LeftXAnalog,
                        XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
                    );

                    ControllerAnalog(
                        Input::GamepadKey::LeftAnalogY,
                        controller,
                        state.Gamepad.sThumbLY,
                        NormalizeAnalog(state.Gamepad.sThumbLY),
                        current_state.LeftYAnalog,
                        XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
                    );

                    ControllerAnalog(
                        Input::GamepadKey::RightAnalogX,
                        controller,
                        state.Gamepad.sThumbRX,
                        NormalizeAnalog(state.Gamepad.sThumbRX),
                        current_state.RightXAnalog,
                        XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
                    );

                    ControllerAnalog(
                        Input::GamepadKey::RightAnalogY,
                        controller,
                        state.Gamepad.sThumbRY,
                        NormalizeAnalog(state.Gamepad.sThumbRY),
                        current_state.RightYAnalog,
                        XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
                    );

                    ControllerAnalog(
                        Input::GamepadKey::LeftTriggerAnalog,
                        controller,
                        state.Gamepad.bLeftTrigger,
                        static_cast<float>(state.Gamepad.bLeftTrigger) / 255.0F,
                        current_state.LeftTriggerAnalog,
                        XINPUT_GAMEPAD_TRIGGER_THRESHOLD
                    );

                    ControllerAnalog(
                        Input::GamepadKey::RightTriggerAnalog,
                        controller,
                        state.Gamepad.bRightTrigger,
                        static_cast<float>(state.Gamepad.bRightTrigger) / 255.0F,
                        current_state.RightTriggerAnalog,
                        XINPUT_GAMEPAD_TRIGGER_THRESHOLD
                    );

                    for (size_t i = 0; i < MaxButtons; ++i)
                    {
                        if (current_state.Button[i] != button_states[i])
                        {
                            bool const pressed = button_states[i];
                            if (pressed)
                            {
                                m_Handler->OnControllerButtonPressed(
                                    XBoxPadInputMapping[i],
                                    controller,
                                    false
                                );

                                current_state.RepeatTime[i] = current_time + m_ButtonInitialDelay;
                            }
                            else
                            {
                                m_Handler->OnControllerButtonReleased(
                                    XBoxPadInputMapping[i],
                                    controller,
                                    false
                                );
                            }
                        }
                        else if (current_state.Button[i] && current_state.RepeatTime[i] <= current_time)
                        {
                            m_Handler->OnControllerButtonPressed(
                                XBoxPadInputMapping[i],
                                controller,
                                true
                            );

                            current_state.RepeatTime[i] = current_time + m_ButtonRepeatDelay;
                        }

                        current_state.Button[i] = button_states[i];
                    }
                }
            }
        }

        (void)delta_time;
    }
}
