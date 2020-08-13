#include "OpenGLGpuDevice.hxx"
#include <GxBase/Unicode.hxx>
#include "OpenGLGpuSampler.hxx"
#include "OpenGLGpuViewport.hxx"
#include "OpenGLGpuVertexBuffer.hxx"
#include "OpenGLGpuIndexBuffer.hxx"
#include "OpenGLGpuPixelFormat.hxx"
#include "OpenGLGpuCommandList.hxx"

namespace Graphyte::Graphics
{
    void APIENTRY OpenGLGpuDevice::DebugMessageCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* context) noexcept
    {
        GX_LOG_TRACE(LogOpenGLRender,
            "{} {} {} {} {} {} {}\n",
            source,
            type,
            id,
            severity,
            length,
            reinterpret_cast<const char*>(message),
            context);
    }

    OpenGLGpuDevice::OpenGLGpuDevice() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS

        WNDCLASSW wc{};
        wc.lpfnWndProc   = DefWindowProcW;
        wc.hInstance     = GetModuleHandleW(nullptr);
        wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
        wc.lpszClassName = L"oglversionchecksample";
        wc.style         = CS_OWNDC;

        if (RegisterClassW(&wc) == 0)
        {
            GX_ABORT("Failed to register window class");
        }

        m_InitialWindow = CreateWindowExW(
            0,
            L"oglversionchecksample",
            L"oglversionchecksample",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            nullptr,
            nullptr,
            wc.hInstance,
            nullptr);

        PIXELFORMATDESCRIPTOR pfd = {
            .nSize           = sizeof(PIXELFORMATDESCRIPTOR),
            .nVersion        = 1,
            .dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType      = PFD_TYPE_RGBA,
            .cColorBits      = 32,
            .cRedBits        = 0,
            .cRedShift       = 0,
            .cGreenBits      = 0,
            .cGreenShift     = 0,
            .cBlueBits       = 0,
            .cBlueShift      = 0,
            .cAlphaBits      = 0,
            .cAlphaShift     = 0,
            .cAccumBits      = 0,
            .cAccumRedBits   = 0,
            .cAccumGreenBits = 0,
            .cAccumBlueBits  = 0,
            .cAccumAlphaBits = 0,
            .cDepthBits      = 24,
            .cStencilBits    = 8,
            .cAuxBuffers     = 0,
            .iLayerType      = PFD_MAIN_PLANE,
            .bReserved       = 0,
            .dwLayerMask     = 0,
            .dwVisibleMask   = 0,
            .dwDamageMask    = 0,
        };

        HDC hdc = GetDC(m_InitialWindow);

        int format = ChoosePixelFormat(hdc, &pfd);

        SetPixelFormat(hdc, format, &pfd);

        m_InitialContext = wglCreateContext(hdc);
        wglMakeCurrent(hdc, m_InitialContext);

        if (gladLoadGL() != 1)
        {
            GX_ABORT("Failed to initialize OpenGL");
        }

        if (gladLoadWGL(hdc) != 1)
        {
            GX_ABORT("Failed to initialize OpenGL WGL");
        }

#else

        auto temp_window = SDL_CreateWindow(
            "SDL GLAD init window",
            0,
            0,
            0,
            0,
            SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

        auto temp_context = SDL_GL_CreateContext(
            temp_window);

        SDL_GL_MakeCurrent(
            temp_window,
            temp_context);

        if (SDL_GL_LoadLibrary(nullptr) != 0)
        {
            GX_ASSERTF(false, "Failed to initialize default OpenGL");
        }

        //GX_VERIFYF(gladLoadGL() == 1, "Failed to initialize OpenGL");

        if (gladLoadGLLoader(SDL_GL_GetProcAddress) != 1)
        {
            GX_ASSERTF(false, "Failed to initialize GLAD");
        }

        {
            auto display = XOpenDisplay(nullptr);

            if (gladLoadGLX(display, 0) != 1)
            {
                GX_ASSERTF(false, "Failed to initialize OpenGL WGL");
            }
        }

#endif

        GX_LOG_TRACE(LogOpenGLRender, "OpenGL Version:  {}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
        GX_LOG_TRACE(LogOpenGLRender, "OpenGL Vendor:   {}\n", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
        GX_LOG_TRACE(LogOpenGLRender, "OpenGL Renderer: {}\n", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

#if GRAPHYTE_PLATFORM_WINDOWS

        wglDeleteContext(m_InitialContext);
        DestroyWindow(m_InitialWindow);

#else

        SDL_GL_MakeCurrent(nullptr, nullptr);
        SDL_GL_DeleteContext(temp_context);
        SDL_DestroyWindow(temp_window);

#endif

#define LOG_GLAD_EXTENSION(extension) \
    GX_LOG_TRACE(LogOpenGLRender, "{}: {}\n", #extension, extension) \
    GX_ASSERTF(extension != 0, "Extension: `{}` is not supported", #extension)

        LOG_GLAD_EXTENSION(GLAD_GL_VERSION_4_5);
        LOG_GLAD_EXTENSION(GLAD_GL_VERSION_4_6);

        LOG_GLAD_EXTENSION(GLAD_GL_ARB_arrays_of_arrays);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_bindless_texture);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_buffer_storage);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_direct_state_access);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_draw_indirect);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_draw_instanced);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_gl_spirv);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_multi_draw_indirect);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_occlusion_query);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_parallel_shader_compile);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_separate_shader_objects);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_shader_subroutine);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_shading_language_include);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_spirv_extensions);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_texture_storage);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_texture_view);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_uniform_buffer_object);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_vertex_attrib_64bit);
        LOG_GLAD_EXTENSION(GLAD_GL_ARB_vertex_attrib_binding);
        LOG_GLAD_EXTENSION(GLAD_GL_KHR_debug);
        LOG_GLAD_EXTENSION(GLAD_GL_NV_command_list);

        m_CommandList = new OpenGLGpuCommandList();
    }

    OpenGLGpuDevice::~OpenGLGpuDevice() noexcept
    {
        delete m_CommandList;
    }

    void OpenGLGpuDevice::Tick(
        float time) noexcept
    {
        (void)time;
    }

    void OpenGLGpuDevice::FlushLogs() noexcept
    {
    }
}
