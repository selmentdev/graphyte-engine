#pragma once
#include <GxGraphics/Graphics.module.hxx>
#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Status.hxx>

namespace Graphyte::Graphics
{
    using DecodeImageFn = Status(std::unique_ptr<Image>& result, Storage::Archive& archive) noexcept;
    using EncodeImageFn = Status(Storage::Archive& archive, Image const& image) noexcept;
}
