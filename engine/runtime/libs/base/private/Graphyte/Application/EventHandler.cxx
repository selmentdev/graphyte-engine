#include "Base.pch.hxx"
#include <Graphyte/Application.hxx>

namespace Graphyte::Application
{
    EventHandler::~EventHandler() noexcept = default;

    bool EventHandler::CanHandleInput(
        [[maybe_unused]] Window& window
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnKeyChar(
        [[maybe_unused]] char32_t character,
        [[maybe_unused]] bool repeat
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnKeyDown(
        [[maybe_unused]] Input::KeyCode key,
        [[maybe_unused]] char32_t character,
        [[maybe_unused]] bool repeat
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnKeyUp(
        [[maybe_unused]] Input::KeyCode key,
        [[maybe_unused]] char32_t character,
        [[maybe_unused]] bool repeat
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnMouseDown(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] Input::MouseButton button,
        [[maybe_unused]] Maths::Float2 position
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnMouseUp(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] Input::MouseButton button,
        [[maybe_unused]] Maths::Float2 position
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnMouseDoubleClick(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] Input::MouseButton button,
        [[maybe_unused]] Maths::Float2 position
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnMouseWheel(
        [[maybe_unused]] float delta,
        [[maybe_unused]] Maths::Float2 position
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnMouseMove() noexcept
    {
        return false;
    }

    bool EventHandler::OnMouseMove(
        [[maybe_unused]] Maths::Float2 position
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnControllerAnalog(
        [[maybe_unused]] Input::GamepadKey key,
        [[maybe_unused]] uint32_t controller,
        [[maybe_unused]] float value
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnControllerButtonPressed(
        [[maybe_unused]] Input::GamepadKey key,
        [[maybe_unused]] uint32_t controller,
        [[maybe_unused]] bool repeat
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnControllerButtonReleased(
        [[maybe_unused]] Input::GamepadKey key,
        [[maybe_unused]] uint32_t controller,
        [[maybe_unused]] bool repeat
    ) noexcept
    {
        return false;
    }

    void EventHandler::OnGestureStart() noexcept
    {
    }

    bool EventHandler::OnGestureTouch(
        [[maybe_unused]] Input::GestureType gesture,
        [[maybe_unused]] Maths::Float2 delta,
        [[maybe_unused]] float wheel_delta,
        [[maybe_unused]] bool inverted
    ) noexcept
    {
        return false;
    }

    void EventHandler::OnGestureEnd() noexcept
    {
    }

    bool EventHandler::OnTouchStarted(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] Maths::Float2 position,
        [[maybe_unused]] Input::TouchIndex touch_index,
        [[maybe_unused]] uint32_t controller
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnTouchMoved(
        [[maybe_unused]] Maths::Float2 location,
        [[maybe_unused]] Input::TouchIndex touch_index,
        [[maybe_unused]] uint32_t controller
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnTouchEnded(
        [[maybe_unused]] Maths::Float2 location,
        [[maybe_unused]] Input::TouchIndex touch_index,
        [[maybe_unused]] uint32_t controller
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnMotion(
        [[maybe_unused]] Maths::Float3 tilt,
        [[maybe_unused]] Maths::Float3 rotation_rate,
        [[maybe_unused]] Maths::Float3 gravity,
        [[maybe_unused]] Maths::Float3 acceleration,
        [[maybe_unused]] uint32_t controller
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnWindowSizeChanged(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] Maths::Float2 size,
        [[maybe_unused]] bool was_minimized
    ) noexcept
    {
        return false;
    }

    void EventHandler::OnWindowPaint(
        [[maybe_unused]] Window& window
    ) noexcept
    {
    }


    WindowLimits EventHandler::GetSizeLimits(
        [[maybe_unused]] Window& window
    ) noexcept
    {
        return {};
    }

    void EventHandler::OnWindowSizing(
        [[maybe_unused]] Window& window
    ) noexcept
    {
    }

    bool EventHandler::OnWindowSizingBegin(
        [[maybe_unused]] Window& window
    ) noexcept
    {
        return false;
    }

    void EventHandler::OnWindowSizingEnd(
        [[maybe_unused]] Window& window
    ) noexcept
    {
    }

    void EventHandler::OnDPIScaleChanged(
        [[maybe_unused]] Window& window
    ) noexcept
    {
    }

    void EventHandler::OnWindowMoved(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] Maths::Float2 position
    ) noexcept
    {
    }

    void EventHandler::OnWindowClose(
        [[maybe_unused]] Window& window
    ) noexcept
    {
    }

    bool EventHandler::OnWindowActivated(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] WindowActivation activation
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnApplicationActivated(
        [[maybe_unused]] bool active
    ) noexcept
    {
        return false;
    }

    bool EventHandler::OnWindowAction(
        [[maybe_unused]] Window& window,
        [[maybe_unused]] WindowAction action
    ) noexcept
    {
        return true;
    }

    void EventHandler::OnPowerSuspend() noexcept
    {
    }

    void EventHandler::OnPowerResume() noexcept
    {
    }

    void EventHandler::OnApplicationShutdown(
        [[maybe_unused]] ShutdownReason reason
    ) noexcept
    {
    }
}
