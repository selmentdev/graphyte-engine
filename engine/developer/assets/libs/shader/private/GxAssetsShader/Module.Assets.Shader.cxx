#include <GxAssetsShader/Assets.Shader.module.hxx>
#include <GxAssetsShader/AssetsPipeline/ShaderProcessor.hxx>
#include <GxAssetsBase/AssetsPipeline/AssetProcessorFactory.hxx>
#include <GxBase/Modules.hxx>

namespace Graphyte::AssetsPipeline
{
    class AssetsMeshModule : public IModule
    {
    public:
        virtual ~AssetsMeshModule() noexcept = default;

        virtual void OnInitialize() noexcept override
        {
            AssetProcessorFactory::Get().Register("compile-shader", []() -> std::unique_ptr<IAssetProcessor> {
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
