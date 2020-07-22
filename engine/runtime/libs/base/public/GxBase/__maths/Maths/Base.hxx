#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/TypeTraits.hxx>
#include <GxBase/Ieee754.hxx>

// =================================================================================================
//
// `mathcall` definition
//

#if GRAPHYTE_HAVE_VECTORCALL
#define mathcall __vectorcall
#elif GRAPHYTE_COMPILER_MSVC
#define mathcall __fastcall
#else
#define mathcall
#endif


// =================================================================================================
//
// `mathinline` and `mathconst` definitions
//

#if GRAPHYTE_COMPILER_MSVC
#define mathinline __forceinline
// XXX: Check when we may make it `constexpr const` instead
#define mathconst extern const __declspec(selectany)
#elif GRAPHYTE_COMPILER_CLANG
#define mathinline inline __attribute__((__always_inline__))
#define mathconst  constexpr const
#else
#define mathinline inline __attribute__((__artificial__, __always_inline__))
#define mathconst  constexpr const
#endif


// =================================================================================================
//
// Native vector type.
//

namespace Graphyte::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) NativeFloat32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
    struct alignas(16) NativeUInt32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
#elif GRAPHYTE_HW_NEON
    using NativeFloat32x4 = float32x4_t;
    using NativeUInt32x4  = uint32x4_t;
#elif GRAPHYTE_HW_AVX
    using NativeFloat32x4 = __m128;
    using NativeUInt32x4  = __m128i;
#else
#error Unknown architecture
#endif

    static_assert(alignof(NativeFloat32x4) == 16);
    static_assert(sizeof(NativeFloat32x4) == 16);

    static_assert(alignof(NativeUInt32x4) == 16);
    static_assert(sizeof(NativeUInt32x4) == 16);
}


// =================================================================================================
//
// Native matrix type
//

namespace Graphyte::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) NativeFloat32x4x4 final
    {
        union
        {
            NativeFloat32x4 R[4];
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
                float M41, M42, M43, M44;
            };
            float M[4][4];
            float F[16];
        };
    };

#else
    struct alignas(16) NativeFloat32x4x4 final
    {
        NativeFloat32x4 R[4];
    };
#endif

    static_assert(alignof(NativeFloat32x4x4) == 16);
    static_assert(sizeof(NativeFloat32x4x4) == 64);
}


// =================================================================================================
//
// Constant types
//

namespace Graphyte::Impl
{
    struct alignas(16) ConstFloat32x4 final
    {
        union
        {
            alignas(16) float F[4];
            NativeFloat32x4 V;
        };
    };

    static_assert(std::is_trivially_copyable_v<ConstFloat32x4>);
    static_assert(std::is_standard_layout_v<ConstFloat32x4>);
    static_assert(alignof(ConstFloat32x4) == 16);
    static_assert(sizeof(ConstFloat32x4) == 16);

    struct alignas(16) ConstInt32x4 final
    {
        union
        {
            alignas(16) int32_t I[4];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };

    static_assert(std::is_trivially_copyable_v<ConstInt32x4>);
    static_assert(std::is_standard_layout_v<ConstInt32x4>);
    static_assert(alignof(ConstInt32x4) == 16);
    static_assert(sizeof(ConstInt32x4) == 16);

    struct alignas(16) ConstUInt32x4 final
    {
        union
        {
            alignas(16) uint32_t U[4];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };
    static_assert(std::is_trivially_copyable_v<ConstUInt32x4>);
    static_assert(std::is_standard_layout_v<ConstUInt32x4>);
    static_assert(alignof(ConstUInt32x4) == 16);
    static_assert(sizeof(ConstUInt32x4) == 16);

