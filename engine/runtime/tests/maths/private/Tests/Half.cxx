#include "Test.Maths.pch.hxx"
#include <Graphyte/Half.hxx>

TEST_CASE("Maths / Half <-> Float conversion")
{
    using namespace Graphyte;

    float const f0 = 3.14f;
    float const f1 = -1.1e-3;
    float const f2 = BitCast<float>(FloatTraits<float>::Infinity);
    float const f3 = BitCast<float>(FloatTraits<float>::QNaN);
    float const f4 = 65500.0f;

    Half const h0{ .Value = 0x4248u }; // 3.14f
    Half const h1{ .Value = 0x9481u }; // -1.1e-3
    Half const h2{ .Value = FloatTraits<Half>::Infinity };
    Half const h3{ .Value = FloatTraits<Half>::QNaN };
    Half const h4{ .Value = 0x7BFFu };

    SECTION("Float -> Half")
    {
        CHECK(ToHalf(f0).Value == 0x4248u);
        CHECK(ToHalf(f1).Value == 0x9481u);
        CHECK(ToHalf(f2).Value == 0x7C00u);
        CHECK(ToHalf(f3).Value == 0x7E00u);
        CHECK(ToHalf(f4).Value == 0x7BFFu);
    }

    SECTION("Half -> Float")
    {
        CHECK(FromHalf(h0) == Approx{ 3.14f }.margin(0.001f));
        CHECK(FromHalf(h1) == Approx{ -1.1e-3 }.margin(0.001f));
        CHECK(std::isinf(FromHalf(h2)));
        CHECK(std::isnan(FromHalf(h3)));
        CHECK(FromHalf(h4) == Approx{ 65504.0f });
    }
}
