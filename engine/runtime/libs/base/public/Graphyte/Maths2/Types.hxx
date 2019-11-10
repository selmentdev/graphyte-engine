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
        static constexpr const size_t Components = 4;
    };

    struct Vec3 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsOrderComparable = void;
        using IsEqualComparable = void;
        static constexpr const size_t Components = 3;
    };

    struct Vec2 final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsOrderComparable = void;
        using IsEqualComparable = void;
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
        static constexpr const size_t Components = 4;
    };

    struct Plane final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        static constexpr const size_t Components = 4;
    };

    struct Sphere final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        static constexpr const size_t Components = 4;
    };

    struct Color final
    {
        Impl::VectorFloat4 V;

        using IsVector = void;
        using IsFloat = void;
        using IsEqualComparable = void;
        static constexpr const size_t Components = 4;
    };
}

namespace Graphyte::Maths::Impl
{
    template <size_t N> struct DeduceMaskTypeImpl;

    template <> struct DeduceMaskTypeImpl<2> final
    {
        using Type = Bool2;
    };

    template <> struct DeduceMaskTypeImpl<3> final
    {
        using Type = Bool3;
    };

    template <> struct DeduceMaskTypeImpl<4> final
    {
        using Type = Bool4;
    };
}

namespace Graphyte::Maths
{
    template <typename T>
    using MaskType = typename Maths::Impl::DeduceMaskTypeImpl<T::Components>::Type;
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

    struct alignas(16) Float3A final
    {
        float X;
        float Y;
        float Z;
    };

    struct alignas(16) Float2A final
    {
        float X;
        float Y;
    };

    struct Float4 final
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    struct Float3 final
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    struct Float2 final
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    struct alignas(16) Float4x4A final
    {
        union
        {
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

    struct alignas(16) Float4x3A final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
                float M41, M42, M43;
            };
            float M[4][3];
            float F[12];
        };
    };

    struct alignas(16) Float3x4A final
    {
        union
        {
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
            };
            float M[3][4];
            float F[12];
        };
    };

    struct alignas(16) Float3x3A final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
            };
            float M[3][3];
            float F[9];
        };
    };

    struct Float4x4 final
    {
        union
        {
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

    struct Float4x3 final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
                float M41, M42, M43;
            };
            float M[4][3];
            float F[12];
        };
    };

    struct Float3x4 final
    {
        union
        {
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
            };
            float M[3][4];
            float F[12];
        };
    };

    struct Float3x3 final
    {
        union
        {
            struct
            {
                float M11, M12, M13;
                float M21, M22, M23;
                float M31, M32, M33;
            };
            float M[3][3];
            float F[9];
        };
    };

    struct ColorRGBA final
    {
        union
        {
            struct
            {
                uint8_t R;
                uint8_t G;
                uint8_t B;
                uint8_t A;
            };

            uint32_t Value;
        };
    };

    struct ColorBGRA final
    {
        union
        {
            struct
            {
                uint8_t B;
                uint8_t G;
                uint8_t R;
                uint8_t A;
            };

            uint32_t Value;
        };
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

    mathinline Color mathcall AsColor(Vec4 v) noexcept
    {
        return { v.V };
    }

    mathinline Vec4 mathcall AsVec4(Color v) noexcept
    {
        return { v.V };
    }
}
