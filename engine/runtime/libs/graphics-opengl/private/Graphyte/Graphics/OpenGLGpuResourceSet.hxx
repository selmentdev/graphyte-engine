#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuResourceSet : public GpuResourceSet
    {
    public:
        std::array<GLuint, GpuLimits::UniformBuffersCount> m_UniformBuffers;
        std::array<GLuint, GpuLimits::TextureUnitsCount> m_Textures;
        std::array<GLuint, GpuLimits::TextureUnitsCount> m_Samplers;
    };
}