    struct alignas(16) ConstUInt8x16 final
    {
        union
        {
            alignas(16) uint8_t U[16];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };
    static_assert(std::is_trivially_copyable_v<ConstUInt8x16>);
    static_assert(std::is_standard_layout_v<ConstUInt8x16>);
    static_assert(alignof(ConstUInt8x16) == 16);
    static_assert(sizeof(ConstUInt8x16) == 16);
}


// =================================================================================================
//
// Scalar constants
//

namespace Graphyte::Impl
{
    template <typename T>
    inline constexpr const T ConstE = static_cast<T>(2.71828182845904523536028747135266249775724709369996);
    template <typename T>
    inline constexpr const T ConstLog2E = static_cast<T>(1.44269504088896340735992468100189213742664595415299);
    template <typename T>
    inline constexpr const T ConstLog10E = static_cast<T>(0.43429448190325182765112891891660508229439700580367);
    template <typename T>
    inline constexpr const T ConstLn2 = static_cast<T>(0.69314718055994530941723212145817656807550013436026);
    template <typename T>
    inline constexpr const T ConstLn10 = static_cast<T>(2.30258509299404568401799145468436420760110148862877);
    template <typename T>
    inline constexpr const T ConstPi = static_cast<T>(3.14159265358979323846264338327950288419716939937510);
    template <typename T>
    inline constexpr const T ConstPi2 = static_cast<T>(6.28318530717958647692528676655900576839433879875021);
    template <typename T>
    inline constexpr const T ConstInvPi = static_cast<T>(0.31830988618379067153776752674502872406891929148091);
    template <typename T>
    inline constexpr const T ConstInvPi2 = static_cast<T>(0.15915494309189533576888376337251436203445964574045);
    template <typename T>
    inline constexpr const T ConstInvSqrtPi = static_cast<T>(0.56418958354775628694807945156077258584405062932899);
    template <typename T>
    inline constexpr const T ConstSqrt2 = static_cast<T>(1.41421356237309504880168872420969807856967187537695);
    template <typename T>
    inline constexpr const T ConstSqrt3 = static_cast<T>(1.73205080756887729352744634150587236694280525381038);
    template <typename T>
    inline constexpr const T ConstSqrt5 = static_cast<T>(2.23606797749978969640917366873127623544061835961153);
    template <typename T>
    inline constexpr const T ConstInvSqrt2 = static_cast<T>(0.70710678118654752440084436210484903928483593768847);
    template <typename T>
    inline constexpr const T ConstInvSqrt3 = static_cast<T>(0.57735026918962576450914878050195745564760175127013);
    template <typename T>
    inline constexpr const T ConstInvSqrt5 = static_cast<T>(0.44721359549995793928183473374625524708812367192231);
    template <typename T>
    inline constexpr const T ConstPhi = static_cast<T>(1.61803398874989484820458683436563811772030917980576);
    template <typename T>
    inline constexpr const T ConstGamma = static_cast<T>(0.57721566490153286060651209008240243104215933593992);
    template <typename T>
    inline constexpr const T ConstPiDiv2 = static_cast<T>(1.57079632679489661923132169163975144209858469968755);
    template <typename T>
    inline constexpr const T ConstPiDiv3 = static_cast<T>(1.04719755119659774615421446109316762806572313312504);
    template <typename T>
    inline constexpr const T ConstPiDiv4 = static_cast<T>(0.78539816339744830961566084581987572104929234984378);
    template <typename T>
    inline constexpr const T ConstPiDiv6 = static_cast<T>(0.52359877559829887307710723054658381403286156656252);
    template <typename T>
    inline constexpr const T ConstPiDiv8 = static_cast<T>(0.39269908169872415480783042290993786052464617492189);

    template <typename T>
    inline constexpr const T ConstEpsilonAngular = static_cast<T>(0.001);
    template <typename T>
    inline constexpr const T ConstEpsilonLow = static_cast<T>(0.0002);
    template <typename T>
    inline constexpr const T ConstEpsilon = static_cast<T>(0.000035);
    template <typename T>
    inline constexpr const T ConstEpsilonHigh = static_cast<T>(0.0000005);

    inline constexpr const uint32_t SELECT_0      = 0x00000000u;
    inline constexpr const uint32_t SELECT_1      = 0xFFFFFFFFu;
    inline constexpr const size_t CACHE_LINE_SIZE = 64;

    template <typename T>
    inline constexpr const T RoundingError = Graphyte::InvalidType<T>{};

