#pragma once
#include <Graphyte/Base.module.hxx>

#if false
#include <Graphyte/Maths/Simd.hxx>
#include <Graphyte/Maths/Types.hxx>

namespace Graphyte
{
    mathinline float mathcall FromHalf(Maths::half value) noexcept
    {
#if GRAPHYTE_HW_F16C
        __m128i v1 = _mm_cvtsi32_si128(static_cast<int32_t>(value.Value));
        __m128 v2 = _mm_cvtph_ps(v1);
        return _mm_cvtss_f32(v2);
#else
        uint32_t mantissa = static_cast<uint32_t>(value.Value & UINT32_C(0x03ff));
        uint32_t exponent = static_cast<uint32_t>(value.Value & UINT32_C(0x7c00));

        if (exponent == UINT32_C(0x7c00))
        {
            exponent = UINT32_C(0x8f);
        }
        else if (exponent != 0)
        {
            exponent = static_cast<uint32_t>((value.Value >> 10) & 0x1f);
        }
        else if (mantissa != 0)
        {
            exponent = 1;

            do
            {
                --exponent;
                mantissa <<= 1;
            } while ((mantissa & UINT32_C(0x0400)) == 0);

            mantissa &= UINT32_C(0x03ff);
        }
        else
        {
            exponent = static_cast<uint32_t>(-112);
        }

        uint32_t result = ((value.Value & UINT32_C(0x8000)) << 16)
            | ((exponent + 112) << 23)
            | (mantissa << 13);

        Impl::Ieee754::FloatBits pun;
        pun.AsUInt32 = result;
        return pun.AsFloat;
#endif
    }

    mathinline Maths::half mathcall ToHalf(float value) noexcept
    {
#if GRAPHYTE_HW_F16C
        __m128 v1 = _mm_set_ss(value);
        __m128i v2 = _mm_cvtps_ph(v1, 0);
        return { static_cast<uint16_t>(_mm_cvtsi128_si32(v2)) };
#else
        Impl::Ieee754::FloatBits pun;
        pun.AsFloat = value;

        uint32_t uvalue = pun.AsUInt32;
        uint32_t sign = (uvalue & UINT32_C(0x80000000)) >> UINT32_C(16);
        uvalue &= UINT32_C(0x7fffffff);

        uint32_t result;

        if (uvalue > UINT32_C(0x477fe000))
        {
            if (((uvalue & UINT32_C(0x7f800000)) == UINT32_C(0x7f800000)) && ((uvalue & UINT32_C(0x007fffff)) != 0))
            {
                result = UINT32_C(0x7fff);
            }
            else
            {
                result = UINT32_C(0x7c00);
            }
        }
        else
        {
            if (uvalue < UINT32_C(0x38800000))
            {
                uint32_t shift = UINT32_C(113) - (uvalue >> UINT32_C(23));
                uvalue = (UINT32_C(0x00800000) | (uvalue & UINT32_C(0x007fffff))) >> shift;
            }
            else
            {
                uvalue += UINT32_C(0xc8000000);
            }

            result = ((uvalue + UINT32_C(0x0fff) + ((uvalue >> UINT32_C(13)) & UINT32_C(1))) >> UINT32_C(13)) & UINT32_C(0x7fff);
        }

        return Maths::half{ static_cast<uint16_t>(result | sign) };
#endif
    }
}
#endif
