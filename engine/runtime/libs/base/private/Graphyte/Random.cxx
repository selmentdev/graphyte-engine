#include <Graphyte/Random.hxx>
#include <Graphyte/Bitwise.hxx>

namespace Graphyte::Random::Impl
{
    extern BASE_API uint64_t SplitMix64(uint64_t& seed) noexcept
    {
        // Based on: https://github.com/svaarala/duktape/blob/master/misc/splitmix64.c

        seed += 0x9E3779B97F4A7C15u;
        uint64_t const z0 = seed;
        uint64_t const z1 = (z0 ^ (z0 >> 30)) * 0xBF58476D1CE4E5B9u;
        uint64_t const z2 = (z1 ^ (z1 >> 27)) * 0x94D049BB133111EBu;
        uint64_t const z3 = (z2 ^ (z2 >> 31));
        return z3;
    }
}

// NOTE: This module implements xoroshiro256plusplus random generator

namespace Graphyte::Random
{
    extern BASE_API void Initialize(RandomState& state, uint64_t seed) noexcept
    {
        state.State[0] = Impl::SplitMix64(seed);
        state.State[1] = Impl::SplitMix64(seed);
        state.State[2] = Impl::SplitMix64(seed);
        state.State[3] = Impl::SplitMix64(seed);
    }

    extern BASE_API uint64_t Generate64(RandomState& state) noexcept
    {
        uint64_t const result = RotateLeft<uint64_t>(state.State[0] + state.State[3], 23) + state.State[0];

        uint64_t const t = state.State[1] << 17;

        state.State[2] ^= state.State[0];
        state.State[3] ^= state.State[1];
        state.State[1] ^= state.State[2];
        state.State[0] ^= state.State[3];

        state.State[2] ^= t;
        state.State[3] = RotateLeft<uint64_t>(state.State[3], 45);

        return result;
    }

    extern BASE_API void Generate(RandomState& state, notstd::span<std::byte> buffer) noexcept
    {
        while (buffer.size() >= sizeof(uint64_t))
        {
            uint64_t const sample = Generate64(state);
            memcpy(buffer.data(), &sample, sizeof(uint64_t));

            buffer.remove_prefix(sizeof(uint64_t));
        }

        if (!buffer.empty())
        {
            uint64_t const sample = Generate64(state);
            memcpy(buffer.data(), &sample, buffer.size());
        }
    }

    extern BASE_API void Skip2p128(RandomState& state) noexcept
    {
        static uint64_t const indices[] = {
            0x180EC6D33CFD0ABAu,
            0xD5A61266F0C9392Cu,
            0xA9582618E03FC9AAu,
            0x39ABDC4529B1661Cu,
        };

        uint64_t s0 = 0;
        uint64_t s1 = 0;
        uint64_t s2 = 0;
        uint64_t s3 = 0;

        for (size_t i = 0; i < std::size(indices); ++i)
        {
            for (size_t b = 0; b < 64; ++b)
            {
                if ((indices[i] & (uint64_t{ 1 } << b)) != 0)
                {
                    s0 ^= state.State[0];
                    s1 ^= state.State[1];
                    s2 ^= state.State[2];
                    s3 ^= state.State[3];
                }

                Generate64(state);
            }
        }

        state.State[0] = s0;
        state.State[1] = s1;
        state.State[2] = s2;
        state.State[3] = s3;
    }

    extern BASE_API void Skip2p192(RandomState& state) noexcept
    {
        static const uint64_t indices[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };

        uint64_t s0 = 0;
        uint64_t s1 = 0;
        uint64_t s2 = 0;
        uint64_t s3 = 0;

        for (size_t i = 0; i < std::size(indices); ++i)
        {
            for (size_t b = 0; b < 64; ++b)
            {
                if ((indices[i] & (uint64_t{ 1 } << b)) != 0)
                {
                    s0 ^= state.State[0];
                    s1 ^= state.State[1];
                    s2 ^= state.State[2];
                    s3 ^= state.State[3];
                }

                Generate64(state);
            }
        }

        state.State[0] = s0;
        state.State[1] = s1;
        state.State[2] = s2;
        state.State[3] = s3;
    }
}
