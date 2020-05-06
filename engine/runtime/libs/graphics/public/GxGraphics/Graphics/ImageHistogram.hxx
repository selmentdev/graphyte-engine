#pragma once
#include <GxGraphics/Graphics/Image.hxx>

namespace Graphyte::Graphics
{
    class GRAPHICS_API ImageHistogram final
    {
    public:
        std::array<std::array<uint32_t, 256>, 4> Channels;
        uint64_t Samples;

        void Add(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept
        {
            ++Channels[0][r];
            ++Channels[1][g];
            ++Channels[2][b];
            ++Channels[3][a];
            ++Samples;
        }

    public:
        static bool Compute(ImageHistogram& histogram, const std::unique_ptr<Image>& image) noexcept;
    };
}
