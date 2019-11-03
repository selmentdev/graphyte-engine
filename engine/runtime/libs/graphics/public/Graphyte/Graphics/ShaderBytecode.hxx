#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Storage/Archive.hxx>
#include <Graphyte/Graphics/Gpu/GpuDevice.hxx>

namespace Graphyte::Graphics
{
    // TODO: Move this to module.rendering!

    enum struct ShaderBytecodeFlags : uint32_t
    {
        None = 0,
        Debug = 1 << 0,
        Helper = 1 << 1,
    };
    GX_ENUM_CLASS_FLAGS(ShaderBytecodeFlags);

    class ShaderBytecode final
    {
    public:
        static constexpr const uint64_t FileSignature = 0xb084f8149e928dd6;
        static constexpr const uint32_t CurrentVersion = 1;

    public:
        std::vector<std::byte> Bytecode;
        System::PlatformType Platform;
        GpuRenderAPI RenderAPI;
        GpuShaderProfile Profile;
        GpuShaderStage Stage;
        ShaderBytecodeFlags Flags;

    public:
        GpuShaderBytecode ToShaderBytecode() const noexcept
        {
            return { std::data(Bytecode), std::size(Bytecode) };
        }

    public:
        GRAPHICS_API friend Storage::Archive& operator << (Storage::Archive& archive, ShaderBytecode& bytecode) noexcept;
    };
}
