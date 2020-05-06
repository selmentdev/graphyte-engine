#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuCommon.hxx"
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuViewport : public GpuViewport
    {
    public:
        IDXGISwapChain1* m_SwapChain;
        IDXGIOutput* m_FullscreenOutput;
        ID3D11Texture2D* m_DepthStencil;
        ID3D11RenderTargetView* m_RenderTargetView;
        ID3D11DepthStencilView* m_DepthStencilView;

        HWND m_Handle;
        uint32_t m_Width;
        uint32_t m_Height;
        PixelFormat m_ColorFormat;
        PixelFormat m_DepthFormat;
        bool m_Fullscreen;
        bool m_Valid;

        GpuMsaaQuality m_MsaaQuality;

    public:
        DXGI_MODE_DESC GetCompatibleMode() const noexcept;
        void Reset(bool force) noexcept;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuViewport>);
}
