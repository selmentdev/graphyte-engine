#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuUniformBuffer.hxx"
#include <GxBase/Bitwise.hxx>
#include <GxBase/Flags.hxx>

namespace Graphyte::Graphics
{
    GpuUniformBufferHandle OpenGLGpuDevice::CreateUniformBuffer(
        size_t size,
        GpuBufferUsage usage,
        const GpuSubresourceData* subresource
    ) noexcept
    {
        auto native = new OpenGLGpuUniformBuffer();

        GPU_GL_VALIDATE(glCreateBuffers(
            1,
            &native->m_Resource
        ));

        native->m_Size = static_cast<uint32_t>(size);
        native->m_Usage = usage;

        const void* data = nullptr;

        if (subresource != nullptr)
        {
            GX_ASSERT(size == subresource->Pitch);
            data = subresource->Memory;
        }

        GLenum usage_flags = Flags::Any(usage, GpuBufferUsage::AnyDynamic)
            ? GL_DYNAMIC_DRAW
            : GL_STATIC_DRAW;

        GPU_GL_VALIDATE(glNamedBufferData(
            native->m_Resource,
            static_cast<GLsizeiptr>(size),
            data,
            usage_flags
        ));

#if ENABLE_GPU_API_DEBUG
        GPU_GL_VALIDATE(glObjectLabel(
            GL_BUFFER,
            native->m_Resource,
            static_cast<GLsizei>(strlen("UniformBuffer")),
            "UniformBuffer"
        ));
#endif

        return native;
    }

    void OpenGLGpuDevice::DestroyUniformBuffer(
        GpuUniformBufferHandle handle
    ) noexcept
    {
        auto native = static_cast<OpenGLGpuUniformBuffer*>(handle);

        GPU_GL_VALIDATE(glDeleteBuffers(
            1,
            &native->m_Resource
        ));

        delete native;
    }

    void* OpenGLGpuDevice::LockUniformBuffer(
        GpuUniformBufferHandle handle,
        uint32_t offset,
        uint32_t size,
        GpuResourceLockMode lock_mode
    ) noexcept
    {
        (void)size;

        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuUniformBuffer*>(handle);

        GLenum native_lock_mode = GL_NONE;

        switch (lock_mode)
        {
        case GpuResourceLockMode::ReadWrite:
            {
                native_lock_mode = GL_READ_WRITE;
                break;
            }
        case GpuResourceLockMode::ReadOnly:
            {
                native_lock_mode = GL_READ_ONLY;
                break;
            }
        case GpuResourceLockMode::WriteOnly:
        case GpuResourceLockMode::WriteOnlyUnsynchronized:
        case GpuResourceLockMode::WriteOnlyPersistent:
            {
                native_lock_mode = GL_WRITE_ONLY;
                break;
            }
        }

        void* result = glMapNamedBuffer(
            native->m_Resource,
            native_lock_mode
        );

        GX_ASSERT(result != nullptr);
        GX_ASSERT(glGetError() == GL_NO_ERROR);

        return result != nullptr
            ? reinterpret_cast<char*>(result) + offset
            : nullptr;
    }

    void OpenGLGpuDevice::UnlockUniformBuffer(
        GpuUniformBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuUniformBuffer*>(handle);

        GPU_GL_VALIDATE(glUnmapNamedBuffer(
            native->m_Resource
        ));
    }
    
    void OpenGLGpuDevice::CopyUniformBuffer(
        GpuUniformBufferHandle source,
        GpuUniformBufferHandle destination
    ) noexcept
    {
        (void)source;
        (void)destination;
    }
}
