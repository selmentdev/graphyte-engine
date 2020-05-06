#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    std::string_view OpenGLGetErrorString(
        GLenum error
    ) noexcept
    {
#define CASE(x) case x: return #x

        switch (error)
        {
        CASE(GL_NO_ERROR);
        CASE(GL_INVALID_ENUM);
        CASE(GL_INVALID_VALUE);
        CASE(GL_INVALID_OPERATION);
        CASE(GL_STACK_OVERFLOW);
        CASE(GL_STACK_UNDERFLOW);
        CASE(GL_OUT_OF_MEMORY);
        CASE(GL_TABLE_TOO_LARGE);
        CASE(GL_INVALID_FRAMEBUFFER_OPERATION);
        default:
            return "<unknown>";
        }

#undef CASE
    }
}
