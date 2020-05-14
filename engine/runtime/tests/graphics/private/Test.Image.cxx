#include <catch2/catch.hpp>
#include <GxGraphics/Graphics/PixelFormat.hxx>
#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/ByteAccess.hxx>
#include <GxBase/Hash/XXHash.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxGraphics/Graphics/ImageCodecs/ImageCodec.DDS.hxx>
#include <GxBase/Storage/ArchiveMemoryReader.hxx>
#include <GxBase/Storage/ArchiveMemoryWriter.hxx>
#include <GxBase/Types.hxx>
#include <GxBase/Random.hxx>


using Graphyte::Graphics::PixelFormat;
using Graphyte::Graphics::PixelFormatProperties;
using Graphyte::Graphics::Image;
using Graphyte::Graphics::ImageDimension;
using Graphyte::Graphics::ImageAlphaMode;
using Graphyte::Graphics::ImagePixels;
using Graphyte::Graphics::CubeFace;
using Graphyte::Hash::XXHash64;
using Graphyte::ColorBGRA;
using Graphyte::Storage::ArchiveMemoryReader;
using Graphyte::Storage::ArchiveMemoryWriter;

TEST_CASE("gen-1d.dds")
{
    static constexpr std::array<const unsigned char, 172> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x05, 0x10, 0x02, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0xbf, 0xba, 0x4c, 0xcd,
        0xc8, 0x33, 0x6f, 0x2c
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 4);
    CHECK(image->GetHeight() == 1);
    CHECK(image->GetDepth() == 1);
    CHECK(image->GetDimension() == ImageDimension::Texture1D);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 1);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 1);
    CHECK(image->GetSubresourcesCount() == 2);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            auto pixels_0 = image->GetPixels(0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 1);
            CHECK(pixels_0->LinePitch == 16);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 4);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x5CF2DEB4);
            CHECK(scanline_0[1].Value == 0x66048560);
            CHECK(scanline_0[2].Value == 0x8BEBEC78);
            CHECK(scanline_0[3].Value == 0xB751C400);
        }
        {
            auto pixels_1 = image->GetPixels(0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 8);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 8);
            CHECK(pixels_1->SlicePitch == 8);
            CHECK(pixels_1->Width == 2);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCD4CBABF);
            CHECK(scanline_0[1].Value == 0x2C6F33C8);
        }
    }
}

