#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte
{
    [[nodiscard]] BASE_API uint32_t Crc32(
        std::span<std::byte const> buffer,
        uint32_t initial,
        bool finalize) noexcept;

    [[nodiscard]] BASE_API uint64_t Crc64(
        std::span<std::byte const> buffer,
        uint64_t initial,
        bool finalize) noexcept;
}
