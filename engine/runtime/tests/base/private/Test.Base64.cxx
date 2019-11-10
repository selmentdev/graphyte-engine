#include "Test.Base.pch.hxx"
//#include <Graphyte/Base64.hxx>

#if false
TEST_CASE("Base64")
{
    using Graphyte::Base64;

    SECTION("Encoding")
    {
        {
            std::vector<std::byte> data{};

            notstd::span<std::byte> data_view{ data.data(), data.size() };

            const std::string_view string{ "" };

            CHECK(Base64::Encode(data_view) == string);
            CHECK(Base64::Decode(string) == data);
        }

        {
            std::vector<std::byte> data{ std::byte{ 'G' }, std::byte{ 'r' }, std::byte{ 'a' }, std::byte{ 'p' }, std::byte{ 'h' }, std::byte{ 'y' }, std::byte{ 't' }, std::byte{ 'e' } };
            notstd::span<std::byte> data_view{ data.data(), data.size() };

            const std::string_view string{ "R3JhcGh5dGU=" };

            CHECK(Base64::Encode(data_view) == string);
            CHECK(Base64::Decode(string) == data);
        }

        {
            std::vector<std::byte> data{ std::byte{ 'G' }, std::byte{ 'r' }, std::byte{ 'a' }, std::byte{ 'p' }, std::byte{ 'h' }, std::byte{ 'y' }, std::byte{ 't' }, std::byte{ 'e' }, std::byte{ ' ' }, std::byte{ 'E' }, std::byte{ 'n' }, std::byte{ 'g' }, std::byte{ 'i' }, std::byte{ 'n' }, std::byte{ 'e' } };
            notstd::span<std::byte> data_view{ data.data(), data.size() };

            const std::string_view string{ "R3JhcGh5dGUgRW5naW5l" };

            CHECK(Base64::Encode(data_view) == string);
            CHECK(Base64::Decode(string) == data);
        }
        {
            std::vector<std::byte> data{ std::byte{ 'D' }, std::byte{ 'u' }, std::byte{ 'c' }, std::byte{ 'k' }, std::byte{ 'y' }, std::byte{ ' ' }, std::byte{ 'M' }, std::byte{ 'c' }, std::byte{ 'Q' }, std::byte{ 'u' }, std::byte{ 'a' }, std::byte{ 'c' }, std::byte{ 'k' } };
            notstd::span<std::byte> data_view{ data.data(), data.size() };

            const std::string_view string{ "RHVja3kgTWNRdWFjaw==" };

            CHECK(Base64::Encode(data_view) == string);
            CHECK(Base64::Decode(string) == data);
        }
    }
}
#endif
