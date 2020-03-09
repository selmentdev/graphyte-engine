#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 120

#include <catch2/catch.hpp>

#include <Graphyte/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Graphyte Engine Unit Test",
    "unittest",
    "Graphyte",
    Graphyte::Application::ApplicationType::UnitTest,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include <io.h>
#include <fcntl.h>
#endif

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
    ::_setmode(::_fileno(stdout), _O_TEXT);
#endif

    return Catch::Session().run();
}

#undef CATCH_CONFIG_RUNNER
