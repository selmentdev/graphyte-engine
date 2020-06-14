#include <GxGraphics/Graphics/PixelFormat.hxx>

#include <dxgiformat.h>

namespace Graphyte::Graphics
{
    PixelFormat D3D11GpuGetPixelFormat(
        DXGI_FORMAT format) noexcept
    {
        switch (format)
        {
            case DXGI_FORMAT_UNKNOWN:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT_R8_UNORM:
                return PixelFormat::R8_UNORM;
            case DXGI_FORMAT_R8_SNORM:
                return PixelFormat::R8_SNORM;
            case DXGI_FORMAT_R8_UINT:
                return PixelFormat::R8_UINT;
            case DXGI_FORMAT_R8_SINT:
                return PixelFormat::R8_SINT;
            case DXGI_FORMAT_A8_UNORM:
                return PixelFormat::A8_UNORM;
            case DXGI_FORMAT_R16_FLOAT:
                return PixelFormat::R16_FLOAT;
            case DXGI_FORMAT_R16_UNORM:
                return PixelFormat::R16_UNORM;
            case DXGI_FORMAT_R16_SNORM:
                return PixelFormat::R16_SNORM;
            case DXGI_FORMAT_R16_UINT:
                return PixelFormat::R16_UINT;
            case DXGI_FORMAT_R16_SINT:
                return PixelFormat::R16_SINT;
            case DXGI_FORMAT_R32_FLOAT:
                return PixelFormat::R32_FLOAT;
            case DXGI_FORMAT_R32_UINT:
                return PixelFormat::R32_UINT;
            case DXGI_FORMAT_R32_SINT:
                return PixelFormat::R32_SINT;
            case DXGI_FORMAT_R8G8_UNORM:
                return PixelFormat::R8G8_UNORM;
            case DXGI_FORMAT_R8G8_SNORM:
                return PixelFormat::R8G8_SNORM;
            case DXGI_FORMAT_R8G8_UINT:
                return PixelFormat::R8G8_UINT;
            case DXGI_FORMAT_R8G8_SINT:
                return PixelFormat::R8G8_SINT;
            case DXGI_FORMAT_R16G16_FLOAT:
                return PixelFormat::R16G16_FLOAT;
            case DXGI_FORMAT_R16G16_UNORM:
                return PixelFormat::R16G16_UNORM;
            case DXGI_FORMAT_R16G16_SNORM:
                return PixelFormat::R16G16_SNORM;
            case DXGI_FORMAT_R16G16_UINT:
                return PixelFormat::R16G16_UINT;
            case DXGI_FORMAT_R16G16_SINT:
                return PixelFormat::R16G16_SINT;
            case DXGI_FORMAT_R32G32_FLOAT:
                return PixelFormat::R32G32_FLOAT;
            case DXGI_FORMAT_R32G32_UINT:
                return PixelFormat::R32G32_UINT;
            case DXGI_FORMAT_R32G32_SINT:
                return PixelFormat::R32G32_SINT;
            case DXGI_FORMAT_B5G6R5_UNORM:
                return PixelFormat::B5G6R5_UNORM;
            case DXGI_FORMAT_R11G11B10_FLOAT:
                return PixelFormat::R11G11B10_FLOAT;
            case DXGI_FORMAT_B8G8R8A8_UNORM:
                return PixelFormat::B8G8R8A8_UNORM;
            case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
                return PixelFormat::B8G8R8A8_UNORM_SRGB;
            case DXGI_FORMAT_B8G8R8X8_UNORM:
                return PixelFormat::B8G8R8X8_UNORM;
            case DXGI_FORMAT_R8G8B8A8_UNORM:
                return PixelFormat::R8G8B8A8_UNORM;
            case DXGI_FORMAT_R8G8B8A8_SNORM:
                return PixelFormat::R8G8B8A8_SNORM;
            case DXGI_FORMAT_R8G8B8A8_UINT:
                return PixelFormat::R8G8B8A8_UINT;
            case DXGI_FORMAT_R8G8B8A8_SINT:
                return PixelFormat::R8G8B8A8_SINT;
            case DXGI_FORMAT_R10G10B10A2_UNORM:
                return PixelFormat::R10G10B10A2_UNORM;
            case DXGI_FORMAT_R10G10B10A2_UINT:
                return PixelFormat::R10G10B10A2_UINT;
            case DXGI_FORMAT_R16G16B16A16_FLOAT:
                return PixelFormat::R16G16B16A16_FLOAT;
            case DXGI_FORMAT_R16G16B16A16_UNORM:
                return PixelFormat::R16G16B16A16_UNORM;
            case DXGI_FORMAT_R16G16B16A16_SNORM:
                return PixelFormat::R16G16B16A16_SNORM;
            case DXGI_FORMAT_R16G16B16A16_UINT:
                return PixelFormat::R16G16B16A16_UINT;
            case DXGI_FORMAT_R16G16B16A16_SINT:
                return PixelFormat::R16G16B16A16_SINT;
            case DXGI_FORMAT_R32G32B32A32_FLOAT:
                return PixelFormat::R32G32B32A32_FLOAT;
            case DXGI_FORMAT_R32G32B32A32_UINT:
                return PixelFormat::R32G32B32A32_UINT;
            case DXGI_FORMAT_R32G32B32A32_SINT:
                return PixelFormat::R32G32B32A32_SINT;
            case DXGI_FORMAT_D16_UNORM:
                return PixelFormat::D16_UNORM;
            case DXGI_FORMAT_D24_UNORM_S8_UINT:
                return PixelFormat::D24_UNORM_S8_UINT;
            case DXGI_FORMAT_D32_FLOAT:
                return PixelFormat::D32_FLOAT;
            case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
                return PixelFormat::D32_FLOAT_S8X24_UINT;
            case DXGI_FORMAT_BC1_UNORM:
                return PixelFormat::BC1_UNORM;
            case DXGI_FORMAT_BC2_UNORM:
                return PixelFormat::BC2_UNORM;
            case DXGI_FORMAT_BC3_UNORM:
                return PixelFormat::BC3_UNORM;
            case DXGI_FORMAT_BC4_SNORM:
                return PixelFormat::BC4_SNORM;
            case DXGI_FORMAT_BC4_UNORM:
                return PixelFormat::BC4_UNORM;
            case DXGI_FORMAT_BC5_SNORM:
                return PixelFormat::BC5_SNORM;
            case DXGI_FORMAT_BC5_UNORM:
                return PixelFormat::BC5_UNORM;
            case DXGI_FORMAT_BC6H_SF16:
                return PixelFormat::BC6H_SF16;
            case DXGI_FORMAT_BC6H_UF16:
                return PixelFormat::BC6H_UF16;
            case DXGI_FORMAT_BC7_UNORM:
                return PixelFormat::BC7_UNORM;
            case DXGI_FORMAT_B5G5R5A1_UNORM:
                return PixelFormat::B5G5R5A1_UNORM;
            default:
                break;
        }

        return PixelFormat::UNKNOWN;
    }

