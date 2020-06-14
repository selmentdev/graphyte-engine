#include <catch2/catch.hpp>
#include <GxBase/String.hxx>

TEST_CASE("String pattern matching")
{
    SECTION("Wildcard matching")
    {
        SECTION("Identity matching")
        {
            CHECK(Graphyte::MatchWildcard("", ""));
            CHECK(Graphyte::MatchWildcard("a", "a"));
            CHECK(Graphyte::MatchWildcard("ab", "ab"));
            CHECK(Graphyte::MatchWildcard("abc", "abc"));
            CHECK(Graphyte::MatchWildcard("abcd", "abcd"));
        }

        SECTION("Definitely not matching")
        {
            CHECK_FALSE(Graphyte::MatchWildcard("a", "z"));
            CHECK_FALSE(Graphyte::MatchWildcard("a", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("", "z"));
            CHECK_FALSE(Graphyte::MatchWildcard("abcd", "xyzw"));
            CHECK_FALSE(Graphyte::MatchWildcard("ab", "xyzw"));
            CHECK_FALSE(Graphyte::MatchWildcard("abcd", "xw"));
        }

        SECTION("Matching single characters - without pattern chars")
        {
            CHECK_FALSE(Graphyte::MatchWildcard("?", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("??", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("???", ""));
            CHECK(Graphyte::MatchWildcard("?", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("??", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("???", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("?", "ab"));
            CHECK(Graphyte::MatchWildcard("??", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("???", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("?", "abc"));
            CHECK_FALSE(Graphyte::MatchWildcard("??", "abc"));
            CHECK(Graphyte::MatchWildcard("???", "abc"));
            CHECK_FALSE(Graphyte::MatchWildcard("?", "abcd"));
            CHECK_FALSE(Graphyte::MatchWildcard("??", "abcd"));
            CHECK_FALSE(Graphyte::MatchWildcard("???", "abcd"));
            CHECK_FALSE(Graphyte::MatchWildcard("?", "abcde"));
            CHECK_FALSE(Graphyte::MatchWildcard("??", "abcde"));
            CHECK_FALSE(Graphyte::MatchWildcard("???", "abcde"));
        }

        SECTION("Matching single characters - with pattern chars")
        {
            CHECK_FALSE(Graphyte::MatchWildcard("a?cd", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("a?c?", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("?b??", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("a?cd", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("??cd", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("??c?", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("a?cd", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("?b?d", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("?b??", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("ab?d", "abc"));
            CHECK_FALSE(Graphyte::MatchWildcard("?b?d", "abc"));
            CHECK_FALSE(Graphyte::MatchWildcard("??c?", "abc"));
            CHECK(Graphyte::MatchWildcard("?bcd", "abcd"));
            CHECK(Graphyte::MatchWildcard("?b?d", "abcd"));
            CHECK(Graphyte::MatchWildcard("?b??", "abcd"));
            CHECK_FALSE(Graphyte::MatchWildcard("?bcd", "abcde"));
            CHECK_FALSE(Graphyte::MatchWildcard("?b?d", "abcde"));
            CHECK_FALSE(Graphyte::MatchWildcard("?b??", "abcde"));
        }

        SECTION("Matching single characters - without pattern chars")
        {
            CHECK(Graphyte::MatchWildcard("*", ""));
            CHECK(Graphyte::MatchWildcard("**", ""));
            CHECK(Graphyte::MatchWildcard("***", ""));
            CHECK(Graphyte::MatchWildcard("*", "a"));
            CHECK(Graphyte::MatchWildcard("**", "a"));
            CHECK(Graphyte::MatchWildcard("***", "a"));
            CHECK(Graphyte::MatchWildcard("*", "ab"));
            CHECK(Graphyte::MatchWildcard("**", "ab"));
            CHECK(Graphyte::MatchWildcard("***", "ab"));
            CHECK(Graphyte::MatchWildcard("*", "abc"));
            CHECK(Graphyte::MatchWildcard("**", "abc"));
            CHECK(Graphyte::MatchWildcard("***", "abc"));
            CHECK(Graphyte::MatchWildcard("*", "abcd"));
            CHECK(Graphyte::MatchWildcard("**", "abcd"));
            CHECK(Graphyte::MatchWildcard("***", "abcd"));
            CHECK(Graphyte::MatchWildcard("*", "abcde"));
            CHECK(Graphyte::MatchWildcard("**", "abcde"));
            CHECK(Graphyte::MatchWildcard("***", "abcde"));
        }

        SECTION("Matching single characters - with pattern chars")
        {
            CHECK_FALSE(Graphyte::MatchWildcard("a*cd", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("a*c*", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("*b**", ""));
            CHECK_FALSE(Graphyte::MatchWildcard("a*cd", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("**cd", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("**c*", "a"));
            CHECK_FALSE(Graphyte::MatchWildcard("a*cd", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("*b*d", "ab"));
            CHECK(Graphyte::MatchWildcard("*b**", "ab"));
            CHECK_FALSE(Graphyte::MatchWildcard("ab*d", "abc"));
            CHECK_FALSE(Graphyte::MatchWildcard("*b*d", "abc"));
            CHECK(Graphyte::MatchWildcard("**c*", "abc"));
            CHECK(Graphyte::MatchWildcard("*bcd", "abcd"));
            CHECK(Graphyte::MatchWildcard("*b*d", "abcd"));
            CHECK(Graphyte::MatchWildcard("*b**", "abcd"));
            CHECK_FALSE(Graphyte::MatchWildcard("*bcd", "abcde"));
            CHECK_FALSE(Graphyte::MatchWildcard("*b*d", "abcde"));
            CHECK(Graphyte::MatchWildcard("*b**", "abcde"));
        }
    }
}


TEST_CASE("String split")
{
    SECTION("Path alike")
    {
        auto result = Graphyte::Split("/some/string/separated/by/slashes", "/");
        REQUIRE(result.size() == 5);
        CHECK(result[0] == "some");
        CHECK(result[1] == "string");
        CHECK(result[2] == "separated");
        CHECK(result[3] == "by");
        CHECK(result[4] == "slashes");
    }

    SECTION("Path alike - char")
    {
        auto result = Graphyte::Split("/some/string/separated/by/slashes", '/');
        REQUIRE(result.size() == 5);
        CHECK(result[0] == "some");
        CHECK(result[1] == "string");
        CHECK(result[2] == "separated");
        CHECK(result[3] == "by");
        CHECK(result[4] == "slashes");
    }

    SECTION("Splitting by empty values - right")
    {
        auto result = Graphyte::Split("a:", ':', false);
        REQUIRE(result.size() == 2);
        CHECK(result[0] == "a");
        CHECK(result[1] == "");
    }

    SECTION("Splitting by empty values - left")
    {
        auto result = Graphyte::Split(":a", ':', false);
        REQUIRE(result.size() == 2);
        CHECK(result[0] == "");
        CHECK(result[1] == "a");
    }

    SECTION("Splitting by empty values - middle")
    {
        auto result = Graphyte::Split("a::c", ':', false);
        REQUIRE(result.size() == 3);
        CHECK(result[0] == "a");
        CHECK(result[1] == "");
        CHECK(result[2] == "c");
    }

    SECTION("Empty elements")
    {
        auto result = Graphyte::Split("some/string///separated/by//////slashes", "/");
        REQUIRE(result.size() == 5);
        CHECK(result[0] == "some");
        CHECK(result[1] == "string");
        CHECK(result[2] == "separated");
        CHECK(result[3] == "by");
        CHECK(result[4] == "slashes");
    }

    SECTION("Empty elements - char")
    {
        auto result = Graphyte::Split("some/string///separated/by//////slashes", '/');
        REQUIRE(result.size() == 5);
        CHECK(result[0] == "some");
        CHECK(result[1] == "string");
        CHECK(result[2] == "separated");
        CHECK(result[3] == "by");
        CHECK(result[4] == "slashes");
    }

    SECTION("Trimming")
    {
        auto result = Graphyte::Split("////some/string/separated/by/slashes////", "/");
        REQUIRE(result.size() == 5);
        CHECK(result[0] == "some");
        CHECK(result[1] == "string");
        CHECK(result[2] == "separated");
        CHECK(result[3] == "by");
        CHECK(result[4] == "slashes");
    }

    SECTION("Trimming - char")
    {
        auto result = Graphyte::Split("////some/string/separated/by/slashes////", '/');
        REQUIRE(result.size() == 5);
        CHECK(result[0] == "some");
        CHECK(result[1] == "string");
        CHECK(result[2] == "separated");
        CHECK(result[3] == "by");
        CHECK(result[4] == "slashes");
    }

    SECTION("Longer separators")
    {
        auto result = Graphyte::Split("|__|some/string|__|separated/by|__|slashes|__||__|", "|__|");
        REQUIRE(result.size() == 3);
        CHECK(result[0] == "some/string");
        CHECK(result[1] == "separated/by");
        CHECK(result[2] == "slashes");
    }
}

TEST_CASE("String join")
{
    SECTION("Initializer list")
    {
        CHECK(Graphyte::Join({ "some", "parts", "of", "path" }, "/") == "some/parts/of/path");
        CHECK(Graphyte::Join({}, "/") == "");
    }

    SECTION("Vector")
    {
        std::vector<std::string_view> values{
            { "some", "parts", "of", "path" }
        };

        CHECK(Graphyte::Join(values, "/") == "some/parts/of/path");

        values.clear();
        CHECK(Graphyte::Join(values, "/") == "");
    }

    SECTION("List")
    {
        std::list<std::string_view> values{
            { "some", "parts", "of", "path" }
        };

        CHECK(Graphyte::Join(values, "/") == "some/parts/of/path");

        values.clear();
        CHECK(Graphyte::Join(values, "/") == "");
    }
}
