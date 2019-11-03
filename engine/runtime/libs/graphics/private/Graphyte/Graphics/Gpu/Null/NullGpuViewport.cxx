#include "Graphics.pch.hxx"
#include "NullGpuViewport.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuViewportHandle NullGpuDevice::CreateViewport(
        [[maybe_unused]] void* native_handle,
        [[maybe_unused]] uint32_t width,
        [[maybe_unused]] uint32_t height,
        [[maybe_unused]] bool fullscreen,
        [[maybe_unused]] PixelFormat color_format,
        [[maybe_unused]] PixelFormat depth_format,
        [[maybe_unused]] GpuMsaaQuality msaa
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyViewport(
        [[maybe_unused]] GpuViewportHandle handle
    ) noexcept
    {
    }

    void NullGpuDevice::ResizeViewport(
        [[maybe_unused]] GpuViewportHandle handle,
        [[maybe_unused]] uint32_t width,
        [[maybe_unused]] uint32_t height,
        [[maybe_unused]] bool fullscreen,
        [[maybe_unused]] PixelFormat format
    ) noexcept
    {
    }

    void NullGpuDevice::BeginDrawViewport(
        [[maybe_unused]] GpuViewportHandle handle
    ) noexcept
    {
    }

    void NullGpuDevice::EndDrawViewport(
        [[maybe_unused]] GpuViewportHandle handle,
        [[maybe_unused]] bool present,
        [[maybe_unused]] int interval
    ) noexcept
    {
    }
}
