#include <Graphyte/Rendering/StaticMesh.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>
#include <Graphyte/Half.hxx>

namespace Graphyte::Rendering
{
    StaticMesh::StaticMesh() noexcept
        : m_VertexBuffer{}
        , m_IndexBuffer{}
        , m_InputLayout{}
    {
    }

    StaticMesh::~StaticMesh() noexcept = default;

    void StaticMesh::InitializeGpuResources() noexcept
    {
    }

    void StaticMesh::ReleaseGpuResources() noexcept
    {
        if (m_VertexBuffer != nullptr)
        {
            GRenderDevice->DestroyVertexBuffer(m_VertexBuffer);
        }

        if (m_IndexBuffer != nullptr)
        {
            GRenderDevice->DestroyIndexBuffer(m_IndexBuffer);
        }
    }

    void StaticMesh::LoadMesh(Geometry::Mesh& mesh, [[maybe_unused]] Graphics::GpuInputLayout layout) noexcept
    {
        m_InputLayout = Graphics::GpuInputLayout::Complex;

        std::vector<Graphics::GpuVertexComplex> vertices{};

        uint32_t const faces = mesh.GetFacesCount();
        for (uint32_t face = 0; face < faces; ++face)
        {
            Graphics::GpuVertexComplex v1{};
            Graphics::GpuVertexComplex v2{};
            Graphics::GpuVertexComplex v3{};

            uint32_t const w1 = mesh.ComputeWedgeIndex(face, 0);
            uint32_t const w2 = mesh.ComputeWedgeIndex(face, 1);
            uint32_t const w3 = mesh.ComputeWedgeIndex(face, 2);

            uint32_t const i1 = mesh.WedgeIndices[w1];
            uint32_t const i2 = mesh.WedgeIndices[w2];
            uint32_t const i3 = mesh.WedgeIndices[w3];

            v1.Position = mesh.VertexPositions[i1];
            v2.Position = mesh.VertexPositions[i2];
            v3.Position = mesh.VertexPositions[i3];

            //Maths::Float2 const uv1 = mesh.WedgeTextureCoords[0][w1];
            //Maths::Float2 const uv2 = mesh.WedgeTextureCoords[0][w2];
            //Maths::Float2 const uv3 = mesh.WedgeTextureCoords[0][w3];


            //v1.UV[0] = Maths::Half2{ ToHalf(uv1.X), ToHalf(uv1.Y) };
            //v2.UV[0] = Maths::Half2{ ToHalf(uv2.X), ToHalf(uv2.Y) };
            //v3.UV[0] = Maths::Half2{ ToHalf(uv3.X), ToHalf(uv3.Y) };


            vertices.push_back(v1);
            vertices.push_back(v2);
            vertices.push_back(v3);
        }

        Graphics::GpuSubresourceData subresource{};
        subresource.Memory = std::data(vertices);
        subresource.Pitch = static_cast<uint32_t>(sizeof(Graphics::GpuVertexComplex) * std::size(vertices));
        subresource.SlicePitch = 0;

        m_VertexCount = static_cast<uint32_t>(vertices.size());
        m_VertexBuffer = GRenderDevice->CreateVertexBuffer(subresource.Pitch, Graphics::GpuBufferUsage::Static, &subresource);
    }

    void StaticMesh::Render(Graphics::GpuCommandList& commandList) noexcept
    {
        commandList.BindVertexBuffer(m_VertexBuffer, 0, sizeof(Graphics::GpuVertexComplex), 0);
        commandList.Draw(m_VertexCount, 0);
    }
}
