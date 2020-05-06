#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuUniformBuffer : public GpuUniformBuffer { };
    static_assert(!std::is_polymorphic_v<NullGpuUniformBuffer>);
}
