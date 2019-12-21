#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Bitwise.hxx>

// =================================================================================================
//
// AVX support headers.
//

#if GRAPHYTE_HW_AVX
#include <xmmintrin.h>
#include <emmintrin.h>
#endif

// =================================================================================================
//
// ARM64 NEON support headers.
//

#if GRAPHYTE_HW_NEON && GRAPHYTE_COMPILER_MSVC
#if defined(_M_ARM)
#include <arm_neon.h>
#elif defined(_M_ARM64)
#include <arm64_neon.h>
#endif
#endif


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
// Bit-specific functions
//

namespace Graphyte::Maths::Impl
{
    constexpr bool mathcall BitIsNan(uint32_t bits) noexcept
    {
        return ((bits & uint32_t{ 0x7f800000 }) == uint32_t{0x7f800000})
            && ((bits & uint32_t{ 0x007fffff }) != 0);
    }

    constexpr bool mathcall BitIsInf(uint32_t bits) noexcept
    {
        return ((bits & uint32_t{ 0x7fffffff }) == uint32_t{ 0x7f800000 });
    }
}

// =================================================================================================
//
// Native vector type.
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) SimdFloat32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
#elif GRAPHYTE_HW_NEON
    using SimdFloat32x4 = float32x4_t;
#elif GRAPHYTE_HW_AVX
    using SimdFloat32x4 = __m128;
#else
#error Unknown architecture
#endif
}


// =================================================================================================
//
// Native matrix type
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) SimdFloat32x4x4 final
    {
        union
        {
            SimdFloat32x4 R[4];
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
    struct alignas(16) SimdFloat32x4x4 final
    {
        SimdFloat32x4 R[4];
    };
#endif
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
            SimdFloat32x4 V;
        };
    };

    static_assert(std::is_pod_v<ConstFloat32x4>);

    struct alignas(16) ConstInt32x4 final
    {
        union
        {
            alignas(16) int32_t I[4];
            SimdFloat32x4 V;
        };
    };
    static_assert(std::is_pod_v<ConstInt32x4>);

    struct alignas(16) ConstUInt32x4 final
    {
        union
        {
            alignas(16) uint32_t U[4];
            SimdFloat32x4 V;
        };
    };
    static_assert(std::is_pod_v<ConstUInt32x4>);

    struct alignas(16) ConstUInt8x16 final
    {
        union
        {
            alignas(16) uint8_t U[16];
            SimdFloat32x4 V;
        };
    };
    static_assert(std::is_pod_v<ConstUInt8x16>);
}

// =================================================================================================
//
// Scalar constants
//

namespace Graphyte::Maths
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
            0x7F800000,
            0x7F800000,
            0x7F800000,
            0x7F800000,
        } } };

    mathconst ConstUInt32x4 VEC4_QNAN = { { {
            0x7FC00000,
            0x7FC00000,
            0x7FC00000,
            0x7FC00000,
        } } };

    mathconst ConstUInt32x4 VEC4_QNAN_TEST = { { {
            0x007FFFFF,
            0x007FFFFF,
            0x007FFFFF,
            0x007FFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_FLOAT_MIN = { { {
            0x00800000,
            0x00800000,
            0x00800000,
            0x00800000,
        } } };

    mathconst ConstUInt32x4 VEC4_FLOAT_MAX = { { {
            0x7F7FFFFF,
            0x7F7FFFFF,
            0x7F7FFFFF,
            0x7F7FFFFF,
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
            0x007FFFFF,
            0x007FFFFF,
            0x007FFFFF,
            0x007FFFFF,
        } } };

    mathconst ConstUInt32x4 VEC4_MASK_ABS = { { {
            0x7FFFFFFF,
            0x7FFFFFFF,
            0x7FFFFFFF,
            0x7FFFFFFF,
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
            0x00800000,
            0x00800000,
            0x00800000,
            0x00800000,
        } } };

    mathconst ConstUInt32x4 VEC4_NEGATIVE_INFINITY = { { {
            0xFF800000,
            0xFF800000,
            0xFF800000,
            0xFF800000,
        } } };

    mathconst ConstUInt32x4 VEC4_NEGATIVE_QNAN = { { {
            0xFFC00000,
            0xFFC00000,
            0xFFC00000,
            0xFFC00000,
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
// Type traits
//

namespace Graphyte::Maths::Impl
{
    template <size_t Components>
    struct BitMaskFromComponents;

    template <> struct BitMaskFromComponents<4> final { static constexpr size_t Mask = 0b1111; };
    template <> struct BitMaskFromComponents<3> final { static constexpr size_t Mask = 0b0111; };
    template <> struct BitMaskFromComponents<2> final { static constexpr size_t Mask = 0b0011; };
    template <> struct BitMaskFromComponents<1> final { static constexpr size_t Mask = 0b0001; };

    template <size_t Components>
    constexpr size_t ComponentsBitMask = BitMaskFromComponents<Components>::Mask;
}

// =================================================================================================
//
// Concepts
//

namespace Graphyte::Maths
{
    template <typename T>
    struct IsOrderComparable : std::false_type { };

    template <typename T>
    concept OrderComparable = IsOrderComparable<T>::value;

    template <typename T>
    struct IsEqualComparable : std::false_type { };

    template <typename T>
    concept EqualComparable = IsEqualComparable<T>::value;

    template <typename T>
    concept Comparable = EqualComparable<T> and OrderComparable<T>;


    template <typename T>
    struct IsLoadable : std::false_type { };

    template <typename T>
    concept Loadable = IsLoadable<T>::value;


    template <typename T>
    struct IsStorable : std::false_type { };

    template <typename T>
    concept Storable = IsStorable<T>::value;


    template <typename T>
    struct IsArithmetic : std::false_type { };

    template <typename T>
    concept Arithmetic = IsArithmetic<T>::value;

    template <typename T>
    struct IsBitwisable : std::false_type { };

    template <typename T>
    concept Bitwisable = IsBitwisable<T>::value;

    template <typename T>
    struct IsTranscendental : std::false_type { };

    template <typename T>
    concept Transcendental = IsTranscendental<T>::value;

    template <typename T>
    struct IsRoundable : std::false_type { };

    template <typename T>
    concept Roundable = IsRoundable<T>::value;

    template <typename T>
    struct IsInterpolable : std::false_type { };

    template <typename T>
    concept Interpolable = IsInterpolable<T>::value and Arithmetic<T>;

    template <typename T>
    concept ScalarLike = std::is_floating_point_v<T>;

    template <typename T>
    struct IsVectorLike : std::false_type { };

    template <typename T>
    concept VectorLike = IsVectorLike<T>::value;

    template <typename T>
    struct IsMatrixLike : std::false_type { };

    template <typename T>
    concept MatrixLike = IsMatrixLike<T>::value;
}

// =================================================================================================
//
// Math types
//

namespace Graphyte::Maths
{
    struct Bool4 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = uint32_t;
        using MaskType = Bool4;
    };

    template <> struct IsVectorLike<Bool4> : std::true_type { };
    template <> struct IsEqualComparable<Bool4> : std::true_type { };
    template <> struct IsBitwisable<Bool4> : std::true_type { };


    struct Bool3 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 3;
        static constexpr const uint32_t CompareMask = 0b0111;
        using ComponentType = uint32_t;
        using MaskType = Bool3;
    };

    template <> struct IsVectorLike<Bool3> : std::true_type { };
    template <> struct IsEqualComparable<Bool3> : std::true_type { };
    template <> struct IsBitwisable<Bool3> : std::true_type { };


    struct Bool2 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 2;
        using ComponentType = uint32_t;
        using MaskType = Bool2;
    };

    template <> struct IsVectorLike<Bool2> : std::true_type { };
    template <> struct IsEqualComparable<Bool2> : std::true_type { };
    template <> struct IsBitwisable<Bool2> : std::true_type { };


    struct Bool1 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 1;
        using ComponentType = uint32_t;
        using MaskType = Bool1;
    };

    template <> struct IsVectorLike<Bool1> : std::true_type { };
    template <> struct IsEqualComparable<Bool1> : std::true_type { };
    template <> struct IsBitwisable<Bool1> : std::true_type { };

    struct Vector4 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    template <> struct IsVectorLike<Vector4> : std::true_type { };
    template <> struct IsLoadable<Vector4> : std::true_type { };
    template <> struct IsStorable<Vector4> : std::true_type { };
    template <> struct IsOrderComparable<Vector4> : std::true_type { };
    template <> struct IsEqualComparable<Vector4> : std::true_type { };
    template <> struct IsArithmetic<Vector4> : std::true_type { };
    template <> struct IsTranscendental<Vector4> : std::true_type { };
    template <> struct IsRoundable<Vector4> : std::true_type { };
    template <> struct IsInterpolable<Vector4> : std::true_type { };

    struct Vector3 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 3;
        using ComponentType = float;
        using MaskType = Bool3;
    };

    template <> struct IsVectorLike<Vector3> : std::true_type { };
    template <> struct IsLoadable<Vector3> : std::true_type { };
    template <> struct IsStorable<Vector3> : std::true_type { };
    template <> struct IsOrderComparable<Vector3> : std::true_type { };
    template <> struct IsEqualComparable<Vector3> : std::true_type { };
    template <> struct IsArithmetic<Vector3> : std::true_type { };
    template <> struct IsTranscendental<Vector3> : std::true_type { };
    template <> struct IsRoundable<Vector3> : std::true_type { };
    template <> struct IsInterpolable<Vector3> : std::true_type { };

    struct Vector2 final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 2;
        using ComponentType = float;
        using MaskType = Bool2;
    };

    template <> struct IsVectorLike<Vector2> : std::true_type { };
    template <> struct IsLoadable<Vector2> : std::true_type { };
    template <> struct IsStorable<Vector2> : std::true_type { };
    template <> struct IsOrderComparable<Vector2> : std::true_type { };
    template <> struct IsEqualComparable<Vector2> : std::true_type { };
    template <> struct IsArithmetic<Vector2> : std::true_type { };
    template <> struct IsTranscendental<Vector2> : std::true_type { };
    template <> struct IsRoundable<Vector2> : std::true_type { };
    template <> struct IsInterpolable<Vector2> : std::true_type { };

    struct Vector1 final
    {
        Impl::SimdFloat32x4 V;
        static constexpr const size_t Components = 1;
        using ComponentType = float;
        using MaskType = Bool1;
    };

    template <> struct IsVectorLike<Vector1> : std::true_type { };
    template <> struct IsLoadable<Vector1> : std::true_type { };
    template <> struct IsStorable<Vector1> : std::true_type { };
    template <> struct IsOrderComparable<Vector1> : std::true_type { };
    template <> struct IsEqualComparable<Vector1> : std::true_type { };
    template <> struct IsArithmetic<Vector1> : std::true_type { };
    template <> struct IsTranscendental<Vector1> : std::true_type { };
    template <> struct IsRoundable<Vector1> : std::true_type { };
    template <> struct IsInterpolable<Vector1> : std::true_type { };


    struct Quaternion final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    template <> struct IsVectorLike<Quaternion> : std::true_type {};
    template <> struct IsEqualComparable<Quaternion> : std::true_type {};
    template <> struct IsLoadable<Quaternion> : std::true_type {};
    template <> struct IsStorable<Quaternion> : std::true_type {};

    struct Plane final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    template <> struct IsVectorLike<Plane> : std::true_type { };
    template <> struct IsEqualComparable<Plane> : std::true_type { };
    template <> struct IsLoadable<Plane> : std::true_type { };
    template <> struct IsStorable<Plane> : std::true_type { };

    struct Sphere final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    template <> struct IsVectorLike<Sphere> : std::true_type { };
    template <> struct IsEqualComparable<Sphere> : std::true_type { };
    template <> struct IsLoadable<Sphere> : std::true_type { };
    template <> struct IsStorable<Sphere> : std::true_type { };

    struct Matrix final
    {
        Impl::SimdFloat32x4x4 M;

        static constexpr const size_t Components = 16;
        static constexpr const size_t Rows = 4;
        static constexpr const size_t Columns = 4;
        using ComponentType = float;
    };

    template <> struct IsMatrixLike<Matrix> : std::true_type { };
    template <> struct IsEqualComparable<Matrix> : std::true_type { };
    template <> struct IsLoadable<Matrix> : std::true_type { };
    template <> struct IsStorable<Matrix> : std::true_type { };
    template <> struct IsArithmetic<Matrix> : std::true_type { };
    template <> struct IsRoundable<Matrix> : std::true_type { };

    struct Color final
    {
        Impl::SimdFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    template <> struct IsVectorLike<Color> : std::true_type { };
    template <> struct IsLoadable<Color> : std::true_type { };
    template <> struct IsStorable<Color> : std::true_type { };
    template <> struct IsOrderComparable<Color> : std::true_type { };
    template <> struct IsEqualComparable<Color> : std::true_type { };
    template <> struct IsInterpolable<Color> : std::true_type { };
}


// =================================================================================================
//
// Storage types
//

namespace Graphyte::Maths
{
    struct Half final
    {
        uint16_t Value;
    };

    using Half1 = Half;

    struct Half2 final
    {
        Half X;
        Half Y;
    };

    struct Half3 final
    {
        Half X;
        Half Y;
        Half Z;
    };

    struct Half4 final
    {
        Half X;
        Half Y;
        Half Z;
        Half W;
    };

    struct Float4 final
    {
        float X, Y, Z, W;
    };

    struct Float3 final
    {
        float X, Y, Z;
    };

    struct Float2 final
    {
        float X, Y;
    };

    struct Float1 final
    {
        float X;
    };

    struct alignas(16) Float4A final
    {
        float X, Y, Z, W;
    };

    struct alignas(16) Float3A final
    {
        float X, Y, Z;
    };

    struct alignas(16) Float2A final
    {
        float X, Y;
    };

    struct alignas(16) Float1A final
    {
        float X;
    };

    struct Float4x4 final
    {
        union
        {
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

    struct Float4x3 final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
                float M41, M42, M43;
            };
            float M[4][3];
            float F[12];
        };
    };

    struct Float3x4 final
    {
        union
        {
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
            };
            float M[3][4];
            float F[12];
        };
    };

    struct Float3x3 final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
            };
            float M[3][3];
            float F[9];
        };
    };

    struct alignas(16) Float4x4A final
    {
        union
        {
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

    struct alignas(16) Float4x3A final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
                float M41, M42, M43;
            };
            float M[4][3];
            float F[12];
        };
    };

    struct alignas(16) Float3x4A final
    {
        union
        {
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
            };
            float M[3][4];
            float F[12];
        };
    };

    struct alignas(16) Float3x3A final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
            };
            float M[3][3];
            float F[9];
        };
    };

    struct ColorRGBA final
    {
        union
        {
            struct
            {
                uint8_t R;
                uint8_t G;
                uint8_t B;
                uint8_t A;
            };

            uint32_t Value;
        };
    };

    struct ColorBGRA final
    {
        union
        {
            struct
            {
                uint8_t B;
                uint8_t G;
                uint8_t R;
                uint8_t A;
            };

            uint32_t Value;
        };
    };

    struct UInt4 final
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
        uint32_t W;
    };

    struct UInt3 final
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };

    struct UInt2 final
    {
        uint32_t X;
        uint32_t Y;
    };

    struct UInt1 final
    {
        uint32_t X;
    };

    struct SInt4 final
    {
        int32_t X;
        int32_t Y;
        int32_t Z;
        int32_t W;
    };

    struct SInt3 final
    {
        int32_t X;
        int32_t Y;
        int32_t Z;
    };

    struct SInt2 final
    {
        int32_t X;
        int32_t Y;
    };

    struct SInt1 final
    {
        int32_t X;
    };

    struct UByte4 final
    {
        uint8_t X;
        uint8_t Y;
        uint8_t Z;
        uint8_t W;
    };

    struct SByte4 final
    {
        int8_t X;
        int8_t Y;
        int8_t Z;
        int8_t W;
    };
}

