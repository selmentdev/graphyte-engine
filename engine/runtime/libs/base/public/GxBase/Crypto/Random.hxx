#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte::Crypto
{
    //! \brief Generates crypto secure sequence of bytes.
    //!
    //! \param buffer Returns buffer of random number bytes.
    //!
    //! \return The status code.
    BASE_API Status GetRandomBytes(
        notstd::span<std::byte> buffer) noexcept;
}