    DXGI_FORMAT D3D11GpuGetPixelFormat(
        PixelFormat format) noexcept
    {
        switch (format)
        {
            case PixelFormat::UNKNOWN:
                return DXGI_FORMAT_UNKNOWN;
            case PixelFormat::R8_UNORM:
                return DXGI_FORMAT_R8_UNORM;
            case PixelFormat::R8_SNORM:
                return DXGI_FORMAT_R8_SNORM;
            case PixelFormat::R8_UINT:
                return DXGI_FORMAT_R8_UINT;
            case PixelFormat::R8_SINT:
                return DXGI_FORMAT_R8_SINT;
            case PixelFormat::A8_UNORM:
                return DXGI_FORMAT_A8_UNORM;
            case PixelFormat::R16_FLOAT:
                return DXGI_FORMAT_R16_FLOAT;
            case PixelFormat::R16_UNORM:
                return DXGI_FORMAT_R16_UNORM;
            case PixelFormat::R16_SNORM:
                return DXGI_FORMAT_R16_SNORM;
            case PixelFormat::R16_UINT:
                return DXGI_FORMAT_R16_UINT;
            case PixelFormat::R16_SINT:
                return DXGI_FORMAT_R16_SINT;
            case PixelFormat::R32_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case PixelFormat::R32_UINT:
                return DXGI_FORMAT_R32_UINT;
            case PixelFormat::R32_SINT:
                return DXGI_FORMAT_R32_SINT;
            case PixelFormat::R8G8_UNORM:
                return DXGI_FORMAT_R8G8_UNORM;
            case PixelFormat::R8G8_SNORM:
                return DXGI_FORMAT_R8G8_SNORM;
            case PixelFormat::R8G8_UINT:
                return DXGI_FORMAT_R8G8_UINT;
            case PixelFormat::R8G8_SINT:
                return DXGI_FORMAT_R8G8_SINT;
            case PixelFormat::R16G16_FLOAT:
                return DXGI_FORMAT_R16G16_FLOAT;
            case PixelFormat::R16G16_UNORM:
                return DXGI_FORMAT_R16G16_UNORM;
            case PixelFormat::R16G16_SNORM:
                return DXGI_FORMAT_R16G16_SNORM;
            case PixelFormat::R16G16_UINT:
                return DXGI_FORMAT_R16G16_UINT;
            case PixelFormat::R16G16_SINT:
                return DXGI_FORMAT_R16G16_SINT;
            case PixelFormat::R32G32_FLOAT:
                return DXGI_FORMAT_R32G32_FLOAT;
            case PixelFormat::R32G32_UINT:
                return DXGI_FORMAT_R32G32_UINT;
            case PixelFormat::R32G32_SINT:
                return DXGI_FORMAT_R32G32_SINT;
            case PixelFormat::B5G6R5_UNORM:
                return DXGI_FORMAT_B5G6R5_UNORM;
            case PixelFormat::R11G11B10_FLOAT:
                return DXGI_FORMAT_R11G11B10_FLOAT;
            case PixelFormat::B8G8R8A8_UNORM:
                return DXGI_FORMAT_B8G8R8A8_UNORM;
            case PixelFormat::B8G8R8A8_UNORM_SRGB:
                return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
            case PixelFormat::B8G8R8X8_UNORM:
                return DXGI_FORMAT_B8G8R8X8_UNORM;
            case PixelFormat::R8G8B8A8_UNORM:
                return DXGI_FORMAT_R8G8B8A8_UNORM;
            case PixelFormat::R8G8B8A8_SNORM:
                return DXGI_FORMAT_R8G8B8A8_SNORM;
            case PixelFormat::R8G8B8A8_UINT:
                return DXGI_FORMAT_R8G8B8A8_UINT;
            case PixelFormat::R8G8B8A8_SINT:
                return DXGI_FORMAT_R8G8B8A8_SINT;
            case PixelFormat::R10G10B10A2_UNORM:
                return DXGI_FORMAT_R10G10B10A2_UNORM;
            case PixelFormat::R10G10B10A2_UINT:
                return DXGI_FORMAT_R10G10B10A2_UINT;
            case PixelFormat::R16G16B16A16_FLOAT:
                return DXGI_FORMAT_R16G16B16A16_FLOAT;
            case PixelFormat::R16G16B16A16_UNORM:
                return DXGI_FORMAT_R16G16B16A16_UNORM;
            case PixelFormat::R16G16B16A16_SNORM:
                return DXGI_FORMAT_R16G16B16A16_SNORM;
            case PixelFormat::R16G16B16A16_UINT:
                return DXGI_FORMAT_R16G16B16A16_UINT;
            case PixelFormat::R16G16B16A16_SINT:
                return DXGI_FORMAT_R16G16B16A16_SINT;
            case PixelFormat::R32G32B32A32_FLOAT:
                return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case PixelFormat::R32G32B32A32_UINT:
                return DXGI_FORMAT_R32G32B32A32_UINT;
            case PixelFormat::R32G32B32A32_SINT:
                return DXGI_FORMAT_R32G32B32A32_SINT;
            case PixelFormat::D16_UNORM:
                return DXGI_FORMAT_D16_UNORM;
            case PixelFormat::D24_UNORM_S8_UINT:
                return DXGI_FORMAT_D24_UNORM_S8_UINT;
            case PixelFormat::D32_FLOAT:
                return DXGI_FORMAT_D32_FLOAT;
            case PixelFormat::D32_FLOAT_S8X24_UINT:
                return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
            case PixelFormat::BC1_UNORM:
                return DXGI_FORMAT_BC1_UNORM;
            case PixelFormat::BC2_UNORM:
                return DXGI_FORMAT_BC2_UNORM;
            case PixelFormat::BC3_UNORM:
                return DXGI_FORMAT_BC3_UNORM;
            case PixelFormat::BC4_SNORM:
                return DXGI_FORMAT_BC4_SNORM;
            case PixelFormat::BC4_UNORM:
                return DXGI_FORMAT_BC4_UNORM;
            case PixelFormat::BC5_SNORM:
                return DXGI_FORMAT_BC5_SNORM;
            case PixelFormat::BC5_UNORM:
                return DXGI_FORMAT_BC5_UNORM;
            case PixelFormat::BC6H_SF16:
                return DXGI_FORMAT_BC6H_SF16;
            case PixelFormat::BC6H_UF16:
                return DXGI_FORMAT_BC6H_UF16;
            case PixelFormat::BC7_UNORM:
                return DXGI_FORMAT_BC7_UNORM;
            case PixelFormat::B5G5R5A1_UNORM:
                return DXGI_FORMAT_B5G5R5A1_UNORM;
        }

        return DXGI_FORMAT_UNKNOWN;
    }

