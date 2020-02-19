#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuShader.hxx"

namespace Graphyte::Graphics
{
    GpuShaderHandle OpenGLGpuDevice::CreateShader(
        GpuShaderStage stage,
        GpuShaderBytecode bytecode,
        [[maybe_unused]] GpuInputLayout inputLayout
    ) noexcept
    {
        GLenum target{};

        switch (stage)
        {
        case GpuShaderStage::Pixel:
            target = GL_FRAGMENT_SHADER;
            break;
        case GpuShaderStage::Vertex:
            target = GL_VERTEX_SHADER;
            break;
        case GpuShaderStage::Geometry:
            target = GL_GEOMETRY_SHADER;
            break;
        case GpuShaderStage::Hull:
            target = GL_TESS_CONTROL_SHADER;
            break;
        case GpuShaderStage::Domain:
            target = GL_TESS_EVALUATION_SHADER;
            break;
        case GpuShaderStage::Compute:
            target = GL_COMPUTE_SHADER;
            break;
        default:
            GX_ASSERT_NOT_IMPLEMENTED();
        }

        constexpr const bool USE_GLSL = false;

        GLuint resource{};

        GPU_GL_VALIDATE(resource = glCreateShader(target));

        if constexpr (USE_GLSL)
        {
            const GLchar* data = reinterpret_cast<const GLchar*>(bytecode.Bytecode);
            GLint data_size = static_cast<GLint>(bytecode.Size);

            GPU_GL_VALIDATE(glShaderSource(
                resource,
                1,
                &data,
                &data_size
            ));

            GPU_GL_VALIDATE(glCompileShader(
                resource
            ));
        }
        else
        {
            GPU_GL_VALIDATE(glShaderBinary(
                1,
                &resource,
                GL_SHADER_BINARY_FORMAT_SPIR_V,
                bytecode.Bytecode,
                static_cast<GLsizei>(bytecode.Size)
            ));

            GPU_GL_VALIDATE(glSpecializeShader(
                resource,
                "main",
                0,
                nullptr,
                nullptr
            ));
        }

        GLint success = 0;
        GPU_GL_VALIDATE(glGetShaderiv(
            resource,
            GL_COMPILE_STATUS,
            &success
        ));

        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            GPU_GL_VALIDATE(glGetShaderiv(
                resource,
                GL_INFO_LOG_LENGTH,
                &maxLength
            ));

            std::vector<char> errorLog(static_cast<size_t>(maxLength));

            GPU_GL_VALIDATE(glGetShaderInfoLog(
                resource,
                maxLength,
                &maxLength,
                std::data(errorLog)
            ));

            std::string log;
            for (size_t i = 0; i < errorLog.size(); i++)
            {
                log += errorLog[i];
            }
            GX_LOG(LogOpenGLRender, Trace, "{}\n", log);

            GPU_GL_VALIDATE(glDeleteShader(
                resource
            ));
        }

        auto result = new OpenGLGpuShader();
        result->m_Resource = resource;
        return result;
    }

    void OpenGLGpuDevice::DestroyShader(
        GpuShaderHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuShader*>(handle);

        GPU_GL_VALIDATE(glDeleteShader(
            native->m_Resource
        ));

        delete native;
    }
}
