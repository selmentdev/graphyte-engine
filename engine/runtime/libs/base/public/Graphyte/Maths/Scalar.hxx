#pragma once
#include <Graphyte/Maths/Base.hxx>

namespace Graphyte::MathsX
{
    template <>
    mathinline float mathcall Pi<float>() noexcept
    {
        return MathsX::Impl::PI<float>;
    }

    template <>
    mathinline float mathcall Pi2<float>() noexcept
    {
        return MathsX::Impl::PI2<float>;
    }

    template <>
    mathinline float mathcall OneOverPi<float>() noexcept
    {
        return MathsX::Impl::ONE_OVER_PI<float>;
    }

    template <>
    mathinline float mathcall OneOverPi2<float>() noexcept
    {
        return MathsX::Impl::ONE_OVER_PI2<float>;
    }

    template <>
    mathinline float mathcall PiOver2<float>() noexcept
    {
        return MathsX::Impl::PI_OVER_2<float>;
    }

    template <>
    mathinline float mathcall E<float>() noexcept
    {
        return MathsX::Impl::E<float>;
    }
}
