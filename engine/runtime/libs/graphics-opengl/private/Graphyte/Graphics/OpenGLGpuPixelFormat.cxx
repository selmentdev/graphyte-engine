#include <Graphyte/Graphics/PixelFormat.hxx>
#include "OpenGLGpuPixelFormat.hxx"

namespace Graphyte::Graphics
{
    namespace Impl
    {
        constexpr static struct PixelFormatMapping final
        {
            PixelFormat Format;
            GLenum InternalFormat;
            GLenum NativeFormat;
            GLenum NativeType;
            GLboolean Compressed;
        } GPixelFormatMapping[] = {
            { PixelFormat::UNKNOWN,                 GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::R8_UNORM,                GL_R8,                              GL_RED,             GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8_SNORM,                GL_R8_SNORM,                        GL_RED,             GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8_UINT,                 GL_R8UI,                            GL_RED,             GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8_SINT,                 GL_R8I,                             GL_RED,             GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::A8_UNORM,                GL_R8UI,                            GL_RED,             GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R16_FLOAT,               GL_R16F,                            GL_RED,             GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16_UNORM,               GL_R16,                             GL_RED,             GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16_SNORM,               GL_R16_SNORM,                       GL_RED,             GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16_UINT,                GL_R16UI,                           GL_RED,             GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16_SINT,                GL_R16I,                            GL_RED,             GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R32_FLOAT,               GL_R32F,                            GL_RED,             GL_FLOAT,                   GL_FALSE, },
            { PixelFormat::R32_UINT,                GL_R32UI,                           GL_RED,             GL_UNSIGNED_INT,            GL_FALSE, },
            { PixelFormat::R32_SINT,                GL_R32I,                            GL_RED,             GL_INT,                     GL_FALSE, },
            { PixelFormat::R8G8_UNORM,              GL_RG8,                             GL_RG,              GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8_SNORM,              GL_RG8_SNORM,                       GL_RG,              GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8_UINT,               GL_RG8UI,                           GL_RG,              GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8_SINT,               GL_RG8I,                            GL_RG,              GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R16G16_FLOAT,            GL_RG16F,                           GL_RG,              GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16_UNORM,            GL_RG16,                            GL_RG,              GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16_SNORM,            GL_RG16_SNORM,                      GL_RG,              GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16_UINT,             GL_RG16UI,                          GL_RG,              GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16_SINT,             GL_RG16I,                           GL_RG,              GL_SHORT,                   GL_FALSE, },
            { PixelFormat::R32G32_FLOAT,            GL_RG32F,                           GL_RG,              GL_FLOAT,                   GL_FALSE, },
            { PixelFormat::R32G32_UINT,             GL_RG32UI,                          GL_RG,              GL_UNSIGNED_INT,            GL_FALSE, },
            { PixelFormat::R32G32_SINT,             GL_RG32I,                           GL_RG,              GL_INT,                     GL_FALSE, },
            { PixelFormat::B5G6R5_UNORM,            GL_RGB565,                          GL_RGB,             GL_UNSIGNED_SHORT_5_6_5,    GL_FALSE, },
            { PixelFormat::B5G5R5A1_UNORM,          GL_RGB5_A1,                         GL_RGBA,            GL_UNSIGNED_SHORT_5_5_5_1,  GL_FALSE, },
            { PixelFormat::R11G11B10_FLOAT,         GL_R11F_G11F_B10F,                  GL_RGB,             GL_UNSIGNED_INT,            GL_FALSE, },
            { PixelFormat::B8G8R8A8_UNORM,          GL_RGBA8,                           GL_BGRA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::B8G8R8A8_UNORM_SRGB,     GL_RGBA8,                           GL_BGRA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::B8G8R8X8_UNORM,          GL_RGBA8,                           GL_BGRA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8B8A8_UNORM,          GL_RGBA8,                           GL_RGBA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8B8A8_SNORM,          GL_RGBA8_SNORM,                     GL_RGBA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8B8A8_UINT,           GL_RGBA8UI,                         GL_RGBA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R8G8B8A8_SINT,           GL_RGBA8I,                          GL_RGBA,            GL_UNSIGNED_BYTE,           GL_FALSE, },
            { PixelFormat::R10G10B10A2_UNORM,       GL_RGB10_A2,                        GL_RGBA,            GL_UNSIGNED_INT_10_10_10_2, GL_FALSE, },
            { PixelFormat::R10G10B10A2_UINT,        GL_RGB10_A2UI,                      GL_RGBA,            GL_UNSIGNED_INT_10_10_10_2, GL_FALSE, },
            { PixelFormat::R16G16B16A16_FLOAT,      GL_RGBA16F,                         GL_RGBA,            GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16B16A16_UNORM,      GL_RGBA16,                          GL_RGBA,            GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16B16A16_SNORM,      GL_RGBA16_SNORM,                    GL_RGBA,            GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16B16A16_UINT,       GL_RGBA16UI,                        GL_RGBA,            GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R16G16B16A16_SINT,       GL_RGBA16I,                         GL_RGBA,            GL_UNSIGNED_SHORT,          GL_FALSE, },
            { PixelFormat::R32G32B32A32_FLOAT,      GL_RGBA32F,                         GL_RGBA,            GL_FLOAT,                   GL_FALSE, },
            { PixelFormat::R32G32B32A32_UINT,       GL_RGBA32UI,                        GL_RGBA,            GL_UNSIGNED_INT,            GL_FALSE, },
            { PixelFormat::R32G32B32A32_SINT,       GL_RGBA32I,                         GL_RGBA,            GL_INT,                     GL_FALSE, },
            { PixelFormat::D16_UNORM,               GL_DEPTH_COMPONENT16,               GL_DEPTH_COMPONENT, GL_NONE,                    GL_FALSE, },
            { PixelFormat::D24_UNORM_S8_UINT,       GL_DEPTH24_STENCIL8,                GL_DEPTH_COMPONENT, GL_NONE,                    GL_FALSE, },
            { PixelFormat::D32_FLOAT,               GL_DEPTH_COMPONENT32F,              GL_DEPTH_COMPONENT, GL_NONE,                    GL_FALSE, },
            { PixelFormat::D32_FLOAT_S8X24_UINT,    GL_DEPTH32F_STENCIL8,               GL_DEPTH_COMPONENT, GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC1_UNORM,               GL_COMPRESSED_RGB_S3TC_DXT1_EXT,    GL_NONE,            GL_NONE,                    GL_TRUE,  },
            { PixelFormat::BC2_UNORM,               GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,   GL_NONE,            GL_NONE,                    GL_TRUE,  },
            { PixelFormat::BC3_UNORM,               GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,   GL_NONE,            GL_NONE,                    GL_TRUE,  },
            { PixelFormat::BC4_SNORM,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC4_UNORM,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC5_SNORM,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC5_UNORM,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC6H_SF16,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC6H_UF16,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
            { PixelFormat::BC7_UNORM,               GL_NONE,                            GL_NONE,            GL_NONE,                    GL_FALSE, },
        };
    }


