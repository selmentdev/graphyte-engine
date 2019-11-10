#include "Test.Base.pch.hxx"
#include <Graphyte/Span.hxx>

TEST_CASE("Span type")
{
    int32_t ints[4] = {};

    notstd::span<int32_t> data{ ints };

    REQUIRE(std::size(data) == 4);

    data.remove_prefix(1);

    REQUIRE(std::size(data) == 3);

    REQUIRE(ints[0] == 0);
    REQUIRE(ints[1] == 0);
    REQUIRE(ints[2] == 0);
    REQUIRE(ints[3] == 0);

    auto bytez = as_bytes(data);

    REQUIRE(std::size(bytez) == 12);

    REQUIRE(bytez[0] == std::byte{ 0 });
    REQUIRE(bytez[1] == std::byte{ 0 });
    REQUIRE(bytez[2] == std::byte{ 0 });
    REQUIRE(bytez[3] == std::byte{ 0 });
    REQUIRE(bytez[4] == std::byte{ 0 });
    REQUIRE(bytez[5] == std::byte{ 0 });
    REQUIRE(bytez[6] == std::byte{ 0 });
    REQUIRE(bytez[7] == std::byte{ 0 });
    REQUIRE(bytez[8] == std::byte{ 0 });
    REQUIRE(bytez[9] == std::byte{ 0 });
    REQUIRE(bytez[10] == std::byte{ 0 });
    REQUIRE(bytez[11] == std::byte{ 0 });

    auto subytez = as_writable_bytes(data.subspan(1, 2));
    subytez[0] = std::byte{ 0x42 };
    subytez[1] = std::byte{ 0x42 };
    subytez[2] = std::byte{ 0x42 };
    subytez[3] = std::byte{ 0x42 };
    subytez[7] = std::byte{ 0xcc };

    REQUIRE(subytez.size() == 8);

    REQUIRE(bytez[0] == std::byte{ 0 });
    REQUIRE(bytez[1] == std::byte{ 0 });
    REQUIRE(bytez[2] == std::byte{ 0 });
    REQUIRE(bytez[3] == std::byte{ 0 });
    REQUIRE(bytez[4] == std::byte{ 0x42 });
    REQUIRE(bytez[5] == std::byte{ 0x42 });
    REQUIRE(bytez[6] == std::byte{ 0x42 });
    REQUIRE(bytez[7] == std::byte{ 0x42 });
    REQUIRE(bytez[8] == std::byte{ 0 });
    REQUIRE(bytez[9] == std::byte{ 0 });
    REQUIRE(bytez[10] == std::byte{ 0 });
    REQUIRE(bytez[11] == std::byte{ 0xcc });

    REQUIRE(ints[0] == static_cast<int32_t>(0));
    REQUIRE(ints[1] == static_cast<int32_t>(0));
    REQUIRE(ints[2] == static_cast<int32_t>(0x42424242));
    REQUIRE(ints[3] == static_cast<int32_t>(0xcc000000));
}
