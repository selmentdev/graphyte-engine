#include <GxAssetsMesh/AssetsPipeline/MeshProcessor.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/ArchiveMemoryReader.hxx>
#include <GxGeometry/Geometry/Model.hxx>
#include "Formats/E3DImporter.hxx"

namespace Graphyte::AssetsPipeline
{
    GX_DEFINE_LOG_CATEGORY(LogMeshProcessor);

    MeshProcessor::MeshProcessor() noexcept
    {
    }

    MeshProcessor::~MeshProcessor() noexcept
    {
    }

    bool MeshProcessor::Process([[maybe_unused]] const AssetProcessorRequest& request, [[maybe_unused]] AssetProcessorResponse& response) noexcept
    {
        return false;
    }

    bool MeshProcessor::Process() noexcept
    {
        auto mesh = std::make_unique<Graphyte::Geometry::Model>();

        auto path = Graphyte::Storage::GetProjectContentDirectory();
        Graphyte::Storage::AppendPath(path, "models/201e.e3d");

        std::vector<std::byte> content{};

        if (Graphyte::Storage::ReadBinary(content, path) == Status::Success)
        {
            Graphyte::Storage::ArchiveMemoryReader reader{ content };
            Meshes::E3DImporter importer{};
            Geometry::Model model{};
            //std::vector<Geometry::Mesh> meshes{};

            if (importer.Load(reader, model))
            {
                GX_LOG(LogMeshProcessor, Info, "Loaded successfully\n");
            }
            else
            {
                GX_LOG(LogMeshProcessor, Error, "Failed to parse `{}`\n", path);
            }

            auto destination = Graphyte::Storage::GetProjectContentDirectory();
            Graphyte::Storage::AppendPath(destination, "models/111a28.mesh");
            {
                std::unique_ptr<Graphyte::Storage::Archive> writer{};
                if (Graphyte::Storage::CreateWriter(writer, destination) == Status::Success)
                {
                    *writer << model;
                }
            }
            if constexpr (false)
            {
                Geometry::Model model2{};

                std::unique_ptr<Graphyte::Storage::Archive> reader2{};
                if (Graphyte::Storage::CreateReader(reader2, destination) == Status::Success)
                {
                    *reader2 << model2;
                }

                destination += ".copy";

                std::unique_ptr<Graphyte::Storage::Archive> writer{};
                if (Graphyte::Storage::CreateWriter(writer, destination) == Status::Success)
                {
                    *writer << model2;
                }
            }
        }

        return false;
    }
}
