#include "Graphics.pch.hxx"
#include <Graphyte/Graphics/ImageHistogram.hxx>
#include <Graphyte/Maths.hxx>

namespace Graphyte::Graphics
{
    bool ImageHistogram::Compute(
        ImageHistogram& histogram,
        const std::unique_ptr<Image>& image
    ) noexcept
    {
        for (auto& channel : histogram.Channels)
        {
            std::fill(std::begin(channel), std::end(channel), 0);
        }

        if (image == nullptr)
        {
            return false;
        }

        if (image->GetPixelFormat() != PixelFormat::B8G8R8A8_UNORM)
        {
            return false;
        }

        ImagePixels* subresource = image->GetSubresource(0);

        if (subresource == nullptr)
        {
            return false;
        }

        for (uint32_t row = 0; row < subresource->Height; ++row)
        {
            uint32_t const* scanline = subresource->GetScanline<uint32_t>(row);

            for (uint32_t col = 0; col < subresource->Width; ++col)
            {
                union
                {
                    struct
                    {
                        uint8_t b;
                        uint8_t g;
                        uint8_t r;
                        uint8_t a;
                    };
                    uint32_t value;
                } u;

                u.value = scanline[col];

                histogram.Add(u.r, u.g, u.b, u.a);
            }
        }

        return true;
    }
}
