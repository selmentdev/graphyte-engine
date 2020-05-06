#pragma once
#include <Graphyte/Rendering.module.hxx>
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include <Graphyte/Graphics/Gpu/GpuCommandList.hxx>
#include <Graphyte/Geometry/Mesh.hxx>
#include <Graphyte/Graphics/Gpu/GpuVertex.hxx>

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
