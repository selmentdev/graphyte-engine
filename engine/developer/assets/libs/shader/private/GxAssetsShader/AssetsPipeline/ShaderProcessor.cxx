#include <GxAssetsBase/AssetsPipeline/AssetProcessor.hxx>
#include <GxAssetsBase/AssetsPipeline/AssetProcessorFactory.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxGraphics/Graphics/ShaderBytecode.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Hash/XXHash.hxx>
#include <GxBase/CommandLine.hxx>

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include "Backends/D3DShaderCompilerBackend.hxx"
#include "Backends/DXCShaderCompilerBackend.hxx"
#endif

#include "Backends/OpenGLShaderCompilerBackend.hxx"
#include "Backends/SPIRVShaderCompilerBackend.hxx"

namespace Graphyte::AssetsPipeline
{
    GX_DEFINE_LOG_CATEGORY(LogShaderCompilerFrontend);

    template <typename TValue>
    struct EnumNameValue
    {
        std::string_view Name;
        TValue Value;
    };

    EnumNameValue<System::PlatformType> GPlatformTypeNames[] = {
        { "windows", System::PlatformType::Windows },
        { "android", System::PlatformType::Android },
        { "linux", System::PlatformType::Linux },
    };

    std::string_view ToString(System::PlatformType value) noexcept
    {
        auto it = std::find_if(std::begin(GPlatformTypeNames), std::end(GPlatformTypeNames), [&](auto v)
        {
            return v.Value == value;
        });

        if (it != std::end(GPlatformTypeNames))
        {
            return it->Name;
        }

        return {};
    }

    bool FromString(System::PlatformType& result, std::string_view value) noexcept
    {
        auto it = std::find_if(std::begin(GPlatformTypeNames), std::end(GPlatformTypeNames), [&](auto v)
        {
            return v.Name == value;
        });

        if (it != std::end(GPlatformTypeNames))
        {
            result = it->Value;
            return true;
        }

        return false;
    }

    EnumNameValue<Graphics::GpuRenderAPI> GRenderAPINames[] = {
        { "d3d11", Graphics::GpuRenderAPI::D3D11 },
        { "d3d12", Graphics::GpuRenderAPI::D3D12 },
        { "vulkan", Graphics::GpuRenderAPI::Vulkan },
        { "opengl", Graphics::GpuRenderAPI::OpenGL },
    };

    std::string_view ToString(Graphics::GpuRenderAPI value) noexcept
    {
        auto it = std::find_if(std::begin(GRenderAPINames), std::end(GRenderAPINames), [&](auto v)
        {
            return v.Value == value;
        });

        if (it != std::end(GRenderAPINames))
        {
            return it->Name;
        }

        return {};
    }

    bool FromString(Graphics::GpuRenderAPI& result, std::string_view value) noexcept
    {
        auto it = std::find_if(std::begin(GRenderAPINames), std::end(GRenderAPINames), [&](auto v)
        {
            return v.Name == value;
        });

        if (it != std::end(GRenderAPINames))
        {
            result = it->Value;
            return true;
        }

        return false;
    }

    EnumNameValue<Graphics::GpuShaderProfile> GGpuShaderProfileNames[] = {
        { "d3dsm_5_0", Graphics::GpuShaderProfile::D3DSM_5_0 },
        { "d3dsm_5_1", Graphics::GpuShaderProfile::D3DSM_5_1 },
        { "d3dsm_6_0", Graphics::GpuShaderProfile::D3DSM_6_0 },
        { "d3dsm_6_1", Graphics::GpuShaderProfile::D3DSM_6_1 },
        { "d3dsm_6_2", Graphics::GpuShaderProfile::D3DSM_6_2 },
        { "spirv_1_0", Graphics::GpuShaderProfile::SPIRV_1_0 },
        { "spirv_1_1", Graphics::GpuShaderProfile::SPIRV_1_1 },
        { "spirv_1_2", Graphics::GpuShaderProfile::SPIRV_1_2 },
        { "glsl_4_50", Graphics::GpuShaderProfile::GLSL_4_50 },
        { "glsl_4_60", Graphics::GpuShaderProfile::GLSL_4_60 },
        { "essl_2_00", Graphics::GpuShaderProfile::ESSL_2_00 },
        { "essl_3_00", Graphics::GpuShaderProfile::ESSL_3_00 },
        { "essl_3_10", Graphics::GpuShaderProfile::ESSL_3_10 },
        { "essl_3_20", Graphics::GpuShaderProfile::ESSL_3_20 },
        { "essl_3_30", Graphics::GpuShaderProfile::ESSL_3_30 },
    };

