#pragma once

// =================================================================================================
//
// This module implements AVX specific helper functions.
//

namespace Graphyte::Maths::Impl
{
    mathinline __m128 mathcall avx_fmadd_f32x4(
        __m128 a,
        __m128 b,
        __m128 c
    ) noexcept
    {
#if GRAPHYTE_HW_FMA4
        return _mm_macc_ps(a, b, c);
#elif GRAPHYTE_HW_AVX2
        return _mm_fmadd_ps(a, b, c);
#else
        // (a * b)
        __m128 const ab = _mm_mul_ps(a, b);
        // (a * b) + c
        __m128 const result = _mm_add_ps(ab, c);
        return result;
#endif
    }

    mathinline __m128 mathcall avx_fmsub_f32x4(
        __m128 a,
        __m128 b,
        __m128 c
    ) noexcept
    {
#if GRAPHYTE_HW_FMA4
        return _mm_msub_ps(a, b, c);
#elif GRAPHYTE_HW_AVX2
        return _mm_fmsub_ps(a, b, c);
#else
        // (a * b)
        __m128 const ab = _mm_mul_ps(a, b);
        // (a * b) - c
        __m128 const result = _mm_sub_ps(ab, c);
        return result;
#endif
    }

    mathinline __m128 mathcall avx_fnmadd_f32x4(
        __m128 a,
        __m128 b,
        __m128 c
    ) noexcept
    {
#if GRAPHYTE_HW_FMA4
        return _mm_nmacc_ps(a, b, c);
#elif GRAPHYTE_HW_AVX2
        return _mm_fnmadd_ps(a, b, c);
#else
        // (a * b)
        __m128 const ab = _mm_mul_ps(a, b);
        // -(a * b) + c
        __m128 const result = _mm_sub_ps(c, ab);
        return result;
#endif
    }

    mathinline __m128 mathcall avx_fnmsub_f32x4(
        __m128 a,
        __m128 b,
        __m128 c
    ) noexcept
    {
#if GRAPHYTE_HW_FMA4
        return _mm_nmsub_ps(a, b, c);
#elif GRAPHYTE_HW_AVX2
        return _mm_fnmsub_ps(a, b, c);
#else
        // (a * b)
        __m128 const ab = _mm_mul_ps(a, b);
        __m128 const zero = _mm_setzero_ps();
        // -(a * b)
        __m128 const neg_ab = _mm_sub_ps(zero, ab);
        // -(a * b) - c
        __m128 const result = _mm_sub_ps(neg_ab, c);
        return result;
#endif
    }
}

namespace Graphyte::Maths::Impl
{
    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline __m128 mathcall avx_permute(__m128 a, __m128 b) noexcept
    {
        static_assert((X < 8) and (Y < 8) and (Z < 8) and (W < 8));

        constexpr bool x_up = (X >= 4);
        constexpr bool y_up = (Y >= 4);
        constexpr bool z_up = (Z >= 4);
        constexpr bool w_up = (W >= 4);

        constexpr int shuffle = _MM_SHUFFLE(W & 3, Z & 3, Y & 3, X & 3);

        if constexpr (X == 0 and Y == 1 and Z == 2 and W == 3)
        {
            return a;
        }
        else if constexpr (X == 4 and Y == 5 and Z == 6 and W == 7)
        {
            return b;
        }
        else if constexpr (X == 4 and Y == 1 and Z == 2 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x1);
        }
        else if constexpr (X == 0 and Y == 5 and Z == 2 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x2);
        }
        else if constexpr (X == 4 and Y == 5 and Z == 2 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x3);
        }
        else if constexpr (X == 0 and Y == 1 and Z == 6 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x4);
        }
        else if constexpr (X == 4 and Y == 1 and Z == 6 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x5);
        }
        else if constexpr (X == 0 and Y == 5 and Z == 6 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x6);
        }
        else if constexpr (X == 4 and Y == 5 and Z == 6 and W == 3)
        {
            return _mm_blend_ps(a, b, 0x7);
        }
        else if constexpr (X == 0 and Y == 1 and Z == 2 and W == 7)
        {
            return _mm_blend_ps(a, b, 0x8);
        }
        else if constexpr (X == 4 and Y == 1 and Z == 2 and W == 7)
        {
            return _mm_blend_ps(a, b, 0x9);
        }
        else if constexpr (X == 0 and Y == 5 and Z == 2 and W == 7)
        {
            return _mm_blend_ps(a, b, 0xA);
        }
        else if constexpr (X == 4 and Y == 5 and Z == 2 and W == 7)
        {
            return _mm_blend_ps(a, b, 0xB);
        }
        else if constexpr (X == 0 and Y == 1 and Z == 6 and W == 7)
        {
            return _mm_blend_ps(a, b, 0xC);
        }
        else if constexpr (X == 4 and Y == 1 and Z == 6 and W == 7)
        {
            return _mm_blend_ps(a, b, 0xD);
        }
        else if constexpr (X == 0 and Y == 5 and Z == 6 and W == 7)
        {
            return _mm_blend_ps(a, b, 0xE);
        }
        else if constexpr (X == 0 and Y == 1 and Z == 0 and W == 1)
        {
            return _mm_movelh_ps(a, a);
        }
        else if constexpr (X == 4 and Y == 5 and Z == 4 and W == 5)
        {
            return _mm_movelh_ps(b, b);
        }
        else if constexpr (X == 2 and Y == 3 and Z == 2 and W == 3)
        {
            return _mm_movehl_ps(a, a);
        }
        else if constexpr (X == 6 and Y == 7 and Z == 6 and W == 7)
        {
            return _mm_movehl_ps(b, b);
        }
        else if constexpr (X == 0 and Y == 0 and Z == 1 and W == 1)
        {
            return _mm_unpacklo_ps(a, a);
        }
        else if constexpr (X == 4 and Y == 4 and Z == 5 and W == 5)
        {
            return _mm_unpacklo_ps(b, b);
        }
        else if constexpr (X == 2 and Y == 2 and Z == 3 and W == 3)
        {
            return _mm_unpackhi_ps(a, a);
        }
        else if constexpr (X == 6 and Y == 6 and Z == 7 and W == 7)
        {
            return _mm_unpackhi_ps(b, b);
        }
        else if constexpr (X == 0 and Y == 0 and Z == 2 and W == 2)
        {
            return _mm_moveldup_ps(a);
        }
        else if constexpr (X == 1 and Y == 1 and Z == 3 and W == 3)
        {
            return _mm_movehdup_ps(a);
        }
        else if constexpr (X == 4 and Y == 4 and Z == 6 and W == 6)
        {
            return _mm_moveldup_ps(b);
        }
        else if constexpr (X == 5 and Y == 5 and Z == 7 and W == 7)
        {
            return _mm_movehdup_ps(b);
        }
