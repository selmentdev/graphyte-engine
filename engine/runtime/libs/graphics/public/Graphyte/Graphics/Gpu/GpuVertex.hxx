#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Maths.hxx>

namespace Graphyte::Graphics
{
    struct GpuVertexUI final
    {
        Maths::Float3 Position;
        Maths::Half2 UV[4];
        Maths::ColorBGRA Color;
    };
    static_assert(sizeof(GpuVertexUI) == 32);

    struct GpuVertexCompact final
    {
        Maths::Half4 Position;
        Maths::SByte4 Normal;
        Maths::Half2 UV;
        Maths::SByte4 Tangent;
    };
    static_assert(sizeof(GpuVertexCompact) == 20);

    struct GpuVertexComplex final
    {
        Maths::Float3 Position;
        Maths::SByte4 Normal;
        Maths::SByte4 Tangent;
        Maths::Half2 UV[2];
        Maths::ColorBGRA Color;
    };
    static_assert(sizeof(GpuVertexComplex) == 32);

    struct GpuVertexSkinned final
    {
        Maths::Float3 Position;
        Maths::ColorBGRA BlendWeight;
        Maths::ColorBGRA BlendIndex;
        Maths::SByte4 Normal;
        Maths::SByte4 Tangent;
        Maths::Half2 UV[2];
        Maths::ColorBGRA Color;
    };
    static_assert(sizeof(GpuVertexSkinned) == 40);
}
