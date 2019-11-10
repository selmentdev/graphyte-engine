#pragma once
#include <Graphyte/Maths2/Types.hxx>



namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall ConstTrue() noexcept
        //requires Impl::IsSimdVectorMask<T>
    {
        static_assert(Impl::IsMask<T>);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { 0xFFFF'FFFFU, 0xFFFF'FFFFU, 0xFFFF'FFFFU, 0xFFFF'FFFFU } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set1_epi32(-1);
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    template <typename T>
    mathinline T mathcall ConstFalse() noexcept
        //requires Impl::IsSimdVectorMask<T>
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
        return { _mm_and_ps(v1.V, v2.V) };
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
        return { _mm_or_ps(v1.V, v2.V) };
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
        return { _mm_xor_ps(v1.V, v2.V) };
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
        return { _mm_xor_ps(v1.V, v2.V) };
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
        return { _mm_andnot_ps(v1.V, v2.V) };
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
}