    template <>
    inline constexpr const int32_t RoundingError<int32_t> = 0;
    template <>
    inline constexpr const int64_t RoundingError<int64_t> = 0;
    template <>
    inline constexpr const uint32_t RoundingError<uint32_t> = 0;
    template <>
    inline constexpr const uint64_t RoundingError<uint64_t> = 0;
    template <>
    inline constexpr const float RoundingError<float> = 0.000001f;
    template <>
    inline constexpr const double RoundingError<double> = 0.00000001;
}

#if false
namespace Graphyte::Impl
{
    template <typename T> constexpr const T PI = T(3.14159265358979323846264338327950288419716939937510);
    template <typename T> constexpr const T PI2 = T(6.28318530717958647692528676655900576839433879875021);
    template <typename T> constexpr const T ONE_OVER_PI = T(0.31830988618379067153776752674502872406891929148091);
    template <typename T> constexpr const T ONE_OVER_PI2 = T(0.15915494309189533576888376337251436203445964574046);
    template <typename T> constexpr const T PI_OVER_2 = T(1.57079632679489661923132169163975144209858469968755);
    template <typename T> constexpr const T PI_OVER_3 = T(1.04719755119659774615421446109316762806572313312504);
    template <typename T> constexpr const T PI_OVER_4 = T(0.78539816339744830961566084581987572104929234984378);
    template <typename T> constexpr const T PI_OVER_6 = T(0.52359877559829887307710723054658381403286156656252);
    template <typename T> constexpr const T PI_OVER_8 = T(0.39269908169872415480783042290993786052464617492189);
    template <typename T> constexpr const T E = T(2.71828182845904523536028747135266249775724709369996);
    template <typename T> constexpr const T LOG_2_E = T(1.44269504088896340735992468100189213742664595415299);
    template <typename T> constexpr const T LOG_10_E = T(0.43429448190325182765112891891660508229439700580367);
    template <typename T> constexpr const T LN_2 = T(0.69314718055994530941723212145817656807550013436026);
    template <typename T> constexpr const T LN_10 = T(2.30258509299404568401799145468436420760110148862877);
    template <typename T> constexpr const T ONE_OVER_LN_2 = T(1.44269504088896340735992468100189213742664595415299);
    template <typename T> constexpr const T PHI = T(1.61803398874989484820458683436563811772030917980576);
    template <typename T> constexpr const T GAMMA = T(0.57721566490153286060651209008240243104215933593992);
    template <typename T> constexpr const T SQRT_OF_2 = T(1.41421356237309504880168872420969807856967187537695);
    template <typename T> constexpr const T SQRT_OF_3 = T(1.73205080756887729352744634150587236694280525381038);
    template <typename T> constexpr const T SQRT_OF_5 = T(2.23606797749978969640917366873127623544061835961153);
    template <typename T> constexpr const T ONE_OVER_SQRT_OF_2 = T(0.70710678118654752440084436210484903928483593768847);
    template <typename T> constexpr const T ONE_OVER_SQRT_OF_3 = T(0.57735026918962576450914878050195745564760175127013);
    template <typename T> constexpr const T ONE_OVER_SQRT_OF_5 = T(0.44721359549995793928183473374625524708812367192231);
}
#endif

// =================================================================================================
//
// Vector constants
//

namespace Graphyte::Impl
{
    // clang-format off
    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_X = { { { 1.0f, 0.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_Y = { { { 0.0f, 1.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_Z = { { { 0.0f, 0.0f, 1.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_W = { { { 0.0f, 0.0f, 0.0f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_X = { { { -1.0f, 0.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_Y = { { { 0.0f, -1.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_Z = { { { 0.0f, 0.0f, -1.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_W = { { { 0.0f, 0.0f, 0.0f, -1.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATE_X = { { { -1.0f, 1.0f, 1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATE_Y = { { { 1.0f, -1.0f, 1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATE_Z = { { { 1.0f, 1.0f, -1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATE_W = { { { 1.0f, 1.0f, 1.0f, -1.0f, } } };
    mathconst ConstFloat32x4 VEC4_ZERO_4 = { { { 0.0f, 0.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_ONE_4 = { { { 1.0f, 1.0f, 1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_ONE_3 = { { { 1.0f, 1.0f, 1.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_ONE_4 = { { { -1.0f, -1.0f, -1.0f, -1.0f, } } };
    mathconst ConstFloat32x4 VEC4_ONE_HALF_4 = { { { 0.5f, 0.5f, 0.5f, 0.5f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_ONE_HALF_4 = { { { -0.5f, -0.5f, -0.5f, -0.5f, } } };
    mathconst ConstFloat32x4 VEC4_HALF_4 = { { { 0.5f, 0.5f, 0.5f, 0.5f, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_HALF_4 = { { { -0.5f, -0.5f, -0.5f, -0.5f, } } };
    mathconst ConstFloat32x4 VEC4_TWO_4 = { { { 2.0f, 2.0f, 2.0f, 2.0f, } } };
    mathconst ConstFloat32x4 VEC4_FOUR_4 = { { { 4.0f, 4.0f, 4.0f, 4.0f, } } };
    mathconst ConstFloat32x4 VEC4_SIX_4 = { { { 6.0f, 6.0f, 6.0f, 6.0f, } } };
    mathconst ConstUInt32x4 VEC4_NEGATIVE_ZERO = { { { 0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u, } } };
    mathconst ConstUInt32x4 VEC4_NEGATIVE_ZERO_3 = { { { 0x80000000u, 0x80000000u, 0x80000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_INFINITY = { { { FloatTraits<float>::Infinity, FloatTraits<float>::Infinity, FloatTraits<float>::Infinity, FloatTraits<float>::Infinity, } } };
    mathconst ConstUInt32x4 VEC4_QNAN = { { { FloatTraits<float>::QNaN, FloatTraits<float>::QNaN, FloatTraits<float>::QNaN, FloatTraits<float>::QNaN, } } };
    mathconst ConstUInt32x4 VEC4_QNAN_TEST = { { { FloatTraits<float>::Mantissa, FloatTraits<float>::Mantissa, FloatTraits<float>::Mantissa, FloatTraits<float>::Mantissa, } } };
    mathconst ConstUInt32x4 VEC4_FLOAT_MIN = { { { FloatTraits<float>::MinNormal, FloatTraits<float>::MinNormal, FloatTraits<float>::MinNormal, FloatTraits<float>::MinNormal, } } };
    mathconst ConstUInt32x4 VEC4_FLOAT_MAX = { { { FloatTraits<float>::Max, FloatTraits<float>::Max, FloatTraits<float>::Max, FloatTraits<float>::Max, } } };
    mathconst ConstFloat32x4 VEC4_EPSILON = { { { 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, } } };
    mathconst ConstFloat32x4 VEC4_NO_FRACTION = { { { 8388608.0f, 8388608.0f, 8388608.0f, 8388608.0f, } } };
    mathconst ConstUInt32x4 VEC4_ONE_HALF_MINUS_EPS = { { { 0x3EFFFFFDu, 0x3EFFFFFDu, 0x3EFFFFFDu, 0x3EFFFFFDu, } } };
    mathconst ConstFloat32x4 VEC4_2PI = { { { ConstPi2<float>, ConstPi2<float>, ConstPi2<float>, ConstPi2<float>, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_2PI = { { { -ConstPi2<float>, -ConstPi2<float>, -ConstPi2<float>, -ConstPi2<float>, } } };
    mathconst ConstFloat32x4 VEC4_RECIPROCAL_2PI = { { { ConstInvPi2<float>, ConstInvPi2<float>, ConstInvPi2<float>, ConstInvPi2<float>, } } };
    mathconst ConstFloat32x4 VEC4_PI = { { { ConstPi<float>, ConstPi<float>, ConstPi<float>, ConstPi<float>, } } };
    mathconst ConstFloat32x4 VEC4_NEGATIVE_PI = { { { -ConstPi<float>, -ConstPi<float>, -ConstPi<float>, -ConstPi<float>, } } };
    mathconst ConstFloat32x4 VEC4_RECIPROCAL_PI = { { { ConstInvPi<float>, ConstInvPi<float>, ConstInvPi<float>, ConstInvPi<float>, } } };
    mathconst ConstFloat32x4 VEC4_HALF_PI = { { { ConstPi<float> / 2.0f, ConstPi<float> / 2.0f, ConstPi<float> / 2.0f, ConstPi<float> / 2.0f, } } };
    mathconst ConstFloat32x4 VEC4_UNIT_EPSILON = { { { 1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f, } } };

    // sin cos log exp implementation: http://gruntthepeon.free.fr/ssemath/
    mathconst ConstFloat32x4 VEC4_PI_CONSTANTS_0 = { { { ConstPi<float>, ConstPi2<float>, ConstInvPi<float>, ConstInvPi2<float>, } } };
    mathconst ConstFloat32x4 VEC4_SIN_COEFFICIENTS_0 = { { { -0.16666667f, +0.0083333310f, -0.00019840874f, +2.7525562e-06f, } } };
    mathconst ConstFloat32x4 VEC4_SIN_COEFFICIENTS_1 = { { { -2.3889859e-08f, -0.16665852f, +0.0083139502f, -0.00018524670f, } } };
    mathconst ConstFloat32x4 VEC4_COS_COEFFICIENTS_0 = { { { -0.5f, +0.041666638f, -0.0013888378f, +2.4760495e-05f, } } };
    mathconst ConstFloat32x4 VEC4_COS_COEFFICIENTS_1 = { { { -2.6051615e-07f, -0.49992746f, +0.041493919f, -0.0012712436f, } } };
    mathconst ConstFloat32x4 VEC4_TAN_COEFFICIENTS_0 = { { { 1.0f, 0.333333333f, 0.133333333f, 5.396825397e-2f, } } };
    mathconst ConstFloat32x4 VEC4_TAN_COEFFICIENTS_1 = { { { 2.186948854e-2f, 8.863235530e-3f, 3.592128167e-3f, 1.455834485e-3f, } } };
    mathconst ConstFloat32x4 VEC4_TAN_COEFFICIENTS_2 = { { { 5.900274264e-4f, 2.391290764e-4f, 9.691537707e-5f, 3.927832950e-5f, } } };
    mathconst ConstFloat32x4 VEC4_ARC_COEFFICIENTS_0 = { { { +1.5707963050f, -0.2145988016f, +0.0889789874f, -0.0501743046f, } } };
    mathconst ConstFloat32x4 VEC4_ARC_COEFFICIENTS_1 = { { { +0.0308918810f, -0.0170881256f, +0.0066700901f, -0.0012624911f, } } };
    mathconst ConstFloat32x4 VEC4_ATAN_COEFFICIENTS_0 = { { { -0.3333314528f, +0.1999355085f, -0.1420889944f, +0.1065626393f, } } };
    mathconst ConstFloat32x4 VEC4_ATAN_COEFFICIENTS_1 = { { { -0.0752896400f, +0.0429096138f, -0.0161657367f, +0.0028662257f, } } };
    mathconst ConstFloat32x4 VEC4_ATAN_EST_COEFFICIENTS_0 = { { { +0.999866f, +0.999866f, +0.999866f, +0.999866f, } } };
    mathconst ConstFloat32x4 VEC4_ATAN_EST_COEFFICIENTS_1 = { { { -0.3302995f, +0.180141f, -0.085133f, +0.0208351f, } } };
    mathconst ConstFloat32x4 VEC4_TAN_EST_COEFFICIENTS_0 = { { { 2.484f, -1.954923183e-1f, 2.467401101f, ConstInvPi<float>, } } };
    mathconst ConstFloat32x4 VEC4_ARC_EST_COEFFICIENTS_0 = { { { +1.5707288f, -0.2121144f, +0.0742610f, -0.0187293f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_1 = { { { -6.93147182e-1f, -6.93147182e-1f, -6.93147182e-1f, -6.93147182e-1f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_2 = { { { +2.40226462e-1f, +2.40226462e-1f, +2.40226462e-1f, +2.40226462e-1f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_3 = { { { -5.55036440e-2f, -5.55036440e-2f, -5.55036440e-2f, -5.55036440e-2f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_4 = { { { +9.61597636e-3f, +9.61597636e-3f, +9.61597636e-3f, +9.61597636e-3f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_5 = { { { -1.32823968e-3f, -1.32823968e-3f, -1.32823968e-3f, -1.32823968e-3f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_6 = { { { +1.47491097e-4f, +1.47491097e-4f, +1.47491097e-4f, +1.47491097e-4f, } } };
    mathconst ConstFloat32x4 VEC4_EXP_EST_7 = { { { -1.08635004e-5f, -1.08635004e-5f, -1.08635004e-5f, -1.08635004e-5f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_0 = { { { +1.442693f, +1.442693f, +1.442693f, +1.442693f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_1 = { { { -0.721242f, -0.721242f, -0.721242f, -0.721242f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_2 = { { { +0.479384f, +0.479384f, +0.479384f, +0.479384f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_3 = { { { -0.350295f, -0.350295f, -0.350295f, -0.350295f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_4 = { { { +0.248590f, +0.248590f, +0.248590f, +0.248590f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_5 = { { { -0.145700f, -0.145700f, -0.145700f, -0.145700f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_6 = { { { +0.057148f, +0.057148f, +0.057148f, +0.057148f, } } };
    mathconst ConstFloat32x4 VEC4_LOG_EST_7 = { { { -0.010578f, -0.010578f, -0.010578f, -0.010578f, } } };
    mathconst ConstFloat32x4 VEC4_LGE = { { { +1.442695f, +1.442695f, +1.442695f, +1.442695f, } } };
    mathconst ConstFloat32x4 VEC4_INV_LGE = { { { +6.93147182e-1f, +6.93147182e-1f, +6.93147182e-1f, +6.93147182e-1f, } } };
    mathconst ConstUInt32x4 VEC4_MASK_QNAN = { { { FloatTraits<float>::Mantissa, FloatTraits<float>::Mantissa, FloatTraits<float>::Mantissa, FloatTraits<float>::Mantissa, } } };
    mathconst ConstUInt32x4 VEC4_MASK_ABS = { { { FloatTraits<float>::Sign, FloatTraits<float>::Sign, FloatTraits<float>::Sign, FloatTraits<float>::Sign, } } };
    mathconst ConstUInt32x4 VEC4_MASK_NEGATIVE_ONE = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 VEC4_MASK_COMPONENTS_3 = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_X = { { { 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_Y = { { { 0x00000000u, 0xFFFFFFFFu, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_Z = { { { 0x00000000u, 0x00000000u, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_W = { { { 0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_0101 = { { { 0x00000000u, 0xFFFFFFFFu, 0x00000000u, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1010 = { { { 0xFFFFFFFFu, 0x00000000u, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1000 = { { { 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_0001 = { { { 0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1100 = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1110 = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1011 = { { { 0xFFFFFFFFu, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 VEC4_MASK_A8R8G8B8 = { { { 0x00FF0000u, 0x0000FF00u, 0x000000FFu, 0xFF000000u, } } };
    mathconst ConstUInt32x4 VEC4_FLIP_A_A8R8G8B8 = { { { 0x00000000u, 0x00000000u, 0x00000000u, 0x80000000u, } } };
    mathconst ConstFloat32x4 VEC4_FIX_A_A8R8G8B8 = { { { 0.0f, 0.0f, 0.0f, static_cast<float>(0x80000000u), } } };
    mathconst ConstFloat32x4 VEC4_NORMALIZE_A8R8G8B8 = { { { 1.0f / (255.0f * static_cast<float>(0x10000u)), 1.0f / (255.0f * static_cast<float>(0x100u)), 1.0f / 255.0f, 1.0f / (255.0f * static_cast<float>(0x1000000u)), } } };
    mathconst ConstFloat32x4 VEC4_COLOR_SCALE = { { { 255.0f, 255.0f, 255.0f, 255.0f, } } };
    mathconst ConstFloat32x4 VEC4_COLOR_LUMINANCE = { { { 0.2125f, 0.7154f, 0.0721f, 0.0f, } } };
    mathconst ConstInt32x4 VEC4_EXPONENT_BIAS = { { { 127, 127, 127, 127, } } };
    mathconst ConstInt32x4 VEC4_SUBNORMAL_EXPONENT = { { { -126, -126, -126, -126, } } };
    mathconst ConstInt32x4 VEC4_NUM_TRAILING = { { { 23, 23, 23, 23, } } };
    mathconst ConstInt32x4 VEC4_MIN_NORMAL = { { { 
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
        } } };
    mathconst ConstUInt32x4 VEC4_NEGATIVE_INFINITY = { { {
            FloatTraits<float>::Sign | FloatTraits<float>::Infinity,
            FloatTraits<float>::Sign | FloatTraits<float>::Infinity,
            FloatTraits<float>::Sign | FloatTraits<float>::Infinity,
            FloatTraits<float>::Sign | FloatTraits<float>::Infinity,
        } } };
    mathconst ConstUInt32x4 VEC4_NEGATIVE_QNAN = { { {
            FloatTraits<float>::Sign | FloatTraits<float>::QNaN,
            FloatTraits<float>::Sign | FloatTraits<float>::QNaN,
            FloatTraits<float>::Sign | FloatTraits<float>::QNaN,
            FloatTraits<float>::Sign | FloatTraits<float>::QNaN,
        } } };
    mathconst ConstUInt32x4 VEC4_BIN_128 = { { { 0x43000000u, 0x43000000u, 0x43000000u, 0x43000000u, } } };
    mathconst ConstUInt32x4 VEC4_BIN_NEG_150 = { { { 0xC3160000u, 0xC3160000u, 0xC3160000u, 0xC3160000u, } } };
    mathconst ConstInt32x4 VEC4_VALUE253 = { { { 253, 253, 253, 253, } } };
    mathconst ConstFloat32x4 VEC4_MSRGB_SCALE = { { { 12.92f, 12.92f, 12.92f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_MSRGB_A = { { { 0.055f, 0.055f, 0.055f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_MSRGB_A1 = { { { 1.055f, 1.055f, 1.055f, 1.0f, } } };
    mathconst ConstFloat32x4 VEC4_UNSIGNED_FIX = { { { 32768.0f * 65536.0f, 32768.0f * 65536.0f, 32768.0f * 65536.0f, 32768.0f * 65536.0f, } } };
    mathconst ConstFloat32x4 VEC4_INTMAX = { { { 65536.0f * 32768.0f - 128.0f, 65536.0f * 32768.0f - 128.0f, 65536.0f * 32768.0f - 128.0f, 65536.0f * 32768.0f - 128.0f, } } };
    mathconst ConstFloat32x4 VEC4_UINTMAX = { { { 65536.0f * 65536.0f - 256.0f, 65536.0f * 65536.0f - 256.0f, 65536.0f * 65536.0f - 256.0f, 65536.0f * 65536.0f - 256.0f, } } };
    mathconst ConstUInt32x4 VEC4_MASK_FLIP_Y = { { { 0u, 0x80000000u, 0u, 0u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_FLIP_Z = { { { 0u, 0u, 0x80000000u, 0u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_FLIP_W = { { { 0u, 0u, 0u, 0x80000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_FLIP_YZ = { { { 0u, 0x80000000u, 0x80000000u, 0u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_FLIP_ZW = { { { 0u, 0u, 0x80000000u, 0x80000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_FLIP_YW = { { { 0u, 0x80000000u, 0u, 0x80000000u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_DEC4 = { { { 0x3FFu, 0x3FFu << 10u, 0x3FFu << 20u, 0x3u << 30u, } } };
    mathconst ConstUInt32x4 VEC4_MASK_XOR_DEC4 = { { { 0x200u, 0x200u << 10u, 0x200u << 20u, 0u, } } };
    mathconst ConstFloat32x4 VEC4_ADD_UDEC4 = { { { 0.0f, 0.0f, 0.0f, 32768.0f * 65536.0f, } } };
    mathconst ConstFloat32x4 VEC4_ADD_DEC4 = { { { -512.0f, -512.0f * 1024.0f, -512.0f * 1024.0f * 1024.0f, 0.0f, } } };
    mathconst ConstFloat32x4 VEC4_MUL_DEC4 = { { { 1.0f, 1.0f / 1024.0f, 1.0f / (1024.0f * 1024.0f), 1.0f / (1024.0f * 1024.0f * 1024.0f) } } };
    mathconst ConstFloat32x4 VEC4_UBYTE_MAX = { { { 255.0f, 255.0f, 255.0f, 255.0f, } } };
    mathconst ConstFloat32x4 VEC4_BYTE_MIN = { { { -127.0f, -127.0f, -127.0f, -127.0f, } } };
    mathconst ConstFloat32x4 VEC4_BYTE_MAX = { { { 127.0f, 127.0f, 127.0f, 127.0f, } } };
    mathconst ConstFloat32x4 VEC4_SHORT_MIN = { { { -32767.0f, -32767.0f, -32767.0f, -32767.0f, } } };
    mathconst ConstFloat32x4 VEC4_SHORT_MAX = { { { 32767.0f, 32767.0f, 32767.0f, 32767.0f, } } };
    mathconst ConstFloat32x4 VEC4_USHORT_MAX = { { { 65535.0f, 65535.0f, 65535.0f, 65535.0f, } } };
    // clang-format on
}


// =================================================================================================
//
// Include some internal specific implementation details.
//

#if !GRAPHYTE_MATH_NO_INTRINSICS
#if GRAPHYTE_HW_AVX
#include <GxBase/Maths/Impl/Avx.impl.hxx>
#elif GRAPHYTE_HW_NEON
#include <GxBase/Maths/Impl/Neon.impl.hxx>
#endif
#endif
