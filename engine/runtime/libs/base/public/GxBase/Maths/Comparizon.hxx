#pragma once
#include <GxBase/Maths/Vector.hxx>


// =================================================================================================
//
// Explicit comparison.
//

namespace Graphyte::Maths
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
        requires(Impl::IsSimdFloat4<T>)
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
        requires(std::is_floating_point_v<T>)
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
