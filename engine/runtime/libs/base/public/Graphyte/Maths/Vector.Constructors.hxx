#pragma once
#include <Graphyte/Maths/Types.hxx>

// =================================================================================================
//
// Create Vec4 from bitmasks
//

namespace Graphyte::Maths
{
    mathinline Vec4 mathcall MakeUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_set_epi32(static_cast<int32_t>(w), static_cast<int32_t>(z), static_cast<int32_t>(y), static_cast<int32_t>(x));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vec4 mathcall MakeUInt(uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_temp = _mm_set1_epi32(static_cast<int32_t>(value));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }
}


// =================================================================================================
//
// Create SIMD Vector from floats.
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Make(float x, float y, float z, float w) noexcept
        requires (Maths::SimdVectorType<T> and T::Components == 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z) noexcept
        requires (Maths::SimdVectorType<T> and T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, z, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, z, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y) noexcept
        requires (Maths::SimdVectorType<T> and T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, 0.0F, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float value) noexcept
        requires (Maths::SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#endif
    }
}
