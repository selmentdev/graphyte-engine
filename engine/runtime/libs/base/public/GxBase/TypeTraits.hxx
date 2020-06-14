#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte
{
    template <typename T, typename... Ts>
    inline constexpr bool IsAnyOfType = std::disjunction_v<std::is_same<T, Ts>...>;

    template <typename T>
    inline constexpr bool IsStandardUnsignedType = IsAnyOfType<
        std::remove_cv_t<T>,
        unsigned char,
        unsigned short,
        unsigned int,
        unsigned long,
        unsigned long long>;

    template <typename T>
    inline constexpr bool AlwaysFalse = false;

    template <typename T>
    struct InvalidType final
    {
        static_assert(AlwaysFalse<T>, "This specialization is not available");
    };
}
