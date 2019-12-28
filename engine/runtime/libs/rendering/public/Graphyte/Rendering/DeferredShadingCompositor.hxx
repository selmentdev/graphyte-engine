#pragma once
#include <Graphyte/Rendering/SceneRenderer.hxx>
#include <Graphyte/Maths.hxx>
#include <Graphyte/Rendering/StaticMesh.hxx>

namespace Graphyte::Rendering
{
    class RENDERING_API DeferredShadingCompositor
    {
    public:
        DeferredShadingCompositor(const class DeferredShadingSceneRederer* renderer) noexcept;
        virtual ~DeferredShadingCompositor() noexcept;

    public:
        void ReleaseGpuResources() noexcept;
        void Render(Graphics::GpuCommandList& commandList) noexcept;

    private:
        Rendering::StaticMesh* m_Mesh;
        Graphics::GpuShaderHandle m_ShaderPS;
        Graphics::GpuShaderHandle m_ShaderVS;
        Graphics::GpuSamplerHandle m_Sampler;
        Graphics::GpuTexture2DHandle m_Texture;
        Graphics::GpuResourceSetHandle m_ResourceSet;
        Graphics::GpuGraphicsPipelineStateHandle m_PipelineState;
    };
}
