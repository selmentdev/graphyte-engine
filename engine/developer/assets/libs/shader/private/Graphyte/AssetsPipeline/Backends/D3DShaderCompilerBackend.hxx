#pragma once
#include <Graphyte/Assets.Shader.module.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS

#include <Graphyte/AssetsPipeline/ShaderProcessor.hxx>
#include <Graphyte/System/Library.hxx>

#include "dxcapi.h"
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
