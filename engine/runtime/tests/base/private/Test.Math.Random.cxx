#include <catch2/catch.hpp>
#if false
#include <Graphyte/Maths/Random.hxx>

TEST_CASE("Default random number generator")
{
    using namespace Graphyte::Maths;

    Random::DefaultRandom g;

    static constexpr const uint32_t data[4][16]
    {
        {
            0x49997b83U, 0x96ff1ae6U, 0xcd934781U, 0xdd4f33e3U, 0xca8eac6bU, 0xe0a5f0bbU, 0xd926e864U, 0xbfa33351U,
            0xb830acdcU, 0x7237800cU, 0xc4702af4U, 0xbd92ba17U, 0x3906758aU, 0xe568dfe2U, 0x5cec4dc2U, 0xbc62c801U,
        }, {
            0x59997ba2U, 0x867f1ec7U, 0x5d1343a0U, 0x4dcf37c2U, 0x5a0ea84aU, 0x7025f49aU, 0x49a6ec45U, 0x2f233770U,
            0x28b0a8fdU, 0xe2b6001dU, 0xd653aec5U, 0xfbf1ae26U, 0x357561bbU, 0xab1bcbd3U, 0x501f5df3U, 0xb091d830U,
        }, {
            0x69d97b81U, 0xbebf1ae4U, 0xe5d34783U, 0xf50f33e1U, 0xe2ceac69U, 0xc8e5f0b9U, 0xf166e866U, 0x97e33353U,
            0x9070acdeU, 0x5a348c6eU, 0x75f72296U, 0x8414b275U, 0x00807de8U, 0xdcaed780U, 0x652a45a0U, 0x85a4c063U,
        }, {
            0x79d97ba0U, 0xae3f1ec5U, 0x755343a2U, 0x658f37c0U, 0x724ea848U, 0x5865f498U, 0x61e6ec47U, 0x07633772U,
            0x00f0a8ffU, 0xcab50c7fU, 0x67d4a6a7U, 0xc277a644U, 0x0cf369d9U, 0x92ddc3b1U, 0x69d95591U, 0x8957d052U,
        },
    };

    for (size_t i = 0; i < 4; ++i)
    {
        uint64_t seed = static_cast<uint64_t>(i);

        g.Randomize(seed);

        for (size_t j = 0; j < 16; ++j)
        {
            uint32_t sample = data[i][j];

            CHECK(g.Sample32() == sample);
        }
    }
}

