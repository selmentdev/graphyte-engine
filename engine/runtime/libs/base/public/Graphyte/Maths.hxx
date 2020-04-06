#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Half.hxx>
#include <Graphyte/Types.hxx>
#include <Graphyte/Maths/Base.hxx>


// =================================================================================================
//
// Concepts
//

namespace Graphyte::Maths
{
}

// =================================================================================================
//
// Math types
//

namespace Graphyte::Maths
{
    struct Bool4 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = uint32_t;
        using MaskType = Bool4;
    };

    struct Bool3 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 3;
        static constexpr const uint32_t CompareMask = 0b0111;
        using ComponentType = uint32_t;
        using MaskType = Bool3;
    };

    struct Bool2 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 2;
        using ComponentType = uint32_t;
        using MaskType = Bool2;
    };

    struct Bool1 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 1;
        using ComponentType = uint32_t;
        using MaskType = Bool1;
    };

    struct Vector4 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Vector3 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 3;
        using ComponentType = float;
        using MaskType = Bool3;
    };

    struct Vector2 final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 2;
        using ComponentType = float;
        using MaskType = Bool2;
    };

    struct Vector1 final
    {
        Impl::NativeFloat32x4 V;
        static constexpr const size_t Components = 1;
        using ComponentType = float;
        using MaskType = Bool1;
    };

    struct Quaternion final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Plane final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Sphere final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Matrix final
    {
        Impl::NativeFloat32x4x4 M;

        static constexpr const size_t Components = 16;
        static constexpr const size_t Rows = 4;
        static constexpr const size_t Columns = 4;
        using ComponentType = float;
    };

    struct Color final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;
        using ComponentType = float;
        using MaskType = Bool4;
    };
}


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
        XXXX, YXXX, ZXXX, WXXX,
        XYXX, YYXX, ZYXX, WYXX,
        XZXX, YZXX, ZZXX, WZXX,
        XWXX, YWXX, ZWXX, WWXX,
        XXYX, YXYX, ZXYX, WXYX,
        XYYX, YYYX, ZYYX, WYYX,
        XZYX, YZYX, ZZYX, WZYX,
        XWYX, YWYX, ZWYX, WWYX,
        XXZX, YXZX, ZXZX, WXZX,
        XYZX, YYZX, ZYZX, WYZX,
        XZZX, YZZX, ZZZX, WZZX,
        XWZX, YWZX, ZWZX, WWZX,
        XXWX, YXWX, ZXWX, WXWX,
        XYWX, YYWX, ZYWX, WYWX,
        XZWX, YZWX, ZZWX, WZWX,
        XWWX, YWWX, ZWWX, WWWX,

        XXXY, YXXY, ZXXY, WXXY,
        XYXY, YYXY, ZYXY, WYXY,
        XZXY, YZXY, ZZXY, WZXY,
        XWXY, YWXY, ZWXY, WWXY,
        XXYY, YXYY, ZXYY, WXYY,
        XYYY, YYYY, ZYYY, WYYY,
        XZYY, YZYY, ZZYY, WZYY,
        XWYY, YWYY, ZWYY, WWYY,
        XXZY, YXZY, ZXZY, WXZY,
        XYZY, YYZY, ZYZY, WYZY,
        XZZY, YZZY, ZZZY, WZZY,
        XWZY, YWZY, ZWZY, WWZY,
        XXWY, YXWY, ZXWY, WXWY,
        XYWY, YYWY, ZYWY, WYWY,
        XZWY, YZWY, ZZWY, WZWY,
        XWWY, YWWY, ZWWY, WWWY,

        XXXZ, YXXZ, ZXXZ, WXXZ,
        XYXZ, YYXZ, ZYXZ, WYXZ,
        XZXZ, YZXZ, ZZXZ, WZXZ,
        XWXZ, YWXZ, ZWXZ, WWXZ,
        XXYZ, YXYZ, ZXYZ, WXYZ,
        XYYZ, YYYZ, ZYYZ, WYYZ,
        XZYZ, YZYZ, ZZYZ, WZYZ,
        XWYZ, YWYZ, ZWYZ, WWYZ,
        XXZZ, YXZZ, ZXZZ, WXZZ,
        XYZZ, YYZZ, ZYZZ, WYZZ,
        XZZZ, YZZZ, ZZZZ, WZZZ,
        XWZZ, YWZZ, ZWZZ, WWZZ,
        XXWZ, YXWZ, ZXWZ, WXWZ,
        XYWZ, YYWZ, ZYWZ, WYWZ,
        XZWZ, YZWZ, ZZWZ, WZWZ,
        XWWZ, YWWZ, ZWWZ, WWWZ,

        XXXW, YXXW, ZXXW, WXXW,
        XYXW, YYXW, ZYXW, WYXW,
        XZXW, YZXW, ZZXW, WZXW,
        XWXW, YWXW, ZWXW, WWXW,
        XXYW, YXYW, ZXYW, WXYW,
        XYYW, YYYW, ZYYW, WYYW,
        XZYW, YZYW, ZZYW, WZYW,
        XWYW, YWYW, ZWYW, WWYW,
        XXZW, YXZW, ZXZW, WXZW,
        XYZW, YYZW, ZYZW, WYZW,
        XZZW, YZZW, ZZZW, WZZW,
        XWZW, YWZW, ZWZW, WWZW,
        XXWW, YXWW, ZXWW, WXWW,
        XYWW, YYWW, ZYWW, WYWW,
        XZWW, YZWW, ZZWW, WZWW,
        XWWW, YWWW, ZWWW, WWWW,
    };

    constexpr const uint32_t PERMUTE_0X = 0;
    constexpr const uint32_t PERMUTE_0Y = 1;
    constexpr const uint32_t PERMUTE_0Z = 2;
    constexpr const uint32_t PERMUTE_0W = 3;
    constexpr const uint32_t PERMUTE_1X = 4;
    constexpr const uint32_t PERMUTE_1Y = 5;
    constexpr const uint32_t PERMUTE_1Z = 6;
    constexpr const uint32_t PERMUTE_1W = 7;
}

// =================================================================================================
//
// Reinterpret operation between types
//

namespace Graphyte::Maths
{
    template <typename TTo, typename TFrom>
    mathinline TTo mathcall As(TFrom v) noexcept
    {
        return { v.V };
    }

    template <typename TTo>
    mathinline TTo mathcall As(Impl::NativeFloat32x4 v) noexcept
    {
        return { v };
    }
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
                static_cast<float>(static_cast<int32_t>(vint.U[0]))* scale,
                static_cast<float>(static_cast<int32_t>(vint.U[1]))* scale,
                static_cast<float>(static_cast<int32_t>(vint.U[2]))* scale,
                static_cast<float>(static_cast<int32_t>(vint.U[3]))* scale,
            } } };

        return result.V;
#elif GRAPHYTE_HW_NEON
        float const scale = 1.0F / static_cast<float>(1U << exponent);
        float32x4_t const r0 = vcvtq_f32_s32(vint);
        float32x4_t const r1 = vmulq_n_f32(r0, scale);
        return r1;
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = _mm_cvtepi32_ps(_mm_castps_si128(vint));
        uint32_t uscale = 0x3F800000U - (exponent << 23);
        __m128i const scale = _mm_set1_epi32(static_cast<int>(uscale));
        __m128 const r1 = _mm_mul_ps(r0, _mm_castsi128_ps(scale));
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
        float32x4_t const r0 = vmulq_n_f32(vfloat, static_cast<float>(1U << exponent));
        uint32x4_t const overflow = vcgtq_f32(r0, VEC4_INTMAX.V);
        int32x4_t const r1 = vcvtq_s32_f32(r0);
        uint32x4_t const r2 = vandq_u32(overflow, VEC4_MASK_ABS.V);
        uint32x4_t const r3 = vbicq_u32(r1, overflow);
        uint32x4_t const r4 = vorrq_u32(r3, r2);
        return vreinterpretq_f32_u32(r4);
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = _mm_set_ps1(static_cast<float>(1U << exponent));
        __m128 const r1 = _mm_mul_ps(r0, vfloat);
        __m128 const overflow = _mm_cmpgt_ps(r0, VEC4_INTMAX.V);
        __m128i const r2 = _mm_cvttps_epi32(r1);
        __m128 const r3 = _mm_and_ps(overflow, VEC4_MASK_ABS.V);
        __m128 const r4 = _mm_andnot_ps(overflow, _mm_castsi128_ps(r2));
        __m128 const r5 = _mm_or_ps(r4, r3);
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
        float const scale = 1.0F / static_cast<float>(1U << exponent);
        float32x4_t const r0 = vcvtq_f32_u32(vuint);
        float32x4_t const r1 = vmulq_n_f32(r0, scale);
        return r1;
#elif GRAPHYTE_HW_AVX
        __m128 const mask0 = _mm_and_ps(vuint, VEC4_NEGATIVE_ZERO.V);
        __m128 const r0 = _mm_xor_ps(vuint, mask0);
        __m128 const r1 = _mm_cvtepi32_ps(_mm_castps_si128(r0));
        __m128i const mask1 = _mm_srai_epi32(_mm_castps_si128(mask0), 31);
        __m128 const mask2 = _mm_and_ps(_mm_castsi128_ps(mask1), VEC4_UNSIGNED_FIX.V);
        __m128 const r2 = _mm_add_ps(r1, mask2);
        uint32_t const uscale = 0x3F800000U - (exponent << 23);
        __m128i const iscale = _mm_set1_epi32(static_cast<int>(uscale));
        __m128 const r3 = _mm_mul_ps(r2, _mm_castsi128_ps(iscale));
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
        float32x4_t const r0 = vmulq_n_f32(vfloat, static_cast<float>(1U << exponent));
        uint32x4_t const overflow = vcgtq_f32(r0, VEC4_UINTMAX.V);
        uint32x4_t const r1 = vcvtq_u32_f32(r0);
        uint32x4_t const r2 = vbicq_u32(r1, overflow);
        uint32x4_t const r3 = vorrq_u32(overflow, r2);
        return vreinterpretq_f32_u32(r3);
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = _mm_set_ps1(static_cast<float>(1U << exponent));
        __m128 const r1 = _mm_mul_ps(r0, vfloat);
        __m128 const r2 = _mm_max_ps(r1, _mm_setzero_ps());
        __m128 const overflow = _mm_cmpgt_ps(r2, VEC4_UINTMAX.V);
        __m128 const fix = VEC4_UNSIGNED_FIX.V;
        __m128 const mask = _mm_cmpge_ps(r2, fix);
        __m128 const max = _mm_and_ps(fix, mask);
        __m128 const r3 = _mm_sub_ps(r2, max);
        __m128i const r4 = _mm_cvttps_epi32(r3);
        __m128 const r5 = _mm_and_ps(mask, VEC4_NEGATIVE_ZERO.V);
        __m128 const r6 = _mm_xor_ps(_mm_castsi128_ps(r4), r5);
        __m128 const r7 = _mm_or_ps(r6, overflow);
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
        int32x4_t const fscale = vdupq_n_s32(c);
        float32x4_t const vfscale = vcvtq_f32_s32(fscale);
        uint32_t const uscale = 0x3F800000U - (exponent << 23);
        uint32x4_t const vuscale = vdupq_n_u32(uscale);
        float32x4_t const result = vmulq_f32(vfscale, vreinterpretq_f32_u32(vuscale));
        return result;
#elif GRAPHYTE_HW_AVX
        __m128i const fscale = _mm_set1_epi32(c);
        __m128 const vfscale = _mm_cvtepi32_ps(fscale);
        uint32_t uscale = 0x3F800000u - (exponent << 23);
        __m128i const vuscale = _mm_set1_epi32(static_cast<int>(uscale));
        __m128 const result = _mm_mul_ps(vfscale, _mm_castsi128_ps(vuscale));
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
        int32x4_t const r0 = vdupq_n_s32(c);
        float32x4_t const r1 = vreinterpretq_f32_s32(r0);
        return r1;
#elif GRAPHYTE_HW_AVX
        __m128i const r0 = _mm_set1_epi32(c);
        __m128 const r1 = _mm_castsi128_ps(r0);
        return r1;
#endif
    }
}


// =================================================================================================
//
// Select control mask
//

namespace Graphyte::Maths
{
    mathinline Bool4 mathcall SelectControl(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        GX_ASSERT(x < 2);
        GX_ASSERT(y < 2);
        GX_ASSERT(z < 2);
        GX_ASSERT(w < 4);

        uint32_t const control[2]{ Impl::SELECT_0, Impl::SELECT_1 };

        Impl::ConstUInt32x4 const result{ { {
                control[x],
                control[y],
                control[z],
                control[w],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const xyzw = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
            static_cast<int>(y),
            static_cast<int>(x)
        );
        __m128i const zero = _mm_setzero_si128();
        __m128i const control = _mm_cmpgt_epi32(xyzw, zero);
        __m128 const result = _mm_castsi128_ps(control);
        return { result };
#elif GRAPHYTE_HW_NEON
        int32x2_t const xy = vcreate_s32(static_cast<uint64_t>(x) | static_cast<uint64_t>(y) << 32);
        int32x2_t const zw = vcreate_s32(static_cast<uint64_t>(z) | static_cast<uint64_t>(w) << 32);
        int32x4_t const xyzw = vcombine_s32(xy, zw);
        int32x4_t const zero = vdupq_n_s32(0);
        int32x4_t const result = vcgtq_s32(xyzw, zero);
        return { vreinterpretq_f32_s32(result) };
#endif
    }

    mathinline Vector4 mathcall Select(Vector4 a, Vector4 b, Bool4 control) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] & ~control.V.U[0]) | (b.V.U[0] & control.V.U[0]),
                (a.V.U[1] & ~control.V.U[1]) | (b.V.U[1] & control.V.U[1]),
                (a.V.U[2] & ~control.V.U[2]) | (b.V.U[2] & control.V.U[2]),
                (a.V.U[3] & ~control.V.U[3]) | (b.V.U[3] & control.V.U[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_blendv_ps(a.V, b.V, control.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vbslq_f32(
            vreinterpretq_u32_f32(control.V),
            b.V,
            a.V
        );
        return { result };
#endif
    }

    mathinline float mathcall Select(float a, float b, float control) noexcept
    {
        return (control >= 0.0F) ? a : b;
    }
}


// =================================================================================================
//
// Permutations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Permute(Vector4 a, Vector4 b, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
        GX_ASSERT(x < 8);
        GX_ASSERT(y < 8);
        GX_ASSERT(z < 8);
        GX_ASSERT(w < 8);

#if GRAPHYTE_MATH_NO_INTRINSICS
        uint32_t const* vptrs[2]{
            reinterpret_cast<uint32_t const*>(&a.V),
            reinterpret_cast<uint32_t const*>(&b.V),
        };

        uint32_t const ix = (x & 3);
        uint32_t const iy = (y & 3);
        uint32_t const iz = (z & 3);
        uint32_t const iw = (w & 3);

        uint32_t const vx = (x >> 2);
        uint32_t const vy = (y >> 2);
        uint32_t const vz = (z >> 2);
        uint32_t const vw = (w >> 2);

        uint32_t const rx = vptrs[vx][ix];
        uint32_t const ry = vptrs[vy][iy];
        uint32_t const rz = vptrs[vz][iz];
        uint32_t const rw = vptrs[vw][iw];

        Impl::ConstUInt32x4 const result{ { {
                rx,
                ry,
                rz,
                rw,
            } } };


        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstUInt32x4 const threes{ { {
                3,
                3,
                3,
                3,
            } } };

        alignas(__m128) uint32_t elements[4]{ x, y, z, w };

        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&elements[0]));

        __m128i const select = _mm_cmpgt_epi32(control, _mm_castps_si128(threes.V));
        __m128i const permutation = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(control), threes.V));


        __m128 const shuffle1 = _mm_permutevar_ps(a.V, permutation);
        __m128 const shuffle2 = _mm_permutevar_ps(b.V, permutation);

        __m128 const masked1 = _mm_andnot_ps(_mm_castsi128_ps(select), shuffle1);
        __m128 const masked2 = _mm_and_ps(_mm_castsi128_ps(select), shuffle2);

        __m128 const result = _mm_or_ps(masked1, masked2);

        return { result };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_permute(a.V, b.V, x, y, z, w) };
#endif
    }

    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Permute(Vector4 a, Vector4 b) noexcept
    {
        static_assert((X < 8) && (Y < 8) && (Z < 8) && (W < 8));

        if constexpr (X == 0 && Y == 1 && Z == 2 && W == 3)
        {
            return a;
        }
        else if constexpr (X == 4 && Y == 5 && Z == 6 && W == 7)
        {
            return b;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            return Permute(a, b, X, Y, Z, W);
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_permute<X, Y, Z, W>(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_permute<X, Y, Z, W>(a.V, b.V) };
#endif
        }
    }
}


// =================================================================================================
//
// Swizzling
//

namespace Graphyte::Maths
{
    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    {
        static_assert((X < 4) && (Y < 4) && (Z < 4) && (W < 4));

        if constexpr (X == 0 && Y == 1 && Z == 2 && W == 3)
        {
            return v;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const result{ { {
                    v.V.F[X],
                    v.V.F[Y],
                    v.V.F[Z],
                    v.V.F[W],
                } } };
            return { result.V };
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_swizzle<X, Y, Z, W>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_swizzle<X, Y, Z, W>(v.V) };
#endif
        }
    }

    template <size_t X, size_t Y, size_t Z>
    mathinline Vector3 mathcall Swizzle(Vector3 v) noexcept
    {
        return As<Vector3>(Swizzle<X, Y, Z, X>(As<Vector4>(v)));
    }

    template <size_t X, size_t Y>
    mathinline Vector2 mathcall Swizzle(Vector2 v) noexcept
    {
        return As<Vector2>(Swizzle<X, Y, X, Y>(As<Vector2>(v)));
    }

    template <SwizzleMask M>
    mathinline Vector4 mathcall Swizzle(Vector4 v) noexcept
    {
        return Swizzle<
            (static_cast<size_t>(M) >> 0) & 0b11,
            (static_cast<size_t>(M) >> 2) & 0b11,
            (static_cast<size_t>(M) >> 4) & 0b11,
            (static_cast<size_t>(M) >> 6) & 0b11>(v);
    }

    mathinline Vector4 mathcall Swizzle(Vector4 v, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
        GX_ASSERT((x < 4) && (y < 4) && (z < 4) && (w < 4));
        GX_COMPILER_ASSUME((x < 4) && (y < 4) && (z < 4) && (w < 4));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[x],
                v.V.F[y],
                v.V.F[z],
                v.V.F[w],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        alignas(__m128i) uint32_t indices[4]{
            x,
            y,
            z,
            w,
        };

        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&indices[0]));
        __m128 const result = _mm_permutevar_ps(v.V, control);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_swizzle(v.V, x, y, z, w) };
#endif
    }

    mathinline Vector4 mathcall MergeXY(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0],
                b.V.U[0],
                a.V.U[1],
                b.V.U[1],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_unpacklo_ps(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vzipq_f32(a.V, b.V).val[0];
        return { result };
#endif
    }

    mathinline Vector4 mathcall MergeZW(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[2],
                b.V.U[2],
                a.V.U[3],
                b.V.U[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_unpackhi_ps(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vzipq_f32(a.V, b.V).val[1];
        return { result };
#endif
    }

    template <uint32_t Count>
    mathinline Vector4 mathcall ShiftLeft(Vector4 a, Vector4 b) noexcept
    {
        static_assert(Count < 4);
        return Permute<
            Count + 0,
            Count + 1,
            Count + 2,
            Count + 3>(a, b);
    }

    mathinline Vector4 mathcall ShiftLeft(Vector4 a, Vector4 b, uint32_t count) noexcept
    {
        GX_ASSERT(count < 4);
        return Permute(a, b, count + 0, count + 1, count + 2, count + 3);
    }

    template <uint32_t Count>
    mathinline Vector4 mathcall RotateLeft(Vector4 v) noexcept
    {
        static_assert(Count < 4);

        return Swizzle<
            (Count + 0) & 0b11,
            (Count + 1) & 0b11,
            (Count + 2) & 0b11,
            (Count + 3) & 0b11>(v);
    }

    mathinline Vector4 mathcall RotateLeft(Vector4 v, uint32_t count) noexcept
    {
        GX_ASSERT(count < 4);
        return Swizzle(v, (count + 0) & 0b11, (count + 1) & 0b11, (count + 2) & 0b11, (count + 3) & 0b11);
    }

    template <uint32_t Count>
    mathinline Vector4 mathcall RotateRight(Vector4 v) noexcept
    {
        static_assert(Count < 4);
        return Swizzle<
            (4 - Count) & 0b11,
            (5 - Count) & 0b11,
            (6 - Count) & 0b11,
            (7 - Count) & 0b11>(v);
    }

    mathinline Vector4 mathcall RotateRight(Vector4 v, uint32_t count) noexcept
    {
        GX_ASSERT(count < 4);
        return Swizzle(v, (4 - count) & 0b11, (5 - count) & 0b11, (6 - count) & 0b11, (7 - count) & 0b11);
    }

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
        __m128 const result = _mm_hadd_ps(partial, partial);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const partial = vpaddq_f32(v.V, v.V);
        float32x4_t const result = vpaddq_f32(partial, partial);
        return { result };
#endif
    }
}


// =================================================================================================
//
// Vector insertion
//

namespace Graphyte::Maths
{
    template <bool X, bool Y, bool Z, bool W>
    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b) noexcept
    {
        return Permute<
            0 + (X ? 4 : 0),
            1 + (Y ? 4 : 0),
            2 + (Z ? 4 : 0),
            3 + (W ? 4 : 0)>(a, b);
    }

    template <InsertMask Mask>
    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b) noexcept
    {
        constexpr bool x = ((static_cast<uint32_t>(Mask) >> 3) & 1) != 0;
        constexpr bool y = ((static_cast<uint32_t>(Mask) >> 2) & 1) != 0;
        constexpr bool z = ((static_cast<uint32_t>(Mask) >> 1) & 1) != 0;
        constexpr bool w = ((static_cast<uint32_t>(Mask) >> 0) & 0) != 0;

        return Premute<x, y, z, w>(a, b);
    }

    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b, bool x, bool y, bool z, bool w) noexcept
    {
        Bool4 const control = SelectControl(
            x ? 1 : 0,
            y ? 1 : 0,
            z ? 1 : 0,
            w ? 1 : 0
            );

        return Select(a, b, control);
    }

    mathinline Vector4 mathcall Insert(Vector4 a, Vector4 b, uint32_t rotate_left_count, bool x, bool y, bool z, bool w) noexcept
    {
        Bool4 const control = SelectControl(
            x ? 1 : 0,
            y ? 1 : 0,
            z ? 1 : 0,
            w ? 1 : 0
            );


        return Select(a, Maths::RotateLeft(b, rotate_left_count), control);
    }
}


// =================================================================================================
//
// Type conversion operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall To(float x, Vector3 yzw) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                yzw.V.F[0],
                yzw.V.F[1],
                yzw.V.F[2],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [_, vx, vy, vz]
        float32x4_t const wxyz = Impl::neon_swizzle<3, 0, 1, 2>(yzw.V);
        // = [x, vx, vy, vz]
        float32x4_t const result = vsetq_lane_f32(x, wxyz, 0);
        return { result };
#elif GRAPHYTE_HW_AVX
        // = [_, vx, vy, vz]
        __m128 const wxyz = _mm_permute_ps(yzw.V, _MM_SHUFFLE(2, 1, 0, 3));
        // = [x, _, _, _]
        __m128 const xxxx = _mm_set_ss(x);
        // = [x, vx, vy, vz]
        __m128 const result = _mm_move_ss(wxyz, xxxx);
        return { result };
#endif
    }

    mathinline Vector4 mathcall To(Vector3 xyz, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                xyz.V.F[0],
                xyz.V.F[1],
                xyz.V.F[2],
                w,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const xyzw = vsetq_lane_f32(w, xyz.V, 3);
        return { xyzw };
#elif GRAPHYTE_HW_AVX
        // = [w, _, _, _]
        __m128 const wwww = _mm_set_ss(w);
        // = [vx, vy, vz, w]
        __m128 const result = _mm_insert_ps(xyz.V, wwww, 0x30);
        return { result };
#endif
    }

    mathinline Vector4 mathcall To(float x, float y, Vector2 zw) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                zw.V.F[0],
                zw.V.F[1],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [x, y]
        float32x2_t const r0 = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32)
        );
        // = [vx, vy]
        float32x4_t const r1 = vget_high_f32(zw.V);
        // = [x, y, vx, vy]
        return { vcombine_f32(r0, r1) };
#elif GRAPHYTE_HW_AVX
        // = [x, y, 0, 0]
        __m128 const r0 = _mm_set_ps(0.0f, 0.0f, y, x);
        // = [x, y, vx, vy]
        __m128 const r1 = _mm_shuffle_ps(r0, zw.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { r1 };
#endif
    }

    mathinline Vector4 mathcall To(float x, Vector2 yz, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                yz.V.F[0],
                yz.V.F[1],
                w,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [_, vx, vy, _]
        float32x4_t const r0 = Impl::neon_swizzle<0, 0, 1, 3>(yz.V);
        // = [x, vx, vy, _]
        float32x4_t const r1 = vsetq_lane_f32(x, r0, 0);
        // = [x, vx, vy, w]
        float32x4_t const r2 = vsetq_lane_f32(w, r1, 3);
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [_, vx, vy, _]
        __m128 const r0 = _mm_permute_ps(yz.V, _MM_SHUFFLE(3, 1, 0, 0));
        // = [x, vx, vy, _]
        __m128 const r1 = _mm_insert_ps(r0, _mm_set_ps1(x), 0x00);
        // = [x, vx, vy, w]
        __m128 const r2 = _mm_insert_ps(r1, _mm_set_ps1(w), 0x30);
        return { r2 };
#endif
    }

    mathinline Vector4 mathcall To(Vector2 xy, float z, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                xy.V.F[0],
                xy.V.F[1],
                z,
                w,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [vx, vy]
        float32x2_t const r0 = vget_low_f32(xy.V);

        // = [z, w]
        float32x2_t const r1 = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&w)) << 32)
        );

        // = [vx, vy, z, w]
        return { vcombine_f32(r0, r1) };
#elif GRAPHYTE_HW_AVX
        // = [z, w, _, _]
        __m128 const r0 = _mm_set_ps(0.0f, 0.0f, w, z);
        // = [vx, vy, z, w]
        __m128 const r1 = _mm_shuffle_ps(r0, xy.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { r1 };
#endif
    }

    mathinline Vector4 mathcall To(Vector2 xy, Vector2 zw) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                xy.V.F[0],
                xy.V.F[1],
                zw.V.F[0],
                zw.V.F[1],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [vx, vy]
        float32x2_t const r0 = vget_low_f32(xy.V);
        // = [vz, vw]
        float32x2_t const r1 = vget_low_f32(zw.V);
        // = [vx, vy, vz, vw]
        float32x4_t const r2 = vcombine_f32(r0, r1);
        return { r2 };
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = _mm_shuffle_ps(xy.V, zw.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { r0 };
#endif
    }

    mathinline Vector3 mathcall To(float x, Vector2 yz) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                yz.V.F[0],
                yz.V.F[1],
                0.0f,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [_, vy, vz, _]
        float32x4_t const r0 = Impl::neon_swizzle<0, 0, 1, 1>(yz.V);
        // = [x, vy, vz, _]
        float32x4_t const r1 = vsetq_lane_f32(x, r0, 0);
        // = [x, vy, vz, 0]
        float32x4_t const r2 = vreinterpretq_f32_u32(vandq_u32(
            vreinterpretq_u32_f32(r1),
            vreinterpretq_u32_f32(Impl::VEC4_MASK_SELECT_1110.V)
        ));
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [_, vy, vz, _]
        __m128 const r0 = _mm_permute_ps(yz.V, _MM_SHUFFLE(1, 1, 0, 0));
        // = [x, vy, vz, _]
        __m128 const r1 = _mm_insert_ps(r0, _mm_set_ps1(x), 0x00);
        // = [x, vy, vz, 0]
        __m128 const r2 = _mm_and_ps(r1, Impl::VEC4_MASK_SELECT_1110.V);
        return { r2 };
#endif
    }

    mathinline Vector3 mathcall To(Vector2 xy, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                xy.V.F[0],
                xy.V.F[1],
                z,
                0.0f,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [vx, vy]
        float32x2_t const r0 = vget_low_f32(xy.V);
        // = [z, 0]
        float32x2_t const r1 = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z))
        );
        // = [vx, vy, z, 0]
        float32x4_t const r2 = vcombine_f32(r0, r1);
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [z, 0, 0, 0]
        __m128 const r0 = _mm_set_ps1(z);
        // = [vx, vy, z, 0]
        __m128 const r1 = _mm_shuffle_ps(xy.V, r0, _MM_SHUFFLE(1, 0, 1, 0));
        return { r1 };
#endif
    }
}

// =================================================================================================
//
// Load / store operations
//

namespace Graphyte::Maths
{
    template <typename D, typename S>
    D Load(S const* source) noexcept = delete;

    template <typename D, typename S>
    void Store(D* destination, S source) noexcept = delete;

