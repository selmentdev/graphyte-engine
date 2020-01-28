#include "Graphics.GLCore.pch.hxx"
#include "OpenGLGpuViewport.hxx"
#include "OpenGLGpuPixelFormat.hxx"
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    GpuViewportHandle OpenGLGpuDevice::CreateViewport(
        void* native_handle,
        uint32_t width,
        uint32_t height,
        bool fullscreen,
        PixelFormat color_format,
        PixelFormat depth_format,
        GpuMsaaQuality msaa
    ) noexcept
    {
        (void)width;
        (void)height;
        (void)fullscreen;
        (void)depth_format;
        (void)color_format;

        GX_ASSERT(native_handle != nullptr);

        GLint msaa_samples = 1;
        GLint msaa_buffers = 1;

        switch (msaa)
        {
        case GpuMsaaQuality::Disabled:
            {
                msaa_samples = 1;
                break;
            }
        case GpuMsaaQuality::X2:
            {
                msaa_samples = 2;
                break;
            }
        case GpuMsaaQuality::X4:
            {
                msaa_samples = 4;
                break;
            }
        case GpuMsaaQuality::X8:
            {
                msaa_samples = 8;
                break;
            }
        case GpuMsaaQuality::X16:
            {
                msaa_samples = 16;
                break;
            }
        }

        //
        // Create native viewport object.
        //

        auto native = new OpenGLGpuViewport();

#if GRAPHYTE_PLATFORM_WINDOWS

        native->m_Handle = static_cast<HWND>(native_handle);
        native->m_DeviceContext = GetDC(native->m_Handle);


        //
        // Determine viewport surface params.
        //

        GLint color_bits = 32;
        GLint depth_bits = 24;
        GLint stencil_bits = 8;

        const GLint attributes[]
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,     color_bits,
            WGL_DEPTH_BITS_ARB,     depth_bits,
            WGL_STENCIL_BITS_ARB,   stencil_bits,
            WGL_SAMPLE_BUFFERS_ARB, msaa_buffers,
            WGL_SAMPLES_ARB,        msaa_samples,
            0
        };


        //
        // Choose pixel formats.
        //

        int pixel_format = 0;
        UINT num_formats = 0;

        if (wglChoosePixelFormatARB(
            native->m_DeviceContext,
            attributes,
            nullptr,
            1,
            &pixel_format,
            &num_formats
            ) == 0)
        {
            GX_ASSERTF(false, "Cannot choose pixel format");
        }

        PIXELFORMATDESCRIPTOR pfd{};

        if (DescribePixelFormat(
            native->m_DeviceContext,
            pixel_format,
            sizeof(pfd),
            &pfd
        ) == 0)
        {
            GX_ASSERTF(false, "Cannot describe pixel format");
        }

        if (SetPixelFormat(
            native->m_DeviceContext,
            pixel_format,
            &pfd
        ) == 0)
        {
            GX_ASSERTF(false, "Cannot set pixel format");
        }

        //
        // Create OpenGL context.
        //

        GLint context_attributes[]
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
            WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        //wglMakeCurrent(nullptr, nullptr);
        auto err = GetLastError();

        err = glGetError();

        native->m_ContextHandle = wglCreateContextAttribsARB(
            native->m_DeviceContext,
            nullptr,
            context_attributes
        );

        err = glGetError();

        GX_ASSERT(native->m_ContextHandle != nullptr);

        wglMakeCurrent(
            native->m_DeviceContext,
            native->m_ContextHandle
        );

