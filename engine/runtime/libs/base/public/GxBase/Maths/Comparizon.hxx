#pragma once
#include <GxBase/Maths/Vector.hxx>

// =================================================================================================
//
// Boolean comparisons
//

namespace Graphyte
{
    template <typename T>
    mathinline T mathcall CompareEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.U[0] == b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[1] == b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[2] == b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[3] == b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall CompareNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.U[0] != b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[1] != b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[2] != b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[3] != b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_xor_ps(_mm_castsi128_ps(result), Impl::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.U[0] == b.V.U[0])
                   && (a.V.U[1] == b.V.U[1])
                   && (a.V.U[2] == b.V.U[2])
                   && (a.V.U[3] == b.V.U[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.U[0] == b.V.U[0])
                   && (a.V.U[1] == b.V.U[1])
                   && (a.V.U[2] == b.V.U[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.U[0] == b.V.U[0])
                   && (a.V.U[1] == b.V.U[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.U[0] == b.V.U[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t const expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
        }
        else if constexpr (T::Components == 3)
        {
        }
        else if constexpr (T::Components == 2)
        {
        }
        else if constexpr (T::Components == 1)
        {
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t const expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != expected;
        }
#endif
    }
}

// =================================================================================================
//
// Boolean mask qualification
//

namespace Graphyte
{
    template <typename T>
    mathinline bool mathcall AllTrue(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] != 0)
                   && (v.V.U[1] != 0)
                   && (v.V.U[2] != 0)
                   && (v.V.U[3] != 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] != 0)
                   && (v.V.U[1] != 0)
                   && (v.V.U[2] != 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] != 0)
                   && (v.V.U[1] != 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] != 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) == expected;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AllFalse(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] == 0)
                   && (v.V.U[1] == 0)
                   && (v.V.U[2] == 0)
                   && (v.V.U[3] == 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] == 0)
                   && (v.V.U[1] == 0)
                   && (v.V.U[2] == 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] == 0)
                   && (v.V.U[1] == 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] == 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) == 0;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) == 0;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AnyTrue(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] != 0)
                   || (v.V.U[1] != 0)
                   || (v.V.U[2] != 0)
                   || (v.V.U[3] != 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] != 0)
                   || (v.V.U[1] != 0)
                   || (v.V.U[2] != 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] != 0)
                   || (v.V.U[1] != 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] != 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) != expected;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) != 0;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AnyFalse(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] == 0)
                   || (v.V.U[1] == 0)
                   || (v.V.U[2] == 0)
                   || (v.V.U[3] == 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] == 0)
                   || (v.V.U[1] == 0)
                   || (v.V.U[2] == 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] == 0)
                   || (v.V.U[1] == 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] == 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) != expected;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) != expected;
        }
#endif
    }
}


// =================================================================================================
//
// Bit comparison
//

namespace Graphyte
{
    template <typename T>
    mathinline typename T::Mask BitCompareEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.U[0] == b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[1] == b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[2] == b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[3] == b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    template <typename T>
    mathinline typename T::Mask BitCompareNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.U[0] != b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[1] != b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[2] != b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.U[3] != b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_xor_ps(_mm_castsi128_ps(result), Impl::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }
}


// =================================================================================================
//
// Value comparison
//

namespace Graphyte
{
    template <typename T>
    mathinline typename T::Mask CompareEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.F[0] == b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[1] == b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[2] == b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[3] == b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpeq_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vceqq_f32(a.V, b.V)) };
