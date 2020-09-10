#pragma once
#include <GxAssetsShader/Assets.Shader.module.hxx>

#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

#include <GxAssetsShader/AssetsPipeline/ShaderProcessor.hxx>
#include <GxBase/System/Library.hxx>

#include <Unknwn.h>
#include <dxcapi.h>
#include <d3dcompiler.h>

namespace Graphyte::AssetsPipeline
{
    class D3DShaderCompilerBackend final
        : public IShaderCompilerBackend
    {
    private:
        HMODULE m_LibD3DCompiler;
        pD3DCompile m_D3DCompile;

    private:
        static std::vector<D3D_SHADER_MACRO> GetMacros(const std::vector<std::pair<std::string, std::string>>& macros) noexcept;

    public:
        D3DShaderCompilerBackend() noexcept;
        virtual ~D3DShaderCompilerBackend() noexcept;

        bool IsSupported(ShaderCompilerInput& input) const noexcept override;
        bool Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept override;
    };
}

#endif
