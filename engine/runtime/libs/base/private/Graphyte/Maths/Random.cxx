#include "Base.pch.hxx"
#if false
#include <Graphyte/Maths/Random.hxx>

namespace Graphyte::Maths::Random
{
    // Uses WELL512 algorithm
    
    void DefaultRandom::Randomize(uint64_t seed) noexcept
    {
        uint32_t lo = static_cast<uint32_t>(seed);
        uint32_t hi = static_cast<uint32_t>(seed >> 32);
        Index = 0;

        State[0x00] = lo ^ 0x20b7ffc1U;
        State[0x01] = lo ^ 0x2042ba52U;
        State[0x02] = lo ^ 0xa4cb7989U;
        State[0x03] = lo ^ 0xcd08cba2U;
        State[0x04] = lo ^ 0x54da2a91U;
        State[0x05] = lo ^ 0x18f1fa42U;
        State[0x06] = lo ^ 0x57a8a1c1U;
        State[0x07] = lo ^ 0xadfe0802U;
        State[0x08] = lo ^ 0x468383c2U;
        State[0x09] = lo ^ 0xd14ac1acU;
        State[0x0A] = lo ^ 0xa21a3df3U;
        State[0x0B] = lo ^ 0x60b6adf4U;
        State[0x0C] = lo ^ 0xba0955d5U;
        State[0x0D] = lo ^ 0x8de40326U;
        State[0x0E] = lo ^ 0xd81fcc9bU;
        State[0x0F] = lo ^ 0xb60f2ba3U;
        State[0x10] = hi ^ 0xd97a9ea5U;
        State[0x11] = hi ^ 0x579bb2bcU;
        State[0x12] = hi ^ 0x1e2b53daU;
        State[0x13] = hi ^ 0x5dbc6518U;
        State[0x14] = hi ^ 0x312cbffeU;
        State[0x15] = hi ^ 0x63da12e3U;
        State[0x16] = hi ^ 0x0daa3a59U;
        State[0x17] = hi ^ 0x6159f36dU;
        State[0x18] = hi ^ 0x019c327bU;
        State[0x19] = hi ^ 0x93c58093U;
        State[0x1A] = hi ^ 0x957ae943U;
        State[0x1B] = hi ^ 0xaf0016aeU;
        State[0x1C] = hi ^ 0x0d1fb5aeU;
        State[0x1D] = hi ^ 0x134fcd4aU;
        State[0x1E] = hi ^ 0xc0e2b444U;
        State[0x1F] = hi ^ 0x1fbb85bbU;
    }

    uint32_t DefaultRandom::Sample32() noexcept
    {
        uint32_t a, b, c, d;

        a = State[Index];
        c = State[(Index + 13) & 31];
        b = a ^ c ^ (a << 16) ^ (c << 15);
        c = State[(Index + 9) & 31];
        c ^= (c >> 11);
        a = State[Index] = b ^ c;
        d = a ^ ((a << 5) & 0xDA442D24U);
        Index = (Index + 31) & 31;
        a = State[Index];
        State[Index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
        return State[Index];
    }

    uint64_t DefaultRandom::Sample64() noexcept
    {
        uint64_t lo = Sample32();
        uint64_t hi = Sample32();

        return (hi << 32) | lo;
    }
}
#endif