TEST_CASE("Uniform distribution - unsigned types")
{
    using namespace Graphyte::Maths;

    struct LinearGenerator final
    {
        uint32_t State;

        uint32_t Sample32() noexcept
        {
            return State++;
        }
    } g;

    SECTION("Linear progression")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g) == 0);
        CHECK(Random::NextUInt32(g) == 1);
        CHECK(Random::NextUInt32(g) == 2);
        CHECK(Random::NextUInt32(g) == 3);
        CHECK(Random::NextUInt32(g) == 4);
        CHECK(Random::NextUInt32(g) == 5);
        CHECK(Random::NextUInt32(g) == 6);
        CHECK(Random::NextUInt32(g) == 7);
    }

    SECTION("Wrap around")
    {
        g.State = 0xffff'fffc;
        CHECK(Random::NextUInt32(g) == 0xffff'fffcU);
        CHECK(Random::NextUInt32(g) == 0xffff'fffdU);
        CHECK(Random::NextUInt32(g) == 0xffff'fffeU);
        CHECK(Random::NextUInt32(g) == 0xffff'ffffU);
        CHECK(Random::NextUInt32(g) == 0x0000'0000U);
        CHECK(Random::NextUInt32(g) == 0x0000'0001U);
        CHECK(Random::NextUInt32(g) == 0x0000'0002U);
        CHECK(Random::NextUInt32(g) == 0x0000'0003U);
    }

    SECTION("Bound 0")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 0) == 0);
        CHECK(Random::NextUInt32(g, 0) == 0);
        CHECK(Random::NextUInt32(g, 0) == 0);
        CHECK(Random::NextUInt32(g, 0) == 0);
    }

    SECTION("Bound 1")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 1) == 0);
        CHECK(Random::NextUInt32(g, 1) == 1);
        CHECK(Random::NextUInt32(g, 1) == 0);
        CHECK(Random::NextUInt32(g, 1) == 1);
    }

    SECTION("Bound 2")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 2) == 0);
        CHECK(Random::NextUInt32(g, 2) == 1);
        CHECK(Random::NextUInt32(g, 2) == 2);
        CHECK(Random::NextUInt32(g, 2) == 0);
        CHECK(Random::NextUInt32(g, 2) == 1);
        CHECK(Random::NextUInt32(g, 2) == 2);
    }

    SECTION("Bound 3")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 3) == 0);
        CHECK(Random::NextUInt32(g, 3) == 1);
        CHECK(Random::NextUInt32(g, 3) == 2);
        CHECK(Random::NextUInt32(g, 3) == 3);
        CHECK(Random::NextUInt32(g, 3) == 0);
        CHECK(Random::NextUInt32(g, 3) == 1);
        CHECK(Random::NextUInt32(g, 3) == 2);
        CHECK(Random::NextUInt32(g, 3) == 3);
        CHECK(Random::NextUInt32(g, 3) == 0);
    }

    SECTION("Bound 4")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 4) == 0);
        CHECK(Random::NextUInt32(g, 4) == 1);
        CHECK(Random::NextUInt32(g, 4) == 2);
        CHECK(Random::NextUInt32(g, 4) == 3);
        CHECK(Random::NextUInt32(g, 4) == 4);
        CHECK(Random::NextUInt32(g, 4) == 0);
        CHECK(Random::NextUInt32(g, 4) == 1);
        CHECK(Random::NextUInt32(g, 4) == 2);
        CHECK(Random::NextUInt32(g, 4) == 3);
        CHECK(Random::NextUInt32(g, 4) == 4);
        CHECK(Random::NextUInt32(g, 4) == 0);
        CHECK(Random::NextUInt32(g, 4) == 1);
    }

    SECTION("Range bound")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'fffc);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'fffd);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'fffe);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'ffff);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'fffc);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'fffd);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'fffe);
        CHECK(Random::NextUInt32(g, 0xffff'fffc, 0xffff'ffff) == 0xffff'ffff);
    }

    SECTION("Other range bound")
    {
        g.State = 0;
        CHECK(Random::NextUInt32(g, 2, 4) == 2);
        CHECK(Random::NextUInt32(g, 2, 4) == 3);
        CHECK(Random::NextUInt32(g, 2, 4) == 4);
        CHECK(Random::NextUInt32(g, 2, 4) == 2);
        CHECK(Random::NextUInt32(g, 2, 4) == 3);
        CHECK(Random::NextUInt32(g, 2, 4) == 4);
        CHECK(Random::NextUInt32(g, 2, 4) == 2);
    }

}

TEST_CASE("Uniform distribution - float types")
{
    using namespace Graphyte::Maths;
 
    struct LinearGenerator final
    {
        uint32_t Index;

        uint32_t Sample32() noexcept
        {
            uint32_t i = Index++ & 15;
            return i * 0x1111'1111;
        }
    } g;

    g.Index = 0;

    SECTION("Uniform float progression")
    {
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(0.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(1.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(2.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(3.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(4.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(5.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(6.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(7.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(8.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(9.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(10.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(11.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(12.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(13.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(14.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(15.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(0.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(1.0F));
        CHECK(Random::NextFloat(g, 0.0F, 15.0F) == Approx(2.0F));
    }
}

static double compute_entropy(const void* data, size_t size) noexcept
{
    std::array<uint64_t, 256> histogram{};

    auto const* it = reinterpret_cast<const uint8_t*>(data);

    for (size_t i = 0; i < size; ++i, ++it)
    {
        ++histogram[*it];
    }

    auto entropy = 0.0;

    for (auto&& value : histogram)
    {
        if (value != 0)
        {
            auto freq = static_cast<double>(value) / static_cast<double>(size);
            entropy -= freq * std::log2(freq);
        }
    }

    return entropy;
}

TEST_CASE("Entropy")
{
    Graphyte::Maths::Random::DefaultRandom g{};
    g.Randomize(1);

    std::vector<uint64_t> data{};
    for (size_t i = 0; i < (1 << 20); ++i)
    {
        data.push_back(g.Sample64());
    }

    auto entropy = compute_entropy(data.data(), std::size(data) * sizeof(uint64_t));
    CHECK(entropy == Approx(8.0).epsilon(0.001));
}
#endif
