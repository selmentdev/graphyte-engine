#pragma once
#include <GxGraphics/Graphics.module.hxx>
#include <GxGraphics/Graphics/Image.hxx>
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Status.hxx>

namespace Graphyte::Graphics
{
    class GRAPHICS_API ImageCodec
    {
    public:
        ImageCodec() noexcept;
        virtual ~ImageCodec() noexcept;

    public:
        virtual Status Decode(Storage::Archive& archive, std::unique_ptr<Image>& out_image) noexcept = 0;
        virtual Status Encode(const std::unique_ptr<Image>& image, Storage::Archive& archive) noexcept = 0;
    };
}
