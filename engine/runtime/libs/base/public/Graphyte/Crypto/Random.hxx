#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Status.hxx>
#include <Graphyte/Span.hxx>

namespace Graphyte::Crypto
{
    BASE_API Status GetRandomBytes(notstd::span<std::byte> buffer) noexcept;
}