    std::string_view ToString(Graphics::GpuShaderProfile value) noexcept
    {
        auto it = std::find_if(std::begin(GGpuShaderProfileNames), std::end(GGpuShaderProfileNames), [&](auto v)
        {
            return v.Value == value;
        });

        if (it != std::end(GGpuShaderProfileNames))
        {
            return it->Name;
        }

        return {};
    }

    bool FromString(Graphics::GpuShaderProfile& result, std::string_view value) noexcept
    {
        auto it = std::find_if(std::begin(GGpuShaderProfileNames), std::end(GGpuShaderProfileNames), [&](auto v)
        {
            return v.Name == value;
        });

        if (it != std::end(GGpuShaderProfileNames))
        {
            result = it->Value;
            return true;
        }

        return false;
    }

    EnumNameValue<Graphics::GpuShaderStage> GGpuShaderStageNames[] = {
        { "ps", Graphics::GpuShaderStage::Pixel },
        { "vs", Graphics::GpuShaderStage::Vertex },
        { "gs", Graphics::GpuShaderStage::Geometry },
        { "hs", Graphics::GpuShaderStage::Hull },
        { "ds", Graphics::GpuShaderStage::Domain },
        { "cs", Graphics::GpuShaderStage::Compute },
    };

    std::string_view ToString(Graphics::GpuShaderStage value) noexcept
    {
        auto it = std::find_if(std::begin(GGpuShaderStageNames), std::end(GGpuShaderStageNames), [&](auto v)
        {
            return v.Value == value;
        });

        if (it != std::end(GGpuShaderStageNames))
        {
            return it->Name;
        }

        return {};
    }

    bool FromString(Graphics::GpuShaderStage& result, std::string_view value) noexcept
    {
        auto it = std::find_if(std::begin(GGpuShaderStageNames), std::end(GGpuShaderStageNames), [&](auto v)
        {
            return v.Name == value;
        });

        if (it != std::end(GGpuShaderStageNames))
        {
            result = it->Value;
            return true;
        }

        return false;
    }

    std::string ShaderCompilerInput::BuildFileName() const noexcept
    {
        std::string result = this->FileName;
        result += '_';
        result += ToString(this->RenderAPI);
        result += '_';
        result += ToString(this->Profile);
        result += '_';
        result += ToString(this->Stage);
        result += ".shader";
        return result;
    }

    uint64_t ShaderCompilerInput::GetHash() const noexcept
    {
        Hash::XXHash64 hash{ 2137 };

        hash.Update(&this->Platform, sizeof(this->Platform));
        hash.Update(&this->RenderAPI, sizeof(this->RenderAPI));
        hash.Update(&this->Profile, sizeof(this->Profile));
        hash.Update(&this->Stage, sizeof(this->Stage));
        hash.Update(&this->EnableAggresiveFlattening, sizeof(this->EnableAggresiveFlattening));
        hash.Update(&this->Enable16BitTypes, sizeof(this->Enable16BitTypes));
        hash.Update(&this->EnableStrictMode, sizeof(this->EnableStrictMode));
        hash.Update(&this->AvoidFlowControlConstructs, sizeof(this->AvoidFlowControlConstructs));
        hash.Update(&this->PreferFlowControlConstructs, sizeof(this->PreferFlowControlConstructs));
        hash.Update(&this->ForceIEEE, sizeof(this->ForceIEEE));
        hash.Update(&this->SuppressWarnings, sizeof(this->SuppressWarnings));
        hash.Update(&this->DisableOptimizations, sizeof(this->DisableOptimizations));
        hash.Update(&this->DisableValidation, sizeof(this->DisableValidation));
        hash.Update(&this->WarningsAsErrors, sizeof(this->WarningsAsErrors));
        hash.Update(&this->EnableDebugInfo, sizeof(this->EnableDebugInfo));
        hash.Update(&this->OptimizationLevel, sizeof(this->OptimizationLevel));
        hash.Update(std::data(this->FileName), std::size(this->FileName));
        hash.Update(std::data(this->EntryName), std::size(this->EntryName));

        return hash.GetValue();
    }

    IShaderCompilerBackend::~IShaderCompilerBackend() noexcept = default;

