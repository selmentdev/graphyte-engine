#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define GRAPHICS_API
#else
#if defined(module_graphics_EXPORTS)
#define GRAPHICS_API GX_MODULE_EXPORT
#else
#define GRAPHICS_API GX_MODULE_IMPORT
#endif
#endif

#define ENABLE_GPU_API_DEBUG 0

namespace Graphyte::Graphics
{
    GRAPHICS_API void Initialize() noexcept;
    GRAPHICS_API void Finalize() noexcept;
}
