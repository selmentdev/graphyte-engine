#include <Graphyte/Graphics/GraphicsModule.hxx>
#include <Graphyte/Diagnostics.hxx>

#include "Graphics/VulkanGpuDevice.hxx"

GX_DECLARE_LOG_CATEGORY(LogVulkanModule, Trace, Trace);
GX_DEFINE_LOG_CATEGORY(LogVulkanModule);


class VulkanModule final : public Graphyte::IGraphicsModule
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
        return std::make_unique<Graphyte::Graphics::VulkanGpuDevice>();
    }
};

GX_IMPLEMENT_MODULE(VulkanModule);
