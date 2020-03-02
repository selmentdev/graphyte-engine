#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Half.hxx>

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
#define mathconst constexpr const
#else
#define mathinline inline __attribute__((__artificial__, __always_inline__))
#define mathconst constexpr const
#endif


// =================================================================================================
//
// Native vector type.
//

namespace Graphyte::Maths::Impl
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
    using NativeUInt32x4 = uint32x4_t;
#elif GRAPHYTE_HW_AVX
    using NativeFloat32x4 = __m128;
    using NativeUInt32x4 = __m128i;
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

namespace Graphyte::Maths::Impl
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

namespace Graphyte::Maths::Impl
{
    struct alignas(16) ConstFloat32x4 final
    {
        union
        {
            alignas(16) float F[4];
            NativeFloat32x4 V;
        };
    };

    static_assert(std::is_pod_v<ConstFloat32x4>);
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
    static_assert(std::is_pod_v<ConstInt32x4>);
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
    static_assert(std::is_pod_v<ConstUInt32x4>);
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
    static_assert(std::is_pod_v<ConstUInt8x16>);
    static_assert(alignof(ConstUInt8x16) == 16);
    static_assert(sizeof(ConstUInt8x16) == 16);
}


// =================================================================================================
//
// Scalar constants
//

namespace Graphyte::Maths::Impl
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

    template <typename T> constexpr const T EPSILON_ANGULAR = T(0.001);
    template <typename T> constexpr const T EPSILON_LOW = T(0.0002);
    template <typename T> constexpr const T EPSILON = T(0.000035);
    template <typename T> constexpr const T EPSILON_HIGH = T(0.0000005);

    template <typename T> constexpr const T TAU = PI2<T>;

    constexpr const uint32_t ROUNDING_ERROR_U32 = 0;
    constexpr const uint64_t ROUNDING_ERROR_U64 = 0;
    constexpr const int32_t ROUNDING_ERROR_I32 = 0;
    constexpr const int64_t ROUNDING_ERROR_I64 = 0;
    constexpr const float ROUNDING_ERROR_F32 = 0.000001F;
    constexpr const double ROUNDING_ERROR_F64 = 0.00000001;

    constexpr const uint32_t SELECT_0 = 0x00000000U;
    constexpr const uint32_t SELECT_1 = 0xffffffffU;
    constexpr const size_t CACHE_LINE_SIZE = 64;
}


// =================================================================================================
//
// Vector constants
//