#endif
    }

    template <typename T>
    mathinline typename T::Mask CompareEqual(T a, T b, T epsilon) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const dx = (a.V.F[0] - b.V.F[0]);
        float const dy = (a.V.F[1] - b.V.F[1]);
        float const dz = (a.V.F[2] - b.V.F[2]);
        float const dw = (a.V.F[3] - b.V.F[3]);

        float const absx = fabsf(dx);
        float const absy = fabsf(dy);
        float const absz = fabsf(dz);
        float const absw = fabsf(dw);

        Impl::ConstUInt32x4 const result{ { {
            (absx <= epsilon.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (absy <= epsilon.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (absz <= epsilon.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (absw <= epsilon.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const delv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const negv = _mm_sub_ps(zero, delv);
        __m128 const absv = _mm_max_ps(delv, negv);
        __m128 const mask = _mm_cmple_ps(absv, epsilon.V);
        return { mask };
#elif GRAPHYTE_HW_NEON
        float32x4_t const diff   = vsubq_f32(a.V, b.V);
        float32x4_t const result = vacleq_f32(diff, epsilon.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline typename T::Mask CompareNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.F[0] != b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[1] != b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[2] != b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[3] != b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const equal     = vreinterpretq_u32_f32(vceqq_f32(a.V, b.V));
        uint32x4_t const not_equal = vmvnq_u32(equal);
        return { vreinterpretq_f32_u32(not_equal) };
#endif
    }

    template <typename T>
    mathinline typename T::Mask CompareGreater(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.F[0] > b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[1] > b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[2] > b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[3] > b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpgt_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vcgtq_f32(a.V, b.V)) };
#endif
    }

    template <typename T>
    mathinline typename T::Mask CompareGreaterEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.F[0] >= b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[1] >= b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[2] >= b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[3] >= b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpge_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vcgeq_f32(a.V, b.V)) };
#endif
    }

    template <typename T>
    mathinline typename T::Mask CompareLess(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.F[0] < b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[1] < b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[2] < b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[3] < b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmplt_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vcltq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline typename T::Mask CompareLessEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.F[0] <= b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[1] <= b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[2] <= b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (a.V.F[3] <= b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmple_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vcleq_f32(a.V, b.V)) };
#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    template <typename T>
    mathinline typename T::Mask mathcall CompareNan(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            FloatTraits<float>::BitIsNan(v.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            FloatTraits<float>::BitIsNan(v.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            FloatTraits<float>::BitIsNan(v.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            FloatTraits<float>::BitIsNan(v.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v.V, v.V) };
#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    template <typename T>
    mathinline typename T::Mask mathcall CompareInfinite(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            FloatTraits<float>::BitIsInf(v.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            FloatTraits<float>::BitIsInf(v.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            FloatTraits<float>::BitIsInf(v.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            FloatTraits<float>::BitIsInf(v.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const abs_v  = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const result = _mm_cmpeq_ps(abs_v, Impl::VEC4_INFINITY.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline typename T::Mask mathcall CompareInBounds(T v, T bounds) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
            (-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le    = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge    = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const result     = _mm_and_ps(mask_le, mask_ge);
        return { result };
#endif
    }
}

// =================================================================================================
//
// Explicit comparison.
//

namespace Graphyte
{
    template <typename T>
    mathinline bool mathcall IsZero(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.F[0] == 0.0F)
                   && (v.V.F[1] == 0.0F)
                   && (v.V.F[2] == 0.0F)
                   && (v.V.F[3] == 0.0F);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.F[0] == 0.0F)
                   && (v.V.F[1] == 0.0F)
                   && (v.V.F[2] == 0.0F);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.F[0] == 0.0F)
                   && (v.V.F[1] == 0.0F);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.F[0] == 0.0F);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask = _mm_cmpeq_ps(v.V, zero);

        
        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsZero(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v == T(0.0);
    }

    template <typename T>
    mathinline bool mathcall IsZero(T v, T epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
                   && (fabsf(v.V.F[1]) <= epsilon.V.F[1])
                   && (fabsf(v.V.F[2]) <= epsilon.V.F[2])
                   && (fabsf(v.V.F[3]) <= epsilon.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
                   && (fabsf(v.V.F[1]) <= epsilon.V.F[1])
                   && (fabsf(v.V.F[2]) <= epsilon.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
                   && (fabsf(v.V.F[1]) <= epsilon.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const zero     = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs      = _mm_max_ps(v.V, negative);
        __m128 const mask     = _mm_cmple_ps(abs, epsilon.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsZero(T v, T epsilon) noexcept
    {
        return fabs(v) <= epsilon;
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] == b.V.F[0])
                   && (a.V.F[1] == b.V.F[1])
                   && (a.V.F[2] == b.V.F[2])
                   && (a.V.F[3] == b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] == b.V.F[0])
                   && (a.V.F[1] == b.V.F[1])
                   && (a.V.F[2] == b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] == b.V.F[0])
                   && (a.V.F[1] == b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] == b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a == b);
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b, T epsilon) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);
            float const fy = fabsf(a.V.F[1] - b.V.F[1]);
            float const fz = fabsf(a.V.F[2] - b.V.F[2]);
            float const fw = fabsf(a.V.F[3] - b.V.F[3]);

            return (fx <= epsilon.V.F[0])
                   && (fy <= epsilon.V.F[1])
                   && (fz <= epsilon.V.F[2])
                   && (fw <= epsilon.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);
            float const fy = fabsf(a.V.F[1] - b.V.F[1]);
            float const fz = fabsf(a.V.F[2] - b.V.F[2]);

            return (fx <= epsilon.V.F[0])
                   && (fy <= epsilon.V.F[1])
                   && (fz <= epsilon.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);
            float const fy = fabsf(a.V.F[1] - b.V.F[1]);

            return (fx <= epsilon.V.F[0])
                   && (fy <= epsilon.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);

            return (fx <= epsilon.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const dv   = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const nv   = _mm_sub_ps(zero, dv);
        __m128 const av   = _mm_max_ps(nv, dv);
        __m128 const mask = _mm_cmple_ps(av, epsilon.V);

        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b, T epsilon) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (fabs(a - b) <= epsilon);
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] != b.V.F[0])
                   || (a.V.F[1] != b.V.F[1])
                   || (a.V.F[2] != b.V.F[2])
                   || (a.V.F[3] != b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] != b.V.F[0])
                   || (a.V.F[1] != b.V.F[1])
                   || (a.V.F[2] != b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] != b.V.F[0])
                   || (a.V.F[1] != b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] != b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpneq_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return (_mm_movemask_ps(mask) != 0);
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a != b);
    }

    template <typename T>
    mathinline bool mathcall IsGreater(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] > b.V.F[0])
                   && (a.V.F[1] > b.V.F[1])
                   && (a.V.F[2] > b.V.F[2])
                   && (a.V.F[3] > b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] > b.V.F[0])
                   && (a.V.F[1] > b.V.F[1])
                   && (a.V.F[2] > b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] > b.V.F[0])
                   && (a.V.F[1] > b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] > b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreater(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a > b);
    }

    template <typename T>
    mathinline bool mathcall IsGreaterEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] >= b.V.F[0])
                   && (a.V.F[1] >= b.V.F[1])
                   && (a.V.F[2] >= b.V.F[2])
                   && (a.V.F[3] >= b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] >= b.V.F[0])
                   && (a.V.F[1] >= b.V.F[1])
                   && (a.V.F[2] >= b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] >= b.V.F[0])
                   && (a.V.F[1] >= b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] >= b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpge_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreaterEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a >= b);
    }

    template <typename T>
    mathinline bool mathcall IsLess(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] < b.V.F[0])
                   && (a.V.F[1] < b.V.F[1])
                   && (a.V.F[2] < b.V.F[2])
                   && (a.V.F[3] < b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] < b.V.F[0])
                   && (a.V.F[1] < b.V.F[1])
                   && (a.V.F[2] < b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] < b.V.F[0])
                   && (a.V.F[1] < b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] < b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmplt_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLess(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a < b);
    }

    template <typename T>
    mathinline bool mathcall IsLessEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] <= b.V.F[0])
                   && (a.V.F[1] <= b.V.F[1])
                   && (a.V.F[2] <= b.V.F[2])
                   && (a.V.F[3] <= b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] <= b.V.F[0])
                   && (a.V.F[1] <= b.V.F[1])
                   && (a.V.F[2] <= b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] <= b.V.F[0])
                   && (a.V.F[1] <= b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] <= b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmple_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLessEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a <= b);
    }

    template <typename T>
    mathinline bool InBounds(T v, T bounds) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                   && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
                   && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]))
                   && ((-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]));
        }
        else if constexpr (T::Components == 3)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                   && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
                   && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]));
        }
        else if constexpr (T::Components == 2)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                   && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]));
        }
        else if constexpr (T::Components == 1)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]));
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask_le    = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge    = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask       = _mm_and_ps(mask_le, mask_ge);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool IsNan(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return FloatTraits<float>::IsNan(v.V.F[0])
                   || FloatTraits<float>::IsNan(v.V.F[1])
                   || FloatTraits<float>::IsNan(v.V.F[2])
                   || FloatTraits<float>::IsNan(v.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return FloatTraits<float>::IsNan(v.V.F[0])
                   || FloatTraits<float>::IsNan(v.V.F[1])
                   || FloatTraits<float>::IsNan(v.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return FloatTraits<float>::IsNan(v.V.F[0])
                   || FloatTraits<float>::IsNan(v.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return FloatTraits<float>::IsNan(v.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);

        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != 0;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != 0;
        }
#endif
    }

    template <typename T>
    mathinline bool IsInfinity(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return FloatTraits<float>::IsInf(v.V.F[0])
                   || FloatTraits<float>::IsInf(v.V.F[1])
                   || FloatTraits<float>::IsInf(v.V.F[2])
                   || FloatTraits<float>::IsInf(v.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return FloatTraits<float>::IsInf(v.V.F[0])
                   || FloatTraits<float>::IsInf(v.V.F[1])
                   || FloatTraits<float>::IsInf(v.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return FloatTraits<float>::IsInf(v.V.F[0])
                   || FloatTraits<float>::IsInf(v.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return FloatTraits<float>::IsInf(v.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const abs  = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);

        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != 0;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != 0;
        }
#endif
    }
}

requires(Impl::IsSimdFloat4<T>)
requires(std::is_floating_point_v<T>)



        if constexpr (T::Components == 4)
        {
        }
        else if constexpr (T::Components == 3)
        {
        }
        else if constexpr (T::Components == 2)
        {
        }
        else if constexpr (T::Components == 1)
        {
        }
