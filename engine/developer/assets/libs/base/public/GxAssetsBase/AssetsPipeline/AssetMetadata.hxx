#pragma once
#include <GxAssetsBase/Assets.Base.module.hxx>
#include <GxBase/DateTime.hxx>
#include <GxBase/Uuid.hxx>

namespace Graphyte::AssetsPipeline
{
    class ASSETS_BASE_API AssetMetadata final// : public Serialization::ISerializable
    {
    public:
        std::string m_License{};
        DateTime m_CreationTime{};
        Uuid m_AssetId{};

    public:
        AssetMetadata() noexcept;
        virtual ~AssetMetadata() noexcept;

    public:
        //bool Serialize(Serialization::Writer::Value& value) noexcept override;
        //bool Deserialize(Serialization::Reader::Value& value) noexcept override;
    };
}
