#include <GxGraphics/Graphics/PixelFormat.hxx>
//#include <GxBase/Bitwise.hxx>

namespace Graphyte::Graphics
{
    size_t PixelFormatProperties::GetBlockSize(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::BC1_UNORM:
        case PixelFormat::BC4_SNORM:
        case PixelFormat::BC4_UNORM:
            return 8;
        case PixelFormat::BC2_UNORM:
        case PixelFormat::BC3_UNORM:
        case PixelFormat::BC5_SNORM:
        case PixelFormat::BC5_UNORM:
        case PixelFormat::BC6H_SF16:
        case PixelFormat::BC6H_UF16:
        case PixelFormat::BC7_UNORM:
            return 16;
        default:
            return 0;
        }
    }

    size_t PixelFormatProperties::GetPixelBits(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::R8_UNORM:
        case PixelFormat::R8_SNORM:
        case PixelFormat::R8_UINT:
        case PixelFormat::R8_SINT:
        case PixelFormat::A8_UNORM:
            return 8;

        case PixelFormat::R16_FLOAT:
        case PixelFormat::R16_UNORM:
        case PixelFormat::R16_SNORM:
        case PixelFormat::R16_UINT:
        case PixelFormat::R16_SINT:
        case PixelFormat::R8G8_UNORM:
        case PixelFormat::R8G8_SNORM:
        case PixelFormat::R8G8_UINT:
        case PixelFormat::R8G8_SINT:
        case PixelFormat::B5G6R5_UNORM:
        case PixelFormat::B5G5R5A1_UNORM:
        case PixelFormat::D16_UNORM:
            return 16;

        case PixelFormat::R32_FLOAT:
        case PixelFormat::R32_UINT:
        case PixelFormat::R32_SINT:
        case PixelFormat::R16G16_FLOAT:
        case PixelFormat::R16G16_UNORM:
        case PixelFormat::R16G16_SNORM:
        case PixelFormat::R16G16_UINT:
        case PixelFormat::R16G16_SINT:
        case PixelFormat::R11G11B10_FLOAT:
        case PixelFormat::B8G8R8A8_UNORM:
        case PixelFormat::B8G8R8A8_UNORM_SRGB:
        case PixelFormat::B8G8R8X8_UNORM:
        case PixelFormat::R8G8B8A8_UNORM:
        case PixelFormat::R8G8B8A8_SNORM:
        case PixelFormat::R8G8B8A8_UINT:
        case PixelFormat::R8G8B8A8_SINT:
        case PixelFormat::R10G10B10A2_UNORM:
        case PixelFormat::R10G10B10A2_UINT:
        case PixelFormat::D24_UNORM_S8_UINT:
        case PixelFormat::D32_FLOAT:
            return 32;

        case PixelFormat::R32G32_FLOAT:
        case PixelFormat::R32G32_UINT:
        case PixelFormat::R32G32_SINT:
        case PixelFormat::R16G16B16A16_FLOAT:
        case PixelFormat::R16G16B16A16_UNORM:
        case PixelFormat::R16G16B16A16_SNORM:
        case PixelFormat::R16G16B16A16_UINT:
        case PixelFormat::R16G16B16A16_SINT:
        case PixelFormat::D32_FLOAT_S8X24_UINT:
            return 64;

        case PixelFormat::R32G32B32A32_FLOAT:
        case PixelFormat::R32G32B32A32_UINT:
        case PixelFormat::R32G32B32A32_SINT:
            return 128;

        default:
            return 0;
        }
    }

    size_t PixelFormatProperties::GetColorBits(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::R8_SINT:
        case PixelFormat::R8_SNORM:
        case PixelFormat::R8_UINT:
        case PixelFormat::R8_UNORM:
            return 8;

        case PixelFormat::B5G6R5_UNORM:
        case PixelFormat::B5G5R5A1_UNORM:
        case PixelFormat::R16_FLOAT:
        case PixelFormat::R16_SINT:
        case PixelFormat::R16_SNORM:
        case PixelFormat::R16_UINT:
        case PixelFormat::R16_UNORM:
        case PixelFormat::R8G8_SINT:
        case PixelFormat::R8G8_SNORM:
        case PixelFormat::R8G8_UINT:
        case PixelFormat::R8G8_UNORM:
            return 16;

        case PixelFormat::B8G8R8A8_UNORM:
        case PixelFormat::B8G8R8A8_UNORM_SRGB:
        case PixelFormat::B8G8R8X8_UNORM:
        case PixelFormat::R8G8B8A8_SINT:
        case PixelFormat::R8G8B8A8_SNORM:
        case PixelFormat::R8G8B8A8_UINT:
        case PixelFormat::R8G8B8A8_UNORM:
            return 24;

        case PixelFormat::R10G10B10A2_UINT:
        case PixelFormat::R10G10B10A2_UNORM:
            return 30;

        case PixelFormat::R11G11B10_FLOAT:
        case PixelFormat::R16G16_FLOAT:
        case PixelFormat::R16G16_SINT:
        case PixelFormat::R16G16_SNORM:
        case PixelFormat::R16G16_UINT:
        case PixelFormat::R16G16_UNORM:
        case PixelFormat::R32_FLOAT:
        case PixelFormat::R32_SINT:
        case PixelFormat::R32_UINT:
            return 32;

        case PixelFormat::R16G16B16A16_FLOAT:
        case PixelFormat::R16G16B16A16_SINT:
        case PixelFormat::R16G16B16A16_SNORM:
        case PixelFormat::R16G16B16A16_UINT:
        case PixelFormat::R16G16B16A16_UNORM:
            return 48;

        case PixelFormat::R32G32_FLOAT:
        case PixelFormat::R32G32_SINT:
        case PixelFormat::R32G32_UINT:
            return 64;

        case PixelFormat::R32G32B32A32_FLOAT:
        case PixelFormat::R32G32B32A32_SINT:
        case PixelFormat::R32G32B32A32_UINT:
            return 96;

        default:
            return 0;
        }
    }

    size_t PixelFormatProperties::GetAlphaBits(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::B5G5R5A1_UNORM:
            return 1;

        case PixelFormat::R10G10B10A2_UINT:
        case PixelFormat::R10G10B10A2_UNORM:
            return 2;

        case PixelFormat::A8_UNORM:
        case PixelFormat::R8G8B8A8_SINT:
        case PixelFormat::R8G8B8A8_SNORM:
        case PixelFormat::R8G8B8A8_UINT:
        case PixelFormat::B8G8R8A8_UNORM:
        case PixelFormat::R8G8B8A8_UNORM:
        case PixelFormat::B8G8R8A8_UNORM_SRGB:
            return 8;

        case PixelFormat::R16G16B16A16_FLOAT:
        case PixelFormat::R16G16B16A16_SINT:
        case PixelFormat::R16G16B16A16_SNORM:
        case PixelFormat::R16G16B16A16_UINT:
        case PixelFormat::R16G16B16A16_UNORM:
            return 16;

        case PixelFormat::R32G32B32A32_FLOAT:
        case PixelFormat::R32G32B32A32_SINT:
        case PixelFormat::R32G32B32A32_UINT:
            return 32;

        default:
            return 0;
        }
    }

    bool PixelFormatProperties::IsCompressed(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::BC1_UNORM:
        case PixelFormat::BC2_UNORM:
        case PixelFormat::BC3_UNORM:
        case PixelFormat::BC4_SNORM:
        case PixelFormat::BC4_UNORM:
        case PixelFormat::BC5_SNORM:
        case PixelFormat::BC5_UNORM:
        case PixelFormat::BC6H_SF16:
        case PixelFormat::BC6H_UF16:
        case PixelFormat::BC7_UNORM:
            return true;

        default:
            return false;
        }
    }

    size_t PixelFormatProperties::GetDepthBits(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::D16_UNORM:
            return 16;

        case PixelFormat::D24_UNORM_S8_UINT:
            return 24;

        case PixelFormat::D32_FLOAT:
        case PixelFormat::D32_FLOAT_S8X24_UINT:
            return 32;

        default:
            return 0;
        }
    }

    size_t PixelFormatProperties::GetStencilBits(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::D24_UNORM_S8_UINT:
        case PixelFormat::D32_FLOAT_S8X24_UINT:
            return 8;

        default:
            return 0;
        }
    }

    size_t PixelFormatProperties::GetChannelsCount(
        PixelFormat format
    ) noexcept
    {
        switch (format)
        {
        case PixelFormat::R16_FLOAT:
        case PixelFormat::R32_FLOAT:
        case PixelFormat::R16_SINT:
        case PixelFormat::R32_SINT:
        case PixelFormat::R8_SINT:
        case PixelFormat::BC4_SNORM:
        case PixelFormat::R16_SNORM:
        case PixelFormat::R8_SNORM:
        case PixelFormat::R16_UINT:
        case PixelFormat::R32_UINT:
        case PixelFormat::R8_UINT:
        case PixelFormat::A8_UNORM:
        case PixelFormat::BC4_UNORM:
        case PixelFormat::R16_UNORM:
        case PixelFormat::R8_UNORM:
            return 1;

        case PixelFormat::R16G16_FLOAT:
        case PixelFormat::R32G32_FLOAT:
        case PixelFormat::R16G16_SINT:
        case PixelFormat::R32G32_SINT:
        case PixelFormat::R8G8_SINT:
        case PixelFormat::BC5_SNORM:
        case PixelFormat::R16G16_SNORM:
        case PixelFormat::R8G8_SNORM:
        case PixelFormat::R16G16_UINT:
        case PixelFormat::R32G32_UINT:
        case PixelFormat::R8G8_UINT:
        case PixelFormat::BC5_UNORM:
        case PixelFormat::R16G16_UNORM:
        case PixelFormat::R8G8_UNORM:
            return 2;

        case PixelFormat::R11G11B10_FLOAT:
        case PixelFormat::B5G6R5_UNORM:
            return 3;

        case PixelFormat::BC6H_SF16:
        case PixelFormat::BC6H_UF16:
        case PixelFormat::R16G16B16A16_FLOAT:
        case PixelFormat::R32G32B32A32_FLOAT:
        case PixelFormat::R16G16B16A16_SINT:
        case PixelFormat::R32G32B32A32_SINT:
        case PixelFormat::R8G8B8A8_SINT:
        case PixelFormat::R16G16B16A16_SNORM:
        case PixelFormat::R8G8B8A8_SNORM:
        case PixelFormat::R10G10B10A2_UINT:
        case PixelFormat::R16G16B16A16_UINT:
        case PixelFormat::R32G32B32A32_UINT:
        case PixelFormat::R8G8B8A8_UINT:
        case PixelFormat::B8G8R8A8_UNORM:
        case PixelFormat::B8G8R8X8_UNORM:
        case PixelFormat::BC1_UNORM:
        case PixelFormat::BC2_UNORM:
        case PixelFormat::BC3_UNORM:
        case PixelFormat::BC7_UNORM:
        case PixelFormat::R10G10B10A2_UNORM:
        case PixelFormat::R16G16B16A16_UNORM:
        case PixelFormat::R8G8B8A8_UNORM:
        case PixelFormat::B8G8R8A8_UNORM_SRGB:
        case PixelFormat::B5G5R5A1_UNORM:
            return 4;

        default:
            return 0;
        }
    }

    uint32_t PixelFormatProperties::GetImageWidth(
        uint32_t value,
        uint32_t mipmap,
        PixelFormat format
    ) noexcept
    {
        uint32_t const min_value = static_cast<uint32_t>(IsCompressed(format) ? 4 : 1);
        return std::max<uint32_t>(min_value, value >> mipmap);
    }

    uint32_t PixelFormatProperties::GetImageHeight(
        uint32_t value,
        uint32_t mipmap,
        PixelFormat format
    ) noexcept
    {
        uint32_t const min_value = static_cast<uint32_t>(IsCompressed(format) ? 4 : 1);
        return std::max<uint32_t>(min_value, value >> mipmap);
    }

    uint32_t PixelFormatProperties::GetImageDepth(
        uint32_t value,
        uint32_t mipmap,
        [[maybe_unused]] PixelFormat format
    ) noexcept
    {
        return std::max<uint32_t>(1, value >> mipmap);
    }

    size_t PixelFormatProperties::SlicePitchBytes(
        PixelFormat format,
        uint32_t width,
        uint32_t height,
        uint32_t depth
    ) noexcept
    {
        size_t const block_size = GetBlockSize(format);
        if (block_size != 0)
        {
            uint32_t const blocks_horz = AlignUp<uint32_t>(width, 4) / 4;
            uint32_t const blocks_vert = AlignUp<uint32_t>(height, 4) / 4;
            uint32_t const blocks_count = blocks_horz * blocks_vert;
            return blocks_count * block_size * depth;
        }
        else
        {
            uint64_t bits_total = width;
            bits_total *= height;
            bits_total *= depth;
            bits_total *= GetPixelBits(format);
            size_t const bytes_total = static_cast<size_t>(bits_total / 8);
            return bytes_total;
        }
    }

    size_t PixelFormatProperties::GetStorageSize(
        PixelFormat format,
        uint32_t width,
        uint32_t height,
        uint32_t depth,
        uint32_t mipmaps
    ) noexcept
    {
        uint32_t const w = std::max<uint32_t>(1, width >> mipmaps);
        uint32_t const h = std::max<uint32_t>(1, height >> mipmaps);
        uint32_t const d = std::max<uint32_t>(1, depth >> mipmaps);
        size_t const size = SlicePitchBytes(format, w, h, d);
        return size;
    }

    size_t PixelFormatProperties::LinePitchBytes(
        PixelFormat format,
        uint32_t width
    ) noexcept
    {
        size_t const bits_per_pixel = GetPixelBits(format);

        // For compressed pixel format, bits_per_pixel == 0.
        return (width * bits_per_pixel) / 8;
    }

    size_t PixelFormatProperties::RowPitchBytes(
        PixelFormat format,
        uint32_t width
    ) noexcept
    {
        size_t const block_size = GetBlockSize(format);
        if (block_size != 0)
        {
            uint32_t const blocks_count = AlignUp<uint32_t>(width, 4) / 4;
            return blocks_count * block_size;
        }
        else
        {
            size_t const bits_per_pixel = GetPixelBits(format);
            size_t const result = AlignUp<size_t>(width * bits_per_pixel, 8) / 8;
            return result;
        }
    }

    void PixelFormatProperties::GetSurfaceInfo(
        PixelFormat format,
        uint32_t width,
        uint32_t height,
        size_t& out_bytes,
        size_t& out_row_bytes,
        size_t& out_rows
    ) noexcept
    {
        size_t const block_size = GetBlockSize(format);

        if (block_size != 0)
        {
            size_t blocks_horz = 0;
            if (width > 0)
            {
                blocks_horz = std::max<size_t>(1, AlignUp<uint32_t>(width, 4) / 4);
            }

            size_t blocks_vert = 0;
            if (height > 0)
            {
                blocks_vert = std::max<size_t>(1, AlignUp<uint32_t>(height, 4) / 4);
            }

            out_row_bytes = blocks_horz * block_size;
            out_rows = blocks_vert;
        }
        else
        {
            size_t const bpp = GetPixelBits(format);
            out_row_bytes = AlignUp<size_t>(width * bpp, 8) / 8;
            out_rows = height;
        }

        out_bytes = out_row_bytes * out_rows;
    }

    uint32_t PixelFormatProperties::ComputeMipMapLevels(
        PixelFormat format,
        uint32_t width,
        uint32_t height,
        uint32_t depth
    ) noexcept
    {
        uint32_t const min_value = static_cast<uint32_t>(IsCompressed(format) ? 4 : 1);
        uint32_t levels = 1;

        while (width > min_value || height > min_value || depth > 1)
        {
            width = std::max<uint32_t>(min_value, width >> 1);
            height = std::max<uint32_t>(min_value, height >> 1);
            depth = std::max<uint32_t>(1, depth >> 1);

            ++levels;
        }

        return levels;
    }
}
