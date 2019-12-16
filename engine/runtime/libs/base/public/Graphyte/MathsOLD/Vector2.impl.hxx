#pragma once
#include <Graphyte/Maths/Vector2.hxx>
#include <Graphyte/Maths/Vector4.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Maths
{
    mathinline Vector2 mathcall Vector2::Make(float value) noexcept
    {
        return { Vector4::Make(value).V };
    }

    mathinline Vector2 mathcall Vector2::Make(float x, float y) noexcept
    {
        return { Vector4::Make(x, y, 0.0F, 0.0F).V };
    }

    mathinline Vector2 mathcall Vector2::MakeUInt(uint32_t value) noexcept
    {
        return { Vector4::MakeUInt(value).V };
    }

    mathinline Vector2 mathcall Vector2::MakeUInt(uint32_t x, uint32_t y) noexcept
    {
        return { Vector4::MakeUInt(x, y, 0, 0).V };
    }

    mathinline Vector2 mathcall Vector2::Load(const float2a* source) noexcept
    {
        return { Vector4::Load(source).V };
    }

    mathinline Vector2 mathcall Vector2::LoadPacked(const float2* source) noexcept
    {
        return { Vector4::LoadPacked(source).V };
    }

    mathinline Vector2 mathcall Vector2::Load(const float3a* source) noexcept
    {
        return { Vector4::Load(source).V };
    }

    mathinline Vector2 mathcall Vector2::LoadPacked(const float3* source) noexcept
    {
        return { Vector4::LoadPacked(source).V };
    }

    mathinline Vector2 mathcall Vector2::Load(const float4a* source) noexcept
    {
        return { Vector4::Load(source).V };
    }

    mathinline Vector2 mathcall Vector2::LoadPacked(const float4* source) noexcept
    {
        return { Vector4::LoadPacked(source).V };
    }

    mathinline void mathcall Vector2::Store(float2a* destination, Vector2 v) noexcept
    {
        Vector4::Store(destination, { v.V });
    }

    mathinline void mathcall Vector2::StorePacked(float2* destination, Vector2 v) noexcept
    {
        Vector4::StorePacked(destination, { v.V });
    }

    mathinline void mathcall Vector2::Store(float3a* destination, Vector2 v) noexcept
    {
        Vector4::Store(destination, { v.V });
    }

    mathinline void mathcall Vector2::StorePacked(float3* destination, Vector2 v) noexcept
    {
        Vector4::StorePacked(destination, { v.V });
    }

    mathinline void mathcall Vector2::Store(float4a* destination, Vector2 v) noexcept
    {
        Vector4::Store(destination, { v.V });
    }

    mathinline void mathcall Vector2::StorePacked(float4* destination, Vector2 v) noexcept
    {
        Vector4::StorePacked(destination, { v.V });
    }

    mathinline bool mathcall Vector2::IsEqual(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] == v2.V.F[0]) &&
            (v1.V.F[1] == v2.V.F[0]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsEqual(Vector2 v1, Vector2 v2, Vector2 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_dx = fabsf(v1.V.F[0] - v2.V.F[0]);
        auto f_dy = fabsf(v1.V.F[1] - v2.V.F[1]);
        return
            (f_dx <= epsilon.V.F[0]) &&
            (f_dy <= epsilon.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_delta = _mm_sub_ps(v1.V, v2.V);
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsNotEqual(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] != v2.V.F[0]) ||
            (v1.V.F[1] != v2.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) != 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsGreater(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] > v2.V.F[0]) &&
            (v1.V.F[1] > v2.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpgt_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsGreaterEqual(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] >= v2.V.F[0]) &&
            (v1.V.F[1] >= v2.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpge_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsLess(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] < v2.V.F[0]) &&
            (v1.V.F[1] < v2.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmplt_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsLessEqual(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] <= v2.V.F[0]) &&
            (v1.V.F[1] <= v2.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmple_ps(v1.V, v2.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::InBounds(Vector2 v, Vector2 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            ((v.V.F[0] <= bounds.V.F[0]) && (v.V.F[0] >= -bounds.V.F[0])) &&
            ((v.V.F[1] <= bounds.V.F[1]) && (v.V.F[1] >= -bounds.V.F[1]));
#elif GRAPHYTE_HW_AVX
        auto v_temp1 = _mm_cmple_ps(v.V, bounds.V);
        auto v_temp2 = _mm_mul_ps(bounds.V, Detail::VEC4_NEGATIVE_ONE_4.V);
        v_temp2 = _mm_cmple_ps(v_temp2, v.V);
        v_temp1 = _mm_and_ps(v_temp1, v_temp2);
        return (_mm_movemask_ps(v_temp1) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsNaN(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            std::isnan(v.V.F[0]) ||
            std::isnan(v.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpneq_ps(v.V, v.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) != 0;
#endif
    }

    mathinline bool mathcall Vector2::IsInfinite(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            std::isinf(v.V.F[0]) ||
            std::isinf(v.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_and_ps(v.V, Detail::VEC4_MASK_ABS.V);
        v_temp = _mm_cmpneq_ps(v_temp, Detail::VEC4_INFINITY.V);
        return (_mm_movemask_ps(v_temp) & 0b0011) != 0;
#endif
    }

    mathinline bool mathcall Vector2::IsEqualUInt(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.U[0] == v2.V.U[0]) &&
            (v1.V.U[1] == v2.V.U[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return (_mm_movemask_ps(_mm_castsi128_ps(v_temp)) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall Vector2::IsNotEqualUInt(Vector2 v1, Vector2 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.U[0] != v2.V.U[0]) ||
            (v1.V.U[1] != v2.V.U[1]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return (_mm_movemask_ps(_mm_castsi128_ps(v_temp)) & 0b0011) != 0b0011;
#endif
    }

    mathinline Vector2 mathcall Vector2::Min(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Min({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Max(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Max({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Round(Vector2 v) noexcept
    {
        return { Vector4::Round({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Truncate(Vector2 v) noexcept
    {
        return { Vector4::Truncate({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Floor(Vector2 v) noexcept
    {
        return { Vector4::Floor({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Ceiling(Vector2 v) noexcept
    {
        return { Vector4::Ceiling({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Fract(Vector2 v) noexcept
    {
        return { Vector4::Fract({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Clamp(Vector2 v, Vector2 min, Vector2 max) noexcept
    {
        return { Vector4::Clamp({ v.V }, { min.V }, { max.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Saturate(Vector2 v) noexcept
    {
        return { Vector4::Saturate({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Negate(Vector2 v) noexcept
    {
        return { Vector4::Negate({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Add(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Add({ v1.V }, { v2.V }).V };
    }

    mathinline Vector4 mathcall Vector2::Sum(Vector2 v) noexcept
    {
        return Vector4::Sum({ v.V });
    }

    mathinline Vector2 mathcall Vector2::AddAngles(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::AddAngles({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Subtract(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Subtract({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::SubtractAngles(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::SubtractAngles({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Multiply(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Multiply({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::MultiplyAdd(Vector2 v1, Vector2 v2, Vector2 v3) noexcept
    {
        return { Vector4::MultiplyAdd({ v1.V }, { v2.V }, { v3.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Divide(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Divide({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::NegativeMultiplySubtract(Vector2 v1, Vector2 v2, Vector2 v3) noexcept
    {
        return { Vector4::NegativeMultiplySubtract({ v1.V }, { v2.V }, { v3.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Scale(Vector2 v, float scale) noexcept
    {
        return { Vector4::Scale({ v.V }, scale).V };
    }

    mathinline Vector2 mathcall Vector2::ReciprocalEst(Vector2 v) noexcept
    {
        return { Vector4::ReciprocalEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Reciprocal(Vector2 v) noexcept
    {
        return { Vector4::Reciprocal({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::SqrtEst(Vector2 v) noexcept
    {
        return { Vector4::SqrtEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Sqrt(Vector2 v) noexcept
    {
        return { Vector4::Sqrt({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ReciprocalSqrtEst(Vector2 v) noexcept
    {
        return { Vector4::ReciprocalSqrtEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ReciprocalSqrt(Vector2 v) noexcept
    {
        return { Vector4::ReciprocalSqrt({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Exp2(Vector2 v) noexcept
    {
        return { Vector4::Exp2({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ExpE(Vector2 v) noexcept
    {
        return { Vector4::ExpE({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Exp(Vector2 v) noexcept
    {
        return { Vector4::Exp({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Log2(Vector2 v) noexcept
    {
        return { Vector4::Log2({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::LogE(Vector2 v) noexcept
    {
        return { Vector4::LogE({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Log(Vector2 v) noexcept
    {
        return { Vector4::Log({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Pow(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Pow({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Abs(Vector2 v) noexcept
    {
        return { Vector4::Abs({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Mod(Vector2 v1, Vector2 v2) noexcept
    {
        return { Vector4::Mod({ v1.V }, { v2.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ModAngles(Vector2 angles) noexcept
    {
        return { Vector4::ModAngles({ angles.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Sin(Vector2 v) noexcept
    {
        return { Vector4::Sin({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Cos(Vector2 v) noexcept
    {
        return { Vector4::Cos({ v.V }).V };
    }

    mathinline void mathcall Vector2::SinCos(Vector2* out_sin, Vector2* out_cos, Vector2 v) noexcept
    {
        Vector4::SinCos(
            reinterpret_cast<Vector4*>(out_sin),
            reinterpret_cast<Vector4*>(out_cos),
            { v.V }
        );
    }

    mathinline Vector2 mathcall Vector2::Tan(Vector2 v) noexcept
    {
        return { Vector4::Tan({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::SinH(Vector2 v) noexcept
    {
        return { Vector4::SinH({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::CosH(Vector2 v) noexcept
    {
        return { Vector4::CosH({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::TanH(Vector2 v) noexcept
    {
        return { Vector4::TanH({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ASin(Vector2 v) noexcept
    {
        return { Vector4::ASin({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ACos(Vector2 v) noexcept
    {
        return { Vector4::ACos({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ATan(Vector2 v) noexcept
    {
        return { Vector4::ATan({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ATan2(Vector2 y, Vector2 x) noexcept
    {
        return { Vector4::ATan2({ y.V }, { x.V }).V };
    }

    mathinline Vector2 mathcall Vector2::SinEst(Vector2 v) noexcept
    {
        return { Vector4::SinEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::CosEst(Vector2 v) noexcept
    {
        return { Vector4::CosEst({ v.V }).V };
    }

    mathinline void mathcall Vector2::SinCosEst(Vector2* out_sin, Vector2* out_cos, Vector2 v) noexcept
    {
        Vector4::SinCosEst(
            reinterpret_cast<Vector4*>(out_sin),
            reinterpret_cast<Vector4*>(out_cos),
            { v.V }
        );
    }

    mathinline Vector2 mathcall Vector2::TanEst(Vector2 v) noexcept
    {
        return { Vector4::TanEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ASinEst(Vector2 v) noexcept
    {
        return { Vector4::ASinEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ACosEst(Vector2 v) noexcept
    {
        return { Vector4::ACosEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ATanEst(Vector2 v) noexcept
    {
        return { Vector4::ATanEst({ v.V }).V };
    }

    mathinline Vector2 mathcall Vector2::ATan2Est(Vector2 y, Vector2 x) noexcept
    {
        return { Vector4::ATan2Est({ y.V }, { x.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Lerp(Vector2 v0, Vector2 v1, float t) noexcept
    {
        return { Vector4::Lerp({ v0.V }, { v1.V }, t).V };
    }

    mathinline Vector2 mathcall Vector2::Lerp(Vector2 v0, Vector2 v1, Vector4 t) noexcept
    {
        return { Vector4::Lerp({ v0.V }, { v1.V }, { t.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Hermite(Vector2 position0, Vector2 tangent0, Vector2 position1, Vector2 tangent1, float t) noexcept
    {
        return { Vector4::Hermite({ position0.V }, { tangent0.V }, { position1.V }, { tangent1.V }, t).V };
    }

    mathinline Vector2 mathcall Vector2::Hermite(Vector2 position0, Vector2 tangent0, Vector2 position1, Vector2 tangent1, Vector4 t) noexcept
    {
        return { Vector4::Hermite({ position0.V }, { tangent0.V }, { position1.V }, { tangent1.V }, { t.V }).V };
    }

    mathinline Vector2 mathcall Vector2::CatmullRom(Vector2 position0, Vector2 position1, Vector2 position2, Vector2 position3, float t) noexcept
    {
        return { Vector4::CatmullRom({ position0.V }, { position1.V }, { position2.V }, { position3.V }, t).V };
    }

    mathinline Vector2 mathcall Vector2::CatmullRom(Vector2 position0, Vector2 position1, Vector2 position2, Vector2 position3, Vector4 t) noexcept
    {
        return { Vector4::CatmullRom({ position0.V }, { position1.V }, { position2.V }, { position3.V }, { t.V }).V };
    }

    mathinline Vector2 mathcall Vector2::Barycentric(Vector2 position0, Vector2 position1, Vector2 position2, float f, float g) noexcept
    {
        return { Vector4::Barycentric({ position0.V }, { position1.V }, { position2.V }, f, g).V };
    }

    mathinline Vector2 mathcall Vector2::Barycentric(Vector2 position0, Vector2 position1, Vector2 position2, Vector4 f, Vector4 g) noexcept
    {
        return { Vector4::Barycentric({ position0.V }, { position1.V }, { position2.V }, { f.V }, { g.V }).V };
    }

    mathinline Vector4 mathcall Vector2::ReciprocalLengthEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = LengthSquared(v);
        v_result = Vector4::ReciprocalSqrtEst(v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        return { _mm_rsqrt_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector2::ReciprocalLength(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = LengthSquared(v);
        v_result = Vector4::ReciprocalSqrt(v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp      = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        auto v_length_sq = _mm_sqrt_ps(v_temp);
        return { _mm_div_ps(Detail::VEC4_ONE_4.V, v_length_sq) };
#endif
    }

    mathinline Vector4 mathcall Vector2::LengthEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = LengthSquared(v);
        v_result = Vector4::SqrtEst(v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vector2 mathcall Vector2::NormalizeEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = ReciprocalLength(v);
        v_result = Vector4::Multiply({ v.V }, v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp   = _mm_dp_ps(v.V, v.V, 0b0011'1111);
        auto v_result = _mm_rsqrt_ps(v_temp);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    mathinline Vector2 mathcall Vector2::ClampLength(Vector2 v, float min, float max) noexcept
    {
        auto v_min = Vector4::Make(min);
        auto v_max = Vector4::Make(max);
        return Vector2::ClampLength(v, v_min, v_max);
    }

    mathinline Vector2 mathcall Vector2::ClampLength(Vector2 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(Vector4::GetY(min) == Vector4::GetX(min));
        GX_ASSERT(Vector4::GetY(max) == Vector4::GetX(max));
        GX_ASSERT(Vector2::IsGreaterEqual({ min.V }, { Detail::VEC4_ZERO_4.V }));
        GX_ASSERT(Vector2::IsGreaterEqual({ max.V }, { Detail::VEC4_ZERO_4.V }));
        GX_ASSERT(Vector2::IsGreaterEqual({ max.V }, { min.V }));

        auto v_length_sq = Vector2::LengthSquared(v);
        auto v_zero = Vector4::Zero();
        auto v_rcp_length = Vector4::ReciprocalSqrt(v_length_sq);
        auto v_infinite_length = Vector4::MaskCompareEqual(v_length_sq, { Detail::VEC4_INFINITY.V });
        auto v_zero_length = Vector4::CompareEqual(v_length_sq, v_zero);
        auto v_length = Vector4::Multiply(v_length_sq, v_rcp_length);
        auto v_normal = Vector4::Multiply({ v.V }, v_rcp_length);

        auto v_select = Vector4::MaskCompareEqual(v_infinite_length, v_zero_length);
        v_length = Vector4::Select(v_length_sq, v_length, v_select);
        v_normal = Vector4::Select(v_length_sq, v_normal, v_select);

        auto v_max = Vector4::CompareGreater(v_length, max);
        auto v_min = Vector4::CompareLess(v_length, min);

        auto v_clamp_length = Vector4::Select(v_length, max, v_max);
        v_clamp_length = Vector4::Select(v_clamp_length, min, v_min);

        auto v_result = Vector4::Multiply(v_normal, v_clamp_length);

        auto v_control = Vector4::MaskCompareEqual(v_max, v_min);
        v_result = Vector4::Select(v_result, { v.V }, v_control);
        return { v_result.V };
    }

    mathinline Vector2 mathcall Vector2::Refract(Vector2 incident, Vector2 normal, float refraction_index) noexcept
    {
        auto v_index = Vector4::Make(refraction_index);
        return Vector2::Refract(incident, normal, v_index);
    }

    mathinline Vector2 mathcall Vector2::Refract(Vector2 incident, Vector2 normal, Vector4 refraction_index) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto f_i_dot_n =
            (incident.V.F[0] * normal.V.F[0]) +
            (incident.V.F[1] * normal.V.F[1]);

        auto f_ry = 1.0F - f_i_dot_n;
        auto f_rx = 1.0F - (f_ry * refraction_index.V.F[0] * refraction_index.V.F[0]);
        f_ry = 1.0F - (f_ry * refraction_index.V.F[1] * refraction_index.V.F[1]);

        if (f_rx >= 0.0F)
        {
            f_rx = (refraction_index.V.F[0] * incident.V.F[0]) - (normal.V.F[0] * ((refraction_index.V.F[0] * f_i_dot_n) + sqrtf(f_rx)));
        }
        else
        {
            f_rx = 0.0F;
        }

        if (f_ry >= 0.0F)
        {
            f_ry = (refraction_index.V.F[1] * incident.V.F[1]) - (normal.V.F[1] * ((refraction_index.V.F[1] * f_i_dot_n) + sqrtf(f_ry)));
        }
        else
        {
            f_ry = 0.0F;
        }

        Detail::Vector4F32 v_result = { { {
                f_rx, f_ry, 0.0F, 0.0F
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_i_dot_n = Vector2::Dot(incident, normal).V;
        auto v_temp = _mm_mul_ps(v_i_dot_n, v_i_dot_n);
        v_temp = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_temp);
        v_temp = _mm_mul_ps(v_temp, refraction_index.V);
        v_temp = _mm_mul_ps(v_temp, refraction_index.V);
        v_temp = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_temp);

        auto v_mask = _mm_cmpgt_ps(v_temp, Detail::VEC4_ZERO_4.V);
        v_temp = _mm_sqrt_ps(v_temp);

        auto v_result = _mm_mul_ps(refraction_index.V, v_i_dot_n);
        v_temp = _mm_add_ps(v_temp, v_result);
        v_result = _mm_mul_ps(refraction_index.V, incident.V);
        v_temp = _mm_mul_ps(v_temp, normal.V);
        v_result = _mm_sub_ps(v_result, v_temp);
        v_result = _mm_and_ps(v_result, v_mask);
        return { v_result };
#endif
    }

    mathinline Vector2 mathcall Vector2::Orthogonal(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                -v.V.F[1],
                v.V.F[0],
                0.0F,
                0.0F,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 00, 1));
        v_result = _mm_mul_ps(v_result, Detail::VEC4_NEGATE_X.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector2::AngleBetweenNormalsEst(Vector2 n1, Vector2 n2) noexcept
    {
        auto v_result = Vector2::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACosEst(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector2::AngleBetweenNormals(Vector2 n1, Vector2 n2) noexcept
    {
        auto v_result = Vector2::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACos(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector2::AngleBetweenVectors(Vector2 v1, Vector2 v2) noexcept
    {
        auto v_l1 = Vector2::ReciprocalLength(v1);
        auto v_l2 = Vector2::ReciprocalLength(v2);
        auto v_dot = Vector2::Dot(v1, v2);
        v_l1 = Vector4::Multiply(v_l1, v_l2);

        auto v_cos_angle = Vector4::Multiply(v_dot, v_l1);
        v_cos_angle = Vector4::Clamp(v_cos_angle, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_cos_angle = Vector4::ACos(v_cos_angle);
        return v_cos_angle;
    }

    mathinline Vector4 mathcall Vector2::LinePointDistance(Vector2 line_point1, Vector2 line_point2, Vector2 point) noexcept
    {
        auto v_point_vector = Vector4::Subtract({ point.V }, { line_point1.V });
        auto v_line_vector = Vector4::Subtract({ line_point2.V }, { line_point1.V });

        auto v_length_sq = Vector2::LengthSquared({ v_line_vector.V });

        auto v_point_projection_scale = Vector2::Dot({ v_point_vector.V }, { v_line_vector.V });
        v_point_projection_scale = Vector4::Divide(v_point_projection_scale, v_length_sq);

        auto v_distance_vector = Vector4::Multiply(v_line_vector, v_point_projection_scale);
        v_distance_vector = Vector4::Subtract(v_point_vector, v_distance_vector);
        return Vector2::Length({ v_distance_vector.V });
    }

    mathinline Vector4 mathcall Vector2::IntersectLine(Vector2 line1_point1, Vector2 line1_point2, Vector2 line2_point1, Vector2 line2_point2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_v1 = Vector4::Subtract({ line1_point2.V }, { line1_point1.V });
        auto v_v2 = Vector4::Subtract({ line2_point2.V }, { line2_point1.V });
        auto v_v3 = Vector4::Subtract({ line1_point1.V }, { line2_point1.V });

        auto v_c1 = Vector2::Cross({ v_v1.V }, { v_v2.V });
        auto v_c2 = Vector2::Cross({ v_v2.V }, { v_v3.V });

        auto v_zero = Vector4::Zero();

        Vector4 v_result;

        if (Vector2::IsEqual({ v_c1.V }, { v_zero.V }, { Detail::VEC4_EPSILON.V }))
        {
            if (Vector2::IsEqual({ v_c2.V }, { v_zero.V }, { Detail::VEC4_EPSILON.V }))
            {
                v_result = { Detail::VEC4_INFINITY.V };
            }
            else
            {
                v_result = { Detail::VEC4_QNAN.V };
            }
        }
        else
        {
            auto v_scale = Vector4::Reciprocal(v_c1);
            v_scale = Vector4::Multiply(v_c2, v_scale);
            v_result = Vector4::MultiplyAdd(v_v1, v_scale, { line1_point1.V });
        }

        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_v1 = _mm_sub_ps(line1_point2.V, line1_point1.V);
        auto v_v2 = _mm_sub_ps(line2_point2.V, line2_point1.V);
        auto v_v3 = _mm_sub_ps(line1_point1.V, line2_point1.V);

        auto v_c1 = Vector2::Cross({ v_v1 }, { v_v2 }).V;
        auto v_c2 = Vector2::Cross({ v_v2 }, { v_v3 }).V;

        auto v_result_mask = _mm_setzero_ps();
        v_result_mask = _mm_sub_ps(v_result_mask, v_c1);
        v_result_mask = _mm_max_ps(v_result_mask, v_c1);

        v_result_mask = _mm_cmpgt_ps(v_result_mask, Detail::VEC4_EPSILON.V);

        auto v_fail_mask = _mm_setzero_ps();
        v_fail_mask = _mm_sub_ps(v_fail_mask, v_c2);
        v_fail_mask = _mm_max_ps(v_fail_mask, v_c2);
        v_fail_mask = _mm_cmple_ps(v_fail_mask, Detail::VEC4_EPSILON.V);

        auto v_fail = _mm_and_ps(v_fail_mask, Detail::VEC4_INFINITY.V);
        v_fail_mask = _mm_andnot_ps(v_fail_mask, Detail::VEC4_QNAN.V);
        v_fail = _mm_or_ps(v_fail, v_fail_mask);

        auto v_result = _mm_div_ps(v_c2, v_c1);
        v_result = _mm_mul_ps(v_result, v_v1);
        v_result = _mm_add_ps(v_result, line1_point1.V);

        v_result = _mm_and_ps(v_result, v_result_mask);
        v_result_mask = _mm_andnot_ps(v_result_mask, v_fail);
        v_result = _mm_or_ps(v_result, v_result_mask);

        return { v_result };
#endif
    }

    mathinline Vector2 mathcall Vector2::Transform(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_y = Vector4::SplatY({ v.V });
        auto v_x = Vector4::SplatX({ v.V });

        auto v_result = Vector4::MultiplyAdd(v_y, { m.M.R[1] }, { m.M.R[3] });
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_fmadd_ps(v_result, m.M.R[1], m.M.R[3]);
        auto v_temp = _mm_broadcastss_ps(v.V);
        v_result = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        return { v_result };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        v_result = _mm_mul_ps(v_result, m.M.R[0]);
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_temp = _mm_mul_ps(v_temp, m.M.R[1]);
        v_result = _mm_add_ps(v_result, v_temp);
        v_result = _mm_add_ps(v_result, m.M.R[3]);
        return { v_result };
#endif
    }

    mathinline Vector2 mathcall Vector2::TransformCoord(Vector2 v, Matrix m) noexcept
    {
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_fmadd_ps(v_result, m.M.R[1], m.M.R[3]);
        auto v_temp = _mm_broadcastss_ps(v.V);
        v_result = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        auto v_w = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 3, 3, 3));
        v_result = _mm_div_ps(v_result, v_w);
        return { v_result };
#else
        auto v_y = Vector4::SplatY({ v.V });
        auto v_x = Vector4::SplatX({ v.V });
        auto v_result = Vector4::MultiplyAdd(v_y, { m.M.R[1] }, { m.M.R[3] });
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);
        auto v_w = Vector4::SplatW(v_result);
        v_result = Vector4::Divide(v_result, v_w);
        return { v_result.V };
#endif
    }

    mathinline Vector2 mathcall Vector2::TransformNormal(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_y = Vector4::SplatY({ v.V });
        auto v_x = Vector4::SplatX({ v.V });
        auto v_result = Vector4::Multiply(v_y, { m.M.R[1] });
        v_result = Vector4::MultiplyAdd(v_x, { m.M.R[0] }, v_result);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_mul_ps(v_result, m.M.R[1]);
        auto v_temp = _mm_broadcastss_ps(v.V);
        v_result = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        return { v_result };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        v_result = _mm_mul_ps(v_result, m.M.R[0]);
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_temp = _mm_mul_ps(v_temp, m.M.R[1]);
        v_result = _mm_add_ps(v_result, v_temp);
        return { v_result };
#endif
    }
}
