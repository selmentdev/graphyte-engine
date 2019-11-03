#include "Graphics.pch.hxx"
#include <Graphyte/Graphics.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    extern std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept;
}

namespace Graphyte::Graphics
{
    GRAPHICS_API void Initialize() noexcept
    {
        GRenderDevice = Impl::CreateRenderDevice();
    }

    GRAPHICS_API void Finalize() noexcept
    {
        GRenderDevice = nullptr;
    }
}
