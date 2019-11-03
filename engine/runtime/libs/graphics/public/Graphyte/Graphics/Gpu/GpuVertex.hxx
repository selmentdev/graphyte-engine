#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Maths/Types.hxx>

namespace Graphyte::Graphics
{
    struct GpuVertexUI final
    {
        Maths::float3 Position;
        Maths::half2 UV[4];
        Maths::Packed::color32 Color;
    };
    static_assert(sizeof(GpuVertexUI) == 32);

    struct GpuVertexCompact final
    {
        Maths::half4 Position;
        Maths::sbyte4 Normal;
        Maths::half2 UV;
        Maths::sbyte4 Tangent;
    };
    static_assert(sizeof(GpuVertexCompact) == 20);

    struct GpuVertexComplex final
    {
        Maths::float3 Position;
        Maths::sbyte4 Normal;
        Maths::sbyte4 Tangent;
        Maths::half2 UV[2];
        Maths::Packed::color32 Color;
    };
    static_assert(sizeof(GpuVertexComplex) == 32);

    struct GpuVertexSkinned final
    {
        Maths::float3 Position;
        Maths::Packed::color32 BlendWeight;
        Maths::Packed::color32 BlendIndex;
        Maths::sbyte4 Normal;
        Maths::sbyte4 Tangent;
        Maths::half2 UV[2];
        Maths::Packed::color32 Color;
    };
    static_assert(sizeof(GpuVertexSkinned) == 40);
}
