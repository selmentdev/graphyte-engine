#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define GRAPHICS_D3D11_API
#else
#if defined(module_graphics_d3d11_EXPORTS)
#define GRAPHICS_D3D11_API GX_LIB_EXPORT
#else
#define GRAPHICS_D3D11_API GX_LIB_IMPORT
#endif
#endif
