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
