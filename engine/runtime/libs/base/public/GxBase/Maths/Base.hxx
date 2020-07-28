#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/TypeTraits.hxx>
#include <GxBase/Ieee754.hxx>
#include <GxBase/Types.hxx>

// =================================================================================================
// `mathcall` definition

#if GRAPHYTE_HAVE_VECTORCALL
#define mathcall __vectorcall
#elif GRAPHYTE_COMPILER_MSVC
#define mathcall __fastcall
#else
#define mathcall
#endif


// =================================================================================================
// `mathinline` and `mathconst` definitions

#if GRAPHYTE_COMPILER_MSVC
#define mathinline __forceinline
// XXX: Check when we may make it `constexpr const` instead
#define mathconst extern const __declspec(selectany)
#elif GRAPHYTE_COMPILER_CLANG
#define mathinline inline __attribute__((__always_inline__))
#define mathconst  constexpr const
#else
#define mathinline inline __attribute__((__artificial__, __always_inline__))
#define mathconst  constexpr const
#endif


// =================================================================================================
// Native vector type.

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) NativeFloat32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
    struct alignas(16) NativeUInt32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
#elif GRAPHYTE_HW_NEON
    using NativeFloat32x4 = float32x4_t;
    using NativeUInt32x4  = uint32x4_t;
#elif GRAPHYTE_HW_AVX
    using NativeFloat32x4 = __m128;
    using NativeUInt32x4  = __m128i;
#else
#error Unknown architecture
#endif

    static_assert(alignof(NativeFloat32x4) == 16);
    static_assert(sizeof(NativeFloat32x4) == 16);

    static_assert(alignof(NativeUInt32x4) == 16);
    static_assert(sizeof(NativeUInt32x4) == 16);
}


// =================================================================================================
// Native matrix type

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) NativeFloat32x4x4 final
    {
        union
        {
            NativeFloat32x4 R[4];
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
                float M41, M42, M43, M44;
            };
            float M[4][4];
            float F[16];
        };
    };

#else
    struct alignas(16) NativeFloat32x4x4 final
    {
        NativeFloat32x4 R[4];
    };
#endif

    static_assert(alignof(NativeFloat32x4x4) == 16);
    static_assert(sizeof(NativeFloat32x4x4) == 64);
}


// =================================================================================================
// Constant types

namespace Graphyte::Maths::Impl
{
    struct alignas(16) ConstFloat32x4 final
    {
        union
        {
            alignas(16) float F[4];
            NativeFloat32x4 V;
        };
    };

    static_assert(std::is_trivially_copyable_v<ConstFloat32x4>);
    static_assert(std::is_standard_layout_v<ConstFloat32x4>);
    static_assert(alignof(ConstFloat32x4) == 16);
    static_assert(sizeof(ConstFloat32x4) == 16);

    struct alignas(16) ConstInt32x4 final
    {
        union
        {
            alignas(16) int32_t I[4];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };

    static_assert(std::is_trivially_copyable_v<ConstInt32x4>);
    static_assert(std::is_standard_layout_v<ConstInt32x4>);
    static_assert(alignof(ConstInt32x4) == 16);
    static_assert(sizeof(ConstInt32x4) == 16);

    struct alignas(16) ConstUInt32x4 final
    {
        union
        {
            alignas(16) uint32_t U[4];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };
    static_assert(std::is_trivially_copyable_v<ConstUInt32x4>);
    static_assert(std::is_standard_layout_v<ConstUInt32x4>);
    static_assert(alignof(ConstUInt32x4) == 16);
    static_assert(sizeof(ConstUInt32x4) == 16);

    struct alignas(16) ConstUInt8x16 final
    {
        union
        {
            alignas(16) uint8_t U[16];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };
    static_assert(std::is_trivially_copyable_v<ConstUInt8x16>);
    static_assert(std::is_standard_layout_v<ConstUInt8x16>);
    static_assert(alignof(ConstUInt8x16) == 16);
    static_assert(sizeof(ConstUInt8x16) == 16);
}


// =================================================================================================
// Include some internal specific implementation details.

#if !GRAPHYTE_MATH_NO_INTRINSICS
#if GRAPHYTE_HW_AVX
#include <GxBase/Maths/Impl/Avx.impl.hxx>
#elif GRAPHYTE_HW_NEON
#include <GxBase/Maths/Impl/Neon.impl.hxx>
#endif
#endif
#include <GxBase/Maths/Constants.hxx>


// =================================================================================================
// Standard math types

namespace Graphyte::Maths
{
    struct Bool4 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 4;

