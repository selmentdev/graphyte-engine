#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define GEOMETRY_API
#else
#if defined(module_geometry_EXPORTS)
#define GEOMETRY_API GX_MODULE_EXPORT
#else
#define GEOMETRY_API GX_MODULE_IMPORT
#endif
#endif
