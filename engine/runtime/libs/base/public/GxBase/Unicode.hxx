/*------------------------------------------------------------------------------------------------*
    Copyright selmentdev 2019. All Rights reserved.
 *------------------------------------------------------------------------------------------------*/

#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Text
{
    // Based on LLVM ConvertUTF.cpp

    enum struct ConversionResult
    {
        Success,
        SourceExhausted,
        TargetExhausted,
        SourceIllegal,
    };

    enum struct ConversionType
    {
        /// Strict conversion breaks on non-convertible byte sequences.
        Strict,

        /// Tolerant conversion uses replacement characters on failure.
        Tolerant,
    };

    /// @brief Converts range of chars from UTF8 to UTF16.
    ///
    /// @details Parameters @p source_start and @p target_start are updated accordingly.
    ///
    /// @param source_start Provides location of source characters range.
    /// @param source_end   Provides end of source characters range.
    /// @param target_start Provides location of destination character range.
    /// @param target_end   Provides end of destination characters range.
    /// @param type         Provides type of conversion.
    ///
    /// @return The result of conversion.
    BASE_API ConversionResult ConvertUTF8ToUTF16(
        const char8_t** source_start,
        const char8_t* source_end,
        char16_t** target_start,
        char16_t* target_end,
        ConversionType type) noexcept;

    /// @brief Converts range of characters from UTF8 to UTF32.
    ///
    /// @details Patameters \p source_start and \p target_start are updated accordingly.
    ///
    /// @param source_start Provides location of source characters range.
    /// @param source_end   Provides end of source characters range.
    /// @param target_start Provides location of destination characters range.
    /// @param target_end   Provides end of destination characters range.
    /// @param type         Provides type of conversion.
    ///
    /// @return The result of conversion.
    BASE_API ConversionResult ConvertUTF8ToUTF32Partial(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type) noexcept;

    /// @brief Converts range of characters from UTF8 to UTF32.
    ///
    /// @details Patameters \p source_start and \p target_start are updated accordingly.
    ///
    /// @param source_start Provides location of source characters range.
    /// @param source_end   Provides end of source characters range.
    /// @param target_start Provides location of destination characters range.
    /// @param target_end   Provides end of destination characters range.
    /// @param type         Provides type of conversion.
    ///
    /// @return The result of conversion.
    BASE_API ConversionResult ConvertUTF8ToUTF32(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertUTF16ToUTF8(
        const char16_t** source_start,
        const char16_t* source_end,
        char8_t** target_start,
        char8_t* target_end,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertUTF32ToUTF8(
        const char32_t** source_start,
        const char32_t* source_end,
        char8_t** target_start,
        char8_t* target_end,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertUTF16ToUTF32(
        const char16_t** source_start,
        const char16_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertUTF32ToUTF16(
        const char32_t** source_start,
        const char32_t* source_end,
        char16_t** target_start,
        char16_t* target_end, ConversionType type) noexcept;

    BASE_API bool IsLegalUTF8Sequence(
        const char8_t* source_start,
        const char8_t* source_end) noexcept;

    BASE_API bool IsLegalUTF8String(
        const char8_t** source_start,
        const char8_t* source_end) noexcept;

    BASE_API size_t GetBytesCountForUTF8(
        char8_t leading_byte) noexcept;

    BASE_API ConversionResult ConvertUTF8Sequence(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t* target,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertUTF8Sequence(
        char32_t character,
        char8_t** target_start,
        char8_t* target_end,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::string_view source,
        std::wstring& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::wstring_view source,
        std::string& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::string_view source,
        std::u16string& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::string_view source,
        std::u32string& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::u16string_view source,
        std::string& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::u32string_view source,
        std::string& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::u16string_view source,
        std::u32string& result,
        ConversionType type) noexcept;

    BASE_API ConversionResult ConvertString(
        std::u32string_view source,
        std::u16string& result,
        ConversionType type) noexcept;
}