    template <>
    mathinline Vector4 mathcall Load<Vector4, Float4A>(Float4A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                source->W,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps(reinterpret_cast<float const*>(source)) };
#endif
    }

    template <>
    mathinline Plane mathcall Load<Plane, Float4A>(Float4A const* source) noexcept
    {
        return { Load<Vector4, Float4A>(source).V };
    }

    template <>
    mathinline Sphere mathcall Load<Sphere, Float4A>(Float4A const* source) noexcept
    {
        return { Load<Vector4, Float4A>(source).V };
    }

    template <>
    mathinline Quaternion mathcall Load<Quaternion, Float4A>(Float4A const* source) noexcept
    {
        return { Load<Vector4, Float4A>(source).V };
    }

    template <>
    mathinline void mathcall Store<Float4A, Vector4>(Float4A* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <>
    mathinline void mathcall Store<Float4A, Plane>(Float4A* destination, Plane v) noexcept
    {
        Store<Float4A, Vector4>(destination, { v.V });
    }

    template <>
    mathinline void mathcall Store<Float4A, Sphere>(Float4A* destination, Sphere v) noexcept
    {
        Store<Float4A, Vector4>(destination, { v.V });
    }

    template <>
    mathinline void mathcall Store<Float4A, Quaternion>(Float4A* destination, Quaternion v) noexcept
    {
        Store<Float4A, Vector4>(destination, { v.V });
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, Float4>(Float4 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                source->W,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_loadu_ps(reinterpret_cast<float const*>(source)) };
#endif
    }

    template <>
    mathinline Plane mathcall Load<Plane, Float4>(Float4 const* source) noexcept
    {
        return { Load<Vector4, Float4>(source).V };
    }

    template <>
    mathinline Sphere mathcall Load<Sphere, Float4>(Float4 const* source) noexcept
    {
        return { Load<Vector4, Float4>(source).V };
    }

    template <>
    mathinline Quaternion mathcall Load<Quaternion, Float4>(Float4 const* source) noexcept
    {
        return { Load<Vector4, Float4>(source).V };
    }

    template <>
    mathinline void mathcall Store<Float4, Vector4>(Float4* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <>
    mathinline void mathcall Store<Float4, Plane>(Float4* destination, Plane v) noexcept
    {
        Store<Float4, Vector4>(destination, { v.V });
    }

    template <>
    mathinline void mathcall Store<Float4, Sphere>(Float4* destination, Sphere v) noexcept
    {
        Store<Float4, Vector4>(destination, { v.V });
    }

    template <>
    mathinline void mathcall Store<Float4, Quaternion>(Float4* destination, Quaternion v) noexcept
    {
        Store<Float4, Vector4>(destination, { v.V });
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, Float3A>(Float3A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xyzn = _mm_load_ps(reinterpret_cast<float const*>(source));
        __m128 const result = _mm_and_ps(xyzn, Impl::VEC4_MASK_COMPONENTS_3.V);
        return { result };
#endif
    }

    template <>
    mathinline Vector3 mathcall Load<Vector3, Float3A>(Float3A const* source) noexcept
    {
        return { Load<Vector4, Float3A>(source).V };
    }

    template <>
    mathinline void mathcall Store<Float3A, Vector4>(Float3A* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(&destination->Z, zzzz);
#endif
    }

    template <>
    mathinline void mathcall Store<Float3A, Vector3>(Float3A* destination, Vector3 v) noexcept
    {
        Store<Float3A, Vector4>(destination, { v.V });
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, Float3>(Float3 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                source->Z,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        __m128 const v_z = _mm_load_ss(&source->Z);
        __m128 const v_xy = _mm_unpacklo_ps(v_x, v_y);
        __m128 const v_xyz = _mm_movelh_ps(v_xy, v_z);
        return { v_xyz };
#endif
    }

    template <>
    mathinline Vector3 mathcall Load<Vector3, Float3>(Float3 const* source) noexcept
    {
        return { Load<Vector4, Float3>(source).V };
    }

    template <>
    mathinline void mathcall Store<Float3, Vector4>(Float3* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, yyyy);
        _mm_store_ss(&destination->Z, zzzz);
#endif
    }

    template <>
    mathinline void mathcall Store<Float3, Vector3>(Float3* destination, Vector3 v) noexcept
    {
        Store<Float3, Vector4>(destination, { v.V });
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, Float2A>(Float2A const* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_xy = _mm_loadl_epi64(reinterpret_cast<__m128i const*>(source));
        return { _mm_castsi128_ps(v_xy) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Load<Vector3, Float2A>(Float2A const* source) noexcept
    {
        return { Load<Vector4, Float2A>(source).V };
    }

    template <>
    mathinline Vector2 mathcall Load<Vector2, Float2A>(Float2A const* source) noexcept
    {
        return { Load<Vector4, Float2A>(source).V };
    }

    template <>
    mathinline void mathcall Store<Float2A, Vector4>(Float2A* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    template <>
    mathinline void mathcall Store<Float2A, Vector3>(Float2A* destination, Vector3 v) noexcept
    {
        Store<Float2A, Vector4>(destination, { v.V });
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, Float2>(Float2 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                source->X,
                source->Y,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_x = _mm_load_ss(&source->X);
        __m128 const v_y = _mm_load_ss(&source->Y);
        __m128 const result = _mm_unpacklo_ps(v_x, v_y);
        return { result };
#endif
    }

    template <>
    mathinline Vector3 mathcall Load<Vector3, Float2>(Float2 const* source) noexcept
    {
        return { Load<Vector4, Float2>(source).V };
    }

    template <>
    mathinline Vector2 mathcall Load<Vector2, Float2>(Float2 const* source) noexcept
    {
        return { Load<Vector4, Float2>(source).V };
    }

    template <>
    mathinline void mathcall Store<Float2, Vector4>(Float2* destination, Vector4 v) noexcept
    {

        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
#endif
    }

    template <>
    mathinline void mathcall Store<Float2, Vector3>(Float2* destination, Vector3 v) noexcept
    {
        Store<Float2, Vector4>(destination, { v.V });
    }

    template <>
    mathinline void mathcall Store<Float2, Vector2>(Float2* destination, Vector2 v) noexcept
    {
        Store<Float2, Vector4>(destination, { v.V });
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, float>(float const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                *source,
                0.0F,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ss(source) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Load<Vector3, float>(float const* source) noexcept
    {
        return { Load<Vector4, float>(source).V };
    }

    template <>
    mathinline Vector2 mathcall Load<Vector2, float>(float const* source) noexcept
    {
        return { Load<Vector4, float>(source).V };
    }

    template <>
    mathinline void mathcall Store<float, Vector4>(float* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*destination) = v.V.F[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(destination, v.V);
#endif
    }

    template <>
    mathinline void mathcall Store<float, Vector3>(float* destination, Vector3 v) noexcept
    {
        Store<float, Vector4>(destination, { v.V });
    }

    template <>
    mathinline void mathcall Store<float, Vector2>(float* destination, Vector2 v) noexcept
    {
        Store<float, Vector4>(destination, { v.V });
    }
}

namespace Graphyte::Maths
{
    template <>
    mathinline Vector4 mathcall Load<Vector4, Half4>(Half4 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
                FromHalf(source->X),
                FromHalf(source->Y),
                FromHalf(source->Z),
                FromHalf(source->W),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_loadl_epi64(reinterpret_cast<__m128i const*>(source));
        __m128 const h1 = _mm_cvtph_ps(_mm_castps_si128(h0));
        return { h1 };
#endif
    }

    template <>
    mathinline void mathcall Store<Half4, Vector4>(Half4* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const components{
            .V = v.V
        };

        destination->X = ToHalf(components.F[0]);
        destination->Y = ToHalf(components.F[1]);
        destination->Z = ToHalf(components.F[2]);
        destination->W = ToHalf(components.F[3]);
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_cvtps_ph(v.V, 0);
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), h0);
#endif
    }

    template <>
    mathinline Vector4 mathcall Load<Vector4, Half2>(Half2 const* source) noexcept
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
                FromHalf(source->X),
                FromHalf(source->Y),
                0.0f,
                0.0f,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_load_ss(reinterpret_cast<float const*>(source));
        __m128 const h1 = _mm_cvtph_ps(_mm_castps_si128(h0));
        return { h1 };
#endif
    }

    template <>
    mathinline void mathcall Store<Half2, Vector4>(Half2* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const components{
            .V = v.V
        };

        destination->X = ToHalf(components.F[0]);
        destination->Y = ToHalf(components.F[1]);
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_cvtps_ph(v.V, 0);
        __m128 const h1 = _mm_castsi128_ps(h0);
        _mm_store_ss(reinterpret_cast<float*>(destination), h1);
#endif
    }
}


// =================================================================================================
//
// Component getters and setters
//

namespace Graphyte::Maths
{
    template <typename T>
    T SplatX(T v) noexcept = delete;

    template <>
    mathinline Vector4 mathcall SplatX<Vector4>(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[0];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcastss_ps(v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_low_f32(v.V), 0) };
#endif
    }

    template <>
    mathinline Vector3 mathcall SplatX<Vector3>(Vector3 v) noexcept
    {
        return { SplatX<Vector4>({ v.V }).V };
    }

    template <>
    mathinline Vector2 mathcall SplatX<Vector2>(Vector2 v) noexcept
    {
        return { SplatX<Vector4>({ v.V }).V };
    }

    template <typename T>
    T SplatY(T v) noexcept = delete;

    template <>
    mathinline Vector4 mathcall SplatY<Vector4>(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[1];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_low_f32(v.V), 1) };
#endif
    }

    template <>
    mathinline Vector3 mathcall SplatY<Vector3>(Vector3 v) noexcept
    {
        return { SplatY<Vector4>({ v.V }).V };
    }

    template <>
    mathinline Vector2 mathcall SplatY<Vector2>(Vector2 v) noexcept
    {
        return { SplatY<Vector4>({ v.V }).V };
    }

    template <typename T>
    T SplatZ(T v) noexcept = delete;

    template <>
    mathinline Vector4 mathcall SplatZ<Vector4>(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[2];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_high_f32(v.V), 0) };
#endif
    }

    template <>
    mathinline Vector3 mathcall SplatZ<Vector3>(Vector3 v) noexcept
    {
        return { SplatZ<Vector4>({ v.V }).V };
    }

    template <typename T>
    T SplatW(T v) noexcept = delete;

    template <>
    mathinline Vector4 mathcall SplatW<Vector4>(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[3];
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_high_f32(v.V), 1) };
#endif
    }

    mathinline float mathcall GetByIndex(Vector4 v, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[index];
#else
        Impl::ConstFloat32x4 result;
        result.V = v.V;
        return result.F[index];
#endif
    }


    mathinline Vector4 mathcall SetByIndex(Vector4 v, float value, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V = v.V;
        result.F[index] = value;
        return { result.V };
    }

    mathinline void mathcall GetByIndex(float* result, Vector4 v, size_t index) noexcept
    {
        GX_ASSERT(result != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[index];
#else
        Impl::ConstFloat32x4 r;
        r.V = v.V;
        (*result) = r.F[index];
#endif
    }

    mathinline Vector4 mathcall SetByIndex(Vector4 v, float const* value, size_t index)
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V = v.V;
        result.F[index] = (*value);
        return { result.V };
    }

    mathinline float mathcall GetX(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 0);
#endif
    }

    mathinline float mathcall GetX(Vector3 v) noexcept
    {
        return GetX(Vector4{ v.V });
    }

    mathinline float mathcall GetX(Vector2 v) noexcept
    {
        return GetX(Vector4{ v.V });
    }

    mathinline float mathcall GetX(Vector1 v) noexcept
    {
        return GetX(Vector4{ v.V });
    }

    mathinline float mathcall GetX(Quaternion v) noexcept
    {
        return GetX(Vector4{ v.V });
    }

    mathinline float mathcall GetX(Plane v) noexcept
    {
        return GetX(Vector4{ v.V });
    }

    mathinline float mathcall GetY(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 1);
#endif
    }

    mathinline float mathcall GetY(Vector3 v) noexcept
    {
        return GetY(Vector4{ v.V });
    }

    mathinline float mathcall GetY(Vector2 v) noexcept
    {
        return GetY(Vector4{ v.V });
    }

    mathinline float mathcall GetY(Quaternion v) noexcept
    {
        return GetY(Vector4{ v.V });
    }

    mathinline float mathcall GetY(Plane v) noexcept
    {
        return GetY(Vector4{ v.V });
    }

    mathinline float mathcall GetZ(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 2);
#endif
    }

    mathinline float mathcall GetZ(Vector3 v) noexcept
    {
        return GetZ(Vector4{ v.V });
    }

    mathinline float mathcall GetZ(Quaternion v) noexcept
    {
        return GetZ(Vector4{ v.V });
    }

    mathinline float mathcall GetZ(Plane v) noexcept
    {
        return GetZ(Vector4{ v.V });
    }

    mathinline float mathcall GetW(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 3);
#endif
    }

    mathinline float mathcall GetW(Quaternion v) noexcept
    {
        return GetW(Vector4{ v.V });
    }

    mathinline float mathcall GetW(Plane v) noexcept
    {
        return GetW(Vector4{ v.V });
    }

    mathinline void mathcall GetX(float* result, Vector4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[0];
#elif GRAPHYTE_HW_NEON
        (*result) = vgetq_lane_f32(v.V, 0);
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(result, v.V);
#endif
    }

    mathinline void mathcall GetX(float* result, Vector3 v) noexcept
    {
        GetX(result, Vector4{ v.V });
    }

    mathinline void mathcall GetX(float* result, Vector2 v) noexcept
    {
        GetX(result, Vector4{ v.V });
    }

    mathinline void mathcall GetX(float* result, Vector1 v) noexcept
    {
        GetX(result, Vector4{ v.V });
    }

    mathinline void mathcall GetX(float* result, Quaternion v) noexcept
    {
        GetX(result, Vector4{ v.V });
    }

    mathinline void mathcall GetX(float* result, Plane v) noexcept
    {
        GetX(result, Vector4{ v.V });
    }

    mathinline void mathcall GetY(float* result, Vector4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[1];
#elif GRAPHYTE_HW_NEON
        (*result) = vgetq_lane_f32(v.V, 1);
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 1);
#endif
    }

    mathinline void mathcall GetY(float* result, Vector3 v) noexcept
    {
        GetY(result, Vector4{ v.V });
    }

    mathinline void mathcall GetY(float* result, Vector2 v) noexcept
    {
        GetY(result, Vector4{ v.V });
    }

    mathinline void mathcall GetY(float* result, Quaternion v) noexcept
    {
        GetY(result, Vector4{ v.V });
    }

    mathinline void mathcall GetY(float* result, Plane v) noexcept
    {
        GetY(result, Vector4{ v.V });
    }

    mathinline void mathcall GetZ(float* result, Vector4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[2];
#elif GRAPHYTE_HW_NEON
        (*result) = vgetq_lane_f32(v.V, 2);
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 2);
#endif
    }

    mathinline void mathcall GetZ(float* result, Vector3 v) noexcept
    {
        GetZ(result, Vector4{ v.V });
    }

    mathinline void mathcall GetZ(float* result, Quaternion v) noexcept
    {
        GetZ(result, Vector4{ v.V });
    }

    mathinline void mathcall GetZ(float* result, Plane v) noexcept
    {
        GetZ(result, Vector4{ v.V });
    }

    mathinline void mathcall GetW(float* result, Vector4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[3];
#elif GRAPHYTE_HW_NEON
        (*result) = vgetq_lane_f32(v.V, 3);
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 3);
#endif
    }

    mathinline void mathcall GetW(float* result, Quaternion v) noexcept
    {
        GetW(result, Vector4{ v.V });
    }

    mathinline void mathcall GetW(float* result, Plane v) noexcept
    {
        GetW(result, Vector4{ v.V });
    }

    mathinline Vector4 mathcall SetX(Vector4 v, float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                value,
                v.V.F[1],
                v.V.F[2],
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_set_ss(value);
        __m128 const result = _mm_move_ss(v.V, xxxx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 0) };
#endif
    }

    mathinline Vector3 mathcall SetX(Vector3 v, float value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Vector2 mathcall SetX(Vector2 v, float value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Vector1 mathcall SetX(Vector1 v, float value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Quaternion mathcall SetX(Quaternion v, float value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetX(Plane v, float value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetY(Vector4 v, float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                value,
                v.V.F[2],
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, yyyy, 0x10);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 1) };
#endif
    }

    mathinline Vector3 mathcall SetY(Vector3 v, float value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Vector2 mathcall SetY(Vector2 v, float value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Quaternion mathcall SetY(Quaternion v, float value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetY(Plane v, float value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetZ(Vector4 v, float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                value,
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, zzzz, 0x20);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 2) };
#endif
    }

    mathinline Vector3 mathcall SetZ(Vector3 v, float value) noexcept
    {
        return { SetZ(Vector4{ v.V }, value).V };
    }

    mathinline Quaternion mathcall SetZ(Quaternion v, float value) noexcept
    {
        return { SetZ(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetZ(Plane v, float value) noexcept
    {
        return { SetZ(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetW(Vector4 v, float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                v.V.F[2],
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, wwww, 0x30);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 3) };
#endif
    }

    mathinline Quaternion mathcall SetW(Quaternion v, float value) noexcept
    {
        return { SetW(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetW(Plane v, float value) noexcept
    {
        return { SetW(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetX(Vector4 v, float const* value) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                *value,
                v.V.F[1],
                v.V.F[2],
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_load_ss(value);
        __m128 const result = _mm_move_ss(v.V, xxxx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 0) };
#endif
    }

    mathinline Vector3 mathcall SetX(Vector3 v, float const* value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Vector2 mathcall SetX(Vector2 v, float const* value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Vector1 mathcall SetX(Vector1 v, float const* value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Quaternion mathcall SetX(Quaternion v, float const* value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetX(Plane v, float const* value) noexcept
    {
        return { SetX(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetY(Vector4 v, float const* value) noexcept
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                *value,
                v.V.F[2],
                v.V.F[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_yxzw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const yyyy = _mm_load_ss(value);
        __m128 const n_yxzw = _mm_move_ss(o_yxzw, yyyy);
        __m128 const xyzw = _mm_permute_ps(n_yxzw, _MM_SHUFFLE(3, 2, 0, 1));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 1) };
#endif
    }

    mathinline Vector3 mathcall SetY(Vector3 v, float const* value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Vector2 mathcall SetY(Vector2 v, float const* value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Quaternion mathcall SetY(Quaternion v, float const* value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetY(Plane v, float const* value) noexcept
    {
        return { SetY(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetZ(Vector4 v, float const* value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                *value,
                v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_zyxw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const zzzz = _mm_load_ss(value);
        __m128 const n_zyxw = _mm_move_ss(o_zyxw, zzzz);
        __m128 const xyzw = _mm_permute_ps(n_zyxw, _MM_SHUFFLE(3, 0, 1, 2));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 2) };
#endif
    }

    mathinline Vector3 mathcall SetZ(Vector3 v, float const* value) noexcept
    {
        return { SetZ(Vector4{ v.V }, value).V };
    }

    mathinline Quaternion mathcall SetZ(Quaternion v, float const* value) noexcept
    {
        return { SetZ(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetZ(Plane v, float const* value) noexcept
    {
        return { SetZ(Vector4{ v.V }, value).V };
    }

    mathinline Vector4 mathcall SetW(Vector4 v, float const* value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0],
                v.V.F[1],
                v.V.F[2],
                *value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_wyzx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        __m128 const wwww = _mm_load_ss(value);
        __m128 const n_wyzx = _mm_move_ss(o_wyzx, wwww);
        __m128 const xyzw = _mm_permute_ps(n_wyzx, _MM_SHUFFLE(0, 2, 1, 3));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 3) };
#endif
    }

    mathinline Quaternion mathcall SetW(Quaternion v, float const* value) noexcept
    {
        return { SetW(Vector4{ v.V }, value).V };
    }

    mathinline Plane mathcall SetW(Plane v, float const* value) noexcept
    {
        return { SetW(Vector4{ v.V }, value).V };
    }
}

// =================================================================================================
//
// Getters and setters for bitwisable vectors
//

namespace Graphyte::Maths
{
    mathinline uint32_t mathcall GetByIndex(Bool4 v, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[index];
#elif GRAPHYTE_HW_AVX
        Impl::ConstUInt32x4 result;
        result.V = v.V;
        return result.U[index];
#endif
    }

    mathinline Bool4 mathcall SetUIntByIndex(Bool4 v, uint32_t value, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstUInt32x4 result;
        result.V = v.V;
        result.U[index] = value;
        return { result.V };
    }

    mathinline void mathcall GetUIntByIndex(uint32_t* result, Bool4 v, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[index];
#elif GRAPHYTE_HW_AVX
        Impl::ConstUInt32x4 r;
        r.V = v.V;
        (*result) = r.U[index];
#endif
    }

    mathinline Bool4 mathcall SetUIntByIndex(Bool4 v, uint32_t const* value, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstUInt32x4 result;
        result.V = v.V;
        result.U[index] = (*value);
        return { result.V };
    }

    mathinline uint32_t mathcall GetX(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[0];
#elif GRAPHYTE_HW_AVX
        return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(v.V)));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 0);
#endif
    }

    mathinline uint32_t mathcall GetX(Bool3 v) noexcept
    {
        return GetX(Bool4{ v.V });
    }

    mathinline uint32_t mathcall GetX(Bool2 v) noexcept
    {
        return GetX(Bool4{ v.V });
    }

    mathinline uint32_t mathcall GetX(Bool1 v) noexcept
    {
        return GetX(Bool4{ v.V });
    }

    mathinline uint32_t mathcall GetY(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[1];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(r, 1));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 1);
#endif
    }

    mathinline uint32_t mathcall GetY(Bool3 v) noexcept
    {
        return GetY(Bool4{ v.V });
    }

    mathinline uint32_t mathcall GetY(Bool2 v) noexcept
    {
        return GetY(Bool4{ v.V });
    }

    mathinline uint32_t mathcall GetZ(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[2];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(r, 2));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 2);
#endif
    }

    mathinline uint32_t GetZ(Bool3 v) noexcept
    {
        return GetZ(Bool4{ v.V });
    }

    mathinline uint32_t mathcall GetW(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[3];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(r, 3));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 3);
#endif
    }

    mathinline void mathcall GetX(uint32_t* result, Bool4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(reinterpret_cast<float*>(result), v.V);
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 0);
#endif
    }

    mathinline void mathcall GetX(uint32_t* result, Bool3 v) noexcept
    {
        GetX(result, Bool4{ v.V });
    }

    mathinline void mathcall GetX(uint32_t* result, Bool2 v) noexcept
    {
        GetX(result, Bool4{ v.V });
    }

    mathinline void mathcall GetX(uint32_t* result, Bool1 v) noexcept
    {
        GetX(result, Bool4{ v.V });
    }

    mathinline void mathcall GetY(uint32_t* result, Bool4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[1];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        (*result) = static_cast<uint32_t>(_mm_extract_epi32(r, 1));
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 1);
#endif
    }

    mathinline void mathcall GetY(uint32_t* result, Bool3 v) noexcept
    {
        GetY(result, Bool4{ v.V });
    }

    mathinline void mathcall GetY(uint32_t* result, Bool2 v) noexcept
    {
        GetY(result, Bool4{ v.V });
    }

    mathinline void mathcall GetZ(uint32_t* result, Bool4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[2];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        (*result) = static_cast<uint32_t>(_mm_extract_epi32(r, 2));
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 2);
#endif
    }

    mathinline void mathcall GetZ(uint32_t* result, Bool3 v) noexcept
    {
        GetZ(result, Bool4{ v.V });
    }

    mathinline void mathcall GetW(uint32_t* result, Bool4 v) noexcept
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[3];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        (*result) = static_cast<uint32_t>(_mm_extract_epi32(r, 3));
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 3);
#endif
    }

    mathinline Bool4 mathcall SetX(Bool4 v, uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                value,
                v.V.U[1],
                v.V.U[2],
                v.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const xxxx = _mm_cvtsi32_si128(static_cast<int>(value));
        __m128 const result = _mm_move_ss(v.V, _mm_castsi128_ps(xxxx));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 0) };
#endif
    }

    mathinline Bool3 mathcall SetX(Bool3 v, uint32_t value) noexcept
    {
        return Bool3{ SetX(Bool4{ v.V }, value).V };
    }

    mathinline Bool2 mathcall SetX(Bool2 v, uint32_t value) noexcept
    {
        return Bool2{ SetX(Bool4{ v.V }, value).V };
    }

    mathinline Bool1 mathcall SetX(Bool1 v, uint32_t value) noexcept
    {
        return Bool1{ SetX(Bool4{ v.V }, value).V };
    }

    mathinline Bool4 mathcall SetY(Bool4 v, uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                v.V.U[0],
                value,
                v.V.U[2],
                v.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const vu = _mm_castps_si128(v.V);
        __m128i const vy = _mm_insert_epi32(vu, static_cast<int>(value), 1);
        __m128 const result = _mm_castsi128_ps(vy);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 1) };
#endif
    }

    mathinline Bool3 mathcall SetY(Bool3 v, uint32_t value) noexcept
    {
        return Bool3{ SetY(Bool4{ v.V }, value).V };
    }

    mathinline Bool2 mathcall SetY(Bool2 v, uint32_t value) noexcept
    {
        return Bool2{ SetY(Bool4{ v.V }, value).V };
    }

    mathinline Bool4 mathcall SetZ(Bool4 v, uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                v.V.U[0],
                v.V.U[1],
                value,
                v.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const vu = _mm_castps_si128(v.V);
        __m128i const vz = _mm_insert_epi32(vu, static_cast<int>(value), 2);
        __m128 const result = _mm_castsi128_ps(vz);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 2) };
#endif
    }

    mathinline Bool3 mathcall SetZ(Bool3 v, uint32_t value) noexcept
    {
        return Bool3{ SetZ(Bool4{ v.V }, value).V };
    }

    mathinline Bool4 mathcall SetW(Bool4 v, uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                v.V.U[0],
                v.V.U[1],
                v.V.U[2],
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const vu = _mm_castps_si128(v.V);
        __m128i const vw = _mm_insert_epi32(vu, static_cast<int>(value), 3);
        __m128 const result = _mm_castsi128_ps(vw);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 3) };
#endif
    }

    mathinline Bool4 mathcall SetX(Bool4 v, uint32_t const* value) noexcept
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                *value,
                v.V.U[1],
                v.V.U[2],
                v.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const vx = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const result = _mm_move_ss(v.V, vx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 0) };
#endif
    }

    mathinline Bool3 mathcall SetX(Bool3 v, uint32_t const* value) noexcept
    {
        return Bool3{ SetX(Bool4{ v.V }, value).V };
    }

    mathinline Bool2 mathcall SetX(Bool2 v, uint32_t const* value) noexcept
    {
        return Bool2{ SetX(Bool4{ v.V }, value).V };
    }

    mathinline Bool1 mathcall SetX(Bool1 v, uint32_t const* value) noexcept
    {
        return Bool1{ SetX(Bool4{ v.V }, value).V };
    }

    mathinline Bool4 mathcall SetY(Bool4 v, uint32_t const* value) noexcept
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                v.V.U[0],
                *value,
                v.V.U[2],
                v.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yxzw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const yyyy = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const x_yxzw = _mm_move_ss(yxzw, yyyy);
        __m128 const result = _mm_permute_ps(x_yxzw, _MM_SHUFFLE(3, 2, 0, 1));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 1) };
#endif
    }

    mathinline Bool3 mathcall SetY(Bool3 v, uint32_t const* value) noexcept
    {
        return Bool3{ SetY(Bool4{ v.V }, value).V };
    }

    mathinline Bool2 mathcall SetY(Bool2 v, uint32_t const* value) noexcept
    {
        return Bool2{ SetY(Bool4{ v.V }, value).V };
    }

    mathinline Bool4 mathcall SetZ(Bool4 v, uint32_t const* value) noexcept
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                v.V.U[0],
                v.V.U[1],
                *value,
                v.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zyxw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const zzzz = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const z_zyxw = _mm_move_ss(zyxw, zzzz);
        __m128 const result = _mm_permute_ps(z_zyxw, _MM_SHUFFLE(3, 0, 1, 2));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 2) };
#endif
    }

    mathinline Bool3 mathcall SetZ(Bool3 v, uint32_t const* value) noexcept
    {
        return Bool3{ SetZ(Bool4{ v.V }, value).V };
    }

    mathinline Bool4 mathcall SetW(Bool4 v, uint32_t const* value) noexcept
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                v.V.U[0],
                v.V.U[1],
                v.V.U[2],
                *value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wyzx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        __m128 const wwww = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const w_wyzx = _mm_move_ss(wyzx, wwww);
        __m128 const result = _mm_permute_ps(w_wyzx, _MM_SHUFFLE(0, 2, 1, 3));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 3) };
#endif
    }
}

// =================================================================================================
//
// Constants
//

namespace Graphyte::Maths
{
    template <typename T> T UnitX() noexcept = delete;

    template <> mathinline Vector4 mathcall UnitX<Vector4>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_X.V }; }
    template <> mathinline Vector3 mathcall UnitX<Vector3>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_X.V }; }
    template <> mathinline Vector2 mathcall UnitX<Vector2>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_X.V }; }
    template <> mathinline Vector1 mathcall UnitX<Vector1>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_X.V }; }
    template <> mathinline Quaternion mathcall UnitX<Quaternion>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_X.V }; }

    template <typename T> T UnitY() noexcept = delete;

    template <> mathinline Vector4 mathcall UnitY<Vector4>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Y.V }; }
    template <> mathinline Vector3 mathcall UnitY<Vector3>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Y.V }; }
    template <> mathinline Vector2 mathcall UnitY<Vector2>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Y.V }; }
    template <> mathinline Quaternion mathcall UnitY<Quaternion>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Y.V }; }

    template <typename T> T UnitZ() noexcept = delete;

    template <> mathinline Vector4 mathcall UnitZ<Vector4>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Z.V }; }
    template <> mathinline Vector3 mathcall UnitZ<Vector3>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Z.V }; }
    template <> mathinline Quaternion mathcall UnitZ<Quaternion>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_Z.V }; }

    template <typename T> T UnitW() noexcept = delete;

    template <> mathinline Vector4 mathcall UnitW<Vector4>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_W.V }; }
    template <> mathinline Quaternion mathcall UnitW<Quaternion>() noexcept { return { Impl::VEC4_POSITIVE_UNIT_W.V }; }

    template <typename T> T NegativeUnitX() noexcept = delete;

    template <> mathinline Vector4 mathcall NegativeUnitX<Vector4>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_X.V }; }
    template <> mathinline Vector3 mathcall NegativeUnitX<Vector3>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_X.V }; }
    template <> mathinline Vector2 mathcall NegativeUnitX<Vector2>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_X.V }; }
    template <> mathinline Vector1 mathcall NegativeUnitX<Vector1>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_X.V }; }
    template <> mathinline Quaternion mathcall NegativeUnitX<Quaternion>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_X.V }; }

    template <typename T> T NegativeUnitY() noexcept = delete;

    template <> mathinline Vector4 mathcall NegativeUnitY<Vector4>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Y.V }; }
    template <> mathinline Vector3 mathcall NegativeUnitY<Vector3>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Y.V }; }
    template <> mathinline Vector2 mathcall NegativeUnitY<Vector2>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Y.V }; }
    template <> mathinline Quaternion mathcall NegativeUnitY<Quaternion>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Y.V }; }

    template <typename T> T NegativeUnitZ() noexcept = delete;

    template <> mathinline Vector4 mathcall NegativeUnitZ<Vector4>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Z.V }; }
    template <> mathinline Vector3 mathcall NegativeUnitZ<Vector3>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Z.V }; }
    template <> mathinline Quaternion mathcall NegativeUnitZ<Quaternion>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_Z.V }; }

    template <typename T> T NegativeUnitW() noexcept = delete;

    template <> mathinline Vector4 mathcall NegativeUnitW<Vector4>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_W.V }; }
    template <> mathinline Quaternion mathcall NegativeUnitW<Quaternion>() noexcept { return { Impl::VEC4_NEGATIVE_UNIT_W.V }; }


    template <typename T> T Zero() noexcept = delete;

    template <>
    mathinline Vector4 mathcall Zero<Vector4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_ZERO_4.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(0.0F) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Zero<Vector3>() noexcept
    {
        return { Zero<Vector4>().V };
    }

    template <>
    mathinline Vector2 mathcall Zero<Vector2>() noexcept
    {
        return { Zero<Vector4>().V };
    }

    template <>
    mathinline Vector1 mathcall Zero<Vector1>() noexcept
    {
        return { Zero<Vector4>().V };
    }

    template <>
    mathinline Quaternion mathcall Zero<Quaternion>() noexcept
    {
        return { Zero<Vector4>().V };
    }


    template <typename T>
    T Identity() noexcept = delete;

    template <typename T> T One() noexcept = delete;

    template <>
    mathinline Vector4 mathcall One<Vector4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F,
                1.0F,
                1.0F,
                1.0F,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_ONE_4.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(1.0F) };
