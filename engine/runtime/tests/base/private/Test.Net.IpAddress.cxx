#include <catch2/catch.hpp>
#if false
#include <GxBase/Network/IpAddress.hxx>

TEST_CASE("IpAddress tests")
{
    using Graphyte::Network::IpAddress;
    using Graphyte::Network::AddressFamily;

    struct
    {
        std::array<std::uint8_t, 4> address;
        std::string_view parsed;
    } ipv4_addresses[] = {
        { { { 82, 115, 65, 248 } }, "82.115.65.248" },
        { { { 127, 0, 0, 1 } }, "127.0.0.1" },
        { { { 255, 255, 255, 255 } }, "255.255.255.255" },
        { { { 0, 0, 0, 0 } }, "0.0.0.0" },
    };

    for (size_t i = 0; i < (sizeof(ipv4_addresses) / sizeof(ipv4_addresses[0])); ++i)
    {
        SECTION(std::string("IPV4 ") + std::to_string(i))
        {
            const auto& test_data = ipv4_addresses[i];

            auto address = IpAddress::MakeAddress(test_data.address.data(), static_cast<socklen_t>(test_data.address.size()));

            CHECK(address.Family() == AddressFamily::IpV4);

            std::string result{};

            CHECK(address.ToString(result));
            CHECK(result == test_data.parsed);

            IpAddress newone{};
            CHECK(IpAddress::TryParse(newone, result.c_str()));

            CHECK(newone.Family() == AddressFamily::IpV4);

            std::array<std::uint8_t, 4> bytes{};
            CHECK(newone.ToBytesIPv4(bytes));
            CHECK(bytes == test_data.address);
        }
    }

    struct
    {
        std::array<std::uint8_t, 16> address;
        std::string_view parsed;
    } ipv6_addresses[] = {
        { { { 0x20, 0x01, 0x0d, 0xb8, 0x85, 0xa3, 0x08, 0xd3, 0x13, 0x19, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x48 } }, "2001:db8:85a3:8d3:1319:8a2e:370:7348" },
        { { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 } }, "::1" },
        { { { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 } }, "8000::1" },
        { { { 0x20, 0x01, 0x0d, 0xb8, 0x33, 0x33, 0x44, 0x44, 0x55, 0x55, 0x66, 0x66, 0x01, 0x02, 0x03, 0x04 } }, "2001:db8:3333:4444:5555:6666:102:304" },
    };


    for (size_t i = 0; i < (sizeof(ipv6_addresses) / sizeof(ipv6_addresses[0])); ++i)
    {
        SECTION(std::string("IPV4 ") + std::to_string(i))
        {
            const auto& test_data = ipv6_addresses[i];

            auto address = IpAddress::MakeAddress(test_data.address.data(), static_cast<socklen_t>(test_data.address.size()));

            CHECK(address.Family() == AddressFamily::IpV6);

            std::string result{};

            CHECK(address.ToString(result));
            CHECK(result == test_data.parsed);

            IpAddress newone{};
            CHECK(IpAddress::TryParse(newone, result.c_str()));

            CHECK(newone.Family() == AddressFamily::IpV6);

            std::array<std::uint8_t, 16> bytes{};
            CHECK(newone.ToBytesIPv6(bytes));
            CHECK(bytes == test_data.address);
        }
    }
}

TEST_CASE("Masking")
{
    using Graphyte::Network::IpAddress;
    using Graphyte::Network::AddressFamily;

    const std::array<std::uint8_t, 4> raw_address{ { 82, 115, 65, 248 } };
    const std::array<std::uint8_t, 4> raw_mask{ { 255, 255, 192, 0 } };
    const std::array<std::uint8_t, 4> raw_set{ { 198, 234, 254, 111 } };

    SECTION("IPv4 Mask")
    {
        auto address = IpAddress::MakeAddress(raw_address.data(), static_cast<socklen_t>(raw_address.size()));
        auto mask = IpAddress::MakeAddress(raw_mask.data(), static_cast<socklen_t>(raw_mask.size()));

        auto result = IpAddress::Mask(address, mask);

        std::array<std::uint8_t, 4> raw_result{};
        CHECK(result.ToBytesIPv4(raw_result) == true);

        CHECK(static_cast<uint32_t>(raw_result[0]) == 82);
        CHECK(static_cast<uint32_t>(raw_result[1]) == 115);
        CHECK(static_cast<uint32_t>(raw_result[2]) == 64);
        CHECK(static_cast<uint32_t>(raw_result[3]) == 0);
    }

    SECTION("IPv4 Mask with set")
    {
        auto address = IpAddress::MakeAddress(raw_address.data(), static_cast<socklen_t>(raw_address.size()));
        auto mask = IpAddress::MakeAddress(raw_mask.data(), static_cast<socklen_t>(raw_mask.size()));
        auto set = IpAddress::MakeAddress(raw_set.data(), static_cast<socklen_t>(raw_set.size()));

        auto result = IpAddress::Mask(address, mask, set);

        std::array<std::uint8_t, 4> raw_result{};
        CHECK(result.ToBytesIPv4(raw_result) == true);

        CHECK(static_cast<uint32_t>(raw_result[0]) == 82);
        CHECK(static_cast<uint32_t>(raw_result[1]) == 115);
        CHECK(static_cast<uint32_t>(raw_result[2]) == 126);
        CHECK(static_cast<uint32_t>(raw_result[3]) == 111);
    }
}
#endif
