    mathinline Quaternion mathcall Quaternion::Slerp(Quaternion q0, Quaternion q1, float t) noexcept
    {
        auto v_t = Vector4::Make(t);
        return Quaternion::Slerp(q0, q1, v_t);
    }

    mathinline Quaternion mathcall Quaternion::Slerp(Quaternion q0, Quaternion q1, Vector4 t) noexcept
    {
        GX_ASSERT(
            Vector4::GetX(t) == Vector4::GetY(t) &&
            Vector4::GetX(t) == Vector4::GetZ(t) &&
            Vector4::GetX(t) == Vector4::GetW(t)
        );

#if GRAPHYTE_MATH_NO_INTRINSICS
        static const Detail::Vector4F32 one_minus_epsilon = { { { 1.0F - 0.00001F, 1.0F - 0.00001F, 1.0F - 0.00001F, 1.0F - 0.00001F } } };

        auto v_cos_omega = Quaternion::Dot(q0, q1);

        auto v_zero = Vector4::Zero();
        auto v_control = Vector4::CompareLess(v_cos_omega, v_zero);
        auto v_sign = Vector4::Select({ Detail::VEC4_ONE_4.V }, { Detail::VEC4_NEGATIVE_ONE_4.V }, v_control);

        v_cos_omega = Vector4::Multiply(v_cos_omega, v_sign);
        v_control = Vector4::CompareLess(v_cos_omega, { one_minus_epsilon.V });

        auto v_sin_omega = Vector4::NegativeMultiplySubtract(v_cos_omega, v_cos_omega, { Detail::VEC4_ONE_4.V });
        v_sin_omega = Vector4::Sqrt(v_sin_omega);

        auto v_omega = Vector4::ATan2(v_sin_omega, v_cos_omega);

        auto v_sign_mask = Vector4::SignMask();
        auto v_v01 = Vector4::ShiftLeft(t, v_zero, 2);
        v_sign_mask = Vector4::ShiftLeft(v_sign_mask, v_zero, 3);
        v_v01 = Vector4::MaskXorUInt(v_v01, v_sign_mask);
        v_v01 = Vector4::Add({ Detail::VEC4_POSITIVE_UNIT_X.V }, v_v01);

        auto v_inv_sin_omega = Vector4::Reciprocal(v_sin_omega);

        auto v_s0 = Vector4::Multiply(v_v01, v_omega);
        v_s0 = Vector4::Sin(v_s0);
        v_s0 = Vector4::Multiply(v_s0, v_inv_sin_omega);

        v_s0 = Vector4::Select(v_v01, v_s0, v_control);

        auto v_s1 = Vector4::SplatY(v_s0);

        v_s0 = Vector4::SplatX(v_s0);
        v_s1 = Vector4::Multiply(v_s1, v_sign);

        auto v_result = Vector4::Multiply({ q0.V }, v_s0);
        v_result = Vector4::MultiplyAdd({ q1.V }, v_s1, v_result);

        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 one_minus_epsilon = { { { 1.0F - 0.00001F, 1.0F - 0.00001F, 1.0F - 0.00001F, 1.0F - 0.00001F } } };
        static const Detail::Vector4F32 sign_mask_2 = { { { 0x80000000, 0x00000000, 0x00000000, 0x00000000 } } };

        auto v_cos_omega = Quaternion::Dot(q0, q1).V;

        auto v_zero = _mm_setzero_ps();
        auto v_control = Vector4::CompareLess({ v_cos_omega }, { v_zero }).V;
        auto v_sign = Vector4::Select({ Detail::VEC4_ONE_4.V }, { Detail::VEC4_NEGATIVE_ONE_4.V }, { v_control }).V;

        v_cos_omega = _mm_mul_ps(v_cos_omega, v_sign);

        v_control = Vector4::CompareLess({ v_cos_omega }, { one_minus_epsilon.V }).V;

        auto v_sin_omega = _mm_mul_ps(v_cos_omega, v_cos_omega);
        v_sin_omega = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_sin_omega);
        v_sin_omega = _mm_sqrt_ps(v_sin_omega);

        auto v_omega = Vector4::ATan2({ v_sin_omega }, { v_cos_omega }).V;

        auto v_v01 = _mm_permute_ps(t.V, _MM_SHUFFLE(2, 3, 0, 1));
        v_v01 = _mm_and_ps(v_v01, Detail::VEC4_MASK_SELECT_1100);
        v_v01 = _mm_xor_ps(v_v01, sign_mask_2.V);
        v_v01 = _mm_add_ps(Detail::VEC4_POSITIVE_UNIT_X.V, v_v01);

        auto v_s0 = _mm_mul_ps(v_v01, v_omega);
        v_s0 = Vector4::Sin({ v_s0 }).V;
        v_s0 = _mm_div_ps(v_s0, v_sin_omega);
        v_s0 = Vector4::Select({ v_s0 }, { v_s0 }, { v_control }).V;

        auto v_s1 = Vector4::SplatY({ v_s0 }).V;
        v_s0 = Vector4::SplatX({ v_s0 }).V;

        v_s1 = _mm_mul_ps(v_s1, v_sign);

        auto v_result = _mm_mul_ps(q0.V, v_s0);
        v_s1 = _mm_mul_ps(v_s1, q1.V);
        v_result = _mm_add_ps(v_result, v_s1);
        return { v_result };
