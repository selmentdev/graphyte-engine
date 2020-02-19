#include "VulkanGpuPixelFormat.hxx"

namespace Graphyte::Graphics
{
    VkFormat VKGetPixelFormat(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::UNKNOWN:                  return VK_FORMAT_UNDEFINED;
        case PixelFormat::R8_UNORM:                 return VK_FORMAT_R8_UNORM;
        case PixelFormat::R8_SNORM:                 return VK_FORMAT_R8_SNORM;
        case PixelFormat::R8_UINT:                  return VK_FORMAT_R8_UINT;
        case PixelFormat::R8_SINT:                  return VK_FORMAT_R8_SINT;
        case PixelFormat::A8_UNORM:                 return VK_FORMAT_R8_UNORM;
        case PixelFormat::R16_FLOAT:                return VK_FORMAT_R16_SFLOAT;
        case PixelFormat::R16_UNORM:                return VK_FORMAT_R16_UNORM;
        case PixelFormat::R16_SNORM:                return VK_FORMAT_R16_SNORM;
        case PixelFormat::R16_UINT:                 return VK_FORMAT_R16_UINT;
        case PixelFormat::R16_SINT:                 return VK_FORMAT_R16_SINT;
        case PixelFormat::R32_FLOAT:                return VK_FORMAT_R32_SFLOAT;
        case PixelFormat::R32_UINT:                 return VK_FORMAT_R32_UINT;
        case PixelFormat::R32_SINT:                 return VK_FORMAT_R32_SINT;
        case PixelFormat::R8G8_UNORM:               return VK_FORMAT_R8G8_UNORM;
        case PixelFormat::R8G8_SNORM:               return VK_FORMAT_R8G8_SNORM;
        case PixelFormat::R8G8_UINT:                return VK_FORMAT_R8G8_UINT;
        case PixelFormat::R8G8_SINT:                return VK_FORMAT_R8G8_SINT;
        case PixelFormat::R16G16_FLOAT:             return VK_FORMAT_R16G16_SFLOAT;
        case PixelFormat::R16G16_UNORM:             return VK_FORMAT_R16G16_UNORM;
        case PixelFormat::R16G16_SNORM:             return VK_FORMAT_R16G16_SNORM;
        case PixelFormat::R16G16_UINT:              return VK_FORMAT_R16G16_UINT;
        case PixelFormat::R16G16_SINT:              return VK_FORMAT_R16G16_SINT;
        case PixelFormat::R32G32_FLOAT:             return VK_FORMAT_R32G32_SFLOAT;
        case PixelFormat::R32G32_UINT:              return VK_FORMAT_R32G32_UINT;
        case PixelFormat::R32G32_SINT:              return VK_FORMAT_R32G32_SINT;
        case PixelFormat::B5G6R5_UNORM:             return VK_FORMAT_B5G6R5_UNORM_PACK16;
        case PixelFormat::R11G11B10_FLOAT:          return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
        case PixelFormat::B8G8R8A8_UNORM:           return VK_FORMAT_B8G8R8A8_UNORM;
        case PixelFormat::B8G8R8A8_UNORM_SRGB:      return VK_FORMAT_B8G8R8A8_SRGB;
        case PixelFormat::B8G8R8X8_UNORM:           return VK_FORMAT_UNDEFINED;
        case PixelFormat::R8G8B8A8_UNORM:           return VK_FORMAT_R8G8B8A8_UNORM;
        case PixelFormat::R8G8B8A8_SNORM:           return VK_FORMAT_R8G8B8A8_SNORM;
        case PixelFormat::R8G8B8A8_UINT:            return VK_FORMAT_R8G8B8A8_UINT;
        case PixelFormat::R8G8B8A8_SINT:            return VK_FORMAT_R8G8B8A8_SINT;
        case PixelFormat::R10G10B10A2_UNORM:        return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
        case PixelFormat::R10G10B10A2_UINT:         return VK_FORMAT_A2B10G10R10_UINT_PACK32;
        case PixelFormat::R16G16B16A16_FLOAT:       return VK_FORMAT_R16G16B16A16_SFLOAT;
        case PixelFormat::R16G16B16A16_UNORM:       return VK_FORMAT_R16G16B16A16_UNORM;
        case PixelFormat::R16G16B16A16_SNORM:       return VK_FORMAT_R16G16B16A16_SNORM;
        case PixelFormat::R16G16B16A16_UINT:        return VK_FORMAT_R16G16B16A16_UINT;
        case PixelFormat::R16G16B16A16_SINT:        return VK_FORMAT_R16G16B16A16_SINT;
        case PixelFormat::R32G32B32A32_FLOAT:       return VK_FORMAT_R32G32B32A32_SFLOAT;
        case PixelFormat::R32G32B32A32_UINT:        return VK_FORMAT_R32G32B32A32_UINT;
        case PixelFormat::R32G32B32A32_SINT:        return VK_FORMAT_R32G32B32A32_SINT;
        case PixelFormat::D16_UNORM:                return VK_FORMAT_D16_UNORM;
        case PixelFormat::D24_UNORM_S8_UINT:        return VK_FORMAT_D24_UNORM_S8_UINT;
        case PixelFormat::D32_FLOAT:                return VK_FORMAT_D32_SFLOAT;
        case PixelFormat::D32_FLOAT_S8X24_UINT:     return VK_FORMAT_D32_SFLOAT_S8_UINT;
        case PixelFormat::BC1_UNORM:                return VK_FORMAT_BC1_RGB_UNORM_BLOCK;
        case PixelFormat::BC2_UNORM:                return VK_FORMAT_BC2_UNORM_BLOCK;
        case PixelFormat::BC3_UNORM:                return VK_FORMAT_BC3_UNORM_BLOCK;
        case PixelFormat::BC4_SNORM:                return VK_FORMAT_BC4_SNORM_BLOCK;
        case PixelFormat::BC4_UNORM:                return VK_FORMAT_BC4_UNORM_BLOCK;
        case PixelFormat::BC5_SNORM:                return VK_FORMAT_BC5_SNORM_BLOCK;
        case PixelFormat::BC5_UNORM:                return VK_FORMAT_BC5_UNORM_BLOCK;
        case PixelFormat::BC6H_SF16:                return VK_FORMAT_BC6H_SFLOAT_BLOCK;
        case PixelFormat::BC6H_UF16:                return VK_FORMAT_BC6H_UFLOAT_BLOCK;
        case PixelFormat::BC7_UNORM:                return VK_FORMAT_BC7_UNORM_BLOCK;
        case PixelFormat::B5G5R5A1_UNORM:           return VK_FORMAT_B5G5R5A1_UNORM_PACK16;
        }

        return VK_FORMAT_UNDEFINED;
    }
}
