#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class NullGpuViewport : public GpuViewport { };
    static_assert(!std::is_polymorphic_v<NullGpuViewport>);
}
