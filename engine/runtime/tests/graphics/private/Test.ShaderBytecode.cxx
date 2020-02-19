#include <catch2/catch.hpp>
#include <Graphyte/Storage/ArchiveMemoryReader.hxx>
#include <Graphyte/Storage/ArchiveMemoryWriter.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/Graphics/ShaderBytecode.hxx>

TEST_CASE("Shader Bytecode loading & saving")
{
    using Graphyte::Graphics::ShaderBytecode;
    using Graphyte::Graphics::ShaderBytecodeFlags;

    ShaderBytecode original{};
    std::string_view code{ R"hakuna(struct INPUT_GPU_VERTEX_UI
{
    float3 Position : POSITION;
    float2 UV_0     : TEXCOORD0;
    float2 UV_1     : TEXCOORD1;
    float2 UV_2     : TEXCOORD2;
    float2 UV_3     : TEXCOORD3;
    float4 Color    : COLOR;
};

struct INPUT_GPU_VERTEX_COMPACT
{
    float3 Position : POSITION;
    float3 Normal   : NORMAL;
    float2 UV       : TEXCOORD;
    float3 Tangent  : TANGENT;
};

struct INPUT_GPU_VERTEX_COMPLEX
{
    float3 Position : POSITION;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float2 UV_0     : TEXCOORD0;
    float2 UV_1     : TEXCOORD1;
    float4 Color    : COLOR;
};)hakuna" };

    original.Bytecode.assign(
        reinterpret_cast<const std::byte*>(std::data(code)),
        reinterpret_cast<const std::byte*>(std::data(code) + code.length()));

    original.Platform = Graphyte::System::PlatformType::Windows;
    original.RenderAPI = Graphyte::Graphics::GpuRenderAPI::D3D11;
    original.Profile = Graphyte::Graphics::GpuShaderProfile::D3DSM_5_0;
    original.Stage = Graphyte::Graphics::GpuShaderStage::Pixel;
    original.Flags = ShaderBytecodeFlags::Debug;

    std::vector<std::byte> buffer{};
    {
        Graphyte::Storage::ArchiveMemoryWriter writer{ buffer };
        writer << original;
        REQUIRE(!writer.IsError());
    }

    ShaderBytecode copied{};
    {
        Graphyte::Storage::ArchiveMemoryReader reader{ buffer };
        reader << copied;
        REQUIRE(!reader.IsError());
    }

    REQUIRE(copied.Platform == Graphyte::System::PlatformType::Windows);
    REQUIRE(copied.RenderAPI == Graphyte::Graphics::GpuRenderAPI::D3D11);
    REQUIRE(copied.Profile == Graphyte::Graphics::GpuShaderProfile::D3DSM_5_0);
    REQUIRE(copied.Stage == Graphyte::Graphics::GpuShaderStage::Pixel);
    REQUIRE(copied.Flags == ShaderBytecodeFlags::Debug);
    REQUIRE(copied.Bytecode.size() == original.Bytecode.size());
    REQUIRE(copied.Bytecode == original.Bytecode);
}
