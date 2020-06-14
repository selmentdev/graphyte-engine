#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuGraphicsPipelineState final : public GpuGraphicsPipelineState
    {
    };
    static_assert(!std::is_polymorphic_v<NullGpuGraphicsPipelineState>);
}