// =================================================================================================
//
// Common enum types
//

namespace Graphyte::Maths
{
    enum class SelectMask : uint32_t
    {
        Select0 = UINT32_C(0x00000000),
        Select1 = UINT32_C(0xffffffff),
    };

    enum class InsertMask : uint8_t
    {
        _0000 = 0b0000,
        _0001 = 0b0001,
        _0010 = 0b0010,
        _0011 = 0b0011,
        _0100 = 0b0100,
        _0101 = 0b0101,
        _0110 = 0b0110,
        _0111 = 0b0111,
        _1000 = 0b1000,
        _1001 = 0b1001,
        _1010 = 0b1010,
        _1011 = 0b1011,
        _1100 = 0b1100,
        _1101 = 0b1101,
        _1110 = 0b1110,
        _1111 = 0b1111,
    };

    enum class SwizzleMask
    {
        XXXX, YXXX, ZXXX, WXXX,
        XYXX, YYXX, ZYXX, WYXX,
        XZXX, YZXX, ZZXX, WZXX,
        XWXX, YWXX, ZWXX, WWXX,
        XXYX, YXYX, ZXYX, WXYX,
        XYYX, YYYX, ZYYX, WYYX,
        XZYX, YZYX, ZZYX, WZYX,
        XWYX, YWYX, ZWYX, WWYX,
        XXZX, YXZX, ZXZX, WXZX,
        XYZX, YYZX, ZYZX, WYZX,
        XZZX, YZZX, ZZZX, WZZX,
        XWZX, YWZX, ZWZX, WWZX,
        XXWX, YXWX, ZXWX, WXWX,
        XYWX, YYWX, ZYWX, WYWX,
        XZWX, YZWX, ZZWX, WZWX,
        XWWX, YWWX, ZWWX, WWWX,

        XXXY, YXXY, ZXXY, WXXY,
        XYXY, YYXY, ZYXY, WYXY,
        XZXY, YZXY, ZZXY, WZXY,
        XWXY, YWXY, ZWXY, WWXY,
        XXYY, YXYY, ZXYY, WXYY,
        XYYY, YYYY, ZYYY, WYYY,
        XZYY, YZYY, ZZYY, WZYY,
        XWYY, YWYY, ZWYY, WWYY,
        XXZY, YXZY, ZXZY, WXZY,
        XYZY, YYZY, ZYZY, WYZY,
        XZZY, YZZY, ZZZY, WZZY,
        XWZY, YWZY, ZWZY, WWZY,
        XXWY, YXWY, ZXWY, WXWY,
        XYWY, YYWY, ZYWY, WYWY,
        XZWY, YZWY, ZZWY, WZWY,
        XWWY, YWWY, ZWWY, WWWY,

        XXXZ, YXXZ, ZXXZ, WXXZ,
        XYXZ, YYXZ, ZYXZ, WYXZ,
        XZXZ, YZXZ, ZZXZ, WZXZ,
        XWXZ, YWXZ, ZWXZ, WWXZ,
        XXYZ, YXYZ, ZXYZ, WXYZ,
        XYYZ, YYYZ, ZYYZ, WYYZ,
        XZYZ, YZYZ, ZZYZ, WZYZ,
        XWYZ, YWYZ, ZWYZ, WWYZ,
        XXZZ, YXZZ, ZXZZ, WXZZ,
        XYZZ, YYZZ, ZYZZ, WYZZ,
        XZZZ, YZZZ, ZZZZ, WZZZ,
        XWZZ, YWZZ, ZWZZ, WWZZ,
        XXWZ, YXWZ, ZXWZ, WXWZ,
        XYWZ, YYWZ, ZYWZ, WYWZ,
        XZWZ, YZWZ, ZZWZ, WZWZ,
        XWWZ, YWWZ, ZWWZ, WWWZ,

        XXXW, YXXW, ZXXW, WXXW,
        XYXW, YYXW, ZYXW, WYXW,
        XZXW, YZXW, ZZXW, WZXW,
        XWXW, YWXW, ZWXW, WWXW,
        XXYW, YXYW, ZXYW, WXYW,
        XYYW, YYYW, ZYYW, WYYW,
        XZYW, YZYW, ZZYW, WZYW,
        XWYW, YWYW, ZWYW, WWYW,
        XXZW, YXZW, ZXZW, WXZW,
        XYZW, YYZW, ZYZW, WYZW,
        XZZW, YZZW, ZZZW, WZZW,
        XWZW, YWZW, ZWZW, WWZW,
        XXWW, YXWW, ZXWW, WXWW,
        XYWW, YYWW, ZYWW, WYWW,
        XZWW, YZWW, ZZWW, WZWW,
        XWWW, YWWW, ZWWW, WWWW,
    };

    constexpr const uint32_t PERMUTE_0X = 0;
    constexpr const uint32_t PERMUTE_0Y = 1;
    constexpr const uint32_t PERMUTE_0Z = 2;
    constexpr const uint32_t PERMUTE_0W = 3;
    constexpr const uint32_t PERMUTE_1X = 4;
    constexpr const uint32_t PERMUTE_1Y = 5;
    constexpr const uint32_t PERMUTE_1Z = 6;
    constexpr const uint32_t PERMUTE_1W = 7;
}

// =================================================================================================
//
// Reinterpret operation between types
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall AsVector4(Vector3 v) noexcept
    {
        return { v.V };
    }

    mathinline Vector4 mathcall AsVector4(Vector2 v) noexcept
    {
        return { v.V };
    }

    mathinline Vector4 mathcall AsVector4(Quaternion v) noexcept
    {
        return { v.V };
    }

    mathinline Vector4 mathcall AsVector4(Plane v) noexcept
    {
        return { v.V };
    }

    mathinline Vector4 mathcall AsVector4(Color v) noexcept
    {
        return { v.V };
    }

    mathinline Quaternion mathcall AsQuaternion(Vector4 v) noexcept
    {
        return { v.V };
    }

    mathinline Plane mathcall AsPlane(Vector4 v) noexcept
    {
        return { v.V };
    }

    mathinline Color mathcall AsColor(Vector4 v) noexcept
    {
        return { v.V };
    }

    mathinline Vector3 mathcall AsVector3(Vector4 v) noexcept
    {
        return { v.V };
    }

    mathinline Vector2 mathcall AsVector2(Vector4 v) noexcept
    {
        return { v.V };
    }
}


// =================================================================================================
//
// Vector4 permutations
//

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS

namespace Graphyte::Maths::Impl
{
    template <uint32_t S, bool X, bool Y, bool Z, bool W>
    mathinline Vector4 mathcall PermuteHelper(Vector4 v1, Vector4 v2) noexcept
    {
        if constexpr (X == false && Y == false && Z == false && W == false)
        {
            return { _mm_permute_ps(v1.V, S) };
        }
        else if constexpr (X == true && Y == true && Z == true && W == true)
        {
            return { _mm_permute_ps(v2.V, S) };
        }
        else if constexpr (X == false && Y == false && Z == true && W == true)
        {
            return { _mm_shuffle_ps(v1.V, v2.V, S) };
        }
        else if constexpr (X == true && Y == true && Z == false && W == false)
        {
            return { _mm_shuffle_ps(v2.V, v1.V, S) };
        }
        else
        {
            static constexpr Impl::ConstUInt32x4 const select_mask{ { {
                    X ? SELECT_1 : SELECT_0,
                    Y ? SELECT_1 : SELECT_0,
                    Z ? SELECT_1 : SELECT_0,
                    W ? SELECT_1 : SELECT_0,
                } } };

            __m128 const shuffled_v1 = _mm_permute_ps(v1.V, S);
            __m128 const shuffled_v2 = _mm_permute_ps(v2.V, S);
            __m128 const masked_v1 = _mm_andnot_ps(select_mask.V, shuffled_v1);
            __m128 const masked_v2 = _mm_and_ps(select_mask.V, shuffled_v2);
            __m128 const result = _mm_or_ps(masked_v1, masked_v2);
            return { result };
        }
    }
}

#endif

namespace Graphyte::Maths
{
    template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
    mathinline Vector4 mathcall Permute(Vector4 v1, Vector4 v2) noexcept
    {
        static_assert(X < 8);
        static_assert(Y < 8);
        static_assert(Z < 8);
        static_assert(W < 8);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return Permute(v1, v2, X, Y, Z, W);
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t shuffle = _MM_SHUFFLE(W & 3, Z & 3, Y & 3, X & 3);
        constexpr bool x = (X >= 4);
        constexpr bool y = (Y >= 4);
        constexpr bool z = (Z >= 4);
        constexpr bool w = (W >= 4);

        return Impl::PermuteHelper<shuffle, x, y, z, w>(v1, v2);
#endif
    }

    template <>
    mathinline Vector4 mathcall Permute<0, 1, 2, 3>(Vector4 v1, [[maybe_unused]] Vector4 v2) noexcept
    {
        return v1;
    }

    mathinline Vector4 mathcall Permute(Vector4 a, Vector4 b, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
        GX_ASSERT(x < 8);
        GX_ASSERT(y < 8);
        GX_ASSERT(z < 8);
        GX_ASSERT(w < 8);

#if GRAPHYTE_MATH_NO_INTRINSICS
        const uint32_t* aPtr[2];
        aPtr[0] = reinterpret_cast<const uint32_t*>(&V1);
        aPtr[1] = reinterpret_cast<const uint32_t*>(&V2);

        XMVECTOR Result;
        auto pWork = reinterpret_cast<uint32_t*>(&Result);

        const uint32_t i0 = PermuteX & 3;
        const uint32_t vi0 = PermuteX >> 2;
        pWork[0] = aPtr[vi0][i0];

        const uint32_t i1 = PermuteY & 3;
        const uint32_t vi1 = PermuteY >> 2;
        pWork[1] = aPtr[vi1][i1];

        const uint32_t i2 = PermuteZ & 3;
        const uint32_t vi2 = PermuteZ >> 2;
        pWork[2] = aPtr[vi2][i2];

        const uint32_t i3 = PermuteW & 3;
        const uint32_t vi3 = PermuteW >> 2;
        pWork[3] = aPtr[vi3][i3];

        return Result;


        uint32_t const* vptrs[2]{
            reinterpret_cast<uint32_t const*>(&a.V),
            reinterpret_cast<uint32_t const*>(&b.V),
        };

        uint32_t const ix = (x & 3);
        uint32_t const iy = (y & 3);
        uint32_t const iz = (z & 3);
        uint32_t const iw = (w & 3);

        uint32_t const vx = (x >> 2);
        uint32_t const vy = (y >> 2);
        uint32_t const vz = (z >> 2);
        uint32_t const vw = (w >> 2);

        uint32_t const rx = vptrs[vx][ix];
        uint32_t const ry = vptrs[vy][iy];
        uint32_t const rz = vptrs[vz][iz];
        uint32_t const rw = vptrs[vw][iw];

        Impl::ConstUInt32x4 const result{ { {
                rx,
                ry,
                rz,
                rw,
            } } };


#elif GRAPHYTE_HW_AVX
        static Impl::ConstUInt32x4 const threes{ { {
                3,
                3,
                3,
                3,
            } } };

        alignas(__m128) uint32_t elements[4]{ x, y, z, w };

        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&elements[0]));

        __m128i const select = _mm_cmpgt_epi32(control, _mm_castps_si128(threes.V));
        __m128i const permutation = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(control), threes.V));


        __m128 const shuffle1 = _mm_permutevar_ps(a.V, permutation);
        __m128 const shuffle2 = _mm_permutevar_ps(b.V, permutation);

        __m128 const masked1 = _mm_andnot_ps(_mm_castsi128_ps(select), shuffle1);
        __m128 const masked2 = _mm_and_ps(_mm_castsi128_ps(select), shuffle2);

        __m128 const result = _mm_or_ps(masked1, masked2);

        return { result };
#endif
    }
}

// =================================================================================================
//
// Swizzling
//

