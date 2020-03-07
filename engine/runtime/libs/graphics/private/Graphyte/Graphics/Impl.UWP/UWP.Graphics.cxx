#include <Graphyte/Base.module.hxx>
#include <Graphyte/Graphics/GraphicsModule.hxx>
#include <Graphyte/CommandLine.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept
    {
        return nullptr;
    }
}
