#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxGraphics/Graphics/ImageCodecs/ImageCodec.DDS.hxx>

namespace Graphyte::Graphics::Impl::DDS
{
    enum struct DXGI_FORMAT : uint32_t
    {
        UNKNOWN                    = 0,
        R32G32B32A32_TYPELESS      = 1,
        R32G32B32A32_FLOAT         = 2,
        R32G32B32A32_UINT          = 3,
        R32G32B32A32_SINT          = 4,
        R32G32B32_TYPELESS         = 5,
        R32G32B32_FLOAT            = 6,
        R32G32B32_UINT             = 7,
        R32G32B32_SINT             = 8,
        R16G16B16A16_TYPELESS      = 9,
        R16G16B16A16_FLOAT         = 10,
        R16G16B16A16_UNORM         = 11,
        R16G16B16A16_UINT          = 12,
        R16G16B16A16_SNORM         = 13,
        R16G16B16A16_SINT          = 14,
        R32G32_TYPELESS            = 15,
        R32G32_FLOAT               = 16,
        R32G32_UINT                = 17,
        R32G32_SINT                = 18,
        R32G8X24_TYPELESS          = 19,
        D32_FLOAT_S8X24_UINT       = 20,
        R32_FLOAT_X8X24_TYPELESS   = 21,
        X32_TYPELESS_G8X24_UINT    = 22,
        R10G10B10A2_TYPELESS       = 23,
        R10G10B10A2_UNORM          = 24,
        R10G10B10A2_UINT           = 25,
        R11G11B10_FLOAT            = 26,
        R8G8B8A8_TYPELESS          = 27,
        R8G8B8A8_UNORM             = 28,
        R8G8B8A8_UNORM_SRGB        = 29,
        R8G8B8A8_UINT              = 30,
        R8G8B8A8_SNORM             = 31,
        R8G8B8A8_SINT              = 32,
        R16G16_TYPELESS            = 33,
        R16G16_FLOAT               = 34,
        R16G16_UNORM               = 35,
        R16G16_UINT                = 36,
        R16G16_SNORM               = 37,
        R16G16_SINT                = 38,
        R32_TYPELESS               = 39,
        D32_FLOAT                  = 40,
        R32_FLOAT                  = 41,
        R32_UINT                   = 42,
        R32_SINT                   = 43,
        R24G8_TYPELESS             = 44,
        D24_UNORM_S8_UINT          = 45,
        R24_UNORM_X8_TYPELESS      = 46,
        X24_TYPELESS_G8_UINT       = 47,
        R8G8_TYPELESS              = 48,
        R8G8_UNORM                 = 49,
        R8G8_UINT                  = 50,
        R8G8_SNORM                 = 51,
        R8G8_SINT                  = 52,
        R16_TYPELESS               = 53,
        R16_FLOAT                  = 54,
        D16_UNORM                  = 55,
        R16_UNORM                  = 56,
        R16_UINT                   = 57,
        R16_SNORM                  = 58,
        R16_SINT                   = 59,
        R8_TYPELESS                = 60,
        R8_UNORM                   = 61,
        R8_UINT                    = 62,
        R8_SNORM                   = 63,
        R8_SINT                    = 64,
        A8_UNORM                   = 65,
        R1_UNORM                   = 66,
        R9G9B9E5_SHAREDEXP         = 67,
        R8G8_B8G8_UNORM            = 68,
        G8R8_G8B8_UNORM            = 69,
        BC1_TYPELESS               = 70,
        BC1_UNORM                  = 71,
        BC1_UNORM_SRGB             = 72,
        BC2_TYPELESS               = 73,
        BC2_UNORM                  = 74,
        BC2_UNORM_SRGB             = 75,
        BC3_TYPELESS               = 76,
        BC3_UNORM                  = 77,
        BC3_UNORM_SRGB             = 78,
        BC4_TYPELESS               = 79,
        BC4_UNORM                  = 80,
        BC4_SNORM                  = 81,
        BC5_TYPELESS               = 82,
        BC5_UNORM                  = 83,
        BC5_SNORM                  = 84,
        B5G6R5_UNORM               = 85,
        B5G5R5A1_UNORM             = 86,
        B8G8R8A8_UNORM             = 87,
        B8G8R8X8_UNORM             = 88,
        R10G10B10_XR_BIAS_A2_UNORM = 89,
        B8G8R8A8_TYPELESS          = 90,
        B8G8R8A8_UNORM_SRGB        = 91,
        B8G8R8X8_TYPELESS          = 92,
        B8G8R8X8_UNORM_SRGB        = 93,
        BC6H_TYPELESS              = 94,
        BC6H_UF16                  = 95,
        BC6H_SF16                  = 96,
        BC7_TYPELESS               = 97,
        BC7_UNORM                  = 98,
        BC7_UNORM_SRGB             = 99,
        AYUV                       = 100,
        Y410                       = 101,
        Y416                       = 102,
        NV12                       = 103,
        P010                       = 104,
        P016                       = 105,
        OPAQUE_420                 = 106,
        YUY2                       = 107,
        Y210                       = 108,
        Y216                       = 109,
        NV11                       = 110,
        AI44                       = 111,
        IA44                       = 112,
        P8                         = 113,
        A8P8                       = 114,
        B4G4R4A4_UNORM             = 115,
        P208                       = 130,
        V208                       = 131,
        V408                       = 132,
    };