namespace Graphyte::Maths
{
    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    {
        static_assert(X < 4);
        static_assert(Y < 4);
        static_assert(Z < 4);
        static_assert(W < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[X],
                v.V.F[Y],
                v.V.F[Z],
                v.V.F[W],
            } } };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(W, Z, Y, X)) };
#endif
    }

    template<> mathinline Vector4 mathcall Swizzle<0, 1, 2, 3>(Vector4 v) noexcept
    {
        return v;
    }

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    template<> mathinline Vector4 mathcall Swizzle<0, 1, 0, 1>(Vector4 v) noexcept
    {
        return { _mm_movelh_ps(v.V, v.V) };
    }

    template<> mathinline Vector4 mathcall Swizzle<2, 3, 2, 3>(Vector4 v) noexcept
    {
        return { _mm_movehl_ps(v.V, v.V) };
    }

    template<> mathinline Vector4 mathcall Swizzle<0, 0, 1, 1>(Vector4 v) noexcept
    {
        return { _mm_unpacklo_ps(v.V, v.V) };
    }

    template<> mathinline Vector4 mathcall Swizzle<2, 2, 3, 3>(Vector4 v) noexcept
    {
        return { _mm_unpackhi_ps(v.V, v.V) };
    }

    template<> mathinline Vector4 mathcall Swizzle<0, 0, 2, 2>(Vector4 v) noexcept
    {
        return { _mm_moveldup_ps(v.V) };
    }

    template<> mathinline Vector4 mathcall Swizzle<1, 1, 3, 3>(Vector4 v) noexcept
    {
        return { _mm_movehdup_ps(v.V) };
    }
#endif

#if GRAPHYTE_HW_AVX2 && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vector4 mathcall Vector4::Swizzle<0, 0, 0, 0>(Vector4 v) noexcept
    {
        return { _mm_broadcastss_ps(v.V) };
    }
#endif

    template <SwizzleMask M>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    {
        return Swizzle<
            (static_cast<size_t>(M) >> 0) & 3,
            (static_cast<size_t>(M) >> 2) & 3,
            (static_cast<size_t>(M) >> 4) & 3,
            (static_cast<size_t>(M) >> 6) & 3>(v);
    }

    mathinline Vector4 mathcall Swizzle(Vector4 v, uint32_t index0, uint32_t index1, uint32_t index2, uint32_t index3) noexcept
    {
        GX_ASSERT((index0 < 4) && (index1 < 4) && (index2 < 4) && (index3 < 4));
        GX_COMPILER_ASSUME((index0 < 4) && (index1 < 4) && (index2 < 4) && (index3 < 4));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[index0],
                v.V.F[index1],
                v.V.F[index2],
                v.V.F[index3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        alignas(__m128i) uint32_t indices[4]{
            index0,
            index1,
            index2,
            index3,
        };

        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&indices[0]));
        __m128 const result = _mm_permutevar_ps(v.V, control);
        return { result };
#endif
    }

    mathinline Vector4 mathcall MergeXY(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0],
                b.V.U[0],
                a.V.U[1],
                b.V.U[1],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_unpacklo_ps(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vzipq_f32(a.V, b.V).val[0];
        return { result };
#endif
    }

    mathinline Vector4 mathcall MergeZW(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[2],
                b.V.U[2],
                a.V.U[3],
                b.V.U[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_unpackhi_ps(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vzipq_f32(a.V, b.V).val[1];
        return { result };
#endif
    }

    mathinline Vector4 mathcall ShiftLeft(Vector4 a, Vector4 b, uint32_t count) noexcept
    {
        GX_ASSERT(count < 4);
        return Permute(a, b, count + 0, count + 1, count + 2, count + 3);
    }

    mathinline Vector4 mathcall RotateLeft(Vector4 v, uint32_t count) noexcept
    {
        GX_ASSERT(count < 4);
        return Swizzle(v, (count + 0) & 0b11, (count + 1) & 0b11, (count + 2) & 0b11, (count + 3) & 0b11);
    }

    mathinline Vector4 mathcall RotateRight(Vector4 v, uint32_t count) noexcept
    {
        GX_ASSERT(count < 4);
        return Swizzle(v, (4 - count) & 0b11, (5 - count) & 0b11, (6 - count) & 0b11, (7 - count) & 0b11);
    }

    mathinline Vector4 mathcall SumComponents(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const sum = (v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
                sum,
                sum,
                sum,
                sum,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const partial = _mm_hadd_ps(v.V, v.V);
        __m128 const result = _mm_hadd_ps(partial, partial);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const partial = vpaddq_f32(v.V, v.V);
        float32x4_t const result = vpaddq_f32(partial, partial);
        return { result };
#endif
    }
}


// =================================================================================================
//
// Type conversion operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall ToVector4(float x, Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                x,
                v.V.F[0],
                v.V.F[1],
                v.V.F[2],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // [x, y, z, w] -> [w, x, y, z]
        __m128 const wxyz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const xxxx = _mm_set_ss(x);
        __m128 const result = _mm_move_ss(wxyz, xxxx);
        return { result };
#endif
    }

    mathinline Vector4 mathcall ToVector4(Vector3 v, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                v.V.F[0],
                v.V.F[1],
                v.V.F[2],
                w
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww = _mm_set_ss(w);
        __m128 const result = _mm_insert_ps(v.V, wwww, 0x30);
        return { result };
#endif
    }

    mathinline Vector4 mathcall ToVector4(float x, float y, Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                x,
                y,
                v.V.F[0],
                v.V.F[1],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xy00 = _mm_set_ps(0.0F, 0.0F, y, x);
        __m128 const xyxy = _mm_shuffle_ps(xy00, v.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { xyxy };
#endif
    }

    mathinline Vector4 mathcall ToVector4(float x, Vector2 v, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                x,
                v.V.F[0],
                v.V.F[1],
                w,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX

        // [_, x, y, _]
        __m128 const nxyn = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 1, 0, 0));
        // [x', x, y, _]
        __m128 const xxyn = _mm_insert_ps(nxyn, _mm_set_ps1(x), 0x00);
        // [x', x, y, w']
        __m128 const xxyw = _mm_insert_ps(xxyn, _mm_set_ps1(w), 0x30);

        return { xxyw };
#endif
    }

    mathinline Vector4 mathcall ToVector4(Vector2 v, float z, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                v.V.F[0],
                v.V.F[1],
                z,
                w,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // [_, _, z, w]
        __m128 const nnzw = _mm_set_ps(0.0F, 0.0F, w, z);
        // [x, y, z, w]
        __m128 const xyzw = _mm_shuffle_ps(nnzw, v.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { xyzw };
#endif
    }

    mathinline Vector3 mathcall ToVector3(float x, Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                x,
                v.V.F[0],
                v.V.F[1],
                v.V.F[1],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // [_, x, y, y]
        __m128 const nxyn = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 0, 0));
        // [x', x, y, _]
        __m128 const xxyn = _mm_insert_ps(nxyn, _mm_set_ps1(x), 0x00);

        return { xxyn };
#endif
    }

    mathinline Vector3 mathcall ToVector3(Vector2 v, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                v.V.F[0],
                v.V.F[1],
                z,
                z,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_set_ps1(z);
        __m128 const xyzz = _mm_shuffle_ps(v.V, zzzz, _MM_SHUFFLE(1, 0, 1, 0));
        return { xyzz };
#endif
    }
}


// =================================================================================================
//
// Load / store operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Load(Float4A const* source) noexcept
        requires VectorLike<T> and Loadable<T> and (T::Components == 4)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                source->W,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps(reinterpret_cast<float const*>(source)) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4A* destination, T v) noexcept
        requires VectorLike<T> and Storable<T> and (T::Components == 4)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float4 const* source) noexcept
        requires VectorLike<T> and Loadable<T> and (T::Components == 4)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                source->W,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_loadu_ps(reinterpret_cast<float const*>(source)) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4* destination, T v) noexcept
        requires VectorLike<T> and Storable<T> and (T::Components == 4)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3A const* source) noexcept
        requires VectorLike<T> and Loadable<T> and (T::Components >= 3)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xyzn = _mm_load_ps(reinterpret_cast<float const*>(source));
        __m128 const result = _mm_and_ps(xyzn, Impl::VEC4_MASK_COMPONENTS_3.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3A* destination, T v) noexcept
        requires VectorLike<T> and Storable<T> and (T::Components >= 3)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(&destination->Z, zzzz);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3 const* source) noexcept
        requires VectorLike<T> and Loadable<T> and (T::Components >= 3)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        __m128 const v_z = _mm_load_ss(&source->Z);
        __m128 const v_xy = _mm_unpacklo_ps(v_x, v_y);
        __m128 const v_xyz = _mm_movelh_ps(v_xy, v_z);
        return { v_xyz };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3* destination, T v) noexcept
        requires VectorLike<T> and Storable<T> and (T::Components >= 3)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, yyyy);
        _mm_store_ss(&destination->Z, zzzz);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2A const* source) noexcept
        requires VectorLike<T> and Loadable<T> and (T::Components >= 2)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_xy = _mm_loadl_epi64(reinterpret_cast<__m128i* const*>(source));
        return { _mm_castsi128_ps(v_xy) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2A* destination, T v) noexcept
        requires VectorLike<T> and Storable<T> and (T::Components >= 2)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2 const* source) noexcept
        requires VectorLike<T> and Loadable<T> and (T::Components >= 2)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        __m128 const result = _mm_unpacklo_ps(v_x, v_y);
        return { result };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2* destination, T v) noexcept
        requires VectorLike<T> and Storable<T> and (T::Components >= 2)
    {

        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
#endif
    }
}


// =================================================================================================
//
// Component getters and setters
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SplatX(T v) noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[0];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcastss_ps(v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0)) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatY(T v) noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[1];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1)) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatZ(T v) noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[2];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2)) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatW(T v) noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[3];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3)) };
#endif
    }

    template <typename T>
    mathinline float mathcall GetByIndex(T v, size_t index) noexcept
        requires VectorLike<T>
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[index];
#else
        Impl::ConstFloat32x4 result;
        result.V = v.V;
        return result.F[index];
#endif
    }

    template <typename T>
    mathinline T mathcall SetByIndex(T v, float value, size_t index) noexcept
        requires VectorLike<T>
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V = v.V;
        result.F[index] = value;
        return { result.V };
    }

    template <typename T>
    mathinline void mathcall GetByIndex(float* result, T v, size_t index) noexcept
        requires VectorLike<T>
    {
        GX_ASSERT(result != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[index];
#else
        Impl::ConstFloat32x4 r;
        r.V = v.V;
        (*result) = r.F[index];
#endif
    }

    template <typename T>
    mathinline T mathcall SetByIndex(T v, float const* value, size_t index)
        requires VectorLike<T>
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V = v.V;
        result.F[index] = (*value);
        return { result.V };
    }

    template <typename T>
    mathinline float mathcall GetX(T v) noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 0);
#endif
    }

    template <typename T>
    mathinline float mathcall GetY(T v) noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 1);
#endif
    }

    template <typename T>
    mathinline float mathcall GetZ(T v) noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 2);
#endif
    }

    template <typename T>
    mathinline float mathcall GetW(T v) noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 3);
#endif
    }

    template <typename T>
    mathinline void mathcall GetX(float* result, T v) noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(result, v.V);
#endif
    }

    template <typename T>
    mathinline void mathcall GetY(float* result, T v) noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) =  v.V.F[1];
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 1);
#endif
    }

    template <typename T>
    mathinline void mathcall GetZ(float* result, T v) noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) =  v.V.F[2];
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 2);
#endif
    }

    template <typename T>
    mathinline void mathcall GetW(float* result, T v) noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) =  v.V.F[3];
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 3);
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, float value) noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                value,
                v.V.F[1],
                v.V.F[2],
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_set_ss(value);
        __m128 const result = _mm_move_ss(v.V, xxxx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float value) noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                value,
                v.V.F[2],
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, yyyy, 0x10);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float value) noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                value,
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, zzzz, 0x20);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float value) noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                v.V.F[2],
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, wwww, 0x30);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 3) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, float const* value) noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                *value,
                v.V.F[1],
                v.V.F[2],
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_load_ss(value);
        __m128 const result = _mm_move_ss(v.V, xxxx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float const* value) noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                *value,
                v.V.F[2],
                v.V.F[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_yxzw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const yyyy = _mm_load_ss(value);
        __m128 const n_yxzw = _mm_move_ss(o_yxzw, yyyy);
        __m128 const xyzw = _mm_permute_ps(n_yxzw, _MM_SHUFFLE(3, 2, 0, 1));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float const* value) noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                *value,
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_zyxw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const zzzz = _mm_load_ss(value);
        __m128 const n_zyxw = _mm_move_ss(o_zyxw, zzzz);
        __m128 const xyzw = _mm_permute_ps(n_zyxw, _MM_SHUFFLE(3, 0, 1, 2));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float const* value) noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                v.V.F[2],
                *value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_wyzx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        __m128 const wwww = _mm_load_ss(value);
        __m128 const n_wyzx = _mm_move_ss(o_wyzx, wwww);
        __m128 const xyzw = _mm_permute_ps(n_wyzx, _MM_SHUFFLE(0, 2, 1, 3));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 3) };
#endif
    }
}

// =================================================================================================
//
// Constants
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall UnitX() noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
        return { Impl::VEC4_POSITIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall UnitY() noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
        return { Impl::VEC4_POSITIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall UnitZ() noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
        return { Impl::VEC4_POSITIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall UnitW() noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitX() noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitY() noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitZ() noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitW() noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_W.V };
    }


    template <typename T>
    mathinline T mathcall Zero() noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_ZERO_4.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(0.0F) };
#endif
    }

    template <typename T>
    mathinline T mathcall Identity() noexcept = delete;

    template <typename T>
    mathinline bool mathcall IsIdentity(T v) noexcept = delete;

    template <typename T>
    mathinline T mathcall One() noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F,
                1.0F,
                1.0F,
                1.0F,
            } } };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_ONE_4.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(1.0F) };
