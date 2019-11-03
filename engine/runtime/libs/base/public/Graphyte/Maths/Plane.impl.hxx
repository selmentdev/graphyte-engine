#pragma once
#include <Graphyte/Maths/Plane.hxx>
#include <Graphyte/Maths/Vector4.hxx>
#include <Graphyte/Maths/Vector3.hxx>
#include <Graphyte/Maths/Matrix.hxx>

namespace Graphyte::Maths
{
    mathinline bool mathcall Plane::IsEqual(Plane p1, Plane p2) noexcept
    {
        return Vector4::IsEqual({ p1.V }, { p2.V });
    }

    mathinline bool mathcall Plane::IsEqual(Plane p1, Plane p2, Vector4 epsilon) noexcept
    {
        auto n_p1 = Plane::Normalize(p1);
        auto n_p2 = Plane::Normalize(p2);
        return Vector4::IsEqual({ n_p1.V }, { n_p2.V }, epsilon);
    }

    mathinline bool mathcall Plane::IsNotEqual(Plane p1, Plane p2) noexcept
    {
        return Vector4::IsNotEqual({ p1.V }, { p2.V });
    }

    mathinline bool mathcall Plane::IsNaN(Plane p) noexcept
    {
        return Vector4::IsNaN({ p.V });
    }

    mathinline bool mathcall Plane::IsInfinite(Plane p) noexcept
    {
        return Vector4::IsInfinite({ p.V });
    }

    mathinline Vector4 mathcall Plane::Dot(Plane p, Vector4 v) noexcept
    {
        return Vector4::Dot({ p.V }, v);
    }

    mathinline Vector4 mathcall Plane::DotCoord(Plane p, Vector3 v) noexcept
    {
        auto v_v3 = Vector4::Select({ Detail::VEC4_ONE_4.V }, { v.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto v_result = Vector4::Dot({ p.V }, v_v3);
        return v_result;
    }

    mathinline Vector4 mathcall Plane::DotNormal(Plane p, Vector3 v) noexcept
    {
        return Vector3::Dot({ p.V }, v);
    }

    mathinline Plane mathcall Plane::NormalizeEst(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector3::ReciprocalLengthEst({ p.V });
        v_result = Vector4::Multiply({ p.V }, v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(p.V, p.V, 0b0111'1111);
        auto v_result = _mm_rsqrt_ps(v_temp);
        return { _mm_mul_ps(v_result, p.V) };
#endif
    }

    mathinline Plane mathcall Plane::Normalize(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_length_sq = sqrtf(
            (p.V.F[0] * p.V.F[0]) + (p.V.F[1] * p.V.F[1]) + (p.V.F[2] * p.V.F[2])
        );

        if (f_length_sq > 0.0F)
        {
            f_length_sq = 1.0F / f_length_sq;
        }

        Detail::Vector4F32 v_result = { { {
                p.V.F[0] * f_length_sq,
                p.V.F[1] * f_length_sq,
                p.V.F[2] * f_length_sq,
                p.V.F[3] * f_length_sq,
            } } };

        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_length_sq = _mm_dp_ps(p.V, p.V, 0b0111'1111);
        auto v_result = _mm_sqrt_ps(v_length_sq);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Detail::VEC4_INFINITY.V);
        v_result = _mm_div_ps(p.V, v_result);
        v_result = _mm_and_ps(v_result, v_length_sq);
        return { v_result };
#endif
    }

    mathinline Vector3 mathcall Plane::IntersectLine(Plane p, Vector3 line_point1, Vector3 line_point2) noexcept
    {
        auto v_v1 = Vector3::Dot({ p.V }, line_point1);
        auto v_v2 = Vector3::Dot({ p.V }, line_point2);
        auto v_d = Vector4::Subtract(v_v1, v_v2);
        auto v_vt = Plane::DotCoord(p, line_point1);
        v_vt = Vector4::Divide(v_vt, v_d);

        auto v_point = Vector4::Subtract({ line_point2.V }, { line_point1.V });
        v_point = Vector4::MultiplyAdd(v_point, v_vt, { line_point1.V });

        auto v_zero = Vector4::Zero();
        auto v_control = Vector4::CompareEqual(v_d, v_zero, { Detail::VEC4_EPSILON.V });
        return { Vector4::Select(v_point, { Detail::VEC4_QNAN.V }, v_control).V };
    }

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

    mathinline Plane mathcall Plane::Transform(Plane p, Matrix m) noexcept
    {
        auto v_w = Vector4::SplatW({ p.V });
        auto v_z = Vector4::SplatZ({ p.V });
        auto v_y = Vector4::SplatY({ p.V });
        auto v_x = Vector4::SplatX({ p.V });

        auto v_result = Vector4::Multiply(v_w, { m.M.R[3] });
        v_result = Vector4::MultiplyAdd(v_z, { m.M.R[2] }, v_result);
        v_result = Vector4::MultiplyAdd(v_y, { m.M.R[1] }, v_result);
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);

        return { v_result.V };
    }

    mathinline Plane mathcall Plane::FromPointNormal(Vector3 point, Vector3 normal) noexcept
    {
        auto v_w = Vector3::Dot({ point.V }, normal);
        v_w = Vector4::Negate(v_w);
        return { Vector4::Select(v_w, { normal.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V };
    }

    mathinline Plane mathcall Plane::FromPoints(Vector3 point1, Vector3 point2, Vector3 point3) noexcept
    {
        auto v_v21 = Vector4::Subtract({ point1.V }, { point2.V });
        auto v_v31 = Vector4::Subtract({ point1.V }, { point3.V });

        auto v_n = Vector3::Cross({ v_v21.V }, { v_v31.V });
        v_n = Vector3::Normalize(v_n);

        auto v_d = Plane::DotNormal({ v_n.V }, point1);
        v_d = Vector4::Negate(v_d);

        auto v_result = Vector4::Select(v_d, { v_n.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        return { v_result.V };
    }
}
