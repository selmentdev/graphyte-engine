#pragma once
#include <Graphyte/Maths/Simd.hxx>
#include <Graphyte/Maths/Vector4.hxx>

namespace Graphyte::Maths
{
    struct Vector2;
    struct Vector3;
    struct Vector4;
    struct Quaternion;
    struct Matrix;
}

namespace Graphyte::Maths
{
    struct Color final
    {
    public:
        VectorFloat4 V;

    public:
        static Color mathcall Load(const float4a* source) noexcept;
        static Color mathcall Load(const Packed::color32* source) noexcept;
        static Color mathcall LoadPacked(const float4* source) noexcept;

        static void mathcall Store(float4a* destination, Color c) noexcept;
        static void mathcall Store(Packed::color32* destination, Color c) noexcept;
        static void mathcall StorePacked(float4* destination, Color c) noexcept;

    public:
        static bool mathcall IsEqual(Color c1, Color c2) noexcept;
        static bool mathcall IsNotEqual(Color c1, Color c2) noexcept;
        static bool mathcall IsGreater(Color c1, Color c2) noexcept;
        static bool mathcall IsGreaterEqual(Color c1, Color c2) noexcept;
        static bool mathcall IsLess(Color c1, Color c2) noexcept;
        static bool mathcall IsLessEqual(Color c1, Color c2) noexcept;
        static bool mathcall IsNaN(Color c) noexcept;
        static bool mathcall IsInfinite(Color c) noexcept;

    public:
        static Color mathcall Negative(Color c) noexcept;
        static Color mathcall Modulate(Color c1, Color c2) noexcept;
        static Color mathcall AdjustSaturation(Color c, float saturation) noexcept;
        static Color mathcall AdjustContrast(Color c, float contrast) noexcept;

    public:
        static Vector4 mathcall HueToClr(Vector4 p, Vector4 q, Vector4 h) noexcept;
        static Color mathcall RGBToHSL(Color c) noexcept;
        static Color mathcall HSLToRGB(Color c) noexcept;
        static Color mathcall RGBToHSV(Color c) noexcept;
        static Color mathcall HSVToRGB(Color c) noexcept;
        static Color mathcall RGBToYUV(Color c) noexcept;
        static Color mathcall YUVToRGB(Color c) noexcept;
        static Color mathcall RGBToYUVHD(Color c) noexcept;
        static Color mathcall YUVToRGBHD(Color c) noexcept;
        static Color mathcall RGBToXYZ(Color c) noexcept;
        static Color mathcall XYZToRGB(Color c) noexcept;
        static Color mathcall XYZToSRGB(Color c) noexcept;
        static Color mathcall SRGBToXYZ(Color c) noexcept;
        static Color mathcall RGBToSRGB(Color c) noexcept;
        static Color mathcall SRGBToRGB(Color c) noexcept;
    };

#if GRAPHYTE_MATH_ENABLE_OPERATORS

    mathinline bool mathcall operator== (Color c1, Color c2) noexcept
    {
        return Color::IsEqual(c1, c2);
    }

    mathinline bool mathcall operator!= (Color c1, Color c2) noexcept
    {
        return Color::IsNotEqual(c1, c2);
    }

    mathinline bool mathcall operator< (Color c1, Color c2) noexcept
    {
        return Color::IsLess(c1, c2);
    }

    mathinline bool mathcall operator<= (Color c1, Color c2) noexcept
    {
        return Color::IsLessEqual(c1, c2);
    }

    mathinline bool mathcall operator> (Color c1, Color c2) noexcept
    {
        return Color::IsGreater(c1, c2);
    }

    mathinline bool mathcall operator>= (Color c1, Color c2) noexcept
    {
        return Color::IsGreaterEqual(c1, c2);
    }

#endif
}

#include <Graphyte/Maths/Color.impl.hxx>
