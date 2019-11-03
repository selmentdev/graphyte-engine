#include "Graphics.Vulkan.pch.hxx"
#include "VulkanGpuVertexBuffer.hxx"
#include "VulkanGpuDevice.hxx"
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Flags.hxx>

namespace Graphyte::Graphics
{
    VkBufferUsageFlags VulkanMapGpuBufferUsage(
        GpuBufferUsage usage
    ) noexcept
    {
        VkBufferUsageFlags result{};

        if (Flags::Has(usage, GpuBufferUsage::DrawIndirect))
        {
            result |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
        }

        if (Flags::Has(usage, GpuBufferUsage::Static))
        {
            result |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        }

        if (Flags::Has(usage, GpuBufferUsage::Dynamic))
        {
            result |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        }

        return result;
    }

    GpuVertexBufferHandle VulkanGpuDevice::CreateVertexBuffer(
        uint32_t size,
        [[maybe_unused]] GpuBufferUsage usage,
        const GpuSubresourceData* subresource
    ) noexcept
    {
        auto native = new VulkanGpuVertexBuffer{};

        VkBufferCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        ci.size = size;
        ci.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
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

        ci.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
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

    void VulkanGpuDevice::DestroyVertexBuffer(
        GpuVertexBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuVertexBuffer*>(handle);

        vmaDestroyBuffer(
            m_Allocator,
            native->m_Resource,
            native->m_Allocation
        );

        delete handle;
    }

    void* VulkanGpuDevice::LockVertexBuffer(
        GpuVertexBufferHandle handle,
        uint32_t offset,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuResourceLockMode lock_mode
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuVertexBuffer*>(handle);

        void* result{};

        GPU_VK_VALIDATE(vmaMapMemory(
            m_Allocator,
            native->m_Allocation,
            &result
        ));

        result = AdvancePointer(result, offset);
        return result;
    }

    void VulkanGpuDevice::UnlockVertexBuffer(
        GpuVertexBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<VulkanGpuVertexBuffer*>(handle);

        vmaUnmapMemory(
            m_Allocator,
            native->m_Allocation
        );
    }

    void VulkanGpuDevice::CopyVertexBuffer(
        [[maybe_unused]] GpuVertexBufferHandle source,
        [[maybe_unused]] GpuVertexBufferHandle destination
    ) noexcept
    {
    }
}
