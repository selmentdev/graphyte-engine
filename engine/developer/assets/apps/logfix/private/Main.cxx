#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/CommandLine.hxx>
#include <Graphyte/Modules.hxx>

GX_DECLARE_LOG_CATEGORY(LogFixTool, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogFixTool);

#include <Graphyte/Launch/Main.hxx>

#include <Graphyte/Developer/Elf.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Graphyte Assets Compiler",
    "assets.compiler",
    "Graphyte",
    Graphyte::Application::ApplicationType::ConsoleTool,
    Graphyte::Version{ 1, 0, 0, 0 }
};

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    return 0;
}
