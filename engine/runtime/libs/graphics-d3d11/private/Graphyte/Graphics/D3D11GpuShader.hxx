#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuShader final : public GpuShader
    {
    public:
        union
        {
            ID3D11PixelShader* m_PS;
            ID3D11VertexShader* m_VS;
            ID3D11GeometryShader* m_GS;
            ID3D11HullShader* m_HS;
            ID3D11DomainShader* m_DS;
            ID3D11ComputeShader* m_CS;
        };
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuShader>);
}
