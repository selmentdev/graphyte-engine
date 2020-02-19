#include <Graphyte/CommandLine.hxx>
#include <Graphyte/AssetsPipeline/AssetProcessorFactory.hxx>
#include <Graphyte/Modules.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <Graphyte/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Graphyte Assets Compiler",
    "assets.compiler",
    "Graphyte",
    Graphyte::Application::ApplicationType::ConsoleTool,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#include <Graphyte/Status.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>

#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Network.hxx>

#include <Graphyte/Crypto/HashAlgorithm.hxx>
#include <Graphyte/System/Process.hxx>
#include <Graphyte/System/Library.hxx>
#include <Graphyte/Storage/FileManager.hxx>

#include <Graphyte/Diagnostics.hxx>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    using namespace Graphyte;
    using namespace Graphyte::System;

    ModuleManager::LoadChecked("com.graphyte.assets.base");
    ModuleManager::LoadChecked("com.graphyte.assets.mesh");
    ModuleManager::LoadChecked("com.graphyte.assets.shader");

    std::string_view value{};
    if (Graphyte::CommandLine::Has("--help"))
    {
        fmt::print("This is assets compiler\n");

    }
    else if (Graphyte::CommandLine::Get("--processor", value))
    {
        if (value.empty())
        {
            fmt::print("List of available processors:\n");
            auto processors = AssetsPipeline::AssetProcessorFactory::Get().GetNames();

            for (auto&& processor : processors)
            {
                fmt::print("  {}\n", processor);
            }
        }
        else
        {
            auto processor = AssetsPipeline::AssetProcessorFactory::Get().ActivateInstance(value);
            if (processor != nullptr)
            {
                if (!processor->Process())
                {
                    fmt::print("Processor failed\n");
                }
            }
            else
            {
                fmt::print("Unknown operation specified: {}\n", value);
            }
        }
    }
    else
    {
        fmt::print("Accepted params are --help or --processor\n");
    }

    return 0;
}