#endif
    }

    template <typename T>
    mathinline T mathcall Infinity() noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x7F800000,
                0x7F800000,
                0x7F800000,
                0x7F800000,
            } } };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_INFINITY.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x7F800000) };
#endif
    }

    template <typename T>
    mathinline T mathcall Nan() noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x7FC00000,
                0x7FC00000,
                0x7FC00000,
                0x7FC00000,
            } } };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_QNAN.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x7FC00000) };
#endif
    }

    template <typename T>
    mathinline T mathcall Epsilon() noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x34000000,
                0x34000000,
                0x34000000,
                0x34000000,
            } } };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_EPSILON.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x34000000) };
#endif
    }

    template <typename T>
    mathinline T mathcall SignMask() noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x80000000U,
                0x80000000U,
                0x80000000U,
                0x80000000U,
            } } };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set1_epi32(static_cast<int>(0x80000000));
        return { _mm_castsi128_ps(v_temp) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x80000000U) };
#endif

#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_NEGATIVE_ZERO.V };
#elif GRAPHYTE_HW_AVX
#endif
    }
}


// =================================================================================================
//
// Constructors
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Make(float x, float y, float z, float w) noexcept
        requires VectorLike<T> and (T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                z,
                w,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z) noexcept
        requires VectorLike<T> and (T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                z,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, z, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y) noexcept
        requires VectorLike<T> and (T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x) noexcept
        requires VectorLike<T> and (T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                0.0F,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, 0.0F, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Replicate(float value) noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#endif
    }

    template <typename T>
    mathinline T mathcall Replicate(float const* source) noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = (*source);
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(source) };
#endif
    }

    template <typename T>
    mathinline T mathcall MakeUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires VectorLike<T> and Bitwisable<T> and (T::Components == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                x,
                y,
                z,
                w,
            } } };
#elif GRAPHYTE_HW_AVX
        __m128i const ivec = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
            static_cast<int>(y),
            static_cast<int>(x)
        );

        return { _mm_castsi128_ps(ivec) };
#endif
    }

    template <typename T>
    mathinline T mathcall ReplicateUInt(uint32_t value) noexcept
        requires VectorLike<T> and Bitwisable<T> and (T::Components == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const ivec = _mm_set1_epi32(static_cast<int>(value));
        return { _mm_castsi128_ps(ivec) };
#endif
    }

    template <typename T>
    mathinline T mathcall ReplicateUInt(uint32_t const* source) noexcept
        requires VectorLike<T> and Bitwisable<T> and (T::Components == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        uint32_t const value = (*source);

        Impl::ConstUInt32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(reinterpret_cast<float const*>(source)) };
#endif
    }
}


// =================================================================================================
//
// Boolean operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall True() noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0xFFFF'FFFFU,
                0xFFFF'FFFFU,
                0xFFFF'FFFFU,
                0xFFFF'FFFFU,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set1_epi32(-1);
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall False() noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result = { { {
                0.0F,
                0.0F,
                0.0F,
                0.0F
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#endif
    }

    template <typename T>
    mathinline T mathcall And(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] & b.V.U[0],
                a.V.U[1] & b.V.U[1],
                a.V.U[2] & b.V.U[2],
                a.V.U[3] & b.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_and_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall AndNot(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result = { { {
                a.V.U[0] & ~b.V.U[0],
                a.V.U[1] & ~b.V.U[1],
                a.V.U[2] & ~b.V.U[2],
                a.V.U[3] & ~b.V.U[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_andnot_si128(_mm_castps_si128(b.V), _mm_castps_si128(a.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall Or(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] | b.V.U[0],
                a.V.U[1] | b.V.U[1],
                a.V.U[2] | b.V.U[2],
                a.V.U[3] | b.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_or_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall Xor(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] ^ b.V.U[0],
                a.V.U[1] ^ b.V.U[1],
                a.V.U[2] ^ b.V.U[2],
                a.V.U[3] ^ b.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_xor_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall Nor(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                ~(a.V.U[0] | b.V.U[0]),
                ~(a.V.U[1] | b.V.U[1]),
                ~(a.V.U[2] | b.V.U[2]),
                ~(a.V.U[3] | b.V.U[3]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const partial = _mm_or_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        __m128i const result = _mm_andnot_si128(partial, _mm_castps_si128(Impl::VEC4_MASK_NEGATIVE_ONE.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall SelectControl(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        GX_ASSERT(x < 2);
        GX_ASSERT(y < 2);
        GX_ASSERT(z < 2);
        GX_ASSERT(w < 4);

        uint32_t const control[2]{ SELECT_0, SELECT_1 };

        Impl::ConstUInt32x4 const result{ { {
                control[x],
                control[y],
                control[z],
                control[w],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const xyzw = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
            static_cast<int>(y),
            static_cast<int>(x)
        );
        __m128i const zero = _mm_setzero_si128();
        __m128i const control = _mm_cmpgt_epi32(xyzw, zero);
        __m128 const result = _mm_castsi128_ps(control);
        return { result };
#elif GRAPHYTE_HW_NEON
        int32x2_t const xy = vcreate_s32(static_cast<uint64_t>(x) | static_cast<uint64_t>(y) << 32);
        int32x2_t const zw = vcreate_s32(static_cast<uint64_t>(z) | static_cast<uint64_t>(w) << 32);
        int32x4_t const xyzw = vcombine_s32(xy, zw);
        int32x4_t const zero = vdupq_n_s32(0);
        int32x4_t const result = vcgtq_s32(xyzw, zero);
        return { vreinterpretq_f32_s32(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall Select(T a, T b, typename T::MaskType control) noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] & ~control.V.U[0]) | (b.V.U[0] & control.V.U[0]),
                (a.V.U[1] & ~control.V.U[1]) | (b.V.U[1] & control.V.U[1]),
                (a.V.U[2] & ~control.V.U[2]) | (b.V.U[2] & control.V.U[2]),
                (a.V.U[3] & ~control.V.U[3]) | (b.V.U[3] & control.V.U[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const masked1 = _mm_andnot_ps(control.V, a.V);
        __m128 const masked2 = _mm_and_ps(b.V, control.V);
        __m128 const result = _mm_or_ps(masked1, masked2);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = _vbslq_f32(control.V, b.V, a.V);
        return { result };
#endif
    }
}

// =================================================================================================
//
// Boolean type comparison
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall CompareEqual(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] == b.V.U[0]) ? SELECT_1 : SELECT_0,
                (a.V.U[1] == b.V.U[1]) ? SELECT_1 : SELECT_0,
                (a.V.U[2] == b.V.U[2]) ? SELECT_1 : SELECT_0,
                (a.V.U[3] == b.V.U[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall CompareNotEqual(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] != b.V.U[0]) ? SELECT_1 : SELECT_0,
                (a.V.U[1] != b.V.U[1]) ? SELECT_1 : SELECT_0,
                (a.V.U[2] != b.V.U[2]) ? SELECT_1 : SELECT_0,
                (a.V.U[3] != b.V.U[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_xor_ps(_mm_castsi128_ps(result), Impl::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }
}


// =================================================================================================
//
// Boolean mask qualification
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline bool mathcall AllTrue(T v) noexcept
        requires VectorLike<T> and Bitwisable<T> and EqualComparable<T> and (T::Components >= 1) and (T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] != 0)
                && (v.V.U[1] != 0)
                && (v.V.U[2] != 0)
                && (v.V.U[3] != 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] != 0)
                && (v.V.U[1] != 0)
                && (v.V.U[2] != 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] != 0)
                && (v.V.U[1] != 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] != 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) == movemask;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AllFalse(T v) noexcept
        requires VectorLike<T> and Bitwisable<T> and EqualComparable<T> and (T::Components >= 1) and (T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] == 0)
                && (v.V.U[1] == 0)
                && (v.V.U[2] == 0)
                && (v.V.U[3] == 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] == 0)
                && (v.V.U[1] == 0)
                && (v.V.U[2] == 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] == 0)
                && (v.V.U[1] == 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] == 0);
        }
#elif GRAPHYTE_HW_AVX

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) == 0;
        }
        else
        {
            constexpr const int movemask = (1 << T::Components) - 1;
            return (_mm_movemask_ps(v.V) & movemask) == 0;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AnyTrue(T v) noexcept
        requires VectorLike<T> and Bitwisable<T> and EqualComparable<T> and (T::Components >= 1) and (T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] != 0)
                || (v.V.U[1] != 0)
                || (v.V.U[2] != 0)
                || (v.V.U[3] != 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] != 0)
                || (v.V.U[1] != 0)
                || (v.V.U[2] != 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] != 0)
                || (v.V.U[1] != 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] != 0);
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) != 0;
        }
        else
        {
            constexpr const int movemask = (1 << T::Components) - 1;
            return (_mm_movemask_ps(v.V) & movemask) != 0;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AnyFalse(T v) noexcept
        requires VectorLike<T> and Bitwisable<T> and EqualComparable<T> and (T::Components >= 1) and (T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] == 0)
                || (v.V.U[1] == 0)
                || (v.V.U[2] == 0)
                || (v.V.U[3] == 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] == 0)
                || (v.V.U[1] == 0)
                || (v.V.U[2] == 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] == 0)
                || (v.V.U[1] == 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] == 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) != movemask;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & movemask) != movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T> and EqualComparable<T>
    {
        T const result = Maths::CompareEqual(a, b);
        return AllTrue(result);
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires VectorLike<T> and Bitwisable<T> and EqualComparable<T>
    {
        T const result = Maths::CompareNotEqual(a, b);
        return AllTrue(result);
    }

}


