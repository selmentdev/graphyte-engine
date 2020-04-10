#include <catch2/catch.hpp>
#include <Graphyte/Random.hxx>
#include <Graphyte/Ieee754.hxx>

TEST_CASE("Float Traits")
{
    using Graphyte::FloatTraits;

    SECTION("float")
    {
        using Trait = FloatTraits<float>;

        SECTION("Basics")
        {
            CHECK(Trait::ToBits(0.0f) == 0u);
            CHECK(Trait::ToBits(1.0f) == Trait::One);
            CHECK(Trait::ToBits(2.0f) == 0x4000'0000);
        }

        SECTION("Range12FromHighBits")
        {
            float const one = Trait::Range12FromHighBits(0u);
            float const almost_two = Trait::Range12FromHighBits(0xFFFFFFFFu);
            float const exact_two = std::nexttowardf(almost_two, 10.0f);

            CHECK(one == 1.0f);
            CHECK(almost_two < 2.0f);
            CHECK(exact_two == 2.0f);
        }
    }

    SECTION("double")
    {
        using Trait = FloatTraits<double>;

        SECTION("Basics")
        {
            CHECK(Trait::ToBits(0.0) == 0u);
            CHECK(Trait::ToBits(1.0) == Trait::One);
        }

        SECTION("Range01FromHighBits")
        {
            double const one = Trait::Range12FromHighBits(0u);
            double const almost_two = Trait::Range12FromHighBits(0xFFFFFFFF'FFFFFFFFu);
            double const exact_two = std::nexttoward(almost_two, 10.0);

            CHECK(one == 1.0);
            CHECK(almost_two < 2.0);
            CHECK(exact_two == 2.0);
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

        CHECK(NextUInt64(state) == uint64_t{ 0x99EC5F36CB75F2B4u });
        CHECK(NextUInt64(state) == uint64_t{ 0xBF6E1F784956452Au });
        CHECK(NextUInt64(state) == uint64_t{ 0x1A5F849D4933E6E0u });
        CHECK(NextUInt64(state) == uint64_t{ 0x6AA594F1262D2D2Cu });
        CHECK(NextUInt64(state) == uint64_t{ 0xBBA5AD4A1F842E59u });
        CHECK(NextUInt64(state) == uint64_t{ 0xFFEF8375D9EBCACAu });
        CHECK(NextUInt64(state) == uint64_t{ 0x6C160DEED2F54C98u });
        CHECK(NextUInt64(state) == uint64_t{ 0x8920AD648FC30A3Fu });
        CHECK(NextUInt64(state) == uint64_t{ 0xDB032C0BA7539731u });
        CHECK(NextUInt64(state) == uint64_t{ 0xEB3A475A3E749A3Du });
        CHECK(NextUInt64(state) == uint64_t{ 0x1D42993FA43F2A54u });
        CHECK(NextUInt64(state) == uint64_t{ 0x11361BF526A14BB5u });
        CHECK(NextUInt64(state) == uint64_t{ 0x1B4F07A5AB3D8E9Cu });
        CHECK(NextUInt64(state) == uint64_t{ 0xA7A3257F6986DB7Fu });
        CHECK(NextUInt64(state) == uint64_t{ 0x7EFDAA95605DFC9Cu });
        CHECK(NextUInt64(state) == uint64_t{ 0x4BDE97C0A78EAAB8u });
    }

    SECTION("Generate random uint32 values")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        CHECK(NextUInt32(state) == uint32_t{ 0x5299AD82u });
        CHECK(NextUInt32(state) == uint32_t{ 0xF6385A52u });
        CHECK(NextUInt32(state) == uint32_t{ 0x536C627Du });
        CHECK(NextUInt32(state) == uint32_t{ 0x4C88B9DDu });
        CHECK(NextUInt32(state) == uint32_t{ 0xA4218313u });
        CHECK(NextUInt32(state) == uint32_t{ 0x260449BFu });
        CHECK(NextUInt32(state) == uint32_t{ 0xBEE34176u });
        CHECK(NextUInt32(state) == uint32_t{ 0x06E3A75Bu });
        CHECK(NextUInt32(state) == uint32_t{ 0x7C50BB3Au });
        CHECK(NextUInt32(state) == uint32_t{ 0xD54EDD67u });
        CHECK(NextUInt32(state) == uint32_t{ 0xB97DB36Bu });
        CHECK(NextUInt32(state) == uint32_t{ 0x37975040u });
        CHECK(NextUInt32(state) == uint32_t{ 0xB0728939u });
        CHECK(NextUInt32(state) == uint32_t{ 0xCE25FE00u });
        CHECK(NextUInt32(state) == uint32_t{ 0x1EA05609u });
        CHECK(NextUInt32(state) == uint32_t{ 0xEC503D78u });
    }

    SECTION("Generate random uint32 values between 10 and 22")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 15 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 16 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 20 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 14 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 15 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 16 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 22 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 14 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 13 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 15 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 13 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 16 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 17 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 22 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 14 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 18 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 20 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 18 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 18 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 19 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 20 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 15 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 22 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 22 });
        CHECK(NextUInt32(state, 10, 22) == uint32_t{ 11 });
    }

    SECTION("Next<uint32_t> follows uniform distribution")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        std::array<uint64_t, 32> histogram{};

        for (uint64_t i = 0; i < 10'000'000u; ++i)
        {
            size_t index = NextUInt32(state, 0, 31);
            ++histogram[index];
        }

        uint64_t total{};

        for (auto const& hist : histogram)
        {
            CHECK(hist == Approx{ 310'000 }.margin(3'650));
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
            float const sample = NextFloat(state, 1'000.0f);
            size_t const index = static_cast<size_t>(sample);

            ++histogram[index];
        }

        uint64_t total{};

        for (auto const& hist : histogram)
        {
            CHECK(hist == Approx{ 1'000'000 }.margin(3'700));
            total += hist;
        }

        REQUIRE(total == 1'000'000'000u);
    }

    SECTION("Generating random bytes")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        std::array<uint64_t, 8> buffer{};

        Generate(state, notstd::as_writable_bytes(notstd::span<uint64_t>{ buffer } ));

        CHECK(buffer[0] == 0x99EC5F36CB75F2B4u);
        CHECK(buffer[1] == 0xBF6E1F784956452Au);
        CHECK(buffer[2] == 0x1A5F849D4933E6E0u);
        CHECK(buffer[3] == 0x6AA594F1262D2D2Cu);
        CHECK(buffer[4] == 0xBBA5AD4A1F842E59u);
        CHECK(buffer[5] == 0xFFEF8375D9EBCACAu);
        CHECK(buffer[6] == 0x6C160DEED2F54C98u);
        CHECK(buffer[7] == 0x8920AD648FC30A3Fu);
    }

    SECTION("Float4 from random state")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        Graphyte::Float4 const sample = NextFloat4(state);

        CHECK(Graphyte::FloatTraits<float>::ToBits(sample.X) == 0x3F4B75F2u);
        CHECK(Graphyte::FloatTraits<float>::ToBits(sample.Y) == 0x3E92AC88u);
        CHECK(Graphyte::FloatTraits<float>::ToBits(sample.Z) == 0x3F19EC5Eu);
        CHECK(Graphyte::FloatTraits<float>::ToBits(sample.W) == 0x3F3F6E1Eu);
    }
}