TEST_CASE("gen-1d-array.dds")
{
    static constexpr std::array<const unsigned char, 244> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x05, 0x10, 0x02, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0xbf, 0xba, 0x4c, 0xcd,
        0xc8, 0x33, 0x6f, 0x2c, 0x9a, 0x4a, 0x5a, 0xe4, 0x69, 0x3f, 0x68, 0x79,
        0x63, 0xe9, 0x93, 0x43, 0xf7, 0xd3, 0xed, 0x88, 0xa5, 0x14, 0xf5, 0xc0,
        0x6f, 0x60, 0x46, 0xfd, 0xd9, 0xb6, 0x7b, 0x14, 0xfa, 0xda, 0xdb, 0xc2,
        0xbf, 0x29, 0xe8, 0x18, 0x57, 0x99, 0x46, 0x86, 0x64, 0xc3, 0xac, 0xac,
        0x60, 0xf1, 0x58, 0xe7, 0xf1, 0x44, 0x58, 0x8f, 0x4e, 0x25, 0x99, 0xd1,
        0x63, 0xc8, 0x0b, 0x9d, 0xe6, 0xec, 0xda, 0x2c, 0xed, 0xc4, 0x27, 0x13,
        0x1d, 0xa5, 0xf5, 0x89
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 4);
    CHECK(image->GetHeight() == 1);
    CHECK(image->GetDepth() == 1);
    CHECK(image->GetDimension() == ImageDimension::Texture1DArray);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 4);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 1);
    CHECK(image->GetSubresourcesCount() == 8);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            auto pixels_0 = image->GetPixels(0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 1);
            CHECK(pixels_0->LinePitch == 16);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 4);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x5CF2DEB4);
            CHECK(scanline_0[1].Value == 0x66048560);
            CHECK(scanline_0[2].Value == 0x8BEBEC78);
            CHECK(scanline_0[3].Value == 0xB751C400);
        }
        {
            auto pixels_1 = image->GetPixels(0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 8);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 8);
            CHECK(pixels_1->SlicePitch == 8);
            CHECK(pixels_1->Width == 2);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCD4CBABF);
            CHECK(scanline_0[1].Value == 0x2C6F33C8);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(1, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 1);
            CHECK(pixels_0->LinePitch == 16);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 4);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xE45A4A9A);
            CHECK(scanline_0[1].Value == 0x79683F69);
            CHECK(scanline_0[2].Value == 0x4393E963);
            CHECK(scanline_0[3].Value == 0x88EDD3F7);
        }
        {
            auto pixels_1 = image->GetPixels(1, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 8);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 8);
            CHECK(pixels_1->SlicePitch == 8);
            CHECK(pixels_1->Width == 2);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xC0F514A5);
            CHECK(scanline_0[1].Value == 0xFD46606F);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(2, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 1);
            CHECK(pixels_0->LinePitch == 16);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 4);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x147BB6D9);
            CHECK(scanline_0[1].Value == 0xC2DBDAFA);
            CHECK(scanline_0[2].Value == 0x18E829BF);
            CHECK(scanline_0[3].Value == 0x86469957);
        }
        {
            auto pixels_1 = image->GetPixels(2, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 8);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 8);
            CHECK(pixels_1->SlicePitch == 8);
            CHECK(pixels_1->Width == 2);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xACACC364);
            CHECK(scanline_0[1].Value == 0xE758F160);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(3, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 1);
            CHECK(pixels_0->LinePitch == 16);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 4);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x8F5844F1);
            CHECK(scanline_0[1].Value == 0xD199254E);
            CHECK(scanline_0[2].Value == 0x9D0BC863);
            CHECK(scanline_0[3].Value == 0x2CDAECE6);
        }
        {
            auto pixels_1 = image->GetPixels(3, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 8);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 8);
            CHECK(pixels_1->SlicePitch == 8);
            CHECK(pixels_1->Width == 2);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x1327C4ED);
            CHECK(scanline_0[1].Value == 0x89F5A51D);
        }
    }

}

TEST_CASE("gen-2d.dds")
{
    static constexpr std::array<const unsigned char, 168> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0xbf, 0xba, 0x4c, 0xcd
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 2);
    CHECK(image->GetHeight() == 2);
    CHECK(image->GetDepth() == 1);
    CHECK(image->GetDimension() == ImageDimension::Texture2D);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 1);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 1);
    CHECK(image->GetSubresourcesCount() == 2);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            auto pixels_0 = image->GetPixels(0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x5CF2DEB4);
            CHECK(scanline_0[1].Value == 0x66048560);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x8BEBEC78);
            CHECK(scanline_1[1].Value == 0xB751C400);
        }
        {
            auto pixels_1 = image->GetPixels(0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCD4CBABF);
        }
    }
}

TEST_CASE("gen-2d-array.dds")
{
    static constexpr std::array<const unsigned char, 188> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0xbf, 0xba, 0x4c, 0xcd,
        0x3d, 0x47, 0x01, 0x61, 0x55, 0x6f, 0xdd, 0x1c, 0xe2, 0xc3, 0x99, 0x0c,
        0xc7, 0xff, 0x14, 0x41, 0xd1, 0xa6, 0x2e, 0x07
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 2);
    CHECK(image->GetHeight() == 2);
    CHECK(image->GetDepth() == 1);
    CHECK(image->GetDimension() == ImageDimension::Texture2DArray);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 2);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 1);
    CHECK(image->GetSubresourcesCount() == 4);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            auto pixels_0 = image->GetPixels(0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x5CF2DEB4);
            CHECK(scanline_0[1].Value == 0x66048560);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x8BEBEC78);
            CHECK(scanline_1[1].Value == 0xB751C400);
        }
        {
            auto pixels_1 = image->GetPixels(0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCD4CBABF);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(1, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x6101473D);
            CHECK(scanline_0[1].Value == 0x1CDD6F55);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x0C99C3E2);
            CHECK(scanline_1[1].Value == 0x4114FFC7);
        }
        {
            auto pixels_1 = image->GetPixels(1, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x072EA6D1);
        }
    }
}

