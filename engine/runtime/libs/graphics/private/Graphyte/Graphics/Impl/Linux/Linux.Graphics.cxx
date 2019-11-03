#include "Graphics.pch.hxx"
#include <Graphyte/CommandLine.hxx>
#include <Graphyte/Platform.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept
    {
        return nullptr;
    }
}
