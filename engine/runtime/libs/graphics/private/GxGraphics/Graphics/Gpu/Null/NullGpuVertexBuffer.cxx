#include "NullGpuVertexBuffer.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuVertexBufferHandle NullGpuDevice::CreateVertexBuffer(
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuBufferUsage usage,
        [[maybe_unused]] const GpuSubresourceData* subresource) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyVertexBuffer(
        [[maybe_unused]] GpuVertexBufferHandle handle) noexcept
    {
    }

    void* NullGpuDevice::LockVertexBuffer(
        [[maybe_unused]] GpuVertexBufferHandle handle,
        [[maybe_unused]] uint32_t offset,
        [[maybe_unused]] uint32_t size,
        [[maybe_unused]] GpuResourceLockMode lock_mode) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::UnlockVertexBuffer(
        [[maybe_unused]] GpuVertexBufferHandle handle) noexcept
    {
    }

    void NullGpuDevice::CopyVertexBuffer(
        [[maybe_unused]] GpuVertexBufferHandle source,
        [[maybe_unused]] GpuVertexBufferHandle destination) noexcept
    {
    }
}
