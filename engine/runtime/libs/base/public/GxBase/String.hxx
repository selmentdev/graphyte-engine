#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte
{
    /// @brief Replaces all occurences of substring in string.
    ///
    /// @param string   Provides string to modify.
    /// @param oldValue Provides string to be replaced.
    /// @param newValue Provides string to replace all occurences of @p oldValue.
    BASE_API void ReplaceAll(
        std::string& string,
        std::string_view from,
        std::string_view to) noexcept;

    /// @brief Splits string using specified string separator.
    ///
    /// @param value       Provides source string to split.
    /// @param separator   Provides separator string.
    /// @param removeEmpty Provides value indicating whether empty slices should be removed.
    ///
    /// @return The collection of slices of source string.
    [[nodiscard]] BASE_API std::vector<std::string_view> Split(
        std::string_view value,
        std::string_view separator,
        bool removeEmpty = true) noexcept;


    /// @brief Splits string using specified character separator.
    ///
    /// @param value       Provides source string to split.
    /// @param separator   Provides separator character.
    /// @param removeEmpty Provides value indicating whether empty slices should be removed.
    ///
    /// @return The collection of sliced parts of source string.
    [[nodiscard]] BASE_API std::vector<std::string_view> Split(
        std::string_view value,
        char separator,
        bool removeEmpty = true) noexcept;


    /// @brief Joins container of strings using separator into single string.
    ///
    /// @param container Provides container of strings.
    /// @param separator Provides separator string.
    ///
    /// @return The joined string.
    template <typename TContainer>
    [[nodiscard]] inline std::string Join(
        TContainer const& container,
        std::string_view separator) noexcept
    {
        std::string result{};

        auto it  = std::cbegin(container);
        auto end = std::cend(container);

        if (it != end)
        {
            result = *it;

            for (++it; it != end; ++it)
            {
                result += separator;
                result += *it;
            }
        }

        return result;
    }


    /// @brief Joins container of strings using separator into single string.
    ///
    /// @param container Provides container of strings.
    /// @param separator Provides separator string.
    ///
    /// @return The joined string.
    [[nodiscard]] inline std::string Join(
        std::initializer_list<std::string_view> container,
        std::string_view separator) noexcept
    {
        std::string result{};

        auto it  = std::begin(container);
        auto end = std::end(container);

        if (it != end)
        {
            result = *it;

            for (++it; it != end; ++it)
            {
                result += separator;
                result += *it;
            }
        }

        return result;
    }

    /// @brief Trims string left whitespace.
    ///
    /// @param value Provides string to left trim.
    ///
    /// @return The trimmed string.
    [[nodiscard]] inline std::string_view TrimLeft(
        std::string_view value) noexcept
    {
        std::size_t const offset = value.find_first_not_of(" \t\f\r\n\v\b");

        if (offset != std::string_view::npos)
        {
            return value.substr(offset);
        }

        return {};
    }

    /// @brief Trims string right whitespace.
    ///
    /// @param value Provides string to right trim.
    ///
    /// @return The trimmed string.
    [[nodiscard]] inline std::string_view TrimRight(
        std::string_view value) noexcept
    {
        std::size_t const offset = value.find_last_not_of(" \t\f\r\n\v\b");

        if (offset != std::string_view::npos)
        {
            return value.substr(0, offset + 1);
        }

        return value;
    }

    /// @brief Trims string both left and right whitespace.
    ///
    /// @param value Provides string to trim.
    ///
    /// @return The Trimmed string.
    [[nodiscard]] inline std::string_view Trim(
        std::string_view value) noexcept
    {
        return TrimLeft(TrimRight(value));
    }

    [[nodiscard]] BASE_API bool MatchWildcard(
        std::string_view::const_iterator pattern_first,
        std::string_view::const_iterator pattern_last,
        std::string_view::const_iterator value_first,
        std::string_view::const_iterator value_last) noexcept;

    /// @brief Matches wildcard pattern against value.
    ///
    /// @param pattern Provides wildcard pattern.
    /// @param value   Provides value to match.
    ///
    /// @return @c true when matched, @c false otherwise.
    [[nodiscard]] inline bool MatchWildcard(
        std::string_view pattern,
        std::string_view value) noexcept
    {
        return MatchWildcard(
            std::cbegin(pattern),
            std::cend(pattern),
            std::cbegin(value),
            std::cend(value));
    }

    [[nodiscard]] BASE_API bool HexStringToByteStream(
        std::vector<std::byte>& output,
        std::string_view input) noexcept;

    [[nodiscard]] BASE_API bool HexStringFromByteStream(
        std::string& output,
        std::span<const std::byte> input) noexcept;
}
