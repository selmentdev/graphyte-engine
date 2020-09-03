#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Plane.hxx>

// =================================================================================================
// Intersections

namespace Graphyte::Maths
{
    [[nodiscard]] mathinline Vector3 mathcall LinePlaneIntersection(Plane plane, Vector3 start, Vector3 end) noexcept
    {
        Vector3 const plane_normal{ plane.V };
        Vector3 const plane_normal_dot_start = Dot(plane_normal, start);
        Vector3 const plane_normal_dot_end   = Dot(plane_normal, end);
        Vector3 const diff                   = Subtract(plane_normal_dot_start, plane_normal_dot_end);
        Vector4 const plane_dot_start        = DotCoord(plane, start);
        Vector4 const normalized             = Divide(plane_dot_start, Vector4{ diff.V });

        Vector3 const point_distance = Subtract(end, start);
        Vector3 const point_on_plane = MultiplyAdd(point_distance, Vector3{ normalized.V }, start);

        Vector3 const zero  = Zero<Vector3>();
        Bool4 const control = Bool4{ CompareEqual(diff, zero, Epsilon<Vector3>()).V };
        Vector3 const result{ Select(Vector4{ point_on_plane.V }, Nan<Vector4>(), control).V };
        return result;
    }

    mathinline void PlanePlaneIntersection(
        Vector3& out_line1,
        Vector3& out_line2,
        Plane plane1,
        Plane plane2) noexcept
    {
        Vector3 const cross0        = Cross(Vector3{ plane2.V }, Vector3{ plane1.V });
        Vector4 const cross0_length{ Length(cross0).V };
        Vector3 const cross1        = Cross(Vector3{ plane2.V }, cross0);
        Vector4 const plane1_wwww   = SplatW(Vector4{ plane1.V });
        Vector4 const point0        = Multiply(Vector4{ cross1.V }, plane1_wwww);
        Vector3 const cross2        = Cross(cross0, Vector3{ plane1.V });
        Vector4 const plane2_wwww   = SplatW(Vector4{ plane2.V });
        Vector4 const point1        = MultiplyAdd(Vector4{ cross2.V }, plane2_wwww, point0);
        Vector4 const linepoint1    = Divide(point1, cross0_length);
        Vector4 const linepoint2    = Add(linepoint1, Vector4{ cross0.V });
        Bool4 const control         = CompareLessEqual(cross0_length, Vector4{ Impl::c_V4_F32_Epsilon.V });

        out_line1 = Vector3{ Select(linepoint1, Nan<Vector4>(), control).V };
        out_line2 = Vector3{ Select(linepoint2, Nan<Vector4>(), control).V };
    }

    [[nodiscard]] mathinline Vector2 mathcall LineLineIntersection(
        Vector2 line1_start,
        Vector2 line1_end,
        Vector2 line2_start,
        Vector2 line2_end) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector2 const line1  = Subtract(line1_end, line1_start);
        Vector2 const line2  = Subtract(line2_end, line2_start);
        Vector2 const line12 = Subtract(line1_start, line2_start);

        Vector2 const c0 = Cross(line1, line2);
        Vector2 const c1 = Cross(line2, line12);

        Vector2 const zero = Zero<Vector2>();

        Vector2 result;

        if (IsEqual(c0, zero, Epsilon<Vector2>()))
        {
            if (IsEqual(c1, zero, Epsilon<Vector2>()))
            {
                // concident
                result = Infinity<Vector2>();
            }
            else
            {
                // parallel
                result = Nan<Vector2>();
            }
        }
        else
        {
            Vector2 const rcp_c0    = Reciprocal(c0);
            Vector2 const c1_div_c0 = Multiply(c1, rcp_c0);
            result                  = MultiplyAdd(line1, c1_div_c0, line1_start);
        }

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const line1  = _mm_sub_ps(line1_end.V, line1_start.V);
        __m128 const line2  = _mm_sub_ps(line2_end.V, line2_start.V);
        __m128 const line12 = _mm_sub_ps(line1_start.V, line2_start.V);

        __m128 const c0 = Cross(Vector2{ line1 }, Vector2{ line2 }).V;
        __m128 const c1 = Cross(Vector2{ line2 }, Vector2{ line12 }).V;

        // check c0 for zero
        __m128 const cmp0 = _mm_setzero_ps();
        __m128 const cmp1 = _mm_sub_ps(cmp0, c0);
        __m128 const cmp2 = _mm_max_ps(cmp1, c0);
        __m128 const succ = _mm_cmpgt_ps(cmp2, Impl::c_V4_F32_Epsilon.V);

        // check c1 for zero
        __m128 const fail0 = _mm_setzero_ps();
        __m128 const fail1 = _mm_sub_ps(fail0, c1);
        __m128 const fail2 = _mm_max_ps(fail1, c1);
        __m128 const fail3 = _mm_cmple_ps(fail2, Impl::c_V4_F32_Epsilon.V);

        // select inf or nan based on result of comparison
        __m128 const fail4 = _mm_and_ps(fail3, Impl::c_V4_F32_Positive_Infinity.V);
        __m128 const fail5 = _mm_andnot_ps(fail3, Impl::c_V4_F32_Positive_QNan.V);
        __m128 const fail  = _mm_or_ps(fail4, fail5);

        // compute intersection
        __m128 const c1_div_c0 = _mm_div_ps(c1, c0);
        __m128 const result    = Impl::avx_fmadd_f32x4(c1_div_c0, line1, line1_start.V);

        // select result or failure value
        __m128 const r0 = _mm_and_ps(result, succ);
        __m128 const r1 = _mm_andnot_ps(succ, fail);
        __m128 const r2 = _mm_or_ps(r0, r1);
        return { r2 };
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline Vector4 mathcall LinePointDistance(T line1, T line2, T point) noexcept
    {
        T const vec_line_point       = Subtract(point, line1);
        T const vec_line_line        = Subtract(line2, line1);
        Vector4 const length_squared = LengthSquared(vec_line_line);

        Vector4 const projection_scale_0 = Dot(vec_line_point, vec_line_line);
        T const projection_scale_1       = T{ Divide(projection_scale_0, length_squared).V };

        T const distance_0 = Multiply(vec_line_line, projection_scale_1);
        T const distance_1 = Subtract(vec_line_point, distance_0);
        return Length(T{ distance_1 });
    }
}
