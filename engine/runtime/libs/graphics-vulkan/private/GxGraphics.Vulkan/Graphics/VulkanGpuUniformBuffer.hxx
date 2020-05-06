#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuUniformBuffer : public GpuUniformBuffer
    {
    public:
        VkBuffer m_Resource{ VK_NULL_HANDLE };
        VmaAllocation m_Allocation{ VK_NULL_HANDLE };
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuUniformBuffer>);
}
