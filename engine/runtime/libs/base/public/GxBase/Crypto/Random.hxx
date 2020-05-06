#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte::Crypto
{
    BASE_API Status GetRandomBytes(notstd::span<std::byte> buffer) noexcept;
}
