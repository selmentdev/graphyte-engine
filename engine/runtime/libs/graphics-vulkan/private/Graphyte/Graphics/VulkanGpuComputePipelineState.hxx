#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuComputePipelineState final : public GpuComputePipelineState
    {
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuComputePipelineState>);
}
