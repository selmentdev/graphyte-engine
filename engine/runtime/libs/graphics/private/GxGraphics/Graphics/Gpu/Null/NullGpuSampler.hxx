#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class NullGpuSampler final : public GpuSampler
    {
    };
    static_assert(!std::is_polymorphic_v<NullGpuSampler>);
}
