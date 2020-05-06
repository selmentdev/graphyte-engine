namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Color::HueToClr(Vector4 p, Vector4 q, Vector4 h) noexcept
    {
        static const Detail::Vector4F32 v_one_sixth  = { { { 1.0F / 6.0F, 1.0F / 6.0F, 1.0F / 6.0F, 1.0F / 6.0F } } };
        static const Detail::Vector4F32 v_two_thirds = { { { 2.0F / 3.0F, 2.0F / 3.0F, 2.0F / 3.0F, 2.0F / 3.0F } } };

        auto t = h;
        if (Vector3::IsLess({ t.V }, Vector3::Zero()))
        {
            t = Vector4::Add(t, Vector4::One());
        }

        if (Vector3::IsGreater({ t.V }, Vector3::One()))
        {
            t = Vector4::Subtract(t, Vector4::One());
        }

        if (Vector3::IsLess({ t.V }, { v_one_sixth.V }))
        {
            auto v_t1 = Vector4::Subtract(q, p);
            auto v_t2 = Vector4::Multiply({ Detail::VEC4_SIX_4.V }, t);
            return Vector4::MultiplyAdd(v_t1, v_t2, p);
        }

        if (Vector3::IsLess({ t.V }, { Detail::VEC4_ONE_HALF_4.V }))
        {
            return q;
        }

        if (Vector3::IsLess({ t.V }, { v_two_thirds.V }))
        {
            auto v_t1 = Vector4::Subtract(q, p);
            auto v_t2 = Vector4::Multiply({ Detail::VEC4_SIX_4.V }, Vector4::Subtract({ v_two_thirds.V }, t));
            return Vector4::MultiplyAdd(v_t1, v_t2, p);
        }

        return p;
    }

    mathinline Color mathcall Color::RGBToHSL(Color c) noexcept
    {
        auto v_r = Vector4::SplatX({ c.V });
        auto v_g = Vector4::SplatY({ c.V });
        auto v_b = Vector4::SplatZ({ c.V });

        auto v_min = Vector4::Min(v_r, Vector4::Min(v_g, v_b));
        auto v_max = Vector4::Max(v_r, Vector4::Max(v_g, v_b));

        auto v_l = Vector4::Multiply(Vector4::Add(v_min, v_max), { Detail::VEC4_ONE_HALF_4.V });

        auto v_d = Vector4::Subtract(v_max, v_min);

        auto v_la = Vector4::Select({ c.V }, v_l, { Detail::VEC4_MASK_SELECT_1110.V });

        if (Vector3::IsLess({ v_d.V }, { Detail::VEC4_EPSILON.V }))
        {
            return { Vector4::Select({ v_la.V }, { Detail::VEC4_ZERO_4.V }, { Detail::VEC4_MASK_SELECT_1100.V }).V };
        }
        else
        {
            Vector4 v_s, v_h;

            Vector4 v_d2 = Vector4::Add(v_min, v_max);

            if (Vector3::IsGreater({ v_l.V }, { Detail::VEC4_ONE_HALF_4.V }))
            {
                v_s = Vector4::Divide(v_d, Vector4::Subtract({ Detail::VEC4_TWO_4.V }, v_d2));
            }
            else
            {
                v_s = Vector4::Divide(v_d, v_d2);
            }

            if (Vector3::IsEqual({ v_r.V }, { v_max.V }))
            {
                v_h = Vector4::Divide(Vector4::Subtract(v_g, v_b), v_d);
            }
            else if (Vector3::IsEqual({ v_g.V }, { v_max.V }))
            {
                v_h = Vector4::Divide(Vector4::Subtract(v_b, v_r), v_d);
                v_h = Vector4::Add(v_h, { Detail::VEC4_TWO_4.V });
            }
            else
            {
                v_h = Vector4::Divide(Vector4::Subtract(v_r, v_g), v_d);
                v_h = Vector4::Add(v_h, { Detail::VEC4_FOUR_4.V });
            }

            v_h = Vector4::Divide(v_h, { Detail::VEC4_SIX_4.V });

            if (Vector3::IsLess({ v_h.V }, { Detail::VEC4_ZERO_4.V }))
            {
                v_h = Vector4::Add(v_h, { Detail::VEC4_ONE_4.V });
            }

            auto v_lha = Vector4::Select(v_la, v_h, { Detail::VEC4_MASK_SELECT_1100.V });
            return { Vector4::Select(v_s, v_lha, { Detail::VEC4_MASK_SELECT_1011.V }).V };
        }
    }

    mathinline Color mathcall Color::HSLToRGB(Color c) noexcept
    {
        static const Detail::Vector4F32 v_one_third = { { { 1.0F / 3.0F, 1.0F / 3.0F, 1.0F / 3.0F, 1.0F / 3.0F } } };

        auto v_s = Vector4::SplatY({ c.V });
        auto v_l = Vector4::SplatZ({ c.V });

        if (Vector3::IsEqual({ v_s.V }, { Detail::VEC4_ZERO_4.V }, { Detail::VEC4_EPSILON.V }))
        {
            return { Vector4::Select({ c.V }, v_l, { Detail::VEC4_MASK_SELECT_1110.V }).V };
        }
        else
        {
            auto v_h = Vector4::SplatX({ c.V });

            Vector4 v_q;
            if (Vector3::IsLess({ v_l.V }, { Detail::VEC4_ONE_HALF_4.V }))
            {
                v_q = Vector4::Multiply(v_l, Vector4::Add({ Detail::VEC4_ONE_4.V }, v_s));
            }
            else
            {
                v_q = Vector4::Subtract(Vector4::Add(v_l, v_s), Vector4::Multiply(v_l, v_s));
            }

            auto v_p = Vector4::Subtract(Vector4::Multiply({ Detail::VEC4_TWO_4.V }, v_l), v_q);

            auto v_r = Color::HueToClr(v_p, v_q, Vector4::Add(v_h, { v_one_third.V }));
            auto v_g = Color::HueToClr(v_p, v_q, v_h);
            auto v_b = Color::HueToClr(v_p, v_q, Vector4::Subtract(v_h, { v_one_third.V }));

            auto v_rg = Vector4::Select(v_g, v_r, { Detail::VEC4_MASK_SELECT_1000.V });
            auto v_ba = Vector4::Select({ c.V }, v_b, { Detail::VEC4_MASK_SELECT_1110.V });

            return { Vector4::Select(v_ba, v_rg, { Detail::VEC4_MASK_SELECT_1100.V }).V };
        }
    }

    mathinline Color mathcall Color::RGBToHSV(Color c) noexcept
    {
        auto v_r = Vector4::SplatX({ c.V });
        auto v_g = Vector4::SplatY({ c.V });
        auto v_b = Vector4::SplatZ({ c.V });

        auto v_min = Vector4::Min(v_r, Vector4::Min(v_g, v_b));
        auto v_v = Vector4::Max(v_r, Vector4::Max(v_g, v_b));

        auto v_d = Vector4::Subtract(v_v, v_min);

        auto v_s = (Vector3::IsEqual({ v_v.V }, { Detail::VEC4_ZERO_4.V }, { Detail::VEC4_EPSILON.V })) ? Vector4{ Detail::VEC4_ZERO_4.V } : Vector4::Divide(v_d, v_v);

        if (Vector3::IsLess({ v_d.V }, { Detail::VEC4_EPSILON.V }))
        {
            auto v_hv = Vector4::Select(v_v, { Detail::VEC4_ZERO_4.V }, { Detail::VEC4_MASK_SELECT_1000.V });
            auto v_hva = Vector4::Select({ c.V }, v_hv, { Detail::VEC4_MASK_SELECT_1110.V });
            return { Vector4::Select(v_s, v_hva, { Detail::VEC4_MASK_SELECT_1011.V }).V };
        }
        else
        {
            Vector4 v_h;

            if (Vector3::IsEqual({ v_r.V }, { v_v.V }))
            {
                v_h = Vector4::Divide(Vector4::Subtract(v_g, v_b), v_d);

                if (Vector3::IsLess({ v_g.V }, { v_b.V }))
                {
                    v_h = Vector4::Add(v_h, { Detail::VEC4_SIX_4.V });
                }
            }
            else if (Vector3::IsEqual({ v_g.V }, { v_v.V }))
            {
                v_h = Vector4::Divide(Vector4::Subtract(v_b, v_r), v_d);
                v_h = Vector4::Add(v_h, { Detail::VEC4_TWO_4.V });
            }
            else
            {
                v_h = Vector4::Divide(Vector4::Subtract(v_r, v_g), v_d);
                v_h = Vector4::Add(v_h, { Detail::VEC4_FOUR_4.V });
            }

            v_h = Vector4::Divide(v_h, { Detail::VEC4_SIX_4.V });

            auto v_hv = Vector4::Select(v_v, v_h, { Detail::VEC4_MASK_SELECT_1000.V });
            auto v_hva = Vector4::Select({ c.V }, v_hv, { Detail::VEC4_MASK_SELECT_1110.V });
            return { Vector4::Select(v_s, v_hva, { Detail::VEC4_MASK_SELECT_1011.V }).V };
        }
    }

    mathinline Color mathcall Color::HSVToRGB(Color c) noexcept
    {
        auto v_h = Vector4::SplatX({ c.V });
        auto v_s = Vector4::SplatY({ c.V });
        auto v_v = Vector4::SplatZ({ c.V });

        auto v_h6 = Vector4::Multiply(v_h, { Detail::VEC4_SIX_4.V });

        auto v_i = Vector4::Floor(v_h6);
        auto v_f = Vector4::Subtract(v_h6, v_i);

        auto v_p = Vector4::Multiply(v_v, Vector4::Subtract({ Detail::VEC4_ONE_4.V }, v_s));
        auto v_q = Vector4::Multiply(v_v, Vector4::Subtract({ Detail::VEC4_ONE_4.V }, Vector4::Multiply(v_f, v_s)));

        auto v_t = Vector4::Multiply(v_v, Vector4::Subtract({ Detail::VEC4_ONE_4.V }, Vector4::Multiply(Vector4::Subtract({ Detail::VEC4_ONE_4.V }, v_f), v_s)));

        auto ii = static_cast<int>(Vector4::GetX(Vector4::Mod(v_i, { Detail::VEC4_SIX_4.V })));

        Vector4 v_rgb;

        switch (ii)
        {
        case 0:
            {
                auto v_vt = Vector4::Select(v_t, v_v, { Detail::VEC4_MASK_SELECT_1000.V });
                v_rgb = Vector4::Select(v_p, v_vt, { Detail::VEC4_MASK_SELECT_1100.V });
                break;
            }
        case 1:
            {
                auto v_qv = Vector4::Select(v_v, v_q, { Detail::VEC4_MASK_SELECT_1000.V });
                v_rgb = Vector4::Select(v_p, v_qv, { Detail::VEC4_MASK_SELECT_1100.V });
                break;
            }
        case 2:
            {
                auto v_pv = Vector4::Select(v_v, v_p, { Detail::VEC4_MASK_SELECT_1000.V });
                v_rgb = Vector4::Select(v_t, v_pv, { Detail::VEC4_MASK_SELECT_1100.V });
                break;
            }
        case 3:
            {
                auto v_pq = Vector4::Select(v_q, v_p, { Detail::VEC4_MASK_SELECT_1000.V });
                v_rgb = Vector4::Select(v_v, v_pq, { Detail::VEC4_MASK_SELECT_1100.V });
                break;
            }
        case 4:
            {
                auto v_tp = Vector4::Select(v_p, v_t, { Detail::VEC4_MASK_SELECT_1000.V });
                v_rgb = Vector4::Select(v_v, v_tp, { Detail::VEC4_MASK_SELECT_1100.V });
                break;
            }
        default:
            {
                auto v_vp = Vector4::Select(v_p, v_v, { Detail::VEC4_MASK_SELECT_1000.V });
                v_rgb = Vector4::Select(v_q, v_vp, { Detail::VEC4_MASK_SELECT_1100.V });
            }
            break;
        }

        return { Vector4::Select({ c.V }, v_rgb, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::RGBToYUV(Color c) noexcept
    {
        static const Detail::Vector4F32 scale0 = { { { 0.299F, -0.147F, 0.615F, 0.0F } } };
        static const Detail::Vector4F32 scale1 = { { { 0.587F, -0.289F, -0.515F, 0.0F } } };
        static const Detail::Vector4F32 scale2 = { { { 0.114F, 0.436F, -0.100F, 0.0F } } };

        Matrix m;
        m.M.R[0] = scale0.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_result = Vector3::Transform({ c.V }, m);

        return { Vector4::Select({ c.V }, { v_result.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::YUVToRGB(Color c) noexcept
    {
        static const Detail::Vector4F32 scale1 = { { { 0.0F, -0.395F, 2.032F, 0.0F } } };
        static const Detail::Vector4F32 scale2 = { { { 1.140F, -0.581F, 0.0F, 0.0F } } };

        Matrix m;
        m.M.R[0] = Detail::VEC4_ONE_4.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_result = Vector3::Transform({ c.V }, m);

        return { Vector4::Select({ c.V }, { v_result.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::RGBToYUVHD(Color c) noexcept
    {
        static const Detail::Vector4F32 scale0 = { { { 0.2126F, -0.0997F, 0.6150F, 0.0F } } };
        static const Detail::Vector4F32 scale1 = { { { 0.7152F, -0.3354F, -0.5586F, 0.0F } } };
        static const Detail::Vector4F32 scale2 = { { { 0.0722F, 0.4351F, -0.0564F, 0.0F } } };

        Matrix m;
        m.M.R[0] = scale0.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_result = Vector3::Transform({ c.V }, m);

        return { Vector4::Select({ c.V }, { v_result.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::YUVToRGBHD(Color c) noexcept
    {
        static const Detail::Vector4F32 scale1 = { { { 0.0F, -0.2153F, 2.1324F, 0.0F } } };
        static const Detail::Vector4F32 scale2 = { { { 1.2803F, -0.3806F, 0.0F, 0.0F } } };
        
        Matrix m;
        m.M.R[0] = Detail::VEC4_ONE_4.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_result = Vector3::Transform({ c.V }, m);

        return { Vector4::Select({ c.V }, { v_result.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::RGBToXYZ(Color c) noexcept
    {
        static const Detail::Vector4F32 scale0 = { { { 0.4887180F, 0.1762044F, 0.0000000F, 0.0F } } };
        static const Detail::Vector4F32 scale1 = { { { 0.3106803F, 0.8129847F, 0.0102048F, 0.0F } } };
        static const Detail::Vector4F32 scale2 = { { { 0.2006017F, 0.0108109F, 0.9897952F, 0.0F } } };
        static const Detail::Vector4F32 scale = { { { 1.0F / 0.17697F, 1.0F / 0.17697F, 1.0F / 0.17697F, 0.0F } } };

        Matrix m;
        m.M.R[0] = scale0.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_result = Vector4::Multiply({ Vector3::Transform({ c.V }, m).V }, { scale.V });

        return { Vector4::Select({ c.V }, { v_result.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::XYZToRGB(Color c) noexcept
    {
        static const Detail::Vector4F32 scale0 = { { { 2.3706743f, -0.5138850f, 0.0052982f, 0.0f } } };
        static const Detail::Vector4F32 scale1 = { { { -0.9000405f, 1.4253036f, -0.0146949f, 0.0f } } };
        static const Detail::Vector4F32 scale2 = { { { -0.4706338f, 0.0885814f, 1.0093968f, 0.0f } } };
        static const Detail::Vector4F32 scale = { { { 0.17697f, 0.17697f, 0.17697f, 0.0f } } };

        Matrix m;
        m.M.R[0] = scale0.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_result = Vector3::Transform({ Vector4::Multiply({ c.V }, { scale.V }).V }, m);

        return { Vector4::Select({ c.V }, { v_result.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::XYZToSRGB(Color c) noexcept
    {
        static const Detail::Vector4F32 scale0 = { { { 3.2406F, -0.9689F, 0.0557F, 0.0F } } };
        static const Detail::Vector4F32 scale1 = { { { -1.5372F, 1.8758F, -0.2040F, 0.0F } } };
        static const Detail::Vector4F32 scale2 = { { { -0.4986F, 0.0415F, 1.0570F, 0.0F } } };
        static const Detail::Vector4F32 cutoff = { { { 0.0031308F, 0.0031308F, 0.0031308F, 0.0F } } };
        static const Detail::Vector4F32 exp = { { { 1.0F / 2.4F, 1.0F / 2.4F, 1.0F / 2.4F, 1.0F } } };

        Matrix m;
        m.M.R[0] = scale0.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        Vector4 v_lclr{ Vector3::Transform({ c.V }, m).V };

        auto v_sel = Vector4::CompareGreater(v_lclr, { cutoff.V });
        auto v_small_c = Vector4::Multiply(v_lclr, { Detail::VEC4_MSRGB_SCALE.V });
        auto v_large_c = Vector4::Subtract(Vector4::Multiply({ Detail::VEC4_MSRGB_A1.V }, Vector4::Pow(v_lclr, { exp.V })), { Detail::VEC4_MSRGB_A.V });

        auto v_clr = Vector4::Select(v_small_c, v_large_c, v_sel);

        return { Vector4::Select({ c.V }, v_clr, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::SRGBToXYZ(Color c) noexcept
    {
        static const Detail::Vector4F32 scale0 = { { { 0.4124f, 0.2126f, 0.0193f, 0.0f } } };
        static const Detail::Vector4F32 scale1 = { { { 0.3576f, 0.7152f, 0.1192f, 0.0f } } };
        static const Detail::Vector4F32 scale2 = { { { 0.1805f, 0.0722f, 0.9505f, 0.0f } } };
        static const Detail::Vector4F32 cutoff = { { { 0.04045f, 0.04045f, 0.04045f, 0.0f } } };
        static const Detail::Vector4F32 exp = { { { 2.4f, 2.4f, 2.4f, 1.0f } } };

        auto v_sel = Vector4::CompareGreater({ c.V }, { cutoff.V });
        auto v_small_c = Vector4::Divide({ c.V }, { Detail::VEC4_MSRGB_SCALE.V });
        auto v_large_c = Vector4::Pow(Vector4::Divide(Vector4::Add({ c.V }, { Detail::VEC4_MSRGB_A.V }), { Detail::VEC4_MSRGB_A1.V }), { exp.V });
        auto v_lclr = Vector4::Select(v_small_c, v_large_c, v_sel);

        Matrix m;
        m.M.R[0] = scale0.V;
        m.M.R[1] = scale1.V;
        m.M.R[2] = scale2.V;
        m.M.R[3] = Detail::VEC4_ZERO_4.V;

        auto v_clr = Vector3::Transform({ v_lclr.V }, m);

        return { Vector4::Select({ c.V }, { v_clr.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::RGBToSRGB(Color c) noexcept
    {
        static const Detail::Vector4F32 cutoff = { { { 0.0031308F, 0.0031308F, 0.0031308F, 1.0F } } };
        static const Detail::Vector4F32 linear = { { { 12.92F, 12.92F, 12.92F, 1.0F } } };
        static const Detail::Vector4F32 scale = { { { 1.055F, 1.055F, 1.055F, 1.0F } } };
        static const Detail::Vector4F32 bias = { { { 0.055F, 0.055F, 0.055F, 0.0F } } };
        static const Detail::Vector4F32 inv_gamma = { { { 1.0F / 2.4F, 1.0F / 2.4F, 1.0F / 2.4F, 1.0F } } };

        auto v_v = Vector4::Saturate({ c.V });
        auto v_v0 = Vector4::Multiply(v_v, { linear.V });
        auto v_v1 = Vector4::Subtract(Vector4::Multiply({ scale.V }, Vector4::Pow(v_v, { inv_gamma.V })), { bias.V });
        auto v_select = Vector4::CompareLess(v_v, { cutoff.V });
        v_v = Vector4::Select(v_v1, v_v0, v_select);
        return { Vector4::Select({ c.V }, v_v, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Color mathcall Color::SRGBToRGB(Color c) noexcept
    {
        static const Detail::Vector4F32 cutoff = { { { 0.04045F, 0.04045F, 0.04045F, 1.0F } } };
        static const Detail::Vector4F32 linear = { { { 1.0F / 12.92F, 1.0F / 12.92F, 1.0F / 12.92F, 1.0F } } };
        static const Detail::Vector4F32 scale  = { { { 1.0F / 1.055F, 1.0F / 1.055F, 1.0F / 1.055F, 1.0F } } };
        static const Detail::Vector4F32 bias   = { { { 0.055F, 0.055F, 0.055F, 0.0F } } };
        static const Detail::Vector4F32 gamma  = { { { 2.4F, 2.4F, 2.4F, 1.0F } } };

        auto v = Vector4::Saturate({ c.V });
        auto v_v0 = Vector4::Multiply(v, { linear.V });
        auto v_v1 = Vector4::Pow(Vector4::Multiply(Vector4::Add(v, { bias.V }), { scale.V }), { gamma.V });
        auto v_select = Vector4::CompareGreater(v, { cutoff.V });
        v = Vector4::Select(v_v0, v_v1, v_select);
        v = Vector4::Select({ c.V }, v, { Detail::VEC4_MASK_SELECT_1110.V });
        return { v.V };
    }
}
