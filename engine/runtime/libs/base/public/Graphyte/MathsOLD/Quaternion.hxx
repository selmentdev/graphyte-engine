#pragma once
#include <Graphyte/Maths/Simd.hxx>

// Forward declarations.
namespace Graphyte::Maths
{
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Matrix;
    struct Quaternion;
}

namespace Graphyte::Maths
{
    struct Quaternion final
    {
    public:
        VectorFloat4 V;

    public:
        mathinline mathcall operator VectorFloat4() const noexcept
        {
            return V;
        }

    public:
        static bool mathcall IsEqual(Quaternion q1, Quaternion q2) noexcept;
        static bool mathcall IsNotEqual(Quaternion q1, Quaternion q2) noexcept;
        static bool mathcall IsNaN(Quaternion q) noexcept;
        static bool mathcall IsInfinite(Quaternion q) noexcept;
        static bool mathcall IsIdentity(Quaternion q) noexcept;
        static Vector4 mathcall Dot(Quaternion q1, Quaternion q2) noexcept;
        static Quaternion mathcall Multiply(Quaternion q1, Quaternion q2) noexcept;
        static Vector4 mathcall LengthSquared(Quaternion q) noexcept;
        static Vector4 mathcall ReciprocalLength(Quaternion q) noexcept;
        static Vector4 mathcall Length(Quaternion q) noexcept;
        static Quaternion mathcall NormalizeEst(Quaternion q) noexcept;
        static Quaternion mathcall Normalize(Quaternion q) noexcept;
        static Quaternion mathcall Conjugate(Quaternion q) noexcept;
        static Quaternion mathcall Inverse(Quaternion q) noexcept;
        static Quaternion mathcall Ln(Quaternion q) noexcept;
        static Quaternion mathcall Exp(Quaternion q);
        static Quaternion mathcall Slerp(Quaternion q0, Quaternion q1, float t) noexcept;
        static Quaternion mathcall Slerp(Quaternion q0, Quaternion q1, Vector4 t) noexcept;
        static Quaternion mathcall Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, float t) noexcept;
        static Quaternion mathcall Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, Vector4 t) noexcept;
        static void mathcall SquadSetup(Quaternion* out_a, Quaternion* out_b, Quaternion* out_c, Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3) noexcept;
        static Quaternion mathcall Barycentric(Quaternion q0, Quaternion q1, Quaternion q2, float f, float g) noexcept;
        static Quaternion mathcall Barycentric(Quaternion q0, Quaternion q1, Quaternion q2, Vector4 f, Vector4 g) noexcept;
        static Quaternion mathcall Identity() noexcept;
        static Quaternion mathcall RotationFromRollPitchYaw(float pitch, float yaw, float roll) noexcept;
        static Quaternion mathcall RotationFromRollPitchYaw(Vector3 angles) noexcept;
        static Quaternion mathcall RotationNormal(Vector3 normal_axis, float angle) noexcept;
        static Quaternion mathcall RotationAxis(Vector3 axis, float angle) noexcept;
        static Quaternion mathcall RotationMatrix(Matrix m) noexcept;
        static void mathcall ToAxisAngle(Vector3* axis, float* angle, Quaternion q) noexcept;
    };
}

#include <Graphyte/Maths/Quaternion.impl.hxx>
