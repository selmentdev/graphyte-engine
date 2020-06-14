#pragma once
#include <GxGraphics/Graphics.module.hxx>

namespace Graphyte::Graphics
{
    // https://msdn.microsoft.com/en-us/library/windows/desktop/cc308051(v=vs.85).aspx
    enum struct PixelFormat
    {
        UNKNOWN,
        R8_UNORM,
        R8_SNORM,
        R8_UINT,
        R8_SINT,
        A8_UNORM,
        R16_FLOAT,
        R16_UNORM,
        R16_SNORM,
        R16_UINT,
        R16_SINT,
        R32_FLOAT,
        R32_UINT,
        R32_SINT,
        R8G8_UNORM,
        R8G8_SNORM,
        R8G8_UINT,
        R8G8_SINT,
        R16G16_FLOAT,
        R16G16_UNORM,
        R16G16_SNORM,
        R16G16_UINT,
        R16G16_SINT,
        R32G32_FLOAT,
        R32G32_UINT,
        R32G32_SINT,
        B5G6R5_UNORM,
        B5G5R5A1_UNORM,
        R11G11B10_FLOAT,
        B8G8R8A8_UNORM,
        B8G8R8A8_UNORM_SRGB,
        B8G8R8X8_UNORM,
        R8G8B8A8_UNORM,
        R8G8B8A8_SNORM,
        R8G8B8A8_UINT,
        R8G8B8A8_SINT,
        R10G10B10A2_UNORM,
        R10G10B10A2_UINT,
        R16G16B16A16_FLOAT,
        R16G16B16A16_UNORM,
        R16G16B16A16_SNORM,
        R16G16B16A16_UINT,
        R16G16B16A16_SINT,
        R32G32B32A32_FLOAT,
        R32G32B32A32_UINT,
        R32G32B32A32_SINT,

        D16_UNORM,
        D24_UNORM_S8_UINT,
        D32_FLOAT,
        D32_FLOAT_S8X24_UINT,

        BC1_UNORM,
        BC2_UNORM,
        BC3_UNORM,
        BC4_SNORM,
        BC4_UNORM,
        BC5_SNORM,
        BC5_UNORM,
        BC6H_SF16,
        BC6H_UF16,
        BC7_UNORM,
    };

    struct GRAPHICS_API PixelFormatProperties final
    {
        static size_t GetBlockSize(
            PixelFormat format) noexcept;

        static size_t GetPixelBits(
            PixelFormat format) noexcept;

        static size_t GetColorBits(
            PixelFormat format) noexcept;

        static size_t GetAlphaBits(
            PixelFormat format) noexcept;

        static bool IsCompressed(
            PixelFormat format) noexcept;

        static size_t GetDepthBits(
            PixelFormat format) noexcept;

        static size_t GetStencilBits(
            PixelFormat format) noexcept;

        static size_t GetChannelsCount(
            PixelFormat format) noexcept;

        static uint32_t GetImageWidth(
            uint32_t value,
            uint32_t mipmap,
            PixelFormat format) noexcept;

        static uint32_t GetImageHeight(
            uint32_t value,
            uint32_t mipmap,
            PixelFormat format) noexcept;

        static uint32_t GetImageDepth(
            uint32_t value,
            uint32_t mipmap,
            PixelFormat format) noexcept;

        static size_t SlicePitchBytes(
            PixelFormat format,
            uint32_t width,
            uint32_t height,
            uint32_t depth = 1) noexcept;

        static size_t GetStorageSize(
            PixelFormat format,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            uint32_t mipmaps) noexcept;

        static size_t LinePitchBytes(
            PixelFormat format,
            uint32_t width) noexcept;

        static size_t RowPitchBytes(
            PixelFormat format,
            uint32_t width) noexcept;

        static void GetSurfaceInfo(
            PixelFormat format,
            uint32_t width,
            uint32_t height,
            size_t& out_bytes,
            size_t& out_row_bytes,
            size_t& out_rows) noexcept;

        static uint32_t ComputeMipMapLevels(
            PixelFormat format,
            uint32_t width,
            uint32_t height,
            uint32_t depth = 1) noexcept;

        static uint32_t CalcSubresource(
            uint32_t mip_slice,
            uint32_t array_slice,
            uint32_t mip_levels) noexcept
        {
            return mip_slice + (array_slice * mip_levels);
        }
    };
}
