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
#include <GxBase/Stopwatch.hxx>

class EventHandler : public Graphyte::App::IEventHandler
{
public:
    Graphyte::App::Window* m_Window;

public:
    virtual void OnKeyDown(Graphyte::App::KeyEvent const& event) noexcept override
    {
        if (event.Key == Graphyte::App::KeyCode::F1)
        {
            this->m_Window->SetMode(Graphyte::App::WindowMode::Fullscreen);
        }
        else if (event.Key == Graphyte::App::KeyCode::F2)
        {
            this->m_Window->SetMode(Graphyte::App::WindowMode::Windowed);
        }
        else if (event.Key == Graphyte::App::KeyCode::F3)
        {
            this->m_Window->SetMode(Graphyte::App::WindowMode::WindowedFullscreen);
        }
    }
    virtual void OnControllerButtonPressed(Graphyte::App::GamepadButtonEvent const& event) noexcept override
    {
        if (event.Key == Graphyte::App::GamepadKey::DPadLeft)
        {
            this->m_Window->SetMode(Graphyte::App::WindowMode::Fullscreen);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadUp)
        {
            this->m_Window->SetMode(Graphyte::App::WindowMode::Windowed);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadRight)
        {
            this->m_Window->SetMode(Graphyte::App::WindowMode::WindowedFullscreen);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadDown)
        {
            Graphyte::App::RequestExit();
        }
    }
    virtual void OnWindowClose(Graphyte::App::Window& window) noexcept override
    {
        (void)window;
        Graphyte::App::RequestExit();
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

    auto window = Graphyte::App::MakeWindow(Graphyte::App::WindowType::Game);

    e.m_Window = window;

    window->SetMode(Graphyte::App::WindowMode::WindowedFullscreen);
    window->SetCaption("Game");
    window->SetSizeLimits(Graphyte::App::WindowSizeLimits{
        .Min = std::nullopt,
        .Max = Graphyte::System::Size{ 1024, 768 },
    });

    Graphyte::Diagnostics::Stopwatch sw{};
    sw.Start();

    while (!Graphyte::App::IsRequestingExit())
    {
        Graphyte::Threading::SleepThread(16);
        Graphyte::App::Tick(0.016f);
        double const elapsed = sw.GetElapsedTime<double>();
        window->SetCaption(fmt::format("Frame: {:.18}", elapsed));
        sw.Restart();
    }

    Graphyte::App::DestroyWindow(window);

    return 0;
}
