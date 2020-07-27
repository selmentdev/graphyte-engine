#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Ieee754.hxx>
#include <GxBase/Types.hxx>
#include <GxBase/Maths.Types.hxx>


// =================================================================================================
//
// Common enum types
//

namespace Graphyte::Maths
{
    enum class SelectMask : uint32_t
    {
        Select0 = UINT32_C(0x00000000),
        Select1 = UINT32_C(0xffffffff),
    };

    // Order: X, Y, Z, W
    enum class InsertMask : uint8_t
    {
        AAAA = 0b0000,
        AAAB = 0b0001,
        AABA = 0b0010,
        AABB = 0b0011,
        ABAA = 0b0100,
        ABAB = 0b0101,
        ABBA = 0b0110,
        ABBB = 0b0111,
        BAAA = 0b0000,
        BAAB = 0b0001,
        BABA = 0b0010,
        BABB = 0b0011,
        BBAA = 0b0100,
        BBAB = 0b0101,
        BBBA = 0b0110,
        BBBB = 0b0111,
    };

    enum class SwizzleMask
    {
        XXXX,
        YXXX,
        ZXXX,
        WXXX,
        XYXX,
        YYXX,
        ZYXX,
        WYXX,
        XZXX,
        YZXX,
        ZZXX,
        WZXX,
        XWXX,
        YWXX,
        ZWXX,
        WWXX,
        XXYX,
        YXYX,
        ZXYX,
        WXYX,
        XYYX,
        YYYX,
        ZYYX,
        WYYX,
        XZYX,
        YZYX,
        ZZYX,
        WZYX,
        XWYX,
        YWYX,
        ZWYX,
        WWYX,
        XXZX,
        YXZX,
        ZXZX,
        WXZX,
        XYZX,
        YYZX,
        ZYZX,
        WYZX,
        XZZX,
        YZZX,
        ZZZX,
        WZZX,
        XWZX,
        YWZX,
        ZWZX,
        WWZX,
        XXWX,
        YXWX,
        ZXWX,
        WXWX,
        XYWX,
        YYWX,
        ZYWX,
        WYWX,
        XZWX,
        YZWX,
        ZZWX,
        WZWX,
        XWWX,
        YWWX,
        ZWWX,
        WWWX,

        XXXY,
        YXXY,
        ZXXY,
        WXXY,
        XYXY,
        YYXY,
        ZYXY,
        WYXY,
        XZXY,
        YZXY,
        ZZXY,
        WZXY,
        XWXY,
        YWXY,
        ZWXY,
        WWXY,
        XXYY,
        YXYY,
        ZXYY,
        WXYY,
        XYYY,
        YYYY,
        ZYYY,
        WYYY,
        XZYY,
        YZYY,
        ZZYY,
        WZYY,
        XWYY,
        YWYY,
        ZWYY,
        WWYY,
        XXZY,
        YXZY,
        ZXZY,
        WXZY,
        XYZY,
        YYZY,
        ZYZY,
        WYZY,
        XZZY,
        YZZY,
        ZZZY,
        WZZY,
        XWZY,
        YWZY,
        ZWZY,
        WWZY,
        XXWY,
        YXWY,
        ZXWY,
        WXWY,
        XYWY,
        YYWY,
        ZYWY,
        WYWY,
        XZWY,
        YZWY,
        ZZWY,
        WZWY,
        XWWY,
        YWWY,
        ZWWY,
        WWWY,

        XXXZ,
        YXXZ,
        ZXXZ,
        WXXZ,
        XYXZ,
        YYXZ,
        ZYXZ,
        WYXZ,
        XZXZ,
        YZXZ,
        ZZXZ,
        WZXZ,
        XWXZ,
        YWXZ,
        ZWXZ,
        WWXZ,
        XXYZ,
        YXYZ,
        ZXYZ,
        WXYZ,
        XYYZ,
        YYYZ,
        ZYYZ,
        WYYZ,
        XZYZ,
        YZYZ,
        ZZYZ,
        WZYZ,
        XWYZ,
        YWYZ,
        ZWYZ,
        WWYZ,
        XXZZ,
        YXZZ,
        ZXZZ,
        WXZZ,
        XYZZ,
        YYZZ,
        ZYZZ,
        WYZZ,
        XZZZ,
        YZZZ,
        ZZZZ,
        WZZZ,
        XWZZ,
        YWZZ,
        ZWZZ,
        WWZZ,
        XXWZ,
        YXWZ,
        ZXWZ,
        WXWZ,
        XYWZ,
        YYWZ,
        ZYWZ,
        WYWZ,
        XZWZ,
        YZWZ,
        ZZWZ,
        WZWZ,
        XWWZ,
        YWWZ,
        ZWWZ,
        WWWZ,

