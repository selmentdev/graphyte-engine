#pragma once
#include <Graphyte/Rendering/SceneRenderer.hxx>
#include <Graphyte/Maths.hxx>
#include <Graphyte/Rendering/StaticMesh.hxx>

namespace Graphyte::Rendering
{
    class RENDERING_API DeferredShadingSceneRenderer : public SceneRenderer
    {
    public:
        struct alignas(16) CameraParamsBuffer final
        {
            Maths::Float4x4A View;
            Maths::Float4x4A Projection;
            Maths::Float4x4A ViewProjection;
        };

        struct alignas(16) ObjectParamsBuffer final
        {
            Maths::Float4x4A World;
            Maths::Float4x4A InverseWorld;
        };

        // debug
        std::vector<std::pair<Rendering::StaticMesh*, Maths::Float4x4A>> Meshes;

    public:
        DeferredShadingSceneRenderer(uint32_t width, uint32_t height) noexcept;
        virtual ~DeferredShadingSceneRenderer() noexcept;

    public:
        void SetupView(Maths::Matrix view, Maths::Matrix projection) noexcept;

    public:
        void ReleaseGpuResources() noexcept override;
        void Render(Graphics::GpuCommandList& commandList) noexcept override;
        void RenderGeometry(Graphics::GpuCommandList& commandList) noexcept;
        void RenderLights(Graphics::GpuCommandList& commandList) noexcept;

    private:
        Graphics::GpuRenderTargetHandle m_RenderTarget;
        Graphics::GpuTexture2DHandle m_Color;
        Graphics::GpuTexture2DHandle m_Depth;
        Graphics::GpuUniformBufferHandle m_CameraParams;
        Graphics::GpuUniformBufferHandle m_ObjectParams;

        uint32_t m_Width;
        uint32_t m_Height;

        Graphics::GpuShaderHandle m_ShaderPS;
        Graphics::GpuShaderHandle m_ShaderVS;
        Graphics::GpuSamplerHandle m_Sampler;
        Graphics::GpuTexture2DHandle m_Texture;
        Graphics::GpuResourceSetHandle m_ResourceSet;
        Graphics::GpuGraphicsPipelineStateHandle m_PipelineState;
    };
}
