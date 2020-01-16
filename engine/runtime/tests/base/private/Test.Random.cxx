#include "Test.Base.pch.hxx"
#include <Graphyte/Random.hxx>
#include <Graphyte/Ieee754.hxx>

/// Random number between range [0;1)
GX_NOINLINE
float NextF32(Graphyte::Random::RandomState& state) noexcept
{
    // Generate sample from range 1.0f..2.0f
    uint32_t const sample
        = Graphyte::FloatTraits<float>::One
        | Graphyte::FloatTraits<float>::Mantissa & Graphyte::Random::Generate32(state);

    float const range = Graphyte::FloatTraits<float>::FromBits(sample);
    return range - 1.0f;
}

double NextF64(Graphyte::Random::RandomState& state) noexcept
{
    // Generate sample from range 1.0..2.0
    uint64_t const sample
        = Graphyte::FloatTraits<double>::One
        | Graphyte::FloatTraits<double>::Mantissa & Graphyte::Random::Generate64(state);

    double const range = Graphyte::FloatTraits<double>::FromBits(sample);
    return range - 1.0;
}

TEST_CASE("Floating point assumptions")
{
    using namespace Graphyte;

    SECTION("float")
    {
        SECTION("perfect 1.0f")
        {
            uint32_t const sample
                = FloatTraits<float>::One
                | FloatTraits<float>::Mantissa & 0x0000'0000u;

            float const value = FloatTraits<float>::FromBits(sample);

            REQUIRE(value == 1.0f);
            REQUIRE(FloatTraits<float>::ToBits(1.0f) == 0x3F80'0000u);
        }

        SECTION("perfect 2.0f")
        {
            uint32_t const sample
                = FloatTraits<float>::One
                | FloatTraits<float>::Mantissa & 0xFFFF'FFFFu;

            REQUIRE(sample == 0x3FFF'FFFFu);

            float const value = FloatTraits<float>::FromBits(sample);

            REQUIRE(value < 2.0f);

            uint32_t const perfect_sample = sample + 1;

            float const perfect_value = FloatTraits<float>::FromBits(perfect_sample);

            REQUIRE(perfect_value == 2.0f);
            REQUIRE((perfect_value - 1.0f) == 1.0f);

            REQUIRE(FloatTraits<float>::ToBits(2.0f) == 0x4000'0000u);
            REQUIRE(FloatTraits<float>::ToBits(std::nextafter(2.0f, 1.0f)) == 0x3FFF'FFFFu);
        }
    }

    SECTION("double")
    {
        SECTION("perfect 1.0")
        {
            uint64_t const sample
                = FloatTraits<double>::One
                | FloatTraits<double>::Mantissa & 0x0000'0000'0000'0000u;

            double const value = FloatTraits<double>::FromBits(sample);

            REQUIRE(value == 1.0);
        }

        SECTION("perfect 2.0")
        {
            uint64_t const sample
                = FloatTraits<double>::One
                | FloatTraits<double>::Mantissa & 0xFFFF'FFFF'FFFF'FFFFu;

            double const value = FloatTraits<double>::FromBits(sample);

            REQUIRE(value < 2.0);

            uint64_t const perfect_sample = sample + 1;

            double const perfect_value = FloatTraits<double>::FromBits(perfect_sample);

            REQUIRE(perfect_value == 2.0);
            REQUIRE((perfect_value - 1.0) == 1.0);
        }
    }
}

TEST_CASE("Random Generator")
{
    SECTION("Split Mix 64 PRNG for key expansion for xoroshiro")
    {
        uint64_t key = 0;

        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xE220A8397B1DCDAFU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x6E789E6AA1B965F4U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x06C45D188009454FU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xF88BB8A8724C81ECU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x1B39896A51A8749BU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x53CB9F0C747EA2EAU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x2C829ABE1F4532E1U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xC584133AC916AB3CU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x3EE5789041C98AC3U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xF3B8488C368CB0A6U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x657EECDD3CB13D09U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xC2D326E0055BDEF6U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x8621A03FE0BBDB7BU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x8E1F7555983AA92FU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xB54E0F1600CC4D19U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x84BB3F97971D80ABU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x7D29825C75521255U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xC3CF17102B7F7F86U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x3466E9A083914F64U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xD81A8D2B5A4485ACU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xDB01602B100B9ED7U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xA9038A921825F10DU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xEDF5F1D90DCA2F6AU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x54496AD67BD2634CU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xDD7C01D4F5407269U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x935E82F1DB4C4F7BU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x69B82EBC92233300U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x40D29EB57DE1D510U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xA2F09DABB45C6316U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xEE521D7A0F4D3872U });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0xF16952EE72F3454FU });
        CHECK(Graphyte::Random::Impl::SplitMix64(key) == uint64_t{ 0x377D35DEA8E40225U });

        CHECK(key == uint64_t{ 0xC6EF372FE94F82A0u });
    }

    SECTION("Generate N uint64 values")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        CHECK(Generate64(state) == uint64_t{ 0x53175d61490b23dfu });
        CHECK(Generate64(state) == uint64_t{ 0x61da6f3dc380d507u });
        CHECK(Generate64(state) == uint64_t{ 0x5c0fdf91ec9a7bfcu });
        CHECK(Generate64(state) == uint64_t{ 0x02eebf8c3bbe5e1au });
        CHECK(Generate64(state) == uint64_t{ 0x7eca04ebaf4a5eeau });
        CHECK(Generate64(state) == uint64_t{ 0x0543c37757f08d9au });
        CHECK(Generate64(state) == uint64_t{ 0xdb7490c75ab5026eu });
        CHECK(Generate64(state) == uint64_t{ 0xd87343e6464bc959u });
        CHECK(Generate64(state) == uint64_t{ 0x4b7da0a02389f0ffu });
        CHECK(Generate64(state) == uint64_t{ 0x1300fc58c0424c16u });
        CHECK(Generate64(state) == uint64_t{ 0x5084843206c19968u });
        CHECK(Generate64(state) == uint64_t{ 0x10ea073de9aa4dfcu });
        CHECK(Generate64(state) == uint64_t{ 0x1aae554343960cc1u });
        CHECK(Generate64(state) == uint64_t{ 0x1804139f10fae720u });
        CHECK(Generate64(state) == uint64_t{ 0x10d790e7b8ac10fau });
        CHECK(Generate64(state) == uint64_t{ 0x667d2bffdd1496f7u });
    }

    SECTION("Generate random uint32 values")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        CHECK(Next<uint32_t>(state) == uint32_t{ 0x1a1c7ebeu });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xa25aba3au });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xb095a46du });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x3950e196u });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xd1805a01u });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x52b34eedu });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x81c192a9u });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x9e388abfu });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x68f4505fu });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xd342b04eu });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x56451d5au });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xf9404ac1u });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x59385982u });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0x08fef4bfu });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xa87b801du });
        CHECK(Next<uint32_t>(state) == uint32_t{ 0xbb69bd08u });
    }

    SECTION("Generate random uint32 values between 2 and 12")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 14 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 16 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 21 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 12 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 10 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 21 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 17 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 14 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 10 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 14 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 17 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 10 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 15 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 21 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 12 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 11 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 22 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 13 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 10 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 10 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 11 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 17 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 21 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 12 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 10 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 18 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 14 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 21 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 22 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 17 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 15 });
        CHECK(Next<uint32_t>(state, 10, 22) == uint32_t{ 12 });
    }

    SECTION("Next<uint32_t> follows uniform distribution")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        std::array<uint64_t, 32> histogram{};

        for (uint64_t i = 0; i < 10'000'000u; ++i)
        {
            size_t index = Next<uint32_t>(state, 0, 31);
            ++histogram[index];
        }

        uint64_t total{};

        for (auto const& hist : histogram)
        {
            CHECK(hist == Approx{ 310'000 }.margin(3'600));
            total += hist;
        }

        REQUIRE(total == 10'000'000u);
    }

    SECTION("NextFloat follows uniform distribution")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        // split histogram into 1000 bins
        std::array<uint64_t, 1'000> histogram{};

        for (uint64_t i = 0; i < 1'000'000'000u; ++i)
        {
            float const sample = Next<float>(state, 1'000.0f);
            size_t const index = static_cast<size_t>(sample);

            ++histogram[index];
        }

        uint64_t total{};

        for (auto const& hist : histogram)
        {
            CHECK(hist == Approx{ 1'000'000 }.margin(4'000));
            total += hist;
        }

        REQUIRE(total == 1'000'000'000u);
    }
}
