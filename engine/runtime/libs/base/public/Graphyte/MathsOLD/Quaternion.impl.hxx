#pragma once
#include <Graphyte/Maths/Quaternion.hxx>
#include <Graphyte/Maths/Vector4.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Maths
{
    mathinline bool mathcall Quaternion::IsEqual(Quaternion q1, Quaternion q2) noexcept
    {
        return Vector4::IsEqual({ q1.V }, { q2.V });
    }

    mathinline bool mathcall Quaternion::IsNotEqual(Quaternion q1, Quaternion q2) noexcept
    {
        return Vector4::IsNotEqual({ q1.V }, { q2.V });
    }

    mathinline bool mathcall Quaternion::IsNaN(Quaternion q) noexcept
    {
        return Vector4::IsNaN({ q.V });
    }

    mathinline bool mathcall Quaternion::IsInfinite(Quaternion q) noexcept
    {
        return Vector4::IsInfinite({ q.V });
    }

    mathinline bool mathcall Quaternion::IsIdentity(Quaternion q) noexcept
    {
        return Vector4::IsEqual({ q.V }, { Detail::VEC4_POSITIVE_UNIT_W.V });
    }

    mathinline Vector4 mathcall Quaternion::Dot(Quaternion q1, Quaternion q2) noexcept
    {
        return Vector4::Dot({ q1.V }, { q2.V });
    }

    mathinline Quaternion mathcall Quaternion::Multiply(Quaternion q1, Quaternion q2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                (q2.V.F[3] * q1.V.F[0]) + (q2.V.F[0] * q1.V.F[3]) + (q2.V.F[1] * q1.V.F[2]) - (q2.V.F[2] * q1.V.F[1]),
                (q2.V.F[3] * q1.V.F[1]) - (q2.V.F[0] * q1.V.F[2]) + (q2.V.F[1] * q1.V.F[3]) + (q2.V.F[2] * q1.V.F[0]),
                (q2.V.F[3] * q1.V.F[2]) + (q2.V.F[0] * q1.V.F[1]) - (q2.V.F[1] * q1.V.F[0]) + (q2.V.F[2] * q1.V.F[3]),
                (q2.V.F[3] * q1.V.F[3]) - (q2.V.F[0] * q1.V.F[0]) - (q2.V.F[1] * q1.V.F[1]) - (q2.V.F[2] * q1.V.F[2]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 control_wzyx = { { { 1.0F, -1.0F, 1.0F, -1.0F } } };
        static const Detail::Vector4F32 control_zwxy = { { { 1.0F, 1.0F, -1.0F, -1.0F } } };
        static const Detail::Vector4F32 control_yxwz = { { { -1.0F, 1.0F, 1.0F, -1.0F } } };

        auto v_q2x = q2.V;
        auto v_q2y = q2.V;
        auto v_q2z = q2.V;
        auto v_result = q2.V;

        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 3, 3, 3));
        v_q2x = _mm_permute_ps(v_q2x, _MM_SHUFFLE(0, 0, 0, 0));
        v_q2y = _mm_permute_ps(v_q2y, _MM_SHUFFLE(1, 1, 1, 1));
        v_q2z = _mm_permute_ps(v_q2z, _MM_SHUFFLE(2, 2, 2, 2));

        v_result = _mm_mul_ps(v_result, q1.V);

        auto v_q1_shuffle = q1.V;
        v_q1_shuffle = _mm_permute_ps(v_q1_shuffle, _MM_SHUFFLE(0, 1, 2, 3));
        v_q2x = _mm_mul_ps(v_q2x, v_q1_shuffle);

        v_q1_shuffle = _mm_permute_ps(v_q1_shuffle, _MM_SHUFFLE(2, 3, 0, 1));
        v_q2x = _mm_mul_ps(v_q2x, control_wzyx.V);

        v_q2y = _mm_mul_ps(v_q2y, v_q1_shuffle);

        v_q1_shuffle = _mm_permute_ps(v_q1_shuffle, _MM_SHUFFLE(0, 1, 2, 3));
        v_q2y = _mm_mul_ps(v_q2y, control_zwxy.V);

        v_q2z = _mm_mul_ps(v_q2z, v_q1_shuffle);
        v_result = _mm_add_ps(v_result, v_q2x);
        v_q2z = _mm_mul_ps(v_q2z, control_yxwz.V);
        v_q2y = _mm_add_ps(v_q2y, v_q2z);
        v_result = _mm_add_ps(v_result, v_q2y);
        return { v_result };
        
#endif
    }

    mathinline Vector4 mathcall Quaternion::LengthSquared(Quaternion q) noexcept
    {
        return Vector4::LengthSquared({ q.V });
    }

    mathinline Vector4 mathcall Quaternion::ReciprocalLength(Quaternion q) noexcept
    {
        return Vector4::ReciprocalLength({ q.V });
    }

    mathinline Vector4 mathcall Quaternion::Length(Quaternion q) noexcept
    {
        return Vector4::Length({ q.V });
    }

    mathinline Quaternion mathcall Quaternion::NormalizeEst(Quaternion q) noexcept
    {
        return { Vector4::NormalizeEst({ q.V }).V };
    }

    mathinline Quaternion mathcall Quaternion::Normalize(Quaternion q) noexcept
    {
        return { Vector4::Normalize({ q.V }).V };
    }

    mathinline Quaternion mathcall Quaternion::Conjugate(Quaternion q) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                -q.V.F[0],
                -q.V.F[1],
                -q.V.F[2],
                q.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 negative_one_3 = { { { -1.0F, -1.0F, -1.0F, 1.0F } } };
        return { _mm_mul_ps(q.V, negative_one_3.V) };
