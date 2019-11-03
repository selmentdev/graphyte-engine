#include "Graphics.GLCore.pch.hxx"
#include "OpenGLGpuIndexBuffer.hxx"
#include "OpenGLGpuDevice.hxx"
#include <Graphyte/Flags.hxx>

namespace Graphyte::Graphics
{
    GpuIndexBufferHandle OpenGLGpuDevice::CreateIndexBuffer(
        uint32_t stride,
        uint32_t size,
        GpuBufferUsage usage,
        const GpuSubresourceData* subresource
    ) noexcept
    {
        auto native = new OpenGLGpuIndexBuffer();

        GPU_GL_VALIDATE(glCreateBuffers(
            1,
            &native->m_Resource
        ));

        native->m_Size = size;
        native->m_Stride = stride;
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

        //glNamedBufferStorage()
        GPU_GL_VALIDATE(glNamedBufferData(
            native->m_Resource,
            size,
            data,
            usage_flags
        ));

#if ENABLE_GPU_API_DEBUG
        GPU_GL_VALIDATE(glObjectLabel(
            GL_BUFFER,
            native->m_Resource,
            static_cast<GLsizei>(strlen("IndexBuffer")),
            "IndexBuffer"
        ));
#endif

        return native;
    }

    void OpenGLGpuDevice::DestroyIndexBuffer(
        GpuIndexBufferHandle handle
    ) noexcept
    {
        auto native = static_cast<OpenGLGpuIndexBuffer*>(handle);

        GPU_GL_VALIDATE(glDeleteBuffers(
            1,
            &native->m_Resource
        ));

        delete native;
    }

    void* OpenGLGpuDevice::LockIndexBuffer(
        GpuIndexBufferHandle handle,
        uint32_t offset,
        uint32_t size,
        GpuResourceLockMode lock_mode
    ) noexcept
    {
        (void)size;

        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuIndexBuffer*>(handle);

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

    void OpenGLGpuDevice::UnlockIndexBuffer(
        GpuIndexBufferHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuIndexBuffer*>(handle);

        GPU_GL_VALIDATE(glUnmapNamedBuffer(
            native->m_Resource
        ));
    }

    void OpenGLGpuDevice::CopyIndexBuffer(
        GpuIndexBufferHandle source,
        GpuIndexBufferHandle destination
    ) noexcept
    {
        (void)source;
        (void)destination;
    }
}
