#include "Graphics.pch.hxx"
#include "NullGpuIndexBuffer.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuIndexBufferHandle NullGpuDevice::CreateIndexBuffer(
        [[maybe_unused]] uint32_t stride,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuBufferUsage usage,
        [[maybe_unused]] const GpuSubresourceData* subresource
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyIndexBuffer(
        [[maybe_unused]] GpuIndexBufferHandle handle
    ) noexcept
    {
        (void)handle;
    }

    void* NullGpuDevice::LockIndexBuffer(
        [[maybe_unused]] GpuIndexBufferHandle handle,
        [[maybe_unused]] uint32_t offset,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuResourceLockMode lock_mode
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::UnlockIndexBuffer(
        [[maybe_unused]] GpuIndexBufferHandle handle
    ) noexcept
    {
    }

    void NullGpuDevice::CopyIndexBuffer(
        [[maybe_unused]] GpuIndexBufferHandle source,
        [[maybe_unused]] GpuIndexBufferHandle destination
    ) noexcept
    {
    }
}
