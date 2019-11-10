#include "Test.Base.pch.hxx"
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


TEST_CASE("Bitwise Byte Swapping")
{
#if GRAPHYTE_HW_AVX
    __m128i value = _mm_set_epi8(0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00);
    __m128i expected = _mm_set_epi8(0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15);

    __m128i swapped = Graphyte::ByteSwap(value);

    __m128i compare_mask = _mm_cmpeq_epi8(swapped, expected);
    auto result = _mm_test_all_ones(compare_mask);
    REQUIRE(result == 1);
#endif
}
