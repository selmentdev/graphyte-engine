#pragma once
#include <Graphyte/Maths/Scalar.hxx>

namespace Graphyte::Maths::Random
{
    struct BASE_API DefaultRandom final
    {
        std::array<uint32_t, 32> State;
        uint32_t Index;

        void Randomize(uint64_t seed) noexcept;

        uint32_t Sample32() noexcept;
        uint64_t Sample64() noexcept;
    };

    template <typename TGenerator>
    inline uint32_t NextUInt32(TGenerator& generator, uint32_t min, uint32_t max) noexcept
    {
        uint32_t result;

        if ((max - min) == std::numeric_limits<uint32_t>::max())
        {
            return generator.Sample32();
        }
        else
        {
            uint32_t range = max - min + 1;
            uint32_t limit = std::numeric_limits<uint32_t>::max() - (std::numeric_limits<uint32_t>::max() % range);

            do
            {
                result = generator.Sample32();
            } while (result >= limit);

            result %= range;
        }

        return min + result;
    }

    template <typename TGenerator>
    inline uint32_t NextUInt32(TGenerator& generator, uint32_t upper_bound) noexcept
    {
        return NextUInt32<TGenerator>(generator, std::numeric_limits<uint32_t>::min(), upper_bound);
    }

    template <typename TGenerator>
    inline uint32_t NextUInt32(TGenerator& generator) noexcept
    {
        return generator.Sample32();
    }

    template <typename TGenerator>
    inline uint64_t NextUInt64(TGenerator& generator, uint64_t min, uint64_t max) noexcept
    {
        uint64_t result;

        if ((max - min) == std::numeric_limits<uint64_t>::max())
        {
            return generator.Sample64();
        }
        else
        {
            uint64_t range = max - min + 1;
            uint64_t limit = std::numeric_limits<uint64_t>::max() - (std::numeric_limits<uint64_t>::max() % range);

            do
            {
                result = generator.Sample32();
            } while (result >= limit);

            result %= range;
        }

        return min + result;
    }

    template <typename TGenerator>
    inline uint64_t NextUInt64(TGenerator& generator, uint64_t upper_bound) noexcept
    {
        return NextUInt64<TGenerator>(generator, std::numeric_limits<uint64_t>::min(), upper_bound);
    }

    template <typename TGenerator>
    inline uint64_t NextUInt64(TGenerator& generator) noexcept
    {
        return generator.Sample64();
    }


    template <typename TGenerator>
    inline float NextFloat(TGenerator& generator) noexcept
    {
        float const sample = static_cast<float>(generator.Sample32());
        return sample / (std::numeric_limits<uint32_t>::max() + 1.0F);
    }

    template <typename TGenerator>
    inline float NextFloat(TGenerator& generator, float upper_bound) noexcept
    {
        return NextFloat(generator) * upper_bound;
    }

    template <typename TGenerator>
    inline float NextFloat(TGenerator& generator, float min, float max) noexcept
    {
        float const sample = NextFloat(generator);
        return min * (1.0F - sample) + max * sample;
    }


    template <typename TGenerator>
    inline double NextDouble(TGenerator& generator) noexcept
    {
        double const sample = static_cast<double>(generator.Sample64());
        return sample / (std::numeric_limits<uint64_t>::max() + 1.0);
    }

    template <typename TGenerator>
    inline double NextDouble(TGenerator& generator, double upper_bound) noexcept
    {
        return NextDouble(generator) * upper_bound;
    }

    template <typename TGenerator>
    inline double NextDouble(TGenerator& generator, double min, double max) noexcept
    {
        double const sample = NextDouble(generator);
        return min * (1.0 - sample) + max * sample;
    }


    template <typename TGenerator>
    inline float NextLaplace(TGenerator& generator, float mean, float scale) noexcept
    {
        float variable = NextFloat32(generator);

        return (variable < 0.5F)
            ? (mean + scale * Log2(2.0F * variable))
            : (mean - scale * Log2(2.0F * (1.0F - variable)));
    }

    template <typename TGenerator>
    inline float NextNormal(TGenerator& generator) noexcept
    {
        float u1 = NextFloat32(generator);
        float u2 = NextFloat32(generator);

        float r = Sqrt(-2.0F * Log(u1));
        float theta = PI2<float> * u2;
        return r * Sin(theta);
    }

    template <typename TGenerator>
    inline float NextNormal(TGenerator& generator, float mean, float stddev) noexcept
    {
        return mean + NextNormal(generator) * stddev;
    }

}
