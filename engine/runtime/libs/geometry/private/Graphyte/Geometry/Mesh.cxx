#include <Graphyte/Geometry/Mesh.hxx>

namespace Graphyte::Geometry
{
    namespace Impl
    {
        template <typename TCollection>
        __forceinline bool IsValidCollection(const TCollection& collection, uint32_t expected_size) noexcept
        {
            return collection.size() == 0
                || collection.size() == static_cast<size_t>(expected_size);
        }
    }

    void Mesh::Clear() noexcept
    {
        FaceMaterialIndices.clear();
        FaceSmoothingMasks.clear();
        VertexPositions.clear();
        WedgeIndices.clear();
        WedgeTangentX.clear();
        WedgeTangentY.clear();
        WedgeTangentZ.clear();

        for (auto& texcoords : WedgeTextureCoords)
        {
            texcoords.clear();
        }

        WedgeColors.clear();
    }

    bool Mesh::IsValid() const noexcept
    {
        uint32_t vertices_count = GetVerticesCount();
        uint32_t wedges_count = GetWedgesCount();
        uint32_t faces_count = GetFacesCount();

        bool valid =
            (vertices_count != 0) &&
            (faces_count != 0) &&
            ((faces_count * FacePrimitiveCornersCount) == wedges_count) &&
            Impl::IsValidCollection(FaceMaterialIndices, faces_count) &&
            Impl::IsValidCollection(FaceSmoothingMasks, faces_count) &&
            Impl::IsValidCollection(WedgeTangentX, wedges_count) &&
            Impl::IsValidCollection(WedgeTangentY, wedges_count) &&
            Impl::IsValidCollection(WedgeTangentZ, wedges_count) &&
            Impl::IsValidCollection(WedgeColors, wedges_count) &&
            (WedgeTextureCoords[0].size() == static_cast<size_t>(wedges_count));

        for (auto& texcoords : WedgeTextureCoords)
        {
            valid = valid && Impl::IsValidCollection(texcoords, wedges_count);
        }

        for (uint32_t wedge_index = 0; valid && (wedge_index < wedges_count); ++wedge_index)
        {
            valid = valid && (WedgeIndices[wedge_index] < vertices_count);
        }

        return valid;
    }

    GEOMETRY_API Storage::Archive& operator<< (Storage::Archive& archive, Mesh& mesh) noexcept
    {
        archive << mesh.FaceMaterialIndices;
        archive << mesh.FaceSmoothingMasks;
        archive << mesh.VertexPositions;
        archive << mesh.WedgeIndices;
        archive << mesh.WedgeTangentX;
        archive << mesh.WedgeTangentY;
        archive << mesh.WedgeTangentZ;

        for (auto& texcoords : mesh.WedgeTextureCoords)
        {
            archive << texcoords;
        }

        archive << mesh.WedgeColors;

        return archive;
    }
}