TEST_CASE("gen-2d-cube.dds")
{
    static constexpr std::array<const unsigned char, 268> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0xbf, 0xba, 0x4c, 0xcd,
        0x3d, 0x47, 0x01, 0x61, 0x55, 0x6f, 0xdd, 0x1c, 0xe2, 0xc3, 0x99, 0x0c,
        0xc7, 0xff, 0x14, 0x41, 0xd1, 0xa6, 0x2e, 0x07, 0xe7, 0x92, 0xa3, 0x88,
        0x7d, 0xaa, 0xcf, 0xf1, 0x8a, 0x82, 0x2a, 0x4d, 0x9a, 0x6a, 0x67, 0x73,
        0xbd, 0xe5, 0x2e, 0xc0, 0x23, 0x1b, 0x16, 0xca, 0x48, 0xe1, 0x45, 0x4e,
        0xc5, 0xa4, 0x7f, 0x52, 0xb4, 0xb1, 0x0d, 0xce, 0x20, 0x8a, 0x98, 0xce,
        0xf7, 0xbc, 0xfb, 0x4d, 0x99, 0x98, 0xdc, 0x49, 0xf9, 0x39, 0x9a, 0xeb,
        0x8a, 0xc2, 0x04, 0xb0, 0x24, 0xec, 0x54, 0x92, 0xc4, 0x14, 0x7e, 0x49,
        0xd2, 0xa2, 0x96, 0x1b, 0xf3, 0x64, 0x36, 0x2e, 0x5a, 0x72, 0xd9, 0x94,
        0x3b, 0x72, 0xaa, 0x97
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 2);
    CHECK(image->GetHeight() == 2);
    CHECK(image->GetDepth() == 1);
    CHECK(image->GetDimension() == ImageDimension::TextureCube);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 1);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 6);
    CHECK(image->GetSubresourcesCount() == 12);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            auto pixels_0 = image->GetPixels(CubeFace::PositiveX, 0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x5CF2DEB4);
            CHECK(scanline_0[1].Value == 0x66048560);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x8BEBEC78);
            CHECK(scanline_1[1].Value == 0xB751C400);
        }
        {
            auto pixels_1 = image->GetPixels(CubeFace::PositiveX, 0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCD4CBABF);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(CubeFace::NegativeX, 0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x6101473D);
            CHECK(scanline_0[1].Value == 0x1CDD6F55);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x0C99C3E2);
            CHECK(scanline_1[1].Value == 0x4114FFC7);
        }
        {
            auto pixels_1 = image->GetPixels(CubeFace::NegativeX, 0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x072EA6D1);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(CubeFace::PositiveY, 0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x88A392E7);
            CHECK(scanline_0[1].Value == 0xF1CFAA7D);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x4D2A828A);
            CHECK(scanline_1[1].Value == 0x73676A9A);
        }
        {
            auto pixels_1 = image->GetPixels(CubeFace::PositiveY, 0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xC02EE5BD);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(CubeFace::NegativeY, 0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCA161B23);
            CHECK(scanline_0[1].Value == 0x4E45E148);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x527FA4C5);
            CHECK(scanline_1[1].Value == 0xCE0DB1B4);
        }
        {
            auto pixels_1 = image->GetPixels(CubeFace::NegativeY, 0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0xCE988A20);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(CubeFace::PositiveZ, 0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x4DFBBCF7);
            CHECK(scanline_0[1].Value == 0x49DC9899);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0xEB9A39F9);
            CHECK(scanline_1[1].Value == 0xB004C28A);
        }
        {
            auto pixels_1 = image->GetPixels(CubeFace::PositiveZ, 0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x9254EC24);
        }
    }
    {
        {
            auto pixels_0 = image->GetPixels(CubeFace::NegativeZ, 0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 1);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 16);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x497E14C4);
            CHECK(scanline_0[1].Value == 0x1B96A2D2);

            auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
            CHECK(scanline_1[0].Value == 0x2E3664F3);
            CHECK(scanline_1[1].Value == 0x94D9725A);
        }
        {
            auto pixels_1 = image->GetPixels(CubeFace::NegativeZ, 0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
            CHECK(scanline_0[0].Value == 0x97AA723B);
        }
    }
}

