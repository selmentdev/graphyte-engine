#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Threading.hxx>
#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/Storage/FileManager.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <GxLaunch/Launch/Main.hxx>

Graphyte::App::ApplicationDescriptor GraphyteApp{
    .Name       = "Graphyte Assets Compiler",
    .Id         = "assets.compiler",
    .Company    = "Graphyte",
    .Type       = Graphyte::App::ApplicationType::ConsoleTool,
    .AppVersion = Graphyte::Version{ 1, 0, 0, 0 }
};

#include <GxBase/Uuid.hxx>
#include <GxBase/System/Dialogs.hxx>
#include <GxBase/Random.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Plane.hxx>
#include <GxBase/Maths/Quaternion.hxx>
#include <GxBase/Maths/Geometric.hxx>
#include <GxBase/Maths/Color.hxx>
#include <GxBase/App.hxx>
#include <GxBase/Flags.hxx>

class EventHandler : public Graphyte::App::IEventHandler
{
public:
    Graphyte::App::Window* m_Window;

public:
    virtual void OnKeyChar(Graphyte::App::CharEvent const& event) noexcept override
    {
        (void)event;
    }

    virtual void OnKeyDown(Graphyte::App::KeyEvent const& event) noexcept override
    {
        if (event.Key == Graphyte::App::KeyCode::F1)
        {
            this->m_Window->SetWindowMode(Graphyte::App::WindowMode::Fullscreen);
        }
        else if (event.Key == Graphyte::App::KeyCode::F2)
        {
            this->m_Window->SetWindowMode(Graphyte::App::WindowMode::Windowed);
        }
        else if (event.Key == Graphyte::App::KeyCode::F3)
        {
            this->m_Window->SetWindowMode(Graphyte::App::WindowMode::WindowedFullscreen);
        }

        (void)event;
    }
    virtual void OnKeyUp(Graphyte::App::KeyEvent const& event) noexcept override
    {
        (void)event;
    }

    virtual void OnMouseDown(Graphyte::App::Window& window, Graphyte::App::MouseButtonEvent const& event) noexcept override
    {
        (void)window;
        (void)event;
    }
    virtual void OnMouseUp(Graphyte::App::Window& window, Graphyte::App::MouseButtonEvent const& event) noexcept override
    {
        (void)window;
        (void)event;
    }
    virtual void OnMouseDoubleClick(Graphyte::App::Window& window, Graphyte::App::MouseButtonEvent const& event) noexcept override
    {
        (void)window;
        (void)event;
    }
    virtual void OnMouseWheel(Graphyte::App::MouseWheelEvent const& event) noexcept override
    {
        (void)event;
    }
    virtual void OnMouseMove() noexcept override
    {
    }
    virtual void OnMouseMove(Graphyte::App::MouseMoveEvent const& event) noexcept override
    {
        (void)event;
    }

    virtual void OnControllerAnalog(Graphyte::App::GamepadAnalogEvent const& event) noexcept override
    {
        (void)event;
    }
    virtual void OnControllerButtonPressed(Graphyte::App::GamepadButtonEvent const& event) noexcept override
    {
        if (event.Key == Graphyte::App::GamepadKey::DPadLeft)
        {
            this->m_Window->SetWindowMode(Graphyte::App::WindowMode::Fullscreen);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadUp)
        {
            this->m_Window->SetWindowMode(Graphyte::App::WindowMode::Windowed);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadRight)
        {
            this->m_Window->SetWindowMode(Graphyte::App::WindowMode::WindowedFullscreen);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadDown)
        {
            Graphyte::App::RequestExit(true);
        }
    }
    virtual void OnControllerButtonReleased(Graphyte::App::GamepadButtonEvent const& event) noexcept override
    {
        (void)event;
    }

    virtual void OnWindowSizeChanged(Graphyte::App::Window& window, Graphyte::Float2 size, bool minimized) noexcept override
    {
        (void)window;
        (void)size;
        (void)minimized;
    }
    virtual void OnWindowPaint(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
    }
    virtual void OnWindowSizeLimits(Graphyte::App::Window& window, Graphyte::App::WindowLimits& limits) noexcept override
    {
        (void)window;
        (void)limits;
    }
    virtual void OnWindowSizing(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
    }
    virtual void OnWindowSizingBegin(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
    }
    virtual void OnWindowSizingEnd(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
    }
    virtual void OnWindowDpiChanged(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
    }
    virtual void OnWindowMoved(Graphyte::App::Window& window, Graphyte::Float2 position) noexcept override
    {
        (void)window;
        (void)position;
    }
    virtual void OnWindowClose(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
        Graphyte::App::RequestExit(false);
    }
    virtual void OnWindowActivate(Graphyte::App::Window& window, Graphyte::App::WindowActivation activation) noexcept override
    {
        (void)window;
        (void)activation;
    }

    virtual void OnApplicationActivated(bool active) noexcept override
    {
        (void)active;
    }
    virtual void OnApplicationShutdown(Graphyte::App::ShutdownReason reason) noexcept override
    {
        (void)reason;
    }

    virtual void OnSystemPowerSuspend() noexcept override
    {
    }
    virtual void OnSystemPowerRestore() noexcept override
    {
    }
};

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    using namespace Graphyte::Maths;
    auto const v0 = Make<Quaternion>(1.0f, 2.0f, 3.0f, 4.0f);
    auto const q0 = Make<Quaternion>(1.0f, 0.0f, 0.0f, 5.0f);
    auto const l0 = Length(Multiply(q0, v0));

    EventHandler e{};
    Graphyte::App::SetEventHandler(&e);

    auto window = Graphyte::App::MakeWindow(Graphyte::App::WindowDescriptor{
        .SizeLimits = {},
        .Title      = "Hello",
        .Position   = {
            100,
            100,
        },
        .Size = {
            1280,
            720,
        },
        //.Mode         = Graphyte::App::WindowMode::Windowed,
        .Mode         = Graphyte::App::WindowMode::WindowedFullscreen,
        .SystemBorder = true,
        .CloseButton  = true,
        .Regular      = true,
        .Resizable    = true,
    });

    e.m_Window = window;

    window->Show();

    while (!Graphyte::App::IsRequestingExit())
    {
        Graphyte::Threading::SleepThread(16);
        Graphyte::App::Tick(0.016f);
    }

    Graphyte::App::DestroyWindow(window);


    return 0;
}
