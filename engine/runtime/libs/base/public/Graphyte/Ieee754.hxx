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
        static constexpr uint16_t const QNaN          = 0x7E00u;
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

        static constexpr Half FromBits(uint16_t bits) noexcept
        {
            return Half{ bits };
        }

        static constexpr uint16_t ToBits(Half value) noexcept
        {
            return value.Value;
        }

        static constexpr bool BitIsNan(uint16_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                && ((bits & Mantissa) != 0);
        }

        static constexpr bool BitIsInf(uint16_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        static constexpr bool IsInf(Half value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        static constexpr bool IsNan(Half value) noexcept
        {
            return BitIsInf(ToBits(value));
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
        static constexpr uint32_t const QNaN          = 0x7FC0'0000u;
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

        static constexpr float FromBits(uint32_t bits) noexcept
        {
            return Layout{ .AsUInt32 = bits }.AsFloat32;
        }

        static constexpr uint32_t ToBits(float value) noexcept
        {
            return Layout{ .AsFloat32 = value }.AsUInt32;
        }

        static constexpr bool BitIsNan(uint32_t bits) noexcept
        {
#if false
            return ((bits & Exponent) == Exponent)
                && ((bits & Mantissa) != 0);
#else
            uint32_t const umask = bits & 0x7fff'ffffU;
            uint32_t const unan = umask - 0x7f80'0001U;

            return (unan < 0x007f'ffffU);
#endif
        }

        static constexpr bool BitIsInf(uint32_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        static constexpr bool IsInf(float value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        static constexpr bool IsNan(float value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        static constexpr float Range12FromHighBits(uint32_t value) noexcept
        {
            uint32_t const u = One | (value >> (ExponentBits + 1));
            float const f = FromBits(u);
            return f;
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
        static constexpr uint64_t const QNaN          = 0x7FF8'0000'0000'0000u;
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

        static constexpr double FromBits(uint64_t bits) noexcept
        {
            return Layout{ .AsUInt64 = bits }.AsFloat64;
        }

        static constexpr uint64_t ToBits(double value) noexcept
        {
            return Layout{ .AsFloat64 = value }.AsUInt64;
        }

        static constexpr bool BitIsNan(uint64_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                && ((bits & Mantissa) != 0);
        }

        static constexpr bool BitIsInf(uint64_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        static constexpr bool IsInf(double value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        static constexpr bool IsNan(double value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        static constexpr double Range12FromHighBits(uint64_t value) noexcept
        {
            uint64_t const u = One | (value >> (ExponentBits + 1));
            double const f = FromBits(u);
            return f;
        }
    };
}
