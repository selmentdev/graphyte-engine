#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "NullGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class NullGpuRenderTarget final : public GpuRenderTarget { };
    static_assert(!std::is_polymorphic_v<NullGpuRenderTarget>);
}
