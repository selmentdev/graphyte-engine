#pragma once
#include <GxGraphics/Graphics.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/String.hxx>

#include <glad/glad.h>

#if GRAPHYTE_PLATFORM_WINDOWS
#include <glad/glad_wgl.h>
#elif GRAPHYTE_PLATFORM_LINUX
#include <glad/glad_glx.h>
#include <SDL2/SDL.h>

// FUCK X11
#undef None
#undef Success
#undef Always
#undef Complex
#undef True
#undef False
#undef Status
#else
#error "Unsupported platform"
#endif

namespace Graphyte::Graphics
{
    GX_DECLARE_LOG_CATEGORY(LogOpenGLRender, Trace, Trace);

    std::string_view OpenGLGetErrorString(
        GLenum error
    ) noexcept;
}

#define GPU_GL_VALIDATE(expression) \
    { \
        (expression); \
        GLenum _gx_gl_result = glGetError(); \
        GX_ABORT_UNLESS(_gx_gl_result == GL_NO_ERROR, "Last GLCore error code: {} ({})", _gx_gl_result, OpenGLGetErrorString(_gx_gl_result)); \
    }