    static inline PixelFormat ConvertPixelFormat(DXGI_FORMAT format) noexcept
    {
        switch (format)
        {
            case DXGI_FORMAT::UNKNOWN:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R32G32B32A32_TYPELESS:
                return PixelFormat::R32G32B32A32_FLOAT;
            case DXGI_FORMAT::R32G32B32A32_FLOAT:
                return PixelFormat::R32G32B32A32_FLOAT;
            case DXGI_FORMAT::R32G32B32A32_UINT:
                return PixelFormat::R32G32B32A32_UINT;
            case DXGI_FORMAT::R32G32B32A32_SINT:
                return PixelFormat::R32G32B32A32_SINT;
            case DXGI_FORMAT::R32G32B32_TYPELESS:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R32G32B32_FLOAT:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R32G32B32_UINT:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R32G32B32_SINT:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R16G16B16A16_TYPELESS:
                return PixelFormat::R16G16B16A16_FLOAT;
            case DXGI_FORMAT::R16G16B16A16_FLOAT:
                return PixelFormat::R16G16B16A16_FLOAT;
            case DXGI_FORMAT::R16G16B16A16_UNORM:
                return PixelFormat::R16G16B16A16_UNORM;
            case DXGI_FORMAT::R16G16B16A16_UINT:
                return PixelFormat::R16G16B16A16_UINT;
            case DXGI_FORMAT::R16G16B16A16_SNORM:
                return PixelFormat::R16G16B16A16_SNORM;
            case DXGI_FORMAT::R16G16B16A16_SINT:
                return PixelFormat::R16G16B16A16_SINT;
            case DXGI_FORMAT::R32G32_TYPELESS:
                return PixelFormat::R32G32_FLOAT;
            case DXGI_FORMAT::R32G32_FLOAT:
                return PixelFormat::R32G32_FLOAT;
            case DXGI_FORMAT::R32G32_UINT:
                return PixelFormat::R32G32_UINT;
            case DXGI_FORMAT::R32G32_SINT:
                return PixelFormat::R32G32_SINT;
            case DXGI_FORMAT::R32G8X24_TYPELESS:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::D32_FLOAT_S8X24_UINT:
                return PixelFormat::D32_FLOAT_S8X24_UINT;
            case DXGI_FORMAT::R32_FLOAT_X8X24_TYPELESS:
                return PixelFormat::D32_FLOAT_S8X24_UINT;
            case DXGI_FORMAT::X32_TYPELESS_G8X24_UINT:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R10G10B10A2_TYPELESS:
                return PixelFormat::R10G10B10A2_UNORM;
            case DXGI_FORMAT::R10G10B10A2_UNORM:
                return PixelFormat::R10G10B10A2_UNORM;
            case DXGI_FORMAT::R10G10B10A2_UINT:
                return PixelFormat::R10G10B10A2_UINT;
            case DXGI_FORMAT::R11G11B10_FLOAT:
                return PixelFormat::R11G11B10_FLOAT;
            case DXGI_FORMAT::R8G8B8A8_TYPELESS:
                return PixelFormat::R8G8B8A8_UNORM;
            case DXGI_FORMAT::R8G8B8A8_UNORM:
                return PixelFormat::R8G8B8A8_UNORM;
            case DXGI_FORMAT::R8G8B8A8_UNORM_SRGB:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R8G8B8A8_UINT:
                return PixelFormat::R8G8B8A8_UINT;
            case DXGI_FORMAT::R8G8B8A8_SNORM:
                return PixelFormat::R8G8B8A8_SNORM;
            case DXGI_FORMAT::R8G8B8A8_SINT:
                return PixelFormat::R8G8B8A8_SINT;
            case DXGI_FORMAT::R16G16_TYPELESS:
                return PixelFormat::R16G16_UNORM;
            case DXGI_FORMAT::R16G16_FLOAT:
                return PixelFormat::R16G16_FLOAT;
            case DXGI_FORMAT::R16G16_UNORM:
                return PixelFormat::R16G16_UNORM;
            case DXGI_FORMAT::R16G16_UINT:
                return PixelFormat::R16G16_UINT;
            case DXGI_FORMAT::R16G16_SNORM:
                return PixelFormat::R16G16_SNORM;
            case DXGI_FORMAT::R16G16_SINT:
                return PixelFormat::R16G16_SINT;
            case DXGI_FORMAT::R32_TYPELESS:
                return PixelFormat::R32_FLOAT;
            case DXGI_FORMAT::D32_FLOAT:
                return PixelFormat::D32_FLOAT;
            case DXGI_FORMAT::R32_FLOAT:
                return PixelFormat::R32_FLOAT;
            case DXGI_FORMAT::R32_UINT:
                return PixelFormat::R32_UINT;
            case DXGI_FORMAT::R32_SINT:
                return PixelFormat::R32_SINT;
            case DXGI_FORMAT::R24G8_TYPELESS:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::D24_UNORM_S8_UINT:
                return PixelFormat::D24_UNORM_S8_UINT;
            case DXGI_FORMAT::R24_UNORM_X8_TYPELESS:
                return PixelFormat::D24_UNORM_S8_UINT;
            case DXGI_FORMAT::X24_TYPELESS_G8_UINT:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R8G8_TYPELESS:
                return PixelFormat::R8G8_UNORM;
            case DXGI_FORMAT::R8G8_UNORM:
                return PixelFormat::R8G8_UNORM;
            case DXGI_FORMAT::R8G8_UINT:
                return PixelFormat::R8G8_UINT;
            case DXGI_FORMAT::R8G8_SNORM:
                return PixelFormat::R8G8_SNORM;
            case DXGI_FORMAT::R8G8_SINT:
                return PixelFormat::R8G8_SINT;
            case DXGI_FORMAT::R16_TYPELESS:
                return PixelFormat::R16_UNORM;
            case DXGI_FORMAT::R16_FLOAT:
                return PixelFormat::R16_FLOAT;
            case DXGI_FORMAT::D16_UNORM:
                return PixelFormat::D16_UNORM;
            case DXGI_FORMAT::R16_UNORM:
                return PixelFormat::R16_UNORM;
            case DXGI_FORMAT::R16_UINT:
                return PixelFormat::R16_UINT;
            case DXGI_FORMAT::R16_SNORM:
                return PixelFormat::R16_SNORM;
            case DXGI_FORMAT::R16_SINT:
                return PixelFormat::R16_SINT;
            case DXGI_FORMAT::R8_TYPELESS:
                return PixelFormat::R8_UNORM;
            case DXGI_FORMAT::R8_UNORM:
                return PixelFormat::R8_UNORM;
            case DXGI_FORMAT::R8_UINT:
                return PixelFormat::R8_UINT;
            case DXGI_FORMAT::R8_SNORM:
                return PixelFormat::R8_SNORM;
            case DXGI_FORMAT::R8_SINT:
                return PixelFormat::R8_SINT;
            case DXGI_FORMAT::A8_UNORM:
                return PixelFormat::A8_UNORM;
            case DXGI_FORMAT::R1_UNORM:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R9G9B9E5_SHAREDEXP:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::R8G8_B8G8_UNORM:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::G8R8_G8B8_UNORM:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::BC1_TYPELESS:
                return PixelFormat::BC1_UNORM;
            case DXGI_FORMAT::BC1_UNORM:
                return PixelFormat::BC1_UNORM;
            case DXGI_FORMAT::BC1_UNORM_SRGB:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::BC2_TYPELESS:
                return PixelFormat::BC2_UNORM;
            case DXGI_FORMAT::BC2_UNORM:
                return PixelFormat::BC2_UNORM;
            case DXGI_FORMAT::BC2_UNORM_SRGB:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::BC3_TYPELESS:
                return PixelFormat::BC3_UNORM;
            case DXGI_FORMAT::BC3_UNORM:
                return PixelFormat::BC3_UNORM;
            case DXGI_FORMAT::BC3_UNORM_SRGB:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::BC4_TYPELESS:
                return PixelFormat::BC4_UNORM;
            case DXGI_FORMAT::BC4_UNORM:
                return PixelFormat::BC4_UNORM;
            case DXGI_FORMAT::BC4_SNORM:
                return PixelFormat::BC4_SNORM;
            case DXGI_FORMAT::BC5_TYPELESS:
                return PixelFormat::BC5_UNORM;
            case DXGI_FORMAT::BC5_UNORM:
                return PixelFormat::BC5_UNORM;
            case DXGI_FORMAT::BC5_SNORM:
                return PixelFormat::BC5_SNORM;
            case DXGI_FORMAT::B5G6R5_UNORM:
                return PixelFormat::B5G6R5_UNORM;
            case DXGI_FORMAT::B5G5R5A1_UNORM:
                return PixelFormat::B5G5R5A1_UNORM;
            case DXGI_FORMAT::B8G8R8A8_UNORM:
                return PixelFormat::B8G8R8A8_UNORM;
            case DXGI_FORMAT::B8G8R8X8_UNORM:
                return PixelFormat::B8G8R8X8_UNORM;
            case DXGI_FORMAT::R10G10B10_XR_BIAS_A2_UNORM:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::B8G8R8A8_TYPELESS:
                return PixelFormat::B8G8R8A8_UNORM;
            case DXGI_FORMAT::B8G8R8A8_UNORM_SRGB:
                return PixelFormat::B8G8R8A8_UNORM_SRGB;
            case DXGI_FORMAT::B8G8R8X8_TYPELESS:
                return PixelFormat::B8G8R8X8_UNORM;
            case DXGI_FORMAT::B8G8R8X8_UNORM_SRGB:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::BC6H_TYPELESS:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::BC6H_UF16:
                return PixelFormat::BC6H_UF16;
            case DXGI_FORMAT::BC6H_SF16:
                return PixelFormat::BC6H_SF16;
            case DXGI_FORMAT::BC7_TYPELESS:
                return PixelFormat::BC7_UNORM;
            case DXGI_FORMAT::BC7_UNORM:
                return PixelFormat::BC7_UNORM;
            case DXGI_FORMAT::BC7_UNORM_SRGB:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::AYUV:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::Y410:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::Y416:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::NV12:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::P010:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::P016:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::OPAQUE_420:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::YUY2:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::Y210:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::Y216:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::NV11:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::AI44:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::IA44:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::P8:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::A8P8:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::B4G4R4A4_UNORM:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::P208:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::V208:
                return PixelFormat::UNKNOWN;
            case DXGI_FORMAT::V408:
                return PixelFormat::UNKNOWN;
        }
        return PixelFormat::UNKNOWN;
    }