// =================================================================================================
//
// Transcendental functions
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Cos(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cos_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Sin(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_sin_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline void mathcall SinCos(T& result_sin, T& result_cos, T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const vsin{ { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };

        Impl::ConstFloat32x4 const vcos{ { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };

        result_sin.V = vsin.V;
        result_cos.V = vcos.V;

#elif GRAPHYTE_MATH_SVML
        sin.V = _mm_sincos_ps(&cos.V, v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Tan(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                tanf(v.V.F[0]),
                tanf(v.V.F[1]),
                tanf(v.V.F[2]),
                tanf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_tan_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Asin(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                asinf(v.V.F[0]),
                asinf(v.V.F[1]),
                asinf(v.V.F[2]),
                asinf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_asin_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Acos(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                acosf(v.V.F[0]),
                acosf(v.V.F[1]),
                acosf(v.V.F[2]),
                acosf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_acos_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Atan(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                atanf(v.V.F[0]),
                atanf(v.V.F[1]),
                atanf(v.V.F[2]),
                atanf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atan_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Atan2(T y, T x) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                atan2f(y.V.F[0], x.V.F[0]),
                atan2f(y.V.F[1], x.V.F[1]),
                atan2f(y.V.F[2], x.V.F[2]),
                atan2f(y.V.F[3], x.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atan2_ps(y.V, x.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Sinh(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sinhf(v.V.F[0]),
                sinhf(v.V.F[1]),
                sinhf(v.V.F[2]),
                sinhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_sinh_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Cosh(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                coshf(v.V.F[0]),
                coshf(v.V.F[1]),
                coshf(v.V.F[2]),
                coshf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cosh_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Tanh(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                tanhf(v.V.F[0]),
                tanhf(v.V.F[1]),
                tanhf(v.V.F[2]),
                tanhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_tanh_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Asinh(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                asinhf(v.V.F[0]),
                asinhf(v.V.F[1]),
                asinhf(v.V.F[2]),
                asinhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_asinh_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Acosh(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                acoshf(v.V.F[0]),
                acoshf(v.V.F[1]),
                acoshf(v.V.F[2]),
                acoshf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_acosh_ps(v.V) };
#endif
    }


    template <typename T>
    mathinline T mathcall Atanh(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                atanhf(v.V.F[0]),
                atanhf(v.V.F[1]),
                atanhf(v.V.F[2]),
                atanhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atanh_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Log(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                logf(v.V.F[0]),
                logf(v.V.F[1]),
                logf(v.V.F[2]),
                logf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Log10(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                log10f(v.V.F[0]),
                log10f(v.V.F[1]),
                log10f(v.V.F[2]),
                log10f(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log10_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Log2(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                log2f(v.V.F[0]),
                log2f(v.V.F[1]),
                log2f(v.V.F[2]),
                log2f(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log2_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                expf(v.V.F[0]),
                expf(v.V.F[1]),
                expf(v.V.F[2]),
                expf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp10(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                powf(10.0F, v.V.F[0]),
                powf(10.0F, v.V.F[1]),
                powf(10.0F, v.V.F[2]),
                powf(10.0F, v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp10_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp2(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                exp2f(v.V.F[0]),
                exp2f(v.V.F[1]),
                exp2f(v.V.F[2]),
                exp2f(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp2_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Power(T x, T y) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                powf(x.V.F[0], y.V.F[0]),
                powf(x.V.F[1], y.V.F[1]),
                powf(x.V.F[2], y.V.F[2]),
                powf(x.V.F[3], y.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_pow_ps(x.V, y.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Hypot(T x, T y) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                hypotf(x.V.F[0], y.V.F[0]),
                hypotf(x.V.F[1], y.V.F[1]),
                hypotf(x.V.F[2], y.V.F[2]),
                hypotf(x.V.F[3], y.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_hypot_ps(x.V, y.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Sqrt(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall SqrtEst(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall InvSqrt(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / sqrtf(v.V.F[0]),
                1.0F / sqrtf(v.V.F[1]),
                1.0F / sqrtf(v.V.F[2]),
                1.0F / sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rsqrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Cbrt(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                cbrtf(v.V.F[0]),
                cbrtf(v.V.F[1]),
                cbrtf(v.V.F[2]),
                cbrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cbrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall InvCbrt(T v) noexcept
        requires VectorLike<T> and Transcendental<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / cbrtf(v.V.F[0]),
                1.0F / cbrtf(v.V.F[1]),
                1.0F / cbrtf(v.V.F[2]),
                1.0F / cbrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_invcbrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Abs(T v) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                fabsf(v.V.F[0]),
                fabsf(v.V.F[1]),
                fabsf(v.V.F[2]),
                fabsf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const result = _mm_max_ps(negative, v.V);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Negate(T v) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                -v.V.F[0],
                -v.V.F[1],
                -v.V.F[2],
                -v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const result = _mm_sub_ps(zero, v.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vnegq_f32(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Negate(T v) noexcept
    {
        return -v;
    }

    template <typename T>
    mathinline T mathcall Add(T a, T b) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] + b.V.F[0],
                a.V.F[1] + b.V.F[1],
                a.V.F[2] + b.V.F[2],
                a.V.F[3] + b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_add_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vaddq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Subtract(T a, T b) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] - b.V.F[0],
                a.V.F[1] - b.V.F[1],
                a.V.F[2] - b.V.F[2],
                a.V.F[3] - b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vsubq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Multiply(T a, T b) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] * b.V.F[0],
                a.V.F[1] * b.V.F[1],
                a.V.F[2] * b.V.F[2],
                a.V.F[3] * b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vmulq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Multiply(T a, typename T::ComponentType b) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] * b,
                a.V.F[1] * b,
                a.V.F[2] * b,
                a.V.F[3] * b,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_set_ps1(b);
        return { _mm_mul_ps(a.V, s) };
#elif GRAPHYTE_HW_NEON
        return { vmulq_n_f32(a.V, b) };
#endif
    }

    template <typename T>
    mathinline T mathcall Divide(T a, T b) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] / b.V.F[0],
                a.V.F[1] / b.V.F[1],
                a.V.F[2] / b.V.F[2],
                a.V.F[3] / b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vdivq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Divide(T a, typename T::ComponentType b) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const invb = 1.0F / b;

        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] * invb,
                a.V.F[1] * invb,
                a.V.F[2] * invb,
                a.V.F[3] * invb,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX

        __m128 const invb = _mm_set_ps1(1.0F / b);
        return { _mm_mul_ps(a.V, invb) };
#endif
    }

    // (a * b) + c
    template <typename T>
    mathinline T mathcall MultiplyAdd(T a, T b, T c) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] * b.V.F[0]) + c.V.F[0],
                (a.V.F[1] * b.V.F[1]) + c.V.F[1],
                (a.V.F[2] * b.V.F[2]) + c.V.F[2],
                (a.V.F[3] * b.V.F[3]) + c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fmadd_ps(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { vfmaq_f32(c.V, a.V, b.V) };
#endif
    }

    // (a * b) - c
    template <typename T>
    mathinline T mathcall MultiplySubtract(T a, T b, T c) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] * b.V.F[0]) - c.V.F[0],
                (a.V.F[1] * b.V.F[1]) - c.V.F[1],
                (a.V.F[2] * b.V.F[2]) - c.V.F[2],
                (a.V.F[3] * b.V.F[3]) - c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fmsub_ps(a.V, b.V, c.V) };
#endif
    }

    // -(a * b) + c
    template <typename T>
    mathinline T mathcall NegateMultiplyAdd(T a, T b, T c) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                -(a.V.F[0] * b.V.F[0]) + c.V.F[0],
                -(a.V.F[1] * b.V.F[1]) + c.V.F[1],
                -(a.V.F[2] * b.V.F[2]) + c.V.F[2],
                -(a.V.F[3] * b.V.F[3]) + c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fnmadd_ps(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { vfmsq_f32(c.V, a.V, b.V) };
#endif
    }

    // -(a * b) - c
    template <typename T>
    mathinline T mathcall NegateMultiplySubtract(T a, T b, T c) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                -(a.V.F[0] * b.V.F[0]) - c.V.F[0],
                -(a.V.F[1] * b.V.F[1]) - c.V.F[1],
                -(a.V.F[2] * b.V.F[2]) - c.V.F[2],
                -(a.V.F[3] * b.V.F[3]) - c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fnmsub_ps(a.V, b.V, c.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Reciprocal(T v) noexcept
        requires VectorLike<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / v.V.F[0],
                1.0F / v.V.F[1],
                1.0F / v.V.F[2],
                1.0F / v.V.F[3],
            } } };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(Impl::VEC4_ONE_4.V) };
#elif GRAPHYTE_HW_NEON
        float32x4_t const one = vdupq_n_f32(1.0F);
        float32x4_t const result = vdivq_f32(one, v.V);
        return { result };
#endif
    }
}


// =================================================================================================
//
// Interpolation
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Lerp(T a, T b, float t) noexcept
        requires VectorLike<T> and Interpolable<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const scale = Make<T>(t);
        T const length = Subtract<T>(b, a);
        T const result = MultiplyAdd<T>(length, scale, a);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_sub_ps(b.V, a.V);
        __m128 const scale = _mm_set_ps1(t);
        __m128 const result = _mm_fmadd_ps(length, scale, a.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Lerp(T a, T b, T t) noexcept
        requires VectorLike<T> and Interpolable<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length = Subtract<T>(b, a);
        T const result = MultiplyAdd<T>(length, t, a);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_sub_ps(b.V, a.V);
        __m128 const result = _mm_fmadd_ps(length, t.V, a.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, float t) noexcept
        requires VectorLike<T> and Interpolable<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const t2 = t * t;
        float const t3 = t * t2;


        T const p0 = Replicate<T>(2.0F * t3 - 3.0F * t2 + 1.0F);
        T const t0 = Replicate<T>(t3 - 2.0F * t2 + t);
        T const p1 = Replicate<T>(-2.0F * t3 + 3.0F * t2);
        T const t1 = Replicate<T>(t3 - t2);

        T const r0 = Multiply<T>(p0, position0);
        T const r1 = MultiplyAdd<T>(t0, tangent0, r0);
        T const r2 = MultiplyAdd<T>(p1, position1, r1);
        T const r3 = MultiplyAdd<T>(t1, tangent1, r2);

        return { r3 };
#elif GRAPHYTE_HW_AVX
        float const t2 = t * t;
        float const t3 = t * t2;

        __m128 const p0 = _mm_set_ps1(2.0F * t3 - 3.0F * t2 + 1.0F);
        __m128 const t0 = _mm_set_ps1(t3 - 2.0F * t2 + t);
        __m128 const p1 = _mm_set_ps1(-2.0F * t3 + 3.0F * t2);
        __m128 const t1 = _mm_set_ps1(t3 - t2);

        __m128 const r0 = _mm_mul_ps(p0, position0.V);
        __m128 const r1 = _mm_fmadd_ps(t0, tangent0.V, r0);
        __m128 const r2 = _mm_fmadd_ps(p1, position1.V, r1);
        __m128 const r3 = _mm_fmadd_ps(t1, tangent1.V, r2);

        return { r3 };
#endif
    }

    template <typename T>
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, T t) noexcept
        requires VectorLike<T>and Interpolable<T>and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const t2 = Multiply<T>(t, t);
        T const t3 = Multiply<T>(t, t2);

        T const p0 = Replicate<T>(2.0F * t3.V.F[0] - 3.0F * t2.V.F[0] + 1.0F);
        T const t0 = Replicate<T>(t3.V.F[1] - 2.0F * t2.V.F[1] + t.V.F[1]);
        T const p1 = Replicate<T>(-2.0F * t3.V.F[2] + 3.0F * t2.V.F[2]);
        T const t1 = Replicate<T>(t3.V.F[2] - t2.V.F[2]);

        T const r0 = Multiply<T>(p0, position0);
        T const r1 = MultiplyAdd<T>(t0, tangent0, r0);
        T const r2 = MultiplyAdd<T>(p1, position1, r1);
        T const r3 = MultiplyAdd<T>(t1, tangent1, r2);

        return { r3 };

#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const catmul_t2{ { {
                -3.0F,
                -2.0F,
                +3.0F,
                -1.0F,
            } } };

        static Impl::ConstFloat32x4 const catmul_t3{ { {
                +2.0F,
                +1.0F,
                -2.0F,
                +1.0F,
            } } };

        __m128 const t2 = _mm_mul_ps(t.V, t.V);
        __m128 const t3 = _mm_mul_ps(t2, t.V);

        __m128 const t2_m = _mm_mul_ps(t2, catmul_t2.V);
        __m128 const t3_m = _mm_mul_ps(t3, catmul_t3.V);

        __m128 const t2t3_ma = _mm_add_ps(t2_m, t3_m);
        __m128 const ty = _mm_and_ps(t.V, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const t2t3ty = _mm_add_ps(t2t3_ma, ty);
        __m128 const tfinal = _mm_add_ps(t2t3ty, Impl::VEC4_POSITIVE_UNIT_X.V);

        __m128 const r0 = _mm_permute_ps(tfinal, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const r1 = _mm_permute_ps(tfinal, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r2 = _mm_permute_ps(tfinal, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r3 = _mm_permute_ps(tfinal, _MM_SHUFFLE(3, 3, 3, 3));

        __m128 const f0 = _mm_mul_ps(r0, position0.V);
        __m128 const f1 = _mm_fmadd_ps(r1, tangent0.V, f0);
        __m128 const f2 = _mm_fmadd_ps(r2, position1.V, f1);
        __m128 const f3 = _mm_fmadd_ps(r3, tangent1.V, f2);

        return { f3 };
#endif
    }

    template <typename T>
    mathinline T mathcall Barycentric(T a, T b, T c, float f, float g) noexcept
        requires VectorLike<T> and Interpolable<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const pba = Subtract<T>(b, a);
        T const pca = Subtract<T>(c, a);
        T const sf = Replicate<T>(f);
        T const sg = Replicate<T>(g);
        T const accum = MultiplyAdd<T>(pba, sf, a);
        T const result = MultiplyAdd<T>(pca, sg, accum);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const pba = _mm_sub_ps(b.V, a.V);
        __m128 const pca = _mm_sub_ps(c.V, a.V);
        __m128 const sf = _mm_set_ps1(f);
        __m128 const sg = _mm_set_ps1(g);
        __m128 const accum = _mm_fmadd_ps(pba, sf, a.V);
        __m128 const result = _mm_fmadd_ps(pca, sg, accum);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const pba = vsubq_f32(b.V, a.V);
        flaot32x4_t const pca = vsubq_f32(c.V, a.V);
        float32x4_t const accum = vmlaq_n_f32(a.V, pba.V, f);
        float32x4_t const result = vmlaq_n_f32(accum, pca, g);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Barycentric(T a, T b, T c, T f, T g) noexcept
        requires VectorLike<T> and Interpolable<T> and Arithmetic<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const pba = Subtract<T>(b, a);
        T const pca = Subtract<T>(c, a);
        T const accum = MultiplyAdd<T>(pba, f, a);
        T const result = MultiplyAdd<T>(pca, g, accum);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const pba = _mm_sub_ps(b.V, a.V);
        __m128 const pca = _mm_sub_ps(c.V, a.V);
        __m128 const accum = _mm_fmadd_ps(pba, f.V, a.V);
        __m128 const result = _mm_fmadd_ps(pca, g.V, accum);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const pba = vsubq_f32(b.V, a.V);
        flaot32x4_t const pca = vsubq_f32(c.V, a.V);
        float32x4_t const accum = vmlaq_f32(a.V, pba, f.V);
        float32x4_t const result = vmlaq_f32(accum, pca, g.V);
        return { result };
#endif
    }
}


// =================================================================================================
//
// Rounding operations
//

namespace Graphyte::Maths::Impl
{
    mathinline float RoundToNearest(float value) noexcept
    {
        float const integral = floorf(value);
        float const fraction = value - integral;

        if (fraction < 0.5F)
        {
            return integral;
        }

        if (fraction > 0.5F)
        {
            return integral + 1.0F;
        }

        float integral_part;

        (void)modff(integral / 2.0F, &integral_part);

        if ((2.0F * integral_part) == integral)
        {
            return integral;
        }

        return integral + 1.0F;
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Ceiling(T v) noexcept
        requires VectorLike<T> and Roundable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                ceilf(v.V.F[0]),
                ceilf(v.V.F[1]),
                ceilf(v.V.F[2]),
                ceilf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_ceil_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        return { vrndpq_f32(v.V) };
#endif
    }

    mathinline float mathcall Ceiling(float value) noexcept
    {
        return ceilf(value);
    }

    template <typename T>
    mathinline T mathcall Floor(T v) noexcept
        requires VectorLike<T> and Roundable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                floorf(v.V.F[0]),
                floorf(v.V.F[1]),
                floorf(v.V.F[2]),
                floorf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_floor_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        return { vrndmq_f32(v.V) };
#endif
    }

    mathinline float mathcall Floor(float value) noexcept
    {
        return floorf(value);
    }

    template <typename T>
    mathinline T mathcall Truncate(T v) noexcept
        requires VectorLike<T> and Roundable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result;

        for (size_t i = 0; i < 4; ++i)
        {
            if (Impl::BitIsNan(v.V.U[i]))
            {
                result.V.U[i] = 0x7fc00000U;
            }
            else if (fabsf(v.V.F[i]) < 8388608.0F)
            {
                result.V.F[i] = static_cast<float>(static_cast<int32_t>(v.V.F[i]));
            }
            else
            {
                result.V.F[i] = v.V.F[i];
            }
        }

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
#elif GRAPHYTE_HW_NEON
        return { vrndq_f32(v.V) };
#endif
    }

    mathinline float mathcall Truncate(float value) noexcept
    {
        return truncf(value);
    }

    template <typename T>
    mathinline T mathcall Round(T v) noexcept
        requires VectorLike<T> and Roundable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                Impl::RoundToNearest(v.V.F[0]),
                Impl::RoundToNearest(v.V.F[1]),
                Impl::RoundToNearest(v.V.F[2]),
                Impl::RoundToNearest(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
#elif GRAPHYTE_HW_NEON
        return { vrndnq_f32(v.V) };
#endif
    }

    mathinline float mathcall Round(float value) noexcept
    {
        return roundf(value);
    }

    template <typename T>
    mathinline T mathcall Fraction(T x, T y) noexcept
        requires VectorLike<T> and Roundable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                fmodf(x.V.F[0], y.V.F[0]),
                fmodf(x.V.F[1], y.V.F[1]),
                fmodf(x.V.F[2], y.V.F[2]),
                fmodf(x.V.F[3], y.V.F[3]),
            } } };
        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_fmod_ps(x.V, y.V) };
#elif GRAPHYTE_HW_AVX
        __m128 const q = _mm_div_ps(x.V, y.V);
        __m128 const t = _mm_round_ps(q, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
        __m128 const c = _mm_cvtepi32_ps(_mm_cvttps_epi32(t));
        __m128 const result = _mm_fnmadd_ps(c, y.V, x.V);
        return { result };
#endif
    }

    mathinline float mathcall Fraction(float x, float y) noexcept
    {
        return fmodf(x, y);
    }
}

// =================================================================================================
//
// Component-wise comparisons
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline typename T::MaskType mathcall CompareEqual(T a, T b) noexcept
        requires VectorLike<T> and EqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] == b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] == b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] == b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] == b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpeq_ps(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareEqual(T a, T b, T epsilon) noexcept
        requires VectorLike<T> and EqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const dx = (a.V.F[0] - b.V.F[0]);
        float const dy = (a.V.F[1] - b.V.F[1]);
        float const dz = (a.V.F[2] - b.V.F[2]);
        float const dw = (a.V.F[3] - b.V.F[3]);

        float const absx = fabsf(dx);
        float const absy = fabsf(dy);
        float const absz = fabsf(dz);
        float const absw = fabsf(dw);

        Impl::ConstUInt32x4 const result{ { {
                (absx <= epsilon.V.F[0]) ? SELECT_1 : SELECT_0,
                (absy <= epsilon.V.F[1]) ? SELECT_1 : SELECT_0,
                (absz <= epsilon.V.F[2]) ? SELECT_1 : SELECT_0,
                (absw <= epsilon.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const delv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const negv = _mm_sub_ps(zero, delv);
        __m128 const absv = _mm_max_ps(delv, negv);
        __m128 const mask = _mm_cmple_ps(absv, epsilon.V);
        return { mask };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareNotEqual(T a, T b) noexcept
        requires VectorLike<T> and EqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] != b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] != b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] != b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] != b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareGreater(T a, T b) noexcept
        requires VectorLike<T> and OrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] > b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] > b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] > b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] > b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpgt_ps(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareGreaterEqual(T a, T b) noexcept
        requires VectorLike<T> and OrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] >= b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] >= b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] >= b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] >= b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpge_ps(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareLess(T a, T b) noexcept
        requires VectorLike<T> and OrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] < b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] < b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] < b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] < b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmplt_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vcltq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareLessEqual(T a, T b) noexcept
        requires VectorLike<T> and OrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] <= b.V.F[0]) ? SELECT_1 : SELECT_0,
                (a.V.F[1] <= b.V.F[1]) ? SELECT_1 : SELECT_0,
                (a.V.F[2] <= b.V.F[2]) ? SELECT_1 : SELECT_0,
                (a.V.F[3] <= b.V.F[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmple_ps(a.V, b.V) };
#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    template <typename T>
    mathinline typename T::MaskType mathcall CompareNan(T v) noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                Impl::BitIsNan(v.V.U[0]) ? SELECT_1 : SELECT_0,
                Impl::BitIsNan(v.V.U[1]) ? SELECT_1 : SELECT_0,
                Impl::BitIsNan(v.V.U[2]) ? SELECT_1 : SELECT_0,
                Impl::BitIsNan(v.V.U[3]) ? SELECT_1 : SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v.V, v.V) };
