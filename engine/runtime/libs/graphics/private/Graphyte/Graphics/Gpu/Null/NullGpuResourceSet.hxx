#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuResourceSet : public GpuResourceSet { };
    static_assert(!std::is_polymorphic_v<NullGpuResourceSet>);
}
