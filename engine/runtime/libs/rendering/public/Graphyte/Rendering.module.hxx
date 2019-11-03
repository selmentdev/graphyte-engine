#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GRAPHYTE_STATIC_BUILD
#define RENDERING_API
#else
#if defined(module_rendering_EXPORTS)
#define RENDERING_API       GX_LIB_EXPORT
#else
#define RENDERING_API       GX_LIB_IMPORT
#endif
#endif
