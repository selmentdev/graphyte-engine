#pragma once
#include <Graphyte/Maths/Vector3.hxx>
#include <Graphyte/Maths/Vector4.hxx>
#include <Graphyte/Maths/Quaternion.hxx>

namespace Graphyte::Maths
{
    mathinline Vector3 mathcall Vector3::MakeUInt(uint32_t value) noexcept
    {
        return { Vector4::MakeUInt(value).V };
    }

    mathinline Vector3 mathcall Vector3::MakeUInt(uint32_t x, uint32_t y, uint32_t z) noexcept
    {
        return { Vector4::MakeUInt(x, y, z, 0).V };
    }

    mathinline Vector3 mathcall Vector3::Load(const float2a* source) noexcept
    {
        return { Vector4::Load(source).V };
    }

    mathinline Vector3 mathcall Vector3::LoadPacked(const float2* source) noexcept
    {
        return { Vector4::LoadPacked(source).V };
    }

    mathinline Vector3 mathcall Vector3::Load(const float3a* source) noexcept
    {
        return { Vector4::Load(source).V };
    }

    mathinline Vector3 mathcall Vector3::LoadPacked(const float3* source) noexcept
    {
        return { Vector4::LoadPacked(source).V };
    }

    mathinline Vector3 mathcall Vector3::Load(const float4a* source) noexcept
    {
        return { Vector4::Load(source).V };
    }

    mathinline Vector3 mathcall Vector3::LoadPacked(const float4* source) noexcept
    {
        return { Vector4::LoadPacked(source).V };
    }

    mathinline void mathcall Vector3::Store(float2a* destination, Vector3 v) noexcept
    {
        Vector4::Store(destination, { v.V });
    }

    mathinline void mathcall Vector3::StorePacked(float2* destination, Vector3 v) noexcept
    {
        Vector4::StorePacked(destination, { v.V });
    }

    mathinline void mathcall Vector3::Store(float3a* destination, Vector3 v) noexcept
    {
        Vector4::Store(destination, { v.V });
    }

    mathinline void mathcall Vector3::StorePacked(float3* destination, Vector3 v) noexcept
    {
        Vector4::StorePacked(destination, { v.V });
    }

    mathinline void mathcall Vector3::Store(float4a* destination, Vector3 v) noexcept
    {
        Vector4::Store(destination, { v.V });
    }

    mathinline void mathcall Vector3::StorePacked(float4* destination, Vector3 v) noexcept
    {
        Vector4::StorePacked(destination, { v.V });
    }