    static inline DXGI_FORMAT ConvertPixelFormat(PixelFormat format) noexcept
    {
        switch (format)
        {
            case PixelFormat::R8_UNORM:
                return DXGI_FORMAT::R8_UNORM;
            case PixelFormat::R8_SNORM:
                return DXGI_FORMAT::R8_SNORM;
            case PixelFormat::R8_UINT:
                return DXGI_FORMAT::R8_UINT;
            case PixelFormat::R8_SINT:
                return DXGI_FORMAT::R8_SINT;
            case PixelFormat::A8_UNORM:
                return DXGI_FORMAT::A8_UNORM;
            case PixelFormat::R16_FLOAT:
                return DXGI_FORMAT::R16_FLOAT;
            case PixelFormat::R16_UNORM:
                return DXGI_FORMAT::R16_UNORM;
            case PixelFormat::R16_SNORM:
                return DXGI_FORMAT::R16_SNORM;
            case PixelFormat::R16_UINT:
                return DXGI_FORMAT::R16_UINT;
            case PixelFormat::R16_SINT:
                return DXGI_FORMAT::R16_SINT;
            case PixelFormat::R32_FLOAT:
                return DXGI_FORMAT::R32_FLOAT;
            case PixelFormat::R32_UINT:
                return DXGI_FORMAT::R32_UINT;
            case PixelFormat::R32_SINT:
                return DXGI_FORMAT::R32_SINT;
            case PixelFormat::R8G8_UNORM:
                return DXGI_FORMAT::R8G8_UNORM;
            case PixelFormat::R8G8_SNORM:
                return DXGI_FORMAT::R8G8_SNORM;
            case PixelFormat::R8G8_UINT:
                return DXGI_FORMAT::R8G8_UINT;
            case PixelFormat::R8G8_SINT:
                return DXGI_FORMAT::R8G8_SINT;
            case PixelFormat::R16G16_FLOAT:
                return DXGI_FORMAT::R16G16_FLOAT;
            case PixelFormat::R16G16_UNORM:
                return DXGI_FORMAT::R16G16_UNORM;
            case PixelFormat::R16G16_SNORM:
                return DXGI_FORMAT::R16G16_SNORM;
            case PixelFormat::R16G16_UINT:
                return DXGI_FORMAT::R16G16_UINT;
            case PixelFormat::R16G16_SINT:
                return DXGI_FORMAT::R16G16_SINT;
            case PixelFormat::R32G32_FLOAT:
                return DXGI_FORMAT::R32G32_FLOAT;
            case PixelFormat::R32G32_UINT:
                return DXGI_FORMAT::R32G32_UINT;
            case PixelFormat::R32G32_SINT:
                return DXGI_FORMAT::R32G32_SINT;
            case PixelFormat::B5G6R5_UNORM:
                return DXGI_FORMAT::B5G6R5_UNORM;
            case PixelFormat::B5G5R5A1_UNORM:
                return DXGI_FORMAT::B5G5R5A1_UNORM;
            case PixelFormat::R11G11B10_FLOAT:
                return DXGI_FORMAT::R11G11B10_FLOAT;
            case PixelFormat::B8G8R8A8_UNORM:
                return DXGI_FORMAT::B8G8R8A8_UNORM;
            case PixelFormat::B8G8R8A8_UNORM_SRGB:
                return DXGI_FORMAT::B8G8R8A8_UNORM_SRGB;
            case PixelFormat::B8G8R8X8_UNORM:
                return DXGI_FORMAT::B8G8R8X8_UNORM;
            case PixelFormat::R8G8B8A8_UNORM:
                return DXGI_FORMAT::R8G8B8A8_UNORM;
            case PixelFormat::R8G8B8A8_SNORM:
                return DXGI_FORMAT::R8G8B8A8_SNORM;
            case PixelFormat::R8G8B8A8_UINT:
                return DXGI_FORMAT::R8G8B8A8_UINT;
            case PixelFormat::R8G8B8A8_SINT:
                return DXGI_FORMAT::R8G8B8A8_SINT;
            case PixelFormat::R10G10B10A2_UNORM:
                return DXGI_FORMAT::R10G10B10A2_UNORM;
            case PixelFormat::R10G10B10A2_UINT:
                return DXGI_FORMAT::R10G10B10A2_UINT;
            case PixelFormat::R16G16B16A16_FLOAT:
                return DXGI_FORMAT::R16G16B16A16_FLOAT;
            case PixelFormat::R16G16B16A16_UNORM:
                return DXGI_FORMAT::R16G16B16A16_UNORM;
            case PixelFormat::R16G16B16A16_SNORM:
                return DXGI_FORMAT::R16G16B16A16_SNORM;
            case PixelFormat::R16G16B16A16_UINT:
                return DXGI_FORMAT::R16G16B16A16_UINT;
            case PixelFormat::R16G16B16A16_SINT:
                return DXGI_FORMAT::R16G16B16A16_SINT;
            case PixelFormat::R32G32B32A32_FLOAT:
                return DXGI_FORMAT::R32G32B32A32_FLOAT;
            case PixelFormat::R32G32B32A32_UINT:
                return DXGI_FORMAT::R32G32B32A32_UINT;
            case PixelFormat::R32G32B32A32_SINT:
                return DXGI_FORMAT::R32G32B32A32_SINT;
            case PixelFormat::D16_UNORM:
                return DXGI_FORMAT::D16_UNORM;
            case PixelFormat::D24_UNORM_S8_UINT:
                return DXGI_FORMAT::D24_UNORM_S8_UINT;
            case PixelFormat::D32_FLOAT:
                return DXGI_FORMAT::D32_FLOAT;
            case PixelFormat::D32_FLOAT_S8X24_UINT:
                return DXGI_FORMAT::D32_FLOAT_S8X24_UINT;
            case PixelFormat::BC1_UNORM:
                return DXGI_FORMAT::BC1_UNORM;
            case PixelFormat::BC2_UNORM:
                return DXGI_FORMAT::BC2_UNORM;
            case PixelFormat::BC3_UNORM:
                return DXGI_FORMAT::BC3_UNORM;
            case PixelFormat::BC4_SNORM:
                return DXGI_FORMAT::BC4_SNORM;
            case PixelFormat::BC4_UNORM:
                return DXGI_FORMAT::BC4_UNORM;
            case PixelFormat::BC5_SNORM:
                return DXGI_FORMAT::BC5_SNORM;
            case PixelFormat::BC5_UNORM:
                return DXGI_FORMAT::BC5_UNORM;
            case PixelFormat::BC6H_SF16:
                return DXGI_FORMAT::BC6H_SF16;
            case PixelFormat::BC6H_UF16:
                return DXGI_FORMAT::BC6H_UF16;
            case PixelFormat::BC7_UNORM:
                return DXGI_FORMAT::BC7_UNORM;
            case PixelFormat::UNKNOWN:
                break;
        }

        return DXGI_FORMAT::UNKNOWN;
    }


    constexpr const uint32_t DDS_PIXELFORMAT_ALPHAPIXELS = 0x00000001;
    constexpr const uint32_t DDS_PIXELFORMAT_FOURCC      = 0x00000004;
    constexpr const uint32_t DDS_PIXELFORMAT_RGB         = 0x00000040;
    constexpr const uint32_t DDS_PIXELFORMAT_RGBA        = DDS_PIXELFORMAT_RGB | DDS_PIXELFORMAT_ALPHAPIXELS;
    constexpr const uint32_t DDS_PIXELFORMAT_LUMINANCE   = 0x00020000;
    constexpr const uint32_t DDS_PIXELFORMAT_LUMINANCEA  = DDS_PIXELFORMAT_LUMINANCE | DDS_PIXELFORMAT_ALPHAPIXELS;
    constexpr const uint32_t DDS_PIXELFORMAT_ALPHA       = 0x00000002;
    constexpr const uint32_t DDS_PIXELFORMAT_PAL8        = 0x00000020;
    constexpr const uint32_t DDS_PIXELFORMAT_PAL8A       = DDS_PIXELFORMAT_PAL8 | DDS_PIXELFORMAT_ALPHAPIXELS;
    constexpr const uint32_t DDS_PIXELFORMAT_BUMPDUDV    = 0x00080000;

    struct DDS_PIXELFORMAT final
    {
        uint32_t Size;
        uint32_t Flags;
        uint32_t FourCC;
        uint32_t RGBBitCount;
        uint32_t RBitMask;
        uint32_t GBitMask;
        uint32_t BBitMask;
        uint32_t ABitMask;

        constexpr bool IsBitMask(uint32_t r, uint32_t g, uint32_t b, uint32_t a) const noexcept
        {
            return RBitMask == r
                   && GBitMask == g
                   && BBitMask == b
                   && ABitMask == a;
        }
    };

    constexpr uint32_t MakeFourCC(uint8_t ch0, uint8_t ch1, uint8_t ch2, uint8_t ch3) noexcept
    {
        return static_cast<uint32_t>(static_cast<uint8_t>(ch0))
               | static_cast<uint32_t>(static_cast<uint8_t>(ch1) << 8)
               | static_cast<uint32_t>(static_cast<uint8_t>(ch2) << 16)
               | static_cast<uint32_t>(static_cast<uint8_t>(ch3) << 24);
    }

