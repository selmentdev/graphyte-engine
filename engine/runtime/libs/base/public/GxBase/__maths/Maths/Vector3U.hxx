namespace Graphyte::Maths
{
    template <>
    mathinline bool mathcall IsEqual<Vector3U>(Vector3U a, Vector3U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0])
               && (a.V.U[1] == b.V.U[1])
               && (a.V.U[2] == b.V.U[2]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) & 0x0FFF) == 0x0FFFu;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall IsNotEqual<Vector3U>(Vector3U a, Vector3U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0])
               || (a.V.U[1] != b.V.U[1])
               || (a.V.U[2] != b.V.U[2]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) & 0x0FFF) != 0x0FFFu;
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
    mathinline bool mathcall AllTrue<Vector3U>(Vector3U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
               && (v.V.U[1] != 0)
               && (v.V.U[2] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x0FFF) == 0x0FFF;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AllFalse<Vector3U>(Vector3U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
               && (v.V.U[1] == 0)
               && (v.V.U[2] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x0FFF) == 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyTrue<Vector3U>(Vector3U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
               || (v.V.U[1] != 0)
               || (v.V.U[2] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x0FFF) != 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyFalse<Vector3U>(Vector3U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
               || (v.V.U[1] == 0)
               || (v.V.U[2] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return (movemask & 0x0FFF) != 0x0FFF;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }
}
