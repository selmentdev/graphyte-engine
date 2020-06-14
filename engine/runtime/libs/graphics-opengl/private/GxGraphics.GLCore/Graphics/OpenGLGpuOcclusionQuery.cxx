#include "OpenGLGpuOcclusionQuery.hxx"
#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuCommandList.hxx"

namespace Graphyte::Graphics
{
    void OpenGLGpuCommandList::BeginOcclusionQuery(
        GpuOcclusionQueryHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);
        auto native = static_cast<OpenGLGpuOcclusionQuery*>(handle);

        GX_ASSERT(native->m_Resource != 0);

        GPU_GL_VALIDATE(glBeginQuery(
            GL_SAMPLES_PASSED,
            native->m_Resource));
    }

    void OpenGLGpuCommandList::EndOcclusionQuery(
        GpuOcclusionQueryHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuOcclusionQuery*>(handle);

        GX_ASSERT(native->m_Resource != 0);
        (void)native;

        GPU_GL_VALIDATE(glEndQuery(
            GL_SAMPLES_PASSED));
    }

    bool OpenGLGpuCommandList::GetOcclusionQueryResult(
        GpuOcclusionQueryHandle handle,
        uint64_t& result,
        bool wait) noexcept
    {
        (void)wait;

        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuOcclusionQuery*>(handle);

        GX_ASSERT(native->m_Resource != 0);

        GLuint64 query_result{};

        GPU_GL_VALIDATE(glGetQueryObjectui64v(
            native->m_Resource,
            GL_QUERY_RESULT,
            &query_result));

        result = static_cast<uint64_t>(query_result);

        return true;
    }
}

namespace Graphyte::Graphics
{
    GpuOcclusionQueryHandle OpenGLGpuDevice::CreateOcclusionQuery() noexcept
    {
        auto native = new OpenGLGpuOcclusionQuery();

        GPU_GL_VALIDATE(glCreateQueries(
            GL_SAMPLES_PASSED,
            1,
            &native->m_Resource));

        return native;
    }

    void OpenGLGpuDevice::DestroyOcclusionQuery(
        GpuOcclusionQueryHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuOcclusionQuery*>(handle);

        GX_ASSERT(native->m_Resource != 0);

        GPU_GL_VALIDATE(glDeleteQueries(
            1,
            &native->m_Resource));

        delete native;
    }
}
