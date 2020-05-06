#include <GxAssetsMesh/Assets.Mesh.module.hxx>
#include <GxAssetsMesh/AssetsPipeline/MeshProcessor.hxx>
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
            AssetProcessorFactory::Get().Register("compile-mesh", []() -> std::unique_ptr<IAssetProcessor>
            {
                return std::make_unique<MeshProcessor>();
            });
        }

        virtual void OnFinalize() noexcept override
        {
            AssetProcessorFactory::Get().Unregister("compile-mesh");
        }
    };
}

GX_IMPLEMENT_MODULE(Graphyte::AssetsPipeline::AssetsMeshModule);
