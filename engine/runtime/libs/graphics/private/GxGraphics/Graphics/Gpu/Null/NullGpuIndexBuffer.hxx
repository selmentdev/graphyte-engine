#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuIndexBuffer : public GpuIndexBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<NullGpuIndexBuffer>);
}
