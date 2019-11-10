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
    };

    struct Bool3 final
    {
        Impl::VectorFloat4 V;

        using IsMask = void;
    };

    struct Bool2 final
    {
        Impl::VectorFloat4 V;

        using IsMask = void;
    };

    struct Vec4 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        static constexpr const size_t Components = 4;
    };

    struct Vec3 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        static constexpr const size_t Components = 3;
    };

    struct Vec2 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        static constexpr const size_t Components = 2;
    };

    struct Mtx44 final
    {
        Impl::MatrixFloat4x4 M;

        using IsMatrix = void;
        static constexpr const size_t Components = 16;
    };

    struct Quat final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        static constexpr const size_t Components = 4;
    };

    struct Plane final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        static constexpr const size_t Components = 4;
    };

    struct Sphere final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        static constexpr const size_t Components = 4;
    };
}

namespace Graphyte::Maths
{
    struct alignas(16) Float4A final
    {
        float X;
        float Y;
        float Z;
        float W;
    };
}

namespace Graphyte::Maths
{
    mathinline Vec4 mathcall ToVec4(Vec3 v) noexcept
    {
        return { v.V };
    }

    mathinline Vec4 mathcall ToVec4(Vec2 v) noexcept
    {
        return { v.V };
    }

    mathinline Vec4 mathcall ToVec4(Quat v) noexcept
    {
        return { v.V };
    }

    mathinline Vec4 mathcall ToVec4(Plane v) noexcept
    {
        return { v.V };
    }

    mathinline Vec4 mathcall ToVec4(Sphere v) noexcept
    {
        return { v.V };
    }

    mathinline Vec3 mathcall ToVec3(Vec4 v) noexcept
    {
        return { v.V };
    }

    mathinline Vec3 mathcall ToVec3(Quat v) noexcept
    {
        return { v.V };
    }

    mathinline Vec3 mathcall ToVec3(Plane v) noexcept
    {
        return { v.V };
    }

    mathinline Vec3 mathcall ToVec3(Sphere v) noexcept
    {
        return { v.V };
    }

    mathinline Vec2 mathcall ToVec2(Vec4 v) noexcept
    {
        return { v.V };
    }

    mathinline Vec2 mathcall ToVec2(Quat v) noexcept
    {
        return { v.V };
    }

    mathinline Vec2 mathcall ToVec2(Plane v) noexcept
    {
        return { v.V };
    }

    mathinline Vec2 mathcall ToVec2(Sphere v) noexcept
    {
        return { v.V };
    }

    mathinline Quat mathcall ToQuat(Vec4 v) noexcept
    {
        return { v.V };
    }

    mathinline Plane mathcall ToPlane(Vec4 v) noexcept
    {
        return { v.V };
    }

    mathinline Sphere mathcall ToSphere(Vec4 v) noexcept
    {
        return { v.V };
    }
}

namespace Graphyte::Maths
{
    mathinline Bool4 mathcall AsBool4(Vec4 v) noexcept
    {
        return { v.V };
    }

    mathinline Bool3 mathcall AsBool3(Bool4 v) noexcept
    {
        return { v.V };
    }

    mathinline Bool2 mathcall AsBool2(Bool4 v) noexcept
    {
        return { v.V };
    }
}
