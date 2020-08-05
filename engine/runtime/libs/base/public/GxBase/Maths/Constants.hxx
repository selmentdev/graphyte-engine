#pragma once
#include <GxBase/Maths/Base.hxx>

// NOTE:
//  `c_V[X]_F[Y]_` - constant vector with X components and type Y
//  `c_S_` - templated scalar constant value
//  `c_S_F[X]_` - constant scalar with type X 

namespace Graphyte::Maths::Impl
{
    template <typename T>
    inline constexpr const T c_S_E = static_cast<T>(2.71828182845904523536028747135266249775724709369996);

    template <typename T>
    inline constexpr const T c_S_Log2E = static_cast<T>(1.44269504088896340735992468100189213742664595415299);

    template <typename T>
    inline constexpr const T c_S_Log10E = static_cast<T>(0.43429448190325182765112891891660508229439700580367);

    template <typename T>
    inline constexpr const T c_S_Ln2 = static_cast<T>(0.69314718055994530941723212145817656807550013436026);

    template <typename T>
    inline constexpr const T c_S_Ln10 = static_cast<T>(2.30258509299404568401799145468436420760110148862877);

    template <typename T>
    inline constexpr const T c_S_Pi = static_cast<T>(3.14159265358979323846264338327950288419716939937510);

    template <typename T>
    inline constexpr const T c_S_Pi2 = static_cast<T>(6.28318530717958647692528676655900576839433879875021);

    template <typename T>
    inline constexpr const T c_S_InvPi = static_cast<T>(0.31830988618379067153776752674502872406891929148091);

    template <typename T>
    inline constexpr const T c_S_InvPi2 = static_cast<T>(0.15915494309189533576888376337251436203445964574045);

    template <typename T>
    inline constexpr const T c_S_InvSqrtPi = static_cast<T>(0.56418958354775628694807945156077258584405062932899);

    template <typename T>
    inline constexpr const T c_S_Sqrt2 = static_cast<T>(1.41421356237309504880168872420969807856967187537695);

    template <typename T>
    inline constexpr const T c_S_Sqrt3 = static_cast<T>(1.73205080756887729352744634150587236694280525381038);

    template <typename T>
    inline constexpr const T c_S_Sqrt5 = static_cast<T>(2.23606797749978969640917366873127623544061835961153);

    template <typename T>
    inline constexpr const T c_S_InvSqrt2 = static_cast<T>(0.70710678118654752440084436210484903928483593768847);

    template <typename T>
    inline constexpr const T c_S_InvSqrt3 = static_cast<T>(0.57735026918962576450914878050195745564760175127013);

    template <typename T>
    inline constexpr const T c_S_InvSqrt5 = static_cast<T>(0.44721359549995793928183473374625524708812367192231);

    template <typename T>
    inline constexpr const T c_S_Phi = static_cast<T>(1.61803398874989484820458683436563811772030917980576);

    template <typename T>
    inline constexpr const T c_S_Gamma = static_cast<T>(0.57721566490153286060651209008240243104215933593992);

    template <typename T>
    inline constexpr const T c_S_PiDiv2 = static_cast<T>(1.57079632679489661923132169163975144209858469968755);

    template <typename T>
    inline constexpr const T c_S_PiDiv3 = static_cast<T>(1.04719755119659774615421446109316762806572313312504);

    template <typename T>
    inline constexpr const T c_S_PiDiv4 = static_cast<T>(0.78539816339744830961566084581987572104929234984378);

    template <typename T>
    inline constexpr const T c_S_PiDiv6 = static_cast<T>(0.52359877559829887307710723054658381403286156656252);

    template <typename T>
    inline constexpr const T c_S_PiDiv8 = static_cast<T>(0.39269908169872415480783042290993786052464617492189);

    template <typename T>
    inline constexpr const T c_S_EpsilonAngular = static_cast<T>(0.001);

    template <typename T>
    inline constexpr const T c_S_EpsilonLow = static_cast<T>(0.0002);

    template <typename T>
    inline constexpr const T c_S_Epsilon = static_cast<T>(0.000035);

    template <typename T>
    inline constexpr const T c_S_EpsilonHigh = static_cast<T>(0.0000005);

    inline constexpr const uint32_t SELECT_0      = 0x00000000u;
    inline constexpr const uint32_t SELECT_1      = 0xFFFFFFFFu;


