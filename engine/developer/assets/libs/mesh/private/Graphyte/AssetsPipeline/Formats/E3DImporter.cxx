#include "E3DImporter.hxx"
#include <Graphyte/AssetsPipeline/MeshProcessor.hxx>
#include <Graphyte/Maths.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::AssetsPipeline::Meshes
{
    bool E3DImporter::Load(Storage::Archive& archive, Geometry::Model& model) noexcept
    {
        ChunkHeader fileHeader{};
        archive.Serialize(&fileHeader, sizeof(fileHeader));
        GX_ASSERT(fileHeader.Id == Chunks::E3D0);

        std::vector<Submodel> submodels{};
        std::vector<std::string> materials{};
        std::vector<std::string> submodel_names{};
        std::vector<Vertex> vertices{};
        std::vector<Maths::Float4x4> matrices{};

        while (archive.GetPosition() <= archive.GetSize())
        {
            int64_t current = archive.GetPosition();

            ChunkHeader chunkHeader{};
            archive.Serialize(&chunkHeader, sizeof(chunkHeader));

            switch (chunkHeader.Id)
            {
            case Chunks::SUB0:
                {
                    GX_LOG(LogMeshProcessor, Info, "Submodel: {:c}{:c}{:c}{:c} {}\n",
                        chunkHeader.FourCC[0],
                        chunkHeader.FourCC[1],
                        chunkHeader.FourCC[2],
                        chunkHeader.FourCC[3],
                        static_cast<size_t>(chunkHeader.Size));

                    Submodel submodel{};
                    int64_t payloadSize = chunkHeader.Size - sizeof(chunkHeader);
                    size_t count = static_cast<size_t>(payloadSize) / sizeof(submodel);
                    GX_ASSERT((static_cast<size_t>(payloadSize) % sizeof(submodel)) == 0);


                    GX_LOG(LogMeshProcessor, Info, "Submodels: count = {}\n", count);

                    for (size_t i = 0; i < count; ++i)
                    {
                        archive.Serialize(&submodel, sizeof(submodel));
                        submodels.push_back(submodel);

                        GX_LOG(LogMeshProcessor, Info, "- submodel:   {}\n", i);
                        GX_LOG(LogMeshProcessor, Info, "  - texture:  {}\n", submodel.TextureIndex);
                        GX_LOG(LogMeshProcessor, Info, "  - type:     {}\n", static_cast<uint32_t>(submodel.Type));
                        GX_LOG(LogMeshProcessor, Info, "  - vertices: [{}:{})\n", submodel.FirstVertexIndex, submodel.VerticesCount);
                        GX_LOG(LogMeshProcessor, Info, "  - name:     {}\n", submodel.NameIndex);
                    }

                    break;
                }
            case Chunks::TRA0:
                {
                    GX_LOG(LogMeshProcessor, Info, "Transform Matrices: Float4x4A\n");
                    size_t count = static_cast<size_t>((chunkHeader.Size - sizeof(chunkHeader)) / sizeof(Maths::Float4x4));

                    for (size_t i = 0; i < count; ++i)
                    {
                        Maths::Float4x4 matrix{};
                        archive.Serialize(&matrix, sizeof(matrix));
                        matrices.push_back(matrix);
                    }
                    break;
                }
            case Chunks::TRA1:
                {
                    GX_LOG(LogMeshProcessor, Info, "Transform Matrices: double4x4\n");
                    break;
                }
            case Chunks::TEX0:
                {
                    GX_LOG(LogMeshProcessor, Info, "Materials\n");
                    std::string buffer{};

                    size_t bytes = chunkHeader.Size - sizeof(chunkHeader);

                    for (size_t i = 0; i < bytes; ++i)
                    {
                        char ch;
                        archive.Serialize(&ch, sizeof(ch));

                        if (ch == '\0')
                        {
                            materials.push_back(buffer);
                            buffer.clear();
                        }
                        else
                        {
                            buffer.push_back(ch);
                        }
                    }

                    for (size_t i = 0; i < materials.size(); ++i)
                    {
                        GX_LOG(LogMeshProcessor, Info, "- {}: `{}`\n", i, materials[i]);
                    }

                    break;
                }
            case Chunks::NAM0:
                {
                    GX_LOG(LogMeshProcessor, Info, "Submodel names\n");
                    std::string buffer{};

                    size_t bytes = chunkHeader.Size - sizeof(chunkHeader);

                    for (size_t i = 0; i < bytes; ++i)
                    {
                        char ch;
                        archive.Serialize(&ch, sizeof(ch));

                        if (ch == '\0')
                        {
                            submodel_names.push_back(buffer);
                            buffer.clear();
                        }
                        else
                        {
                            buffer.push_back(ch);
                        }
                    }

                    for (size_t i = 0; i < submodel_names.size(); ++i)
                    {
                        GX_LOG(LogMeshProcessor, Info, "- {}: `{}`\n", i, submodel_names[i]);
                    }

                    break;
                }
            case Chunks::VNT0:
                {
                    GX_LOG(LogMeshProcessor, Info, "Vertices\n");
                    int64_t payloadSize = chunkHeader.Size - sizeof(chunkHeader);
                    size_t count = static_cast<size_t>(payloadSize) / sizeof(Vertex);
                    GX_ASSERT((static_cast<size_t>(payloadSize) % sizeof(Vertex)) == 0);

                    Vertex vertex{};
                    for (size_t i = 0; i < count; ++i)
                    {
                        archive.Serialize(&vertex, sizeof(Vertex));
                        vertices.push_back(vertex);
                    }
                    break;
                }
            case Chunks::SUB1:
            default:
            case Chunks::E3D0:
                {
                    GX_LOG(LogMeshProcessor, Error, "Unknown chunk: {:c}{:c}{:c}{:c} {}\n",
                        chunkHeader.FourCC[0],
                        chunkHeader.FourCC[1],
                        chunkHeader.FourCC[2],
                        chunkHeader.FourCC[3],
                        static_cast<size_t>(chunkHeader.Size));
                    break;
                }
            }

            int64_t nextPosition = current + chunkHeader.Size;

            if (nextPosition < archive.GetSize())
            {
                archive.SetPosition(nextPosition);
            }
            else
            {
                GX_ASSERT(nextPosition == fileHeader.Size);
                break;
            }
        }

        for (auto& submesh : submodels)
        {
            auto* part = new Geometry::ModelPart{};
            part->MeshData = new Geometry::Mesh{};
            {
                if (submesh.ViewMatrixIndex >= 0)
                {
                    Maths::Store(&part->LocalTransform, Maths::Load<Maths::Matrix>(&matrices[static_cast<size_t>(submesh.ViewMatrixIndex)]));
                }
                else
                {
                    Maths::Store(&part->LocalTransform, Maths::Identity<Maths::Matrix>());
                }

                Maths::Store(&part->BoneTransform, Maths::Identity<Maths::Matrix>());

                if (submesh.NameIndex >= 0)
                {
                    part->Name = submodel_names[static_cast<size_t>(submesh.NameIndex)];
                }

                if (submesh.Type == SubmodelType::Triangles)
                {
                    part->Type = Geometry::ModelPartType::Mesh;
                    part->HelperSize = {};
                    part->HelperType = Geometry::ModelHelperType::None;
                    
                    size_t base_index = static_cast<size_t>(submesh.FirstVertexIndex);
                    size_t count = static_cast<size_t>(submesh.VerticesCount);

                    part->MeshData->VertexPositions.reserve(count);
                    part->MeshData->WedgeIndices.reserve(count);
                    part->MeshData->WedgeTangentZ.reserve(count);
                    part->MeshData->WedgeTextureCoords[0].reserve(count);

                    for (size_t i = 0; i < count; ++i)
                    {
                        const auto& vertex = vertices[base_index + i];

                        part->MeshData->VertexPositions.push_back(vertex.Position);
                        part->MeshData->WedgeIndices.push_back(static_cast<uint32_t>(i));
                        part->MeshData->WedgeTangentZ.push_back(vertex.Normal);
                        part->MeshData->WedgeTextureCoords[0].push_back(vertex.Texcoord);
                    }

                    GX_ASSERT(part->MeshData->IsValid());
                }
                else
                {
                    part->Type = Geometry::ModelPartType::None;
                }
            }

            model.Parts.push_back(part);
        }

        (void)archive;
        return true;
    }
}
