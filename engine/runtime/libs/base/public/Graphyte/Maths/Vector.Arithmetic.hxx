#pragma once
#include <Graphyte/Maths/Types.hxx>
#include <Graphyte/Bitwise.hxx>


// =================================================================================================
//
// Load/Store operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Load(Float4A const* source) noexcept
        requires (SimdVectorType<T> and T::Components <= 4)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 vresult = { { {
                source->X,
                source->Y,
                source->Z,
                source->W,
        } } };
        return { vresult.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps(reinterpret_cast<float*>(source)) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4A* destination, T v) noexcept
        requires (SimdVectorType<T> and T::Components <= 4)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float4 const* source) noexcept
        requires (SimdVectorType<T> and T::Components <= 4)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 vresult = { { {
                source->X,
                source->Y,
                source->Z,
                source->W,
        } } };
        return { vresult.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_loadu_ps(reinterpret_cast<float*>(source)) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4* destination, T v) noexcept
        requires (SimdVectorType<T> and T::Components <= 4)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3A const* source) noexcept
        requires (SimdVectorType<T> and T::Components <= 4)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_v = _mm_load_ps(&source->X);
        return { _mm_and_ps(v_v, Impl::VEC4_MASK_COMPONENTS_3.V) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3A* destination, T v) noexcept
        requires (SimdVectorType<T> and T::Components <= 3)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(&destination->Z, v_z);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3 const* source) noexcept
        requires (SimdVectorType<T> and T::Components <= 3)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        __m128 const v_z = _mm_load_ss(&source->Z);
        __m128 const v_xy = _mm_unpacklo_ps(v_x, v_y);
        return { _mm_movelh_ps(v_xy, v_z) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3* destination, T v) noexcept
        requires (SimdVectorType<T> and T::Components <= 3)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
        _mm_store_ss(&destination->Z, v_z);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2A const* source) noexcept
        requires (SimdVectorType<T> and T::Components <= 2)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(source));
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2A* destination, T v) noexcept
        requires (SimdVectorType<T> and T::Components <= 2)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2 const* source) noexcept
        requires (SimdVectorType<T>and T::Components <= 2)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        return { _mm_unpacklo_ps(v_x, v_y) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2* destination, T v) noexcept
        requires (SimdVectorType<T> and T::Components <= 2)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
#endif
    }
}


// =================================================================================================
//
// x
//

namespace Graphyte::Maths
{
}


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
    template <typename T>
    mathinline T mathcall Subtract(T v1, T v2) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] - v2.V.F[0],
            v1.V.F[1] - v2.V.F[1],
            v1.V.F[2] - v2.V.F[2],
            v1.V.F[3] - v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Multiply(T v1, T v2) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] * v2.V.F[0],
            v1.V.F[1] * v2.V.F[1],
            v1.V.F[2] * v2.V.F[2],
            v1.V.F[3] * v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Multiply(T v, float s) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
            v.V.F[0] * s,
            v.V.F[1] * s,
            v.V.F[2] * s,
            v.V.F[3] * s,
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_result = _mm_set_ps1(s);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Divide(T v1, T v2) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] / v2.V.F[0],
            v1.V.F[1] / v2.V.F[1],
            v1.V.F[2] / v2.V.F[2],
            v1.V.F[3] / v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Divide(T v, float s) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const inv_s = 1.0F / s;
        Impl::Vec4F32 v_result = { { {
            v.V.F[0] * inv_s,
            v.V.F[1] * inv_s,
            v.V.F[2] * inv_s,
            v.V.F[3] * inv_s,
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_result = _mm_set_ps1(1.0F / s);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    // (v1 * v2) + v3
    template <typename T>
    mathinline T mathcall MultiplyAdd(T v1, T v2, T v3) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                (v1.V.F[0] * v2.V.F[0]) + v3.V.F[0],
                (v1.V.F[1] * v2.V.F[1]) + v3.V.F[1],
                (v1.V.F[2] * v2.V.F[2]) + v3.V.F[2],
                (v1.V.F[3] * v2.V.F[3]) + v3.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fmadd_ps(v1.V, v2.V, v3.V) };
#endif
    }

    // (v1 * v2) - v3
    template <typename T>
    mathinline T mathcall MultiplySubtract(T v1, T v2, T v3) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                (v1.V.F[0] * v2.V.F[0]) - v3.V.F[0],
                (v1.V.F[1] * v2.V.F[1]) - v3.V.F[1],
                (v1.V.F[2] * v2.V.F[2]) - v3.V.F[2],
                (v1.V.F[3] * v2.V.F[3]) - v3.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fmsub_ps(v1.V, v2.V, v3.V) };
#endif
    }

    // -(v1 * v2) + v3
    template <typename T>
    mathinline T mathcall NegateMultiplyAdd(T v1, T v2, T v3) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                v3.V.F[0] - (v1.V.F[0] * v2.V.F[0]),
                v3.V.F[1] - (v1.V.F[1] * v2.V.F[1]),
                v3.V.F[2] - (v1.V.F[2] * v2.V.F[2]),
                v3.V.F[3] - (v1.V.F[3] * v2.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fnmadd_ps(v1.V, v2.V, v3.V) };
#endif
    }

    // -(v1 * v2) - v3
    template <typename T>
    mathinline T mathcall NegateMultiplySubtract(T v1, T v2, T v3) noexcept
        requires SimdVectorType<T>
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                -v3.V.F[0] - (v1.V.F[0] * v2.V.F[0]),
                -v3.V.F[1] - (v1.V.F[1] * v2.V.F[1]),
                -v3.V.F[2] - (v1.V.F[2] * v2.V.F[2]),
                -v3.V.F[3] - (v1.V.F[3] * v2.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_fnmsub_ps(v1.V, v2.V, v3.V) };
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
