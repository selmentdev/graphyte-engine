#pragma once
#include <GxBase/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define ASSETS_MESH_API
#else
#if defined(assets_mesh_EXPORTS)
#define ASSETS_MESH_API GX_LIB_EXPORT
#else
#define ASSETS_MESH_API GX_LIB_IMPORT
#endif
#endif
