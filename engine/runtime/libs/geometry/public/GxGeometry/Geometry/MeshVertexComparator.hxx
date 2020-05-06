#pragma once
#include <GxGeometry/Geometry/Mesh.hxx>

namespace Graphyte::Geometry
{
    /**
     * @brief   Provides way of comparing mesh vertices in generic way.
     */
    struct MeshVertexComparator final
    {
        bool CompareNormals;        //!< Compare normals.
        bool CompareTangentX;       //!< Compare U tangents.
        bool CompareTangentY;       //!< Compare V tangents.
        bool CompareTexcoords[8];   //!< Compare texcoords.
        bool CompareColors;         //!< Compare colors.

        GEOMETRY_API int Compare(const Mesh& mesh, uint32_t lhs_index, uint32_t rhs_index, float tolerance) const noexcept;
    };
}
