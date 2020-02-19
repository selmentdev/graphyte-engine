#include "NullGpuDevice.hxx"
#include "NullGpuUniformBuffer.hxx"

namespace Graphyte::Graphics
{
    GpuUniformBufferHandle NullGpuDevice::CreateUniformBuffer(
        [[maybe_unused]] size_t size,
        [[maybe_unused]] GpuBufferUsage usage,
        [[maybe_unused]] const GpuSubresourceData* subresource
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyUniformBuffer(
        [[maybe_unused]] GpuUniformBufferHandle handle
    ) noexcept
    {
    }

    void* NullGpuDevice::LockUniformBuffer(
        [[maybe_unused]] GpuUniformBufferHandle handle,
        [[maybe_unused]] uint32_t offset,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuResourceLockMode lock_mode
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::UnlockUniformBuffer(
        [[maybe_unused]] GpuUniformBufferHandle handle
    ) noexcept
    {
    }
    
    void NullGpuDevice::CopyUniformBuffer(
        [[maybe_unused]] GpuUniformBufferHandle source,
        [[maybe_unused]] GpuUniformBufferHandle destination
    ) noexcept
    {
    }
}
