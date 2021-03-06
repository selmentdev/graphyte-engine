#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define RENDERING_API
#else
#if defined(module_rendering_EXPORTS)
#define RENDERING_API GX_MODULE_EXPORT
#else
#define RENDERING_API GX_MODULE_IMPORT
#endif
#endif
