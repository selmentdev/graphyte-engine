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
// Swizzling
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall SumComponents(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const sum = (v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
            sum,
            sum,
            sum,
            sum,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const partial = _mm_hadd_ps(v.V, v.V);
        __m128 const result  = _mm_hadd_ps(partial, partial);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const partial = vpaddq_f32(v.V, v.V);
        float32x4_t const result  = vpaddq_f32(partial, partial);
        return { result };
#endif
    }
}


// =================================================================================================
//
// Easing functions
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Smoothstep(Vector4 a, Vector4 b, Vector4 x) noexcept
    {
        Vector4 const length = Subtract(x, a);
        Vector4 const base   = Subtract(b, a);
        Vector4 const t      = Divide(length, base);
        Vector4 const r0     = NegateMultiplyAdd(t, Replicate<Vector4>(2.0F), Replicate<Vector4>(3.0F));
        Vector4 const r1     = Multiply(r0, t);
        Vector4 const r2     = Multiply(r1, t);
        return r2;
    }

    mathinline Vector4 mathcall Smoothstep(Vector4 a, Vector4 b, float x) noexcept
    {
        return Smoothstep(a, b, Replicate<Vector4>(x));
    }

    mathinline float mathcall Smoothstep(float a, float b, float x) noexcept
    {
        float const t = Saturate((x - a) / (b - a));
        return t * (t * NegateMultiplyAdd(t, 2.0F, 3.0F));
    }

    mathinline float mathcall Cosine(float a, float b, float t) noexcept
    {
        float const t0 = (1.0F - Cos(t * Impl::ConstPi<float>)) * 0.5F;
        return Lerp(a, b, t0);
    }

    mathinline float mathcall EaseSmoothC2(float x) noexcept
    {
        return (x * x * x) * (x * ((x * 6.0F) - 15.0F) + 10.0F);
    }

    mathinline float mathcall Smooth(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        float const xx = (x - min) / (max - min);
        return (xx * (xx * (3.0F - (2.0F * x))));
    }

    mathinline float mathcall SmoothSquared(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        float const xx = (x * x);
        return Lerp(min, max, xx);
    }

    mathinline float mathcall SmoothInvSquared(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        float const ox   = 1.0F - x;
        float const oxox = ox * ox;
        float const xx   = 1.0F - oxox;
        return Lerp(min, max, xx);
    }

    mathinline float mathcall SmoothCubed(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        float const xx = (x * x * x);
        return Lerp(min, max, xx);
    }

    mathinline float mathcall SmoothInvCubed(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        float const ox     = 1.0F - x;
        float const oxoxox = ox * ox * ox;
        float const xx     = 1.0F - oxoxox;
        return Lerp(min, max, xx);
    }

    mathinline float mathcall Trapezoid(float a, float b, float c, float d, float t) noexcept
    {
        if (t <= a)
        {
            return 0.0F;
        }
        else if (t < b)
        {
            return (t - a) / (b - a);
        }
        else if (t < c)
        {
            return 1.0F;
        }
        else if (t < d)
        {
            return 1.0F - ((t - c) / (d - c));
        }

        return 0.0F;
    }

    mathinline float mathcall Trapezoid(float a, float b, float c, float d, float t, float min, float max) noexcept
    {
        return Lerp(min, max, Trapezoid(a, b, c, d, t));
    }
}


// =================================================================================================
//
// Vector space operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Dot(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fdot = (a.V.F[0] * b.V.F[0]) + (a.V.F[1] * b.V.F[1]) + (a.V.F[2] * b.V.F[2]) + (a.V.F[3] * b.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
            fdot,
            fdot,
            fdot,
            fdot,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(a.V, b.V, 0xFF) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_dp4(a.V, b.V) };
