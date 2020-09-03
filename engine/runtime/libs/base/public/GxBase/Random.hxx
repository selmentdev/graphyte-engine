#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Types.hxx>
#include <GxBase/Maths/Vector.hxx>

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

    extern BASE_API void Generate(RandomState& state, std::span<std::byte> buffer) noexcept;

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
    [[nodiscard]] extern BASE_API uint32_t NextUInt32(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API uint32_t NextUInt32(RandomState& state, uint32_t max) noexcept;
    [[nodiscard]] extern BASE_API uint32_t NextUInt32(RandomState& state, uint32_t min, uint32_t max) noexcept;

    [[nodiscard]] extern BASE_API UInt32x4 NextUInt32x4(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API UInt32x3 NextUInt32x3(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API UInt32x2 NextUInt32x2(RandomState& state) noexcept;

    [[nodiscard]] extern BASE_API uint64_t NextUInt64(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API uint64_t NextUInt64(RandomState& state, uint64_t max) noexcept;
    [[nodiscard]] extern BASE_API uint64_t NextUInt64(RandomState& state, uint64_t min, uint64_t max) noexcept;

    [[nodiscard]] extern BASE_API float NextFloat(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API float NextFloat(RandomState& state, float max) noexcept;
    [[nodiscard]] extern BASE_API float NextFloat(RandomState& state, float min, float max) noexcept;

    [[nodiscard]] extern BASE_API double NextDouble(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API double NextDouble(RandomState& state, double max) noexcept;
    [[nodiscard]] extern BASE_API double NextDouble(RandomState& state, double min, double max) noexcept;

    [[nodiscard]] extern BASE_API float NextLaplace(RandomState& state, float mean, float scale) noexcept;

    [[nodiscard]] extern BASE_API float NextNormal(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API float NextNormal(RandomState& state, float mean, float stddev) noexcept;

    [[nodiscard]] extern BASE_API Maths::Vector3 InsideUnitSphere(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API Maths::Vector3 OnUnitSphere(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API Maths::Vector2 OnUnitCircle(RandomState& state) noexcept;

    [[nodiscard]] extern BASE_API Maths::Vector4 NextVector4(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API Maths::Vector3 NextVector3(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API Maths::Vector2 NextVector2(RandomState& state) noexcept;

    [[nodiscard]] extern BASE_API Float4 NextFloat4(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API Float3 NextFloat3(RandomState& state) noexcept;
    [[nodiscard]] extern BASE_API Float2 NextFloat2(RandomState& state) noexcept;

    extern BASE_API void GenerateReadableString(RandomState& state, std::span<char> characters) noexcept;
}
