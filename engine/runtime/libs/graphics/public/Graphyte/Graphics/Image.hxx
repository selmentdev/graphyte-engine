#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Graphics/PixelFormat.hxx>
#include <Graphyte/Span.hxx>

namespace Graphyte::Graphics
{
    enum struct CubeFace
    {
        PositiveX = 0,
        NegativeX = 1,
        PositiveY = 2,
        NegativeY = 3,
        PositiveZ = 4,
        NegativeZ = 5,
    };

    enum struct ImageAlphaMode
    {
        Unknown = 0,
        Straight = 1,
        Premultiplied = 2,
        Opaque = 3,
        Custom = 4,
    };

    enum struct ImageDimension
    {
        Unknown = 0,
        Texture1D = 1,
        Texture1DArray = 2,
        Texture2D = 3,
        Texture2DArray = 4,
        TextureCube = 5,
        TextureCubeArray = 6,
        Texture3D = 7,
    };

    struct ImageDimensionProperties final
    {
        static bool IsArray(
            ImageDimension dimension
        ) noexcept
        {
            switch (dimension)
            {
            case ImageDimension::Texture1DArray:
            case ImageDimension::Texture2DArray:
            case ImageDimension::TextureCubeArray:
                return true;
            default:
                break;
            }

            return false;
        }

        static bool IsCube(
            ImageDimension dimension
        ) noexcept
        {
            switch (dimension)
            {
            case ImageDimension::TextureCube:
            case ImageDimension::TextureCubeArray:
                return true;
            default:
                break;
            }

            return false;
        }
    };

    struct ImagePixels final
    {
        void* Buffer;
        size_t LinePitch;
        size_t SlicePitch;
        size_t Size;
        uint32_t Width;
        uint32_t Height;
        uint32_t Depth;
        uint32_t MipLevel;

        template <typename TPixel>
        notstd::span<TPixel> GetPixels(
            size_t line,
            size_t slice = 0
        ) noexcept
        {
            std::byte* typed_buffer = reinterpret_cast<std::byte*>(Buffer);

            return { reinterpret_cast<TPixel*>(typed_buffer + slice * SlicePitch + line * LinePitch), Width };
        }

        template <typename TPixel>
        notstd::span<TPixel const> GetPixels(
            size_t line,
            size_t slice = 0
        ) const noexcept
        {
            std::byte const* typed_buffer = reinterpret_cast<std::byte const*>(Buffer);

            return { reinterpret_cast<TPixel const*>(typed_buffer + slice * SlicePitch + line * LinePitch), Width };
        }

        template <typename TPixel>
        TPixel* GetScanline(
            size_t line,
            size_t slice = 0
        ) noexcept
        {
            std::byte* typed_buffer = reinterpret_cast<std::byte*>(Buffer);

            return reinterpret_cast<TPixel*>(typed_buffer + slice * SlicePitch + line * LinePitch);
        }

        template <typename TPixel>
        const TPixel* GetScanline(
            size_t line,
            size_t slice = 0
        ) const noexcept
        {
            std::byte const* typed_buffer = reinterpret_cast<std::byte const*>(Buffer);

            return reinterpret_cast<TPixel const*>(typed_buffer + slice * SlicePitch + line * LinePitch);
        }
    };

    class GRAPHICS_API Image final
    {
    private:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_Depth;
        uint32_t m_MipmapCount;
        uint32_t m_ArrayCount;
        ImageDimension m_Dimension;
        PixelFormat m_PixelFormat;
        ImageAlphaMode m_AlphaMode;
        size_t m_SubresourcesCount;
        std::unique_ptr<ImagePixels[]> m_Subresources;
        size_t m_BufferSize;
        std::unique_ptr<uint8_t[]> m_Buffer;

    public:
        Image(
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            uint32_t mipmap_count,
            uint32_t array_count,
            PixelFormat format,
            ImageDimension image_dimension,
            ImageAlphaMode alpha_mode
        ) noexcept;

        Image() = delete;
        Image(const Image&) = delete;
        Image& operator = (const Image&) = delete;

        ~Image() noexcept;

