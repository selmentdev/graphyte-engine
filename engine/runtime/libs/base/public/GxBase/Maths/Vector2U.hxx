#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector4U.hxx>

// =================================================================================================
//
// Vector construction.
//

namespace Graphyte::Maths
{
    template <>
    mathinline Vector2U mathcall Make<Vector2U, uint32_t>(uint32_t x, uint32_t y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                x, y, 0, 0,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set_epi32(
            static_cast<int>(0),
            static_cast<int>(0),
            static_cast<int>(y),
            static_cast<int>(x)
        );
        return { result };
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector2U mathcall Replicate<Vector2U, uint32_t>(uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set1_epi32(static_cast<int>(value));
        return { result };
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }
}

// =================================================================================================
//
// Bitwise arithmetic operations.
//

namespace Graphyte::Maths
{
    template <>
    mathinline Vector2U mathcall And<Vector2U>(Vector2U a, Vector2U b) noexcept
    {
        return { And<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector2U mathcall AndNot<Vector2U>(Vector2U a, Vector2U b) noexcept
    {
        return { AndNot<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector2U mathcall Or<Vector2U>(Vector2U a, Vector2U b) noexcept
    {
        return { Or<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector2U mathcall Xor(Vector2U a, Vector2U b) noexcept
    {
        return { Xor<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector2U mathcall Nor(Vector2U a, Vector2U b) noexcept
    {
        return { Nor<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector2U mathcall Not(Vector2U x) noexcept
    {
        return { Not<Vector4U>({ x.V }).V };
    }
}


// =================================================================================================
//
// Comparison masking functions
//

namespace Graphyte::Maths
{
    template <>
    mathinline Vector2U mathcall CompareEqual<Vector2U, Vector2U>(Vector2U a, Vector2U b) noexcept
    {
        return { CompareEqual<Vector4U, Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector2U mathcall CompareNotEqual<Vector2U, Vector2U>(Vector2U a, Vector2U b) noexcept
    {
        return { CompareNotEqual<Vector4U, Vector4U>({ a.V }, { b.V }).V };
    }
}


// =================================================================================================
//
// Comparison logical functions
//

namespace Graphyte::Maths
{
    template <>
    mathinline bool mathcall IsEqual<Vector2U>(Vector2U a, Vector2U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0])
            && (a.V.U[1] == b.V.U[1]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) & 0x00FF) == 0x00FFu;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall IsNotEqual<Vector2U>(Vector2U a, Vector2U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0])
            || (a.V.U[1] != b.V.U[1]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) & 0x00FF) != 0x00FFu;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }
}


// =================================================================================================
//
// Bitwise testing functions.
//

namespace Graphyte::Maths
{
    template <>
    mathinline bool mathcall AllTrue<Vector2U>(Vector2U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            && (v.V.U[1] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x00FF) == 0x00FF;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AllFalse<Vector2U>(Vector2U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            && (v.V.U[1] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x00FF) == 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyTrue<Vector2U>(Vector2U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            || (v.V.U[1] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x00FF) != 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyFalse<Vector2U>(Vector2U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            || (v.V.U[1] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x00FF) != 0x00FF;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }
}
