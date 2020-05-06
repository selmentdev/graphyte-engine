#pragma once
#include <GxAssetsBase/AssetsPipeline/AssetProcessor.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte::AssetsPipeline
{
    GX_DECLARE_LOG_CATEGORY(LogMeshProcessor, Trace, Trace);

    class MeshProcessor final : public IAssetProcessor
    {
    public:
        MeshProcessor() noexcept;
        virtual ~MeshProcessor() noexcept;

        bool Process(const AssetProcessorRequest& request, AssetProcessorResponse& response) noexcept override;
        bool Process() noexcept override;
    };
}
