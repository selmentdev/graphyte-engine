#include "D3D11GpuRenderTarget.hxx"
#include "D3D11GpuDevice.hxx"
#include "D3D11GpuTexture.hxx"
#include "D3D11GpuPixelFormat.hxx"

namespace Graphyte::Graphics
{
    GpuRenderTargetHandle D3D11GpuDevice::BeginCreateRenderTarget(
        uint32_t width,
        uint32_t height,
        uint32_t surfaces) noexcept
    {
        auto result      = new D3D11GpuRenderTarget{};
        result->m_Colors = surfaces;
        result->m_Width  = width;
        result->m_Height = height;
        return result;
    }

    void D3D11GpuDevice::EndCreateRenderTarget(
        [[maybe_unused]] GpuRenderTargetHandle handle) noexcept
    {
        (void)handle;

        // Does nothing.
    }

    void D3D11GpuDevice::SetRenderTargetSurface(
        GpuRenderTargetHandle handle,
        int32_t index,
        GpuTexture2DHandle texture,
        uint32_t mip_index) noexcept
    {
        GX_ASSERT(handle != nullptr);
        GX_ASSERT(texture != nullptr);
        GX_ASSERT(index >= -1);
        GX_ASSERT(index < static_cast<int32_t>(D3D11GpuRenderTarget::MAX_COLOR_ATTACHMENTS));

        auto native = static_cast<D3D11GpuRenderTarget*>(handle);


        GX_ASSERT(static_cast<int32_t>(native->m_Colors) >= 0);
        GX_ASSERT(index < static_cast<int32_t>(native->m_Colors));

        auto native_texture = static_cast<D3D11GpuTexture*>(texture);

        GX_ASSERT(native_texture->m_Dimension == D3D11_SRV_DIMENSION_TEXTURE2D);

        if (index == -1)
        {
            D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
            desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
            desc.Flags              = 0; // D3D11_DSV_READ_ONLY_DEPTH;
            desc.Format             = D3D11GpuGetWriteViewPixelFormat(native_texture->m_Format);
            desc.Texture2D.MipSlice = 0;

            GPU_DX_VALIDATE(m_Device->CreateDepthStencilView(
                native_texture->m_Texture2D,
                &desc,
                &native->m_Depth));
        }
        else
        {
            D3D11_RENDER_TARGET_VIEW_DESC desc{};
            desc.Format             = D3D11GpuGetWriteViewPixelFormat(native_texture->m_Format);
            desc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
            desc.Texture2D.MipSlice = mip_index;

            GPU_DX_VALIDATE(m_Device->CreateRenderTargetView(
                native_texture->m_Texture2D,
                &desc,
                &native->m_Color[index]));
        }
    }

    void D3D11GpuDevice::DestroyRenderTarget(
        GpuRenderTargetHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<D3D11GpuRenderTarget*>(handle);

        DeferResourceRelease(native->m_Depth);

        for (auto&& color : native->m_Color)
        {
            DeferResourceRelease(color);
        }

        delete native;
    }
}
