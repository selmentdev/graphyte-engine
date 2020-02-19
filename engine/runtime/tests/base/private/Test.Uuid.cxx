#include <catch2/catch.hpp>
#include <Graphyte/Uuid.hxx>

TEST_CASE("Uuid")
{
    using namespace Graphyte;

    SECTION("Empty")
    {
        Uuid empty{};

        REQUIRE(empty.Low == 0);
        REQUIRE(empty.High == 0);

        std::string str{};
        REQUIRE(Converter<Uuid>::ToString(str, empty));
        REQUIRE(str == "00000000000000000000000000000000");
    }

    SECTION("Parsing")
    {
        Uuid parsed{};
        REQUIRE(Converter<Uuid>::FromString(parsed, "00000000000000000000000000000000"));
        REQUIRE(parsed.Low == 0);
        REQUIRE(parsed.High == 0);

        REQUIRE(parsed == Uuid{});
    }

    SECTION("Some random uuid")
    {
        Uuid value{ 0xdeadbeefdeadc0de, 0xbeefcacecafebabe, };

        std::string str{};
        REQUIRE(Converter<Uuid>::ToString(str, value));
        REQUIRE(str == "deadbeefdeadc0debeefcacecafebabe");
    }

    SECTION("Ordering")
    {
        Uuid value1{ 0, 1 };
        Uuid value2{ 0, 2 };

        REQUIRE_FALSE(value1 == value2);
        REQUIRE(value1 != value2);
        REQUIRE(value1 < value2);
        REQUIRE_FALSE(value1 > value2);
        REQUIRE(value1 <= value2);
        REQUIRE_FALSE(value1 >= value2);
    }

    SECTION("CreateUuid returns non-empty uuid")
    {
        REQUIRE(Uuid::Create() != Uuid{});
    }
}
