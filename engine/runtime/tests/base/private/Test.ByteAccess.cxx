#include <catch2/catch.hpp>
#include <Graphyte/ByteAccess.hxx>

template <typename T>
struct ByteAccess;

template <>
struct ByteAccess<uint16_t> final
{
    static constexpr uint8_t LoPart(uint16_t value) noexcept
    {
        return static_cast<uint8_t>(value);
    }

    static constexpr uint8_t HiPart(uint16_t value) noexcept
    {
        return static_cast<uint8_t>(value >> 8);
    }

    static constexpr uint16_t Make(uint8_t lo, uint8_t hi) noexcept
    {
        return static_cast<uint16_t>(lo | (hi << 8));
    }

    static constexpr uint16_t Swap(uint16_t value) noexcept
    {
        return Make(HiPart(value), LoPart(value));
    }
};

TEST_CASE("Byte Access - lo/hi part and makexxxx")
{
    REQUIRE(ByteAccess<uint16_t>::LoPart(0x1234) == 0x34);
    REQUIRE(ByteAccess<uint16_t>::HiPart(0x1234) == 0x12);
    REQUIRE(ByteAccess<uint16_t>::Make(0x34, 0x12) == 0x1234);
    REQUIRE(ByteAccess<uint16_t>::Swap(0x1234) == 0x3412);
}
