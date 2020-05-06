#include <catch2/catch.hpp>
#include <GxBase/Storage/ArchiveMemoryReader.hxx>
#include <GxBase/Storage/ArchiveMemoryWriter.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/BinaryFormat.hxx>
#include <GxBase/Compression.hxx>

#if false
TEST_CASE("Mesh serializer with wedges")
{
    auto p0 = Graphyte::Float3(-0.5F, -0.5F,  0.5F);
    auto p1 = Graphyte::Float3( 0.5F, -0.5F,  0.5F);
    auto p2 = Graphyte::Float3( 0.5F, -0.5F, -0.5F);
    auto p3 = Graphyte::Float3(-0.5F, -0.5F, -0.5F);
    auto p4 = Graphyte::Float3(-0.5F,  0.5F,  0.5F);
    auto p5 = Graphyte::Float3( 0.5F,  0.5F,  0.5F);
    auto p6 = Graphyte::Float3( 0.5F,  0.5F, -0.5F);
    auto p7 = Graphyte::Float3(-0.5F,  0.5F, -0.5F);


    auto nu = Graphyte::Float3( 0.0F,  1.0F,  0.0F);
    auto nd = Graphyte::Float3( 0.0F, -1.0F,  0.0F);
    auto nf = Graphyte::Float3( 0.0F,  0.0F,  1.0F);
    auto nb = Graphyte::Float3( 0.0F,  0.0F, -1.0F);
    auto nl = Graphyte::Float3(-1.0F,  0.0F,  0.0F);
    auto nr = Graphyte::Float3( 1.0F,  0.0F,  0.0F);


    auto _11 = Graphyte::Float2(0.0F, 0.0F);
    auto _01 = Graphyte::Float2(1.0F, 0.0F);
    auto _10 = Graphyte::Float2(0.0F, 1.0F);
    auto _00 = Graphyte::Float2(1.0F, 1.0F);

    auto c = Graphyte::ColorBGRA(1.0F, 1.0F, 1.0F, 1.0F);

    Graphyte::Graphics::Geometry::RawMesh mesh{};

    mesh.VertexPositions.assign({
        p0, p1, p2, p3,
        p4, p5, p6, p7
    });

    mesh.WedgeIndices.assign({
        // bottom
        0, 1, 3,
        1, 2, 3,
        // right
        2, 1, 6,
        1, 5, 6,
        // back
        1, 0, 5,
        0, 4, 5,
        // front
        3, 2, 7,
        2, 6, 7,
        // left
        0, 3, 4,
        3, 7, 4,
        // top
        7, 6, 4,
        6, 5, 4,
    });

    mesh.WedgeTexCoords[0].assign({
        _00, _10, _01, _10, _11, _01,
        _00, _10, _01, _10, _11, _01,
        _00, _10, _01, _10, _11, _01,
        _00, _10, _01, _10, _11, _01,
        _00, _10, _01, _10, _11, _01,
        _00, _10, _01, _10, _11, _01,
    });

    mesh.WedgeTangentZ.assign({
        nd, nd, nd, nd, nd, nd,
        nl, nl, nl, nl, nl, nl,
        nf, nf, nf, nf, nf, nf,
        nb, nb, nb, nb, nb, nb,
        nr, nr, nr, nr, nr, nr,
        nu, nu, nu, nu, nu, nu,
    });

    mesh.FaceMaterialIndices.assign({
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
    });

    mesh.WedgeColors.assign({
        c, c, c, c, c, c,
        c, c, c, c, c, c,
        c, c, c, c, c, c,
        c, c, c, c, c, c,
        c, c, c, c, c, c,
        c, c, c, c, c, c,
    });

    CHECK(mesh.IsValid());

    std::vector<std::byte> buffer{};
    {
        Graphyte::Storage::ArchiveMemoryWriter writer{ buffer };
        writer << mesh;
    }

    Graphyte::Graphics::Geometry::RawMesh deserialized{};
    {
        Graphyte::Storage::ArchiveMemoryReader reader{ buffer };
        reader << deserialized;
    }

    std::vector<std::byte> compressed{};
    REQUIRE(Graphyte::Compression::CompressBlock(Graphyte::CompressionMethod::LZ4HC, compressed, buffer));

    std::vector<std::byte> decompressed{};
    decompressed.resize(buffer.size());

    REQUIRE(Graphyte::Compression::DecompressBlock(Graphyte::CompressionMethod::LZ4HC, decompressed, compressed));
    REQUIRE(buffer == decompressed);

    REQUIRE(mesh.FaceMaterialIndices == deserialized.FaceMaterialIndices);
    REQUIRE(mesh.FaceSmoothingMasks == deserialized.FaceSmoothingMasks);
    REQUIRE(mesh.VertexPositions == deserialized.VertexPositions);
    REQUIRE(mesh.WedgeIndices == deserialized.WedgeIndices);
    REQUIRE(mesh.WedgeTangentX == deserialized.WedgeTangentX);
    REQUIRE(mesh.WedgeTangentY == deserialized.WedgeTangentY);
    REQUIRE(mesh.WedgeTangentZ == deserialized.WedgeTangentZ);

    for (size_t i = 0; i < Graphyte::Graphics::Geometry::RawMesh::MaxTextureCoords; ++i)
    {
        REQUIRE(mesh.WedgeTexCoords[i] == deserialized.WedgeTexCoords[i]);
    }

    REQUIRE(mesh.WedgeColors == deserialized.WedgeColors);
}


namespace
{
    using namespace Graphyte;

    class Mesh final
    {
    public:
        std::vector<Float3> Vertices;
        std::vector<Float3> Normals;
        std::vector<uint32_t> Indices;
    };

    enum struct MeshChannel : uint32_t
    {
        Indices,
        Vertices,
        Normals,
    };

    struct MeshChannelHeader final
    {
        uint32_t Size;
        MeshChannel Channel;

        friend inline Storage::Archive& operator << (Storage::Archive& archive, MeshChannelHeader& header) noexcept
        {
            return archive
                << header.Size
                << header.Channel;
        }
    };

    class MeshSerializer final
    {
    public:
        static void Save(Storage::Archive& archive, Mesh& mesh) noexcept
        {
            Storage::BinaryFormatHeader header{};
            archive << header;

            MeshChannelHeader vertices{};
            vertices.Size = static_cast<uint32_t>(sizeof(Float3) * mesh.Vertices.size());
            vertices.Channel = MeshChannel::Vertices;
            archive << vertices;
            archive.Serialize(std::data(mesh.Vertices), sizeof(Float3) * std::size(mesh.Vertices));

            MeshChannelHeader normals{};
            normals.Size = static_cast<uint32_t>(sizeof(Float3) * mesh.Normals.size());
            normals.Channel = MeshChannel::Normals;
            archive << normals;
            archive.Serialize(std::data(mesh.Normals), sizeof(Float3) * std::size(mesh.Normals));

            MeshChannelHeader indices{};
            indices.Size = static_cast<uint32_t>(sizeof(uint32_t) * mesh.Indices.size());
            indices.Channel = MeshChannel::Indices;
            archive << indices;
            archive.Serialize(std::data(mesh.Indices), sizeof(uint32_t) * std::size(mesh.Indices));
        }
    };
}
#endif
