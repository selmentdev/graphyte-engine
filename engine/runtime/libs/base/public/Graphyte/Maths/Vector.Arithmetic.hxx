#pragma once
#include <Graphyte/Maths/Types.hxx>
#include <Graphyte/Bitwise.hxx>

// =================================================================================================
//
// Component-wise functions
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall ComponentSum(T v) noexcept
        requires (SimdVectorType<T> and T::Components == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return Make<T>(v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const vhalf1 = _mm_hadd_ps(v.V, v.V);
        __m128 const vhalf2 = _mm_hadd_ps(vhalf1, vhalf1);
        return { _mm_permute_ps(vhalf2, _MM_SHUFFLE(0, 0, 0, 0)) };
#endif
    }
}


// =================================================================================================
//
// Arithmetic operations
//

namespace Graphyte::Maths
{
}


// =================================================================================================
//
// Per-component comparison
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline typename T::MaskType mathcall CompareEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdEqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] == v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] == v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] == v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] == v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpeq_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareEqual(T v1, T v2, Vec4 epsilon) noexcept
        requires SimdVectorMaskable<T> and SimdEqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float delta_x = (v1.V.F[0] - v2.V.F[0]);
        float delta_y = (v1.V.F[1] - v2.V.F[1]);
        float delta_z = (v1.V.F[2] - v2.V.F[2]);
        float delta_w = (v1.V.F[3] - v2.V.F[3]);

        delta_x = fabsf(delta_x);
        delta_y = fabsf(delta_y);
        delta_z = fabsf(delta_z);
        delta_w = fabsf(delta_w);

        Impl::Vec4U32 v_control = { { {
                (delta_x <= epsilon.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (delta_y <= epsilon.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (delta_z <= epsilon.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (delta_w <= epsilon.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_delta = _mm_sub_ps(v1.V, v2.V);
        __m128 v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareNotEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdEqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] != v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] != v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] != v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] != v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareLess(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdOrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] < v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] < v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] < v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] < v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmplt_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareLessEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdOrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] <= v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] <= v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] <= v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] <= v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmple_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareGreater(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdOrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] > v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] > v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] > v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] > v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpgt_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline typename T::MaskType mathcall CompareGreaterEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdOrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] >= v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] >= v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] >= v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] >= v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpge_ps(v1.V, v2.V) };
#endif
    }
}


// =================================================================================================
//
// Per-component comparison 
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline bool mathcall IsEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdEqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] == v2.V.F[0]) &&
            (v1.V.F[1] == v2.V.F[1]) &&
            (v1.V.F[2] == v2.V.F[2]) &&
            (v1.V.F[3] == v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T v1, T v2, Vec4 epsilon) noexcept
        requires SimdVectorMaskable<T> and SimdEqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const dx = fabsf(v1.V.F[0] - v2.V.F[0]);
        float const dy = fabsf(v1.V.F[1] - v2.V.F[1]);
        float const dz = fabsf(v1.V.F[2] - v2.V.F[2]);
        float const dw = fabsf(v1.V.F[3] - v2.V.F[3]);

        return
            (dx <= epsilon.V.F[0]) &&
            (dy <= epsilon.V.F[1]) &&
            (dz <= epsilon.V.F[2]) &&
            (dw <= epsilon.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_delta = _mm_sub_ps(v1.V, v2.V);
        __m128 v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdEqualComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] != v2.V.F[0]) ||
            (v1.V.F[1] != v2.V.F[1]) ||
            (v1.V.F[2] != v2.V.F[2]) ||
            (v1.V.F[3] != v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpneq_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) != 0b0000;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLess(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdOrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] < v2.V.F[0]) &&
            (v1.V.F[1] < v2.V.F[1]) &&
            (v1.V.F[2] < v2.V.F[2]) &&
            (v1.V.F[3] < v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmplt_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLessEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdVectorORderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] <= v2.V.F[0]) &&
            (v1.V.F[1] <= v2.V.F[1]) &&
            (v1.V.F[2] <= v2.V.F[2]) &&
            (v1.V.F[3] <= v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmple_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreater(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdOrderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] > v2.V.F[0]) &&
            (v1.V.F[1] > v2.V.F[1]) &&
            (v1.V.F[2] > v2.V.F[2]) &&
            (v1.V.F[3] > v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpgt_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreaterEqual(T v1, T v2) noexcept
        requires SimdVectorMaskable<T> and SimdVectorORderComparable<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] >= v2.V.F[0]) &&
            (v1.V.F[1] >= v2.V.F[1]) &&
            (v1.V.F[2] >= v2.V.F[2]) &&
            (v1.V.F[3] >= v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpge_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }
}