#elif GRAPHYTE_PLATFORM_LINUX

        native->m_Handle = reinterpret_cast<SDL_Window*>(native_handle);

        if (0 != SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, msaa_buffers))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa_samples))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG))
        {
            GX_ASSERT(false);
        }

        if (0 != SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        {
            GX_ASSERT(false);
        }


        native->m_Context = SDL_GL_CreateContext(
            native->m_Handle
        );

        GX_ASSERTF(native->m_Context != nullptr, "OpenGL context creation failed: `{}`\n", SDL_GetError());

        SDL_GL_MakeCurrent(
            native->m_Handle,
            native->m_Context
        );

        auto err = glGetError();
#endif

        (void)msaa_samples;
        (void)msaa_buffers;
        err = glGetError();
        (void)err;

#if ENABLE_GPU_API_DEBUG
        GPU_GL_VALIDATE(glEnable(
            GL_DEBUG_OUTPUT
        ));

        GPU_GL_VALIDATE(glEnable(
            GL_DEBUG_OUTPUT_SYNCHRONOUS
        ));

        GPU_GL_VALIDATE(glDebugMessageCallback(
            OpenGLGpuDevice::DebugMessageCallback,
            nullptr
        ));

        GPU_GL_VALIDATE(glDebugMessageControl(
            GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER,
            GL_DONT_CARE,
            0,
            nullptr,
            GL_FALSE
        ));

        GPU_GL_VALIDATE(glDebugMessageControl(
            GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_PUSH_GROUP,
            GL_DONT_CARE,
            0,
            nullptr,
            GL_FALSE
        ));

        GPU_GL_VALIDATE(glDebugMessageControl(
            GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_POP_GROUP,
            GL_DONT_CARE,
            0,
            nullptr,
            GL_FALSE
        ));

#ifdef GL_KHR_debug
        GPU_GL_VALIDATE(glDebugMessageControl(
            GL_DEBUG_SOURCE_API,
            GL_DEBUG_TYPE_OTHER,
            GL_DEBUG_SEVERITY_NOTIFICATION,
            0,
            nullptr,
            GL_FALSE
        ));
#endif

#endif

        GPU_GL_VALIDATE(glViewport(
            0,
            0,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height)
        ));

        return native;
    }

    void OpenGLGpuDevice::DestroyViewport(
        GpuViewportHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuViewport*>(handle);

#if GRAPHYTE_PLATFORM_WINDOWS

        wglDeleteContext(
            native->m_ContextHandle
        );

#elif GRAPHYTE_PLATFORM_LINUX

        SDL_GL_DeleteContext(
            native->m_Context
        );

#endif

        delete native;
    }

    void OpenGLGpuDevice::ResizeViewport(
        GpuViewportHandle handle,
        uint32_t width,
        uint32_t height,
        bool fullscreen,
        PixelFormat format
    ) noexcept
    {
        (void)handle;
        (void)width;
        (void)height;
        (void)fullscreen;
        (void)format;

        GPU_GL_VALIDATE(glViewport(
            0,
            0,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height)
        ));
    }

    void OpenGLGpuDevice::BeginDrawViewport(
        [[maybe_unused]] GpuViewportHandle handle
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);
        // Bind default framebuffer

        GPU_GL_VALIDATE(glBindFramebuffer(
            GL_FRAMEBUFFER,
            0
        ));

        GPU_GL_VALIDATE(glClearColor(
            0.0F,
            0.0F,
            0.0F,
            0.0F
        ));

        GPU_GL_VALIDATE(glClearDepthf(
            1.0F
        ));

        GPU_GL_VALIDATE(glClear(
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
        ));
    }

    void OpenGLGpuDevice::EndDrawViewport(
        GpuViewportHandle handle,
        bool present,
        int interval
    ) noexcept
    {
        GX_ASSERT(handle != nullptr);

        auto native = static_cast<OpenGLGpuViewport*>(handle);

        if (present)
        {
#if GRAPHYTE_PLATFORM_WINDOWS

            GPU_GL_VALIDATE(wglSwapIntervalEXT(
                interval
            ));

            GPU_GL_VALIDATE(SwapBuffers(
                native->m_DeviceContext
            ));

#else

            SDL_GL_SetSwapInterval(
                interval
            );

            SDL_GL_SwapWindow(
                native->m_Handle
            );

#endif
        }
    }
}