        XXXW,
        YXXW,
        ZXXW,
        WXXW,
        XYXW,
        YYXW,
        ZYXW,
        WYXW,
        XZXW,
        YZXW,
        ZZXW,
        WZXW,
        XWXW,
        YWXW,
        ZWXW,
        WWXW,
        XXYW,
        YXYW,
        ZXYW,
        WXYW,
        XYYW,
        YYYW,
        ZYYW,
        WYYW,
        XZYW,
        YZYW,
        ZZYW,
        WZYW,
        XWYW,
        YWYW,
        ZWYW,
        WWYW,
        XXZW,
        YXZW,
        ZXZW,
        WXZW,
        XYZW,
        YYZW,
        ZYZW,
        WYZW,
        XZZW,
        YZZW,
        ZZZW,
        WZZW,
        XWZW,
        YWZW,
        ZWZW,
        WWZW,
        XXWW,
        YXWW,
        ZXWW,
        WXWW,
        XYWW,
        YYWW,
        ZYWW,
        WYWW,
        XZWW,
        YZWW,
        ZZWW,
        WZWW,
        XWWW,
        YWWW,
        ZWWW,
        WWWW,
    };
}

// =================================================================================================
//
// Reinterpret operation between types
//

namespace Graphyte::Maths
{
    //template <typename TTo, typename TFrom, std::enable_if_t<!std::is_same_v<std::remove_cv_t<TTo>, std::remove_cv_t<TFrom>>, int> = 0>
    //mathinline TTo mathcall As(TFrom v) noexcept
    //{
    //    return { v.V };
    //}
    //
    //template <typename TTo>
    //mathinline TTo mathcall As(Impl::NativeFloat32x4 v) noexcept
    //{
    //    return { v };
    //}
}


// =================================================================================================
//
// Constant splatting
//

namespace Graphyte::Maths::Impl
{
    mathinline NativeFloat32x4 mathcall ConvertIntToFloat(NativeFloat32x4 vint, uint32_t exponent) noexcept
    {
        GX_ASSERT(exponent < 32);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const scale = 1.0F / static_cast<float>(1U << exponent);

        ConstFloat32x4 const result{ { {
            static_cast<float>(static_cast<int32_t>(vint.U[0])) * scale,
            static_cast<float>(static_cast<int32_t>(vint.U[1])) * scale,
            static_cast<float>(static_cast<int32_t>(vint.U[2])) * scale,
            static_cast<float>(static_cast<int32_t>(vint.U[3])) * scale,
        } } };

        return result.V;
#elif GRAPHYTE_HW_NEON
        float const scale    = 1.0F / static_cast<float>(1U << exponent);
        float32x4_t const r0 = vcvtq_f32_s32(vint);
        float32x4_t const r1 = vmulq_n_f32(r0, scale);
        return r1;
#elif GRAPHYTE_HW_AVX
        __m128 const r0     = _mm_cvtepi32_ps(_mm_castps_si128(vint));
        uint32_t uscale     = 0x3F800000U - (exponent << 23);
        __m128i const scale = _mm_set1_epi32(static_cast<int>(uscale));
        __m128 const r1     = _mm_mul_ps(r0, _mm_castsi128_ps(scale));
        return r1;
#endif
    }

