#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuDevice.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuSampler final : public GpuSampler
    {
    public:
        ID3D11SamplerState* m_Sampler;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuSampler>);
}
