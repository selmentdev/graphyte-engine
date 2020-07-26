#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Constants.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    constexpr T E() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_E<T>;
    }

    template <typename T>
    constexpr T Log2E() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Log2E<T>;
    }

    template <typename T>
    constexpr T Log10E() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Log10E<T>;
    }

    template <typename T>
    constexpr T Ln2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Ln2<T>;
    }

    template <typename T>
    constexpr T Ln10() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Ln10<T>;
    }

    template <typename T>
    constexpr T Pi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Pi<T>;
    }

    template <typename T>
    constexpr T Pi2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Pi2<T>;
    }

    template <typename T>
    constexpr T InvPi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvPi<T>;
    }

    template <typename T>
    constexpr T InvPi2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvPi2<T>;
    }

    template <typename T>
    constexpr T InvSqrtPi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrtPi<T>;
    }

    template <typename T>
    constexpr T Sqrt2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Sqrt2<T>;
    }

    template <typename T>
    constexpr T Sqrt3() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Sqrt3<T>;
    }

    template <typename T>
    constexpr T Sqrt5() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Sqrt5<T>;
    }

    template <typename T>
    constexpr T InvSqrt2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrt2<T>;
    }

    template <typename T>
    constexpr T InvSqrt3() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrt3<T>;
    }

    template <typename T>
    constexpr T InvSqrt5() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrt5<T>;
    }

    template <typename T>
    constexpr T Phi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Phi<T>;
    }

    template <typename T>
    constexpr T Gamma() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Gamma<T>;
    }

    template <typename T>
    constexpr T PiDiv2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv2<T>;
    }

    template <typename T>
    constexpr T PiDiv3() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv3<T>;
    }

    template <typename T>
    constexpr T PiDiv4() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv4<T>;
    }

    template <typename T>
    constexpr T PiDiv6() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv6<T>;
    }

    template <typename T>
    constexpr T PiDiv8() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv8<T>;
    }

    template <typename T>
    constexpr T EpsilonAngular() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_EpsilonAngular<T>;
    }

    template <typename T>
    constexpr T EpsilonLow() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_EpsilonLow<T>;
    }

    template <typename T>
    constexpr T Epsilon() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Epsilon<T>;
    }

    template <typename T>
    constexpr T EpsilonHigh() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_EpsilonHigh<T>;
    }
}
