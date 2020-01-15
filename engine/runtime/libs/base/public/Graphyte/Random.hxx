#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte::Random::Impl
{
    extern BASE_API uint64_t SplitMix64(uint64_t& seed) noexcept;
}

namespace Graphyte::Random
{
    struct RandomState final
    {
        std::array<uint64_t, 4> State;
    };

    /// Initializes generator from provided seed.
    ///
    /// ```
    /// RandomState state;
    ///
    /// Initialize(state, 0x2137);
    /// ```
    extern BASE_API void Initialize(RandomState& state, uint64_t seed) noexcept;

    /// Generates uint64_t and updates random generator.
    ///
    /// ```
    /// uint64_t const value = Generate(state);
    /// ```
    extern BASE_API uint64_t Generate(RandomState& state) noexcept;

    /// Skips 2^128 generations.
    ///
    /// ```
    /// Skip2p128(state);
    /// ```
    extern BASE_API void Skip2p128(RandomState& state) noexcept;

    /// Skips 2^192 generations.
    ///
    /// ```
    /// Skip2p192(state);
    /// ```
    extern BASE_API void Skip2p192(RandomState& state) noexcept;
}
