#include "Graphics.GLCore.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Graphics/GraphicsModule.hxx>

#include "Graphics/OpenGLGpuDevice.hxx"

GX_DECLARE_LOG_CATEGORY(LogGLCoreModule, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogGLCoreModule);


class GLCoreModule final : public Graphyte::IGraphicsModule
{
public:
    virtual void OnInitialize() noexcept final override
    {
    }

    virtual void OnFinalize() noexcept final override
    {
    }

    virtual bool IsSupported() noexcept final override
    {
        return true;
    }

    virtual std::unique_ptr<Graphyte::Graphics::GpuDevice> CreateDevice() noexcept final override
    {
        return std::make_unique<Graphyte::Graphics::OpenGLGpuDevice>();
    }
};

GX_IMPLEMENT_MODULE(GLCoreModule);
