#include <GxGraphics/Graphics.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    extern std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept;
}

namespace Graphyte::Graphics
{
    GRAPHICS_API void Initialize() noexcept
    {
        g_RenderDevice = Impl::CreateRenderDevice();
    }

    GRAPHICS_API void Finalize() noexcept
    {
        g_RenderDevice = nullptr;
    }
}
