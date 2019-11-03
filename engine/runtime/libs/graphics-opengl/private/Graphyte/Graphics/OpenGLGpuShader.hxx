#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuShader final : public GpuShader
    {
    public:
        GLuint m_Resource;
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuShader>);
}
