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
    struct Vector2 final
    {
    public:
        VectorFloat4 V;

    public:
        //mathinline mathcall operator VectorFloat4() const noexcept
        //{
        //    return V;
        //}

    public:
        static Vector2 mathcall Make(float value) noexcept;
        static Vector2 mathcall Make(float x, float y) noexcept;

        static Vector2 mathcall MakeUInt(uint32_t value) noexcept;
        static Vector2 mathcall MakeUInt(uint32_t x, uint32_t y) noexcept;

    public:
        static Vector2 mathcall Load(const float2a* source) noexcept;
        static Vector2 mathcall LoadPacked(const float2* source) noexcept;

        static Vector2 mathcall Load(const float3a* source) noexcept;
        static Vector2 mathcall LoadPacked(const float3* source) noexcept;

        static Vector2 mathcall Load(const float4a* source) noexcept;
        static Vector2 mathcall LoadPacked(const float4* source) noexcept;

    public:
        static void mathcall Store(float2a* destination, Vector2 v) noexcept;
        static void mathcall StorePacked(float2* destination, Vector2 v) noexcept;

        static void mathcall Store(float3a* destination, Vector2 v) noexcept;
        static void mathcall StorePacked(float3* destination, Vector2 v) noexcept;

        static void mathcall Store(float4a* destination, Vector2 v) noexcept;
        static void mathcall StorePacked(float4* destination, Vector2 v) noexcept;

    public:
        static bool mathcall IsEqual(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall IsEqual(Vector2 v1, Vector2 v2, Vector2 epsilon) noexcept;
        static bool mathcall IsNotEqual(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall IsGreater(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall IsGreaterEqual(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall IsLess(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall IsLessEqual(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall InBounds(Vector2 v, Vector2 bounds) noexcept;
        static bool mathcall IsNaN(Vector2 v) noexcept;
        static bool mathcall IsInfinite(Vector2 v) noexcept;

    public:
        static bool mathcall IsEqualUInt(Vector2 v1, Vector2 v2) noexcept;
        static bool mathcall IsNotEqualUInt(Vector2 v1, Vector2 v2) noexcept;

    public:
        static Vector2 mathcall Min(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall Max(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall Round(Vector2 v) noexcept;
        static Vector2 mathcall Truncate(Vector2 v) noexcept;
        static Vector2 mathcall Floor(Vector2 v) noexcept;
        static Vector2 mathcall Ceiling(Vector2 v) noexcept;
        static Vector2 mathcall Fract(Vector2 v) noexcept;
        static Vector2 mathcall Clamp(Vector2 v, Vector2 min, Vector2 max) noexcept;
        static Vector2 mathcall Saturate(Vector2 v) noexcept;

    public:
        static Vector2 mathcall Negate(Vector2 v) noexcept;
        static Vector2 mathcall Add(Vector2 v1, Vector2 v2) noexcept;
        static Vector4 mathcall Sum(Vector2 v) noexcept;
        static Vector2 mathcall AddAngles(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall Subtract(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall SubtractAngles(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall Multiply(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall MultiplyAdd(Vector2 v1, Vector2 v2, Vector2 v3) noexcept;
        static Vector2 mathcall Divide(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall NegativeMultiplySubtract(Vector2 v1, Vector2 v2, Vector2 v3) noexcept;
        static Vector2 mathcall Scale(Vector2 v, float scale) noexcept;
        static Vector2 mathcall ReciprocalEst(Vector2 v) noexcept;
        static Vector2 mathcall Reciprocal(Vector2 v) noexcept;
        static Vector2 mathcall SqrtEst(Vector2 v) noexcept;
        static Vector2 mathcall Sqrt(Vector2 v) noexcept;
        static Vector2 mathcall ReciprocalSqrtEst(Vector2 v) noexcept;
        static Vector2 mathcall ReciprocalSqrt(Vector2 v) noexcept;
        static Vector2 mathcall Exp2(Vector2 v) noexcept;
        static Vector2 mathcall ExpE(Vector2 v) noexcept;
        static Vector2 mathcall Exp(Vector2 v) noexcept;
        static Vector2 mathcall Log2(Vector2 v) noexcept;
        static Vector2 mathcall LogE(Vector2 v) noexcept;
        static Vector2 mathcall Log(Vector2 v) noexcept;
        static Vector2 mathcall Pow(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall Abs(Vector2 v) noexcept;
        static Vector2 mathcall Mod(Vector2 v1, Vector2 v2) noexcept;
        static Vector2 mathcall ModAngles(Vector2 angles) noexcept;
        static Vector2 mathcall Sin(Vector2 v) noexcept;
        static Vector2 mathcall Cos(Vector2 v) noexcept;
        static void mathcall SinCos(Vector2* out_sin, Vector2* out_cos, Vector2 v) noexcept;
        static Vector2 mathcall Tan(Vector2 v) noexcept;
        static Vector2 mathcall SinH(Vector2 v) noexcept;
        static Vector2 mathcall CosH(Vector2 v) noexcept;
        static Vector2 mathcall TanH(Vector2 v) noexcept;
        static Vector2 mathcall ASin(Vector2 v) noexcept;
        static Vector2 mathcall ACos(Vector2 v) noexcept;
        static Vector2 mathcall ATan(Vector2 v) noexcept;
        static Vector2 mathcall ATan2(Vector2 y, Vector2 x) noexcept;
        static Vector2 mathcall SinEst(Vector2 v) noexcept;
        static Vector2 mathcall CosEst(Vector2 v) noexcept;
        static void mathcall SinCosEst(Vector2* out_sin, Vector2* out_cos, Vector2 v) noexcept;
        static Vector2 mathcall TanEst(Vector2 v) noexcept;
        static Vector2 mathcall ASinEst(Vector2 v) noexcept;
        static Vector2 mathcall ACosEst(Vector2 v) noexcept;
        static Vector2 mathcall ATanEst(Vector2 v) noexcept;
        static Vector2 mathcall ATan2Est(Vector2 y, Vector2 x) noexcept;

    public:
        static Vector2 mathcall Lerp(Vector2 v0, Vector2 v1, float t) noexcept;
        static Vector2 mathcall Lerp(Vector2 v0, Vector2 v1, Vector4 t) noexcept;
        static Vector2 mathcall Hermite(Vector2 position0, Vector2 tangent0, Vector2 position1, Vector2 tangent1, float t) noexcept;
        static Vector2 mathcall Hermite(Vector2 position0, Vector2 tangent0, Vector2 position1, Vector2 tangent1, Vector4 t) noexcept;
        static Vector2 mathcall CatmullRom(Vector2 position0, Vector2 position1, Vector2 position2, Vector2 position3, float t) noexcept;
        static Vector2 mathcall CatmullRom(Vector2 position0, Vector2 position1, Vector2 position2, Vector2 position3, Vector4 t) noexcept;
        static Vector2 mathcall Barycentric(Vector2 position0, Vector2 position1, Vector2 position2, float f, float g) noexcept;
        static Vector2 mathcall Barycentric(Vector2 position0, Vector2 position1, Vector2 position2, Vector4 f, Vector4 g) noexcept;

    public:
        static Vector4 mathcall Dot(Vector2 v1, Vector2 v2) noexcept;
        static Vector4 mathcall Cross(Vector2 v1, Vector2 v2) noexcept;
        static Vector4 mathcall LengthSquared(Vector2 v) noexcept;
        static Vector4 mathcall ReciprocalLengthEst(Vector2 v) noexcept;
        static Vector4 mathcall ReciprocalLength(Vector2 v) noexcept;
        static Vector4 mathcall LengthEst(Vector2 v) noexcept;
        static Vector4 mathcall Length(Vector2 v) noexcept;
        static Vector2 mathcall NormalizeEst(Vector2 v) noexcept;
        static Vector2 mathcall Normalize(Vector2 v) noexcept;
        static Vector2 mathcall ClampLength(Vector2 v, float min, float max) noexcept;
        static Vector2 mathcall ClampLength(Vector2 v, Vector4 min, Vector4 max) noexcept;
        static Vector2 mathcall Reflect(Vector2 incident, Vector2 normal) noexcept;
        static Vector2 mathcall Refract(Vector2 incident, Vector2 normal, float refraction_index) noexcept;
        static Vector2 mathcall Refract(Vector2 incident, Vector2 normal, Vector4 refraction_index) noexcept;
        static Vector2 mathcall Orthogonal(Vector2 v) noexcept;
        static Vector4 mathcall AngleBetweenNormalsEst(Vector2 n1, Vector2 n2) noexcept;
        static Vector4 mathcall AngleBetweenNormals(Vector2 n1, Vector2 n2) noexcept;
        static Vector4 mathcall AngleBetweenVectors(Vector2 v1, Vector2 v2) noexcept;

    public:
        static Vector4 mathcall LinePointDistance(Vector2 line_point1, Vector2 line_point2, Vector2 point) noexcept;
        static Vector4 mathcall IntersectLine(Vector2 line1_point1, Vector2 line1_point2, Vector2 line2_point1, Vector2 line2_point2) noexcept;
        static Vector2 mathcall Transform(Vector2 v, Matrix m) noexcept;
        static Vector2 mathcall TransformCoord(Vector2 v, Matrix m) noexcept;
        static Vector2 mathcall TransformNormal(Vector2 v, Matrix m) noexcept;
    };

#if GRAPHYTE_MATH_ENABLE_OPERATORS

    mathinline bool mathcall operator== (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::IsEqual(v1, v2);
    }

    mathinline bool mathcall operator!= (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::IsNotEqual(v1, v2);
    }

    mathinline bool mathcall operator< (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::IsLess(v1, v2);
    }

    mathinline bool mathcall operator<= (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::IsLessEqual(v1, v2);
    }

    mathinline bool mathcall operator> (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::IsGreater(v1, v2);
    }

    mathinline bool mathcall operator>= (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::IsGreaterEqual(v1, v2);
    }

    mathinline Vector2 mathcall operator+ (Vector2 v) noexcept
    {
        return v;
    }

    mathinline Vector2 mathcall operator- (Vector2 v) noexcept
    {
        return Vector2::Negate(v);
    }

    mathinline Vector2 mathcall operator+ (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::Add(v1, v2);
    }

    mathinline Vector2 mathcall operator- (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::Subtract(v1, v2);
    }

    mathinline Vector2 mathcall operator* (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::Multiply(v1, v2);
    }

    mathinline Vector2 mathcall operator* (float scalar, Vector2 v) noexcept
    {
        return Vector2::Scale(v, scalar);
    }

    mathinline Vector2 mathcall operator* (Vector2 v, float scalar) noexcept
    {
        return Vector2::Scale(v, scalar);
    }

    mathinline Vector2 mathcall operator/ (Vector2 v1, Vector2 v2) noexcept
    {
        return Vector2::Divide(v1, v2);
    }

    mathinline Vector2 mathcall operator/ (Vector2 v, float scalar) noexcept
    {
        return Vector2::Divide(v, Vector2::Make(scalar));
    }

    mathinline Vector2 mathcall operator/ (float scalar, Vector2 v) noexcept
    {
        return Vector2::Divide(Vector2::Make(scalar), v);
    }

    mathinline Vector2& mathcall operator+= (Vector2& v1, Vector2 v2) noexcept
    {
        v1 = Vector2::Add(v1, v2);
        return v1;
    }

    mathinline Vector2& mathcall operator-= (Vector2& v1, Vector2 v2) noexcept
    {
        v1 = Vector2::Subtract(v1, v2);
        return v1;
    }

    mathinline Vector2& mathcall operator*= (Vector2& v1, Vector2 v2) noexcept
    {
        v1 = Vector2::Multiply(v1, v2);
        return v1;
    }

    mathinline Vector2& mathcall operator*= (Vector2& v, float scalar) noexcept
    {
        v = Vector2::Scale(v, scalar);
        return v;
    }

    mathinline Vector2& mathcall operator/= (Vector2& v1, Vector2 v2) noexcept
    {
        v1 = Vector2::Divide(v1, v2);
        return v1;
    }

    mathinline Vector2& mathcall operator/= (Vector2& v, float scalar) noexcept
    {
        v = Vector2::Divide(v, Vector2::Make(scalar));
        return v;
    }

#endif
}

#include <Graphyte/Maths/Vector2.impl.hxx>
