#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Converter.hxx>

// =================================================================================================
//
// Uuid class definition.
//

namespace Graphyte
{
    struct Uuid final
    {
        uint64_t Low;
        uint64_t High;

        [[nodiscard]] BASE_API static Uuid Create() noexcept;

        [[nodiscard]] bool IsEmpty() const noexcept
        {
            return (this->Low | this->High) == 0;
        }

        constexpr auto operator<=>(Uuid const& rhs) const noexcept = default;
    };

    static_assert(sizeof(Uuid) == 16);
    static_assert(alignof(Uuid) == alignof(uint64_t));
}


// =================================================================================================
//
// Converter support.
//

template <>
struct Graphyte::Converter<Graphyte::Uuid> final
{
    [[nodiscard]] BASE_API static bool ToString(std::string& result, Graphyte::Uuid const& value) noexcept;

    [[nodiscard]] BASE_API static bool FromString(Graphyte::Uuid& result, std::string_view value) noexcept;
};


// =================================================================================================
//
// std::format support.
//

template <>
struct fmt::formatter<Graphyte::Uuid>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& context)
    {
        return context.begin();
    }

    template <typename FormatContext>
    auto format(Graphyte::Uuid const& value, FormatContext& context)
    {
        return format_to(context.out(), "{:016x}{:016x}", value.Low, value.High);
    }
};
