#include "Test.Base.pch.hxx"
#include <Graphyte/Version.hxx>

TEST_CASE("Version")
{
    SECTION("Default constructor")
    {
        Graphyte::Version v{};
        CHECK(v.Major == uint32_t{ 0 });
        CHECK(v.Minor == uint32_t{ 0 });
        CHECK(v.Patch == uint32_t{ 0 });
        CHECK(v.Build == uint32_t{ 0 });
    }

    SECTION("Setting constructor and copy constructor")
    {
        Graphyte::Version v{ 1, 2, 3, 4 };
        CHECK(v.Major == uint32_t{ 1 });
        CHECK(v.Minor == uint32_t{ 2 });
        CHECK(v.Patch == uint32_t{ 3 });
        CHECK(v.Build == uint32_t{ 4 });

        Graphyte::Version c{ v };
        CHECK(c.Major == uint32_t{ 1 });
        CHECK(c.Minor == uint32_t{ 2 });
        CHECK(c.Patch == uint32_t{ 3 });
        CHECK(c.Build == uint32_t{ 4 });

        CHECK(Graphyte::Converter<Graphyte::Version>::FromString(v, "8.7.6.5"));
        CHECK(v.Major == uint32_t{ 8 });
        CHECK(v.Minor == uint32_t{ 7 });
        CHECK(v.Patch == uint32_t{ 6 });
        CHECK(v.Build == uint32_t{ 5 });

        c = v;
        CHECK(c.Major == uint32_t{ 8 });
        CHECK(c.Minor == uint32_t{ 7 });
        CHECK(c.Patch == uint32_t{ 6 });
        CHECK(c.Build == uint32_t{ 5 });
    }

    SECTION("String conversion")
    {
        Graphyte::Version v{ 1, 2, 3, 4 };

        std::string str{};
        REQUIRE(Graphyte::Converter<Graphyte::Version>::ToString(str, v));
        CHECK(str == "1.2.3.4");

        CHECK(Graphyte::Converter<Graphyte::Version>::FromString(v, "5.6.7.8"));
        CHECK(v.Major == 5U);
        CHECK(v.Minor == 6U);
        CHECK(v.Patch == 7U);
        CHECK(v.Build == 8U);
    }

    SECTION("FromString invalid values")
    {
        SECTION("empty")
        {
            Graphyte::Version result{};
            CHECK(Graphyte::Converter<Graphyte::Version>::FromString(result, "") == false);
            CHECK(result.Major == 0U);
            CHECK(result.Minor == 0U);
            CHECK(result.Patch == 0U);
            CHECK(result.Build == 0U);
        }

        SECTION("invalid text")
        {
            Graphyte::Version result{};
            CHECK(Graphyte::Converter<Graphyte::Version>::FromString(result, "this isn't valid version string") == false);
            CHECK(result.Major == 0U);
            CHECK(result.Minor == 0U);
            CHECK(result.Patch == 0U);
            CHECK(result.Build == 0U);
        }

        SECTION("1 part")
        {
            Graphyte::Version result{};
            CHECK(Graphyte::Converter<Graphyte::Version>::FromString(result, "1") == false);
            CHECK(result.Major == 0U);
            CHECK(result.Minor == 0U);
            CHECK(result.Patch == 0U);
            CHECK(result.Build == 0U);
        }

        SECTION("2 parts")
        {
            Graphyte::Version result{};
            CHECK(Graphyte::Converter<Graphyte::Version>::FromString(result, "1.2") == false);
            CHECK(result.Major == 0U);
            CHECK(result.Minor == 0U);
            CHECK(result.Patch == 0U);
            CHECK(result.Build == 0U);
        }

        SECTION("3 parts")
        {
            Graphyte::Version result{};
            CHECK(Graphyte::Converter<Graphyte::Version>::FromString(result, "1.2.3") == false);
            CHECK(result.Major == 0U);
            CHECK(result.Minor == 0U);
            CHECK(result.Patch == 0U);
            CHECK(result.Build == 0U);
        }

        SECTION("mixed parts")
        {
            Graphyte::Version result{};
            CHECK(Graphyte::Converter<Graphyte::Version>::FromString(result, "1.2.a.4") == false);
            CHECK(result.Major == 0U);
            CHECK(result.Minor == 0U);
            CHECK(result.Patch == 0U);
            CHECK(result.Build == 0U);
        }
    }
}
