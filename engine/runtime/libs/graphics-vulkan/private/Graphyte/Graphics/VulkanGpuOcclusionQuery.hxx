#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuOcclusionQuery : public GpuOcclusionQuery
    {
    public:
        VkQueryPool m_Resource;
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuOcclusionQuery>);
}
