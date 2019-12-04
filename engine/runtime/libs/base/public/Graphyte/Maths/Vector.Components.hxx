#pragma once
#include <Graphyte/Maths/Types.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Maths/Impl/Simd.Consts.hxx>

// =================================================================================================
//
// Min / Max selection
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Min(T v1, T v2) noexcept
        requires (SimdVectorType<T> and SimdComparable<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                (v1.V.F[0] < v2.V.F[0]) ? v1.V.F[0] : v2.V.F[0],
                (v1.V.F[1] < v2.V.F[1]) ? v1.V.F[1] : v2.V.F[1],
                (v1.V.F[2] < v2.V.F[2]) ? v1.V.F[2] : v2.V.F[2],
                (v1.V.F[3] < v2.V.F[3]) ? v1.V.F[3] : v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_min_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Max(T v1, T v2) noexcept
        requires (SimdVectorType<T> and SimdComparable<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                (v1.V.F[0] > v2.V.F[0]) ? v1.V.F[0] : v2.V.F[0],
                (v1.V.F[1] > v2.V.F[1]) ? v1.V.F[1] : v2.V.F[1],
                (v1.V.F[2] > v2.V.F[2]) ? v1.V.F[2] : v2.V.F[2],
                (v1.V.F[3] > v2.V.F[3]) ? v1.V.F[3] : v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_max_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T result = Max<T>(min, v);
        result = Min<T>(max, result);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 v_result = _mm_max_ps(min.V, v.V);
        v_result = _mm_min_ps(max.V, v_result);
        return { v_result };
#endif
    }

    template <typename T>
    mathinline T mathcall Saturate(T v) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T zero = Zero<T>();
        return Clamp<T>(v, zero, { Impl::VEC4_ONE_4.V });
#elif GRAPHYTE_HW_AVX
        __m128 const v_result = _mm_max_ps(v.V, Impl::VEC4_ZERO_4.V);
        return { _mm_min_ps(v_result, Impl::VEC4_ONE_4.V) };
#endif
    }
}


// =================================================================================================
//
// Rounding functions
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Round(T v) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                RoundToNearest(v.V.F[0]),
                RoundToNearest(v.V.F[1]),
                RoundToNearest(v.V.F[2]),
                RoundToNearest(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
#endif
    }

    template <typename T>
    mathinline T mathcall Trunc(T v) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T result;

        result.V.F[0] = 0.0F;

        for (size_t index = 0; index < 4; ++index)
        {
            if (BitIsNaN(v.V.U[index]))
            {
                result.V.U[index] = 0x7FC00000U;
            }
            else if (fabsf(v.V.F[index]) < 8388608.0F)
            {
                result.V.F[index] = static_cast<float>(static_cast<int32_t>(v.V.F[index]));
            }
            else
            {
                result.V.F[index] = v.V.F[index];
            }
        }

        return result;
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
#endif
    }

    template <typename T>
    mathinline T mathcall Floor(T v) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                floorf(v.V.F[0]),
                floorf(v.V.F[1]),
                floorf(v.V.F[2]),
                floorf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_floor_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Ceil(T v) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                ceilf(v.V.F[0]),
                ceilf(v.V.F[1]),
                ceilf(v.V.F[2]),
                ceilf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_ceil_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Frac(T v) noexcept
        requires (SimdVectorType<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                v.V.F[0] - floorf(v.V.F[0]),
                v.V.F[1] - floorf(v.V.F[1]),
                v.V.F[2] - floorf(v.V.F[2]),
                v.V.F[3] - floorf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_floor_ps(v.V);
        __m128 const v_result = _mm_sub_ps(v.V, v_temp);
        return { v_result };
#endif
    }
}


