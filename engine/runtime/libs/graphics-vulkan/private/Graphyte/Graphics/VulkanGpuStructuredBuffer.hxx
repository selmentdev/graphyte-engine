#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuStructuredBuffer : public GpuStructuredBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuStructuredBuffer>);
}
