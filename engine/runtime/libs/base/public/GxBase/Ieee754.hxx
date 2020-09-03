#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Bitwise.hxx>

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
        using BitsType = uint16_t;

        static constexpr size_t const SignBits     = 1;
        static constexpr size_t const ExponentBits = 5;
        static constexpr size_t const MantissaBits = 10;

        static constexpr uint16_t const Sign         = 0x8000u;
        static constexpr uint16_t const Exponent     = 0x7C00u;
        static constexpr uint16_t const Mantissa     = 0x03FFu;
        static constexpr uint16_t const Infinity     = 0x7C00u;
        static constexpr uint16_t const QNaN         = 0x7E00u;
        static constexpr uint16_t const Zero         = 0x0000u;
        static constexpr uint16_t const NegativeZero = 0x8000u;
        static constexpr uint16_t const Epsilon      = 0x1400u;
        static constexpr uint16_t const Max          = 0x7BFFu;
        static constexpr uint16_t const Min          = 0x0001u;
        static constexpr uint16_t const MinNormal    = 0x0400u;
        static constexpr uint32_t const One          = 0x3C00u;
        static constexpr uint16_t const MaskAbs      = 0x7FFFu;

        struct Layout final
        {
            union
            {
                struct
                {
#if GRAPHYTE_ENDIAN_LITTLE
                    uint16_t Mantissa : MantissaBits;
                    uint16_t Exponent : ExponentBits;
                    uint16_t Sign : SignBits;
#else
                    uint16_t Sign : SignBits;
                    uint16_t Exponent : ExponentBits;
                    uint16_t Mantissa : MantissaBits;
#endif
                } Components;

                uint16_t AsUInt16;
                int16_t AsInt16;
            };
        };
        static_assert(sizeof(Layout) == sizeof(uint16_t));

        [[nodiscard]] static constexpr Half FromBits(uint16_t bits) noexcept
        {
            return Half{ bits };
        }

        [[nodiscard]] static constexpr uint16_t ToBits(Half value) noexcept
        {
            return value.Value;
        }

        [[nodiscard]] static constexpr bool BitIsNan(uint16_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                   && ((bits & Mantissa) != 0);
        }

        [[nodiscard]] static constexpr bool BitIsInf(uint16_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        [[nodiscard]] static constexpr bool IsInf(Half value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        [[nodiscard]] static constexpr bool IsNan(Half value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        [[nodiscard]] static constexpr Half Range12FromHighBits(uint16_t value) noexcept
        {
            uint16_t const u = One | (value >> (ExponentBits + SignBits));
            Half const f     = FromBits(u);
            return f;
        }

        [[nodiscard]] static constexpr Half Range12FromLowBits(uint16_t value) noexcept
        {
            uint16_t const u = One | (value & Mantissa);
            Half const f     = FromBits(u);
            return f;
        }
    };


    //
    // Float-type traits.
    //

    template <>
    struct FloatTraits<float> final
    {
        using BitsType = uint32_t;

        static constexpr size_t const SignBits     = 1;
        static constexpr size_t const ExponentBits = 8;
        static constexpr size_t const MantissaBits = 23;

        static constexpr uint32_t const Sign         = 0x8000'0000u;
        static constexpr uint32_t const Exponent     = 0x7F80'0000u;
        static constexpr uint32_t const Mantissa     = 0x007F'FFFFu;
        static constexpr uint32_t const Infinity     = 0x7F80'0000u;
        static constexpr uint32_t const QNaN         = 0x7FC0'0000u;
        static constexpr uint32_t const Zero         = 0x0000'0000u;
        static constexpr uint32_t const NegativeZero = 0x8000'0000u;
        static constexpr uint32_t const Epsilon      = 0x3400'0000u;
        static constexpr uint32_t const Max          = 0x7F7F'FFFFu;
        static constexpr uint32_t const Min          = 0x0000'0001u;
        static constexpr uint32_t const MinNormal    = 0x0080'0000u;
        static constexpr uint32_t const One          = 0x3F80'0000u;
        static constexpr uint32_t const MaskAbs      = 0x7FFF'FFFFu;

        struct Layout final
        {
            union
            {
                struct
                {
#if GRAPHYTE_ENDIAN_LITTLE
                    uint32_t Mantissa : MantissaBits;
                    uint32_t Exponent : ExponentBits;
                    uint32_t Sign : SignBits;
#else
                    uint32_t Sign : SignBits;
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

        [[nodiscard]] static constexpr float FromBits(uint32_t bits) noexcept
        {
            return BitCast<float, uint32_t>(bits);
        }

        [[nodiscard]] static constexpr uint32_t ToBits(float value) noexcept
        {
            return BitCast<uint32_t, float>(value);
        }

        [[nodiscard]] static constexpr bool BitIsNan(uint32_t bits) noexcept
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

        [[nodiscard]] static constexpr bool BitIsInf(uint32_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        [[nodiscard]] static constexpr bool IsInf(float value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        [[nodiscard]] static constexpr bool IsNan(float value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        [[nodiscard]] static constexpr float Range12FromHighBits(uint32_t value) noexcept
        {
            uint32_t const u = One | (value >> (ExponentBits + SignBits));
            float const f    = FromBits(u);
            return f;
        }

        [[nodiscard]] static constexpr float Range12FromLowBits(uint32_t value) noexcept
        {
            uint32_t const u = One | (value & Mantissa);
            float const f    = FromBits(u);
            return f;
        }
    };


    //
    // Double-type traits.
    //

    template <>
    struct FloatTraits<double> final
    {
        using BitsType = uint64_t;

        static constexpr size_t const SignBits     = 1;
        static constexpr size_t const ExponentBits = 11;
        static constexpr size_t const MantissaBits = 52;

        static constexpr uint64_t const Sign         = 0x8000'0000'0000'0000u;
        static constexpr uint64_t const Exponent     = 0x7FF0'0000'0000'0000u;
        static constexpr uint64_t const Mantissa     = 0x000F'FFFF'FFFF'FFFFu;
        static constexpr uint64_t const Infinity     = 0x7FF0'0000'0000'0000u;
        static constexpr uint64_t const QNaN         = 0x7FF8'0000'0000'0000u;
        static constexpr uint64_t const Zero         = 0x0u;
        static constexpr uint64_t const NegativeZero = 0x8000'0000'0000'0000u;
        static constexpr uint64_t const Epsilon      = 0x3cb0'0000'0000'0000u;
        static constexpr uint64_t const Max          = 0x7FEF'FFFF'FFFF'FFFFu;
        static constexpr uint64_t const Min          = 0x1u;
        static constexpr uint64_t const MinNormal    = 0x0010'0000'0000'0000u;
        static constexpr uint64_t const One          = 0x3FF0'0000'0000'0000u;
        static constexpr uint64_t const MaskAbs      = 0x7FFF'FFFF'FFFF'FFFFu;

        struct Layout final
        {
            union
            {
                struct
                {
#if GRAPHYTE_ENDIAN_LITTLE
                    uint64_t Mantissa : MantissaBits;
                    uint64_t Exponent : ExponentBits;
                    uint64_t Sign : SignBits;
#else
                    uint64_t Sign : SignBits;
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

        [[nodiscard]] static constexpr double FromBits(uint64_t bits) noexcept
        {
            return BitCast<double, uint64_t>(bits);
        }

        [[nodiscard]] static constexpr uint64_t ToBits(double value) noexcept
        {
            return BitCast<uint64_t, double>(value);
        }

        [[nodiscard]] static constexpr bool BitIsNan(uint64_t bits) noexcept
        {
            return ((bits & Exponent) == Exponent)
                   && ((bits & Mantissa) != 0);
        }

        [[nodiscard]] static constexpr bool BitIsInf(uint64_t bits) noexcept
        {
            return ((bits & ~Sign) == Exponent);
        }

        [[nodiscard]] static constexpr bool IsInf(double value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        [[nodiscard]] static constexpr bool IsNan(double value) noexcept
        {
            return BitIsInf(ToBits(value));
        }

        [[nodiscard]] static constexpr double Range12FromHighBits(uint64_t value) noexcept
        {
            uint64_t const u = One | (value >> (ExponentBits + SignBits));
            double const f   = FromBits(u);
            return f;
        }

        [[nodiscard]] static constexpr double Range12FromLowBits(uint64_t value) noexcept
        {
            uint64_t const u = One | (value & Mantissa);
            double const f   = FromBits(u);
            return f;
        }
    };
}

namespace Graphyte
{
    [[nodiscard]] constexpr float FromHalfBitwise(Half v) noexcept
    {
        uint32_t const value = v.Value;

        uint32_t mantissa = static_cast<uint32_t>(value & 0x03FFu);
        uint32_t exponent = (value & FloatTraits<Half>::Exponent);

        if (exponent == FloatTraits<Half>::Infinity)
        {
            // Infinity / NaN
            exponent = 0x8Fu;
        }
        else if (exponent != 0)
        {
            // normalized
            exponent = static_cast<uint32_t>((static_cast<int>(value) >> FloatTraits<Half>::MantissaBits) & 0x1F);
        }
        else if (mantissa != 0)
        {
            // denormalized -> normalized

            exponent = 1;

            do
            {
                --exponent;
                mantissa <<= 1;
            } while ((mantissa & FloatTraits<Half>::MinNormal) == 0);

            mantissa &= FloatTraits<Half>::Mantissa;
        }
        else
        {
            exponent = static_cast<uint32_t>(-112);
        }

        uint32_t const f32_sign     = (value & FloatTraits<Half>::Sign) << 16;
        uint32_t const f32_exponent = ((exponent + 112) << 23);
        uint32_t const f32_mantissa = (mantissa << 13);

        uint32_t const result
            = f32_sign
              | f32_exponent
              | f32_mantissa;

        return BitCast<float>(result);
    }

    [[nodiscard]] constexpr float FromHalf(Half v) noexcept
    {
        if (std::is_constant_evaluated())
        {
            return FromHalfBitwise(v);
        }
        else
        {
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_F16C
            __m128i const vh = _mm_cvtsi32_si128(static_cast<int>(v.Value));
            __m128 const vf  = _mm_cvtph_ps(vh);
            return _mm_cvtss_f32(vf);
#elif !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_NEON
            uint16x4_t vh = vdup_n_u16(v.Value);
            float32x4_t vf = vcvt_f32_f16(vreinterpret_f16_u16(vh));
            return vgetq_lane_f32(vf, 0);
#else
            return FromHalfBitwise(v);
#endif
        }
    }

    [[nodiscard]] constexpr Half ToHalfBitwise(float value) noexcept
    {
        uint32_t result        = 0;
        uint32_t const uvalue1 = BitCast<uint32_t>(value);
        uint32_t sign          = (uvalue1 & FloatTraits<float>::Sign) >> 16u;
        uint32_t uvalue2       = (uvalue1 & ~FloatTraits<float>::Sign);

        if (uvalue2 > 0x477FE000u) // 65504.0f
        {
            if (((uvalue2 & FloatTraits<float>::Exponent) == FloatTraits<float>::Exponent) && ((uvalue2 & FloatTraits<float>::Mantissa) != 0))
            {
                result = FloatTraits<Half>::QNaN;
            }
            else
            {
                result = FloatTraits<Half>::Infinity;
            }
        }
        else if (uvalue2 == 0)
        {
            result = 0;
        }
        else
        {
            if (uvalue2 < 0x38800000u)
            {
                // convert to denormalized
                uint32_t const shift = 113u - (uvalue2 >> 23u);
                uvalue2              = (FloatTraits<float>::MinNormal | ((uvalue2 & FloatTraits<float>::Mantissa) >> shift));
            }
            else
            {
                uvalue2 += 0xC8000000u;
            }

            result = ((uvalue2 + 0x0FFFu + ((uvalue2 >> 13u) & 1u)) >> 13u) & FloatTraits<Half>::MaskAbs;
        }

        return Graphyte::Half{ .Value = static_cast<uint16_t>(result | sign) };
    }

    [[nodiscard]] __forceinline Half ToHalf(float value) noexcept
    {
        if (std::is_constant_evaluated())
        {
            return ToHalfBitwise(value);
        }
        else
        {
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_F16C
            __m128 const vf  = _mm_set_ss(value);
            __m128i const vh = _mm_cvtps_ph(vf, _MM_FROUND_TO_NEAREST_INT);

            return Graphyte::Half{
                .Value = static_cast<uint16_t>(_mm_extract_epi16(vh, 0))
            };
#elif !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_NEON
            float32x4_t const vf = vdupq_n_f32(value);
            float16x4_t const vh = vcvt_f16_f32(vf);

            return Graphyte::Half{
                .Value = static_cast<uint16_t>(vget_lane_u16(vreinterpret_u16_f16(vh), 0))
            };
#else
            return ToHalfBitwise(value);
#endif
        }
    }
}
