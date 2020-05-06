#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuVertexBuffer : public GpuVertexBuffer { };
    static_assert(!std::is_polymorphic_v<NullGpuVertexBuffer>);
}
