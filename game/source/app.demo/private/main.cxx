#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Threading.hxx>
#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/Storage/FileManager.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <GxBase/App.hxx>

Graphyte::App::ApplicationDescriptor GraphyteApp{
    .Name       = "Graphyte Assets Compiler",
    .Id         = "assets.compiler",
    .Company    = "Graphyte",
    .Type       = Graphyte::App::ApplicationType::Game,
    .AppVersion = Graphyte::Version{ 1, 0, 0, 0 }
};

#include <GxLaunch/Main.hxx>

#include <GxBase/Uuid.hxx>
#include <GxBase/System/Dialogs.hxx>
#include <GxBase/Random.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Plane.hxx>
#include <GxBase/Maths/Quaternion.hxx>
#include <GxBase/Maths/Geometric.hxx>
#include <GxBase/Maths/Color.hxx>
#include <GxBase/Flags.hxx>
#include <GxBase/Stopwatch.hxx>
#include <GxBase/Storage/IFileSystem.hxx>

namespace graphyte::system
{
    class Process final
    {
    private:
        void* m_Handle = nullptr;
        std::string_view m_Name{ "unassigned" };

        Process(void* handle, std::string_view name)
            : m_Handle{ handle }
            , m_Name{ name }
        {
            GX_LOG_TRACE(LogAssetsCompiler, "Process explicit ctor: {}\n", m_Name);
        }

    public:
        Process() noexcept
        {
            GX_LOG_TRACE(LogAssetsCompiler, "Process default ctor: {}\n", m_Name);
        }

        ~Process() noexcept
        {
            GX_LOG_TRACE(LogAssetsCompiler, "Process dtor: {}\n", m_Name);
        }

        Process(Process const&) = delete;
        Process& operator=(Process const&) = delete;

        Process(Process&& other) noexcept
            : m_Handle{ std::exchange(other.m_Handle, nullptr) }
            , m_Name{ std::exchange(other.m_Name, "unassigned") }
        {
            GX_LOG_TRACE(LogAssetsCompiler, "Process move ctor: {}\n", m_Name);
        }

        Process& operator=(Process&& other) noexcept
        {
            // cleanup this instance
            std::swap(this->m_Handle, other.m_Handle);
            this->m_Name = std::exchange(other.m_Name, "unassigned");

            GX_LOG_TRACE(LogAssetsCompiler, "Process move op: {}\n", m_Name);
            return (*this);
        }

        static Process Create(std::string_view path) noexcept
        {
            return Process(reinterpret_cast<void*>(INVALID_HANDLE_VALUE), path);
        }

        bool Wait() noexcept
        {
            GX_ASSERT(this->m_Handle == reinterpret_cast<void*>(INVALID_HANDLE_VALUE));
        }
    };
}

class EventHandler : public Graphyte::App::IEventHandler
{
public:
    Graphyte::App::Window* m_Window{};

public:
    virtual void OnKeyDown(Graphyte::App::KeyEvent const& event) noexcept override
    {
        if (event.Key == Graphyte::App::KeyCode::F1)
        {
            Graphyte::App::SetMode(*this->m_Window, Graphyte::App::WindowMode::Fullscreen);
        }
        else if (event.Key == Graphyte::App::KeyCode::F2)
        {
            Graphyte::App::SetMode(*this->m_Window, Graphyte::App::WindowMode::Windowed);
        }
        else if (event.Key == Graphyte::App::KeyCode::F3)
        {
            Graphyte::App::SetMode(*this->m_Window, Graphyte::App::WindowMode::WindowedFullscreen);
        }
    }
    virtual void OnControllerButtonPressed(Graphyte::App::GamepadButtonEvent const& event) noexcept override
    {
        if (event.Key == Graphyte::App::GamepadKey::DPadLeft)
        {
            Graphyte::App::SetMode(*this->m_Window, Graphyte::App::WindowMode::Fullscreen);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadUp)
        {
            Graphyte::App::SetMode(*this->m_Window, Graphyte::App::WindowMode::Windowed);
        }
        else if (event.Key == Graphyte::App::GamepadKey::DPadRight)
        {
            Graphyte::App::SetMode(*this->m_Window, Graphyte::App::WindowMode::WindowedFullscreen);
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

    auto window = Graphyte::App::Create(Graphyte::App::WindowType::Game);

    e.m_Window = window;

    Graphyte::App::SetMode(*window, Graphyte::App::WindowMode::WindowedFullscreen);
    Graphyte::App::SetCaption(*window, "Game");

    std::vector<std::string> paths{};

    if (Graphyte::Storage::IFileSystem::GetPlatformNative().FindFilesRecursive(paths, Graphyte::Storage::GetEngineDirectory(), ".hxx") == Graphyte::Status::Success)
    {
        for (auto const& path : paths)
        {
            GX_LOG_TRACE(LogAssetsCompiler, "Path: {}\n", path);
        }
    }

    Graphyte::Diagnostics::Stopwatch sw{};
    sw.Start();

    while (!Graphyte::App::IsRequestingExit())
    {
        Graphyte::Threading::SleepThread(16);
        Graphyte::App::Tick(0.016f);

        sw.Stop();
        double const elapsed = sw.GetElapsedTime<double>() * 1000.0;
        Graphyte::App::SetCaption(*window, fmt::format("Frame: {:.18}", elapsed));
        sw.Restart();
    }

    Graphyte::App::Destroy(window);

    return 0;
}
