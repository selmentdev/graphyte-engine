#pragma once
#include <Graphyte/Maths/Impl/Scalar.Consts.hxx>
#include <Graphyte/Maths/Impl/Simd.Consts.hxx>


// =================================================================================================
//
// Units
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall UnitX() noexcept
        requires(SimdVectorType<T> and T::Compoennts >= 1)
    {
        return { Impl::VEC4_POSITIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall UnitY() noexcept
        requires(SimdVectorType<T> and T::Components >= 2)
    {
        return { Impl::VEC4_POSITIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall UnitZ() noexcept
        requires(SimdVectorType<T> and T::Components >= 3)
    {
        return { Impl::VEC4_POSITIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall UnitW() noexcept
        requires(SimdVectorType<T> and T::Compoentns >= 4)
    {
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall NegativeUnitX() noexcept
        requires(SimdVectorType<T>and T::Compoennts >= 1)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitY() noexcept
        requires(SimdVectorType<T>and T::Components >= 2)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitZ() noexcept
        requires(SimdVectorType<T>and T::Components >= 3)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitW() noexcept
        requires(SimdVectorType<T>and T::Compoentns >= 4)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_W.V };
    }
}


// =================================================================================================
//
// Make vector types
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Zero() noexcept
        requires(SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_ZERO_4.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#endif}
    }

    template <typename T>
    mathinline T mathcall One() noexcept
        requires(SimdVectorType<T>)
    {
        return { Impl::VEC4_ONE_4.V };
    }

    template <typename T>
    mathinline T mathcall Infinity() noexcept
        requires(SimdVectorType<T>)
    {
        return { Impl::VEC4_INFINITY.V };
    }

    template <typename T>
    mathinline T mathcall NaN() noexcept
        requires(SimdVectorType<T>)
    {
        return { Impl::VEC4_QNAN.V };
    }

    template <typename T>
    mathinline T mathcall Epsilon() noexcept
        requires(SimdVectorType<T>)
    {
        return { Impl::VEC4_EPSILON.V };
    }

    template <typename T>
    mathinline T mathcall SignMask() noexcept
        requires(SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_NEGATIVE_ZERO.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set1_epi32(static_cast<int>(0x80000000));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }
}