#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    template <typename T>
    mathinline typename T::MaskType mathcall CompareInfinite(T v) noexcept
        requires VectorLike<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                Impl::BitIsInf(v.V.U[0]) ? SELECT_1 : SELECT_0,
                Impl::BitIsInf(v.V.U[1]) ? SELECT_1 : SELECT_0,
                Impl::BitIsInf(v.V.U[2]) ? SELECT_1 : SELECT_0,
                Impl::BitIsInf(v.V.U[3]) ? SELECT_1 : SELECT_0,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const abs_v = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const result = _mm_cmpeq_ps(abs_v, Impl::VEC4_INFINITY.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareInBounds(T v, T bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]),
                (-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]),
                (-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]),
                (-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const result = _mm_and_ps(mask_le, mask_ge);
        return { result };
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires VectorLike<T> and EqualComparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] == b.V.F[0])
                && (a.V.F[1] == b.V.F[1])
                && (a.V.F[2] == b.V.F[2])
                && (a.V.F[3] == b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] == b.V.F[0])
                && (a.V.F[1] == b.V.F[1])
                && (a.V.F[2] == b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] == b.V.F[0])
                && (a.V.F[1] == b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] == b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return (_mm_movemask_ps(mask) == movemask);
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires VectorLike<T> and EqualComparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] != b.V.F[0])
                || (a.V.F[1] != b.V.F[1])
                || (a.V.F[2] != b.V.F[2])
                || (a.V.F[3] != b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] != b.V.F[0])
                || (a.V.F[1] != b.V.F[1])
                || (a.V.F[2] != b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] != b.V.F[0])
                || (a.V.F[1] != b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] != b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(a.V, b.V);
        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return (_mm_movemask_ps(mask) != 0);
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) != movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreater(T a, T b) noexcept
        requires VectorLike<T> and OrderComparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] > b.V.F[0])
                && (a.V.F[1] > b.V.F[1])
                && (a.V.F[2] > b.V.F[2])
                && (a.V.F[3] > b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] > b.V.F[0])
                && (a.V.F[1] > b.V.F[1])
                && (a.V.F[2] > b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] > b.V.F[0])
                && (a.V.F[1] > b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] > b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);
        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == movemask;
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreaterEqual(T a, T b) noexcept
        requires VectorLike<T> and Comparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] >= b.V.F[0])
                && (a.V.F[1] >= b.V.F[1])
                && (a.V.F[2] >= b.V.F[2])
                && (a.V.F[3] >= b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] >= b.V.F[0])
                && (a.V.F[1] >= b.V.F[1])
                && (a.V.F[2] >= b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] >= b.V.F[0])
                && (a.V.F[1] >= b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] >= b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpge_ps(a.V, b.V);
        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == movemask;
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLess(T a, T b) noexcept
        requires VectorLike<T> and OrderComparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] < b.V.F[0])
                && (a.V.F[1] < b.V.F[1])
                && (a.V.F[2] < b.V.F[2])
                && (a.V.F[3] < b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] < b.V.F[0])
                && (a.V.F[1] < b.V.F[1])
                && (a.V.F[2] < b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] < b.V.F[0])
                && (a.V.F[1] < b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] < b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmplt_ps(a.V, b.V);
        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == movemask;
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLessEqual(T a, T b) noexcept
        requires VectorLike<T> and Comparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] <= b.V.F[0])
                && (a.V.F[1] <= b.V.F[1])
                && (a.V.F[2] <= b.V.F[2])
                && (a.V.F[3] <= b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] <= b.V.F[0])
                && (a.V.F[1] <= b.V.F[1])
                && (a.V.F[2] <= b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] <= b.V.F[0])
                && (a.V.F[1] <= b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] <= b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmple_ps(a.V, b.V);
        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == movemask;
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool InBounds(T v, T bounds) noexcept
        requires VectorLike<T> and Comparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
                && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]))
                && ((-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]));
        }
        else if constexpr (T::Components == 3)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
                && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]));
        }
        else if constexpr (T::Components == 2)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]));
        }
        else if constexpr (T::Components == 1)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]));
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask = _mm_and_ps(mask_le, mask_ge);

        static constexpr const int movemask = (1 << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == movemask;
        }
        else
        {
            return (_mm_movemask_ps(mask) & movemask) == movemask;
        }
#endif
    }

    template <typename T>
    mathinline bool IsNan(T v) noexcept
        requires VectorLike<T> and EqualComparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return isnanf(v.V.F[0])
                || isnanf(v.V.F[1])
                || isnanf(v.V.F[2])
                || isnanf(v.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return isnanf(v.V.F[0])
                || isnanf(v.V.F[1])
                || isnanf(v.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return isnanf(v.V.F[0])
                || isnanf(v.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return isnanf(v.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != 0;
        }
        else
        {
            static constexpr const int movemask = (1 << T::Components) - 1;
            return (_mm_movemask_ps(mask) & movemask) != 0;
        }
#endif
    }

    template <typename T>
    mathinline bool IsInfinity(T v) noexcept
        requires VectorLike<T> and EqualComparable<T> and (T::Components >= 1 && T::Components <= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return std::isinf(v.V.F[0])
                || std::isinf(v.V.F[1])
                || std::isinf(v.V.F[2])
                || std::isinf(v.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return std::isinf(v.V.F[0])
                || std::isinf(v.V.F[1])
                || std::isinf(v.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return std::isinf(v.V.F[0])
                || std::isinf(v.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return std::isinf(v.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const abs = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != 0;
        }
        else
        {
            static constexpr const int movemask = (1 << T::Components) - 1;
            return (_mm_movemask_ps(mask) & movemask) != 0;
        }
#endif
    }
}

// =================================================================================================
//
// Component-wise operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Min(T a, T b) noexcept
        requires VectorLike<T>and Comparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] < b.V.F[0]) ? a.V.F[0] : b.V.F[0],
                (a.V.F[1] < b.V.F[1]) ? a.V.F[1] : b.V.F[1],
                (a.V.F[2] < b.V.F[2]) ? a.V.F[2] : b.V.F[2],
                (a.V.F[3] < b.V.F[3]) ? a.V.F[3] : b.V.F[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_min_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vminq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Max(T a, T b) noexcept
        requires VectorLike<T>and Comparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] < b.V.F[0]) ? b.V.F[0] : a.V.F[0],
                (a.V.F[1] < b.V.F[1]) ? b.V.F[1] : a.V.F[1],
                (a.V.F[2] < b.V.F[2]) ? b.V.F[2] : a.V.F[2],
                (a.V.F[3] < b.V.F[3]) ? b.V.F[3] : a.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_max_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vmaxq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
        requires VectorLike<T>and Comparable<T>
    {
        GX_ASSERT(IsLessEqual(min, max));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T const below = Max<T>(min, v);
        T const result = Min<T>(max, below);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const below = _mm_max_ps(min.V, v.V);
        __m128 const result = _mm_min_ps(max.V, below);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const below = vmaxq_f32(min.V, v.V);
        float32x4_t const result = vminq_f32(max.V, below);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Saturate(T v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const zero = Zero<T>();
        T const one = One<T>();
        return Clamp(v, zero, one);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const one = Impl::VEC4_ONE_4.V;
        __m128 const below = _mm_max_ps(v.V, zero);
        __m128 const result = _mm_min_ps(below, one);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0F);
        float32x4_t const one = vdupq_n_f32(1.0F);
        float32x4_t const below = vmaxq_f32(v.V, zero);
        float32x4_t const result = vminq_f32(below, one);
        return { result };
#endif
    }
}

