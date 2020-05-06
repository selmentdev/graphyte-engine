#include <GxBase/Base.module.hxx>
#include <GxBase/CommandLine.hxx>
#include <GxBase/System.hxx>
#include <GxGraphics/Graphics/GraphicsModule.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept
    {
        return nullptr;
    }
}
