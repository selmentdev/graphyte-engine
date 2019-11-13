#pragma once
#include <Graphyte/Maths2/Impl/Simd.hxx>


//
// Actual math types.
//

namespace Graphyte::Maths
{
    struct Bool4 final
    {
        Impl::VectorFloat4 V;

        using IsMask = void;
        using IsFloat = void;
        static constexpr const size_t Components = 4;
    };

    struct Bool3 final
    {
        Impl::VectorFloat4 V;

        using IsMask = void;
        using IsFloat = void;
        static constexpr const size_t Components = 3;
    };

    struct Bool2 final
    {
        Impl::VectorFloat4 V;

        using IsMask = void;
        using IsFloat = void;
        static constexpr const size_t Components = 2;
    };

    struct Vec4 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsOrderComparable = void;
        using IsEqualComparable = void;
        using MaskType = Bool4;
        static constexpr const size_t Components = 4;
    };

    struct Vec3 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsOrderComparable = void;
        using IsEqualComparable = void;
        using MaskType = Bool3;
        static constexpr const size_t Components = 3;
    };

    struct Vec2 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsOrderComparable = void;
        using IsEqualComparable = void;
        using MaskType = Bool2;
        static constexpr const size_t Components = 2;
    };

    struct Mtx44 final
    {
        Impl::MatrixFloat4x4 M;

        using IsMatrix = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        static constexpr const size_t Components = 16;
    };

    struct Quat final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        using MaskType = Bool4;
        static constexpr const size_t Components = 4;
    };

    struct Plane final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        using MaskType = Bool4;
        static constexpr const size_t Components = 4;
    };

    struct Sphere final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        using MaskType = Bool4;
        static constexpr const size_t Components = 4;
    };

    struct Color final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        using MaskType = Bool4;
        static constexpr const size_t Components = 4;
    };
}