TEST_CASE("gen-2d-cube-array.dds")
{
    static constexpr std::array<const unsigned char, 388> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0xbf, 0xba, 0x4c, 0xcd,
        0x3d, 0x47, 0x01, 0x61, 0x55, 0x6f, 0xdd, 0x1c, 0xe2, 0xc3, 0x99, 0x0c,
        0xc7, 0xff, 0x14, 0x41, 0xd1, 0xa6, 0x2e, 0x07, 0xe7, 0x92, 0xa3, 0x88,
        0x7d, 0xaa, 0xcf, 0xf1, 0x8a, 0x82, 0x2a, 0x4d, 0x9a, 0x6a, 0x67, 0x73,
        0xbd, 0xe5, 0x2e, 0xc0, 0x23, 0x1b, 0x16, 0xca, 0x48, 0xe1, 0x45, 0x4e,
        0xc5, 0xa4, 0x7f, 0x52, 0xb4, 0xb1, 0x0d, 0xce, 0x20, 0x8a, 0x98, 0xce,
        0xf7, 0xbc, 0xfb, 0x4d, 0x99, 0x98, 0xdc, 0x49, 0xf9, 0x39, 0x9a, 0xeb,
        0x8a, 0xc2, 0x04, 0xb0, 0x24, 0xec, 0x54, 0x92, 0xc4, 0x14, 0x7e, 0x49,
        0xd2, 0xa2, 0x96, 0x1b, 0xf3, 0x64, 0x36, 0x2e, 0x5a, 0x72, 0xd9, 0x94,
        0x3b, 0x72, 0xaa, 0x97, 0xf9, 0xe0, 0x0d, 0x2d, 0x3d, 0xdb, 0x26, 0x5a,
        0x37, 0xb5, 0x75, 0xa3, 0xb6, 0xcd, 0xab, 0x4a, 0x52, 0xa8, 0x70, 0xcd,
        0x70, 0x5a, 0x87, 0xa7, 0x29, 0x9a, 0xa3, 0xf4, 0x43, 0xab, 0xe0, 0x9d,
        0xf1, 0xb6, 0x0c, 0x67, 0xdd, 0x52, 0xaf, 0xcf, 0x9c, 0xca, 0xac, 0x34,
        0xe2, 0x3c, 0x17, 0x26, 0x0c, 0x06, 0x10, 0x2f, 0xa6, 0xe1, 0x04, 0x75,
        0xd8, 0xbe, 0xc9, 0x84, 0xed, 0x48, 0x6d, 0x7e, 0xd5, 0xaf, 0xde, 0xb8,
        0x38, 0xab, 0xb2, 0x7f, 0x32, 0x4a, 0x13, 0xd5, 0xc4, 0x91, 0x4f, 0x3e,
        0xf7, 0x88, 0x39, 0xda, 0xa4, 0xba, 0x75, 0x4c, 0x50, 0x95, 0x90, 0x08,
        0xef, 0xed, 0x3d, 0x7f, 0x15, 0x3e, 0xdd, 0xaf, 0xe1, 0x09, 0x0e, 0x20,
        0xf7, 0x42, 0xf7, 0x12, 0x6c, 0xb3, 0x3e, 0x9d, 0x4e, 0x59, 0x65, 0xcb,
        0x50, 0x3e, 0xf0, 0x8e
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 2);
    CHECK(image->GetHeight() == 2);
    CHECK(image->GetDepth() == 1);
    CHECK(image->GetDimension() == ImageDimension::TextureCubeArray);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 2);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 6);
    CHECK(image->GetSubresourcesCount() == 24);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::PositiveX, 0, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x5CF2DEB4);
                CHECK(scanline_0[1].Value == 0x66048560);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x8BEBEC78);
                CHECK(scanline_1[1].Value == 0xB751C400);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::PositiveX, 0, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xCD4CBABF);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::NegativeX, 0, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x6101473D);
                CHECK(scanline_0[1].Value == 0x1CDD6F55);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x0C99C3E2);
                CHECK(scanline_1[1].Value == 0x4114FFC7);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::NegativeX, 0, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x072EA6D1);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::PositiveY, 0, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x88A392E7);
                CHECK(scanline_0[1].Value == 0xF1CFAA7D);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x4D2A828A);
                CHECK(scanline_1[1].Value == 0x73676A9A);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::PositiveY, 0, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xC02EE5BD);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::NegativeY, 0, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xCA161B23);
                CHECK(scanline_0[1].Value == 0x4E45E148);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x527FA4C5);
                CHECK(scanline_1[1].Value == 0xCE0DB1B4);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::NegativeY, 0, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xCE988A20);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::PositiveZ, 0, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x4DFBBCF7);
                CHECK(scanline_0[1].Value == 0x49DC9899);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0xEB9A39F9);
                CHECK(scanline_1[1].Value == 0xB004C28A);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::PositiveZ, 0, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x9254EC24);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::NegativeZ, 0, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x497E14C4);
                CHECK(scanline_0[1].Value == 0x1B96A2D2);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x2E3664F3);
                CHECK(scanline_1[1].Value == 0x94D9725A);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::NegativeZ, 0, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x97AA723B);
            }
        }
    }
    {
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::PositiveX, 1, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x2D0DE0F9);
                CHECK(scanline_0[1].Value == 0x5A26DB3D);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0xA375B537);
                CHECK(scanline_1[1].Value == 0x4AABCDB6);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::PositiveX, 1, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xCD70A852);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::NegativeX, 1, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xA7875A70);
                CHECK(scanline_0[1].Value == 0xF4A39A29);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x9DE0AB43);
                CHECK(scanline_1[1].Value == 0x670CB6F1);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::NegativeX, 1, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xCFAF52DD);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::PositiveY, 1, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x34ACCA9C);
                CHECK(scanline_0[1].Value == 0x26173CE2);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x2F10060C);
                CHECK(scanline_1[1].Value == 0x7504E1A6);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::PositiveY, 1, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x84C9BED8);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::NegativeY, 1, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x7E6D48ED);
                CHECK(scanline_0[1].Value == 0xB8DEAFD5);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x7FB2AB38);
                CHECK(scanline_1[1].Value == 0xD5134A32);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::NegativeY, 1, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x3E4F91C4);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::PositiveZ, 1, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xDA3988F7);
                CHECK(scanline_0[1].Value == 0x4C75BAA4);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x08909550);
                CHECK(scanline_1[1].Value == 0x7F3DEDEF);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::PositiveZ, 1, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0xAFDD3E15);
            }
        }
        {
            {
                auto pixels_0 = image->GetPixels(CubeFace::NegativeZ, 1, 0);
                REQUIRE(pixels_0 != nullptr);
                CHECK(pixels_0->Buffer != nullptr);
                CHECK(pixels_0->Depth == 1);
                CHECK(pixels_0->Height == 2);
                CHECK(pixels_0->LinePitch == 8);
                CHECK(pixels_0->MipLevel == 0);
                CHECK(pixels_0->Size == 16);
                CHECK(pixels_0->SlicePitch == 16);
                CHECK(pixels_0->Width == 2);

                auto scanline_0 = pixels_0->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x200E09E1);
                CHECK(scanline_0[1].Value == 0x12F742F7);

                auto scanline_1 = pixels_0->GetPixels<ColorBGRA>(1);
                CHECK(scanline_1[0].Value == 0x9D3EB36C);
                CHECK(scanline_1[1].Value == 0xCB65594E);
            }
            {
                auto pixels_1 = image->GetPixels(CubeFace::NegativeZ, 1, 1);
                REQUIRE(pixels_1 != nullptr);
                CHECK(pixels_1->Buffer != nullptr);
                CHECK(pixels_1->Depth == 1);
                CHECK(pixels_1->Height == 1);
                CHECK(pixels_1->LinePitch == 4);
                CHECK(pixels_1->MipLevel == 1);
                CHECK(pixels_1->Size == 4);
                CHECK(pixels_1->SlicePitch == 4);
                CHECK(pixels_1->Width == 1);

                auto scanline_0 = pixels_1->GetPixels<ColorBGRA>(0);
                CHECK(scanline_0[0].Value == 0x8EF03E50);
            }
        }
    }
}

