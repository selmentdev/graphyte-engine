#pragma once
#include <Graphyte/Rendering.module.hxx>
#include <Graphyte/Graphics/Gpu/GpuCommandList.hxx>

namespace Graphyte::Rendering
{
    struct SceneView final
    {
    };

    class RENDERING_API SceneRenderer
    {
    public:
        SceneRenderer() noexcept;
        virtual ~SceneRenderer() noexcept;

    public:
        virtual void ReleaseGpuResources() noexcept = 0;
        virtual void Render(Graphics::GpuCommandList& commandList) noexcept = 0;
    };
}
