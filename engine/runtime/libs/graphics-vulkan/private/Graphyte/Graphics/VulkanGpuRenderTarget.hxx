#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuRenderTarget : public GpuRenderTarget
    {
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuRenderTarget>);
}
