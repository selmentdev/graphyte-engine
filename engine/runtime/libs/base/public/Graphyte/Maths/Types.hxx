#pragma once
#include <Graphyte/Base.module.hxx>


// =================================================================================================
//
// Half types.
//

namespace Graphyte::Maths
{
    struct half final
    {
        uint16_t Value;
    };

    struct half2 final
    {
        half X;
        half Y;
    };

    struct half3 final
    {
        half X;
        half Y;
        half Z;
    };

    struct half4 final
    {
        half X;
        half Y;
        half Z;
        half W;
    };
}


// =================================================================================================
//
// Unaligned float vector types.
//

namespace Graphyte::Maths
{
    struct float4 final
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    struct float3 final
    {
        float X;
        float Y;
        float Z;
    };

    struct float2 final
    {
        float X;
        float Y;
    };
}


// =================================================================================================
//
// Aligned float vector types.
//

namespace Graphyte::Maths
{

    struct alignas(16) float4a final
    {
        float X;
        float Y;
        float Z;
        float W;
    };

    struct alignas(16) float3a final
    {
        float X;
        float Y;
        float Z;
    };

    struct alignas(16) float2a final
    {
        float X;
        float Y;
    };
}


// =================================================================================================
//
// Unaligned float matrix types.
//

namespace Graphyte::Maths
{
    struct float4x4 final
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

    struct float4x3 final
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

    struct float3x4 final
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

    struct float3x3 final
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
// Unaligned float matrix types.
//

namespace Graphyte::Maths
{
    struct alignas(16) float4x4a final
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

    struct alignas(16) float4x3a final
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

    struct alignas(16) float3x4a final
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

    struct alignas(16) float3x3a final
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
// Unaligned integral vector types.
//

namespace Graphyte::Maths
{
    struct uint4 final
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
        uint32_t W;
    };

    struct uint3 final
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };

    struct uint2 final
    {
        uint32_t X;
        uint32_t Y;
    };

    struct int4 final
    {
        int32_t X;
        int32_t Y;
        int32_t Z;
        int32_t W;
    };

    struct int3 final
    {
        int32_t X;
        int32_t Y;
        int32_t Z;
    };

    struct int2 final
    {
        int32_t X;
        int32_t Y;
    };

    struct ubyte4 final
    {
        uint8_t X;
        uint8_t Y;
        uint8_t Z;
        uint8_t W;
    };

    struct sbyte4 final
    {
        int8_t X;
        int8_t Y;
        int8_t Z;
        int8_t W;
    };
}


// =================================================================================================
//
// Packed bit field types
//

namespace Graphyte::Maths::Packed
{
    struct color32 final
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

    struct color64 final
    {
        union
        {
            struct
            {
                uint16_t B;
                uint16_t G;
                uint16_t R;
                uint16_t A;
            };

            uint64_t Value;
        };
    };
}
