#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GRAPHYTE_STATIC_BUILD
#define GRAPHICS_GLCORE_API
#else
#if defined(module_graphics_glcore_EXPORTS)
#define GRAPHICS_GLCORE_API GX_LIB_EXPORT
#else
#define GRAPHICS_GLCORE_API GX_LIB_IMPORT
#endif
#endif