// =================================================================================================
//
// Vector4 operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Dot(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fdot =
            (a.V.F[0] * b.V.F[0]) +
            (a.V.F[1] * b.V.F[1]) +
            (a.V.F[2] * b.V.F[2]) +
            (a.V.F[3] * b.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(a.V, b.V, 0b1111'1111) };
#endif
    }

    mathinline Vector4 mathcall Cross(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (((b.V.F[2] * c.V.F[3]) - (b.V.F[3] * c.V.F[2])) * a.V.F[1]) - (((b.V.F[1] * c.V.F[3]) - (b.V.F[3] * c.V.F[1])) * a.V.F[2]) + (((b.V.F[1] * c.V.F[2]) - (b.V.F[2] * c.V.F[1])) * a.V.F[3]),
                (((b.V.F[3] * c.V.F[2]) - (b.V.F[2] * c.V.F[3])) * a.V.F[0]) - (((b.V.F[3] * c.V.F[0]) - (b.V.F[0] * c.V.F[3])) * a.V.F[2]) + (((b.V.F[2] * c.V.F[0]) - (b.V.F[0] * c.V.F[2])) * a.V.F[3]),
                (((b.V.F[1] * c.V.F[3]) - (b.V.F[3] * c.V.F[1])) * a.V.F[0]) - (((b.V.F[0] * c.V.F[3]) - (b.V.F[3] * c.V.F[0])) * a.V.F[1]) + (((b.V.F[0] * c.V.F[1]) - (b.V.F[1] * c.V.F[0])) * a.V.F[3]),
                (((b.V.F[2] * c.V.F[1]) - (b.V.F[1] * c.V.F[2])) * a.V.F[0]) - (((b.V.F[2] * c.V.F[0]) - (b.V.F[0] * c.V.F[2])) * a.V.F[1]) + (((b.V.F[1] * c.V.F[0]) - (b.V.F[0] * c.V.F[1])) * a.V.F[2]),
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX

        auto v_result1  = _mm_permute_ps(b.V, _MM_SHUFFLE(2, 1, 3, 2));
        auto v_temp3    = _mm_permute_ps(c.V, _MM_SHUFFLE(1, 3, 2, 3));
        auto v_result   = _mm_mul_ps(v_result1, v_temp3);

        auto v_temp2    = _mm_permute_ps(b.V, _MM_SHUFFLE(1, 3, 2, 3));
        v_temp3         = _mm_permute_ps(v_temp3, _MM_SHUFFLE(1, 3, 0, 1));
        v_temp2         = _mm_mul_ps(v_temp2, v_temp3);
        v_result        = _mm_sub_ps(v_result, v_temp2);

        auto v_temp1    = _mm_permute_ps(a.V, _MM_SHUFFLE(0, 0, 0, 1));
        v_result        = _mm_mul_ps(v_result, v_temp1);

        v_temp2         = _mm_permute_ps(b.V, _MM_SHUFFLE(2, 0, 3, 1));
        v_temp3         = _mm_permute_ps(c.V, _MM_SHUFFLE(0, 3, 0, 3));
        v_temp3         = _mm_mul_ps(v_temp3, v_temp2);
        v_temp2         = _mm_permute_ps(v_temp2, _MM_SHUFFLE(2, 1, 2, 1));
        v_temp1         = _mm_permute_ps(c.V, _MM_SHUFFLE(2, 0, 3, 1));
        v_temp2         = _mm_mul_ps(v_temp2, v_temp1);
        v_temp3         = _mm_sub_ps(v_temp3, v_temp2);
        v_temp1         = _mm_permute_ps(a.V, _MM_SHUFFLE(1, 1, 2, 2));
        v_temp1         = _mm_mul_ps(v_temp1, v_temp3);

        v_result        = _mm_sub_ps(v_result, v_temp1);
        v_temp2         = _mm_permute_ps(b.V, _MM_SHUFFLE(1, 0, 2, 1));
        v_temp3         = _mm_permute_ps(c.V, _MM_SHUFFLE(0, 1, 0, 2));
        v_temp3         = _mm_mul_ps(v_temp3, v_temp2);
        v_temp2         = _mm_permute_ps(v_temp2, _MM_SHUFFLE(2, 0, 2, 1));
        v_temp1         = _mm_permute_ps(c.V, _MM_SHUFFLE(1, 0, 2, 1));
        v_temp1         = _mm_mul_ps(v_temp1, v_temp2);
        v_temp3         = _mm_sub_ps(v_temp3, v_temp1);
        v_temp1         = _mm_permute_ps(a.V, _MM_SHUFFLE(2, 3, 3, 3));
        v_temp3         = _mm_mul_ps(v_temp3, v_temp1);

        v_result        = _mm_add_ps(v_result, v_temp3);

        return { v_result };
#endif
    }

    mathinline Vector4 mathcall LengthSquared(Vector4 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vector4 mathcall Length(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0b1111'1111);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Normalize(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = Length(v).V.F[0];

        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0] * length,
                v.V.F[1] * length,
                v.V.F[2] * length,
                v.V.F[3] * length,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0b1111'1111);
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector4 Orthogonal(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[2],
                v.V.F[3],
                -v.V.F[0],
                -v.V.F[1],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const flip_zw{ { {
                1.0F,
                1.0F,
                -1.0F,
                -1.0F,
            } } };

        __m128 const zwxy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 0, 3, 2));
        __m128 const result = _mm_mul_ps(zwxy, flip_zw.V);
        return { result };
#endif
    }

    mathinline Vector4 mathcall Transform(Vector4 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = (m.M.M[0][0] * v.V.F[0]) + (m.M.M[1][0] * v.V.F[1]) + (m.M.M[2][0] * v.V.F[2]) + (m.M.M[3][0] * v.V.F[3]);
        float const fy = (m.M.M[0][1] * v.V.F[0]) + (m.M.M[1][1] * v.V.F[1]) + (m.M.M[2][1] * v.V.F[2]) + (m.M.M[3][1] * v.V.F[3]);
        float const fz = (m.M.M[0][2] * v.V.F[0]) + (m.M.M[1][2] * v.V.F[1]) + (m.M.M[2][2] * v.V.F[2]) + (m.M.M[3][2] * v.V.F[3]);
        float const fw = (m.M.M[0][3] * v.V.F[0]) + (m.M.M[1][3] * v.V.F[1]) + (m.M.M[2][3] * v.V.F[2]) + (m.M.M[3][3] * v.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
                fx,
                fy,
                fz,
                fw,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        __m128 const wwww       = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const wwww_r3    = _mm_mul_ps(wwww, m.M.R[3]);
        __m128 const zzzz       = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const zzzz_r2_r3 = _mm_fmadd_ps(zzzz, m.M.R[2], wwww_r3);
        __m128 const yyyy       = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const yyyy_r1_r2 = _mm_fmadd_ps(yyyy, m.M.R[1], zzzz_r2_r3);
        __m128 const xxxx       = _mm_broadcastss_ps(v.V);
        __m128 const xxxx_r0_r1 = _mm_fmadd_ps(xxxx, m.M.R[0], yyyy_r1_r2);
        return { xxxx_r0_r1 };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww       = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const wwww_r3    = _mm_mul_ps(wwww, m.M.R[3]);
        __m128 const zzzz       = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const zzzz_r2    = _mm_mul_ps(zzzz, m.M.R[2]);
        __m128 const zzzz_r2_r3 = _mm_add_ps(zzzz_r2, wwww_r3);
        __m128 const yyyy       = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const yyyy_r1    = _mm_mul_ps(yyyy, m.M.R[1]);
        __m128 const yyyy_r1_r2 = _mm_add_ps(yyyy_r1, zzzz_r2);
        __m128 const xxxx       = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const xxxx_r0    = _mm_mul_ps(xxxx, m.M.R[0]);
        __m128 const xxxx_r0_r1 = _mm_add_ps(xxxx_r0, yyyy_r1);
        return { xxxx_r0_r1 };
#endif
    }

    mathinline Vector4 mathcall Reflect(Vector4 incident, Vector4 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal)) * normal
        Vector4 const dot = Dot(incident, normal);
        Vector4 const dot_2 = Add(dot, dot);
        Vector4 const result = NegateMultiplyAdd(dot_2, normal, incident);
        return result;
    }
}


