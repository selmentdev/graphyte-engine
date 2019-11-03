#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuGraphicsPipelineState final : public GpuGraphicsPipelineState
    {
    public:
        VkPipeline m_Pipeline;
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuGraphicsPipelineState>);
}
