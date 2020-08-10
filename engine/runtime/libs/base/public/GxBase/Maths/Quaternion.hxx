#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Dot(T a, T b) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { Dot(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    template <typename T>
    mathinline Vector4 mathcall Length(T v) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { Length(Vector4{ v.V }).V };
    }

    template <typename T>
    mathinline Vector4 mathcall LengthSquared(T v) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { LengthSquared(Vector4{ v.V }).V };
    }

    template <typename T>
    mathinline Vector4 mathcall ReciprocalLength(T v) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { ReciprocalLength(Vector4{ v.V }).V };
    }

    template <typename T>
    mathinline T mathcall Normalize(T v) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { Normalize(Vector4{ v.V }).V };
    }

    template <typename T>
    mathinline T mathcall NormalizeEst(T v) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { NormalizeEst(Vector4{ v.V }).V };
    }

    template <typename T>
    mathinline T mathcall Identity() noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return { Impl::c_V4_F32_PositiveUnitW.V };
    }

    template <typename T>
    mathinline bool mathcall IsIdentity(T q) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return IsEqual(Vector4{ q.V }, Vector4{ Impl::c_V4_F32_PositiveUnitW.V });
    }

    template <typename T>
    mathinline bool mathcall IsIdentity(T q, Vector4 epsilon) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        return IsEqual(Vector4{ q.V }, Vector4{ Impl::c_V4_F32_PositiveUnitW.V }, epsilon);
    }

    template <typename T>
    mathinline T mathcall Conjugate(T q) noexcept
        requires(Impl::IsQuaternion<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            -q.V.F[0],
            -q.V.F[1],
            -q.V.F[2],
            q.V.F[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const flip_xyz{ { {
            -1.0F,
            -1.0F,
            -1.0F,
            1.0F,
        } } };

        __m128 const result = _mm_mul_ps(q.V, flip_xyz.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Inverse(T q) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        Vector4 const zero            = Zero<Vector4>();
        Vector4 const length          = Length(q);
        Quaternion const conj         = Conjugate(q);
        Bool4 const control           = CompareLessEqual(length, Epsilon<Vector4>());
        Vector4 const normalized_conj = Divide(Vector4{ conj.V }, length);
        Vector4 const result          = Select(normalized_conj, zero, control);
        return Quaternion{ result.V };
    }

    template <typename T>
    mathinline T mathcall Multiply(T q1, T q2) noexcept
        requires(Impl::IsQuaternion<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (q1.V.F[3] * q2.V.F[0]) + (q1.V.F[0] * q2.V.F[3]) + (q1.V.F[1] * q2.V.F[2]) - (q1.V.F[2] * q2.V.F[1]),
            (q1.V.F[3] * q2.V.F[1]) + (q1.V.F[1] * q2.V.F[3]) + (q1.V.F[2] * q2.V.F[0]) - (q1.V.F[0] * q2.V.F[2]),
            (q1.V.F[3] * q2.V.F[2]) + (q1.V.F[2] * q2.V.F[3]) + (q1.V.F[0] * q2.V.F[1]) - (q1.V.F[1] * q2.V.F[0]),
            (q1.V.F[3] * q2.V.F[3]) - (q1.V.F[0] * q2.V.F[0]) - (q1.V.F[1] * q2.V.F[1]) - (q1.V.F[2] * q2.V.F[2]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const control{ { { 1.0F, 1.0F, 1.0F, -1.0F } } };

        __m128 const q1_xyzw = q1.V;
        __m128 const q2_xyzw = q2.V;

        __m128 const q1_wwww = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r0      = _mm_mul_ps(q1_wwww, q2_xyzw);

        __m128 const q1_xyzx = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(0, 2, 1, 0));
        __m128 const q2_wwwx = _mm_permute_ps(q2_xyzw, _MM_SHUFFLE(0, 3, 3, 3));
        __m128 const r1      = _mm_mul_ps(q1_xyzx, q2_wwwx);

        __m128 const q2_zxyy = _mm_permute_ps(q2_xyzw, _MM_SHUFFLE(1, 1, 0, 2));
        __m128 const q1_yzxy = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(1, 0, 2, 1));

        __m128 const r4      = Impl::avx_fmadd_f32x4(q1_yzxy, q2_zxyy, r1);
        __m128 const r6      = Impl::avx_fmadd_f32x4(r4, control.V, r0);
        __m128 const q1_zxyz = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(2, 1, 0, 2));
        __m128 const q2_yzxz = _mm_permute_ps(q2_xyzw, _MM_SHUFFLE(2, 0, 2, 1));

        __m128 const r7 = Impl::avx_fnmadd_f32x4(q1_zxyz, q2_yzxz, r6);

        return { r7 };
#endif
    }

    mathinline Vector3 Rotate(Vector3 v, Quaternion q) noexcept
    {
        Quaternion const a = Select<Quaternion>(
            Quaternion{ Impl::c_V4_U32_Mask_1110.V },
            Quaternion{ v.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Quaternion const qn   = Conjugate(q);
        Quaternion const qa   = Multiply(q, a);
        Quaternion const qaqn = Multiply(qa, qn);
        return Vector3{ qaqn.V };
    }

    mathinline Vector3 InverseRotate(Vector3 v, Quaternion q) noexcept
    {
        Quaternion const a = Select<Quaternion>(
            Quaternion{ Impl::c_V4_U32_Mask_1110.V },
            Quaternion{ v.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Quaternion const qn   = Conjugate(q);
        Quaternion const qna  = Multiply(qn, a);
        Quaternion const qnaq = Multiply(qna, q);
        return Vector3{ qnaq.V };
    }

    template <typename T>
    mathinline T mathcall Exp(T q) noexcept
        requires(Impl::IsQuaternion<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector3 const q_xyz{ q.V };
        Vector4 const q_dot     = Dot(q_xyz, q_xyz);
        Vector4 const v_rcp_len = InvSqrt(q_dot);
        Vector4 const v_len     = Reciprocal(v_rcp_len);

        Vector4 sinlen;
        Vector4 coslen;
        SinCos(sinlen, coslen, v_len);

        Vector4 const r0     = Multiply(Multiply(Vector4{ q.V }, v_rcp_len), sinlen);
        Vector4 const r1     = Select(coslen, r0, Bool4{ Impl::c_V4_U32_Mask_1110.V });
        Vector4 const w      = SplatW(Vector4{ q.V });
        Vector4 const wexp   = Exp(w);
        Vector4 const result = Multiply(r1, wexp);
        return Quaternion{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_len_sq  = _mm_dp_ps(q.V, q.V, 0x7F);
        __m128 const v_rcp_len = _mm_rsqrt_ps(v_len_sq);
        __m128 const v_len     = _mm_rcp_ps(v_rcp_len);

#if GRAPHYTE_MATH_SVML
        __m128 coslen;
        __m128 const sinlen = _mm_sincos_ps(&coslen, v_len);
#else
        float const f_len         = _mm_cvtss_f32(v_len);
        __m128 const coslen       = _mm_set_ps1(cosf(f_len));
        __m128 const sinlen       = _mm_set_ps1(sinf(f_len));
#endif
        __m128 const r_xyzw = _mm_mul_ps(_mm_mul_ps(q.V, v_rcp_len), sinlen);

        // {x,y,z,coslen}
        __m128 const r0 = _mm_and_ps(r_xyzw, Impl::c_V4_U32_Mask_1110.V);
        __m128 const r1 = _mm_andnot_ps(Impl::c_V4_U32_Mask_1110.V, coslen);
        __m128 const r2 = _mm_or_ps(r0, r1);

        // w = q.wwww
        __m128 const q_w = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));

        // exp(w)
#if GRAPHYTE_MATH_SVML
        __m128 const q_w_exp = _mm_exp_ps(q_w);
#else
        float const f_q_w         = _mm_cvtss_f32(q_w);
        __m128 const q_w_exp      = _mm_set_ps1(expf(f_q_w));
#endif

        __m128 const result = _mm_mul_ps(r2, q_w_exp);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Log(T q) noexcept
        requires(Impl::IsQuaternion<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const qv{ q.V };
        Vector3 const q_xyz{ qv.V };
        Vector4 const v_len_sq = Dot(q_xyz, q_xyz);

        Vector4 const q_w      = SplatW(Vector4{ q.V });
        Vector4 const q_len_sq = MultiplyAdd(q_w, q_w, v_len_sq);

        Vector4 const s       = Multiply(Acos(Clamp(Multiply(q_w, InvSqrt(q_len_sq)), Vector4{ Impl::c_V4_F32_Negative_One.V }, Vector4{ Impl::c_V4_F32_One.V })), InvSqrt(v_len_sq));
        Vector4 const q_xyz_s = Multiply(qv, s);
        Vector4 const w       = Multiply(Log(q_len_sq), 0.5F);

        Quaternion r0{ Select(w, Vector4{ q_xyz_s.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V }).V };
        return r0;
#elif GRAPHYTE_HW_AVX
        __m128 const v_len_sq = _mm_dp_ps(q.V, q.V, 0x7F);
        __m128 const q_w      = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));

        __m128 const q_len_sq = Impl::avx_fmadd_f32x4(q_w, q_w, v_len_sq);

        __m128 const none = _mm_set_ps1(-1.0F);
        __m128 const pone = _mm_set_ps1(1.0F);

        __m128 const rcp          = _mm_mul_ps(q_w, _mm_rsqrt_ps(q_len_sq));
        __m128 const clamped      = _mm_max_ps(_mm_min_ps(rcp, pone), none);

#if GRAPHYTE_MATH_SVML
        __m128 const acos_clamped = _mm_acos_ps(clamped);
#else
        __m128 const acos_clamped = _mm_set_ps1(acosf(_mm_cvtss_f32(clamped)));
#endif

        __m128 const s       = _mm_mul_ps(acos_clamped, _mm_rsqrt_ps(v_len_sq));
        __m128 const q_xyz_s = _mm_mul_ps(q.V, s);

#if GRAPHYTE_MATH_SVML
        __m128 const w       = _mm_mul_ps(_mm_log_ps(q_len_sq), _mm_set_ps1(0.5F));
#else
        __m128 const w            = _mm_set_ps1(logf(_mm_cvtss_f32(q_len_sq)) * 0.5F);
#endif

        __m128 const r0 = _mm_and_ps(q_xyz_s, Impl::c_V4_U32_Mask_1110.V);
        __m128 const r1 = _mm_andnot_ps(Impl::c_V4_U32_Mask_1110.V, w);
        __m128 const r2 = _mm_or_ps(r0, r1);
        return { r2 };
#endif
    }

    template <typename T>
    mathinline T mathcall CreateFromEuler(Vector3 angles) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        static Impl::ConstFloat32x4 const sign{ { {
            1.0F,
            -1.0F,
            -1.0F,
            1.0F,
        } } };

        Vector4 const half_angles = Multiply(Vector4{ angles.V }, { Impl::c_V4_F32_One_Half.V });

        Vector4 sin_angles;
        Vector4 cos_angles;
        SinCos(sin_angles, cos_angles, half_angles);

        Vector4 const sccc_xxxx = Permute<0, 4, 4, 4>(sin_angles, cos_angles);
        Vector4 const cscc_yyyy = Permute<5, 1, 5, 5>(sin_angles, cos_angles);
        Vector4 const ccsc_zzzz = Permute<6, 6, 2, 6>(sin_angles, cos_angles);

        Vector4 const csss_xxxx = Permute<0, 4, 4, 4>(cos_angles, sin_angles);
        Vector4 const scss_yyyy = Permute<5, 1, 5, 5>(cos_angles, sin_angles);
        Vector4 const sscs_zzzz = Permute<6, 6, 2, 6>(cos_angles, sin_angles);

        Vector4 const qa0 = Multiply(csss_xxxx, Vector4{ sign.V });
        Vector4 const qb0 = Multiply(sccc_xxxx, cscc_yyyy);
        Vector4 const qa1 = Multiply(qa0, scss_yyyy);
        Vector4 const qb1 = Multiply(qb0, ccsc_zzzz);
        Vector4 const q   = MultiplyAdd(qa1, sscs_zzzz, qb1);
        return Quaternion{ q.V };
    }

    template <typename T>
    mathinline T mathcall CreateFromEuler(float x, float y, float z) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        Vector3 const angles    = Make<Vector3>(x, y, z);
        Quaternion const result = CreateFromEuler<Quaternion>(angles);
        return result;
    }

    template <typename T>
    mathinline T mathcall CreateFromNormalAngle(Vector3 normal, float angle) noexcept
        requires(Impl::IsQuaternion<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 qv = Select(Vector4{ Impl::c_V4_F32_One.V }, Vector4{ normal.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });

        float fsin;
        float fcos;
        SinCos(fsin, fcos, 0.5F * angle);

        Vector4 const scale  = Make<Vector4>(fsin, fsin, fsin, fcos);
        Vector4 const result = Multiply(qv, scale);
        return Quaternion{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const normal_xyz  = _mm_and_ps(normal.V, Impl::c_V4_U32_Mask_1110.V);
        __m128 const normal_xyz1 = _mm_or_ps(normal_xyz, Impl::c_V4_F32_PositiveUnitW.V);
        __m128 const scale       = _mm_set_ps1(0.5F * angle);

        Vector4 vsin;
        Vector4 vcos;
        SinCos(vsin, vcos, Vector4{ scale });

        __m128 const sin_xyzn = _mm_and_ps(vsin.V, Impl::c_V4_U32_Mask_1110.V);
        __m128 const cos_nnnw = _mm_and_ps(vcos.V, Impl::c_V4_U32_Mask_0001.V);

        __m128 const sincos_xyzw = _mm_or_ps(sin_xyzn, cos_nnnw);
        __m128 const result      = _mm_mul_ps(normal_xyz1, sincos_xyzw);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall CreateFromAxisAngle(Vector3 axis, float angle) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        GX_ASSERT(IsNotEqual(axis, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(axis));

        Vector3 const normal    = Normalize(axis);
        Quaternion const result = CreateFromNormalAngle<Quaternion>(normal, angle);
        return result;
    }

    mathinline void mathcall ToAxisAngle(Vector3& axis, float& angle, Quaternion q) noexcept
    {
        axis  = Vector3{ q.V };
        angle = 2.0f * Acos(GetW(q));
    }

    template <typename T>
    mathinline T mathcall CreateFromMatrix(Matrix m) noexcept
        requires(Impl::IsQuaternion<T>)
    {
        //
        // Converting a Rotation Matrix to a Quaternion
        // Mike Day, Insomniac Gamesmday@insomniacgames.com
        //
        //  if (m22 < 0)
        //  {
        //      if (m00 > m11)
        //      {
        //          t = 1 + m00 - m11 - m22;
        //          q = quat(t, m01 + m10, m20 + m02, m12 - m21);
        //      }
        //      else
        //      {
        //          t = 1 - m00 + m11 - m22;
        //          q = quat(m01 + m10, t, m12 + m21, m20 - m02);
        //      }
        //  }
        //  else
        //  {
        //      if (m00 < -m11)
        //      {
        //          t = 1 - m00 - m11 + m22;
        //          q = quat(m20 + m02, m12 + m21, t, m01 - m10);
        //      }
        //      else
        //      {
        //          t = 1 + m00 + m11 + m22;
        //          q = quat(m12 - m21, m20 - m02, m01 - m10, t);
        //      }
        //  }
        //
        //  q *= 0.5 / Sqrt(t);
        //

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result;

        float const m22 = m.M.M[2][2];

        if (m22 <= 0.0f)
        {
            // (x*x + y*y) >= (z*z + w*w)
            float const diff_m11_m00 = m.M.M[1][1] - m.M.M[0][0];
            float const diff_one_m22 = 1.0f - m22;

            if (diff_m11_m00 <= 0.0f)
            {
                // (x*x) >= (y*y)
                float const x_sqr = diff_one_m22 - diff_m11_m00;
                float const x_inv = 0.5f / sqrtf(x_sqr);

                result.F[0] = x_sqr * x_inv;
                result.F[1] = (m.M.M[0][1] + m.M.M[1][0]) * x_inv;
                result.F[2] = (m.M.M[0][2] + m.M.M[2][0]) * x_inv;
                result.F[3] = (m.M.M[1][2] - m.M.M[2][1]) * x_inv;
            }
            else
            {
                // (y*y) >= (x*x)
                float const y_sqr = diff_one_m22 + diff_m11_m00;
                float const y_inv = 0.5f / sqrtf(y_sqr);

                result.F[0] = (m.M.M[0][1] + m.M.M[1][0]) * y_inv;
                result.F[1] = y_sqr * y_inv;
                result.F[2] = (m.M.M[1][2] + m.M.M[2][1]) * y_inv;
                result.F[3] = (m.M.M[2][0] - m.M.M[0][2]) * y_inv;
            }
        }
        else
        {
            // (z*z + w*w) >= (x*x + y*y)
            float const sum_m11_m00 = m.M.M[1][1] + m.M.M[0][0];
            float const sum_one_m22 = 1.0f + m22;

            if (sum_m11_m00 <= 0.0f)
            {
                // (z*z) >= (w*w)
                float const z_sqr = sum_one_m22 - sum_m11_m00;
                float const z_inv = 0.5f / sqrtf(z_sqr);

                result.F[0] = (m.M.M[0][2] + m.M.M[2][0]) * z_inv;
                result.F[1] = (m.M.M[1][2] + m.M.M[2][1]) * z_inv;
                result.F[2] = z_sqr * z_inv;
                result.F[3] = (m.M.M[0][1] - m.M.M[1][0]) * z_inv;
            }
            else
            {
                // (w*w) >= (z*z)
                float const w_sqr = sum_one_m22 + sum_m11_m00;
                float const w_inv = 0.5f / sqrtf(w_sqr);

                result.F[0] = (m.M.M[1][2] - m.M.M[2][1]) * w_inv;
                result.F[1] = (m.M.M[2][0] - m.M.M[0][2]) * w_inv;
                result.F[2] = (m.M.M[0][1] - m.M.M[1][0]) * w_inv;
                result.F[3] = w_sqr * w_inv;
            }
        }

        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const const_p1_m1_m1_p1{ { { +1.0f, -1.0f, -1.0f, +1.0f } } };
        static Impl::ConstFloat32x4 const const_m1_p1_m1_p1{ { { -1.0f, +1.0f, -1.0f, +1.0f } } };
        static Impl::ConstFloat32x4 const const_m1_m1_p1_p1{ { { -1.0f, -1.0f, +1.0f, +1.0f } } };

        __m128 const r0_xyz = m.M.R[0];
        __m128 const r1_xyz = m.M.R[1];
        __m128 const r2_xyz = m.M.R[2];

        // compute trace of matrix: m00 + m11 + m22
        __m128 const r0_xxx = _mm_permute_ps(r0_xyz, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const r1_yyy = _mm_permute_ps(r1_xyz, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r2_zzz = _mm_permute_ps(r2_xyz, _MM_SHUFFLE(2, 2, 2, 2));

        __m128 const sub_m11_m00   = _mm_sub_ps(r1_yyy, r0_xxx);
        __m128 const mask_x2_ge_y2 = _mm_cmple_ps(sub_m11_m00, _mm_setzero_ps());

        __m128 const add_m11_m00   = _mm_add_ps(r1_yyy, r0_xxx);
        __m128 const mask_z2_ge_w2 = _mm_cmple_ps(add_m11_m00, _mm_setzero_ps());

        __m128 const mask_x2y2_ge_z2w2 = _mm_cmple_ps(r2_zzz, _mm_setzero_ps());

        __m128 const t0_0 = _mm_mul_ps(const_p1_m1_m1_p1.V, r0_xxx);
        __m128 const t1_0 = _mm_mul_ps(const_m1_p1_m1_p1.V, r1_yyy);
        __m128 const t2_0 = _mm_mul_ps(const_m1_m1_p1_p1.V, r2_zzz);

        __m128 const x2y2z2w2_0 = _mm_add_ps(t0_0, t1_0);
        __m128 const x2y2z2w2_1 = _mm_add_ps(t2_0, x2y2z2w2_0);
        __m128 const x2y2z2w2_2 = _mm_add_ps(x2y2z2w2_1, Impl::c_V4_F32_One.V);

        __m128 const t0_1   = _mm_shuffle_ps(r0_xyz, r1_xyz, _MM_SHUFFLE(1, 2, 2, 1));
        __m128 const t1_1_a = _mm_shuffle_ps(r1_xyz, r2_xyz, _MM_SHUFFLE(1, 0, 0, 0));
        __m128 const t1_1   = _mm_permute_ps(t1_1_a, _MM_SHUFFLE(1, 3, 2, 0));

        __m128 const xyxzyz = _mm_add_ps(t0_1, t1_1);

        __m128 const t0_2   = _mm_shuffle_ps(r2_xyz, r1_xyz, _MM_SHUFFLE(0, 0, 0, 1));
        __m128 const t1_2_a = _mm_shuffle_ps(r1_xyz, r0_xyz, _MM_SHUFFLE(1, 2, 2, 2));
        __m128 const t1_2   = _mm_permute_ps(t1_2_a, _MM_SHUFFLE(1, 3, 2, 0));

        __m128 const xwywzw_0 = _mm_sub_ps(t0_2, t1_2);
        __m128 const xwywzw_1 = _mm_mul_ps(const_m1_p1_m1_p1.V, xwywzw_0);

        __m128 const t0_3 = _mm_shuffle_ps(x2y2z2w2_2, xyxzyz, _MM_SHUFFLE(0, 0, 1, 0));
        __m128 const t1_3 = _mm_shuffle_ps(x2y2z2w2_2, xwywzw_1, _MM_SHUFFLE(0, 2, 3, 2));
        __m128 const t2_3 = _mm_shuffle_ps(xyxzyz, xwywzw_1, _MM_SHUFFLE(1, 0, 2, 1));

        __m128 const tensor0 = _mm_shuffle_ps(t0_3, t2_3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const tensor1 = _mm_shuffle_ps(t0_3, t2_3, _MM_SHUFFLE(3, 1, 1, 2));
        __m128 const tensor2 = _mm_shuffle_ps(t2_3, t1_3, _MM_SHUFFLE(2, 0, 1, 0));
        __m128 const tensor3 = _mm_shuffle_ps(t2_3, t1_3, _MM_SHUFFLE(1, 2, 3, 2));

        __m128 const ga0 = _mm_and_ps(mask_x2_ge_y2, tensor0);
        __m128 const gb0 = _mm_andnot_ps(mask_x2_ge_y2, tensor1);
        __m128 const t0  = _mm_or_ps(ga0, gb0);

        __m128 const ga1 = _mm_and_ps(mask_z2_ge_w2, tensor2);
        __m128 const gb1 = _mm_andnot_ps(mask_z2_ge_w2, tensor3);
        __m128 const t1  = _mm_or_ps(ga1, gb1);

        __m128 const m0 = _mm_and_ps(mask_x2y2_ge_z2w2, t0);
        __m128 const m1 = _mm_andnot_ps(mask_x2y2_ge_z2w2, t1);
        __m128 const m2 = _mm_or_ps(m0, m1);

        __m128 const length = Length(Vector4{ m2 }).V;

        return { _mm_div_ps(m2, length) };
#endif
    }

    mathinline Quaternion mathcall Slerp(Quaternion q0, Quaternion q1, Vector4 t) noexcept
    {
        GX_ASSERT(GetX(t) == GetY(t) && GetX(t) == GetZ(t) && GetX(t) == GetW(t));

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        static constexpr Impl::ConstFloat32x4 const one_minus_epsilon{ { {
            1.0f - 0.00001f,
            1.0f - 0.00001f,
            1.0f - 0.00001f,
            1.0f - 0.00001f,
        } } };

        Vector4 const vcos_omega0{ Dot(q0, q1).V };

        Vector4 const vzero   = Zero<Vector4>();
        Bool4 const vc0 = CompareLess(vcos_omega0, vzero);
        Vector4 const vsign   = Select(Vector4{ Impl::c_V4_F32_One.V }, Vector4{ Impl::c_V4_F32_Negative_One.V }, vc0);

        Vector4 const vcos_omega1 = Multiply(vcos_omega0, vsign);
        Bool4 const vc1     = CompareLess(vcos_omega1, Vector4{ one_minus_epsilon.V });

        Vector4 const vsin_omega_sq = NegateMultiplySubtract(vcos_omega1, vcos_omega1, Vector4{ Impl::c_V4_F32_One.V });
        Vector4 const vsin_omega    = Sqrt(vsin_omega_sq);

        Vector4 const vomega = Atan2(vsin_omega, vcos_omega1);

        Vector4 const vsign_mask0 = SignMask<Vector4>();
        Vector4 const vv01a       = ShiftLeft(t, vzero, 2);
        Vector4 const vsign_mask1 = ShiftLeft(vsign_mask0, vzero, 3);
        Vector4 const vv01b       = Xor(vv01a, vsign_mask1);
        Vector4 const vv01c       = Add(Vector4{ Impl::c_V4_F32_PositiveUnitX.V }, vv01b);

        Vector4 const vinv_sin_omega = Reciprocal(vsin_omega);

        Vector4 const vs0a = Multiply(vv01c, vomega);
        Vector4 const vs0b = Sin(vs0a);
        Vector4 const vs0c = Multiply(vs0b, vinv_sin_omega);

        Vector4 const vs0d = Select(vv01c, vs0c, vcontrol1);

        Vector4 const vs1a = SplatY(vs0d);

        Vector4 const vs0e = SplatX(vs0d);
        Vector4 const vs1b = Multiply(vs1a, vsign);

        Vector4 const vresult0 = Multiply(Vector4{ q0.V }, vs0e);
        Vector4 const vresult1 = MultiplyAdd(Vector4{ q1.V }, vs1b, vresult0);

        return Quaternion{ vresult1.V };
#elif GRAPHYTE_HW_AVX
        static constexpr Impl::ConstFloat32x4 const one_minus_epsilon{ { {
            1.0f - 0.00001f,
            1.0f - 0.00001f,
            1.0f - 0.00001f,
            1.0f - 0.00001f,
        } } };

        static constexpr Impl::ConstFloat32x4 const sign_mask_2{ { { 0x80000000, 0x00000000, 0x00000000, 0x00000000 } } };

        __m128 const vcos_omega0 = Dot(q0, q1).V;

        __m128 const vzero = _mm_setzero_ps();
        __m128 const vc0   = _mm_cmplt_ps(vcos_omega0, vzero);
        __m128 const vsign = _mm_blendv_ps(Impl::c_V4_F32_One.V, Impl::c_V4_F32_Negative_One.V, vc0);
        __m128 const vcos_omega1 = _mm_mul_ps(vcos_omega0, vsign);
        __m128 const vc1         = _mm_cmplt_ps(vcos_omega1, one_minus_epsilon.V);
        __m128 const vsin_omega0 = _mm_mul_ps(vcos_omega1, vcos_omega1);
        __m128 const vsin_omega1 = _mm_sub_ps(Impl::c_V4_F32_One.V, vsin_omega0);
        __m128 const vsin_omega2 = _mm_sqrt_ps(vsin_omega1);

        __m128 const vomega = Atan2(Vector4{ vsin_omega2 }, Vector4{ vcos_omega1 }).V;
        __m128 const v01a   = _mm_permute_ps(t.V, _MM_SHUFFLE(2, 3, 0, 1));
        __m128 const v01b   = _mm_and_ps(v01a, Impl::c_V4_U32_Mask_1100.V);
        __m128 const v01c   = _mm_xor_ps(v01b, sign_mask_2.V);
        __m128 const v01d   = _mm_add_ps(Impl::c_V4_F32_PositiveUnitX.V, v01c);

        __m128 const vs0a = _mm_mul_ps(v01d, vomega);
        __m128 const vs0b = Sin(Vector4{ vs0a }).V;
        __m128 const vs0c = _mm_div_ps(vs0b, vsin_omega2);
        __m128 const vs0d = _mm_blendv_ps(v01d, vs0c, vc1);

        __m128 const vs1a = SplatY(Vector4{v01d}).V;
        __m128 const vs0e = SplatX(Vector4{v01d}).V;

        __m128 const vs1b = _mm_mul_ps(vs1a, vsign);

        __m128 const vresult0 = _mm_mul_ps(q0.V, vs0e);
        __m128 const vresult1 = Impl::avx_fmadd_f32x4(q1.V, vs1b, vresult0);
        return Quaternion{ vresult1 };
#endif
    }

    mathinline Quaternion mathcall Slerp(Quaternion q0, Quaternion q1, float t) noexcept
    {
        return Slerp(q0, q1, Make<Vector4>(t));
    }

    mathinline Quaternion mathcall Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, Vector4 t) noexcept
    {
        GX_ASSERT(GetX(t) == GetY(t) && GetX(t) == GetZ(t) && GetX(t) == GetW(t));

        Vector4 const two{ Impl::SplatConstant(2, 0) };

        Quaternion const q03 = Slerp(q0, q3, t);
        Quaternion const q12 = Slerp(q1, q2, t);

        Vector4 const t1 = NegateMultiplySubtract(t, t, t);
        Vector4 const t2 = Multiply(t1, two);

        Quaternion const result = Slerp(q03, q12, t2);
        return result;
    }

    mathinline Quaternion mathcall Squad(Quaternion q0, Quaternion q1, Quaternion q2, Quaternion q3, float t) noexcept
    {
        return Squad(q0, q1, q2, q3, Make<Vector4>(t));
    }

    mathinline void mathcall SquadSetup(
        Quaternion& out_a,
        Quaternion& out_b,
        Quaternion& out_c,
        Quaternion q0,
        Quaternion q1,
        Quaternion q2,
        Quaternion q3) noexcept
    {
        Quaternion const nq2{ Negate(Vector4{ q2.V }).V };
        Quaternion const nq0{ Negate(Vector4{ q0.V }).V };
        Quaternion const nq3{ Negate(Vector4{ q3.V }).V };

        Vector4 const vls12 = LengthSquared(Quaternion{ Add(Vector4{ q1.V }, Vector4{ q2.V }).V });
        Vector4 const vld12 = LengthSquared(Quaternion{ Subtract(Vector4{ q1.V }, Vector4{ q2.V }).V });

        Vector4 const vls01 = LengthSquared(Quaternion{ Add(Vector4{ q0.V }, Vector4{ q1.V }).V });
        Vector4 const vld01 = LengthSquared(Quaternion{ Subtract(Vector4{ q0.V }, Vector4{ q1.V }).V });

        Bool4 const vc1 = CompareLess(vls12, vld12);

        Quaternion const vsq2 = Select(q2, nq2, vc1);

        Vector4 const vls23 = LengthSquared(Quaternion{ Add(Vector4{ vsq2.V }, Vector4{ q3.V }).V });
        Vector4 const vld23 = LengthSquared(Quaternion{ Subtract(Vector4{ vsq2.V }, Vector4{ q3.V }).V });

        Bool4 const vc0 = CompareLess(vls01, vld01);
        Bool4 const vc2 = CompareLess(vls23, vld23);

        Quaternion const vsq0 = Select(q0, nq0, vc0);
        Quaternion const vsq3 = Select(q3, nq3, vc2);

        Quaternion const qinv_q1 = Inverse(q1);
        Quaternion const qinv_q2 = Inverse(vsq2);

        Quaternion const qln_q0 = Log(Multiply(qinv_q1, vsq0));
        Quaternion const qln_q1 = Log(Multiply(qinv_q1, vsq2));
        Quaternion const qln_q2 = Log(Multiply(qinv_q2, q1));
        Quaternion const qln_q3 = Log(Multiply(qinv_q2, vsq3));

        Vector4 const v_negative_one_quater{ Impl::SplatConstant(-1, 2) };

        Quaternion const qe_q02{ Multiply(Add(Vector4{ qln_q0.V }, Vector4{ qln_q2.V }), v_negative_one_quater).V };
        Quaternion const qe_q13{ Multiply(Add(Vector4{ qln_q1.V }, Vector4{ qln_q3.V }), v_negative_one_quater).V };

        Quaternion const qexp_q02 = Exp(qe_q02);
        Quaternion const qexp_q13 = Exp(qe_q13);

        out_a = Multiply(q1, qexp_q02);
        out_b = Multiply(vsq2, qexp_q13);
        out_c = vsq2;
    }

    mathinline Quaternion mathcall Barycentric(Quaternion q0, Quaternion q1, Quaternion q2, Vector4 f, Vector4 g) noexcept
    {
        GX_ASSERT(GetX(f) == GetY(f) && GetX(f) == GetZ(f) && GetX(f) == GetW(f));
        GX_ASSERT(GetX(g) == GetY(g) && GetX(g) == GetZ(g) && GetX(g) == GetW(g));

        Vector4 const epsilon{ Impl::SplatConstant(1, 16) };
        Vector4 const fg = Add(f, g);

        Quaternion result;

        if (InBounds(fg, epsilon))
        {
            result = q0;
        }
        else
        {
            Quaternion const q01 = Slerp(q0, q1, fg);
            Quaternion const q02 = Slerp(q0, q2, fg);
            Vector4 const inv_fg = Reciprocal(fg);
            Vector4 const vt     = Multiply(g, inv_fg);
            result               = Slerp(q01, q02, vt);
        }

        return result;
    }

    mathinline Quaternion mathcall Barycentric(Quaternion q0, Quaternion q1, Quaternion q2, float f, float g) noexcept
    {
        float const fg = f + g;

        Quaternion result;

        if ((fg < 0.00001f) && (fg > -0.00001f))
        {
            result = q0;
        }
        else
        {
            Quaternion const q01 = Slerp(q0, q1, fg);
            Quaternion const q02 = Slerp(q0, q2, fg);
            result               = Slerp(q01, q02, g / fg);
        }

        return result;
    }
}
