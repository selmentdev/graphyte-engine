#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuComputePipelineState final : public GpuComputePipelineState
    {
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuComputePipelineState>);
}
