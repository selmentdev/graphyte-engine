
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
