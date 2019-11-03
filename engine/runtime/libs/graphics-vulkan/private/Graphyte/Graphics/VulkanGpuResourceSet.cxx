#include "Graphics.Vulkan.pch.hxx"
#include "VulkanGpuDevice.hxx"
#include "VulkanGpuCommandList.hxx"

namespace Graphyte::Graphics
{
    void VulkanGpuCommandList::BindResourceSet(
        [[maybe_unused]] GpuResourceSetHandle handle
    ) noexcept
    {
    }
}

namespace Graphyte::Graphics
{
    GpuResourceSetHandle VulkanGpuDevice::CreateResourceSet(
        const GpuResourceSetDesc& desc
    ) noexcept
    {
        (void)desc;
        return nullptr;
    }

    void VulkanGpuDevice::DestroyResourceSet(
        GpuResourceSetHandle handle
    ) noexcept
    {
        (void)handle;
    }

    void VulkanGpuDevice::UpdateResourceSet(
        GpuResourceSetHandle handle,
        const GpuResourceSetDesc& desc
    ) noexcept
    {
        (void)handle;
        (void)desc;
    }
}
