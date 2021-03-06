#include <GxGraphics/Graphics/Gpu/GpuDevice.hxx>
#include "Null/NullGpuDevice.hxx"

namespace Graphyte
{
    GRAPHICS_API std::unique_ptr<Graphics::GpuDevice> g_RenderDevice{ nullptr };
}


namespace Graphyte::Graphics
{
    GpuDevice::GpuDevice() noexcept = default;

    GpuDevice::~GpuDevice() noexcept = default;

    void GpuDevice::Tick([[maybe_unused]] float time) noexcept
    {
    }
}
