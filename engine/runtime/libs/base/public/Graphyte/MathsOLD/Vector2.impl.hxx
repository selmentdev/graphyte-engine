    mathinline Vector4 mathcall Vector2::IntersectLine(Vector2 line1_point1, Vector2 line1_point2, Vector2 line2_point1, Vector2 line2_point2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_v1 = Vector4::Subtract({ line1_point2.V }, { line1_point1.V });
        auto v_v2 = Vector4::Subtract({ line2_point2.V }, { line2_point1.V });
        auto v_v3 = Vector4::Subtract({ line1_point1.V }, { line2_point1.V });

        auto v_c1 = Vector2::Cross({ v_v1.V }, { v_v2.V });
        auto v_c2 = Vector2::Cross({ v_v2.V }, { v_v3.V });

        auto v_zero = Vector4::Zero();

        Vector4 v_result;

        if (Vector2::IsEqual({ v_c1.V }, { v_zero.V }, { Detail::VEC4_EPSILON.V }))
        {
            if (Vector2::IsEqual({ v_c2.V }, { v_zero.V }, { Detail::VEC4_EPSILON.V }))
            {
                v_result = { Detail::VEC4_INFINITY.V };
            }
            else
            {
                v_result = { Detail::VEC4_QNAN.V };
            }
        }
        else
        {
            auto v_scale = Vector4::Reciprocal(v_c1);
            v_scale = Vector4::Multiply(v_c2, v_scale);
            v_result = Vector4::MultiplyAdd(v_v1, v_scale, { line1_point1.V });
        }

        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_v1 = _mm_sub_ps(line1_point2.V, line1_point1.V);
        auto v_v2 = _mm_sub_ps(line2_point2.V, line2_point1.V);
        auto v_v3 = _mm_sub_ps(line1_point1.V, line2_point1.V);

        auto v_c1 = Vector2::Cross({ v_v1 }, { v_v2 }).V;
        auto v_c2 = Vector2::Cross({ v_v2 }, { v_v3 }).V;

        auto v_result_mask = _mm_setzero_ps();
        v_result_mask = _mm_sub_ps(v_result_mask, v_c1);
        v_result_mask = _mm_max_ps(v_result_mask, v_c1);

        v_result_mask = _mm_cmpgt_ps(v_result_mask, Detail::VEC4_EPSILON.V);

        auto v_fail_mask = _mm_setzero_ps();
        v_fail_mask = _mm_sub_ps(v_fail_mask, v_c2);
        v_fail_mask = _mm_max_ps(v_fail_mask, v_c2);
        v_fail_mask = _mm_cmple_ps(v_fail_mask, Detail::VEC4_EPSILON.V);

        auto v_fail = _mm_and_ps(v_fail_mask, Detail::VEC4_INFINITY.V);
        v_fail_mask = _mm_andnot_ps(v_fail_mask, Detail::VEC4_QNAN.V);
        v_fail = _mm_or_ps(v_fail, v_fail_mask);

        auto v_result = _mm_div_ps(v_c2, v_c1);
        v_result = _mm_mul_ps(v_result, v_v1);
        v_result = _mm_add_ps(v_result, line1_point1.V);

        v_result = _mm_and_ps(v_result, v_result_mask);
        v_result_mask = _mm_andnot_ps(v_result_mask, v_fail);
        v_result = _mm_or_ps(v_result, v_result_mask);

        return { v_result };
#endif
    }
