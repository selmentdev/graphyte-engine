#include <Graphyte/Base.module.hxx>
#include <Graphyte/Graphics/GraphicsModule.hxx>
#include <Graphyte/CommandLine.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept
    {
        //
        // Detect forced rendering device from command line.
        //

        bool force_glcore = CommandLine::Has("--force-glcore");
        bool force_vulkan = CommandLine::Has("--force-vulkan");
        bool force_d3d11 = CommandLine::Has("--force-d3d11");
        bool force_d3d12 = CommandLine::Has("--force-d3d12");

        if (!force_glcore && !force_vulkan && !force_d3d11 && !force_d3d12)
        {
            force_d3d11 = true;
        }


        //
        // Load proper module.
        //

        IGraphicsModule* graphicsModule{};
        Status status{};

        if (force_glcore && graphicsModule == nullptr)
        {
            graphicsModule = ModuleManager::Load<IGraphicsModule>("GxGraphicsGLCore", &status);
        }

        if (force_vulkan && graphicsModule == nullptr)
        {
            graphicsModule = ModuleManager::Load<IGraphicsModule>("GxGraphicsVulkan", &status);
        }

        if (force_d3d11 && graphicsModule == nullptr)
        {
            graphicsModule = ModuleManager::Load<IGraphicsModule>("GxGraphicsD3D11", &status);
        }

        if (force_d3d11 && graphicsModule == nullptr)
        {
            graphicsModule = ModuleManager::Load<IGraphicsModule>("GxGraphicsD3D12", &status);
        }

        if (status != Status::Success)
        {
            GX_LOG(LogPlatform, Fatal, "Failed to setup rendering: {}\n", status);
        }

        if (graphicsModule == nullptr || !graphicsModule->IsSupported())
        {
            GX_LOG(LogPlatform, Fatal, "Rendering not supported\n");
        }

        return graphicsModule->CreateDevice();
    }
}
