#include "Geometry.pch.hxx"
#include <Graphyte/Geometry/MeshVertexComparator.hxx>
#include <Graphyte/Maths/Vector4.hxx>
#include <Graphyte/Maths/Vector3.hxx>
#include <Graphyte/Maths/Vector2.hxx>
#include <Graphyte/Maths/Color.hxx>

namespace Graphyte::Geometry
{
    int MeshVertexComparator::Compare(
        const Mesh& mesh,
        uint32_t lhs_index,
        uint32_t rhs_index,
        float tolerance
    ) const noexcept
    {
        Maths::Vector4 const vtolerance = Maths::Vector4::Make(tolerance);

        //
        // Compare vertex positions.
        //
        {
            auto const& lhs_vertex = mesh.VertexPositions[mesh.WedgeIndices[lhs_index]];
            auto const& rhs_vertex = mesh.VertexPositions[mesh.WedgeIndices[rhs_index]];

            Maths::Vector3 const lhs = Maths::Vector3::LoadPacked(&lhs_vertex);
            Maths::Vector3 const rhs = Maths::Vector3::LoadPacked(&rhs_vertex);

            if (!Maths::Vector3::IsEqual(lhs, rhs, vtolerance))
            {
                if (Maths::Vector3::IsLess(lhs, rhs))
                {
                    return -1;
                }
                else if (Maths::Vector3::IsGreater(lhs, rhs))
                {
                    return 1;
                }
            }
        }

        //
        // Compare vertex normals.
        //
        if (this->CompareNormals)
        {
            auto const lhs = Maths::Vector3::LoadPacked(&mesh.WedgeTangentZ[lhs_index]);
            auto const rhs = Maths::Vector3::LoadPacked(&mesh.WedgeTangentZ[rhs_index]);

            if (!Maths::Vector3::IsEqual(lhs, rhs, vtolerance))
            {
                if (Maths::Vector3::IsLess(lhs, rhs))
                {
                    return -1;
                }
                else if (Maths::Vector3::IsGreater(lhs, rhs))
                {
                    return 1;
                }
            }
        }

        //
        // Compare tangent X.
        //
        if (this->CompareTangentX)
        {
            auto const lhs = Maths::Vector3::LoadPacked(&mesh.WedgeTangentX[lhs_index]);
            auto const rhs = Maths::Vector3::LoadPacked(&mesh.WedgeTangentX[rhs_index]);

            if (!Maths::Vector3::IsEqual(lhs, rhs, vtolerance))
            {
                if (Maths::Vector3::IsLess(lhs, rhs))
                {
                    return -1;
                }
                else if (Maths::Vector3::IsGreater(lhs, rhs))
                {
                    return 1;
                }
            }
        }

        //
        // Compare tangent Y.
        //
        if (this->CompareTangentY)
        {
            auto const lhs = Maths::Vector3::LoadPacked(&mesh.WedgeTangentY[lhs_index]);
            auto const rhs = Maths::Vector3::LoadPacked(&mesh.WedgeTangentY[rhs_index]);

            if (!Maths::Vector3::IsEqual(lhs, rhs, vtolerance))
            {
                if (Maths::Vector3::IsLess(lhs, rhs))
                {
                    return -1;
                }
                else if (Maths::Vector3::IsGreater(lhs, rhs))
                {
                    return 1;
                }
            }
        }

        //
        // Compare texcoords.
        //
        for (size_t i = 0; i < Mesh::MaxTextureCoords; ++i)
        {
            if (this->CompareTexcoords[i])
            {
                auto const lhs = Maths::Vector2::LoadPacked(&mesh.WedgeTextureCoords[i][lhs_index]);
                auto const rhs = Maths::Vector2::LoadPacked(&mesh.WedgeTextureCoords[i][rhs_index]);

                if (!Maths::Vector2::IsEqual(lhs, rhs, Maths::Vector2{ vtolerance.V }))
                {
                    if (Maths::Vector2::IsLess(lhs, rhs))
                    {
                        return -1;
                    }
                    else if (Maths::Vector2::IsGreater(lhs, rhs))
                    {
                        return 1;
                    }
                }
            }
        }

        //
        // Compare colors.
        //
        if (this->CompareTangentY)
        {
            auto const lhs = Maths::Color::Load(&mesh.WedgeColors[lhs_index]);
            auto const rhs = Maths::Color::Load(&mesh.WedgeColors[rhs_index]);

            if (!Maths::Vector4::IsEqual(Maths::Vector4{ lhs.V }, Maths::Vector4{ rhs.V }, vtolerance))
            {
                if (Maths::Color::IsLess(lhs, rhs))
                {
                    return -1;
                }
                else if (Maths::Color::IsGreater(lhs, rhs))
                {
                    return 1;
                }
            }
        }

        return 0;
    }
}
