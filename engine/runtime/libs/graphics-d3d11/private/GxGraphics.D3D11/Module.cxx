#include <GxBase/Diagnostics.hxx>
#include <GxGraphics/Graphics/GraphicsModule.hxx>

#include "Graphics/D3D11GpuDevice.hxx"

GX_DECLARE_LOG_CATEGORY(LogD3D11Module, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogD3D11Module);


class D3D11Module final : public Graphyte::IGraphicsModule
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
        return std::make_unique<Graphyte::Graphics::D3D11GpuDevice>();
    }
};

GX_IMPLEMENT_MODULE(D3D11Module);
