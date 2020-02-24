#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Types.hxx>


namespace Graphyte::Graphics
{
    struct GpuVertexUI final
    {
        Float3 Position;
        Half2 UV[4];
        ColorBGRA Color;
    };
    static_assert(sizeof(GpuVertexUI) == 32);

    struct GpuVertexCompact final
    {
        Half4 Position;
        SByte4 Normal;
        Half2 UV;
        SByte4 Tangent;
    };
    static_assert(sizeof(GpuVertexCompact) == 20);

    struct GpuVertexComplex final
    {
        Float3 Position;
        SByte4 Normal;
        SByte4 Tangent;
        Half2 UV[2];
        ColorBGRA Color;
    };
    static_assert(sizeof(GpuVertexComplex) == 32);

    struct GpuVertexSkinned final
    {
        Float3 Position;
        ColorBGRA BlendWeight;
        ColorBGRA BlendIndex;
        SByte4 Normal;
        SByte4 Tangent;
        Half2 UV[2];
        ColorBGRA Color;
    };
    static_assert(sizeof(GpuVertexSkinned) == 40);
}
