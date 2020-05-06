#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuUniformBuffer : public GpuUniformBuffer
    {
    public:
        ID3D11Buffer* m_Resource;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuUniformBuffer>);
}
