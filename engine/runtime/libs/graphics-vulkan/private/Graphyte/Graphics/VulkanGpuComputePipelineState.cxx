#include "Graphics.Vulkan.pch.hxx"
#include "VulkanGpuComputePipelineState.hxx"
#include "VulkanGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuComputePipelineStateHandle VulkanGpuDevice::CreateComputePipelineState(
        const GpuComputePipelineStateCreateArgs& args,
        const GpuResourceSetDesc& layout
    ) noexcept
    {
        (void)args;
        (void)layout;
        return nullptr;
    }

    void VulkanGpuDevice::DestroyComputePipelineState(
        GpuComputePipelineStateHandle handle
    ) noexcept
    {
        (void)handle;
    }
}
