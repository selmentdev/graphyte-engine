#include <Graphyte/Geometry/Model.hxx>
#include <Graphyte/Storage/BinaryFormat.hxx>

namespace Graphyte::Geometry
{
    namespace Impl
    {
        constexpr Storage::BinarySignature ModelFileSignature{ 0x1032'0402'1020'1ace };
        constexpr Storage::BinaryFormatVersion ModelFileVersion{ 1, 0 };
        constexpr uint64_t MaxPartsCount = 2048;
    }

    Model::Model() noexcept
    {
    }

    Model::~Model() noexcept
    {
        for (auto* part : Parts)
        {
            delete part->MeshData;
            delete part;
        }
    }

    std::vector<ModelPart*> Model::FindChildren(ModelPart* parentPart) const noexcept
    {
        std::vector<ModelPart*> result{};

        for (auto* part : Parts)
        {
            if (part->Parent == parentPart)
            {
                result.push_back(part);
            }
        }

        return result;
    }

    Matrix Model::ComputeWorldMatrix([[maybe_unused]] ModelPart* part) const noexcept
    {
        Matrix result = Maths::Identity<Matrix>();
        
        while (part != nullptr)
        {
            auto const local = Maths::Load<Matrix>(&part->LocalTransform);
            result = Maths::MultiplyTranspose(result, local);
            part = part->Parent;
        }
        
        result = Maths::Transpose(result);
        return result;
        return {};
    }

    GEOMETRY_API Storage::Archive& operator<< (Storage::Archive& archive, Model& model) noexcept
    {
        Storage::BinaryFormatHeader header{};
        header.Signature = Impl::ModelFileSignature;
        header.Version = Impl::ModelFileVersion;
        header.Encoding = ByteEncoding::LittleEndian;
        header.CustomFlags = {};
        header.FileSize = {};
        header.OffsetToFirstBlock = {};

        archive << header;

        uint64_t parts_count{ static_cast<uint64_t>(model.Parts.size()) };

        archive << parts_count;

        if (archive.IsLoading())
        {
            //
            // Validate file header.
            //
            GX_ASSERT(header.Signature == Impl::ModelFileSignature);
            GX_ASSERT(header.Version == Impl::ModelFileVersion);
            GX_ASSERT(header.Encoding == ByteEncoding::LittleEndian);
            GX_ASSERT(header.CustomFlags == 0);
            GX_ASSERT(header.FileSize == 0);
            GX_ASSERT(header.OffsetToFirstBlock == 0);

            GX_ASSERT(parts_count < Impl::MaxPartsCount);

            //
            // Load model part metadata.
            //

            for (size_t i = 0; i < static_cast<size_t>(parts_count); ++i)
            {
                // XXX: This code assumes that parent part is loaded before currently loaded one.
                uint32_t parent_index{ ~0U };
                archive << parent_index;
                GX_ASSERT((parent_index == ~static_cast<uint32_t>(0)) || parent_index < parts_count);

                auto* part = new ModelPart{};

                if (parent_index == uint32_t{ ~0U })
                {
                    part->Parent = nullptr;
                }
                else
                {
                    part->Parent = model.Parts[parent_index];
                }

                archive << part->Type;
                archive << part->Flags;
                archive << part->LodCount;
                archive << part->ChildrenCount;
                archive << part->HelperType;
                archive << part->HelperSize;
                archive << part->Name;
                archive << part->LocalTransform;
                archive << part->BoneTransform;

                part->MeshData = new Mesh{};

                GX_ASSERT(part->LodCount == 0);

                model.Parts.push_back(part);
            }

            GX_ASSERT(model.Parts.size() == parts_count);
        }
        else
        {
            //
            // Save model part metadata.
            //
            for (size_t i = 0; i < model.Parts.size(); ++i)
            {
                auto* part = model.Parts[i];
                GX_ASSERT(part != nullptr);

                //
                // Determine index of parent model part.
                //
                auto parent = std::find(model.Parts.begin(), model.Parts.end(), part->Parent);

                uint32_t parent_index{ ~0U };
                if (parent != model.Parts.end())
                {
                    parent_index = static_cast<uint32_t>(std::distance(model.Parts.begin(), parent));
                }

                archive << parent_index;
                archive << part->Type;
                archive << part->Flags;
                archive << part->LodCount;
                archive << part->ChildrenCount;
                archive << part->HelperType;
                archive << part->HelperSize;
                archive << part->Name;
                archive << part->LocalTransform;
                archive << part->BoneTransform;
            }
        }


        //
        // Process meshes.
        //

        for (size_t i = 0; i < static_cast<size_t>(parts_count); ++i)
        {
            auto* part = model.Parts[i];
            bool const contains_mesh =
                part->Type == ModelPartType::Hull ||
                part->Type == ModelPartType::Mesh;

            bool const helper_mesh =
                part->Type == ModelPartType::Helper &&
                part->HelperType == ModelHelperType::Mesh;

            if (contains_mesh || helper_mesh)
            {
                archive << *part->MeshData;
            }
        }

        return archive;
    }
}