    constexpr const DDS_PIXELFORMAT DDSPF_DXT1      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('D', 'X', 'T', '1'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_DXT2      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('D', 'X', 'T', '2'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_DXT3      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('D', 'X', 'T', '3'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_DXT4      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('D', 'X', 'T', '4'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_DXT5      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('D', 'X', 'T', '5'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_BC4_UNORM = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('B', 'C', '4', 'U'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_BC4_SNORM = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('B', 'C', '4', 'S'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_BC5_UNORM = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('B', 'C', '5', 'U'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_BC5_SNORM = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('B', 'C', '5', 'S'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_R8G8_B8G8 = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('R', 'G', 'B', 'G'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_G8R8_G8B8 = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('G', 'R', 'G', 'B'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_YUY2      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('Y', 'U', 'Y', '2'), 0, 0, 0, 0, 0 };
    constexpr const DDS_PIXELFORMAT DDSPF_A8R8G8B8  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGBA, 0, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_X8R8G8B8  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGB, 0, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_A8B8G8R8  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGBA, 0, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_X8B8G8R8  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGB, 0, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0x00000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_G16R16    = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGB, 0, 32, 0x0000ffff, 0xffff0000, 0x00000000, 0x00000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_R5G6B5    = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGB, 0, 16, 0x0000f800, 0x000007e0, 0x0000001f, 0x00000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_A1R5G5B5  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGBA, 0, 16, 0x00007c00, 0x000003e0, 0x0000001f, 0x00008000 };
    constexpr const DDS_PIXELFORMAT DDSPF_A4R4G4B4  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGBA, 0, 16, 0x00000f00, 0x000000f0, 0x0000000f, 0x0000f000 };
    constexpr const DDS_PIXELFORMAT DDSPF_R8G8B8    = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_RGB, 0, 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_L8        = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_LUMINANCE, 0, 8, 0xff, 0x00, 0x00, 0x00 };
    constexpr const DDS_PIXELFORMAT DDSPF_L16       = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_LUMINANCE, 0, 16, 0xffff, 0x0000, 0x0000, 0x0000 };
    constexpr const DDS_PIXELFORMAT DDSPF_A8L8      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_LUMINANCEA, 0, 16, 0x00ff, 0x0000, 0x0000, 0xff00 };
    constexpr const DDS_PIXELFORMAT DDSPF_A8L8_ALT  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_LUMINANCEA, 0, 8, 0x00ff, 0x0000, 0x0000, 0xff00 };
    constexpr const DDS_PIXELFORMAT DDSPF_A8        = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_ALPHA, 0, 8, 0x00, 0x00, 0x00, 0xff };
    constexpr const DDS_PIXELFORMAT DDSPF_V8U8      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_BUMPDUDV, 0, 16, 0x00ff, 0xff00, 0x0000, 0x0000 };
    constexpr const DDS_PIXELFORMAT DDSPF_Q8W8V8U8  = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_BUMPDUDV, 0, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_V16U16    = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_BUMPDUDV, 0, 32, 0x0000ffff, 0xffff0000, 0x00000000, 0x00000000 };
    constexpr const DDS_PIXELFORMAT DDSPF_DX10      = { sizeof(DDS_PIXELFORMAT), DDS_PIXELFORMAT_FOURCC, MakeFourCC('D', 'X', '1', '0'), 0, 0, 0, 0, 0 };

    constexpr const uint32_t D3DFMT_ATI1          = MakeFourCC('A', 'T', 'I', '1');
    constexpr const uint32_t D3DFMT_ATI2          = MakeFourCC('A', 'T', 'I', '2');
    constexpr const uint32_t D3DFMT_BC4S          = MakeFourCC('B', 'C', '4', 'S');
    constexpr const uint32_t D3DFMT_BC4U          = MakeFourCC('B', 'C', '4', 'U');
    constexpr const uint32_t D3DFMT_BC5S          = MakeFourCC('B', 'C', '5', 'S');
    constexpr const uint32_t D3DFMT_BC5U          = MakeFourCC('B', 'C', '5', 'U');
    constexpr const uint32_t D3DFMT_DXT1          = MakeFourCC('D', 'X', 'T', '1');
    constexpr const uint32_t D3DFMT_DXT2          = MakeFourCC('D', 'X', 'T', '2');
    constexpr const uint32_t D3DFMT_DXT3          = MakeFourCC('D', 'X', 'T', '3');
    constexpr const uint32_t D3DFMT_DXT4          = MakeFourCC('D', 'X', 'T', '4');
    constexpr const uint32_t D3DFMT_DXT5          = MakeFourCC('D', 'X', 'T', '5');
    constexpr const uint32_t D3DFMT_GRGB          = MakeFourCC('G', 'R', 'G', 'B');
    constexpr const uint32_t D3DFMT_RGBG          = MakeFourCC('R', 'G', 'B', 'G');
    constexpr const uint32_t D3DFMT_YUY2          = MakeFourCC('Y', 'U', 'Y', '2');
    constexpr const uint32_t D3DFMT_A16B16G16R16  = 36;
    constexpr const uint32_t D3DFMT_Q16W16V16U16  = 110;
    constexpr const uint32_t D3DFMT_R16F          = 111;
    constexpr const uint32_t D3DFMT_G16R16F       = 112;
    constexpr const uint32_t D3DFMT_A16B16G16R16F = 113;
    constexpr const uint32_t D3DFMT_R32F          = 114;
    constexpr const uint32_t D3DFMT_G32R32F       = 115;
    constexpr const uint32_t D3DFMT_A32B32G32R32F = 116;

    constexpr const uint32_t DDS_HEADER_SIGNATURE = 0x20534444;

    constexpr const uint32_t DDS_HEADER_CAPS        = 0x1;
    constexpr const uint32_t DDS_HEADER_HEIGHT      = 0x2;
    constexpr const uint32_t DDS_HEADER_WIDTH       = 0x4;
    constexpr const uint32_t DDS_HEADER_PITCH       = 0x8;
    constexpr const uint32_t DDS_HEADER_PIXELFORMAT = 0x1000;
    constexpr const uint32_t DDS_HEADER_MIPMAP      = 0x20000;
    constexpr const uint32_t DDS_HEADER_LINEARSIZE  = 0x80000;
    constexpr const uint32_t DDS_HEADER_VOLUME      = 0x800000;

    constexpr const uint32_t DDS_HEADER_TEXTURE
        = DDS_HEADER_CAPS
          | DDS_HEADER_HEIGHT
          | DDS_HEADER_WIDTH
          | DDS_HEADER_PIXELFORMAT;

    constexpr const uint32_t DDS_SURFACE_TEXTURE = 0x1000;
    constexpr const uint32_t DDS_SURFACE_MIPMAP  = 0x400008;
    constexpr const uint32_t DDS_SURFACE_CUBEMAP = 0x8;

    constexpr const uint32_t DDS_CUBEMAP           = 0x200;
    constexpr const uint32_t DDS_CUBEMAP_POSITIVEX = 0x600;
    constexpr const uint32_t DDS_CUBEMAP_NEGATIVEX = 0xa00;
    constexpr const uint32_t DDS_CUBEMAP_POSITIVEY = 0x1200;
    constexpr const uint32_t DDS_CUBEMAP_NEGATIVEY = 0x2200;
    constexpr const uint32_t DDS_CUBEMAP_POSITIVEZ = 0x4200;
    constexpr const uint32_t DDS_CUBEMAP_NEGATIVEZ = 0x8200;

    constexpr const uint32_t DDS_CUBEMAP_ALLFACES = DDS_CUBEMAP_POSITIVEX | DDS_CUBEMAP_NEGATIVEX | DDS_CUBEMAP_POSITIVEY | DDS_CUBEMAP_NEGATIVEY | DDS_CUBEMAP_POSITIVEZ | DDS_CUBEMAP_NEGATIVEZ;

    constexpr const uint32_t DDS_CUBEMAP_VOLUME = 0x200000;

    struct DDS_HEADER final
    {
        uint32_t Size;
        uint32_t Flags;
        uint32_t Height;
        uint32_t Width;
        uint32_t PitchOrLinearSize;
        uint32_t Depth;
        uint32_t MipMapCount;
        uint32_t Reserved1[11];
        DDS_PIXELFORMAT PixelFormat;
        uint32_t Surface;
        uint32_t Cubemap;
        uint32_t Caps3;
        uint32_t Caps4;
        uint32_t Reserved2;
    };
    static_assert(sizeof(DDS_HEADER) == 124);

    constexpr const uint32_t DDS_RESOURCE_DIMENSION_TEXTURE_1D = 2;
    constexpr const uint32_t DDS_RESOURCE_DIMENSION_TEXTURE_2D = 3;
    constexpr const uint32_t DDS_RESOURCE_DIMENSION_TEXTURE_3D = 4;

    constexpr const uint32_t DDS_RESOURCE_MISC_FLAG_TEXTURE_CUBE = 0x4;

    constexpr const uint32_t DDS_ALPHA_MODE_UNKNOWN       = 0;
    constexpr const uint32_t DDS_ALPHA_MODE_STRAIGHT      = 1;
    constexpr const uint32_t DDS_ALPHA_MODE_PREMULTIPLIED = 2;
    constexpr const uint32_t DDS_ALPHA_MODE_OPAQUE        = 3;
    constexpr const uint32_t DDS_ALPHA_MODE_CUSTOM        = 4;

    constexpr const uint32_t DDS_MISC_FLAGS2_ALPHA_MODE_MASK = 7;

    struct DDS_HEADER_DXT10 final
    {
        DXGI_FORMAT Format;
        uint32_t ResourceDimension;
        uint32_t MiscFlags;
        uint32_t ArraySize;
        uint32_t MiscFlags2;
    };
    static_assert(sizeof(DDS_HEADER_DXT10) == 20);


    size_t BitsPerPixel(DXGI_FORMAT format) noexcept
    {
        switch (format)
        {
            case DXGI_FORMAT::R32G32B32A32_TYPELESS:
            case DXGI_FORMAT::R32G32B32A32_FLOAT:
            case DXGI_FORMAT::R32G32B32A32_UINT:
            case DXGI_FORMAT::R32G32B32A32_SINT:
                return 128;

            case DXGI_FORMAT::R32G32B32_TYPELESS:
            case DXGI_FORMAT::R32G32B32_FLOAT:
            case DXGI_FORMAT::R32G32B32_UINT:
            case DXGI_FORMAT::R32G32B32_SINT:
                return 96;

            case DXGI_FORMAT::R16G16B16A16_TYPELESS:
            case DXGI_FORMAT::R16G16B16A16_FLOAT:
            case DXGI_FORMAT::R16G16B16A16_UNORM:
            case DXGI_FORMAT::R16G16B16A16_UINT:
            case DXGI_FORMAT::R16G16B16A16_SNORM:
            case DXGI_FORMAT::R16G16B16A16_SINT:
            case DXGI_FORMAT::R32G32_TYPELESS:
            case DXGI_FORMAT::R32G32_FLOAT:
            case DXGI_FORMAT::R32G32_UINT:
            case DXGI_FORMAT::R32G32_SINT:
            case DXGI_FORMAT::R32G8X24_TYPELESS:
            case DXGI_FORMAT::D32_FLOAT_S8X24_UINT:
            case DXGI_FORMAT::R32_FLOAT_X8X24_TYPELESS:
            case DXGI_FORMAT::X32_TYPELESS_G8X24_UINT:
            case DXGI_FORMAT::Y416:
            case DXGI_FORMAT::Y210:
            case DXGI_FORMAT::Y216:
                return 64;

            case DXGI_FORMAT::R10G10B10A2_TYPELESS:
            case DXGI_FORMAT::R10G10B10A2_UNORM:
            case DXGI_FORMAT::R10G10B10A2_UINT:
            case DXGI_FORMAT::R11G11B10_FLOAT:
            case DXGI_FORMAT::R8G8B8A8_TYPELESS:
            case DXGI_FORMAT::R8G8B8A8_UNORM:
            case DXGI_FORMAT::R8G8B8A8_UNORM_SRGB:
            case DXGI_FORMAT::R8G8B8A8_UINT:
            case DXGI_FORMAT::R8G8B8A8_SNORM:
            case DXGI_FORMAT::R8G8B8A8_SINT:
            case DXGI_FORMAT::R16G16_TYPELESS:
            case DXGI_FORMAT::R16G16_FLOAT:
            case DXGI_FORMAT::R16G16_UNORM:
            case DXGI_FORMAT::R16G16_UINT:
            case DXGI_FORMAT::R16G16_SNORM:
            case DXGI_FORMAT::R16G16_SINT:
            case DXGI_FORMAT::R32_TYPELESS:
            case DXGI_FORMAT::D32_FLOAT:
            case DXGI_FORMAT::R32_FLOAT:
            case DXGI_FORMAT::R32_UINT:
            case DXGI_FORMAT::R32_SINT:
            case DXGI_FORMAT::R24G8_TYPELESS:
            case DXGI_FORMAT::D24_UNORM_S8_UINT:
            case DXGI_FORMAT::R24_UNORM_X8_TYPELESS:
            case DXGI_FORMAT::X24_TYPELESS_G8_UINT:
            case DXGI_FORMAT::R9G9B9E5_SHAREDEXP:
            case DXGI_FORMAT::R8G8_B8G8_UNORM:
            case DXGI_FORMAT::G8R8_G8B8_UNORM:
            case DXGI_FORMAT::B8G8R8A8_UNORM:
            case DXGI_FORMAT::B8G8R8X8_UNORM:
            case DXGI_FORMAT::R10G10B10_XR_BIAS_A2_UNORM:
            case DXGI_FORMAT::B8G8R8A8_TYPELESS:
            case DXGI_FORMAT::B8G8R8A8_UNORM_SRGB:
            case DXGI_FORMAT::B8G8R8X8_TYPELESS:
            case DXGI_FORMAT::B8G8R8X8_UNORM_SRGB:
            case DXGI_FORMAT::AYUV:
            case DXGI_FORMAT::Y410:
            case DXGI_FORMAT::YUY2:
                return 32;

            case DXGI_FORMAT::P010:
            case DXGI_FORMAT::P016:
                return 24;

            case DXGI_FORMAT::R8G8_TYPELESS:
            case DXGI_FORMAT::R8G8_UNORM:
            case DXGI_FORMAT::R8G8_UINT:
            case DXGI_FORMAT::R8G8_SNORM:
            case DXGI_FORMAT::R8G8_SINT:
            case DXGI_FORMAT::R16_TYPELESS:
            case DXGI_FORMAT::R16_FLOAT:
            case DXGI_FORMAT::D16_UNORM:
            case DXGI_FORMAT::R16_UNORM:
            case DXGI_FORMAT::R16_UINT:
            case DXGI_FORMAT::R16_SNORM:
            case DXGI_FORMAT::R16_SINT:
            case DXGI_FORMAT::B5G6R5_UNORM:
            case DXGI_FORMAT::B5G5R5A1_UNORM:
            case DXGI_FORMAT::A8P8:
            case DXGI_FORMAT::B4G4R4A4_UNORM:
                return 16;

            case DXGI_FORMAT::NV12:
            case DXGI_FORMAT::OPAQUE_420:
            case DXGI_FORMAT::NV11:
                return 12;

            case DXGI_FORMAT::R8_TYPELESS:
            case DXGI_FORMAT::R8_UNORM:
            case DXGI_FORMAT::R8_UINT:
            case DXGI_FORMAT::R8_SNORM:
            case DXGI_FORMAT::R8_SINT:
            case DXGI_FORMAT::A8_UNORM:
            case DXGI_FORMAT::AI44:
            case DXGI_FORMAT::IA44:
            case DXGI_FORMAT::P8:
                return 8;

            case DXGI_FORMAT::R1_UNORM:
                return 1;

            case DXGI_FORMAT::BC1_TYPELESS:
            case DXGI_FORMAT::BC1_UNORM:
            case DXGI_FORMAT::BC1_UNORM_SRGB:
            case DXGI_FORMAT::BC4_TYPELESS:
            case DXGI_FORMAT::BC4_UNORM:
            case DXGI_FORMAT::BC4_SNORM:
                return 4;

            case DXGI_FORMAT::BC2_TYPELESS:
            case DXGI_FORMAT::BC2_UNORM:
            case DXGI_FORMAT::BC2_UNORM_SRGB:
            case DXGI_FORMAT::BC3_TYPELESS:
            case DXGI_FORMAT::BC3_UNORM:
            case DXGI_FORMAT::BC3_UNORM_SRGB:
            case DXGI_FORMAT::BC5_TYPELESS:
            case DXGI_FORMAT::BC5_UNORM:
            case DXGI_FORMAT::BC5_SNORM:
            case DXGI_FORMAT::BC6H_TYPELESS:
            case DXGI_FORMAT::BC6H_UF16:
            case DXGI_FORMAT::BC6H_SF16:
            case DXGI_FORMAT::BC7_TYPELESS:
            case DXGI_FORMAT::BC7_UNORM:
            case DXGI_FORMAT::BC7_UNORM_SRGB:
                return 8;

            default:
                return 0;
        }
    }

    DXGI_FORMAT MakeSRGB(DXGI_FORMAT format) noexcept
    {
        switch (format)
        {
            case DXGI_FORMAT::R8G8B8A8_UNORM:
                return DXGI_FORMAT::R8G8B8A8_UNORM_SRGB;

            case DXGI_FORMAT::BC1_UNORM:
                return DXGI_FORMAT::BC1_UNORM_SRGB;

            case DXGI_FORMAT::BC2_UNORM:
                return DXGI_FORMAT::BC2_UNORM_SRGB;

            case DXGI_FORMAT::BC3_UNORM:
                return DXGI_FORMAT::BC3_UNORM_SRGB;

            case DXGI_FORMAT::B8G8R8A8_UNORM:
                return DXGI_FORMAT::B8G8R8A8_UNORM_SRGB;

            case DXGI_FORMAT::B8G8R8X8_UNORM:
                return DXGI_FORMAT::B8G8R8X8_UNORM_SRGB;

            case DXGI_FORMAT::BC7_UNORM:
                return DXGI_FORMAT::BC7_UNORM_SRGB;

            default:
                return format;
        }
    }

    bool IsCompressed(DXGI_FORMAT format) noexcept
    {
        switch (format)
        {
            case DXGI_FORMAT::BC1_TYPELESS:
            case DXGI_FORMAT::BC1_UNORM:
            case DXGI_FORMAT::BC1_UNORM_SRGB:
            case DXGI_FORMAT::BC2_TYPELESS:
            case DXGI_FORMAT::BC2_UNORM:
            case DXGI_FORMAT::BC2_UNORM_SRGB:
            case DXGI_FORMAT::BC3_TYPELESS:
            case DXGI_FORMAT::BC3_UNORM:
            case DXGI_FORMAT::BC3_UNORM_SRGB:
            case DXGI_FORMAT::BC4_TYPELESS:
            case DXGI_FORMAT::BC4_UNORM:
            case DXGI_FORMAT::BC4_SNORM:
            case DXGI_FORMAT::BC5_TYPELESS:
            case DXGI_FORMAT::BC5_UNORM:
            case DXGI_FORMAT::BC5_SNORM:
            case DXGI_FORMAT::BC6H_TYPELESS:
            case DXGI_FORMAT::BC6H_UF16:
            case DXGI_FORMAT::BC6H_SF16:
            case DXGI_FORMAT::BC7_TYPELESS:
            case DXGI_FORMAT::BC7_UNORM:
            case DXGI_FORMAT::BC7_UNORM_SRGB:
                return true;

            default:
                return false;
        }
    }

    DXGI_FORMAT EnsureNotTypeless(DXGI_FORMAT format) noexcept
    {
        // Assumes UNORM or FLOAT; doesn't use UINT or SINT
        switch (format)
        {
            case DXGI_FORMAT::R32G32B32A32_TYPELESS:
                return DXGI_FORMAT::R32G32B32A32_FLOAT;
            case DXGI_FORMAT::R32G32B32_TYPELESS:
                return DXGI_FORMAT::R32G32B32_FLOAT;
            case DXGI_FORMAT::R16G16B16A16_TYPELESS:
                return DXGI_FORMAT::R16G16B16A16_UNORM;
            case DXGI_FORMAT::R32G32_TYPELESS:
                return DXGI_FORMAT::R32G32_FLOAT;
            case DXGI_FORMAT::R10G10B10A2_TYPELESS:
                return DXGI_FORMAT::R10G10B10A2_UNORM;
            case DXGI_FORMAT::R8G8B8A8_TYPELESS:
                return DXGI_FORMAT::R8G8B8A8_UNORM;
            case DXGI_FORMAT::R16G16_TYPELESS:
                return DXGI_FORMAT::R16G16_UNORM;
            case DXGI_FORMAT::R32_TYPELESS:
                return DXGI_FORMAT::R32_FLOAT;
            case DXGI_FORMAT::R8G8_TYPELESS:
                return DXGI_FORMAT::R8G8_UNORM;
            case DXGI_FORMAT::R16_TYPELESS:
                return DXGI_FORMAT::R16_UNORM;
            case DXGI_FORMAT::R8_TYPELESS:
                return DXGI_FORMAT::R8_UNORM;
            case DXGI_FORMAT::BC1_TYPELESS:
                return DXGI_FORMAT::BC1_UNORM;
            case DXGI_FORMAT::BC2_TYPELESS:
                return DXGI_FORMAT::BC2_UNORM;
            case DXGI_FORMAT::BC3_TYPELESS:
                return DXGI_FORMAT::BC3_UNORM;
            case DXGI_FORMAT::BC4_TYPELESS:
                return DXGI_FORMAT::BC4_UNORM;
            case DXGI_FORMAT::BC5_TYPELESS:
                return DXGI_FORMAT::BC5_UNORM;
            case DXGI_FORMAT::B8G8R8A8_TYPELESS:
                return DXGI_FORMAT::B8G8R8A8_UNORM;
            case DXGI_FORMAT::B8G8R8X8_TYPELESS:
                return DXGI_FORMAT::B8G8R8X8_UNORM;
            case DXGI_FORMAT::BC7_TYPELESS:
                return DXGI_FORMAT::BC7_UNORM;
            default:
                return format;
        }
    }

    DXGI_FORMAT ConvertFormat(const DDS_PIXELFORMAT& format)
    {
        if (format.Flags & DDS_PIXELFORMAT_RGB)
        {
            switch (format.RGBBitCount)
            {
                case 32:
                {
                    if (format.IsBitMask(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000))
                    {
                        return DXGI_FORMAT::R8G8B8A8_UNORM;
                    }

                    if (format.IsBitMask(0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000))
                    {
                        return DXGI_FORMAT::B8G8R8A8_UNORM;
                    }

                    if (format.IsBitMask(0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000))
                    {
                        return DXGI_FORMAT::B8G8R8X8_UNORM;
                    }

                    // No DXGI format maps to ISBITMASK(0x000000ff,0x0000ff00,0x00ff0000,0x00000000) aka D3DFMT_X8B8G8R8

                    // Note that many common DDS reader/writers (including D3DX) swap the
                    // the RED/BLUE masks for 10:10:10:2 formats. We assume
                    // below that the 'backwards' header mask is being used since it is most
                    // likely written by D3DX. The more robust solution is to use the 'DX10'
                    // header extension and specify the DXGI_FORMAT::R10G10B10A2_UNORM format directly

                    // For 'correct' writers, this should be 0x000003ff,0x000ffc00,0x3ff00000 for RGB data
                    if (format.IsBitMask(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000))
                    {
                        return DXGI_FORMAT::R10G10B10A2_UNORM;
                    }

                    // No DXGI format maps to ISBITMASK(0x000003ff,0x000ffc00,0x3ff00000,0xc0000000) aka D3DFMT_A2R10G10B10

                    if (format.IsBitMask(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000))
                    {
                        return DXGI_FORMAT::R16G16_UNORM;
                    }

                    if (format.IsBitMask(0xffffffff, 0x00000000, 0x00000000, 0x00000000))
                    {
                        // Only 32-bit color channel format in D3D9 was R32F
                        return DXGI_FORMAT::R32_FLOAT; // D3DX writes this out as a FourCC of 114
                    }
                    break;
                }

                case 24:
                {
                    break;
                }

                case 16:
                {
                    if (format.IsBitMask(0x7c00, 0x03e0, 0x001f, 0x8000))
                    {
                        return DXGI_FORMAT::B5G5R5A1_UNORM;
                    }
                    if (format.IsBitMask(0xf800, 0x07e0, 0x001f, 0x0000))
                    {
                        return DXGI_FORMAT::B5G6R5_UNORM;
                    }

                    // No DXGI format maps to ISBITMASK(0x7c00,0x03e0,0x001f,0x0000) aka D3DFMT_X1R5G5B5

                    if (format.IsBitMask(0x0f00, 0x00f0, 0x000f, 0xf000))
                    {
                        return DXGI_FORMAT::B4G4R4A4_UNORM;
                    }

                    // No DXGI format maps to ISBITMASK(0x0f00,0x00f0,0x000f,0x0000) aka D3DFMT_X4R4G4B4

                    // No 3:3:2, 3:3:2:8, or paletted DXGI formats aka D3DFMT_A8R3G3B2, D3DFMT_R3G3B2, D3DFMT_P8, D3DFMT_A8P8, etc.
                    break;
                }
            }
        }
        else if (format.Flags & DDS_PIXELFORMAT_LUMINANCE)
        {
            if (8 == format.RGBBitCount)
            {
                if (format.IsBitMask(0x000000ff, 0x00000000, 0x00000000, 0x00000000))
                {
                    return DXGI_FORMAT::R8_UNORM; // D3DX10/11 writes this out as DX10 extension
                }

                // No DXGI format maps to ISBITMASK(0x0f,0x00,0x00,0xf0) aka D3DFMT_A4L4

                if (format.IsBitMask(0x000000ff, 0x00000000, 0x00000000, 0x0000ff00))
                {
                    return DXGI_FORMAT::R8G8_UNORM; // Some DDS writers assume the bitcount should be 8 instead of 16
                }
            }

            if (16 == format.RGBBitCount)
            {
                if (format.IsBitMask(0x0000ffff, 0x00000000, 0x00000000, 0x00000000))
                {
                    return DXGI_FORMAT::R16_UNORM; // D3DX10/11 writes this out as DX10 extension
                }
                if (format.IsBitMask(0x000000ff, 0x00000000, 0x00000000, 0x0000ff00))
                {
                    return DXGI_FORMAT::R8G8_UNORM; // D3DX10/11 writes this out as DX10 extension
                }
            }
        }
        else if (format.Flags & DDS_PIXELFORMAT_ALPHA)
        {
            if (8 == format.RGBBitCount)
            {
                return DXGI_FORMAT::A8_UNORM;
            }
        }
        else if (format.Flags & DDS_PIXELFORMAT_BUMPDUDV)
        {
            if (16 == format.RGBBitCount)
            {
                if (format.IsBitMask(0x00ff, 0xff00, 0x0000, 0x0000))
                {
                    return DXGI_FORMAT::R8G8_SNORM; // D3DX10/11 writes this out as DX10 extension
                }
            }

            if (32 == format.RGBBitCount)
            {
                if (format.IsBitMask(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000))
                {
                    return DXGI_FORMAT::R8G8B8A8_SNORM; // D3DX10/11 writes this out as DX10 extension
                }
                if (format.IsBitMask(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000))
                {
                    return DXGI_FORMAT::R16G16_SNORM; // D3DX10/11 writes this out as DX10 extension
                }

                // No DXGI format maps to ISBITMASK(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000) aka D3DFMT_A2W10V10U10
            }
        }
        else if (format.Flags & DDS_PIXELFORMAT_FOURCC)
        {
            switch (format.FourCC)
            {
                case D3DFMT_DXT1:
                    return DXGI_FORMAT::BC1_UNORM;

                case D3DFMT_DXT3:
                    return DXGI_FORMAT::BC2_UNORM;
                case D3DFMT_DXT5:
                    return DXGI_FORMAT::BC3_UNORM;

                    // While pre-multiplied alpha isn't directly supported by the DXGI formats,
                    // they are basically the same as these BC formats so they can be mapped
                case D3DFMT_DXT2:
                    return DXGI_FORMAT::BC2_UNORM;
                case D3DFMT_DXT4:
                    return DXGI_FORMAT::BC3_UNORM;
                case D3DFMT_ATI1:
                    return DXGI_FORMAT::BC4_UNORM;
                case D3DFMT_BC4U:
                    return DXGI_FORMAT::BC4_UNORM;
                case D3DFMT_BC4S:
                    return DXGI_FORMAT::BC4_SNORM;
                case D3DFMT_ATI2:
                    return DXGI_FORMAT::BC5_UNORM;
                case D3DFMT_BC5U:
                    return DXGI_FORMAT::BC5_UNORM;
                case D3DFMT_BC5S:
                    return DXGI_FORMAT::BC5_SNORM;

                    // BC6H and BC7 are written using the "DX10" extended header
                case D3DFMT_RGBG:
                    return DXGI_FORMAT::R8G8_B8G8_UNORM;
                case D3DFMT_GRGB:
                    return DXGI_FORMAT::G8R8_G8B8_UNORM;

                case D3DFMT_YUY2:
                    return DXGI_FORMAT::YUY2;

                case D3DFMT_A16B16G16R16:
                    return DXGI_FORMAT::R16G16B16A16_UNORM;

                case D3DFMT_Q16W16V16U16:
                    return DXGI_FORMAT::R16G16B16A16_SNORM;

                case D3DFMT_R16F:
                    return DXGI_FORMAT::R16_FLOAT;

                case D3DFMT_G16R16F:
                    return DXGI_FORMAT::R16G16_FLOAT;

                case D3DFMT_A16B16G16R16F:
                    return DXGI_FORMAT::R16G16B16A16_FLOAT;

                case D3DFMT_R32F:
                    return DXGI_FORMAT::R32_FLOAT;

                case D3DFMT_G32R32F:
                    return DXGI_FORMAT::R32G32_FLOAT;

                case D3DFMT_A32B32G32R32F:
                    return DXGI_FORMAT::R32G32B32A32_FLOAT;
            }
        }

        return DXGI_FORMAT::UNKNOWN;
    }

    constexpr const uint32_t DDS_TEXTURE_1D_U_DIMENSION          = 16384;
    constexpr const uint32_t DDS_TEXTURE_1D_ARRAY_AXIS_DIMENSION = 2048;
    constexpr const uint32_t DDS_TEXTURE_2D_UV_DIMENSION         = 16384;
    constexpr const uint32_t DDS_TEXTURE_2D_ARRAY_AXIS_DIMENSION = 2048;
    constexpr const uint32_t DDS_TEXTURE_3D_UVW_DIMENSION        = 2048;
    constexpr const uint32_t DDS_TEXTURE_CUBE_DIMENSION          = 16384;

    static inline ImageAlphaMode ConvertAlphaMode_DXT10(uint32_t value) noexcept
    {
        switch (value)
        {
            case DDS_ALPHA_MODE_STRAIGHT:
                return ImageAlphaMode::Straight;
            case DDS_ALPHA_MODE_PREMULTIPLIED:
                return ImageAlphaMode::Premultiplied;
            case DDS_ALPHA_MODE_OPAQUE:
                return ImageAlphaMode::Opaque;
            case DDS_ALPHA_MODE_CUSTOM:
                return ImageAlphaMode::Custom;
            case DDS_ALPHA_MODE_UNKNOWN:
                break;
        }

        return ImageAlphaMode::Unknown;
    }

    static inline uint32_t ConvertAlphaMode_DXT10(ImageAlphaMode value) noexcept
    {
        switch (value)
        {
            case ImageAlphaMode::Straight:
                return DDS_ALPHA_MODE_STRAIGHT;
            case ImageAlphaMode::Premultiplied:
                return DDS_ALPHA_MODE_PREMULTIPLIED;
            case ImageAlphaMode::Opaque:
                return DDS_ALPHA_MODE_OPAQUE;
            case ImageAlphaMode::Custom:
                return DDS_ALPHA_MODE_CUSTOM;
            case ImageAlphaMode::Unknown:
                break;
        }

        return DDS_ALPHA_MODE_UNKNOWN;
    }
}


namespace Graphyte::Graphics
{
    GRAPHICS_API Status DecodeImage_DDS(
        std::unique_ptr<Image>& result,
        Storage::Archive& archive) noexcept
    {
        int64_t stream_size = archive.GetSize();

        if (stream_size < static_cast<int64_t>(sizeof(Impl::DDS::DDS_HEADER) + sizeof(uint32_t)))
        {
            return Status::InvalidFormat;
        }

        uint32_t signature{};
        archive.Serialize(&signature, sizeof(signature));

        if (signature != Impl::DDS::DDS_HEADER_SIGNATURE)
        {
            return Status::InvalidFormat;
        }

        Impl::DDS::DDS_HEADER header{};
        archive.Serialize(&header, sizeof(header));

        if (header.Size != sizeof(header) || header.PixelFormat.Size != sizeof(Impl::DDS::DDS_PIXELFORMAT))
        {
            return Status::InvalidFormat;
        }

        uint32_t width  = header.Width;
        uint32_t height = header.Height;
        uint32_t depth  = header.Depth;

        ImageDimension dimension = ImageDimension::Unknown;

        uint32_t array_size = 1;

        Impl::DDS::DXGI_FORMAT format = Impl::DDS::DXGI_FORMAT::UNKNOWN;
        bool is_cubemap               = false;

        ImageAlphaMode alpha_mode = ImageAlphaMode::Unknown;

        uint32_t mipmap_count = header.MipMapCount;

        if (mipmap_count == 0)
        {
            mipmap_count = 1;
        }

        if (stream_size < static_cast<int64_t>((sizeof(Impl::DDS::DDS_HEADER) + sizeof(uint32_t) + sizeof(Impl::DDS::DDS_HEADER_DXT10))))
        {
            return Status::InvalidFormat;
        }

        Impl::DDS::DDS_HEADER_DXT10 dxt10{};

        if ((header.PixelFormat.Flags & Impl::DDS::DDS_PIXELFORMAT_FOURCC) && (header.PixelFormat.FourCC == Impl::DDS::MakeFourCC('D', 'X', '1', '0')))
        {
            archive.Serialize(&dxt10, sizeof(dxt10));

            array_size = dxt10.ArraySize;
            alpha_mode = Impl::DDS::ConvertAlphaMode_DXT10(dxt10.MiscFlags2 & Impl::DDS::DDS_MISC_FLAGS2_ALPHA_MODE_MASK);

            if (array_size == 0)
            {
                return Status::InvalidFormat;
            }

            switch (dxt10.Format)
            {
                case Impl::DDS::DXGI_FORMAT::AI44:
                case Impl::DDS::DXGI_FORMAT::IA44:
                case Impl::DDS::DXGI_FORMAT::P8:
                case Impl::DDS::DXGI_FORMAT::A8P8:
                    return Status::InvalidFormat;

                default:
                    if (Impl::DDS::BitsPerPixel(dxt10.Format) == 0)
                    {
                        return Status::InvalidFormat;
                    }
            }

            format = dxt10.Format;

            switch (dxt10.ResourceDimension)
            {
                case Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_1D:
                {
                    if ((header.Flags & Impl::DDS::DDS_HEADER_HEIGHT) && height != 1)
                    {
                        return Status::InvalidFormat;
                    }

                    height = depth = 1;
                    dimension      = ImageDimension::Texture1D;
                    break;
                }
                case Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_2D:
                {
                    if (dxt10.MiscFlags & Impl::DDS::DDS_RESOURCE_MISC_FLAG_TEXTURE_CUBE)
                    {
                        is_cubemap = true;
                    }

                    depth     = 1;
                    dimension = ImageDimension::Texture2D;
                    break;
                }
                case Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_3D:
                {
                    if (!(header.Flags & Impl::DDS::DDS_HEADER_VOLUME))
                    {
                        return Status::InvalidFormat;
                    }

                    if (array_size > 1)
                    {
                        return Status::InvalidFormat;
                    }

                    dimension = ImageDimension::Texture3D;
                    break;
                }
                default:
                    return Status::InvalidFormat;
            }
        }
        else
        {
            format = Impl::DDS::ConvertFormat(header.PixelFormat);

            if (format == Impl::DDS::DXGI_FORMAT::UNKNOWN)
            {
                return Status::InvalidFormat;
            }

            if (header.Flags & Impl::DDS::DDS_HEADER_VOLUME)
            {
                dimension = ImageDimension::Texture3D;
            }
            else
            {
                if (header.Cubemap & Impl::DDS::DDS_CUBEMAP)
                {
                    if ((header.Cubemap & Impl::DDS::DDS_CUBEMAP_ALLFACES) != Impl::DDS::DDS_CUBEMAP_ALLFACES)
                    {
                        return Status::InvalidFormat;
                    }

                    array_size = 1;
                    is_cubemap = true;
                }

                depth     = 1;
                dimension = ImageDimension::Texture2D;
            }

            GX_ASSERT(Impl::DDS::BitsPerPixel(format) != 0);
        }

        switch (dimension)
        {
            case ImageDimension::Texture1D:
            {
                if (array_size > Impl::DDS::DDS_TEXTURE_1D_ARRAY_AXIS_DIMENSION || width > Impl::DDS::DDS_TEXTURE_1D_U_DIMENSION)
                {
                    return Status::InvalidFormat;
                }
                break;
            }
            case ImageDimension::Texture2D:
            {
                if (is_cubemap)
                {
                    if (array_size > Impl::DDS::DDS_TEXTURE_1D_ARRAY_AXIS_DIMENSION || width > Impl::DDS::DDS_TEXTURE_CUBE_DIMENSION || height > Impl::DDS::DDS_TEXTURE_CUBE_DIMENSION)
                    {
                        return Status::InvalidFormat;
                    }

                    if (width != height)
                    {
                        return Status::InvalidFormat;
                    }
                }
                else
                {
                    if (array_size > Impl::DDS::DDS_TEXTURE_1D_ARRAY_AXIS_DIMENSION || width > Impl::DDS::DDS_TEXTURE_2D_UV_DIMENSION || height > Impl::DDS::DDS_TEXTURE_2D_UV_DIMENSION)
                    {
                        return Status::InvalidFormat;
                    }
                }
                break;
            }
            case ImageDimension::Texture3D:
            {
                if (array_size > 1 || width > Impl::DDS::DDS_TEXTURE_3D_UVW_DIMENSION || height > Impl::DDS::DDS_TEXTURE_3D_UVW_DIMENSION || depth > Impl::DDS::DDS_TEXTURE_3D_UVW_DIMENSION)
                {
                    return Status::InvalidFormat;
                }
                break;
            }
            default:
            {
                return Status::InvalidFormat;
            }
        }

        PixelFormat pixel_format = Impl::DDS::ConvertPixelFormat(format);

        if (pixel_format == PixelFormat::UNKNOWN)
        {
            return Status::InvalidFormat;
        }


        std::unique_ptr<Image> image = nullptr;

        switch (dimension)
        {
            case ImageDimension::Texture1D:
            {
                image = Image::Create1D(pixel_format, width, mipmap_count, array_size, alpha_mode);
                break;
            }
            case ImageDimension::Texture2D:
            {
                if (is_cubemap)
                {
                    image = Image::CreateCube(pixel_format, width, mipmap_count, array_size, alpha_mode);
                }
                else
                {
                    image = Image::Create2D(pixel_format, width, height, mipmap_count, array_size, alpha_mode);
                }
                break;
            }
            case ImageDimension::Texture3D:
            {
                image = Image::Create3D(pixel_format, width, height, depth, mipmap_count, alpha_mode);
                break;
            }
            default:
                return Status::InvalidFormat;
        }

        if (image != nullptr)
        {
            int64_t data_size = archive.GetSize() - archive.GetPosition();
            GX_ASSERT(data_size > 0);

            int64_t buffer_size = static_cast<int64_t>(image->GetBufferSize());
            GX_ASSERT(buffer_size == data_size);

            if (buffer_size != data_size)
            {
                return Status::InvalidFormat;
            }

            size_t subresources = image->GetSubresourcesCount();

            for (size_t i = 0; i < subresources; ++i)
            {
                ImagePixels* subresource = image->GetSubresource(i);
                GX_ASSERT(subresource != nullptr);

                if (subresource == nullptr)
                {
                    return Status::InvalidFormat;
                }

                archive.Serialize(subresource->Buffer, subresource->Size);
            }
        }

        int64_t stream_position = archive.GetPosition();

        GX_ASSERTF(stream_size == stream_position, "Garbage after file content: strean-position: {}, stream-size: {}", stream_position, stream_size);

        if (stream_size != stream_position)
        {
            return Status::InvalidFormat;
        }

        result = std::move(image);
        return Status::Success;
    }