        using ComponentType = uint32_t;
        using MaskType      = Bool4;
    };

    struct Bool3 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 3;

        using ComponentType = uint32_t;
        using MaskType      = Bool3;
    };

    struct Bool2 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 2;

        using ComponentType = uint32_t;
        using MaskType      = Bool2;
    };

    struct Bool1 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 1;

        using ComponentType = uint32_t;
        using MaskType      = Bool1;
    };

    struct Vector4 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector     = void;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Vector3 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector     = void;

        static constexpr const size_t Components = 3;

        using ComponentType = float;
        using MaskType      = Bool3;
    };

    struct Vector2 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector     = void;

        static constexpr const size_t Components = 2;

        using ComponentType = float;
        using MaskType      = Bool2;
    };

    struct Vector1 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector     = void;

        static constexpr const size_t Components = 1;

        using ComponentType = float;
        using MaskType      = Bool1;
    };

    struct Matrix final
    {
        Impl::NativeFloat32x4x4 M;

        using IsSimdFloat4x4 = void;
        using IsMatrix       = void;

        static constexpr const size_t Components = 16;
        static constexpr const size_t Rows       = 4;
        static constexpr const size_t Columns    = 4;

        using ComponentType = float;
    };

    struct Color final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsColor      = void;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Plane final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsPlane      = void;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Quaternion final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsQuaternion = void;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Sphere final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsSphere     = void;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };
}


// =================================================================================================
// Traits

namespace Graphyte::Maths::Impl
{
    template <typename T>
    concept IsSimdFloat4 = requires
    {
        typename T::ComponentType;
        typename T::IsSimdFloat4;
    };

    template <typename T>
    concept IsSimdUInt4 = requires
    {
        typename T::ComponentType;
        typename T::IsSimdUInt4;
    };

    template <typename T>
    concept IsColor
        = T::Components == 4
          && requires
    {
        typename T::MaskType;
        typename T::ComponentType;

        typename T::IsSimdFloat4;
        typename T::IsColor;
    }
    &&T::Components == 4;

    template <typename T>
    concept IsQuaternion
        = T::Components == 4
          && requires
    {
        typename T::MaskType;
        typename T::ComponentType;

        typename T::IsSimdFloat4;
        typename T::IsQuaternion;
    };

    template <typename T>
    concept IsPlane
        = T::Components == 4
          && requires
    {
        typename T::MaskType;
        typename T::ComponentType;

        typename T::IsSimdFloat4;
        typename T::IsPlane;
    };

    template <typename T>
    concept IsVector = requires
    {
        typename T::MaskType;
        typename T::ComponentType;

        typename T::IsSimdFloat4;
        typename T::IsVector;
    };

    template <typename T>
    concept IsMatrix = requires
    {
        typename T::ComponentType;

        typename T::IsSimdFloat4x4;
        typename T::IsMatrix;
    };
}


// =================================================================================================
// Constant splatting

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
// Rounding internals

namespace Graphyte::Maths::Impl
{
    template <typename T>
    mathinline T mathcall RoundToNearest(T value) noexcept
    {
        T const integral = floor(value);
        T const fraction = value - integral;

        if (fraction < T(0.5))
        {
            return integral;
        }

        if (fraction > T(0.5))
        {
            return integral + T(1.0);
        }

        T integral_part;
        modf(integral / T(2.0), &integral_part);

        if ((T(2.0) * integral_part) == integral)
        {
            return integral;
        }

        return integral + T(1.0);
    }
}


// =================================================================================================
// Select control masking

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SelectControl(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        GX_ASSERT(x < 2);
        GX_ASSERT(y < 2);
        GX_ASSERT(z < 2);
        GX_ASSERT(w < 2);

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
            static_cast<int>(x));
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

    template <typename T>
    mathinline T mathcall Select(T a, T b, typename T::MaskType control) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
            a.V);
        return { result };
#endif
    }
}


