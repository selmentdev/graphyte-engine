#include <GxAssetsShader/Assets.Shader.module.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

#include "D3DShaderCompilerBackend.hxx"
#include <GxAssetsBase/AssetsPipeline/PlatformToolchain.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDefinitions.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>

#include "HlslShaderTraits.hxx"

#include <wrl/client.h>

namespace Graphyte::AssetsPipeline
{
    class D3DShaderIncludeHandler : public ID3DInclude
    {
    private:
        std::string m_BasePath;

    public:
        explicit D3DShaderIncludeHandler(std::string_view base_path) noexcept;
        virtual ~D3DShaderIncludeHandler() noexcept;

        HRESULT STDMETHODCALLTYPE Open(D3D_INCLUDE_TYPE include_type, LPCSTR filename, LPCVOID parent_data, LPCVOID* data, UINT* size) override;
        HRESULT STDMETHODCALLTYPE Close(LPCVOID data) override;
    };

    D3DShaderIncludeHandler::D3DShaderIncludeHandler(std::string_view base_path) noexcept
        : m_BasePath{ base_path }
    {
    }

    D3DShaderIncludeHandler::~D3DShaderIncludeHandler() noexcept = default;

    HRESULT STDMETHODCALLTYPE D3DShaderIncludeHandler::Open(D3D_INCLUDE_TYPE include_type, LPCSTR filename, LPCVOID parent_data, LPCVOID* data, UINT* size)
    {
        (void)include_type;
        (void)parent_data;

        std::vector<std::byte> content{};
        if (Storage::ReadBinary(content, Storage::CombinePath(m_BasePath, filename)) != Status::Success)
        {
            (*data) = nullptr;
            (*size) = 0;
            return E_FAIL;
        }

        auto* raw = new std::byte[content.size()];
        memcpy(raw, std::data(content), std::size(content));

        (*data) = static_cast<LPCVOID>(raw);
        (*size) = static_cast<UINT>(content.size());

        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE D3DShaderIncludeHandler::Close(LPCVOID data)
    {
        if (data != nullptr)
        {
            delete[] reinterpret_cast<const std::byte*>(data);
        }

        return S_OK;
    }
}

namespace Graphyte::AssetsPipeline
{
    std::vector<D3D_SHADER_MACRO> D3DShaderCompilerBackend::GetMacros(const std::vector<std::pair<std::string, std::string>>& macros) noexcept
    {
        std::vector<D3D_SHADER_MACRO> result{};

        for (auto&& item : macros)
        {
            D3D_SHADER_MACRO shader_macro{};
            shader_macro.Name = item.first.c_str();

            if (!item.second.empty())
            {
                shader_macro.Definition = item.second.c_str();
            }

            result.push_back(shader_macro);
        }

        result.emplace_back();

        return result;
    }

    D3DShaderCompilerBackend::D3DShaderCompilerBackend() noexcept
        : m_LibD3DCompiler{}
        , m_D3DCompile{}
    {
        auto sdk_path = PlatformToolchain::GetWindowsSdkBinary();

        System::Impl::WindowsPath wpath{};

        if (System::Impl::WidenStringPath(wpath, Storage::CombinePath(sdk_path, "d3dcompiler_47.dll")))
        {
            m_LibD3DCompiler = ::LoadLibraryW(wpath.data());

            if (m_LibD3DCompiler != nullptr)
            {
                m_D3DCompile = reinterpret_cast<pD3DCompile>(reinterpret_cast<void*>(::GetProcAddress(m_LibD3DCompiler, "D3DCompile")));
            }
        }
    }

    D3DShaderCompilerBackend::~D3DShaderCompilerBackend() noexcept
    {
        m_D3DCompile = nullptr;
        if (m_LibD3DCompiler != nullptr)
        {
            ::FreeLibrary(m_LibD3DCompiler);
        }
    }

    bool D3DShaderCompilerBackend::IsSupported(ShaderCompilerInput& input) const noexcept
    {
        if (m_D3DCompile == nullptr)
        {
            return false;
        }

        switch (input.Platform)
        {
            case System::PlatformType::Windows:
                break;
            default:
                return false;
        }

        switch (input.RenderAPI)
        {
            case Graphics::GpuRenderAPI::D3D11:
                break;
            default:
                return false;
        }

        switch (input.Profile)
        {
            case Graphics::GpuShaderProfile::D3DSM_5_0:
            case Graphics::GpuShaderProfile::D3DSM_5_1:
                break;
            default:
                return false;
        }

        return true;
    }

