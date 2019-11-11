#pragma once
#include <Graphyte/Maths2/Consts.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Maths/Scalar.hxx>


//
// Common constructors.
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Make(float value) noexcept
    {
        static_assert(Impl::IsVector<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y) noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 2);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, 0.0F, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z) noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 3);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, z, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, z, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z, float w) noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components == 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#endif
    }

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


//
// Accessing vector members.
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SplatX(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 1);

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
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 2);

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
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 3);

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
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const w = v.V.F[3];
        Impl::Vec4F32 v_result = { { { w, w, w, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3)) };
#endif
    }
}


namespace Graphyte::Maths
{
    template <typename T>
    mathinline float mathcall GetX(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 1);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#endif
    }

    template <typename T>
    mathinline float mathcall GetY(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 2);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    template <typename T>
    mathinline float mathcall GetZ(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 3);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    template <typename T>
    mathinline float mathcall GetW(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, float x) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 1);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { x, v.V.F[1], v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(x);
        v_temp = _mm_move_ss(v.V, v_temp);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float y) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 2);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], y, v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(y);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x10);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float z) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 3);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], v.V.F[1], z, v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(z);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x20);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float w) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], v.V.F[1], v.V.F[2], w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_temp = _mm_set_ss(w);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x30);
        return { v_temp };
