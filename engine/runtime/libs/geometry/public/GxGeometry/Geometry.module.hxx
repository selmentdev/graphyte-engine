#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GRAPHYTE_STATIC_BUILD
#define GEOMETRY_API
#else
#if defined(module_geometry_EXPORTS)
#define GEOMETRY_API    GX_LIB_EXPORT
#else
#define GEOMETRY_API    GX_LIB_IMPORT
#endif
#endif
