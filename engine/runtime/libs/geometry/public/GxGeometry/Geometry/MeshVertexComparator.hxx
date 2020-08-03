#pragma once
#include <GxGeometry/Geometry/Mesh.hxx>

namespace Graphyte::Geometry
{
    /// @brief Provides way of comparing mesh vertices in generic way.
    struct MeshVertexComparator final
    {
        bool CompareNormals;
        bool CompareTangentX;
        bool CompareTangentY;
        bool CompareTexcoords[8];
        bool CompareColors;

        GEOMETRY_API int Compare(const Mesh& mesh, uint32_t lhs_index, uint32_t rhs_index, float tolerance) const noexcept;
    };
}
