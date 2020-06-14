#include "VulkanGpuUniformBuffer.hxx"
#include "VulkanGpuDevice.hxx"
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Graphics
{
    VkBufferUsageFlags VulkanMapGpuBufferUsage(
        GpuBufferUsage usage) noexcept;

    GpuUniformBufferHandle VulkanGpuDevice::CreateUniformBuffer(
        size_t size,
        [[maybe_unused]] GpuBufferUsage usage,
        const GpuSubresourceData* subresource) noexcept
    {
        auto native = new VulkanGpuUniformBuffer{};

        VkBufferCreateInfo ci{};
        ci.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        ci.size        = size;
        ci.usage       = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        ci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        VmaAllocationCreateInfo vma_ci{};
        vma_ci.usage = VMA_MEMORY_USAGE_CPU_ONLY;
        vma_ci.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;

        VkBuffer staging{ VK_NULL_HANDLE };
        VmaAllocation staging_alloc{ VK_NULL_HANDLE };

        VmaAllocationInfo staging_info = {};
        GPU_VK_VALIDATE(vmaCreateBuffer(
            m_Allocator,
            &ci,
            &vma_ci,
            &staging,
            &staging_alloc,
            &staging_info));

        if (subresource != nullptr && staging_info.pMappedData != nullptr)
        {
            std::memcpy(
                staging_info.pMappedData,
                subresource->Memory,
                subresource->Pitch);
        }

        ci.usage     = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        vma_ci.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
        vma_ci.flags = 0;

        GPU_VK_VALIDATE(vmaCreateBuffer(
            m_Allocator,
            &ci,
            &vma_ci,
            &native->m_Resource,
            &native->m_Allocation,
            nullptr));

        return native;
    }

    void VulkanGpuDevice::DestroyUniformBuffer(
        GpuUniformBufferHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuUniformBuffer*>(handle);

        vmaDestroyBuffer(
            m_Allocator,
            native->m_Resource,
            native->m_Allocation);
    }

    void* VulkanGpuDevice::LockUniformBuffer(
        GpuUniformBufferHandle handle,
        uint32_t offset,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuResourceLockMode lock_mode) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuUniformBuffer*>(handle);

        void* result{};
        GPU_VK_VALIDATE(vmaMapMemory(
            m_Allocator,
            native->m_Allocation,
            &result));

        result = AdvancePointer(result, offset);

        return result;
    }

    void VulkanGpuDevice::UnlockUniformBuffer(
        GpuUniformBufferHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuUniformBuffer*>(handle);

        vmaUnmapMemory(
            m_Allocator,
            native->m_Allocation);
    }

    void VulkanGpuDevice::CopyUniformBuffer(
        [[maybe_unused]] GpuUniformBufferHandle source,
        [[maybe_unused]] GpuUniformBufferHandle destination) noexcept
    {
    }
}