#endif
    }

    mathinline Vector4 mathcall Dot(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fdot = (a.V.F[0] * b.V.F[0]) + (a.V.F[1] * b.V.F[1]) + (a.V.F[2] * b.V.F[2]);

        Impl::ConstFloat32x4 const result{ { {
            fdot,
            fdot,
            fdot,
            fdot,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(a.V, b.V, 0x7F) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_dp3(a.V, b.V) };
#endif
    }

    mathinline Vector4 mathcall Dot(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fdot = (a.V.F[0] * b.V.F[0]) + (a.V.F[1] * b.V.F[1]);

        Impl::ConstFloat32x4 const result{ { {
            fdot,
            fdot,
            fdot,
            fdot,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(a.V, b.V, 0x3F) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_dp2(a.V, b.V) };
#endif
    }

    mathinline float mathcall Dot(float a, float b) noexcept
    {
        return a * b;
    }

    mathinline Vector4 mathcall LengthSquared(Vector4 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vector4 mathcall LengthSquared(Vector3 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline Vector4 mathcall LengthSquared(Vector2 v) noexcept
    {
        return Dot(v, v);
    }

    mathinline float mathcall LengthSquared(float v) noexcept
    {
        return v * v;
    }

    mathinline Vector4 mathcall Length(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length         = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Length(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length         = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Length(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length         = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Length(Quaternion q) noexcept
    {
        return Length(Vector4{ q.V });
    }

    mathinline Vector4 mathcall LengthEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length         = SqrtEst(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall LengthEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length         = SqrtEst(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall LengthEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length         = SqrtEst(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLength(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length     = InvSqrt(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const inv_length     = _mm_sqrt_ps(length_squared);
        __m128 const one            = Impl::VEC4_ONE_4.V;
        __m128 const length         = _mm_div_ps(one, inv_length);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLength(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length     = InvSqrt(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const inv_length     = _mm_sqrt_ps(length_squared);
        __m128 const one            = Impl::VEC4_ONE_4.V;
        __m128 const length         = _mm_div_ps(one, inv_length);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLength(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length     = InvSqrt(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const inv_length     = _mm_sqrt_ps(length_squared);
        __m128 const one            = Impl::VEC4_ONE_4.V;
        __m128 const length         = _mm_div_ps(one, inv_length);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLengthEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length     = InvSqrtEst(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLengthEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length     = InvSqrtEst(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLengthEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length     = InvSqrtEst(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Distance(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const difference = Subtract(b, a);
        Vector4 const result     = Length(difference);
        return result;
    }

    mathinline Vector3 mathcall Distance(Vector3 a, Vector3 b) noexcept
    {
        Vector3 const difference = Subtract(b, a);
        Vector4 const result     = Length(difference);
        return Vector3{ result.V };
    }

    mathinline Vector2 mathcall Distance(Vector2 a, Vector2 b) noexcept
    {
        Vector2 const difference = Subtract(b, a);
        Vector4 const result     = Length(difference);
        return Vector2{ result.V };
    }

    mathinline float mathcall Distance(float a, float b) noexcept
    {
        return fabsf(b - a);
    }

    mathinline Vector4 mathcall DistanceSquared(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const difference = Subtract(b, a);
        Vector4 const result     = LengthSquared(difference);
        return result;
    }

    mathinline Vector4 mathcall DistanceSquared(Vector3 a, Vector3 b) noexcept
    {
        Vector3 const difference = Subtract(b, a);
        Vector4 const result     = LengthSquared(difference);
        return result;
    }

    mathinline Vector4 mathcall DistanceSquared(Vector2 a, Vector2 b) noexcept
    {
        Vector2 const difference = Subtract(b, a);
        Vector4 const result     = LengthSquared(difference);
        return result;
    }

    mathinline float mathcall DistanceSquared(float a, float b) noexcept
    {
        float const difference = b - a;
        float const result     = difference * difference;
        return result;
    }

    mathinline bool mathcall IsUnit(Vector4 v) noexcept
    {
        // = |v|
        Vector4 const length = Length(v);
        // = |v| - 1
        Vector4 const difference = Subtract(length, One<Vector4>());
        // = | |v| - 1 |
        Vector4 const abs_difference = Abs(difference);
        // = (| |v| - 1 |) < eps
        return IsLess(abs_difference, Vector4{ Impl::VEC4_UNIT_EPSILON.V });
    }

    mathinline Vector4 mathcall Normalize(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const length = Length(v).V.F[0];

        float const rcp_length = (length > 0.0F)
                                     ? (1.0F / length)
                                     : length;

        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * rcp_length,
            v.V.F[1] * rcp_length,
            v.V.F[2] * rcp_length,
            v.V.F[3] * rcp_length,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_sqrt_ps(length_squared);

        __m128 const zero             = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf  = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized             = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan            = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf             = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector3 mathcall Normalize(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const length = Length(v).V.F[0];

        float const rcp_length = (length > 0.0F)
                                     ? (1.0F / length)
                                     : length;

        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * rcp_length,
            v.V.F[1] * rcp_length,
            v.V.F[2] * rcp_length,
            v.V.F[3] * rcp_length,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length         = _mm_sqrt_ps(length_squared);

        __m128 const zero             = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf  = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized             = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan            = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf             = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector2 mathcall Normalize(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const length = Length(v).V.F[0];

        float const rcp_length = (length > 0.0F)
                                     ? (1.0F / length)
                                     : length;

        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * rcp_length,
            v.V.F[1] * rcp_length,
            v.V.F[2] * rcp_length,
            v.V.F[3] * rcp_length,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length         = _mm_sqrt_ps(length_squared);

        __m128 const zero             = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf  = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized             = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan            = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf             = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector4 mathcall NormalizeEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const rcp_length = ReciprocalLength(v);
        Vector4 const result     = Multiply(v, rcp_length);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        __m128 const result         = _mm_mul_ps(length, v.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall NormalizeEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const rcp_length = ReciprocalLength(v);
        Vector3 const result     = Multiply(v, Vector3{ rcp_length.V });
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        __m128 const result         = _mm_mul_ps(length, v.V);
        return { result };
#endif
    }

    mathinline Vector2 mathcall NormalizeEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const rcp_length = ReciprocalLength(v);
        Vector2 const result     = Multiply(v, Vector2{ rcp_length.V });
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        __m128 const result         = _mm_mul_ps(length, v.V);
        return { result };
#endif
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

    mathinline Vector4 mathcall ClampLength(Vector4 v, float min, float max) noexcept
    {
        Vector4 const vmin = Replicate<Vector4>(min);
        Vector4 const vmax = Replicate<Vector4>(max);

        return ClampLength(v, vmin, vmax);
    }

    mathinline Vector3 mathcall ClampLength(Vector3 v, float min, float max) noexcept
    {
        Vector4 const vmin = Replicate<Vector4>(min);
        Vector4 const vmax = Replicate<Vector4>(max);

        return ClampLength(v, vmin, vmax);
    }

    mathinline Vector2 mathcall ClampLength(Vector2 v, float min, float max) noexcept
    {
        Vector4 const vmin = Replicate<Vector4>(min);
        Vector4 const vmax = Replicate<Vector4>(max);

        return ClampLength(v, vmin, vmax);
    }

    mathinline Vector4 mathcall Reflect(Vector4 incident, Vector4 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal) * normal
        Vector4 const dot    = Dot(incident, normal);
        Vector4 const dot2   = Add(dot, dot);
        Vector4 const result = NegateMultiplyAdd(dot2, normal, incident);
        return result;
    }

    mathinline Vector3 mathcall Reflect(Vector3 incident, Vector3 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal) * normal
        Vector4 const dot    = Dot(incident, normal);
        Vector4 const dot2   = Add(dot, dot);
        Vector3 const result = NegateMultiplyAdd(Vector3{ dot2.V }, normal, incident);
        return result;
    }

    mathinline Vector2 mathcall Reflect(Vector2 incident, Vector2 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal) * normal
        Vector4 const dot    = Dot(incident, normal);
        Vector4 const dot2   = Add(dot, dot);
        Vector2 const result = NegateMultiplyAdd(Vector2{ dot2.V }, normal, incident);
        return result;
    }

    mathinline Vector4 mathcall Refract(Vector4 incident, Vector4 normal, Vector4 index) noexcept
    {
        //
        // k = 1.0 - index * index * (1.0 - dot(N, I) * dot(N, I));
        // if (k < 0.0)
        //     R = T(0.0);
        // else
        //     R = index * I - (index * dot(N, I) + sqrt(k)) * N;
        //

        // r0 = i dot n
        Vector4 const i_dot_n = Dot(incident, normal);

        Vector4 const one{ Impl::VEC4_ONE_4.V };

        // r1 = 1 - (r0 * r0)
        Vector4 const r1 = NegateMultiplyAdd(i_dot_n, i_dot_n, one);

        // r2 = r1 * index
        Vector4 const r2 = Multiply(r1, index);

        // r3 = 1 - (index * r2)
        Vector4 const r3 = NegateMultiplyAdd(r2, index, one);

        // Check for zero
        Vector4 const zero = Zero<Vector4>();

        if (IsLessEqual(r3, zero))
        {
            // internal refraction
            return zero;
        }
        else
        {
            // r4 = sqrt(r3)
            Vector4 const r4 = Sqrt(r3);

            // r5 = (index * i_dot_n) + r4
            Vector4 const r5 = MultiplyAdd(index, i_dot_n, r4);

            // r6 = index * incident
            Vector4 const r6 = Multiply(index, incident);

            // r7 = r6 - (normal * r5)
            Vector4 const r7 = NegateMultiplyAdd(normal, r5, r6);

            return r7;
        }
    }

    mathinline Vector3 mathcall Refract(Vector3 incident, Vector3 normal, Vector4 index) noexcept
    {
        //
        // k = 1.0 - index * index * (1.0 - dot(N, I) * dot(N, I));
        // if (k < 0.0)
        //     R = T(0.0);
        // else
        //     R = index * I - (index * dot(N, I) + sqrt(k)) * N;
        //

        // r0 = i dot n
        Vector4 const i_dot_n = Dot(incident, normal);

        Vector4 const one{ Impl::VEC4_ONE_4.V };

        // r1 = 1 - (r0 * r0)
        Vector4 const r1 = NegateMultiplyAdd(i_dot_n, i_dot_n, one);

        // r2 = r1 * index
        Vector4 const r2 = Multiply(r1, index);

        // r3 = 1 - (index * r2)
        Vector4 const r3 = NegateMultiplyAdd(r2, index, one);

        // Check for zero
        Vector4 const zero = Zero<Vector4>();

        if (IsLessEqual(r3, zero))
        {
            // internal refraction
            return Vector3{ zero.V };
        }
        else
        {
            // r4 = sqrt(r3)
            Vector4 const r4 = Sqrt(r3);

            // r5 = (index * i_dot_n) + r4
            Vector4 const r5 = MultiplyAdd(index, i_dot_n, r4);

            // r6 = index * incident
            Vector4 const r6 = Multiply(index, Vector4{ incident.V });

            // r7 = r6 - (normal * r5)
            Vector4 const r7 = NegateMultiplyAdd(Vector4{ normal.V }, r5, r6);

            return Vector3{ r7.V };
        }
    }

    mathinline Vector2 mathcall Refract(Vector2 incident, Vector2 normal, Vector4 index) noexcept
    {
        //
        // k = 1.0 - index * index * (1.0 - dot(N, I) * dot(N, I));
        // if (k < 0.0)
        //     R = T(0.0);
        // else
        //     R = index * I - (index * dot(N, I) + sqrt(k)) * N;
        //

        // r0 = i dot n
        Vector4 const i_dot_n = Dot(incident, normal);

        Vector4 const one{ Impl::VEC4_ONE_4.V };

        // r1 = 1 - (r0 * r0)
        Vector4 const r1 = NegateMultiplyAdd(i_dot_n, i_dot_n, one);

        // r2 = r1 * index
        Vector4 const r2 = Multiply(r1, index);

        // r3 = 1 - (index * r2)
        Vector4 const r3 = NegateMultiplyAdd(r2, index, one);

        // Check for zero
        Vector4 const zero = Zero<Vector4>();

        if (IsLessEqual(r3, zero))
        {
            // internal refraction
            return Vector2{ zero.V };
        }
        else
        {
            // r4 = sqrt(r3)
            Vector4 const r4 = Sqrt(r3);

            // r5 = (index * i_dot_n) + r4
            Vector4 const r5 = MultiplyAdd(index, i_dot_n, r4);

            // r6 = index * incident
            Vector4 const r6 = Multiply(index, Vector4{ incident.V });

            // r7 = r6 - (normal * r5)
            Vector4 const r7 = NegateMultiplyAdd(Vector4{ normal.V }, r5, r6);

            return Vector2{ r7.V };
        }
    }

    mathinline Vector4 mathcall Refract(Vector4 incident, Vector4 normal, float index) noexcept
    {
        Vector4 const vindex = Replicate<Vector4>(index);
        return Refract(incident, normal, vindex);
    }

    mathinline Vector3 mathcall Refract(Vector3 incident, Vector3 normal, float index) noexcept
    {
        Vector4 const vindex = Replicate<Vector4>(index);
        return Refract(incident, normal, vindex);
    }

    mathinline Vector2 mathcall Refract(Vector2 incident, Vector2 normal, float index) noexcept
    {
        Vector4 const vindex = Replicate<Vector4>(index);
        return Refract(incident, normal, vindex);
    }

    mathinline Vector3 mathcall FaceForward(Vector3 normal, Vector3 incident, Vector3 reference) noexcept
    {
        Vector3 const dot0{ Dot(reference, incident).V };
        Vector3 const sign0 = Sign(dot0);
        Vector3 const r0    = Multiply(sign0, Replicate<Vector3>(-1.0f));
        Vector3 const r1    = Multiply(normal, r0);
        return r1;
    }

    mathinline Vector2 mathcall FaceForward(Vector2 normal, Vector2 incident, Vector2 reference) noexcept
    {
        Vector2 const dot0{ Dot(reference, incident).V };
        Vector2 const sign0 = Sign(dot0);
        Vector2 const r0    = Multiply(sign0, Replicate<Vector2>(-1.0f));
        Vector2 const r1    = Multiply(normal, r0);
        return r1;
    }

    mathinline Vector4 mathcall AngleBetweenNormals(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const cos_angle = Dot(a, b);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle             = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenNormals(Vector3 a, Vector3 b) noexcept
    {
        Vector4 const cos_angle = Dot(a, b);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle             = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenNormals(Vector2 a, Vector2 b) noexcept
    {
        Vector4 const cos_angle = Dot(a, b);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle             = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenVectors(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const rcp_len_a = ReciprocalLength(a);
        Vector4 const rcp_len_b = ReciprocalLength(b);

        Vector4 const a_dot_b       = Dot(a, b);
        Vector4 const rcp_len_ab_sq = Multiply(rcp_len_a, rcp_len_b);
        Vector4 const cos_angle     = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle             = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenVectors(Vector3 a, Vector3 b) noexcept
    {
        Vector4 const rcp_len_a = ReciprocalLength(a);
        Vector4 const rcp_len_b = ReciprocalLength(b);

        Vector4 const a_dot_b       = Dot(a, b);
        Vector4 const rcp_len_ab_sq = Multiply(rcp_len_a, rcp_len_b);
        Vector4 const cos_angle     = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle             = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenVectors(Vector2 a, Vector2 b) noexcept
    {
        Vector4 const rcp_len_a = ReciprocalLength(a);
        Vector4 const rcp_len_b = ReciprocalLength(b);

        Vector4 const a_dot_b       = Dot(a, b);
        Vector4 const rcp_len_ab_sq = Multiply(rcp_len_a, rcp_len_b);
        Vector4 const cos_angle     = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle             = Acos(cos_angle_clamped);
        return angle;
    }
}


// =================================================================================================
//
// Move towards
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall MoveTowards(Vector4 current, Vector4 target, float max_distance) noexcept
    {
        Vector4 const diff   = Subtract(target, current);
        Vector4 const length = Length(diff);
        Vector4 const vmax   = Replicate<Vector4>(max_distance);

        if (IsLessEqual(length, vmax) || IsZero(length))
        {
            return target;
        }

        return MultiplyAdd(current, Divide(diff, length), vmax);
    }

    mathinline Vector3 mathcall MoveTowards(Vector3 current, Vector3 target, float max_distance) noexcept
    {
        Vector3 const diff = Subtract(target, current);
        Vector3 const length{ Length(diff).V };
        Vector3 const vmax = Replicate<Vector3>(max_distance);

        if (IsLessEqual(length, vmax) || IsZero(length))
        {
            return target;
        }

        return MultiplyAdd(current, Divide(diff, length), vmax);
    }

    mathinline Vector2 mathcall MoveTowards(Vector2 current, Vector2 target, float max_distance) noexcept
    {
        Vector2 const diff = Subtract(target, current);
        Vector2 const length{ Length(diff).V };
        Vector2 const vmax = Replicate<Vector2>(max_distance);

        if (IsLessEqual(length, vmax) || IsZero(length))
        {
            return target;
        }

        return MultiplyAdd(current, Divide(diff, length), vmax);
    }

    mathinline float mathcall MoveTowards(float current, float target, float max_distance) noexcept
    {
        float const distance = target - current;

        if (Abs(distance) <= max_distance)
        {
            return target;
        }

        return current + Sign(distance) * max_distance;
    }
}

// =================================================================================================
//
// Vector4 operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Cross(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (((b.V.F[2] * c.V.F[3]) - (b.V.F[3] * c.V.F[2])) * a.V.F[1]) - (((b.V.F[1] * c.V.F[3]) - (b.V.F[3] * c.V.F[1])) * a.V.F[2]) + (((b.V.F[1] * c.V.F[2]) - (b.V.F[2] * c.V.F[1])) * a.V.F[3]),
            (((b.V.F[3] * c.V.F[2]) - (b.V.F[2] * c.V.F[3])) * a.V.F[0]) - (((b.V.F[3] * c.V.F[0]) - (b.V.F[0] * c.V.F[3])) * a.V.F[2]) + (((b.V.F[2] * c.V.F[0]) - (b.V.F[0] * c.V.F[2])) * a.V.F[3]),
            (((b.V.F[1] * c.V.F[3]) - (b.V.F[3] * c.V.F[1])) * a.V.F[0]) - (((b.V.F[0] * c.V.F[3]) - (b.V.F[3] * c.V.F[0])) * a.V.F[1]) + (((b.V.F[0] * c.V.F[1]) - (b.V.F[1] * c.V.F[0])) * a.V.F[3]),
            (((b.V.F[2] * c.V.F[1]) - (b.V.F[1] * c.V.F[2])) * a.V.F[0]) - (((b.V.F[2] * c.V.F[0]) - (b.V.F[0] * c.V.F[2])) * a.V.F[1]) + (((b.V.F[1] * c.V.F[0]) - (b.V.F[0] * c.V.F[1])) * a.V.F[2]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        // r0 = ((b.zwyz * c.wzwy) - (b.wzwy * c.zwyz)) * a.yxxx

        __m128 const b0 = _mm_permute_ps(b.V, _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const c0 = _mm_permute_ps(c.V, _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const m0 = _mm_mul_ps(b0, c0);

        __m128 const b1 = _mm_permute_ps(b.V, _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const c1 = _mm_permute_ps(c0, _MM_SHUFFLE(1, 3, 0, 1)); // wzwy -> zwyz
        __m128 const m1 = _mm_mul_ps(b1, c1);

        __m128 const s0 = _mm_sub_ps(m0, m1);
        __m128 const a0 = _mm_permute_ps(a.V, _MM_SHUFFLE(0, 0, 0, 1));
        __m128 const r0 = _mm_mul_ps(s0, a0);

        // r1 = ((b.ywxz * c.wxwx) - (b.wxwx * c.ywxz)) * a.zzyy
        __m128 const b2 = _mm_permute_ps(b.V, _MM_SHUFFLE(2, 0, 3, 1));
        __m128 const c2 = _mm_permute_ps(c.V, _MM_SHUFFLE(0, 3, 0, 3));
        __m128 const m2 = _mm_mul_ps(b2, c2);

        __m128 const b3 = _mm_permute_ps(b2, _MM_SHUFFLE(2, 1, 2, 1)); // ywxz -> wxwx
        __m128 const c3 = _mm_permute_ps(c.V, _MM_SHUFFLE(2, 0, 3, 1));
        __m128 const m3 = _mm_mul_ps(b3, c3);

        __m128 const s1 = _mm_sub_ps(m2, m3);
        __m128 const a1 = _mm_permute_ps(a.V, _MM_SHUFFLE(1, 1, 2, 2));
        __m128 const r1 = _mm_mul_ps(s1, a1);

        // t0 = r0 - r1
        __m128 const t0 = _mm_sub_ps(r0, r1);

        // r2 = ((b.yzxy * c.zxyx) - (b.zxyx * c.yzxy)) * a.wwwz
        __m128 const b4 = _mm_permute_ps(b.V, _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const c4 = _mm_permute_ps(c.V, _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const m4 = _mm_mul_ps(b4, c4);

        // yzxy ->  zxyx
        __m128 const b5 = _mm_permute_ps(b4, _MM_SHUFFLE(2, 0, 2, 1));
        __m128 const c5 = _mm_permute_ps(c.V, _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const m5 = _mm_mul_ps(b5, c5);

        __m128 const s2 = _mm_sub_ps(m4, m5);
        __m128 const a2 = _mm_permute_ps(a.V, _MM_SHUFFLE(2, 3, 3, 3));
        __m128 const r2 = _mm_mul_ps(s2, a2);

        // t1 = t0 + r2
        __m128 const result = _mm_add_ps(t0, r2);

        return { result };
#endif
    }

    mathinline Vector4 mathcall Orthogonal(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[2],
            v.V.F[3],
            -v.V.F[0],
            -v.V.F[1],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const flip_zw{ { {
            1.0F,
            1.0F,
            -1.0F,
            -1.0F,
        } } };

        __m128 const zwxy   = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 0, 3, 2));
        __m128 const result = _mm_mul_ps(zwxy, flip_zw.V);
        return { result };
#endif
    }

    mathinline Vector4 mathcall Transform(Vector4 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = (m.M.M[0][0] * v.V.F[0]) + (m.M.M[1][0] * v.V.F[1]) + (m.M.M[2][0] * v.V.F[2]) + (m.M.M[3][0] * v.V.F[3]);
        float const fy = (m.M.M[0][1] * v.V.F[0]) + (m.M.M[1][1] * v.V.F[1]) + (m.M.M[2][1] * v.V.F[2]) + (m.M.M[3][1] * v.V.F[3]);
        float const fz = (m.M.M[0][2] * v.V.F[0]) + (m.M.M[1][2] * v.V.F[1]) + (m.M.M[2][2] * v.V.F[2]) + (m.M.M[3][2] * v.V.F[3]);
        float const fw = (m.M.M[0][3] * v.V.F[0]) + (m.M.M[1][3] * v.V.F[1]) + (m.M.M[2][3] * v.V.F[2]) + (m.M.M[3][3] * v.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
            fx,
            fy,
            fz,
            fw,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r0   = _mm_mul_ps(wwww, m.M.R[3]);
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r1   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], r0);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r2   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r1);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r3   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r2);
        return { r3 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const x  = vmulq_lane_f32(m.M.R[0], xy, 0);
        float32x4_t const y  = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x2_t const zw = vget_high_f32(v.V);
        float32x4_t const z  = vmlaq_lane_f32(y, m.M.R[2], zw, 0);
        float32x4_t const w  = vmlaq_lane_f32(z, m.M.R[3], zw, 1);
        return { w };
#endif
    }
}


// =================================================================================================
//
// Vector3 operations
//

namespace Graphyte::Maths
{
    mathinline Vector3 mathcall Cross(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (a.V.F[1] * b.V.F[2]) - (a.V.F[2] * b.V.F[1]),
            (a.V.F[2] * b.V.F[0]) - (a.V.F[0] * b.V.F[2]),
            (a.V.F[0] * b.V.F[1]) - (a.V.F[1] * b.V.F[0]),
            0.0F,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [x, y]
        float32x2_t const a_xy = vget_low_f32(a.V);
        float32x2_t const b_xy = vget_low_f32(b.V);

        // = [y, x]
        float32x2_t const a_yx = vrev64_f32(a_xy);
        float32x2_t const b_yx = vrev64_f32(b_xy);

        // = [z, z]
        float32x2_t const a_zz = vdup_lane_f32(vget_high_f32(a.V), 0);
        float32x2_t const b_zz = vdup_lane_f32(vget_high_f32(b.V), 0);

        // = [y, x, x, y]
        float32x4_t const a_yxxy = vcombine_f32(a_yx, a_xy);
        float32x4_t const b_yxxy = vcombine_f32(b_yx, b_xy);

        // = [z, z, y, x]
        float32x4_t const b_zzyx = vcombine_f32(b_zz, b_yx);
        float32x4_t const a_zzyx = vcombine_f32(a_zz, a_yx);

        // = [
        //      a.y * b.z,
        //      a.x * b.z,
        //      a.x * b.y,
        //      a.y * b.x
        // ]
        float32x4_t const m0 = vmulq_f32(a_yxxy, b_zzyx);

        // = [
        //      (a.y * b.z) - (a.z * b.y),
        //      (a.x * b.z) - (a.z * b.x),
        //      (a.x * b.y) - (a.y * b.x),
        //      (a.y * b.x) - (a.x * b.y),
        // ]
        float32x4_t const m1 = vmlsq_f32(m0, a_zzyx, b_yxxy);

        // flip: m2.y = m1.y * -1
        // m1: (a.x * b.z) - (a.z * b.x)
        // m2: -(a.x * b.z) + (a.z * b.x) = (a.z * b.x) - (a.x * b.z)
        uint32x4_t const m2 = veorq_u32(vreinterpretq_u32_f32(m1), Impl::VEC4_MASK_FLIP_Y);

        uint32x4_t const m3 = vandq_u32(m2, Impl::VEC4_MASK_SELECT_1110.V);

        return { vreinterpretq_f32_u32(m3) };

#elif GRAPHYTE_HW_AVX
        // m0 = (a.yzx * b.zxy)
        __m128 const a0 = _mm_permute_ps(a.V, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const b0 = _mm_permute_ps(b.V, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 const m0 = _mm_mul_ps(a0, b0);

        // m1 = (a.zxy * b.yzx)
        __m128 const a1 = _mm_permute_ps(a0, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const b1 = _mm_permute_ps(b0, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 const m1 = _mm_mul_ps(a1, b1);

        // r0 = m0 - m1
        __m128 const r0     = _mm_sub_ps(m0, m1);
        __m128 const result = _mm_and_ps(r0, Impl::VEC4_MASK_COMPONENTS_3.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Orthogonal(Vector3 v) noexcept
    {
        Vector3 const zzz = SplatZ(v);
        Vector3 const yzy{ Swizzle<1, 2, 1, 1>(Vector4{ v.V }).V };
        Vector3 const negv = Negate(v);
        Vector3 const zero = Zero<Vector3>();

        Bool3 const cmp_zzz_negative = CompareLess(zzz, zero);
        Bool3 const cmp_yzy_negative = CompareLess(yzy, zero);

        Vector3 const s = Add(yzy, zzz);
        Vector3 const d = Subtract(yzy, zzz);

        Bool3 const select = CompareEqual(cmp_zzz_negative, cmp_yzy_negative);

        Vector4 const r0 = Permute<4, 0, 0, 0>(Vector4{ negv.V }, Vector4{ s.V });
        Vector4 const r1 = Permute<4, 0, 0, 0>(Vector4{ v.V }, Vector4{ d.V });

        Vector4 const result = Select(r1, r0, Bool4{ select.V });

        return Vector3{ result.V };
    }

    mathinline void mathcall ComponentsFromNormal(Vector3& out_parallel, Vector3& out_perpendicular, Vector3 v, Vector3 n) noexcept
    {
        Vector4 const scale    = Dot(v, n);
        Vector3 const parallel = Multiply(n, Vector3{ scale.V });

        out_parallel      = parallel;
        out_perpendicular = Subtract(v, parallel);
    }

    mathinline Vector3 mathcall Transform(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0   = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1   = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2   = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return Vector3{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const r2   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        return { r2 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x2_t const zn = vget_high_f32(v.V);
        float32x4_t const x  = vmlaq_lane_f32(m.M.R[3], m.M.R[0], xy, 0);
        float32x4_t const y  = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x4_t const z  = vmlaq_lane_f32(y, m.M.R[2], zn, 0);
        return { z };
#endif
    }

    mathinline Vector3 mathcall TransformCoord(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz   = SplatZ<Vector4>(v4);
        Vector4 const r0     = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy   = SplatY<Vector4>(v4);
        Vector4 const r1     = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx   = SplatX<Vector4>(v4);
        Vector4 const r2     = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        Vector4 const wwww   = SplatW<Vector4>(r2);
        Vector4 const result = Divide(r2, wwww);
        return Vector3{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r2   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        __m128 const wwww = _mm_permute_ps(r2, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r3   = _mm_div_ps(r2, wwww);
        return { r3 };
#endif
    }

    mathinline Vector3 mathcall TransformNormal(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0   = Multiply(zzzz, Vector4{ m.M.R[2] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1   = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2   = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return Vector3{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0   = _mm_mul_ps(xxxx, m.M.R[2]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const zzzz = _mm_broadcastss_ps(v.V);
        __m128 const r2   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[0], r1);
        return { r2 };
#endif
    }
}

// =================================================================================================
//
// Vector2 operations
//

namespace Graphyte::Maths
{
    mathinline Vector2 mathcall Cross(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = (a.V.F[0] * b.V.F[1]) - (a.V.F[1] * b.V.F[0]);

        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // b.yx * a.xy = [b.y * a.x, b.x * a.y]
        __m128 const b_yx          = _mm_permute_ps(b.V, _MM_SHUFFLE(0, 1, 0, 1));
        __m128 const b_yx_mul_a_xy = _mm_mul_ps(b_yx, a.V);

        __m128 const bx_mul_ay               = _mm_permute_ps(b_yx_mul_a_xy, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const by_mul_ax_sub_bx_mul_ay = _mm_sub_ss(b_yx_mul_a_xy, bx_mul_ay);

        __m128 const result = _mm_permute_ps(by_mul_ax_sub_bx_mul_ay, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector2 mathcall Orthogonal(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            -v.V.F[1],
            v.V.F[0],
            0.0F,
            0.0F,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const partial = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const result  = _mm_mul_ps(partial, Impl::VEC4_NEGATE_X.V);
        return { result };
#endif
    }

    mathinline Vector2 mathcall Transform(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0   = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1   = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return Vector2{ r1.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const y  = vmlaq_lane_f32(m.M.R[3], m.M.R[1], xy, 1);
        float32x4_t const x  = vmlaq_lane_f32(y, m.M.R[0], xy, 0);
        return { x };
#endif
    }

    mathinline Vector2 mathcall TransformCoord(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0   = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1   = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        Vector4 const wwww = SplatW(r1);
        Vector4 const r2   = Divide(r1, wwww);
        return Vector2{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        __m128 const wwww = _mm_permute_ps(r1, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r2   = _mm_div_ps(r1, wwww);
        return { r2 };
#endif
    }

    mathinline Vector2 mathcall TransformNormal(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0   = Multiply(yyyy, { m.M.R[1] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1   = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return Vector2{ r1.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0   = _mm_mul_ps(yyyy, m.M.R[1]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#endif
    }
}

// =================================================================================================
//
// Create rotation from axis/angle or normal/angle / euler angles
//

namespace Graphyte::Maths
{
    template <typename T>
    T CreateFromAxisAngle(Vector3 axis, float angle) noexcept = delete;

    template <typename T>
    T CreateFromNormalAngle(Vector3 normal, float angle) noexcept = delete;

    template <typename T>
    T CreateFromEuler(Vector3 angles) noexcept = delete;

    template <typename T>
    T CreateFromEuler(float x, float y, float z) noexcept = delete;
}


// =================================================================================================
//
// Quaternion operations
//

namespace Graphyte::Maths
{
    template <>
    mathinline Quaternion mathcall Identity<Quaternion>() noexcept
    {
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }

    mathinline bool mathcall IsIdentity(Quaternion v) noexcept
    {
        return IsEqual(Vector4{ v.V }, Vector4{ Impl::VEC4_POSITIVE_UNIT_W.V });
    }


    mathinline bool mathcall IsIdentity(Quaternion v, Vector4 epsilon) noexcept
    {
        return IsEqual(Vector4{ v.V }, Vector4{ Impl::VEC4_POSITIVE_UNIT_W.V }, epsilon);
    }

    mathinline Quaternion mathcall Conjugate(Quaternion q) noexcept
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

    mathinline Quaternion Inverse(Quaternion q) noexcept
    {
        Vector4 const zero            = Zero<Vector4>();
        Vector4 const length          = Length(q);
        Quaternion const conj         = Conjugate(q);
        Bool4 const control           = CompareLessEqual(length, Epsilon<Vector4>());
        Vector4 const normalized_conj = Divide(Vector4{ conj.V }, length);
        Vector4 const result          = Select(normalized_conj, zero, control);
        return Quaternion{ result.V };
    }

    mathinline Quaternion mathcall Multiply(Quaternion q1, Quaternion q2) noexcept
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

    [[deprecated("Not supported on quaternion. Multiply by inverse.")]] mathinline Quaternion mathcall Divide(Quaternion q) noexcept = delete;

    mathinline Quaternion mathcall Multiply(Quaternion q, Vector4 v) noexcept
    {
        return Quaternion{ Multiply(Vector4{ q.V }, v).V };
    }

    mathinline Quaternion mathcall Divide(Quaternion q, Vector4 v) noexcept
    {
        return Quaternion{ Divide(Vector4{ q.V }, v).V };
    }

    mathinline Quaternion mathcall Exp(Quaternion q) noexcept
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
        Vector4 const r1     = Select(coslen, r0, Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
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
        __m128 const r0 = _mm_and_ps(r_xyzw, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const r1 = _mm_andnot_ps(Impl::VEC4_MASK_SELECT_1110.V, coslen);
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


    mathinline Quaternion mathcall Log(Quaternion q) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const qv{ q.V };
        Vector3 const q_xyz{ qv.V };
        Vector4 const v_len_sq = Dot(q_xyz, q_xyz);

        Vector4 const q_w      = SplatW(Vector4{ q.V });
        Vector4 const q_len_sq = MultiplyAdd(q_w, q_w, v_len_sq);

        Vector4 const s       = Multiply(Acos(Clamp(Multiply(q_w, InvSqrt(q_len_sq)), Vector4{ Impl::VEC4_NEGATIVE_ONE_4.V }, Vector4{ Impl::VEC4_ONE_4.V })), InvSqrt(v_len_sq));
        Vector4 const q_xyz_s = Multiply(qv, s);
        Vector4 const w       = Multiply(Log(q_len_sq), 0.5F);

        Quaternion r0{ Select(w, Vector4{ q_xyz_s.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V }).V };
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

        __m128 const r0 = _mm_and_ps(q_xyz_s, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const r1 = _mm_andnot_ps(Impl::VEC4_MASK_SELECT_1110.V, w);
        __m128 const r2 = _mm_or_ps(r0, r1);
        return { r2 };
#endif
    }

    template <>
    mathinline Quaternion mathcall CreateFromEuler<Quaternion>(Vector3 angles) noexcept
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
        Vector4 const q   = MultiplyAdd(qa1, sscs_zzzz, qb1);
        return Quaternion{ q.V };
    }

    template <>
    mathinline Quaternion mathcall CreateFromEuler<Quaternion>(float x, float y, float z) noexcept
    {
        Vector3 const angles    = Make<Vector3>(x, y, z);
        Quaternion const result = CreateFromEuler<Quaternion>(angles);
        return result;
    }

    template <>
    mathinline Quaternion mathcall CreateFromNormalAngle<Quaternion>(Vector3 normal, float angle) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 qv = Select(Vector4{ Impl::VEC4_ONE_4.V }, Vector4{ normal.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V });

        float fsin;
        float fcos;
        SinCos(fsin, fcos, 0.5F * angle);

        Vector4 const scale  = Make<Vector4>(fsin, fsin, fsin, fcos);
        Vector4 const result = Multiply(qv, scale);
        return Quaternion{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const normal_xyz  = _mm_and_ps(normal.V, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const normal_xyz1 = _mm_or_ps(normal_xyz, Impl::VEC4_POSITIVE_UNIT_W.V);
        __m128 const scale       = _mm_set_ps1(0.5F * angle);

        Vector4 vsin;
        Vector4 vcos;
        SinCos(vsin, vcos, Vector4{ scale });

        __m128 const sin_xyzn = _mm_and_ps(vsin.V, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const cos_nnnw = _mm_and_ps(vcos.V, Impl::VEC4_MASK_COMPONENT_W.V);

        __m128 const sincos_xyzw = _mm_or_ps(sin_xyzn, cos_nnnw);
        __m128 const result      = _mm_mul_ps(normal_xyz1, sincos_xyzw);
        return { result };
#endif
    }

    mathinline Quaternion mathcall CreateFromMatrix(Matrix m) noexcept
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
        __m128 const x2y2z2w2_2 = _mm_add_ps(x2y2z2w2_1, Impl::VEC4_ONE_4.V);

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

    template <>
    mathinline Quaternion mathcall CreateFromAxisAngle<Quaternion>(Vector3 axis, float angle) noexcept
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
        angle = 2.0F * Acos(GetW(q));
    }

    mathinline Vector3 Rotate(Vector3 v, Quaternion q) noexcept
    {
        Quaternion const a{ Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ v.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V })
                                .V };

        Quaternion const qn   = Conjugate(q);
        Quaternion const qa   = Multiply(q, a);
        Quaternion const qaqn = Multiply(qa, qn);
        return Vector3{ qaqn.V };
    }

    mathinline Vector3 InverseRotate(Vector3 v, Quaternion q) noexcept
    {
        Quaternion const a{ Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ v.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V })
                                .V };

        Quaternion const qn   = Conjugate(q);
        Quaternion const qna  = Multiply(qn, a);
        Quaternion const qnaq = Multiply(qna, q);
        return Vector3{ qnaq.V };
    }
}


// =================================================================================================
//
// Matrix operations
//

namespace Graphyte::Maths
{
    mathinline Matrix mathcall Make(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;
        result.M.M[0][0] = m00;
        result.M.M[0][1] = m01;
        result.M.M[0][2] = m02;
        result.M.M[0][3] = m03;

        result.M.M[1][0] = m10;
        result.M.M[1][1] = m11;
        result.M.M[1][2] = m12;
        result.M.M[1][3] = m13;

        result.M.M[2][0] = m20;
        result.M.M[2][1] = m21;
        result.M.M[2][2] = m22;
        result.M.M[2][3] = m23;

        result.M.M[3][0] = m30;
        result.M.M[3][1] = m31;
        result.M.M[3][2] = m32;
        result.M.M[3][3] = m33;

        return result;
#elif GRAPHYTE_HW_AVX
        Matrix result;
        result.M.R[0] = _mm_set_ps(m03, m02, m01, m00);
        result.M.R[1] = _mm_set_ps(m13, m12, m11, m10);
        result.M.R[2] = _mm_set_ps(m23, m22, m21, m20);
        result.M.R[3] = _mm_set_ps(m33, m32, m31, m30);
        return result;
#endif
    }

    template <>
    mathinline Matrix mathcall Load<Matrix, Float4x4A>(Float4x4A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.R[0].F[0] = source->M[0][0];
        result.M.R[0].F[1] = source->M[0][1];
        result.M.R[0].F[2] = source->M[0][2];
        result.M.R[0].F[3] = source->M[0][3];

        result.M.R[1].F[0] = source->M[1][0];
        result.M.R[1].F[1] = source->M[1][1];
        result.M.R[1].F[2] = source->M[1][2];
        result.M.R[1].F[3] = source->M[1][3];

        result.M.R[2].F[0] = source->M[2][0];
        result.M.R[2].F[1] = source->M[2][1];
        result.M.R[2].F[2] = source->M[2][2];
        result.M.R[2].F[3] = source->M[2][3];

        result.M.R[3].F[0] = source->M[3][0];
        result.M.R[3].F[1] = source->M[3][1];
        result.M.R[3].F[2] = source->M[3][2];
        result.M.R[3].F[3] = source->M[3][3];

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;

        result.M.R[0] = _mm_load_ps(&source->M11);
        result.M.R[1] = _mm_load_ps(&source->M21);
        result.M.R[2] = _mm_load_ps(&source->M31);
        result.M.R[3] = _mm_load_ps(&source->M41);

        return result;

#endif
    }

    template <>
    mathinline void mathcall Store<Float4x4A, Matrix>(Float4x4A* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];
        destination->M[0][3] = m.M.R[0].F[3];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];
        destination->M[1][3] = m.M.R[1].F[3];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[2].F[3];

        destination->M[3][0] = m.M.R[3].F[0];
        destination->M[3][1] = m.M.R[3].F[1];
        destination->M[3][2] = m.M.R[3].F[2];
        destination->M[3][3] = m.M.R[3].F[3];

#elif GRAPHYTE_HW_AVX

        _mm_store_ps(&destination->M11, m.M.R[0]);
        _mm_store_ps(&destination->M21, m.M.R[1]);
        _mm_store_ps(&destination->M31, m.M.R[2]);
        _mm_store_ps(&destination->M41, m.M.R[3]);

#endif
    }

    template <>
    mathinline Matrix mathcall Load<Matrix, Float4x3A>(Float4x3A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[3][0];
        result.M.M[3][1] = source->M[3][1];
        result.M.M[3][2] = source->M[3][2];
        result.M.M[3][3] = 1.0f;

        return result;
#elif GRAPHYTE_HW_AVX
        // = [r0.xyz, r1.x]
        __m128 const r0 = _mm_load_ps(&source->M[0][0]);
        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_load_ps(&source->M[1][1]);
        // = [r2.z, r3.xyz]
        __m128 const t2 = _mm_load_ps(&source->M[2][2]);

        // = [r2.xyzz]
        __m128 const r2 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(0, 0, 3, 2));
        // = [r1.yzxx]
        __m128 const t1 = _mm_shuffle_ps(t0, r0, _MM_SHUFFLE(3, 3, 1, 0));
        // = [r1.xyzz]
        __m128 const r1 = _mm_permute_ps(t1, _MM_SHUFFLE(1, 1, 0, 2));

        // = [r0.xyz, 0]
        __m128 const m0 = _mm_and_ps(r0, Impl::VEC4_MASK_COMPONENTS_3.V);
        // = [r1.xyz, 0]
        __m128 const m1 = _mm_and_ps(r1, Impl::VEC4_MASK_COMPONENTS_3.V);
        // = [r2.xyz, 0]
        __m128 const m2 = _mm_and_ps(r2, Impl::VEC4_MASK_COMPONENTS_3.V);

        // = [r2.z, r3.xyz] >> 4 bytes = [r3.xyz]
        __m128i const t3 = _mm_srli_si128(_mm_castps_si128(t2), 32 / 8);
        // = [r3.xyz, 1]
        __m128 const m3 = _mm_castsi128_ps(_mm_or_si128(t3, _mm_castps_si128(Impl::VEC4_POSITIVE_UNIT_W.V)));

        Matrix result;
        result.M.R[0] = m0;
        result.M.R[1] = m1;
        result.M.R[2] = m2;
        result.M.R[3] = m3;
        return result;
#endif
    }

    template <>
    mathinline void mathcall Store<Float4x3A, Matrix>(Float4x3A* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];

        destination->M[3][0] = m.M.M[3][0];
        destination->M[3][1] = m.M.M[3][1];
        destination->M[3][2] = m.M.M[3][2];
#elif GRAPHYTE_HW_AVX
        // = [r0.xyzw]
        __m128 const r0 = m.M.R[0];
        // = [r1.xyzw]
        __m128 const r1 = m.M.R[1];
        // = [r2.xyzw]
        __m128 const r2 = m.M.R[2];
        // = [r3.xyzw]
        __m128 const r3 = m.M.R[3];

        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 2, 1));
        // = [r1.xx, r0.zz]
        __m128 const t1 = _mm_shuffle_ps(r1, r0, _MM_SHUFFLE(2, 2, 0, 0));
        // = [r0.xyz, r1.x]
        __m128 const t2 = _mm_shuffle_ps(r0, t1, _MM_SHUFFLE(0, 2, 1, 0));
        // = [r2.zz, r3.xx]
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(0, 0, 2, 2));
        // = [r2.z, r3.xyz]
        __m128 const t4 = _mm_shuffle_ps(t3, r3, _MM_SHUFFLE(2, 1, 2, 0));

        // = [r0.xyz, r1.x]
        _mm_store_ps(&destination->M[0][0], t2);
        // = [r1.yz, r2.xy]
        _mm_store_ps(&destination->M[1][1], t0);
        // = [r2.z, r3.xyz]
        _mm_store_ps(&destination->M[2][2], t4);
#endif
    }

    /// \note   Float3x4 is stored as transposed Float4x3
    template <>
    mathinline Matrix mathcall Load<Matrix, Float3x4A>(Float3x4A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[1][0];
        result.M.M[0][2] = source->M[2][0];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[0][1];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[2][1];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[0][2];
        result.M.M[2][1] = source->M[1][2];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[0][3];
        result.M.M[3][1] = source->M[1][3];
        result.M.M[3][2] = source->M[2][3];
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        // = []
        __m128 const r0 = _mm_load_ps(&source->M[0][0]);
        __m128 const r1 = _mm_load_ps(&source->M[1][0]);
        __m128 const r2 = _mm_load_ps(&source->M[2][0]);
        __m128 const r3 = Impl::VEC4_POSITIVE_UNIT_W.V;

        __m128 const t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t2 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t1 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(3, 2, 3, 2));

        Matrix result;
        result.M.R[0] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[1] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(3, 1, 3, 1));
        result.M.R[2] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[3] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 1, 3, 1));
        return result;
#endif
    }

    template <>
    mathinline void mathcall Store<Float3x4A, Matrix>(Float3x4A* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[1].F[0];
        destination->M[0][2] = m.M.R[2].F[0];
        destination->M[0][3] = m.M.R[3].F[0];

        destination->M[1][0] = m.M.R[0].F[1];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[2].F[1];
        destination->M[1][3] = m.M.R[3].F[1];

        destination->M[2][0] = m.M.R[0].F[2];
        destination->M[2][1] = m.M.R[1].F[2];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        // load & transpose
        __m128 const t1 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t2 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t4 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const r0 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const r2 = _mm_shuffle_ps(t3, t4, _MM_SHUFFLE(2, 0, 2, 0));

        _mm_store_ps(&destination->M[0][0], r0);
        _mm_store_ps(&destination->M[1][0], r1);
        _mm_store_ps(&destination->M[2][0], r2);
#endif
    }

    template <>
    mathinline Matrix mathcall Load<Matrix, Float4x4>(Float4x4 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = source->M[0][3];

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = source->M[1][3];

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = source->M[2][3];

        result.M.M[3][0] = source->M[3][0];
        result.M.M[3][1] = source->M[3][1];
        result.M.M[3][2] = source->M[3][2];
        result.M.M[3][3] = source->M[3][3];

        return result;
#elif GRAPHYTE_HW_AVX
        Matrix result;

        result.M.R[0] = _mm_loadu_ps(&source->M[0][0]);
        result.M.R[1] = _mm_loadu_ps(&source->M[1][0]);
        result.M.R[2] = _mm_loadu_ps(&source->M[2][0]);
        result.M.R[3] = _mm_loadu_ps(&source->M[3][0]);

        return result;
#endif
    }

    template <>
    mathinline void mathcall Store<Float4x4, Matrix>(Float4x4* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];
        destination->M[0][3] = m.M.M[0][3];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];
        destination->M[1][3] = m.M.M[1][3];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];
        destination->M[2][3] = m.M.M[2][3];

        destination->M[3][0] = m.M.M[3][0];
        destination->M[3][1] = m.M.M[3][1];
        destination->M[3][2] = m.M.M[3][2];
        destination->M[3][3] = m.M.M[3][3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(&destination->M[0][0], m.M.R[0]);
        _mm_storeu_ps(&destination->M[1][0], m.M.R[1]);
        _mm_storeu_ps(&destination->M[2][0], m.M.R[2]);
        _mm_storeu_ps(&destination->M[3][0], m.M.R[3]);
#endif
    }

    template <>
    mathinline Matrix mathcall Load<Matrix, Float4x3>(Float4x3 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[3][0];
        result.M.M[3][1] = source->M[3][1];
        result.M.M[3][2] = source->M[3][2];
        result.M.M[3][3] = 1.0f;

        return result;
#elif GRAPHYTE_HW_AVX
        // = [r0.xyz, r1.x]
        __m128 const r0 = _mm_loadu_ps(&source->M[0][0]);
        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_loadu_ps(&source->M[1][1]);
        // = [r2.z, r3.xyz]
        __m128 const t2 = _mm_loadu_ps(&source->M[2][2]);

        // = [r2.xyzz]
        __m128 const r2 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(0, 0, 3, 2));
        // = [r1.yzxx]
        __m128 const t1 = _mm_shuffle_ps(t0, r0, _MM_SHUFFLE(3, 3, 1, 0));
        // = [r1.xyzz]
        __m128 const r1 = _mm_permute_ps(t1, _MM_SHUFFLE(1, 1, 0, 2));

        // = [r0.xyz, 0]
        __m128 const m0 = _mm_and_ps(r0, Impl::VEC4_MASK_COMPONENTS_3.V);
        // = [r1.xyz, 0]
        __m128 const m1 = _mm_and_ps(r1, Impl::VEC4_MASK_COMPONENTS_3.V);
        // = [r2.xyz, 0]
        __m128 const m2 = _mm_and_ps(r2, Impl::VEC4_MASK_COMPONENTS_3.V);

        // = [r2.z, r3.xyz] >> 4 bytes = [r3.xyz]
        __m128i const t3 = _mm_srli_si128(_mm_castps_si128(t2), 32 / 8);
        // = [r3.xyz, 1]
        __m128 const m3 = _mm_castsi128_ps(_mm_or_si128(t3, _mm_castps_si128(Impl::VEC4_POSITIVE_UNIT_W.V)));

        Matrix result;
        result.M.R[0] = m0;
        result.M.R[1] = m1;
        result.M.R[2] = m2;
        result.M.R[3] = m3;
        return result;
#endif
    }

    template <>
    mathinline void mathcall Store<Float4x3, Matrix>(Float4x3* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];

        destination->M[3][0] = m.M.M[3][0];
        destination->M[3][1] = m.M.M[3][1];
        destination->M[3][2] = m.M.M[3][2];
#elif GRAPHYTE_HW_AVX
        // = [r0.xyzw]
        __m128 const r0 = m.M.R[0];
        // = [r1.xyzw]
        __m128 const r1 = m.M.R[1];
        // = [r2.xyzw]
        __m128 const r2 = m.M.R[2];
        // = [r3.xyzw]
        __m128 const r3 = m.M.R[3];

        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 2, 1));
        // = [r1.xx, r0.zz]
        __m128 const t1 = _mm_shuffle_ps(r1, r0, _MM_SHUFFLE(2, 2, 0, 0));
        // = [r0.xyz, r1.x]
        __m128 const t2 = _mm_shuffle_ps(r0, t1, _MM_SHUFFLE(0, 2, 1, 0));
        // = [r2.zz, r3.xx]
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(0, 0, 2, 2));
        // = [r2.z, r3.xyz]
        __m128 const t4 = _mm_shuffle_ps(t3, r3, _MM_SHUFFLE(2, 1, 2, 0));

        // = [r0.xyz, r1.x]
        _mm_storeu_ps(&destination->M[0][0], t2);
        // = [r1.yz, r2.xy]
        _mm_storeu_ps(&destination->M[1][1], t0);
        // = [r2.z, r3.xyz]
        _mm_storeu_ps(&destination->M[2][2], t4);
#endif
    }

    /// \note   Float3x4 is stored as transposed Float4x3
    template <>
    mathinline Matrix mathcall Load<Matrix, Float3x4>(Float3x4 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[1][0];
        result.M.M[0][2] = source->M[2][0];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[0][1];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[2][1];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[0][2];
        result.M.M[2][1] = source->M[1][2];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[0][3];
        result.M.M[3][1] = source->M[1][3];
        result.M.M[3][2] = source->M[2][3];
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        // = []
        __m128 const r0 = _mm_loadu_ps(&source->M[0][0]);
        __m128 const r1 = _mm_loadu_ps(&source->M[1][0]);
        __m128 const r2 = _mm_loadu_ps(&source->M[2][0]);
        __m128 const r3 = Impl::VEC4_POSITIVE_UNIT_W.V;

        __m128 const t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t2 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t1 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(3, 2, 3, 2));

        Matrix result;
        result.M.R[0] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[1] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(3, 1, 3, 1));
        result.M.R[2] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[3] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 1, 3, 1));
        return result;
#endif
    }

    template <>
    mathinline void mathcall Store<Float3x4, Matrix>(Float3x4* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[1].F[0];
        destination->M[0][2] = m.M.R[2].F[0];
        destination->M[0][3] = m.M.R[3].F[0];

        destination->M[1][0] = m.M.R[0].F[1];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[2].F[1];
        destination->M[1][3] = m.M.R[3].F[1];

        destination->M[2][0] = m.M.R[0].F[2];
        destination->M[2][1] = m.M.R[1].F[2];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        // load & transpose
        __m128 const t1 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t2 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t4 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const r0 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const r2 = _mm_shuffle_ps(t3, t4, _MM_SHUFFLE(2, 0, 2, 0));

        _mm_storeu_ps(&destination->M[0][0], r0);
        _mm_storeu_ps(&destination->M[1][0], r1);
        _mm_storeu_ps(&destination->M[2][0], r2);
#endif
    }

    template <>
    mathinline Matrix mathcall Load<Matrix, Float3x3>(Float3x3 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();

        __m128 const t0 = _mm_loadu_ps(&source->M[0][0]);
        __m128 const t1 = _mm_loadu_ps(&source->M[1][1]);
        __m128 const t2 = _mm_load_ss(&source->M[2][2]);

        __m128 const t3 = _mm_unpackhi_ps(t0, zero);
        __m128 const t4 = _mm_unpacklo_ps(t1, zero);
        __m128 const t5 = _mm_shuffle_ps(t2, t4, _MM_SHUFFLE(0, 1, 0, 0));
        __m128 const t6 = _mm_movehl_ps(t4, t5);
        __m128 const t7 = _mm_movehl_ps(zero, t3);

        Matrix result;
        result.M.R[0] = _mm_movelh_ps(t0, t3);
        result.M.R[1] = _mm_add_ps(t6, t7);
        result.M.R[2] = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(1, 0, 3, 2));
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    template <>
    mathinline void mathcall Store<Float3x3, Matrix>(Float3x3* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(0, 0, 2, 2));
        __m128 const m0 = _mm_shuffle_ps(r0, t0, _MM_SHUFFLE(2, 0, 1, 0));
        _mm_storeu_ps(&destination->M[0][0], m0);
        __m128 const m1 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 2, 1));
        _mm_storeu_ps(&destination->M[1][1], m1);
        __m128 const m2 = _mm_permute_ps(r2, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->M[2][2], m2);
#endif
    }

    mathinline Matrix mathcall OuterProduct(Vector4 c, Vector4 r) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(c, SplatX<Vector4>(r)).V;
        result.M.R[1] = Multiply(c, SplatY<Vector4>(r)).V;
        result.M.R[2] = Multiply(c, SplatZ<Vector4>(r)).V;
        result.M.R[3] = Multiply(c, SplatW<Vector4>(r)).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0]         = vmulq_f32(c.V, vdupq_lane_f32(vget_low_f32(r.V), 0));
        result.M.R[1]         = vmulq_f32(c.V, vdupq_lane_f32(vget_low_f32(r.V), 1));
        result.M.R[2]         = vmulq_f32(c.V, vdupq_lane_f32(vget_high_f32(r.V), 0));
        result.M.R[3]         = vmulq_f32(c.V, vdupq_lane_f32(vget_high_f32(r.V), 1));
#elif GRAPHYTE_HW_AVX
        result.M.R[0]     = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(0, 0, 0, 0)));
        result.M.R[1]     = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(1, 1, 1, 1)));
        result.M.R[2]     = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(2, 2, 2, 2)));
        result.M.R[3]     = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(3, 3, 3, 3)));
#endif
        return result;
    }

    mathinline Vector4 mathcall Diagonal(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            m.M.M[0][0],
            m.M.M[1][1],
            m.M.M[2][2],
            m.M.M[3][3],
        } } };
        return { result.V };

#elif GRAPHYTE_HW_NEON
        uint32x4_t const t0_x = vandq_u32(vreinterpretq_u32_f32(m.M.R[0]), vreinterpretq_u32_f32(Impl::VEC4_MASK_COMPONENT_X.V));
        uint32x4_t const t0_y = vandq_u32(vreinterpretq_u32_f32(m.M.R[1]), vreinterpretq_u32_f32(Impl::VEC4_MASK_COMPONENT_Y.V));
        uint32x4_t const t0_z = vandq_u32(vreinterpretq_u32_f32(m.M.R[2]), vreinterpretq_u32_f32(Impl::VEC4_MASK_COMPONENT_Z.V));
        uint32x4_t const t0_w = vandq_u32(vreinterpretq_u32_f32(m.M.R[3]), vreinterpretq_u32_f32(Impl::VEC4_MASK_COMPONENT_W.V));

        uint32x4_t const t1_xy = vorq_u32(t0_x, t0_y);
        uint32x4_t const t1_zw = vorq_u32(t0_z, t0_w);

        uint32x4_t const t2_xyzw = vorq_u32(t1_xy, t1_zw);

        return { vreinterpret_f32_u32(t2_xyzw) };

#elif GRAPHYTE_HW_AVX
        __m128 const t0_x = _mm_and_ps(m.M.R[0], Impl::VEC4_MASK_COMPONENT_X.V);
        __m128 const t0_y = _mm_and_ps(m.M.R[1], Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const t0_z = _mm_and_ps(m.M.R[2], Impl::VEC4_MASK_COMPONENT_Z.V);
        __m128 const t0_w = _mm_and_ps(m.M.R[3], Impl::VEC4_MASK_COMPONENT_W.V);

        __m128 const t1_xy = _mm_or_ps(t0_x, t0_y);
        __m128 const t1_zw = _mm_or_ps(t0_z, t0_w);

        __m128 const t2_xyzw = _mm_or_ps(t1_xy, t1_zw);
        return { t2_xyzw };
#endif
    }

    mathinline Vector4 mathcall Trace(Matrix m) noexcept
    {
        Vector4 const diagonal = Diagonal(m);
        return Hsum(diagonal);
    }

    mathinline Matrix mathcall Add(Matrix m1, Matrix m2) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Add(Vector4{ m1.M.R[0] }, Vector4{ m2.M.R[0] }).V;
        result.M.R[1] = Add(Vector4{ m1.M.R[1] }, Vector4{ m2.M.R[1] }).V;
        result.M.R[2] = Add(Vector4{ m1.M.R[2] }, Vector4{ m2.M.R[2] }).V;
        result.M.R[3] = Add(Vector4{ m1.M.R[3] }, Vector4{ m2.M.R[3] }).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0]        = vaddq_f32(m1.M.R[0], m2.M.R[0]);
        result.M.R[1]        = vaddq_f32(m1.M.R[1], m2.M.R[1]);
        result.M.R[2]        = vaddq_f32(m1.M.R[2], m2.M.R[2]);
        result.M.R[3]        = vaddq_f32(m1.M.R[3], m2.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0]   = _mm_add_ps(m1.M.R[0], m2.M.R[0]);
        result.M.R[1]   = _mm_add_ps(m1.M.R[1], m2.M.R[1]);
        result.M.R[2]   = _mm_add_ps(m1.M.R[2], m2.M.R[2]);
        result.M.R[3]   = _mm_add_ps(m1.M.R[3], m2.M.R[3]);
#endif
        return result;
    }

    mathinline Matrix mathcall Subtract(Matrix m1, Matrix m2) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Subtract(Vector4{ m1.M.R[0] }, Vector4{ m2.M.R[0] }).V;
        result.M.R[1] = Subtract(Vector4{ m1.M.R[1] }, Vector4{ m2.M.R[1] }).V;
        result.M.R[2] = Subtract(Vector4{ m1.M.R[2] }, Vector4{ m2.M.R[2] }).V;
        result.M.R[3] = Subtract(Vector4{ m1.M.R[3] }, Vector4{ m2.M.R[3] }).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0]        = vsubq_f32(m1.M.R[0], m2.M.R[0]);
        result.M.R[1]        = vsubq_f32(m1.M.R[1], m2.M.R[1]);
        result.M.R[2]        = vsubq_f32(m1.M.R[2], m2.M.R[2]);
        result.M.R[3]        = vsubq_f32(m1.M.R[3], m2.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0]   = _mm_sub_ps(m1.M.R[0], m2.M.R[0]);
        result.M.R[1]   = _mm_sub_ps(m1.M.R[1], m2.M.R[1]);
        result.M.R[2]   = _mm_sub_ps(m1.M.R[2], m2.M.R[2]);
        result.M.R[3]   = _mm_sub_ps(m1.M.R[3], m2.M.R[3]);
#endif
        return result;
    }

    mathinline Matrix mathcall Negate(Matrix m) noexcept
    {
        Matrix result;
        result.M.R[0] = Negate(Vector4{ m.M.R[0] }).V;
        result.M.R[1] = Negate(Vector4{ m.M.R[1] }).V;
        result.M.R[2] = Negate(Vector4{ m.M.R[2] }).V;
        result.M.R[3] = Negate(Vector4{ m.M.R[3] }).V;
        return result;
    }

    mathinline Matrix mathcall Multiply(float s, Matrix m) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(Vector4{ m.M.R[0] }, s).V;
        result.M.R[1] = Multiply(Vector4{ m.M.R[1] }, s).V;
        result.M.R[2] = Multiply(Vector4{ m.M.R[2] }, s).V;
        result.M.R[3] = Multiply(Vector4{ m.M.R[3] }, s).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0]        = vmulq_f32(m.M.R[0], sv);
        result.M.R[1]        = vmulq_f32(m.M.R[1], sv);
        result.M.R[2]        = vmulq_f32(m.M.R[2], sv);
        result.M.R[3]        = vmulq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0]   = _mm_mul_ps(m.M.R[0], sv);
        result.M.R[1]   = _mm_mul_ps(m.M.R[1], sv);
        result.M.R[2]   = _mm_mul_ps(m.M.R[2], sv);
        result.M.R[3]   = _mm_mul_ps(m.M.R[3], sv);
#endif
        return result;
    }

    mathinline Matrix mathcall Multiply(Matrix m, float s) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(Vector4{ m.M.R[0] }, s).V;
        result.M.R[1] = Multiply(Vector4{ m.M.R[1] }, s).V;
        result.M.R[2] = Multiply(Vector4{ m.M.R[2] }, s).V;
        result.M.R[3] = Multiply(Vector4{ m.M.R[3] }, s).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0]        = vmulq_f32(m.M.R[0], sv);
        result.M.R[1]        = vmulq_f32(m.M.R[1], sv);
        result.M.R[2]        = vmulq_f32(m.M.R[2], sv);
        result.M.R[3]        = vmulq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0]   = _mm_mul_ps(m.M.R[0], sv);
        result.M.R[1]   = _mm_mul_ps(m.M.R[1], sv);
        result.M.R[2]   = _mm_mul_ps(m.M.R[2], sv);
        result.M.R[3]   = _mm_mul_ps(m.M.R[3], sv);
#endif
        return result;
    }

    mathinline Matrix mathcall Divide(Matrix m, float s) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const sv = Replicate<Vector4>(s);
        result.M.R[0]    = Divide(Vector4{ m.M.R[0] }, sv).V;
        result.M.R[1]    = Divide(Vector4{ m.M.R[1] }, sv).V;
        result.M.R[2]    = Divide(Vector4{ m.M.R[2] }, sv).V;
        result.M.R[3]    = Divide(Vector4{ m.M.R[3] }, sv).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0]        = vdivq_f32(m.M.R[0], sv);
        result.M.R[1]        = vdivq_f32(m.M.R[1], sv);
        result.M.R[2]        = vdivq_f32(m.M.R[2], sv);
        result.M.R[3]        = vdivq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0]   = _mm_div_ps(m.M.R[0], sv);
        result.M.R[1]   = _mm_div_ps(m.M.R[1], sv);
        result.M.R[2]   = _mm_div_ps(m.M.R[2], sv);
        result.M.R[3]   = _mm_div_ps(m.M.R[3], sv);