    mathinline bool mathcall Vector3::IsEqual(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] == v2.V.F[0]) &&
            (v1.V.F[1] == v2.V.F[1]) &&
            (v1.V.F[2] == v2.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsEqual(Vector3 v1, Vector3 v2, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_dx = fabsf(v1.V.F[0] - v2.V.F[0]);
        auto f_dy = fabsf(v1.V.F[1] - v2.V.F[1]);
        auto f_dz = fabsf(v1.V.F[2] - v2.V.F[2]);

        return
            (f_dx <= epsilon.V.F[0]) &&
            (f_dy <= epsilon.V.F[1]) &&
            (f_dz <= epsilon.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_delta = _mm_sub_ps(v1.V, v2.V);
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsNotEqual(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] != v2.V.F[0]) ||
            (v1.V.F[1] != v2.V.F[1]) ||
            (v1.V.F[2] != v2.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) != 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsGreater(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] > v2.V.F[0]) &&
            (v1.V.F[1] > v2.V.F[1]) &&
            (v1.V.F[2] > v2.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpgt_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsGreaterEqual(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] >= v2.V.F[0]) &&
            (v1.V.F[1] >= v2.V.F[1]) &&
            (v1.V.F[2] >= v2.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpge_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsLess(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] < v2.V.F[0]) &&
            (v1.V.F[1] < v2.V.F[1]) &&
            (v1.V.F[2] < v2.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmplt_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsLessEqual(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] <= v2.V.F[0]) &&
            (v1.V.F[1] <= v2.V.F[1]) &&
            (v1.V.F[2] <= v2.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmple_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::InBounds(Vector3 v, Vector3 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            ((v.V.F[0] <= bounds.V.F[0]) && (v.V.F[0] >= -bounds.V.F[0])) &&
            ((v.V.F[1] <= bounds.V.F[1]) && (v.V.F[1] >= -bounds.V.F[1])) &&
            ((v.V.F[2] <= bounds.V.F[2]) && (v.V.F[2] >= -bounds.V.F[2]));
#elif GRAPHYTE_HW_AVX
        auto v_temp1 = _mm_cmple_ps(v.V, bounds.V);
        auto v_temp2 = _mm_mul_ps(bounds.V, Detail::VEC4_NEGATIVE_ONE_4.V);
        v_temp2 = _mm_cmple_ps(v_temp2, v.V);
        v_temp1 = _mm_and_ps(v_temp1, v_temp2);
        return (_mm_movemask_ps(v_temp1) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsNaN(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            std::isnan(v.V.F[0]) ||
            std::isnan(v.V.F[1]) ||
            std::isnan(v.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpneq_ps(v.V, v.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) != 0;
#endif
    }

    mathinline bool mathcall Vector3::IsInfinite(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            std::isinf(v.V.F[0]) ||
            std::isinf(v.V.F[1]) ||
            std::isinf(v.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_and_ps(v.V, Detail::VEC4_MASK_ABS.V);
        v_temp = _mm_cmpeq_ps(v_temp, Detail::VEC4_INFINITY.V);
        return (_mm_movemask_ps(v_temp) & 0b0111) != 0;
#endif
    }

    mathinline bool mathcall Vector3::IsEqualUInt(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.U[0] == v2.V.U[0]) &&
            (v1.V.U[1] == v2.V.U[1]) &&
            (v1.V.U[2] == v2.V.U[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return (_mm_movemask_ps(_mm_castsi128_ps(v_temp)) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall Vector3::IsNotEqualUInt(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.U[0] != v2.V.U[0]) ||
            (v1.V.U[1] != v2.V.U[1]) ||
            (v1.V.U[2] != v2.V.U[2]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return (_mm_movemask_ps(_mm_castsi128_ps(v_temp)) & 0b0111) != 0b0111;
#endif
    }

    mathinline Vector3 mathcall Vector3::Clamp(Vector3 v, Vector3 min, Vector3 max) noexcept
    {
        return { Vector4::Clamp({ v.V }, { min.V }, { max.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Saturate(Vector3 v) noexcept
    {
        return { Vector4::Saturate({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::AddAngles(Vector3 v1, Vector3 v2) noexcept
    {
        return { Vector4::AddAngles({ v1.V }, { v2.V }).V };
    }

    mathinline Vector3 mathcall Vector3::SubtractAngles(Vector3 v1, Vector3 v2) noexcept
    {
        return { Vector4::SubtractAngles({ v1.V }, { v2.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ReciprocalEst(Vector3 v) noexcept
    {
        return { Vector4::ReciprocalEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Reciprocal(Vector3 v) noexcept
    {
        return { Vector4::Reciprocal({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ReciprocalSqrtEst(Vector3 v) noexcept
    {
        return { Vector4::ReciprocalSqrtEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ReciprocalSqrt(Vector3 v) noexcept
    {
        return { Vector4::ReciprocalSqrt({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Exp2(Vector3 v) noexcept
    {
        return { Vector4::Exp2({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ExpE(Vector3 v) noexcept
    {
        return { Vector4::ExpE({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Exp(Vector3 v) noexcept
    {
        return { Vector4::Exp({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Log2(Vector3 v) noexcept
    {
        return { Vector4::Log2({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::LogE(Vector3 v) noexcept
    {
        return { Vector4::LogE({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Log(Vector3 v) noexcept
    {
        return { Vector4::Log({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Pow(Vector3 v1, Vector3 v2) noexcept
    {
        return { Vector4::Pow({ v1.V }, { v2.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Abs(Vector3 v) noexcept
    {
        return { Vector4::Abs({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Mod(Vector3 v1, Vector3 v2) noexcept
    {
        return { Vector4::Mod({ v1.V }, { v2.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ModAngles(Vector3 angles) noexcept
    {
        return { Vector4::ModAngles({ angles.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Sin(Vector3 v) noexcept
    {
        return { Vector4::Sin({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Cos(Vector3 v) noexcept
    {
        return { Vector4::Cos({ v.V }).V };
    }

    mathinline void mathcall Vector3::SinCos(Vector3* out_sin, Vector3* out_cos, Vector3 v) noexcept
    {
        Vector4::SinCos(
            reinterpret_cast<Vector4*>(out_sin),
            reinterpret_cast<Vector4*>(out_cos),
            { v.V }
        );
    }

    mathinline Vector3 mathcall Vector3::Tan(Vector3 v) noexcept
    {
        return { Vector4::Tan({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::SinH(Vector3 v) noexcept
    {
        return { Vector4::SinH({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::CosH(Vector3 v) noexcept
    {
        return { Vector4::CosH({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::TanH(Vector3 v) noexcept
    {
        return { Vector4::TanH({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ASin(Vector3 v) noexcept
    {
        return { Vector4::ASin({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ACos(Vector3 v) noexcept
    {
        return { Vector4::ACos({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ATan(Vector3 v) noexcept
    {
        return { Vector4::ATan({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ATan2(Vector3 y, Vector3 x) noexcept
    {
        return { Vector4::ATan2({ y.V }, { x.V }).V };
    }

    mathinline Vector3 mathcall Vector3::SinEst(Vector3 v) noexcept
    {
        return { Vector4::SinEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::CosEst(Vector3 v) noexcept
    {
        return { Vector4::CosEst({ v.V }).V };
    }

    mathinline void mathcall Vector3::SinCosEst(Vector3* out_sin, Vector3* out_cos, Vector3 v) noexcept
    {
        Vector4::SinCosEst(
            reinterpret_cast<Vector4*>(out_sin),
            reinterpret_cast<Vector4*>(out_cos),
            { v.V }
        );
    }

    mathinline Vector3 mathcall Vector3::TanEst(Vector3 v) noexcept
    {
        return { Vector4::TanEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ASinEst(Vector3 v) noexcept
    {
        return { Vector4::ASinEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ACosEst(Vector3 v) noexcept
    {
        return { Vector4::ACosEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ATanEst(Vector3 v) noexcept
    {
        return { Vector4::ATanEst({ v.V }).V };
    }

    mathinline Vector3 mathcall Vector3::ATan2Est(Vector3 y, Vector3 x) noexcept
    {
        return { Vector4::ATan2Est({ y.V }, { x.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Lerp(Vector3 v0, Vector3 v1, float t) noexcept
    {
        return { Vector4::Lerp({ v0.V }, { v1.V }, t).V };
    }

    mathinline Vector3 mathcall Vector3::Lerp(Vector3 v0, Vector3 v1, Vector4 t) noexcept
    {
        return { Vector4::Lerp({ v0.V }, { v1.V }, { t.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Hermite(Vector3 position0, Vector3 tangent0, Vector3 position1, Vector3 tangent1, float t) noexcept
    {
        return { Vector4::Hermite({ position0.V }, { tangent0.V }, { position1.V }, { tangent1.V }, t).V };
    }

    mathinline Vector3 mathcall Vector3::Hermite(Vector3 position0, Vector3 tangent0, Vector3 position1, Vector3 tangent1, Vector4 t) noexcept
    {
        return { Vector4::Hermite({ position0.V }, { tangent0.V }, { position1.V }, { tangent1.V }, { t.V }).V };
    }

    mathinline Vector3 mathcall Vector3::CatmullRom(Vector3 position0, Vector3 position1, Vector3 position2, Vector3 position3, float t) noexcept
    {
        return { Vector4::CatmullRom({ position0.V }, { position1.V }, { position2.V }, { position3.V }, t).V };
    }

    mathinline Vector3 mathcall Vector3::CatmullRom(Vector3 position0, Vector3 position1, Vector3 position2, Vector3 position3, Vector4 t) noexcept
    {
        return { Vector4::CatmullRom({ position0.V }, { position1.V }, { position2.V }, { position3.V }, { t.V }).V };
    }

    mathinline Vector3 mathcall Vector3::Barycentric(Vector3 position0, Vector3 position1, Vector3 position2, float f, float g) noexcept
    {
        return { Vector4::Barycentric({ position0.V }, { position1.V }, { position2.V }, f, g).V };
    }

    mathinline Vector3 mathcall Vector3::Barycentric(Vector3 position0, Vector3 position1, Vector3 position2, Vector4 f, Vector4 g) noexcept
    {
        return { Vector4::Barycentric({ position0.V }, { position1.V }, { position2.V }, { f.V }, { g.V }).V };
    }

    mathinline Vector4 mathcall Vector3::Dot(Vector3 v1, Vector3 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_dot =
            v1.V.F[0] * v2.V.F[0] +
            v1.V.F[1] * v2.V.F[1] +
            v1.V.F[2] * v2.V.F[2];
        Detail::Vector4F32 v_result = { { {
                f_dot, f_dot, f_dot, f_dot,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(v1.V, v2.V, 0b0111'1111) };
#endif
    }

    mathinline Vector4 mathcall Vector3::LengthSquared(Vector3 v) noexcept
    {
        return Vector3::Dot(v, v);
    }

    mathinline Vector4 mathcall Vector3::ReciprocalLengthEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector3::LengthSquared(v);
        v_result = Vector4::ReciprocalSqrtEst(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        return { _mm_rsqrt_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector3::ReciprocalLength(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector3::LengthSquared(v);
        v_result = Vector4::ReciprocalSqrt(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        auto v_length = _mm_sqrt_ps(v_temp);
        return { _mm_div_ps(Detail::VEC4_ONE_4.V, v_length) };
#endif
    }

    mathinline Vector4 mathcall Vector3::LengthEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector3::LengthSquared(v);
        v_result = Vector4::SqrtEst(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector3::Length(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector3::LengthSquared(v);
        v_result = Vector4::Sqrt(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vector3 mathcall Vector3::NormalizeEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector3::ReciprocalLength(v);
        v_result = Vector4::Multiply({ v.V }, v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        auto v_result = _mm_rsqrt_ps(v_temp);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    mathinline Vector3 mathcall Vector3::Normalize(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float f_length = Vector3::Length(v).V.F[0];

        if (f_length > 0.0F)
        {
            f_length = 1.0F / f_length;
        }

        Detail::Vector4F32 v_result = { { {
                v.V.F[0] * f_length,
                v.V.F[1] * f_length,
                v.V.F[2] * f_length,
                v.V.F[3] * f_length,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_length_sq = _mm_dp_ps(v.V, v.V, 0b0111'1111);
        auto v_result = _mm_sqrt_ps(v_length_sq);
        auto v_zero_mask = _mm_setzero_ps();
        v_zero_mask = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq = _mm_cmpneq_ps(v_length_sq, Detail::VEC4_INFINITY.V);
        v_result = _mm_div_ps(v.V, v_result);
        v_result = _mm_and_ps(v_result, v_zero_mask);
        auto v_temp1 = _mm_andnot_ps(v_length_sq, Detail::VEC4_QNAN.V);
        auto v_temp2 = _mm_and_ps(v_result, v_length_sq);
        v_result = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }

    mathinline Vector3 mathcall Vector3::ClampLength(Vector3 v, float min, float max) noexcept
    {
        auto v_max = Vector4::Make(max);
        auto v_min = Vector4::Make(min);
        return Vector3::ClampLength(v, v_min, v_max);
    }

    mathinline Vector3 mathcall Vector3::ClampLength(Vector3 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(Vector4::GetX(min) == Vector4::GetY(min) && Vector4::GetX(min) == Vector4::GetZ(min));
        GX_ASSERT(Vector4::GetX(max) == Vector4::GetY(max) && Vector4::GetX(max) == Vector4::GetZ(max));
        GX_ASSERT(Vector3::IsGreaterEqual({ min.V }, { Detail::VEC4_ZERO_4.V }));
        GX_ASSERT(Vector3::IsGreaterEqual({ max.V }, { Detail::VEC4_ZERO_4.V }));
        GX_ASSERT(Vector3::IsGreaterEqual({ max.V }, { min.V }));

        auto v_length_sq = Vector3::LengthSquared(v);
        auto v_zero = Vector4::Zero();

        auto v_rcp_length = Vector4::ReciprocalSqrt(v_length_sq);
        auto v_infinite_length = Vector4::MaskCompareEqual(v_length_sq, { Detail::VEC4_INFINITY.V });
        auto v_zero_length = Vector4::CompareEqual(v_length_sq, v_zero);

        auto v_normal = Vector4::Multiply({ v.V }, v_rcp_length);
        auto v_length = Vector4::Multiply(v_length_sq, v_rcp_length);

        auto v_select = Vector4::MaskCompareEqual(v_infinite_length, v_zero_length);
        v_length = Vector4::Select(v_length_sq, v_length, v_select);
        v_normal = Vector4::Select(v_length_sq, v_normal, v_select);

        auto v_control_max = Vector4::CompareGreater(v_length, max);
        auto v_control_min = Vector4::CompareLess(v_length, min);

        auto v_clamp_length = Vector4::Select(v_length, max, v_control_max);
        v_clamp_length = Vector4::Select(v_clamp_length, min, v_control_min);

        auto v_result = Vector4::Multiply(v_normal, v_clamp_length);

        auto v_control = Vector4::MaskCompareEqual(v_control_max, v_control_min);
        v_result = Vector4::Select(v_result, { v.V }, v_control);
        return { v_result.V };
    }

    mathinline Vector3 mathcall Vector3::Reflect(Vector3 incident, Vector3 normal) noexcept
    {
        auto v_result = Vector3::Dot(incident, normal);
        v_result = Vector4::Add(v_result, v_result);
        v_result = Vector4::NegativeMultiplySubtract(v_result, { normal.V }, { incident.V });
        return { v_result.V };
    }

    mathinline Vector3 mathcall Vector3::Refract(Vector3 incident, Vector3 normal, float refraction_index) noexcept
    {
        auto v_index = Vector4::Make(refraction_index);
        return Vector3::Refract(incident, normal, v_index);
    }

    mathinline Vector3 mathcall Vector3::Refract(Vector3 incident, Vector3 normal, Vector4 refraction_index) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_zero = Vector4::Zero();
        auto v_i_dot_n = Vector3::Dot(incident, normal);

        auto v_r = Vector4::NegativeMultiplySubtract(v_i_dot_n, v_i_dot_n, { Detail::VEC4_ONE_4.V });
        v_r = Vector4::Multiply(v_r, refraction_index);
        v_r = Vector4::NegativeMultiplySubtract(v_r, refraction_index, { Detail::VEC4_ONE_4.V });

        if (Vector4::IsLessEqual(v_r, v_zero))
        {
            return { v_zero.V };
        }
        else
        {
            v_r = Vector4::Sqrt(v_r);
            v_r = Vector4::MultiplyAdd(refraction_index, v_i_dot_n, v_r);

            auto v_result = Vector4::Multiply(refraction_index, { incident.V });
            v_result = Vector4::NegativeMultiplySubtract({ normal.V }, v_r, v_result);
            return { v_result.V };
        }
#elif GRAPHYTE_HW_AVX
        auto v_i_dot_n = Vector3::Dot(incident, normal).V;
        auto v_r       = _mm_mul_ps(v_i_dot_n, v_i_dot_n);
        v_r            = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_r);
        v_r            = _mm_mul_ps(v_r, refraction_index.V);
        v_r            = _mm_mul_ps(v_r, refraction_index.V);
        v_r            = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_r);

        auto v_result  = _mm_cmple_ps(v_r, Detail::VEC4_ZERO_4.V);

        if (_mm_movemask_ps(v_result) == 0b1111)
        {
            v_result = Detail::VEC4_ZERO_4.V;
        }
        else
        {
            v_r      = _mm_sqrt_ps(v_r);
            v_result = _mm_mul_ps(refraction_index.V, v_i_dot_n);
            v_r      = _mm_add_ps(v_r, v_result);
            v_result = _mm_mul_ps(refraction_index.V, incident.V);
            v_r      = _mm_mul_ps(v_r, normal.V);
            v_result = _mm_sub_ps(v_result, v_r);
        }

        return { v_result };
#endif
    }

    mathinline Vector3 mathcall Vector3::Orthogonal(Vector3 v) noexcept
    {
        auto v_zero = Vector4::Zero();
        auto v_z = Vector4::SplatZ({ v.V });
        auto v_yzyy = Vector4::Swizzle<SwizzleMask::YZYY>({ v.V });
        auto v_negative_v = Vector4::Subtract(v_zero, { v.V });

        auto v_z_is_negative = Vector4::CompareLess(v_z, v_zero);

        auto v_yzyy_is_negative = Vector4::CompareLess(v_yzyy, v_zero);

        auto v_s = Vector4::Add(v_yzyy, v_z);
        auto v_d = Vector4::Subtract(v_yzyy, v_z);

        auto v_select = Vector4::MaskCompareEqual(v_z_is_negative, v_yzyy_is_negative);

        auto v_r0 = Vector4::Permute<4, 0, 0, 0>(v_negative_v, v_s);
        auto v_r1 = Vector4::Permute<4, 0, 0, 0>({ v.V }, v_d);

        return { Vector4::Select(v_r1, v_r0, v_select).V };
    }

    mathinline Vector4 mathcall Vector3::AngleBetweenNormalsEst(Vector3 n1, Vector3 n2) noexcept
    {
        auto v_result = Vector3::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACosEst(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector3::AngleBetweenNormals(Vector3 n1, Vector3 n2) noexcept
    {
        auto v_result = Vector3::Dot(n1, n2);
        v_result      = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result      = Vector4::ACos(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector3::AngleBetweenVectors(Vector3 v1, Vector3 v2) noexcept
    {
        auto v_l1 = Vector3::ReciprocalLength(v1);
        auto v_l2 = Vector3::ReciprocalLength(v2);

        auto v_dot = Vector3::Dot(v1, v2);

        v_l1 = Vector4::Multiply(v_l1, v_l2);

        auto v_cos_angle = Vector4::Multiply(v_dot, v_l1);
        v_cos_angle      = Vector4::Clamp(v_cos_angle, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_cos_angle      = Vector4::ACos(v_cos_angle);
        return v_cos_angle;
    }

    mathinline Vector4 mathcall Vector3::LinePointDistance(Vector3 line_point1, Vector3 line_point2, Vector3 point) noexcept
    {
        auto v_point_vector = Vector4::Subtract({ point.V }, { line_point1.V });
        auto v_line_vector  = Vector4::Subtract({ line_point2.V }, { line_point1.V });
        auto v_length_sq    = Vector3::LengthSquared({ v_line_vector.V });

        auto v_point_projection_scale = Vector3::Dot({ v_point_vector.V }, { v_line_vector.V });
        v_point_projection_scale      = Vector4::Divide(v_point_projection_scale, v_length_sq);

        auto v_distance_vector = Vector4::Multiply(v_line_vector, v_point_projection_scale);
        v_distance_vector      = Vector4::Subtract(v_point_vector, v_distance_vector);
        return Vector3::Length({ v_distance_vector.V });
    }

    mathinline void mathcall Vector3::ComponentsFromNormal(Vector3* parallel, Vector3* perpendicular, Vector3 v, Vector3 n) noexcept
    {
        GX_ASSERT(parallel != nullptr);
        GX_ASSERT(perpendicular != nullptr);

        auto v_scale = Vector3::Dot(v, n);
        auto v_parallel = Vector4::Multiply({ n.V }, v_scale);

        (*parallel) = { v_parallel.V };
        (*perpendicular) = { Vector4::Subtract({ v.V }, v_parallel).V };
    }

    mathinline Vector3 mathcall Vector3::Rotate(Vector3 v, Quaternion q) noexcept
    {
        auto v_a      = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { v.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto v_q      = Quaternion::Conjugate(q);
        auto v_result = Quaternion::Multiply(v_q, { v_a.V });
        return { Quaternion::Multiply(v_result, q).V };
    }

    mathinline Vector3 mathcall Vector3::InverseRotate(Vector3 v, Quaternion q) noexcept
    {
        auto v_a      = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { v.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto v_result = Quaternion::Multiply(q, { v_a.V });
        auto v_q      = Quaternion::Conjugate(q);
        return { Quaternion::Multiply(v_result, v_q).V };
    }

    mathinline Vector3 mathcall Vector3::Transform(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_z = Vector4::SplatZ({ v.V });
        auto v_y = Vector4::SplatY({ v.V });
        auto v_x = Vector4::SplatX({ v.V });
        auto v_result = Vector4::MultiplyAdd(v_z, { m.M.R[2] }, { m.M.R[3] });
        v_result = Vector4::MultiplyAdd(v_y, { m.M.R[1] }, v_result);
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);

        return { v_result.V };
#elif GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        v_result = _mm_fmadd_ps(v_result, m.M.R[2], m.M.R[3]);
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_fmadd_ps(v_temp, m.M.R[1], v_result);
        v_temp = _mm_broadcastss_ps(v.V);
        v_result = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        return { v_result };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        v_result      = _mm_mul_ps(v_result, m.M.R[0]);
        auto v_temp   = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_temp        = _mm_mul_ps(v_temp, m.M.R[1]);
        v_result      = _mm_add_ps(v_result, v_temp);
        v_temp        = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        v_temp        = _mm_mul_ps(v_temp, m.M.R[2]);
        v_result      = _mm_add_ps(v_result, v_temp);
        v_result      = _mm_add_ps(v_result, m.M.R[3]);
        return { v_result };
#endif
    }

    mathinline Vector3 mathcall Vector3::TransformCoord(Vector3 v, Matrix m) noexcept
    {
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        v_result = _mm_fmadd_ps(v_result, m.M.R[2], m.M.R[3]);
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_fmadd_ps(v_temp, m.M.R[1], v_result);
        v_temp = _mm_broadcastss_ps(v.V);
        v_result = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        auto v_w = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 3, 3, 3));
        v_result = _mm_div_ps(v_result, v_w);
        return { v_result };

#elif GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX
        auto v_z = Vector4::SplatZ({ v.V });
        auto v_y = Vector4::SplatY({ v.V });
        auto v_x = Vector4::SplatX({ v.V });

        auto v_result = Vector4::MultiplyAdd(v_z, { m.M.R[2] }, { m.M.R[3] });
        v_result = Vector4::MultiplyAdd(v_y, { m.M.R[1] }, v_result);
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);

        auto v_w = Vector4::SplatW(v_result);
        return { Vector4::Divide(v_result, v_w).V };
#endif
    }

    mathinline Vector3 mathcall Vector3::TransformNormal(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_z = Vector4::SplatZ({ v.V });
        auto v_y = Vector4::SplatY({ v.V });
        auto v_x = Vector4::SplatX({ v.V });

        auto v_result = Vector4::Multiply(v_z, { m.M.R[2] });
        v_result = Vector4::MultiplyAdd(v_y, { m.M.R[1] }, v_result);
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        v_result = _mm_mul_ps(v_result, m.M.R[2]);
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_fmadd_ps(v_temp, m.M.R[1], v_result);
        v_temp = _mm_broadcastss_ps(v.V);
        v_result = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        return { v_result };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        v_result = _mm_mul_ps(v_result, m.M.R[0]);
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_temp = _mm_mul_ps(v_temp, m.M.R[1]);
        v_result = _mm_add_ps(v_result, v_temp);
        v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        v_temp = _mm_mul_ps(v_temp, m.M.R[2]);
        v_result = _mm_add_ps(v_result, v_temp);
        return { v_result };
#endif
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
