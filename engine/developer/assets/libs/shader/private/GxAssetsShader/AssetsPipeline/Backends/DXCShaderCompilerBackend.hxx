#pragma once
#include <GxAssetsShader/AssetsPipeline/ShaderProcessor.hxx>
#include <GxBase/System/Library.hxx>

#include <Unknwn.h>
#include <dxcapi.h>
#include <wrl/client.h>

namespace Graphyte::AssetsPipeline
{
    class DXCShaderCompilerBackend final
        : public IShaderCompilerBackend
    {
    private:
        HMODULE m_LibDxCompiler;
        HMODULE m_LibDxil;

        Microsoft::WRL::ComPtr<IDxcLibrary> m_DxcLibrary;
        Microsoft::WRL::ComPtr<IDxcCompiler> m_DxcCompiler;

    public:
        DXCShaderCompilerBackend() noexcept;
        virtual ~DXCShaderCompilerBackend() noexcept;

        bool IsSupported(ShaderCompilerInput& input) const noexcept override;
        bool Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept override;

    private:
        static std::vector<const wchar_t*> GetCompilerOptions(const ShaderCompilerInput& input) noexcept;
        static std::vector<DxcDefine> GetCompilerDefinitions(const std::vector<std::pair<std::wstring, std::wstring>>& definitions) noexcept;
    };
}
