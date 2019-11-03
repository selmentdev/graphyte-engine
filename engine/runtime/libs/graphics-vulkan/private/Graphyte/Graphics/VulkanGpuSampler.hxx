#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuSampler : public GpuSampler
    {
    public:
        VkSampler m_Resource{ VK_NULL_HANDLE };
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuSampler>);
}
