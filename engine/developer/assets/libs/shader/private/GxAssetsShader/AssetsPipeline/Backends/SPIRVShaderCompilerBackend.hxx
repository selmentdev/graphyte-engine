#pragma once
#include <GxAssetsShader/AssetsPipeline/ShaderProcessor.hxx>

namespace Graphyte::AssetsPipeline
{
    class SPIRVShaderCompilerBackend final
        : public IShaderCompilerBackend
    {
    private:
        std::string m_CompilerPath;
        bool m_IsValid;

    public:
        SPIRVShaderCompilerBackend() noexcept;
        virtual ~SPIRVShaderCompilerBackend() noexcept;

        bool IsSupported(ShaderCompilerInput& input) const noexcept override;
        bool Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept override;
    };
}
