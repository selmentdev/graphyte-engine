#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 120

#include <catch2/catch.hpp>

#include <GxLaunch/Launch/Main.hxx>

Graphyte::App::ApplicationDescriptor GraphyteApp{
    .Name       = "Graphyte Engine Unit Test",
    .Id         = "unittest",
    .Company    = "Graphyte",
    .Type       = Graphyte::App::ApplicationType::UnitTest,
    .AppVersion = Graphyte::Version{ 1, 0, 0, 0 }
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
