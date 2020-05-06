#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuShader : public GpuShader
    {
    public:
        VkShaderModule m_Resource;
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuShader>);
}
