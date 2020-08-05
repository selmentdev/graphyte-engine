#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Matrix.hxx>

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall DotCoord(Plane p, Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        // v4 = {v3, 1}
        Vector4 const v4_1 = Select(Vector4{ Impl::c_V4_F32_One.V }, Vector4{ v.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
        Vector4 const result = Dot(Vector4{ p.V }, v4_1);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const mask = Impl::c_V4_U32_Mask_1110.V;

        // select {_,_,_,1}
        __m128 const one4 = _mm_andnot_ps(mask, Impl::c_V4_F32_One.V);
        // select {a,b,c,_}
        __m128 const abcn = _mm_and_ps(v.V, mask);
        // select {a,b,c,1}
        __m128 const abc1 = _mm_or_ps(one4, abcn);
        // r = dot4(abc1, p);
        __m128 const r = _mm_dp_ps(abc1, p.V, 0xFF);
        return { r };
#endif
    }

    mathinline Vector4 mathcall DotNormal(Plane p, Vector3 n) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return Vector4{ Dot(Vector3{ p.V }, n).V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_dp_ps(p.V, n.V, 0x3F);
        return { result };
#endif
    }

    mathinline Plane mathcall Normalize(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = sqrtf(
            (p.V.F[0] * p.V.F[0]) * (p.V.F[1] * p.V.F[1]) * (p.V.F[2] * p.V.F[2]));

        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Impl::ConstFloat32x4 const result{ { {
            p.V.F[0] * length,
            p.V.F[1] * length,
            p.V.F[2] * length,
            p.V.F[3] * length,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_sq = _mm_dp_ps(p.V, p.V, 0b0111'1111);
        __m128 const length = _mm_sqrt_ps(length_sq);
        __m128 const mask = _mm_cmpneq_ps(length_sq, Impl::c_V4_F32_Positive_Infinity.V);
        __m128 const normalized = _mm_div_ps(p.V, length);
        __m128 const result = _mm_and_ps(normalized, mask);
        return { result };
#endif
    }

    mathinline Plane mathcall NormalizeEst(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length{ ReciprocalLengthEst(Vector3{ p.V }).V };
        Vector4 const result = Multiply(Vector4{ p.V }, length);
        return Plane{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_dp_ps(p.V, p.V, 0x7F);
        __m128 const rcp_length = _mm_rsqrt_ps(length);
        __m128 const result = _mm_mul_ps(p.V, rcp_length);
        return { result };
#endif
    }

    // tag: this probably could be handled by template version
    mathinline bool mathcall IsEqual(Plane p1, Plane p2, Vector4 epsilon) noexcept
    {
        Vector4 const np1{ Normalize(p1).V };
        Vector4 const np2{ Normalize(p2).V };
        return IsEqual(np1, np2, epsilon);
    }

    mathinline Plane mathcall Transform(Plane p, Matrix m) noexcept
    {
        Vector4 const pl{ p.V };

        Vector4 const vw = SplatW(pl);
        Vector4 const vz = SplatZ(pl);
        Vector4 const vy = SplatY(pl);
        Vector4 const vx = SplatX(pl);

        Vector4 const r0 = Multiply(vw, GetBaseW(m));
        Vector4 const r1 = MultiplyAdd(vz, GetBaseZ(m), r0);
        Vector4 const r2 = MultiplyAdd(vy, GetBaseY(m), r1);
        Vector4 const r3 = MultiplyAdd(vx, GetBaseX(m), r2);

        return Plane{ r3.V };
    }

    mathinline Plane mathcall CreateFromPointNormal(Vector3 point, Vector3 normal) noexcept
    {
        Vector3 const p_wwww = Dot(point, normal);
        Vector3 const n_wwww = Negate(p_wwww);
        Vector4 const abcw   = Select(Vector4{ n_wwww.V }, Vector4{ normal.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
        Plane const result{ abcw.V };
        return result;
    }

    mathinline Plane mathcall CreateFromPoints(Vector3 p1, Vector3 p2, Vector3 p3) noexcept
    {
        Vector3 const d_p21 = Subtract(p1, p2);
        Vector3 const d_p31 = Subtract(p1, p3);

        Vector3 const plane_perpendicular = Cross(d_p21, d_p31);
        Vector3 const plane_normal = Normalize(plane_perpendicular);

        Vector4 const neg_plane_distance = DotNormal(Plane{ plane_normal.V }, p1);
        Vector4 const plane_distance = Negate(neg_plane_distance);

        Vector4 const result = Select(
            plane_distance,
            Vector4{ plane_normal.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });
        Plane const plane{ result.V };
        return plane;
    }

    mathinline Matrix mathcall Reflect(Plane reflection) noexcept
    {
        GX_ASSERT(!IsEqual(Vector3{ reflection.V }, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(reflection));

        static Impl::ConstFloat32x4 const negative_two{ { { -2.0f,
            -2.0f,
            -2.0f,
            0.0f } } };

        Vector4 const vp{ Normalize(reflection).V };
        Vector4 const vs = Multiply(vp, Vector4{ negative_two.V });

        Vector4 const p_aaaa = SplatX(vp);
        Vector4 const p_bbbb = SplatY(vp);
        Vector4 const p_cccc = SplatZ(vp);
        Vector4 const p_dddd = SplatW(vp);

        Matrix result;

        result.M.R[0] = MultiplyAdd(p_aaaa, vs, UnitX<Vector4>()).V;
        result.M.R[1] = MultiplyAdd(p_bbbb, vs, UnitY<Vector4>()).V;
        result.M.R[2] = MultiplyAdd(p_cccc, vs, UnitZ<Vector4>()).V;
        result.M.R[3] = MultiplyAdd(p_dddd, vs, UnitW<Vector4>()).V;

        return result;
    }

    mathinline Matrix mathcall Shadow(Plane shadow, Vector4 light) noexcept
    {
        GX_ASSERT(!IsEqual(Vector3{ shadow.V }, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(shadow));

        Vector4 const vp{ Normalize(shadow).V };
        Vector4 const pp = Negate(vp);
        Vector4 const p_aaaa = SplatX(pp);
        Vector4 const p_bbbb = SplatY(pp);
        Vector4 const p_cccc = SplatZ(pp);
        Vector4 const p_dddd = SplatW(pp);

        Vector4 dot = Dot(vp, light);
        dot = Select(Vector4{ Impl::c_V4_U32_Mask_0001.V }, dot, Bool4{ Impl::c_V4_U32_Mask_0001.V });

        Matrix result;
        result.M.R[3] = MultiplyAdd(p_dddd, light, dot).V;
        dot = RotateLeft<1>(dot);
        result.M.R[2] = MultiplyAdd(p_cccc, light, dot).V;
        dot = RotateLeft<1>(dot);
        result.M.R[1] = MultiplyAdd(p_bbbb, light, dot).V;
        dot = RotateLeft<1>(dot);
        result.M.R[0] = MultiplyAdd(p_aaaa, light, dot).V;

        return result;
    }
}
