#include <catch2/catch.hpp>
#include <Graphyte/ByteAccess.hxx>

TEST_CASE("Bitwise ops")
{
    using namespace Graphyte;

    SECTION("ctz64")
    {
        CHECK(CountTrailingZeros<uint64_t>(0) == 64);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 0) == 0);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 1) == 1);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 2) == 2);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 3) == 3);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 60) == 60);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 61) == 61);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 62) == 62);
        CHECK(CountTrailingZeros<uint64_t>(UINT64_C(1) << 63) == 63);
    }

    SECTION("clz64")
    {
        CHECK(CountLeadingZeros<uint64_t>(0) == 64);
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 0) == (64 - 0 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 1) == (64 - 1 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 2) == (64 - 2 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 3) == (64 - 3 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 60) == (64 - 60 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 61) == (64 - 61 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 62) == (64 - 62 - 1));
        CHECK(CountLeadingZeros<uint64_t>(UINT64_C(1) << 63) == (64 - 63 - 1));
    }

    SECTION("ctz32")
    {
        CHECK(CountTrailingZeros<uint32_t>(0) == 32);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 0) == 0);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 1) == 1);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 2) == 2);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 3) == 3);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 28) == 28);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 29) == 29);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 30) == 30);
        CHECK(CountTrailingZeros<uint32_t>(UINT32_C(1) << 31) == 31);
    }

    SECTION("clz32")
    {
        CHECK(CountLeadingZeros<uint32_t>(0) == 32);
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 0) == (32 - 0 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 1) == (32 - 1 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 2) == (32 - 2 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 3) == (32 - 3 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 28) == (32 - 28 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 29) == (32 - 29 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 30) == (32 - 30 - 1));
        CHECK(CountLeadingZeros<uint32_t>(UINT32_C(1) << 31) == (32 - 31 - 1));
    }

    SECTION("popcnt64")
    {
        CHECK(CountBits<uint64_t>(UINT64_C(0x00)) == 0);
        CHECK(CountBits<uint64_t>(UINT64_C(0x01)) == 1);
        CHECK(CountBits<uint64_t>(UINT64_C(0x02)) == 1);
        CHECK(CountBits<uint64_t>(UINT64_C(0x03)) == 2);
        CHECK(CountBits<uint64_t>(UINT64_C(0x70)) == 3);
        CHECK(CountBits<uint64_t>(UINT64_C(0x80)) == 1);
        CHECK(CountBits<uint64_t>(UINT64_C(0xF0)) == 4);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFF)) == 8);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFF)) == 12);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFF)) == 16);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFF)) == 20);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFF)) == 24);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFF)) == 28);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFF)) == 32);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFF)) == 36);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFF)) == 40);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFFF)) == 44);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFFFF)) == 48);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFFFFF)) == 52);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFFFFFF)) == 56);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFFFFFFF)) == 60);
        CHECK(CountBits<uint64_t>(UINT64_C(0xFFFFFFFFFFFFFFFF)) == 64);
    }

    SECTION("popcnt32")
    {
        CHECK(CountBits<uint32_t>(UINT32_C(0x00)) == 0);
        CHECK(CountBits<uint32_t>(UINT32_C(0x01)) == 1);
        CHECK(CountBits<uint32_t>(UINT32_C(0x02)) == 1);
        CHECK(CountBits<uint32_t>(UINT32_C(0x03)) == 2);
        CHECK(CountBits<uint32_t>(UINT32_C(0x70)) == 3);
        CHECK(CountBits<uint32_t>(UINT32_C(0x80)) == 1);
        CHECK(CountBits<uint32_t>(UINT32_C(0xF0)) == 4);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFF)) == 8);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFFF)) == 12);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFFFF)) == 16);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFFFFF)) == 20);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFFFFFF)) == 24);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFFFFFFF)) == 28);
        CHECK(CountBits<uint32_t>(UINT32_C(0xFFFFFFFF)) == 32);
    }

    SECTION("Byte swap")
    {
        CHECK(ByteSwap<uint16_t>(0x1234) == 0x3412);
        CHECK(ByteSwap<uint16_t>(0x0001) == 0x0100);
        CHECK(ByteSwap<uint32_t>(0x00001234) == 0x34120000);
        CHECK(ByteSwap<uint32_t>(0x00000001) == 0x01000000);
        CHECK(ByteSwap<uint64_t>(0x0123456789abcdef) == 0xefcdab8967452301);
        CHECK(ByteSwap<uint64_t>(0x0102030405060708) == 0x0807060504030201);
    }
}
