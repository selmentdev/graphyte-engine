#include "OpenGLGpuRenderTarget.hxx"
#include "OpenGLGpuDevice.hxx"
#include "OpenGLGpuTexture.hxx"
#include "OpenGLGpuPixelFormat.hxx"

namespace Graphyte::Graphics
{
    GpuRenderTargetHandle OpenGLGpuDevice::BeginCreateRenderTarget(
        uint32_t width,
        uint32_t height,
        uint32_t surfaces) noexcept
    {
        auto* native = new OpenGLGpuRenderTarget();

        GPU_GL_VALIDATE(glCreateFramebuffers(
            1,
            &native->m_Framebuffer));

        native->m_Colors = surfaces;
        native->m_Width  = width;
        native->m_Height = height;

        return native;
    }

    void OpenGLGpuDevice::EndCreateRenderTarget(
        GpuRenderTargetHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto* native = static_cast<OpenGLGpuRenderTarget*>(handle);
        (void)native;

        [[maybe_unused]] GLenum result = glCheckNamedFramebufferStatus(
            native->m_Framebuffer,
            GL_FRAMEBUFFER);

        GX_ASSERT(result == GL_FRAMEBUFFER_COMPLETE);
        // XXX: This is obviously broken. We can't bind texture with depth/stencil to framebuffer because it requires renderbuffer in opengl...
        //GPU_GL_VALIDATE(glDeleteFramebuffers(1, &native->m_Framebuffer));
    }

    void OpenGLGpuDevice::SetRenderTargetSurface(
        GpuRenderTargetHandle handle,
        int32_t index,
        GpuTexture2DHandle texture,
        uint32_t mip_index) noexcept
    {
        auto* native_render_target = static_cast<OpenGLGpuRenderTarget*>(handle);
        auto* native_texture       = static_cast<OpenGLGpuTexture*>(texture);

        GX_ASSERT(native_render_target != nullptr);
        GX_ASSERT(native_texture != nullptr);

        if (index < 0)
        {
            //
            // Binding depth/stencil texture.
            //
            GPU_GL_VALIDATE(glNamedFramebufferTexture2DEXT(
                native_render_target->m_Framebuffer,
                GL_DEPTH_STENCIL_ATTACHMENT,
                GL_TEXTURE_2D,
                native_texture->m_Resource,
                static_cast<GLint>(mip_index)));
        }
        else
        {
            //
            // Binding color attachment.
            //
            GPU_GL_VALIDATE(glNamedFramebufferTexture2DEXT(
                native_render_target->m_Framebuffer,
                static_cast<GLenum>(GL_COLOR_ATTACHMENT0 + index),
                GL_TEXTURE_2D,
                native_texture->m_Resource,
                static_cast<GLint>(mip_index)));
        }
    }

    void OpenGLGpuDevice::DestroyRenderTarget(
        GpuRenderTargetHandle handle) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto* native = static_cast<OpenGLGpuRenderTarget*>(handle);

        GPU_GL_VALIDATE(glDeleteFramebuffers(
            1,
            &native->m_Framebuffer));

        delete native;
    }
}
