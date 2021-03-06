#include "SPIRVShaderCompilerBackend.hxx"
#include <GxAssetsBase/AssetsPipeline/PlatformToolchain.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxGraphics/Graphics/Gpu/GpuDefinitions.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/System/Process.hxx>
#include <GxBase/System.hxx>

namespace Graphyte::AssetsPipeline
{
    SPIRVShaderCompilerBackend::SPIRVShaderCompilerBackend() noexcept
        : m_CompilerPath{}
        , m_IsValid{}
    {
        m_CompilerPath = Storage::CombinePath(
            PlatformToolchain::PlatformToolchain::GetVulkanSdkBinary(),
            "glslc");
        m_CompilerPath += System::GetExecutableExtension();

        m_IsValid = Storage::IFileSystem::GetPlatformNative().Exists(m_CompilerPath) == Status::Success;
    }

    SPIRVShaderCompilerBackend::~SPIRVShaderCompilerBackend() noexcept
    {
    }

    std::string_view GetShaderStage(Graphics::GpuShaderStage stage) noexcept
    {
        switch (stage)
        {
            case Graphics::GpuShaderStage::Pixel:
                return "frag";
            case Graphics::GpuShaderStage::Vertex:
                return "vert";
            case Graphics::GpuShaderStage::Geometry:
                return "geom";
            case Graphics::GpuShaderStage::Hull:
                return "tesc";
            case Graphics::GpuShaderStage::Domain:
                return "tese";
            case Graphics::GpuShaderStage::Compute:
                return "comp";
            default:
                break;
        }

        return {};
    }

    bool SPIRVShaderCompilerBackend::IsSupported(ShaderCompilerInput& input) const noexcept
    {
        switch (input.RenderAPI)
        {
            case Graphics::GpuRenderAPI::OpenGL:
            case Graphics::GpuRenderAPI::Vulkan:
                break;
            default:
                return false;
        }

        switch (input.Profile)
        {
            case Graphics::GpuShaderProfile::SPIRV_1_0:
            case Graphics::GpuShaderProfile::SPIRV_1_1:
            case Graphics::GpuShaderProfile::SPIRV_1_2:
                break;
            default:
                return false;
        }

        return m_IsValid;
    }

    bool SPIRVShaderCompilerBackend::Compile(ShaderCompilerInput& input, ShaderCompilerOutput& output) const noexcept
    {
        using namespace std::literals;

        std::string std_output{};
        std::string std_error{};
        int32_t exit_code;

        std::string temp_directory = Storage::GetProjectIntermediateDirectory();
        Storage::AppendPath(temp_directory, "shader-temp/");

        if (Storage::IFileSystem::GetPlatformNative().DirectoryTreeCreate(temp_directory) != Status::Success)
        {
            GX_LOG_ERROR(LogShaderCompilerFrontend, "Cannot create directory: `{}`\n", temp_directory);
            return false;
        }

        auto source_temp = fmt::format(
            "{}{:x}.tmp.shader.input",
            temp_directory,
            input.GetHash());

        auto target_temp = fmt::format(
            "{}{:x}.tmp.shader.output",
            temp_directory,
            input.GetHash());

        if (Storage::WriteText(input.Source, source_temp) != Status::Success)
        {
            GX_LOG_ERROR(LogShaderCompilerFrontend, "Cannot write source file: `{}`\n", source_temp);
            return false;
        }


        std::string commandline = fmt::format(
            " --target-env=vulkan"
            " -fshader-stage={0}"
            " -I {1}"
            " -c {2}"
            " -o {3}",
            GetShaderStage(input.Stage),
            Storage::CombinePath(Storage::GetProjectContentDirectory(), "shaders"),
            source_temp,
            target_temp);
        //commandline += " --target-env=vulkan";
        //commandline += " --std=450core";
        //commandline += " -fshader-stage="s + GetShaderStage(input.Stage);
        //commandline += " -I "s + Storage::GetProjectContentDirectory() + "shaders/"s;
        //commandline += " -c "s + source_temp;
        //commandline += " -o "s + target_temp;

        auto called = System::Process::Execute(
            m_CompilerPath.c_str(),
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

            GX_LOG_ERROR(LogShaderCompilerFrontend, "Exit code: {}\n", exit_code);

            output.Success = success;

            if (success)
            {
                if (Storage::ReadBinary(output.Bytecode, target_temp) == Status::Success)
                {
                    for (auto&& line : Split(std_output, '\n'))
                    {
                        GX_LOG_ERROR(LogShaderCompilerFrontend, "{}\n", line);
                    }

                    return true;
                }
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
