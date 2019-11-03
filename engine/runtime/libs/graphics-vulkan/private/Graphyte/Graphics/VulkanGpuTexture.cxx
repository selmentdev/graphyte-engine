#include "Graphics.Vulkan.pch.hxx"
#include "VulkanGpuTexture.hxx"
#include "VulkanGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuTexture2DHandle VulkanGpuDevice::CreateTexture2D(
        [[maybe_unused]] const GpuTextureCreateArgs& args
    ) noexcept
    {
        //
        // Compute buffer size based on input data.
        //

        [[maybe_unused]] VkBufferCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        ci.size = 1000;
        ci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        [[maybe_unused]] VmaAllocationCreateInfo vmaci{};
        vmaci.usage = VMA_MEMORY_USAGE_CPU_ONLY;
        vmaci.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;

        [[maybe_unused]] VkBuffer staging{ VK_NULL_HANDLE };
        [[maybe_unused]] VmaAllocation stagingAlloc{ VK_NULL_HANDLE };

        [[maybe_unused]] VmaAllocationInfo stagingInfo{};
        //GPU_VK_VALIDATE(vmaCreateImage);

        return nullptr;
    }

    void VulkanGpuDevice::DestroyTexture2D(
        GpuTexture2DHandle texture
    ) noexcept
    {
        (void)texture;
    }

    void VulkanGpuDevice::UpdateTexture2D(
        GpuTexture2DHandle texture,
        uint32_t mip_level,
        const GpuRect* rect,
        const void* data,
        uint32_t pitch
    ) noexcept
    {
        (void)texture;
        (void)mip_level;
        (void)rect;
        (void)data;
        (void)pitch;
    }

    void VulkanGpuDevice::GenerateMipmapsTexture2D(
        GpuTexture2DHandle texture
    ) noexcept
    {
        (void)texture;
    }

    std::unique_ptr<Image> VulkanGpuDevice::SaveTexture2D(
        GpuTexture2DHandle texture
    ) noexcept
    {
        (void)texture;
        return nullptr;
    }

    GpuTexture2DArrayHandle VulkanGpuDevice::CreateTexture2DArray(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        (void)args;
        return nullptr;
    }

    void VulkanGpuDevice::DestroyTexture2DArray(
        GpuTexture2DArrayHandle handle
    ) noexcept
    {
        (void)handle;
    }

    GpuTexture3DHandle VulkanGpuDevice::CreateTexture3D(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        (void)args;
        return nullptr;
    }

    void VulkanGpuDevice::DestroyTexture3D(
        GpuTexture3DHandle handle
    ) noexcept
    {
        (void)handle;
    }

    GpuTextureCubeHandle VulkanGpuDevice::CreateTextureCube(
        const GpuTextureCreateArgs& args
    ) noexcept
    {
        (void)args;
        return nullptr;
    }

    void VulkanGpuDevice::DestroyTextureCube(
        GpuTextureCubeHandle handle
    ) noexcept
    {
        (void)handle;
    }
}
