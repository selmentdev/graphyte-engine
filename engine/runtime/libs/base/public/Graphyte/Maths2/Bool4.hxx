#pragma once
#include <Graphyte/Maths2/Types.hxx>
#include <Graphyte/Maths2/Consts.hxx>


namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall True() noexcept
    {
        static_assert(Impl::IsMask<T>);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { 0xFFFF'FFFFU, 0xFFFF'FFFFU, 0xFFFF'FFFFU, 0xFFFF'FFFFU } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_set1_epi32(-1);
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    template <typename T>
    mathinline T mathcall False() noexcept
    {
        static_assert(Impl::IsMask<T>);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { 0.0F, 0.0F, 0.0F, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#endif
    }

    mathinline Bool4 mathcall And(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                v1.V.U[0] & v2.V.U[0],
                v1.V.U[1] & v2.V.U[1],
                v1.V.U[2] & v2.V.U[2],
                v1.V.U[3] & v2.V.U[3],
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_and_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Bool4 mathcall Or(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                v1.V.U[0] | v2.V.U[0],
                v1.V.U[1] | v2.V.U[1],
                v1.V.U[2] | v2.V.U[2],
                v1.V.U[3] | v2.V.U[3],
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_or_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Bool4 mathcall Xor(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                v1.V.U[0] ^ v2.V.U[0],
                v1.V.U[1] ^ v2.V.U[1],
                v1.V.U[2] ^ v2.V.U[2],
                v1.V.U[3] ^ v2.V.U[3],
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_result = _mm_xor_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Bool4 mathcall Nor(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                ~(v1.V.U[0] | v2.V.U[0]),
                ~(v1.V.U[1] | v2.V.U[1]),
                ~(v1.V.U[2] | v2.V.U[2]),
                ~(v1.V.U[3] | v2.V.U[3]),
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i v_result = _mm_or_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        v_result = _mm_andnot_si128(v_result, _mm_castps_si128(Impl::VEC4_MASK_NEGATIVE_ONE.V));
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Bool4 mathcall AndNot(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                v1.V.U[0] & ~v2.V.U[0],
                v1.V.U[1] & ~v2.V.U[1],
                v1.V.U[2] & ~v2.V.U[2],
                v1.V.U[3] & ~v2.V.U[3],
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_andnot_si128(_mm_castps_si128(v2.V), _mm_castps_si128(v1.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Bool4 mathcall CmpEq(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                (v1.V.U[0] == v2.V.U[0]) ? 0xFFFF'FFFFU : 0,
                (v1.V.U[1] == v2.V.U[1]) ? 0xFFFF'FFFFU : 0,
                (v1.V.U[2] == v2.V.U[2]) ? 0xFFFF'FFFFU : 0,
                (v1.V.U[3] == v2.V.U[3]) ? 0xFFFF'FFFFU : 0,
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Bool4 mathcall CmpNeq(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                (v1.V.U[0] != v2.V.U[0]) ? 0xFFFF'FFFFU : 0,
                (v1.V.U[1] != v2.V.U[1]) ? 0xFFFF'FFFFU : 0,
                (v1.V.U[2] != v2.V.U[2]) ? 0xFFFF'FFFFU : 0,
                (v1.V.U[3] != v2.V.U[3]) ? 0xFFFF'FFFFU : 0,
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_xor_ps(_mm_castsi128_ps(v_temp), Impl::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }

    mathinline bool mathcall IsEq(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        bool const result =
            v1.V.U[0] == v2.V.U[0] &&
            v1.V.U[1] == v2.V.U[1] &&
            v1.V.U[2] == v2.V.U[2] &&
            v1.V.U[3] == v2.V.U[3];

        return result;
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(_mm_cmpeq_ps(v1.V, v2.V)) == 0b1111;
#endif
    }

    mathinline bool mathcall IsNeq(Bool4 v1, Bool4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        bool const result =
            v1.V.U[0] != v2.V.U[0] ||
            v1.V.U[1] != v2.V.U[1] ||
            v1.V.U[2] != v2.V.U[2] ||
            v1.V.U[3] != v2.V.U[3];

        return result;
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(_mm_cmpeq_ps(v1.V, v2.V)) == 0b1111;
#endif
    }

    mathinline bool mathcall AnyTrue(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            || (v.V.U[1] != 0)
            || (v.V.U[2] != 0)
            || (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) != 0;
#endif
    }

    mathinline bool mathcall AnyFalse(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            || (v.V.U[1] == 0)
            || (v.V.U[2] == 0)
            || (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) != 0b1111;
#endif
    }

    mathinline bool mathcall AllTrue(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            && (v.V.U[1] != 0)
            && (v.V.U[2] != 0)
            && (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) == 0b1111;
#endif
    }

    mathinline bool mathcall AllFalse(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            && (v.V.U[1] == 0)
            && (v.V.U[2] == 0)
            && (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) == 0;
#endif
    }

    mathinline Bool4 mathcall MakeMask(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_set_epi32(static_cast<int32_t>(w), static_cast<int32_t>(z), static_cast<int32_t>(y), static_cast<int32_t>(x));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Bool3 mathcall MakeMask(uint32_t x, uint32_t y, uint32_t z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { x, y, z, 0 } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_set_epi32(0, static_cast<int32_t>(z), static_cast<int32_t>(y), static_cast<int32_t>(x));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Bool2 mathcall MakeMask(uint32_t x, uint32_t y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { x, y, 0, 0 } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_set_epi32(0, 0, static_cast<int32_t>(y), static_cast<int32_t>(x));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }
}
