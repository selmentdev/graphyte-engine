#pragma once
#include <GxRendering/Rendering.module.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDefinitions.hxx>

namespace Graphyte::Rendering
{
    static constexpr bool IsDebugRenderEnabled = (GX_ENABLE_DEBUG_RENDER != 0);

    class IDebugRenderer
    {
    public:
        virtual ~IDebugRenderer() noexcept = default;

    public:
        virtual void Update(
            float deltaTime) noexcept = 0;

        virtual void Enable(
            bool value) noexcept = 0;

        virtual void Render(
            Graphics::GpuCommandListHandle commandList) noexcept = 0;

    public:
        virtual void Line(
            Maths::Vector3 start,
            Maths::Vector3 end,
            Maths::Color color,
            float width,
            bool ztest,
            float timeout = 0.0F) noexcept = 0;
    };

    extern RENDERING_API std::unique_ptr<IDebugRenderer> CreateDebugRender(
        Graphics::GpuDeviceHandle device) noexcept;
}
