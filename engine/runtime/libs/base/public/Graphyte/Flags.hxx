#pragma once
#include <Graphyte/Base.module.hxx>
#include <bitset>


namespace Graphyte
{
    struct Flags final
    {
        template <typename TEnumType>
        static constexpr TEnumType Set(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return TEnumType(
                underlying_type(value) | underlying_type(mask)
            );
        }

        template <typename TEnumType>
        static constexpr TEnumType Clear(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return TEnumType(
                underlying_type(value) & ~underlying_type(mask)
            );
        }

        template <typename TEnumType>
        static constexpr TEnumType Toggle(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return TEnumType(
                underlying_type(value) ^ underlying_type(mask)
            );
        }

        template <typename TEnumType>
        static constexpr TEnumType Mask(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return TEnumType(
                underlying_type(value) & underlying_type(mask)
            );
        }

        template <typename TEnumType>
        static constexpr TEnumType Change(TEnumType value, TEnumType set, TEnumType clear) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return TEnumType(
                (underlying_type(value) & underlying_type(clear)) | underlying_type(set)
            );
        }

        template <typename TEnumType>
        static constexpr bool Has(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return (underlying_type(value) & underlying_type(mask)) == underlying_type(mask);
        }

        template <typename TEnumType>
        static constexpr bool Any(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return (underlying_type(value) & underlying_type(mask)) != underlying_type(TEnumType{});
        }

        template <typename TEnumType>
        static constexpr bool None(TEnumType value, TEnumType mask) noexcept
        {
            using underlying_type = std::underlying_type_t<TEnumType>;
            return (underlying_type(value) & underlying_type(mask)) == underlying_type(TEnumType{});
        }
    };
}
