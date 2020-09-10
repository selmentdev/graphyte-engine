#pragma once
#include <GxBase/Base.module.hxx>

// =================================================================================================
//
// Default converter implementation.
//

namespace Graphyte
{
    template <typename T>
    struct Converter;
}


// =================================================================================================
//
// Common types support.
//

namespace Graphyte
{
    template <>
    struct Converter<bool> final
    {
        [[nodiscard]] static std::string_view ToString(bool value) noexcept
        {
            return value ? "true" : "false";
        }

        static bool FromString(bool& result, std::string_view value) noexcept
        {
            if (value == "true")
            {
                result = true;
                return true;
            }
            else if (value == "false")
            {
                result = false;
                return true;
            }

            return false;
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<float> final
    {
        [[nodiscard]] static std::string ToString(float value) noexcept
        {
#if GX_COMPILER_MSVC

            char buffer[80];

            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value);

            return { buffer, end };

#else

            return fmt::format("{}", value);

#endif
        }

        static bool FromString(float& result, std::string_view value) noexcept
        {
#if GX_COMPILER_MSVC

            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));

#else

            std::string buffer{ value };
            errno = 0;
            char* endptr{};
            result = strtof(buffer.c_str(), &endptr);
            return errno == 0;

#endif
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<double> final
    {
        [[nodiscard]] static std::string ToString(double value) noexcept
        {
#if GX_COMPILER_MSVC

            char buffer[80];

            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value);

            return { buffer, end };

#else
            return fmt::format("{}", value);
#endif
        }

        static bool FromString(double& result, std::string_view value) noexcept
        {
#if GX_COMPILER_MSVC

            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));

#else
            std::string buffer{ value };
            errno = 0;
            char* endptr{};
            result = strtod(buffer.c_str(), &endptr);
            return errno == 0;
#endif
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<signed char> final
    {
        [[nodiscard]] static std::string ToString(signed char value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(signed char& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };

    template <>
    struct Converter<unsigned char> final
    {
        [[nodiscard]] static std::string ToString(unsigned char value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(unsigned char& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<signed short> final
    {
        [[nodiscard]] static std::string ToString(signed short value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(signed short& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };

    template <>
    struct Converter<unsigned short> final
    {
        [[nodiscard]] static std::string ToString(unsigned short value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(unsigned short& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<signed int> final
    {
        [[nodiscard]] static std::string ToString(signed int value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(signed int& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };

    template <>
    struct Converter<unsigned int> final
    {
        [[nodiscard]] static std::string ToString(unsigned int value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(unsigned int& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<signed long> final
    {
        [[nodiscard]] static std::string ToString(signed long value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(signed long& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };

    template <>
    struct Converter<unsigned long> final
    {
        [[nodiscard]] static std::string ToString(unsigned long value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(unsigned long& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<signed long long> final
    {
        [[nodiscard]] static std::string ToString(signed long long value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(signed long long& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };

    template <>
    struct Converter<unsigned long long> final
    {
        [[nodiscard]] static std::string ToString(unsigned long long value, int radix = 10) noexcept
        {
            char buffer[80];
            auto [end, ec] = std::to_chars(
                std::data(buffer),
                std::data(buffer) + std::size(buffer),
                value,
                radix);

            return { buffer, end };
        }

        static bool FromString(unsigned long long& result, std::string_view value, int radix = 10) noexcept
        {
            auto [end, ec] = std::from_chars(
                std::data(value),
                std::data(value) + std::size(value),
                result,
                radix);

            return (ec == std::errc{})
                   && (end == (std::data(value) + std::size(value)));
        }
    };
}

namespace Graphyte
{
    template <>
    struct Converter<std::string_view> final
    {
        [[nodiscard]] static std::string_view ToString(std::string_view value) noexcept
        {
            return value;
        }

        [[nodiscard]] static std::string_view FromString(std::string_view value) noexcept
        {
            return value;
        }
    };
}