namespace Graphyte::Maths::Impl
{
    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_X = { { {
            1.0F,
            0.0F,
            0.0F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_Y = { { {
            0.0F,
            1.0F,
            0.0F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_Z = { { {
            0.0F,
            0.0F,
            1.0F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_POSITIVE_UNIT_W = { { {
            0.0F,
            0.0F,
            0.0F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_X = { { {
            -1.0F,
            0.0F,
            0.0F,
            0.0F
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_Y = { { {
            0.0F,
            -1.0F,
            0.0F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_Z = { { {
            0.0F,
            0.0F,
            -1.0F,
            0.0F
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_UNIT_W = { { {
            0.0F,
            0.0F,
            0.0F,
            -1.0F
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATE_X = { { {
            -1.0F,
            1.0F,
            1.0F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATE_Y = { { {
            1.0F,
            -1.0F,
            1.0F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATE_Z = { { {
            1.0F,
            1.0F,
            -1.0F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATE_W = { { {
            1.0F,
            1.0F,
            1.0F,
            -1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_ZERO_4 = { { {
            0.0F,
            0.0F,
            0.0F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_ONE_4 = { { {
            1.0F,
            1.0F,
            1.0F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_ONE_3 = { { {
            1.0F,
            1.0F,
            1.0F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_ONE_4 = { { {
            -1.0F,
            -1.0F,
            -1.0F,
            -1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_ONE_HALF_4 = { { {
            0.5F,
            0.5F,
            0.5F,
            0.5F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_ONE_HALF_4 = { { {
            -0.5F,
            -0.5F,
            -0.5F,
            -0.5F,
        } } };

    mathconst ConstFloat32x4 VEC4_HALF_4 = { { {
            0.5F,
            0.5F,
            0.5F,
            0.5F,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_HALF_4 = { { {
            -0.5F,
            -0.5F,
            -0.5F,
            -0.5F,
        } } };

    mathconst ConstFloat32x4 VEC4_TWO_4 = { { {
            2.0F,
            2.0F,
            2.0F,
            2.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_FOUR_4 = { { {
            4.0F,
            4.0F,
            4.0F,
            4.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_SIX_4 = { { {
            6.0F,
            6.0F,
            6.0F,
            6.0F
        } } };

    mathconst ConstUInt32x4 VEC4_NEGATIVE_ZERO = { { {
            0x80000000,
            0x80000000,
            0x80000000,
            0x80000000,
        } } };

    mathconst ConstUInt32x4 VEC4_NEGATIVE_ZERO_3 = { { {
            0x80000000,
            0x80000000,
            0x80000000,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_INFINITY = { { {
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
        } } };

    mathconst ConstUInt32x4 VEC4_QNAN = { { {
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
        } } };

    mathconst ConstUInt32x4 VEC4_QNAN_TEST = { { {
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
        } } };

    mathconst ConstUInt32x4 VEC4_FLOAT_MIN = { { {
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
        } } };

    mathconst ConstUInt32x4 VEC4_FLOAT_MAX = { { {
            FloatTraits<float>::Max,
            FloatTraits<float>::Max,
            FloatTraits<float>::Max,
            FloatTraits<float>::Max,
        } } };

    mathconst ConstFloat32x4 VEC4_EPSILON = { { {
            1.192092896e-7F,
            1.192092896e-7F,
            1.192092896e-7F,
            1.192092896e-7F,
        } } };

    mathconst ConstFloat32x4 VEC4_NO_FRACTION = { { {
            8388608.0F,
            8388608.0F,
            8388608.0F,
            8388608.0F,
        } } };

    mathconst ConstUInt32x4 VEC4_ONE_HALF_MINUS_EPS = { { {
            0x3EFFFFFD,
            0x3EFFFFFD,
            0x3EFFFFFD,
            0x3EFFFFFD,
        } } };

    mathconst ConstFloat32x4 VEC4_2PI = { { {
            PI2<float>,
            PI2<float>,
            PI2<float>,
            PI2<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_2PI = { { {
            -PI2<float>,
            -PI2<float>,
            -PI2<float>,
            -PI2<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_RECIPROCAL_2PI = { { {
            ONE_OVER_PI2<float>,
            ONE_OVER_PI2<float>,
            ONE_OVER_PI2<float>,
            ONE_OVER_PI2<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_PI = { { {
            PI<float>,
            PI<float>,
            PI<float>,
            PI<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_NEGATIVE_PI = { { {
            -PI<float>,
            -PI<float>,
            -PI<float>,
            -PI<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_RECIPROCAL_PI = { { {
            ONE_OVER_PI<float>,
            ONE_OVER_PI<float>,
            ONE_OVER_PI<float>,
            ONE_OVER_PI<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_HALF_PI = { { {
            PI_OVER_2<float>,
            PI_OVER_2<float>,
            PI_OVER_2<float>,
            PI_OVER_2<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_UNIT_EPSILON = { { {
            1.0e-4f,
            1.0e-4f,
            1.0e-4f,
            1.0e-4f,
        } } };

    // sin cos log exp implementation: http://gruntthepeon.free.fr/ssemath/
    mathconst ConstFloat32x4 VEC4_PI_CONSTANTS_0 = { { {
            PI<float>,
            PI2<float>,
            ONE_OVER_PI<float>,
            ONE_OVER_PI2<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_SIN_COEFFICIENTS_0 = { { {
            -0.16666667F,
            +0.0083333310F,
            -0.00019840874F,
            +2.7525562e-06F,
        } } };

    mathconst ConstFloat32x4 VEC4_SIN_COEFFICIENTS_1 = { { {
            -2.3889859e-08F,
            -0.16665852F,
            +0.0083139502F,
            -0.00018524670F,
        } } };

    mathconst ConstFloat32x4 VEC4_COS_COEFFICIENTS_0 = { { {
            -0.5F,
            +0.041666638F,
            -0.0013888378F,
            +2.4760495e-05F,
        } } };

    mathconst ConstFloat32x4 VEC4_COS_COEFFICIENTS_1 = { { {
            -2.6051615e-07F,
            -0.49992746F,
            +0.041493919F,
            -0.0012712436F,
        } } };

    mathconst ConstFloat32x4 VEC4_TAN_COEFFICIENTS_0 = { { {
            1.0F,
            0.333333333F,
            0.133333333F,
            5.396825397e-2F,
        } } };

    mathconst ConstFloat32x4 VEC4_TAN_COEFFICIENTS_1 = { { {
            2.186948854e-2F,
            8.863235530e-3F,
            3.592128167e-3F,
            1.455834485e-3F,
        } } };

    mathconst ConstFloat32x4 VEC4_TAN_COEFFICIENTS_2 = { { {
            5.900274264e-4F,
            2.391290764e-4F,
            9.691537707e-5F,
            3.927832950e-5F,
        } } };

    mathconst ConstFloat32x4 VEC4_ARC_COEFFICIENTS_0 = { { {
            +1.5707963050F,
            -0.2145988016F,
            +0.0889789874F,
            -0.0501743046F,
        } } };

    mathconst ConstFloat32x4 VEC4_ARC_COEFFICIENTS_1 = { { {
            +0.0308918810F,
            -0.0170881256F,
            +0.0066700901F,
            -0.0012624911F,
        } } };

    mathconst ConstFloat32x4 VEC4_ATAN_COEFFICIENTS_0 = { { {
            -0.3333314528F,
            +0.1999355085F,
            -0.1420889944F,
            +0.1065626393F,
        } } };

    mathconst ConstFloat32x4 VEC4_ATAN_COEFFICIENTS_1 = { { {
            -0.0752896400F,
            +0.0429096138F,
            -0.0161657367F,
            +0.0028662257F,
        } } };

    mathconst ConstFloat32x4 VEC4_ATAN_EST_COEFFICIENTS_0 = { { {
            +0.999866F,
            +0.999866F,
            +0.999866F,
            +0.999866F,
        } } };

    mathconst ConstFloat32x4 VEC4_ATAN_EST_COEFFICIENTS_1 = { { {
            -0.3302995F,
            +0.180141F,
            -0.085133F,
            +0.0208351F,
        } } };

    mathconst ConstFloat32x4 VEC4_TAN_EST_COEFFICIENTS_0 = { { {
            2.484F,
            -1.954923183e-1F,
            2.467401101F,
            ONE_OVER_PI<float>,
        } } };

    mathconst ConstFloat32x4 VEC4_ARC_EST_COEFFICIENTS_0 = { { {
            +1.5707288F,
            -0.2121144F,
            +0.0742610F,
            -0.0187293F,
        } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_1 = { { {
            -6.93147182e-1F,
            -6.93147182e-1F,
            -6.93147182e-1F,
            -6.93147182e-1F,
         } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_2 = { { {
            +2.40226462e-1F,
            +2.40226462e-1F,
            +2.40226462e-1F,
            +2.40226462e-1F,
         } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_3 = { { {
            -5.55036440e-2F,
            -5.55036440e-2F,
            -5.55036440e-2F,
            -5.55036440e-2F,
         } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_4 = { { {
            +9.61597636e-3F,
            +9.61597636e-3F,
            +9.61597636e-3F,
            +9.61597636e-3F,
         } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_5 = { { {
            -1.32823968e-3F,
            -1.32823968e-3F,
            -1.32823968e-3F,
            -1.32823968e-3F,
         } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_6 = { { {
            +1.47491097e-4F,
            +1.47491097e-4F,
            +1.47491097e-4F,
            +1.47491097e-4F,
         } } };

    mathconst ConstFloat32x4 VEC4_EXP_EST_7 = { { {
            -1.08635004e-5F,
            -1.08635004e-5F,
            -1.08635004e-5F,
            -1.08635004e-5F,
         } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_0 = { { {
            +1.442693F,
            +1.442693F,
            +1.442693F,
            +1.442693F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_1 = { { {
            -0.721242F,
            -0.721242F,
            -0.721242F,
            -0.721242F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_2 = { { {
            +0.479384F,
            +0.479384F,
            +0.479384F,
            +0.479384F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_3 = { { {
            -0.350295F,
            -0.350295F,
            -0.350295F,
            -0.350295F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_4 = { { {
            +0.248590F,
            +0.248590F,
            +0.248590F,
            +0.248590F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_5 = { { {
            -0.145700F,
            -0.145700F,
            -0.145700F,
            -0.145700F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_6 = { { {
            +0.057148F,
            +0.057148F,
            +0.057148F,
            +0.057148F,
        } } };

    mathconst ConstFloat32x4 VEC4_LOG_EST_7 = { { {
            -0.010578F,
            -0.010578F,
            -0.010578F,
            -0.010578F,
        } } };

    mathconst ConstFloat32x4 VEC4_LGE = { { {
            +1.442695F,
            +1.442695F,
            +1.442695F,
            +1.442695F,
        } } };

    mathconst ConstFloat32x4 VEC4_INV_LGE = { { {
            +6.93147182e-1F,
            +6.93147182e-1F,
            +6.93147182e-1F,
            +6.93147182e-1F,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_QNAN = { { {
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_ABS = { { {
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_NEGATIVE_ONE = { { {
            0xFFFFFFFF,
            0xFFFFFFFF,
            0xFFFFFFFF,
            0xFFFFFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_COMPONENTS_3 = { { {
            0xFFFFFFFF,
            0xFFFFFFFF,
            0xFFFFFFFF,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_X = { { {
            0xFFFFFFFF,
            0x00000000,
            0x00000000,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_Y = { { {
            0x00000000,
            0xFFFFFFFF,
            0x00000000,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_Z = { { {
            0x00000000,
            0x00000000,
            0xFFFFFFFF,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_COMPONENT_W = { { {
            0x00000000,
            0x00000000,
            0x00000000,
            0xFFFFFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_0101 = { { {
            0x00000000,
            0xFFFFFFFF,
            0x00000000,
            0xFFFFFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1010 = { { {
            0xFFFFFFFF,
            0x00000000,
            0xFFFFFFFF,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1000 = { { {
            0xFFFFFFFF,
            0x00000000,
            0x00000000,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_0001 = { { {
            0x00000000,
            0x00000000,
            0x00000000,
            0xFFFFFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1100 = { { {
            0xFFFFFFFF,
            0xFFFFFFFF,
            0x00000000,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1110 = { { {
            0xFFFFFFFF,
            0xFFFFFFFF,
            0xFFFFFFFF,
            0x00000000,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_SELECT_1011 = { { {
            0xFFFFFFFF,
            0x00000000,
            0xFFFFFFFF,
            0xFFFFFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_A8R8G8B8 = { { {
            0x00FF0000,
            0x0000FF00,
            0x000000FF,
            0xFF000000,
        } } };

    mathconst ConstUInt32x4 VEC4_FLIP_A_A8R8G8B8 = { { {
            0x00000000,
            0x00000000,
            0x00000000,
            0x80000000,
        } } };

    mathconst ConstFloat32x4 VEC4_FIX_A_A8R8G8B8 = { { {
            0.0F,
            0.0F,
            0.0F,
            static_cast<float>(0x80000000U),
        } } };

    mathconst ConstFloat32x4 VEC4_NORMALIZE_A8R8G8B8 = { { {
            1.0F / (255.0F * static_cast<float>(0x10000)),
            1.0F / (255.0F * static_cast<float>(0x100)),
            1.0F / 255.0F,
            1.0F / (255.0F * static_cast<float>(0x1000000)),
        } } };

    mathconst ConstFloat32x4 VEC4_COLOR_SCALE = { { {
            255.0F,
            255.0F,
            255.0F,
            255.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_COLOR_LUMINANCE = { { {
            0.2125F,
            0.7154F,
            0.0721F,
            0.0F,
        } } };

    mathconst ConstInt32x4 VEC4_EXPONENT_BIAS = { { {
            127,
            127,
            127,
            127,
        } } };

    mathconst ConstInt32x4 VEC4_SUBNORMAL_EXPONENT = { { {
            -126,
            -126,
            -126,
            -126,
        } } };

    mathconst ConstInt32x4 VEC4_NUM_TRAILING = { { {
            23,
            23,
            23,
            23,
        } } };

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

    mathconst ConstInt32x4 VEC4_BIN_128 = { { {
            0x43000000,
            0x43000000,
            0x43000000,
            0x43000000,
        } } };

    mathconst ConstUInt32x4 VEC4_BIN_NEG_150 = { { {
            0xC3160000,
            0xC3160000,
            0xC3160000,
            0xC3160000,
        } } };

    mathconst ConstInt32x4 VEC4_VALUE253 = { { {
            253,
            253,
            253,
            253,
        } } };

    mathconst ConstFloat32x4 VEC4_MSRGB_SCALE = { { {
            12.92F,
            12.92F,
            12.92F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_MSRGB_A = { { {
            0.055F,
            0.055F,
            0.055F,
            0.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_MSRGB_A1 = { { {
            1.055F,
            1.055F,
            1.055F,
            1.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_UNSIGNED_FIX = { { {
            32768.0F * 65536.0F,
            32768.0F * 65536.0F,
            32768.0F * 65536.0F,
            32768.0F * 65536.0F,
        } } };
    mathconst ConstFloat32x4 VEC4_INTMAX = { { {
            65536.0F * 32768.0F - 128.0F,
            65536.0F * 32768.0F - 128.0F,
            65536.0F * 32768.0F - 128.0F,
            65536.0F * 32768.0F - 128.0F,
        } } };
    mathconst ConstFloat32x4 VEC4_UINTMAX = { { {
            65536.0F * 65536.0F - 256.0F,
            65536.0F * 65536.0F - 256.0F,
            65536.0F * 65536.0F - 256.0F,
            65536.0F * 65536.0F - 256.0F,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_FLIP_Y = { { {
            UINT32_C(0),
            UINT32_C(0x80000000),
            UINT32_C(0),
            UINT32_C(0),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_FLIP_Z = { { {
            UINT32_C(0),
            UINT32_C(0),
            UINT32_C(0x80000000),
            UINT32_C(0),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_FLIP_W = { { {
            UINT32_C(0),
            UINT32_C(0),
            UINT32_C(0),
            UINT32_C(0x80000000),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_FLIP_YZ = { { {
            UINT32_C(0),
            UINT32_C(0x80000000),
            UINT32_C(0x80000000),
            UINT32_C(0),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_FLIP_ZW = { { {
            UINT32_C(0),
            UINT32_C(0),
            UINT32_C(0x80000000),
            UINT32_C(0x80000000),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_FLIP_YW = { { {
            UINT32_C(0),
            UINT32_C(0x80000000),
            UINT32_C(0),
            UINT32_C(0x80000000),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_DEC4 = { { {
            UINT32_C(0x3FF),
            UINT32_C(0x3FF) << UINT32_C(10),
            UINT32_C(0x3FF) << UINT32_C(20),
            UINT32_C(0x3) << UINT32_C(30),
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_XOR_DEC4 = { { {
            UINT32_C(0x200),
            UINT32_C(0x200) << UINT32_C(10),
            UINT32_C(0x200) << UINT32_C(20),
            UINT32_C(0)
        } } };

    mathconst ConstFloat32x4 VEC4_ADD_UDEC4 = { { {
            0.0F,
            0.0F,
            0.0F,
            32768.0F * 65536.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_ADD_DEC4 = { { {
            -512.0F,
            -512.0F * 1024.0F,
            -512.0F * 1024.0F * 1024.0F,
            0,
        } } };
    mathconst ConstFloat32x4 VEC4_MUL_DEC4 = { { {
            1.0F,
            1.0F / 1024.0F,
            1.0F / (1024.0F * 1024.0F),
            1.0F / (1024.0F * 1024.0F * 1024.0F)
        } } };

    mathconst ConstFloat32x4 VEC4_UBYTE_MAX = { { {
            255.0F,
            255.0F,
            255.0F,
            255.0F, } } };
    mathconst ConstFloat32x4 VEC4_BYTE_MIN = { { {
            -127.0F,
            -127.0F,
            -127.0F,
            -127.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_BYTE_MAX = { { {
            127.0F,
            127.0F,
            127.0F,
            127.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_SHORT_MIN = { { {
            -32767.0F,
            -32767.0F,
            -32767.0F,
            -32767.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_SHORT_MAX = { { {
            32767.0F,
            32767.0F,
            32767.0F,
            32767.0F,
        } } };

    mathconst ConstFloat32x4 VEC4_USHORT_MAX = { { {
            65535.0F,
            65535.0F,
            65535.0F,
            65535.0F,
        } } };
}


// =================================================================================================
//
// Include some internal specific implementation details.
//

#if !GRAPHYTE_MATH_NO_INTRINSICS
#if GRAPHYTE_HW_AVX
#include <Graphyte/Maths/Impl/Avx.impl.hxx>
#elif GRAPHYTE_HW_NEON
#include <Graphyte/Maths/Impl/Neon.impl.hxx>
#endif
#endif


// =================================================================================================
//
// Supported types
//

namespace Graphyte::Maths
{
    struct Vector4U final
    {
        Impl::NativeUInt32x4 V;
    };

    struct Vector3U final
    {
        Impl::NativeUInt32x4 V;
    };

    struct Vector2U final
    {
        Impl::NativeUInt32x4 V;
    };

    struct Vector1U final
    {
        Impl::NativeUInt32x4 V;
    };

    struct Vector4F final
    {
        Impl::NativeFloat32x4 V;
    };

    struct Vector3F final
    {
        Impl::NativeFloat32x4 V;
    };

    struct Vector2F final
    {
        Impl::NativeFloat32x4 V;
    };

    struct Vector1F final
    {
        Impl::NativeFloat32x4 V;
    };

    struct QuaternionF final
    {
        Impl::NativeFloat32x4 V;
    };

    struct PlaneF final
    {
        Impl::NativeFloat32x4 V;
    };

    struct SphereF final
    {
        Impl::NativeFloat32x4 V;
    };

    struct ColorF final
    {
        Impl::NativeFloat32x4 V;
    };

    struct MatrixF final
    {
        Impl::NativeFloat32x4 V;
    };
}

// =================================================================================================
//
// Constants.
//

// =================================================================================================
//
// Vector construction.
//

namespace Graphyte::Maths
{
    // Explicit Nth dimension construction.
    template <typename R, typename C>
    R Make(C x, C y, C z, C w) noexcept = delete;

    template <typename R, typename C>
    R Make(C x, C y, C z) noexcept = delete;

    template <typename R, typename C>
    R Make(C x, C y) noexcept = delete;

    template <typename R, typename C>
    R Make(C x) noexcept = delete;

    // Replicate value on all components.
    template <typename R, typename C>
    R Replicate(C value) noexcept = delete;
}


// =================================================================================================
//
// Bitwise arithmetic operations.
//

namespace Graphyte::Maths
{
    template <typename T>
    T And(T a, T b) noexcept = delete;

    template <typename T>
    T AndNot(T a, T b) noexcept = delete;

    template <typename T>
    T Or(T a, T b) noexcept = delete;

    template <typename T>
    T Xor(T a, T b) noexcept = delete;

    template <typename T>
    T Nor(T a, T b) noexcept = delete;

    template <typename T>
    T Not(T x) noexcept = delete;
}


// =================================================================================================
//
// Comparison masking functions
//

namespace Graphyte::Maths
{
    template <typename R, typename T>
    R CompareEqual(T a, T b) noexcept = delete;

    template <typename R, typename T>
    R CompareNotEqual(T a, T b) noexcept = delete;
}


// =================================================================================================
//
// Comparison logical functions
//

namespace Graphyte::Maths
{
    template <typename T>
    bool IsEqual(T a, T b) noexcept = delete;

    template <typename T>
    bool IsNotEqual(T a, T b) noexcept = delete;
}


// =================================================================================================
//
// Bitwise testing functions.
//

namespace Graphyte::Maths
{
    template <typename T>
    bool AllTrue(T v) noexcept = delete;

    template <typename T>
    bool AllFalse(T v) noexcept = delete;

    template <typename T>
    bool AnyTrue(T v) noexcept = delete;

    template <typename T>
    bool AnyFalse(T v) noexcept = delete;
}

#if false

// =================================================================================================
//
// Typed constants
//

namespace Graphyte::MathsX
{
    template <typename T> T Zero() noexcept = delete;
    template <typename T> T One() noexcept = delete;

    template <typename T> T Infinity() noexcept = delete;
    template <typename T> T Nan() noexcept = delete;
    template <typename T> T Epsilon() noexcept = delete;
    template <typename T> T SignMask() noexcept = delete;

    template <typename T> T UnitX() noexcept = delete;
    template <typename T> T UnitY() noexcept = delete;
    template <typename T> T UnitZ() noexcept = delete;
    template <typename T> T UnitW() noexcept = delete;

    template <typename T> T NegativeUnitX() noexcept = delete;
    template <typename T> T NegativeUnitY() noexcept = delete;
    template <typename T> T NegativeUnitZ() noexcept = delete;
    template <typename T> T NegativeUnitW() noexcept = delete;

    template <typename T> T Identity() noexcept = delete;

    template <typename T> bool IsIdentity(T value) noexcept = delete;
    template <typename T, typename U> bool IsIdentity(T value, U epsilon) noexcept = delete;

    template <typename T> T True() noexcept = delete;
    template <typename T> T False() noexcept = delete;

    template <typename T> T Pi() noexcept = delete;
    template <typename T> T Pi2() noexcept = delete;
    template <typename T> T OneOverPi() noexcept = delete;
    template <typename T> T OneOverPi2() noexcept = delete;
    template <typename T> T PiOver2() noexcept = delete;
    template <typename T> T E() noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> bool AllTrue(T value) noexcept = delete;
    template <typename T> bool AllFalse(T value) noexcept = delete;
    template <typename T> bool AnyTrue(T value) noexcept = delete;
    template <typename T> bool AnyFalse(T value) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> T And(T a, T b) noexcept = delete;
    template <typename T> T AndNot(T a, T b) noexcept = delete;
    template <typename T> T Or(T a, T b) noexcept = delete;
    template <typename T> T Xor(T a, T b) noexcept = delete;
    template <typename T> T Nor(T a, T b) noexcept = delete;
    template <typename T> T Not(T a, T b) noexcept = delete;
}



namespace Graphyte::MathsX
{
    template <typename T> T Cos(T value) noexcept = delete;
    template <typename T> T Sin(T value) noexcept = delete;
    template <typename T> void SinCos(T& result_sin, T& result_cos, T value) noexcept = delete;
    template <typename T> T Tan(T value) noexcept = delete;
    template <typename T> T Asin(T value) noexcept = delete;
    template <typename T> T Acos(T value) noexcept = delete;
    template <typename T> T Atan(T value) noexcept = delete;
    template <typename T> T Atan2(T y, T x) noexcept = delete;
    template <typename T> T Sinh(T value) noexcept = delete;
    template <typename T> T Cosh(T value) noexcept = delete;
    template <typename T> T Tanh(T value) noexcept = delete;
    template <typename T> T Asinh(T value) noexcept = delete;
    template <typename T> T Acosh(T value) noexcept = delete;
    template <typename T> T Atanh(T value) noexcept = delete;

    template <typename T> T Log(T value) noexcept = delete;
    template <typename T> T Log(T base, T value) noexcept = delete;
    template <typename T> T Log10(T value) noexcept = delete;
    template <typename T> T Log2(T value) noexcept = delete;

    template <typename T> T Exp(T value) noexcept = delete;
    template <typename T> T Exp10(T value) noexcept = delete;
    template <typename T> T Exp2(T value) noexcept = delete;

    template <typename T> T Power(T x, T y) noexcept = delete;
    template <typename T> T Hypot(T x, T y) noexcept = delete;
    template <typename T> T Sqrt(T value) noexcept = delete;
    template <typename T> T SqrtEst(T value) noexcept = delete;
    template <typename T> T InvSqrt(T value) noexcept = delete;
    template <typename T> T InvSqrtEst(T value) noexcept = delete;
    template <typename T> T Cbrt(T value) noexcept = delete;
    template <typename T> T InvCbrt(T value) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> T Abs(T value) noexcept = delete;
    template <typename T> T Negate(T value) noexcept = delete;
    template <typename T> T Add(T a, T b) noexcept = delete;
    template <typename T> T Subtract(T a, T b) noexcept = delete;
    template <typename T> T Multiply(T a, T b) noexcept = delete;
    template <typename T, typename U> T Multiply(T a, U b) noexcept = delete;
    template <typename T> T Reciprocal(T value) noexcept = delete;
    template <typename T> T Divide(T value) noexcept = delete;
    template <typename T, typename U> T Divide(T a, U b) noexcept = delete;
    template <typename T> T MultiplyAdd(T a, T b, T c) noexcept = delete;
    template <typename T> T MultiplySubtract(T a, T b, T c) noexcept = delete;
    template <typename T> T NegateMultiplyAdd(T a, T b, T c) noexcept = delete;
    template <typename T> T NegateMultiplySubtract(T a, T b, T c) noexcept = delete;

    template <typename T> T Square(T value) noexcept = delete;
    template <typename T> T SignedSquare(T v) noexcept = delete;
    template <typename T> T Cube(T v) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T, typename U> T Lerp(T a, T b, U t) noexcept = delete;
    template <typename T> T Lerp(T a, T b, T t) noexcept = delete;

    template <typename T> T Unlerp(T v, T a, T b) noexcept = delete;

    template <typename T, typename U> T LerpPrecise(T a, T b, U t) noexcept = delete;
    template <typename T> T LerpPrecise(T a, T b, T t) noexcept = delete;

    template <typename T, typename U> T Hermite(T p0, T t0, T p1, T t1, U t) noexcept = delete;
    template <typename T> T Hermite(T p0, T t0, T p1, T t1, T t) noexcept = delete;

    template <typename T, typename U> T Barycentric(T a, T b, T c, U f, U g) noexcept = delete;
    template <typename T> T Barycentric(T a, T b, T c, T f, T g) noexcept = delete;

    template <typename T, typename U> T CatmullRom(T p0, T p1, T p2, T p3, U t) noexcept = delete;
    template <typename T> T CatmullRom(T p0, T p1, T p2, T p3, T t) noexcept = delete;

    template <typename T, typename U> T Bezier(T a, T b, T c, U t) noexcept = delete;
    template <typename T> T Bezier(T a, T b, T c, T t) noexcept = delete;

    template <typename T, typename U> T Bezier(T a, T b, T c, T d, U t) noexcept = delete;
    template <typename T> T Bezier(T a, T b, T c, T d, T t) noexcept = delete;

    template <typename T> T Remap(T v, T from_min, T from_max, T to_min, T to_max) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> T CopySign(T number, T sign) noexcept = delete;
    template <typename T> T Sign(T v) noexcept = delete;
    template <typename T> T Ceiling(T v) noexcept = delete;
    template <typename T> T Floor(T v) noexcept = delete;
    template <typename T> T Truncate(T v) noexcept = delete;
    template <typename T> T Round(T v) noexcept = delete;
    template <typename T> T Remainder(T x, T y) noexcept = delete;
    template <typename T> T Fraction(T x, T y) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename R, typename T> R BitCompareEqual(T a, T b) noexcept = delete;
    template <typename R, typename T> R BitCompareNotEqual(T a, T b) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename R, typename T> R CompareEqual(T a, T b) noexcept = delete;
    template <typename R, typename T, typename U> R CompareEqual(T a, T b, U epsilon) noexcept = delete;
    template <typename R, typename T> R CompareNotEqual(T a, T b) noexcept = delete;
    template <typename R, typename T> R CompareGreater(T a, T b) noexcept = delete;
    template <typename R, typename T> R CompareGreaterEqual(T a, T b) noexcept = delete;
    template <typename R, typename T> R CompareLess(T a, T b) noexcept = delete;
    template <typename R, typename T> R CompareLessEqual(T a, T b) noexcept = delete;
    template <typename R, typename T> R CompareInfinity(T v) noexcept = delete;
    template <typename R, typename T> R CompareNan(T v) noexcept = delete;
    template <typename R, typename T> R CompareInBounds(T v, T bounds) noexcept = delete;

    template <typename T> bool IsZero(T v) noexcept = delete;
    template <typename T> bool IsZero(T v, T epsilon) noexcept = delete;
    template <typename T> bool IsEqual(T a, T b) noexcept = delete;
    template <typename T, typename U> bool IsEqual(T a, T b, U epsilon) noexcept = delete;
    template <typename T> bool IsNotEqual(T a, T b) noexcept = delete;
    template <typename T> bool IsGreater(T a, T b) noexcept = delete;
    template <typename T> bool IsGreaterEqual(T a, T b) noexcept = delete;
    template <typename T> bool IsLess(T a, T b) noexcept = delete;
    template <typename T> bool IsLessEqual(T a, T b) noexcept = delete;
    template <typename T> bool IsInfinity(T v) noexcept = delete;
    template <typename T> bool IsNan(T v) noexcept = delete;
    template <typename T> bool InBounds(T v, T bounds) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> bool IsNearEqual(T a, T b, int32_t tolerance) noexcept = delete;
    template <typename T> bool IsNearEqual(T a, T b) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> T Min(T a, T b) noexcept = delete;
    template <typename T> T Max(T a, T b) noexcept = delete;
    template <typename T> T Clamp(T v, T min, T max) noexcept = delete;
    template <typename T> T Saturate(T v) noexcept = delete;
    template <typename T> T Wrap(T v, T min, T max) noexcept = delete;
    template <typename T> Vector4 Hmin(T v) noexcept = delete;
    template <typename T> Vector4 Hmax(T v) noexcept = delete;
    template <typename T> Vector4 Hsum(T v) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T, typename U> T SmoothStep(T a, T b, U x) noexcept = delete;

    template <typename T, typename U> T Cosine(T a, T b, U x) noexcept = delete;

    template <typename T> T EaseSmoothC2(T x) noexcept = delete;
    template <typename T> T Smooth(T min, T max, T x) noexcept = delete;
    template <typename T> T SmoothSquared(T min, T max, T x) noexcept = delete;
    template <typename T> T SmoothInvSquared(T min, T max, T x) noexcept = delete;
    template <typename T> T SmoothCubed(T min, T max, T x) noexcept = delete;
    template <typename T> T SmoothInvCubed(T min, T max, T x) noexcept = delete;
    template <typename T> T Trapezoid(T a, T b, T c, T d, T t) noexcept = delete;
    template <typename T> T Trapezoid(T a, T b, T c, T d, T t, T min, T max) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T, typename R> R Dot(T a, T b) noexcept = delete;
    template <typename T, typename R> R LengthSquared(T v) noexcept = delete;
    template <typename T, typename R> R Length(T v) noexcept = delete;
    template <typename T, typename R> R LengthEst(T v) noexcept = delete;
    template <typename T, typename R> R ReciprocalLength(T v) noexcept = delete;
    template <typename T, typename R> R ReciprocalLengthEst(T v) noexcept = delete;
    template <typename T, typename R> R Distance(T a, T b) noexcept = delete;
    template <typename T, typename R> R DistanceSquared(T a, T b) noexcept = delete;

    template <typename T> bool IsUnit(T v) noexcept;
    template <typename T> T Normalize(T v) noexcept;
    template <typename T> T NormalizeEst(T v) noexcept;

    template <typename T, typename U> T ClampLength(T v, U min, U max) noexcept = delete;
    template <typename T> T Reflect(T incident, T normal) noexcept = delete;
    template <typename T, typename U> T Refract(T incident, T normal, U index) noexcept = delete;
    template <typename T> T FaceForward(T normal, T incident, T reference) noexcept = delete;
    template <typename T> Vector4 AngleBetweenNormals(T a, T b) noexcept = delete;
    template <typename T> Vector4 AngleBetweenVectors(T a, T b) noexcept = delete;

    template <typename T> T Cross(T a, T b) noexcept = delete;
    template <typename T> T Cross(T a, T b, T c) noexcept = delete;

    template <typename T> T Orthogonal(T v) noexcept = delete;

    template <typename T, typename M> T Transform(T v, M m) noexcept = delete;
    template <typename T, typename M> T TransformCoord(T v, M m) noexcept = delete;
    template <typename T, typename M> T TransformNormal(T v, M m) noexcept = delete;

    void ComponentsFromNormal(Vector3& parallel, Vector3& perpendicular, Vector3 v, Vector3 n) noexcept;
}

namespace Graphyte::MathsX
{
    template <typename R> R CreateFromAxisAngle(Vector3 axis, float angle) noexcept = delete;
    template <typename R> R CreateFromNormalAngle(Vector3 normal, float angle) noexcept = delete;
    template <typename R> R CreateFromEuler(float x, float y, float z) noexcept = delete;
    template <typename R> R CreateFromEuler(Vector3 angles) noexcept = delete;

    template <typename R> R CreateFromMatrix(Matrix m) noexcept = delete;
    template <typename R> R CreateFromQuaternion(Quaternion v) noexcept = delete;

    template <typename T> void ToAxisAngle(Vector3& axis, float& angle, T v) noexcept = delete;

    template <typename M> Vector3 Rotate(Vector3 v, M m) noexcept = delete;
    template <typename M> Vector3 InverseRotate(Vector3 v, M m) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> T Conjugate(T v) noexcept = delete;
    template <typename T> T Inverse(T v) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <typename T> T RevolutionsToDegrees(T x) noexcept = delete;
    template <typename T> T RevolutionsToRadians(T x) noexcept = delete;
    template <typename T> T RevolutionsToGradians(T x) noexcept = delete;
    template <typename T> T DegreesToRevolutions(T x) noexcept = delete;
    template <typename T> T RadiansToRevolutions(T x) noexcept = delete;
    template <typename T> T GradiansToRevolutions(T x) noexcept = delete;
    template <typename T> T RadiansToGradians(T x) noexcept = delete;
    template <typename T> T GradiansToRadians(T x) noexcept = delete;
    template <typename T> T RadiansToDegrees(T x) noexcept = delete;
    template <typename T> T DegreesToRadians(T x) noexcept = delete;
    template <typename T> T GradiansToDegrees(T x) noexcept = delete;
    template <typename T> T DegreesToGradians(T x) noexcept = delete;
}

// =================================================================================================
//
// Make operations
//

namespace Graphyte::MathsX
{
    template <typename T, typename S> T Replicate(S value) noexcept = delete;
    template <typename T, typename S> T Replicate(S const* source) noexcept = delete;
    template <typename T, typename S> T Make(S x) noexcept = delete;
    template <typename T, typename S> T Make(S x, S y) noexcept = delete;
    template <typename T, typename S> T Make(S x, S y, S z) noexcept = delete;
    template <typename T, typename S> T Make(S x, S y, S z, S w) noexcept = delete;
}

// =================================================================================================
//
// Swizzling operations
//

namespace Graphyte::MathsX
{
    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    {
        static_assert(X < 4 and Y < 4 and Z < 4 and W < 4);

        if constexpr (X == 0 and Y == 1 and Z == 2 and W == 3)
        {
            return v;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const result{ { {
                    v.V.F[X],
                    v.V.F[Y],
                    v.V.F[Z],
                    v.V.F[W],
                } } };
#elif GRAPHYTE_HW_AVX
            return { Maths::Impl::avx_swizzle<X, Y, Z, W>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Maths::Impl::neon_swizzle<X, Y, Z, W>(v.V) };
#endif
        }
    }

    template <size_t X, size_t Y, size_t Z>
    mathinline Vector3 mathcall Swizzle(Vector4 v) noexcept
    {
        return Vector3{ Swizzle<X, Y, Z, Z>(v).V };
    }

    template <size_t X, size_t Y>
    mathinline Vector2 mathcall Swizzle(Vector4 v) noexcept
    {
        return Vector2{ Swizzle<X, Y, X, Y>(v).V };
    }



    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Swizzle(Vector3 v) noexcept
    {
        static_assert(X < 3 and Y < 3 and Z < 3 and W < 3);
        return Vector4{ Swizzle<X, Y, Z, W>(Vector4{ v.V }).V };
    }

    template <size_t X, size_t Y, size_t Z>
    mathinline Vector3 mathcall Swizzle(Vector3 v) noexcept
    {
        static_assert(X < 3 and Y < 3 and Z < 3);
        return Vector3{ Swizzle<X, Y, Z, Z>(Vector4{ v.V }).V };
    }

    template <size_t X, size_t Y>
    mathinline Vector2 mathcall Swizzle(Vector3 v) noexcept
    {
        static_assert(X < 3 and Y < 3);
        return Vector2{ Swizzle<X, Y, X, Y>(Vector4{ v.V }).V };
    }


    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Swizzle(Vector2 v) noexcept
    {
        static_assert(X < 2 and Y < 2 and Z < 2 and W < 2);
        return Vector4{ Swizzle<X, Y, Z, W>(Vector4{ v.V }).V };
    }

    template <size_t X, size_t Y, size_t Z>
    mathinline Vector3 mathcall Swizzle(Vector2 v) noexcept
    {
        static_assert(X < 2 and Y < 2 and Z < 2);
        return Vector3{ Swizzle<X, Y, Z, Z>(Vector4{ v.V }).V };
    }

    template <size_t X, size_t Y>
    mathinline Vector3 mathcall Swizzle(Vector2 v) noexcept
    {
        static_assert(X < 2 and Y < 2);
        return Vector3{ Swizzle<X, Y, X, Y>(Vector4{ v.V }).V };
    }

    mathinline Vector4 mathcall Swizzle(Vector4 v, size_t x, size_t y, size_t z, size_t w) noexcept
    {
        GX_ASSERT((x < 4) && (y < 4) && (z < 4) && (w < 4));
        GX_COMPILER_ASSUME((x < 4) && (y < 4) && (z < 4) && (w < 4));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[x],
                v.V.F[y],
                v.V.F[z],
                v.V.F[w],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        alignas(__m128i) uint32_t indices[4]{
            static_cast<uint32_t>(x),
            static_cast<uint32_t>(y),
            static_cast<uint32_t>(z),
            static_cast<uint32_t>(w),
        };
        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&indices[0]));
        __m128 const result = _mm_permutevar_ps(v.V, control);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { Maths::Impl::neon_swizzle(v.V, x, y, z, w) };
#endif
    }
}

namespace Graphyte::MathsX
{
    // Splat component on all lanes.
    template <typename T> T SplatX(T v) noexcept = delete;
    template <typename T> T SplatY(T v) noexcept = delete;
    template <typename T> T SplatZ(T v) noexcept = delete;
    template <typename T> T SplatW(T v) noexcept = delete;

    // get/set component by index.
    template <typename R, typename T> R GetByIndex(T v, size_t index) noexcept = delete;
    template <typename T, typename S> T SetByIndex(T v, S value, size_t index) noexcept = delete;

    template <typename R, typename T> void GetByIndex(R* result, T v, size_t index) noexcept = delete;
    template <typename T, typename S> T SetByIndex(T v, S const* value, size_t index) noexcept = delete;

    template <typename R, typename T> R GetX(T v) noexcept = delete;
    template <typename R, typename T> R GetY(T v) noexcept = delete;
    template <typename R, typename T> R GetZ(T v) noexcept = delete;
    template <typename R, typename T> R GetW(T v) noexcept = delete;

    template <typename R, typename T> void GetX(R* result, T v) noexcept = delete;
    template <typename R, typename T> void GetY(R* result, T v) noexcept = delete;
    template <typename R, typename T> void GetZ(R* result, T v) noexcept = delete;
    template <typename R, typename T> void GetW(R* result, T v) noexcept = delete;

    template <typename T, typename S> T SetX(T v, S value) noexcept = delete;
    template <typename T, typename S> T SetY(T v, S value) noexcept = delete;
    template <typename T, typename S> T SetZ(T v, S value) noexcept = delete;
    template <typename T, typename S> T SetW(T v, S value) noexcept = delete;

    template <typename T, typename S> T SetX(T v, S const* value) noexcept = delete;
    template <typename T, typename S> T SetY(T v, S const* value) noexcept = delete;
    template <typename T, typename S> T SetZ(T v, S const* value) noexcept = delete;
    template <typename T, typename S> T SetW(T v, S const* value) noexcept = delete;
}

// =================================================================================================
//
// Vector conversion functions.
//

namespace Graphyte::MathsX
{
    template <typename R, typename T> R To(T v) noexcept = delete;
    template <typename R, typename T1, typename T2> R To(T1 a, T2 b) noexcept = delete;
    template <typename R, typename T1, typename T2, typename T3> R To(T1 a, T2 b, T3 c) noexcept = delete;
}

namespace Graphyte::MathsX
{
    template <>
    mathinline Bool4 mathcall CompareNotEqual<Bool4, Vector4>(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] != b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] != b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] != b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] != b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const equal = vreinterpretq_u32_f32(vceqq_f32(a.V, b.V));
        uint32x4_t const not_equal = vmvnq_u32(equal);
        return { vreinterpretq_f32_u32(not_equal) };
#endif
    }

    // forward specialization for specific type
    template <> mathinline Bool3 mathcall CompareNotEqual<Bool3, Vector3>(Vector3 a, Vector3 b) noexcept
    {
        return { CompareNotEqual<Bool4, Vector4>({ a.V }, { b.V }).V };
    }
    template <> mathinline Bool2 mathcall CompareNotEqual<Bool2, Vector2>(Vector2 a, Vector2 b) noexcept
    {
        return { CompareNotEqual<Bool4, Vector4>({ a.V }, { b.V }).V };
    }

    template <> mathinline Bool4 mathcall CompareNotEqual<Bool4, Plane>(Plane a, Plane b) noexcept
    {
        return CompareNotEqual<Bool4, Vector4>({ a.V }, { b.V });
    }
}

#endif
