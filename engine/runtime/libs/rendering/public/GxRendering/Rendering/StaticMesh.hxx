#pragma once
#include <GxRendering/Rendering.module.hxx>
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include <GxGraphics/Graphics/Gpu/GpuCommandList.hxx>
#include <GxGeometry/Geometry/Mesh.hxx>
#include <GxGraphics/Graphics/Gpu/GpuVertex.hxx>

namespace Graphyte::Rendering
{
    class RENDERING_API StaticMesh
    {
    public:
        StaticMesh() noexcept;
        virtual ~StaticMesh() noexcept;

    public:
        virtual void InitializeGpuResources() noexcept;
        virtual void ReleaseGpuResources() noexcept;

        void LoadMesh(Geometry::Mesh& mesh, Graphics::GpuInputLayout layout) noexcept;
        void Render(Graphics::GpuCommandList& commandList) noexcept;

    protected:
        Graphics::GpuVertexBufferHandle m_VertexBuffer;
        Graphics::GpuIndexBufferHandle m_IndexBuffer;
        Graphics::GpuInputLayout m_InputLayout;
        uint32_t m_VertexCount;
    };
}
