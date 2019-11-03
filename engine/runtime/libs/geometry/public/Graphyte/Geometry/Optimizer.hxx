#pragma once
#include <Graphyte/Geometry.module.hxx>
#include <Graphyte/Geometry/Mesh.hxx>

namespace Graphyte::Geometry
{
    class GEOMETRY_API Optimizer final
    {
    public:
        static bool RemoveDegeneratedTriangles(Mesh& mesh) noexcept;
    };
}
