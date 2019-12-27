
    mathinline Vector2 mathcall Vector2::Refract(Vector2 incident, Vector2 normal, float refraction_index) noexcept
    {
        auto v_index = Vector4::Make(refraction_index);
        return Vector2::Refract(incident, normal, v_index);
    }

    mathinline Vector2 mathcall Vector2::Refract(Vector2 incident, Vector2 normal, Vector4 refraction_index) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_i_dot_n =
            (incident.V.F[0] * normal.V.F[0]) +
            (incident.V.F[1] * normal.V.F[1]);

        auto f_ry = 1.0F - f_i_dot_n;
        auto f_rx = 1.0F - (f_ry * refraction_index.V.F[0] * refraction_index.V.F[0]);
        f_ry = 1.0F - (f_ry * refraction_index.V.F[1] * refraction_index.V.F[1]);

        if (f_rx >= 0.0F)
        {
            f_rx = (refraction_index.V.F[0] * incident.V.F[0]) - (normal.V.F[0] * ((refraction_index.V.F[0] * f_i_dot_n) + sqrtf(f_rx)));
        }
        else
        {
            f_rx = 0.0F;
        }

        if (f_ry >= 0.0F)
        {
            f_ry = (refraction_index.V.F[1] * incident.V.F[1]) - (normal.V.F[1] * ((refraction_index.V.F[1] * f_i_dot_n) + sqrtf(f_ry)));
        }
        else
        {
            f_ry = 0.0F;
        }

        Detail::Vector4F32 v_result = { { {
                f_rx, f_ry, 0.0F, 0.0F
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_i_dot_n = Vector2::Dot(incident, normal).V;
        auto v_temp = _mm_mul_ps(v_i_dot_n, v_i_dot_n);
        v_temp = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_temp);
        v_temp = _mm_mul_ps(v_temp, refraction_index.V);
        v_temp = _mm_mul_ps(v_temp, refraction_index.V);
        v_temp = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_temp);

        auto v_mask = _mm_cmpgt_ps(v_temp, Detail::VEC4_ZERO_4.V);
        v_temp = _mm_sqrt_ps(v_temp);

        auto v_result = _mm_mul_ps(refraction_index.V, v_i_dot_n);
        v_temp = _mm_add_ps(v_temp, v_result);
        v_result = _mm_mul_ps(refraction_index.V, incident.V);
        v_temp = _mm_mul_ps(v_temp, normal.V);
        v_result = _mm_sub_ps(v_result, v_temp);
        v_result = _mm_and_ps(v_result, v_mask);
        return { v_result };
#endif
    }
    mathinline Vector4 mathcall Vector2::AngleBetweenNormalsEst(Vector2 n1, Vector2 n2) noexcept
    {
        auto v_result = Vector2::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACosEst(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector2::AngleBetweenNormals(Vector2 n1, Vector2 n2) noexcept
    {
        auto v_result = Vector2::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACos(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector2::AngleBetweenVectors(Vector2 v1, Vector2 v2) noexcept
    {
        auto v_l1 = Vector2::ReciprocalLength(v1);
        auto v_l2 = Vector2::ReciprocalLength(v2);
        auto v_dot = Vector2::Dot(v1, v2);
        v_l1 = Vector4::Multiply(v_l1, v_l2);

        auto v_cos_angle = Vector4::Multiply(v_dot, v_l1);
        v_cos_angle = Vector4::Clamp(v_cos_angle, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_cos_angle = Vector4::ACos(v_cos_angle);
        return v_cos_angle;
    }

    mathinline Vector4 mathcall Vector2::LinePointDistance(Vector2 line_point1, Vector2 line_point2, Vector2 point) noexcept
    {
        auto v_point_vector = Vector4::Subtract({ point.V }, { line_point1.V });
        auto v_line_vector = Vector4::Subtract({ line_point2.V }, { line_point1.V });

        auto v_length_sq = Vector2::LengthSquared({ v_line_vector.V });

        auto v_point_projection_scale = Vector2::Dot({ v_point_vector.V }, { v_line_vector.V });
        v_point_projection_scale = Vector4::Divide(v_point_projection_scale, v_length_sq);

        auto v_distance_vector = Vector4::Multiply(v_line_vector, v_point_projection_scale);
        v_distance_vector = Vector4::Subtract(v_point_vector, v_distance_vector);
        return Vector2::Length({ v_distance_vector.V });
    }

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
