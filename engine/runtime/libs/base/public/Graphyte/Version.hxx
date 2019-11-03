#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Converter.hxx>


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
            return Major == 0
                && Minor == 0
                && Patch == 0
                && Build == 0;
        }
    };
}


// =================================================================================================
//
// Converter specialization.
//

template<>
struct Graphyte::Converter<Graphyte::Version> final
{
    BASE_API static bool ToString(std::string& result, Graphyte::Version const& value) noexcept;
    BASE_API static bool FromString(Graphyte::Version& result, std::string_view value) noexcept;
};


// =================================================================================================
//
// std::format specialization.
//

template<>
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
            value.Build
        );
    }
};