    mathinline NativeFloat32x4 mathcall ConvertFloatToInt(NativeFloat32x4 vfloat, uint32_t exponent) noexcept
    {
        GX_ASSERT(exponent < 32);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const scale = static_cast<float>(1U << exponent);

        NativeFloat32x4 result;

        for (size_t index = 0; index < 4; ++index)
        {
            float const t = vfloat.F[index] * scale;
            int32_t r;

            if (t <= -(65536.0F * 32768.0F))
            {
                r = (-0x7FFFFFFF) - 1;
            }
            else if (t > ((65536.0f * 32768.0f) - 128.0f))
            {
                r = 0x7FFFFFFF;
            }
            else
            {
                r = static_cast<int32_t>(t);
            }

            result.I[index] = r;
        }

        return result;
#elif GRAPHYTE_HW_NEON
        float32x4_t const r0      = vmulq_n_f32(vfloat, static_cast<float>(1U << exponent));
        uint32x4_t const overflow = vcgtq_f32(r0, VEC4_INTMAX.V);
        int32x4_t const r1        = vcvtq_s32_f32(r0);
        uint32x4_t const r2       = vandq_u32(overflow, VEC4_MASK_ABS.V);
        uint32x4_t const r3       = vbicq_u32(r1, overflow);
        uint32x4_t const r4       = vorrq_u32(r3, r2);
        return vreinterpretq_f32_u32(r4);
#elif GRAPHYTE_HW_AVX
        __m128 const r0       = _mm_set_ps1(static_cast<float>(1U << exponent));
        __m128 const r1       = _mm_mul_ps(r0, vfloat);
        __m128 const overflow = _mm_cmpgt_ps(r0, VEC4_INTMAX.V);
        __m128i const r2      = _mm_cvttps_epi32(r1);
        __m128 const r3       = _mm_and_ps(overflow, VEC4_MASK_ABS.V);
        __m128 const r4       = _mm_andnot_ps(overflow, _mm_castsi128_ps(r2));
        __m128 const r5       = _mm_or_ps(r4, r3);
        return r5;
#endif
    }

