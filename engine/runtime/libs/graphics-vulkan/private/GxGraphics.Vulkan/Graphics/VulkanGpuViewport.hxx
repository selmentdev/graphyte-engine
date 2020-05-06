#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuViewport final : public GpuViewport
    {
    public:
        VkSurfaceKHR Surface;
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuViewport>);
}
