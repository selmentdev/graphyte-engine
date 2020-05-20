#include <GxBase/Random.hxx>
#include <GxBase/Bitwise.hxx>
#include <GxBase/Maths.hxx>

namespace Graphyte::Random::Impl
{
    uint64_t SplitMix64(uint64_t& seed) noexcept
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
    void Initialize(RandomState& state, uint64_t seed) noexcept
    {
        state.State[0] = Impl::SplitMix64(seed);
        state.State[1] = Impl::SplitMix64(seed);
        state.State[2] = Impl::SplitMix64(seed);
        state.State[3] = Impl::SplitMix64(seed);
    }

    void Generate(RandomState& state, notstd::span<std::byte> buffer) noexcept
    {
        while (buffer.size() >= sizeof(uint64_t))
        {
            uint64_t const sample = NextUInt64(state);
            memcpy(buffer.data(), &sample, sizeof(uint64_t));

            buffer.remove_prefix(sizeof(uint64_t));
        }

        if (!buffer.empty())
        {
            uint64_t const sample = NextUInt64(state);
            memcpy(buffer.data(), &sample, buffer.size());
        }
    }

    void Skip2p128(RandomState& state) noexcept
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

                NextUInt64(state);
            }
        }

        state.State[0] = s0;
        state.State[1] = s1;
        state.State[2] = s2;
        state.State[3] = s3;
    }

    void Skip2p192(RandomState& state) noexcept
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

                NextUInt64(state);
            }
        }

        state.State[0] = s0;
        state.State[1] = s1;
        state.State[2] = s2;
        state.State[3] = s3;
    }
}

namespace Graphyte::Random
{
    uint32_t NextUInt32(RandomState& state) noexcept
    {
        uint64_t const sample = NextUInt64(state);
        uint32_t const hi = static_cast<uint32_t>(sample >> 32u);
        uint32_t const lo = static_cast<uint32_t>(sample);
        uint32_t const result = hi ^ lo;
        return result;
    }

    uint32_t NextUInt32(RandomState& state, uint32_t max) noexcept
    {
        uint32_t const result = NextUInt32(state, 0, max);
        return result;
    }

    uint32_t NextUInt32(RandomState& state, uint32_t min, uint32_t max) noexcept
    {
        uint32_t const range = (max - min);
        static constexpr uint32_t max_value = std::numeric_limits<uint32_t>::max();

        if (range == max_value)
        {
            return NextUInt32(state);
        }
        else
        {
            uint32_t const span = range + 1;
            uint32_t const limit = max_value - (max_value % span);

            uint32_t result;

            do
            {
                result = NextUInt32(state);
            } while (result >= limit);

            return min + (result % span);
        }
    }

    UInt32x4 NextUInt32x4(RandomState& state) noexcept
    {
        uint64_t const lo = NextUInt64(state);
        uint64_t const hi = NextUInt64(state);

        return UInt32x4{
            .X = static_cast<uint32_t>(lo),
            .Y = static_cast<uint32_t>(hi),
            .Z = static_cast<uint32_t>(lo >> 32u),
            .W = static_cast<uint32_t>(hi >> 32u),
        };
    }

    UInt32x3 NextUInt32x3(RandomState& state) noexcept
    {
        uint64_t const lo = NextUInt64(state);
        uint64_t const hi = NextUInt64(state);

        return UInt32x3{
            .X = static_cast<uint32_t>(lo),
            .Y = static_cast<uint32_t>(hi),
            .Z = static_cast<uint32_t>(lo >> 32u) ^ static_cast<uint32_t>(hi >> 32u),
        };
    }

    UInt32x2 NextUInt32x2(RandomState& state) noexcept
    {
        uint64_t const sample = NextUInt64(state);

        return UInt32x2{
            .X = static_cast<uint32_t>(sample),
            .Y = static_cast<uint32_t>(sample >> 32u),
        };
    }

    uint64_t NextUInt64(RandomState& state) noexcept
    {
        uint64_t const result = BitRotateLeft<uint64_t>(state.State[1] * 5, 7) * 9;

        uint64_t const t = state.State[1] << 17;

        state.State[2] ^= state.State[0];
        state.State[3] ^= state.State[1];
        state.State[1] ^= state.State[2];
        state.State[0] ^= state.State[3];

        state.State[2] ^= t;
        state.State[3] = BitRotateLeft<uint64_t>(state.State[3], 45);

        return result;
    }

    uint64_t NextUInt64(RandomState& state, uint64_t max) noexcept
    {
        uint64_t const result = NextUInt64(state, 0, max);
        return result;
    }

    uint64_t NextUInt64(RandomState& state, uint64_t min, uint64_t max) noexcept
    {
        uint64_t const range = (max - min);
        static constexpr uint64_t max_value = std::numeric_limits<uint64_t>::max();

        if (range == max_value)
        {
            return NextUInt64(state);
        }
        else
        {
            uint64_t const span = range + 1;
            uint64_t const limit = max_value - (max_value % span);

            uint64_t result;

            do
            {
                result = NextUInt64(state);
            } while (result >= limit);

            return min + (result % span);
        }
    }

