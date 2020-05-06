#pragma once
#include <GxGraphics/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuSampler final : public GpuSampler
    {
    public:
        GLuint m_Resource;
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuSampler>);
}
