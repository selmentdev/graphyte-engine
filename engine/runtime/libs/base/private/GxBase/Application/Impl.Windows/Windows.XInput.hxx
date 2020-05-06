#pragma once
#include <GxBase/Application.hxx>

namespace Graphyte::Application::Impl
{
    class WindowsXInputDevice final
    {
    public:
        static const size_t MaxControllers = 4;
        static const size_t MaxButtons = 24;
        
    private:
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

            bool IsConnected;
        };

    private:
        EventHandler* m_Handler;
        std::array<ControllerState, MaxControllers> m_Controllers;
        float m_ButtonRepeatDelay;
        float m_ButtonInitialDelay;
        bool m_NeedsUpdate;

    public:
        WindowsXInputDevice() noexcept;
        ~WindowsXInputDevice() noexcept;

    public:
        void SetEventHandler(
            EventHandler* eventHandler
        ) noexcept
        {
            m_Handler = eventHandler;
        }

    private:
        void ControllerAnalog(
            Input::GamepadKey key,
            uint32_t controller,
            int16_t value,
            float normalized,
            int16_t& previous_value,
            int32_t deadzone
        ) noexcept;

    public:
        void Poll(
            float delta_time
        ) noexcept;
    };
}
