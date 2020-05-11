#pragma once
#include <GxBase/Maths/Base.hxx>

// =================================================================================================
//
// Vector construction.
//

namespace Graphyte::Maths
{
    template <>
    mathinline Vector4U mathcall Make<Vector4U, uint32_t>(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                x, y, z, w,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
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
    mathinline Vector4U mathcall Replicate<Vector4U, uint32_t>(uint32_t value) noexcept
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
    mathinline Vector4U mathcall And<Vector4U>(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] & b.V.U[0],
                a.V.U[1] & b.V.U[1],
                a.V.U[2] & b.V.U[2],
                a.V.U[3] & b.V.U[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_and_si128(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const result = vandq_u32(a.V, b.V);
        return { result };
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector4U mathcall AndNot<Vector4U>(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] & ~b.V.U[0],
                a.V.U[1] & ~b.V.U[1],
                a.V.U[2] & ~b.V.U[2],
                a.V.U[3] & ~b.V.U[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_andnot_si128(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const result = vbicq_u32(a.V, b.V);
        return { result };
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector4U mathcall Or<Vector4U>(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] | b.V.U[0],
                a.V.U[1] | b.V.U[1],
                a.V.U[2] | b.V.U[2],
                a.V.U[3] | b.V.U[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_or_si128(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const result = vorrq_u32(a.V, b.V);
        return { result };
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector4U mathcall Xor(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] ^ b.V.U[0],
                a.V.U[1] ^ b.V.U[1],
                a.V.U[2] ^ b.V.U[2],
                a.V.U[3] ^ b.V.U[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_xor_si128(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const result = veorq_u32(a.V, b.V);
        return { result };
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector4U mathcall Nor(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                ~(a.V.U[0] | b.V.U[0]),
                ~(a.V.U[1] | b.V.U[1]),
                ~(a.V.U[2] | b.V.U[2]),
                ~(a.V.U[3] | b.V.U[3]),
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const partial = _mm_or_si128(a.V, b.V);
        __m128i const allbits = _mm_set1_epi32(-1);
        __m128i const result = _mm_andnot_si128(partial, allbits);
        return { result };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const partial = vorrq_u32(a.V, b.V);
        uint32x4_t const result = vmvnq_u32(partial);
        return { result };
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector4U mathcall Not(Vector4U x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                ~(a.V.U[0] | b.V.U[0]),
                ~(a.V.U[1] | b.V.U[1]),
                ~(a.V.U[2] | b.V.U[2]),
                ~(a.V.U[3] | b.V.U[3]),
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const allbits = _mm_set1_epi32(-1);
        __m128i const result = _mm_xor_si128(x.V, allbits);
        return { result };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const result = vmvnq_u32(a.V, b.V);
        return { result };
#else
#error Not supported
#endif
    }
}


// =================================================================================================
//
// Comparison masking functions
//

namespace Graphyte::Maths
{
    template <>
    mathinline Vector4U mathcall CompareEqual<Vector4U, Vector4U>(Vector4U a, Vector4U b) noexcept
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
        __m128i const result = _mm_cmpeq_epi32(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline Vector4U mathcall CompareNotEqual<Vector4U, Vector4U>(Vector4U a, Vector4U b) noexcept
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
        __m128i const result = _mm_andnot_si128(
            _mm_cmpeq_epi32(a.V, b.V),
            _mm_set1_epi32(~0)
        );
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
// Comparison logical functions
//

namespace Graphyte::Maths
{
    template <>
    mathinline bool mathcall IsEqual<Vector4U>(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0])
            && (a.V.U[1] == b.V.U[1])
            && (a.V.U[2] == b.V.U[2])
            && (a.V.U[3] == b.V.U[3]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask)) == 0xFFFFu;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall IsNotEqual<Vector4U>(Vector4U a, Vector4U b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0])
            || (a.V.U[1] != b.V.U[1])
            || (a.V.U[2] != b.V.U[2])
            || (a.V.U[3] != b.V.U[3]);
#elif GRAPHYTE_HW_AVX
        __m128i const mask = _mm_cmpeq_epi32(a.V, b.V);
        return (_mm_movemask_epi8(mask) != 0xFFFFu);
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
    mathinline bool mathcall AllTrue<Vector4U>(Vector4U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            && (v.V.U[1] != 0)
            && (v.V.U[2] != 0)
            && (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return movemask == 0xFFFF;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AllFalse<Vector4U>(Vector4U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            && (v.V.U[1] == 0)
            && (v.V.U[2] == 0)
            && (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return movemask == 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyTrue<Vector4U>(Vector4U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            || (v.V.U[1] != 0)
            || (v.V.U[2] != 0)
            || (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return movemask != 0;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }

    template <>
    mathinline bool mathcall AnyFalse<Vector4U>(Vector4U v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            || (v.V.U[1] == 0)
            || (v.V.U[2] == 0)
            || (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        int const movemask = _mm_movemask_epi8(v.V);
        return movemask != 0xFFFF;
#elif GRAPHYTE_HW_NEON
#error Not implemented
#else
#error Not supported
#endif
    }
}
