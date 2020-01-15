#include "Test.Base.pch.hxx"
#include <Graphyte/Random.hxx>

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

        CHECK(Generate(state) == uint64_t{ 0x53175d61490b23dfu });
        CHECK(Generate(state) == uint64_t{ 0x61da6f3dc380d507u });
        CHECK(Generate(state) == uint64_t{ 0x5c0fdf91ec9a7bfcu });
        CHECK(Generate(state) == uint64_t{ 0x02eebf8c3bbe5e1au });
        CHECK(Generate(state) == uint64_t{ 0x7eca04ebaf4a5eeau });
        CHECK(Generate(state) == uint64_t{ 0x0543c37757f08d9au });
        CHECK(Generate(state) == uint64_t{ 0xdb7490c75ab5026eu });
        CHECK(Generate(state) == uint64_t{ 0xd87343e6464bc959u });
        CHECK(Generate(state) == uint64_t{ 0x4b7da0a02389f0ffu });
        CHECK(Generate(state) == uint64_t{ 0x1300fc58c0424c16u });
        CHECK(Generate(state) == uint64_t{ 0x5084843206c19968u });
        CHECK(Generate(state) == uint64_t{ 0x10ea073de9aa4dfcu });
        CHECK(Generate(state) == uint64_t{ 0x1aae554343960cc1u });
        CHECK(Generate(state) == uint64_t{ 0x1804139f10fae720u });
        CHECK(Generate(state) == uint64_t{ 0x10d790e7b8ac10fau });
        CHECK(Generate(state) == uint64_t{ 0x667d2bffdd1496f7u });
    }
}
