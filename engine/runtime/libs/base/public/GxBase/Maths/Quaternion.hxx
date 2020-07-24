#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Comparizon.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Identity() noexcept
        requires(std::same_as<T, Quaternion>)
    {
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }

    template <typename T>
    mathinline bool mathcall IsIdentity(Quaternion q) noexcept
        requires(std::same_as<T, Quaternion>)
    {
        return IsEqual(Vector4{ q.V }, Vector4{ Impl::VEC4_POSITIVE_UNIT_W.V });
    }

    template <typename T>
    mathinline bool mathcall IsIdentity(Quaternion q, Vector4 epsilon) noexcept
        requires(std::same_as<T, Quaternion>)
    {
        return IsEqual(Vector4{ q.V }, Vector4{ Impl::VEC4_POSITIVE_UNIT_W.V }, epsilon);
    }

    template <typename T>
    mathinline T mathcall Conjugate(T q) noexcept
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
    {
        Vector4 const zero = Zero<Vector4>();
        Vector4 const length = Length(q);
        Quaternion const conj = Conjugate(q);
        Bool4 const control = CompareLessEqual(length, Epsilon<Vector4>());
        Vector4 const normalized_conj = Divide(Vector4{ conj.V }, length);
        Vector4 const result = Select(normalized_conj, zero, control);
        return Quaternion{ result.V };
    }

    template <typename T>
    mathinline T mathcall Multiply(T q1, T q2) noexcept
        requires(std::same_as<T, Quaternion>)
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
        __m128 const r0 = _mm_mul_ps(q1_wwww, q2_xyzw);

        __m128 const q1_xyzx = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(0, 2, 1, 0));
        __m128 const q2_wwwx = _mm_permute_ps(q2_xyzw, _MM_SHUFFLE(0, 3, 3, 3));
        __m128 const r1 = _mm_mul_ps(q1_xyzx, q2_wwwx);

        __m128 const q2_zxyy = _mm_permute_ps(q2_xyzw, _MM_SHUFFLE(1, 1, 0, 2));
        __m128 const q1_yzxy = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(1, 0, 2, 1));

        __m128 const r4 = Impl::avx_fmadd_f32x4(q1_yzxy, q2_zxyy, r1);
        __m128 const r6 = Impl::avx_fmadd_f32x4(r4, control.V, r0);
        __m128 const q1_zxyz = _mm_permute_ps(q1_xyzw, _MM_SHUFFLE(2, 1, 0, 2));
        __m128 const q2_yzxz = _mm_permute_ps(q2_xyzw, _MM_SHUFFLE(2, 0, 2, 1));

        __m128 const r7 = Impl::avx_fnmadd_f32x4(q1_zxyz, q2_yzxz, r6);

        return { r7 };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp(T q) noexcept
        requires(std::same_as<T, Quaternion>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector3 const q_xyz{ q.V };
        Vector4 const q_dot = Dot(q_xyz, q_xyz);
        Vector4 const v_rcp_len = InvSqrt(q_dot);
        Vector4 const v_len = Reciprocal(v_rcp_len);

        Vector4 sinlen;
        Vector4 coslen;
        SinCos(sinlen, coslen, v_len);

        Vector4 const r0 = Multiply(Multiply(Vector4{ q.V }, v_rcp_len), sinlen);
        Vector4 const r1 = Select(coslen, r0, Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
        Vector4 const w = SplatW(Vector4{ q.V });
        Vector4 const wexp = Exp(w);
        Vector4 const result = Multiply(r1, wexp);
        return Quaternion{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_len_sq = _mm_dp_ps(q.V, q.V, 0x7F);
        __m128 const v_rcp_len = _mm_rsqrt_ps(v_len_sq);
        __m128 const v_len = _mm_rcp_ps(v_rcp_len);

#if GRAPHYTE_MATH_SVML
        __m128 coslen;
        __m128 const sinlen = _mm_sincos_ps(&coslen, v_len);
#else
        float const f_len = _mm_cvtss_f32(v_len);
        __m128 const coslen = _mm_set_ps1(cosf(f_len));
        __m128 const sinlen = _mm_set_ps1(sinf(f_len));
#endif
        __m128 const r_xyzw = _mm_mul_ps(_mm_mul_ps(q.V, v_rcp_len), sinlen);

        // {x,y,z,coslen}
        __m128 const r0 = _mm_and_ps(r_xyzw, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const r1 = _mm_andnot_ps(Impl::VEC4_MASK_SELECT_1110.V, coslen);
        __m128 const r2 = _mm_or_ps(r0, r1);

        // w = q.wwww
        __m128 const q_w = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));

        // exp(w)
#if GRAPHYTE_MATH_SVML
        __m128 const q_w_exp = _mm_exp_ps(q_w);
#else
        float const f_q_w = _mm_cvtss_f32(q_w);
        __m128 const q_w_exp = _mm_set_ps1(expf(f_q_w));
#endif

        __m128 const result = _mm_mul_ps(r2, q_w_exp);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Log(T q) noexcept
        requires(std::same_as<T, Quaternion>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const qv{ q.V };
        Vector3 const q_xyz{ qv.V };
        Vector4 const v_len_sq = Dot(q_xyz, q_xyz);

        Vector4 const q_w = SplatW(Vector4{ q.V });
        Vector4 const q_len_sq = MultiplyAdd(q_w, q_w, v_len_sq);

        Vector4 const s = Multiply(Acos(Clamp(Multiply(q_w, InvSqrt(q_len_sq)), Vector4{ Impl::VEC4_NEGATIVE_ONE_4.V }, Vector4{ Impl::VEC4_ONE_4.V })), InvSqrt(v_len_sq));
        Vector4 const q_xyz_s = Multiply(qv, s);
        Vector4 const w = Multiply(Log(q_len_sq), 0.5F);

        Quaternion r0{ Select(w, Vector4{ q_xyz_s.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V }).V };
        return r0;
#elif GRAPHYTE_HW_AVX
        __m128 const v_len_sq = _mm_dp_ps(q.V, q.V, 0x7F);
        __m128 const q_w = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));

        __m128 const q_len_sq = Impl::avx_fmadd_f32x4(q_w, q_w, v_len_sq);

        __m128 const none = _mm_set_ps1(-1.0F);
        __m128 const pone = _mm_set_ps1(1.0F);

        __m128 const rcp = _mm_mul_ps(q_w, _mm_rsqrt_ps(q_len_sq));
        __m128 const clamped = _mm_max_ps(_mm_min_ps(rcp, pone), none);

#if GRAPHYTE_MATH_SVML
        __m128 const acos_clamped = _mm_acos_ps(clamped);
#else
        __m128 const acos_clamped = _mm_set_ps1(acosf(_mm_cvtss_f32(clamped)));
#endif

        __m128 const s = _mm_mul_ps(acos_clamped, _mm_rsqrt_ps(v_len_sq));
        __m128 const q_xyz_s = _mm_mul_ps(q.V, s);

#if GRAPHYTE_MATH_SVML
        __m128 const w = _mm_mul_ps(_mm_log_ps(q_len_sq), _mm_set_ps1(0.5F));
#else
        __m128 const w = _mm_set_ps1(logf(_mm_cvtss_f32(q_len_sq)) * 0.5F);
#endif

        __m128 const r0 = _mm_and_ps(q_xyz_s, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const r1 = _mm_andnot_ps(Impl::VEC4_MASK_SELECT_1110.V, w);
        __m128 const r2 = _mm_or_ps(r0, r1);
        return { r2 };
#endif
    }

    template <typename T>
    mathinline T mathcall CreateFromEuler(Vector3 angles) noexcept
        requires(std::same_as<T, Quaternion>)
    {
        static Impl::ConstFloat32x4 const sign{ { {
            1.0F,
            -1.0F,
            -1.0F,
            1.0F,
        } } };

        Vector4 const half_angles = Multiply(Vector4{ angles.V }, { Impl::VEC4_ONE_HALF_4.V });

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
        Vector4 const q = MultiplyAdd(qa1, sscs_zzzz, qb1);
        return Quaternion{ q.V };
    }

    template <typename T>
    mathinline T mathcall CreateFromEuler(float x, float y, float z) noexcept
        requires(std::same_as<T, Quaternion>)
    {
        Vector3 const angles = Make<Vector3>(x, y, z);
        Quaternion const result = CreateFromEuler<Quaternion>(angles);
        return result;
    }
}

#if false
namespace Graphyte::Maths
{
    mathinline Quaternion mathcall Slerp(Quaternion q0, Quaternion q1, Vector4 t) noexcept
    {
        GX_ASSERT(
            (GetX(t) == GetY(t)) && (GetX(t) == GetZ(t)) && (GetX(t) == GetW(t)));

#if GRAPHYTE_MATH_NO_INTRINSICS
        static const ConstFloat32x4 one_minus_epsilon{ { {
                1.0f - 0.00001f,
                1.0f - 0.00001f,
                1.0f - 0.00001f,
                1.0f - 0.00001f, } } };

        auto v_cos_omega = Dot(q0, q1);
        

#elif GRAPHYTE_HW_AVX
#else
#error Not implemented
#endif
    }

    mathinline Quaternion mathcall Slerp(Quaternion q0, Quaternion q1, float t) noexcept
    {
        Vector4 const vt = Make<Vector4>(t);
        return Slerp(q0, q1, vt);
    }
}
#endif