    bool D3DShaderCompilerBackend::Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept
    {
        auto macros        = HlslShaderTraits::SanitizeMacros(input);
        auto shader_macros = GetMacros(macros);

        std::string entry_point = input.EntryName;

        if (entry_point.empty())
        {
            if (!HlslShaderTraits::GetHlslEntryPoint(entry_point, input.Stage))
            {
                return false;
            }
        }

        std::string profile{};
        if (!HlslShaderTraits::GetHlslProfileName(profile, input.Stage, input.Profile))
        {
            return false;
        }

        UINT flags = 0;

        if (input.EnableAggresiveFlattening)
        {
            flags |= D3DCOMPILE_ALL_RESOURCES_BOUND;
        }

        if (input.EnableStrictMode)
        {
            flags |= D3DCOMPILE_ENABLE_STRICTNESS;
        }

        if (input.AvoidFlowControlConstructs)
        {
            flags |= D3DCOMPILE_AVOID_FLOW_CONTROL;
        }

        if (input.PreferFlowControlConstructs)
        {
            flags |= D3DCOMPILE_PREFER_FLOW_CONTROL;
        }

        if (input.ForceIEEE)
        {
            flags |= D3DCOMPILE_IEEE_STRICTNESS;
        }

        if (input.DisableOptimizations)
        {
            flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
        }

        if (input.DisableValidation)
        {
            flags |= D3DCOMPILE_SKIP_VALIDATION;
        }

        if (input.WarningsAsErrors)
        {
            flags |= D3DCOMPILE_WARNINGS_ARE_ERRORS;
        }

        if (input.EnableDebugInfo)
        {
            flags |= D3DCOMPILE_DEBUG;

#if defined(D3DCOMPILE_DEBUG_NAME_FOR_SOURCE)
            flags |= D3DCOMPILE_DEBUG_NAME_FOR_SOURCE;
#endif

#if defined(D3DCOMPILE_DEBUG_NAME_FOR_BINARY)
            flags |= D3DCOMPILE_DEBUG_NAME_FOR_BINARY;
#endif
        }

        switch (input.OptimizationLevel)
        {
            case ShaderOptimizationLevel::Level0:
                flags |= D3DCOMPILE_OPTIMIZATION_LEVEL0;
                break;
            case ShaderOptimizationLevel::Level1:
                flags |= D3DCOMPILE_OPTIMIZATION_LEVEL1;
                break;
            case ShaderOptimizationLevel::Level2:
                flags |= D3DCOMPILE_OPTIMIZATION_LEVEL2;
                break;
            default:
            case ShaderOptimizationLevel::Level3:
            case ShaderOptimizationLevel::Level4:
                flags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
                break;
        }

        Microsoft::WRL::ComPtr<ID3DBlob> bytecode{};
        Microsoft::WRL::ComPtr<ID3DBlob> errors{};

        D3DShaderIncludeHandler include_handler{ Storage::GetProjectContentDirectory() + "shaders/" };

        HRESULT hr_compile = m_D3DCompile(
            std::data(input.Source),
            std::size(input.Source),
            input.FileName.c_str(),
            std::data(shader_macros),
            &include_handler,
            entry_point.c_str(),
            profile.c_str(),
            flags,
            0,
            bytecode.GetAddressOf(),
            errors.GetAddressOf());

        bool is_success = SUCCEEDED(hr_compile);

        output.Success = is_success;

        if (is_success)
        {
            output.Bytecode.assign(
                reinterpret_cast<const std::byte*>(bytecode->GetBufferPointer()),
                reinterpret_cast<const std::byte*>(bytecode->GetBufferPointer()) + bytecode->GetBufferSize());
        }

        if (errors != nullptr && errors->GetBufferSize() != 0)
        {
            std::string_view log{
                reinterpret_cast<const char*>(errors->GetBufferPointer()),
                errors->GetBufferSize() - 1
            };

            auto lines = Split(log, '\n');

            for (auto&& line : lines)
            {
                output.Log.emplace_back(line);
            }
        }

        return is_success;
    }
}

#endif
