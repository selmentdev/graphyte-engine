#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuVertexBuffer : public GpuVertexBuffer
    {
    public:
        GLuint m_Resource;
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuVertexBuffer>);
}
