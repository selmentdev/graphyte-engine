#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Load(ColorBGRA const* source) noexcept
        requires(Impl::IsColor<T>)
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

    template <typename T>
    mathinline void mathcall Store(ColorBGRA* destination, T color) noexcept
        requires(Impl::IsColor<T>)
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
        __m128 const c0 = _mm_mul_ps(color_min, Impl::VEC4_UBYTE_MAX.V);
        __m128 const c1 = _mm_permute_ps(c0, _MM_SHUFFLE(3, 0, 1, 2));
        __m128i const c2 = _mm_cvtps_epi32(c1);
        __m128i const c3 = _mm_packs_epi32(c2, c2);
        __m128i const c4 = _mm_packus_epi16(c3, c3);

        _mm_store_ss(reinterpret_cast<float*>(&destination->Value), _mm_castsi128_ps(c4));
#endif
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Negative(T v) noexcept
        requires(Impl::IsColor<T>)
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

    template <typename T>
    mathinline T mathcall Modulate(T a, T b) noexcept
        requires(Impl::IsColor<T>)
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

    template <typename T>
    mathinline T mathcall AdjustSaturation(T v, float saturation) noexcept
        requires(Impl::IsColor<T>)
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
        __m128 const vfactor = _mm_dp_ps(v.V, luminance.V, 0x3F);
        __m128 const vsaturation = _mm_set_ps1(saturation);
        __m128 const r0 = _mm_sub_ps(v.V, vfactor);
        __m128 const r1 = Impl::avx_fmadd_f32x4(r0, vsaturation, vfactor);
        __m128 const r2 = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
        return { r3 };
#endif
    }

    template <typename T>
    mathinline T mathcall AdjustContrast(T v, float contrast) noexcept
        requires(Impl::IsColor<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { { ((v.V.F[0] - 0.5F) * contrast) + 0.5F,
            ((v.V.F[1] - 0.5F) * contrast) + 0.5F,
            ((v.V.F[2] - 0.5F) * contrast) + 0.5F,
            v.V.F[3] } } };
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
