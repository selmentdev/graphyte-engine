#pragma once
#include <Graphyte/AssetsPipeline/ShaderProcessor.hxx>

namespace Graphyte::AssetsPipeline
{
    class OpenGLShaderCompilerBackend final
        : public IShaderCompilerBackend
    {
    private:
        std::string m_Glslc;
        bool m_IsValid;
    public:
        OpenGLShaderCompilerBackend() noexcept;
        virtual ~OpenGLShaderCompilerBackend() noexcept;

        bool IsSupported(ShaderCompilerInput& input) const noexcept override;
        bool Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept override;
    };
}