// =================================================================================================
// Permutations

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Permute(T a, T b, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <size_t X, size_t Y, size_t Z, size_t W, typename T>
    mathinline T mathcall Permute(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T> && (X < 8) && (Y < 8) && (Z < 8) && (W < 8))
    {

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
// Swizzling

namespace Graphyte::Maths
{
    template <size_t X, size_t Y, size_t Z, size_t W, typename T>
    mathinline T mathcall Swizzle(T v) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && (X < 4) && (Y < 4) && (Z < 4) && (W < 4))
    {
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

    template <size_t X, size_t Y, size_t Z, typename T>
    mathinline T mathcall Swizzle(T v) noexcept
        requires(T::Components == 3 && Impl::IsSimdFloat4<T> && (X < 3) && (Y < 3) && (Z < 3))
    {
        if constexpr (X == 0 && Y == 1 && Z == 2)
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
                v.V.F[Y],
            } } };
            return { result.V };
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_swizzle<X, Y, Z, Y>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_swizzle<X, Y, Z, Y>(v.V) };
#endif
        }
    }

    template <size_t X, size_t Y, typename T>
    mathinline T mathcall Swizzle(T v) noexcept
        requires(T::Components == 2 && Impl::IsSimdFloat4<T> && (X < 2) && (Y < 2))
    {
        if constexpr (X == 0 && Y == 1)
        {
            return v;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const result{ { {
                v.V.F[X],
                v.V.F[Y],
                v.V.F[X],
                v.V.F[Y],
            } } };
            return { result.V };
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_swizzle<X, Y, X, Y>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_swizzle<X, Y, X, Y>(v.V) };
#endif
        }
    }

    template <typename T>
    mathinline T mathcall Swizzle(T v, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
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

    template <typename R, typename T>
    mathinline R mathcall MergeXY(T a, T b) noexcept
        requires(R::Components == 4 && T::Components >= 2 && Impl::IsSimdFloat4<R> && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall MergeZW(T a, T b) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
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

    template <uint32_t Count, typename T>
    mathinline T mathcall ShiftLeft(T a, T b) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && Count < 4)
    {
        return Permute<Count + 0, Count + 1, Count + 2, Count + 3>(a, b);
    }

    template <typename T>
    mathinline T mathcall ShiftLeft(T a, T b, uint32_t count) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(count < 4);
        return Permute(a, b, count + 0, count + 1, count + 2, count + 3);
    }

    template <uint32_t Count, typename T>
    mathinline T mathcall RotateLeft(T v) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && Count < 4)
    {
        return Swizzle<(Count + 0) & 0b11, (Count + 1) & 0b11, (Count + 2) & 0b11, (Count + 3) & 0b11>(v);
    }

    template <typename T>
    mathinline T mathcall RotateLeft(T v, uint32_t count) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(count < 4);

        return Swizzle(v, (count + 0) & 0b11, (count + 1) & 0b11, (count + 2) & 0b11, (count + 3) & 0b11);
    }

    template <uint32_t Count, typename T>
    mathinline T mathcall RotateRight(T v) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && Count < 4)
    {
        return Swizzle<(4 - Count) & 0b11, (5 - Count) & 0b11, (6 - Count) & 0b11, (7 - Count) & 0b11>(v);
    }

    template <typename T>
    mathinline T mathcall RotateRight(T v, uint32_t count) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(count < 4);
        return Swizzle(v, (4 - count) & 0b11, (5 - count) & 0b11, (6 - count) & 0b11, (7 - count) & 0b11);
    }
}


// =================================================================================================
// Vector insert

namespace Graphyte::Maths
{
    template <bool X, bool Y, bool Z, bool W, typename T>
    mathinline T mathcall Insert(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        constexpr uint32_t const index_x = 0 + (X ? 4 : 0);
        constexpr uint32_t const index_y = 1 + (Y ? 4 : 0);
        constexpr uint32_t const index_z = 2 + (Z ? 4 : 0);
        constexpr uint32_t const index_w = 3 + (W ? 4 : 0);
        return Permute<index_x, index_y, index_z, index_w>(a, b);
    }

