#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte
{
    struct Half final
    {
        uint16_t Value;
    };

    template <typename T>
    struct FloatTraits;


    //
    // Half-type traits.
    //

    template <>
    struct FloatTraits<Half> final
    {
        static constexpr size_t const SignBits = 1;
        static constexpr size_t const ExponentBits = 5;
        static constexpr size_t const MantissaBits = 10;

        static constexpr uint16_t const Sign          = 0x8000u;
        static constexpr uint16_t const Exponent      = 0x7C00u;
        static constexpr uint16_t const Mantissa      = 0x03FFu;
        static constexpr uint16_t const Infinity      = 0x7C00u;
        static constexpr uint16_t const QNan          = 0x7E00u;
        static constexpr uint16_t const Zero          = 0x0000u;
        static constexpr uint16_t const NegativeZero  = 0x8000u;
        static constexpr uint16_t const Epsilon       = 0x1400u;
        static constexpr uint16_t const Max           = 0x7BFFu;
        static constexpr uint16_t const Min           = 0x0001u;
        static constexpr uint16_t const MinNormal     = 0x0400u;
        static constexpr uint32_t const One           = 0x3C00u;
        static constexpr uint16_t const MaskAbs       = 0x7FFFu;

        struct Layout final
        {
            union
            {
                struct
                {
    #if GRAPHYTE_ENDIAN_LITTLE
                    uint16_t Mantissa : MantissaBits;
                    uint16_t Exponent : ExponentBits;
                    uint16_t Sign     : SignBits;
    #else
                    uint16_t Sign     : SignBits;
                    uint16_t Exponent : ExponentBits;
                    uint16_t Mantissa : MantissaBits;
    #endif
                } Components;

                uint16_t AsUInt16;
                int16_t AsInt16;
            };
        };
        static_assert(sizeof(Layout) == sizeof(uint16_t));

        static constexpr bool BitIsNan(uint16_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                && ((bits & Mantissa) != 0);
        }

        static constexpr bool BitIsInf(uint16_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        static constexpr Half FromBits(uint16_t bits) noexcept
        {
            return Half{ bits };
        }

        static constexpr uint16_t ToBits(Half value) noexcept
        {
            return value.Value;
        }
    };


    //
    // Float-type traits.
    //

    template <>
    struct FloatTraits<float> final
    {
        static constexpr size_t const SignBits     = 1;
        static constexpr size_t const ExponentBits = 8;
        static constexpr size_t const MantissaBits = 23;

        static constexpr uint32_t const Sign          = 0x8000'0000u;
        static constexpr uint32_t const Exponent      = 0x7F80'0000u;
        static constexpr uint32_t const Mantissa      = 0x007F'FFFFu;
        static constexpr uint32_t const Infinity      = 0x7F80'0000u;
        static constexpr uint32_t const QNan          = 0x7FC0'0000u;
        static constexpr uint32_t const Zero          = 0x0000'0000u;
        static constexpr uint32_t const NegativeZero  = 0x8000'0000u;
        static constexpr uint32_t const Epsilon       = 0x3400'0000u;
        static constexpr uint32_t const Max           = 0x7F7F'FFFFu;
        static constexpr uint32_t const Min           = 0x0000'0001u;
        static constexpr uint32_t const MinNormal     = 0x0080'0000u;
        static constexpr uint32_t const One           = 0x3F80'0000u;
        static constexpr uint32_t const MaskAbs       = 0x7FFF'FFFFu;

        struct Layout final
        {
            union
            {
                struct
                {
    #if GRAPHYTE_ENDIAN_LITTLE
                    uint32_t Mantissa : MantissaBits;
                    uint32_t Exponent : ExponentBits;
                    uint32_t Sign     : SignBits;
    #else
                    uint32_t Sign     : SignBits;
                    uint32_t Exponent : ExponentBits;
                    uint32_t Mantissa : MantissaBits;
    #endif
                } Components;

                uint32_t AsUInt32;
                int32_t AsInt32;
                float AsFloat32;
            };
        };
        static_assert(sizeof(Layout) == sizeof(float));

        static constexpr bool BitIsNan(uint32_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                && ((bits & Mantissa) != 0);
        }

        static constexpr bool BitIsInf(uint32_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        static constexpr float FromBits(uint32_t bits) noexcept
        {
            return Layout{ .AsUInt32 = bits }.AsFloat32;
        }

        static constexpr uint32_t ToBits(float value) noexcept
        {
            return Layout{ .AsFloat32 = value }.AsUInt32;
        }
    };


    //
    // Double-type traits.
    //

    template <>
    struct FloatTraits<double> final
    {
        static constexpr size_t const SignBits     = 1;
        static constexpr size_t const ExponentBits = 11;
        static constexpr size_t const MantissaBits = 52;

        static constexpr uint64_t const Sign          = 0x8000'0000'0000'0000u;
        static constexpr uint64_t const Exponent      = 0x7FF0'0000'0000'0000u;
        static constexpr uint64_t const Mantissa      = 0x000F'FFFF'FFFF'FFFFu;
        static constexpr uint64_t const Infinity      = 0x7FF0'0000'0000'0000u;
        static constexpr uint64_t const QNan          = 0x7FF8'0000'0000'0000u;
        static constexpr uint64_t const Zero          = 0x0u;
        static constexpr uint64_t const NegativeZero  = 0x8000'0000'0000'0000u;
        static constexpr uint64_t const Epsilon       = 0x3cb0'0000'0000'0000u;
        static constexpr uint64_t const Max           = 0x7FEF'FFFF'FFFF'FFFFu;
        static constexpr uint64_t const Min           = 0x1u;
        static constexpr uint64_t const MinNormal     = 0x0010'0000'0000'0000u;
        static constexpr uint64_t const One           = 0x3FF0'0000'0000'0000u;
        static constexpr uint64_t const MaskAbs       = 0x7FFF'FFFF'FFFF'FFFFu;

        struct Layout final
        {
            union
            {
                struct
                {
    #if GRAPHYTE_ENDIAN_LITTLE
                    uint64_t Mantissa : MantissaBits;
                    uint64_t Exponent : ExponentBits;
                    uint64_t Sign     : SignBits;
    #else
                    uint64_t Sign     : SignBits;
                    uint64_t Exponent : ExponentBits;
                    uint64_t Mantissa : MantissaBits;
    #endif
                } Components;

                uint64_t AsUInt64;

                int64_t AsInt64;

                double AsFloat64;
            };
        };
        static_assert(sizeof(Layout) == sizeof(double));

        static constexpr bool BitIsNan(uint64_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                && ((bits & Mantissa) != 0);
        }

        static constexpr bool BitIsInf(uint64_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        static constexpr double FromBits(uint64_t bits) noexcept
        {
            return Layout{ .AsUInt64 = bits }.AsFloat64;
        }

        static constexpr uint64_t ToBits(double value) noexcept
        {
            return Layout{ .AsFloat64 = value }.AsUInt64;
        }
    };
}

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

    constexpr bool BitIsNan(uint16_t bits) noexcept
    {
        return ((bits & F16_EXPONENT) == F16_EXPONENT)
            && ((bits & F16_MANTISSA) != 0);
    }

    constexpr bool BitIsInf(uint16_t bits) noexcept
    {
        return ((bits & ~F16_SIGN) == F16_EXPONENT);
    }
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


    constexpr bool BitIsNan(uint32_t bits) noexcept
    {
        return ((bits & F32_EXPONENT) == F32_EXPONENT)
            && ((bits & F32_MANTISSA) != 0);
    }

    constexpr bool BitIsInf(uint32_t bits) noexcept
    {
        return ((bits & ~F32_SIGN) == F32_EXPONENT);
    }
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

    constexpr bool BitIsNan(uint64_t bits) noexcept
    {
        return ((bits & F64_EXPONENT) == F64_EXPONENT)
            && ((bits & F64_MANTISSA) != 0);
    }

    constexpr bool BitIsInf(uint64_t bits) noexcept
    {
        return ((bits & ~F64_SIGN) == F64_EXPONENT);
    }
}
