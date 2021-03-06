#include "OpenGLShaderCompilerBackend.hxx"
#include <GxAssetsBase/AssetsPipeline/PlatformToolchain.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDefinitions.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/System.hxx>
#include <GxBase/System/Process.hxx>

namespace Graphyte::AssetsPipeline
{
    OpenGLShaderCompilerBackend::OpenGLShaderCompilerBackend() noexcept
        : m_Glslc{}
        , m_IsValid{}
    {
        m_Glslc = Storage::CombinePath(
            PlatformToolchain::PlatformToolchain::GetVulkanSdkBinary(),
            "glslc");

        m_Glslc += System::GetExecutableExtension();

        m_IsValid = Storage::IFileSystem::GetPlatformNative().Exists(m_Glslc) == Status::Success;
    }

    OpenGLShaderCompilerBackend::~OpenGLShaderCompilerBackend() noexcept
    {
    }

    bool OpenGLShaderCompilerBackend::IsSupported(ShaderCompilerInput& input) const noexcept
    {
        if (input.RenderAPI == Graphics::GpuRenderAPI::OpenGL)
        {
            switch (input.Profile)
            {
                case Graphics::GpuShaderProfile::ESSL_2_00:
                case Graphics::GpuShaderProfile::ESSL_3_00:
                case Graphics::GpuShaderProfile::ESSL_3_10:
                case Graphics::GpuShaderProfile::ESSL_3_20:
                case Graphics::GpuShaderProfile::ESSL_3_30:
                case Graphics::GpuShaderProfile::GLSL_4_50:
                case Graphics::GpuShaderProfile::GLSL_4_60:
                    break;
                default:
                    return false;
                    ;
            }
        }

        return m_IsValid;
    }

#if false
    namespace
    {
        std::string_view GetShaderStage(Graphics::Gpu::GpuShaderStage stage) noexcept
        {
            switch (stage)
            {
            case Graphics::Gpu::GpuShaderStage::Pixel:
                return "frag";
            case Graphics::Gpu::GpuShaderStage::Vertex:
                return "vert";
            case Graphics::Gpu::GpuShaderStage::Geometry:
                return "geom";
            case Graphics::Gpu::GpuShaderStage::Hull:
                return "tesc";
            case Graphics::Gpu::GpuShaderStage::Domain:
                return "tese";
            case Graphics::Gpu::GpuShaderStage::Compute:
                return "comp";
            default:
                break;
            }

            return nullptr;
        }
    }
#endif

    bool OpenGLShaderCompilerBackend::Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept
    {
        using namespace std::literals;

        std::string std_output{};
        std::string std_error{};

        auto temp_directory = Storage::GetProjectIntermediateDirectory() + "shader-temp/";
        if (Storage::IFileSystem::GetPlatformNative().DirectoryTreeCreate(temp_directory) != Status::Success)
        {
            GX_LOG_ERROR(LogShaderCompilerFrontend, "Cannot create directory: `{}`\n", temp_directory);
            return false;
        }

        auto source_temp = fmt::format("{}{:x}.tmp.shader",
            temp_directory,
            input.GetHash());

        if (Storage::WriteText(input.Source, source_temp) != Status::Success)
        {
            GX_LOG_ERROR(LogShaderCompilerFrontend, "Cannot write source file: `{}`\n", source_temp);
            return false;
        }


        std::string commandline = fmt::format(
            " --target-env=opengl"
            " -I {0}"
            " -c {1}"
            " -E",
            Storage::CombinePath(Storage::GetProjectContentDirectory(), "shaders"),
            source_temp);
        //commandline += " --target-env=opengl";
        //commandline += " --std=450core";
        //commandline += " --fshader-stage="s + GetShaderStage(input.Stage);
        //commandline += " -I "s + Storage::GetProjectContentDirectory() + "shaders/"s;
        //commandline += " -o "s + target_temp;
        //commandline += " -c "s + source_temp;
        //commandline += " -E";

        auto called = System::Process::Execute(
            m_Glslc.c_str(),
            commandline.c_str(),
            nullptr,
            &std_output,
            &std_error);

        if (bool success = called.StatusCode == Status::Success && called.ExitCode == 0; success)
        {
            for (auto&& line : Split(std_error, '\n'))
            {
                output.Log.emplace_back(line);
            }

            GX_LOG_ERROR(LogShaderCompilerFrontend, "Exit code: {}\n", called.ExitCode);
            output.Success = success;

            if (success)
            {
                output.Bytecode.assign(
                    reinterpret_cast<const std::byte*>(std::data(std_output)),
                    reinterpret_cast<const std::byte*>(std::data(std_output)) + std::size(std_output));

                for (auto&& line : Split(std_output, '\n'))
                {
                    GX_LOG_ERROR(LogShaderCompilerFrontend, "{}\n", line);
                }

                return true;
            }
            else
            {
                return false;
            }
        }

        GX_LOG_ERROR(LogShaderCompilerFrontend, "Vulkan compiler not found!\n");
        return false;
    }
}
