#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuCommon.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuStructuredBuffer : public GpuStructuredBuffer
    {
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuStructuredBuffer>);
}
