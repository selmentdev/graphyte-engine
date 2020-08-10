#pragma once

// =================================================================================================
//
// This module implements AVX specific helper functions.
//

namespace Graphyte::Maths::Impl
{
    template <size_t Components>
    inline constexpr int avx_mm_dp_mask = 0xFF >> (4 - Components);

    mathinline __m128 mathcall avx_fmadd_f32x4(
        __m128 a,
        __m128 b,
        __m128 c) noexcept
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
        __m128 c) noexcept
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
        __m128 c) noexcept
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
        __m128 c) noexcept
    {
#if GRAPHYTE_HW_FMA4
        return _mm_nmsub_ps(a, b, c);
#elif GRAPHYTE_HW_AVX2
        return _mm_fnmsub_ps(a, b, c);
#else
        // (a * b)
        __m128 const ab   = _mm_mul_ps(a, b);
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
        static_assert((X < 8) && (Y < 8) && (Z < 8) && (W < 8));

        constexpr bool x_up = (X >= 4);
        constexpr bool y_up = (Y >= 4);
        constexpr bool z_up = (Z >= 4);
        constexpr bool w_up = (W >= 4);

        constexpr int shuffle = _MM_SHUFFLE(W & 3, Z & 3, Y & 3, X & 3);

        if constexpr (X == 0 && Y == 1 && Z == 2 && W == 3)
        {
            return a;
        }
        else if constexpr (X == 4 && Y == 5 && Z == 6 && W == 7)
        {
            return b;
        }
        else if constexpr (X == 4 && Y == 1 && Z == 2 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x1);
        }
        else if constexpr (X == 0 && Y == 5 && Z == 2 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x2);
        }
        else if constexpr (X == 4 && Y == 5 && Z == 2 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x3);
        }
        else if constexpr (X == 0 && Y == 1 && Z == 6 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x4);
        }
        else if constexpr (X == 4 && Y == 1 && Z == 6 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x5);
        }
        else if constexpr (X == 0 && Y == 5 && Z == 6 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x6);
        }
        else if constexpr (X == 4 && Y == 5 && Z == 6 && W == 3)
        {
            return _mm_blend_ps(a, b, 0x7);
        }
        else if constexpr (X == 0 && Y == 1 && Z == 2 && W == 7)
        {
            return _mm_blend_ps(a, b, 0x8);
        }
        else if constexpr (X == 4 && Y == 1 && Z == 2 && W == 7)
        {
            return _mm_blend_ps(a, b, 0x9);
        }
        else if constexpr (X == 0 && Y == 5 && Z == 2 && W == 7)
        {
            return _mm_blend_ps(a, b, 0xA);
        }
        else if constexpr (X == 4 && Y == 5 && Z == 2 && W == 7)
        {
            return _mm_blend_ps(a, b, 0xB);
        }
        else if constexpr (X == 0 && Y == 1 && Z == 6 && W == 7)
        {
            return _mm_blend_ps(a, b, 0xC);
        }
        else if constexpr (X == 4 && Y == 1 && Z == 6 && W == 7)
        {
            return _mm_blend_ps(a, b, 0xD);
        }
        else if constexpr (X == 0 && Y == 5 && Z == 6 && W == 7)
        {
            return _mm_blend_ps(a, b, 0xE);
        }
        else if constexpr (X == 0 && Y == 1 && Z == 0 && W == 1)
        {
            return _mm_movelh_ps(a, a);
        }
        else if constexpr (X == 4 && Y == 5 && Z == 4 && W == 5)
        {
            return _mm_movelh_ps(b, b);
        }
        else if constexpr (X == 2 && Y == 3 && Z == 2 && W == 3)
        {
            return _mm_movehl_ps(a, a);
        }
        else if constexpr (X == 6 && Y == 7 && Z == 6 && W == 7)
        {
            return _mm_movehl_ps(b, b);
        }
        else if constexpr (X == 0 && Y == 0 && Z == 1 && W == 1)
        {
            return _mm_unpacklo_ps(a, a);
        }
        else if constexpr (X == 4 && Y == 4 && Z == 5 && W == 5)
        {
            return _mm_unpacklo_ps(b, b);
        }
        else if constexpr (X == 2 && Y == 2 && Z == 3 && W == 3)
        {
            return _mm_unpackhi_ps(a, a);
        }
        else if constexpr (X == 6 && Y == 6 && Z == 7 && W == 7)
        {
            return _mm_unpackhi_ps(b, b);
        }
        else if constexpr (X == 0 && Y == 0 && Z == 2 && W == 2)
        {
            return _mm_moveldup_ps(a);
        }
        else if constexpr (X == 1 && Y == 1 && Z == 3 && W == 3)
        {
            return _mm_movehdup_ps(a);
        }
        else if constexpr (X == 4 && Y == 4 && Z == 6 && W == 6)
        {
            return _mm_moveldup_ps(b);
        }
        else if constexpr (X == 5 && Y == 5 && Z == 7 && W == 7)
        {
            return _mm_movehdup_ps(b);
        }