    PixelFormat OpenGLGpuGetPixelFormat(
        GLenum internal_format
    ) noexcept
    {
        (void)internal_format;
        return PixelFormat::UNKNOWN;
    }

    PixelFormat OpenGLGpuGetPixelFormat(
        GLenum format,
        GLenum type
    ) noexcept
    {
        (void)format;
        (void)type;
        return PixelFormat::UNKNOWN;
    }

    bool OpenGLGpuGetPixelFormat(
        PixelFormat pixel_format,
        GLenum& internal_format,
        GLboolean& compressed
    ) noexcept
    {
        auto result = std::find_if(
            std::begin(Impl::GPixelFormatMapping),
            std::end(Impl::GPixelFormatMapping),
            [&](const Impl::PixelFormatMapping& mapping) -> bool
            {
                return mapping.Format == pixel_format;
            }
        );

        if (result != std::end(Impl::GPixelFormatMapping))
        {
            internal_format = result->InternalFormat;
            compressed = result->Compressed;
            return true;
        }

        return false;
    }

    bool OpenGLGpuGetPixelFormat(
        PixelFormat pixel_format,
        GLenum& format,
        GLenum& type
    ) noexcept
    {
        auto result = std::find_if(
            std::begin(Impl::GPixelFormatMapping),
            std::end(Impl::GPixelFormatMapping),
            [&](const Impl::PixelFormatMapping& mapping) -> bool
            {
                return mapping.Format == pixel_format;
            }
        );

        if (result != std::end(Impl::GPixelFormatMapping))
        {
            format = result->NativeFormat;
            type = result->NativeType;
            return true;
        }

        return false;
    }
}
