#include <GxBase/Base.module.hxx>
#include <GxBase/CommandLine.hxx>
#include <GxBase/System.hxx>
#include <GxGraphics/Graphics/GraphicsModule.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics::Impl
{
    std::unique_ptr<Graphics::GpuDevice> CreateRenderDevice() noexcept
    {
        //
        // Detect forced rendering device from command line.
        //

        bool force_glcore = CommandLine::Get("--force-glcore").has_value();
        bool force_vulkan = CommandLine::Get("--force-vulkan").has_value();
        bool force_d3d11  = CommandLine::Get("--force-d3d11").has_value();
        bool force_d3d12  = CommandLine::Get("--force-d3d12").has_value();

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
