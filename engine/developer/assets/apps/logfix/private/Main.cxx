#include <GxBase/Diagnostics.hxx>
#include <GxBase/CommandLine.hxx>
#include <GxBase/Modules.hxx>
#include <GxBase/System/Process.hxx>

GX_DECLARE_LOG_CATEGORY(LogFixTool, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogFixTool);

#include <GxLaunch/Launch/Main.hxx>

#include <Graphyte/Developer/Elf.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp{
    "Graphyte Assets Compiler",
    "assets.compiler",
    "Graphyte",
    Graphyte::Application::ApplicationType::ConsoleTool,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#include <stdio.h>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    std::string err{ "" };
    std::string out{ "" };
    Graphyte::System::Process::Execute(
        "c:/windows/system32/notepad.exe",
        nullptr,
        nullptr,
        &out,
        &err);
    return 0;
}
