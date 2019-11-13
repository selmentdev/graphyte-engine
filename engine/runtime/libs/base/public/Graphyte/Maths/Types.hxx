#pragma once
#include <Graphyte/Maths/Impl/Simd.hxx>


// =================================================================================================
//
// Half Vector Storage
//


namespace Graphyte::Maths
{
    struct Half final
    {
        uint16_t Value;
    };

    using Half1 = Half;

    struct Half2 final
    {
        Half X;
        Half Y;
    };

    struct Half3 final
    {
        Half X;
        Half Y;
        Half Z;
    };

    struct Half4 final
    {
        Half X;
        Half Y;
        Half Z;
        Half W;
    };
}


// =================================================================================================
//
// Float Vector Storage
//

namespace Graphyte::Maths
{
    struct Float4 final
    {
        float X, Y, Z, W;
    };

    struct Float3 final
    {
        float X, Y, Z;
    };

    struct Float2 final
    {
        float X, Y;
    };

    struct Float1 final
    {
        float X;
    };

    struct alignas(16) Float4A final
    {
        float X, Y, Z, W;
    };

    struct alignas(16) Float3A final
    {
        float X, Y, Z;
    };

    struct alignas(16) Float2A final
    {
        float X, Y;
    };

    struct alignas(16) Float1A final
    {
        float X;
    };

}

// =================================================================================================
//
// Float Matrix Storage
//

namespace Graphyte::Maths
{
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
}

// =================================================================================================
//
// Color space
//

namespace Graphyte::Maths
{
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


// =================================================================================================
//
// Mask types
// 

namespace Graphyte::Maths
{
    struct Bool4 final
    {
        Impl::VectorFloat4 V;
        using IsSimdMask = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 4;
    };

    struct Bool3 final
    {
        Impl::VectorFloat4 V;
        using IsSimdMask = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 3;
    };

    struct Bool2 final
    {
        Impl::VectorFloat4 V;
        using IsSimdMask = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 2;
    };
}


// =================================================================================================
//
//  Vector types
//

namespace Graphyte::Maths
{
    struct Vec4 final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        using IsSimdOrderComparable = void;
        static constexpr const size_t Components = 4;
    };

    struct Vec3 final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        using IsSimdOrderComparable = void;
        static constexpr const size_t Components = 3;
    };

    struct Vec2 final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        using IsSimdOrderComparable = void;
        static constexpr const size_t Components = 2;
    };

    struct Quat final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 4;
    };
}


// =================================================================================================
//
// Matrix types
//

namespace Graphyte::Maths
{
    struct Matrix final
    {
        Impl::MatrixFloat4x4 M;
        using IsSimdMatrix = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 16;
    };
}

// =================================================================================================
//
// Geometric types
//

namespace Graphyte::Maths
{
    struct Plane final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 4;
    };

    struct Sphere final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 4;
    };

    struct Color final
    {
        Impl::VectorFloat4 V;
        using IsSimdVector = void;
        using IsSimdEqualComparable = void;
        static constexpr const size_t Components = 4;
    };
}


// =================================================================================================
//
// Unsigned integer types
//

namespace Graphyte::Maths
{
    struct UInt4 final
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
        uint32_t W;
    };

    struct UInt3 final
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };

    struct UInt2 final
    {
        uint32_t X;
        uint32_t Y;
    };

    struct UInt1 final
    {
        uint32_t X;
    };
}


// =================================================================================================
//
// Signed integer types
//

namespace Graphyte::Maths
{
    struct SInt4 final
    {
        int32_t X;
        int32_t Y;
        int32_t Z;
        int32_t W;
    };

    struct SInt3 final
    {
        int32_t X;
        int32_t Y;
        int32_t Z;
    };

    struct SInt2 final
    {
        int32_t X;
        int32_t Y;
    };

    struct SInt1 final
    {
        int32_t X;
    };
}



// =================================================================================================
//
// Byte types
//

namespace Graphyte::Maths
{
    struct UByte4 final
    {
        uint8_t X;
        uint8_t Y;
        uint8_t Z;
        uint8_t W;
    };

    struct SByte4 final
    {
        int8_t X;
        int8_t Y;
        int8_t Z;
        int8_t W;
    };
}
