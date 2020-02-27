#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Types.hxx>
#include <Graphyte/Span.hxx>

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
    /// uint64_t const value = Generate64(state);
    /// ```
    extern BASE_API uint64_t Generate64(RandomState& state) noexcept;

    inline uint32_t Generate32(RandomState& state) noexcept
    {
        uint64_t const sample = Generate64(state);
        uint32_t const hi = static_cast<uint32_t>(sample >> 32u);
        uint32_t const lo = static_cast<uint32_t>(sample);
        uint32_t const result = hi ^ lo;
        return result;
    }

    extern BASE_API void Generate(RandomState& state, notstd::span<std::byte> buffer) noexcept;

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

namespace Graphyte::Random
{
    template <typename T> T Next(RandomState&) noexcept = delete;

    template <>
    inline float Next<float>(RandomState& state) noexcept
    {
        uint32_t const sample = Generate32(state);

        return FloatTraits<float>::Range12FromHighBits(sample) - 1.0f;
    }

    template <>
    inline double Next<double>(RandomState& state) noexcept
    {
        uint64_t const sample = Generate64(state);
        return FloatTraits<double>::Range12FromHighBits(sample) - 1.0;
    }

    template <typename T>
    inline T Next(RandomState& state, T max) noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            T const sample = Next<T>(state);
            T const result = sample * max;
            return result;
        }
        else if constexpr (std::is_unsigned_v<T>)
        {
            T const result = Next<T>(state, 0, max);
            return result;
        }
        else
        {
            static_assert(false, "Type T is not supported");
        }
    }

    template <typename T>
    inline T Next(RandomState& state, T min, T max) noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            T const sample = Next<T>(state);
            T const scale = (max - min);
            T const result = (sample * scale) + min;
            return result;
        }
        else if constexpr (std::is_unsigned_v<T>)
        {
            T result;

            if ((max - min) == std::numeric_limits<T>::max())
            {
                return Next<T>(state);
            }
            else
            {
                T const range = max - min + 1;
                T const limit = std::numeric_limits<T>::max() - (std::numeric_limits<T>::max() % range);

                do
                {
                    result = Next<T>(state);
                } while (result >= limit);

                result %= range;
            }

            return min + result;
        }
        else
        {
            static_assert(false, "Type T is not supported");
        }
    }

    template <>
    inline Float4A Next(RandomState& state) noexcept
    {
        uint64_t const sample0 = Generate64(state);
        uint64_t const sample1 = Generate64(state);

        uint32_t const c0_u32 = static_cast<uint32_t>(sample0);
        uint32_t const c1_u32 = static_cast<uint32_t>(sample0 >> 32);
        uint32_t const c2_u32 = static_cast<uint32_t>(sample1);
        uint32_t const c3_u32 = static_cast<uint32_t>(sample1 >> 32);

        return {
            .X = FloatTraits<float>::Range12FromHighBits(c0_u32) - 1.0f,
            .Y = FloatTraits<float>::Range12FromHighBits(c1_u32) - 1.0f,
            .Z = FloatTraits<float>::Range12FromHighBits(c2_u32) - 1.0f,
            .W = FloatTraits<float>::Range12FromHighBits(c3_u32) - 1.0f,
        };
    }

    template <>
    inline uint32_t Next<uint32_t>(RandomState& state) noexcept
    {
        return Generate32(state);
    }

    template <>
    inline uint64_t Next<uint64_t>(RandomState& state) noexcept
    {
        return Generate64(state);
    }

    template <typename T>
    inline T NextLaplace(RandomState& state, T mean, T scale) noexcept
    {
        T const variable = Next<T>(state);

        return (variable < T(0.5))
            ? (mean + scale * std::log2(T(2.0) * variable))
            : (mean - scale * std::log2(T(2.0) * (T(1.0) - variable)));
    }

    template <typename T>
    inline T NextNormal(RandomState& state) noexcept
    {
        static_assert(std::is_floating_point_v<T>);

        T const u1 = Next<T>(state);
        T const u2 = Next<T>(state);

        T const r = std::sqrt(T(-2.0) * std::log(u1));
        T const theta = T(6.183018) * u2;
        T const result = r * std::sin(theta);
        return result;
    }

    template <typename T>
    inline T NextNormal(RandomState& state, T mean, T stddev) noexcept
    {
        static_assert(std::is_floating_point_v<T>);

        return mean + NextNormal<T>(state) * stddev;
    }
}
