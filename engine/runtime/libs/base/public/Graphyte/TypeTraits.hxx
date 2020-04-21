#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte::Impl
{
    template <typename T, typename... Ts>
    inline constexpr bool IsAnyOfType = std::disjunction_v<std::is_same<T, Ts>...>;

    template <typename T>
    inline constexpr bool AlwaysFalse = false;

    template <typename T>
    struct InvalidType final
    {
        static_assert(AlwaysFalse<T>, "This specialization is not available");
    };
}
