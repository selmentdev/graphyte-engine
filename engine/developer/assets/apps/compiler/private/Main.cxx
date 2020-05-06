#include <GxBase/CommandLine.hxx>
#include <GxAssetsBase/AssetsPipeline/AssetProcessorFactory.hxx>
#include <GxBase/Modules.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <GxLaunch/Launch/Main.hxx>

Graphyte::Application::ApplicationDescriptor GraphyteApp
{
    "Graphyte Assets Compiler",
    "assets.compiler",
    "Graphyte",
    Graphyte::Application::ApplicationType::ConsoleTool,
    Graphyte::Version{ 1, 0, 0, 0 }
};

#include <GxBase/Status.hxx>
#include <GxBase/Storage/IFileSystem.hxx>

#include <GxBase/Bitwise.hxx>
#include <GxBase/Network.hxx>

#include <GxBase/Crypto/HashAlgorithm.hxx>
#include <GxBase/System/Process.hxx>
#include <GxBase/System/Library.hxx>
#include <GxBase/Storage/FileManager.hxx>

#include <GxBase/Diagnostics.hxx>

int GraphyteMain([[maybe_unused]] int argc, [[maybe_unused]] char** argv) noexcept
{
    using namespace Graphyte;
    using namespace Graphyte::System;

    ModuleManager::LoadChecked("GxAssetsBase");
    ModuleManager::LoadChecked("GxAssetsMesh");
    ModuleManager::LoadChecked("GxAssetsShader");

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