#endif
    }

    template <>
    mathinline Vector3 mathcall One<Vector3>() noexcept
    {
        return { One<Vector4>().V };
    }

    template <>
    mathinline Vector2 mathcall One<Vector2>() noexcept
    {
        return { One<Vector4>().V };
    }

    template <>
    mathinline Vector1 mathcall One<Vector1>() noexcept
    {
        return { One<Vector4>().V };
    }

    template <typename T> T Infinity() noexcept = delete;

    template <>
    mathinline Vector4 mathcall Infinity<Vector4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x7F800000,
                0x7F800000,
                0x7F800000,
                0x7F800000,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_INFINITY.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x7F800000) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Infinity<Vector3>() noexcept
    {
        return { Infinity<Vector4>().V };
    }

    template <>
    mathinline Vector2 mathcall Infinity<Vector2>() noexcept
    {
        return { Infinity<Vector4>().V };
    }

    template <>
    mathinline Vector1 mathcall Infinity<Vector1>() noexcept
    {
        return { Infinity<Vector4>().V };
    }

    template <typename T> T Nan() noexcept = delete;

    template <>
    mathinline Vector4 mathcall Nan<Vector4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x7FC00000,
                0x7FC00000,
                0x7FC00000,
                0x7FC00000,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_QNAN.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x7FC00000) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Nan<Vector3>() noexcept
    {
        return { Nan<Vector4>().V };
    }

    template <>
    mathinline Vector2 mathcall Nan<Vector2>() noexcept
    {
        return { Nan<Vector4>().V };
    }

    template <>
    mathinline Vector1 mathcall Nan<Vector1>() noexcept
    {
        return { Nan<Vector4>().V };
    }

    template <typename T> T Epsilon() noexcept = delete;

    template <>
    mathinline Vector4 mathcall Epsilon<Vector4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x34000000,
                0x34000000,
                0x34000000,
                0x34000000,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_EPSILON.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x34000000) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Epsilon<Vector3>() noexcept
    {
        return { Epsilon<Vector4>().V };
    }

    template <>
    mathinline Vector2 mathcall Epsilon<Vector2>() noexcept
    {
        return { Epsilon<Vector4>().V };
    }

    template <>
    mathinline Vector1 mathcall Epsilon<Vector1>() noexcept
    {
        return { Epsilon<Vector4>().V };
    }

    template <typename T> T SignMask() noexcept = delete;

    template <>
    mathinline Vector4 mathcall SignMask<Vector4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0x80000000U,
                0x80000000U,
                0x80000000U,
                0x80000000U,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_castsi128_ps(_mm_set1_epi32(static_cast<int>(0x80000000))) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x80000000U) };
#endif
    }

    template <>
    mathinline Vector3 mathcall SignMask<Vector3>() noexcept
    {
        return { SignMask<Vector4>().V };
    }

    template <>
    mathinline Vector2 mathcall SignMask<Vector2>() noexcept
    {
        return { SignMask<Vector4>().V };
    }

    template <>
    mathinline Vector1 mathcall SignMask<Vector1>() noexcept
    {
        return { SignMask<Vector4>().V };
    }
}


// =================================================================================================
//
// Constructors
//

namespace Graphyte::Maths
{
    template <>
    mathinline Vector4 mathcall Make<Vector4, float>(float x, float y, float z, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                z,
                w,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32)
        );

        float32x2_t const zw = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&w)) << 32)
        );

        return { vcombine_f32(xy, zw) };
#endif
    }

    template <>
    mathinline Quaternion mathcall Make<Quaternion, float>(float x, float y, float z, float w) noexcept
    {
        return { Make<Vector4>(x, y, z, w).V };
    }

    template <>
    mathinline Plane mathcall Make<Plane, float>(float x, float y, float z, float w) noexcept
    {
        return { Make<Plane>(x, y, z, w).V };
    }

    template <>
    mathinline Vector3 mathcall Make<Vector3, float>(float x, float y, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                z,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, z, y, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32)
        );

        float32x2_t const zn = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z))
        );

        return { vcombine_f32(xy, zn) };
#endif
    }


    template <>
    mathinline Vector2 mathcall Make<Vector2, float>(float x, float y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                y,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, y, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32)
        );

        float32x2_t const zero = vdup_n_f32(0.0F);

        return { vcombine_f32(xy, zero) };
#endif
    }

    template <>
    mathinline Vector1 mathcall Make<Vector1, float>(float x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                x,
                0.0F,
                0.0F,
                0.0F,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, 0.0F, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xn = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x))
        );

        float32x2_t const zero = vdup_n_f32(0.0F);

        return { vcombine_f32(xn, zero) };
#endif
    }

    template <>
    mathinline Vector4 mathcall Replicate<Vector4, float>(float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(value) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Replicate<Vector3, float>(float value) noexcept
    {
        return { Replicate<Vector4, float>(value).V };
    }

    template <>
    mathinline Vector2 mathcall Replicate<Vector2, float>(float value) noexcept
    {
        return { Replicate<Vector4, float>(value).V };
    }

    template <>
    mathinline Vector1 mathcall Replicate<Vector1, float>(float value) noexcept
    {
        return { Replicate<Vector4, float>(value).V };
    }

    template <>
    mathinline Vector4 mathcall Replicate<Vector4, float const*>(float const* source) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = (*source);
        Impl::ConstFloat32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcast_ss(source) };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(source) };
#elif GRAPHYTE_HW_NEON
        return { vld1q_dup_f32(source) };
#endif
    }

    template <>
    mathinline Vector3 mathcall Replicate<Vector3, float const*>(float const* value) noexcept
    {
        return { Replicate<Vector4, float const*>(value).V };
    }

    template <>
    mathinline Vector2 mathcall Replicate<Vector2, float const*>(float const* value) noexcept
    {
        return { Replicate<Vector4, float const*>(value).V };
    }

    template <>
    mathinline Vector1 mathcall Replicate<Vector1, float const*>(float const* value) noexcept
    {
        return { Replicate<Vector4, float const*>(value).V };
    }


    template <>
    mathinline Bool4 mathcall Make<Bool4, uint32_t>(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                x,
                y,
                z,
                w,
            } } };
#elif GRAPHYTE_HW_AVX
        __m128i const ivec = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
            static_cast<int>(y),
            static_cast<int>(x)
        );

        return { _mm_castsi128_ps(ivec) };
#elif GRAPHYTE_HW_NEON
        uint32x2_t const r0_xy = vcreate_u32(static_cast<uint64_t>(x) | (static_cast<uint64_t>(y) << 32));
        uint32x2_t const r0_zw = vcreate_u32(static_cast<uint64_t>(z) | (static_cast<uint64_t>(w) << 32));

        float32x4_t const result = vreinterpretq_f32_u32(
            vcombine_u32(r0_xy, r0_zw)
        );

        return { result };
#endif
    }

    template <>
    mathinline Bool4 mathcall Replicate<Bool4, uint32_t>(uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const ivec = _mm_set1_epi32(static_cast<int>(value));
        return { _mm_castsi128_ps(ivec) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(value) };
#endif
    }

    template <>
    mathinline Bool4 mathcall Replicate<Bool4, uint32_t const*>(uint32_t const* source) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        uint32_t const value = (*source);

        Impl::ConstUInt32x4 const result{ { {
                value,
                value,
                value,
                value,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(reinterpret_cast<float const*>(source)) };
#elif GRAPHYTE_HW_NEON
        return { vld1q_dup_u32(source) };
#endif
    }
}


// =================================================================================================
//
// Boolean operations
//

namespace Graphyte::Maths
{
    template <typename T> T True() noexcept = delete;
    template <typename T> T False() noexcept = delete;

    template <>
    mathinline Bool4 mathcall True<Bool4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                0xFFFF'FFFFU,
                0xFFFF'FFFFU,
                0xFFFF'FFFFU,
                0xFFFF'FFFFU,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set1_epi32(-1);
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0xFFFFFFFFu) };
#endif
    }

    template <>
    mathinline Bool3 mathcall True<Bool3>() noexcept
    {
        return { True<Bool4>().V };
    }

    template <>
    mathinline Bool2 mathcall True<Bool2>() noexcept
    {
        return { True<Bool4>().V };
    }

    template <>
    mathinline Bool1 mathcall True<Bool1>() noexcept
    {
        return { True<Bool4>().V };
    }

    template <>
    mathinline Bool4 mathcall False<Bool4>() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result = { { {
                0.0F,
                0.0F,
                0.0F,
                0.0F
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0u) };
#endif
    }

    template <>
    mathinline Bool3 mathcall False<Bool3>() noexcept
    {
        return { False<Bool4>().V };
    }

    template <>
    mathinline Bool2 mathcall False<Bool2>() noexcept
    {
        return { False<Bool4>().V };
    }

    template <>
    mathinline Bool1 mathcall False<Bool1>() noexcept
    {
        return { False<Bool4>().V };
    }

    mathinline Bool4 mathcall And(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] & b.V.U[0],
                a.V.U[1] & b.V.U[1],
                a.V.U[2] & b.V.U[2],
                a.V.U[3] & b.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_and_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vandq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)
            )
        );