    public:
        static std::unique_ptr<Image> Create1D(
            PixelFormat format,
            uint32_t width,
            uint32_t mipmap_count = 1,
            uint32_t array_count = 1,
            ImageAlphaMode alpha_mode = ImageAlphaMode::Unknown
        ) noexcept;

        static std::unique_ptr<Image> Create2D(
            PixelFormat format,
            uint32_t width,
            uint32_t height,
            uint32_t mipmap_count = 1,
            uint32_t array_count = 1,
            ImageAlphaMode alpha_mode = ImageAlphaMode::Unknown
        ) noexcept;

        static std::unique_ptr<Image> Create3D(
            PixelFormat format,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            uint32_t mipmap_count = 1,
            ImageAlphaMode alpha_mode = ImageAlphaMode::Unknown
        ) noexcept;

        static std::unique_ptr<Image> CreateCube(
            PixelFormat format,
            uint32_t size,
            uint32_t mipmap_count = 1,
            uint32_t array_count = 1,
            ImageAlphaMode alpha_mode = ImageAlphaMode::Unknown
        ) noexcept;

    public:
        static uint32_t CalcSubresource(
            uint32_t mip_slice,
            uint32_t array_slice,
            uint32_t mip_count
        ) noexcept
        {
            return (array_slice * mip_count) + mip_slice;
        }

    public:
        notstd::span<ImagePixels const> GetSubresources() const noexcept
        {
            return { &m_Subresources[0], m_SubresourcesCount };
        }

        notstd::span<ImagePixels> GetSubresources() noexcept
        {
            return { &m_Subresources[0], m_SubresourcesCount };
        }

        const ImagePixels* GetSubresource(
            size_t index
        ) const noexcept
        {
            if (index < m_SubresourcesCount)
            {
                return &m_Subresources[index];
            }

            return nullptr;
        }

        ImagePixels* GetSubresource(
            size_t index
        ) noexcept
        {
            if (index < m_SubresourcesCount)
            {
                return &m_Subresources[index];
            }

            return nullptr;
        }
        
        bool GetDimensions(
            uint32_t mipmap_level,
            uint32_t& width,
            uint32_t& height,
            uint32_t& depth
        ) const noexcept
        {
            if (mipmap_level < m_MipmapCount)
            {
                width = PixelFormatProperties::GetImageWidth(m_Width, mipmap_level, m_PixelFormat);
                height = PixelFormatProperties::GetImageHeight(m_Height, mipmap_level, m_PixelFormat);
                depth = PixelFormatProperties::GetImageDepth(m_Depth, mipmap_level, m_PixelFormat);

                return true;
            }

            width = {};
            height = {};
            depth = {};

            return false;
        }

        ImagePixels* GetPixels(
            uint32_t array_index,
            uint32_t mipmap_index = 0
        ) noexcept;

        ImagePixels* GetPixels(
            CubeFace cube_face,
            uint32_t array_index,
            uint32_t mipmap_index = 0
        ) noexcept;

    public:
        uint32_t GetWidth() const noexcept
        {
            return m_Width;
        }
        uint32_t GetHeight() const noexcept
        {
            return m_Height;
        }
        uint32_t GetDepth() const noexcept
        {
            return m_Depth;
        }
        uint32_t GetMipmapCount() const noexcept
        {
            return m_MipmapCount;
        }
        uint32_t GetArrayCount() const noexcept
        {
            return m_ArrayCount;
        }
        uint32_t GetFacesCount() const noexcept
        {
            return static_cast<uint32_t>(ImageDimensionProperties::IsCube(m_Dimension) ? 6 : 1);
        }

        ImageDimension GetDimension() const noexcept
        {
            return m_Dimension;
        }
        PixelFormat GetPixelFormat() const noexcept
        {
            return m_PixelFormat;
        }

        size_t GetSubresourcesCount() const noexcept
        {
            return m_SubresourcesCount;
        }

        size_t GetBufferSize() const noexcept
        {
            return m_BufferSize;
        }

        ImageAlphaMode GetAlphaMode() const noexcept
        {
            return m_AlphaMode;
        }

    private:
        void AllocateResources() noexcept;
    };
}