// =================================================================================================
//
// Vector3 operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Dot(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fdot =
            (a.V.F[0] * b.V.F[0]) +
            (a.V.F[1] * b.V.F[1]) +
            (a.V.F[2] * b.V.F[2]);

        Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(a.V, b.V, 0b0111'1111) };
#endif
    }

    mathinline Vector4 mathcall Cross(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[1] * b.V.F[2]) - (a.V.F[2] * b.V.F[1]),
                (a.V.F[2] * b.V.F[0]) - (a.V.F[0] * b.V.F[2]),
                (a.V.F[0] * b.V.F[1]) - (a.V.F[1] * b.V.F[0]),
                0.0F,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const a_yzxw = _mm_permute_ps(a.V, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const b_zxyw = _mm_permute_ps(b.V, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 const mul_a_yzxw_b_zxyw = _mm_mul_ps(a_yzxw, b_zxyw);
        __m128 const a_zxyw = _mm_permute_ps(a_yzxw, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const b_yzxw = _mm_permute_ps(b_zxyw, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 const mul_a_zxyw_b_yzxw = _mm_mul_ps(a_zxyw, b_yzxw);
        __m128 const sub_ab_ba = _mm_sub_ps(mul_a_yzxw_b_zxyw, mul_a_zxyw_b_yzxw);
        __m128 const result = _mm_and_ps(sub_ab_ba, Impl::VEC4_MASK_COMPONENTS_3.V);
        return { result };
#endif
    }

    mathinline Vector4 mathcall LengthSquared(Vector3 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vector4 mathcall Length(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector3 mathcall Normalize(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = Length(v).V.F[0];

        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0] * length,
                v.V.F[1] * length,
                v.V.F[2] * length,
                v.V.F[3] * length,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector3 mathcall Reflect(Vector3 incident, Vector3 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal)) * normal
        Vector3 const dot = AsVector3(Dot(incident, normal));
        Vector3 const dot_2 = Add(dot, dot);
        Vector3 const result = NegateMultiplyAdd(dot_2, normal, incident);
        return result;
    }
}

// =================================================================================================
//
// Vector2 operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Dot(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fdot =
            (a.V.F[0] * b.V.F[0]) +
            (a.V.F[1] * b.V.F[1]);

        Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(a.V, b.V, 0b0011'1111) };
#endif
    }

    mathinline Vector2 mathcall Cross(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = (a.V.F[0] * b.V.F[1]) - (a.V.F[1] * b.V.F[0]);
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // b.yx * a.xy = [b.y * a.x, b.x * a.y]
        __m128 const b_yx = _mm_permute_ps(b.V, _MM_SHUFFLE(0, 1, 0, 1));
        __m128 const b_yx_mul_a_xy = _mm_mul_ps(b_yx, a.V);

        __m128 const bx_mul_ay = _mm_permute_ps(b_yx_mul_a_xy, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const by_mul_ax_sub_bx_mul_ay = _mm_sub_ss(b_yx_mul_a_xy, bx_mul_ay);

        __m128 const result = _mm_permute_ps(by_mul_ax_sub_bx_mul_ay, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector4 mathcall LengthSquared(Vector2 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vector4 mathcall Length(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector2 mathcall Normalize(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = Length(v).V.F[0];

        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0] * length,
                v.V.F[1] * length,
                v.V.F[2] * length,
                v.V.F[3] * length,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector2 mathcall Reflect(Vector2 incident, Vector2 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal)) * normal
        Vector2 const dot = AsVector2(Dot(incident, normal));
        Vector2 const dot_2 = Add(dot, dot);
        Vector2 const result = NegateMultiplyAdd(dot_2, normal, incident);
        return result;
    }
}

// =================================================================================================
//
// Quaternion operations
//

namespace Graphyte::Maths
{
    template <>
    mathinline Quaternion mathcall Identity<Quaternion>() noexcept
    {
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }

    template <>
    mathinline bool mathcall IsIdentity<Quaternion>(Quaternion v) noexcept
    {
        return IsEqual<Vector4>(AsVector4(v), { Impl::VEC4_POSITIVE_UNIT_W.V });
    }

    mathinline Vector4 mathcall Dot(Quaternion a, Quaternion b) noexcept
    {
        return Dot(AsVector4(a), AsVector4(b));
    }

    mathinline Vector4 mathcall LengthSquared(Quaternion v) noexcept
    {
        return LengthSquared(AsVector4(v));
    }

    mathinline Vector4 mathcall Length(Quaternion v) noexcept
    {
        return Length(AsVector4(v));
    }
}


// =================================================================================================
//
// Matrix operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Load(Float4x4A const* source) noexcept
        requires MatrixLike<T> and (T::Rows == 4) and (T::Columns == 4)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.R[0].F[0] = source->M[0][0];
        result.M.R[0].F[1] = source->M[0][1];
        result.M.R[0].F[2] = source->M[0][2];
        result.M.R[0].F[3] = source->M[0][3];

        result.M.R[1].F[0] = source->M[1][0];
        result.M.R[1].F[1] = source->M[1][1];
        result.M.R[1].F[2] = source->M[1][2];
        result.M.R[1].F[3] = source->M[1][3];

        result.M.R[2].F[0] = source->M[2][0];
        result.M.R[2].F[1] = source->M[2][1];
        result.M.R[2].F[2] = source->M[2][2];
        result.M.R[2].F[3] = source->M[2][3];

        result.M.R[3].F[0] = source->M[3][0];
        result.M.R[3].F[1] = source->M[3][1];
        result.M.R[3].F[2] = source->M[3][2];
        result.M.R[3].F[3] = source->M[3][3];

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;

        result.M.R[0] = _mm_load_ps(&source->M11);
        result.M.R[1] = _mm_load_ps(&source->M21);
        result.M.R[2] = _mm_load_ps(&source->M31);
        result.M.R[3] = _mm_load_ps(&source->M41);

        return result;

#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4x4A* destination, T m) noexcept
        requires MatrixLike<T> and (T::Rows == 4) and (T::Columns == 4)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];
        destination->M[0][3] = m.M.R[0].F[3];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];
        destination->M[1][3] = m.M.R[1].F[3];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[2].F[3];

        destination->M[3][0] = m.M.R[3].F[0];
        destination->M[3][1] = m.M.R[3].F[1];
        destination->M[3][2] = m.M.R[3].F[2];
        destination->M[3][3] = m.M.R[3].F[3];

#elif GRAPHYTE_HW_AVX

        _mm_store_ps(&destination->M11, m.M.R[0]);
        _mm_store_ps(&destination->M21, m.M.R[1]);
        _mm_store_ps(&destination->M31, m.M.R[2]);
        _mm_store_ps(&destination->M41, m.M.R[3]);

#endif
    }

#if false
    template <typename T>
    mathinline T mathcall Load(Float4x3A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.R[0].F[0] = source->M[0][0];
        result.M.R[0].F[1] = source->M[0][1];
        result.M.R[0].F[2] = source->M[0][2];
        result.M.R[0].F[3] = 0.0F;

        result.M.R[1].F[0] = source->M[1][0];
        result.M.R[1].F[1] = source->M[1][1];
        result.M.R[1].F[2] = source->M[1][2];
        result.M.R[1].F[3] = 0.0F;

        result.M.R[2].F[0] = source->M[2][0];
        result.M.R[2].F[1] = source->M[2][1];
        result.M.R[2].F[2] = source->M[2][2];
        result.M.R[2].F[3] = 0.0F;

        result.M.R[3].F[0] = source->M[3][0];
        result.M.R[3].F[1] = source->M[3][1];
        result.M.R[3].F[2] = source->M[3][2];
        result.M.R[3].F[3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX
#endif
    }
#endif

    //mathinline Matrix mathcall Load(Float4x3A const* source) noexcept;
    //mathinline Matrix mathcall Load(Float3x4A const* source) noexcept;
    //mathinline Matrix mathcall
    //mathinline Matrix mathcall Load(Float3x3 const* source) noexcept;

    mathinline Matrix mathcall Multiply(Matrix a, Matrix b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        {
            float const x = a.M.M[0][0];
            float const y = a.M.M[0][1];
            float const z = a.M.M[0][2];
            float const w = a.M.M[0][3];

            result.M.M[0][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[0][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[0][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[0][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[1][0];
            float const y = a.M.M[1][1];
            float const z = a.M.M[1][2];
            float const w = a.M.M[1][3];

            result.M.M[1][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[1][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[1][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[1][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[2][0];
            float const y = a.M.M[2][1];
            float const z = a.M.M[2][2];
            float const w = a.M.M[2][3];

            result.M.M[2][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[2][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[2][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[2][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[3][0];
            float const y = a.M.M[3][1];
            float const z = a.M.M[3][2];
            float const w = a.M.M[3][3];

            result.M.M[3][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[3][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[3][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[3][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;

        __m128 const x_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);

        __m128 const abx_r0 = _mm_mul_ps(x_r0, b.M.R[0]);
        __m128 const aby_r0 = _mm_fmadd_ps(y_r0, b.M.R[1], abx_r0);
        __m128 const abz_r0 = _mm_fmadd_ps(z_r0, b.M.R[2], aby_r0);
        __m128 const abw_r0 = _mm_fmadd_ps(w_r0, b.M.R[3], abz_r0);

        __m128 const x_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);

        __m128 const abx_r1 = _mm_mul_ps(x_r1, b.M.R[0]);
        __m128 const aby_r1 = _mm_fmadd_ps(y_r1, b.M.R[1], abx_r1);
        __m128 const abz_r1 = _mm_fmadd_ps(z_r1, b.M.R[2], aby_r1);
        __m128 const abw_r1 = _mm_fmadd_ps(w_r1, b.M.R[3], abz_r1);

        __m128 const x_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);

        __m128 const abx_r2 = _mm_mul_ps(x_r2, b.M.R[0]);
        __m128 const aby_r2 = _mm_fmadd_ps(y_r2, b.M.R[1], abx_r2);
        __m128 const abz_r2 = _mm_fmadd_ps(z_r2, b.M.R[2], aby_r2);
        __m128 const abw_r2 = _mm_fmadd_ps(w_r2, b.M.R[3], abz_r2);

        __m128 const x_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);

        __m128 const abx_r3 = _mm_mul_ps(x_r3, b.M.R[0]);
        __m128 const aby_r3 = _mm_fmadd_ps(y_r3, b.M.R[1], abx_r3);
        __m128 const abz_r3 = _mm_fmadd_ps(z_r3, b.M.R[2], aby_r3);
        __m128 const abw_r3 = _mm_fmadd_ps(w_r3, b.M.R[3], abz_r3);

        result.M.R[0] = abw_r0;
        result.M.R[1] = abw_r1;
        result.M.R[2] = abw_r2;
        result.M.R[3] = abw_r3;

        return result;

#endif
    }

    mathinline Matrix mathcall MultiplyTranspose(Matrix a, Matrix b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        {
            float const x = b.M.M[0][0];
            float const y = b.M.M[0][1];
            float const z = b.M.M[0][2];
            float const w = b.M.M[0][3];

            result.M.M[0][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[0][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[0][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[0][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[1][0];
            float const y = b.M.M[1][1];
            float const z = b.M.M[1][2];
            float const w = b.M.M[1][3];

            result.M.M[1][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[1][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[1][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[1][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[2][0];
            float const y = b.M.M[2][1];
            float const z = b.M.M[2][2];
            float const w = b.M.M[2][3];

            result.M.M[2][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[2][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[2][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[2][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[3][0];
            float const y = b.M.M[3][1];
            float const z = b.M.M[3][2];
            float const w = b.M.M[3][3];

            result.M.M[3][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[3][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[3][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[3][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        return result;

#elif GRAPHYTE_HW_AVX
        Matrix result;

        __m128 const x_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);

        __m128 const abx_r0 = _mm_mul_ps(x_r0, b.M.R[0]);
        __m128 const aby_r0 = _mm_fmadd_ps(y_r0, b.M.R[1], abx_r0);
        __m128 const abz_r0 = _mm_fmadd_ps(z_r0, b.M.R[2], aby_r0);
        __m128 const abw_r0 = _mm_fmadd_ps(w_r0, b.M.R[3], abz_r0);

        __m128 const x_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);

        __m128 const abx_r1 = _mm_mul_ps(x_r1, b.M.R[0]);
        __m128 const aby_r1 = _mm_fmadd_ps(y_r1, b.M.R[1], abx_r1);
        __m128 const abz_r1 = _mm_fmadd_ps(z_r1, b.M.R[2], aby_r1);
        __m128 const abw_r1 = _mm_fmadd_ps(w_r1, b.M.R[3], abz_r1);

        __m128 const x_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);

        __m128 const abx_r2 = _mm_mul_ps(x_r2, b.M.R[0]);
        __m128 const aby_r2 = _mm_fmadd_ps(y_r2, b.M.R[1], abx_r2);
        __m128 const abz_r2 = _mm_fmadd_ps(z_r2, b.M.R[2], aby_r2);
        __m128 const abw_r2 = _mm_fmadd_ps(w_r2, b.M.R[3], abz_r2);

        __m128 const x_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);

        __m128 const abx_r3 = _mm_mul_ps(x_r3, b.M.R[0]);
        __m128 const aby_r3 = _mm_fmadd_ps(y_r3, b.M.R[1], abx_r3);
        __m128 const abz_r3 = _mm_fmadd_ps(z_r3, b.M.R[2], aby_r3);
        __m128 const abw_r3 = _mm_fmadd_ps(w_r3, b.M.R[3], abz_r3);

        __m128 const trn_r0 = _mm_shuffle_ps(abw_r0, abw_r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trn_r2 = _mm_shuffle_ps(abw_r0, abw_r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const trn_r1 = _mm_shuffle_ps(abw_r2, abw_r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trn_r3 = _mm_shuffle_ps(abw_r2, abw_r3, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const final_r0 = _mm_shuffle_ps(trn_r0, trn_r1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const final_r1 = _mm_shuffle_ps(trn_r0, trn_r1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const final_r2 = _mm_shuffle_ps(trn_r2, trn_r3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const final_r3 = _mm_shuffle_ps(trn_r2, trn_r3, _MM_SHUFFLE(3, 1, 3, 1));

        result.M.R[0] = final_r0;
        result.M.R[1] = final_r1;
        result.M.R[2] = final_r2;
        result.M.R[3] = final_r3;

        return result;
#endif
    }

    mathinline Matrix mathcall Transpose(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.F[0][0] = b.M.F[0][0];
        result.M.F[0][1] = b.M.F[1][0];
        result.M.F[0][2] = b.M.F[2][0];
        result.M.F[0][3] = b.M.F[3][0];

        result.M.F[1][0] = b.M.F[0][1];
        result.M.F[1][1] = b.M.F[1][1];
        result.M.F[1][2] = b.M.F[2][1];
        result.M.F[1][3] = b.M.F[3][1];

        result.M.F[2][0] = b.M.F[0][2];
        result.M.F[2][1] = b.M.F[1][2];
        result.M.F[2][2] = b.M.F[2][2];
        result.M.F[2][3] = b.M.F[3][2];

        result.M.F[3][0] = b.M.F[0][3];
        result.M.F[3][1] = b.M.F[1][3];
        result.M.F[3][2] = b.M.F[2][3];
        result.M.F[3][3] = b.M.F[3][3];

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const trx_r0 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trx_r2 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const trx_r1 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trx_r3 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const res_r0 = _mm_shuffle_ps(trx_r0, trx_r1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const res_r1 = _mm_shuffle_ps(trx_r0, trx_r1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const res_r2 = _mm_shuffle_ps(trx_r2, trx_r3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const res_r3 = _mm_shuffle_ps(trx_r2, trx_r3, _MM_SHUFFLE(3, 1, 3, 1));

        Matrix result;
        result.M.R[0] = res_r0;
        result.M.R[1] = res_r1;
        result.M.R[2] = res_r2;
        result.M.R[3] = res_r3;
        return result;
#endif
    }

    template <typename T>
    mathinline T mathcall Nan() noexcept
        requires MatrixLike<T> and (T::Rows == 4) and (T::Columns == 4)
    {
        T result;
        result.M.R[0] = Impl::VEC4_QNAN.V;
        result.M.R[1] = Impl::VEC4_QNAN.V;
        result.M.R[2] = Impl::VEC4_QNAN.V;
        result.M.R[3] = Impl::VEC4_QNAN.V;
        return result;
    }


#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    template <typename T>
    mathinline bool mathcall IsNan(T m) noexcept
        requires MatrixLike<T> and (T::Rows == 4) and (T::Columns == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        size_t count = T::Components;

        uint32_t const* item = reinterpret_cast<uint32_t const*>(&m.M.F[0]);

        do
        {
            uint32_t const value = (*item);
            uint32_t const umask = value & 0x7fff'ffffU;
            uint32_t const unan = umask - 0x7f80'0001U;

            if (unan < 0x007f'ffffU)
            {
                break;
            }

            ++item;
        } while (--count != 0);

        return count != 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const eq_r0 = _mm_cmpneq_ps(r0, r0);
        __m128 const eq_r1 = _mm_cmpneq_ps(r1, r1);
        __m128 const eq_r2 = _mm_cmpneq_ps(r2, r2);
        __m128 const eq_r3 = _mm_cmpneq_ps(r3, r3);

        __m128 const eq_r0r1 = _mm_or_ps(eq_r0, eq_r1);
        __m128 const eq_r2r3 = _mm_or_ps(eq_r2, eq_r3);

        __m128 const eq_r0r1r2r3 = _mm_or_ps(eq_r0r1, eq_r2r3);

        return _mm_movemask_ps(eq_r0r1r2r3) != 0;

#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    template <typename T>
    mathinline Matrix mathcall Infinity() noexcept
        requires MatrixLike<T> and (T::Rows == 4) and (T::Columns == 4)
    {
        T result;

        result.M.R[0] = Impl::VEC4_INFINITY.V;
        result.M.R[1] = Impl::VEC4_INFINITY.V;
        result.M.R[2] = Impl::VEC4_INFINITY.V;
        result.M.R[3] = Impl::VEC4_INFINITY.V;

        return result;
    }

    template <typename T>
    mathinline bool mathcall IsInfinity(T m) noexcept
        requires MatrixLike<T> and (T::Rows == 4) and (T::Columns == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        size_t count = T::Components;

        uint32_t const* item = reinterpret_cast<uint32_t const*>(&m.M.F[0]);

        do
        {
            uint32_t const value = (*item);
            uint32_t const umask = value & 0x7fff'ffffU;

            if (umask == 0x7f80'0000U)
            {
                break;
            }

            ++item;
        } while (--count != 0);

        return count != 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const abs = Impl::VEC4_MASK_ABS.V;

        __m128 const abs_r0 = _mm_and_ps(r0, abs);
        __m128 const abs_r1 = _mm_and_ps(r1, abs);
        __m128 const abs_r2 = _mm_and_ps(r2, abs);
        __m128 const abs_r3 = _mm_and_ps(r3, abs);

        __m128 const inf = Impl::VEC4_INFINITY.V;

        __m128 const inf_r0 = _mm_cmpeq_ps(abs_r0, inf);
        __m128 const inf_r1 = _mm_cmpeq_ps(abs_r1, inf);
        __m128 const inf_r2 = _mm_cmpeq_ps(abs_r2, inf);
        __m128 const inf_r3 = _mm_cmpeq_ps(abs_r3, inf);

        __m128 const inf_r0r1 = _mm_or_ps(inf_r0, inf_r1);
        __m128 const inf_r2r3 = _mm_or_ps(inf_r2, inf_r3);

        __m128 const inf_r0r1r2r3 = _mm_or_ps(inf_r0r1, inf_r2r3);

        return _mm_movemask_ps(inf_r0r1r2r3) != 0;

#endif
    }

    template <>
    mathinline Matrix mathcall Identity<Matrix>() noexcept
    {
        Matrix result;
        result.M.R[0] = Impl::VEC4_POSITIVE_UNIT_X.V;
        result.M.R[1] = Impl::VEC4_POSITIVE_UNIT_Y.V;
        result.M.R[2] = Impl::VEC4_POSITIVE_UNIT_Z.V;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;
        return result;
    }

    template <>
    mathinline bool mathcall IsIdentity<Matrix>(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        uint32_t const* items = reinterpret_cast<uint32_t const*>(&m.M.M[0][0]);

        uint32_t one = items[0] ^ 0x3f80'0000;
        uint32_t zero = items[1];
        zero |= items[2];
        zero |= items[3];

        zero |= items[4];
        one |= items[5];
        zero |= items[6];
        zero |= items[7];

        zero |= items[8];
        zero |= items[9];
        one |= items[10];
        zero |= items[11];

        zero |= items[12];
        zero |= items[13];
        zero |= items[14];
        one |= items[15] ^ 0x3f80'0000;

        // clear sign mask
        zero &= 0x7fff'ffff;
        one |= zero;

        return one == 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const m0 = _mm_cmpeq_ps(r0, Impl::VEC4_POSITIVE_UNIT_X.V);
        __m128 const m1 = _mm_cmpeq_ps(r1, Impl::VEC4_POSITIVE_UNIT_Y.V);
        __m128 const m2 = _mm_cmpeq_ps(r2, Impl::VEC4_POSITIVE_UNIT_Z.V);
        __m128 const m3 = _mm_cmpeq_ps(r3, Impl::VEC4_POSITIVE_UNIT_W.V);

        __m128 const m1_0 = _mm_and_ps(m0, m1);
        __m128 const m1_1 = _mm_and_ps(m2, m3);

        __m128 const m2_final = _mm_and_ps(m1_0, m1_1);

        return _mm_movemask_ps(m2_final) == 0b1111;
#endif
    }

    mathinline Vector4 mathcall GetBaseX(Matrix m) noexcept
    {
        return { m.M.R[0] };
    }

    mathinline Vector4 mathcall GetBaseY(Matrix m) noexcept
    {
        return { m.M.R[1] };
    }

    mathinline Vector4 mathcall GetBaseZ(Matrix m) noexcept
    {
        return { m.M.R[2] };
    }

    mathinline Vector4 mathcall GetBaseW(Matrix m) noexcept
    {
        return { m.M.R[3] };
    }
}

