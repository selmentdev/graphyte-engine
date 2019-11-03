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
    struct Vector4 final
    {
    public:
        VectorFloat4 V;

    public:
        //mathinline mathcall operator VectorFloat4() const noexcept
        //{
        //    return V;
        //}

    public:
        static Vector4 mathcall Make(float x, float y, float z, float w) noexcept;
        static Vector4 mathcall Make(float value) noexcept;
        static Vector4 mathcall Make(const float* value) noexcept;

        static Vector4 mathcall MakeUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept;
        static Vector4 mathcall MakeUInt(uint32_t value) noexcept;
        static Vector4 mathcall MakeUInt(const uint32_t* value) noexcept;

        static Vector4 mathcall SplatConstant(int32_t constant) noexcept;
        static Vector4 mathcall SplatConstant(int32_t constant, uint32_t exponent) noexcept;

    public:
        static Vector4 mathcall LoadRaw1(const uint32_t* source) noexcept;
        static Vector4 mathcall LoadRaw2(const uint32_t* source) noexcept;
        static Vector4 mathcall LoadRawPacked2(const uint32_t* source) noexcept;
        static Vector4 mathcall LoadRaw3(const uint32_t* source) noexcept;
        static Vector4 mathcall LoadRawPacked3(const uint32_t* source) noexcept;
        static Vector4 mathcall LoadRaw4(const uint32_t* source) noexcept;
        static Vector4 mathcall LoadRawPacked4(const uint32_t* source) noexcept;

    public:
        static void mathcall StoreRaw1(uint32_t* destination, Vector4 v) noexcept;
        static void mathcall StoreRaw2(uint32_t* destination, Vector4 v) noexcept;
        static void mathcall StoreRawPacked2(uint32_t* destination, Vector4 v) noexcept;
        static void mathcall StoreRaw3(uint32_t* destination, Vector4 v) noexcept;
        static void mathcall StoreRawPacked3(uint32_t* destination, Vector4 v) noexcept;
        static void mathcall StoreRaw4(uint32_t* destination, Vector4 v) noexcept;
        static void mathcall StoreRawPacked4(uint32_t* destination, Vector4 v) noexcept;

#if false
    public:
        static Vector4 mathcall Load(const Int_10_10_10_2_SNorm* source) noexcept;
        static Vector4 mathcall Load(const Int_10_10_10_2_UNorm* source) noexcept;
        static Vector4 mathcall Load(const UInt_10_10_10_2* source) noexcept;
        static Vector4 mathcall Load(const UShort_4_4_4_4* source) noexcept;
        static Vector4 mathcall Load(const UShort_5_5_5_1* source) noexcept;
        static Vector4 mathcall Load(const UShort_5_6_5* source) noexcept;

    public:
        static void mathcall Store(Int_10_10_10_2_SNorm* source, Vector4 v) noexcept;
        static void mathcall Store(Int_10_10_10_2_UNorm* source, Vector4 v) noexcept;
        static void mathcall Store(UInt_10_10_10_2* source, Vector4 v) noexcept;
        static void mathcall Store(UShort_4_4_4_4* source, Vector4 v) noexcept;
        static void mathcall Store(UShort_5_5_5_1* source, Vector4 v) noexcept;
        static void mathcall Store(UShort_5_6_5* source, Vector4 v) noexcept;

    public:
        static Vector4 mathcall Load(const SByte4* source) noexcept;
        static Vector4 mathcall Load(const SByteN4* source) noexcept;
        static Vector4 mathcall Load(const UByte4* source) noexcept;
        static Vector4 mathcall Load(const UByteN4* source) noexcept;

    public:
        static void mathcall Store(SByte4* destination, Vector4 v) noexcept;
        static void mathcall Store(SByteN4* destination, Vector4 v) noexcept;
        static void mathcall Store(UByte4* destination, Vector4 v) noexcept;
        static void mathcall Store(UByteN4* destination, Vector4 v) noexcept;

    public:
        static Vector4 mathcall Load(const Short4* source) noexcept;
        static Vector4 mathcall Load(const ShortN4* source) noexcept;
        static Vector4 mathcall Load(const UShort4* source) noexcept;
        static Vector4 mathcall Load(const UShortN4* source) noexcept;

    public:
        static void mathcall Store(Short4* destination, Vector4 v) noexcept;
        static void mathcall Store(ShortN4* destination, Vector4 v) noexcept;
        static void mathcall Store(UShort4* destination, Vector4 v) noexcept;
        static void mathcall Store(UShortN4* destination, Vector4 v) noexcept;
#endif

    public:
        static Vector4 mathcall Load(const int2* source) noexcept;
        static Vector4 mathcall Load(const int3* source) noexcept;
        static Vector4 mathcall Load(const int4* source) noexcept;
        static Vector4 mathcall Load(const uint2* source) noexcept;
        static Vector4 mathcall Load(const uint3* source) noexcept;
        static Vector4 mathcall Load(const uint4* source) noexcept;

    public:
        static void mathcall Store(int2* destination, Vector4 v) noexcept;
        static void mathcall Store(int3* destination, Vector4 v) noexcept;
        static void mathcall Store(int4* destination, Vector4 v) noexcept;
        static void mathcall Store(uint2* destination, Vector4 v) noexcept;
        static void mathcall Store(uint3* destination, Vector4 v) noexcept;
        static void mathcall Store(uint4* destination, Vector4 v) noexcept;

    public:
        static Vector4 mathcall Load(const float* source) noexcept;
        static Vector4 mathcall Load(const float2a* source) noexcept;
        static Vector4 mathcall LoadPacked(const float2* source) noexcept;
        static Vector4 mathcall Load(const float3a* source) noexcept;
        static Vector4 mathcall LoadPacked(const float3* source) noexcept;
        static Vector4 mathcall Load(const float4a* source) noexcept;
        static Vector4 mathcall LoadPacked(const float4* source) noexcept;

    public:
        static void mathcall Store(float* destination, Vector4 v) noexcept;
        static void mathcall Store(float2a* destination, Vector4 v) noexcept;
        static void mathcall StorePacked(float2* destination, Vector4 v) noexcept;
        static void mathcall Store(float3a* destination, Vector4 v) noexcept;
        static void mathcall StorePacked(float3* destination, Vector4 v) noexcept;
        static void mathcall Store(float4a* destination, Vector4 v) noexcept;
        static void mathcall StorePacked(float4* destination, Vector4 v) noexcept;

#if false
    public:
        static Vector4 mathcall Load(const Float3PK* source) noexcept;
        static Vector4 mathcall Load(const Float3SE* source) noexcept;

    public:
        static void mathcall Store(Float3PK* destination, Vector4 v) noexcept;
        static void mathcall Store(Float3SE* destination, Vector4 v) noexcept;
#endif

    public:
        static Vector4 mathcall Load(const half2* source) noexcept;
        static Vector4 mathcall Load(const half4* source) noexcept;

    public:
        static void mathcall Store(half2* destination, Vector4 v) noexcept;
        static void mathcall Store(half4* destination, Vector4 v) noexcept;

    public:
        static Vector4 mathcall SplatX(Vector4 v) noexcept;
        static Vector4 mathcall SplatY(Vector4 v) noexcept;
        static Vector4 mathcall SplatZ(Vector4 v) noexcept;
        static Vector4 mathcall SplatW(Vector4 v) noexcept;

    public:
        static float mathcall GetByIndex(Vector4 v, size_t index) noexcept;
        static void mathcall GetByIndex(float* value, Vector4 v, size_t index) noexcept;

        static float mathcall GetX(Vector4 v) noexcept;
        static float mathcall GetY(Vector4 v) noexcept;
        static float mathcall GetZ(Vector4 v) noexcept;
        static float mathcall GetW(Vector4 v) noexcept;

        static void mathcall GetX(float* value, Vector4 v) noexcept;
        static void mathcall GetY(float* value, Vector4 v) noexcept;
        static void mathcall GetZ(float* value, Vector4 v) noexcept;
        static void mathcall GetW(float* value, Vector4 v) noexcept;

    public:
        static Vector4 mathcall SetByIndex(Vector4 v, float value, size_t index) noexcept;
        static Vector4 mathcall SetByIndex(Vector4 v, const float* value, size_t index) noexcept;

        static Vector4 mathcall SetX(Vector4 v, float x) noexcept;
        static Vector4 mathcall SetY(Vector4 v, float y) noexcept;
        static Vector4 mathcall SetZ(Vector4 v, float z) noexcept;
        static Vector4 mathcall SetW(Vector4 v, float w) noexcept;

        static Vector4 mathcall SetX(Vector4 v, const float* x) noexcept;
        static Vector4 mathcall SetY(Vector4 v, const float* y) noexcept;
        static Vector4 mathcall SetZ(Vector4 v, const float* z) noexcept;
        static Vector4 mathcall SetW(Vector4 v, const float* w) noexcept;

    public:
        static uint32_t mathcall GetUIntByIndex(Vector4 v, size_t index) noexcept;
        static void mathcall GetUIntByIndex(uint32_t* value, Vector4 v, size_t index) noexcept;

        static uint32_t mathcall GetUIntX(Vector4 v) noexcept;
        static uint32_t mathcall GetUIntY(Vector4 v) noexcept;
        static uint32_t mathcall GetUIntZ(Vector4 v) noexcept;
        static uint32_t mathcall GetUIntW(Vector4 v) noexcept;

        static void mathcall GetUIntX(uint32_t* value, Vector4 v) noexcept;
        static void mathcall GetUIntY(uint32_t* value, Vector4 v) noexcept;
        static void mathcall GetUIntZ(uint32_t* value, Vector4 v) noexcept;
        static void mathcall GetUIntW(uint32_t* value, Vector4 v) noexcept;

    public:
        static Vector4 mathcall SetUIntByIndex(Vector4 v, uint32_t value, size_t index) noexcept;
        static Vector4 mathcall SetUIntByIndex(Vector4 v, const uint32_t* value, size_t index) noexcept;

        static Vector4 mathcall SetUIntX(Vector4 v, uint32_t x) noexcept;
        static Vector4 mathcall SetUIntY(Vector4 v, uint32_t y) noexcept;
        static Vector4 mathcall SetUIntZ(Vector4 v, uint32_t z) noexcept;
        static Vector4 mathcall SetUIntW(Vector4 v, uint32_t w) noexcept;

        static Vector4 mathcall SetUIntX(Vector4 v, const uint32_t* x) noexcept;
        static Vector4 mathcall SetUIntY(Vector4 v, const uint32_t* y) noexcept;
        static Vector4 mathcall SetUIntZ(Vector4 v, const uint32_t* z) noexcept;
        static Vector4 mathcall SetUIntW(Vector4 v, const uint32_t* w) noexcept;

    public:
        template <SwizzleMask Mask>
        static Vector4 mathcall Swizzle(Vector4 v) noexcept;

        template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
        static Vector4 mathcall Swizzle(Vector4 v) noexcept;

        static Vector4 mathcall Swizzle(Vector4 v, uint32_t element0, uint32_t element1, uint32_t element2, uint32_t element3) noexcept;


    public:
        template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
        static Vector4 mathcall Permute(Vector4 v1, Vector4 v2) noexcept;

        static Vector4 mathcall Permute(Vector4 v1, Vector4 v2, uint32_t permute_x, uint32_t permute_y, uint32_t permute_z, uint32_t permute_w) noexcept;

    public:
        static Vector4 mathcall SelectControl(uint32_t index0, uint32_t index1, uint32_t index2, uint32_t index3) noexcept;
        static Vector4 mathcall Select(Vector4 v1, Vector4 v2, Vector4 control) noexcept;
        static Vector4 mathcall MergeXY(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MergeZW(Vector4 v1, Vector4 v2) noexcept;

    public:
        template <uint32_t Elements>
        static Vector4 mathcall ShiftLeft(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall ShiftLeft(Vector4 v1, Vector4 v2, uint32_t elements) noexcept;

        template <uint32_t Elements>
        static Vector4 mathcall RotateLeft(Vector4 v) noexcept;
        static Vector4 mathcall RotateLeft(Vector4 v, uint32_t elements) noexcept;

        template <uint32_t Elements>
        static Vector4 mathcall RotateRight(Vector4 v) noexcept;
        static Vector4 mathcall RotateRight(Vector4 v, uint32_t elements) noexcept;

    public:
        template <InsertMask Mask>
        static Vector4 mathcall Insert(Vector4 destination, Vector4 source);
        static Vector4 mathcall Insert(Vector4 destination, Vector4 source, uint32_t select0, uint32_t select1, uint32_t select2, uint32_t select3) noexcept;
        static Vector4 mathcall Insert(Vector4 destination, Vector4 source, uint32_t rotate_left_elements, uint32_t select0, uint32_t select1, uint32_t select2, uint32_t select3) noexcept;

    public:
        static Vector4 mathcall CompareEqual(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall CompareEqual(Vector4 v1, Vector4 v2, Vector4 epsilon) noexcept;
        static Vector4 mathcall CompareNotEqual(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall CompareGreater(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall CompareGreaterEqual(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall CompareLess(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall CompareLessEqual(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall CompareInBounds(Vector4 v, Vector4 bounds) noexcept;

        static Vector4 mathcall CompareIsNaN(Vector4 v) noexcept;
        static Vector4 mathcall CompareIsInfinite(Vector4 v) noexcept;

    public:
        static Vector4 mathcall MaskCompareEqual(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MaskCompareNotEqual(Vector4 v1, Vector4 v2) noexcept;

    public:
        static bool mathcall IsEqual(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall IsEqual(Vector4 v1, Vector4 v2, Vector4 epsilon) noexcept;
        static bool mathcall IsNotEqual(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall IsGreater(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall IsGreaterEqual(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall IsLess(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall IsLessEqual(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall InBounds(Vector4 v, Vector4 bounds) noexcept;
        static bool mathcall IsNaN(Vector4 v) noexcept;
        static bool mathcall IsInfinite(Vector4 v) noexcept;

    public:
        static bool mathcall IsEqualUInt(Vector4 v1, Vector4 v2) noexcept;
        static bool mathcall IsNotEqualUInt(Vector4 v1, Vector4 v2) noexcept;

    public:
        static Vector4 mathcall SwapEndian(Vector4 v) noexcept;

    public:
        static Vector4 mathcall Zero() noexcept;
        static Vector4 mathcall One() noexcept;
        static Vector4 mathcall Infinity() noexcept;
        static Vector4 mathcall NaN() noexcept;
        static Vector4 mathcall Epsilon() noexcept;
        static Vector4 mathcall SignMask() noexcept;

        static Vector4 mathcall UnitX() noexcept;
        static Vector4 mathcall UnitY() noexcept;
        static Vector4 mathcall UnitZ() noexcept;
        static Vector4 mathcall UnitW() noexcept;

        static Vector4 mathcall NegativeUnitX() noexcept;
        static Vector4 mathcall NegativeUnitY() noexcept;
        static Vector4 mathcall NegativeUnitZ() noexcept;
        static Vector4 mathcall NegativeUnitW() noexcept;

    public:
        static Vector4 mathcall MaskTrue() noexcept;
        static Vector4 mathcall MaskFalse() noexcept;

        static Vector4 mathcall MaskAndUInt(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MaskAndCUInt(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MaskOrUInt(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MaskNorUInt(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MaskXorUInt(Vector4 v1, Vector4 v2) noexcept;

    public:
        static Vector4 mathcall Min(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Max(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Round(Vector4 v) noexcept;
        static Vector4 mathcall Truncate(Vector4 v) noexcept;
        static Vector4 mathcall Floor(Vector4 v) noexcept;
        static Vector4 mathcall Ceiling(Vector4 v) noexcept;
        static Vector4 mathcall Fract(Vector4 v) noexcept;
        static Vector4 mathcall Clamp(Vector4 v, Vector4 min, Vector4 max) noexcept;
        static Vector4 mathcall Saturate(Vector4 v) noexcept;

    public:
        static Vector4 mathcall Negate(Vector4 v) noexcept;
        static Vector4 mathcall Add(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Sum(Vector4 v) noexcept;
        static Vector4 mathcall AddAngles(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Subtract(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall SubtractAngles(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Multiply(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall MultiplyAdd(Vector4 v1, Vector4 v2, Vector4 v3) noexcept;
        static Vector4 mathcall Divide(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall NegativeMultiplySubtract(Vector4 v1, Vector4 v2, Vector4 v3) noexcept;
        static Vector4 mathcall Scale(Vector4 v, float scale) noexcept;
        static Vector4 mathcall ReciprocalEst(Vector4 v) noexcept;
        static Vector4 mathcall Reciprocal(Vector4 v) noexcept;
        static Vector4 mathcall SqrtEst(Vector4 v) noexcept;
        static Vector4 mathcall Sqrt(Vector4 v) noexcept;
        static Vector4 mathcall ReciprocalSqrtEst(Vector4 v) noexcept;
        static Vector4 mathcall ReciprocalSqrt(Vector4 v) noexcept;
        static Vector4 mathcall Exp2(Vector4 v) noexcept;
        static Vector4 mathcall ExpE(Vector4 v) noexcept;
        static Vector4 mathcall Exp(Vector4 v) noexcept;
        static Vector4 mathcall Log2(Vector4 v) noexcept;
        static Vector4 mathcall LogE(Vector4 v) noexcept;
        static Vector4 mathcall Log(Vector4 v) noexcept;
        static Vector4 mathcall Pow(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Abs(Vector4 v) noexcept;
        static Vector4 mathcall Mod(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall ModAngles(Vector4 angles) noexcept;
        static Vector4 mathcall Sin(Vector4 v) noexcept;
        static Vector4 mathcall Cos(Vector4 v) noexcept;
        static void mathcall SinCos(Vector4* out_sin, Vector4* out_cos, Vector4 v) noexcept;
        static Vector4 mathcall Tan(Vector4 v) noexcept;
        static Vector4 mathcall SinH(Vector4 v) noexcept;
        static Vector4 mathcall CosH(Vector4 v) noexcept;
        static Vector4 mathcall TanH(Vector4 v) noexcept;
        static Vector4 mathcall ASin(Vector4 v) noexcept;
        static Vector4 mathcall ACos(Vector4 v) noexcept;
        static Vector4 mathcall ATan(Vector4 v) noexcept;
        static Vector4 mathcall ATan2(Vector4 y, Vector4 x) noexcept;
        static Vector4 mathcall SinEst(Vector4 v) noexcept;
        static Vector4 mathcall CosEst(Vector4 v) noexcept;
        static void mathcall SinCosEst(Vector4* out_sin, Vector4* out_cos, Vector4 v) noexcept;
        static Vector4 mathcall TanEst(Vector4 v) noexcept;
        static Vector4 mathcall ASinEst(Vector4 v) noexcept;
        static Vector4 mathcall ACosEst(Vector4 v) noexcept;
        static Vector4 mathcall ATanEst(Vector4 v) noexcept;
        static Vector4 mathcall ATan2Est(Vector4 y, Vector4 x) noexcept;

    public:
        static Vector4 mathcall Lerp(Vector4 v0, Vector4 v1, float t) noexcept;
        static Vector4 mathcall Lerp(Vector4 v0, Vector4 v1, Vector4 t) noexcept;
        static Vector4 mathcall Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, float t) noexcept;
        static Vector4 mathcall Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, Vector4 t) noexcept;
        static Vector4 mathcall CatmullRom(Vector4 position0, Vector4 position1, Vector4 position2, Vector4 position3, float t) noexcept;
        static Vector4 mathcall CatmullRom(Vector4 position0, Vector4 position1, Vector4 position2, Vector4 position3, Vector4 t) noexcept;
        static Vector4 mathcall Barycentric(Vector4 position0, Vector4 position1, Vector4 position2, float f, float g) noexcept;
        static Vector4 mathcall Barycentric(Vector4 position0, Vector4 position1, Vector4 position2, Vector4 f, Vector4 g) noexcept;

    public:
        static Vector4 mathcall Dot(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Cross(Vector4 v1, Vector4 v2, Vector4 v3) noexcept;
        static Vector4 mathcall LengthSquared(Vector4 v) noexcept;
        static Vector4 mathcall ReciprocalLengthEst(Vector4 v) noexcept;
        static Vector4 mathcall ReciprocalLength(Vector4 v) noexcept;
        static Vector4 mathcall LengthEst(Vector4 v) noexcept;
        static Vector4 mathcall Length(Vector4 v) noexcept;
        static Vector4 mathcall NormalizeEst(Vector4 v) noexcept;
        static Vector4 mathcall Normalize(Vector4 v) noexcept;
        static Vector4 mathcall ClampLength(Vector4 v, float min, float max) noexcept;
        static Vector4 mathcall ClampLength(Vector4 v, Vector4 min, Vector4 max) noexcept;
        static Vector4 mathcall Reflect(Vector4 incident, Vector4 normal) noexcept;
        static Vector4 mathcall Refract(Vector4 incident, Vector4 normal, float refraction_index) noexcept;
        static Vector4 mathcall Refract(Vector4 incident, Vector4 normal, Vector4 refraction_index) noexcept;
        static Vector4 mathcall Orthogonal(Vector4 v) noexcept;
        static Vector4 mathcall AngleBetweenNormalsEst(Vector4 n1, Vector4 n2) noexcept;
        static Vector4 mathcall AngleBetweenNormals(Vector4 n1, Vector4 n2) noexcept;
        static Vector4 mathcall AngleBetweenVectors(Vector4 v1, Vector4 v2) noexcept;
        static Vector4 mathcall Transform(Vector4 v, Matrix m) noexcept;

    public:
        static Vector4 mathcall FresnelTerm(Vector4 cos_incident_angle, Vector4 refraction_index) noexcept;

    public:
        static Vector4 mathcall ConvertIntToFloat(Vector4 vint, uint32_t div_exponent) noexcept;
        static Vector4 mathcall ConvertFloatToInt(Vector4 vfloat, uint32_t mul_exponent) noexcept;
        static Vector4 mathcall ConvertUIntToFloat(Vector4 vuint, uint32_t div_exponent) noexcept;
        static Vector4 mathcall ConvertFloatToUInt(Vector4 vfloat, uint32_t mul_exponent) noexcept;

    public:
        static bool mathcall AnyTrue(Vector4 v) noexcept;
        static bool mathcall AnyFalse(Vector4 v) noexcept;
        static bool mathcall AllTrue(Vector4 v) noexcept;
        static bool mathcall AllFalse(Vector4 v) noexcept;
    };
    static_assert(std::is_nothrow_move_constructible_v<Vector4>);
    static_assert(std::is_nothrow_move_assignable_v<Vector4>);
    static_assert(std::is_trivial_v<Vector4>);

#if GRAPHYTE_MATH_ENABLE_OPERATORS

    mathinline bool mathcall operator== (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::IsEqual(v1, v2);
    }

    mathinline bool mathcall operator!= (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::IsNotEqual(v1, v2);
    }

    mathinline bool mathcall operator< (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::IsLess(v1, v2);
    }

    mathinline bool mathcall operator<= (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::IsLessEqual(v1, v2);
    }

    mathinline bool mathcall operator> (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::IsGreater(v1, v2);
    }

    mathinline bool mathcall operator>= (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::IsGreaterEqual(v1, v2);
    }

    mathinline Vector4 mathcall operator+ (Vector4 v) noexcept
    {
        return v;
    }

    mathinline Vector4 mathcall operator- (Vector4 v) noexcept
    {
        return Vector4::Negate(v);
    }

    mathinline Vector4 mathcall operator+ (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::Add(v1, v2);
    }

    mathinline Vector4 mathcall operator- (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::Subtract(v1, v2);
    }

    mathinline Vector4 mathcall operator* (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::Multiply(v1, v2);
    }

    mathinline Vector4 mathcall operator* (float scalar, Vector4 v) noexcept
    {
        return Vector4::Scale(v, scalar);
    }

    mathinline Vector4 mathcall operator* (Vector4 v, float scalar) noexcept
    {
        return Vector4::Scale(v, scalar);
    }

    mathinline Vector4 mathcall operator/ (Vector4 v1, Vector4 v2) noexcept
    {
        return Vector4::Divide(v1, v2);
    }

    mathinline Vector4 mathcall operator/ (Vector4 v, float scalar) noexcept
    {
        return Vector4::Divide(v, Vector4::Make(scalar));
    }

    mathinline Vector4 mathcall operator/ (float scalar, Vector4 v) noexcept
    {
        return Vector4::Divide(Vector4::Make(scalar), v);
    }

    mathinline Vector4& mathcall operator+= (Vector4& v1, Vector4 v2) noexcept
    {
        v1 = Vector4::Add(v1, v2);
        return v1;
    }

    mathinline Vector4& mathcall operator-= (Vector4& v1, Vector4 v2) noexcept
    {
        v1 = Vector4::Subtract(v1, v2);
        return v1;
    }

    mathinline Vector4& mathcall operator*= (Vector4& v1, Vector4 v2) noexcept
    {
        v1 = Vector4::Multiply(v1, v2);
        return v1;
    }

    mathinline Vector4& mathcall operator*= (Vector4& v, float scalar) noexcept
    {
        v = Vector4::Scale(v, scalar);
        return v;
    }

    mathinline Vector4& mathcall operator/= (Vector4& v1, Vector4 v2) noexcept
    {
        v1 = Vector4::Divide(v1, v2);
        return v1;
    }

    mathinline Vector4& mathcall operator/= (Vector4& v, float scalar) noexcept
    {
        v = Vector4::Divide(v, Vector4::Make(scalar));
        return v;
    }

#endif
}

#include <Graphyte/Maths/Vector4.impl.hxx>
