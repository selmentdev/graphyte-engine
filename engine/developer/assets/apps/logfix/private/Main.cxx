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

#include <stdio.h>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    FILE* f = fopen(argv[1], "r");
    Graphyte::Developer::Elf::ElfImageHeader64 header{};
    fread(&header, sizeof(header), 1, f);
    fclose(f);
    return 0;
}
