#include "Graphics.D3D12.pch.hxx"
#include <Graphyte/Graphics/GraphicsModule.hxx>
#include <Graphyte/Diagnostics.hxx>

GX_DECLARE_LOG_CATEGORY(LogD3D12Module, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogD3D12Module);


class D3D12Module final : public Graphyte::IGraphicsModule
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
        return false;
    }

    virtual std::unique_ptr<Graphyte::Graphics::GpuDevice> CreateDevice() noexcept final override
    {
        return nullptr;
    }
};

GX_IMPLEMENT_MODULE(D3D12Module);