    inline constexpr const uint32_t PERMUTE_0X = 0;
    inline constexpr const uint32_t PERMUTE_0Y = 1;
    inline constexpr const uint32_t PERMUTE_0Z = 2;
    inline constexpr const uint32_t PERMUTE_0W = 3;
    inline constexpr const uint32_t PERMUTE_1X = 4;
    inline constexpr const uint32_t PERMUTE_1Y = 5;
    inline constexpr const uint32_t PERMUTE_1Z = 6;
    inline constexpr const uint32_t PERMUTE_1W = 7;

    inline constexpr const size_t CACHE_LINE_SIZE = 64;

    template <typename T>
    inline constexpr const T c_S_RoundingError = 0;

    template <>
    inline constexpr const float c_S_RoundingError<float> = 0.000001f;

    template <>
    inline constexpr const double c_S_RoundingError<double> = 0.00000001;
}


// =================================================================================================
//
// Vector constants
//

namespace Graphyte::Maths::Impl
{
    // clang-format off
    mathconst ConstFloat32x4 c_V4_F32_PositiveUnitX{ { { 1.0f, 0.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_PositiveUnitY{ { { 0.0f, 1.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_PositiveUnitZ{ { { 0.0f, 0.0f, 1.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_PositiveUnitW{ { { 0.0f, 0.0f, 0.0f, 1.0f, } } };

    mathconst ConstFloat32x4 c_V4_F32_NegativeUnitX{ { { 1.0f, 0.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_NegativeUnitY{ { { 0.0f, 1.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_NegativeUnitZ{ { { 0.0f, 0.0f, 1.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_NegativeUnitW{ { { 0.0f, 0.0f, 0.0f, 1.0f, } } };

    mathconst ConstFloat32x4 c_V4_F32_Negate_X{ { { -1.0f, 1.0f, 1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_Negate_Y{ { { 1.0f, -1.0f, 1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_Negate_Z{ { { 1.0f, 1.0f, -1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_Negate_W{ { { 1.0f, 1.0f, 1.0f, -1.0f, } } };

    mathconst ConstFloat32x4 c_V4_F32_Zero{ { { 0.0f, 0.0f, 0.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_One{ { { 1.0f, 1.0f, 1.0f, 1.0f, } } };
    mathconst ConstFloat32x4 c_V3_F32_One{ { { 1.0f, 1.0f, 1.0f, 0.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_Negative_One{ { { -1.0f, -1.0f, -1.0f, -1.0f, } } };

    mathconst ConstFloat32x4 c_V4_F32_One_Half{ { { 0.5f, 0.5f, 0.5f, 0.5f, } } };
    mathconst ConstFloat32x4 c_V4_F32_Negative_One_Half{ { { -0.5f, -0.5f, -0.5f, -0.5f, } } };

    mathconst ConstFloat32x4 c_V4_F32_E = { { { c_S_E<float>, c_S_E<float>, c_S_E<float>, c_S_E<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Log2E = { { { c_S_Log2E<float>, c_S_Log2E<float>, c_S_Log2E<float>, c_S_Log2E<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Log10E = { { { c_S_Log10E<float>, c_S_Log10E<float>, c_S_Log10E<float>, c_S_Log10E<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Ln2 = { { { c_S_Ln2<float>, c_S_Ln2<float>, c_S_Ln2<float>, c_S_Ln2<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Ln10 = { { { c_S_Ln10<float>, c_S_Ln10<float>, c_S_Ln10<float>, c_S_Ln10<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Pi = { { { c_S_Pi<float>, c_S_Pi<float>, c_S_Pi<float>, c_S_Pi<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Pi2 = { { { c_S_Pi2<float>, c_S_Pi2<float>, c_S_Pi2<float>, c_S_Pi2<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_InvPi = { { { c_S_InvPi<float>, c_S_InvPi<float>, c_S_InvPi<float>, c_S_InvPi<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_InvPi2 = { { { c_S_InvPi2<float>, c_S_InvPi2<float>, c_S_InvPi2<float>, c_S_InvPi2<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_InvSqrtPi = { { { c_S_InvSqrtPi<float>, c_S_InvSqrtPi<float>, c_S_InvSqrtPi<float>, c_S_InvSqrtPi<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Sqrt2 = { { { c_S_Sqrt2<float>, c_S_Sqrt2<float>, c_S_Sqrt2<float>, c_S_Sqrt2<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Sqrt3 = { { { c_S_Sqrt3<float>, c_S_Sqrt3<float>, c_S_Sqrt3<float>, c_S_Sqrt3<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Sqrt5 = { { { c_S_Sqrt5<float>, c_S_Sqrt5<float>, c_S_Sqrt5<float>, c_S_Sqrt5<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_InvSqrt2 = { { { c_S_InvSqrt2<float>, c_S_InvSqrt2<float>, c_S_InvSqrt2<float>, c_S_InvSqrt2<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_InvSqrt3 = { { { c_S_InvSqrt3<float>, c_S_InvSqrt3<float>, c_S_InvSqrt3<float>, c_S_InvSqrt3<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_InvSqrt5 = { { { c_S_InvSqrt5<float>, c_S_InvSqrt5<float>, c_S_InvSqrt5<float>, c_S_InvSqrt5<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Phi = { { { c_S_Phi<float>, c_S_Phi<float>, c_S_Phi<float>, c_S_Phi<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Gamma = { { { c_S_Gamma<float>, c_S_Gamma<float>, c_S_Gamma<float>, c_S_Gamma<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_PiDiv2 = { { { c_S_PiDiv2<float>, c_S_PiDiv2<float>, c_S_PiDiv2<float>, c_S_PiDiv2<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_PiDiv3 = { { { c_S_PiDiv3<float>, c_S_PiDiv3<float>, c_S_PiDiv3<float>, c_S_PiDiv3<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_PiDiv4 = { { { c_S_PiDiv4<float>, c_S_PiDiv4<float>, c_S_PiDiv4<float>, c_S_PiDiv4<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_PiDiv6 = { { { c_S_PiDiv6<float>, c_S_PiDiv6<float>, c_S_PiDiv6<float>, c_S_PiDiv6<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_PiDiv8 = { { { c_S_PiDiv8<float>, c_S_PiDiv8<float>, c_S_PiDiv8<float>, c_S_PiDiv8<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_EpsilonAngular = { { { c_S_EpsilonAngular<float>, c_S_EpsilonAngular<float>, c_S_EpsilonAngular<float>, c_S_EpsilonAngular<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_EpsilonLow = { { { c_S_EpsilonLow<float>, c_S_EpsilonLow<float>, c_S_EpsilonLow<float>, c_S_EpsilonLow<float>, } } };
    //mathconst ConstFloat32x4 c_V4_F32_Epsilon = { { { c_S_Epsilon<float>, c_S_Epsilon<float>, c_S_Epsilon<float>, c_S_Epsilon<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Epsilon = { { { 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, 1.192092896e-7f, } } };
    mathconst ConstFloat32x4 c_V4_F32_EpsilonHigh = { { { c_S_EpsilonHigh<float>, c_S_EpsilonHigh<float>, c_S_EpsilonHigh<float>, c_S_EpsilonHigh<float>, } } };
    mathconst ConstFloat32x4 c_V4_F32_Unit_Epsilon = { { { 1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f, } } };
    mathconst ConstFloat32x4 c_V4_F32_RoundingError = { { { c_S_RoundingError<float>, c_S_RoundingError<float>, c_S_RoundingError<float>, c_S_RoundingError<float>, } } };

    mathconst ConstUInt32x4 c_V4_F32_Negative_Zero{ { { FloatTraits<float>::Sign, FloatTraits<float>::Sign, FloatTraits<float>::Sign, FloatTraits<float>::Sign, } } };
    mathconst ConstUInt32x4 c_V3_F32_Negative_Zero{ { { FloatTraits<float>::Sign, FloatTraits<float>::Sign, FloatTraits<float>::Sign, 0u, } } };

    mathconst ConstUInt32x4 c_V4_U32_Mask_1111 = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_1110 = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_1100 = { { { 0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_1000 = { { { 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_0100 = { { { 0x00000000u, 0xFFFFFFFFu, 0x00000000u, 0x00000000u, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_0010 = { { { 0x00000000u, 0x00000000u, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_0001 = { { { 0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_0101 = { { { 0x00000000u, 0xFFFFFFFFu, 0x00000000u, 0xFFFFFFFFu, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_1010 = { { { 0xFFFFFFFFu, 0x00000000u, 0xFFFFFFFFu, 0x00000000u, } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_1011 = { { { 0xFFFFFFFFu, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, } } };

    mathconst ConstUInt32x4 c_V4_U32_Sign_0100 = { { {
            0u,
            FloatTraits<float>::Sign,
            0u,
            0u,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Sign_0010 = { { {
            0u,
            0u,
            FloatTraits<float>::Sign,
            0u,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Sign_0001 = { { {
            0u,
            0u,
            0u,
            FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Sign_0110 = { { {
            0u,
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
            0u,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Sign_0011 = { { {
            0u,
            0u,
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Sign_0101 = { { {
            0u,
            FloatTraits<float>::Sign,
            0u,
            FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Positive_Infinity{ { {
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Negative_Infinity{ { {
            FloatTraits<float>::Infinity | FloatTraits<float>::Sign,
            FloatTraits<float>::Infinity | FloatTraits<float>::Sign,
            FloatTraits<float>::Infinity | FloatTraits<float>::Sign,
            FloatTraits<float>::Infinity | FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Positive_QNan{ { {
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Negative_QNan{ { {
            FloatTraits<float>::QNaN | FloatTraits<float>::Sign,
            FloatTraits<float>::QNaN | FloatTraits<float>::Sign,
            FloatTraits<float>::QNaN | FloatTraits<float>::Sign,
            FloatTraits<float>::QNaN | FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Positive_Max{ { {
            FloatTraits<float>::Max,
            FloatTraits<float>::Max,
            FloatTraits<float>::Max,
            FloatTraits<float>::Max,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Negative_Max{ { {
            FloatTraits<float>::Max | FloatTraits<float>::Sign,
            FloatTraits<float>::Max | FloatTraits<float>::Sign,
            FloatTraits<float>::Max | FloatTraits<float>::Sign,
            FloatTraits<float>::Max | FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Positive_Min{ { {
            FloatTraits<float>::Min,
            FloatTraits<float>::Min,
            FloatTraits<float>::Min,
            FloatTraits<float>::Min,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Negative_Min{ { {
            FloatTraits<float>::Min | FloatTraits<float>::Sign,
            FloatTraits<float>::Min | FloatTraits<float>::Sign,
            FloatTraits<float>::Min | FloatTraits<float>::Sign,
            FloatTraits<float>::Min | FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Positive_Min_Normal{ { {
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
            FloatTraits<float>::MinNormal,
        } } };

    mathconst ConstUInt32x4 c_V4_F32_Negative_Min_Normal{ { {
            FloatTraits<float>::MinNormal | FloatTraits<float>::Sign,
            FloatTraits<float>::MinNormal | FloatTraits<float>::Sign,
            FloatTraits<float>::MinNormal | FloatTraits<float>::Sign,
            FloatTraits<float>::MinNormal | FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Mask_Sign{ { {
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
            FloatTraits<float>::Sign,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Mask_Mantissa{ { {
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
            FloatTraits<float>::Mantissa,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Mask_Exponent{ { {
            FloatTraits<float>::Exponent,
            FloatTraits<float>::Exponent,
            FloatTraits<float>::Exponent,
            FloatTraits<float>::Exponent,
        } } };

    mathconst ConstUInt32x4 c_V4_U32_Mask_MaskAbs{ { {
            FloatTraits<float>::MaskAbs,
            FloatTraits<float>::MaskAbs,
            FloatTraits<float>::MaskAbs,
            FloatTraits<float>::MaskAbs,
        } } };

    mathconst ConstFloat32x4 c_V4_F32_U8_Max = { { { 255.0f, 255.0f, 255.0f, 255.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_S8_Min = { { { -127.0f, -127.0f, -127.0f, -127.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_S8_Max = { { { 127.0f, 127.0f, 127.0f, 127.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_S16_Min = { { { -32767.0f, -32767.0f, -32767.0f, -32767.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_S16_Max = { { { 32767.0f, 32767.0f, 32767.0f, 32767.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_S32_Max = { { { 65536.0f * 32768.0f - 128.0f, 65536.0f * 32768.0f - 128.0f, 65536.0f * 32768.0f - 128.0f, 65536.0f * 32768.0f - 128.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_U32_Max = { { { 65536.0f * 65536.0f - 256.0f, 65536.0f * 65536.0f - 256.0f, 65536.0f * 65536.0f - 256.0f, 65536.0f * 65536.0f - 256.0f, } } };
    mathconst ConstFloat32x4 c_V4_F32_U32_Fix = { { { 32768.0f * 65536.0f, 32768.0f * 65536.0f, 32768.0f * 65536.0f, 32768.0f * 65536.0f, } } };

    // clang-format on
}
