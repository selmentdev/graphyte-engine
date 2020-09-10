#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define GRAPHICS_D3D12_API
#else
#if defined(module_graphics_d3d12_EXPORTS)
#define GRAPHICS_D3D12_API GX_MODULE_EXPORT
#else
#define GRAPHICS_D3D12_API GX_MODULE_IMPORT
#endif
#endif
