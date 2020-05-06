#include <GxAssetsShader/Assets.Shader.module.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

#include "DXCShaderCompilerBackend.hxx"
#include <GxAssetsBase/AssetsPipeline/PlatformToolchain.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDefinitions.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>

#include "HlslShaderTraits.hxx"

namespace Graphyte::AssetsPipeline
{
    class DXCIncludeHandler : public IDxcIncludeHandler
    {
    public:
        DXCIncludeHandler(std::string_view base_path) noexcept;
        virtual ~DXCIncludeHandler() noexcept;

        HRESULT STDMETHODCALLTYPE LoadSource(LPCWSTR pFilename, IDxcBlob** ppIncludeSource) override;
    };
}

namespace Graphyte::AssetsPipeline
{
    DXCShaderCompilerBackend::DXCShaderCompilerBackend() noexcept
        : m_LibDxCompiler{}
        , m_LibDxil{}
        , m_DxcLibrary{}
        , m_DxcCompiler{}
    {
        using Storage::Path;

        auto sdk_path = PlatformToolchain::GetWindowsSdkBinary();

        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, Path::Combine(sdk_path, "dxcompiler.dll"));

        m_LibDxCompiler = ::LoadLibraryW(wpath.data());

        if (m_LibDxCompiler != nullptr)
        {
            auto create_instance = reinterpret_cast<DxcCreateInstanceProc>(reinterpret_cast<void*>(::GetProcAddress(m_LibDxCompiler, "DxcCreateInstance")));

            if (create_instance != nullptr)
            {
                HRESULT hr{};

                hr = create_instance(
                    CLSID_DxcLibrary,
                    __uuidof(IDxcLibrary),
                    reinterpret_cast<void**>(m_DxcLibrary.GetAddressOf())
                );

                GX_ABORT_UNLESS(SUCCEEDED(hr), "Failed to create DXC Library");

                hr = create_instance(
                    CLSID_DxcCompiler,
                    __uuidof(IDxcCompiler),
                    reinterpret_cast<void**>(m_DxcCompiler.GetAddressOf())
                );

                GX_ABORT_UNLESS(SUCCEEDED(hr), "Failed to create DXC Compiler");

                System::Impl::WidenStringPath(wpath, Path::Combine(sdk_path, "dxil.dll"));
                m_LibDxil = ::LoadLibraryW(wpath.data());
            }
        }
    }

    DXCShaderCompilerBackend::~DXCShaderCompilerBackend() noexcept
    {
        m_DxcLibrary = nullptr;
        m_DxcCompiler = nullptr;

        if (m_LibDxCompiler != nullptr)
        {
            ::FreeLibrary(m_LibDxCompiler);
        }

        if (m_LibDxil != nullptr)
        {
            ::FreeLibrary(m_LibDxil);
        }
    }

    bool DXCShaderCompilerBackend::IsSupported(ShaderCompilerInput& input) const noexcept
    {
        if (m_DxcLibrary != nullptr && m_DxcCompiler != nullptr)
        {

            switch (input.Platform)
            {
            case System::PlatformType::Windows:
                break;
            default:
                return false;
            }

            switch (input.RenderAPI)
            {
            case Graphics::GpuRenderAPI::D3D12:
                break;
            default:
                return false;
            }

            switch (input.Profile)
            {
            case Graphics::GpuShaderProfile::D3DSM_6_0:
            case Graphics::GpuShaderProfile::D3DSM_6_1:
            case Graphics::GpuShaderProfile::D3DSM_6_2:
                break;
            default:
                return false;
            }

            return true;
        }

        return false;
    }

    bool DXCShaderCompilerBackend::Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept
    {
        using Storage::Path;

        Microsoft::WRL::ComPtr<IDxcBlobEncoding> source_blob{};
        if (FAILED(m_DxcLibrary->CreateBlobWithEncodingFromPinned(std::data(input.Source), static_cast<UINT32>(std::size(input.Source)), CP_UTF8, source_blob.GetAddressOf())))
        {
            return false;
        }

        System::Impl::WindowsPath wname{};
        if (!System::Impl::WidenStringPath(wname, input.FileName))
        {
            return false;
        }

        std::wstring profile_name{};
        if (!HlslShaderTraits::GetHlslProfileName(profile_name, input.Stage, input.Profile))
        {
            return false;
        }

        std::wstring entry_name = System::Impl::WidenString(input.EntryName);
        if (entry_name.empty())
        {
            if (!HlslShaderTraits::GetHlslEntryPoint(entry_name, input.Stage))
            {
                return false;
            }
        }

        auto compiler_options = GetCompilerOptions(input);

        auto definitions_source = HlslShaderTraits::SanitizeMacrosW(input);

        auto dxc_defines = GetCompilerDefinitions(definitions_source);

        Microsoft::WRL::ComPtr<IDxcOperationResult> compile_result;
        HRESULT hr_compile = m_DxcCompiler->Compile(
            source_blob.Get(),
            wname.data(),
            entry_name.c_str(),
            profile_name.c_str(),
            std::data(compiler_options),
            static_cast<UINT32>(std::size(compiler_options)),
            std::data(dxc_defines),
            static_cast<UINT32>(std::size(dxc_defines)),
            nullptr,
            compile_result.ReleaseAndGetAddressOf()
        );

        if (FAILED(hr_compile))
        {
            return false;
        }

        HRESULT hr_status{};

        if (FAILED(compile_result->GetStatus(&hr_status)))
        {
            return false;
        }

        output.Success = SUCCEEDED(hr_status);
        if (SUCCEEDED(hr_status))
        {
            Microsoft::WRL::ComPtr<IDxcBlob> bytecode{};
            if (FAILED(compile_result->GetResult(bytecode.GetAddressOf())))
            {
                return false;
            }

            output.Bytecode.assign(
                reinterpret_cast<std::byte*>(bytecode->GetBufferPointer()),
                reinterpret_cast<std::byte*>(bytecode->GetBufferPointer()) + bytecode->GetBufferSize()
            );
        }

        Microsoft::WRL::ComPtr<IDxcBlobEncoding> errors{};
        if (FAILED(compile_result->GetErrorBuffer(errors.GetAddressOf())))
        {
            return false;
        }

        Microsoft::WRL::ComPtr<IDxcBlobEncoding> errors_utf8{};
        if (FAILED(m_DxcLibrary->GetBlobAsUtf8(errors.Get(), errors_utf8.GetAddressOf())))
        {
            return false;
        }

        std::string error_log{
            reinterpret_cast<const char*>(errors_utf8->GetBufferPointer()),
            errors_utf8->GetBufferSize()
        };

        GX_LOG(LogShaderCompilerFrontend, Error, "Errors: `{}`\n", error_log);

        return true;
    }

    std::vector<const wchar_t*> DXCShaderCompilerBackend::GetCompilerOptions(const ShaderCompilerInput& input) noexcept
    {
        std::vector<const wchar_t*> result{};

        if (input.EnableAggresiveFlattening)
        {
            // Enables agressive flattening
            result.push_back(L"-all_resources_bound");
        }

        if (input.Enable16BitTypes)
        {
            // Enable 16bit types and disable min precision types. Available in HLSL 2018 and shader model 6.2
            result.push_back(L"-enable-16bit-types");
        }

        if (input.EnableStrictMode)
        {
            // Enable strict mode
            result.push_back(L"-Ges");
        }

        if (input.AvoidFlowControlConstructs)
        {
            // Avoid flow control constructs
            result.push_back(L"-Gfa");
        }

        if (input.PreferFlowControlConstructs)
        {
            // Prefer flow control constructs
            result.push_back(L"-Gfp");
        }

        if (input.ForceIEEE)
        {
            // Force IEEE strictness
            result.push_back(L"-Gis");
        }

        if (input.SuppressWarnings)
        {
            // Suppress warnings
            result.push_back(L"-no-warnings");
        }

        if (input.DisableOptimizations)
        {
            // Disable optimizations
            result.push_back(L"-Od");
        }

        if (input.DisableValidation)
        {
            // Disable validation
            result.push_back(L"-Vd");
        }

        if (input.WarningsAsErrors)
        {
            // Treat warnings as errors
            result.push_back(L"-WX");
        }

        if (input.EnableDebugInfo)
        {
            // Enable debug information
            result.push_back(L"-Zi");
        }

        return result;
    }

    std::vector<DxcDefine> DXCShaderCompilerBackend::GetCompilerDefinitions(const std::vector<std::pair<std::wstring, std::wstring>>& definitions) noexcept
    {
        std::vector<DxcDefine> result{};

        for (auto&& item : definitions)
        {
            DxcDefine def{};
            def.Name = item.first.c_str();

            if (!item.second.empty())
            {
                def.Value = item.second.c_str();
            }

            result.push_back(def);
        }

        return result;
    }
}

#endif
