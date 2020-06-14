#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class NullGpuTexture : public GpuTexture
    {
    };
    static_assert(!std::is_polymorphic_v<NullGpuTexture>);
}
