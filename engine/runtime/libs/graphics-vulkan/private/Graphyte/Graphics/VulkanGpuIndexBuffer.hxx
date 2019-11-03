#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"


namespace Graphyte::Graphics
{
    class VulkanGpuIndexBuffer : public GpuIndexBuffer
    {
    public:
        VkBuffer m_Resource{ VK_NULL_HANDLE };
        VmaAllocation m_Allocation{ VK_NULL_HANDLE };
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuIndexBuffer>);
}
