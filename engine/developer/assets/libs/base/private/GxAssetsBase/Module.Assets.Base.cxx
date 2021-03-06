#include <GxAssetsBase/Assets.Base.module.hxx>
#include <GxBase/Modules.hxx>

namespace Graphyte::AssetsPipeline
{
    class AssetsBaseModule : public IModule
    {
    public:
        virtual ~AssetsBaseModule() noexcept = default;

        virtual void OnInitialize() noexcept override
        {
        }

        virtual void OnFinalize() noexcept override
        {
        }
    };
}

GX_IMPLEMENT_MODULE(Graphyte::AssetsPipeline::AssetsBaseModule);
