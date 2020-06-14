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
    mathinline Vector1U mathcall Make<Vector1U, uint32_t>(uint32_t x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            x,
            0,
            0,
            0,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set_epi32(
            static_cast<int>(0),
            static_cast<int>(0),
            static_cast<int>(0),
            static_cast<int>(x));
        return { result };
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector1U mathcall Replicate<Vector1U, uint32_t>(uint32_t value) noexcept
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
    mathinline Vector1U mathcall And<Vector1U>(Vector1U a, Vector1U b) noexcept
    {
        return { And<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector1U mathcall AndNot<Vector1U>(Vector1U a, Vector1U b) noexcept
    {
        return { AndNot<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector1U mathcall Or<Vector1U>(Vector1U a, Vector1U b) noexcept
    {
        return { Or<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector1U mathcall Xor(Vector1U a, Vector1U b) noexcept
    {
        return { Xor<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector1U mathcall Nor(Vector1U a, Vector1U b) noexcept
    {
        return { Nor<Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector1U mathcall Not(Vector1U x) noexcept
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
    mathinline Vector1U mathcall CompareEqual<Vector1U, Vector1U>(Vector1U a, Vector1U b) noexcept
    {
        return { CompareEqual<Vector4U, Vector4U>({ a.V }, { b.V }).V };
    }

    template <>
    mathinline Vector1U mathcall CompareNotEqual<Vector1U, Vector1U>(Vector1U a, Vector1U b) noexcept
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
    mathinline bool mathcall IsEqual<Vector1U>(Vector1U a, Vector1U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) & 0x000F) == 0x000Fu;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall IsNotEqual<Vector1U>(Vector1U a, Vector1U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) & 0x000F) != 0x000Fu;
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
    mathinline bool mathcall AllTrue<Vector1U>(Vector1U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x000F) == 0x000F;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AllFalse<Vector1U>(Vector1U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x000F) == 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyTrue<Vector1U>(Vector1U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x000F) != 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyFalse<Vector1u>(Vector1U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x000F) != 0x000F;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }
}
