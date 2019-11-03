#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class VulkanGpuResourceSet : public GpuResourceSet
    {
    };
    static_assert(!std::is_polymorphic_v<VulkanGpuResourceSet>);
}
