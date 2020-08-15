#include <GxBase/App.hxx>

namespace Graphyte::App::Impl
{
    IEventHandler* g_EventHandler;
}

namespace Graphyte::App
{
    IEventHandler::~IEventHandler() noexcept = default;

    void IEventHandler::OnKeyChar(Graphyte::App::CharEvent const& event) noexcept
    {
        (void)event;
    }

    void IEventHandler::OnKeyDown(Graphyte::App::KeyEvent const& event) noexcept
    {
        (void)event;
    }
    void IEventHandler::OnKeyUp(Graphyte::App::KeyEvent const& event) noexcept
    {
        (void)event;
    }

    void IEventHandler::OnMouseDown(Graphyte::App::Window& window, Graphyte::App::MouseButtonEvent const& event) noexcept
    {
        (void)window;
        (void)event;
    }
    void IEventHandler::OnMouseUp(Graphyte::App::Window& window, Graphyte::App::MouseButtonEvent const& event) noexcept
    {
        (void)window;
        (void)event;
    }
    void IEventHandler::OnMouseDoubleClick(Graphyte::App::Window& window, Graphyte::App::MouseButtonEvent const& event) noexcept
    {
        (void)window;
        (void)event;
    }
    void IEventHandler::OnMouseWheel(Graphyte::App::MouseWheelEvent const& event) noexcept
    {
        (void)event;
    }
    void IEventHandler::OnMouseMove() noexcept
    {
    }
    void IEventHandler::OnMouseMove(Graphyte::App::MouseMoveEvent const& event) noexcept
    {
        (void)event;
    }

    void IEventHandler::OnControllerAnalog(Graphyte::App::GamepadAnalogEvent const& event) noexcept
    {
        (void)event;
    }
    void IEventHandler::OnControllerButtonPressed(Graphyte::App::GamepadButtonEvent const& event) noexcept
    {
        (void)event;
    }
    void IEventHandler::OnControllerButtonReleased(Graphyte::App::GamepadButtonEvent const& event) noexcept
    {
        (void)event;
    }

    void IEventHandler::OnWindowSizeChanged(Graphyte::App::Window& window, Graphyte::Float2 size, bool minimized) noexcept
    {
        (void)window;
        (void)size;
        (void)minimized;
    }
    void IEventHandler::OnWindowSizingBegin(Graphyte::App::Window& window) noexcept
    {
        (void)window;
    }
    void IEventHandler::OnWindowSizingEnd(Graphyte::App::Window& window) noexcept
    {
        (void)window;
    }
    void IEventHandler::OnWindowDpiChanged(Graphyte::App::Window& window) noexcept
    {
        (void)window;
    }
    void IEventHandler::OnWindowMoved(Graphyte::App::Window& window, Graphyte::Float2 position) noexcept
    {
        (void)window;
        (void)position;
    }
    void IEventHandler::OnWindowClose(Graphyte::App::Window& window) noexcept
    {
        (void)window;
    }
    void IEventHandler::OnWindowActivate(Graphyte::App::Window& window, Graphyte::App::WindowActivation activation) noexcept
    {
        (void)window;
        (void)activation;
    }

    void IEventHandler::OnApplicationActivated(bool active) noexcept
    {
        (void)active;
    }
    void IEventHandler::OnSystemPowerShutdown(Graphyte::App::ShutdownReason reason) noexcept
    {
        (void)reason;
    }

    void IEventHandler::OnSystemPowerSuspend() noexcept
    {
    }
    void IEventHandler::OnSystemPowerRestore() noexcept
    {
    }
}

namespace Graphyte::App
{
    void SetEventHandler(IEventHandler* eventHandler) noexcept
    {
        Impl::g_EventHandler = eventHandler;
    }
}
