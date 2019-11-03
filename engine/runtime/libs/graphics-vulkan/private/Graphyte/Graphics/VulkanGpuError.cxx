#include "Graphics.Vulkan.pch.hxx"
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    std::string_view VulkanVkResultToString(
        VkResult result
    ) noexcept
    {
#define CASE(x) case x: return #x
        switch (result)
        {
        CASE(VK_SUCCESS);
        CASE(VK_NOT_READY);
        CASE(VK_TIMEOUT);
        CASE(VK_EVENT_SET);
        CASE(VK_EVENT_RESET);
        CASE(VK_INCOMPLETE);
        CASE(VK_ERROR_OUT_OF_HOST_MEMORY);
        CASE(VK_ERROR_OUT_OF_DEVICE_MEMORY);
        CASE(VK_ERROR_INITIALIZATION_FAILED);
        CASE(VK_ERROR_DEVICE_LOST);
        CASE(VK_ERROR_MEMORY_MAP_FAILED);
        CASE(VK_ERROR_LAYER_NOT_PRESENT);
        CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
        CASE(VK_ERROR_FEATURE_NOT_PRESENT);
        CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
        CASE(VK_ERROR_TOO_MANY_OBJECTS);
        CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
        CASE(VK_ERROR_FRAGMENTED_POOL);
        CASE(VK_ERROR_OUT_OF_POOL_MEMORY);
        CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE);
        CASE(VK_ERROR_SURFACE_LOST_KHR);
        CASE(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
        CASE(VK_SUBOPTIMAL_KHR);
        CASE(VK_ERROR_OUT_OF_DATE_KHR);
        CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
        CASE(VK_ERROR_VALIDATION_FAILED_EXT);
        CASE(VK_ERROR_INVALID_SHADER_NV);
        CASE(VK_ERROR_FRAGMENTATION_EXT);
        CASE(VK_ERROR_NOT_PERMITTED_EXT);
        default:
            return "<unknown>";
        }
#undef CASE
    }
}
