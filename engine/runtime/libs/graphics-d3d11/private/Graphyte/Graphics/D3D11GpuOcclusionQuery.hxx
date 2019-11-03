#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "D3D11GpuCommon.hxx"

namespace Graphyte::Graphics
{
    class D3D11GpuOcclusionQuery : public GpuOcclusionQuery
    {
    public:
        ID3D11Query* m_Query;
    };
    static_assert(!std::is_polymorphic_v<D3D11GpuOcclusionQuery>);
}
