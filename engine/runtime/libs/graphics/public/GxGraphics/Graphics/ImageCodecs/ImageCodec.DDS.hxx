#pragma once
#include <GxGraphics/Graphics/ImageCodec.hxx>

namespace Graphyte::Graphics
{
    class GRAPHICS_API ImageCodecDDS : public ImageCodec
    {
    public:
        ImageCodecDDS() noexcept;
        virtual ~ImageCodecDDS() noexcept;

    public:
        virtual Status Decode(Storage::Archive& archive, std::unique_ptr<Image>& out_image) noexcept override;
        virtual Status Encode(const std::unique_ptr<Image>& image, Storage::Archive& archive) noexcept override;
    };
}
