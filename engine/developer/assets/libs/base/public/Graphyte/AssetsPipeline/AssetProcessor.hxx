#pragma once
#include <Graphyte/Assets.Base.module.hxx>
#include <Graphyte/Uuid.hxx>

namespace Graphyte::AssetsPipeline
{
    struct AssetProcessorRequest
    {
        std::string SourcePath;
        std::string DestinationPath;
        Uuid AssetId;
    };

    struct AssetProcessorResponse
    {
        std::vector<std::string> Log;
        bool Success;
    };

    struct IAssetProcessor// : Serialization::ISerializable
    {
        virtual ~IAssetProcessor() = default;

        virtual bool Process(const AssetProcessorRequest& request, AssetProcessorResponse& response) noexcept = 0;
        virtual bool Process() noexcept = 0;
    };
}