// =================================================================================================
//
// Component selection
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Select(T v1, T v2, typename T::MaskType mask) noexcept
        requires (SimdVectorType<T> and SimdMaskType<T::MaskType>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { {
                (v1.V.U[0] & ~mask.V.U[0]) | (v2.V.U[0] & mask.V.U[0]),
                (v1.V.U[1] & ~mask.V.U[1]) | (v2.V.U[1] & mask.V.U[1]),
                (v1.V.U[2] & ~mask.V.U[2]) | (v2.V.U[2] & mask.V.U[2]),
                (v1.V.U[3] & ~mask.V.U[3]) | (v2.V.U[3] & mask.V.U[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_blendv_ps(v1.V, v2.V, mask.V) };
#endif
    }
}


// =================================================================================================
//
// Comparison operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline typename T::MaskType CompareEqual(T v1, T v2) noexcept
        requires (SimdVectorType<T> and SimdMaskType<T::MaskType> and (T::Components == T::MaskType::Components))
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
}


// =================================================================================================
//
// Component Splatting
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SplatX(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const x = v.V.F[0];
        Impl::Vec4F32 vresult = { { { x, x, x, x } } };
        return { vresult.V };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcastss_ps(v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0)) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatY(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const y = v.V.F[1];
        Impl::Vec4F32 v_result = { { { y, y, y, y } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1)) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatZ(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const z = v.V.F[2];
        Impl::Vec4F32 v_result = { { { z, z, z, z } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2)) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatW(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const w = v.V.F[3];
        Impl::Vec4F32 v_result = { { { w, w, w, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3)) };
#endif
    }
}


// =================================================================================================
//
// Getting float component by value
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline float mathcall GetX(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 0);
#endif
    }

    template <typename T>
    mathinline float mathcall GetY(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(v_temp);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 1);
#endif
    }

    template <typename T>
    mathinline float mathcall GetZ(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(v_temp);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 2);
#endif
    }

    template <typename T>
    mathinline float mathcall GetW(T v) noexcept
        requires (SimdVectorType<T> and T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(v_temp);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 3);
#endif
    }
}


// =================================================================================================
//
// Setting float component by value
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SetX(T v, float x) noexcept
        requires (SimdVectorType<T> and T::Components >= 1)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { x, v.V.F[1], v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(x);
        v_temp = _mm_move_ss(v.V, v_temp);
        return { v_temp };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(x, v.V, 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float y) noexcept
        requires (SimdVectorType<T> and T::Components >= 2)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], y, v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(y);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x10);
        return { v_temp };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(y, v.V, 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float z) noexcept
        requires (SimdVectorType<T> and T::Components >= 3)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], v.V.F[1], z, v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(z);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x20);
        return { v_temp };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(z, v.V, 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float w) noexcept
        requires (SimdVectorType<T> and T::Components >= 4)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], v.V.F[1], v.V.F[2], w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(w);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x30);
        return { v_temp };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(w, v.V, 3) };
#endif
    }
}


// =================================================================================================
//
// Permute operations
//

