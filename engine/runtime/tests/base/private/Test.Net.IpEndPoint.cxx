#include "Test.Base.pch.hxx"
#include <Graphyte/Network/IpEndPoint.hxx>
#include <Graphyte/Network/IpAddress.hxx>

TEST_CASE("IpEndPoint tests")
{
    using Graphyte::Network::IpEndPoint;
    using Graphyte::Network::IpAddress;
    using Graphyte::Network::AddressFamily;

    struct
    {
        std::array<std::uint8_t, 4> address;
        uint32_t port;
        std::string_view parsed;
    } ipv4_addresses[] = {
        { { { 82, 115, 65, 248 } }, 1337, "82.115.65.248:1337" },
        { { { 127, 0, 0, 1 } }, 82, "127.0.0.1:82" },
        { { { 255, 255, 255, 255 } }, 255, "255.255.255.255:255" },
        { { { 0, 0, 0, 0 } }, 25, "0.0.0.0:25" },
    };

    for (size_t i = 0; i < (sizeof(ipv4_addresses) / sizeof(ipv4_addresses[0])); ++i)
    {
        SECTION(std::string("IPV4 ") + std::to_string(i))
        {
            const auto& test_data = ipv4_addresses[i];

            IpEndPoint endpoint{ IpAddress::MakeAddress(test_data.address.data(), static_cast<socklen_t>(test_data.address.size())), static_cast<uint16_t>(test_data.port) };

            CHECK(endpoint.GetPort() == test_data.port);
            CHECK(endpoint.GetFamily() == AddressFamily::IpV4);

            std::string result{};

            CHECK(endpoint.ToString(result));
            CHECK(result == test_data.parsed);

            IpEndPoint newone{};
            CHECK(IpEndPoint::TryParse(newone, result.c_str()));

            CHECK(newone.GetFamily() == AddressFamily::IpV4);
            CHECK(newone.GetPort() == test_data.port);

            std::array<std::uint8_t, 4> bytes{};
            CHECK(newone.GetAddress().ToBytesIPv4(bytes));
            CHECK(bytes == test_data.address);
        }
    }

    struct
    {
        std::array<std::uint8_t, 16> address;
        uint32_t port;
        std::string_view parsed;
    } ipv6_addresses[] = {
        { { { 0x20, 0x01, 0x0d, 0xb8, 0x85, 0xa3, 0x08, 0xd3, 0x13, 0x19, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x48 } }, 1337, "[2001:db8:85a3:8d3:1319:8a2e:370:7348]:1337" },
        { { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 } }, 80, "[::1]:80" },
        { { { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 } }, 2137, "[8000::1]:2137" },
        { { { 0x20, 0x01, 0x0d, 0xb8, 0x33, 0x33, 0x44, 0x44, 0x55, 0x55, 0x66, 0x66, 0x01, 0x02, 0x03, 0x04 } }, 5858, "[2001:db8:3333:4444:5555:6666:102:304]:5858" },
    };


    for (size_t i = 0; i < (sizeof(ipv6_addresses) / sizeof(ipv6_addresses[0])); ++i)
    {
        SECTION(std::string("IPV4 ") + std::to_string(i))
        {
            const auto& test_data = ipv6_addresses[i];

            IpEndPoint endpoint{ IpAddress::MakeAddress(test_data.address.data(), static_cast<socklen_t>(test_data.address.size())), static_cast<uint16_t>(test_data.port) };

            CHECK(endpoint.GetPort() == test_data.port);
            CHECK(endpoint.GetFamily() == AddressFamily::IpV6);

            std::string result{};

            CHECK(endpoint.ToString(result));
            CHECK(result == test_data.parsed);

            IpEndPoint newone{};
            CHECK(IpEndPoint::TryParse(newone, result.c_str()));

            CHECK(newone.GetFamily() == AddressFamily::IpV6);
            CHECK(newone.GetPort() == test_data.port);

            std::array<std::uint8_t, 16> bytes{};
            CHECK(newone.GetAddress().ToBytesIPv6(bytes));
            CHECK(bytes == test_data.address);
        }
    }
}