#endif
    }

    mathinline Quaternion mathcall Quaternion::Inverse(Quaternion q) noexcept
    {
        auto v_zero = Vector4::Zero();
        auto v_length = Vector4::Length({ q.V });
        auto q_conjugate = Quaternion::Conjugate(q);
        auto v_control = Vector4::CompareLessEqual(v_length, { Detail::VEC4_EPSILON.V });
        auto v_result = Vector4::Divide({ q_conjugate.V }, v_length);
        v_result = Vector4::Select(v_result, v_zero, v_control);
        return { v_result.V };
    }

    mathinline Quaternion mathcall Quaternion::Ln(Quaternion q) noexcept
    {
        static const Detail::Vector4F32 one_minus_epsilon = { { { 1.0F - 0.00001F, 1.0F - 0.00001F, 1.0F - 0.00001F, 1.0F - 0.00001F } } };

        auto v_qw = Vector4::SplatW({ q.V });
        auto v_q0 = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { q.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto v_control_w = Vector4::CompareInBounds(v_qw, { one_minus_epsilon.V });
        auto v_theta = Vector4::ACos(v_qw);
        auto v_sin_theta = Vector4::Sin(v_theta);
        auto v_s = Vector4::Divide(v_theta, v_sin_theta);
        auto v_result = Vector4::Multiply(v_q0, v_s);
        v_result = Vector4::Select(v_q0, v_result, v_control_w);
        return { v_result.V };
    }

    mathinline Quaternion mathcall Quaternion::Exp(Quaternion q)
    {
        auto v_theta = Vector3::Length({ q.V });

        Vector4 v_sin_theta;
        Vector4 v_cos_theta;

        Vector4::SinCos(&v_sin_theta, &v_cos_theta, v_theta);
        auto v_s = Vector4::Divide(v_sin_theta, v_theta);
        auto v_result = Vector4::Multiply({ q.V }, v_s);

        auto v_zero = Vector4::Zero();
        auto v_control = Vector4::CompareEqual(v_theta, v_zero, { Detail::VEC4_EPSILON.V });
        v_result = Vector4::Select(v_result, { q.V }, v_control);
        v_result = Vector4::Select(v_cos_theta, v_result, { Detail::VEC4_MASK_SELECT_1110.V });
        return { v_result.V };
    }

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

    mathinline Quaternion mathcall Quaternion::Identity() noexcept
    {
        return { Detail::VEC4_POSITIVE_UNIT_W.V };
    }

    mathinline Quaternion mathcall Quaternion::RotationFromRollPitchYaw(float pitch, float yaw, float roll) noexcept
    {
        auto v_angles = Vector3{ Vector4::Make(pitch, yaw, roll, 0.0F).V };
        auto v_result = Quaternion::RotationFromRollPitchYaw(v_angles);
        return v_result;
    }

    mathinline Quaternion mathcall Quaternion::RotationFromRollPitchYaw(Vector3 angles) noexcept
    {
        static const Detail::Vector4F32 sign = { { { 1.0F, -1.0F, -1.0F, 1.0F } } };

        auto v_half_angles = Vector4::Multiply({ angles.V }, { Detail::VEC4_ONE_HALF_4.V });

        Vector4 v_sin_angles;
        Vector4 v_cos_angles;
        Vector4::SinCos(&v_sin_angles, &v_cos_angles, v_half_angles);

        auto p0 = Vector4::Permute<0, 4, 4, 4>(v_sin_angles, v_cos_angles);
        auto y0 = Vector4::Permute<5, 1, 5, 5>(v_sin_angles, v_cos_angles);
        auto r0 = Vector4::Permute<6, 6, 2, 6>(v_sin_angles, v_cos_angles);
        auto p1 = Vector4::Permute<0, 4, 4, 4>(v_cos_angles, v_sin_angles);
        auto y1 = Vector4::Permute<5, 1, 5, 5>(v_cos_angles, v_sin_angles);
        auto r1 = Vector4::Permute<6, 6, 2, 6>(v_cos_angles, v_sin_angles);

        auto q1 = Vector4::Multiply(p1, { sign.V });
        auto q0 = Vector4::Multiply(p0, y0);
        q1 = Vector4::Multiply(q1, y1);
        q0 = Vector4::Multiply(q0, r0);
        auto q = Vector4::MultiplyAdd(q1, r1, q0);
        return { q.V };
    }

    mathinline Quaternion mathcall Quaternion::RotationNormal(Vector3 normal_axis, float angle) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_normal = Vector4::Select({ Detail::VEC4_ONE_4.V }, { normal_axis.V }, { Detail::VEC4_MASK_SELECT_1110.V });

        float f_sin;
        float f_cos;
        SinCos(f_sin, f_cos, 0.5F * angle);

        auto v_scale = Vector4::Make(f_sin, f_sin, f_sin, f_cos);
        return { Vector4::Multiply(v_normal, v_scale).V };
#elif GRAPHYTE_HW_AVX
        auto v_normal = _mm_and_ps(normal_axis.V, Detail::VEC4_MASK_SELECT_1110.V);
        v_normal = _mm_or_ps(v_normal, Detail::VEC4_POSITIVE_UNIT_W.V);
        auto v_scale = _mm_set_ps1(0.5F * angle);

        Vector4 v_sin;
        Vector4 v_cos;
        Vector4::SinCos(&v_sin, &v_cos, { v_scale });
        v_scale = _mm_and_ps(v_sin.V, Detail::VEC4_MASK_SELECT_1110.V);
        v_cos.V = _mm_and_ps(v_cos.V, Detail::VEC4_MASK_COMPONENT_W.V);
        v_scale = _mm_or_ps(v_scale, v_cos.V);
        v_normal = _mm_mul_ps(v_normal, v_scale);
        return { v_normal };
#endif
    }

    mathinline Quaternion mathcall Quaternion::RotationAxis(Vector3 axis, float angle) noexcept
    {
        GX_ASSERT(!Vector3::IsEqual(axis, { Vector4::Zero().V }));
        GX_ASSERT(!Vector3::IsInfinite(axis));

        auto v_normal = Vector3::Normalize(axis);
        auto v_result = Quaternion::RotationNormal(v_normal, angle);
        return v_result;
    }

    mathinline Quaternion mathcall Quaternion::RotationMatrix(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result;

        auto r22 = m.M.M[2][2];
        if (r22 <= 0.0F)
        {
            auto dif10 = m.M.M[1][1] - m.M.M[0][0];
            auto omr22 = 1.0F - r22;
            if (dif10 <= 0.0F)
            {
                auto fourXSqr = omr22 - dif10;
                auto inv4x = 0.5F / sqrtf(fourXSqr);
                v_result.V.F[0] = fourXSqr * inv4x;
                v_result.V.F[1] = (m.M.M[0][1] + m.M.M[1][0]) * inv4x;
                v_result.V.F[2] = (m.M.M[0][2] + m.M.M[2][0]) * inv4x;
                v_result.V.F[3] = (m.M.M[1][2] - m.M.M[2][1]) * inv4x;
            }
            else
            {
                auto fourYSqr = omr22 + dif10;
                auto inv4y = 0.5F / sqrtf(fourYSqr);
                v_result.V.F[0] = (m.M.M[0][1] + m.M.M[1][0]) * inv4y;
                v_result.V.F[1] = fourYSqr * inv4y;
                v_result.V.F[2] = (m.M.M[1][2] + m.M.M[2][1]) * inv4y;
                v_result.V.F[3] = (m.M.M[2][0] - m.M.M[0][2]) * inv4y;
            }
        }
        else
        {
            auto sum10 = m.M.M[1][1] + m.M.M[0][0];
            auto opr22 = 1.0F + r22;
            if (sum10 <= 0.0F)
            {
                auto fourZSqr = opr22 - sum10;
                auto inv4z = 0.5F / sqrtf(fourZSqr);
                v_result.V.F[0] = (m.M.M[0][2] + m.M.M[2][0]) * inv4z;
                v_result.V.F[1] = (m.M.M[1][2] + m.M.M[2][1]) * inv4z;
                v_result.V.F[2] = fourZSqr * inv4z;
                v_result.V.F[3] = (m.M.M[0][1] - m.M.M[1][0]) * inv4z;
            }
            else
            {
                auto fourWSqr = opr22 + sum10;
                auto inv4w = 0.5f / sqrtf(fourWSqr);
                v_result.V.F[0] = (m.M.M[1][2] - m.M.M[2][1]) * inv4w;
                v_result.V.F[1] = (m.M.M[2][0] - m.M.M[0][2]) * inv4w;
                v_result.V.F[2] = (m.M.M[0][1] - m.M.M[1][0]) * inv4w;
                v_result.V.F[3] = fourWSqr * inv4w;
            }
        }

        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 xmpmmp = { { { +1.0F, -1.0F, -1.0F, +1.0F } } };
        static const Detail::Vector4F32 xmmpmp = { { { -1.0F, +1.0F, -1.0F, +1.0F } } };
        static const Detail::Vector4F32 xmmmpp = { { { -1.0F, -1.0F, +1.0F, +1.0F } } };

        auto r0 = m.M.R[0];
        auto r1 = m.M.R[1];
        auto r2 = m.M.R[2];

        auto r00 = _mm_permute_ps(r0, _MM_SHUFFLE(0, 0, 0, 0));
        auto r11 = _mm_permute_ps(r1, _MM_SHUFFLE(1, 1, 1, 1));
        auto r22 = _mm_permute_ps(r2, _MM_SHUFFLE(2, 2, 2, 2));

        auto r11mr00 = _mm_sub_ps(r11, r00);
        auto x2gey2 = _mm_cmple_ps(r11mr00, Detail::VEC4_ZERO_4.V);

        auto r11pr00 = _mm_add_ps(r11, r00);
        auto z2gew2 = _mm_cmple_ps(r11pr00, Detail::VEC4_ZERO_4.V);

        auto x2py2gez2pw2 = _mm_cmple_ps(r22, Detail::VEC4_ZERO_4.V);

        auto t0 = _mm_mul_ps(xmpmmp, r00);
        auto t1 = _mm_mul_ps(xmmpmp, r11);
        auto t2 = _mm_mul_ps(xmmmpp, r22);

        auto x2y2z2w2 = _mm_add_ps(t0, t1);
        x2y2z2w2 = _mm_add_ps(t2, x2y2z2w2);
        x2y2z2w2 = _mm_add_ps(x2y2z2w2, Detail::VEC4_ONE_4.V);

        t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 2, 2, 1));
        t1 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 0, 0));
        t1 = _mm_permute_ps(t1, _MM_SHUFFLE(1, 3, 2, 0));
        auto xyxzyz = _mm_add_ps(t0, t1);

        t0 = _mm_shuffle_ps(r2, r1, _MM_SHUFFLE(0, 0, 0, 1));
        t1 = _mm_shuffle_ps(r1, r0, _MM_SHUFFLE(1, 2, 2, 2));
        t1 = _mm_permute_ps(t1, _MM_SHUFFLE(1, 3, 2, 0));
        auto xwywzw = _mm_sub_ps(t0, t1);
        xwywzw = _mm_mul_ps(xmmpmp, xwywzw);

        t0 = _mm_shuffle_ps(x2y2z2w2, xyxzyz, _MM_SHUFFLE(0, 0, 1, 0));
        t1 = _mm_shuffle_ps(x2y2z2w2, xwywzw, _MM_SHUFFLE(0, 2, 3, 2));
        t2 = _mm_shuffle_ps(xyxzyz, xwywzw, _MM_SHUFFLE(1, 0, 2, 1));

        auto tensor0 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(2, 0, 2, 0));
        auto tensor1 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(3, 1, 1, 2));
        auto tensor2 = _mm_shuffle_ps(t2, t1, _MM_SHUFFLE(2, 0, 1, 0));
        auto tensor3 = _mm_shuffle_ps(t2, t1, _MM_SHUFFLE(1, 2, 3, 2));

        t0 = _mm_and_ps(x2gey2, tensor0);
        t1 = _mm_andnot_ps(x2gey2, tensor1);
        t0 = _mm_or_ps(t0, t1);
        t1 = _mm_and_ps(z2gew2, tensor2);
        t2 = _mm_andnot_ps(z2gew2, tensor3);
        t1 = _mm_or_ps(t1, t2);
        t0 = _mm_and_ps(x2py2gez2pw2, t0);
        t1 = _mm_andnot_ps(x2py2gez2pw2, t1);
        t2 = _mm_or_ps(t0, t1);

        t0 = Vector4::Length({ t2 }).V;
        return { _mm_div_ps(t2, t0) };
#endif
    }

    mathinline void mathcall Quaternion::ToAxisAngle(Vector3* axis, float* angle, Quaternion q) noexcept
    {
        GX_ASSERT(axis != nullptr);
        GX_ASSERT(angle != nullptr);

        (*axis) = { q.V };
        (*angle) = 2.0F * Acos(Vector4::GetW({ q.V }));
    }
}