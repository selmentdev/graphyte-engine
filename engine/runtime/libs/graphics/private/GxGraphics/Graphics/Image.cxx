#include <GxGraphics/Graphics/Image.hxx>

namespace Graphyte::Graphics
{
    Image::Image(
        uint32_t width,
        uint32_t height,
        uint32_t depth,
        uint32_t mipmap_count,
        uint32_t array_count,
        PixelFormat format,
        ImageDimension image_dimension,
        ImageAlphaMode alpha_mode) noexcept
        : m_Width{ width }
        , m_Height{ height }
        , m_Depth{ depth }
        , m_MipmapCount{ std::max<uint32_t>(1, mipmap_count) }
        , m_ArrayCount{ std::max<uint32_t>(1, array_count) }
        , m_Dimension{ image_dimension }
        , m_PixelFormat{ format }
        , m_AlphaMode{ alpha_mode }
        , m_SubresourcesCount{}
        , m_Subresources{}
        , m_BufferSize{}
        , m_Buffer{}
    {
        AllocateResources();
    }

    Image::~Image() noexcept = default;


    std::unique_ptr<Image> Image::Create1D(
        PixelFormat format,
        uint32_t width,
        uint32_t mipmap_count,
        uint32_t array_count,
        ImageAlphaMode alpha_mode) noexcept
    {
        ImageDimension const image_dimension = (array_count > 1)
                                                   ? ImageDimension::Texture1DArray
                                                   : ImageDimension::Texture1D;

        return std::make_unique<Image>(
            width,
            1,
            1,
            mipmap_count,
            array_count,
            format,
            image_dimension,
            alpha_mode);
    }

    std::unique_ptr<Image> Image::Create2D(
        PixelFormat format,
        uint32_t width,
        uint32_t height,
        uint32_t mipmap_count,
        uint32_t array_count,
        ImageAlphaMode alpha_mode) noexcept
    {
        ImageDimension const image_dimension = (array_count > 1)
                                                   ? ImageDimension::Texture2DArray
                                                   : ImageDimension::Texture2D;

        return std::make_unique<Image>(
            width,
            height,
            1,
            mipmap_count,
            array_count,
            format,
            image_dimension,
            alpha_mode);
    }

    std::unique_ptr<Image> Image::Create3D(
        PixelFormat format,
        uint32_t width,
        uint32_t height,
        uint32_t depth,
        uint32_t mipmap_count,
        ImageAlphaMode alpha_mode) noexcept
    {
        ImageDimension const image_dimension = ImageDimension::Texture3D;

        return std::make_unique<Image>(
            width,
            height,
            depth,
            mipmap_count,
            1,
            format,
            image_dimension,
            alpha_mode);
    }

    std::unique_ptr<Image> Image::CreateCube(
        PixelFormat format,
        uint32_t size,
        uint32_t mipmap_count,
        uint32_t array_count,
        ImageAlphaMode alpha_mode) noexcept
    {
        ImageDimension const image_dimension = (array_count > 1)
                                                   ? ImageDimension::TextureCubeArray
                                                   : ImageDimension::TextureCube;

        return std::make_unique<Image>(
            size,
            size,
            1,
            mipmap_count,
            array_count,
            format,
            image_dimension,
            alpha_mode);
    }

    ImagePixels* Image::GetPixels(
        uint32_t array_index,
        uint32_t mipmap_index) noexcept
    {
        if (array_index >= m_ArrayCount || mipmap_index >= m_MipmapCount)
        {
            return nullptr;
        }

        if (IsCube(m_Dimension))
        {
            return nullptr;
        }

        if (array_index != 0 && !IsArray(m_Dimension))
        {
            return nullptr;
        }

        size_t subresource = (static_cast<size_t>(array_index) * m_MipmapCount) + mipmap_index;

        if (subresource >= m_SubresourcesCount)
        {
            return nullptr;
        }

        return &m_Subresources[subresource];
    }

