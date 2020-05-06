#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuTexture : public GpuTexture
    {
    public:
        GLuint m_Resource;
        GLenum m_Target;
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuTexture>);
}
