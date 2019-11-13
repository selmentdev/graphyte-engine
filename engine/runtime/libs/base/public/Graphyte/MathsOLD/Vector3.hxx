#pragma once
#include <Graphyte/Maths/Simd.hxx>
#include <Graphyte/Maths/Types.hxx>

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
    struct Vector3 final
    {
    public:
        VectorFloat4 V;

    public:
        //mathinline mathcall operator VectorFloat4() const noexcept
        //{
        //    return V;
        //}

    public:
        static Vector3 mathcall Make(float value) noexcept;
        static Vector3 mathcall Make(float x, float y) noexcept;
        static Vector3 mathcall Make(float x, float y, float z) noexcept;

        static Vector3 mathcall MakeUInt(uint32_t value) noexcept;
        static Vector3 mathcall MakeUInt(uint32_t x, uint32_t y, uint32_t z) noexcept;

    public:
        static Vector3 mathcall Load(const float2a* source) noexcept;
        static Vector3 mathcall LoadPacked(const float2* source) noexcept;

        static Vector3 mathcall Load(const float3a* source) noexcept;
        static Vector3 mathcall LoadPacked(const float3* source) noexcept;

        static Vector3 mathcall Load(const float4a* source) noexcept;
        static Vector3 mathcall LoadPacked(const float4* source) noexcept;

    public:
        static void mathcall Store(float2a* destination, Vector3 v) noexcept;
        static void mathcall StorePacked(float2* destination, Vector3 v) noexcept;

        static void mathcall Store(float3a* destination, Vector3 v) noexcept;
        static void mathcall StorePacked(float3* destination, Vector3 v) noexcept;

        static void mathcall Store(float4a* destination, Vector3 v) noexcept;
        static void mathcall StorePacked(float4* destination, Vector3 v) noexcept;

    public:
        static Vector3 mathcall Zero() noexcept;
        static Vector3 mathcall One() noexcept;
        static Vector3 mathcall Infinity() noexcept;
        static Vector3 mathcall NaN() noexcept;
        static Vector3 mathcall Epsilon() noexcept;
        static Vector3 mathcall SignMask() noexcept;

        static Vector3 mathcall UnitX() noexcept;
        static Vector3 mathcall UnitY() noexcept;
        static Vector3 mathcall UnitZ() noexcept;

    public:
        static Vector3 mathcall SplatX() noexcept;
        static Vector3 mathcall SplatY() noexcept;
        static Vector3 mathcall SplatZ() noexcept;

    public:
        static bool mathcall IsEqual(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall IsEqual(Vector3 v1, Vector3 v2, Vector4 epsilon) noexcept;
        static bool mathcall IsNotEqual(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall IsGreater(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall IsGreaterEqual(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall IsLess(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall IsLessEqual(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall InBounds(Vector3 v, Vector3 bounds) noexcept;
        static bool mathcall IsNaN(Vector3 v) noexcept;
        static bool mathcall IsInfinite(Vector3 v) noexcept;

    public:
        static bool mathcall IsEqualUInt(Vector3 v1, Vector3 v2) noexcept;
        static bool mathcall IsNotEqualUInt(Vector3 v1, Vector3 v2) noexcept;

    public:
        static Vector3 mathcall Min(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall Max(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall Round(Vector3 v) noexcept;
        static Vector3 mathcall Truncate(Vector3 v) noexcept;
        static Vector3 mathcall Floor(Vector3 v) noexcept;
        static Vector3 mathcall Ceiling(Vector3 v) noexcept;
        static Vector3 mathcall Fract(Vector3 v) noexcept;
        static Vector3 mathcall Clamp(Vector3 v, Vector3 min, Vector3 max) noexcept;
        static Vector3 mathcall Saturate(Vector3 v) noexcept;

    public:
        static Vector3 mathcall Negate(Vector3 v) noexcept;
        static Vector3 mathcall Add(Vector3 v1, Vector3 v2) noexcept;
        static Vector4 mathcall Sum(Vector3 v) noexcept;
        static Vector3 mathcall AddAngles(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall Subtract(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall SubtractAngles(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall Multiply(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall MultiplyAdd(Vector3 v1, Vector3 v2, Vector3 v3) noexcept;
        static Vector3 mathcall Divide(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall NegativeMultiplySubtract(Vector3 v1, Vector3 v2, Vector3 v3) noexcept;
        static Vector3 mathcall Scale(Vector3 v, float scale) noexcept;
        static Vector3 mathcall ReciprocalEst(Vector3 v) noexcept;
        static Vector3 mathcall Reciprocal(Vector3 v) noexcept;
        static Vector3 mathcall SqrtEst(Vector3 v) noexcept;
        static Vector3 mathcall Sqrt(Vector3 v) noexcept;
        static Vector3 mathcall ReciprocalSqrtEst(Vector3 v) noexcept;
        static Vector3 mathcall ReciprocalSqrt(Vector3 v) noexcept;
        static Vector3 mathcall Exp2(Vector3 v) noexcept;
        static Vector3 mathcall ExpE(Vector3 v) noexcept;
        static Vector3 mathcall Exp(Vector3 v) noexcept;
        static Vector3 mathcall Log2(Vector3 v) noexcept;
        static Vector3 mathcall LogE(Vector3 v) noexcept;
        static Vector3 mathcall Log(Vector3 v) noexcept;
        static Vector3 mathcall Pow(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall Abs(Vector3 v) noexcept;
        static Vector3 mathcall Mod(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall ModAngles(Vector3 angles) noexcept;
        static Vector3 mathcall Sin(Vector3 v) noexcept;
        static Vector3 mathcall Cos(Vector3 v) noexcept;
        static void mathcall SinCos(Vector3* out_sin, Vector3* out_cos, Vector3 v) noexcept;
        static Vector3 mathcall Tan(Vector3 v) noexcept;
        static Vector3 mathcall SinH(Vector3 v) noexcept;
        static Vector3 mathcall CosH(Vector3 v) noexcept;
        static Vector3 mathcall TanH(Vector3 v) noexcept;
        static Vector3 mathcall ASin(Vector3 v) noexcept;
        static Vector3 mathcall ACos(Vector3 v) noexcept;
        static Vector3 mathcall ATan(Vector3 v) noexcept;
        static Vector3 mathcall ATan2(Vector3 y, Vector3 x) noexcept;
        static Vector3 mathcall SinEst(Vector3 v) noexcept;
        static Vector3 mathcall CosEst(Vector3 v) noexcept;
        static void mathcall SinCosEst(Vector3* out_sin, Vector3* out_cos, Vector3 v) noexcept;
        static Vector3 mathcall TanEst(Vector3 v) noexcept;
        static Vector3 mathcall ASinEst(Vector3 v) noexcept;
        static Vector3 mathcall ACosEst(Vector3 v) noexcept;
        static Vector3 mathcall ATanEst(Vector3 v) noexcept;
        static Vector3 mathcall ATan2Est(Vector3 y, Vector3 x) noexcept;

    public:
        static Vector3 mathcall Lerp(Vector3 v0, Vector3 v1, float t) noexcept;
        static Vector3 mathcall Lerp(Vector3 v0, Vector3 v1, Vector4 t) noexcept;
        static Vector3 mathcall Hermite(Vector3 position0, Vector3 tangent0, Vector3 position1, Vector3 tangent1, float t) noexcept;
        static Vector3 mathcall Hermite(Vector3 position0, Vector3 tangent0, Vector3 position1, Vector3 tangent1, Vector4 t) noexcept;
        static Vector3 mathcall CatmullRom(Vector3 position0, Vector3 position1, Vector3 position2, Vector3 position3, float t) noexcept;
        static Vector3 mathcall CatmullRom(Vector3 position0, Vector3 position1, Vector3 position2, Vector3 position3, Vector4 t) noexcept;
        static Vector3 mathcall Barycentric(Vector3 position0, Vector3 position1, Vector3 position2, float f, float g) noexcept;
        static Vector3 mathcall Barycentric(Vector3 position0, Vector3 position1, Vector3 position2, Vector4 f, Vector4 g) noexcept;

    public:
        static Vector4 mathcall Dot(Vector3 v1, Vector3 v2) noexcept;
        static Vector3 mathcall Cross(Vector3 v1, Vector3 v2) noexcept;
        static Vector4 mathcall LengthSquared(Vector3 v) noexcept;
        static Vector4 mathcall ReciprocalLengthEst(Vector3 v) noexcept;
        static Vector4 mathcall ReciprocalLength(Vector3 v) noexcept;
        static Vector4 mathcall LengthEst(Vector3 v) noexcept;
        static Vector4 mathcall Length(Vector3 v) noexcept;
        static Vector3 mathcall NormalizeEst(Vector3 v) noexcept;
        static Vector3 mathcall Normalize(Vector3 v) noexcept;
        static Vector3 mathcall ClampLength(Vector3 v, float min, float max) noexcept;
        static Vector3 mathcall ClampLength(Vector3 v, Vector4 min, Vector4 max) noexcept;
        static Vector3 mathcall Reflect(Vector3 incident, Vector3 normal) noexcept;
        static Vector3 mathcall Refract(Vector3 incident, Vector3 normal, float refraction_index) noexcept;
        static Vector3 mathcall Refract(Vector3 incident, Vector3 normal, Vector4 refraction_index) noexcept;
        static Vector3 mathcall Orthogonal(Vector3 v) noexcept;
        static Vector4 mathcall AngleBetweenNormalsEst(Vector3 n1, Vector3 n2) noexcept;
        static Vector4 mathcall AngleBetweenNormals(Vector3 n1, Vector3 n2) noexcept;
        static Vector4 mathcall AngleBetweenVectors(Vector3 v1, Vector3 v2) noexcept;
        static Vector4 mathcall LinePointDistance(Vector3 line_point1, Vector3 line_point2, Vector3 point) noexcept;
        static void mathcall ComponentsFromNormal(Vector3* parallel, Vector3* perpendicular, Vector3 v, Vector3 n) noexcept;
        static Vector3 mathcall Rotate(Vector3 v, Quaternion q) noexcept;
        static Vector3 mathcall InverseRotate(Vector3 v, Quaternion q) noexcept;
        static Vector3 mathcall Transform(Vector3 v, Matrix m) noexcept;
        static Vector3 mathcall TransformCoord(Vector3 v, Matrix m) noexcept;
        static Vector3 mathcall TransformNormal(Vector3 v, Matrix m) noexcept;
        static Vector3 mathcall Project(Vector3 v, float viewport_x, float viewport_y, float viewport_width, float viewport_height, float viewport_min_z, float viewport_max_z, Matrix projection, Matrix view, Matrix world) noexcept;
        static Vector3 mathcall Unproject(Vector3 v, float viewport_x, float viewport_y, float viewport_width, float viewport_height, float viewport_min_z, float viewport_max_z, Matrix projection, Matrix view, Matrix world) noexcept;
    };

#if GRAPHYTE_MATH_ENABLE_OPERATORS

    mathinline bool mathcall operator== (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::IsEqual(v1, v2);
    }

    mathinline bool mathcall operator!= (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::IsNotEqual(v1, v2);
    }

    mathinline bool mathcall operator< (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::IsLess(v1, v2);
    }

    mathinline bool mathcall operator<= (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::IsLessEqual(v1, v2);
    }

    mathinline bool mathcall operator> (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::IsGreater(v1, v2);
    }

    mathinline bool mathcall operator>= (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::IsGreaterEqual(v1, v2);
    }

    mathinline Vector3 mathcall operator+ (Vector3 v) noexcept
    {
        return v;
    }

    mathinline Vector3 mathcall operator- (Vector3 v) noexcept
    {
        return Vector3::Negate(v);
    }

    mathinline Vector3 mathcall operator+ (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::Add(v1, v2);
    }

    mathinline Vector3 mathcall operator- (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::Subtract(v1, v2);
    }

    mathinline Vector3 mathcall operator* (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::Multiply(v1, v2);
    }

    mathinline Vector3 mathcall operator* (float scalar, Vector3 v) noexcept
    {
        return Vector3::Scale(v, scalar);
    }

    mathinline Vector3 mathcall operator* (Vector3 v, float scalar) noexcept
    {
        return Vector3::Scale(v, scalar);
    }

    mathinline Vector3 mathcall operator/ (Vector3 v1, Vector3 v2) noexcept
    {
        return Vector3::Divide(v1, v2);
    }

    mathinline Vector3 mathcall operator/ (Vector3 v, float scalar) noexcept
    {
        return Vector3::Divide(v, Vector3::Make(scalar));
    }

    mathinline Vector3 mathcall operator/ (float scalar, Vector3 v) noexcept
    {
        return Vector3::Divide(Vector3::Make(scalar), v);
    }

    mathinline Vector3& mathcall operator+= (Vector3& v1, Vector3 v2) noexcept
    {
        v1 = Vector3::Add(v1, v2);
        return v1;
    }

    mathinline Vector3& mathcall operator-= (Vector3& v1, Vector3 v2) noexcept
    {
        v1 = Vector3::Subtract(v1, v2);
        return v1;
    }

    mathinline Vector3& mathcall operator*= (Vector3& v1, Vector3 v2) noexcept
    {
        v1 = Vector3::Multiply(v1, v2);
        return v1;
    }

    mathinline Vector3& mathcall operator*= (Vector3& v, float scalar) noexcept
    {
        v = Vector3::Scale(v, scalar);
        return v;
    }

    mathinline Vector3& mathcall operator/= (Vector3& v1, Vector3 v2) noexcept
    {
        v1 = Vector3::Divide(v1, v2);
        return v1;
    }

    mathinline Vector3& mathcall operator/= (Vector3& v, float scalar) noexcept
    {
        v = Vector3::Divide(v, Vector3::Make(scalar));
        return v;
    }

#endif
}

#include <Graphyte/Maths/Vector3.impl.hxx>
