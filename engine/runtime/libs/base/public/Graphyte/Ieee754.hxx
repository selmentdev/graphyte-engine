#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte::Ieee754
{
    constexpr size_t const F16_SIGN_BITS     = 1;
    constexpr size_t const F16_EXPONENT_BITS = 5;
    constexpr size_t const F16_MANTISSA_BITS = 10;

    constexpr uint16_t const F16_SIGN          = 0x8000u;
    constexpr uint16_t const F16_EXPONENT      = 0x7C00u;
    constexpr uint16_t const F16_MANTISSA      = 0x03FFu;
    constexpr uint16_t const F16_INFINITY      = 0x7C00u;
    constexpr uint16_t const F16_QNAN          = 0x7E00u;
    constexpr uint16_t const F16_ZERO          = 0x0u;
    constexpr uint16_t const F16_NEGATIVE_ZERO = 0x8000u;
    constexpr uint16_t const F16_EPSILON       = 0x1400u;
    constexpr uint16_t const F16_MAX           = 0x7BFFu;
    constexpr uint16_t const F16_MIN           = 0x1u;
    constexpr uint16_t const F16_MIN_NORMAL    = 0x0400u;
    constexpr uint32_t const F16_ONE           = 0x3C00u;
    constexpr uint16_t const F16_MASK_ABS      = 0x7FFFu;

    struct Float16Bits final
    {
        union
        {
            struct
            {
#if GRAPHYTE_ENDIAN_LITTLE
                uint16_t Mantissa : F16_MANTISSA_BITS;
                uint16_t Exponent : F16_EXPONENT_BITS;
                uint16_t Sign     : F16_SIGN_BITS;
#else
                uint16_t Sign     : F16_SIGN_BITS;
                uint16_t Exponent : F16_EXPONENT_BITS;
                uint16_t Mantissa : F16_MANTISSA_BITS;
#endif
            } Components;

            uint16_t AsUInt16;

            int16_t AsInt16;
        };
    };
    static_assert(sizeof(Float16Bits) == sizeof(uint16_t));
}

namespace Graphyte::Ieee754
{
    constexpr size_t const F32_SIGN_BITS     = 1;
    constexpr size_t const F32_EXPONENT_BITS = 8;
    constexpr size_t const F32_MANTISSA_BITS = 23;

    constexpr uint32_t const F32_SIGN          = 0x8000'0000u;
    constexpr uint32_t const F32_EXPONENT      = 0x7F80'0000u;
    constexpr uint32_t const F32_MANTISSA      = 0x007F'FFFFu;
    constexpr uint32_t const F32_INFINITY      = 0x7F80'0000u;
    constexpr uint32_t const F32_QNAN          = 0x7FC0'0000u;
    constexpr uint32_t const F32_ZERO          = 0x0u;
    constexpr uint32_t const F32_NEGATIVE_ZERO = 0x8000'0000u;
    constexpr uint32_t const F32_EPSILON       = 0x3400'0000u;
    constexpr uint32_t const F32_MAX           = 0x7F7F'FFFFu;
    constexpr uint32_t const F32_MIN           = 0x1u;
    constexpr uint32_t const F32_MIN_NORMAL    = 0x0080'0000u;
    constexpr uint32_t const F32_ONE           = 0x3F80'0000u;
    constexpr uint32_t const F32_MASK_ABS      = 0x7FFF'FFFFu;

    struct Float32Bits final
    {
        union
        {
            struct
            {
#if GRAPHYTE_ENDIAN_LITTLE
                uint32_t Mantissa : F32_MANTISSA_BITS;
                uint32_t Exponent : F32_EXPONENT_BITS;
                uint32_t Sign     : F32_SIGN_BITS;
#else
                uint32_t Sign     : F32_SIGN_BITS;
                uint32_t Exponent : F32_EXPONENT_BITS;
                uint32_t Mantissa : F32_MANTISSA_BITS;
#endif
            } Components;

            uint32_t AsUInt32;

            int32_t AsInt32;

            float AsFloat32;
        };
    };
    static_assert(sizeof(Float32Bits) == sizeof(float));
}

namespace Graphyte::Ieee754
{
    constexpr size_t const F64_SIGN_BITS     = 1;
    constexpr size_t const F64_EXPONENT_BITS = 11;
    constexpr size_t const F64_MANTISSA_BITS = 52;

    constexpr uint64_t const F64_SIGN          = 0x8000'0000'0000'0000u;
    constexpr uint64_t const F64_EXPONENT      = 0x7FF0'0000'0000'0000u;
    constexpr uint64_t const F64_MANTISSA      = 0x000F'FFFF'FFFF'FFFFu;
    constexpr uint64_t const F64_INFINITY      = 0x7FF0'0000'0000'0000u;
    constexpr uint64_t const F64_QNAN          = 0x7FF8'0000'0000'0000u;
    constexpr uint64_t const F64_ZERO          = 0x0u;
    constexpr uint64_t const F64_NEGATIVE_ZERO = 0x8000'0000'0000'0000u;
    constexpr uint64_t const F64_EPSILON       = 0x3cb0'0000'0000'0000u;
    constexpr uint64_t const F64_MAX           = 0x7FEF'FFFF'FFFF'FFFFu;
    constexpr uint64_t const F64_MIN           = 0x1u;
    constexpr uint64_t const F64_MIN_NORMAL    = 0x0010'0000'0000'0000u;
    constexpr uint64_t const F64_ONE           = 0x3FF0'0000'0000'0000u;
    constexpr uint64_t const F64_MASK_ABS      = 0x7FFF'FFFF'FFFF'FFFFu;

    struct Float64Bits final
    {
        union
        {
            struct
            {
#if GRAPHYTE_ENDIAN_LITTLE
                uint64_t Mantissa : F64_MANTISSA_BITS;
                uint64_t Exponent : F64_EXPONENT_BITS;
                uint64_t Sign     : F64_SIGN_BITS;
#else
                uint64_t Sign     : F64_SIGN_BITS;
                uint64_t Exponent : F64_EXPONENT_BITS;
                uint64_t Mantissa : F64_MANTISSA_BITS;
#endif
            } Components;

            uint64_t AsUInt64;

            int64_t AsInt64;

            double AsFloat64;
        };
    };
    static_assert(sizeof(Float64Bits) == sizeof(double));
}