#if GRAPHYTE_HW_AVX2
        else if constexpr (X == 0 && Y == 0 && Z == 0 && W == 0)
        {
            return _mm_broadcastss_ps(a, shuffle);
        }
        else if constexpr (X == 4 && Y == 4 && Z == 4 && W == 4)
        {
            return _mm_broadcastss_ps(b, shuffle);
        }
#endif
        else if constexpr (!x_up && !y_up && !z_up && !w_up)
        {
            return _mm_permute_ps(a, shuffle);
        }
        else if constexpr (x_up && y_up && z_up && w_up)
        {
            return _mm_permute_ps(b, shuffle);
        }
        else if constexpr (!x_up && !y_up && z_up && w_up)
        {
            return _mm_shuffle_ps(a, b, shuffle);
        }
        else if constexpr (x_up && y_up && !z_up && !w_up)
        {
            return _mm_shuffle_ps(b, a, shuffle);
        }
        else
        {
            //
            // General case.
            //

            alignas(__m128) static constexpr uint32_t const select_mask[4]{
                x_up ? 0xFFFFFFFFu : 0x00000000u,
                y_up ? 0xFFFFFFFFu : 0x00000000u,
                z_up ? 0xFFFFFFFFu : 0x00000000u,
                w_up ? 0xFFFFFFFFu : 0x00000000u,
            };

            __m128 const mask        = _mm_load_ps(reinterpret_cast<float const*>(&select_mask[0]));
            __m128 const shuffled_v1 = _mm_permute_ps(a, shuffle);
            __m128 const shuffled_v2 = _mm_permute_ps(b, shuffle);
            __m128 const masked_v1   = _mm_andnot_ps(mask, shuffled_v1);
            __m128 const masked_v2   = _mm_and_ps(mask, shuffled_v2);
            __m128 const result      = _mm_or_ps(masked_v1, masked_v2);

            return result;
        }
    }

    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline __m128 mathcall avx_swizzle(__m128 v) noexcept
    {
        static_assert((X < 4) && (Y < 4) && (Z < 4) && (W < 4));

        if constexpr (X == 0 && Y == 1 && Z == 2 && W == 3)
        {
            return v;
        }
        else if constexpr (X == 0 && Y == 1 && Z == 0 && W == 1)
        {
            return _mm_movelh_ps(v, v);
        }
        else if constexpr (X == 2 && Y == 3 && Z == 2 && W == 3)
        {
            return _mm_movehl_ps(v, v);
        }
        else if constexpr (X == 0 && Y == 0 && Z == 1 && W == 1)
        {
            return _mm_unpacklo_ps(v, v);
        }
        else if constexpr (X == 2 && Y == 2 && Z == 3 && W == 3)
        {
            return _mm_unpackhi_ps(v, v);
        }
        else if constexpr (X == 0 && Y == 0 && Z == 2 && W == 2)
        {
            return _mm_moveldup_ps(v);
        }
        else if constexpr (X == 1 && Y == 1 && Z == 3 && W == 3)
        {
            return _mm_movehdup_ps(v);
        }
#if GRAPHYTE_HW_AVX2
        else if constexpr (X == 0 && Y == 0 && Z == 0 && W == 0)
        {
            return _mm_broadcastss_ps(v);
        }
#endif
        else
        {
            //
            // General case.
            //

            return _mm_permute_ps(v, _MM_SHUFFLE(W, Z, Y, X));
        }
    }

    mathinline __m128 mathcall avx_select(__m128 a, __m128 b, __m128 control) noexcept
    {
        __m128 const result = _mm_blendv_ps(a, b, control);
        return result;
    }
}
