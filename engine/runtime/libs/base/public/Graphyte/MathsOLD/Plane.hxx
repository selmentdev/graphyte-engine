#pragma once
#include <Graphyte/Maths/Simd.hxx>
#if false
namespace Graphyte::Maths
{
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Plane;
    struct Quaternion;
    struct Matrix;
}

namespace Graphyte::Maths
{
    struct Plane final
    {
    public:
        VectorFloat4 V;

    public:
        //mathinline mathcall operator VectorFloat4() const noexcept
        //{
        //    return V;
        //}

    public:
        static bool mathcall IsEqual(Plane p1, Plane p2) noexcept;
        static bool mathcall IsEqual(Plane p1, Plane p2, Vector4 epsilon) noexcept;
        static bool mathcall IsNotEqual(Plane p1, Plane p2) noexcept;
        static bool mathcall IsNaN(Plane p) noexcept;
        static bool mathcall IsInfinite(Plane p) noexcept;

    public:
        static Vector4 mathcall Dot(Plane p, Vector4 v) noexcept;
        static Vector4 mathcall DotCoord(Plane p, Vector3 v) noexcept;
        static Vector4 mathcall DotNormal(Plane p, Vector3 v) noexcept;
        static Plane mathcall NormalizeEst(Plane p) noexcept;
        static Plane mathcall Normalize(Plane p) noexcept;
        static Vector3 mathcall IntersectLine(Plane p, Vector3 line_point1, Vector3 line_point2) noexcept;
        static void mathcall IntersectPlane(Vector3* line_point1, Vector3* line_point2, Plane p1, Plane p2) noexcept;
        static Plane mathcall Transform(Plane p, Matrix m) noexcept;
        static Plane mathcall FromPointNormal(Vector3 point, Vector3 normal) noexcept;
        static Plane mathcall FromPoints(Vector3 point1, Vector3 point2, Vector3 point3) noexcept;
    };

#if GRAPHYTE_MATH_ENABLE_OPERATORS

    mathinline bool mathcall operator== (Plane p1, Plane p2) noexcept
    {
        return Plane::IsEqual(p1, p2);
    }

    mathinline bool mathcall operator!= (Plane p1, Plane p2) noexcept
    {
        return Plane::IsNotEqual(p1, p2);
    }

#endif
}

#include <Graphyte/Maths/Plane.impl.hxx>
#endif
