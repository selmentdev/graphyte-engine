#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuComputePipelineState final : public GpuComputePipelineState
    {
    public:
        ID3D11ComputeShader* m_CS;
        uint32_t m_NodeMask;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuComputePipelineState>);
}