#endif
        return result;
    }

    mathinline Matrix mathcall ComponentMultiply(Matrix a, Matrix b) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(Vector4{ a.M.R[0] }, Vector4{ b.M.R[0] }).V;
        result.M.R[1] = Multiply(Vector4{ a.M.R[1] }, Vector4{ b.M.R[1] }).V;
        result.M.R[2] = Multiply(Vector4{ a.M.R[2] }, Vector4{ b.M.R[2] }).V;
        result.M.R[3] = Multiply(Vector4{ a.M.R[3] }, Vector4{ b.M.R[3] }).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0]        = vmulq_f32(a.M.R[0], b.M.R[0]);
        result.M.R[1]        = vmulq_f32(a.M.R[1], b.M.R[1]);
        result.M.R[2]        = vmulq_f32(a.M.R[2], b.M.R[2]);
        result.M.R[3]        = vmulq_f32(a.M.R[3], b.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0]   = _mm_mul_ps(a.M.R[0], b.M.R[0]);
        result.M.R[1]   = _mm_mul_ps(a.M.R[1], b.M.R[1]);
        result.M.R[2]   = _mm_mul_ps(a.M.R[2], b.M.R[2]);
        result.M.R[3]   = _mm_mul_ps(a.M.R[3], b.M.R[3]);
