#include <Graphyte/Assets.Shader.module.hxx>
#include <Graphyte/AssetsPipeline/ShaderProcessor.hxx>
#include <Graphyte/AssetsPipeline/AssetProcessorFactory.hxx>
#include <Graphyte/Modules.hxx>

namespace Graphyte::AssetsPipeline
{
    class AssetsMeshModule : public IModule
    {
    public:
        virtual ~AssetsMeshModule() noexcept = default;

        virtual void OnInitialize() noexcept override
        {
            AssetProcessorFactory::Get().Register("compile-shader", []() -> std::unique_ptr<IAssetProcessor>
            {
                return std::make_unique<ShaderProcessor>();
            });
        }

        virtual void OnFinalize() noexcept override
        {
            AssetProcessorFactory::Get().Unregister("compile-shader");
        }
    };
}

GX_IMPLEMENT_MODULE(Graphyte::AssetsPipeline::AssetsMeshModule);
