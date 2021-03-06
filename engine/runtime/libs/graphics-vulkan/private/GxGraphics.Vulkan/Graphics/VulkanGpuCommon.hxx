#pragma once
#include <GxGraphics/Graphics.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/String.hxx>

#include <vulkan/vulkan.h>

#if GX_PLATFORM_WINDOWS
#include <vulkan/vulkan_win32.h>
#elif GX_PLATFORM_LINUX
#include <xcb/xcb.h>
#include <vulkan/vulkan_xcb.h>
#include <vulkan/vulkan_wayland.h>
#endif

#if GX_COMPILER_CLANG
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
#elif GX_COMPILER_GNU
#pragma GCC diagnostic push
#elif GX_COMPILER_MSVC
#pragma push_macro("new")
#undef new
#endif

#include <vk_mem_alloc.h>

#if GX_COMPILER_CLANG
#pragma clang diagnostic pop
#elif GX_COMPILER_GNU
#pragma GCC diagnostic pop
#elif GX_COMPILER_MSVC
#pragma pop_macro("new")
#endif

namespace Graphyte::Graphics
{
    GX_DECLARE_LOG_CATEGORY(LogVkRender, Trace, Trace);

    std::string_view VulkanVkResultToString(
        VkResult result) noexcept;

    template <typename T>
    __forceinline T VKGetFunction(
        VkInstance instance,
        const char* name) noexcept
    {
        return reinterpret_cast<T>(reinterpret_cast<void*>(vkGetInstanceProcAddr(
            instance,
            name)));
    }
}

#define GPU_VK_VALIDATE(expression) \
    { \
        VkResult const _gx_vk_result = (expression); \
        GX_ABORT_UNLESS(_gx_vk_result == VK_SUCCESS, "VK operation failure: VK_RESULT[{}, {}]", _gx_vk_result, VulkanVkResultToString(_gx_vk_result)); \
    }
