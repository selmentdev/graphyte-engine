#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Ieee754.hxx>

namespace Graphyte
{
    __forceinline float FromHalf(Half v) noexcept
    {
#if GRAPHYTE_HW_F16C
        __m128i const vh = _mm_cvtsi32_si128(static_cast<int>(v.Value));
        __m128 const vf = _mm_cvtph_ps(vh);
        return _mm_cvtss_f32(vf);
#elif GRAPHYTE_HW_NEON
        uint16x4_t vh = vdup_n_u16(v.Value);
        float32x4_t vf = vcvt_f32_f16(vreinterpret_f16_u16(vh));
        return vgetq_lane_f32(vf, 0);
#else
        uint32_t const value = v.Value;

        uint32_t mantissa = static_cast<uint32_t>(value & 0x03FFu);
        uint32_t exponent = (value & Ieee754::F16_EXPONENT);

        if (exponent == Ieee754::F16_INFINITY)
        {
            // Infinity / NaN
            exponent = 0x8Fu;
        }
        else if (exponent != 0)
        {
            // normalized
            exponent = static_cast<uint32_t>((static_cast<int>(value) >> Ieee754::F16_MANTISSA_BITS) & 0x1F);
        }
        else if (mantissa != 0)
        {
            // denormalized -> normalized

            exponent = 1;

            do
            {
                --exponent;
                mantissa <<= 1;
            } while ((mantissa & Ieee754::F16_MIN_NORMAL) == 0);

            mantissa &= Ieee754::F16_MANTISSA;
    }
        else
        {
            exponent = static_cast<uint32_t>(-112);
        }

        uint32_t const f32_sign = (value & Ieee754::F16_SIGN) << 16;
        uint32_t const f32_exponent = ((exponent + 112) << 23);
        uint32_t const f32_mantissa = (mantissa << 13);

        uint32_t const result
            = f32_sign
            | f32_exponent
            | f32_mantissa;

        return BitCast<float>(result);
#endif
    }

    __forceinline Half ToHalf(float value) noexcept
    {
#if GRAPHYTE_HW_F16C
        __m128 const vf = _mm_set_ss(value);
        __m128i const vh = _mm_cvtps_ph(vf, 0);

        return Graphyte::Half{
            .Value = static_cast<uint16_t>(_mm_cvtsi128_si32(vh))
        };
#elif GRAPHYTE_HW_NEON
        float32x4_t const vf = vdupq_n_f32(value);
        float16x4_t const vh = vcvt_f16_f32(vf);

        return Graphyte::Half{
            .Value = static_cast<uint16_t>(vget_lane_u16(vreinterpret_u16_f16(vh), 0))
        };
#else
        uint32_t result;
        uint32_t const uvalue1 = BitCast<uint32_t>(value);
        uint32_t sign = (uvalue1 & Ieee754::F32_SIGN) >> 16u;
        uint32_t uvalue2 = (uvalue1 & ~Ieee754::F32_SIGN);

        if (uvalue2 > 0x477FE000u) // 65504.0f
        {
            if (((uvalue2 & Ieee754::F32_EXPONENT) == Ieee754::F32_EXPONENT) && ((uvalue2 & Ieee754::F32_MANTISSA) != 0))
            {
                result = Ieee754::F16_QNAN;
            }
            else
            {
                result = Ieee754::F16_INFINITY;
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
                uvalue2 = (Ieee754::F32_MIN_NORMAL | ((uvalue2 & Ieee754::F32_MANTISSA) >> shift));
            }
            else
            {
                uvalue2 += 0xC8000000u;
            }

            result = ((uvalue2 + 0x0FFFu + ((uvalue2 >> 13u) & 1u)) >> 13u) & ~Ieee754::F16_SIGN;
        }

        return Graphyte::Half{ .Value = static_cast<uint16_t>(result | sign) };
#endif
    }
}
