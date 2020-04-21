#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Half.hxx>
#include <Graphyte/TypeTraits.hxx>

namespace Graphyte
{
    struct Float16x4 final
    {
        Half X, Y, Z, W;
    };

    struct Float16x3 final
    {
        Half X, Y, Z;
    };

    struct Float16x2 final
    {
        Half X, Y;
    };

    struct Float16x1 final
    {
        Half X;
    };

    struct Float32x4 final
    {
        float X, Y, Z, W;
    };

    struct Float32x3 final
    {
        float X, Y, Z;
    };

    struct Float32x2 final
    {
        float X, Y;
    };

    struct Float32x1 final
    {
        float X;
    };

    struct alignas(16) Float32x4A final
    {
        float X, Y, Z, W;
    };

    struct alignas(16) Float32x3A final
    {
        float X, Y, Z;
    };

    struct alignas(16) Float32x2A final
    {
        float X, Y;
    };

    struct alignas(16) Float32x1A final
    {
        float X;
    };

    struct Float32x4x4 final
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

    struct Float32x4x3 final
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

    struct Float32x3x4 final
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

    struct Float32x3x3 final
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

    struct alignas(16) Float32x4x4A final
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

    struct alignas(16) Float32x4x3A final
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

    struct alignas(16) Float32x3x4A final
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

    struct alignas(16) Float32x3x3A final
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

    struct UInt32x4 final
    {
        uint32_t X, Y, Z, W;
    };

    struct UInt32x3 final
    {
        uint32_t X, Y, Z;
    };

    struct UInt32x2 final
    {
        uint32_t X, Y;
    };

    struct UInt32x1 final
    {
        uint32_t X;
    };


    struct SInt32x4 final
    {
        int32_t X, Y, Z, W;
    };

    struct SInt32x3 final
    {
        int32_t X, Y, Z;
    };

    struct SInt32x2 final
    {
        int32_t X, Y;
    };

    struct SInt32x1 final
    {
        int32_t X;
    };


    struct UInt8x4 final
    {
        uint8_t X, Y, Z, W;
    };

    struct UInt8x3 final
    {
        uint8_t X, Y, Z;
    };

    struct UInt8x2 final
    {
        uint8_t X, Y;
    };

    struct UInt8x1 final
    {
        uint8_t X;
    };


    struct SInt8x4 final
    {
        int8_t X, Y, Z, W;
    };

    struct SInt8x3 final
    {
        int8_t X, Y, Z;
    };

    struct SInt8x2 final
    {
        int8_t X, Y;
    };

    struct SInt8x1 final
    {
        int8_t X;
    };

}

namespace Graphyte
{
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
