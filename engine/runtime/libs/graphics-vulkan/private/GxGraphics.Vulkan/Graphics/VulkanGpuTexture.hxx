#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuTexture : public GpuTexture
    {
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuTexture>);
}
