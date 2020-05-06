#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuGraphicsPipelineState final : public GpuGraphicsPipelineState
    {
    public:
        ID3D11RasterizerState* m_RasterizerState;
        ID3D11DepthStencilState* m_DepthStencilState;
        ID3D11InputLayout* m_InputLayout;
        ID3D11BlendState* m_BlendState;

        ID3D11VertexShader* m_VS;
        ID3D11PixelShader* m_PS;
        ID3D11GeometryShader* m_GS;
        ID3D11DomainShader* m_DS;
        ID3D11HullShader* m_HS;

        uint32_t m_BlendState_SampleMask;
        Float4 m_BlendState_BlendFactors;
        D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuGraphicsPipelineState>);
}