    DXGI_FORMAT D3D11GpuGetCreateResourcePixelFormat(
        PixelFormat format) noexcept
    {
        switch (format)
        {
            case PixelFormat::UNKNOWN:
                return DXGI_FORMAT_UNKNOWN;
            case PixelFormat::R8_UNORM:
                return DXGI_FORMAT_R8_TYPELESS;
            case PixelFormat::R8_SNORM:
                return DXGI_FORMAT_R8_TYPELESS;
            case PixelFormat::R8_UINT:
                return DXGI_FORMAT_R8_TYPELESS;
            case PixelFormat::R8_SINT:
                return DXGI_FORMAT_R8_TYPELESS;
            case PixelFormat::A8_UNORM:
                return DXGI_FORMAT_R8_TYPELESS;
            case PixelFormat::R16_FLOAT:
                return DXGI_FORMAT_R16_TYPELESS;
            case PixelFormat::R16_UNORM:
                return DXGI_FORMAT_R16_TYPELESS;
            case PixelFormat::R16_SNORM:
                return DXGI_FORMAT_R16_TYPELESS;
            case PixelFormat::R16_UINT:
                return DXGI_FORMAT_R16_TYPELESS;
            case PixelFormat::R16_SINT:
                return DXGI_FORMAT_R16_TYPELESS;
            case PixelFormat::R32_FLOAT:
                return DXGI_FORMAT_R32_TYPELESS;
            case PixelFormat::R32_UINT:
                return DXGI_FORMAT_R32_TYPELESS;
            case PixelFormat::R32_SINT:
                return DXGI_FORMAT_R32_TYPELESS;
            case PixelFormat::R8G8_UNORM:
                return DXGI_FORMAT_R8G8_TYPELESS;
            case PixelFormat::R8G8_SNORM:
                return DXGI_FORMAT_R8G8_TYPELESS;
            case PixelFormat::R8G8_UINT:
                return DXGI_FORMAT_R8G8_TYPELESS;
            case PixelFormat::R8G8_SINT:
                return DXGI_FORMAT_R8G8_TYPELESS;
            case PixelFormat::R16G16_FLOAT:
                return DXGI_FORMAT_R16G16_TYPELESS;
            case PixelFormat::R16G16_UNORM:
                return DXGI_FORMAT_R16G16_TYPELESS;
            case PixelFormat::R16G16_SNORM:
                return DXGI_FORMAT_R16G16_TYPELESS;
            case PixelFormat::R16G16_UINT:
                return DXGI_FORMAT_R16G16_TYPELESS;
            case PixelFormat::R16G16_SINT:
                return DXGI_FORMAT_R16G16_TYPELESS;
            case PixelFormat::R32G32_FLOAT:
                return DXGI_FORMAT_R32G32_TYPELESS;
            case PixelFormat::R32G32_UINT:
                return DXGI_FORMAT_R32G32_TYPELESS;
            case PixelFormat::R32G32_SINT:
                return DXGI_FORMAT_R32G32_TYPELESS;
            case PixelFormat::B5G6R5_UNORM:
                return DXGI_FORMAT_B5G6R5_UNORM;
            case PixelFormat::R11G11B10_FLOAT:
                return DXGI_FORMAT_R11G11B10_FLOAT;
            case PixelFormat::B8G8R8A8_UNORM:
                return DXGI_FORMAT_B8G8R8A8_TYPELESS;
            case PixelFormat::B8G8R8A8_UNORM_SRGB:
                return DXGI_FORMAT_B8G8R8A8_TYPELESS;
            case PixelFormat::B8G8R8X8_UNORM:
                return DXGI_FORMAT_B8G8R8X8_TYPELESS;
            case PixelFormat::R8G8B8A8_UNORM:
                return DXGI_FORMAT_R8G8B8A8_TYPELESS;
            case PixelFormat::R8G8B8A8_SNORM:
                return DXGI_FORMAT_R8G8B8A8_TYPELESS;
            case PixelFormat::R8G8B8A8_UINT:
                return DXGI_FORMAT_R8G8B8A8_TYPELESS;
            case PixelFormat::R8G8B8A8_SINT:
                return DXGI_FORMAT_R8G8B8A8_TYPELESS;
            case PixelFormat::R10G10B10A2_UNORM:
                return DXGI_FORMAT_R10G10B10A2_TYPELESS;
            case PixelFormat::R10G10B10A2_UINT:
                return DXGI_FORMAT_R10G10B10A2_TYPELESS;
            case PixelFormat::R16G16B16A16_FLOAT:
                return DXGI_FORMAT_R16G16B16A16_TYPELESS;
            case PixelFormat::R16G16B16A16_UNORM:
                return DXGI_FORMAT_R16G16B16A16_TYPELESS;
            case PixelFormat::R16G16B16A16_SNORM:
                return DXGI_FORMAT_R16G16B16A16_TYPELESS;
            case PixelFormat::R16G16B16A16_UINT:
                return DXGI_FORMAT_R16G16B16A16_TYPELESS;
            case PixelFormat::R16G16B16A16_SINT:
                return DXGI_FORMAT_R16G16B16A16_TYPELESS;
            case PixelFormat::R32G32B32A32_FLOAT:
                return DXGI_FORMAT_R32G32B32A32_TYPELESS;
            case PixelFormat::R32G32B32A32_UINT:
                return DXGI_FORMAT_R32G32B32A32_TYPELESS;
            case PixelFormat::R32G32B32A32_SINT:
                return DXGI_FORMAT_R32G32B32A32_TYPELESS;
            case PixelFormat::D16_UNORM:
                return DXGI_FORMAT_R16_TYPELESS;
            case PixelFormat::D24_UNORM_S8_UINT:
                return DXGI_FORMAT_R24G8_TYPELESS;
            case PixelFormat::D32_FLOAT:
                return DXGI_FORMAT_R32_TYPELESS;
            case PixelFormat::D32_FLOAT_S8X24_UINT:
                return DXGI_FORMAT_R32G8X24_TYPELESS;
            case PixelFormat::BC1_UNORM:
                return DXGI_FORMAT_BC1_TYPELESS;
            case PixelFormat::BC2_UNORM:
                return DXGI_FORMAT_BC2_TYPELESS;
            case PixelFormat::BC3_UNORM:
                return DXGI_FORMAT_BC3_TYPELESS;
            case PixelFormat::BC4_SNORM:
                return DXGI_FORMAT_BC4_TYPELESS;
            case PixelFormat::BC4_UNORM:
                return DXGI_FORMAT_BC4_TYPELESS;
            case PixelFormat::BC5_SNORM:
                return DXGI_FORMAT_BC5_TYPELESS;
            case PixelFormat::BC5_UNORM:
                return DXGI_FORMAT_BC5_TYPELESS;
            case PixelFormat::BC6H_SF16:
                return DXGI_FORMAT_BC6H_TYPELESS;
            case PixelFormat::BC6H_UF16:
                return DXGI_FORMAT_BC6H_TYPELESS;
            case PixelFormat::BC7_UNORM:
                return DXGI_FORMAT_BC7_TYPELESS;
            case PixelFormat::B5G5R5A1_UNORM:
                return DXGI_FORMAT_B5G5R5A1_UNORM;
        }

        return DXGI_FORMAT_UNKNOWN;
    }

