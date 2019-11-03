#include "Graphics.pch.hxx"
#include "NullGpuTexture.hxx"
#include "NullGpuDevice.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuTexture2DHandle NullGpuDevice::CreateTexture2D(
        [[maybe_unused]] const GpuTextureCreateArgs& args
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyTexture2D(
        [[maybe_unused]] GpuTexture2DHandle texture
    ) noexcept
    {
    }

    void NullGpuDevice::UpdateTexture2D(
        [[maybe_unused]] GpuTexture2DHandle texture,
        [[maybe_unused]] uint32_t mip_level,
        [[maybe_unused]] const GpuRect* rect,
        [[maybe_unused]] const void* data,
        [[maybe_unused]] uint32_t pitch
    ) noexcept
    {
    }

    void NullGpuDevice::GenerateMipmapsTexture2D(
        [[maybe_unused]] GpuTexture2DHandle texture
    ) noexcept
    {
    }

    std::unique_ptr<Image> NullGpuDevice::SaveTexture2D(
        [[maybe_unused]] GpuTexture2DHandle texture
    ) noexcept
    {
        return nullptr;
    }
}

namespace Graphyte::Graphics
{
    GpuTexture2DArrayHandle NullGpuDevice::CreateTexture2DArray(
        [[maybe_unused]] const GpuTextureCreateArgs& args
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyTexture2DArray(
        [[maybe_unused]] GpuTexture2DArrayHandle handle
    ) noexcept
    {
    }
}

namespace Graphyte::Graphics
{
    GpuTexture3DHandle NullGpuDevice::CreateTexture3D(
        [[maybe_unused]] const GpuTextureCreateArgs& args
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyTexture3D(
        [[maybe_unused]] GpuTexture3DHandle handle
    ) noexcept
    {
        (void)handle;
    }
}

namespace Graphyte::Graphics
{
    GpuTextureCubeHandle NullGpuDevice::CreateTextureCube(
        [[maybe_unused]] const GpuTextureCreateArgs& args
    ) noexcept
    {
        return nullptr;
    }

    void NullGpuDevice::DestroyTextureCube(
        [[maybe_unused]] GpuTextureCubeHandle handle
    ) noexcept
    {
    }
}
