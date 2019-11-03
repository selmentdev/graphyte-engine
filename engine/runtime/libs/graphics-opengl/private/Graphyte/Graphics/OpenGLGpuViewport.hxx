#pragma once
#include <Graphyte/Graphics/Gpu/GpuResources.hxx>
#include "OpenGLGpuCommon.hxx"
#include "OpenGLGpuDevice.hxx"

namespace Graphyte::Graphics
{
    class OpenGLGpuViewport : public GpuViewport
    {
    public:
#if GRAPHYTE_PLATFORM_WINDOWS

        HWND m_Handle;
        HGLRC m_ContextHandle;
        HDC m_DeviceContext;

#elif GRAPHYTE_PLATFORM_LINUX

        SDL_Window* m_Handle;
        SDL_GLContext m_Context;

#endif
    };
    static_assert(!std::is_polymorphic_v<OpenGLGpuViewport>);
}
