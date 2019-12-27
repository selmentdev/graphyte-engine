    mathinline void mathcall Plane::IntersectPlane(Vector3* line_point1, Vector3* line_point2, Plane p1, Plane p2) noexcept
    {
        GX_ASSERT(line_point1 != nullptr);
        GX_ASSERT(line_point2 != nullptr);

        auto v_v1 = Vector3::Cross({ p2.V }, { p1.V });
        auto v_length_sq = Vector3::Length(v_v1);
        auto v_v2 = Vector3::Cross({ p2.V }, v_v1);
        auto v_p1w = Vector4::SplatW({ p1.V });
        auto v_point = Vector4::Multiply({ v_v2.V }, v_p1w);
        auto v_v3 = Vector3::Cross({ v_v1.V }, { p1.V });

        auto v_p2w = Vector4::SplatW({ p2.V });
        v_point = Vector4::MultiplyAdd({ v_v3.V }, v_p2w, v_point);
        auto v_lp1 = Vector4::Divide(v_point, v_length_sq);
        auto v_lp2 = Vector4::Add(v_lp1, { v_v1.V });
        auto v_control = Vector4::CompareLessEqual(v_length_sq, { Detail::VEC4_EPSILON.V });
        (*line_point1) = { Vector4::Select(v_lp1, { Detail::VEC4_QNAN.V }, v_control).V };
        (*line_point2) = { Vector4::Select(v_lp2, { Detail::VEC4_QNAN.V }, v_control).V };
    }
