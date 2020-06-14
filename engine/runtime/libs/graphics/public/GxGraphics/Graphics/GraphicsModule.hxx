#pragma once
#include <GxBase/Modules.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte
{
    struct IGraphicsModule : public IModule
    {
    public:
        virtual ~IGraphicsModule() noexcept = default;

    public:
        virtual bool IsSupported() noexcept = 0;

        virtual std::unique_ptr<Graphics::GpuDevice> CreateDevice() noexcept = 0;
    };
}
