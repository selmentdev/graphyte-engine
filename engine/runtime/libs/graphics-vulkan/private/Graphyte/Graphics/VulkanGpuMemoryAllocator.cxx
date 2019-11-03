#include "Graphics.Vulkan.pch.hxx"

#if GRAPHYTE_COMPILER_MSVC
#pragma warning(disable : 4296 4100 4189 4701 4703 4191)
#endif

#if GRAPHYTE_COMPILER_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wcast-align"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wimplicit-fallthrough"
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#pragma clang diagnostic ignored "-Wtautological-unsigned-zero-compare"
#elif GRAPHYTE_COMPILER_GNU
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define VMA_IMPLEMENTATION
#include "VulkanGpuCommon.hxx"

#if GRAPHYTE_COMPILER_CLANG
#pragma clang diagnostic pop
#elif GRAPHYTE_COMPILER_GNU
#pragma GCC diagnostic pop
#endif