TEST_CASE("gen-3d.dds")
{
    static constexpr std::array<const unsigned char, 184> source
    {
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x82, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x10, 0x40, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xb4, 0xde, 0xf2, 0x5c, 0x60, 0x85, 0x04, 0x66,
        0x78, 0xec, 0xeb, 0x8b, 0x00, 0xc4, 0x51, 0xb7, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xbf, 0xba, 0x4c, 0xcd
    };

    auto const source_view = notstd::as_bytes(notstd::span<const unsigned char>{ source });
    std::vector<std::byte> contents(std::begin(source_view), std::end(source_view));

    ArchiveMemoryReader reader{ contents };
    std::unique_ptr<Image> image{};

    REQUIRE(DecodeImage_DDS(image, reader) == Graphyte::Status::Success);
    CHECK(image->GetWidth() == 2);
    CHECK(image->GetHeight() == 2);
    CHECK(image->GetDepth() == 2);
    CHECK(image->GetDimension() == ImageDimension::Texture3D);
    CHECK(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);
    CHECK(image->GetArrayCount() == 1);
    CHECK(image->GetMipmapCount() == 2);
    CHECK(image->GetFacesCount() == 1);
    CHECK(image->GetSubresourcesCount() == 2);
    CHECK(image->GetAlphaMode() == ImageAlphaMode::Opaque);

    {
        {
            auto pixels_0 = image->GetPixels(0, 0);
            REQUIRE(pixels_0 != nullptr);
            CHECK(pixels_0->Buffer != nullptr);
            CHECK(pixels_0->Depth == 2);
            CHECK(pixels_0->Height == 2);
            CHECK(pixels_0->LinePitch == 8);
            CHECK(pixels_0->MipLevel == 0);
            CHECK(pixels_0->Size == 32);
            CHECK(pixels_0->SlicePitch == 16);
            CHECK(pixels_0->Width == 2);

            auto scanline_0_0 = pixels_0->GetPixels<ColorBGRA>(0, 0);
            CHECK(scanline_0_0[0].Value == 0x5CF2DEB4);
            CHECK(scanline_0_0[1].Value == 0x66048560);

            auto scanline_1_0 = pixels_0->GetPixels<ColorBGRA>(1, 0);
            CHECK(scanline_1_0[0].Value == 0x8BEBEC78);
            CHECK(scanline_1_0[1].Value == 0xB751C400);

            auto scanline_0_1 = pixels_0->GetPixels<ColorBGRA>(0, 1);
            CHECK(scanline_0_1[0].Value == 0);
            CHECK(scanline_0_1[1].Value == 0);

            auto scanline_1_1 = pixels_0->GetPixels<ColorBGRA>(1, 1);
            CHECK(scanline_1_1[0].Value == 0);
            CHECK(scanline_1_1[1].Value == 0);
        }
        {
            auto pixels_1 = image->GetPixels(0, 1);
            REQUIRE(pixels_1 != nullptr);
            CHECK(pixels_1->Buffer != nullptr);
            CHECK(pixels_1->Depth == 1);
            CHECK(pixels_1->Height == 1);
            CHECK(pixels_1->LinePitch == 4);
            CHECK(pixels_1->MipLevel == 1);
            CHECK(pixels_1->Size == 4);
            CHECK(pixels_1->SlicePitch == 4);
            CHECK(pixels_1->Width == 1);

            auto scanline_0_0 = pixels_1->GetPixels<ColorBGRA>(0, 0);
            CHECK(scanline_0_0[0].Value == 0xCD4CBABF);
        }
    }
}

