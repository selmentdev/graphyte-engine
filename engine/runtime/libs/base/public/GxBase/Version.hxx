#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Converter.hxx>


// =================================================================================================
//
// Version struct.
//

namespace Graphyte
{
    struct Version final
    {
        uint32_t Major;
        uint32_t Minor;
        uint32_t Patch;
        uint32_t Build;

        constexpr bool IsEmpty() const noexcept
        {
            return (this->Major | this->Minor | this->Patch | this->Build) == 0;
        }

        constexpr auto operator<=>(Version const& rhs) const noexcept = default;
    };
}


// =================================================================================================
//
// Converter specialization.
//

template <>
struct Graphyte::Converter<Graphyte::Version> final
{
    BASE_API static bool ToString(std::string& result, Graphyte::Version const& value) noexcept;
    BASE_API static bool FromString(Graphyte::Version& result, std::string_view value) noexcept;
};


// =================================================================================================
//
// std::format specialization.
//

template <>
struct fmt::formatter<Graphyte::Version>
{
    template <typename ParseContext>
    constexpr auto Parse(ParseContext& context)
    {
        return context.begin();
    }

    template <typename FormatContext>
    auto format(Graphyte::Version const& value, FormatContext& context)
    {
        return format_to(context.out(), "{:d}.{:d}.{:d}.{:d}",
            value.Major,
            value.Minor,
            value.Patch,
            value.Build);
    }
};
