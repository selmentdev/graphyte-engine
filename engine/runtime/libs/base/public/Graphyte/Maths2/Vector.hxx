#pragma once
#include <Graphyte/Maths2/Consts.hxx>


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
        const auto y = v.V.F[1];
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
        const auto z = v.V.F[2];
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
        const auto w = v.V.F[3];
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
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 2);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    template <typename T>
    mathinline float mathcall GetZ(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 3);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    template <typename T>
    mathinline float mathcall GetW(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, float x) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 1);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { x, v.V.F[1], v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(x);
        v_temp = _mm_move_ss(v.V, v_temp);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float y) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 2);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], y, v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(y);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x10);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float z) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 3);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], v.V.F[1], z, v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(z);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x20);
        return { v_temp };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float w) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(T::Components >= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_temp = { { { v.V.F[0], v.V.F[1], v.V.F[2], w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(w);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x30);
        return { v_temp };
#endif
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Sum(T v) noexcept
    {
        static_assert(VectorType<T>);
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
        static_assert(0 < T::Components && T::Components <= 4);

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
        static_assert(0 < T::Components && T::Components <= 4);

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
        static_assert(0 < T::Components && T::Components <= 4);

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
        static_assert(0 < T::Components && T::Components <= 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { {
            v.V.F[0] * s,
            v.V.F[1] * s,
            v.V.F[2] * s,
            v.V.F[3] * s,
        } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_set_ps1(s);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Div(T v1, T v2) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(0 < T::Components && T::Components <= 4);

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
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(0 < T::Components && T::Components <= 4);

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

    // (v1 * v2) - v3
    template <typename T>
    mathinline T mathcall MulSub(T v1, T v2, T v3) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(0 < T::Components && T::Components <= 4);

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

    // -(v1 * v2) + v3
    template <typename T>
    mathinline T mathcall NegMulAdd(T v1, T v2, T v3) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(0 < T::Components && T::Components <= 4);

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

    // -(v1 * v2) - v3
    template <typename T>
    mathinline T mathcall NegMulSub(T v1, T v2, T v3) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(0 < T::Components && T::Components <= 4);

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

namespace Graphyte::Maths
{
    template <typename T>
    mathinline void Store(Float4A* destination, T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(T::Components <= 4);

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
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Sqrt(T v) noexcept
    {
        static_assert(VectorType<T>);
        static_assert(!GeometricVectorType<T>);
        static_assert(0 < T::Components && T::Components <= 4);

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
        auto v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
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
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
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
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }


    mathinline Vec4 mathcall Normalize(Vec4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto length = Length(v).V.F[0];
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
        auto v_length_sq = _mm_dp_ps(v.V, v.V, 0xff);
        auto v_result = _mm_sqrt_ps(v_length_sq);
        auto v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Impl::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        auto v_temp1 = _mm_andnot_ps(v_length_sq, Impl::VEC4_QNAN.V);
        auto v_temp2 = _mm_and_ps(v_result, v_length_sq);
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
        auto v_length_sq = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        auto v_result = _mm_sqrt_ps(v_length_sq);
        auto v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Impl::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        auto v_temp1 = _mm_andnot_ps(v_length_sq, Impl::VEC4_QNAN.V);
        auto v_temp2 = _mm_and_ps(v_result, v_length_sq);
        v_result = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }

    mathinline Vec2 mathcall Normalize(Vec2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_length = Vector2::Length(v).V.F[0];

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
        auto v_length_sq = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        auto v_result = _mm_sqrt_ps(v_length_sq);
        auto v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Impl::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        auto v_temp1 = _mm_andnot_ps(v_length_sq, Impl::VEC4_QNAN.V);
        auto v_temp2 = _mm_and_ps(v_result, v_length_sq);
        v_result = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }
}
