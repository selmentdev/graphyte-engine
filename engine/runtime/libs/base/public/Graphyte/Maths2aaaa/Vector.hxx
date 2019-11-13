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

    }
}
