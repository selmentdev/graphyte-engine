#pragma once
#include <Graphyte/Graphics.module.hxx>
#include <Graphyte/Graphics/Image.hxx>
#include <Graphyte/Storage/Archive.hxx>
#include <Graphyte/Status.hxx>

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
