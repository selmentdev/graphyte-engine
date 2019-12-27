    mathinline Vector3 mathcall Vector3::Reflect(Vector3 incident, Vector3 normal) noexcept
    {
        auto v_result = Vector3::Dot(incident, normal);
        v_result = Vector4::Add(v_result, v_result);
        v_result = Vector4::NegativeMultiplySubtract(v_result, { normal.V }, { incident.V });
        return { v_result.V };
    }

    mathinline Vector3 mathcall Vector3::Refract(Vector3 incident, Vector3 normal, float refraction_index) noexcept
    {
        auto v_index = Vector4::Make(refraction_index);
        return Vector3::Refract(incident, normal, v_index);
    }

    mathinline Vector3 mathcall Vector3::Refract(Vector3 incident, Vector3 normal, Vector4 refraction_index) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_zero = Vector4::Zero();
        auto v_i_dot_n = Vector3::Dot(incident, normal);

        auto v_r = Vector4::NegativeMultiplySubtract(v_i_dot_n, v_i_dot_n, { Detail::VEC4_ONE_4.V });
        v_r = Vector4::Multiply(v_r, refraction_index);
        v_r = Vector4::NegativeMultiplySubtract(v_r, refraction_index, { Detail::VEC4_ONE_4.V });

        if (Vector4::IsLessEqual(v_r, v_zero))
        {
            return { v_zero.V };
        }
        else
        {
            v_r = Vector4::Sqrt(v_r);
            v_r = Vector4::MultiplyAdd(refraction_index, v_i_dot_n, v_r);

            auto v_result = Vector4::Multiply(refraction_index, { incident.V });
            v_result = Vector4::NegativeMultiplySubtract({ normal.V }, v_r, v_result);
            return { v_result.V };
        }
#elif GRAPHYTE_HW_AVX
        auto v_i_dot_n = Vector3::Dot(incident, normal).V;
        auto v_r       = _mm_mul_ps(v_i_dot_n, v_i_dot_n);
        v_r            = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_r);
        v_r            = _mm_mul_ps(v_r, refraction_index.V);
        v_r            = _mm_mul_ps(v_r, refraction_index.V);
        v_r            = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_r);

        auto v_result  = _mm_cmple_ps(v_r, Detail::VEC4_ZERO_4.V);

        if (_mm_movemask_ps(v_result) == 0b1111)
        {
            v_result = Detail::VEC4_ZERO_4.V;
        }
        else
        {
            v_r      = _mm_sqrt_ps(v_r);
            v_result = _mm_mul_ps(refraction_index.V, v_i_dot_n);
            v_r      = _mm_add_ps(v_r, v_result);
            v_result = _mm_mul_ps(refraction_index.V, incident.V);
            v_r      = _mm_mul_ps(v_r, normal.V);
            v_result = _mm_sub_ps(v_result, v_r);
        }

        return { v_result };
#endif
    }
    mathinline Vector4 mathcall Vector3::AngleBetweenNormalsEst(Vector3 n1, Vector3 n2) noexcept
    {
        auto v_result = Vector3::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACosEst(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector3::AngleBetweenNormals(Vector3 n1, Vector3 n2) noexcept
    {
        auto v_result = Vector3::Dot(n1, n2);
        v_result      = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result      = Vector4::ACos(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector3::AngleBetweenVectors(Vector3 v1, Vector3 v2) noexcept
    {
        auto v_l1 = Vector3::ReciprocalLength(v1);
        auto v_l2 = Vector3::ReciprocalLength(v2);

        auto v_dot = Vector3::Dot(v1, v2);

        v_l1 = Vector4::Multiply(v_l1, v_l2);

        auto v_cos_angle = Vector4::Multiply(v_dot, v_l1);
        v_cos_angle      = Vector4::Clamp(v_cos_angle, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_cos_angle      = Vector4::ACos(v_cos_angle);
        return v_cos_angle;
    }

    mathinline Vector4 mathcall Vector3::LinePointDistance(Vector3 line_point1, Vector3 line_point2, Vector3 point) noexcept
    {
        auto v_point_vector = Vector4::Subtract({ point.V }, { line_point1.V });
        auto v_line_vector  = Vector4::Subtract({ line_point2.V }, { line_point1.V });
        auto v_length_sq    = Vector3::LengthSquared({ v_line_vector.V });

        auto v_point_projection_scale = Vector3::Dot({ v_point_vector.V }, { v_line_vector.V });
        v_point_projection_scale      = Vector4::Divide(v_point_projection_scale, v_length_sq);

        auto v_distance_vector = Vector4::Multiply(v_line_vector, v_point_projection_scale);
        v_distance_vector      = Vector4::Subtract(v_point_vector, v_distance_vector);
        return Vector3::Length({ v_distance_vector.V });
    }

    mathinline void mathcall Vector3::ComponentsFromNormal(Vector3* parallel, Vector3* perpendicular, Vector3 v, Vector3 n) noexcept
    {
        GX_ASSERT(parallel != nullptr);
        GX_ASSERT(perpendicular != nullptr);

        auto v_scale = Vector3::Dot(v, n);
        auto v_parallel = Vector4::Multiply({ n.V }, v_scale);

        (*parallel) = { v_parallel.V };
        (*perpendicular) = { Vector4::Subtract({ v.V }, v_parallel).V };
    }
    mathinline Vector3 mathcall Vector3::Project(Vector3 v, float viewport_x, float viewport_y, float viewport_width, float viewport_height, float viewport_min_z, float viewport_max_z, Matrix projection, Matrix view, Matrix world) noexcept
    {
        auto f_half_viewport_width = viewport_width * 0.5F;
        auto f_half_viewport_height = viewport_height * 0.5F;

        auto v_scale = Vector4::Make(f_half_viewport_width, -f_half_viewport_height, viewport_max_z - viewport_min_z, 0.0F);
        auto v_offset = Vector4::Make(viewport_x + f_half_viewport_width, viewport_y + f_half_viewport_height, viewport_min_z, 0.0F);

        auto m_transform = Matrix::Multiply(world, view);
        m_transform = Matrix::Multiply(m_transform, projection);

        auto v_result = Vector3::TransformCoord(v, m_transform);
        v_result = { Vector4::MultiplyAdd({ v_result.V }, v_scale, v_offset).V };
        return { v_result.V };
    }

    mathinline Vector3 mathcall Vector3::Unproject(Vector3 v, float viewport_x, float viewport_y, float viewport_width, float viewport_height, float viewport_min_z, float viewport_max_z, Matrix projection, Matrix view, Matrix world) noexcept
    {
        static const Detail::Vector4F32 d = { { { -1.0F, 1.0F, 0.0F, 0.0F } } };
        auto v_scale = Vector4::Make(viewport_width * 0.5F, -viewport_height * 0.5F, viewport_max_z - viewport_min_z, 1.0F);
        v_scale = Vector4::Reciprocal(v_scale);

        auto v_offset = Vector4::Make(-viewport_x, -viewport_y, -viewport_min_z, 0.0F);
        v_offset = Vector4::MultiplyAdd(v_scale, v_offset, { d.V });

        auto m_transform = Matrix::Multiply(world, view);
        m_transform = Matrix::Multiply(m_transform, projection);
        m_transform = Matrix::Inverse(nullptr, m_transform);

        auto v_result = Vector4::MultiplyAdd({ v.V }, v_scale, v_offset);
        return { Vector3::TransformCoord({ v_result.V }, m_transform).V };
    }
}