    GRAPHICS_API Status EncodeImage_DDS(
        Storage::Archive& archive,
        Image const& image) noexcept
    {
        uint32_t const mipmap_count = image.GetMipmapCount();

        if (mipmap_count == 0)
        {
            return Status::InvalidFormat;
        }

        uint32_t const array_count = image.GetArrayCount();

        if (array_count == 0)
        {
            // Image must have at least one array element - no matter of image dimension.
            return Status::InvalidFormat;
        }

        ImageDimension const dimension = image.GetDimension();

        if (!IsArray(dimension) && array_count > 1)
        {
            // This is invalid situation - non-array images must have one element.
            return Status::InvalidFormat;
        }

        PixelFormat const format = image.GetPixelFormat();

        uint32_t dxt10_resource_dimension = 0;

        uint32_t image_width    = image.GetWidth();
        uint32_t image_height   = image.GetHeight();
        uint32_t image_depth    = image.GetDepth();
        uint32_t header_cubemap = 0;

        uint32_t header_surface = Impl::DDS::DDS_SURFACE_TEXTURE;
        uint32_t header_flags   = Impl::DDS::DDS_HEADER_CAPS | Impl::DDS::DDS_HEADER_PIXELFORMAT;

        if (mipmap_count > 1)
        {
            header_flags |= Impl::DDS::DDS_HEADER_MIPMAP;
            header_surface |= Impl::DDS::DDS_SURFACE_MIPMAP;
        }

        switch (dimension)
        {
            case ImageDimension::Texture1DArray:
            case ImageDimension::Texture1D:
            {
                dxt10_resource_dimension = Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_1D;
                GX_ASSERT(image_height == 1);
                GX_ASSERT(image_depth == 1);
                image_height = 1;
                image_depth  = 1;
                header_flags |= Impl::DDS::DDS_HEADER_WIDTH;
                break;
            }
            case ImageDimension::Texture2D:
            case ImageDimension::Texture2DArray:
            {
                dxt10_resource_dimension = Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_2D;
                GX_ASSERT(image_depth == 1);
                image_depth = 1;
                header_flags |= Impl::DDS::DDS_HEADER_WIDTH | Impl::DDS::DDS_HEADER_HEIGHT;
                break;
            }
            case ImageDimension::TextureCube:
            case ImageDimension::TextureCubeArray:
            {
                dxt10_resource_dimension = Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_2D;
                GX_ASSERT(image_depth == 1);
                image_depth = 1;
                header_flags |= Impl::DDS::DDS_HEADER_WIDTH | Impl::DDS::DDS_HEADER_HEIGHT;
                header_surface |= Impl::DDS::DDS_SURFACE_CUBEMAP;
                header_cubemap = Impl::DDS::DDS_CUBEMAP_ALLFACES;

                GX_ASSERT(image_width == image_height);

                if (image_width != image_height)
                {
                    return Status::InvalidFormat;
                }

                break;
            }
            case ImageDimension::Texture3D:
            {
                dxt10_resource_dimension = Impl::DDS::DDS_RESOURCE_DIMENSION_TEXTURE_3D;
                GX_ASSERT(array_count == 1);
                if (array_count != 1)
                {
                    return Status::InvalidFormat;
                }

                image_width  = image.GetWidth();
                image_height = image.GetHeight();
                image_depth  = image.GetDepth();
                header_flags |= Impl::DDS::DDS_HEADER_WIDTH | Impl::DDS::DDS_HEADER_HEIGHT | Impl::DDS::DDS_HEADER_VOLUME;
                header_cubemap |= Impl::DDS::DDS_CUBEMAP_VOLUME;
                break;
            }

            default:
            case ImageDimension::Unknown:
            {
                return Status::InvalidFormat;
            }
        }


        Impl::DDS::DDS_HEADER header{
            .Size        = sizeof(header),
            .Flags       = header_flags,
            .Height      = image_height,
            .Width       = image_width,
            .Depth       = image_depth,
            .MipMapCount = mipmap_count,
            .PixelFormat = Impl::DDS::DDSPF_DX10,
            .Surface     = header_surface,
            .Cubemap     = header_cubemap,
        };

        uint32_t const dxt10_misc_flags = IsCube(dimension)
                                              ? Impl::DDS::DDS_RESOURCE_MISC_FLAG_TEXTURE_CUBE
                                              : 0;

        Impl::DDS::DDS_HEADER_DXT10 dxt10{
            .Format            = Impl::DDS::ConvertPixelFormat(format),
            .ResourceDimension = dxt10_resource_dimension,
            .MiscFlags         = dxt10_misc_flags,
            .ArraySize         = array_count,
            .MiscFlags2        = Impl::DDS::ConvertAlphaMode_DXT10(image.GetAlphaMode()),
        };


        uint32_t signature = Impl::DDS::DDS_HEADER_SIGNATURE;
        archive.Serialize(&signature, sizeof(signature));
        archive.Serialize(&header, sizeof(header));
        archive.Serialize(&dxt10, sizeof(dxt10));

        for (size_t i = 0; i < image.GetSubresourcesCount(); ++i)
        {
            ImagePixels const* subresource = image.GetSubresource(i);
            GX_ASSERT(subresource != nullptr);

            archive.Serialize(subresource->Buffer, subresource->Size);
        }

        return Status::Success;
    }
}
