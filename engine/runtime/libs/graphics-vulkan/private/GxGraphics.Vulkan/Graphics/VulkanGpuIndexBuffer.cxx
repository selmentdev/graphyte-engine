#include "VulkanGpuIndexBuffer.hxx"
#include "VulkanGpuDevice.hxx"
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Graphics
{
    VkBufferUsageFlags VulkanMapGpuBufferUsage(
        GpuBufferUsage usage
    ) noexcept;

    GpuIndexBufferHandle VulkanGpuDevice::CreateIndexBuffer(
        [[maybe_unused]] uint32_t stride,
        uint32_t size,
        [[maybe_unused]] GpuBufferUsage usage,
        const GpuSubresourceData* subresource
    ) noexcept
    {
        auto native = new VulkanGpuIndexBuffer{};

        VkBufferCreateInfo ci{
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .size = size,
            .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        };

        VmaAllocationCreateInfo vma_ci{
            .flags = VMA_ALLOCATION_CREATE_MAPPED_BIT,
            .usage = VMA_MEMORY_USAGE_CPU_ONLY,
        };

        VkBuffer staging{ VK_NULL_HANDLE };
        VmaAllocation staging_alloc{ VK_NULL_HANDLE };

        VmaAllocationInfo staging_info = {};

        GPU_VK_VALIDATE(vmaCreateBuffer(
            m_Allocator,
            &ci,
            &vma_ci,
            &staging,
            &staging_alloc,
            &staging_info
        ));

        if (subresource != nullptr && staging_info.pMappedData != nullptr)
        {
            std::memcpy(
                staging_info.pMappedData,
                subresource->Memory,
                subresource->Pitch
            );
        }

        ci.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        vma_ci.usage = VMA_MEMORY_USAGE_GPU_ONLY;
        vma_ci.flags = 0;

        GPU_VK_VALIDATE(vmaCreateBuffer(
            m_Allocator,
            &ci,
            &vma_ci,
            &native->m_Resource,
            &native->m_Allocation,
            nullptr
        ));

        return native;
    }

    void VulkanGpuDevice::DestroyIndexBuffer(
        GpuIndexBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuIndexBuffer*>(handle);

        vmaDestroyBuffer(
            m_Allocator,
            native->m_Resource,
            native->m_Allocation
        );
    }

    void* VulkanGpuDevice::LockIndexBuffer(
        GpuIndexBufferHandle handle,
        uint32_t offset,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuResourceLockMode lock_mode
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuIndexBuffer*>(handle);

        void* result{};
        GPU_VK_VALIDATE(vmaMapMemory(
            m_Allocator,
            native->m_Allocation,
            &result
        ));

        result = AdvancePointer(
            result,
            offset
        );

        return result;
    }

    void VulkanGpuDevice::UnlockIndexBuffer(
        GpuIndexBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuIndexBuffer*>(handle);

        vmaUnmapMemory(
            m_Allocator,
            native->m_Allocation
        );
    }

    void VulkanGpuDevice::CopyIndexBuffer(
        [[maybe_unused]] GpuIndexBufferHandle source,
        [[maybe_unused]] GpuIndexBufferHandle destination
    ) noexcept
    {
    }
}
