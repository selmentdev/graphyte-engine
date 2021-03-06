#include <GxBase/CommandLine.hxx>
#include <GxAssetsBase/AssetsPipeline/AssetProcessorFactory.hxx>
#include <GxBase/Modules.hxx>

GX_DECLARE_LOG_CATEGORY(LogAssetsCompiler, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogAssetsCompiler);

#include <GxBase/App.hxx>

Graphyte::App::ApplicationDescriptor GraphyteApp{
    .Name       = "Graphyte Assets Compiler",
    .Id         = "assets.compiler",
    .Company    = "Graphyte",
    .Type       = Graphyte::App::ApplicationType::ConsoleTool,
    .AppVersion = Graphyte::Version{ 1, 0, 0, 0 },
};

#include <GxLaunch/Main.hxx>

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

    (void)ModuleManager::LoadChecked("GxAssetsBase");
    (void)ModuleManager::LoadChecked("GxAssetsMesh");
    (void)ModuleManager::LoadChecked("GxAssetsShader");

    if (Graphyte::CommandLine::Get("--help").has_value())
    {
        fmt::print("This is assets compiler\n");
    }
    else if (auto processor = Graphyte::CommandLine::Get("--processor"); processor.has_value())
    {
        std::string_view value = processor.value();

        if (value.empty())
        {
            fmt::print("List of available processors:\n");
            auto processors = AssetsPipeline::AssetProcessorFactory::Get().GetNames();

            for (auto&& current : processors)
            {
                fmt::print("  {}\n", current);
            }
        }
        else
        {
            auto instance = AssetsPipeline::AssetProcessorFactory::Get().ActivateInstance(value);
            if (instance != nullptr)
            {
                if (!instance->Process())
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
