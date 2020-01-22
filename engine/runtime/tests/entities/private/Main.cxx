#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 120

#include <catch2/catch.hpp>

#include <Graphyte/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Library GxEntities unit test",
    "module.entities.unittest",
    "Graphyte",
    Graphyte::Application::ApplicationType::UnitTest,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#if GRAPHYTE_PLATFORM_WINDOWS
#include <io.h>
#include <fcntl.h>
#endif

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
#if GRAPHYTE_PLATFORM_WINDOWS
    ::_setmode(::_fileno(stdout), _O_TEXT);
#endif

    return Catch::Session().run();
}