#endif
    }

    mathinline Quaternion mathcall Quaternion::Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, float t) noexcept
    {
        auto v_t = Vector4::Make(t);
        return Quaternion::Squad(q0, q1, q2, q3, v_t);
    }

    mathinline Quaternion mathcall Quaternion::Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, Vector4 t) noexcept
    {
        GX_ASSERT(
            Vector4::GetX(t) == Vector4::GetY(t) &&
            Vector4::GetX(t) == Vector4::GetZ(t) &&
            Vector4::GetX(t) == Vector4::GetW(t)
        );

        auto v_tp = t;
        auto v_two = Vector4::SplatConstant(2, 0);
        auto q_q03 = Quaternion::Slerp(q0, q3, t);
        auto q_q12 = Quaternion::Slerp(q1, q2, t);

        v_tp = Vector4::NegativeMultiplySubtract(v_tp, v_tp, v_tp);
        v_tp = Vector4::Multiply(v_tp, v_two);

        auto q_result = Quaternion::Slerp(q_q03, q_q12, v_tp);
        return q_result;
    }

    mathinline void mathcall Quaternion::SquadSetup(Quaternion* out_a, Quaternion* out_b, Quaternion* out_c, Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3) noexcept
    {
        GX_ASSERT(out_a != nullptr);
        GX_ASSERT(out_b != nullptr);
        GX_ASSERT(out_c != nullptr);

        auto v_ls12 = Quaternion::LengthSquared({ Vector4::Add({ q1.V }, { q2.V }).V });
        auto v_ld12 = Quaternion::LengthSquared({ Vector4::Subtract({ q1.V }, { q2.V }).V });
        auto v_sq2 = Vector4::Negate({ q2.V });

        auto v_control = Vector4::CompareLess(v_ls12, v_ld12);
        v_sq2 = Vector4::Select({ q2.V }, v_sq2, v_control);

        auto v_ls01 = Quaternion::LengthSquared({ Vector4::Add({ q0.V }, { q1.V }).V });
        auto v_ld01 = Quaternion::LengthSquared({ Vector4::Subtract({ q0.V }, { q1.V }).V });
        auto v_sq0 = Vector4::Negate({ q0.V });

        auto v_ls23 = Quaternion::LengthSquared({ Vector4::Add({ v_sq2.V }, { q3.V }).V });
        auto v_ld23 = Quaternion::LengthSquared({ Vector4::Subtract({ v_sq2.V }, { q3.V }).V });
        auto v_sq3 = Vector4::Negate({ q3.V });

        auto v_control0 = Vector4::CompareLess(v_ls01, v_ld01);
        auto v_control2 = Vector4::CompareLess(v_ls23, v_ld23);

        v_sq0 = Vector4::Select({ q0.V }, v_sq0, v_control0);
        v_sq3 = Vector4::Select({ q3.V }, v_sq3, v_control2);

        auto q_inv_q1 = Quaternion::Inverse(q1);
        auto q_inv_q2 = Quaternion::Inverse({ v_sq2.V });

        auto q_ln_q0 = Quaternion::Ln(Quaternion::Multiply(q_inv_q1, { v_sq0.V }));
        auto q_ln_q2 = Quaternion::Ln(Quaternion::Multiply(q_inv_q1, { v_sq2.V }));
        auto q_ln_q1 = Quaternion::Ln(Quaternion::Multiply(q_inv_q2, q1));
        auto q_ln_q3 = Quaternion::Ln(Quaternion::Multiply(q_inv_q2, { v_sq3.V }));

        auto v_negative_one_quater = Vector4::SplatConstant(-1, 2);

        auto v_exp_q02 = Quaternion{ Vector4::Multiply(Vector4::Add({ q_ln_q0.V }, { q_ln_q2.V }), v_negative_one_quater).V };
        auto v_exp_q13 = Quaternion{ Vector4::Multiply(Vector4::Add({ q_ln_q1.V }, { q_ln_q3.V }), v_negative_one_quater).V };

        v_exp_q02 = Quaternion::Exp(v_exp_q02);
        v_exp_q13 = Quaternion::Exp(v_exp_q13);

        (*out_a) = Quaternion::Multiply(q1, v_exp_q02);
        (*out_b) = Quaternion::Multiply({ v_sq2.V }, v_exp_q13);
        (*out_c) = { v_sq2.V };
    }

    mathinline Quaternion mathcall Quaternion::Barycentric(Quaternion q0, Quaternion q1, Quaternion q2, float f, float g) noexcept
    {
        auto f_s = f + g;

        Quaternion v_result;

        if ((f_s < 0.00001F) && (f_s > -0.00001F))
        {
            v_result = q0;
        }
        else
        {
            auto q_q01 = Quaternion::Slerp(q0, q1, f_s);
            auto q_q02 = Quaternion::Slerp(q0, q2, f_s);

            v_result = Quaternion::Slerp(q_q01, q_q02, g / f_s);
        }

        return v_result;
    }

    mathinline Quaternion mathcall Quaternion::Barycentric(Quaternion q0, Quaternion q1, Quaternion q2, Vector4 f, Vector4 g) noexcept
    {
        GX_ASSERT(Vector4::GetX(f) == Vector4::GetY(f) && Vector4::GetX(f) == Vector4::GetZ(f) && Vector4::GetX(f) == Vector4::GetW(f));
        GX_ASSERT(Vector4::GetX(g) == Vector4::GetY(g) && Vector4::GetX(g) == Vector4::GetZ(g) && Vector4::GetX(g) == Vector4::GetW(g));

        auto v_epsilon = Vector4::SplatConstant(1, 16);

        auto v_s = Vector4::Add(f, g);

        Quaternion v_result;
        if (Vector4::InBounds(v_s, v_epsilon))
        {
            v_result = q0;
        }
        else
        {
            auto q_q01 = Quaternion::Slerp(q0, q1, v_s);
            auto q_q02 = Quaternion::Slerp(q0, q2, v_s);
            auto v_rcp_gs = Vector4::Reciprocal(v_s);
            v_rcp_gs = Vector4::Multiply(g, v_rcp_gs);

            v_result = Quaternion::Slerp(q_q01, q_q02, v_rcp_gs);
        }

        return v_result;
    }
