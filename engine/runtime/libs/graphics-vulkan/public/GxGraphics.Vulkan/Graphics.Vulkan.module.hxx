#pragma once
#include <Graphyte/Platform/Impl/Detect.hxx>

#if GX_STATIC_BUILD
#define GRAPHICS_VULKAN_API
#else
#if defined(module_graphics_vulkan_EXPORTS)
#define GRAPHICS_VULKAN_API GX_LIB_EXPORT
#else
#define GRAPHICS_VULKAN_API GX_LIB_IMPORT
#endif
#endif