#endif
        return result;
    }

    mathinline Matrix mathcall Multiply(Matrix a, Matrix b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        {
            float const x = a.M.M[0][0];
            float const y = a.M.M[0][1];
            float const z = a.M.M[0][2];
            float const w = a.M.M[0][3];

            result.M.M[0][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[0][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[0][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[0][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[1][0];
            float const y = a.M.M[1][1];
            float const z = a.M.M[1][2];
            float const w = a.M.M[1][3];

            result.M.M[1][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[1][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[1][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[1][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[2][0];
            float const y = a.M.M[2][1];
            float const z = a.M.M[2][2];
            float const w = a.M.M[2][3];

            result.M.M[2][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[2][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[2][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[2][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[3][0];
            float const y = a.M.M[3][1];
            float const z = a.M.M[3][2];
            float const w = a.M.M[3][3];

            result.M.M[3][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[3][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[3][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[3][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;

#if GRAPHYTE_HW_AVX2
        __m128 const m_r0 = a.M.R[0];
        __m128 const x_r0 = _mm_broadcastss_ps(m_r0);
        __m128 const y_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);
#endif

        __m128 const abx_r0 = _mm_mul_ps(x_r0, b.M.R[0]);
        __m128 const aby_r0 = Impl::avx_fmadd_f32x4(y_r0, b.M.R[1], abx_r0);
        __m128 const abz_r0 = Impl::avx_fmadd_f32x4(z_r0, b.M.R[2], aby_r0);
        __m128 const abw_r0 = Impl::avx_fmadd_f32x4(w_r0, b.M.R[3], abz_r0);


#if GRAPHYTE_HW_AVX2
        __m128 const m_r1 = a.M.R[1];
        __m128 const x_r1 = _mm_broadcastss_ps(m_r1);
        __m128 const y_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);
#endif

        __m128 const abx_r1 = _mm_mul_ps(x_r1, b.M.R[0]);
        __m128 const aby_r1 = Impl::avx_fmadd_f32x4(y_r1, b.M.R[1], abx_r1);
        __m128 const abz_r1 = Impl::avx_fmadd_f32x4(z_r1, b.M.R[2], aby_r1);
        __m128 const abw_r1 = Impl::avx_fmadd_f32x4(w_r1, b.M.R[3], abz_r1);


#if GRAPHYTE_HW_AVX2
        __m128 const m_r2 = a.M.R[2];
        __m128 const x_r2 = _mm_broadcastss_ps(m_r2);
        __m128 const y_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);
#endif

        __m128 const abx_r2 = _mm_mul_ps(x_r2, b.M.R[0]);
        __m128 const aby_r2 = Impl::avx_fmadd_f32x4(y_r2, b.M.R[1], abx_r2);
        __m128 const abz_r2 = Impl::avx_fmadd_f32x4(z_r2, b.M.R[2], aby_r2);
        __m128 const abw_r2 = Impl::avx_fmadd_f32x4(w_r2, b.M.R[3], abz_r2);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r3 = a.M.R[3];
        __m128 const x_r3 = _mm_broadcastss_ps(m_r3);
        __m128 const y_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);
#endif

        __m128 const abx_r3 = _mm_mul_ps(x_r3, b.M.R[0]);
        __m128 const aby_r3 = Impl::avx_fmadd_f32x4(y_r3, b.M.R[1], abx_r3);
        __m128 const abz_r3 = Impl::avx_fmadd_f32x4(z_r3, b.M.R[2], aby_r3);
        __m128 const abw_r3 = Impl::avx_fmadd_f32x4(w_r3, b.M.R[3], abz_r3);

        result.M.R[0] = abw_r0;
        result.M.R[1] = abw_r1;
        result.M.R[2] = abw_r2;
        result.M.R[3] = abw_r3;

        return result;

#elif GRAPHYTE_HW_NEON

        // rNc0 = (b.r0 * a.rN.xxxx)
        float32x4_t const r0c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[0], 0);
        float32x4_t const r1c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[1], 0);
        float32x4_t const r2c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[2], 0);
        float32x4_t const r3c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[3], 0);

        // rNc1 = (b.r1 * a.rN.yyyy) + rNc0
        float32x4_t const r0c1 = vmlaq_laneq_f32(r0c0, b.M.R[1], a.M.R[0], 1);
        float32x4_t const r1c1 = vmlaq_laneq_f32(r1c0, b.M.R[1], a.M.R[1], 1);
        float32x4_t const r2c1 = vmlaq_laneq_f32(r2c0, b.M.R[1], a.M.R[2], 1);
        float32x4_t const r3c1 = vmlaq_laneq_f32(r3c0, b.M.R[1], a.M.R[3], 1);

        // rNc2 = (b.r2 * a.rN.zzzz) + rNc1
        float32x4_t const r0c2 = vmlaq_laneq_f32(r0c1, b.M.R[2], a.M.R[0], 2);
        float32x4_t const r1c2 = vmlaq_laneq_f32(r1c1, b.M.R[2], a.M.R[1], 2);
        float32x4_t const r2c2 = vmlaq_laneq_f32(r2c1, b.M.R[2], a.M.R[2], 2);
        float32x4_t const r3c2 = vmlaq_laneq_f32(r3c1, b.M.R[2], a.M.R[3], 2);

        // rNc3 = (b.r3 * a.rN.wwww) + rNc2
        float32x4_t const r0c3 = vmlaq_laneq_f32(r0c2, b.M.R[3], a.M.R[0], 3);
        float32x4_t const r1c3 = vmlaq_laneq_f32(r1c2, b.M.R[3], a.M.R[1], 3);
        float32x4_t const r2c3 = vmlaq_laneq_f32(r2c2, b.M.R[3], a.M.R[2], 3);
        float32x4_t const r3c3 = vmlaq_laneq_f32(r3c2, b.M.R[3], a.M.R[3], 3);

        Matrix result;
        result.M.R[0] = r0c3;
        result.M.R[1] = r1c3;
        result.M.R[2] = r2c3;
        result.M.R[3] = r3c3;
        return result;

#endif
    }

    mathinline Matrix mathcall MultiplyTranspose(Matrix a, Matrix b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        {
            float const x = b.M.M[0][0];
            float const y = b.M.M[0][1];
            float const z = b.M.M[0][2];
            float const w = b.M.M[0][3];

            result.M.M[0][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[0][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[0][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[0][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[1][0];
            float const y = b.M.M[1][1];
            float const z = b.M.M[1][2];
            float const w = b.M.M[1][3];

            result.M.M[1][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[1][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[1][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[1][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[2][0];
            float const y = b.M.M[2][1];
            float const z = b.M.M[2][2];
            float const w = b.M.M[2][3];

            result.M.M[2][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[2][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[2][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[2][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[3][0];
            float const y = b.M.M[3][1];
            float const z = b.M.M[3][2];
            float const w = b.M.M[3][3];

            result.M.M[3][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[3][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[3][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[3][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        return result;

#elif GRAPHYTE_HW_AVX
        Matrix result;


#if GRAPHYTE_HW_AVX2
        __m128 const m_r0   = a.M.R[0];
        __m128 const x_r0   = _mm_broadcastss_ps(m_r0);
        __m128 const y_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);
#endif

        __m128 const abx_r0 = _mm_mul_ps(x_r0, b.M.R[0]);
        __m128 const aby_r0 = Impl::avx_fmadd_f32x4(y_r0, b.M.R[1], abx_r0);
        __m128 const abz_r0 = Impl::avx_fmadd_f32x4(z_r0, b.M.R[2], aby_r0);
        __m128 const abw_r0 = Impl::avx_fmadd_f32x4(w_r0, b.M.R[3], abz_r0);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r1 = a.M.R[1];
        __m128 const x_r1 = _mm_broadcastss_ps(m_r1);
        __m128 const y_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);
#endif

        __m128 const abx_r1 = _mm_mul_ps(x_r1, b.M.R[0]);
        __m128 const aby_r1 = Impl::avx_fmadd_f32x4(y_r1, b.M.R[1], abx_r1);
        __m128 const abz_r1 = Impl::avx_fmadd_f32x4(z_r1, b.M.R[2], aby_r1);
        __m128 const abw_r1 = Impl::avx_fmadd_f32x4(w_r1, b.M.R[3], abz_r1);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r2 = a.M.R[2];
        __m128 const x_r2 = _mm_broadcastss_ps(m_r2);
        __m128 const y_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);
#endif

        __m128 const abx_r2 = _mm_mul_ps(x_r2, b.M.R[0]);
        __m128 const aby_r2 = Impl::avx_fmadd_f32x4(y_r2, b.M.R[1], abx_r2);
        __m128 const abz_r2 = Impl::avx_fmadd_f32x4(z_r2, b.M.R[2], aby_r2);
        __m128 const abw_r2 = Impl::avx_fmadd_f32x4(w_r2, b.M.R[3], abz_r2);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r3 = a.M.R[3];
        __m128 const x_r3 = _mm_broadcastss_ps(m_r3);
        __m128 const y_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3         = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);
#endif

        __m128 const abx_r3 = _mm_mul_ps(x_r3, b.M.R[0]);
        __m128 const aby_r3 = Impl::avx_fmadd_f32x4(y_r3, b.M.R[1], abx_r3);
        __m128 const abz_r3 = Impl::avx_fmadd_f32x4(z_r3, b.M.R[2], aby_r3);
        __m128 const abw_r3 = Impl::avx_fmadd_f32x4(w_r3, b.M.R[3], abz_r3);

        __m128 const trn_r0 = _mm_shuffle_ps(abw_r0, abw_r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trn_r2 = _mm_shuffle_ps(abw_r0, abw_r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const trn_r1 = _mm_shuffle_ps(abw_r2, abw_r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trn_r3 = _mm_shuffle_ps(abw_r2, abw_r3, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const final_r0 = _mm_shuffle_ps(trn_r0, trn_r1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const final_r1 = _mm_shuffle_ps(trn_r0, trn_r1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const final_r2 = _mm_shuffle_ps(trn_r2, trn_r3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const final_r3 = _mm_shuffle_ps(trn_r2, trn_r3, _MM_SHUFFLE(3, 1, 3, 1));

        result.M.R[0] = final_r0;
        result.M.R[1] = final_r1;
        result.M.R[2] = final_r2;
        result.M.R[3] = final_r3;

        return result;
#endif
    }

    mathinline Matrix mathcall Transpose(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = m.M.M[0][0];
        result.M.M[0][1] = m.M.M[1][0];
        result.M.M[0][2] = m.M.M[2][0];
        result.M.M[0][3] = m.M.M[3][0];

        result.M.M[1][0] = m.M.M[0][1];
        result.M.M[1][1] = m.M.M[1][1];
        result.M.M[1][2] = m.M.M[2][1];
        result.M.M[1][3] = m.M.M[3][1];

        result.M.M[2][0] = m.M.M[0][2];
        result.M.M[2][1] = m.M.M[1][2];
        result.M.M[2][2] = m.M.M[2][2];
        result.M.M[2][3] = m.M.M[3][2];

        result.M.M[3][0] = m.M.M[0][3];
        result.M.M[3][1] = m.M.M[1][3];
        result.M.M[3][2] = m.M.M[2][3];
        result.M.M[3][3] = m.M.M[3][3];

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const trx_r0 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trx_r2 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const trx_r1 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trx_r3 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const res_r0 = _mm_shuffle_ps(trx_r0, trx_r1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const res_r1 = _mm_shuffle_ps(trx_r0, trx_r1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const res_r2 = _mm_shuffle_ps(trx_r2, trx_r3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const res_r3 = _mm_shuffle_ps(trx_r2, trx_r3, _MM_SHUFFLE(3, 1, 3, 1));

        Matrix result;
        result.M.R[0] = res_r0;
        result.M.R[1] = res_r1;
        result.M.R[2] = res_r2;
        result.M.R[3] = res_r3;
        return result;
#elif GRAPHYTE_HW_NEON
        float32x4x2_t const t0 = vzipq_f32(m.M.R[0], m.M.R[2]);
        float32x4x2_t const t1 = vzipq_f32(m.M.R[1], m.M.R[3]);
        float32x4x2_t const r0 = vzipq_f32(t0.val[0], t1.val[0]);
        float32x4x2_t const r1 = vzipq_f32(t0.val[1], t1.val[1]);

        Matrix result;
        result.M.R[0] = r0.val[0];
        result.M.R[1] = r0.val[1];
        result.M.R[2] = r1.val[0];
        result.M.R[3] = r1.val[1];
        return result;
#endif
    }

    mathinline Matrix mathcall Inverse(Matrix m, Vector4* determinant = nullptr) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix const mt = Transpose(m);

        Vector4 const ca0 = Swizzle<0, 0, 1, 1>({ mt.M.R[2] });
        Vector4 const ca1 = Swizzle<2, 3, 2, 3>({ mt.M.R[3] });
        Vector4 const cb0 = Swizzle<0, 0, 1, 1>({ mt.M.R[0] });
        Vector4 const cb1 = Swizzle<2, 3, 2, 3>({ mt.M.R[1] });
        Vector4 const cc0 = Permute<PERMUTE_0X, PERMUTE_0Z, PERMUTE_1X, PERMUTE_1Z>({ mt.M.R[2] }, { mt.M.R[0] });
        Vector4 const cc1 = Permute<PERMUTE_0Y, PERMUTE_0W, PERMUTE_1Y, PERMUTE_1W>({ mt.M.R[3] }, { mt.M.R[1] });

        Vector4 const ra0 = Multiply(ca0, ca1);
        Vector4 const rb0 = Multiply(cb0, cb1);
        Vector4 const rc0 = Multiply(cc0, cc1);

        Vector4 const da0 = Swizzle<2, 3, 2, 3>({ mt.M.R[2] });
        Vector4 const da1 = Swizzle<0, 0, 1, 1>({ mt.M.R[3] });
        Vector4 const db0 = Swizzle<2, 3, 2, 3>({ mt.M.R[0] });
        Vector4 const db1 = Swizzle<0, 0, 1, 1>({ mt.M.R[1] });
        Vector4 const dc0 = Permute<PERMUTE_0Y, PERMUTE_0W, PERMUTE_1Y, PERMUTE_1W>({ mt.M.R[2] }, { mt.M.R[0] });
        Vector4 const dc1 = Permute<PERMUTE_0X, PERMUTE_0Z, PERMUTE_1X, PERMUTE_1Z>({ mt.M.R[3] }, { mt.M.R[1] });

        Vector4 const ra1 = NegateMultiplyAdd(da0, da1, ra0);
        Vector4 const rb1 = NegateMultiplyAdd(db0, db1, rb0);
        Vector4 const rc1 = NegateMultiplyAdd(dc0, dc1, rc0);

        Vector4 const ea0 = Swizzle<1, 2, 0, 1>({ mt.M.R[1] });
        Vector4 const ea1 = Permute<PERMUTE_1Y, PERMUTE_0Y, PERMUTE_0W, PERMUTE_0X>(ra1, rc1);
        Vector4 const eb0 = Swizzle<2, 0, 1, 0>({ mt.M.R[0] });
        Vector4 const eb1 = Permute<PERMUTE_0W, PERMUTE_1Y, PERMUTE_0Y, PERMUTE_0Z>(ra1, rc1);
        Vector4 const ec0 = Swizzle<1, 2, 0, 1>({ mt.M.R[3] });
        Vector4 const ec1 = Permute<PERMUTE_1W, PERMUTE_0Y, PERMUTE_0W, PERMUTE_0X>(rb1, rc1);
        Vector4 const ed0 = Swizzle<2, 0, 1, 0>({ mt.M.R[2] });
        Vector4 const ed1 = Permute<PERMUTE_0W, PERMUTE_1W, PERMUTE_0Y, PERMUTE_0Z>(rb1, rc1);

        Vector4 const fa0 = Multiply(ea0, ea1);
        Vector4 const fb0 = Multiply(eb0, eb1);
        Vector4 const fc0 = Multiply(ec0, ec1);
        Vector4 const fd0 = Multiply(ed0, ed1);

        Vector4 const ga0 = Swizzle<2, 3, 1, 2>({ mt.M.R[1] });
        Vector4 const ga1 = Permute<PERMUTE_0W, PERMUTE_0X, PERMUTE_0Y, PERMUTE_1X>(ra1, rc1);
        Vector4 const gb0 = Swizzle<3, 2, 3, 1>({ mt.M.R[0] });
        Vector4 const gb1 = Permute<PERMUTE_0Z, PERMUTE_0Y, PERMUTE_1X, PERMUTE_0X>(ra1, rc1);
        Vector4 const gc0 = Swizzle<2, 3, 1, 2>({ mt.M.R[3] });
        Vector4 const gc1 = Permute<PERMUTE_0W, PERMUTE_0X, PERMUTE_0Y, PERMUTE_1Z>(rb1, rc1);
        Vector4 const gd0 = Swizzle<3, 2, 3, 1>({ mt.M.R[2] });
        Vector4 const gd1 = Permute<PERMUTE_0Z, PERMUTE_0Y, PERMUTE_1Z, PERMUTE_0X>(rb1, rc1);

        Vector4 const fa1 = NegateMultiplyAdd(ga0, ga1, fa0);
        Vector4 const fb1 = NegateMultiplyAdd(gb0, gb1, fb0);
        Vector4 const fc1 = NegateMultiplyAdd(gc0, gc1, fc0);
        Vector4 const fd1 = NegateMultiplyAdd(gd0, gd1, fd0);

        Vector4 const ha0 = Swizzle<3, 0, 3, 0>({ mt.M.R[1] });
        Vector4 const ha1 = Permute<PERMUTE_0Z, PERMUTE_1Y, PERMUTE_1X, PERMUTE_0Z>(ra1, rc1);
        Vector4 const hb0 = Swizzle<1, 3, 0, 2>({ mt.M.R[0] });
        Vector4 const hb1 = Permute<PERMUTE_1Y, PERMUTE_0X, PERMUTE_0W, PERMUTE_1X>(ra1, rc1);
        Vector4 const hc0 = Swizzle<3, 0, 3, 0>({ mt.M.R[3] });
        Vector4 const hc1 = Permute<PERMUTE_0Z, PERMUTE_1W, PERMUTE_1Z, PERMUTE_0Z>(rb1, rc1);
        Vector4 const hd0 = Swizzle<1, 3, 0, 2>({ mt.M.R[2] });
        Vector4 const hd1 = Permute<PERMUTE_1W, PERMUTE_0X, PERMUTE_0W, PERMUTE_1Z>(rb1, rc1);

        Vector4 const r1 = NegateMultiplyAdd(ha0, ha1, fa1);
        Vector4 const r0 = MultiplyAdd(ha0, ha1, fa1);
        Vector4 const r3 = MultiplyAdd(hb0, hb1, fb1);
        Vector4 const r2 = NegateMultiplyAdd(hb0, hb1, fb1);
        Vector4 const r5 = NegateMultiplyAdd(hc0, hc1, fc1);
        Vector4 const r4 = MultiplyAdd(hc0, hc1, fc1);
        Vector4 const r7 = MultiplyAdd(hd0, hd1, fd1);
        Vector4 const r6 = NegateMultiplyAdd(hd0, hd1, fd1);

        Matrix partial;
        partial.M.R[0] = Select(r0, r1, Bool4{ Impl::VEC4_MASK_SELECT_0101.V }).V;
        partial.M.R[1] = Select(r2, r3, Bool4{ Impl::VEC4_MASK_SELECT_0101.V }).V;
        partial.M.R[2] = Select(r4, r5, Bool4{ Impl::VEC4_MASK_SELECT_0101.V }).V;
        partial.M.R[3] = Select(r6, r7, Bool4{ Impl::VEC4_MASK_SELECT_0101.V }).V;

        Vector4 const det = Dot(Vector4{ partial.M.R[0] }, Vector4{ mt.M.R[0] });

        if (determinant != nullptr)
        {
            (*determinant) = det;
        }

        Vector4 const rcp_det = Reciprocal(det);

        Matrix result;
        result.M.R[0] = Multiply(Vector4{ partial.M.R[0] }, rcp_det).V;
        result.M.R[1] = Multiply(Vector4{ partial.M.R[1] }, rcp_det).V;
        result.M.R[2] = Multiply(Vector4{ partial.M.R[2] }, rcp_det).V;
        result.M.R[3] = Multiply(Vector4{ partial.M.R[3] }, rcp_det).V;

        return result;
#elif GRAPHYTE_HW_AVX

        Matrix mt = Transpose(m);

        __m128 const ca0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const ca1 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const cb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const cb1 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const cc0 = _mm_shuffle_ps(mt.M.R[2], mt.M.R[0], _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const cc1 = _mm_shuffle_ps(mt.M.R[3], mt.M.R[1], _MM_SHUFFLE(3, 1, 3, 1));

        __m128 const ra0 = _mm_mul_ps(ca0, ca1);
        __m128 const rb0 = _mm_mul_ps(cb0, cb1);
        __m128 const rc0 = _mm_mul_ps(cc0, cc1);

        __m128 const da0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const da1 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const db0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const db1 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const dc0 = _mm_shuffle_ps(mt.M.R[2], mt.M.R[0], _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const dc1 = _mm_shuffle_ps(mt.M.R[3], mt.M.R[1], _MM_SHUFFLE(2, 0, 2, 0));

        __m128 const ra1 = Impl::avx_fnmadd_f32x4(da0, da1, ra0);
        __m128 const rb1 = Impl::avx_fnmadd_f32x4(db0, db1, rb0);
        __m128 const rc1 = Impl::avx_fnmadd_f32x4(dc0, dc1, rc0);


        __m128 const tmp1 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 1, 3, 1));
        __m128 const tmp2 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 3, 3, 1));
        __m128 const ea0  = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const ea1  = _mm_shuffle_ps(tmp1, ra1, _MM_SHUFFLE(0, 3, 0, 2));
        __m128 const eb0  = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const eb1  = _mm_shuffle_ps(tmp1, ra1, _MM_SHUFFLE(2, 1, 2, 1));
        __m128 const ec0  = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const ec1  = _mm_shuffle_ps(tmp2, rb1, _MM_SHUFFLE(0, 3, 0, 2));
        __m128 const ed0  = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const ed1  = _mm_shuffle_ps(tmp2, rb1, _MM_SHUFFLE(2, 1, 2, 1));

        __m128 const fa0 = _mm_mul_ps(ea0, ea1);
        __m128 const fb0 = _mm_mul_ps(eb0, eb1);
        __m128 const fc0 = _mm_mul_ps(ec0, ec1);
        __m128 const fd0 = _mm_mul_ps(ed0, ed1);

        __m128 const tmp3 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(0, 0, 1, 0));
        __m128 const ga0  = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const ga1  = _mm_shuffle_ps(ra1, tmp3, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const gb0  = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const gb1  = _mm_shuffle_ps(ra1, tmp3, _MM_SHUFFLE(0, 2, 1, 2));

        __m128 const tmp4 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(2, 2, 1, 0));
        __m128 const gc0  = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const gc1  = _mm_shuffle_ps(rb1, tmp4, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const gd0  = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const gd1  = _mm_shuffle_ps(rb1, tmp4, _MM_SHUFFLE(0, 2, 1, 2));

        __m128 const fa1 = Impl::avx_fnmadd_f32x4(ga0, ga1, fa0);
        __m128 const fb1 = Impl::avx_fnmadd_f32x4(gb0, gb1, fb0);
        __m128 const fc1 = Impl::avx_fnmadd_f32x4(gc0, gc1, fc0);
        __m128 const fd1 = Impl::avx_fnmadd_f32x4(gd0, gd1, fd0);

        __m128 const ha0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(0, 3, 0, 3));

        __m128 const tmp5 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 0, 2, 2));
        __m128 const ha1  = _mm_permute_ps(tmp5, _MM_SHUFFLE(0, 2, 3, 0));
        __m128 const hb0  = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(2, 0, 3, 1));

        __m128 const tmp6 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 0, 3, 0));
        __m128 const hb1  = _mm_permute_ps(tmp6, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const hc0  = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(0, 3, 0, 3));

        __m128 const tmp7 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const hc1  = _mm_permute_ps(tmp7, _MM_SHUFFLE(0, 2, 3, 0));
        __m128 const hd0  = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(2, 0, 3, 1));

        __m128 const tmp8 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 2, 3, 0));
        __m128 const hd1  = _mm_permute_ps(tmp8, _MM_SHUFFLE(2, 1, 0, 3));

        __m128 const k0 = _mm_mul_ps(ha0, ha1);
        __m128 const k1 = _mm_mul_ps(hb0, hb1);
        __m128 const k2 = _mm_mul_ps(hc0, hc1);
        __m128 const k3 = _mm_mul_ps(hd0, hd1);

        __m128 const t1 = _mm_sub_ps(fa1, k0);
        __m128 const t0 = _mm_add_ps(fa1, k0);
        __m128 const t3 = _mm_add_ps(fb1, k1);
        __m128 const t2 = _mm_sub_ps(fb1, k1);
        __m128 const t5 = _mm_sub_ps(fc1, k2);
        __m128 const t4 = _mm_add_ps(fc1, k2);
        __m128 const t7 = _mm_add_ps(fd1, k3);
        __m128 const t6 = _mm_sub_ps(fd1, k3);

        __m128 const w0 = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const w2 = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const w4 = _mm_shuffle_ps(t4, t5, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const w6 = _mm_shuffle_ps(t6, t7, _MM_SHUFFLE(3, 1, 2, 0));

        __m128 const r0 = _mm_permute_ps(w0, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const r2 = _mm_permute_ps(w2, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const r4 = _mm_permute_ps(w4, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const r6 = _mm_permute_ps(w6, _MM_SHUFFLE(3, 1, 2, 0));

        // determinant
        __m128 const det = _mm_dp_ps(r0, mt.M.R[0], 0xFF);

        if (determinant != nullptr)
        {
            determinant->V = det;
        }

        __m128 const rcp_det = _mm_div_ps(Impl::VEC4_ONE_4.V, det);

        Matrix result;
        result.M.R[0] = _mm_mul_ps(r0, rcp_det);
        result.M.R[1] = _mm_mul_ps(r2, rcp_det);
        result.M.R[2] = _mm_mul_ps(r4, rcp_det);
        result.M.R[3] = _mm_mul_ps(r6, rcp_det);
        return result;
#endif
    }

    mathinline Vector4 mathcall Determinant(Matrix m) noexcept
    {
        static Impl::ConstFloat32x4 const sign{ { { 1.0f,
            -1.0f,
            1.0f,
            -1.0f } } };

        Vector4 const r2_yxxx = Swizzle<1, 0, 0, 0>(Vector4{ m.M.R[2] });
        Vector4 const r3_zzyy = Swizzle<2, 2, 1, 1>(Vector4{ m.M.R[3] });
        Vector4 const r3_wwwz = Swizzle<3, 3, 3, 2>(Vector4{ m.M.R[3] });
        Vector4 const r2_zzyy = Swizzle<2, 2, 1, 1>(Vector4{ m.M.R[2] });

        Vector4 const pa0 = Multiply(r2_yxxx, r3_zzyy);
        Vector4 const pa1 = Multiply(r2_yxxx, r3_wwwz);
        Vector4 const pa2 = Multiply(r2_zzyy, r3_wwwz);

        Vector4 const r3_yxxx = Swizzle<1, 0, 0, 0>(Vector4{ m.M.R[3] });
        Vector4 const r2_wwwz = Swizzle<3, 3, 3, 2>(Vector4{ m.M.R[2] });

        Vector4 const pb0 = NegateMultiplyAdd(r2_zzyy, r3_yxxx, pa0);
        Vector4 const pb1 = NegateMultiplyAdd(r2_wwwz, r3_yxxx, pa1);
        Vector4 const pb2 = NegateMultiplyAdd(r2_wwwz, r3_zzyy, pa2);

        Vector4 const r1_wwwz = Swizzle<3, 3, 3, 2>(Vector4{ m.M.R[1] });
        Vector4 const r1_zzyy = Swizzle<2, 2, 1, 1>(Vector4{ m.M.R[1] });
        Vector4 const r1_yxxx = Swizzle<1, 0, 0, 0>(Vector4{ m.M.R[1] });

        Vector4 const s0 = Multiply(Vector4{ m.M.R[0] }, Vector4{ sign.V });
        Vector4 const t0 = Multiply(r1_wwwz, pb0);
        Vector4 const t1 = NegateMultiplyAdd(r1_zzyy, pb1, t0);
        Vector4 const t2 = MultiplyAdd(r1_yxxx, pb2, t1);

        return Dot(s0, t2);
    }

    mathinline bool mathcall Decompose(
        Vector4& out_scale,
        Quaternion& out_rotation,
        Vector4& out_translation,
        Matrix m) noexcept
    {
        constexpr float const DecomposeEpsilon = 0.0001f;

        constexpr Impl::NativeFloat32x4 const* canonical_basis[3]{
            &Impl::VEC4_POSITIVE_UNIT_X.V,
            &Impl::VEC4_POSITIVE_UNIT_Y.V,
            &Impl::VEC4_POSITIVE_UNIT_Z.V,
        };

        out_translation.V = m.M.R[3];

        Matrix temp;
        temp.M.R[0] = m.M.R[0];
        temp.M.R[1] = m.M.R[1];
        temp.M.R[2] = m.M.R[2];
        temp.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        Impl::NativeFloat32x4* basis[3]{
            &temp.M.R[0],
            &temp.M.R[1],
            &temp.M.R[2],
        };

        float* scales = reinterpret_cast<float*>(&out_scale.V);
        GetX(&scales[0], Length(Vector3{ *basis[0] }));
        GetX(&scales[1], Length(Vector3{ *basis[1] }));
        GetX(&scales[2], Length(Vector3{ *basis[2] }));
        scales[3] = 0.0f;

        auto decompose_rank_abc = [](size_t& a, size_t& b, size_t& c, float x, float y, float z) {
            if (x < y)
            {
                if (y < z)
                {
                    a = 2;
                    b = 1;
                    c = 0;
                }
                else
                {
                    a = 1;

                    if (x < z)
                    {
                        b = 2;
                        c = 0;
                    }
                    else
                    {
                        b = 0;
                        c = 2;
                    }
                }
            }
            else
            {
                if (x < z)
                {
                    a = 2;
                    b = 0;
                    c = 1;
                }
                else
                {
                    a = 0;

                    if (y < z)
                    {
                        b = 2;
                        c = 1;
                    }
                    else
                    {
                        b = 1;
                        c = 2;
                    }
                }
            }
        };

        size_t a;
        size_t b;
        size_t c;

        decompose_rank_abc(a, b, c, scales[0], scales[1], scales[2]);

        if (scales[a] < DecomposeEpsilon)
        {
            (*basis[a]) = (*canonical_basis[a]);
        }

        (*basis[a]) = Normalize(Vector3{ *basis[a] }).V;

        if (scales[b] < DecomposeEpsilon)
        {
            float const absx = fabsf(GetX(Vector4{ *basis[a] }));
            float const absy = fabsf(GetY(Vector4{ *basis[a] }));
            float const absz = fabsf(GetZ(Vector4{ *basis[a] }));

            size_t const cc = [](float x, float y, float z) -> size_t {
                if (x < y)
                {
                    if ((y < z) || (x < z))
                    {
                        return 0;
                    }
                    else
                    {
                        return 2;
                    }
                }
                else
                {
                    if ((x < z) || (y < z))
                    {
                        return 1;
                    }
                    else
                    {
                        return 2;
                    }
                }
            }(absx, absy, absz);

            (*basis[b]) = Cross(Vector3{ *basis[a] }, Vector3{ *canonical_basis[cc] }).V;
        }

        (*basis[b]) = Normalize(Vector3{ *basis[b] }).V;

        if (scales[c] < DecomposeEpsilon)
        {
            (*basis[c]) = Cross(Vector3{ *basis[a] }, Vector3{ *basis[b] }).V;
        }

        (*basis[c]) = Normalize(Vector3{ *basis[c] }).V;

        float det = GetX(Determinant(temp));

        if (det < 0.0f)
        {
            scales[a]   = -scales[a];
            (*basis[a]) = Negate(Vector4{ *basis[a] }).V;
            det         = -det;
        }

        det -= 1.0f;
        det *= det;

        if (DecomposeEpsilon < det)
        {
            return false;
        }

        out_rotation = CreateFromMatrix(temp);
        return true;
    }

    template <>
    mathinline Matrix mathcall Nan<Matrix>() noexcept
    {
        Matrix result;
        result.M.R[0] = Impl::VEC4_QNAN.V;
        result.M.R[1] = Impl::VEC4_QNAN.V;
        result.M.R[2] = Impl::VEC4_QNAN.V;
        result.M.R[3] = Impl::VEC4_QNAN.V;
        return result;
    }


#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    mathinline bool mathcall IsNan(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        size_t count = 16u;

        uint32_t const* item = reinterpret_cast<uint32_t const*>(&m.M.F[0]);

        do
        {
            uint32_t const value = (*item);
            if (FloatTraits<float>::BitIsNan(value))
            {
                break;
            }

            ++item;
        } while (--count != 0);

        return count != 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const eq_r0 = _mm_cmpneq_ps(r0, r0);
        __m128 const eq_r1 = _mm_cmpneq_ps(r1, r1);
        __m128 const eq_r2 = _mm_cmpneq_ps(r2, r2);
        __m128 const eq_r3 = _mm_cmpneq_ps(r3, r3);

        __m128 const eq_r0r1 = _mm_or_ps(eq_r0, eq_r1);
        __m128 const eq_r2r3 = _mm_or_ps(eq_r2, eq_r3);

        __m128 const eq_r0r1r2r3 = _mm_or_ps(eq_r0r1, eq_r2r3);

        return _mm_movemask_ps(eq_r0r1r2r3) != 0;

#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    template <>
    mathinline Matrix mathcall Infinity<Matrix>() noexcept
    {
        Matrix result;

        result.M.R[0] = Impl::VEC4_INFINITY.V;
        result.M.R[1] = Impl::VEC4_INFINITY.V;
        result.M.R[2] = Impl::VEC4_INFINITY.V;
        result.M.R[3] = Impl::VEC4_INFINITY.V;

        return result;
    }

    mathinline bool mathcall IsInfinity(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        size_t count = 16;

        uint32_t const* item = reinterpret_cast<uint32_t const*>(&m.M.F[0]);

        do
        {
            uint32_t const value = (*item);

            if (FloatTraits<float>::BitIsInf(value))
            {
                break;
            }

            ++item;
        } while (--count != 0);

        return count != 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const abs = Impl::VEC4_MASK_ABS.V;

        __m128 const abs_r0 = _mm_and_ps(r0, abs);
        __m128 const abs_r1 = _mm_and_ps(r1, abs);
        __m128 const abs_r2 = _mm_and_ps(r2, abs);
        __m128 const abs_r3 = _mm_and_ps(r3, abs);

        __m128 const inf = Impl::VEC4_INFINITY.V;

        __m128 const inf_r0 = _mm_cmpeq_ps(abs_r0, inf);
        __m128 const inf_r1 = _mm_cmpeq_ps(abs_r1, inf);
        __m128 const inf_r2 = _mm_cmpeq_ps(abs_r2, inf);
        __m128 const inf_r3 = _mm_cmpeq_ps(abs_r3, inf);

        __m128 const inf_r0r1 = _mm_or_ps(inf_r0, inf_r1);
        __m128 const inf_r2r3 = _mm_or_ps(inf_r2, inf_r3);

        __m128 const inf_r0r1r2r3 = _mm_or_ps(inf_r0r1, inf_r2r3);

        return _mm_movemask_ps(inf_r0r1r2r3) != 0;

#endif
    }

    template <>
    mathinline Matrix mathcall Identity<Matrix>() noexcept
    {
        Matrix result;
        result.M.R[0] = Impl::VEC4_POSITIVE_UNIT_X.V;
        result.M.R[1] = Impl::VEC4_POSITIVE_UNIT_Y.V;
        result.M.R[2] = Impl::VEC4_POSITIVE_UNIT_Z.V;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;
        return result;
    }

    mathinline bool mathcall IsIdentity(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        uint32_t const* items = reinterpret_cast<uint32_t const*>(&m.M.M[0][0]);

        uint32_t one  = items[0] ^ 0x3f80'0000;
        uint32_t zero = items[1];
        zero |= items[2];
        zero |= items[3];

        zero |= items[4];
        one |= items[5];
        zero |= items[6];
        zero |= items[7];

        zero |= items[8];
        zero |= items[9];
        one |= items[10];
        zero |= items[11];

        zero |= items[12];
        zero |= items[13];
        zero |= items[14];
        one |= items[15] ^ 0x3f80'0000;

        // clear sign mask
        zero &= 0x7fff'ffff;
        one |= zero;

        return one == 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const m0 = _mm_cmpeq_ps(r0, Impl::VEC4_POSITIVE_UNIT_X.V);
        __m128 const m1 = _mm_cmpeq_ps(r1, Impl::VEC4_POSITIVE_UNIT_Y.V);
        __m128 const m2 = _mm_cmpeq_ps(r2, Impl::VEC4_POSITIVE_UNIT_Z.V);
        __m128 const m3 = _mm_cmpeq_ps(r3, Impl::VEC4_POSITIVE_UNIT_W.V);

        __m128 const m1_0 = _mm_and_ps(m0, m1);
        __m128 const m1_1 = _mm_and_ps(m2, m3);

        __m128 const m2_final = _mm_and_ps(m1_0, m1_1);

        return _mm_movemask_ps(m2_final) == 0b1111;
#endif
    }

    mathinline Vector4 mathcall GetBaseX(Matrix m) noexcept
    {
        return { m.M.R[0] };
    }

    mathinline Vector4 mathcall GetBaseY(Matrix m) noexcept
    {
        return { m.M.R[1] };
    }

    mathinline Vector4 mathcall GetBaseZ(Matrix m) noexcept
    {
        return { m.M.R[2] };
    }

    mathinline Vector4 mathcall GetBaseW(Matrix m) noexcept
    {
        return { m.M.R[3] };
    }

    template <>
    mathinline Matrix mathcall CreateFromNormalAngle<Matrix>(Vector3 normal, float angle) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        float sin_angle;
        float cos_angle;

        SinCos(sin_angle, cos_angle, angle);

        Vector4 const a = Make<Vector4>(sin_angle, cos_angle, 1.0f - cos_angle, 0.0f);

        Vector4 const c0 = SplatX(a);
        Vector4 const c1 = SplatY(a);
        Vector4 const c2 = SplatZ(a);

        Vector4 const n0 = Swizzle<1, 2, 0, 3>(Vector4{ normal.V });
        Vector4 const n1 = Swizzle<2, 0, 1, 3>(Vector4{ normal.V });

        Vector4 const g0 = Multiply(c2, n0);
        Vector4 const g1 = Multiply(g0, n1);

        Vector4 const h0 = Multiply(c2, Vector4{ normal.V });
        Vector4 const h1 = MultiplyAdd(h0, Vector4{ normal.V }, c1);

        Vector4 const i0 = MultiplyAdd(c0, Vector4{ normal.V }, g1);
        Vector4 const i1 = NegateMultiplyAdd(c0, Vector4{ normal.V }, g1);

        Vector4 const r0 = Select(a, h1, Bool4{ Impl::VEC4_MASK_SELECT_1110.V });

        Vector4 const r1 = Permute<2, 5, 6, 0>(i0, i1);
        Vector4 const r2 = Permute<1, 4, 1, 4>(i0, i1);

        Matrix result;
        result.M.R[0] = Permute<0, 4, 5, 3>(r0, r1).V;
        result.M.R[1] = Permute<6, 1, 7, 3>(r0, r1).V;
        result.M.R[2] = Permute<4, 5, 2, 3>(r0, r2).V;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;
        return result;
#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;

        SinCos(sin_angle, cos_angle, angle);

        __m128 const c0 = _mm_set_ps1(sin_angle);
        __m128 const c1 = _mm_set_ps1(cos_angle);
        __m128 const c2 = _mm_set_ps1(1.0f - cos_angle);

        __m128 const n0 = _mm_permute_ps(normal.V, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const n1 = _mm_permute_ps(normal.V, _MM_SHUFFLE(3, 1, 0, 2));

        __m128 const g0 = _mm_mul_ps(c2, n0);
        __m128 const g1 = _mm_mul_ps(g0, n1);

        __m128 const h0 = _mm_mul_ps(c2, normal.V);

        __m128 const i0 = Impl::avx_fmadd_f32x4(h0, normal.V, c1);
        __m128 const i1 = Impl::avx_fmadd_f32x4(c0, normal.V, g1);
        __m128 const i2 = Impl::avx_fnmadd_f32x4(c0, normal.V, g1);

        __m128 const r0 = _mm_and_ps(i0, Impl::VEC4_MASK_SELECT_1110.V);

        __m128 const t0 = _mm_shuffle_ps(i1, i2, _MM_SHUFFLE(2, 1, 2, 0));
        __m128 const r1 = _mm_permute_ps(t0, _MM_SHUFFLE(0, 3, 2, 1));

        __m128 const t1 = _mm_shuffle_ps(i1, i2, _MM_SHUFFLE(0, 0, 1, 1));
        __m128 const r2 = _mm_permute_ps(t1, _MM_SHUFFLE(2, 0, 2, 0));

        __m128 const t2 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 0, 3, 0));
        __m128 const r3 = _mm_permute_ps(t2, _MM_SHUFFLE(1, 3, 2, 0));

        Matrix result;
        result.M.R[0] = r3;

        __m128 const t3 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 2, 3, 1));
        __m128 const r4 = _mm_permute_ps(t3, _MM_SHUFFLE(1, 3, 0, 2));

        result.M.R[1] = r4;

        __m128 const r5 = _mm_shuffle_ps(r2, r0, _MM_SHUFFLE(3, 2, 1, 0));
        result.M.R[2]   = r5;
        result.M.R[3]   = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    template <>
    mathinline Matrix mathcall CreateFromAxisAngle<Matrix>(Vector3 axis, float angle) noexcept
    {
        GX_ASSERT(!IsEqual(axis, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(axis));

        Vector3 const normal = Normalize(axis);
        return CreateFromNormalAngle<Matrix>(normal, angle);
    }

    mathinline Matrix mathcall CreateFromQuaternion(Quaternion q) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const q_xyzw{ q.V };

        Vector4 const q0 = Add(q_xyzw, q_xyzw);
        Vector4 const q1 = Multiply(q_xyzw, q0);

        Vector4 const q1_yxx_1 = Permute<1, 0, 0, 7>(q1, Vector4{ Impl::VEC4_ONE_3.V });
        Vector4 const q1_zzy_1 = Permute<2, 2, 1, 7>(q1, Vector4{ Impl::VEC4_ONE_3.V });
        Vector4 const o0       = Subtract(Vector4{ Impl::VEC4_ONE_3.V }, q1_yxx_1);
        Vector4 const s0       = Subtract(o0, q1_zzy_1);

        Vector4 const q_xxyw  = Swizzle<0, 0, 1, 3>(q_xyzw);
        Vector4 const q0_zyzw = Swizzle<2, 1, 2, 3>(q0);
        Vector4 const m0      = Multiply(q_xxyw, q0_zyzw);

        Vector4 const q_wwww  = SplatW(q_xyzw);
        Vector4 const q0_yzxw = Swizzle<1, 2, 0, 3>(q0);
        Vector4 const m1      = Multiply(q_wwww, q0_yzxw);

        Vector4 const r0 = Add(m0, m1);
        Vector4 const r1 = Subtract(m0, m1);

        Vector4 const r2 = Permute<1, 4, 5, 2>(r0, r1);
        Vector4 const r3 = Permute<0, 6, 0, 6>(r0, r1);

        Matrix result;
        result.M.R[0] = Permute<0, 4, 5, 3>(s0, r2).V;
        result.M.R[1] = Permute<6, 1, 7, 3>(s0, r2).V;
        result.M.R[2] = Permute<4, 5, 2, 3>(s0, r3).V;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;
        return result;

#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const Constant1110 = { { { 1.0f, 1.0f, 1.0f, 0.0f } } };

        __m128 Q0 = _mm_add_ps(q.V, q.V);
        __m128 Q1 = _mm_mul_ps(q.V, Q0);

        __m128 V0 = _mm_permute_ps(Q1, _MM_SHUFFLE(3, 0, 0, 1));
        V0        = _mm_and_ps(V0, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 V1 = _mm_permute_ps(Q1, _MM_SHUFFLE(3, 1, 2, 2));
        V1        = _mm_and_ps(V1, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 R0 = _mm_sub_ps(Constant1110.V, V0);
        R0        = _mm_sub_ps(R0, V1);

        V0 = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 1, 0, 0));
        V1 = _mm_permute_ps(Q0, _MM_SHUFFLE(3, 2, 1, 2));
        V0 = _mm_mul_ps(V0, V1);

        V1        = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 V2 = _mm_permute_ps(Q0, _MM_SHUFFLE(3, 0, 2, 1));
        V1        = _mm_mul_ps(V1, V2);

        __m128 R1 = _mm_add_ps(V0, V1);
        __m128 R2 = _mm_sub_ps(V0, V1);

        V0 = _mm_shuffle_ps(R1, R2, _MM_SHUFFLE(1, 0, 2, 1));
        V0 = _mm_permute_ps(V0, _MM_SHUFFLE(1, 3, 2, 0));
        V1 = _mm_shuffle_ps(R1, R2, _MM_SHUFFLE(2, 2, 0, 0));
        V1 = _mm_permute_ps(V1, _MM_SHUFFLE(2, 0, 2, 0));

        Q1 = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(1, 0, 3, 0));
        Q1 = _mm_permute_ps(Q1, _MM_SHUFFLE(1, 3, 2, 0));

        Matrix m;
        m.M.R[0] = Q1;

        Q1       = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(3, 2, 3, 1));
        Q1       = _mm_permute_ps(Q1, _MM_SHUFFLE(1, 3, 0, 2));
        m.M.R[1] = Q1;

        Q1       = _mm_shuffle_ps(V1, R0, _MM_SHUFFLE(3, 2, 1, 0));
        m.M.R[2] = Q1;
        m.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;
        return m;
#endif
    }


    template <>
    mathinline Matrix mathcall CreateFromEuler<Matrix>(Vector3 angles) noexcept
    {
        Quaternion const q = CreateFromEuler<Quaternion>(angles);
        return CreateFromQuaternion(q);
    }

    template <>
    mathinline Matrix mathcall CreateFromEuler<Matrix>(float x, float y, float z) noexcept
    {
        Vector3 const v = Make<Vector3>(x, y, z);
        return CreateFromEuler<Matrix>(v);
    }


    //
    // Transforms
    //

    mathinline Matrix mathcall CreateTranslation(float x, float y, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = 1.0F;
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = 1.0F;
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = 1.0F;
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = x;
        result.M.M[3][1] = y;
        result.M.M[3][2] = z;
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;
        result.M.R[0] = Impl::VEC4_POSITIVE_UNIT_X.V;
        result.M.R[1] = Impl::VEC4_POSITIVE_UNIT_Y.V;
        result.M.R[2] = Impl::VEC4_POSITIVE_UNIT_Z.V;
        result.M.R[3] = _mm_set_ps(1.0F, z, y, x);

        return result;
#endif
    }

    mathinline Matrix mathcall CreateTranslation(Vector3 translation) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = 1.0F;
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = 1.0F;
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = 1.0F;
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = translation.V.F[0];
        result.M.M[3][1] = translation.V.F[1];
        result.M.M[3][2] = translation.V.F[2];
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON

        Matrix result;
        result.M.R[0] = Impl::VEC4_POSITIVE_UNIT_X.V;
        result.M.R[1] = Impl::VEC4_POSITIVE_UNIT_Y.V;
        result.M.R[2] = Impl::VEC4_POSITIVE_UNIT_Z.V;
        result.M.R[3] = Select(
            Vector4{ Impl::VEC4_POSITIVE_UNIT_W.V },
            Vector4{ translation.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V })
                            .V;

        return result;
#endif
    }

    mathinline Matrix mathcall CreateScaling(float x, float y, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = x;
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = y;
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = z;
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = 0.0F;
        result.M.M[3][1] = 0.0F;
        result.M.M[3][2] = 0.0F;
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;
        result.M.R[0] = _mm_set_ps(0.0F, 0.0F, 0.0F, x);
        result.M.R[1] = _mm_set_ps(0.0F, 0.0F, y, 0.0F);
        result.M.R[2] = _mm_set_ps(0.0F, z, 0.0F, 0.0F);
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    mathinline Matrix mathcall CreateScaling(Vector3 scale) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = scale.V.F[0];
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = scale.V.F[1];
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = scale.V.F[2];
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = 0.0F;
        result.M.M[3][1] = 0.0F;
        result.M.M[3][2] = 0.0F;
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;
        result.M.R[0] = _mm_and_ps(scale.V, Impl::VEC4_MASK_COMPONENT_X.V);
        result.M.R[1] = _mm_and_ps(scale.V, Impl::VEC4_MASK_COMPONENT_Y.V);
        result.M.R[2] = _mm_and_ps(scale.V, Impl::VEC4_MASK_COMPONENT_Z.V);
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    mathinline Matrix mathcall CreateRotationX(float angle) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        Matrix result;
        result.M.M[0][0] = 1.0f;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = cos_angle;
        result.M.M[1][2] = sin_angle;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = -sin_angle;
        result.M.M[2][2] = cos_angle;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        __m128 const ssin = _mm_set_ss(sin_angle);
        __m128 const scos = _mm_set_ss(cos_angle);

        __m128 const vcos = _mm_shuffle_ps(scos, ssin, _MM_SHUFFLE(3, 0, 0, 3));

        Matrix result;
        result.M.R[0] = Impl::VEC4_POSITIVE_UNIT_X.V;
        result.M.R[1] = vcos;

        __m128 const temp = _mm_permute_ps(vcos, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const vsin = _mm_mul_ps(temp, Impl::VEC4_NEGATE_Y.V);

        result.M.R[2] = vsin;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    mathinline Matrix mathcall CreateRotationY(float angle) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        Matrix result;
        result.M.M[0][0] = cos_angle;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = -sin_angle;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = 1.0f;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = sin_angle;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = cos_angle;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        __m128 const ssin = _mm_set_ss(sin_angle);
        __m128 const scos = _mm_set_ss(cos_angle);

        __m128 const vsin = _mm_shuffle_ps(ssin, scos, _MM_SHUFFLE(3, 0, 3, 0));

        Matrix result;
        result.M.R[2] = vsin;
        result.M.R[1] = Impl::VEC4_POSITIVE_UNIT_Y.V;

        __m128 const temp = _mm_permute_ps(vsin, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const vcos = _mm_mul_ps(temp, Impl::VEC4_NEGATE_Z.V);

        result.M.R[0] = vcos;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    mathinline Matrix mathcall CreateRotationZ(float angle) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        Matrix result;
        result.M.M[0][0] = cos_angle;
        result.M.M[0][1] = sin_angle;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = -sin_angle;
        result.M.M[1][1] = cos_angle;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = 1.0f;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        __m128 const ssin = _mm_set_ss(sin_angle);
        __m128 const scos = _mm_set_ss(cos_angle);

        __m128 const vcos = _mm_unpacklo_ps(scos, ssin);

        Matrix result;
        result.M.R[0] = vcos;

        __m128 const temp = _mm_permute_ps(vcos, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const vsin = _mm_mul_ps(temp, Impl::VEC4_NEGATE_X.V);

        result.M.R[1] = vsin;
        result.M.R[2] = Impl::VEC4_POSITIVE_UNIT_Z.V;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return result;
#endif
    }

    mathinline Matrix mathcall CreateTransform2D(
        Vector2 scaling_origin,
        float scaling_orientation,
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation) noexcept
    {
        Vector3 const v_scaling_origin{ Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1100.V },
            Vector4{ scaling_origin.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V })
                                            .V };

        // Create scanling origin transform
        Vector3 const v_scaling_origin_negated = Negate(v_scaling_origin);
        Matrix const m_scaling_origin          = CreateTranslation(v_scaling_origin_negated);

        // Create scaling orientation transform
        Matrix const m_scaling_orientation     = CreateRotationZ(scaling_orientation);
        Matrix const m_scaling_orientation_trn = Transpose(m_scaling_orientation);

        // Create scaling transform
        Vector3 const v_scaling_xy1{ Select(
            Vector4{ Impl::VEC4_ONE_4.V },
            Vector4{ scaling.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V })
                                         .V };

        Matrix const m_scaling = CreateScaling(v_scaling_xy1);

        // Create rotation origin
        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1100.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V });

        // Create rotation transform
        Matrix const m_rotation = CreateRotationZ(rotation);

        // Create translation vector
        Vector4 const v_translation = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1100.V },
            Vector4{ translation.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V });

        Matrix const m0 = Multiply(m_scaling_origin, m_scaling_orientation_trn);
        Matrix const m1 = Multiply(m0, m_scaling);

        Matrix m2 = Multiply(m1, m_scaling_orientation);
        m2.M.R[3] = Add(Vector4{ m2.M.R[3] }, Vector4{ v_scaling_origin.V }).V;
        m2.M.R[3] = Subtract(Vector4{ m2.M.R[3] }, v_rotation_origin).V;

        Matrix m3 = Multiply(m2, m_rotation);
        m3.M.R[3] = Add(Vector4{ m3.M.R[3] }, v_rotation_origin).V;
        m3.M.R[3] = Add(Vector4{ m3.M.R[3] }, v_translation).V;

        return m3;
    }

    mathinline Matrix mathcall CreateAffineTransform2D(
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation) noexcept
    {
        Vector3 const v_scaling{ Select(
            Vector4{ Impl::VEC4_ONE_4.V },
            Vector4{ scaling.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V })
                                     .V };

        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1100.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V });

        Vector4 const v_translation = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1100.V },
            Vector4{ translation.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1100.V });

        Matrix const m_rotation = CreateRotationZ(rotation);

        Matrix result = CreateScaling(v_scaling);
        result.M.R[3] = Subtract(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result        = Multiply(result, m_rotation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_translation).V;

        return result;
    }

    mathinline Matrix mathcall CreateTransform(
        Vector3 scaling_origin,
        Quaternion scaling_orientation,
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation) noexcept
    {
        Vector3 const v_scaling_origin{ Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ scaling_origin.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V })
                                            .V };

        Vector3 const v_scaling_origin_negated = Negate(v_scaling_origin);

        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V });

        Vector4 const v_translation = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ translation.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V });

        Matrix const m_scaling_origin          = CreateTranslation(v_scaling_origin_negated);
        Matrix const m_scaling_orientation     = CreateFromQuaternion(scaling_orientation);
        Matrix const m_scaling_orientation_trn = Transpose(m_scaling_orientation);
        Matrix const m_scaling                 = CreateScaling(scaling);
        Matrix const m_rotation                = CreateFromQuaternion(rotation);

        Matrix result = Multiply(m_scaling_origin, m_scaling_orientation_trn);
        result        = Multiply(result, m_scaling);
        result        = Multiply(result, m_scaling_orientation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, Vector4{ v_scaling_origin.V }).V;
        result.M.R[3] = Subtract(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result        = Multiply(result, m_rotation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_translation).V;

        return result;
    }

    mathinline Matrix mathcall CreateAffineTransform(
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation) noexcept
    {

        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V });

        Vector4 const v_translation = Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ translation.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V });

        Matrix const m_rotation = CreateFromQuaternion(rotation);

        Matrix result = CreateScaling(scaling);
        result.M.R[3] = Subtract(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result        = Multiply(result, m_rotation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_translation).V;

        return result;
    }

    //
    // View matrices.
    //

    mathinline Matrix mathcall LookToLH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
    {
        GX_ASSERT(!IsEqual(eye_direction, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(eye_direction));
        GX_ASSERT(!IsEqual(up_direction, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(up_direction));

        Vector3 const r2 = Normalize(eye_direction);

        Vector3 const t0 = Cross(up_direction, r2);
        Vector3 const r0 = Normalize(t0);

        Vector3 const r1 = Cross(r2, r0);

        Vector3 const neg_eye_position = Negate(eye_position);

        Vector4 const d0 = Dot(r0, neg_eye_position);
        Vector4 const d1 = Dot(r1, neg_eye_position);
        Vector4 const d2 = Dot(r2, neg_eye_position);

        Matrix result;
        result.M.R[0] = Select(d0, Vector4{ r0.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V }).V;
        result.M.R[1] = Select(d1, Vector4{ r1.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V }).V;
        result.M.R[2] = Select(d2, Vector4{ r2.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V }).V;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

        return Transpose(result);
    }

    mathinline Matrix mathcall LookToRH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
    {
        Vector3 const neg_eye_direction = Negate(eye_direction);
        return LookToLH(eye_position, neg_eye_direction, up_direction);
    }

    mathinline Matrix mathcall LookAtLH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
    {
        Vector3 const eye_direction = Subtract(eye_position, focus_position);
        return LookToLH(eye_position, eye_direction, up_direction);
    }

    mathinline Matrix mathcall LookAtRH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
    {
        Vector3 const eye_direction = Subtract(eye_position, focus_position);
        return LookToRH(eye_position, eye_direction, up_direction);
    }

    //
    // Projection matrices.
    //

    mathinline Matrix mathcall PerspectiveLH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.000001f));

        float const z_near_2 = z_near + z_near;
        float const range    = z_far / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(z_near_2 / view_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(z_near_2 / view_height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
        result.M.R[3]          = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 / view_width,
            z_near_2 / view_height,
            range,
            -range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        // [range, -range * z_near, 0, 1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, 1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, -range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    mathinline Matrix mathcall PerspectiveRH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.000001f));

        float const z_near_2 = z_near + z_near;
        float const range    = z_far / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = -1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(z_near_2 / view_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(z_near_2 / view_height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, Impl::VEC4_NEGATIVE_UNIT_W.V, 2);
        result.M.R[3]          = vsetq_lane_f32(range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 / view_width,
            z_near_2 / view_height,
            range,
            range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        // [range, range * z_near, 0, -1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_NEGATIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, 1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    mathinline Matrix mathcall PerspectiveFovLH(
        float fov_angle_y,
        float aspect_ratio,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(fov_angle_y, 0.0f, 0.00001f * 2.0f));
        GX_ASSERT(!IsEqual(aspect_ratio, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float fov_sin;
        float fov_cos;
        SinCos(fov_sin, fov_cos, 0.5f * fov_angle_y);

        float const height = fov_cos / fov_sin;
        float const width  = height / aspect_ratio;
        float const range  = z_far / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
        result.M.R[3]          = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            width,
            height,
            range,
            -range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        // [range, -range * z_near, 0, 1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, 1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, -range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    mathinline Matrix mathcall PerspectiveFovRH(
        float fov_angle_y,
        float aspect_ratio,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(fov_angle_y, 0.0f, 0.00001f * 2.0f));
        GX_ASSERT(!IsEqual(aspect_ratio, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float fov_sin;
        float fov_cos;
        SinCos(fov_sin, fov_cos, 0.5f * fov_angle_y);

        float const height = fov_cos / fov_sin;
        float const width  = height / aspect_ratio;
        float const range  = z_far / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = -1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, Impl::VEC4_NEGATIVE_UNIT_W.V, 2);
        result.M.R[3]          = vsetq_lane_f32(range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            width,
            height,
            range,
            range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        // [range, range * z_near, 0, -1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_NEGATIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, -1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    mathinline Matrix mathcall PerspectiveOffsetLH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.0001f));

        float const z_near_2   = z_near + z_near;
        float const rcp_width  = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range      = z_far / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 * rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 * rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = -(view_left + view_right) * rcp_width;
        result.M.M[2][1] = -(view_top + view_bottom) * rcp_height;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(z_near_2 * rcp_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(z_near_2 * rcp_height, zero, 1);
        result.M.R[2]          = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range,
            1.0f)
                            .V;
        result.M.R[3]          = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 * rcp_width,
            z_near_2 * rcp_height,
            -range * z_near,
            0.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        // [z_near_2 * rcp_width, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, z_near_2 * rcp_height, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        __m128 const r2_zw = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range,
            1.0f)
                                 .V;

        // [0, 0, -range * z_near, 0]
        __m128 const r3_z = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Z.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_z;
#endif
        return result;
    }

    mathinline Matrix mathcall PerspectiveOffsetRH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.0001f));

        float const z_near_2   = z_near + z_near;
        float const rcp_width  = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range      = z_far / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 * rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 * rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = (view_left + view_right) * rcp_width;
        result.M.M[2][1] = (view_top + view_bottom) * rcp_height;
        result.M.M[2][2] = range;
        result.M.M[2][3] = -1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(z_near_2 * rcp_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(z_near_2 * rcp_height, zero, 1);
        result.M.R[2]          = Make<Vector4>(
            (view_left + view_right) * rcp_width,
            (view_top + view_bottom) * rcp_height,
            range,
            -1.0f)
                            .V;
        result.M.R[3]          = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 * rcp_width,
            z_near_2 * rcp_height,
            range * z_near,
            0.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        // [z_near_2 * rcp_width, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, z_near_2 * rcp_height, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        __m128 const r2_zw = Make<Vector4>(
            (view_left + view_right) * rcp_width,
            (view_top + view_bottom) * rcp_height,
            range,
            -1.0f)
                                 .V;

        // [0, 0, range * z_near, 0]
        __m128 const r3_z = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Z.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_z;
#endif
        return result;
    }

    mathinline Matrix mathcall OrthographicLH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const range = 1.0f / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = 2.0f / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = 2.0f / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(2.0f / view_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(2.0f / view_height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, zero, 2);
        result.M.R[3]          = vsetq_lane_f32(-range * z_near, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            2.0f / view_width,
            2.0f / view_height,
            range,
            -range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        __m128 const r0_x    = _mm_move_ss(zero, values);
        __m128 const r1_y    = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const r2_z    = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 0, 0, 0));
        __m128 const r3_zw   = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_zw;
#endif
        return result;
    }

    mathinline Matrix mathcall OrthographicRH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const range = 1.0f / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = 2.0f / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = 2.0f / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(2.0f / view_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(2.0f / view_height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, zero, 2);
        result.M.R[3]          = vsetq_lane_f32(range * z_near, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            2.0f / view_width,
            2.0f / view_height,
            range,
            range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        __m128 const r0_x    = _mm_move_ss(zero, values);
        __m128 const r1_y    = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const r2_z    = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 0, 0, 0));
        __m128 const r3_zw   = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_zw;
#endif
        return result;
    }

    mathinline Matrix mathcall OrthographicOffsetLH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const rcp_width  = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range      = 1.0f / (z_far - z_near);

        Matrix result;

#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = rcp_width + rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = rcp_height + rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = -(view_left + view_right) * rcp_width;
        result.M.M[3][1] = -(view_top + view_bottom) * rcp_height;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(rcp_width + rcp_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(rcp_height + rcp_height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, zero, 2);
        result.M.R[3]          = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            -range * z_near,
            1.0f)
                            .V;
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            rcp_width,
            rcp_height,
            range,
            1.0f,
        } } };
        Impl::ConstFloat32x4 const mvalues2{ { {
            -(view_left + view_right),
            -(view_top + view_bottom),
            -z_near,
            1.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        __m128 const t0_x = _mm_move_ss(zero, values);
        __m128 const r0_x = _mm_add_ss(t0_x, t0_x);

        __m128 const t1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const r1_y = _mm_add_ps(t1_y, t1_y);

        __m128 const r2_z = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Z.V);

        __m128 const r3_xyzw = _mm_mul_ps(values, mvalues2.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_xyzw;
#endif
        return result;
    }

    mathinline Matrix mathcall OrthographicOffsetRH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far) noexcept
    {
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const rcp_width  = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range      = 1.0f / (z_near - z_far);

        Matrix result;

#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = rcp_width + rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = rcp_height + rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = -(view_left + view_right) * rcp_width;
        result.M.M[3][1] = -(view_top + view_bottom) * rcp_height;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0]          = vsetq_lane_f32(rcp_width + rcp_width, zero, 0);
        result.M.R[1]          = vsetq_lane_f32(rcp_height + rcp_height, zero, 1);
        result.M.R[2]          = vsetq_lane_f32(range, zero, 2);
        result.M.R[3]          = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range * z_near,
            1.0f)
                            .V;
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            rcp_width,
            rcp_height,
            range,
            1.0f,
        } } };
        Impl::ConstFloat32x4 const mvalues2{ { {
            -(view_left + view_right),
            -(view_top + view_bottom),
            z_near,
            1.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero   = _mm_setzero_ps();

        __m128 const t0_x = _mm_move_ss(zero, values);
        __m128 const r0_x = _mm_add_ss(t0_x, t0_x);

        __m128 const t1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const r1_y = _mm_add_ps(t1_y, t1_y);

        __m128 const r2_z = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Z.V);

        __m128 const r3_xyzw = _mm_mul_ps(values, mvalues2.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_xyzw;
#endif
        return result;
    }
}

// =================================================================================================
//
// Color operations
//

namespace Graphyte::Maths
{
    mathinline Color mathcall Negative(Color v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F - v.V.F[0],
            1.0F - v.V.F[1],
            1.0F - v.V.F[2],
            v.V.F[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const neg_xyz = _mm_xor_ps(v.V, Impl::VEC4_NEGATIVE_ZERO_3.V);
        __m128 const result  = _mm_add_ps(neg_xyz, Impl::VEC4_ONE_3.V);
        return { result };
#endif
    }

    mathinline Color mathcall Modulate(Color a, Color b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] * b.V.F[0],
            a.V.F[1] * b.V.F[1],
            a.V.F[2] * b.V.F[2],
            a.V.F[3] * b.V.F[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(a.V, b.V) };
#endif
    }

    mathinline Color mathcall AdjustSaturation(Color v, float saturation) noexcept
    {
        static Impl::ConstFloat32x4 const luminance{ { {
            0.2125F,
            0.7154F,
            0.0721F,
            0.0F,
        } } };

#if GRAPHYTE_MATH_NO_INTRINSICS
        float const factor
            = (v.V.F[0] * luminance.V.F[0])
              + (v.V.F[1] * luminance.V.F[1])
              + (v.V.F[2] * luminance.V.F[2]);

        Impl::ConstFloat32x4 const result{ { { ((v.V.F[0] - factor) * saturation) + factor,
            ((v.V.F[1] - factor) * saturation) + factor,
            ((v.V.F[2] - factor) * saturation) + factor,
            v.V.F[3] } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const vfactor     = _mm_dp_ps(v.V, luminance.V, 0x3F);
        __m128 const vsaturation = _mm_set_ps1(saturation);
        __m128 const r0          = _mm_sub_ps(v.V, vfactor);
        __m128 const r1          = Impl::avx_fmadd_f32x4(r0, vsaturation, vfactor);
        __m128 const r2          = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3          = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
        return { r3 };
#endif
    }

    mathinline Color mathcall AdjustContrast(Color v, float contrast) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { { ((v.V.F[0] - 0.5F) * contrast) + 0.5F,
            ((v.V.F[1] - 0.5F) * contrast) + 0.5F,
            ((v.V.F[2] - 0.5F) * contrast) + 0.5F,
            v.V.F[3] } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const vcontrast = _mm_set_ps1(contrast);
        __m128 const r0        = _mm_sub_ps(v.V, Impl::VEC4_ONE_HALF_4.V);
        __m128 const r1        = Impl::avx_fmadd_f32x4(r0, vcontrast, Impl::VEC4_ONE_HALF_4.V);
        __m128 const r2        = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3        = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
        return { r3 };
#endif
    }
}

// =================================================================================================
//
// Plane operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall DotCoord(Plane p, Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        // v4 = {v3, 1}
        Vector4 const v4_1   = Select(Vector4{ Impl::VEC4_ONE_4.V }, Vector4{ v.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
        Vector4 const result = Dot(Vector4{ p.V }, v4_1);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const mask = Impl::VEC4_MASK_SELECT_1110.V;

        // select {_,_,_,1}
        __m128 const one4 = _mm_andnot_ps(mask, Impl::VEC4_ONE_4.V);
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
        __m128 const length_sq  = _mm_dp_ps(p.V, p.V, 0b0111'1111);
        __m128 const length     = _mm_sqrt_ps(length_sq);
        __m128 const mask       = _mm_cmpneq_ps(length_sq, Impl::VEC4_INFINITY.V);
        __m128 const normalized = _mm_div_ps(p.V, length);
        __m128 const result     = _mm_and_ps(normalized, mask);
        return { result };
#endif
    }

    mathinline Plane mathcall NormalizeEst(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length = ReciprocalLengthEst(Vector3{ p.V });
        Vector4 const result = Multiply(Vector4{ p.V }, length);
        return Plane{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const length     = _mm_dp_ps(p.V, p.V, 0x7F);
        __m128 const rcp_length = _mm_rsqrt_ps(length);
        __m128 const result     = _mm_mul_ps(p.V, rcp_length);
        return { result };
#endif
    }

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
        Vector4 const p_wwww = Dot(point, normal);
        Vector4 const n_wwww = Negate(p_wwww);
        Vector4 const abcw   = Select(n_wwww, Vector4{ normal.V }, Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
        Plane const result{ abcw.V };
        return result;
    }

    mathinline Plane mathcall CreateFromPoints(Vector3 p1, Vector3 p2, Vector3 p3) noexcept
    {
        Vector3 const d_p21 = Subtract(p1, p2);
        Vector3 const d_p31 = Subtract(p1, p3);

        Vector3 const plane_perpendicular = Cross(d_p21, d_p31);
        Vector3 const plane_normal        = Normalize(plane_perpendicular);

        Vector4 const neg_plane_distance = DotNormal(Plane{ plane_normal.V }, p1);
        Vector4 const plane_distance     = Negate(neg_plane_distance);

        Vector4 const result = Select(
            plane_distance,
            Vector4{ plane_normal.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
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
        Vector4 const pp     = Negate(vp);
        Vector4 const p_aaaa = SplatX(pp);
        Vector4 const p_bbbb = SplatY(pp);
        Vector4 const p_cccc = SplatZ(pp);
        Vector4 const p_dddd = SplatW(pp);

        Vector4 dot = Dot(vp, light);
        dot         = Select(Vector4{ Impl::VEC4_MASK_SELECT_0001.V }, dot, Bool4{ Impl::VEC4_MASK_SELECT_0001.V });

        Matrix result;
        result.M.R[3] = MultiplyAdd(p_dddd, light, dot).V;
        dot           = RotateLeft<1>(dot);
        result.M.R[2] = MultiplyAdd(p_cccc, light, dot).V;
        dot           = RotateLeft<1>(dot);
        result.M.R[1] = MultiplyAdd(p_bbbb, light, dot).V;
        dot           = RotateLeft<1>(dot);
        result.M.R[0] = MultiplyAdd(p_aaaa, light, dot).V;

        return result;
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


// =================================================================================================
//
// Degrees / Radians conversion
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall RevolutionsToDegrees(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(360.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RevolutionsToDegrees(float value) noexcept
    {
        return value * 360.0F;
    }

    mathinline Vector4 mathcall RevolutionsToRadians(Vector4 value) noexcept
    {
        Vector4 const multiplier{ Impl::VEC4_PI.V };
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RevolutionsToRadians(float value) noexcept
    {
        return value * Maths::Impl::ConstPi<float>;
    }

    mathinline Vector4 mathcall RevolutionsToGradians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(400.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RevolutionsToGradians(float value) noexcept
    {
        return value * 400.0F;
    }

    mathinline Vector4 mathcall DegreesToRevolutions(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(1.0F / 360.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall DegreesToRevolutions(float value) noexcept
    {
        return value / 360.0F;
    }

    mathinline Vector4 mathcall RadiansToRevolutions(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(1.0F / Maths::Impl::ConstPi2<float>);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RadiansToRevolutions(float value) noexcept
    {
        return value / Maths::Impl::ConstPi2<float>;
    }

    mathinline Vector4 mathcall GradiansToRevolutions(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(1.0F / 400.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall GradiansToRevolutions(float value) noexcept
    {
        return value / 400.0F;
    }

    mathinline Vector4 mathcall RadiansToGradians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(200.0F / Maths::Impl::ConstPi<float>);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RadiansToGradians(float value) noexcept
    {
        return value * (200.0F / Maths::Impl::ConstPi<float>);
    }

    mathinline Vector4 mathcall GradiansToRadians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(Maths::Impl::ConstPi<float> / 200.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall GradiansToRadians(float value) noexcept
    {
        return value * (Maths::Impl::ConstPi<float> / 200.0F);
    }

    mathinline Vector4 mathcall RadiansToDegrees(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(180.0F / Maths::Impl::ConstPi<float>);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RadiansToDegrees(float value) noexcept
    {
        return value * (180.0F / Maths::Impl::ConstPi<float>);
    }

    mathinline Vector4 mathcall DegreesToRadians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(Maths::Impl::ConstPi<float> / 180.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall DegreesToRadians(float value) noexcept
    {
        return value * (Maths::Impl::ConstPi<float> / 180.0F);
    }

    mathinline Vector4 mathcall GradiansToDegrees(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(9.0F / 10.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall GradiansToDegrees(float value) noexcept
    {
        return value * (9.0F / 10.0F);
    }

    mathinline Vector4 mathcall DegreesToGradians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(10.0F / 9.0F);
        Vector4 const result     = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall DegreesToGradians(float value) noexcept
    {
        return value * (10.0F / 9.0F);
    }
}

// =================================================================================================
//
// ULP Near Equal
//

namespace Graphyte::Maths
{
    mathinline bool mathcall IsNearEqual(float a, float b, int32_t tolerance) noexcept
    {
        if (IsZero(a - b))
        {
            return true;
        }

        int32_t const ia = BitCast<int32_t>(a);
        int32_t const ib = BitCast<int32_t>(b);

        if ((ia < 0) != (ib < 0))
        {
            return false;
        }

        int32_t const ulp = abs(ia - ib);

        return ulp <= tolerance;
    }

    mathinline bool mathcall IsNearEqual(float value1, float value2) noexcept
    {
        static constexpr const int32_t tolerance{ 4 };
        return IsNearEqual(value1, value2, tolerance);
    }
}


// =================================================================================================
//
// Fixed/Float conversion.
//

namespace Graphyte::Maths
{
    mathinline uint32_t mathcall FixedToFixed(uint32_t value, uint32_t n, uint32_t p) noexcept
    {
        if (n > p)
        {
            value >>= (n - p);
        }
        else if (n < p)
        {
            if (value == (static_cast<uint32_t>(1) << n) - 1)
            {
                value = static_cast<uint32_t>((1 << p) - 1);
            }
            else
            {
                value = static_cast<uint32_t>((value * (1 << p)) / ((1 << n) - 1));
            }
        }

        return value;
    }

    mathinline uint32_t mathcall FloatToFixed(float value, uint32_t bits) noexcept
    {
        if (value <= 0.0F)
        {
            return 0;
        }
        else if (value >= 1.0F)
        {
            return static_cast<uint32_t>((1 << bits) - 1);
        }


        return static_cast<uint32_t>(value * static_cast<float>(1U << bits));
    }

    mathinline float mathcall FixedToFloat(uint32_t value, uint32_t bits) noexcept
    {
        return static_cast<float>(value) / static_cast<float>((1 << bits) - 1);
    }
}


// =================================================================================================
//
// Coordinate systems
//

namespace Graphyte::Maths
{
    mathinline Float3A mathcall CartesianToSpherical(const Float3A& value) noexcept
    {
        float const radius = Sqrt(
            value.X * value.X + value.Y * value.Y + value.Z * value.Z);
        float const theta = Acos(
            value.Z / radius);
        float const phi = Atan(
            value.Y / value.X);

        return { radius, theta, phi };
    }

    mathinline Float3A mathcall SphericalToCartesian(const Float3A& value) noexcept
    {
        float sin_theta;
        float cos_theta;
        float sin_phi;
        float cos_phi;
        float const radius = value.X;
        SinCos(sin_theta, cos_theta, value.Y);
        SinCos(sin_phi, cos_phi, value.Z);

        float const partial = radius * sin_theta;

        return { partial * cos_phi, partial * sin_phi, radius * cos_theta };
    }

    mathinline Float3A mathcall CartesianToCylindrical(const Float3A& value) noexcept
    {
        float const radius = Sqrt(
            value.X * value.X + value.Y * value.Y);
        float const angle = Atan(
            value.Y / value.X);
        float const elevation = value.Z;

        return { radius, angle, elevation };
    }

    mathinline Float3A mathcall CylindricalToCartesian(const Float3A& value) noexcept
    {
        float const radius    = value.X;
        float const angle     = value.Y;
        float const elevation = value.Z;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        return { radius * cos_angle, radius * sin_angle, elevation };
    }

    mathinline Float2A mathcall PolarToCartesian(const Float2A& value) noexcept
    {
        float const radius = value.X;
        float const angle  = value.Y;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        float const x = radius * cos_angle;
        float const y = radius * sin_angle;

        return { x, y };
    }

    mathinline Float2A mathcall CartesianToPolar(const Float2A& value) noexcept
    {
        float const radius = Sqrt(
            value.X * value.X + value.Y * value.Y);
        float const angle = Atan2(value.Y, value.X);

        return { radius, angle };
    }
}


// =================================================================================================
//
// Common functions TODO: CATALOG
//

namespace Graphyte::Maths
{
    mathinline float mathcall Gain(float value, float gain) noexcept
    {
        float const g = -Log2(1.0F - gain);
        float const c = Power(value, gain);
        return c / (c + Power(1.0F - value, g));
    }

    mathinline float mathcall Bias(float value, float base) noexcept
    {
        return Power(value, -Log2(base));
    }

    mathinline float mathcall Step(float value1, float value2) noexcept
    {
        return (value1 <= value2)
                   ? 0.0F
                   : 1.0F;
    }

    mathinline int mathcall QuadricEquation(float a, float b, float c, float& out_x1, float& out_x2) noexcept
    {
        float const delta = (b * b) - (4.0F * a * c);

        if (delta < 0.0F)
        {
            out_x1 = out_x2 = std::numeric_limits<float>::infinity();
            return 0;
        }
        else if (IsZero(delta))
        {
            out_x1 = out_x2 = (-b / (2.0F * a));
            return 1;
        }

        float const denominator = 1.0F / (2.0F * a);
        float const delta_sqrt  = Sqrt(delta);

        out_x1 = (-b - delta_sqrt) * denominator;
        out_x2 = (-b + delta_sqrt) * denominator;

        return 2;
    }

    mathinline float mathcall SnapToGrid(float value, float grid_size) noexcept
    {
        if (grid_size == 0.0F)
        {
            return value;
        }
        else
        {
            return Floor((value + 0.5F * grid_size) / grid_size) * grid_size;
        }
    }

    mathinline float mathcall WangHashNoise(uint32_t u, uint32_t v, uint32_t s) noexcept
    {
        uint32_t seed = (u * 1664525U + v) + s;

        seed = (seed ^ 61U) ^ (seed >> 16U);
        seed *= 9U;
        seed = seed ^ (seed >> 4U);
        seed *= 0x27d4eb2d;
        seed = seed ^ (seed >> 15U);

        float value = static_cast<float>(seed);
        value       = static_cast<float>(static_cast<double>(value) * (1.0 / 4294967296.0));
        return value;
    }

    mathinline float mathcall WrapAngle(float value) noexcept
    {
        float const raw = value + Maths::Impl::ConstPi<float>;
        float abs       = Abs(raw);

        float const scaled = static_cast<float>(static_cast<int32_t>(abs / Maths::Impl::ConstPi<float>));

        abs -= Maths::Impl::ConstPi<float> * scaled;
        abs -= Maths::Impl::ConstPi<float>;

        if (raw < 0.0F)
        {
            abs = -abs;
        }

        return abs;
    }

    mathinline float mathcall DiffAngle(float angle1, float angle2) noexcept
    {
        float const r1 = angle2 - angle1;
        float const r2 = r1 - Maths::Impl::ConstPi2<float>;
        float const r3 = r1 + Maths::Impl::ConstPi2<float>;

        float const a1 = Abs(r1);
        float const a2 = Abs(r2);
        float const a3 = Abs(r3);

        if ((a1 < a2) && (a1 < a3))
        {
            return r1;
        }
        else if (a2 < a3)
        {
            return r2;
        }

        return r3;
    }
}


// =================================================================================================
//
// Fresnel Term
//


namespace Graphyte::Maths
{
    mathinline Vector4 mathcall FresnelTerm(Vector4 cos_incident_angle, Vector4 refraction_index) noexcept
    {
        // c = cos_incident_angle
        // g = sqrt(c^2 + refraction_index^2 - 1)
        // r = 0.5f * (g - c)^2 / (g + c)^2 * ((c * (g + c) - 1)^2 / (c * (g - c) + 1)^2 + 1)

        GX_ASSERT(!IsInfinity(cos_incident_angle));

#if GRAPHYTE_MATH_NO_INTRINSICS

        // = refraction_index^2 - 1
        Vector4 const g0 = MultiplyAdd(refraction_index, refraction_index, Vector4{ Impl::VEC4_NEGATIVE_ONE_4.V });

        // = c^2 + refraction_index^2 - 1
        Vector4 const g1 = MultiplyAdd(cos_incident_angle, cos_incident_angle, g0);
        Vector4 const g2 = Abs(g1);
        Vector4 const g3 = Sqrt(g2);

        // = (g + c)^2
        Vector4 const s0 = Add(g3, cos_incident_angle);
        Vector4 const s1 = Multiply(s0, s0);

        // = (g - c)^2
        Vector4 const d0 = Subtract(g3, cos_incident_angle);
        Vector4 const d1 = Multiply(d0, d0);

        // = 0.5f * (g - c)^2 / (g + c)^2
        Vector4 const rcp_s1  = Reciprocal(s1);
        Vector4 const half_d1 = Multiply(Vector4{ Impl::VEC4_HALF_4.V }, d1);
        Vector4 const r0      = Multiply(half_d1, rcp_s1);

        // = (c * (g + c) - 1)^2
        Vector4 const ca0 = MultiplyAdd(cos_incident_angle, s0, Vector4{ Impl::VEC4_NEGATIVE_ONE_4.V });
        Vector4 const ca1 = Multiply(ca0, ca0);

        // = (c * (g - c) + 1)^2
        Vector4 const cb0 = MultiplyAdd(cos_incident_angle, d0, Vector4{ Impl::VEC4_ONE_4.V });
        Vector4 const cb1 = Multiply(cb0, cb0);
        Vector4 const cb2 = Reciprocal(cb1);

        Vector4 const r1 = MultiplyAdd(ca1, cb2, Vector4{ Impl::VEC4_ONE_4.V });
        Vector4 const r2 = Multiply(r0, r1);
        Vector4 const r3 = Saturate(r2);

        return r3;

#elif GRAPHYTE_HW_AVX

        __m128 const one = Impl::VEC4_ONE_4.V;

        // NOTE: possible optimization; instead of storing `zero` in register whole time, we may insert it later
        __m128 const zero = _mm_setzero_ps();

        // = c^2 + refraction_index^2 - 1
        __m128 const g0 = Impl::avx_fmsub_f32x4(refraction_index.V, refraction_index.V, one);
        __m128 const g1 = Impl::avx_fmadd_f32x4(cos_incident_angle.V, cos_incident_angle.V, g0);
        __m128 const g2 = _mm_sub_ps(zero, g1);
        __m128 const g3 = _mm_max_ps(g2, g1);
        __m128 const g4 = _mm_sqrt_ps(g3);

        // s = (g + c)^2
        // d = (g - c)^2
        __m128 const s0 = _mm_add_ps(g4, cos_incident_angle.V);
        __m128 const d0 = _mm_sub_ps(g4, cos_incident_angle.V);
        __m128 const s1 = _mm_mul_ps(s0, s0);
        __m128 const d1 = _mm_mul_ps(d0, d0);

        // = 0.5f * (g - c)^2 / (g + c)^2
        __m128 const half_d1 = _mm_mul_ps(d1, Impl::VEC4_ONE_HALF_4.V);
        __m128 const r0      = _mm_div_ps(half_d1, s1);

        // = (c * (g + c) - 1)^2
        __m128 const ca0 = Impl::avx_fmsub_f32x4(cos_incident_angle.V, s0, one);
        __m128 const ca1 = _mm_mul_ps(ca0, ca0);

        // = (c * (g - c) + 1)^2
        __m128 const cb0 = Impl::avx_fmadd_f32x4(cos_incident_angle.V, d0, one);
        __m128 const cb1 = _mm_mul_ps(cb0, cb0);

        __m128 const r1 = _mm_div_ps(ca1, cb1);
        __m128 const r2 = _mm_add_ps(r1, one);
        __m128 const r3 = _mm_mul_ps(r0, r2);

        __m128 const rmin = _mm_max_ps(r3, zero);
        __m128 const rmax = _mm_min_ps(rmin, one);
        return { rmax };
#endif
    }
}


// =================================================================================================
//
// Vector projection on viewport
//

namespace Graphyte::Maths
{
    // TODO: make Viewport struct instead of this
    mathinline Vector3 mathcall Project(
        Vector3 v,
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float viewport_min_z,
        float viewport_max_z,
        Matrix projection,
        Matrix view,
        Matrix world) noexcept
    {
        float const half_width  = viewport_width * 0.5F;
        float const half_height = viewport_height * 0.5F;

        Vector3 const scale = Make<Vector3>(
            half_width,
            -half_height,
            viewport_max_z - viewport_min_z);

        Vector3 const offset = Make<Vector3>(
            viewport_x + half_width,
            viewport_y + half_height,
            viewport_min_z);

        Matrix const wv  = Multiply(world, view);
        Matrix const wvp = Multiply(wv, projection);

        Vector3 const tv     = TransformCoord(v, wvp);
        Vector3 const result = MultiplyAdd(tv, scale, offset);
        return result;
    }

    mathinline Vector3 mathcall Unproject(
        Vector3 v,
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float viewport_min_z,
        float viewport_max_z,
        Matrix projection,
        Matrix view,
        Matrix world) noexcept
    {
        static Impl::ConstFloat32x4 const d{ { {
            -1.0F,
            1.0F,
            0.0F,
            0.0F,
        } } };

        Vector3 const scale = Make<Vector3>(
            viewport_width * 0.5F,
            -viewport_height * 0.5F,
            viewport_max_z - viewport_min_z);

        Vector3 const rcp_scale = Reciprocal(scale);

        Vector3 const offset = Make<Vector3>(
            -viewport_x,
            -viewport_y,
            -viewport_min_z);

        Vector3 const projected = MultiplyAdd(rcp_scale, offset, Vector3{ d.V });

        Matrix const mv      = Multiply(world, view);
        Matrix const mvp     = Multiply(mv, projection);
        Matrix const inv_mvp = Inverse(mvp);

        Vector3 const coord  = MultiplyAdd(v, rcp_scale, projected);
        Vector3 const result = TransformCoord(coord, inv_mvp);
        return result;
    }
}


// =================================================================================================
//
// Load / Store for packed types
//

namespace Graphyte::Maths
{
    template <>
    mathinline Color mathcall Load<Color, ColorBGRA>(ColorBGRA const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        uint32_t const value = source->Value;

        Impl::ConstFloat32x4 const result{ { {
            (1.0f / 255.0f) * static_cast<float>((value >> 16) & 0xFFu),
            (1.0f / 255.0f) * static_cast<float>((value >> 8) & 0xFFu),
            (1.0f / 255.0f) * static_cast<float>(value & 0xFFu),
            (1.0f / 255.0f) * static_cast<float>((value >> 24) & 0xFFu),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // {c0}[#bgra, #bgra, #bgra, #bgra]
        __m128i const c0 = _mm_set1_epi32(static_cast<int>(source->Value));
        // {c1}[#__r_, #_g__, #b___, #___a]
        __m128i const c1 = _mm_and_si128(c0, _mm_castps_si128(Impl::VEC4_MASK_A8R8G8B8.V));
        __m128i const c2 = _mm_xor_si128(c1, _mm_castps_si128(Impl::VEC4_FLIP_A_A8R8G8B8.V));
        __m128 const c3  = _mm_cvtepi32_ps(c2);
        __m128 const c4  = _mm_add_ps(c3, Impl::VEC4_FIX_A_A8R8G8B8.V);
        __m128 const c5  = _mm_mul_ps(c4, Impl::VEC4_NORMALIZE_A8R8G8B8.V);
        return { c5 };
#endif
    }

    template <>
    mathinline void mathcall Store<ColorBGRA, Color>(ColorBGRA* destination, Color color) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const c0 = Saturate(Vector4{ color.V });
        Vector4 const c1 = Multiply(c0, Vector4{ Impl::VEC4_UBYTE_MAX.V });
        Vector4 const c2 = Round(c1);

        Float4A buffer;
        Store(&buffer, c2);

        uint32_t const a = static_cast<uint32_t>(buffer.W) << 24;
        uint32_t const r = static_cast<uint32_t>(buffer.X) << 16;
        uint32_t const g = static_cast<uint32_t>(buffer.Y) << 8;
        uint32_t const b = static_cast<uint32_t>(buffer.X);

        destination->Value = a | r | g | b;
#elif GRAPHYTE_HW_AVX
        // Saturate
        __m128 const color_max = _mm_max_ps(color.V, _mm_setzero_ps());
        __m128 const color_min = _mm_min_ps(color_max, Impl::VEC4_ONE_4.V);

        // RGBA -> ARGB
        __m128 const c0  = _mm_mul_ps(color_min, Impl::VEC4_UBYTE_MAX.V);
        __m128 const c1  = _mm_permute_ps(c0, _MM_SHUFFLE(3, 0, 1, 2));
        __m128i const c2 = _mm_cvtps_epi32(c1);
        __m128i const c3 = _mm_packs_epi32(c2, c2);
        __m128i const c4 = _mm_packus_epi16(c3, c3);

        _mm_store_ss(reinterpret_cast<float*>(&destination->Value), _mm_castsi128_ps(c4));
#endif
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
