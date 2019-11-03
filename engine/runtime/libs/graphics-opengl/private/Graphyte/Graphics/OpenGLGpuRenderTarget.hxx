#pragma once
#include "OpenGLGpuCommon.hxx"
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>

namespace Graphyte::Graphics
{
    class OpenGLGpuRenderTarget final : public GpuRenderTarget
    {
    public:
        static const constexpr size_t MAX_COLOR_ATTACHMENTS = 8;

    public:
        GLuint m_Framebuffer;

    public:
        uint32_t m_Colors;
        uint32_t m_Width;
        uint32_t m_Height;
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuRenderTarget>);
}