namespace Graphyte::Maths
{
#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    namespace Impl
    {
        template <uint32_t Shuffle, bool X, bool Y, bool Z, bool W> struct PermuteHelper final
        {
            static Vec4 mathcall Permute(Vec4 v1, Vec4 v2) noexcept
            {
                static const Impl::Vec4U32 select_mask = { { {
                        X ? 0xFFFFFFFFU : 0U,
                        Y ? 0xFFFFFFFFU : 0U,
                        Z ? 0xFFFFFFFFU : 0U,
                        W ? 0xFFFFFFFFU : 0U,
                    } } };

                __m128 const v_shuffled1 = _mm_permute_ps(v1.V, Shuffle);
                __m128 const v_shuffled2 = _mm_permute_ps(v2.V, Shuffle);
                __m128 const v_masked1 = _mm_andnot_ps(select_mask.V, v_shuffled1);
                __m128 const v_masked2 = _mm_and_ps(select_mask.V, v_shuffled2);
                return { _mm_or_ps(v_masked1, v_masked2) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, false, false, false, false>
        {
            static Vec4 mathcall Permute(Vec4 v1, [[maybe_unused]] Vec4 v2) noexcept
            {
                return { _mm_permute_ps(v1.V, Shuffle) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, true, true, true, true>
        {
            static Vec4 mathcall Permute([[maybe_unused]] Vec4 v1, Vec4 v2) noexcept
            {
                return { _mm_permute_ps(v2.V, Shuffle) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, false, false, true, true>
        {
            static Vec4 mathcall Permute(Vec4 v1, Vec4 v2) noexcept
            {
                return { _mm_shuffle_ps(v1.V, v2.V, Shuffle) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, true, true, false, false>
        {
            static Vec4 mathcall Permute(Vec4 v1, Vec4 v2) noexcept
            {
                return { _mm_shuffle_ps(v2.V, v1.V, Shuffle) };
            }
        };
    }
#endif

    template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
    mathinline Vec4 mathcall Permute(Vec4 v1, Vec4 v2) noexcept
    {
        static_assert(X <= 7, "X template parameter out of range");
        static_assert(Y <= 7, "Y template parameter out of range");
        static_assert(Z <= 7, "Z template parameter out of range");
        static_assert(W <= 7, "W template parameter out of range");

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
        constexpr uint32_t shuffle = _MM_SHUFFLE(W & 3, Z & 3, Y & 3, X & 3);
        constexpr bool x = X > 3;
        constexpr bool y = Y > 3;
        constexpr bool z = Z > 3;
        constexpr bool w = W > 3;
        return Impl::PermuteHelper<shuffle, x, y, z, w>::Permute(v1, v2);
#else
        return Permute(v1, v2, X, Y, Z, W);
#endif
    }


    template <> mathinline Vec4 mathcall Permute<0, 1, 2, 3>(Vec4 v1, [[maybe_unused]] Vec4 v2) noexcept
    {
        return v1;
    }

    template <> mathinline Vec4 mathcall Permute<4, 5, 6, 7>([[maybe_unused]] Vec4 v1, Vec4 v2) noexcept
    {
        return v2;
    }

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vec4 mathcall Permute<0, 1, 4, 5>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_movelh_ps(v1.V, v2.V) };
    }
    template <> mathinline Vec4 mathcall Permute<6, 7, 2, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_movehl_ps(v1.V, v2.V) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 4, 1, 5>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_unpacklo_ps(v1.V, v2.V) };
    }
    template <> mathinline Vec4 mathcall Permute<2, 6, 3, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_unpackhi_ps(v1.V, v2.V) };
    }
    template <> mathinline Vec4 mathcall Permute<2, 3, 6, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(v1.V), _mm_castps_pd(v2.V))) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 1, 2, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x1) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 5, 2, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x2) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 5, 2, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x3) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 1, 6, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x4) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 1, 6, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x5) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 5, 6, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x6) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 5, 6, 3>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x7) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 1, 2, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x8) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 1, 2, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x9) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 5, 2, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xA) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 5, 2, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xB) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 1, 6, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xC) };
    }
    template <> mathinline Vec4 mathcall Permute<4, 1, 6, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xD) };
    }
    template <> mathinline Vec4 mathcall Permute<0, 5, 6, 7>(Vec4 v1, Vec4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xE) };
    }
#endif

    mathinline Vec4 mathcall Permute(Vec4 v1, Vec4 v2, uint32_t permute_x, uint32_t permute_y, uint32_t permute_z, uint32_t permute_w) noexcept
    {
        GX_ASSERT((permute_x <= 7) && (permute_y <= 7) && (permute_z <= 7) && (permute_w <= 7));
        GX_COMPILER_ASSUME((permute_x <= 7) && (permute_y <= 7) && (permute_z <= 7) && (permute_w <= 7));

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
        static const Impl::Vec4U32 v_threes = { { { 3, 3, 3, 3 } } };

        alignas(16) uint32_t elements[4] = { permute_x, permute_y, permute_z, permute_w };
        __m128i v_control = _mm_load_si128(reinterpret_cast<const __m128i*>(&elements[0]));

        __m128i const v_select = _mm_cmpgt_epi32(v_control, _mm_castps_si128(v_threes.V));
        v_control = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(v_control), v_threes.V));

        __m128 const v_shuffled1 = _mm_permutevar_ps(v1.V, v_control);
        __m128 const v_shuffled2 = _mm_permutevar_ps(v2.V, v_control);

        __m128 const v_masked1 = _mm_andnot_ps(_mm_castsi128_ps(v_select), v_shuffled1);
        __m128 const v_masked2 = _mm_and_ps(_mm_castsi128_ps(v_select), v_shuffled2);

        return { _mm_or_ps(v_masked1, v_masked2) };
