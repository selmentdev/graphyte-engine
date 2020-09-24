#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/KnownColors.hxx>

namespace Graphyte::Maths::Impl
{
    // color specific consts
    mathconst ConstFloat32x4 c_V4_F32_Two{ { {
        2.0f,
        2.0f,
        2.0f,
        2.0f,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Four{ { {
        4.0f,
        4.0f,
        4.0f,
        4.0f,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Six{ { {
        6.0f,
        6.0f,
        6.0f,
        6.0f,
    } } };
    mathconst ConstUInt32x4 c_V4_U32_Mask_A8R8G8B8          = { { {
        0x00FF0000u,
        0x0000FF00u,
        0x000000FFu,
        0xFF000000u,
    } } };
    mathconst ConstUInt32x4 c_V4_U32_Flip_Alpha_A8R8G8B8    = { { {
        0x00000000u,
        0x00000000u,
        0x00000000u,
        0x80000000u,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Fix_Alpha_A8R8G8B8    = { { {
        0.0f,
        0.0f,
        0.0f,
        static_cast<float>(0x80000000u),
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Normalize_A8R8G8B8    = { { {
        1.0f / (255.0f * static_cast<float>(0x10000u)),
        1.0f / (255.0f * static_cast<float>(0x100u)),
        1.0f / 255.0f,
        1.0f / (255.0f * static_cast<float>(0x1000000u)),
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Color_Scale           = { { {
        255.0f,
        255.0f,
        255.0f,
        255.0f,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Color_Luminance       = { { {
        0.2125f,
        0.7154f,
        0.0721f,
        0.0f,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Color_MSRGB_Scale     = { { {
        12.92f,
        12.92f,
        12.92f,
        1.0f,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Color_MSRGB_Alpha     = { { {
        0.055f,
        0.055f,
        0.055f,
        0.0f,
    } } };
    mathconst ConstFloat32x4 c_V4_F32_Color_MSRGB_Alpha_One = { { {
        1.055f,
        1.055f,
        1.055f,
        1.0f,
    } } };
}

// =================================================================================================
// Load / store

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(ColorBGRA const* source) noexcept
        requires(Impl::IsColor<T>)
    {
        GX_ASSERT(source != nullptr);

#if GX_MATH_NO_INTRINSICS
        uint32_t const value = source->Value;

        Impl::ConstFloat32x4 const result{ { {
            (1.0f / 255.0f) * static_cast<float>((value >> 16) & 0xFFu),
            (1.0f / 255.0f) * static_cast<float>((value >> 8) & 0xFFu),
            (1.0f / 255.0f) * static_cast<float>(value & 0xFFu),
            (1.0f / 255.0f) * static_cast<float>((value >> 24) & 0xFFu),
        } } };

        return { result.V };
#elif GX_HW_AVX
        // {c0}[#bgra, #bgra, #bgra, #bgra]
        __m128i const c0 = _mm_set1_epi32(static_cast<int>(source->Value));
        // {c1}[#__r_, #_g__, #b___, #___a]
        __m128i const c1 = _mm_and_si128(c0, _mm_castps_si128(Impl::c_V4_U32_Mask_A8R8G8B8.V));
        __m128i const c2 = _mm_xor_si128(c1, _mm_castps_si128(Impl::c_V4_U32_Flip_Alpha_A8R8G8B8.V));
        __m128 const c3  = _mm_cvtepi32_ps(c2);
        __m128 const c4  = _mm_add_ps(c3, Impl::c_V4_F32_Fix_Alpha_A8R8G8B8.V);
        __m128 const c5  = _mm_mul_ps(c4, Impl::c_V4_F32_Normalize_A8R8G8B8.V);
        return { c5 };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(ColorBGRA* destination, T color) noexcept
        requires(Impl::IsColor<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GX_MATH_NO_INTRINSICS
        Vector4 const c0 = Saturate(Vector4{ color.V });
        Vector4 const c1 = Multiply(c0, Vector4{ Impl::c_V4_F32_U8_Max.V });
        Vector4 const c2 = Round(c1);

        Float4A buffer;
        Store(&buffer, c2);

        uint32_t const a = static_cast<uint32_t>(buffer.W) << 24;
        uint32_t const r = static_cast<uint32_t>(buffer.X) << 16;
        uint32_t const g = static_cast<uint32_t>(buffer.Y) << 8;
        uint32_t const b = static_cast<uint32_t>(buffer.X);

        destination->Value = a | r | g | b;
#elif GX_HW_AVX
        // Saturate
        __m128 const color_max = _mm_max_ps(color.V, _mm_setzero_ps());
        __m128 const color_min = _mm_min_ps(color_max, Impl::c_V4_F32_One.V);

        // RGBA -> ARGB
        __m128 const c0  = _mm_mul_ps(color_min, Impl::c_V4_F32_U8_Max.V);
        __m128 const c1  = _mm_permute_ps(c0, _MM_SHUFFLE(3, 0, 1, 2));
        __m128i const c2 = _mm_cvtps_epi32(c1);
        __m128i const c3 = _mm_packs_epi32(c2, c2);
        __m128i const c4 = _mm_packus_epi16(c3, c3);

        _mm_store_ss(reinterpret_cast<float*>(&destination->Value), _mm_castsi128_ps(c4));
#endif
    }
}


// =================================================================================================
// Color opereations

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall Negative(T v) noexcept
        requires(Impl::IsColor<T>)
    {
#if GX_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F - v.V.F[0],
            1.0F - v.V.F[1],
            1.0F - v.V.F[2],
            v.V.F[3],
        } } };
        return { result.V };
#elif GX_HW_AVX
        __m128 const neg_xyz = _mm_xor_ps(v.V, Impl::c_V3_F32_Negative_Zero.V);
        __m128 const result  = _mm_add_ps(neg_xyz, Impl::c_V3_F32_One.V);
        return { result };
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Modulate(T a, T b) noexcept
        requires(Impl::IsColor<T>)
    {
#if GX_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] * b.V.F[0],
            a.V.F[1] * b.V.F[1],
            a.V.F[2] * b.V.F[2],
            a.V.F[3] * b.V.F[3],
        } } };
        return { result.V };
#elif GX_HW_AVX
        return { _mm_mul_ps(a.V, b.V) };
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall AdjustSaturation(T v, float saturation) noexcept
        requires(Impl::IsColor<T>)
    {
        static Impl::ConstFloat32x4 const luminance{ { {
            0.2125F,
            0.7154F,
            0.0721F,
            0.0F,
        } } };

#if GX_MATH_NO_INTRINSICS
        float const factor
            = (v.V.F[0] * luminance.V.F[0])
              + (v.V.F[1] * luminance.V.F[1])
              + (v.V.F[2] * luminance.V.F[2]);

        Impl::ConstFloat32x4 const result{ { { ((v.V.F[0] - factor) * saturation) + factor,
            ((v.V.F[1] - factor) * saturation) + factor,
            ((v.V.F[2] - factor) * saturation) + factor,
            v.V.F[3] } } };

        return { result.V };
#elif GX_HW_AVX
        __m128 const vfactor     = _mm_dp_ps(v.V, luminance.V, 0x3F);
        __m128 const vsaturation = _mm_set_ps1(saturation);
        __m128 const r0          = _mm_sub_ps(v.V, vfactor);
        __m128 const r1          = Impl::avx_fmadd_f32x4(r0, vsaturation, vfactor);
        __m128 const r2          = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3          = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
        return { r3 };
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall AdjustContrast(T v, float contrast) noexcept
        requires(Impl::IsColor<T>)
    {
#if GX_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { { ((v.V.F[0] - 0.5F) * contrast) + 0.5F,
            ((v.V.F[1] - 0.5F) * contrast) + 0.5F,
            ((v.V.F[2] - 0.5F) * contrast) + 0.5F,
            v.V.F[3] } } };
        return { result.V };
#elif GX_HW_AVX
        __m128 const vcontrast = _mm_set_ps1(contrast);
        __m128 const r0        = _mm_sub_ps(v.V, Impl::c_V4_F32_One_Half.V);
        __m128 const r1        = Impl::avx_fmadd_f32x4(r0, vcontrast, Impl::c_V4_F32_One_Half.V);
        __m128 const r2        = _mm_shuffle_ps(r1, v.V, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const r3        = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(3, 0, 1, 0));
        return { r3 };
#endif
    }
}


// =================================================================================================
// Color space conversion

namespace Graphyte::Maths::Impl
{
    [[nodiscard]] mathinline Vector3 mathcall HueToColor(Vector3 p, Vector3 q, Vector3 h) noexcept
    {
        static constexpr Impl::ConstFloat32x4 g_OneSixth  = { { {
            1.0f / 6.0f,
            1.0f / 6.0f,
            1.0f / 6.0f,
            1.0f / 6.0f,
        } } };
        static constexpr Impl::ConstFloat32x4 g_TwoThirds = { { {
            2.0f / 3.0f,
            2.0f / 3.0f,
            2.0f / 3.0f,
            2.0f / 3.0f,
        } } };

        Vector3 const one = One<Vector3>();

        Vector3 t = h;

        if (IsLess(t, Zero<Vector3>()))
        {
            t = Add(t, one);
        }

        if (IsGreater(t, one))
        {
            t = Subtract(t, one);
        }

        if (IsLess(t, Vector3{ g_OneSixth.V }))
        {
            Vector3 const vt1 = Subtract(q, p);
            Vector3 const vt2 = Multiply(Vector3{ Impl::c_V4_F32_Six.V }, t);
            return MultiplyAdd(vt1, vt2, p);
        }

        if (IsLess(t, Vector3{ Impl::c_V4_F32_One_Half.V }))
        {
            return q;
        }

        if (IsLess(t, Vector3{ g_TwoThirds.V }))
        {
            Vector3 const vt1 = Subtract(q, p);
            Vector3 const vt2 = Multiply(Vector3{ Impl::c_V4_F32_Six.V }, Subtract(Vector3{ g_TwoThirds.V }, t));
            return MultiplyAdd(vt1, vt2, p);
        }

        return p;
    }
}

namespace Graphyte::Maths
{
    [[nodiscard]] mathinline Color mathcall RGBToHSL(Color c) noexcept;
    [[nodiscard]] mathinline Color mathcall HSLToRGB(Color c) noexcept;
    [[nodiscard]] mathinline Color mathcall RGBToHSV(Color c) noexcept;
    [[nodiscard]] mathinline Color mathcall HSVToRGB(Color c) noexcept;

    [[nodiscard]] mathinline Color mathcall RGBToYUV(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m0{ { { 0.299f, -0.147f, 0.615f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m1{ { { 0.587f, -0.289f, -0.515f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { 0.114f, 0.436f, -0.100f, 0.0f } } };

        Matrix m;
        m.M.R[0] = m0.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector3 const result = Transform(Vector3{ c.V }, m);

        return Select(c, Color{ result.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall YUVToRGB(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m1{ { { 0.0f, -0.395f, 2.032f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { 1.140f, -0.581f, 0.0f, 0.0f } } };

        Matrix m;
        m.M.R[0] = Impl::c_V4_F32_One.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector3 const result = Transform(Vector3{ c.V }, m);

        return Select(c, Color{ result.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall RGBToYUVHD(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m0{ { { 0.2126f, -0.0997f, 0.6150f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m1{ { { 0.7152f, -0.3354f, -0.5586f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { 0.0722f, 0.4351f, -0.0564f, 0.0f } } };

        Matrix m;
        m.M.R[0] = m0.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector3 const result = Transform(Vector3{ c.V }, m);

        return Select(c, Color{ result.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall YUVToRGBHD(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m1{ { { 0.0f, -0.2153f, 2.1324f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { 1.2803f, -0.3806f, 0.0f, 0.0f } } };

        Matrix m;
        m.M.R[0] = Impl::c_V4_F32_One.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector3 const result = Transform(Vector3{ c.V }, m);

        return Select(c, Color{ result.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall RGBToXYZ(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m0{ { { 0.4887180f, 0.1762044f, 0.0000000f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m1{ { { 0.3106803f, 0.8129847f, 0.0102048f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { 0.2006017f, 0.0108109f, 0.9897952f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 scale{ { { 1.0f / 0.17697f, 1.0f / 0.17697f, 1.0f / 0.17697f, 0.0f } } };

        Matrix m;
        m.M.R[0] = m0.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector3 const result = Multiply(Transform(Vector3{ c.V }, m), Vector3{ scale.V });
        return Select(c, Color{ result.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall XYZToRGB(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m0{ { { 2.3706743f, -0.5138850f, 0.0052982f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m1{ { { -0.9000405f, 1.4253036f, -0.0146949f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { -0.4706338f, 0.0885814f, 1.0093968f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 scale{ { { 0.17697f, 0.17697f, 0.17697f, 0.0f } } };

        Matrix m;
        m.M.R[0] = m0.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector3 const result = Multiply(Transform(Vector3{ c.V }, m), Vector3{ scale.V });
        return Select(c, Color{ result.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall XYZToSRGB(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m0{ { { 3.2406f, -0.9689f, 0.0557f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m1{ { { -1.5372f, 1.8758f, -0.2040f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { -0.4986f, 0.0415f, 1.0570f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 cut{ { { 0.0031308f, 0.0031308f, 0.0031308f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 exp{ { { 1.0f / 2.4f, 1.0f / 2.4f, 1.0f / 2.4f, 1.0f } } };

        Matrix m;
        m.M.R[0] = m0.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Vector4 const lclr{ Transform(Vector3{ c.V }, m).V };

        Bool4 const vsel           = CompareGreater(lclr, Vector4{ cut.V });
        Vector4 const vsmall_color = Multiply(lclr, Vector4{ Impl::c_V4_F32_Color_MSRGB_Scale.V });
        Vector4 const vlarge_color = Subtract(Multiply(Vector4{ Impl::c_V4_F32_Color_MSRGB_Alpha_One.V }, Power(lclr, Vector4{ exp.V })), Vector4{ Impl::c_V4_F32_Color_MSRGB_Alpha.V });
        Vector4 const vclr         = Select(vsmall_color, vlarge_color, vsel);
        return Select(c, Color{ vclr.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall SRGBToXYZ(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 m0{ { { 0.4124f, 0.2126f, 0.0193f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m1{ { { 0.3576f, 0.7152f, 0.1192f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 m2{ { { 0.1805f, 0.0722f, 0.9505f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 cut{ { { 0.04045f, 0.04045f, 0.04045f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 exp{ { { 2.4f, 2.4f, 2.4f, 1.0f } } };

        Bool4 const vsel           = CompareGreater(Vector4{ c.V }, Vector4{ cut.V });
        Vector4 const vsmall_color = Divide(Vector4{ c.V }, Vector4{ Impl::c_V4_F32_Color_MSRGB_Scale.V });
        Vector4 const vlarge_color = Power(Divide(Add(Vector4{ c.V }, Vector4{ Impl::c_V4_F32_Color_MSRGB_Alpha.V }), Vector4{ Impl::c_V4_F32_Color_MSRGB_Alpha_One.V }), Vector4{ exp.V });
        Vector4 const vlclr        = Select(vsmall_color, vlarge_color, vsel);

        Matrix m;
        m.M.R[0] = m0.V;
        m.M.R[1] = m1.V;
        m.M.R[2] = m2.V;
        m.M.R[3] = Impl::c_V4_F32_Zero.V;

        Color const vclr{ Transform(Vector3{ vlclr.V }, m).V };
        return Select(c, vclr, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall RGBToSRGB(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 cutoff{ { { 0.0031308f, 0.0031308f, 0.0031308f, 1.0f } } };
        static constexpr Impl::ConstFloat32x4 linear{ { { 12.92f, 12.92f, 12.92f, 1.0f } } };
        static constexpr Impl::ConstFloat32x4 scale{ { { 1.055f, 1.055f, 1.055f, 1.0f } } };
        static constexpr Impl::ConstFloat32x4 bias{ { { 0.055f, 0.055f, 0.055f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 inv_gamma{ { { 1.0f / 2.4f, 1.0f / 2.4f, 1.0f / 2.4f, 1.0f } } };

        Vector4 const vv  = Saturate(Vector4{ c.V });
        Vector4 const vv0 = Multiply(vv, Vector4{ linear.V });
        Vector4 const vv1 = Subtract(Multiply(Vector4{ scale.V }, Power(vv, Vector4{ inv_gamma.V })), Vector4{ bias.V });
        Bool4 const vsel  = CompareLess(vv, Vector4{ cutoff.V });
        Vector4 vv2       = Select(vv1, vv0, vsel);
        return Select(c, Color{ vv2.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }

    [[nodiscard]] mathinline Color mathcall SRGBToRGB(Color c) noexcept
    {
        static constexpr Impl::ConstFloat32x4 cutoff{ { { 0.04045f, 0.04045f, 0.04045f, 1.0f } } };
        static constexpr Impl::ConstFloat32x4 linear{ { { 1.0f / 12.92f, 1.0f / 12.92f, 1.0f / 12.92f, 1.0f } } };
        static constexpr Impl::ConstFloat32x4 scale{ { { 1.0f / 1.055f, 1.0f / 1.055f, 1.0f / 1.055f, 1.0f } } };
        static constexpr Impl::ConstFloat32x4 bias{ { { 0.055f, 0.055f, 0.055f, 0.0f } } };
        static constexpr Impl::ConstFloat32x4 gamma{ { { 2.4f, 2.4f, 2.4f, 1.0f } } };

        Vector4 const vv  = Saturate(Vector4{ c.V });
        Vector4 const vv0 = Multiply(vv, Vector4{ linear.V });
        Vector4 const vv1 = Power(Multiply(Add(vv, Vector4{ bias.V }), Vector4{ scale.V }), Vector4{ gamma.V });
        Bool4 const vsel  = CompareGreater(vv, Vector4{ cutoff.V });
        Vector4 const v01 = Select(vv0, vv1, vsel);
        return Select(c, Color{ v01.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V });
    }
}
