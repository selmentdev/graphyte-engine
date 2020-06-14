#include "VulkanGpuRenderTarget.hxx"
#include "VulkanGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuRenderTargetHandle VulkanGpuDevice::BeginCreateRenderTarget(
        uint32_t width,
        uint32_t height,
        uint32_t surfaces) noexcept
    {
        (void)width;
        (void)height;
        (void)surfaces;
        return nullptr;
    }

    void VulkanGpuDevice::EndCreateRenderTarget(
        GpuRenderTargetHandle handle) noexcept
    {
        (void)handle;
    }

    void VulkanGpuDevice::SetRenderTargetSurface(
        GpuRenderTargetHandle handle,
        int32_t index,
        GpuTexture2DHandle texture,
        uint32_t mip_index) noexcept
    {
        (void)handle;
        (void)index;
        (void)texture;
        (void)mip_index;
    }

    void VulkanGpuDevice::DestroyRenderTarget(
        GpuRenderTargetHandle handle) noexcept
    {
        (void)handle;
    }
}