    mathinline NativeFloat32x4 mathcall ConvertUIntToFloat(NativeFloat32x4 vuint, uint32_t exponent) noexcept
    {
        GX_ASSERT(exponent < 32);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const scale = 1.0F / static_cast<float>(1U << exponent);

        ConstFloat32x4 const result{ { {
            static_cast<float>(vuint.U[0]) * scale,
            static_cast<float>(vuint.U[1]) * scale,
            static_cast<float>(vuint.U[2]) * scale,
            static_cast<float>(vuint.U[3]) * scale,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        float const scale    = 1.0F / static_cast<float>(1U << exponent);
        float32x4_t const r0 = vcvtq_f32_u32(vuint);
        float32x4_t const r1 = vmulq_n_f32(r0, scale);
        return r1;
#elif GRAPHYTE_HW_AVX
        __m128 const mask0    = _mm_and_ps(vuint, VEC4_NEGATIVE_ZERO.V);
        __m128 const r0       = _mm_xor_ps(vuint, mask0);
        __m128 const r1       = _mm_cvtepi32_ps(_mm_castps_si128(r0));
        __m128i const mask1   = _mm_srai_epi32(_mm_castps_si128(mask0), 31);
        __m128 const mask2    = _mm_and_ps(_mm_castsi128_ps(mask1), VEC4_UNSIGNED_FIX.V);
        __m128 const r2       = _mm_add_ps(r1, mask2);
        uint32_t const uscale = 0x3F800000U - (exponent << 23);
        __m128i const iscale  = _mm_set1_epi32(static_cast<int>(uscale));
        __m128 const r3       = _mm_mul_ps(r2, _mm_castsi128_ps(iscale));
        return r3;
#endif
    }

    mathinline NativeFloat32x4 mathcall ConvertFloatToUInt(NativeFloat32x4 vfloat, uint32_t exponent)
    {
        GX_ASSERT(exponent < 32);

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const scale = static_cast<float>(1U << exponent);

        NativeFloat32x4 result;

        for (size_t index = 0; index < 4; ++index)
        {
            float const t = vfloat.F[index] * scale;
            uint32_t r;

            if (t <= 0.0F)
            {
                r = 0;
            }
            else if (t > (65536.0F * 65536.0F))
            {
                r = 0xFFFFFFFF;
            }
            else
            {
                r = static_cast<uint32_t>(t);
            }

            result.U[index] = r;
        }

        return result;
#elif GRAPHYTE_HW_NEON
        float32x4_t const r0      = vmulq_n_f32(vfloat, static_cast<float>(1U << exponent));
        uint32x4_t const overflow = vcgtq_f32(r0, VEC4_UINTMAX.V);
        uint32x4_t const r1       = vcvtq_u32_f32(r0);
        uint32x4_t const r2       = vbicq_u32(r1, overflow);
        uint32x4_t const r3       = vorrq_u32(overflow, r2);
        return vreinterpretq_f32_u32(r3);
#elif GRAPHYTE_HW_AVX
        __m128 const r0       = _mm_set_ps1(static_cast<float>(1U << exponent));
        __m128 const r1       = _mm_mul_ps(r0, vfloat);
        __m128 const r2       = _mm_max_ps(r1, _mm_setzero_ps());
        __m128 const overflow = _mm_cmpgt_ps(r2, VEC4_UINTMAX.V);
        __m128 const fix      = VEC4_UNSIGNED_FIX.V;
        __m128 const mask     = _mm_cmpge_ps(r2, fix);
        __m128 const max      = _mm_and_ps(fix, mask);
        __m128 const r3       = _mm_sub_ps(r2, max);
        __m128i const r4      = _mm_cvttps_epi32(r3);
        __m128 const r5       = _mm_and_ps(mask, VEC4_NEGATIVE_ZERO.V);
        __m128 const r6       = _mm_xor_ps(_mm_castsi128_ps(r4), r5);
        __m128 const r7       = _mm_or_ps(r6, overflow);
        return r7;
#endif
    }

    mathinline NativeFloat32x4 mathcall SplatConstant(int32_t c, uint32_t exponent) noexcept
    {
        GX_ASSERT(-16 <= c && c < 16);
        GX_ASSERT(exponent < 32);

#if GRAPHYTE_MATH_NO_INTRINSICS
        ConstInt32x4 const result{ { {
            c,
            c,
            c,
            c,
        } } };

        return result.V;
#elif GRAPHYTE_HW_NEON
        int32x4_t const fscale    = vdupq_n_s32(c);
        float32x4_t const vfscale = vcvtq_f32_s32(fscale);
        uint32_t const uscale     = 0x3F800000U - (exponent << 23);
        uint32x4_t const vuscale  = vdupq_n_u32(uscale);
        float32x4_t const result  = vmulq_f32(vfscale, vreinterpretq_f32_u32(vuscale));
        return result;
#elif GRAPHYTE_HW_AVX
        __m128i const fscale  = _mm_set1_epi32(c);
        __m128 const vfscale  = _mm_cvtepi32_ps(fscale);
        uint32_t uscale       = 0x3F800000u - (exponent << 23);
        __m128i const vuscale = _mm_set1_epi32(static_cast<int>(uscale));
        __m128 const result   = _mm_mul_ps(vfscale, _mm_castsi128_ps(vuscale));
        return result;
#endif
    }

    mathinline NativeFloat32x4 mathcall SplatConstant(int32_t c) noexcept
    {
        GX_ASSERT(-16 <= c && c < 16);

#if GRAPHYTE_MATH_NO_INTRINSICS
        ConstInt32x4 const result{ { {
            c,
            c,
            c,
            c,
        } } };

        return result.V;
#elif GRAPHYTE_HW_NEON
        int32x4_t const r0   = vdupq_n_s32(c);
        float32x4_t const r1 = vreinterpretq_f32_s32(r0);
        return r1;
#elif GRAPHYTE_HW_AVX
        __m128i const r0 = _mm_set1_epi32(c);
        __m128 const r1  = _mm_castsi128_ps(r0);
        return r1;
#endif
    }
}

// =================================================================================================
//
// Vector space operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Length(Quaternion q) noexcept
    {
        return Length(Vector4{ q.V });
    }

    mathinline Vector4 mathcall ClampLength(Vector4 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(GetX(min) == GetY(min));
        GX_ASSERT(GetX(max) == GetY(max));
        GX_ASSERT(GetX(min) == GetZ(min));
        GX_ASSERT(GetX(max) == GetZ(max));
        GX_ASSERT(GetX(min) == GetW(min));
        GX_ASSERT(GetX(max) == GetW(max));

        GX_ASSERT(IsGreaterEqual(min, Vector4{ Impl::VEC4_ZERO_4.V }));
        GX_ASSERT(IsGreaterEqual(max, Vector4{ Impl::VEC4_ZERO_4.V }));
        GX_ASSERT(IsGreaterEqual(max, min));

        Vector4 const length_squared = LengthSquared(v);
        Vector4 const zero           = Zero<Vector4>();

        Vector4 const rcp_length     = InvSqrt(length_squared);
        Bool4 const mask_inf_length  = BitCompareEqual(length_squared, Vector4{ Impl::VEC4_INFINITY.V });
        Bool4 const mask_zero_length = CompareEqual(length_squared, zero);

        Vector4 const normal = Multiply(v, rcp_length);
        Vector4 const length = Multiply(length_squared, rcp_length);

        Bool4 const select          = CompareEqual(mask_inf_length, mask_zero_length);
        Vector4 const select_length = Select(length_squared, length, select);
        Vector4 const select_normal = Select(length_squared, normal, select);

        Bool4 const control_max = CompareGreater(select_length, max);
        Bool4 const control_min = CompareLess(select_length, min);

        Vector4 const clamp_length_0 = Select(select_length, max, control_max);
        Vector4 const clamp_length_1 = Select(clamp_length_0, min, control_min);

        Vector4 const clamped = Multiply(select_normal, clamp_length_1);
        Bool4 const control   = CompareEqual(control_max, control_min);
        Vector4 const result  = Select(clamped, v, control);
        return result;
    }

    mathinline Vector3 mathcall ClampLength(Vector3 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(GetX(min) == GetY(min));
        GX_ASSERT(GetX(max) == GetY(max));
        GX_ASSERT(GetX(min) == GetZ(min));
        GX_ASSERT(GetX(max) == GetZ(max));
        GX_ASSERT(GetX(min) == GetW(min));
        GX_ASSERT(GetX(max) == GetW(max));

        GX_ASSERT(IsGreaterEqual(min, Vector4{ Impl::VEC4_ZERO_4.V }));
        GX_ASSERT(IsGreaterEqual(max, Vector4{ Impl::VEC4_ZERO_4.V }));
        GX_ASSERT(IsGreaterEqual(max, min));

        Vector4 const length_squared = LengthSquared(v);
        Vector4 const zero           = Zero<Vector4>();

        Vector4 const rcp_length     = InvSqrt(length_squared);
        Bool4 const mask_inf_length  = BitCompareEqual(length_squared, Vector4{ Impl::VEC4_INFINITY.V });
        Bool4 const mask_zero_length = CompareEqual(length_squared, zero);

        Vector4 const normal = Multiply(Vector4{ v.V }, rcp_length);
        Vector4 const length = Multiply(length_squared, rcp_length);

        Bool4 const select          = CompareEqual(mask_inf_length, mask_zero_length);
        Vector4 const select_length = Select(length_squared, length, select);
        Vector4 const select_normal = Select(length_squared, normal, select);

        Bool4 const control_max = CompareGreater(select_length, max);
        Bool4 const control_min = CompareLess(select_length, min);

        Vector4 const clamp_length_0 = Select(select_length, max, control_max);
        Vector4 const clamp_length_1 = Select(clamp_length_0, min, control_min);

        Vector4 const clamped = Multiply(select_normal, clamp_length_1);
        Bool4 const control   = CompareEqual(control_max, control_min);
        Vector4 const result  = Select(clamped, Vector4{ v.V }, control);
        return Vector3{ result.V };
    }

    mathinline Vector2 mathcall ClampLength(Vector2 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(GetX(min) == GetY(min));
        GX_ASSERT(GetX(max) == GetY(max));
        GX_ASSERT(GetX(min) == GetZ(min));
        GX_ASSERT(GetX(max) == GetZ(max));
        GX_ASSERT(GetX(min) == GetW(min));
        GX_ASSERT(GetX(max) == GetW(max));

        GX_ASSERT(IsGreaterEqual(min, Vector4{ Impl::VEC4_ZERO_4.V }));
        GX_ASSERT(IsGreaterEqual(max, Vector4{ Impl::VEC4_ZERO_4.V }));
        GX_ASSERT(IsGreaterEqual(max, min));

        Vector4 const length_squared = LengthSquared(v);
        Vector4 const zero           = Zero<Vector4>();

        Vector4 const rcp_length     = InvSqrt(length_squared);
        Bool4 const mask_inf_length  = BitCompareEqual(length_squared, Vector4{ Impl::VEC4_INFINITY.V });
        Bool4 const mask_zero_length = CompareEqual(length_squared, zero);

        Vector4 const normal = Multiply(Vector4{ v.V }, rcp_length);
        Vector4 const length = Multiply(length_squared, rcp_length);

        Bool4 const select          = CompareEqual(mask_inf_length, mask_zero_length);
        Vector4 const select_length = Select(length_squared, length, select);
        Vector4 const select_normal = Select(length_squared, normal, select);

        Bool4 const control_max = CompareGreater(select_length, max);
        Bool4 const control_min = CompareLess(select_length, min);

        Vector4 const clamp_length_0 = Select(select_length, max, control_max);
        Vector4 const clamp_length_1 = Select(clamp_length_0, min, control_min);

        Vector4 const clamped = Multiply(select_normal, clamp_length_1);
        Bool4 const control   = CompareEqual(control_max, control_min);
        Vector4 const result  = Select(clamped, Vector4{ v.V }, control);
        return Vector2{ result.V };
    }
}



// =================================================================================================
//
// Intersections
//

namespace Graphyte::Maths
{
    mathinline Vector3 mathcall LinePlaneIntersection(Plane plane, Vector3 start, Vector3 end) noexcept
    {
        Vector3 const plane_normal{ plane.V };
        Vector4 const plane_normal_dot_start = Dot(plane_normal, start);
        Vector4 const plane_normal_dot_end   = Dot(plane_normal, end);
        Vector4 const diff                   = Subtract(plane_normal_dot_start, plane_normal_dot_end);
        Vector4 const plane_dot_start        = DotCoord(plane, start);
        Vector4 const normalized             = Divide(plane_dot_start, diff);

        Vector3 const point_distance = Subtract(end, start);
        Vector3 const point_on_plane = MultiplyAdd(point_distance, Vector3{ normalized.V }, start);

        Vector3 const zero  = Zero<Vector3>();
        Bool4 const control = Bool4{ CompareEqual(Vector3{ diff.V }, zero, Epsilon<Vector4>()).V };
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
        Vector4 const cross0_length = Length(cross0);
        Vector3 const cross1        = Cross(Vector3{ plane2.V }, cross0);
        Vector4 const plane1_wwww   = SplatW(Vector4{ plane1.V });
        Vector4 const point0        = Multiply(Vector4{ cross1.V }, plane1_wwww);
        Vector3 const cross2        = Cross(cross0, Vector3{ plane1.V });
        Vector4 const plane2_wwww   = SplatW(Vector4{ plane2.V });
        Vector4 const point1        = MultiplyAdd(Vector4{ cross2.V }, plane2_wwww, point0);
        Vector4 const linepoint1    = Divide(point1, cross0_length);
        Vector4 const linepoint2    = Add(linepoint1, Vector4{ cross0.V });
        Bool4 const control         = CompareLessEqual(cross0_length, Vector4{ Impl::VEC4_EPSILON.V });

        out_line1 = Vector3{ Select(linepoint1, Nan<Vector4>(), control).V };
        out_line2 = Vector3{ Select(linepoint2, Nan<Vector4>(), control).V };
    }

    mathinline Vector2 mathcall LineLineIntersection(
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

        if (IsEqual(c0, zero, Epsilon<Vector4>()))
        {
            if (IsEqual(c1, zero, Epsilon<Vector4>()))
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
        __m128 const succ = _mm_cmpgt_ps(cmp2, Impl::VEC4_EPSILON.V);

        // check c1 for zero
        __m128 const fail0 = _mm_setzero_ps();
        __m128 const fail1 = _mm_sub_ps(fail0, c1);
        __m128 const fail2 = _mm_max_ps(fail1, c1);
        __m128 const fail3 = _mm_cmple_ps(fail2, Impl::VEC4_EPSILON.V);

        // select inf or nan based on result of comparison
        __m128 const fail4 = _mm_and_ps(fail3, Impl::VEC4_INFINITY.V);
        __m128 const fail5 = _mm_andnot_ps(fail3, Impl::VEC4_QNAN.V);
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
    mathinline Vector4 mathcall LinePointDistance(T line1, T line2, T point) noexcept
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


//==================================================================================================
//
// Unsequential algorithms
//

namespace Graphyte::Maths::Unsequential
{
    mathinline Vector4 mathcall Dot(
        Vector4 x1,
        Vector4 y1,
        Vector4 z1,
        Vector4 w1,
        Vector4 x2,
        Vector4 y2,
        Vector4 z2,
        Vector4 w2) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        Vector4 const r2 = MultiplyAdd(z1, z2, r1);
        Vector4 const r3 = MultiplyAdd(w1, w2, r2);
        return r3;
    }

    mathinline Vector4 mathcall Dot(
        Vector4 x1,
        Vector4 y1,
        Vector4 z1,
        Vector4 x2,
        Vector4 y2,
        Vector4 z2) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        Vector4 const r2 = MultiplyAdd(z1, z2, r1);
        return r2;
    }

    mathinline Vector4 mathcall Dot(
        Vector4 x1,
        Vector4 y1,
        Vector4 x2,
        Vector4 y2) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        return r1;
    }
}