    template <typename T>
    mathinline T mathcall Insert(T a, T b, bool x, bool y, bool z, bool w) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        typename T::MaskComponent const control = SelectControl<typename T::MaskComponent>(
            x ? 1 : 0,
            y ? 1 : 0,
            z ? 1 : 0,
            w ? 1 : 0);
        return Select(a, b, control);
    }

    template <typename T>
    mathinline T mathcall Insert(T a, T b, uint32_t rotate_left_count, bool x, bool y, bool z, bool w) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        typename T::MaskComponent const control = SelectControl<typename T::MaskComponent>(
            x ? 1 : 0,
            y ? 1 : 0,
            z ? 1 : 0,
            w ? 1 : 0);
        return Select(a, RotateLeft(b, rotate_left_count), control);
    }
}


// =================================================================================================
// Load / store operations

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Load(Float4A const* source) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Store(Float4A* destination, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Load(Float4 const* source) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Float4* destination, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Load(Float3A const* source) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Float3A* destination, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Load(Float3 const* source) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Float3* destination, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Load(Float2A const* source) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Float2A* destination, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Load(Float2 const* source) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Float2* destination, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Load(float const* source) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(float* destination, T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*destination) = v.V.F[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(destination, v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Half4 const* source) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Half4* destination, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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
        __m128 const h0 = _mm_cvtps_ph(v.V, _MM_FROUND_TO_NEAREST_INT);
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), h0);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Half2 const* source) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall Store(Half2* destination, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const components{
            .V = v.V
        };

        destination->X = ToHalf(components.F[0]);
        destination->Y = ToHalf(components.F[1]);
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_cvtps_ph(v.V, _MM_FROUND_TO_NEAREST_INT);
        __m128 const h1 = _mm_castsi128_ps(h0);
        _mm_store_ss(reinterpret_cast<float*>(destination), h1);
#endif
    }
}