#endif
    }

    mathinline Bool3 mathcall And(Bool3 a, Bool3 b) noexcept
    {
        return { And(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall And(Bool2 a, Bool2 b) noexcept
    {
        return { And(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall And(Bool1 a, Bool1 b) noexcept
    {
        return { And(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool4 mathcall AndNot(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result = { { {
                a.V.U[0] & ~b.V.U[0],
                a.V.U[1] & ~b.V.U[1],
                a.V.U[2] & ~b.V.U[2],
                a.V.U[3] & ~b.V.U[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_andnot_si128(_mm_castps_si128(b.V), _mm_castps_si128(a.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vbicq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)
            )
        );
#endif
    }

    mathinline Bool3 mathcall AndNot(Bool3 a, Bool3 b) noexcept
    {
        return { AndNot(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall AndNot(Bool2 a, Bool2 b) noexcept
    {
        return { AndNot(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall AndNot(Bool1 a, Bool1 b) noexcept
    {
        return { AndNot(Bool4{ a.V }, Bool4{ b.V }).V };
    }


    mathinline Bool4 mathcall Or(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] | b.V.U[0],
                a.V.U[1] | b.V.U[1],
                a.V.U[2] | b.V.U[2],
                a.V.U[3] | b.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_or_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vorrq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)
            )
        );
#endif
    }

    mathinline Bool3 mathcall Or(Bool3 a, Bool3 b) noexcept
    {
        return { Or(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall Or(Bool2 a, Bool2 b) noexcept
    {
        return { Or(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall Or(Bool1 a, Bool1 b) noexcept
    {
        return { Or(Bool4{ a.V }, Bool4{ b.V }).V };
    }


    mathinline Bool4 mathcall Xor(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                a.V.U[0] ^ b.V.U[0],
                a.V.U[1] ^ b.V.U[1],
                a.V.U[2] ^ b.V.U[2],
                a.V.U[3] ^ b.V.U[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_xor_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            veorq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)
            )
        );
#endif
    }

    mathinline Bool3 mathcall Xor(Bool3 a, Bool3 b) noexcept
    {
        return { Xor(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall Xor(Bool2 a, Bool2 b) noexcept
    {
        return { Xor(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall Xor(Bool1 a, Bool1 b) noexcept
    {
        return { Xor(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool4 mathcall Nor(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                ~(a.V.U[0] | b.V.U[0]),
                ~(a.V.U[1] | b.V.U[1]),
                ~(a.V.U[2] | b.V.U[2]),
                ~(a.V.U[3] | b.V.U[3]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const partial = _mm_or_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        __m128i const result = _mm_andnot_si128(partial, _mm_castps_si128(Impl::VEC4_MASK_NEGATIVE_ONE.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const partial = vorrq_u32(
            vreinterpretq_u32_f32(a.V),
            vreinterpretq_u32_f32(b.V)
        );

        return vreinterpretq_f32_u32(vmvnq_u32(partial));
#endif
    }

    mathinline Bool3 mathcall Nor(Bool3 a, Bool3 b) noexcept
    {
        return { Nor(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall Nor(Bool2 a, Bool2 b) noexcept
    {
        return { Nor(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall Nor(Bool1 a, Bool1 b) noexcept
    {
        return { Nor(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool4 mathcall Not(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                ~(v.V.U[0]),
                ~(v.V.U[1]),
                ~(v.V.U[2]),
                ~(v.V.U[3]),
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const fullbits = _mm_castsi128_ps(_mm_set1_epi32(-1));
        __m128 const result = _mm_xor_ps(v.V, fullbits);
        return { result };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vmvnq_u32(vreinterpretq_u32_f32(v.V))
        );
#endif
    }

    mathinline Bool3 mathcall Not(Bool3 v) noexcept
    {
        return { Not(Bool4{ v.V }).V };
    }

    mathinline Bool2 mathcall Not(Bool2 v) noexcept
    {
        return { Not(Bool4{ v.V }).V };
    }

    mathinline Bool1 mathcall Not(Bool1 v) noexcept
    {
        return { Not(Bool4{ v.V }).V };
    }
}

// =================================================================================================
//
// Boolean type comparison
//

namespace Graphyte::Maths
{
    mathinline Bool4 mathcall CompareEqual(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] == b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[1] == b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[2] == b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[3] == b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    mathinline Bool3 mathcall CompareEqual(Bool3 a, Bool3 b) noexcept
    {
        return { CompareEqual(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareEqual(Bool2 a, Bool2 b) noexcept
    {
        return { CompareEqual(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareEqual(Bool1 a, Bool1 b) noexcept
    {
        return { CompareEqual(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareNotEqual(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] != b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[1] != b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[2] != b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[3] != b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_xor_ps(_mm_castsi128_ps(result), Impl::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }

    mathinline Bool3 mathcall CompareNotEqual(Bool3 a, Bool3 b) noexcept
    {
        return { CompareNotEqual(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareNotEqual(Bool2 a, Bool2 b) noexcept
    {
        return { CompareNotEqual(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareNotEqual(Bool1 a, Bool1 b) noexcept
    {
        return { CompareNotEqual(Bool4{ a.V }, Bool4{ b.V }).V };
    }

    mathinline bool mathcall IsEqual(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0])
            && (a.V.U[1] == b.V.U[1])
            && (a.V.U[2] == b.V.U[2])
            && (a.V.U[3] == b.V.U[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsEqual(Bool3 a, Bool3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0])
            && (a.V.U[1] == b.V.U[1])
            && (a.V.U[2] == b.V.U[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsEqual(Bool2 a, Bool2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0])
            && (a.V.U[1] == b.V.U[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsEqual(Bool1 a, Bool1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] == b.V.U[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsNotEqual(Bool4 a, Bool4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0])
            || (a.V.U[1] != b.V.U[1])
            || (a.V.U[2] != b.V.U[2])
            || (a.V.U[3] != b.V.U[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return _mm_movemask_ps(mask) != 0b1111;
#endif
    }

    mathinline bool mathcall IsNotEqual(Bool3 a, Bool3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0])
            || (a.V.U[1] != b.V.U[1])
            || (a.V.U[2] != b.V.U[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return (_mm_movemask_ps(mask) & 0b0111) != 0b0111;
#endif
    }

    mathinline bool mathcall IsNotEqual(Bool2 a, Bool2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0])
            || (a.V.U[1] != b.V.U[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return (_mm_movemask_ps(mask) & 0b0011) != 0b0011;
#endif
    }

    mathinline bool mathcall IsNotEqual(Bool1 a, Bool1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.U[0] != b.V.U[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));
        return (_mm_movemask_ps(mask) & 0b0001) != 0b0001;
#endif
    }
}


// =================================================================================================
//
// Boolean mask qualification
//

namespace Graphyte::Maths
{
    mathinline bool mathcall AllTrue(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            && (v.V.U[1] != 0)
            && (v.V.U[2] != 0)
            && (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) == 0b1111;
#endif
    }

    mathinline bool mathcall AllTrue(Bool3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            && (v.V.U[1] != 0)
            && (v.V.U[2] != 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall AllTrue(Bool2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            && (v.V.U[1] != 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall AllTrue(Bool1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall AllFalse(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            && (v.V.U[1] == 0)
            && (v.V.U[2] == 0)
            && (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) == 0;
#endif
    }

    mathinline bool mathcall AllFalse(Bool3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            && (v.V.U[1] == 0)
            && (v.V.U[2] == 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0111) == 0;
#endif
    }

    mathinline bool mathcall AllFalse(Bool2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            && (v.V.U[1] == 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0011) == 0;
#endif
    }

    mathinline bool mathcall AllFalse(Bool1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0001) == 0;
#endif
    }

    mathinline bool mathcall AnyTrue(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            || (v.V.U[1] != 0)
            || (v.V.U[2] != 0)
            || (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) != 0;
#endif
    }

    mathinline bool mathcall AnyTrue(Bool3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            || (v.V.U[1] != 0)
            || (v.V.U[2] != 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0111) != 0;
#endif
    }

    mathinline bool mathcall AnyTrue(Bool2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0)
            || (v.V.U[1] != 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0011) != 0;
#endif
    }

    mathinline bool mathcall AnyTrue(Bool1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] != 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0001) != 0;
#endif
    }

    mathinline bool mathcall AnyFalse(Bool4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            || (v.V.U[1] == 0)
            || (v.V.U[2] == 0)
            || (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) != 0b1111;
#endif
    }

    mathinline bool mathcall AnyFalse(Bool3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            || (v.V.U[1] == 0)
            || (v.V.U[2] == 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0111) != 0b0111;
#endif
    }

    mathinline bool mathcall AnyFalse(Bool2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0)
            || (v.V.U[1] == 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0011) != 0b0011;
#endif
    }

    mathinline bool mathcall AnyFalse(Bool1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.U[0] == 0);
#elif GRAPHYTE_HW_AVX
        return (_mm_movemask_ps(v.V) & 0b0001) != 0b0001;
#endif
    }
}


// =================================================================================================
//
// Componentwise functions
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Cos(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cos_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                cosf(components.F[0]),
                cosf(components.F[1]),
                cosf(components.F[2]),
                cosf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Cos(Vector3 v) noexcept
    {
        return { Cos(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Cos(Vector2 v) noexcept
    {
        return { Cos(Vector4{ v.V }).V };
    }

    mathinline float mathcall Cos(float v) noexcept
    {
        return cosf(v);
    }

    mathinline Vector4 mathcall Sin(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_sin_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                sinf(components.F[0]),
                sinf(components.F[1]),
                sinf(components.F[2]),
                sinf(components.F[3]),
            } } };
        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Sin(Vector3 v) noexcept
    {
        return { Sin(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Sin(Vector2 v) noexcept
    {
        return { Sin(Vector4{ v.V }).V };
    }

    mathinline float mathcall Sin(float v) noexcept
    {
        return sinf(v);
    }

    namespace Impl
    {
        mathinline void mathcall SinCosImpl(
            NativeFloat32x4& out_sin,
            NativeFloat32x4& out_cos,
            NativeFloat32x4 v) noexcept
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const vsin{ { {
                    sinf(v.F[0]),
                    sinf(v.F[1]),
                    sinf(v.F[2]),
                    sinf(v.F[3]),
                } } };

            Impl::ConstFloat32x4 const vcos{ { {
                    cosf(v.F[0]),
                    cosf(v.F[1]),
                    cosf(v.F[2]),
                    cosf(v.F[3]),
                } } };

            out_sin = vsin.V;
            out_cos = vcos.V;

#elif GRAPHYTE_MATH_SVML
            out_sin = _mm_sincos_ps(&out_cos, v);
#else
            Impl::ConstFloat32x4 const components{ .V = v };
            out_sin = Impl::ConstFloat32x4{ { {
                    sinf(components.F[0]),
                    sinf(components.F[1]),
                    sinf(components.F[2]),
                    sinf(components.F[3]),
                } } }.V;

            out_cos = Impl::ConstFloat32x4{ { {
                    cosf(components.F[0]),
                    cosf(components.F[1]),
                    cosf(components.F[2]),
                    cosf(components.F[3]),
                } } }.V;
#endif
        }
    }

    mathinline void mathcall SinCos(Vector4& result_sin, Vector4& result_cos, Vector4 v) noexcept
    {
        Impl::SinCosImpl(result_sin.V, result_cos.V, v.V);
    }

    mathinline void mathcall SinCos(Vector3& result_sin, Vector3& result_cos, Vector3 v) noexcept
    {
        Impl::SinCosImpl(result_sin.V, result_cos.V, v.V);
    }

    mathinline void mathcall SinCos(Vector2& result_sin, Vector2& result_cos, Vector2 v) noexcept
    {
        Impl::SinCosImpl(result_sin.V, result_cos.V, v.V);
    }

    mathinline void mathcall SinCos(float& result_sin, float& result_cos, float v) noexcept
    {
        result_sin = sinf(v);
        result_cos = cosf(v);
    }

    mathinline Vector4 mathcall Tan(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                tanf(v.V.F[0]),
                tanf(v.V.F[1]),
                tanf(v.V.F[2]),
                tanf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_tan_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                tanf(components.F[0]),
                tanf(components.F[1]),
                tanf(components.F[2]),
                tanf(components.F[3]),
            } } };
        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Tan(Vector3 v) noexcept
    {
        return { Tan(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Tan(Vector2 v) noexcept
    {
        return { Tan(Vector4{ v.V }).V };
    }

    mathinline float mathcall Tan(float v) noexcept
    {
        return tanf(v);
    }

    mathinline Vector4 mathcall Asin(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                asinf(v.V.F[0]),
                asinf(v.V.F[1]),
                asinf(v.V.F[2]),
                asinf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_asin_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                asinf(components.F[0]),
                asinf(components.F[1]),
                asinf(components.F[2]),
                asinf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Asin(Vector3 v) noexcept
    {
        return { Asin(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Asin(Vector2 v) noexcept
    {
        return { Asin(Vector4{ v.V }).V };
    }

    mathinline float mathcall Asin(float v) noexcept
    {
        return asinf(v);
    }

    mathinline Vector4 mathcall Acos(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                acosf(v.V.F[0]),
                acosf(v.V.F[1]),
                acosf(v.V.F[2]),
                acosf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_acos_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                acosf(components.F[0]),
                acosf(components.F[1]),
                acosf(components.F[2]),
                acosf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Acos(Vector3 v) noexcept
    {
        return { Acos(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Acos(Vector2 v) noexcept
    {
        return { Acos(Vector4{ v.V }).V };
    }

    mathinline float mathcall Acos(float v) noexcept
    {
        return acosf(v);
    }

    mathinline Vector4 mathcall Atan(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                atanf(v.V.F[0]),
                atanf(v.V.F[1]),
                atanf(v.V.F[2]),
                atanf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atan_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                atanf(components.F[0]),
                atanf(components.F[1]),
                atanf(components.F[2]),
                atanf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Atan(Vector3 v) noexcept
    {
        return { Atan(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Atan(Vector2 v) noexcept
    {
        return { Atan(Vector4{ v.V }).V };
    }

    mathinline float mathcall Atan(float v) noexcept
    {
        return atanf(v);
    }

    mathinline Vector4 mathcall Atan2(Vector4 y, Vector4 x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                atan2f(y.V.F[0], x.V.F[0]),
                atan2f(y.V.F[1], x.V.F[1]),
                atan2f(y.V.F[2], x.V.F[2]),
                atan2f(y.V.F[3], x.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atan2_ps(y.V, x.V) };
#else
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const result{ { {
                atan2f(components_y.F[0], components_x.F[0]),
                atan2f(components_y.F[1], components_x.F[1]),
                atan2f(components_y.F[2], components_x.F[2]),
                atan2f(components_y.F[3], components_x.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Atan2(Vector3 y, Vector3 x) noexcept
    {
        return { Atan2(Vector4{ y.V }, Vector4{ x.V }).V };
    }

    mathinline Vector2 mathcall Atan2(Vector2 y, Vector2 x) noexcept
    {
        return { Atan2(Vector4{ y.V }, Vector4{ x.V }).V };
    }

    mathinline float mathcall Atan2(float y, float x) noexcept
    {
        return atan2f(y, x);
    }

    mathinline Vector4 mathcall Sinh(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sinhf(v.V.F[0]),
                sinhf(v.V.F[1]),
                sinhf(v.V.F[2]),
                sinhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_sinh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                sinhf(components.F[0]),
                sinhf(components.F[1]),
                sinhf(components.F[2]),
                sinhf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Sinh(Vector3 v) noexcept
    {
        return { Sinh(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Sinh(Vector2 v) noexcept
    {
        return { Sinh(Vector4{ v.V }).V };
    }

    mathinline float mathcall Sinh(float v) noexcept
    {
        return sinhf(v);
    }

    mathinline Vector4 mathcall Cosh(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                coshf(v.V.F[0]),
                coshf(v.V.F[1]),
                coshf(v.V.F[2]),
                coshf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cosh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                coshf(components.F[0]),
                coshf(components.F[1]),
                coshf(components.F[2]),
                coshf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Cosh(Vector3 v) noexcept
    {
        return { Cosh(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Cosh(Vector2 v) noexcept
    {
        return { Cosh(Vector4{ v.V }).V };
    }

    mathinline float mathcall Cosh(float v) noexcept
    {
        return coshf(v);
    }

    mathinline Vector4 mathcall Tanh(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                tanhf(v.V.F[0]),
                tanhf(v.V.F[1]),
                tanhf(v.V.F[2]),
                tanhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_tanh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                tanhf(components.F[0]),
                tanhf(components.F[1]),
                tanhf(components.F[2]),
                tanhf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Tanh(Vector3 v) noexcept
    {
        return { Tanh(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Tanh(Vector2 v) noexcept
    {
        return { Tanh(Vector4{ v.V }).V };
    }

    mathinline float mathcall Tanh(float v) noexcept
    {
        return tanhf(v);
    }

    mathinline Vector4 mathcall Asinh(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                asinhf(v.V.F[0]),
                asinhf(v.V.F[1]),
                asinhf(v.V.F[2]),
                asinhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_asinh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                asinhf(components.F[0]),
                asinhf(components.F[1]),
                asinhf(components.F[2]),
                asinhf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Asinh(Vector3 v) noexcept
    {
        return { Asinh(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Asinh(Vector2 v) noexcept
    {
        return { Asinh(Vector4{ v.V }).V };
    }

    mathinline float mathcall Asinh(float v) noexcept
    {
        return asinhf(v);
    }

    mathinline Vector4 mathcall Acosh(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                acoshf(v.V.F[0]),
                acoshf(v.V.F[1]),
                acoshf(v.V.F[2]),
                acoshf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_acosh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                acoshf(components.F[0]),
                acoshf(components.F[1]),
                acoshf(components.F[2]),
                acoshf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Acosh(Vector3 v) noexcept
    {
        return { Acosh(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Acosh(Vector2 v) noexcept
    {
        return { Acosh(Vector4{ v.V }).V };
    }

    mathinline float mathcall Acosh(float v) noexcept
    {
        return acoshf(v);
    }

    mathinline Vector4 mathcall Atanh(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                atanhf(v.V.F[0]),
                atanhf(v.V.F[1]),
                atanhf(v.V.F[2]),
                atanhf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atanh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                atanhf(components.F[0]),
                atanhf(components.F[1]),
                atanhf(components.F[2]),
                atanhf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Atanh(Vector3 v) noexcept
    {
        return { Atanh(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Atanh(Vector2 v) noexcept
    {
        return { Atanh(Vector4{ v.V }).V };
    }

    mathinline float mathcall Atanh(float v) noexcept
    {
        return atanhf(v);
    }

    mathinline Vector4 mathcall Log(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                logf(v.V.F[0]),
                logf(v.V.F[1]),
                logf(v.V.F[2]),
                logf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                logf(components.F[0]),
                logf(components.F[1]),
                logf(components.F[2]),
                logf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Log(Vector3 v) noexcept
    {
        return { Log(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Log(Vector2 v) noexcept
    {
        return { Log(Vector4{ v.V }).V };
    }

    mathinline float mathcall Log(float v) noexcept
    {
        return logf(v);
    }

    mathinline Vector4 mathcall Log(Vector4 base, Vector4 value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
                logf(value.V.F[0]) / logf(base.V.F[0]),
                logf(value.V.F[1]) / logf(base.V.F[1]),
                logf(value.V.F[2]) / logf(base.V.F[2]),
                logf(value.V.F[3]) / logf(base.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        __m128 const log_value = _mm_log_ps(value.V);
        __m128 const log_base = _mm_log_ps(base.V);
        __m128 const result = _mm_div_ps(log_value, log_base);
        return { result };
#else
        Impl::ConstFloat32x4 const components_base{ .V = base.V };
        Impl::ConstFloat32x4 const components_value{ .V = value.V };
        Impl::ConstFloat32x4 const result{ { {
                logf(components_value.F[0]) / logf(components_base.F[0]),
                logf(components_value.F[1]) / logf(components_base.F[1]),
                logf(components_value.F[2]) / logf(components_base.F[2]),
                logf(components_value.F[3]) / logf(components_base.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Log(Vector3 base, Vector3 value) noexcept
    {
        return { Log(Vector4{ base.V }, Vector4{ value.V }).V };
    }

    mathinline Vector2 mathcall Log(Vector2 base, Vector2 value) noexcept
    {
        return { Log(Vector4{ base.V }, Vector4{ value.V }).V };
    }

    mathinline float mathcall Log(float base, float value) noexcept
    {
        return logf(value) / logf(base);
    }

    mathinline Vector4 mathcall Log10(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                log10f(v.V.F[0]),
                log10f(v.V.F[1]),
                log10f(v.V.F[2]),
                log10f(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log10_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                log10f(components.F[0]),
                log10f(components.F[1]),
                log10f(components.F[2]),
                log10f(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Log10(Vector3 v) noexcept
    {
        return { Log10(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Log10(Vector2 v) noexcept
    {
        return { Log10(Vector4{ v.V }).V };
    }

    mathinline float mathcall Log10(float v) noexcept
    {
        return log10f(v);
    }

    mathinline Vector4 mathcall Log2(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                log2f(v.V.F[0]),
                log2f(v.V.F[1]),
                log2f(v.V.F[2]),
                log2f(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log2_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                log2f(components.F[0]),
                log2f(components.F[1]),
                log2f(components.F[2]),
                log2f(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Log2(Vector3 v) noexcept
    {
        return { Log2(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Log2(Vector2 v) noexcept
    {
        return { Log2(Vector4{ v.V }).V };
    }

    mathinline float mathcall Log2(float v) noexcept
    {
        return log2f(v);
    }

    mathinline Vector4 mathcall Exp(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                expf(v.V.F[0]),
                expf(v.V.F[1]),
                expf(v.V.F[2]),
                expf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                expf(components.F[0]),
                expf(components.F[1]),
                expf(components.F[2]),
                expf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Exp(Vector3 v) noexcept
    {
        return { Exp(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Exp(Vector2 v) noexcept
    {
        return { Exp(Vector4{ v.V }).V };
    }

    mathinline float mathcall Exp(float v) noexcept
    {
        return expf(v);
    }

    mathinline Vector4 mathcall Exp10(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                powf(10.0F, v.V.F[0]),
                powf(10.0F, v.V.F[1]),
                powf(10.0F, v.V.F[2]),
                powf(10.0F, v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp10_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                powf(10.0F, components.F[0]),
                powf(10.0F, components.F[1]),
                powf(10.0F, components.F[2]),
                powf(10.0F, components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Exp10(Vector3 v) noexcept
    {
        return { Exp10(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Exp10(Vector2 v) noexcept
    {
        return { Exp10(Vector4{ v.V }).V };
    }

    mathinline float mathcall Exp10(float v) noexcept
    {
        return powf(10.0F, v);
    }

    mathinline Vector4 mathcall Exp2(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                exp2f(v.V.F[0]),
                exp2f(v.V.F[1]),
                exp2f(v.V.F[2]),
                exp2f(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp2_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                exp2f(components.F[0]),
                exp2f(components.F[1]),
                exp2f(components.F[2]),
                exp2f(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Exp2(Vector3 v) noexcept
    {
        return { Exp2(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Exp2(Vector2 v) noexcept
    {
        return { Exp2(Vector4{ v.V }).V };
    }

    mathinline float mathcall Exp2(float v) noexcept
    {
        return exp2f(v);
    }

    mathinline Vector4 mathcall Power(Vector4 x, Vector4 y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                powf(x.V.F[0], y.V.F[0]),
                powf(x.V.F[1], y.V.F[1]),
                powf(x.V.F[2], y.V.F[2]),
                powf(x.V.F[3], y.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_pow_ps(x.V, y.V) };
#else
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const result{ { {
                powf(components_x.F[0], components_y.F[0]),
                powf(components_x.F[1], components_y.F[1]),
                powf(components_x.F[2], components_y.F[2]),
                powf(components_x.F[3], components_y.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Power(Vector3 x, Vector3 y) noexcept
    {
        return { Power(Vector4{ x.V }, Vector4{ y.V }).V };
    }

    mathinline Vector2 mathcall Power(Vector2 x, Vector2 y) noexcept
    {
        return { Power(Vector4{ x.V }, Vector4{ y.V }).V };
    }

    mathinline float mathcall Power(float x, float y) noexcept
    {
        return powf(x, y);
    }

    mathinline Vector4 mathcall Hypot(Vector4 x, Vector4 y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                hypotf(x.V.F[0], y.V.F[0]),
                hypotf(x.V.F[1], y.V.F[1]),
                hypotf(x.V.F[2], y.V.F[2]),
                hypotf(x.V.F[3], y.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_hypot_ps(x.V, y.V) };
#else
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const result{ { {
                hypotf(components_x.F[0], components_y.F[0]),
                hypotf(components_x.F[1], components_y.F[1]),
                hypotf(components_x.F[2], components_y.F[2]),
                hypotf(components_x.F[3], components_y.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Hypot(Vector3 x, Vector3 y) noexcept
    {
        return { Hypot(Vector4{ x.V }, Vector4{ y.V }).V };
    }

    mathinline Vector2 mathcall Hypot(Vector2 x, Vector2 y) noexcept
    {
        return { Hypot(Vector4{ x.V }, Vector4{ y.V }).V };
    }

    mathinline float mathcall Hypot(float x, float y) noexcept
    {
        return hypotf(x, y);
    }

    mathinline Vector4 mathcall Sqrt(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const s0 = vrsqrteq_f32(v);
        float32x4_t const p0 = vmulq_f32(v, s0);
        float32x4_t const r0 = vrsqrtsq_f32(p0, s0);

        float32x4_t const s1 = vmulq_f32(s0, r0);
        float32x4_t const p1 = vmulq_f32(v, s1);
        float32x4_t const r1 = vrsqrtsq_f32(p1, s1);

        float32x4_t const s2 = vmulq_f32(s1, r1);
        float32x4_t const p2 = vmulq_f32(v, s2);
        float32x4_t const r2 = vrsqrtsq_f32(p2, s2);

        float32x4_t const s3 = vmulq_f32(s2, r2);

        uint32x4_t const inf_mask = vceqq_u32(vreinterpretq_u32_f32(v), vdupq_n_u32(0x7F800000U));
        uint32x4_t const zero_mask = vceqq_f32(v, vdupq_n_f32(0.0F));
        float32x4_t const result = vmulq_f32(v, s3);
        uint32x4_t const select_mask = vceqq_u32(inf_mask, zero_mask);
        float32x4_t const final_result = vbslq_f32(select_mask, result, v);
        return { final_result };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    mathinline Vector3 mathcall Sqrt(Vector3 v) noexcept
    {
        return { Sqrt(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Sqrt(Vector2 v) noexcept
    {
        return { Sqrt(Vector4{ v.V }).V };
    }

    mathinline float mathcall Sqrt(float v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_sqrt_ss(_mm_set_ss(v));
        float result;
        _mm_store_ss(&result, s);
        return result;
#endif
    }

    mathinline Vector4 mathcall SqrtEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    mathinline Vector3 mathcall SqrtEst(Vector3 v) noexcept
    {
        return { SqrtEst(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall SqrtEst(Vector2 v) noexcept
    {
        return { SqrtEst(Vector4{ v.V }).V };
    }

    mathinline float mathcall SqrtEst(float v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_rcp_ss(_mm_rsqrt_ss(_mm_set_ss(v)));
        float result;
        _mm_store_ss(&result, s);
        return result;
#endif
    }

    mathinline Vector4 mathcall InvSqrt(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / sqrtf(v.V.F[0]),
                1.0F / sqrtf(v.V.F[1]),
                1.0F / sqrtf(v.V.F[2]),
                1.0F / sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        // Newton-Raphson x2
        float32x4_t const s0 = vrsqrteq_f32(v);

        float32x4_t const p0 = vmulq_f32(v, s0);
        float32x4_t const r0 = vrsqrtsq_f32(p0, s0);

        float32x4_t const s1 = vmulq_f32(s0, r0);
        float32x4_t const p1 = vmulq_f32(v, s1);
        float32x4_t const r1 = vrsqrtsq_f32(p1, s1);

        float32x4_t const r = vmulq_f32(s1, r1);
        return { r };
#elif GRAPHYTE_HW_AVX
        __m128 const partial = _mm_sqrt_ps(v.V);
        __m128 const result = _mm_div_ps(Impl::VEC4_ONE_4.V, partial);
        return { result };
#endif
    }

    mathinline Vector3 mathcall InvSqrt(Vector3 v) noexcept
    {
        return { InvSqrt(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall InvSqrt(Vector2 v) noexcept
    {
        return { InvSqrt(Vector4{ v.V }).V };
    }

    mathinline Vector1 mathcall InvSqrt(Vector1 v) noexcept
    {
        return { InvSqrt(Vector4{ v.V }).V };
    }

    mathinline float mathcall InvSqrt(float v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return 1.0F / sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const vv = _mm_set_ss(v);
        __m128 const rv = _mm_rsqrt_ss(vv);
        float result;
        _mm_store_ss(&result, rv);
        return result;
#endif
    }

    mathinline Vector4 mathcall InvSqrtEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / sqrtf(v.V.F[0]),
                1.0F / sqrtf(v.V.F[1]),
                1.0F / sqrtf(v.V.F[2]),
                1.0F / sqrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rsqrt_ps(v.V) };
#endif
    }

    mathinline Vector3 mathcall InvSqrtEst(Vector3 v) noexcept
    {
        return { InvSqrtEst(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall InvSqrtEst(Vector2 v) noexcept
    {
        return { InvSqrtEst(Vector4{ v.V }).V };
    }

    mathinline Vector1 mathcall InvSqrtEst(Vector1 v) noexcept
    {
        return { InvSqrtEst(Vector4{ v.V }).V };
    }

    mathinline float mathcall InvSqrtEst(float v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return 1.0F / sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const vv = _mm_set_ss(v);
        __m128 const rv = _mm_rsqrt_ss(vv);
        float result;
        _mm_store_ss(&result, rv);
        return result;
#endif
    }

    mathinline Vector4 mathcall Cbrt(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                cbrtf(v.V.F[0]),
                cbrtf(v.V.F[1]),
                cbrtf(v.V.F[2]),
                cbrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cbrt_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                cbrtf(components.F[0]),
                cbrtf(components.F[1]),
                cbrtf(components.F[2]),
                cbrtf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Cbrt(Vector3 v) noexcept
    {
        return { Cbrt(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Cbrt(Vector2 v) noexcept
    {
        return { Cbrt(Vector4{ v.V }).V };
    }

    mathinline Vector1 mathcall Cbrt(Vector1 v) noexcept
    {
        return { Cbrt(Vector4{ v.V }).V };
    }

    mathinline float mathcall Cbrt(float v) noexcept
    {
        return cbrtf(v);
    }

    mathinline Vector4 mathcall InvCbrt(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / cbrtf(v.V.F[0]),
                1.0F / cbrtf(v.V.F[1]),
                1.0F / cbrtf(v.V.F[2]),
                1.0F / cbrtf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_invcbrt_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
                1.0F / cbrtf(components.F[0]),
                1.0F / cbrtf(components.F[1]),
                1.0F / cbrtf(components.F[2]),
                1.0F / cbrtf(components.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall InvCbrt(Vector3 v) noexcept
    {
        return { InvCbrt(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall InvCbrt(Vector2 v) noexcept
    {
        return { InvCbrt(Vector4{ v.V }).V };
    }

    mathinline Vector1 mathcall InvCbrt(Vector1 v) noexcept
    {
        return { InvCbrt(Vector4{ v.V }).V };
    }

    mathinline float mathcall InvCbrt(float v) noexcept
    {
        return 1.0F / cbrtf(v);
    }

    mathinline Vector4 mathcall Abs(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                fabsf(v.V.F[0]),
                fabsf(v.V.F[1]),
                fabsf(v.V.F[2]),
                fabsf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        return { vabsq_f32(v.V) };
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const result = _mm_max_ps(negative, v.V);

        return { result };
#endif
    }

    mathinline Vector3 mathcall Abs(Vector3 v) noexcept
    {
        return { Abs(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Abs(Vector2 v) noexcept
    {
        return { Abs(Vector4{ v.V }).V };
    }

    mathinline float mathcall Abs(float v) noexcept
    {
        return fabsf(v);
    }

    mathinline Vector4 mathcall Negate(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                -v.V.F[0],
                -v.V.F[1],
                -v.V.F[2],
                -v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const result = _mm_sub_ps(zero, v.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vnegq_f32(v.V) };
#endif
    }

    mathinline Vector3 mathcall Negate(Vector3 v) noexcept
    {
        return { Negate(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Negate(Vector2 v) noexcept
    {
        return { Negate(Vector4{ v.V }).V };
    }

    mathinline float mathcall Negate(float v) noexcept
    {
        return -v;
    }

    mathinline Vector4 mathcall Add(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] + b.V.F[0],
                a.V.F[1] + b.V.F[1],
                a.V.F[2] + b.V.F[2],
                a.V.F[3] + b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_add_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vaddq_f32(a.V, b.V) };
#endif
    }

    mathinline Vector3 mathcall Add(Vector3 a, Vector3 b) noexcept
    {
        return { Add(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector2 mathcall Add(Vector2 a, Vector2 b) noexcept
    {
        return { Add(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector4 mathcall Subtract(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] - b.V.F[0],
                a.V.F[1] - b.V.F[1],
                a.V.F[2] - b.V.F[2],
                a.V.F[3] - b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vsubq_f32(a.V, b.V) };
#endif
    }

    mathinline Vector3 mathcall Subtract(Vector3 a, Vector3 b) noexcept
    {
        return { Subtract(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector2 mathcall Subtract(Vector2 a, Vector2 b) noexcept
    {
        return { Subtract(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector4 mathcall Multiply(Vector4 a, Vector4 b) noexcept
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
#elif GRAPHYTE_HW_NEON
        return { vmulq_f32(a.V, b.V) };
#endif
    }

    mathinline Vector3 mathcall Multiply(Vector3 a, Vector3 b) noexcept
    {
        return { Multiply(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector2 mathcall Multiply(Vector2 a, Vector2 b) noexcept
    {
        return { Multiply(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector4 mathcall Multiply(Vector4 a, float b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] * b,
                a.V.F[1] * b,
                a.V.F[2] * b,
                a.V.F[3] * b,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_set_ps1(b);
        return { _mm_mul_ps(a.V, s) };
#elif GRAPHYTE_HW_NEON
        return { vmulq_n_f32(a.V, b) };
#endif
    }

    mathinline Vector3 mathcall Multiply(Vector3 a, float b) noexcept
    {
        return { Multiply(Vector4{ a.V }, b).V };
    }

    mathinline Vector2 mathcall Multiply(Vector2 a, float b) noexcept
    {
        return { Multiply(Vector4{ a.V }, b).V };
    }

    mathinline Vector4 mathcall Reciprocal(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                1.0F / v.V.F[0],
                1.0F / v.V.F[1],
                1.0F / v.V.F[2],
                1.0F / v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rcp_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        float32x4_t const one = vdupq_n_f32(1.0F);
        float32x4_t const result = vdivq_f32(one, v.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Reciprocal(Vector3 v) noexcept
    {
        return { Reciprocal(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Reciprocal(Vector2 v) noexcept
    {
        return { Reciprocal(Vector4{ v.V }).V };
    }

    mathinline float mathcall Reciprocal(float v) noexcept
    {
        return 1.0F / v;
    }

    mathinline Vector4 mathcall Divide(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] / b.V.F[0],
                a.V.F[1] / b.V.F[1],
                a.V.F[2] / b.V.F[2],
                a.V.F[3] / b.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vdivq_f32(a.V, b.V) };
#endif
    }

    mathinline Vector3 mathcall Divide(Vector3 a, Vector3 b) noexcept
    {
        return { Divide(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector2 mathcall Divide(Vector2 a, Vector2 b) noexcept
    {
        return { Divide(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector4 mathcall Divide(Vector4 a, float b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const invb = 1.0F / b;

        Impl::ConstFloat32x4 const result{ { {
                a.V.F[0] * invb,
                a.V.F[1] * invb,
                a.V.F[2] * invb,
                a.V.F[3] * invb,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        return { vdivq_n_f32(a.V, b) };
#elif GRAPHYTE_HW_AVX
        __m128 const invb = _mm_set_ps1(1.0F / b);
        return { _mm_mul_ps(a.V, invb) };
#endif
    }

    mathinline Vector3 mathcall Divide(Vector3 a, float b) noexcept
    {
        return { Divide(Vector4{ a.V }, b).V };
    }

    mathinline Vector2 mathcall Divide(Vector2 a, float b) noexcept
    {
        return { Divide(Vector4{ a.V }, b).V };
    }

    // (a * b) + c
    mathinline Vector4 mathcall MultiplyAdd(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] * b.V.F[0]) + c.V.F[0],
                (a.V.F[1] * b.V.F[1]) + c.V.F[1],
                (a.V.F[2] * b.V.F[2]) + c.V.F[2],
                (a.V.F[3] * b.V.F[3]) + c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fmadd_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fmadd_f32x4(a.V, b.V, c.V) };
#endif
    }

    mathinline Vector3 mathcall MultiplyAdd(Vector3 a, Vector3 b, Vector3 c) noexcept
    {
        return { MultiplyAdd(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline Vector2 mathcall MultiplyAdd(Vector2 a, Vector2 b, Vector2 c) noexcept
    {
        return { MultiplyAdd(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline float mathcall MultiplyAdd(float a, float b, float c) noexcept
    {
        return (a * b) + c;
    }

    // (a * b) - c
    mathinline Vector4 mathcall MultiplySubtract(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] * b.V.F[0]) - c.V.F[0],
                (a.V.F[1] * b.V.F[1]) - c.V.F[1],
                (a.V.F[2] * b.V.F[2]) - c.V.F[2],
                (a.V.F[3] * b.V.F[3]) - c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fmsub_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fmsub_f32x4(a.V, b.V, c.V) };
#endif
    }

    mathinline Vector3 mathcall MultiplySubtract(Vector3 a, Vector3 b, Vector3 c) noexcept
    {
        return { MultiplySubtract(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline Vector2 mathcall MultiplySubtract(Vector2 a, Vector2 b, Vector2 c) noexcept
    {
        return { MultiplySubtract(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline float mathcall MultiplySubtract(float a, float b, float c) noexcept
    {
        return (a * b) - c;
    }

    // -(a * b) + c
    mathinline Vector4 mathcall NegateMultiplyAdd(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                -(a.V.F[0] * b.V.F[0]) + c.V.F[0],
                -(a.V.F[1] * b.V.F[1]) + c.V.F[1],
                -(a.V.F[2] * b.V.F[2]) + c.V.F[2],
                -(a.V.F[3] * b.V.F[3]) + c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fnmadd_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fnmadd_f32x4(a.V, b.V, c.V) };
#endif
    }

    mathinline Vector3 mathcall NegateMultiplyAdd(Vector3 a, Vector3 b, Vector3 c) noexcept
    {
        return { NegateMultiplyAdd(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline Vector2 mathcall NegateMultiplyAdd(Vector2 a, Vector2 b, Vector2 c) noexcept
    {
        return { NegateMultiplyAdd(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline float mathcall NegateMultiplyAdd(float a, float b, float c) noexcept
    {
        return -(a * b) + c;
    }

    // -(a * b) - c
    mathinline Vector4 mathcall NegateMultiplySubtract(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                -(a.V.F[0] * b.V.F[0]) - c.V.F[0],
                -(a.V.F[1] * b.V.F[1]) - c.V.F[1],
                -(a.V.F[2] * b.V.F[2]) - c.V.F[2],
                -(a.V.F[3] * b.V.F[3]) - c.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fnmsub_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fnmsub_f32x4(a.V, b.V, c.V) };
#endif
    }

    mathinline Vector3 mathcall NegateMultiplySubtract(Vector3 a, Vector3 b, Vector3 c) noexcept
    {
        return { NegateMultiplySubtract(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline Vector2 mathcall NegateMultiplySubtract(Vector2 a, Vector2 b, Vector2 c) noexcept
    {
        return { NegateMultiplySubtract(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }).V };
    }

    mathinline float mathcall NegateMultiplySubtract(float a, float b, float c) noexcept
    {
        return -(a * b) - c;
    }

    mathinline Vector4 mathcall Square(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0] * v.V.F[0],
                v.V.F[1] * v.V.F[1],
                v.V.F[2] * v.V.F[2],
                v.V.F[3] * v.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        return { vmulq_f32(v.V, v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(v.V, v.V) };
#endif
    }

    mathinline Vector3 mathcall Square(Vector3 v) noexcept
    {
        return { Square(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Square(Vector2 v) noexcept
    {
        return { Square(Vector4{ v.V }).V };
    }

    mathinline float mathcall Square(float v) noexcept
    {
        return v * v;
    }

    mathinline Vector4 mathcall SignedSquare(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0] * fabsf(v.V.F[0]),
                v.V.F[1] * fabsf(v.V.F[1]),
                v.V.F[2] * fabsf(v.V.F[2]),
                v.V.F[3] * fabsf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const r0 = vabsq_f32(v.V);
        float32x4_t const r1 = vmulq_f32(r0, v.V);
        return { r1 };
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs = _mm_max_ps(negative, v.V);
        __m128 const result = _mm_mul_ps(abs, v.V);

        return { result };
#endif
    }

    mathinline Vector3 mathcall SignedSquare(Vector3 v) noexcept
    {
        return { SignedSquare(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall SignedSquare(Vector2 v) noexcept
    {
        return { SignedSquare(Vector4{ v.V }).V };
    }

    mathinline float mathcall SignedSquare(float v) noexcept
    {
        return v * fabsf(v);
    }

    mathinline Vector4 mathcall Cube(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                v.V.F[0] * v.V.F[0] * v.V.F[0],
                v.V.F[1] * v.V.F[1] * v.V.F[1],
                v.V.F[2] * v.V.F[2] * v.V.F[2],
                v.V.F[3] * v.V.F[3] * v.V.F[3],
            } } };
#elif GRAPHYTE_HW_NEON
        float32x4_t const r0 = vmulq_f32(v.V, v.V);
        float32x4_t const r1 = vmulq_f32(r0, v.V);
        return { r1 };
#elif GRAPHYTE_HW_AVX
        __m128 const v2 = _mm_mul_ps(v.V, v.V);
        __m128 const v3 = _mm_mul_ps(v.V, v2);
        return { v3 };
#endif
    }

    mathinline Vector3 mathcall Cube(Vector3 v) noexcept
    {
        return { Cube(Vector4{ v.V }).V };
    }

    mathinline float mathcall Cube(float v) noexcept
    {
        return v * v * v;
    }
}


// =================================================================================================
//
// Interpolation
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Lerp(Vector4 a, Vector4 b, float t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const scale = Replicate<Vector4>(t);
        Vector4 const length = Subtract(b, a);
        Vector4 const result = MultiplyAdd(length, scale, a);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_sub_ps(b.V, a.V);
        __m128 const scale = _mm_set_ps1(t);
        __m128 const result = Impl::avx_fmadd_f32x4(length, scale, a.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Lerp(Vector3 a, Vector3 b, float t) noexcept
    {
        return { Lerp(Vector4{ a.V }, Vector4{ b.V }, t).V };
    }

    mathinline Vector2 mathcall Lerp(Vector2 a, Vector2 b, float t) noexcept
    {
        return { Lerp(Vector4{ a.V }, Vector4{ b.V }, t).V };
    }

    mathinline Vector4 mathcall Lerp(Vector4 a, Vector4 b, Vector4 t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length = Subtract(b, a);
        Vector4 const result = MultiplyAdd(length, t, a);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_sub_ps(b.V, a.V);
        __m128 const result = Impl::avx_fmadd_f32x4(length, t.V, a.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Lerp(Vector3 a, Vector3 b, Vector3 t) noexcept
    {
        return { Lerp(Vector4{ a.V }, Vector4{ b.V }, Vector4{ t.V }).V };
    }

    mathinline Vector2 mathcall Lerp(Vector2 a, Vector2 b, Vector2 t) noexcept
    {
        return { Lerp(Vector4{ a.V }, Vector4{ b.V }, Vector4{ t.V }).V };
    }

    mathinline float mathcall Lerp(float a, float b, float t) noexcept
    {
        return a + (b - a) * t;
    }

    mathinline float mathcall LerpPrecise(float a, float b, float t) noexcept
    {
        return ((1.0F - t) * a) + (t * b);
    }

    mathinline Vector4 mathcall Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, float t) noexcept
    {
        float const t2 = t * t;
        float const t3 = t * t2;

        Vector4 const p0 = Replicate<Vector4>(2.0F * t3 - 3.0F * t2 + 1.0F);
        Vector4 const t0 = Replicate<Vector4>(t3 - 2.0F * t2 + t);
        Vector4 const p1 = Replicate<Vector4>(-2.0F * t3 + 3.0F * t2);
        Vector4 const t1 = Replicate<Vector4>(t3 - t2);

        Vector4 const r0 = Multiply(p0, position0);
        Vector4 const r1 = MultiplyAdd(t0, tangent0, r0);
        Vector4 const r2 = MultiplyAdd(p1, position1, r1);
        Vector4 const r3 = MultiplyAdd(t1, tangent1, r2);

        return { r3 };
    }

    mathinline Vector3 mathcall Hermite(Vector3 position0, Vector3 tangent0, Vector3 position1, Vector3 tangent1, float t) noexcept
    {
        return { Hermite(Vector4{ position0.V }, Vector4{ tangent0.V }, Vector4{ position1.V }, Vector4{ tangent1.V }, t).V };
    }

    mathinline Vector2 mathcall Hermite(Vector2 position0, Vector2 tangent0, Vector2 position1, Vector2 tangent1, float t) noexcept
    {
        return { Hermite(Vector4{ position0.V }, Vector4{ tangent0.V }, Vector4{ position1.V }, Vector4{ tangent1.V }, t).V };
    }

    mathinline Vector1 mathcall Hermite(Vector1 position0, Vector1 tangent0, Vector1 position1, Vector1 tangent1, float t) noexcept
    {
        return { Hermite(Vector4{ position0.V }, Vector4{ tangent0.V }, Vector4{ position1.V }, Vector4{ tangent1.V }, t).V };
    }

    mathinline Vector4 mathcall Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, Vector4 t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const t2 = Multiply(t, t);
        Vector4 const t3 = Multiply(t, t2);

        Vector4 const p0 = Replicate<Vector4>(2.0F * t3.V.F[0] - 3.0F * t2.V.F[0] + 1.0F);
        Vector4 const t0 = Replicate<Vector4>(t3.V.F[1] - 2.0F * t2.V.F[1] + t.V.F[1]);
        Vector4 const p1 = Replicate<Vector4>(-2.0F * t3.V.F[2] + 3.0F * t2.V.F[2]);
        Vector4 const t1 = Replicate<Vector4>(t3.V.F[2] - t2.V.F[2]);

        Vector4 const r0 = Multiply(p0, position0);
        Vector4 const r1 = MultiplyAdd(t0, tangent0, r0);
        Vector4 const r2 = MultiplyAdd(p1, position1, r1);
        Vector4 const r3 = MultiplyAdd(t1, tangent1, r2);

        return { r3 };

#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const catmul_t2{ { {
                -3.0F,
                -2.0F,
                +3.0F,
                -1.0F,
            } } };

        static Impl::ConstFloat32x4 const catmul_t3{ { {
                +2.0F,
                +1.0F,
                -2.0F,
                +1.0F,
            } } };

        __m128 const t2 = _mm_mul_ps(t.V, t.V);
        __m128 const t3 = _mm_mul_ps(t2, t.V);

        __m128 const t2_m = _mm_mul_ps(t2, catmul_t2.V);
        __m128 const t3_m = _mm_mul_ps(t3, catmul_t3.V);

        __m128 const t2t3_ma = _mm_add_ps(t2_m, t3_m);
        __m128 const ty = _mm_and_ps(t.V, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const t2t3ty = _mm_add_ps(t2t3_ma, ty);
        __m128 const tfinal = _mm_add_ps(t2t3ty, Impl::VEC4_POSITIVE_UNIT_X.V);

        __m128 const r0 = _mm_permute_ps(tfinal, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const f0 = _mm_mul_ps(r0, position0.V);

        __m128 const r1 = _mm_permute_ps(tfinal, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const f1 = Impl::avx_fmadd_f32x4(r1, tangent0.V, f0);

        __m128 const r2 = _mm_permute_ps(tfinal, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const f2 = Impl::avx_fmadd_f32x4(r2, position1.V, f1);

        __m128 const r3 = _mm_permute_ps(tfinal, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const f3 = Impl::avx_fmadd_f32x4(r3, tangent1.V, f2);

        return { f3 };
#endif
    }

    mathinline Vector3 mathcall Hermite(Vector3 position0, Vector3 tangent0, Vector3 position1, Vector3 tangent1, Vector4 t) noexcept
    {
        return { Hermite(Vector4{ position0.V }, Vector4{ tangent0.V }, Vector4{ position1.V }, Vector4{ tangent1.V }, t).V };
    }

    mathinline Vector2 mathcall Hermite(Vector2 position0, Vector2 tangent0, Vector2 position1, Vector2 tangent1, Vector4 t) noexcept
    {
        return { Hermite(Vector4{ position0.V }, Vector4{ tangent0.V }, Vector4{ position1.V }, Vector4{ tangent1.V }, t).V };
    }

    mathinline Vector1 mathcall Hermite(Vector1 position0, Vector1 tangent0, Vector1 position1, Vector1 tangent1, Vector4 t) noexcept
    {
        return { Hermite(Vector4{ position0.V }, Vector4{ tangent0.V }, Vector4{ position1.V }, Vector4{ tangent1.V }, t).V };
    }

    mathinline float mathcall Hermite(float position0, float tangent0, float position1, float tangent1, float t) noexcept
    {
        float const t2 = t * t;
        float const t3 = t * t2;

        float const p0 = (2.0F * t3 - 3.0F * t2 + 1.0F);
        float const t0 = (t3 - 2.0F * t2 + t);
        float const p1 = (-2.0F * t3 + 3.0F * t2);
        float const t1 = (t3 - t2);

        float const r0 = (p0 * position0);
        float const r1 = (t0 * tangent0) + r0;
        float const r2 = (p1 * position1) + r1;
        float const r3 = (t1 * tangent1) + r2;

        return r3;
    }

    mathinline Vector4 mathcall Barycentric(Vector4 a, Vector4 b, Vector4 c, float f, float g) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const pba = Subtract(b, a);
        Vector4 const pca = Subtract(c, a);
        Vector4 const sf = Replicate<Vector4>(f);
        Vector4 const sg = Replicate<Vector4>(g);
        Vector4 const accum = MultiplyAdd(pba, sf, a);
        Vector4 const result = MultiplyAdd(pca, sg, accum);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const pba = _mm_sub_ps(b.V, a.V);
        __m128 const pca = _mm_sub_ps(c.V, a.V);
        __m128 const sf = _mm_set_ps1(f);
        __m128 const sg = _mm_set_ps1(g);

        __m128 const accum = Impl::avx_fmadd_f32x4(pba, sf, a.V);
        __m128 const result = Impl::avx_fmadd_f32x4(pca, sg, accum);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const pba = vsubq_f32(b.V, a.V);
        float32x4_t const pca = vsubq_f32(c.V, a.V);
        float32x4_t const accum = vmlaq_n_f32(a.V, pba.V, f);
        float32x4_t const result = vmlaq_n_f32(accum, pca, g);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Barycentric(Vector3 a, Vector3 b, Vector3 c, float f, float g) noexcept
    {
        return Vector3{ Barycentric(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }, f, g).V };
    }

    mathinline Vector2 mathcall Barycentric(Vector2 a, Vector2 b, Vector2 c, float f, float g) noexcept
    {
        return Vector2{ Barycentric(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }, f, g).V };
    }

    mathinline Vector1 mathcall Barycentric(Vector1 a, Vector1 b, Vector1 c, float f, float g) noexcept
    {
        return Vector1{ Barycentric(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }, f, g).V };
    }

    mathinline float mathcall Barycentric(float a, float b, float c, float f, float g) noexcept
    {
        float const pba = b - a;
        float const pca = c - a;
        float const accum = (pba * f) + a;
        float const result = (pca * g) + accum;
        return result;
    }

    mathinline Vector4 mathcall Barycentric(Vector4 a, Vector4 b, Vector4 c, Vector4 f, Vector4 g) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const pba = Subtract(b, a);
        Vector4 const pca = Subtract(c, a);
        Vector4 const accum = MultiplyAdd(pba, f, a);
        Vector4 const result = MultiplyAdd(pca, g, accum);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const pba = _mm_sub_ps(b.V, a.V);
        __m128 const pca = _mm_sub_ps(c.V, a.V);
        __m128 const accum = Impl::avx_fmadd_f32x4(pba, f.V, a.V);
        __m128 const result = Impl::avx_fmadd_f32x4(pca, g.V, accum);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const pba = vsubq_f32(b.V, a.V);
        float32x4_t const pca = vsubq_f32(c.V, a.V);
        float32x4_t const accum = vmlaq_f32(a.V, pba, f.V);
        float32x4_t const result = vmlaq_f32(accum, pca, g.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Barycentric(Vector3 a, Vector3 b, Vector3 c, Vector3 f, Vector3 g) noexcept
    {
        return Vector3{ Barycentric(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }, Vector4{ f.V }, Vector4{ g.V }).V };
    }

    mathinline Vector2 mathcall Barycentric(Vector2 a, Vector2 b, Vector2 c, Vector2 f, Vector2 g) noexcept
    {
        return Vector2{ Barycentric(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }, Vector4{ f.V }, Vector4{ g.V }).V };
    }

    mathinline Vector1 mathcall Barycentric(Vector1 a, Vector1 b, Vector1 c, Vector1 f, Vector1 g) noexcept
    {
        return Vector1{ Barycentric(Vector4{ a.V }, Vector4{ b.V }, Vector4{ c.V }, Vector4{ f.V }, Vector4{ g.V }).V };
    }


    mathinline Vector4 mathcall CatmullRom(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3, float t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const t2 = t * t;
        float const t3 = t * t2;

        Vector4 const f0 = Replicate<Vector4>((-t3 + 2.0F * t2 - t) * 0.5F);
        Vector4 const f1 = Replicate<Vector4>((3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F);
        Vector4 const f2 = Replicate<Vector4>((-3.0F * t3 + 4.0F * t2 + t) * 0.5F);
        Vector4 const f3 = Replicate<Vector4>((t3 - t2) * 0.5F);

        Vector4 const r0 = Multiply(f0, p0);
        Vector4 const r1 = MultiplyAdd(f1, p1, r0);
        Vector4 const r2 = MultiplyAdd(f2, p2, r1);
        Vector4 const r3 = MultiplyAdd(f3, p3, r2);

        return r3;
#elif GRAPHYTE_HW_AVX
        float const t2 = t * t;
        float const t3 = t * t2;

        __m128 const f0 = _mm_set_ps1((-t3 + 2.0F * t2 - t) * 0.5F);
        __m128 const f1 = _mm_set_ps1((3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F);
        __m128 const f2 = _mm_set_ps1((-3.0F * t3 + 4.0F * t2 + t) * 0.5F);
        __m128 const f3 = _mm_set_ps1((t3 - t2) * 0.5F);

        __m128 const r0 = _mm_mul_ps(f0, p0.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(f1, p1.V, r0);
        __m128 const r2 = Impl::avx_fmadd_f32x4(f2, p2.V, r1);
        __m128 const r3 = Impl::avx_fmadd_f32x4(f3, p3.V, r2);

        return { r3 };
#endif
    }

    mathinline Vector3 mathcall CatmullRom(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t) noexcept
    {
        return Vector3{ CatmullRom(Vector4{ p0.V }, Vector4{ p1.V }, Vector4{ p2.V }, Vector4{ p3.V }, t).V };
    }

    mathinline Vector2 mathcall CatmullRom(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t) noexcept
    {
        return Vector2{ CatmullRom(Vector4{ p0.V }, Vector4{ p1.V }, Vector4{ p2.V }, Vector4{ p3.V }, t).V };
    }

    mathinline Vector1 mathcall CatmullRom(Vector1 p0, Vector1 p1, Vector1 p2, Vector1 p3, float t) noexcept
    {
        return Vector1{ CatmullRom(Vector4{ p0.V }, Vector4{ p1.V }, Vector4{ p2.V }, Vector4{ p3.V }, t).V };
    }


    mathinline Vector4 mathcall CatmullRom(Vector4 p0, Vector4 p1, Vector4 p2, Vector4 p3, Vector4 t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = t.V.F[0];
        float const fy = t.V.F[1];
        float const fz = t.V.F[2];
        float const fw = t.V.F[3];

        float const dx
            = 0.5F * ((-fx * fx * fx + 2.0F * fx * fx - fx) * p0.V.F[0]
            + (3.0F * fx * fx * fx - 5.0F * fx * fx + 2.0F) * p1.V.F[0]
            + (-3.0F * fx * fx * fx + 4.0F * fx * fx + fx) * p2.V.F[0]
            + (fx * fx * fx - fx * fx) * p3.V.F[0]);


        float const dy
            = 0.5F * ((-fy * fy * fy + 2.0F * fy * fy - fy) * p0.V.F[1]
            + (3.0F * fy * fy * fy - 5.0F * fy * fy + 2.0F) * p1.V.F[1]
            + (-3.0F * fy * fy * fy + 4.0F * fy * fy + fy) * p2.V.F[1]
            + (fy * fy * fy - fy * fy) * p3.V.F[1]);

        float const dz
            = 0.5F * ((-fz * fz * fz + 2.0F * fz * fz - fz) * p0.V.F[2]
            + (3.0F * fz * fz * fz - 5.0F * fz * fz + 2.0F) * p1.V.F[2]
            + (-3.0F * fz * fz * fz + 4.0F * fz * fz + fz) * p2.V.F[2]
            + (fz * fz * fz - fz * fz) * p3.V.F[2]);

        float const dw
            = 0.5F * ((-fw * fw * fw + 2.0F * fw * fw - fw) * p0.V.F[3]
            + (3.0F * fw * fw * fw - 5.0F * fw * fw + 2.0F) * p1.V.F[3]
            + (-3.0F * fw * fw * fw + 4.0F * fw * fw + fw) * p2.V.F[3]
            + (fw * fw * fw - fw * fw) * p3.V.F[3]);


        Impl::ConstFloat32x4 const result{ { {
                dx,
                dy,
                dz,
                dw,
            } } };

        return { result.V };

#elif GRAPHYTE_HW_AVX

        static Impl::ConstFloat32x4 const catmul2{ { { 2.0F, 2.0F, 2.0F, 2.0F } } };
        static Impl::ConstFloat32x4 const catmul3{ { { 3.0F, 3.0F, 3.0F, 3.0F } } };
        static Impl::ConstFloat32x4 const catmul4{ { { 4.0F, 4.0F, 4.0F, 4.0F } } };
        static Impl::ConstFloat32x4 const catmul5{ { { 5.0F, 5.0F, 5.0F, 5.0F } } };

        __m128 t2 = _mm_mul_ps(t.V, t.V);
        __m128 t3 = _mm_mul_ps(t.V, t2);

        // p0
        __m128 result = _mm_add_ps(t2, t2);
        result = _mm_sub_ps(result, t.V);
        result = _mm_sub_ps(result, t3);
        result = _mm_mul_ps(result, p0.V);

        // p1
        __m128 temp = _mm_mul_ps(t3, catmul3.V);
        __m128 temp2 = _mm_mul_ps(t2, catmul5.V);
        temp = _mm_sub_ps(temp, temp2);
        temp = _mm_add_ps(temp, catmul2.V);
        temp = _mm_mul_ps(temp, p1.V);
        result = _mm_add_ps(result, temp);

        // p2
        temp = _mm_mul_ps(t2, catmul4.V);
        temp2 = _mm_mul_ps(t3, catmul3.V);
        temp = _mm_sub_ps(temp, temp2);
        temp = _mm_add_ps(temp, t.V);
        temp = _mm_mul_ps(temp, p2.V);
        result = _mm_add_ps(result, temp);

        // p3
        t3 = _mm_sub_ps(t3, t2);
        t3 = _mm_mul_ps(t3, p3.V);
        result = _mm_add_ps(result, t3);

        // final result
        result = _mm_mul_ps(result, Impl::VEC4_ONE_HALF_4.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall CatmullRom(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, Vector4 t) noexcept
    {
        return Vector3{ CatmullRom(
            Vector4{ p0.V },
            Vector4{ p1.V },
            Vector4{ p2.V },
            Vector4{ p3.V },
            t
        ).V };
    }

    mathinline Vector2 mathcall CatmullRom(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, Vector4 t) noexcept
    {
        return Vector2{ CatmullRom(
            Vector4{ p0.V },
            Vector4{ p1.V },
            Vector4{ p2.V },
            Vector4{ p3.V },
            t
        ).V };
    }

    mathinline float mathcall CatmullRom(float p0, float p1, float p2, float p3, float t) noexcept
    {
        float const t2 = t * t;
        float const t3 = t * t2;

        float const f0 = (-t3 + 2.0F * t2 - t) * 0.5F;
        float const f1 = (3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F;
        float const f2 = (-3.0F * t3 + 4.0F * t2 + t) * 0.5F;
        float const f3 = (t3 - t2) * 0.5F;

        float const r0 = (f0 * p0);
        float const r1 = (f1 * p1) + r0;
        float const r2 = (f2 * p2) + r1;
        float const r3 = (f3 * p3) + r2;

        return r3;
    }

    mathinline Vector4 mathcall Remap(Vector4 value, Vector4 from_min, Vector4 from_max, Vector4 to_min, Vector4 to_max) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const from_abs = Subtract(value, from_min);
        Vector4 const from_max_abs = Subtract(from_max, from_min);

        Vector4 const normal = Divide(from_abs, from_max_abs);

        Vector4 const to_max_abs = Subtract(to_max, to_min);

        Vector4 const to = MultiplyAdd(to_max_abs, normal, to_min);

        return to;
#elif GRAPHYTE_HW_AVX
        __m128 const from_abs = _mm_sub_ps(value.V, from_min.V);
        __m128 const from_max_abs = _mm_sub_ps(from_max.V, from_min.V);

        __m128 const normal = _mm_div_ps(from_abs, from_max_abs);

        __m128 const to_max_abs = _mm_sub_ps(to_max.V, to_min.V);
        __m128 const to = Impl::avx_fmadd_f32x4(to_max_abs, normal, to_min.V);

        return { to };
#endif
    }

    mathinline Vector3 mathcall Remap(Vector3 value, Vector3 from_min, Vector3 from_max, Vector3 to_min, Vector3 to_max) noexcept
    {
        return Vector3{ Remap(
            Vector4{ value.V },
            Vector4{ from_min.V },
            Vector4{ from_max.V },
            Vector4{ to_min.V },
            Vector4{ to_max.V }
        ).V };
    }

    mathinline Vector2 mathcall Remap(Vector2 value, Vector2 from_min, Vector2 from_max, Vector2 to_min, Vector2 to_max) noexcept
    {
        return Vector2{ Remap(
            Vector4{ value.V },
            Vector4{ from_min.V },
            Vector4{ from_max.V },
            Vector4{ to_min.V },
            Vector4{ to_max.V }
        ).V };
    }

    mathinline float mathcall Remap(float value, float from_min, float from_max, float to_min, float to_max) noexcept
    {
        float const from_abs = (value - from_min);
        float const from_max_abs = (from_max - from_min);

        float const normal = (from_abs / from_max_abs);

        float const to_max_abs = (to_max - to_min);
        float const to_abs = (to_max_abs * normal);

        float const to = (to_abs + to_min);

        return to;
    }

    mathinline Vector4 mathcall Unlerp(Vector4 value, Vector4 min, Vector4 max) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const base = Subtract(value, min);
        Vector4 const range = Subtract(max, min);
        Vector4 const result = Divide(base, range);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const base = _mm_sub_ps(value.V, min.V);
        __m128 const range = _mm_sub_ps(max.V, min.V);
        __m128 const result = _mm_div_ps(base, range);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Unlerp(Vector3 value, Vector3 min, Vector3 max) noexcept
    {
        return { Unlerp(Vector4{ value.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline Vector2 mathcall Unlerp(Vector2 value, Vector2 min, Vector2 max) noexcept
    {
        return { Unlerp(Vector4{ value.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline float mathcall Unlerp(float value, float min, float max) noexcept
    {
        float const base = (value - min);
        float const range = (max - min);
        float const result = (base / range);
        return result;
    }

    mathinline float mathcall Bezier(float a, float b, float c, float t) noexcept
    {
        float const t2 = t * t;
        float const t1 = 1.0F - t;
        float const t12 = t1 * t1;
        return (a * t12) + (2.0F * b * t1 * t) + (c * t2);
    }

    mathinline float mathcall Bezier(float a, float b, float c, float d, float t) noexcept
    {
        float const t1 = 1.0F - t;
        float const t13 = t1 * t1 * t1;
        float const t3 = t * t * t;

        return (t13 * a) + (3.0F * t * t1 * t1 * b) + (3.0F * t * t * t1 * c) + (t3 * d);
    }
}


// =================================================================================================
//
// Rounding operations
//

namespace Graphyte::Maths::Impl
{
    mathinline float RoundToNearest(float value) noexcept
    {
        float const integral = floorf(value);
        float const fraction = value - integral;

        if (fraction < 0.5F)
        {
            return integral;
        }

        if (fraction > 0.5F)
        {
            return integral + 1.0F;
        }

        float integral_part;

        (void)modff(integral / 2.0F, &integral_part);

        if ((2.0F * integral_part) == integral)
        {
            return integral;
        }

        return integral + 1.0F;
    }
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall CopySign(Vector4 number, Vector4 sign) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                copysignf(number.V.F[0], sign.V.F[0]),
                copysignf(number.V.F[1], sign.V.F[1]),
                copysignf(number.V.F[2], sign.V.F[2]),
                copysignf(number.V.F[3], sign.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_castsi128_ps(_mm_set1_epi32(static_cast<int>(0x80000000)));
        __m128 const sign_mask = _mm_and_ps(sign.V, mask);
        __m128 const abs_number = _mm_andnot_ps(mask, number.V);
        __m128 const result = _mm_or_ps(abs_number, sign_mask);
        return { result };
#endif
    }

    mathinline Vector3 mathcall CopySign(Vector3 number, Vector3 sign) noexcept
    {
        return { CopySign(Vector4{ number.V }, Vector4{ sign.V }).V };
    }

    mathinline Vector2 mathcall CopySign(Vector2 number, Vector2 sign) noexcept
    {
        return { CopySign(Vector4{ number.V }, Vector4{ sign.V }).V };
    }

    mathinline float mathcall CopySign(float number, float sign) noexcept
    {
        return copysignf(number, sign);
    }

    mathinline float mathcall Sign(float val)
    {
        float const gt_zero = ((0.0f < val) ? 1.0f : 0.0f);
        float const lt_zero = ((val < 0.0f) ? 1.0f : 0.0f);
        return gt_zero - lt_zero;
    }

    mathinline Vector4 mathcall Sign(Vector4 x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                Sign(x.V.F[0]),
                Sign(x.V.F[1]),
                Sign(x.V.F[2]),
                Sign(x.V.F[3]),
            } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        uint32x4_t const pos_one = vreinterpretq_u32_f32(vdupq_n_f32(1.0f));
        uint32x4_t const neg_one = vreinterpretq_u32_f32(vdupq_n_f32(-1.0f));
        uint32x4_t const lt_zero = vcltq_f32(x.V, zero);
        uint32x4_t const gt_zero = vcgtq_f32(x.V, zero);
        uint32x4_t const lt_sign = vandq_u32(lt_zero, neg_one);
        uint32x4_t const gt_sign = vandq_u32(gt_zero, pos_one);
        float32x4_t const result = vreinterpretq_f32_u32(vorq_u32(lt_sign, gt_sign));
        return { result };
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const pos_one = _mm_set1_ps(1.0f);
        __m128 const neg_one = _mm_set1_ps(-1.0f);
        __m128 const lt_zero = _mm_cmplt_ps(x.V, zero);
        __m128 const gt_zero = _mm_cmpgt_ps(x.V, zero);
        __m128 const lt_sign = _mm_and_ps(lt_zero, neg_one);
        __m128 const gt_sign = _mm_and_ps(gt_zero, pos_one);
        __m128 const result = _mm_or_ps(lt_sign, gt_sign);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Sign(Vector3 x) noexcept
    {
        return { Sign(Vector4{ x.V }).V };
    }

    mathinline Vector2 mathcall Sign(Vector2 x) noexcept
    {
        return { Sign(Vector4{ x.V }).V };
    }

    mathinline Vector4 mathcall Ceiling(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
                ceilf(v.V.F[0]),
                ceilf(v.V.F[1]),
                ceilf(v.V.F[2]),
                ceilf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_ceil_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        return { vrndpq_f32(v.V) };
#endif
    }

    mathinline Vector3 mathcall Ceiling(Vector3 v) noexcept
    {
        return { Ceiling(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Ceiling(Vector2 v) noexcept
    {
        return { Ceiling(Vector4{ v.V }).V };
    }

    mathinline float mathcall Ceiling(float value) noexcept
    {
        return ceilf(value);
    }

    mathinline Vector4 mathcall Floor(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                floorf(v.V.F[0]),
                floorf(v.V.F[1]),
                floorf(v.V.F[2]),
                floorf(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_floor_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        return { vrndmq_f32(v.V) };
#endif
    }

    mathinline Vector3 mathcall Floor(Vector3 v) noexcept
    {
        return { Floor(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Floor(Vector2 v) noexcept
    {
        return { Floor(Vector4{ v.V }).V };
    }

    mathinline float mathcall Floor(float value) noexcept
    {
        return floorf(value);
    }

    mathinline Vector4 mathcall Truncate(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result;

        for (size_t i = 0; i < 4; ++i)
        {
            if (FloatTraits<float>::BitIsNan(v.V.U[i]))
            {
                result.V.U[i] = 0x7fc00000U;
            }
            else if (fabsf(v.V.F[i]) < 8388608.0F)
            {
                result.V.F[i] = static_cast<float>(static_cast<int32_t>(v.V.F[i]));
            }
            else
            {
                result.V.F[i] = v.V.F[i];
            }
        }

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
#elif GRAPHYTE_HW_NEON
        return { vrndq_f32(v.V) };
#endif
    }

    mathinline Vector3 mathcall Truncate(Vector3 v) noexcept
    {
        return { Truncate(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Truncate(Vector2 v) noexcept
    {
        return { Truncate(Vector4{ v.V }).V };
    }

    mathinline float mathcall Truncate(float value) noexcept
    {
        return truncf(value);
    }

    mathinline Vector4 mathcall Round(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                Impl::RoundToNearest(v.V.F[0]),
                Impl::RoundToNearest(v.V.F[1]),
                Impl::RoundToNearest(v.V.F[2]),
                Impl::RoundToNearest(v.V.F[3]),
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
#elif GRAPHYTE_HW_NEON
        return { vrndnq_f32(v.V) };
#endif
    }

    mathinline Vector3 mathcall Round(Vector3 v) noexcept
    {
        return { Round(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Round(Vector2 v) noexcept
    {
        return { Round(Vector4{ v.V }).V };
    }

    mathinline float mathcall Round(float value) noexcept
    {
        return roundf(value);
    }

    mathinline Vector4 mathcall Remainder(Vector4 x, Vector4 y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                fmodf(x.V.F[0], y.V.F[0]),
                fmodf(x.V.F[1], y.V.F[1]),
                fmodf(x.V.F[2], y.V.F[2]),
                fmodf(x.V.F[3], y.V.F[3]),
            } } };
        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_fmod_ps(x.V, y.V) };
#elif GRAPHYTE_HW_AVX
        __m128 const q = _mm_div_ps(x.V, y.V);
        __m128 const t = _mm_round_ps(q, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
        __m128 const c = _mm_cvtepi32_ps(_mm_cvttps_epi32(t));
        __m128 const result = Impl::avx_fnmadd_f32x4(c, y.V, x.V);
        return { result };
#else
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const result{ { {
                fmodf(components_x.F[0], components_y.F[0]),
                fmodf(components_x.F[1], components_y.F[1]),
                fmodf(components_x.F[2], components_y.F[2]),
                fmodf(components_x.F[3], components_y.F[3]),
            } } };

        return { result.V };
#endif
    }

    mathinline Vector3 mathcall Remainder(Vector3 x, Vector3 y) noexcept
    {
        return { Remainder(Vector4{ x.V }, Vector4{ y.V }).V };
    }

    mathinline Vector2 mathcall Remainder(Vector2 x, Vector2 y) noexcept
    {
        return { Remainder(Vector4{ x.V }, Vector4{ y.V }).V };
    }

    mathinline float mathcall Remainder(float x, float y) noexcept
    {
        return fmodf(x, y);
    }

    mathinline Vector4 mathcall Fraction(Vector4 x) noexcept
    {
        return Subtract(x, Floor(x));
    }

    mathinline Vector3 mathcall Fraction(Vector3 x) noexcept
    {
        return { Fraction(Vector4{ x.V }).V };
    }

    mathinline Vector2 mathcall Fraction(Vector2 x) noexcept
    {
        return { Fraction(Vector4{ x.V }).V };
    }

    mathinline float mathcall Fraction(float x) noexcept
    {
        return x - Floor(x);
    }
}


// =================================================================================================
//
// Component-wise comparisons
//

namespace Graphyte::Maths
{
    mathinline Bool4 mathcall BitCompareEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] == b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[1] == b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[2] == b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[3] == b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#endif
    }

    mathinline Bool3 mathcall BitCompareEqual(Vector3 a, Vector3 b) noexcept
    {
        return { BitCompareEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall BitCompareEqual(Vector2 a, Vector2 b) noexcept
    {
        return { BitCompareEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall BitCompareEqual(Vector1 a, Vector1 b) noexcept
    {
        return { BitCompareEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall BitCompareNotEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.U[0] != b.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[1] != b.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[2] != b.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.U[3] != b.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_xor_ps(_mm_castsi128_ps(result), Impl::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }

    mathinline Bool3 mathcall BitCompareNotEqual(Vector3 a, Vector3 b) noexcept
    {
        return { BitCompareNotEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall BitCompareNotEqual(Vector2 a, Vector2 b) noexcept
    {
        return { BitCompareNotEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall BitCompareNotEqual(Vector1 a, Vector1 b) noexcept
    {
        return { BitCompareNotEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] == b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[1] == b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[2] == b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[3] == b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpeq_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vceqq_f32(a.V, b.V)) };
#endif
    }

    mathinline Bool3 mathcall CompareEqual(Vector3 a, Vector3 b) noexcept
    {
        return { CompareEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareEqual(Vector2 a, Vector2 b) noexcept
    {
        return { CompareEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareEqual(Vector1 a, Vector1 b) noexcept
    {
        return { CompareEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareEqual(Vector4 a, Vector4 b, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const dx = (a.V.F[0] - b.V.F[0]);
        float const dy = (a.V.F[1] - b.V.F[1]);
        float const dz = (a.V.F[2] - b.V.F[2]);
        float const dw = (a.V.F[3] - b.V.F[3]);

        float const absx = fabsf(dx);
        float const absy = fabsf(dy);
        float const absz = fabsf(dz);
        float const absw = fabsf(dw);

        Impl::ConstUInt32x4 const result{ { {
                (absx <= epsilon.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (absy <= epsilon.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (absz <= epsilon.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (absw <= epsilon.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const delv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const negv = _mm_sub_ps(zero, delv);
        __m128 const absv = _mm_max_ps(delv, negv);
        __m128 const mask = _mm_cmple_ps(absv, epsilon.V);
        return { mask };
#elif GRAPHYTE_HW_NEON
        float32x4_t const diff = vsubq_f32(a.V, b.V);
        float32x4_t const result = vacleq_f32(diff, epsilon.V);
        return { result };
#endif
    }

    mathinline Bool3 mathcall CompareEqual(Vector3 a, Vector3 b, Vector4 epsilon) noexcept
    {
        return { CompareEqual(Vector4{ a.V }, Vector4{ b.V }, epsilon).V };
    }

    mathinline Bool2 mathcall CompareEqual(Vector2 a, Vector2 b, Vector4 epsilon) noexcept
    {
        return { CompareEqual(Vector4{ a.V }, Vector4{ b.V }, epsilon).V };
    }

    mathinline Bool1 mathcall CompareEqual(Vector1 a, Vector1 b, Vector4 epsilon) noexcept
    {
        return { CompareEqual(Vector4{ a.V }, Vector4{ b.V }, epsilon).V };
    }


    mathinline Bool4 mathcall CompareNotEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] != b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[1] != b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[2] != b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[3] != b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const equal = vreinterpretq_u32_f32(vceqq_f32(a.V, b.V));
        uint32x4_t const not_equal = vmvnq_u32(equal);
        return { vreinterpretq_f32_u32(not_equal) };
#endif
    }

    mathinline Bool3 mathcall CompareNotEqual(Vector3 a, Vector3 b) noexcept
    {
        return { CompareNotEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareNotEqual(Vector2 a, Vector2 b) noexcept
    {
        return { CompareNotEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareNotEqual(Vector1 a, Vector1 b) noexcept
    {
        return { CompareNotEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareGreater(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] > b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[1] > b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[2] > b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[3] > b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpgt_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vcgtq_f32(a.V, b.V)) };
#endif
    }

    mathinline Bool3 mathcall CompareGreater(Vector3 a, Vector3 b) noexcept
    {
        return { CompareGreater(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareGreater(Vector2 a, Vector2 b) noexcept
    {
        return { CompareGreater(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareGreater(Vector1 a, Vector1 b) noexcept
    {
        return { CompareGreater(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareGreaterEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] >= b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[1] >= b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[2] >= b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[3] >= b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpge_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vcgeq_f32(a.V, b.V)) };
#endif
    }

    mathinline Bool3 mathcall CompareGreaterEqual(Vector3 a, Vector3 b) noexcept
    {
        return { CompareGreaterEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareGreaterEqual(Vector2 a, Vector2 b) noexcept
    {
        return { CompareGreaterEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareGreaterEqual(Vector1 a, Vector1 b) noexcept
    {
        return { CompareGreaterEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareLess(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] < b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[1] < b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[2] < b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[3] < b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmplt_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vcltq_f32(a.V, b.V) };
#endif
    }

    mathinline Bool3 mathcall CompareLess(Vector3 a, Vector3 b) noexcept
    {
        return { CompareLess(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareLess(Vector2 a, Vector2 b) noexcept
    {
        return { CompareLess(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareLess(Vector1 a, Vector1 b) noexcept
    {
        return { CompareLess(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool4 mathcall CompareLessEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (a.V.F[0] <= b.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[1] <= b.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[2] <= b.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (a.V.F[3] <= b.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmple_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vreinterpretq_f32_u32(vcleq_f32(a.V, b.V)) };
#endif
    }

    mathinline Bool3 mathcall CompareLessEqual(Vector3 a, Vector3 b) noexcept
    {
        return { CompareLessEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool2 mathcall CompareLessEqual(Vector2 a, Vector2 b) noexcept
    {
        return { CompareLessEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Bool1 mathcall CompareLessEqual(Vector1 a, Vector1 b) noexcept
    {
        return { CompareLessEqual(Vector4{ a.V }, Vector4{ b.V }).V };
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    mathinline Bool4 mathcall CompareNan(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                FloatTraits<float>::BitIsNan(v.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                FloatTraits<float>::BitIsNan(v.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                FloatTraits<float>::BitIsNan(v.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                FloatTraits<float>::BitIsNan(v.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v.V, v.V) };
#endif
    }

    mathinline Bool3 mathcall CompareNan(Vector3 v) noexcept
    {
        return Bool3{ CompareNan(Vector4{ v.V }).V };
    }

    mathinline Bool2 mathcall CompareNan(Vector2 v) noexcept
    {
        return Bool2{ CompareNan(Vector4{ v.V }).V };
    }

    mathinline Bool1 mathcall CompareNan(Vector1 v) noexcept
    {
        return Bool1{ CompareNan(Vector4{ v.V }).V };
    }


#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    mathinline Bool4 mathcall CompareInfinite(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                FloatTraits<float>::BitIsInf(v.V.U[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                FloatTraits<float>::BitIsInf(v.V.U[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                FloatTraits<float>::BitIsInf(v.V.U[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                FloatTraits<float>::BitIsInf(v.V.U[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const abs_v = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const result = _mm_cmpeq_ps(abs_v, Impl::VEC4_INFINITY.V);
        return { result };
#endif
    }

    mathinline Bool3 mathcall CompareInfinite(Vector3 v) noexcept
    {
        return Bool3{ CompareInfinite(Vector4{ v.V }).V };
    }

    mathinline Bool2 mathcall CompareInfinite(Vector2 v) noexcept
    {
        return Bool2{ CompareInfinite(Vector4{ v.V }).V };
    }

    mathinline Bool1 mathcall CompareInfinite(Vector1 v) noexcept
    {
        return Bool1{ CompareInfinite(Vector4{ v.V }).V };
    }

    mathinline Bool4 mathcall CompareInBounds(Vector4 v, Vector4 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
                (-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]) ? Impl::SELECT_1 : Impl::SELECT_0,
                (-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]) ? Impl::SELECT_1 : Impl::SELECT_0,
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const result = _mm_and_ps(mask_le, mask_ge);
        return { result };
#endif
    }

    mathinline Bool3 mathcall CompareInBounds(Vector3 v, Vector3 bounds) noexcept
    {
        return Bool3{ CompareInBounds(Vector4{ v.V }, Vector4{ bounds.V }).V };
    }

    mathinline Bool2 mathcall CompareInBounds(Vector2 v, Vector2 bounds) noexcept
    {
        return Bool2{ CompareInBounds(Vector4{ v.V }, Vector4{ bounds.V }).V };
    }

    mathinline Bool1 mathcall CompareInBounds(Vector1 v, Vector1 bounds) noexcept
    {
        return Bool1{ CompareInBounds(Vector4{ v.V }, Vector4{ bounds.V }).V };
    }

    mathinline bool mathcall IsZero(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.F[0] == 0.0F)
            && (v.V.F[1] == 0.0F)
            && (v.V.F[2] == 0.0F)
            && (v.V.F[3] == 0.0F);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const mask = _mm_cmpeq_ps(v.V, zero);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsZero(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.F[0] == 0.0F)
            && (v.V.F[1] == 0.0F)
            && (v.V.F[2] == 0.0F);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const mask = _mm_cmpeq_ps(v.V, zero);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsZero(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.F[0] == 0.0F)
            && (v.V.F[1] == 0.0F);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const mask = _mm_cmpeq_ps(v.V, zero);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsZero(Vector1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (v.V.F[0] == 0.0F);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const mask = _mm_cmpeq_ps(v.V, zero);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsZero(float v) noexcept
    {
        return v == 0.0F;
    }

    mathinline bool mathcall IsZero(Vector4 v, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
            && (fabsf(v.V.F[1]) <= epsilon.V.F[1])
            && (fabsf(v.V.F[2]) <= epsilon.V.F[2])
            && (fabsf(v.V.F[3]) <= epsilon.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs = _mm_max_ps(v.V, negative);
        __m128 const mask = _mm_cmple_ps(abs, epsilon.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsZero(Vector3 v, Vector3 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
            && (fabsf(v.V.F[1]) <= epsilon.V.F[1])
            && (fabsf(v.V.F[2]) <= epsilon.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs = _mm_max_ps(v.V, negative);
        __m128 const mask = _mm_cmple_ps(abs, epsilon.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsZero(Vector2 v, Vector2 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
            && (fabsf(v.V.F[1]) <= epsilon.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs = _mm_max_ps(v.V, negative);
        __m128 const mask = _mm_cmple_ps(abs, epsilon.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsZero(Vector1 v, Vector1 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (fabsf(v.V.F[0]) <= epsilon.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs = _mm_max_ps(v.V, negative);
        __m128 const mask = _mm_cmple_ps(abs, epsilon.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsZero(float v, float epsilon) noexcept
    {
        return fabsf(v) <= epsilon;
    }

    mathinline bool mathcall IsEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] == b.V.F[0])
            && (a.V.F[1] == b.V.F[1])
            && (a.V.F[2] == b.V.F[2])
            && (a.V.F[3] == b.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsEqual(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] == b.V.F[0])
            && (a.V.F[1] == b.V.F[1])
            && (a.V.F[2] == b.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsEqual(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] == b.V.F[0])
            && (a.V.F[1] == b.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsEqual(Vector1 a, Vector1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] == b.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsEqual(float a, float b) noexcept
    {
        return (a == b);
    }

    mathinline bool mathcall IsEqual(Vector4 a, Vector4 b, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = fabsf(a.V.F[0] - b.V.F[0]);
        float const fy = fabsf(a.V.F[1] - b.V.F[1]);
        float const fz = fabsf(a.V.F[2] - b.V.F[2]);
        float const fw = fabsf(a.V.F[3] - b.V.F[3]);

        return (fx <= epsilon.V.F[0])
            && (fy <= epsilon.V.F[1])
            && (fz <= epsilon.V.F[2])
            && (fw <= epsilon.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const dv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const nv = _mm_sub_ps(zero, dv);
        __m128 const av = _mm_max_ps(nv, dv);
        __m128 const mask = _mm_cmple_ps(av, epsilon.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsEqual(Vector3 a, Vector3 b, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = fabsf(a.V.F[0] - b.V.F[0]);
        float const fy = fabsf(a.V.F[1] - b.V.F[1]);
        float const fz = fabsf(a.V.F[2] - b.V.F[2]);

        return (fx <= epsilon.V.F[0])
            && (fy <= epsilon.V.F[1])
            && (fz <= epsilon.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const dv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const nv = _mm_sub_ps(zero, dv);
        __m128 const av = _mm_max_ps(nv, dv);
        __m128 const mask = _mm_cmple_ps(av, epsilon.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsEqual(Vector2 a, Vector2 b, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = fabsf(a.V.F[0] - b.V.F[0]);
        float const fy = fabsf(a.V.F[1] - b.V.F[1]);

        return (fx <= epsilon.V.F[0])
            && (fy <= epsilon.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const dv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const nv = _mm_sub_ps(zero, dv);
        __m128 const av = _mm_max_ps(nv, dv);
        __m128 const mask = _mm_cmple_ps(av, epsilon.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsEqual(Vector1 a, Vector1 b, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = fabsf(a.V.F[0] - b.V.F[0]);

        return (fx <= epsilon.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const dv = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const nv = _mm_sub_ps(zero, dv);
        __m128 const av = _mm_max_ps(nv, dv);
        __m128 const mask = _mm_cmple_ps(av, epsilon.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsEqual(float a, float b, float epsilon) noexcept
    {
        return (fabsf(a - b) <= epsilon);
    }

    mathinline bool mathcall IsNotEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] != b.V.F[0])
            || (a.V.F[1] != b.V.F[1])
            || (a.V.F[2] != b.V.F[2])
            || (a.V.F[3] != b.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) != 0);
#endif
    }

    mathinline bool mathcall IsNotEqual(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] != b.V.F[0])
            || (a.V.F[1] != b.V.F[1])
            || (a.V.F[2] != b.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0111) != 0b0111;
#endif
    }

    mathinline bool mathcall IsNotEqual(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] != b.V.F[0])
            || (a.V.F[1] != b.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0011) != 0b0011;
#endif
    }

    mathinline bool mathcall IsNotEqual(Vector1 a, Vector1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] != b.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0001) != 0b0001;
#endif
    }

    mathinline bool mathcall IsNotEqual(float a, float b) noexcept
    {
        return (a != b);
    }

    mathinline bool mathcall IsGreater(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] > b.V.F[0])
            && (a.V.F[1] > b.V.F[1])
            && (a.V.F[2] > b.V.F[2])
            && (a.V.F[3] > b.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsGreater(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] > b.V.F[0])
            && (a.V.F[1] > b.V.F[1])
            && (a.V.F[2] > b.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsGreater(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] > b.V.F[0])
            && (a.V.F[1] > b.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsGreater(Vector1 a, Vector1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] > b.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsGreater(float a, float b) noexcept
    {
        return (a > b);
    }

    mathinline bool mathcall IsGreaterEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] >= b.V.F[0])
            && (a.V.F[1] >= b.V.F[1])
            && (a.V.F[2] >= b.V.F[2])
            && (a.V.F[3] >= b.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpge_ps(a.V, b.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsGreaterEqual(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] >= b.V.F[0])
            && (a.V.F[1] >= b.V.F[1])
            && (a.V.F[2] >= b.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpge_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsGreaterEqual(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] >= b.V.F[0])
            && (a.V.F[1] >= b.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpge_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsGreaterEqual(Vector1 a, Vector1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] >= b.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpge_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsGreaterEqual(float a, float b) noexcept
    {
        return (a >= b);
    }

    mathinline bool mathcall IsLess(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] < b.V.F[0])
            && (a.V.F[1] < b.V.F[1])
            && (a.V.F[2] < b.V.F[2])
            && (a.V.F[3] < b.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmplt_ps(a.V, b.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsLess(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] < b.V.F[0])
            && (a.V.F[1] < b.V.F[1])
            && (a.V.F[2] < b.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmplt_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsLess(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] < b.V.F[0])
            && (a.V.F[1] < b.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmplt_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsLess(Vector1 a, Vector1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] < b.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmplt_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsLess(float a, float b) noexcept
    {
        return (a < b);
    }

    mathinline bool mathcall IsLessEqual(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] <= b.V.F[0])
            && (a.V.F[1] <= b.V.F[1])
            && (a.V.F[2] <= b.V.F[2])
            && (a.V.F[3] <= b.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmple_ps(a.V, b.V);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool mathcall IsLessEqual(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] <= b.V.F[0])
            && (a.V.F[1] <= b.V.F[1])
            && (a.V.F[2] <= b.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmple_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool mathcall IsLessEqual(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] <= b.V.F[0])
            && (a.V.F[1] <= b.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmple_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool mathcall IsLessEqual(Vector1 a, Vector1 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return (a.V.F[0] <= b.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmple_ps(a.V, b.V);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool mathcall IsLessEqual(float a, float b) noexcept
    {
        return (a <= b);
    }

    mathinline bool InBounds(Vector4 v, Vector4 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
            && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
            && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]))
            && ((-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]));
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask = _mm_and_ps(mask_le, mask_ge);
        return _mm_movemask_ps(mask) == 0b1111;
#endif
    }

    mathinline bool InBounds(Vector3 v, Vector3 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
            && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
            && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]));
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask = _mm_and_ps(mask_le, mask_ge);
        return (_mm_movemask_ps(mask) & 0b0111) == 0b0111;
#endif
    }

    mathinline bool InBounds(Vector2 v, Vector2 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
            && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]));
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask = _mm_and_ps(mask_le, mask_ge);
        return (_mm_movemask_ps(mask) & 0b0011) == 0b0011;
#endif
    }

    mathinline bool InBounds(Vector1 v, Vector1 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]));
#elif GRAPHYTE_HW_AVX
        __m128 const mask_le = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::VEC4_NEGATIVE_ONE_4.V);
        __m128 const mask_ge = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask = _mm_and_ps(mask_le, mask_ge);
        return (_mm_movemask_ps(mask) & 0b0001) == 0b0001;
#endif
    }

    mathinline bool IsNan(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsNan(v.V.F[0])
            || FloatTraits<float>::IsNan(v.V.F[1])
            || FloatTraits<float>::IsNan(v.V.F[2])
            || FloatTraits<float>::IsNan(v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);
        return _mm_movemask_ps(mask) != 0;
#endif
    }

    mathinline bool IsNan(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsNan(v.V.F[0])
            || FloatTraits<float>::IsNan(v.V.F[1])
            || FloatTraits<float>::IsNan(v.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);
        return (_mm_movemask_ps(mask) & 0b0111) != 0;
#endif
    }

    mathinline bool IsNan(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsNan(v.V.F[0])
            || FloatTraits<float>::IsNan(v.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);
        return (_mm_movemask_ps(mask) & 0b0011) != 0;
#endif
    }

    mathinline bool IsNan(Vector1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsNan(v.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);
        return (_mm_movemask_ps(mask) & 0b0001) != 0;
#endif
    }

    mathinline bool IsInfinity(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsInf(v.V.F[0])
            || FloatTraits<float>::IsInf(v.V.F[1])
            || FloatTraits<float>::IsInf(v.V.F[2])
            || FloatTraits<float>::IsInf(v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        __m128 const abs = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);
        return _mm_movemask_ps(mask) != 0;
#endif
    }

    mathinline bool IsInfinity(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsInf(v.V.F[0])
            || FloatTraits<float>::IsInf(v.V.F[1])
            || FloatTraits<float>::IsInf(v.V.F[2]);
#elif GRAPHYTE_HW_AVX
        __m128 const abs = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);

        return (_mm_movemask_ps(mask) & 0b0111) != 0;
#endif
    }

    mathinline bool IsInfinity(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsInf(v.V.F[0])
            || FloatTraits<float>::IsInf(v.V.F[1]);
#elif GRAPHYTE_HW_AVX
        __m128 const abs = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);

        return (_mm_movemask_ps(mask) & 0b0111) != 0;
#endif
    }

    mathinline bool IsInfinity(Vector1 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return FloatTraits<float>::IsInf(v.V.F[0]);
#elif GRAPHYTE_HW_AVX
        __m128 const abs = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);

        return (_mm_movemask_ps(mask) & 0b0111) != 0;
#endif
    }

    mathinline bool IsInfinity(Quaternion q) noexcept
    {
        return IsInfinity(Vector4{ q.V });
    }

    mathinline bool IsInfinity(Plane q) noexcept
    {
        return IsInfinity(Vector4{ q.V });
    }
}

// =================================================================================================
//
// Component-wise operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Min(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] < b.V.F[0]) ? a.V.F[0] : b.V.F[0],
                (a.V.F[1] < b.V.F[1]) ? a.V.F[1] : b.V.F[1],
                (a.V.F[2] < b.V.F[2]) ? a.V.F[2] : b.V.F[2],
                (a.V.F[3] < b.V.F[3]) ? a.V.F[3] : b.V.F[3],
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_min_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vminq_f32(a.V, b.V) };
#endif
    }

    mathinline Vector3 mathcall Min(Vector3 a, Vector3 b) noexcept
    {
        return { Min(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector2 mathcall Min(Vector2 a, Vector2 b) noexcept
    {
        return { Min(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector1 mathcall Min(Vector1 a, Vector1 b) noexcept
    {
        return { Min(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline float mathcall Min(float a, float b) noexcept
    {
        return (a < b) ? a : b;
    }

    mathinline Vector4 mathcall Max(Vector4 a, Vector4 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                (a.V.F[0] < b.V.F[0]) ? b.V.F[0] : a.V.F[0],
                (a.V.F[1] < b.V.F[1]) ? b.V.F[1] : a.V.F[1],
                (a.V.F[2] < b.V.F[2]) ? b.V.F[2] : a.V.F[2],
                (a.V.F[3] < b.V.F[3]) ? b.V.F[3] : a.V.F[3],
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_max_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vmaxq_f32(a.V, b.V) };
#endif
    }

    mathinline Vector3 mathcall Max(Vector3 a, Vector3 b) noexcept
    {
        return { Max(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector2 mathcall Max(Vector2 a, Vector2 b) noexcept
    {
        return { Max(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline Vector1 mathcall Max(Vector1 a, Vector1 b) noexcept
    {
        return { Max(Vector4{ a.V }, Vector4{ b.V }).V };
    }

    mathinline float mathcall Max(float a, float b) noexcept
    {
        return (a > b) ? a : b;
    }

    mathinline Vector4 mathcall Clamp(Vector4 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(IsLessEqual(min, max));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const below = Max(min, v);
        Vector4 const result = Min(max, below);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const below = _mm_max_ps(min.V, v.V);
        __m128 const result = _mm_min_ps(max.V, below);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const below = vmaxq_f32(min.V, v.V);
        float32x4_t const result = vminq_f32(max.V, below);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Clamp(Vector3 v, Vector3 min, Vector3 max) noexcept
    {
        return { Clamp(Vector4{ v.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline Vector2 mathcall Clamp(Vector2 v, Vector2 min, Vector2 max) noexcept
    {
        return { Clamp(Vector4{ v.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline Vector1 mathcall Clamp(Vector1 v, Vector1 min, Vector1 max) noexcept
    {
        return { Clamp(Vector4{ v.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline float mathcall Clamp(float v, float min, float max) noexcept
    {
        float const below = Max(min, v);
        float const result = Min(max, below);
        return result;
    }

    mathinline Vector4 mathcall Saturate(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const zero = Zero<Vector4>();
        Vector4 const one = One<Vector4>();
        return Clamp(v, zero, one);
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();
        __m128 const one = Impl::VEC4_ONE_4.V;
        __m128 const below = _mm_max_ps(v.V, zero);
        __m128 const result = _mm_min_ps(below, one);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0F);
        float32x4_t const one = vdupq_n_f32(1.0F);
        float32x4_t const below = vmaxq_f32(v.V, zero);
        float32x4_t const result = vminq_f32(below, one);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Saturate(Vector3 v) noexcept
    {
        return { Saturate(Vector4{ v.V }).V };
    }

    mathinline Vector2 mathcall Saturate(Vector2 v) noexcept
    {
        return { Saturate(Vector4{ v.V }).V };
    }

    mathinline Vector1 mathcall Saturate(Vector1 v) noexcept
    {
        return { Saturate(Vector4{ v.V }).V };
    }

    mathinline float mathcall Saturate(float v) noexcept
    {
        float const below = Max(0.0F, v);
        float const result = Min(1.0F, below);
        return result;
    }

    mathinline Vector4 mathcall Wrap(Vector4 v, Vector4 min, Vector4 max) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const range0 = (max.V.F[0] - min.V.F[0]);
        float const range1 = (max.V.F[1] - min.V.F[1]);
        float const range2 = (max.V.F[2] - min.V.F[2]);
        float const range3 = (max.V.F[3] - min.V.F[3]);

        float const progress0 = (v.V.F[0] - min.V.F[0]);
        float const progress1 = (v.V.F[1] - min.V.F[1]);
        float const progress2 = (v.V.F[2] - min.V.F[2]);
        float const progress3 = (v.V.F[3] - min.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
                min.V.F[0] + progress0 + (range0 * floorf(progress0 / range0)),
                min.V.F[1] + progress1 + (range1 * floorf(progress1 / range1)),
                min.V.F[2] + progress2 + (range2 * floorf(progress2 / range2)),
                min.V.F[3] + progress3 + (range3 * floorf(progress3 / range3)),
            } } };
#elif GRAPHYTE_HW_AVX
        __m128 const range = _mm_sub_ps(max.V, min.V);
        __m128 const progress = _mm_sub_ps(v.V, min.V);

        __m128 const ratio = _mm_div_ps(progress, range);

        __m128 const base = _mm_floor_ps(ratio);

        __m128 const addend = Impl::avx_fmadd_f32x4(range, base, progress);

        __m128 const result = _mm_add_ps(min.V, addend);

        return { result };
#endif
    }

    mathinline Vector3 mathcall Wrap(Vector3 v, Vector3 min, Vector3 max) noexcept
    {
        return { Wrap(Vector4{ v.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline Vector2 mathcall Wrap(Vector2 v, Vector2 min, Vector2 max) noexcept
    {
        return { Wrap(Vector4{ v.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline Vector1 mathcall Wrap(Vector1 v, Vector1 min, Vector1 max) noexcept
    {
        return { Wrap(Vector4{ v.V }, Vector4{ min.V }, Vector4{ max.V }).V };
    }

    mathinline float mathcall Wrap(float v, float min, float max) noexcept
    {
        float const range = (max - min);
        float const progress = (v - min);
        return min + progress + (range * floorf(progress / range));
    }
}


// =================================================================================================
//
// Horizontal operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Hmin(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c0 = Min(v.V.F[0], v.V.F[1]);
        float const c1 = Min(v.V.F[2], v.V.F[3]);
        float const c2 = Min(c0, c1);

        Impl::ConstFloat32x4 const result{ { {
                c2,
                c2,
                c2,
                c2,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        // {z,w, ...}
        __m128 const low_23 = _mm_movehl_ps(v.V, v.V);
        // {min(x,z), min(y,w), ...}
        __m128 const min_01_23 = _mm_min_ps(low_23, v.V);
        // {min(y,w)...}
        __m128 const min_11_11 = _mm_permute_ps(min_01_23, _MM_SHUFFLE(1, 1, 1, 1));
        // {min(min(x,z), min(y,w)}
        __m128 const min = _mm_min_ps(min_01_23, min_11_11);
        // {}.xxxx
        __m128 const result = _mm_permute_ps(min, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hmin(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c0 = Min(v.V.F[0], v.V.F[1]);
        float const c1 = Min(v.V.F[2], c0);

        Impl::ConstFloat32x4 const result{ { {
                c1,
                c1,
                c1,
                c1,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xyzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 1, 0));
        __m128 const zzzz = _mm_movehl_ps(xyzz, xyzz);
        __m128 const min_xz_yz = _mm_min_ps(xyzz, zzzz);
        __m128 const min_yz = _mm_permute_ps(min_xz_yz, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const min = _mm_min_ps(min_xz_yz, min_yz);
        __m128 const result = _mm_permute_ps(min, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hmin(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c0 = Min(v.V.F[0], v.V.F[1]);

        Impl::ConstFloat32x4 const result{ { {
                c0,
                c0,
                c0,
                c0,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xy = v.V;
        __m128 const yy = _mm_permute_ps(xy, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const min_xy_yy = _mm_min_ps(xy, yy);
        __m128 const result = _mm_permute_ps(min_xy_yy, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hmax(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c0 = Max(v.V.F[0], v.V.F[1]);
        float const c1 = Max(v.V.F[2], v.V.F[3]);
        float const c2 = Max(c0, c1);

        Impl::ConstFloat32x4 const result{ { {
                c2,
                c2,
                c2,
                c2,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        // {z,w, ...}
        __m128 const low_23 = _mm_movehl_ps(v.V, v.V);
        // {max(x,z), max(y,w), ...}
        __m128 const max_01_23 = _mm_max_ps(low_23, v.V);
        // {min(y,w)...}
        __m128 const max_11_11 = _mm_permute_ps(max_01_23, _MM_SHUFFLE(1, 1, 1, 1));
        // {min(min(x,z), min(y,w)}
        __m128 const max = _mm_max_ps(max_01_23, max_11_11);
        // {}.xxxx
        __m128 const result = _mm_permute_ps(max, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hmax(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c0 = Max(v.V.F[0], v.V.F[1]);
        float const c1 = Max(v.V.F[2], c0);

        Impl::ConstFloat32x4 const result{ { {
                c1,
                c1,
                c1,
                c1,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xyzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 1, 0));
        __m128 const zzzz = _mm_movehl_ps(xyzz, xyzz);
        __m128 const max_xz_yz = _mm_max_ps(xyzz, zzzz);
        __m128 const max_yz = _mm_permute_ps(max_xz_yz, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const max = _mm_max_ps(max_xz_yz, max_yz);
        __m128 const result = _mm_permute_ps(max, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hmax(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c0 = Max(v.V.F[0], v.V.F[1]);

        Impl::ConstFloat32x4 const result{ { {
                c0,
                c0,
                c0,
                c0,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xy = v.V;
        __m128 const yy = _mm_permute_ps(xy, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const max_xy_yy = _mm_max_ps(xy, yy);
        __m128 const result = _mm_permute_ps(max_xy_yy, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }
    mathinline Vector4 mathcall Hsum(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c = (v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xy_zw = _mm_hadd_ps(v.V, v.V);
        __m128 const result = _mm_hadd_ps(xy_zw, xy_zw);
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hsum(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c = (v.V.F[0] + v.V.F[1] + v.V.F[2]);

        Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xyz0 = _mm_and_ps(v.V, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const xy_zz = _mm_hadd_ps(xyz0, xyz0);
        __m128 const result = _mm_hadd_ps(xy_zz, xy_zz);
        return { result };
#endif
    }

    mathinline Vector4 mathcall Hsum(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const c = (v.V.F[0] + v.V.F[1]);

        Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yx = _mm_movelh_ps(v.V, v.V);
        __m128 const result = _mm_hadd_ps(yx, yx);
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
        Vector4 const base = Subtract(b, a);
        Vector4 const t = Divide(length, base);
        Vector4 const r0 = NegateMultiplyAdd(t, Replicate<Vector4>(2.0F), Replicate<Vector4>(3.0F));
        Vector4 const r1 = Multiply(r0, t);
        Vector4 const r2 = Multiply(r1, t);
        return r2;
    }

    mathinline Vector3 mathcall Smoothstep(Vector3 a, Vector3 b, Vector4 x) noexcept
    {
        return Vector3{ Smoothstep(Vector4{ a.V }, Vector4{ b.V }, x).V };
    }

    mathinline Vector2 mathcall Smoothstep(Vector2 a, Vector2 b, Vector4 x) noexcept
    {
        return Vector2{ Smoothstep(Vector4{ a.V }, Vector4{ b.V }, x).V };
    }

    mathinline Vector4 mathcall Smoothstep(Vector4 a, Vector4 b, float x) noexcept
    {
        return Smoothstep(a, b, Replicate<Vector4>(x));
    }

    mathinline Vector3 mathcall Smoothstep(Vector3 a, Vector3 b, float x) noexcept
    {
        return Smoothstep(a, b, Replicate<Vector4>(x));
    }

    mathinline Vector2 mathcall Smoothstep(Vector2 a, Vector2 b, float x) noexcept
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
        float const t0 = (1.0F - Cos(t * Impl::PI<float>)) * 0.5F;
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

        float const ox = 1.0F - x;
        float const oxox = ox * ox;
        float const xx = 1.0F - oxox;
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

        float const ox = 1.0F - x;
        float const oxoxox = ox * ox * ox;
        float const xx = 1.0F - oxoxox;
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
        float const fdot =
            (a.V.F[0] * b.V.F[0]) +
            (a.V.F[1] * b.V.F[1]) +
            (a.V.F[2] * b.V.F[2]) +
            (a.V.F[3] * b.V.F[3]);

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
        float const fdot =
            (a.V.F[0] * b.V.F[0]) +
            (a.V.F[1] * b.V.F[1]) +
            (a.V.F[2] * b.V.F[2]);

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
        float const fdot =
            (a.V.F[0] * b.V.F[0]) +
            (a.V.F[1] * b.V.F[1]);

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
        Vector4 const length = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Length(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Length(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = Sqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length = _mm_sqrt_ps(length_squared);
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
        Vector4 const length = SqrtEst(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall LengthEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = SqrtEst(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall LengthEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const length = SqrtEst(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLength(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length = InvSqrt(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const inv_length = _mm_sqrt_ps(length_squared);
        __m128 const one = Impl::VEC4_ONE_4.V;
        __m128 const length = _mm_div_ps(one, inv_length);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLength(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length = InvSqrt(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const inv_length = _mm_sqrt_ps(length_squared);
        __m128 const one = Impl::VEC4_ONE_4.V;
        __m128 const length = _mm_div_ps(one, inv_length);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLength(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length = InvSqrt(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const inv_length = _mm_sqrt_ps(length_squared);
        __m128 const one = Impl::VEC4_ONE_4.V;
        __m128 const length = _mm_div_ps(one, inv_length);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLengthEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length = InvSqrtEst(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLengthEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length = InvSqrtEst(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x7F);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall ReciprocalLengthEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length_squared = LengthSquared(v);
        Vector4 const rcp_length = InvSqrtEst(length_squared);
        return rcp_length;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0x3F);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    mathinline Vector4 mathcall Distance(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const difference = Subtract(b, a);
        Vector4 const result = Length(difference);
        return result;
    }

    mathinline Vector3 mathcall Distance(Vector3 a, Vector3 b) noexcept
    {
        Vector3 const difference = Subtract(b, a);
        Vector4 const result = Length(difference);
        return Vector3{ result.V };
    }

    mathinline Vector2 mathcall Distance(Vector2 a, Vector2 b) noexcept
    {
        Vector2 const difference = Subtract(b, a);
        Vector4 const result = Length(difference);
        return Vector2{ result.V };
    }

    mathinline float mathcall Distance(float a, float b) noexcept
    {
        return fabsf(b - a);
    }

    mathinline Vector4 mathcall DistanceSquared(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const difference = Subtract(b, a);
        Vector4 const result = LengthSquared(difference);
        return result;
    }

    mathinline Vector4 mathcall DistanceSquared(Vector3 a, Vector3 b) noexcept
    {
        Vector3 const difference = Subtract(b, a);
        Vector4 const result = LengthSquared(difference);
        return result;
    }

    mathinline Vector4 mathcall DistanceSquared(Vector2 a, Vector2 b) noexcept
    {
        Vector2 const difference = Subtract(b, a);
        Vector4 const result = LengthSquared(difference);
        return result;
    }

    mathinline float mathcall DistanceSquared(float a, float b) noexcept
    {
        float const difference = b - a;
        float const result = difference * difference;
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

    mathinline bool mathcall IsUnit(Vector3 v) noexcept
    {
        return IsUnit(Vector4{ v.V });
    }

    mathinline bool mathcall IsUnit(Vector2 v) noexcept
    {
        return IsUnit(Vector4{ v.V });
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
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

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
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

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
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    mathinline Vector4 mathcall NormalizeEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const rcp_length = ReciprocalLength(v);
        Vector4 const result = Multiply(v, rcp_length);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        __m128 const result = _mm_mul_ps(length, v.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall NormalizeEst(Vector3 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const rcp_length = ReciprocalLength(v);
        Vector3 const result = Multiply(v, Vector3{ rcp_length.V });
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        __m128 const result = _mm_mul_ps(length, v.V);
        return { result };
#endif
    }

    mathinline Vector2 mathcall NormalizeEst(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const rcp_length = ReciprocalLength(v);
        Vector2 const result = Multiply(v, Vector2{ rcp_length.V });
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, 0xFF);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        __m128 const result = _mm_mul_ps(length, v.V);
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
        Vector4 const zero = Zero<Vector4>();

        Vector4 const rcp_length = InvSqrt(length_squared);
        Bool4 const mask_inf_length = BitCompareEqual(length_squared, Vector4{ Impl::VEC4_INFINITY.V });
        Bool4 const mask_zero_length = CompareEqual(length_squared, zero);

        Vector4 const normal = Multiply(v, rcp_length);
        Vector4 const length = Multiply(length_squared, rcp_length);

        Bool4 const select = CompareEqual(mask_inf_length, mask_zero_length);
        Vector4 const select_length = Select(length_squared, length, select);
        Vector4 const select_normal = Select(length_squared, normal, select);

        Bool4 const control_max = CompareGreater(select_length, max);
        Bool4 const control_min = CompareLess(select_length, min);

        Vector4 const clamp_length_0 = Select(select_length, max, control_max);
        Vector4 const clamp_length_1 = Select(clamp_length_0, min, control_min);

        Vector4 const clamped = Multiply(select_normal, clamp_length_1);
        Bool4 const control = CompareEqual(control_max, control_min);
        Vector4 const result = Select(clamped, v, control);
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
        Vector4 const zero = Zero<Vector4>();

        Vector4 const rcp_length = InvSqrt(length_squared);
        Bool4 const mask_inf_length = BitCompareEqual(length_squared, Vector4{ Impl::VEC4_INFINITY.V });
        Bool4 const mask_zero_length = CompareEqual(length_squared, zero);

        Vector4 const normal = Multiply(Vector4{ v.V }, rcp_length);
        Vector4 const length = Multiply(length_squared, rcp_length);

        Bool4 const select = CompareEqual(mask_inf_length, mask_zero_length);
        Vector4 const select_length = Select(length_squared, length, select);
        Vector4 const select_normal = Select(length_squared, normal, select);

        Bool4 const control_max = CompareGreater(select_length, max);
        Bool4 const control_min = CompareLess(select_length, min);

        Vector4 const clamp_length_0 = Select(select_length, max, control_max);
        Vector4 const clamp_length_1 = Select(clamp_length_0, min, control_min);

        Vector4 const clamped = Multiply(select_normal, clamp_length_1);
        Bool4 const control = CompareEqual(control_max, control_min);
        Vector4 const result = Select(clamped, Vector4{ v.V }, control);
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
        Vector4 const zero = Zero<Vector4>();

        Vector4 const rcp_length = InvSqrt(length_squared);
        Bool4 const mask_inf_length = BitCompareEqual(length_squared, Vector4{ Impl::VEC4_INFINITY.V });
        Bool4 const mask_zero_length = CompareEqual(length_squared, zero);

        Vector4 const normal = Multiply(Vector4{ v.V }, rcp_length);
        Vector4 const length = Multiply(length_squared, rcp_length);

        Bool4 const select = CompareEqual(mask_inf_length, mask_zero_length);
        Vector4 const select_length = Select(length_squared, length, select);
        Vector4 const select_normal = Select(length_squared, normal, select);

        Bool4 const control_max = CompareGreater(select_length, max);
        Bool4 const control_min = CompareLess(select_length, min);

        Vector4 const clamp_length_0 = Select(select_length, max, control_max);
        Vector4 const clamp_length_1 = Select(clamp_length_0, min, control_min);

        Vector4 const clamped = Multiply(select_normal, clamp_length_1);
        Bool4 const control = CompareEqual(control_max, control_min);
        Vector4 const result = Select(clamped, Vector4{ v.V }, control);
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
        Vector4 const dot = Dot(incident, normal);
        Vector4 const dot2 = Add(dot, dot);
        Vector4 const result = NegateMultiplyAdd(dot2, normal, incident);
        return result;
    }

    mathinline Vector3 mathcall Reflect(Vector3 incident, Vector3 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal) * normal
        Vector4 const dot = Dot(incident, normal);
        Vector4 const dot2 = Add(dot, dot);
        Vector3 const result = NegateMultiplyAdd(Vector3{ dot2.V }, normal, incident);
        return result;
    }

    mathinline Vector2 mathcall Reflect(Vector2 incident, Vector2 normal) noexcept
    {
        // result = incident - (2 * dot(incident, normal) * normal
        Vector4 const dot = Dot(incident, normal);
        Vector4 const dot2 = Add(dot, dot);
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
        Vector3 const dot0 = Vector3{ Dot(reference, incident).V };
        Vector3 const sign0 = Sign(dot0);
        Vector3 const r0 = Multiply(sign0, Replicate<Vector3>(-1.0f));
        Vector3 const r1 = Multiply(normal, r0);
        return r1;
    }

    mathinline Vector2 mathcall FaceForward(Vector2 normal, Vector2 incident, Vector2 reference) noexcept
    {
        Vector2 const dot0 = Vector2{ Dot(reference, incident).V };
        Vector2 const sign0 = Sign(dot0);
        Vector2 const r0 = Multiply(sign0, Replicate<Vector2>(-1.0f));
        Vector2 const r1 = Multiply(normal, r0);
        return r1;
    }

    mathinline Vector4 mathcall AngleBetweenNormals(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const cos_angle = Dot(a, b);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenNormals(Vector3 a, Vector3 b) noexcept
    {
        Vector4 const cos_angle = Dot(a, b);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenNormals(Vector2 a, Vector2 b) noexcept
    {
        Vector4 const cos_angle = Dot(a, b);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenVectors(Vector4 a, Vector4 b) noexcept
    {
        Vector4 const rcp_len_a = ReciprocalLength(a);
        Vector4 const rcp_len_b = ReciprocalLength(b);

        Vector4 const a_dot_b = Dot(a, b);
        Vector4 const rcp_len_ab_sq = Multiply(rcp_len_a, rcp_len_b);
        Vector4 const cos_angle = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenVectors(Vector3 a, Vector3 b) noexcept
    {
        Vector4 const rcp_len_a = ReciprocalLength(a);
        Vector4 const rcp_len_b = ReciprocalLength(b);

        Vector4 const a_dot_b = Dot(a, b);
        Vector4 const rcp_len_ab_sq = Multiply(rcp_len_a, rcp_len_b);
        Vector4 const cos_angle = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle = Acos(cos_angle_clamped);
        return angle;
    }

    mathinline Vector4 mathcall AngleBetweenVectors(Vector2 a, Vector2 b) noexcept
    {
        Vector4 const rcp_len_a = ReciprocalLength(a);
        Vector4 const rcp_len_b = ReciprocalLength(b);

        Vector4 const a_dot_b = Dot(a, b);
        Vector4 const rcp_len_ab_sq = Multiply(rcp_len_a, rcp_len_b);
        Vector4 const cos_angle = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to Acos range
        Vector4 const cos_angle_clamped = Clamp(cos_angle, { Impl::VEC4_NEGATIVE_ONE_4.V }, { Impl::VEC4_ONE_4.V });
        Vector4 const angle = Acos(cos_angle_clamped);
        return angle;
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

        __m128 const zwxy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 0, 3, 2));
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
        __m128 const r0 = _mm_mul_ps(wwww, m.M.R[3]);
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r1 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], r0);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r2 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r1);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r3 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r2);
        return { r3 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const x = vmulq_lane_f32(m.M.R[0], xy, 0);
        float32x4_t const y = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x2_t const zw = vget_high_f32(v.V);
        float32x4_t const z = vmlaq_lane_f32(y, m.M.R[2], zw, 0);
        float32x4_t const w = vmlaq_lane_f32(z, m.M.R[3], zw, 1);
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
        __m128 const r0 = _mm_sub_ps(m0, m1);
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

        Vector4 const r0 = Permute<4, 0, 0, 0>(As<Vector4>(negv), As<Vector4>(s));
        Vector4 const r1 = Permute<4, 0, 0, 0>(As<Vector4>(v), As<Vector4>(d));

        Vector4 const result = Select(r1, r0, Bool4{ select.V });

        return As<Vector3>(result);
    }

    mathinline void mathcall ComponentsFromNormal(Vector3& out_parallel, Vector3& out_perpendicular, Vector3 v, Vector3 n) noexcept
    {
        Vector4 const scale = Dot(v, n);
        Vector3 const parallel = Multiply(n, As<Vector3>(scale));

        out_parallel = parallel;
        out_perpendicular = Subtract(v, parallel);
    }

    mathinline Vector3 mathcall Transform(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4 = As<Vector4>(v);
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0 = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1 = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2 = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return As<Vector3>(r2);
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const r2 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        return { r2 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x2_t const zn = vget_high_f32(v.V);
        float32x4_t const x = vmlaq_lane_f32(m.M.R[3], m.M.R[0], xy, 0);
        float32x4_t const y = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x4_t const z = vmlaq_lane_f32(y, m.M.R[2], zn, 0);
        return { z };
#endif
    }

    mathinline Vector3 mathcall TransformCoord(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4 = As<Vector4>(v);
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0 = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1 = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2 = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        Vector4 const wwww = SplatW<Vector4>(r2);
        Vector4 const result = Divide(r2, wwww);
        return As<Vector3>(result);
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r2 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        __m128 const wwww = _mm_permute_ps(r2, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r3 = _mm_div_ps(r2, wwww);
        return { r3 };
#endif
    }

    mathinline Vector3 mathcall TransformNormal(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4 = As<Vector4>(v);
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0 = Multiply(zzzz, Vector4{ m.M.R[2] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1 = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2 = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return As<Vector3>(r2);
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0 = _mm_mul_ps(xxxx, m.M.R[2]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const zzzz = _mm_broadcastss_ps(v.V);
        __m128 const r2 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[0], r1);
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
        __m128 const b_yx = _mm_permute_ps(b.V, _MM_SHUFFLE(0, 1, 0, 1));
        __m128 const b_yx_mul_a_xy = _mm_mul_ps(b_yx, a.V);

        __m128 const bx_mul_ay = _mm_permute_ps(b_yx_mul_a_xy, _MM_SHUFFLE(1, 1, 1, 1));
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
        __m128 const result = _mm_mul_ps(partial, Impl::VEC4_NEGATE_X.V);
        return { result };
#endif
    }

    mathinline Vector2 mathcall Transform(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4 = As<Vector4>(v);
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0 = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1 = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return As<Vector2>(r1);
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const y = vmlaq_lane_f32(m.M.R[3], m.M.R[1], xy, 1);
        float32x4_t const x = vmlaq_lane_f32(y, m.M.R[0], xy, 0);
        return { x };
#endif
    }

    mathinline Vector2 mathcall TransformCoord(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4 = As<Vector4>(v);
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0 = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1 = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        Vector4 const wwww = SplatW(r1);
        Vector4 const r2 = Divide(r1, wwww);
        return As<Vector2>(r2);
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        __m128 const wwww = _mm_permute_ps(r1, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r2 = _mm_div_ps(r1, wwww);
        return { r2 };
#endif
    }

    mathinline Vector2 mathcall TransformNormal(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4 = As<Vector4>(v);
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0 = Multiply(yyyy, { m.M.R[1] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1 = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return As<Vector2>(r1);
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0 = _mm_mul_ps(yyyy, m.M.R[1]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
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
        Vector4 const zero = Zero<Vector4>();
        Vector4 const length = Length(q);
        Quaternion const conj = Conjugate(q);
        Bool4 const control = CompareLessEqual(length, Epsilon<Vector4>());
        Vector4 const normalized_conj = Divide(As<Vector4>(conj), length);
        Vector4 const result = Select(normalized_conj, zero, control);
        return As<Quaternion>(result);
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

    [[deprecated("Not supported on quaternion. Multiply by inverse.")]]
    mathinline Quaternion mathcall Divide(Quaternion q) noexcept = delete;

    mathinline Quaternion mathcall Multiply(Quaternion q, Vector4 v) noexcept
    {
        return As<Quaternion>(Multiply(As<Vector4>(q), v));
    }

    mathinline Quaternion mathcall Divide(Quaternion q, Vector4 v) noexcept
    {
        return As<Quaternion>(Divide(As<Vector4>(q), v));
    }

    mathinline Quaternion mathcall Exp(Quaternion q) noexcept
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
        return As<Quaternion>(result);
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


    mathinline Quaternion mathcall Log(Quaternion q) noexcept
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
        Vector4 const q = MultiplyAdd(qa1, sscs_zzzz, qb1);
        return Quaternion{ q.V };
    }

    template <>
    mathinline Quaternion mathcall CreateFromEuler<Quaternion>(float x, float y, float z) noexcept
    {
        Vector3 const angles = Make<Vector3>(x, y, z);
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

        Vector4 const scale = Make<Vector4>(fsin, fsin, fsin, fcos);
        Vector4 const result = Multiply(qv, scale);
        return As<Quaternion>(result);
#elif GRAPHYTE_HW_AVX
        __m128 const normal_xyz = _mm_and_ps(normal.V, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const normal_xyz1 = _mm_or_ps(normal_xyz, Impl::VEC4_POSITIVE_UNIT_W.V);
        __m128 const scale = _mm_set_ps1(0.5F * angle);

        Vector4 vsin;
        Vector4 vcos;
        SinCos(vsin, vcos, Vector4{ scale });

        __m128 const sin_xyzn = _mm_and_ps(vsin.V, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 const cos_nnnw = _mm_and_ps(vcos.V, Impl::VEC4_MASK_COMPONENT_W.V);

        __m128 const sincos_xyzw = _mm_or_ps(sin_xyzn, cos_nnnw);
        __m128 const result = _mm_mul_ps(normal_xyz1, sincos_xyzw);
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
    __m128 const r0_xxx = _mm_permute_ps(r0_xyz, _MM_SHUFFLE(0,0,0,0));
    __m128 const r1_yyy = _mm_permute_ps(r1_xyz, _MM_SHUFFLE(1,1,1,1));
    __m128 const r2_zzz = _mm_permute_ps(r2_xyz, _MM_SHUFFLE(2,2,2,2));

    __m128 const sub_m11_m00 = _mm_sub_ps(r1_yyy, r0_xxx);
    __m128 const mask_x2_ge_y2 = _mm_cmple_ps(sub_m11_m00, _mm_setzero_ps());

    __m128 const add_m11_m00 = _mm_add_ps(r1_yyy, r0_xxx);
    __m128 const mask_z2_ge_w2 = _mm_cmple_ps(add_m11_m00, _mm_setzero_ps());

    __m128 const mask_x2y2_ge_z2w2 = _mm_cmple_ps(r2_zzz, _mm_setzero_ps());

    __m128 const t0_0 = _mm_mul_ps(const_p1_m1_m1_p1.V, r0_xxx);
    __m128 const t1_0 = _mm_mul_ps(const_m1_p1_m1_p1.V, r1_yyy);
    __m128 const t2_0 = _mm_mul_ps(const_m1_m1_p1_p1.V, r2_zzz);

    __m128 const x2y2z2w2_0 = _mm_add_ps(t0_0, t1_0);
    __m128 const x2y2z2w2_1 = _mm_add_ps(t2_0, x2y2z2w2_0);
    __m128 const x2y2z2w2_2 = _mm_add_ps(x2y2z2w2_1, Impl::VEC4_ONE_4.V);

    __m128 const t0_1 = _mm_shuffle_ps(r0_xyz, r1_xyz, _MM_SHUFFLE(1,2,2,1));
    __m128 const t1_1_a = _mm_shuffle_ps(r1_xyz, r2_xyz, _MM_SHUFFLE(1,0,0,0));
    __m128 const t1_1 = _mm_permute_ps(t1_1_a, _MM_SHUFFLE(1,3,2,0));

    __m128 const xyxzyz = _mm_add_ps(t0_1, t1_1);

    __m128 const t0_2 = _mm_shuffle_ps(r2_xyz, r1_xyz, _MM_SHUFFLE(0,0,0,1));
    __m128 const t1_2_a = _mm_shuffle_ps(r1_xyz, r0_xyz, _MM_SHUFFLE(1,2,2,2));
    __m128 const t1_2 = _mm_permute_ps(t1_2_a, _MM_SHUFFLE(1,3,2,0));

    __m128 const xwywzw_0 = _mm_sub_ps(t0_2, t1_2);
    __m128 const xwywzw_1 = _mm_mul_ps(const_m1_p1_m1_p1.V, xwywzw_0);

    __m128 const t0_3 = _mm_shuffle_ps(x2y2z2w2_2, xyxzyz, _MM_SHUFFLE(0,0,1,0));
    __m128 const t1_3 = _mm_shuffle_ps(x2y2z2w2_2, xwywzw_1, _MM_SHUFFLE(0,2,3,2));
    __m128 const t2_3 = _mm_shuffle_ps(xyxzyz, xwywzw_1, _MM_SHUFFLE(1,0,2,1));

    __m128 const tensor0 = _mm_shuffle_ps(t0_3, t2_3, _MM_SHUFFLE(2,0,2,0));
    __m128 const tensor1 = _mm_shuffle_ps(t0_3, t2_3, _MM_SHUFFLE(3,1,1,2));
    __m128 const tensor2 = _mm_shuffle_ps(t2_3, t1_3, _MM_SHUFFLE(2,0,1,0));
    __m128 const tensor3 = _mm_shuffle_ps(t2_3, t1_3, _MM_SHUFFLE(1,2,3,2));

    __m128 const ga0 = _mm_and_ps(mask_x2_ge_y2, tensor0);
    __m128 const gb0 = _mm_andnot_ps(mask_x2_ge_y2, tensor1);
    __m128 const t0 = _mm_or_ps(ga0, gb0);

    __m128 const ga1 = _mm_and_ps(mask_z2_ge_w2, tensor2);
    __m128 const gb1 = _mm_andnot_ps(mask_z2_ge_w2, tensor3);
    __m128 const t1 = _mm_or_ps(ga1, gb1);

    __m128 const m0 = _mm_and_ps(mask_x2y2_ge_z2w2, t0);
    __m128 const m1 = _mm_andnot_ps(mask_x2y2_ge_z2w2, t1);
    __m128 const m2 = _mm_or_ps(m0, m1);

    __m128 const length = Length(As<Vector4>(m2)).V;

    return { _mm_div_ps(m2, length) };
#endif
    }

    template <>
    mathinline Quaternion mathcall CreateFromAxisAngle<Quaternion>(Vector3 axis, float angle) noexcept
    {
        GX_ASSERT(IsNotEqual(axis, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(axis));

        Vector3 const normal = Normalize(axis);
        Quaternion const result = CreateFromNormalAngle<Quaternion>(normal, angle);
        return result;
    }

    mathinline void mathcall ToAxisAngle(Vector3& axis, float& angle, Quaternion q) noexcept
    {
        axis = As<Vector3>(q);
        angle = 2.0F * Acos(GetW(q));
    }

    mathinline Vector3 Rotate(Vector3 v, Quaternion q) noexcept
    {
        Quaternion const a = As<Quaternion>(Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ v.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V }
        ));

        Quaternion const qn = Conjugate(q);
        Quaternion const qa = Multiply(q, a);
        Quaternion const qaqn = Multiply(qa, qn);
        return As<Vector3>(qaqn);
    }

    mathinline Vector3 InverseRotate(Vector3 v, Quaternion q) noexcept
    {
        Quaternion const a = As<Quaternion>(Select(
            Vector4{ Impl::VEC4_MASK_SELECT_1110.V },
            Vector4{ v.V },
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V }
        ));

        Quaternion const qn = Conjugate(q);
        Quaternion const qna = Multiply(qn, a);
        Quaternion const qnaq = Multiply(qna, q);
        return As<Vector3>(qnaq);
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
        float m30, float m31, float m32, float m33
    ) noexcept
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

    mathinline Matrix mathcall Load(Float4x4A const* source) noexcept
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

    mathinline void mathcall Store(Float4x4A* destination, Matrix m) noexcept
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

    mathinline Matrix mathcall Load(Float4x3A const* source) noexcept
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

    mathinline void mathcall Store(Float4x3A* destination, Matrix m) noexcept
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
    mathinline Matrix mathcall Load(Float3x4A const* source) noexcept
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

    mathinline void mathcall Store(Float3x4A* destination, Matrix m) noexcept
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

    mathinline Matrix mathcall Load(Float4x4 const* source) noexcept
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

    mathinline void mathcall Store(Float4x4* destination, Matrix m) noexcept
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

    mathinline Matrix mathcall Load(Float4x3 const* source) noexcept
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

    mathinline void mathcall Store(Float4x3* destination, Matrix m) noexcept
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
    mathinline Matrix mathcall Load(Float3x4 const* source) noexcept
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

    mathinline void mathcall Store(Float3x4* destination, Matrix m) noexcept
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

    mathinline Matrix mathcall Load(Float3x3 const* source) noexcept
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

    mathinline void mathcall Store(Float3x3* destination, Matrix m) noexcept
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
        result.M.R[0] = vmulq_f32(c.V, vdupq_lane_f32(vget_low_f32(r.V), 0));
        result.M.R[1] = vmulq_f32(c.V, vdupq_lane_f32(vget_low_f32(r.V), 1));
        result.M.R[2] = vmulq_f32(c.V, vdupq_lane_f32(vget_high_f32(r.V), 0));
        result.M.R[3] = vmulq_f32(c.V, vdupq_lane_f32(vget_high_f32(r.V), 1));
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(0, 0, 0, 0)));
        result.M.R[1] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(1, 1, 1, 1)));
        result.M.R[2] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(2, 2, 2, 2)));
        result.M.R[3] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(3, 3, 3, 3)));
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
        result.M.R[0] = Add(As<Vector4>(m1.M.R[0]), As<Vector4>(m2.M.R[0])).V;
        result.M.R[1] = Add(As<Vector4>(m1.M.R[1]), As<Vector4>(m2.M.R[1])).V;
        result.M.R[2] = Add(As<Vector4>(m1.M.R[2]), As<Vector4>(m2.M.R[2])).V;
        result.M.R[3] = Add(As<Vector4>(m1.M.R[3]), As<Vector4>(m2.M.R[3])).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vaddq_f32(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = vaddq_f32(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = vaddq_f32(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = vaddq_f32(m1.M.R[3], m2.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_add_ps(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = _mm_add_ps(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = _mm_add_ps(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = _mm_add_ps(m1.M.R[3], m2.M.R[3]);
#endif
        return result;
    }

    mathinline Matrix mathcall Subtract(Matrix m1, Matrix m2) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Subtract(As<Vector4>(m1.M.R[0]), As<Vector4>(m2.M.R[0])).V;
        result.M.R[1] = Subtract(As<Vector4>(m1.M.R[1]), As<Vector4>(m2.M.R[1])).V;
        result.M.R[2] = Subtract(As<Vector4>(m1.M.R[2]), As<Vector4>(m2.M.R[2])).V;
        result.M.R[3] = Subtract(As<Vector4>(m1.M.R[3]), As<Vector4>(m2.M.R[3])).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vsubq_f32(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = vsubq_f32(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = vsubq_f32(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = vsubq_f32(m1.M.R[3], m2.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_sub_ps(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = _mm_sub_ps(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = _mm_sub_ps(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = _mm_sub_ps(m1.M.R[3], m2.M.R[3]);
#endif
        return result;
    }

    mathinline Matrix mathcall Negate(Matrix m) noexcept
    {
        Matrix result;
        result.M.R[0] = Negate(As<Vector4>(m.M.R[0])).V;
        result.M.R[1] = Negate(As<Vector4>(m.M.R[1])).V;
        result.M.R[2] = Negate(As<Vector4>(m.M.R[2])).V;
        result.M.R[3] = Negate(As<Vector4>(m.M.R[3])).V;
        return result;
    }

    mathinline Matrix mathcall Multiply(float s, Matrix m) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(As<Vector4>(m.M.R[0]), s).V;
        result.M.R[1] = Multiply(As<Vector4>(m.M.R[1]), s).V;
        result.M.R[2] = Multiply(As<Vector4>(m.M.R[2]), s).V;
        result.M.R[3] = Multiply(As<Vector4>(m.M.R[3]), s).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0] = vmulq_f32(m.M.R[0], sv);
        result.M.R[1] = vmulq_f32(m.M.R[1], sv);
        result.M.R[2] = vmulq_f32(m.M.R[2], sv);
        result.M.R[3] = vmulq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0] = _mm_mul_ps(m.M.R[0], sv);
        result.M.R[1] = _mm_mul_ps(m.M.R[1], sv);
        result.M.R[2] = _mm_mul_ps(m.M.R[2], sv);
        result.M.R[3] = _mm_mul_ps(m.M.R[3], sv);
#endif
        return result;
    }

    mathinline Matrix mathcall Multiply(Matrix m, float s) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(As<Vector4>(m.M.R[0]), s).V;
        result.M.R[1] = Multiply(As<Vector4>(m.M.R[1]), s).V;
        result.M.R[2] = Multiply(As<Vector4>(m.M.R[2]), s).V;
        result.M.R[3] = Multiply(As<Vector4>(m.M.R[3]), s).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0] = vmulq_f32(m.M.R[0], sv);
        result.M.R[1] = vmulq_f32(m.M.R[1], sv);
        result.M.R[2] = vmulq_f32(m.M.R[2], sv);
        result.M.R[3] = vmulq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0] = _mm_mul_ps(m.M.R[0], sv);
        result.M.R[1] = _mm_mul_ps(m.M.R[1], sv);
        result.M.R[2] = _mm_mul_ps(m.M.R[2], sv);
        result.M.R[3] = _mm_mul_ps(m.M.R[3], sv);
#endif
        return result;
    }

    mathinline Matrix mathcall Divide(Matrix m, float s) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const sv = Replicate<Vector4>(s);
        result.M.R[0] = Divide(As<Vector4>(m.M.R[0]), sv).V;
        result.M.R[1] = Divide(As<Vector4>(m.M.R[1]), sv).V;
        result.M.R[2] = Divide(As<Vector4>(m.M.R[2]), sv).V;
        result.M.R[3] = Divide(As<Vector4>(m.M.R[3]), sv).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0] = vdivq_f32(m.M.R[0], sv);
        result.M.R[1] = vdivq_f32(m.M.R[1], sv);
        result.M.R[2] = vdivq_f32(m.M.R[2], sv);
        result.M.R[3] = vdivq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0] = _mm_div_ps(m.M.R[0], sv);
        result.M.R[1] = _mm_div_ps(m.M.R[1], sv);
        result.M.R[2] = _mm_div_ps(m.M.R[2], sv);
        result.M.R[3] = _mm_div_ps(m.M.R[3], sv);
#endif
        return result;
    }

    mathinline Matrix mathcall ComponentMultiply(Matrix a, Matrix b) noexcept
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(As<Vector4>(a.M.R[0]), As<Vector4>(b.M.R[0])).V;
        result.M.R[1] = Multiply(As<Vector4>(a.M.R[1]), As<Vector4>(b.M.R[1])).V;
        result.M.R[2] = Multiply(As<Vector4>(a.M.R[2]), As<Vector4>(b.M.R[2])).V;
        result.M.R[3] = Multiply(As<Vector4>(a.M.R[3]), As<Vector4>(b.M.R[3])).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vmulq_f32(a.M.R[0], b.M.R[0]);
        result.M.R[1] = vmulq_f32(a.M.R[1], b.M.R[1]);
        result.M.R[2] = vmulq_f32(a.M.R[2], b.M.R[2]);
        result.M.R[3] = vmulq_f32(a.M.R[3], b.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_mul_ps(a.M.R[0], b.M.R[0]);
        result.M.R[1] = _mm_mul_ps(a.M.R[1], b.M.R[1]);
        result.M.R[2] = _mm_mul_ps(a.M.R[2], b.M.R[2]);
        result.M.R[3] = _mm_mul_ps(a.M.R[3], b.M.R[3]);
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
        __m128 const x_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);
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
        __m128 const x_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);
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
        __m128 const x_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);
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
        __m128 const x_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);
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
        __m128 const m_r0 = a.M.R[0];
        __m128 const x_r0 = _mm_broadcastss_ps(m_r0);
        __m128 const y_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);
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
        __m128 const x_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);
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
        __m128 const x_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);
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
        __m128 const x_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);
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
        __m128 const ea0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const ea1 = _mm_shuffle_ps(tmp1, ra1, _MM_SHUFFLE(0, 3, 0, 2));
        __m128 const eb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const eb1 = _mm_shuffle_ps(tmp1, ra1, _MM_SHUFFLE(2, 1, 2, 1));
        __m128 const ec0 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const ec1 = _mm_shuffle_ps(tmp2, rb1, _MM_SHUFFLE(0, 3, 0, 2));
        __m128 const ed0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const ed1 = _mm_shuffle_ps(tmp2, rb1, _MM_SHUFFLE(2, 1, 2, 1));

        __m128 const fa0 = _mm_mul_ps(ea0, ea1);
        __m128 const fb0 = _mm_mul_ps(eb0, eb1);
        __m128 const fc0 = _mm_mul_ps(ec0, ec1);
        __m128 const fd0 = _mm_mul_ps(ed0, ed1);

        __m128 const tmp3 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(0, 0, 1, 0));
        __m128 const ga0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const ga1 = _mm_shuffle_ps(ra1, tmp3, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const gb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const gb1 = _mm_shuffle_ps(ra1, tmp3, _MM_SHUFFLE(0, 2, 1, 2));

        __m128 const tmp4 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(2, 2, 1, 0));
        __m128 const gc0 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const gc1 = _mm_shuffle_ps(rb1, tmp4, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const gd0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const gd1 = _mm_shuffle_ps(rb1, tmp4, _MM_SHUFFLE(0, 2, 1, 2));

        __m128 const fa1 = Impl::avx_fnmadd_f32x4(ga0, ga1, fa0);
        __m128 const fb1 = Impl::avx_fnmadd_f32x4(gb0, gb1, fb0);
        __m128 const fc1 = Impl::avx_fnmadd_f32x4(gc0, gc1, fc0);
        __m128 const fd1 = Impl::avx_fnmadd_f32x4(gd0, gd1, fd0);

        __m128 const ha0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(0, 3, 0, 3));

        __m128 const tmp5 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 0, 2, 2));
        __m128 const ha1 = _mm_permute_ps(tmp5, _MM_SHUFFLE(0, 2, 3, 0));
        __m128 const hb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(2, 0, 3, 1));

        __m128 const tmp6 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 0, 3, 0));
        __m128 const hb1 = _mm_permute_ps(tmp6, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const hc0 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(0, 3, 0, 3));

        __m128 const tmp7 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const hc1 = _mm_permute_ps(tmp7, _MM_SHUFFLE(0, 2, 3, 0));
        __m128 const hd0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(2, 0, 3, 1));

        __m128 const tmp8 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 2, 3, 0));
        __m128 const hd1 = _mm_permute_ps(tmp8, _MM_SHUFFLE(2, 1, 0, 3));

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
        static Impl::ConstFloat32x4 const sign{ { {
                1.0f,
                -1.0f,
                1.0f,
                -1.0f
            } } };

        Vector4 const r2_yxxx = Swizzle<1, 0, 0, 0>(As<Vector4>(m.M.R[2]));
        Vector4 const r3_zzyy = Swizzle<2, 2, 1, 1>(As<Vector4>(m.M.R[3]));
        Vector4 const r3_wwwz = Swizzle<3, 3, 3, 2>(As<Vector4>(m.M.R[3]));
        Vector4 const r2_zzyy = Swizzle<2, 2, 1, 1>(As<Vector4>(m.M.R[2]));

        Vector4 const pa0 = Multiply(r2_yxxx, r3_zzyy);
        Vector4 const pa1 = Multiply(r2_yxxx, r3_wwwz);
        Vector4 const pa2 = Multiply(r2_zzyy, r3_wwwz);

        Vector4 const r3_yxxx = Swizzle<1, 0, 0, 0>(As<Vector4>(m.M.R[3]));
        Vector4 const r2_wwwz = Swizzle<3, 3, 3, 2>(As<Vector4>(m.M.R[2]));

        Vector4 const pb0 = NegateMultiplyAdd(r2_zzyy, r3_yxxx, pa0);
        Vector4 const pb1 = NegateMultiplyAdd(r2_wwwz, r3_yxxx, pa1);
        Vector4 const pb2 = NegateMultiplyAdd(r2_wwwz, r3_zzyy, pa2);

        Vector4 const r1_wwwz = Swizzle<3, 3, 3, 2>(As<Vector4>(m.M.R[1]));
        Vector4 const r1_zzyy = Swizzle<2, 2, 1, 1>(As<Vector4>(m.M.R[1]));
        Vector4 const r1_yxxx = Swizzle<1, 0, 0, 0>(As<Vector4>(m.M.R[1]));

        Vector4 const s0 = Multiply(As<Vector4>(m.M.R[0]), As<Vector4>(sign.V));
        Vector4 const t0 = Multiply(r1_wwwz, pb0);
        Vector4 const t1 = NegateMultiplyAdd(r1_zzyy, pb1, t0);
        Vector4 const t2 = MultiplyAdd(r1_yxxx, pb2, t1);

        return Dot(s0, t2);
    }

    mathinline bool mathcall Decompose(
        Vector4& out_scale,
        Quaternion& out_rotation,
        Vector4& out_translation,
        Matrix m
    ) noexcept
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
        GetX(&scales[0], Length(As<Vector3>(*basis[0])));
        GetX(&scales[1], Length(As<Vector3>(*basis[1])));
        GetX(&scales[2], Length(As<Vector3>(*basis[2])));
        scales[3] = 0.0f;

        auto decompose_rank_abc = [](size_t& a, size_t& b, size_t& c, float x, float y, float z)
        {
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

        (*basis[a]) = Normalize(As<Vector3>(*basis[a])).V;

        if (scales[b] < DecomposeEpsilon)
        {
            float const absx = fabsf(GetX(As<Vector4>(*basis[a])));
            float const absy = fabsf(GetY(As<Vector4>(*basis[a])));
            float const absz = fabsf(GetZ(As<Vector4>(*basis[a])));

            size_t const cc = [](float x, float y, float z) -> size_t
            {
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

            (*basis[b]) = Cross(As<Vector3>(*basis[a]), As<Vector3>(*canonical_basis[cc])).V;
        }

        (*basis[b]) = Normalize(As<Vector3>(*basis[b])).V;

        if (scales[c] < DecomposeEpsilon)
        {
            (*basis[c]) = Cross(As<Vector3>(*basis[a]), As<Vector3>(*basis[b])).V;
        }

        (*basis[c]) = Normalize(As<Vector3>(*basis[c])).V;

        float det = GetX(Determinant(temp));

        if (det < 0.0f)
        {
            scales[a] = -scales[a];
            (*basis[a]) = Negate(As<Vector4>(*basis[a])).V;
            det = -det;
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

        uint32_t one = items[0] ^ 0x3f80'0000;
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

        Vector4 const n0 = Swizzle<1, 2, 0, 3>(As<Vector4>(normal));
        Vector4 const n1 = Swizzle<2, 0, 1, 3>(As<Vector4>(normal));

        Vector4 const g0 = Multiply(c2, n0);
        Vector4 const g1 = Multiply(g0, n1);

        Vector4 const h0 = Multiply(c2, As<Vector4>(normal));
        Vector4 const h1 = MultiplyAdd(h0, As<Vector4>(normal), c1);

        Vector4 const i0 = MultiplyAdd(c0, As<Vector4>(normal), g1);
        Vector4 const i1 = NegateMultiplyAdd(c0, As<Vector4>(normal), g1);

        Vector4 const r0 = Select(a, h1, As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V));

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
        result.M.R[2] = r5;
        result.M.R[3] = Impl::VEC4_POSITIVE_UNIT_W.V;

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
        Vector4 const q_xyzw = As<Vector4>(q);

        Vector4 const q0 = Add(q_xyzw, q_xyzw);
        Vector4 const q1 = Multiply(q_xyzw, q0);

        Vector4 const q1_yxx_1 = Permute<1, 0, 0, 7>(q1, As<Vector4>(Impl::VEC4_ONE_3.V));
        Vector4 const q1_zzy_1 = Permute<2, 2, 1, 7>(q1, As<Vector4>(Impl::VEC4_ONE_3.V));
        Vector4 const o0 = Subtract(As<Vector4>(Impl::VEC4_ONE_3.V), q1_yxx_1);
        Vector4 const s0 = Subtract(o0, q1_zzy_1);

        Vector4 const q_xxyw = Swizzle<0, 0, 1, 3>(q_xyzw);
        Vector4 const q0_zyzw = Swizzle<2, 1, 2, 3>(q0);
        Vector4 const m0 = Multiply(q_xxyw, q0_zyzw);

        Vector4 const q_wwww = SplatW(q_xyzw);
        Vector4 const q0_yzxw = Swizzle<1, 2, 0, 3>(q0);
        Vector4 const m1 = Multiply(q_wwww, q0_yzxw);

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
        V0 = _mm_and_ps(V0, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 V1 = _mm_permute_ps(Q1, _MM_SHUFFLE(3, 1, 2, 2));
        V1 = _mm_and_ps(V1, Impl::VEC4_MASK_SELECT_1110.V);
        __m128 R0 = _mm_sub_ps(Constant1110.V, V0);
        R0 = _mm_sub_ps(R0, V1);

        V0 = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 1, 0, 0));
        V1 = _mm_permute_ps(Q0, _MM_SHUFFLE(3, 2, 1, 2));
        V0 = _mm_mul_ps(V0, V1);

        V1 = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 V2 = _mm_permute_ps(Q0, _MM_SHUFFLE(3, 0, 2, 1));
        V1 = _mm_mul_ps(V1, V2);

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

        Q1 = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(3, 2, 3, 1));
        Q1 = _mm_permute_ps(Q1, _MM_SHUFFLE(1, 3, 0, 2));
        m.M.R[1] = Q1;

        Q1 = _mm_shuffle_ps(V1, R0, _MM_SHUFFLE(3, 2, 1, 0));
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
            As<Vector4>(Impl::VEC4_POSITIVE_UNIT_W.V),
            As<Vector4>(translation),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V)
        ).V;

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
        Vector2 translation
    ) noexcept
    {
        Vector3 const v_scaling_origin = As<Vector3>(Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1100.V),
            As<Vector4>(scaling_origin),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        ));

        // Create scanling origin transform
        Vector3 const v_scaling_origin_negated = Negate(v_scaling_origin);
        Matrix const m_scaling_origin = CreateTranslation(v_scaling_origin_negated);

        // Create scaling orientation transform
        Matrix const m_scaling_orientation = CreateRotationZ(scaling_orientation);
        Matrix const m_scaling_orientation_trn = Transpose(m_scaling_orientation);

        // Create scaling transform
        Vector3 const v_scaling_xy1 = As<Vector3>(Select(
            As<Vector4>(Impl::VEC4_ONE_4.V),
            As<Vector4>(scaling),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        ));

        Matrix const m_scaling = CreateScaling(v_scaling_xy1);

        // Create rotation origin
        Vector4 const v_rotation_origin = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1100.V),
            As<Vector4>(rotation_origin),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        );

        // Create rotation transform
        Matrix const m_rotation = CreateRotationZ(rotation);

        // Create translation vector
        Vector4 const v_translation = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1100.V),
            As<Vector4>(translation),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        );

        Matrix const m0 = Multiply(m_scaling_origin, m_scaling_orientation_trn);
        Matrix const m1 = Multiply(m0, m_scaling);

        Matrix m2 = Multiply(m1, m_scaling_orientation);
        m2.M.R[3] = Add(As<Vector4>(m2.M.R[3]), As<Vector4>(v_scaling_origin)).V;
        m2.M.R[3] = Subtract(As<Vector4>(m2.M.R[3]), v_rotation_origin).V;

        Matrix m3 = Multiply(m2, m_rotation);
        m3.M.R[3] = Add(As<Vector4>(m3.M.R[3]), v_rotation_origin).V;
        m3.M.R[3] = Add(As<Vector4>(m3.M.R[3]), v_translation).V;

        return m3;
    }

    mathinline Matrix mathcall CreateAffineTransform2D(
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation
    ) noexcept
    {
        Vector3 const v_scaling = As<Vector3>(Select(
            As<Vector4>(Impl::VEC4_ONE_4.V),
            As<Vector4>(scaling),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        ));

        Vector4 const v_rotation_origin = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1100.V),
            As<Vector4>(rotation_origin),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        );

        Vector4 const v_translation = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1100.V),
            As<Vector4>(translation),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1100.V)
        );

        Matrix const m_rotation = CreateRotationZ(rotation);

        Matrix result = CreateScaling(v_scaling);
        result.M.R[3] = Subtract(As<Vector4>(result.M.R[3]), v_rotation_origin).V;
        result = Multiply(result, m_rotation);
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), v_rotation_origin).V;
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), v_translation).V;

        return result;
    }

    mathinline Matrix mathcall CreateTransform(
        Vector3 scaling_origin,
        Quaternion scaling_orientation,
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation
    ) noexcept
    {
        Vector3 const v_scaling_origin = As<Vector3>(Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1110.V),
            As<Vector4>(scaling_origin),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V)
        ));

        Vector3 const v_scaling_origin_negated = Negate(v_scaling_origin);

        Vector4 const v_rotation_origin = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1110.V),
            As<Vector4>(rotation_origin),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V)
        );

        Vector4 const v_translation = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1110.V),
            As<Vector4>(translation),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V)
        );

        Matrix const m_scaling_origin = CreateTranslation(v_scaling_origin_negated);
        Matrix const m_scaling_orientation = CreateFromQuaternion(scaling_orientation);
        Matrix const m_scaling_orientation_trn = Transpose(m_scaling_orientation);
        Matrix const m_scaling = CreateScaling(scaling);
        Matrix const m_rotation = CreateFromQuaternion(rotation);

        Matrix result = Multiply(m_scaling_origin, m_scaling_orientation_trn);
        result = Multiply(result, m_scaling);
        result = Multiply(result, m_scaling_orientation);
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), As<Vector4>(v_scaling_origin)).V;
        result.M.R[3] = Subtract(As<Vector4>(result.M.R[3]), v_rotation_origin).V;
        result = Multiply(result, m_rotation);
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), v_rotation_origin).V;
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), v_translation).V;

        return result;
    }

    mathinline Matrix mathcall CreateAffineTransform(
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation
    ) noexcept
    {

        Vector4 const v_rotation_origin = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1110.V),
            As<Vector4>(rotation_origin),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V)
        );

        Vector4 const v_translation = Select(
            As<Vector4>(Impl::VEC4_MASK_SELECT_1110.V),
            As<Vector4>(translation),
            As<Bool4>(Impl::VEC4_MASK_SELECT_1110.V)
        );

        Matrix const m_rotation = CreateFromQuaternion(rotation);

        Matrix result = CreateScaling(scaling);
        result.M.R[3] = Subtract(As<Vector4>(result.M.R[3]), v_rotation_origin).V;
        result = Multiply(result, m_rotation);
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), v_rotation_origin).V;
        result.M.R[3] = Add(As<Vector4>(result.M.R[3]), v_translation).V;

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
        float z_far
    ) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.000001f));

        float const z_near_2 = z_near + z_near;
        float const range = z_far / (z_far - z_near);

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
        result.M.R[0] = vsetq_lane_f32(z_near_2 / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                z_near_2 / view_width,
                z_near_2 / view_height,
                range,
                -range * z_near,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

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
        float z_far
    ) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.000001f));

        float const z_near_2 = z_near + z_near;
        float const range = z_far / (z_near - z_far);

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
        result.M.R[0] = vsetq_lane_f32(z_near_2 / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::VEC4_NEGATIVE_UNIT_W.V, 2);
        result.M.R[3] = vsetq_lane_f32(range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                z_near_2 / view_width,
                z_near_2 / view_height,
                range,
                range * z_near,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

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
        float z_far
    ) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(fov_angle_y, 0.0f, 0.00001f * 2.0f));
        GX_ASSERT(!IsEqual(aspect_ratio, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float fov_sin;
        float fov_cos;
        SinCos(fov_sin, fov_cos, 0.5f * fov_angle_y);

        float const height = fov_cos / fov_sin;
        float const width = height / aspect_ratio;
        float const range = z_far / (z_far - z_near);

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
        result.M.R[0] = vsetq_lane_f32(width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                width,
                height,
                range,
                -range * z_near,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

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
        float z_far
    ) noexcept
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(fov_angle_y, 0.0f, 0.00001f * 2.0f));
        GX_ASSERT(!IsEqual(aspect_ratio, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float fov_sin;
        float fov_cos;
        SinCos(fov_sin, fov_cos, 0.5f * fov_angle_y);

        float const height = fov_cos / fov_sin;
        float const width = height / aspect_ratio;
        float const range = z_far / (z_near - z_far);

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
        result.M.R[0] = vsetq_lane_f32(width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::VEC4_NEGATIVE_UNIT_W.V, 2);
        result.M.R[3] = vsetq_lane_f32(range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                width,
                height,
                range,
                range * z_near,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

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
        float z_far
    )
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.0001f));

        float const z_near_2 = z_near + z_near;
        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = z_far / (z_far - z_near);

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
        result.M.R[0] = vsetq_lane_f32(z_near_2 * rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 * rcp_height, zero, 1);
        result.M.R[2] = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range,
            1.0f
        ).V;
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                z_near_2 * rcp_width,
                z_near_2 * rcp_height,
                -range * z_near,
                0.0f,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [z_near_2 * rcp_width, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, z_near_2 * rcp_height, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        __m128 const r2_zw = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range,
            1.0f
        ).V;

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
        float z_far
    )
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.0001f));

        float const z_near_2 = z_near + z_near;
        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = z_far / (z_near - z_far);

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
        result.M.R[0] = vsetq_lane_f32(z_near_2 * rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 * rcp_height, zero, 1);
        result.M.R[2] = Make<Vector4>(
            (view_left + view_right) * rcp_width,
            (view_top + view_bottom) * rcp_height,
            range,
            -1.0f
        ).V;
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                z_near_2 * rcp_width,
                z_near_2 * rcp_height,
                range * z_near,
                0.0f,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [z_near_2 * rcp_width, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, z_near_2 * rcp_height, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);

        __m128 const r2_zw = Make<Vector4>(
            (view_left + view_right) * rcp_width,
            (view_top + view_bottom) * rcp_height,
            range,
            -1.0f
        ).V;

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
        float z_far
    ) noexcept
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
        result.M.R[0] = vsetq_lane_f32(2.0f / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(2.0f / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = vsetq_lane_f32(-range * z_near, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                2.0f / view_width,
                2.0f / view_height,
                range,
                -range * z_near,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        __m128 const r0_x = _mm_move_ss(zero, values);
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const r2_z = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 0, 0, 0));
        __m128 const r3_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 1, 0, 0));

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
        float z_far
    ) noexcept
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
        result.M.R[0] = vsetq_lane_f32(2.0f / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(2.0f / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = vsetq_lane_f32(range * z_near, Impl::VEC4_POSITIVE_UNIT_W.V, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
                2.0f / view_width,
                2.0f / view_height,
                range,
                range * z_near,
            } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        __m128 const r0_x = _mm_move_ss(zero, values);
        __m128 const r1_y = _mm_and_ps(values, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const values2 = _mm_shuffle_ps(values, Impl::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const r2_z = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 0, 0, 0));
        __m128 const r3_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 1, 0, 0));

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
        float z_far
    ) noexcept
    {
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = 1.0f / (z_far - z_near);

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
        result.M.R[0] = vsetq_lane_f32(rcp_width + rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(rcp_height + rcp_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            -range * z_near,
            1.0f
        ).V;
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
        __m128 const zero = _mm_setzero_ps();

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
        float z_far
    ) noexcept
    {
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = 1.0f / (z_near - z_far);

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
        result.M.R[0] = vsetq_lane_f32(rcp_width + rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(rcp_height + rcp_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range * z_near,
            1.0f
        ).V;
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
        __m128 const zero = _mm_setzero_ps();

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
        __m128 const result = _mm_add_ps(neg_xyz, Impl::VEC4_ONE_3.V);
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

        Impl::ConstFloat32x4 const result{ { {
                ((v.V.F[0] - factor) * saturation) + factor,
                ((v.V.F[1] - factor) * saturation) + factor,
                ((v.V.F[2] - factor) * saturation) + factor,
                v.V.F[3]
            } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const vfactor = _mm_dp_ps(v.V, luminance.V, 0x3F);
        __m128 const vsaturation = _mm_set_ps1(saturation);
        __m128 const r0 = _mm_sub_ps(v.V, vfactor);
        __m128 const r1 = Impl::avx_fmadd_f32x4(r0, vsaturation, vfactor);
        __m128 const r2 = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
        return { r3 };
#endif
    }

    mathinline Color mathcall AdjustContrast(Color v, float contrast) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                ((v.V.F[0] - 0.5F) * contrast) + 0.5F,
                ((v.V.F[1] - 0.5F) * contrast) + 0.5F,
                ((v.V.F[2] - 0.5F) * contrast) + 0.5F,
                v.V.F[3]
            } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const vcontrast = _mm_set_ps1(contrast);
        __m128 const r0 = _mm_sub_ps(v.V, Impl::VEC4_ONE_HALF_4.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(r0, vcontrast, Impl::VEC4_ONE_HALF_4.V);
        __m128 const r2 = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
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
        Vector4 const v4_1 = Select(Vector4{ Impl::VEC4_ONE_4.V }, As<Vector4>(v), Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
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
        return As<Vector4>(Dot(As<Vector3>(p), As<Vector3>(n)));
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_dp_ps(p.V, n.V, 0x3F);
        return { result };
#endif
    }

    mathinline Plane mathcall Normalize(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float length = sqrtf(
            (p.V.F[0] * p.V.F[0]) *
            (p.V.F[1] * p.V.F[1]) *
            (p.V.F[2] * p.V.F[2])
        );

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
        __m128 const mask = _mm_cmpneq_ps(length_sq, Impl::VEC4_INFINITY.V);
        __m128 const normalized = _mm_div_ps(p.V, length);
        __m128 const result = _mm_and_ps(normalized, mask);
        return { result };
#endif
    }

    mathinline Plane mathcall NormalizeEst(Plane p) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length = ReciprocalLengthEst(As<Vector3>(p));
        Vector4 const result = Multiply(As<Vector4>(p), length);
        return As<Plane>(result);
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_dp_ps(p.V, p.V, 0x7F);
        __m128 const rcp_length = _mm_rsqrt_ps(length);
        __m128 const result = _mm_mul_ps(p.V, rcp_length);
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
        Vector4 const pl = As<Vector4>(p);

        Vector4 const vw = SplatW(pl);
        Vector4 const vz = SplatZ(pl);
        Vector4 const vy = SplatY(pl);
        Vector4 const vx = SplatX(pl);

        Vector4 const r0 = Multiply(vw, GetBaseW(m));
        Vector4 const r1 = MultiplyAdd(vz, GetBaseZ(m), r0);
        Vector4 const r2 = MultiplyAdd(vy, GetBaseY(m), r1);
        Vector4 const r3 = MultiplyAdd(vx, GetBaseX(m), r2);

        return As<Plane>(r3);
    }

    mathinline Plane mathcall CreateFromPointNormal(Vector3 point, Vector3 normal) noexcept
    {
        Vector4 const p_wwww = Dot(point, normal);
        Vector4 const n_wwww = Negate(p_wwww);
        Vector4 const abcw = Select(n_wwww, As<Vector4>(normal), Bool4{ Impl::VEC4_MASK_SELECT_1110.V });
        Plane const result = As<Plane>(abcw);
        return result;
    }

    mathinline Plane mathcall CreateFromPoints(Vector3 p1, Vector3 p2, Vector3 p3) noexcept
    {
        Vector3 const d_p21 = Subtract(p1, p2);
        Vector3 const d_p31 = Subtract(p1, p3);

        Vector3 const plane_perpendicular = Cross(d_p21, d_p31);
        Vector3 const plane_normal = Normalize(plane_perpendicular);

        Vector4 const neg_plane_distance = DotNormal(As<Plane>(plane_normal), p1);
        Vector4 const plane_distance = Negate(neg_plane_distance);

        Vector4 const result = Select(
            plane_distance,
            As<Vector4>(plane_normal),
            Bool4{ Impl::VEC4_MASK_SELECT_1110.V }
        );
        Plane const plane = As<Plane>(result);
        return plane;
    }

    mathinline Matrix mathcall Reflect(Plane reflection) noexcept
    {
        GX_ASSERT(!IsEqual(As<Vector3>(reflection), Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(reflection));

        static Impl::ConstFloat32x4 const negative_two{ { {
                -2.0f,
                -2.0f,
                -2.0f,
                0.0f
            } } };

        Vector4 const vp = As<Vector4>(Normalize(reflection));
        Vector4 const vs = Multiply(vp, As<Vector4>(negative_two.V));

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
        GX_ASSERT(!IsEqual(As<Vector3>(shadow), Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(shadow));

        Vector4 const vp = As<Vector4>(Normalize(shadow));
        Vector4 const pp = Negate(vp);
        Vector4 const p_aaaa = SplatX(pp);
        Vector4 const p_bbbb = SplatY(pp);
        Vector4 const p_cccc = SplatZ(pp);
        Vector4 const p_dddd = SplatW(pp);

        Vector4 dot = Dot(vp, light);
        dot = Select(As<Vector4>(Impl::VEC4_MASK_SELECT_0001.V), dot, As<Bool4>(Impl::VEC4_MASK_SELECT_0001.V));

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

// =================================================================================================
//
// Intersections
//

namespace Graphyte::Maths
{
    mathinline Vector3 mathcall LinePlaneIntersection(Plane plane, Vector3 start, Vector3 end) noexcept
    {
        Vector3 const plane_normal = As<Vector3>(plane);
        Vector4 const plane_normal_dot_start = Dot(plane_normal, start);
        Vector4 const plane_normal_dot_end = Dot(plane_normal, end);
        Vector4 const diff = Subtract(plane_normal_dot_start, plane_normal_dot_end);
        Vector4 const plane_dot_start = DotCoord(plane, start);
        Vector4 const normalized = Divide(plane_dot_start, diff);

        Vector3 const point_distance = Subtract(end, start);
        Vector3 const point_on_plane = MultiplyAdd(point_distance, As<Vector3>(normalized), start);

        Vector3 const zero = Zero<Vector3>();
        Bool4 const control = As<Bool4>(CompareEqual(As<Vector3>(diff), zero, Epsilon<Vector4>()));
        Vector3 const result = As<Vector3>(Select(As<Vector4>(point_on_plane), Nan<Vector4>(), control));
        return result;
    }

    mathinline void PlanePlaneIntersection(
        Vector3& out_line1,
        Vector3& out_line2,
        Plane plane1,
        Plane plane2
    ) noexcept
    {
        Vector3 const cross0 = Cross(As<Vector3>(plane2), As<Vector3>(plane1));
        Vector4 const cross0_length = Length(cross0);
        Vector3 const cross1 = Cross(As<Vector3>(plane2), cross0);
        Vector4 const plane1_wwww = SplatW(As<Vector4>(plane1));
        Vector4 const point0 = Multiply(As<Vector4>(cross1), plane1_wwww);
        Vector3 const cross2 = Cross(cross0, As<Vector3>(plane1));
        Vector4 const plane2_wwww = SplatW(As<Vector4>(plane2));
        Vector4 const point1 = MultiplyAdd(As<Vector4>(cross2), plane2_wwww, point0);
        Vector4 const linepoint1 = Divide(point1, cross0_length);
        Vector4 const linepoint2 = Add(linepoint1, As<Vector4>(cross0));
        Bool4 const control = CompareLessEqual(cross0_length, Vector4{ Impl::VEC4_EPSILON.V });

        out_line1 = As<Vector3>(Select(linepoint1, Nan<Vector4>(), control));
        out_line2 = As<Vector3>(Select(linepoint2, Nan<Vector4>(), control));
    }

    mathinline Vector2 mathcall LineLineIntersection(
        Vector2 line1_start,
        Vector2 line1_end,
        Vector2 line2_start,
        Vector2 line2_end
    ) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector2 const line1 = Subtract(line1_end, line1_start);
        Vector2 const line2 = Subtract(line2_end, line2_start);
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
            Vector2 const rcp_c0 = Reciprocal(c0);
            Vector2 const c1_div_c0 = Multiply(c1, rcp_c0);
            result = MultiplyAdd(line1, c1_div_c0, line1_start);
        }

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const line1 = _mm_sub_ps(line1_end.V, line1_start.V);
        __m128 const line2 = _mm_sub_ps(line2_end.V, line2_start.V);
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
        __m128 const fail = _mm_or_ps(fail4, fail5);

        // compute intersection
        __m128 const c1_div_c0 = _mm_div_ps(c1, c0);
        __m128 const result = Impl::avx_fmadd_f32x4(c1_div_c0, line1, line1_start.V);

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
        T const vec_line_point = Subtract(point, line1);
        T const vec_line_line = Subtract(line2, line1);
        Vector4 const length_squared = LengthSquared(vec_line_line);

        Vector4 const projection_scale_0 = Dot(vec_line_point, vec_line_line);
        T const projection_scale_1 = As<T>(Divide(projection_scale_0, length_squared));

        T const distance_0 = Multiply(vec_line_line, projection_scale_1);
        T const distance_1 = Subtract(vec_line_point, distance_0);
        return Length(As<T>(distance_1));
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
        Vector4 const result = Multiply(value, multiplier);
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
        return value * Maths::Impl::PI<float>;
    }

    mathinline Vector4 mathcall RevolutionsToGradians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(400.0F);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RevolutionsToGradians(float value) noexcept
    {
        return value * 400.0F;
    }

    mathinline Vector4 mathcall DegreesToRevolutions(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(1.0F / 360.0F);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall DegreesToRevolutions(float value) noexcept
    {
        return value / 360.0F;
    }

    mathinline Vector4 mathcall RadiansToRevolutions(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(1.0F / Maths::Impl::PI2<float>);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RadiansToRevolutions(float value) noexcept
    {
        return value / Maths::Impl::PI2<float>;
    }

    mathinline Vector4 mathcall GradiansToRevolutions(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(1.0F / 400.0F);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall GradiansToRevolutions(float value) noexcept
    {
        return value / 400.0F;
    }

    mathinline Vector4 mathcall RadiansToGradians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(200.0F / Maths::Impl::PI<float>);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RadiansToGradians(float value) noexcept
    {
        return value * (200.0F / Maths::Impl::PI<float>);
    }

    mathinline Vector4 mathcall GradiansToRadians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(Maths::Impl::PI<float> / 200.0F);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall GradiansToRadians(float value) noexcept
    {
        return value * (Maths::Impl::PI<float> / 200.0F);
    }

    mathinline Vector4 mathcall RadiansToDegrees(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(180.0F / Maths::Impl::PI<float>);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall RadiansToDegrees(float value) noexcept
    {
        return value * (180.0F / Maths::Impl::PI<float>);
    }

    mathinline Vector4 mathcall DegreesToRadians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(Maths::Impl::PI<float> / 180.0F);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall DegreesToRadians(float value) noexcept
    {
        return value * (Maths::Impl::PI<float> / 180.0F);
    }

    mathinline Vector4 mathcall GradiansToDegrees(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(9.0F / 10.0F);
        Vector4 const result = Multiply(value, multiplier);
        return result;
    }

    mathinline float mathcall GradiansToDegrees(float value) noexcept
    {
        return value * (9.0F / 10.0F);
    }

    mathinline Vector4 mathcall DegreesToGradians(Vector4 value) noexcept
    {
        Vector4 const multiplier = Replicate<Vector4>(10.0F / 9.0F);
        Vector4 const result = Multiply(value, multiplier);
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


        return static_cast<uint32_t>(value * (1U << bits));
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
        const auto radius = Sqrt(
            value.X * value.X +
            value.Y * value.Y +
            value.Z * value.Z
        );
        const auto theta = Acos(
            value.Z / radius
        );
        const auto phi = Atan(
            value.Y / value.X
        );

        return { radius, theta, phi };
    }

    mathinline Float3A mathcall SphericalToCartesian(const Float3A& value) noexcept
    {
        float sin_theta;
        float cos_theta;
        float sin_phi;
        float cos_phi;
        const auto radius = value.X;
        SinCos(sin_theta, cos_theta, value.Y);
        SinCos(sin_phi, cos_phi, value.Z);

        const auto partial = radius * sin_theta;

        return { partial * cos_phi, partial * sin_phi, radius * cos_theta };
    }

    mathinline Float3A mathcall CartesianToCylindrical(const Float3A& value) noexcept
    {
        const auto radius = Sqrt(
            value.X * value.X +
            value.Y * value.Y
        );
        const auto angle = Atan(
            value.Y / value.X
        );
        const auto elevation = value.Z;

        return { radius, angle, elevation };
    }

    mathinline Float3A mathcall CylindricalToCartesian(const Float3A& value) noexcept
    {
        const auto radius = value.X;
        const auto angle = value.Y;
        const auto elevation = value.Z;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        return { radius * cos_angle, radius * sin_angle, elevation };
    }

    mathinline Float2A mathcall PolarToCartesian(const Float2A& value) noexcept
    {
        const auto radius = value.X;
        const auto angle = value.Y;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        const auto x = radius * cos_angle;
        const auto y = radius * sin_angle;

        return { x, y };
    }

    mathinline Float2A mathcall CartesianToPolar(const Float2A& value) noexcept
    {
        const auto radius = Sqrt(
            value.X * value.X +
            value.Y * value.Y
        );
        const auto angle = Atan2(value.Y, value.X);

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
        const auto g = -Log2(1.0F - gain);
        const auto c = Power(value, gain);
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
        const auto delta = (b * b) - (4.0F * a * c);

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

        const auto denominator = 1.0F / (2.0F * a);
        const auto delta_sqrt = Sqrt(delta);

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

        auto value = static_cast<float>(seed);
        value = static_cast<float>(static_cast<double>(value)* (1.0 / 4294967296.0));
        return value;
    }

    mathinline float mathcall WrapAngle(float value) noexcept
    {
        const auto raw = value + Maths::Impl::PI<float>;
        auto abs = Abs(raw);

        const auto scaled = static_cast<float>(static_cast<int32_t>(abs / Maths::Impl::PI<float>));

        abs -= Maths::Impl::PI<float> * scaled;
        abs -= Maths::Impl::PI<float>;

        if (raw < 0.0F)
        {
            abs = -abs;
        }

        return abs;
    }

    mathinline float mathcall DiffAngle(float angle1, float angle2) noexcept
    {
        const auto r1 = angle2 - angle1;
        const auto r2 = r1 - Maths::Impl::PI2<float>;
        const auto r3 = r1 + Maths::Impl::PI2<float>;

        const auto a1 = Abs(r1);
        const auto a2 = Abs(r2);
        const auto a3 = Abs(r3);

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
        Vector4 const rcp_s1 = Reciprocal(s1);
        Vector4 const half_d1 = Multiply(Vector4{ Impl::VEC4_HALF_4.V }, d1);
        Vector4 const r0 = Multiply(half_d1, rcp_s1);

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
        __m128 const r0 = _mm_div_ps(half_d1, s1);

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
        Matrix world
    ) noexcept
    {
        float const half_width = viewport_width * 0.5F;
        float const half_height = viewport_height * 0.5F;

        Vector3 const scale = Make<Vector3>(
            half_width,
            -half_height,
            viewport_max_z - viewport_min_z
        );

        Vector3 const offset = Make<Vector3>(
            viewport_x + half_width,
            viewport_y + half_height,
            viewport_min_z
        );

        Matrix const wv = Multiply(world, view);
        Matrix const wvp = Multiply(wv, projection);

        Vector3 const tv = TransformCoord(v, wvp);
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
        Matrix world
    ) noexcept
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
            viewport_max_z - viewport_min_z
        );

        Vector3 const rcp_scale = Reciprocal(scale);

        Vector3 const offset = Make<Vector3>(
            -viewport_x,
            -viewport_y,
            -viewport_min_z
        );

        Vector3 const projected = MultiplyAdd(rcp_scale, offset, Vector3{ d.V });

        Matrix const mv = Multiply(world, view);
        Matrix const mvp = Multiply(mv, projection);
        Matrix const inv_mvp = Inverse(mvp);

        Vector3 const coord = MultiplyAdd(v, rcp_scale, projected);
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
    mathinline Color mathcall Load(ColorBGRA const* source) noexcept
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
        __m128 const c3 = _mm_cvtepi32_ps(c2);
        __m128 const c4 = _mm_add_ps(c3, Impl::VEC4_FIX_A_A8R8G8B8.V);
        __m128 const c5 = _mm_mul_ps(c4, Impl::VEC4_NORMALIZE_A8R8G8B8.V);
        return { c5 };
#endif
    }

    mathinline void mathcall Store(ColorBGRA* destination, Color color) noexcept
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const c0 = Saturate(As<Vector4>(color));
        Vector4 const c1 = Multiply(c0, As<Vector4>(Impl::VEC4_UBYTE_MAX.V));
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
        __m128 const c0 = _mm_mul_ps(color_min, Impl::VEC4_UBYTE_MAX.V);
        __m128 const c1 = _mm_permute_ps(c0, _MM_SHUFFLE(3, 0, 1, 2));
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
        Vector4 w2
    ) noexcept
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
        Vector4 z2
    ) noexcept
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
        Vector4 y2
    ) noexcept
    {
        Vector4 const r0 = Multiply(x1, x2);
        Vector4 const r1 = MultiplyAdd(y1, y2, r0);
        return r1;
    }
}