    ShaderProcessor::ShaderProcessor() noexcept
        : m_Backends{}
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        m_Backends.push_back(std::make_unique<D3DShaderCompilerBackend>());
        m_Backends.push_back(std::make_unique<DXCShaderCompilerBackend>());
#endif
        m_Backends.push_back(std::make_unique<OpenGLShaderCompilerBackend>());
        m_Backends.push_back(std::make_unique<SPIRVShaderCompilerBackend>());
    }

    ShaderProcessor::~ShaderProcessor() noexcept = default;

    bool ShaderProcessor::Process(const AssetProcessorRequest& request, AssetProcessorResponse& response) noexcept
    {
        (void)request;
        (void)response;
        return false;
    }

    bool ShaderProcessor::Process() noexcept
    {
        std::string_view path{};
        std::string_view outputFilename{};

        ShaderCompilerInput input{};
        input.Platform = System::PlatformType::Windows;
        input.RenderAPI = Graphics::GpuRenderAPI::OpenGL;
        input.Profile = Graphics::GpuShaderProfile::GLSL_4_50;

        if (auto option = CommandLine::Get("--input"); option.has_value())
        {
            path = option.value();
        }

        if (auto option = CommandLine::Get("--output"); option.has_value())
        {
            outputFilename = option.value();
        }

        if (auto option = CommandLine::Get("--stage"); option.has_value())
        {
            auto value = option.value();

            if (!FromString(input.Stage, value))
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Invalid stage type: {}\n", value);
            }
        }

        if (auto option = CommandLine::Get("--platform"); option.has_value())
        {
            auto value = option.value();

            if (!FromString(input.Platform, value))
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Invalid platform type: {}\n", value);
            }
        }

        if (auto option = CommandLine::Get("--render"); option.has_value())
        {
            auto value = option.value();

            if (!FromString(input.RenderAPI, value))
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Invalid render api type: {}\n", value);
            }
        }

        if (auto option = CommandLine::Get("--profile"); option.has_value())
        {
            auto value = option.value();

            if (!FromString(input.Profile, value))
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Invalid profile name: {}\n", value);
            }
        }

        input.Definitions["ENABLE_ERROR"] = "1";

        if (!path.empty())
        {
            if (Storage::ReadText(input.Source, std::string{ path }) != Status::Success)
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Cannot read shader file: {}\n", path);
                return false;
            }
        }
        else
        {
            GX_LOG(LogShaderCompilerFrontend, Error, "Shader file not provided\n");
            return false;
        }

        if (outputFilename.empty())
        {
            GX_LOG(LogShaderCompilerFrontend, Error, "Output file name not provided\n");
            return false;
        }

        input.FileName = Storage::GetFilename(path);

        for (auto&& backend : m_Backends)
        {
            if (!backend->IsSupported(input))
            {
                continue;
            }

            ShaderCompilerOutput output{};

            if (!backend->Compile(input, output))
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Cannot compile shader: `{}`\n", path);

                for (auto&& line : output.Log)
                {
                    GX_LOG(LogShaderCompilerFrontend, Info, "`{}`\n", line);
                }

                return false;
            }

            output.FileName = Storage::GetBaseFilename(outputFilename);
            output.FileName += '.';
            output.FileName += ToString(input.Stage);
            output.FileName += ".shader";

            Graphics::ShaderBytecode bytecode{};
            bytecode.Bytecode = output.Bytecode;
            bytecode.Platform = input.Platform;
            bytecode.RenderAPI = input.RenderAPI;
            bytecode.Profile = input.Profile;
            bytecode.Stage = input.Stage;
            bytecode.Flags = input.EnableDebugInfo ? Graphics::ShaderBytecodeFlags::Debug : Graphics::ShaderBytecodeFlags::None;

            auto content_path = Storage::CombinePath(
                Storage::GetProjectContentDirectory(),
                "shaders_compiled/",
                ToString(input.Platform),
                ToString(input.RenderAPI)
            );

            if (Storage::IFileSystem::GetPlatformNative().DirectoryTreeCreate(content_path) != Status::Success)
            {
                GX_LOG(LogShaderCompilerFrontend, Error, "Cannot create directory: `{}`\n", content_path);
                return false;
            }

            std::unique_ptr<Storage::Archive> writer{};

            if (Storage::CreateWriter(writer, Storage::CombinePath(content_path, output.FileName)) == Status::Success)
            {
                *writer << bytecode;
                return true;
            }


            return false;
        }

        GX_LOG(LogShaderCompilerFrontend, Error, "Cannot compile shader: `{}`\n", path);
        return false;
    }

    //bool ShaderProcessor::Serialize(Serialization::Writer::Value& value) noexcept
    //{
    //    (void)value;
    //    return false;
    //}
    //
    //bool ShaderProcessor::Deserialize(Serialization::Reader::Value& value) noexcept
    //{
    //    (void)value;
    //    return false;
    //}
}
