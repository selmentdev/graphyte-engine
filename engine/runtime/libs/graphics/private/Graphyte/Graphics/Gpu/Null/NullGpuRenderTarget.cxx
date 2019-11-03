#include "Graphics.pch.hxx"
#include "NullGpuRenderTarget.hxx"
#include "NullGpuDevice.hxx"
#include "NullGpuTexture.hxx"

namespace Graphyte::Graphics
{
    GpuRenderTargetHandle NullGpuDevice::BeginCreateRenderTarget(
        [[maybe_unused]] uint32_t width,
        [[maybe_unused]] uint32_t height,
        [[maybe_unused]] uint32_t surfaces
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::EndCreateRenderTarget(
        [[maybe_unused]] GpuRenderTargetHandle handle
    ) noexcept
    {
    }

    void NullGpuDevice::SetRenderTargetSurface(
        [[maybe_unused]] GpuRenderTargetHandle handle,
        [[maybe_unused]] int32_t index,
        [[maybe_unused]] GpuTexture2DHandle texture,
        [[maybe_unused]] uint32_t mip_index
    ) noexcept
    {
    }

    void NullGpuDevice::DestroyRenderTarget(
        [[maybe_unused]] GpuRenderTargetHandle handle
    ) noexcept
    {
    }
}
