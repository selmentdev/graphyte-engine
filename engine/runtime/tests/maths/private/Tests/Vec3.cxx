#include "Test.Maths.pch.hxx"
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Status.hxx>

// NOTE: This is test for random generator xoroshiro256plusplus

/*

    Original copyright note:

    Written in 2018 by David Blackman and Sebastiano Vigna(vigna@acm.org)

    To the extent possible under law, the author has dedicated all copyright
    and relatedand neighboring rights to this software to the public domain
    worldwide.This software is distributed without any warranty.

    See < http://creativecommons.org/publicdomain/zero/1.0/>
*/

#define RANDOM_API GX_NOINLINE

namespace Graphyte::Random
{
    /// \brief Expands provided key using `splitmix64` algorithm.
    extern RANDOM_API uint64_t SplitMix64(uint64_t& key) noexcept
    {
        /// Based on: https://github.com/svaarala/duktape/blob/master/misc/splitmix64.c

        key += 0x9E3779B97F4A7C15u;
        uint64_t const z0 = key;
        uint64_t const z1 = (z0 ^ (z0 >> 30)) * 0xBF58476D1CE4E5B9u;
        uint64_t const z2 = (z1 ^ (z1 >> 27)) * 0xBF58476D1CE4E5B9u;
        uint64_t const z3 = (z2 ^ (z2 >> 31));
        return z3;
    }

    /// \brief  Represents state of PRNG using `xoroshiro256plusplus` algorithm
    struct RandomState final
    {
        uint64_t State[4];
    };

    extern RANDOM_API void Initialize(RandomState& state, uint64_t key) noexcept
    {
        state.State[0] = SplitMix64(key);
        state.State[1] = SplitMix64(key);
        state.State[2] = SplitMix64(key);
        state.State[3] = SplitMix64(key);
    }

    extern RANDOM_API uint64_t Generate(RandomState& state) noexcept
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

    extern RANDOM_API void Skip2p128(RandomState& state) noexcept
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

                Generate(state);
            }
        }

        state.State[0] = s0;
        state.State[1] = s1;
        state.State[2] = s2;
        state.State[3] = s3;
    }

    extern RANDOM_API void Skip2p192(RandomState& state) noexcept
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

                Generate(state);
            }
        }

        state.State[0] = s0;
        state.State[1] = s1;
        state.State[2] = s2;
        state.State[3] = s3;
    }
}

TEST_CASE("Random Generator")
{
    SECTION("Split Mix 64 PRNG for key expansion for xoroshiro")
    {
        uint64_t key = 0;
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x878A022579129C82u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xC72366F4D66B3D8Au });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x6A54D4686D867E7Bu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xD6DC9D34E9651C3Fu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xB854D2F97B498475u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xD0EAC7253911C058u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xCE2777C667C13D90u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x030C386ED1AC9C33u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xB57B428406F7E16Bu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x14B16ACE1B3A38E3u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xF9D098E903FD60B7u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x89F7234BE7F28832u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x83E21F077CA0DA8Eu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xBA92899245E80124u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x69091B4592BE74F7u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x5473817C1585A4FBu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x5BFA66A0BFB7DBE4u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xD55B6E86D88B5279u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xE47A7213220596D2u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x29F48C7C9C1CB26Au });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x066C1AB986354625u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xAB0E9ADE909413C6u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x2FBFAB9ED3A6A734u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xBF7D6C446A5A8101u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xA32117ABA2D3D654u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x6056F83193A0753Cu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x35B67808A450D039u });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x69C76A1B61983FDEu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0xC4B1A38F43B7579Cu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x6BA3A7042AC5831Eu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x1E50344FB7AF5CAFu });
        CHECK(Graphyte::Random::SplitMix64(key) == uint64_t{ 0x443975AEFF542DD4u });

        CHECK(key == uint64_t{ 0xC6EF372FE94F82A0u });
    }

    SECTION("Generate N uint64 values")
    {
        Graphyte::Random::RandomState state{};
        Initialize(state, 0);

        CHECK(Generate(state) == uint64_t{ 0x34BB3E01D9C1CFD1u });
        CHECK(Generate(state) == uint64_t{ 0xA918C447D24A1385u });
        CHECK(Generate(state) == uint64_t{ 0x172DE17A26554E49u });
        CHECK(Generate(state) == uint64_t{ 0x58E3BB77D9EC1D41u });
        CHECK(Generate(state) == uint64_t{ 0xD886995CA92269D9u });
        CHECK(Generate(state) == uint64_t{ 0x78AD4E9CDF0543AFu });
        CHECK(Generate(state) == uint64_t{ 0x8C7AD06B0EAFA693u });
        CHECK(Generate(state) == uint64_t{ 0xC340BF2A985EC653u });
        CHECK(Generate(state) == uint64_t{ 0x2C8FD277F3112FB7u });
        CHECK(Generate(state) == uint64_t{ 0x46815D307D67B859u });
        CHECK(Generate(state) == uint64_t{ 0x7BA605195AD08B1Eu });
        CHECK(Generate(state) == uint64_t{ 0x0586CCC35456B6BDu });
        CHECK(Generate(state) == uint64_t{ 0x72C045B12BDD9CFFu });
        CHECK(Generate(state) == uint64_t{ 0xACEC6F60786D4F10u });
        CHECK(Generate(state) == uint64_t{ 0x3DFD15169D727C11u });
        CHECK(Generate(state) == uint64_t{ 0xE8254D253450CAA9u });
    }
}
