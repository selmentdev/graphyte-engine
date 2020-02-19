#include "OpenGLGpuResourceSet.hxx"
#include "OpenGLGpuCommandList.hxx"
#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuUniformBuffer.hxx"
#include "OpenGLGpuSampler.hxx"
#include "OpenGLGpuTexture.hxx"

#define RENDERDOC_FIX 0

namespace Graphyte::Graphics
{
    void OpenGLGpuCommandList::BindResourceSet(
        GpuResourceSetHandle handle
    ) noexcept
    {
        auto native = static_cast<OpenGLGpuResourceSet*>(handle);

#if RENDERDOC_FIX

        for (size_t i = 0; i < std::size(native->m_UniformBuffers); ++i)
        {
            GPU_GL_VALIDATE(glBindBufferBase(
                GL_UNIFORM_BUFFER,
                static_cast<GLuint>(i),
                native->m_UniformBuffers[i]
            ));
        }

        for (size_t i = 0; i < std::size(native->m_Textures); ++i)
        {
            GPU_GL_VALIDATE(glBindTextureUnit(
                static_cast<GLuint>(i),
                native->m_Textures[i]
            ));
        }

        for (size_t i = 0; i < std::size(native->m_Textures); ++i)
        {
            GPU_GL_VALIDATE(glBindSampler(
                static_cast<GLuint>(i),
                native->m_Samplers[i]
            ));

            GPU_GL_VALIDATE(glBindTextureUnit(
                static_cast<GLuint>(i),
                native->m_Textures[i]
            ));
        }

#else
        GPU_GL_VALIDATE(glBindBuffersBase(
            GL_UNIFORM_BUFFER,
            0,
            static_cast<GLsizei>(std::size(native->m_UniformBuffers)),
            std::data(native->m_UniformBuffers)
        ));

        GPU_GL_VALIDATE(glBindTextures(
            0,
            static_cast<GLsizei>(std::size(native->m_Textures)),
            std::data(native->m_Textures)
        ));

        GPU_GL_VALIDATE(glBindSamplers(
            0,
            static_cast<GLsizei>(std::size(native->m_Samplers)),
            std::data(native->m_Samplers)
        ));
#endif


    }
}

namespace Graphyte::Graphics
{
    GpuResourceSetHandle OpenGLGpuDevice::CreateResourceSet(
        const GpuResourceSetDesc& desc
    ) noexcept
    {
        auto native = new OpenGLGpuResourceSet();

        for (auto const& binding : desc.m_Bindings)
        {
            if (binding.Key.ResourceType == GpuResourceType::UniformBuffer)
            {
                auto native_uniform_buffer = static_cast<OpenGLGpuUniformBuffer*>(binding.Resource.UniformBuffer);

                native->m_UniformBuffers[binding.Key.ShaderRegister] = native_uniform_buffer->m_Resource;
            }
            else if (binding.Key.ResourceType == GpuResourceType::Texture)
            {
                auto native_texture = static_cast<OpenGLGpuTexture*>(binding.Resource.Texture);

                native->m_Textures[binding.Key.ShaderRegister] = native_texture->m_Resource;
            }
            else if (binding.Key.ResourceType == GpuResourceType::Sampler)
            {
                auto native_sampler = static_cast<OpenGLGpuSampler*>(binding.Resource.Sampler);

                native->m_Samplers[binding.Key.ShaderRegister] = native_sampler->m_Resource;
            }
        }


        return native;
    }

    void OpenGLGpuDevice::DestroyResourceSet(
        GpuResourceSetHandle handle
    ) noexcept
    {
        auto native = static_cast<OpenGLGpuResourceSet*>(handle);
        delete native;
    }

    void OpenGLGpuDevice::UpdateResourceSet(
        GpuResourceSetHandle handle,
        const GpuResourceSetDesc& desc
    ) noexcept
    {
        (void)handle;
        (void)desc;
    }
}
