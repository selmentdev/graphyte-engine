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
        m_CompilerPath = Storage::Path::Combine(
            PlatformToolchain::PlatformToolchain::GetVulkanSdkBinary(),
            "glslc"
        );
        m_CompilerPath += System::GetExecutableExtension();

        m_IsValid = Storage::IFileSystem::GetPlatformNative().Exists(m_CompilerPath) == Status::Success;
    }

    SPIRVShaderCompilerBackend::~SPIRVShaderCompilerBackend() noexcept
    {
    }

    const char* GetShaderStage(Graphics::GpuShaderStage stage) noexcept
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

        return nullptr;
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

        std::string temp_directory = Storage::FileManager::GetProjectIntermediateDirectory();
        Storage::Path::Append(temp_directory, "shader-temp/");

        if (Storage::IFileSystem::GetPlatformNative().DirectoryTreeCreate(temp_directory) != Status::Success)
        {
            GX_LOG(LogShaderCompilerFrontend, Error, "Cannot create directory: `{}`\n", temp_directory);
            return false;
        }

        auto source_temp = fmt::format(
            "{}{:x}.tmp.shader.input",
            temp_directory,
            input.GetHash()
        );

        auto target_temp = fmt::format(
            "{}{:x}.tmp.shader.output",
            temp_directory,
            input.GetHash()
        );

        if (Storage::FileManager::WriteText(input.Source, source_temp) != Status::Success)
        {
            GX_LOG(LogShaderCompilerFrontend, Error, "Cannot write source file: `{}`\n", source_temp);
            return false;
        }


        std::string commandline{};
        commandline += " --target-env=vulkan";
        //commandline += " --std=450core";
        commandline += " -fshader-stage="s + GetShaderStage(input.Stage);
        commandline += " -I "s + Storage::FileManager::GetProjectContentDirectory() + "shaders/"s;
        commandline += " -c "s + source_temp;
        commandline += " -o "s + target_temp;

        auto called = System::Process::Execute(
            m_CompilerPath.c_str(),
            commandline.c_str(),
            nullptr,
            &std_output,
            &std_error
        );

        if (bool success = called.StatusCode == Status::Success and called.ExitCode == 0; success)
        {
            for (auto&& line : Split(std_error, '\n'))
            {
                output.Log.emplace_back(line);
            }

            GX_LOG(LogShaderCompilerFrontend, Error, "Exit code: {}\n", exit_code);

            output.Success = success;

            if (success)
            {
                if (Storage::FileManager::ReadBinary(output.Bytecode, target_temp) == Status::Success)
                {
                    for (auto&& line : Split(std_output, '\n'))
                    {
                        GX_LOG(LogShaderCompilerFrontend, Error, "{}\n", line);
                    }

                    return true;
                }
            }
            else
            {
                return false;
            }
        }

        GX_LOG(LogShaderCompilerFrontend, Error, "Vulkan compiler not found!\n");
        return false;
    }
}