#if GRAPHYTE_HW_AVX2
        else if constexpr (X == 0 and Y == 0 and Z == 0 and W == 0)
        {
            return _mm_broadcastss_ps(a, shuffle);
        }
        else if constexpr (X == 4 and Y == 4 and Z == 4 and W == 4)
        {
            return _mm_broadcastss_ps(b, shuffle);
        }
#endif
        else if constexpr (!x_up and !y_up and !z_up and !w_up)
        {
            return _mm_permute_ps(a, shuffle);
        }
        else if constexpr (x_up and y_up and z_up and w_up)
        {
            return _mm_permute_ps(b, shuffle);
        }
        else if constexpr (!x_up and !y_up and z_up and w_up)
        {
            return _mm_shuffle_ps(a, b, shuffle);
        }
        else if constexpr (x_up and y_up and !z_up and !w_up)
        {
            return _mm_shuffle_ps(b, a, shuffle);
        }
        else
        {
            //
            // General case.
            //

            alignas(__m128) static constexpr uint32_t const select_mask[4] {
                    x_up ? SELECT_1 : SELECT_0,
                    y_up ? SELECT_1 : SELECT_0,
                    z_up ? SELECT_1 : SELECT_0,
                    w_up ? SELECT_1 : SELECT_0,
                };

            __m128 const mask = _mm_load_ps(reinterpret_cast<float const*>(&select_mask[0]));
            __m128 const shuffled_v1 = _mm_permute_ps(a, shuffle);
            __m128 const shuffled_v2 = _mm_permute_ps(b, shuffle);
            __m128 const masked_v1 = _mm_andnot_ps(mask, shuffled_v1);
            __m128 const masked_v2 = _mm_and_ps(mask, shuffled_v2);
            __m128 const result = _mm_or_ps(masked_v1, masked_v2);

            return result;
        }
    }

    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline __m128 mathcall avx_swizzle(__m128 v) noexcept
    {
        static_assert((X < 4) and (Y < 4) and (Z < 4) and (W < 4));

        if constexpr (X == 0 and Y == 1 and Z == 2 and W == 3)
        {
            return v;
        }
        else if constexpr (X == 0 and Y == 1 and Z == 0 and W == 1)
        {
            return _mm_movelh_ps(v, v);
        }
        else if constexpr (X == 2 and Y == 3 and Z == 2 and W == 3)
        {
            return _mm_movehl_ps(v, v);
        }
        else if constexpr (X == 0 and Y == 0 and Z == 1 and W == 1)
        {
            return _mm_unpacklo_ps(v, v);
        }
        else if constexpr (X == 2 and Y == 2 and Z == 3 and W == 3)
        {
            return _mm_unpackhi_ps(v, v);
        }
        else if constexpr (X == 0 and Y == 0 and Z == 2 and W == 2)
        {
            return _mm_moveldup_ps(v);
        }
        else if constexpr (X == 1 and Y == 1 and Z == 3 and W == 3)
        {
            return _mm_movehdup_ps(v);
        }
#if GRAPHYTE_HW_AVX2
        else if constexpr (X == 0 and Y == 0 and Z == 0 and W == 0)
        {
            return _mm_broadcastss_ps(v);
        }
#endif
        else
        {
            //
            // General case.
            //

            return _mm_permute_ps(v, _MM_SHUFFLE(W,Z,Y,X));
        }
    }
}
