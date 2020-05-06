#pragma once
#include <GxGraphics/Graphics/PixelFormat.hxx>
#include "VulkanGpuCommon.hxx"

namespace Graphyte::Graphics
{
    VkFormat VKGetPixelFormat(
        PixelFormat format
    ) noexcept;
}
