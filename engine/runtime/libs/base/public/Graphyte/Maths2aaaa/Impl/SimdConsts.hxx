#pragma once
#include <Graphyte/Maths2/Impl/Simd.hxx>
#include <Graphyte/Maths2/Consts.hxx>

namespace Graphyte::Maths::Impl
{

    mathconst Vec4F32 VEC4_POSITIVE_UNIT_X = { { { 1.0F, 0.0F, 0.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_POSITIVE_UNIT_Y = { { { 0.0F, 1.0F, 0.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_POSITIVE_UNIT_Z = { { { 0.0F, 0.0F, 1.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_POSITIVE_UNIT_W = { { { 0.0F, 0.0F, 0.0F, 1.0F } } };

    mathconst Vec4F32 VEC4_NEGATIVE_UNIT_X = { { { -1.0F, 0.0F, 0.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_NEGATIVE_UNIT_Y = { { { 0.0F, -1.0F, 0.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_NEGATIVE_UNIT_Z = { { { 0.0F, 0.0F, -1.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_NEGATIVE_UNIT_W = { { { 0.0F, 0.0F, 0.0F, -1.0F } } };

    mathconst Vec4F32 VEC4_NEGATE_X = { { { -1.0F, 1.0F, 1.0F, 1.0F } } };
    mathconst Vec4F32 VEC4_NEGATE_Y = { { { 1.0F, -1.0F, 1.0F, 1.0F } } };
    mathconst Vec4F32 VEC4_NEGATE_Z = { { { 1.0F, 1.0F, -1.0F, 1.0F } } };
    mathconst Vec4F32 VEC4_NEGATE_W = { { { 1.0F, 1.0F, 1.0F, -1.0F } } };

    mathconst Vec4F32 VEC4_ZERO_4 = { { { 0.0F, 0.0F, 0.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_ONE_4 = { { { 1.0F, 1.0F, 1.0F, 1.0F } } };
    mathconst Vec4F32 VEC4_ONE_3 = { { { 1.0F, 1.0F, 1.0F, 0.0F } } };
    mathconst Vec4F32 VEC4_NEGATIVE_ONE_4 = { { { -1.0F, -1.0F, -1.0F, -1.0F } } };
    mathconst Vec4F32 VEC4_ONE_HALF_4 = { { { 0.5F, 0.5F, 0.5F, 0.5F } } };
    mathconst Vec4F32 VEC4_NEGATIVE_ONE_HALF_4 = { { { -0.5F, -0.5F, -0.5F, -0.5F } } };
    mathconst Vec4F32 VEC4_HALF_4 = { { { 0.5F, 0.5F, 0.5F, 0.5F } } };
    mathconst Vec4F32 VEC4_NEGATIVE_HALF_4 = { { { -0.5F, -0.5F, -0.5F, -0.5F } } };
    mathconst Vec4F32 VEC4_TWO_4 = { { { 2.0F, 2.0F, 2.0F, 2.0F } } };
    mathconst Vec4F32 VEC4_FOUR_4 = { { { 4.0F, 4.0F, 4.0F, 4.0F } } };
    mathconst Vec4F32 VEC4_SIX_4 = { { { 6.0F, 6.0F, 6.0F, 6.0F } } };

    mathconst Vec4U32 VEC4_NEGATIVE_ZERO = { { { 0x80000000, 0x80000000, 0x80000000, 0x80000000 } } };
    mathconst Vec4U32 VEC4_NEGATIVE_ZERO_3 = { { { 0x80000000, 0x80000000, 0x80000000, 0x00000000 } } };

    mathconst Vec4U32 VEC4_INFINITY = { { { 0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000 } } };
    mathconst Vec4U32 VEC4_QNAN = { { { 0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000 } } };
    mathconst Vec4U32 VEC4_QNAN_TEST = { { { 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF } } };
    mathconst Vec4U32 VEC4_FLOAT_MIN = { { { 0x00800000, 0x00800000, 0x00800000, 0x00800000 } } };
    mathconst Vec4U32 VEC4_FLOAT_MAX = { { { 0x7F7FFFFF, 0x7F7FFFFF, 0x7F7FFFFF, 0x7F7FFFFF } } };
    mathconst Vec4F32 VEC4_EPSILON = { { { 1.192092896e-7F, 1.192092896e-7F, 1.192092896e-7F, 1.192092896e-7F } } };

    mathconst Vec4F32 VEC4_NO_FRACTION = { { { 8388608.0F, 8388608.0F, 8388608.0F, 8388608.0F } } };

    mathconst Vec4U32 VEC4_ONE_HALF_MINUS_EPS = { { { 0x3EFFFFFD, 0x3EFFFFFD, 0x3EFFFFFD, 0x3EFFFFFD } } };

    mathconst Vec4F32 VEC4_2PI = { { { PI2<float>, PI2<float>, PI2<float>, PI2<float> } } };
    mathconst Vec4F32 VEC4_NEGATIVE_2PI = { { { -PI2<float>, -PI2<float>, -PI2<float>, -PI2<float> } } };
    mathconst Vec4F32 VEC4_RECIPROCAL_2PI = { { { ONE_OVER_PI2<float>, ONE_OVER_PI2<float>, ONE_OVER_PI2<float>, ONE_OVER_PI2<float> } } };

    mathconst Vec4F32 VEC4_PI = { { { PI<float>, PI<float>, PI<float>, PI<float> } } };
    mathconst Vec4F32 VEC4_NEGATIVE_PI = { { { -PI<float>, -PI<float>, -PI<float>, -PI<float> } } };
    mathconst Vec4F32 VEC4_RECIPROCAL_PI = { { { ONE_OVER_PI<float>, ONE_OVER_PI<float>, ONE_OVER_PI<float>, ONE_OVER_PI<float> } } };

    mathconst Vec4F32 VEC4_HALF_PI = { { { PI_OVER_2<float>, PI_OVER_2<float>, PI_OVER_2<float>, PI_OVER_2<float> } } };

    // sin cos log exp implementation: http://gruntthepeon.free.fr/ssemath/
    mathconst Vec4F32 VEC4_PI_CONSTANTS_0 = { { { PI<float>, PI2<float>, ONE_OVER_PI<float>, ONE_OVER_PI2<float> } } };

    mathconst Vec4F32 VEC4_SIN_COEFFICIENTS_0 = { { { -0.16666667F, +0.0083333310F, -0.00019840874F, +2.7525562e-06F } } };
    mathconst Vec4F32 VEC4_SIN_COEFFICIENTS_1 = { { { -2.3889859e-08F, -0.16665852F, +0.0083139502F, -0.00018524670F } } };

    mathconst Vec4F32 VEC4_COS_COEFFICIENTS_0 = { { { -0.5F, +0.041666638F, -0.0013888378F, +2.4760495e-05F } } };
    mathconst Vec4F32 VEC4_COS_COEFFICIENTS_1 = { { { -2.6051615e-07F, -0.49992746F, +0.041493919F, -0.0012712436F } } };

    mathconst Vec4F32 VEC4_TAN_COEFFICIENTS_0 = { { { 1.0F, 0.333333333F, 0.133333333F, 5.396825397e-2F } } };
    mathconst Vec4F32 VEC4_TAN_COEFFICIENTS_1 = { { { 2.186948854e-2F, 8.863235530e-3F, 3.592128167e-3F, 1.455834485e-3F } } };
    mathconst Vec4F32 VEC4_TAN_COEFFICIENTS_2 = { { { 5.900274264e-4F, 2.391290764e-4F, 9.691537707e-5F, 3.927832950e-5F } } };

    mathconst Vec4F32 VEC4_ARC_COEFFICIENTS_0 = { { { +1.5707963050F, -0.2145988016F, +0.0889789874F, -0.0501743046F } } };
    mathconst Vec4F32 VEC4_ARC_COEFFICIENTS_1 = { { { +0.0308918810F, -0.0170881256F, +0.0066700901F, -0.0012624911F } } };

    mathconst Vec4F32 VEC4_ATAN_COEFFICIENTS_0 = { { { -0.3333314528F, +0.1999355085F, -0.1420889944F, +0.1065626393F } } };
    mathconst Vec4F32 VEC4_ATAN_COEFFICIENTS_1 = { { { -0.0752896400F, +0.0429096138F, -0.0161657367F, +0.0028662257F } } };

    mathconst Vec4F32 VEC4_ATAN_EST_COEFFICIENTS_0 = { { { +0.999866F, +0.999866F, +0.999866F, +0.999866F } } };
    mathconst Vec4F32 VEC4_ATAN_EST_COEFFICIENTS_1 = { { { -0.3302995F, +0.180141F, -0.085133F, +0.0208351F } } };

    mathconst Vec4F32 VEC4_TAN_EST_COEFFICIENTS_0 = { { { 2.484F, -1.954923183e-1F, 2.467401101F, ONE_OVER_PI<float> } } };

    mathconst Vec4F32 VEC4_ARC_EST_COEFFICIENTS_0 = { { { +1.5707288F, -0.2121144F, +0.0742610F, -0.0187293F } } };

    mathconst Vec4F32 VEC4_EXP_EST_1 = { { { -6.93147182e-1F, -6.93147182e-1F, -6.93147182e-1F, -6.93147182e-1F } } };
    mathconst Vec4F32 VEC4_EXP_EST_2 = { { { +2.40226462e-1F, +2.40226462e-1F, +2.40226462e-1F, +2.40226462e-1F } } };
    mathconst Vec4F32 VEC4_EXP_EST_3 = { { { -5.55036440e-2F, -5.55036440e-2F, -5.55036440e-2F, -5.55036440e-2F } } };
    mathconst Vec4F32 VEC4_EXP_EST_4 = { { { +9.61597636e-3F, +9.61597636e-3F, +9.61597636e-3F, +9.61597636e-3F } } };
    mathconst Vec4F32 VEC4_EXP_EST_5 = { { { -1.32823968e-3F, -1.32823968e-3F, -1.32823968e-3F, -1.32823968e-3F } } };
    mathconst Vec4F32 VEC4_EXP_EST_6 = { { { +1.47491097e-4F, +1.47491097e-4F, +1.47491097e-4F, +1.47491097e-4F } } };
    mathconst Vec4F32 VEC4_EXP_EST_7 = { { { -1.08635004e-5F, -1.08635004e-5F, -1.08635004e-5F, -1.08635004e-5F } } };

    mathconst Vec4F32 VEC4_LOG_EST_0 = { { { +1.442693F, +1.442693F, +1.442693F, +1.442693F } } };
    mathconst Vec4F32 VEC4_LOG_EST_1 = { { { -0.721242F, -0.721242F, -0.721242F, -0.721242F } } };
    mathconst Vec4F32 VEC4_LOG_EST_2 = { { { +0.479384F, +0.479384F, +0.479384F, +0.479384F } } };
    mathconst Vec4F32 VEC4_LOG_EST_3 = { { { -0.350295F, -0.350295F, -0.350295F, -0.350295F } } };
    mathconst Vec4F32 VEC4_LOG_EST_4 = { { { +0.248590F, +0.248590F, +0.248590F, +0.248590F } } };
    mathconst Vec4F32 VEC4_LOG_EST_5 = { { { -0.145700F, -0.145700F, -0.145700F, -0.145700F } } };
    mathconst Vec4F32 VEC4_LOG_EST_6 = { { { +0.057148F, +0.057148F, +0.057148F, +0.057148F } } };
    mathconst Vec4F32 VEC4_LOG_EST_7 = { { { -0.010578F, -0.010578F, -0.010578F, -0.010578F } } };

    mathconst Vec4F32 VEC4_LGE = { { { +1.442695F, +1.442695F, +1.442695F, +1.442695F } } };
    mathconst Vec4F32 VEC4_INV_LGE = { { { +6.93147182e-1F, +6.93147182e-1F, +6.93147182e-1F, +6.93147182e-1F } } };

    mathconst Vec4U32 VEC4_MASK_QNAN = { { { 0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF } } };
    mathconst Vec4U32 VEC4_MASK_ABS = { { { 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF } } };
    mathconst Vec4U32 VEC4_MASK_NEGATIVE_ONE = { { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF } } };

    mathconst Vec4U32 VEC4_MASK_COMPONENTS_3 = { { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_COMPONENT_X = { { { 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_COMPONENT_Y = { { { 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_COMPONENT_Z = { { { 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_COMPONENT_W = { { { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF } } };

    mathconst Vec4U32 VEC4_MASK_SELECT_0101 = { { { 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF } } };
    mathconst Vec4U32 VEC4_MASK_SELECT_1010 = { { { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_SELECT_1000 = { { { 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_SELECT_0001 = { { { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF } } };
    mathconst Vec4U32 VEC4_MASK_SELECT_1100 = { { { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_SELECT_1110 = { { { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000 } } };
    mathconst Vec4U32 VEC4_MASK_SELECT_1011 = { { { 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF } } };

    mathconst Vec4U32 VEC4_MASK_A8R8G8B8 = { { { 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000 } } };
    mathconst Vec4U32 VEC4_FLIP_A_A8R8G8B8 = { { { 0x00000000, 0x00000000, 0x00000000, 0x80000000 } } };
    mathconst Vec4F32 VEC4_FIX_A_A8R8G8B8 = { { { 0.0F, 0.0F, 0.0F, static_cast<float>(0x80000000U) } } };
    mathconst Vec4F32 VEC4_NORMALIZE_A8R8G8B8 = { { {
            1.0F / (255.0F * static_cast<float>(0x10000)),
            1.0F / (255.0F * static_cast<float>(0x100)),
            1.0F / 255.0F,
            1.0F / (255.0F * static_cast<float>(0x1000000))
        } } };
    mathconst Vec4F32 VEC4_COLOR_SCALE = { { { 255.0F, 255.0F, 255.0F, 255.0F } } };
    mathconst Vec4F32 VEC4_COLOR_LUMINANCE = { { { 0.2125F, 0.7154F, 0.0721F, 0.0F } } };

    mathconst Vec4S32 VEC4_EXPONENT_BIAS = { { { 127, 127, 127, 127 } } };
    mathconst Vec4S32 VEC4_SUBNORMAL_EXPONENT = { { { -126, -126, -126, -126 } } };
    mathconst Vec4S32 VEC4_NUM_TRAILING = { { { 23, 23, 23, 23 } } };
    mathconst Vec4S32 VEC4_MIN_NORMAL = { { { 0x00800000, 0x00800000, 0x00800000, 0x00800000 } } };
    mathconst Vec4U32 VEC4_NEGATIVE_INFINITY = { { { 0xFF800000, 0xFF800000, 0xFF800000, 0xFF800000 } } };
    mathconst Vec4U32 VEC4_NEGATIVE_QNAN = { { { 0xFFC00000, 0xFFC00000, 0xFFC00000, 0xFFC00000 } } };
    mathconst Vec4S32 VEC4_BIN_128 = { { { 0x43000000, 0x43000000, 0x43000000, 0x43000000 } } };
    mathconst Vec4U32 VEC4_BIN_NEG_150 = { { { 0xC3160000, 0xC3160000, 0xC3160000, 0xC3160000 } } };
    mathconst Vec4S32 VEC4_VALUE253 = { { { 253, 253, 253, 253 } } };

    mathconst Vec4F32 VEC4_MSRGB_SCALE = { { { 12.92F, 12.92F, 12.92F, 1.0F } } };
    mathconst Vec4F32 VEC4_MSRGB_A = { { { 0.055F, 0.055F, 0.055F, 0.0F } } };
    mathconst Vec4F32 VEC4_MSRGB_A1 = { { { 1.055F, 1.055F, 1.055F, 1.0F } } };

    mathconst Vec4F32 VEC4_UNSIGNED_FIX = { { {
            32768.0F * 65536.0F,
            32768.0F * 65536.0F,
            32768.0F * 65536.0F,
            32768.0F * 65536.0F
        } } };
    mathconst Vec4F32 VEC4_INTMAX = { { {
            65536.0F * 32768.0F - 128.0F,
            65536.0F * 32768.0F - 128.0F,
            65536.0F * 32768.0F - 128.0F,
            65536.0F * 32768.0F - 128.0F
        } } };
    mathconst Vec4F32 VEC4_UINTMAX = { { {
            65536.0F * 65536.0F - 256.0F,
            65536.0F * 65536.0F - 256.0F,
            65536.0F * 65536.0F - 256.0F,
            65536.0F * 65536.0F - 256.0F
        } } };

    mathconst Vec4U32 VEC4_MASK_FLIP_Y = { { { UINT32_C(0), UINT32_C(0x80000000), UINT32_C(0), UINT32_C(0) } } };
    mathconst Vec4U32 VEC4_MASK_FLIP_Z = { { { UINT32_C(0), UINT32_C(0), UINT32_C(0x80000000), UINT32_C(0) } } };
    mathconst Vec4U32 VEC4_MASK_FLIP_W = { { { UINT32_C(0), UINT32_C(0), UINT32_C(0), UINT32_C(0x80000000) } } };
    mathconst Vec4U32 VEC4_MASK_FLIP_YZ = { { { UINT32_C(0), UINT32_C(0x80000000), UINT32_C(0x80000000), UINT32_C(0) } } };
    mathconst Vec4U32 VEC4_MASK_FLIP_ZW = { { { UINT32_C(0), UINT32_C(0), UINT32_C(0x80000000), UINT32_C(0x80000000) } } };
    mathconst Vec4U32 VEC4_MASK_FLIP_YW = { { { UINT32_C(0), UINT32_C(0x80000000), UINT32_C(0), UINT32_C(0x80000000) } } };
    mathconst Vec4U32 VEC4_MASK_DEC4 = { { { UINT32_C(0x3FF), UINT32_C(0x3FF) << UINT32_C(10), UINT32_C(0x3FF) << UINT32_C(20), UINT32_C(0x3) << UINT32_C(30) } } };
    mathconst Vec4U32 VEC4_MASK_XOR_DEC4 = { { {
            UINT32_C(0x200),
            UINT32_C(0x200) << UINT32_C(10),
            UINT32_C(0x200) << UINT32_C(20),
            UINT32_C(0)
        } } };

    mathconst Vec4F32 VEC4_ADD_UDEC4 = { { { 0.0F, 0.0F, 0.0F, 32768.0F * 65536.0F } } };
    mathconst Vec4F32 VEC4_ADD_DEC4 = { { { -512.0F, -512.0F * 1024.0F, -512.0F * 1024.0F * 1024.0F, 0 } } };
    mathconst Vec4F32 VEC4_MUL_DEC4 = { { {
            1.0F,
            1.0F / 1024.0F,
            1.0F / (1024.0F * 1024.0F),
            1.0F / (1024.0F * 1024.0F * 1024.0F)
        } } };

    mathconst Vec4F32 VEC4_UBYTE_MAX = { { { 255.0f, 255.0f, 255.0f, 255.0f } } };
    mathconst Vec4F32 VEC4_BYTE_MIN = { { { -127.0f, -127.0f, -127.0f, -127.0f } } };
    mathconst Vec4F32 VEC4_BYTE_MAX = { { { 127.0f, 127.0f, 127.0f, 127.0f } } };
    mathconst Vec4F32 VEC4_SHORT_MIN = { { { -32767.0f, -32767.0f, -32767.0f, -32767.0f } } };
    mathconst Vec4F32 VEC4_SHORT_MAX = { { { 32767.0f, 32767.0f, 32767.0f, 32767.0f } } };
    mathconst Vec4F32 VEC4_USHORT_MAX = { { { 65535.0f, 65535.0f, 65535.0f, 65535.0f } } };

}