    DXGI_FORMAT D3D11GpuGetRenderTargetFormat(
        PixelFormat format) noexcept
    {
        DXGI_FORMAT result = D3D11GpuGetPixelFormat(format);

        switch (result)
        {
            case DXGI_FORMAT_B8G8R8A8_TYPELESS:
                return DXGI_FORMAT_B8G8R8A8_UNORM;
            case DXGI_FORMAT_BC1_TYPELESS:
                return DXGI_FORMAT_BC1_UNORM;
            case DXGI_FORMAT_BC2_TYPELESS:
                return DXGI_FORMAT_BC2_UNORM;
            case DXGI_FORMAT_BC3_TYPELESS:
                return DXGI_FORMAT_BC3_UNORM;
            case DXGI_FORMAT_R16_TYPELESS:
                return DXGI_FORMAT_R16_UNORM;
            case DXGI_FORMAT_R8G8B8A8_TYPELESS:
                return DXGI_FORMAT_R8G8B8A8_UNORM;
            default:
                break;
        }

        return result;
    }

    DXGI_FORMAT D3D11GpuGetReadViewPixelFormat(
        PixelFormat format) noexcept
    {
        switch (format)
        {
            case PixelFormat::D16_UNORM:
                return DXGI_FORMAT_R16_UNORM;
            case PixelFormat::D24_UNORM_S8_UINT:
                return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            case PixelFormat::D32_FLOAT:
                return DXGI_FORMAT_R32_FLOAT;
            case PixelFormat::D32_FLOAT_S8X24_UINT:
                return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
            default:
                break;
        }

        return D3D11GpuGetPixelFormat(format);
    }

    DXGI_FORMAT D3D11GpuGetWriteViewPixelFormat(
        PixelFormat format) noexcept
    {
        switch (format)
        {
            case PixelFormat::D16_UNORM:
                return DXGI_FORMAT_R16_UNORM;
            case PixelFormat::D24_UNORM_S8_UINT:
                return DXGI_FORMAT_D24_UNORM_S8_UINT;
            case PixelFormat::D32_FLOAT:
                return DXGI_FORMAT_D32_FLOAT;
            case PixelFormat::D32_FLOAT_S8X24_UINT:
                return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
            default:
                break;
        }

        return D3D11GpuGetPixelFormat(format);
    }
}
