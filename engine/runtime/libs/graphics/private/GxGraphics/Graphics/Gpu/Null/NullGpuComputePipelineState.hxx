#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuComputePipelineState final : public GpuComputePipelineState { };
    static_assert(!std::is_polymorphic_v<NullGpuComputePipelineState>);
}
