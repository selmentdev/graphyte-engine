#pragma once
#include <GxAssetsMesh/Assets.Mesh.module.hxx>
#include <GxBase/Storage/Archive.hxx>
#include <GxGeometry/Geometry/Model.hxx>

namespace Graphyte::AssetsPipeline::Meshes
{
    struct Chunks final
    {
        static constexpr uint32_t E3D0 = 0x30443345;
        static constexpr uint32_t SUB0 = 0x30425553;
        static constexpr uint32_t SUB1 = 0x31425553;
        static constexpr uint32_t VNT0 = 0x30544e56;
        static constexpr uint32_t TEX0 = 0x30584554;
        static constexpr uint32_t NAM0 = 0x304d414e;
        static constexpr uint32_t TRA0 = 0x30415254;
        static constexpr uint32_t TRA1 = 0x31415254;
    };

    struct ChunkHeader final
    {
        union
        {
            uint32_t Id;
            char FourCC[4];
        };
        uint32_t Size;
    };
    static_assert(sizeof(ChunkHeader) == 8);

    enum struct SubmodelFlags : uint32_t
    {
        DynamicMaterial0    = (1 << 0),
        DynamicMaterial1    = (1 << 1),
        DynamicMaterial2    = (1 << 2),
        DynamicMaterial     = (1 << 3),
        RenderSolid         = (1 << 4),
        RenderAlpha         = (1 << 5),
        B6                  = (1 << 6),
        NeedsChangeMaterial = (1 << 7),
        B8                  = (1 << 8),
        B9                  = (1 << 9),
        B10                 = (1 << 10),
        B11                 = (1 << 11),
        B12                 = (1 << 12),
        B13                 = (1 << 13),
        Animated            = (1 << 14),
        NonIdentityMatrix   = (1 << 15),
        B16                 = (1 << 16),
        B17                 = (1 << 17),
        B18                 = (1 << 18),
        B19                 = (1 << 19),
        B20                 = (1 << 20),
        B21                 = (1 << 21),
        B22                 = (1 << 22),
        B23                 = (1 << 23),
        B24                 = (1 << 24),
        B25                 = (1 << 25),
        B26                 = (1 << 26),
        B27                 = (1 << 27),
        B28                 = (1 << 28),
        B30                 = (1 << 30),
        B31                 = (1U << 31),
    };

    enum struct SubmodelAnimations : uint32_t
    {
        Unknown     = 0xffffffff,
        None        = 0,
        AxisAngle   = 1,
        EulerAngle  = 2,
        Translation = 3,
        SecondsJump = 4,
        MinutesJump = 5,
        HoursJump   = 6,
        Hours24Jump = 7,
        Seconds     = 8,
        Minutes     = 9,
        Hours       = 10,
        Hours24     = 11,
        Billboard   = 12,
        Wind        = 13,
        Sky         = 14,
        IK          = 15,
        IK1         = 16,
        IK2         = 17,
        Digital,
        DigitalClock,
        Undefined,
    };

    enum struct SubmodelType : uint32_t
    {
        Points        = 0,
        Lines         = 1,
        LineLoop      = 2,
        LineStrip     = 3,
        Triangles     = 4,
        TriangleStrip = 5,
        TriangleFan   = 6,
        Quads         = 7,
        QuadStrip     = 8,
        Polygon       = 9,
        GroupRoot     = 256,
        FreeSpotLight = 257,
        Stars         = 258,
        TextGenerator = 259,
    };

    struct Submodel final
    {
        int32_t NextSiblingIndex;
        int32_t FirstChildIndex;
        SubmodelType Type;
        int32_t NameIndex;
        SubmodelAnimations AnimationType;
        SubmodelFlags Flags;
        int32_t ViewMatrixIndex;
        int32_t VerticesCount;
        int32_t FirstVertexIndex;
        int32_t TextureIndex;
        float BrightnessTreshold;
        float LightTreshold;
        Float4 Ambient;
        Float4 Diffuse;
        Float4 Specular;
        Float4 Selfilum;
        float LineSize;
        float MaxDistanceSquared;
        float MinDistanceSquared;
        float NearAttenuationStart;
        float NearAttenuationEnd;
        uint32_t UserNearAttenuation;
        int32_t FarAttenuationDecay;
        float FarDecayRadius;
        float CosFallofAngle;
        float CosHotspotAngle;
        float CosViewAngle;
        std::byte Reserved[100];
    };
    static_assert(sizeof(Submodel) == 256);

    struct Vertex final
    {
        Float3 Position;
        Float3 Normal;
        Float2 Texcoord;
    };
    static_assert(sizeof(Vertex) == (sizeof(float) * 8));


    class E3DImporter
    {
    public:
        bool Load(Storage::Archive& archive, Geometry::Model& model) noexcept;
    };
}
