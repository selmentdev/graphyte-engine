#pragma once
#include <GxBase/Span.hxx>

namespace Graphyte
{
    BASE_API uint32_t Crc32(
        notstd::span<std::byte const> buffer,
        uint32_t initial,
        bool finalize) noexcept;

    BASE_API uint64_t Crc64(
        notstd::span<std::byte const> buffer,
        uint64_t initial,
        bool finalize) noexcept;
}