    ImagePixels* Image::GetPixels(
        CubeFace cube_face,
        uint32_t array_index,
        uint32_t mipmap_index) noexcept
    {
        if (!IsCube(m_Dimension))
        {
            return nullptr;
        }

        if (array_index >= m_ArrayCount || mipmap_index >= m_MipmapCount)
        {
            return nullptr;
        }

        GX_ASSERT((m_SubresourcesCount % 6) == 0);

        if (array_index != 0 && !IsArray(m_Dimension))
        {
            return nullptr;
        }

        size_t cubeface_index = static_cast<size_t>(cube_face);

        GX_ASSERT(cubeface_index < 6);

        size_t subresource = (((static_cast<size_t>(array_index) * 6) + cubeface_index) * m_MipmapCount) + mipmap_index;

        if (subresource >= m_SubresourcesCount)
        {
            return nullptr;
        }

        return &m_Subresources[subresource];
    }

    void Image::AllocateResources() noexcept
    {
        GX_ASSERT(m_ArrayCount >= 1);
        GX_ASSERT(m_MipmapCount >= 1);

        // Fixup surface dimensions based on pixel format.
        m_Width  = PixelFormatProperties::GetImageWidth(m_Width, 0, m_PixelFormat);
        m_Height = PixelFormatProperties::GetImageHeight(m_Height, 0, m_PixelFormat);
        m_Depth  = PixelFormatProperties::GetImageDepth(m_Depth, 0, m_PixelFormat);

        size_t faces_count = static_cast<size_t>((m_Dimension == ImageDimension::TextureCube || m_Dimension == ImageDimension::TextureCubeArray) ? 6 : 1);

        if (m_MipmapCount == 0)
        {
            m_MipmapCount = PixelFormatProperties::ComputeMipMapLevels(m_PixelFormat, m_Width, m_Height, m_Depth);
        }

        m_SubresourcesCount = static_cast<size_t>(m_ArrayCount) * m_MipmapCount * faces_count;

        m_Subresources = std::make_unique<ImagePixels[]>(m_SubresourcesCount);

        size_t index = 0;

        size_t num_bytes = 0;
        size_t row_bytes = 0;
        size_t row_count = 0;

        for (uint32_t j = 0; j < m_ArrayCount; ++j)
        {
            for (size_t f = 0; f < faces_count; ++f)
            {
                uint32_t w = m_Width;
                uint32_t h = m_Height;
                uint32_t d = m_Depth;

                for (uint32_t i = 0; i < m_MipmapCount; ++i)
                {
                    PixelFormatProperties::GetSurfaceInfo(
                        m_PixelFormat,
                        w,
                        h,
                        num_bytes,
                        row_bytes,
                        row_count);

                    GX_ASSERT(index < (m_SubresourcesCount));

                    m_Subresources[index].LinePitch  = row_bytes;
                    m_Subresources[index].SlicePitch = num_bytes;
                    m_Subresources[index].Buffer     = nullptr;
                    m_Subresources[index].Size       = num_bytes * d;
                    m_Subresources[index].MipLevel   = i;
                    m_Subresources[index].Width      = w;
                    m_Subresources[index].Height     = h;
                    m_Subresources[index].Depth      = d;

                    [[maybe_unused]] size_t const subsize = PixelFormatProperties::GetStorageSize(
                        m_PixelFormat,
                        w,
                        h,
                        d,
                        0);

                    GX_ASSERT(subsize == m_Subresources[index].Size);

                    ++index;

                    w = std::max<uint32_t>(1, w >> 1);
                    h = std::max<uint32_t>(1, h >> 1);
                    d = std::max<uint32_t>(1, d >> 1);
                }
            }
        }

        GX_ASSERT(index == m_SubresourcesCount);

        size_t total_size = 0;
        for (size_t i = 0; i < m_SubresourcesCount; ++i)
        {
            total_size += m_Subresources[i].Size;
        }

        GX_ASSERT(total_size != 0);

        m_BufferSize = total_size;
        m_Buffer     = std::make_unique<uint8_t[]>(m_BufferSize);

        uint8_t* buffer = m_Buffer.get();

        for (size_t i = 0; i < m_SubresourcesCount; ++i)
        {
            m_Subresources[i].Buffer = buffer;

            buffer += m_Subresources[i].Size;
        }
    }
}
