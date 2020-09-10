#include <catch2/catch.hpp>
#include <GxBase/Compression.hxx>

TEST_CASE("Compression")
{
    constexpr const size_t Count          = 2048;
    constexpr const size_t Iterations     = 10240;
    constexpr const uint32_t GeneratorMax = ((1U << 31) - 1);

    std::vector<std::byte> data{};

    uint32_t seed = 1337;
    auto generate = [&]() -> uint32_t {
        return seed = (seed * 1103515245 + 12345) & GeneratorMax;
    };

    for (size_t i = 0; i < Count; ++i)
    {
        data.push_back(static_cast<std::byte>(i));
    }

    for (size_t i = 0; i < Iterations; ++i)
    {
        auto li = generate() % Count;
        auto ri = generate() % Count;

        std::swap(data[li], data[ri]);
    }

    SECTION("LZ4")
    {
        std::vector<std::byte> output{};
        CHECK(Graphyte::Compression::CompressBlock(Graphyte::Compression::CompressionMethod::LZ4, output, data));

        CHECK(output.size() < data.size());
    }

    SECTION("LZ4HC")
    {
        std::vector<std::byte> output{};
        CHECK(Graphyte::Compression::CompressBlock(Graphyte::Compression::CompressionMethod::LZ4HC, output, data));

        CHECK(output.size() < data.size());
    }

#if GX_SDKS_WITH_ZLIB
    SECTION("ZLIB")
    {
        std::vector<std::byte> output{};
        CHECK(Graphyte::Compression::CompressBlock(Graphyte::Compression::CompressionMethod::Zlib, output, data));

        CHECK(output.size() < data.size());
    }
#endif
}
