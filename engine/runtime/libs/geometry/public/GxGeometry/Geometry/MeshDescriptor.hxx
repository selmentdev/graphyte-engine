#pragma once
#include <Graphyte/Geometry.module.hxx>
#include <Graphyte/Storage/Archive.hxx>

namespace Graphyte::Geometry::EditableMesh
{
    struct ElementId
    {
    protected:
        uint32_t m_Value;

    public:
        constexpr ElementId() noexcept
            : m_Value{ ~static_cast<uint32_t>(0) }
        {
        }

        explicit constexpr ElementId(uint32_t value) noexcept
            : m_Value{ value }
        {
        }

        constexpr uint32_t GetValue() const noexcept
        {
            return m_Value;
        }

        constexpr bool operator == (const ElementId& other) const noexcept
        {
            return m_Value == other.m_Value;
        }

        constexpr bool operator != (const ElementId& other) const noexcept
        {
            return m_Value != other.m_Value;
        }

        friend inline Storage::Archive& operator<< (Storage::Archive& archive, ElementId& element) noexcept
        {
            return archive << element.m_Value;
        }
    };

    struct VertexId final : public ElementId
    {
        constexpr VertexId() noexcept
            : ElementId{}
        {
        }

        explicit constexpr VertexId(uint32_t value) noexcept
            : ElementId{ value }
        {
        }

        explicit constexpr VertexId(const ElementId& other) noexcept
            : ElementId{ other.GetValue() }
        {
        }
    };

    struct VertexInstanceId final : public ElementId
    {
        constexpr VertexInstanceId() noexcept
            : ElementId{}
        {
        }

        explicit constexpr VertexInstanceId(uint32_t value) noexcept
            : ElementId{ value }
        {
        }

        explicit constexpr VertexInstanceId(const ElementId& other) noexcept
            : ElementId{ other.GetValue() }
        {
        }
    };

    struct EdgeId final : public ElementId
    {
        constexpr EdgeId() noexcept
            : ElementId{}
        {
        }

        explicit constexpr EdgeId(uint32_t value) noexcept
            : ElementId{ value }
        {
        }

        explicit constexpr EdgeId(const ElementId& other) noexcept
            : ElementId{ other.GetValue() }
        {
        }
    };

    struct PolygonGroupId final : public ElementId
    {
        constexpr PolygonGroupId() noexcept
            : ElementId{}
        {
        }

        explicit constexpr PolygonGroupId(uint32_t value) noexcept
            : ElementId{ value }
        {
        }

        explicit constexpr PolygonGroupId(const ElementId& other) noexcept
            : ElementId{ other.GetValue() }
        {
        }
    };

    struct PolygonId final : public ElementId
    {
        constexpr PolygonId() noexcept
            : ElementId{}
        {
        }

        explicit constexpr PolygonId(uint32_t value) noexcept
            : ElementId{ value }
        {
        }

        explicit constexpr PolygonId(const ElementId& other) noexcept
            : ElementId{ other.GetValue() }
        {
        }
    };

    struct MeshVertex
    {
        std::vector<VertexInstanceId> Instances;
        std::vector<EdgeId> ConnectedEdges;
    };

    struct MeshVertexInstance
    {
        VertexId Vertex;
        std::vector<PolygonId> ConnectedPolygons;
    };

    struct MeshEdge
    {
        VertexId Vertices[2];
        std::vector<PolygonId> ConnectedPolygons;
    };

    struct MeshPolygonContour
    {
        std::vector<VertexInstanceId> Instances;
    };

    struct MeshTriangle
    {
        VertexInstanceId Vertex1;
        VertexInstanceId Vertex2;
        VertexInstanceId Vertex3;
    };

    struct MeshPolygon
    {
        MeshPolygonContour Perimeter;
        std::vector<MeshPolygonContour> Holes;
        std::vector<MeshTriangle> Triangles;
        PolygonGroupId GroupId;
    };

    struct MeshPolygonGroup
    {
        std::vector<PolygonId> Polygons;
    };

    struct MeshDescriptor
    {
        std::vector<MeshVertex> Vertices;
        std::vector<MeshVertexInstance> VertexInstancesCollection;
        std::vector<MeshEdge> EdgesCollection;
        std::vector<MeshPolygon> PolygonsCollection;
        std::vector<MeshPolygonGroup> PolygonGroupsCollection;
    };
}
