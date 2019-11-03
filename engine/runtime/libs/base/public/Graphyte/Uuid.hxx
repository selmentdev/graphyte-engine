#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Converter.hxx>

// =================================================================================================
//
// Uuid class definition.
//

namespace Graphyte
{
    struct Uuid final
    {
    public:
        uint64_t Low;
        uint64_t High;

        BASE_API static Uuid Create() noexcept;

    public:
        bool IsEmpty() const noexcept
        {
            return (this->Low | this->High) == 0;
        }
    };

    static_assert(sizeof(Uuid) == 16);
    static_assert(alignof(Uuid) == alignof(uint64_t));

    constexpr bool Equals(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return ((lhs.Low ^ rhs.Low) | (lhs.High ^ rhs.High)) == 0;
    }

    constexpr int Compare(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        if (lhs.High == rhs.High)
        {
            if (lhs.Low < rhs.Low)
            {
                return -1;
            }

            if (lhs.Low > rhs.Low)
            {
                return 1;
            }

            return 0;
        }

        if (lhs.High < rhs.High)
        {
            return -1;
        }

        return 1;
    }

    constexpr bool operator==(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return Equals(lhs, rhs);
    }

    constexpr bool operator!=(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return !Equals(lhs, rhs);
    }

    constexpr bool operator<(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return Compare(lhs, rhs) < 0;
    }

    constexpr bool operator<=(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return Compare(lhs, rhs) <= 0;
    }

    constexpr bool operator>(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return Compare(lhs, rhs) > 0;
    }

    constexpr bool operator>=(Uuid const& lhs, Uuid const& rhs) noexcept
    {
        return Compare(lhs, rhs) >= 0;
    }
}


// =================================================================================================
//
// Converter support.
//

template <>
struct Graphyte::Converter<Graphyte::Uuid> final
{
    BASE_API static bool ToString(std::string& result, Graphyte::Uuid const& value) noexcept;

    BASE_API static bool FromString(Graphyte::Uuid& result, std::string_view value) noexcept;
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