#else
        const uint32_t* mem_ptr[2];
        mem_ptr[0] = reinterpret_cast<const uint32_t*>(&v1.V);
        mem_ptr[1] = reinterpret_cast<const uint32_t*>(&v2.V);

        Vec4 result;
        uint32_t* work_ptr = reinterpret_cast<uint32_t*>(&result.V);

        size_t const i0 = permute_x & 3;
        size_t const e0 = permute_x >> 2;
        work_ptr[0] = mem_ptr[e0][i0];

        size_t const i1 = permute_y & 3;
        size_t const e1 = permute_y >> 2;
        work_ptr[1] = mem_ptr[e1][i1];

        size_t const i2 = permute_z & 3;
        size_t const e2 = permute_z >> 2;
        work_ptr[2] = mem_ptr[e2][i2];

        size_t const i3 = permute_w & 3;
        size_t const e3 = permute_w >> 2;
        work_ptr[3] = mem_ptr[e3][i3];

        return result;
#endif
    }
}


// =================================================================================================
//
// Swizzle operations
//

namespace Graphyte::Maths
{
    mathinline Vec4 mathcall Swizzle(
        Vec4 v,
        uint32_t element0,
        uint32_t element1,
        uint32_t element2,
        uint32_t element3
    ) noexcept
    {
        GX_ASSERT((element0 < 4) && (element1 < 4) && (element2 < 4) && (element3 < 4));
        GX_COMPILER_ASSUME((element0 < 4) && (element1 < 4) && (element2 < 4) && (element3 < 4));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { v.V.F[element0], v.V.F[element1], v.V.F[element2], v.V.F[element3] } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        uint32_t elements[4] = {
            element0,
            element1,
            element2,
            element3
        };
        __m128i const v_control = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&elements[0]));
        return { _mm_permutevar_ps(v.V, v_control) };
#else
        uint32_t const* mem_ptr = reinterpret_cast<uint32_t const*>(&v.V);

        Vec4 result;
        uint32_t* work_ptr = reinterpret_cast<uint32_t*>(&result.V);

        work_ptr[0] = mem_ptr[element0];
        work_ptr[1] = mem_ptr[element1];
        work_ptr[2] = mem_ptr[element2];
        work_ptr[3] = mem_ptr[element3];

        return { result.V };
#endif
    }

    template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
    mathinline Vec4 mathcall Swizzle(Vec4 v) noexcept
    {
        static_assert(X <= 3, "X out of range");
        static_assert(Y <= 3, "Y out of range");
        static_assert(Z <= 3, "Z out of range");
        static_assert(W <= 3, "W out of range");

#if GRAPHYTE_MATH_NO_INTRINSICS
        return Swizzle(v, X, Y, Z, W);
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(W, Z, Y, X)) };
#endif
    }

    template <> mathinline Vec4 mathcall Swizzle<0, 1, 2, 3>(Vec4 v) noexcept
    {
        return v;
    }

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vec4 mathcall Swizzle<0, 1, 0, 1>(Vec4 v) noexcept
    {
        return { _mm_movelh_ps(v.V, v.V) };
    }
    template <> mathinline Vec4 mathcall Swizzle<2, 3, 2, 3>(Vec4 v) noexcept
    {
        return { _mm_movehl_ps(v.V, v.V) };
    }

    template <> mathinline Vec4 mathcall Swizzle<0, 0, 1, 1>(Vec4 v) noexcept
    {
        return { _mm_unpacklo_ps(v.V, v.V) };
    }
    template <> mathinline Vec4 mathcall Swizzle<2, 2, 3, 3>(Vec4 v) noexcept
    {
        return { _mm_unpackhi_ps(v.V, v.V) };
    }
    template <> mathinline Vec4 mathcall Swizzle<0, 0, 2, 2>(Vec4 v) noexcept
    {
        return { _mm_moveldup_ps(v.V) };
    }
    template <> mathinline Vec4 mathcall Swizzle<1, 1, 3, 3>(Vec4 v) noexcept
    {
        return { _mm_movehdup_ps(v.V) };
    }
#endif

#if GRAPHYTE_HW_AVX2 && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vec4 mathcall Swizzle<0, 0, 0, 0>(Vec4 v) noexcept
    {
        return { _mm_broadcastss_ps(v.V) };
    }
#endif

    template <SwizzleMask Mask>
    mathinline Vec4 mathcall Swizzle(Vec4 v) noexcept
    {
        return Swizzle<
            (static_cast<uint32_t>(Mask) >> 0) & 3,
            (static_cast<uint32_t>(Mask) >> 2) & 3,
            (static_cast<uint32_t>(Mask) >> 4) & 3,
            (static_cast<uint32_t>(Mask) >> 6) & 3>(v);
    }

}

