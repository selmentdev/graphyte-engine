#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuStructuredBuffer : public GpuStructuredBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<NullGpuStructuredBuffer>);
}
