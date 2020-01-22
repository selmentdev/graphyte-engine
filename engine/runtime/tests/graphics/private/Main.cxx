#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 120

#include <catch2/catch.hpp>

#include <Graphyte/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Library GxGraphics unit test",
    "module.graphics.unittest",
    "Graphyte",
    Graphyte::Application::ApplicationType::UnitTest,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#if GRAPHYTE_PLATFORM_WINDOWS
#include <io.h>
#include <fcntl.h>
#endif

int GraphyteMain(int argc, char** argv) noexcept
{
#if GRAPHYTE_PLATFORM_WINDOWS
    [[maybe_unused]] auto previous_mode = ::_setmode(::_fileno(stdout), _O_TEXT);
#endif
    Catch::Session session{};
    bool chuj{};
    auto cli = session.cli() | Catch::clara::Opt(chuj)["--force-no-log"];
    session.cli(cli);

    if (int result = session.applyCommandLine(argc, argv); result != 0)
    {
        return result;
    }


    return session.run();
}