TEST_CASE("image generation")
{
    auto image = Graphyte::Graphics::Image::Create2D(
        PixelFormat::B8G8R8A8_UNORM,
        4,
        4,
        2,
        1,
        ImageAlphaMode::Opaque
    );

    REQUIRE(image != nullptr);
    REQUIRE(image->GetWidth() == 4);
    REQUIRE(image->GetHeight() == 4);
    REQUIRE(image->GetDepth() == 1);
    REQUIRE(image->GetMipmapCount() == 2);
    REQUIRE(image->GetArrayCount() == 1);
    REQUIRE(image->GetAlphaMode() == ImageAlphaMode::Opaque);
    REQUIRE(image->GetPixelFormat() == PixelFormat::B8G8R8A8_UNORM);

    Graphyte::Random::RandomState state{};
    Graphyte::Random::Initialize(state, 0x2137);

    for (auto subresource : image->GetSubresources())
    {
        for (uint32_t y = 0; y < subresource.Height; ++y)
        {
            auto scanline = subresource.GetPixels<ColorBGRA>(y);

            for (uint32_t x = 0; x < scanline.size(); ++x)
            {
                auto& pixel = scanline[x];

                pixel.R = static_cast<uint8_t>(Graphyte::Random::NextUInt32(state, 0xff));
                pixel.G = static_cast<uint8_t>(Graphyte::Random::NextUInt32(state, 0xff));
                pixel.B = static_cast<uint8_t>(Graphyte::Random::NextUInt32(state, 0xff));
                pixel.A = 0xFF;
            }
        }
    }

    std::vector<std::byte> buffer{};
    ArchiveMemoryWriter writer{ buffer };

    REQUIRE(EncodeImage_DDS(writer, *image) == Graphyte::Status::Success);

    if constexpr (true)
    {
        [[maybe_unused]] auto status = Graphyte::Storage::FileManager::WriteBinary({ buffer }, "d:/test.dds");
    }

    static constexpr std::array<const unsigned char, 228> source{
        0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x57, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0xef, 0x7c, 0x56, 0xff, 0xae, 0xb4, 0x7e, 0xff, 0xca, 0xe3, 0xe2, 0xff,
        0xec, 0xa1, 0x5e, 0xff, 0x40, 0xca, 0x05, 0xff, 0xb8, 0x4b, 0x93, 0xff, 0x21, 0x9a, 0xae, 0xff,
        0xec, 0xa9, 0xee, 0xff, 0x12, 0xca, 0x09, 0xff, 0x49, 0x99, 0x1f, 0xff, 0x57, 0x39, 0x0b, 0xff,
        0x9c, 0x86, 0x3a, 0xff, 0xd6, 0x59, 0xa9, 0xff, 0xcb, 0x20, 0x4f, 0xff, 0xc2, 0xd7, 0x0a, 0xff,
        0xfd, 0x42, 0x14, 0xff, 0xbc, 0x7b, 0xeb, 0xff, 0x15, 0x9b, 0x96, 0xff, 0x1c, 0xa0, 0x94, 0xff,
        0xa7, 0xb9, 0x97, 0xff,
    };

    auto const source_view_bytes = notstd::as_bytes(notstd::span<const unsigned char>{ source });

    REQUIRE(std::equal(
        std::begin(buffer),
        std::end(buffer),
        std::begin(source_view_bytes),
        std::end(source_view_bytes)
    ));

}