// =================================================================================================
// Vector splatting

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SplatX(T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SplatY(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SplatZ(T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SplatW(T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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
}


// =================================================================================================
// Float lane accessors

namespace Graphyte::Maths
{
    template <typename T>
    mathinline float mathcall GetByIndex(T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetByIndex(T v, float value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V = v.V;
        result.F[index] = value;
        return { result.V };
    }

    template <typename T>
    mathinline void mathcall GetByIndex(float* result, T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetByIndex(T v, float const* value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V = v.V;
        result.F[index] = (*value);
        return { result.V };
    }

    template <typename T>
    mathinline float mathcall GetX(T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 0);
#endif
    }

    template <typename T>
    mathinline float mathcall GetY(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline float mathcall GetZ(T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline float mathcall GetW(T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall GetX(float* result, T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall GetY(float* result, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall GetZ(float* result, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline void mathcall GetW(float* result, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetX(T v, float value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetY(T v, float value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetZ(T v, float value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetW(T v, float value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetX(T v, float const* value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetY(T v, float const* value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetZ(T v, float const* value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall SetW(T v, float const* value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

}


// =================================================================================================
// UInt lane accessors

namespace Graphyte::Maths
{
    template <typename T>
    mathinline uint32_t mathcall GetByIndex(T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetByIndex(T v, uint32_t value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstUInt32x4 result;
        result.V = v.V;
        result.U[index] = value;
        return { result.V };
    }

    template <typename T>
    mathinline void mathcall GetByIndex(uint32_t* result, T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline void mathcall SetByIndex(T v, uint32_t const* value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstUInt32x4 result;
        result.V = v.V;
        result.U[index] = (*value);
        return { result.V };
    }

    template <typename T>
    mathinline uint32_t mathcall GetX(T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[0];
#elif GRAPHYTE_HW_AVX
        return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(v.V)));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 0);
#endif
    }

    template <typename T>
    mathinline uint32_t mathcall GetY(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline uint32_t mathcall GetZ(T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline uint32_t mathcall GetW(T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline void mathcall GetX(uint32_t* result, T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline void mathcall GetY(uint32_t* result, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline void mathcall GetZ(uint32_t* result, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline void mathcall GetW(uint32_t* result, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetX(T v, uint32_t value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetY(T v, uint32_t value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetZ(T v, uint32_t value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetW(T v, uint32_t value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetX(T v, uint32_t const* value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetY(T v, uint32_t const* value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetZ(T v, uint32_t const* value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall SetW(T v, uint32_t const* value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
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
// Constructors

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Make(float x, float y, float z, float w) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));

        float32x2_t const zw = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&w)) << 32));

        return { vcombine_f32(xy, zw) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));

        float32x2_t const zn = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)));

        return { vcombine_f32(xy, zn) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));

        float32x2_t const zero = vdup_n_f32(0.0F);

        return { vcombine_f32(xy, zero) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)));

        float32x2_t const zero = vdup_n_f32(0.0F);

        return { vcombine_f32(xn, zero) };
#endif
    }

    template <typename T>
    mathinline T mathcall Replicate(float value) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Replicate(float const* source) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Make(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
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
            static_cast<int>(x));

        return { _mm_castsi128_ps(ivec) };
#elif GRAPHYTE_HW_NEON
        uint32x2_t const r0_xy = vcreate_u32(static_cast<uint64_t>(x) | (static_cast<uint64_t>(y) << 32));
        uint32x2_t const r0_zw = vcreate_u32(static_cast<uint64_t>(z) | (static_cast<uint64_t>(w) << 32));

        float32x4_t const result = vreinterpretq_f32_u32(
            vcombine_u32(r0_xy, r0_zw));

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Replicate(uint32_t value) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall Replicate(uint32_t const* source) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
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
// Boolean support

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall True() noexcept
        requires(Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall False() noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result = { { { 0.0F,
            0.0F,
            0.0F,
            0.0F } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0u) };
#endif
    }

    template <typename T>
    mathinline T mathcall And(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall AndNot(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall Or(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall Xor(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall Nor(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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
            vreinterpretq_u32_f32(b.V));

        return vreinterpretq_f32_u32(vmvnq_u32(partial));
#endif
    }

    template <typename T>
    mathinline T mathcall Not(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
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
            vmvnq_u32(vreinterpretq_u32_f32(v.V)));
#endif
    }
}


// =================================================================================================
// Boolean mask comparisons

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall CompareEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline T mathcall CompareNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
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

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.U[0] == b.V.U[0])
                && (a.V.U[1] == b.V.U[1])
                && (a.V.U[2] == b.V.U[2])
                && (a.V.U[3] == b.V.U[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.U[0] == b.V.U[0])
                && (a.V.U[1] == b.V.U[1])
                && (a.V.U[2] == b.V.U[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.U[0] == b.V.U[0])
                && (a.V.U[1] == b.V.U[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.U[0] == b.V.U[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t const expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.U[0] != b.V.U[0])
                || (a.V.U[1] != b.V.U[1])
                || (a.V.U[2] != b.V.U[2])
                || (a.V.U[3] != b.V.U[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.U[0] != b.V.U[0])
                || (a.V.U[1] != b.V.U[1])
                || (a.V.U[2] != b.V.U[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.U[0] != b.V.U[0])
                || (a.V.U[1] != b.V.U[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.U[0] != b.V.U[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t const expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(a.V), _mm_castps_si128(b.V)));

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != expected;
        }
#endif
    }
}


// =================================================================================================
// Boolean mask qualification

namespace Graphyte::Maths
{
    template <typename T>
    mathinline bool mathcall AllTrue(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] != 0)
                && (v.V.U[1] != 0)
                && (v.V.U[2] != 0)
                && (v.V.U[3] != 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] != 0)
                && (v.V.U[1] != 0)
                && (v.V.U[2] != 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] != 0)
                && (v.V.U[1] != 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] != 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) == expected;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AllFalse(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] == 0)
                && (v.V.U[1] == 0)
                && (v.V.U[2] == 0)
                && (v.V.U[3] == 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] == 0)
                && (v.V.U[1] == 0)
                && (v.V.U[2] == 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] == 0)
                && (v.V.U[1] == 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] == 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) == 0;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) == 0;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AnyTrue(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] != 0)
                || (v.V.U[1] != 0)
                || (v.V.U[2] != 0)
                || (v.V.U[3] != 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] != 0)
                || (v.V.U[1] != 0)
                || (v.V.U[2] != 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] != 0)
                || (v.V.U[1] != 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] != 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) != expected;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) != 0;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall AnyFalse(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.U[0] == 0)
                || (v.V.U[1] == 0)
                || (v.V.U[2] == 0)
                || (v.V.U[3] == 0);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.U[0] == 0)
                || (v.V.U[1] == 0)
                || (v.V.U[2] == 0);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.U[0] == 0)
                || (v.V.U[1] == 0);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.U[0] == 0);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(v.V) != expected;
        }
        else
        {
            return (_mm_movemask_ps(v.V) & expected) != expected;
        }
#endif
    }
}

// =================================================================================================
// Bit comparison

namespace Graphyte::Maths
{
    template <typename T>
    mathinline typename T::MaskType BitCompareEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType BitCompareNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
}


// =================================================================================================
// Value comparison

namespace Graphyte::Maths
{
    template <typename T>
    mathinline typename T::MaskType CompareEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType CompareEqual(T a, T b, T epsilon) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType CompareNotEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType CompareGreater(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType CompareGreaterEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType CompareLess(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType CompareLessEqual(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    template <typename T>
    mathinline typename T::MaskType mathcall CompareNan(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    template <typename T>
    mathinline typename T::MaskType mathcall CompareInfinite(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline typename T::MaskType mathcall CompareInBounds(T v, T bounds) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
}


// =================================================================================================
// Generic comparisons

namespace Graphyte::Maths
{
    template <typename T>
    mathinline bool mathcall IsZero(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (v.V.F[0] == 0.0F)
                   && (v.V.F[1] == 0.0F)
                   && (v.V.F[2] == 0.0F)
                   && (v.V.F[3] == 0.0F);
        }
        else if constexpr (T::Components == 3)
        {
            return (v.V.F[0] == 0.0F)
                   && (v.V.F[1] == 0.0F)
                   && (v.V.F[2] == 0.0F);
        }
        else if constexpr (T::Components == 2)
        {
            return (v.V.F[0] == 0.0F)
                   && (v.V.F[1] == 0.0F);
        }
        else if constexpr (T::Components == 1)
        {
            return (v.V.F[0] == 0.0F);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask = _mm_cmpeq_ps(v.V, zero);


        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsZero(T v, T epsilon) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
                   && (fabsf(v.V.F[1]) <= epsilon.V.F[1])
                   && (fabsf(v.V.F[2]) <= epsilon.V.F[2])
                   && (fabsf(v.V.F[3]) <= epsilon.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
                   && (fabsf(v.V.F[1]) <= epsilon.V.F[1])
                   && (fabsf(v.V.F[2]) <= epsilon.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0])
                   && (fabsf(v.V.F[1]) <= epsilon.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (fabsf(v.V.F[0]) <= epsilon.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const zero     = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs      = _mm_max_ps(v.V, negative);
        __m128 const mask     = _mm_cmple_ps(abs, epsilon.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool IsNan(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return FloatTraits<float>::IsNan(v.V.F[0])
                   || FloatTraits<float>::IsNan(v.V.F[1])
                   || FloatTraits<float>::IsNan(v.V.F[2])
                   || FloatTraits<float>::IsNan(v.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return FloatTraits<float>::IsNan(v.V.F[0])
                   || FloatTraits<float>::IsNan(v.V.F[1])
                   || FloatTraits<float>::IsNan(v.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return FloatTraits<float>::IsNan(v.V.F[0])
                   || FloatTraits<float>::IsNan(v.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return FloatTraits<float>::IsNan(v.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const mask = _mm_cmpneq_ps(v.V, v.V);

        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != 0;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != 0;
        }
#endif
    }

    template <typename T>
    mathinline bool IsInfinity(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return FloatTraits<float>::IsInf(v.V.F[0])
                   || FloatTraits<float>::IsInf(v.V.F[1])
                   || FloatTraits<float>::IsInf(v.V.F[2])
                   || FloatTraits<float>::IsInf(v.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return FloatTraits<float>::IsInf(v.V.F[0])
                   || FloatTraits<float>::IsInf(v.V.F[1])
                   || FloatTraits<float>::IsInf(v.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return FloatTraits<float>::IsInf(v.V.F[0])
                   || FloatTraits<float>::IsInf(v.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return FloatTraits<float>::IsInf(v.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const abs  = _mm_and_ps(v.V, Impl::VEC4_MASK_ABS.V);
        __m128 const mask = _mm_cmpeq_ps(abs, Impl::VEC4_INFINITY.V);

        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) != 0;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != 0;
        }
#endif
    }
}

// =================================================================================================
// Rounding functions

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall CopySign(T number, T sign) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Sign(T x) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Ceiling(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Floor(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Truncate(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Round(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Remainder(T x, T y) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Fraction(T x) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        return Subtract(x, Floor(x));
    }
    template <typename T>
    mathinline T mathcall Min(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Max(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(IsLessEqual(min, max));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T const below = Max(min, v);
        T const result = Min(max, below);
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

    template <typename T>
    mathinline T mathcall Saturate(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const zero = Zero<T>();
        T const one = One<T>();
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

    template <typename T>
    mathinline T mathcall Wrap(T v, T min, T max) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Hmin(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
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
        }
        else if constexpr (T::Components == 3)
        {
            float const c0 = Min(v.V.F[0], v.V.F[1]);
            float const c1 = Min(v.V.F[2], c0);

            Impl::ConstFloat32x4 const result{ { {
                c1,
                c1,
                c1,
                c1,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const c0 = Min(v.V.F[0], v.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                c0,
                c0,
                c0,
                c0,
            } } };
            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
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
        }
        else if constexpr (T::Components == 3)
        {
            __m128 const xyzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 1, 0));
            __m128 const zzzz = _mm_movehl_ps(xyzz, xyzz);
            __m128 const min_xz_yz = _mm_min_ps(xyzz, zzzz);
            __m128 const min_yz = _mm_permute_ps(min_xz_yz, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const min = _mm_min_ps(min_xz_yz, min_yz);
            __m128 const result = _mm_permute_ps(min, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
        else if constexpr (T::Components == 2)
        {
            __m128 const xy = v.V;
            __m128 const yy = _mm_permute_ps(xy, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const min_xy_yy = _mm_min_ps(xy, yy);
            __m128 const result = _mm_permute_ps(min_xy_yy, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
#endif
    }

    template <typename T>
    mathinline T mathcall Hmax(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
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
        }
        else if constexpr (T::Components == 3)
        {
            float const c0 = Max(v.V.F[0], v.V.F[1]);
            float const c1 = Max(v.V.F[2], c0);

            Impl::ConstFloat32x4 const result{ { {
                c1,
                c1,
                c1,
                c1,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const c0 = Max(v.V.F[0], v.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                c0,
                c0,
                c0,
                c0,
            } } };
            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
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
        }
        else if constexpr (T::Components == 3)
        {
            __m128 const xyzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 1, 0));
            __m128 const zzzz = _mm_movehl_ps(xyzz, xyzz);
            __m128 const max_xz_yz = _mm_max_ps(xyzz, zzzz);
            __m128 const max_yz = _mm_permute_ps(max_xz_yz, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const max = _mm_max_ps(max_xz_yz, max_yz);
            __m128 const result = _mm_permute_ps(max, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
        else if constexpr (T::Components == 2)
        {
            __m128 const xy = v.V;
            __m128 const yy = _mm_permute_ps(xy, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const max_xy_yy = _mm_max_ps(xy, yy);
            __m128 const result = _mm_permute_ps(max_xy_yy, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
#endif
    }

    template <typename T>
    mathinline T mathcall Hsum(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const c = (v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);

            Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 3)
        {
            float const c = (v.V.F[0] + v.V.F[1] + v.V.F[2]);

            Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const c = (v.V.F[0] + v.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
            __m128 const xy_zw = _mm_hadd_ps(v.V, v.V);
            __m128 const result = _mm_hadd_ps(xy_zw, xy_zw);
            return { result };
        }
        else if constexpr (T::Components == 3)
        {
            __m128 const xyz0 = _mm_and_ps(v.V, Impl::VEC4_MASK_SELECT_1110.V);
            __m128 const xy_zz = _mm_hadd_ps(xyz0, xyz0);
            __m128 const result = _mm_hadd_ps(xy_zz, xy_zz);
        }
        else if constexpr (T::Components == 2)
        {
            __m128 const yx = _mm_movelh_ps(v.V, v.V);
            __m128 const result = _mm_hadd_ps(yx, yx);
            return { result };
        }
#endif
    }
}


// =================================================================================================
