#pragma once
#include "D3D11GpuCommon.hxx"
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>

namespace Graphyte::Graphics
{
    class D3D11GpuRenderTarget final : public GpuRenderTarget
    {
    public:
        static const constexpr size_t MAX_COLOR_ATTACHMENTS = 8;

    public:
        ID3D11RenderTargetView* m_Color[MAX_COLOR_ATTACHMENTS];
        ID3D11DepthStencilView* m_Depth;

        uint32_t m_Colors;
        uint32_t m_Width;
        uint32_t m_Height;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuRenderTarget>);
}
