#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuTexture : public GpuTexture
    {
    public:
        union
        {
            ID3D11Texture1D* m_Texture1D;
            ID3D11Texture2D* m_Texture2D;
            ID3D11Texture3D* m_Texture3D;
        };
        ID3D11ShaderResourceView* m_ShaderResourceView;
        ID3D11DepthStencilView* m_DepthStencilView;
        ID3D11UnorderedAccessView* m_UnorderedAccessView;

        D3D11_SRV_DIMENSION m_Dimension;
        UINT m_MipLevels;
        UINT m_ArrayCount;
        UINT m_MiscFlags;
        D3D11_USAGE m_Usage;
        PixelFormat m_Format;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuTexture>);
}