    float NextFloat(RandomState& state) noexcept
    {
        uint32_t const sample = NextUInt32(state);
        return FloatTraits<float>::Range12FromHighBits(sample) - 1.0f;
    }

    float NextFloat(RandomState& state, float max) noexcept
    {
        float const sample = NextFloat(state);
        float const result = sample * max;
        return result;
    }

    float NextFloat(RandomState& state, float min, float max) noexcept
    {
        float const sample = NextFloat(state);
        float const scale = (max - min);
        float const result = (sample * scale) + min;
        return result;
    }

    double NextDouble(RandomState& state) noexcept
    {
        uint64_t const sample = NextUInt64(state);
        return FloatTraits<double>::Range12FromHighBits(sample) - 1.0f;
    }

    double NextDouble(RandomState& state, double max) noexcept
    {
        double const sample = NextDouble(state);
        double const result = sample * max;
        return result;
    }

    double NextDouble(RandomState& state, double min, double max) noexcept
    {
        double const sample = NextDouble(state);
        double const scale = (max - min);
        double const result = (sample * scale) + min;
        return result;
    }

    float NextLaplace(RandomState& state, float mean, float scale) noexcept
    {
        float const sample = NextFloat(state);

        return (sample < 0.5f)
            ? (mean + scale * std::log2(2.0f * sample))
            : (mean - scale * std::log2(2.0f * (1.0f - sample)));
    }

    float NextNormal(RandomState& state) noexcept
    {
        Float2 const sample = NextFloat2(state);

        float const r = Maths::Sqrt(-2.0f * Maths::Log(sample.X));
        float const theta = sample.Y * Maths::Pi2<float>();
        float const result = r * Maths::Sin(theta);
        return result;
    }

    float NextNormal(RandomState& state, float mean, float stddev) noexcept
    {
        return mean + NextNormal(state) * stddev;
    }

    Vector3 InsideUnitSphere(RandomState& state) noexcept
    {
        float const theta = NextFloat(state, Maths::Pi2<float>());
        float const v = NextFloat(state);
        float const phi = Maths::Acos((2.0f * v) - 1.0f);
        float const r = Maths::Power(NextFloat(state), 1.0f / 3.0f);

        auto [sin_phi, cos_phi] = Maths::SinCos(phi);
        auto [sin_theta, cos_theta] = Maths::SinCos(theta);

        return Maths::Make<Vector3>(
            r * sin_phi * cos_theta,
            r * sin_phi * sin_theta,
            r * cos_phi
        );
    }

    Vector3 OnUnitSphere(RandomState& state) noexcept
    {
        float const x = NextNormal(state);
        float const y = NextNormal(state);
        float const z = NextNormal(state);

        Vector3 const r = Maths::Make<Vector3>(x, y, z);
        return Maths::Normalize(r);
    }

    Vector2 OnUnitCircle(RandomState& state) noexcept
    {
        float const theta = NextFloat(state, Maths::Pi2<float>());
        Float2 const coords = Maths::SinCos(theta);
        return Maths::Load<Vector2>(&coords);
    }

    Vector4 NextVector4(RandomState& state) noexcept
    {
        Float4 const sample = NextFloat4(state);
        return Maths::Load<Vector4>(&sample);
    }

    Vector3 NextVector3(RandomState& state) noexcept
    {
        Float3 const sample = NextFloat3(state);
        return Maths::Load<Vector3>(&sample);
    }

    Vector2 NextVector2(RandomState& state) noexcept
    {
        Float2 const sample = NextFloat2(state);
        return Maths::Load<Vector2>(&sample);
    }

    Float4 NextFloat4(RandomState& state) noexcept
    {
        UInt32x4 const sample = NextUInt32x4(state);

        return Float4{
            .X = FloatTraits<float>::Range12FromHighBits(sample.X) - 1.0f,
            .Y = FloatTraits<float>::Range12FromHighBits(sample.Y) - 1.0f,
            .Z = FloatTraits<float>::Range12FromHighBits(sample.Z) - 1.0f,
            .W = FloatTraits<float>::Range12FromHighBits(sample.W) - 1.0f,
        };
    }

    Float3 NextFloat3(RandomState& state) noexcept
    {
        UInt32x3 const sample = NextUInt32x3(state);

        return Float3{
            .X = FloatTraits<float>::Range12FromHighBits(sample.X) - 1.0f,
            .Y = FloatTraits<float>::Range12FromHighBits(sample.Y) - 1.0f,
            .Z = FloatTraits<float>::Range12FromHighBits(sample.Z) - 1.0f,
        };
    }

    Float2 NextFloat2(RandomState& state) noexcept
    {
        UInt32x2 const sample = NextUInt32x2(state);

        return Float2{
            .X = FloatTraits<float>::Range12FromHighBits(sample.X) - 1.0f,
            .Y = FloatTraits<float>::Range12FromHighBits(sample.Y) - 1.0f,
        };
    }
}
