#pragma once
#include <GxGraphics/Graphics/ImageCodec.hxx>

namespace Graphyte::Graphics
{
    GRAPHICS_API Status DecodeImage_DDS(
        std::unique_ptr<Image>& result,
        Storage::Archive& archive
    ) noexcept;

    GRAPHICS_API Status EncodeImage_DDS(
        Storage::Archive& archive,
        Image const& image
    ) noexcept;
}
