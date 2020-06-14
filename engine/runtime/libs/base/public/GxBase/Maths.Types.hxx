#pragma once
#include <GxBase/Maths/Base.hxx>

// =================================================================================================
//
// Math types
//

namespace Graphyte
{
    struct Bool4 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = uint32_t;
        using MaskType      = Bool4;
    };

    struct Bool3 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components    = 3;
        static constexpr const uint32_t CompareMask = 0b0111;

        using ComponentType = uint32_t;
        using MaskType      = Bool3;
    };

    struct Bool2 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 2;

        using ComponentType = uint32_t;
        using MaskType      = Bool2;
    };

    struct Bool1 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 1;

        using ComponentType = uint32_t;
        using MaskType      = Bool1;
    };

    struct Vector4 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Vector3 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 3;

        using ComponentType = float;
        using MaskType      = Bool3;
    };

    struct Vector2 final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 2;

        using ComponentType = float;
        using MaskType      = Bool2;
    };

    struct Vector1 final
    {
        Maths::Impl::NativeFloat32x4 V;
        static constexpr const size_t Components = 1;

        using ComponentType = float;
        using MaskType      = Bool1;
    };

    struct Quaternion final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Plane final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Sphere final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };

    struct Matrix final
    {
        Maths::Impl::NativeFloat32x4x4 M;

        static constexpr const size_t Components = 16;
        static constexpr const size_t Rows       = 4;
        static constexpr const size_t Columns    = 4;

        using ComponentType = float;
    };

    struct Color final
    {
        Maths::Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };
}