#endif
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Min(T v1, T v2) noexcept
    {
        static_assert(Maths::VectorType<T>);

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
    {
        static_assert(Maths::VectorType<T>);

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
    mathinline T mathcall Round(T v) noexcept
    {
        static_assert(Maths::VectorType<T>);

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
    mathinline T mathcall Truncate(T v) noexcept
    {
        static_assert(Maths::VectorType<T>);

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
    {
        static_assert(Maths::VectorType<T>);

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
    mathinline T mathcall Ceiling(T v) noexcept
    {
        static_assert(Maths::VectorType<T>);

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
    {
        static_assert(Maths::VectorType<T>);

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


    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
    {
        static_assert(Maths::VectorType<T>);

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
    {
        static_assert(Maths::VectorType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        T zero = Zero<T>();
        return Clamp<T>(v, zero, { Impl::VEC4_ONE_4.V });
#elif GRAPHYTE_HW_AVX
        __m128 const v_result = _mm_max_ps(v.V, Impl::VEC4_ZERO_4.V);
        return { _mm_min_ps(v_result, Impl::VEC4_ONE_4.V) };
#endif
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Neg(T v) noexcept
    {
        static_assert(VectorType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                -v.V.F[0],
                -v.V.F[1],
                -v.V.F[2],
                -v.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_zero = _mm_setzero_ps();
        return { _mm_sub_ps(v_zero, v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Sum(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!Maths::MaskableType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components == 4);


#if GRAPHYTE_MATH_NO_INTRINSICS
        return Make<T>(v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const vhalf1 = _mm_hadd_ps(v.V, v.V);
        __m128 const vhalf2 = _mm_hadd_ps(vhalf1, vhalf1);
        return { _mm_permute_ps(vhalf2, _MM_SHUFFLE(0, 0, 0, 0)) };
#endif
    }

    template <typename T>
    mathinline T mathcall Add(T v1, T v2) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] + v2.V.F[0],
            v1.V.F[1] + v2.V.F[1],
            v1.V.F[2] + v2.V.F[2],
            v1.V.F[3] + v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_add_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Sub(T v1, T v2) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] - v2.V.F[0],
            v1.V.F[1] - v2.V.F[1],
            v1.V.F[2] - v2.V.F[2],
            v1.V.F[3] - v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Mul(T v1, T v2) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] * v2.V.F[0],
            v1.V.F[1] * v2.V.F[1],
            v1.V.F[2] * v2.V.F[2],
            v1.V.F[3] * v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Mul(T v, float s) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
            v.V.F[0] * s,
            v.V.F[1] * s,
            v.V.F[2] * s,
            v.V.F[3] * s,
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_result = _mm_set_ps1(s);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Div(T v1, T v2) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { {
            v1.V.F[0] / v2.V.F[0],
            v1.V.F[1] / v2.V.F[1],
            v1.V.F[2] / v2.V.F[2],
            v1.V.F[3] / v2.V.F[3],
        } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(v1.V, v2.V) };
#endif
    }

    // (v1 * v2) + v3
    template <typename T>
    mathinline T mathcall MulAdd(T v1, T v2, T v3) noexcept
    {
        if constexpr (std::is_arithmetic_v<T>)
        {
            return (v1 * v2) + v3;
        }
        else
        {
            static_assert(VectorType<T>);
            static_assert(!GeometricVectorType<T>);
            static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::Vec4F32 v_result = { { {
                    (v1.V.F[0] * v2.V.F[0]) + v3.V.F[0],
                    (v1.V.F[1] * v2.V.F[1]) + v3.V.F[1],
                    (v1.V.F[2] * v2.V.F[2]) + v3.V.F[2],
                    (v1.V.F[3] * v2.V.F[3]) + v3.V.F[3],
                } } };
            return { v_result.V };
#elif GRAPHYTE_HW_AVX
            return { _mm_fmadd_ps(v1.V, v2.V, v3.V) };
#endif
        }
    }

    // (v1 * v2) - v3
    template <typename T>
    mathinline T mathcall MulSub(T v1, T v2, T v3) noexcept
    {
        if constexpr (std::is_arithmetic_v<T>)
        {
            return (v1 * v2) - v3;
        }
        else
        {
            static_assert(VectorType<T>);
            static_assert(!GeometricVectorType<T>);
            static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::Vec4F32 v_result = { { {
                    (v1.V.F[0] * v2.V.F[0]) - v3.V.F[0],
                    (v1.V.F[1] * v2.V.F[1]) - v3.V.F[1],
                    (v1.V.F[2] * v2.V.F[2]) - v3.V.F[2],
                    (v1.V.F[3] * v2.V.F[3]) - v3.V.F[3],
                } } };
            return { v_result.V };
#elif GRAPHYTE_HW_AVX
            return { _mm_fmsub_ps(v1.V, v2.V, v3.V) };
#endif
        }
    }

    // -(v1 * v2) + v3
    template <typename T>
    mathinline T mathcall NegMulAdd(T v1, T v2, T v3) noexcept
    {
        if constexpr (std::is_arithmetic_v<T>)
        {
            return -(v1 * v2) + v3;
        }
        else
        {
            static_assert(VectorType<T>);
            static_assert(!GeometricVectorType<T>);
            static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::Vec4F32 v_result = { { {
                    v3.V.F[0] - (v1.V.F[0] * v2.V.F[0]),
                    v3.V.F[1] - (v1.V.F[1] * v2.V.F[1]),
                    v3.V.F[2] - (v1.V.F[2] * v2.V.F[2]),
                    v3.V.F[3] - (v1.V.F[3] * v2.V.F[3]),
                } } };
            return { v_result.V };
#elif GRAPHYTE_HW_AVX
            return { _mm_fnmadd_ps(v1.V, v2.V, v3.V) };
#endif
        }
    }

    // -(v1 * v2) - v3
    template <typename T>
    mathinline T mathcall NegMulSub(T v1, T v2, T v3) noexcept
    {
        if constexpr (std::is_arithmetic_v<T>)
        {
            return -(v1 * v2) - v3;
        }
        else
        {
            static_assert(VectorType<T>);
            static_assert(!GeometricVectorType<T>);
            static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::Vec4F32 v_result = { { {
                    -v3.V.F[0] - (v1.V.F[0] * v2.V.F[0]),
                    -v3.V.F[1] - (v1.V.F[1] * v2.V.F[1]),
                    -v3.V.F[2] - (v1.V.F[2] * v2.V.F[2]),
                    -v3.V.F[3] - (v1.V.F[3] * v2.V.F[3]),
                } } };
            return { v_result.V };
#elif GRAPHYTE_HW_AVX
            return { _mm_fnmsub_ps(v1.V, v2.V, v3.V) };
#endif
        }
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline void Store(Float4A* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T Load(Float4A const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 vresult = { { {
                source->X,
                source->Y,
                source->Z,
                source->W,
        } } };
        return { vresult.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps(reinterpret_cast<float*>(source)) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3A* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(&destination->Z, v_z);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3A const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_v = _mm_load_ps(&source->X);
        return { _mm_and_ps(v_v, Impl::VEC4_MASK_COMPONENTS_3.V) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2A* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2A const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(source));
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    template <typename T>
    mathinline void Store(Float4* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T Load(Float4 const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 vresult = { { {
                source->X,
                source->Y,
                source->Z,
                source->W,
        } } };
        return { vresult.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_loadu_ps(reinterpret_cast<float*>(source)) };
#endif
    }

    template <typename T>
    mathinline void Store(Float3* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
        _mm_store_ss(&destination->Z, v_z);
#endif

    }

    template <typename T>
    mathinline T Load(Float3 const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        __m128 const v_z = _mm_load_ss(&source->Z);
        __m128 const v_xy = _mm_unpacklo_ps(v_x, v_y);
        return { _mm_movelh_ps(v_xy, v_z) };
#endif
    }

    template <typename T>
    mathinline void Store(Float2* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
#endif
    }

    template <typename T>
    mathinline T Load(Float2 const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        return { _mm_unpacklo_ps(v_x, v_y) };
#endif
    }

    template <typename T>
    mathinline void Store(float* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = GetX(v);
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(destination, v.V);
#endif
    }

    template <typename T>
    mathinline T Load(float const* source) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        T v_result;
        v_result.V.F[0] = source[0];
        v_result.V.F[1] = 0.0F;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ss(source) };
#endif
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Sqrt(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }
}

namespace Graphyte::Maths
{
    mathinline Vec4 mathcall Dot(Vec4 v1, Vec4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const dot =
            v1.V.F[0] * v2.V.F[0] +
            v1.V.F[1] * v2.V.F[1] +
            v1.V.F[2] * v2.V.F[2] +
            v1.V.F[3] * v2.V.F[3];

        Impl::Vec4F32 v_result = { { { dot, dot, dot, dot } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(v1.V, v2.V, 0xFF) };
#endif
    }

    mathinline Vec4 mathcall Dot(Vec3 v1, Vec3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const f_dot =
            v1.V.F[0] * v2.V.F[0] +
            v1.V.F[1] * v2.V.F[1] +
            v1.V.F[2] * v2.V.F[2];

        Impl::Vec4F32 v_result = { { { f_dot, f_dot, f_dot, f_dot, } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(v1.V, v2.V, 0b0111'1111) };
#endif
    }

    mathinline Vec4 mathcall Dot(Vec2 v1, Vec2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const f_dot = (v1.V.F[0] * v2.V.F[0]) + (v1.V.F[1] * v2.V.F[1]);

        Impl::Vec4F32 v_result = { { { f_dot, f_dot, f_dot, f_dot } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(v1.V, v2.V, 0b0011'1111) };
#endif
    }

    mathinline Vec4 mathcall LengthSquared(Vec4 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vec4 mathcall LengthSquared(Vec3 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vec4 mathcall LengthSquared(Vec2 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vec4 mathcall Length(Vec4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vec4 v_result = LengthSquared(v);
        v_result = Sqrt(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vec4 mathcall Length(Vec3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vec4 v_result = LengthSquared(v);
        v_result = Sqrt(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vec4 mathcall Length(Vec2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vec4 v_result = LengthSquared(v);
        v_result = Sqrt(v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }


    mathinline Vec4 mathcall Normalize(Vec4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = Length(v).V.F[0];

        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Impl::Vec4F32 v_result = { { {
                v.V.F[0] * length,
                v.V.F[1] * length,
                v.V.F[2] * length,
                v.V.F[3] * length,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_length_sq = _mm_dp_ps(v.V, v.V, 0xff);
        __m128 v_result = _mm_sqrt_ps(v_length_sq);
        __m128 v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Impl::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        __m128 v_temp1 = _mm_andnot_ps(v_length_sq, Impl::VEC4_QNAN.V);
        __m128 v_temp2 = _mm_and_ps(v_result, v_length_sq);
        v_result = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }

    mathinline Vec3 mathcall Normalize(Vec3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float f_length = Length(v).V.F[0];

        if (f_length > 0.0F)
        {
            f_length = 1.0F / f_length;
        }

        Impl::Vec4F32 v_result = { { {
                v.V.F[0] * f_length,
                v.V.F[1] * f_length,
                v.V.F[2] * f_length,
                v.V.F[3] * f_length,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_length_sq = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        __m128 v_result = _mm_sqrt_ps(v_length_sq);
        __m128 v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Impl::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        __m128 v_temp1 = _mm_andnot_ps(v_length_sq, Impl::VEC4_QNAN.V);
        __m128 v_temp2 = _mm_and_ps(v_result, v_length_sq);
        v_result = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }

    mathinline Vec2 mathcall Normalize(Vec2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = Length(v).V.F[0];

        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Impl::Vec4F32 v_result = { { {
                v.V.F[0] * length,
                v.V.F[1] * length,
                v.V.F[2] * length,
                v.V.F[3] * length,
            } } };
        return { v_result.V };

#elif GRAPHYTE_HW_AVX
        __m128 v_length_sq = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        __m128 v_result = _mm_sqrt_ps(v_length_sq);
        __m128 v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Impl::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        __m128 v_temp1 = _mm_andnot_ps(v_length_sq, Impl::VEC4_QNAN.V);
        __m128 v_temp2 = _mm_and_ps(v_result, v_length_sq);
        v_result = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }

    // TODO: Move to Quat.hxx
    mathinline Vec4 Length(Quat v) noexcept
    {
        return Length(ToVec4(v));
    }
}


namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Abs(T v) noexcept
    {
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
                fabsf(v.V.F[0]),
                fabsf(v.V.F[1]),
                fabsf(v.V.F[2]),
                fabsf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        __m128 v_result = _mm_setzero_ps();
        v_result = _mm_sub_ps(v_result, v.V);
        v_result = _mm_max_ps(v_result, v.V);
        return { v_result };
#endif
    }
}


//
// Comparison
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline auto mathcall CmpEq(T v1, T v2) noexcept -> typename T::MaskType
    {
        static_assert(Maths::EqualComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

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

    template <typename T>
    mathinline auto mathcall CmpEqEps(T v1, T v2, Vec4 epsilon) noexcept -> typename T::MaskType
    {
        static_assert(Maths::EqualComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float delta_x = (v1.V.F[0] - v2.V.F[0]);
        float delta_y = (v1.V.F[1] - v2.V.F[1]);
        float delta_z = (v1.V.F[2] - v2.V.F[2]);
        float delta_w = (v1.V.F[3] - v2.V.F[3]);

        delta_x = fabsf(delta_x);
        delta_y = fabsf(delta_y);
        delta_z = fabsf(delta_z);
        delta_w = fabsf(delta_w);

        Impl::Vec4U32 v_control = { { {
                (delta_x <= epsilon.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (delta_y <= epsilon.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (delta_z <= epsilon.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (delta_w <= epsilon.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_delta = _mm_sub_ps(v1.V, v2.V);
        __m128 v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline auto mathcall CmpNeq(T v1, T v2) noexcept -> typename T::MaskType
    {
        static_assert(Maths::EqualComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] != v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] != v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] != v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] != v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline auto mathcall CmpLt(T v1, T v2) noexcept -> typename T::MaskType
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] < v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] < v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] < v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] < v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmplt_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline auto mathcall CmpLe(T v1, T v2) noexcept -> typename T::MaskType
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] <= v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] <= v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] <= v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] <= v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmple_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline auto mathcall CmpGt(T v1, T v2) noexcept -> typename T::MaskType
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] > v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] > v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] > v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] > v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpgt_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline auto mathcall CmpGe(T v1, T v2) noexcept -> typename T::MaskType
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_control = { { {
                (v1.V.F[0] >= v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] >= v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] >= v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] >= v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpge_ps(v1.V, v2.V) };
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEq(T v1, T v2) noexcept
    {
        static_assert(Maths::EqualComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] == v2.V.F[0]) &&
            (v1.V.F[1] == v2.V.F[1]) &&
            (v1.V.F[2] == v2.V.F[2]) &&
            (v1.V.F[3] == v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqEps(T v1, T v2, Vec4 epsilon) noexcept
    {
        static_assert(Maths::EqualComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const dx = fabsf(v1.V.F[0] - v2.V.F[0]);
        float const dy = fabsf(v1.V.F[1] - v2.V.F[1]);
        float const dz = fabsf(v1.V.F[2] - v2.V.F[2]);
        float const dw = fabsf(v1.V.F[3] - v2.V.F[3]);

        return
            (dx <= epsilon.V.F[0]) &&
            (dy <= epsilon.V.F[1]) &&
            (dz <= epsilon.V.F[2]) &&
            (dw <= epsilon.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_delta = _mm_sub_ps(v1.V, v2.V);
        __m128 v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNeq(T v1, T v2) noexcept
    {
        static_assert(Maths::EqualComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] != v2.V.F[0]) ||
            (v1.V.F[1] != v2.V.F[1]) ||
            (v1.V.F[2] != v2.V.F[2]) ||
            (v1.V.F[3] != v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpneq_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) != 0b0000;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLt(T v1, T v2) noexcept
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] < v2.V.F[0]) &&
            (v1.V.F[1] < v2.V.F[1]) &&
            (v1.V.F[2] < v2.V.F[2]) &&
            (v1.V.F[3] < v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmplt_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLe(T v1, T v2) noexcept
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] <= v2.V.F[0]) &&
            (v1.V.F[1] <= v2.V.F[1]) &&
            (v1.V.F[2] <= v2.V.F[2]) &&
            (v1.V.F[3] <= v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmple_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGt(T v1, T v2) noexcept
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] > v2.V.F[0]) &&
            (v1.V.F[1] > v2.V.F[1]) &&
            (v1.V.F[2] > v2.V.F[2]) &&
            (v1.V.F[3] > v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpgt_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGe(T v1, T v2) noexcept
    {
        static_assert(Maths::OrderComparable<T>);
        static_assert(Maths::VectorType<T>);
        static_assert(!Maths::MaskableType<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] >= v2.V.F[0]) &&
            (v1.V.F[1] >= v2.V.F[1]) &&
            (v1.V.F[2] >= v2.V.F[2]) &&
            (v1.V.F[3] >= v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const v_temp = _mm_cmpge_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Select(T v1, T v2, typename T::MaskType mask) noexcept
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
#if true
        return { _mm_blendv_ps(v1.V, v2.V, mask.V) };
#else
        __m128 const v_temp1 = _mm_andnot_ps(control.V, v1.V);
        __m128 const v_temp2 = _mm_and_ps(v2.V, control.V);
        return { _mm_or_ps(v_temp1, v_temp2) };
#endif
#endif
    }
}

// =================================================================================================
//
// Swizzling.
//

namespace Graphyte::Maths
{
    mathinline Vec4 mathcall Swizzle(Vec4 v, uint32_t element0, uint32_t element1, uint32_t element2, uint32_t element3) noexcept
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
