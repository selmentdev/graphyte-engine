#include "Base.pch.hxx"
#include <Graphyte/Unicode.hxx>
#include <Graphyte/Diagnostics.hxx>

// http://llvm.org/doxygen/ConvertUTF_8cpp_source.html
// http://llvm.org/doxygen/ConvertUTF_8h_source.html

namespace Graphyte::Text::Impl
{
    constexpr const size_t HalfShift = 10;
    constexpr const char32_t HalfBase = 0x0010000;
    constexpr const char32_t HalfMask = 0x3FF;
    constexpr const char32_t SurrogateHighStart = 0xD800;
    constexpr const char32_t SurrogateHighEnd = 0xDBFF;
    constexpr const char32_t SurrogateLowStart = 0xDC00;
    constexpr const char32_t SurrogateLowEnd = 0xDFFF;
    constexpr const char32_t Unicode_ReplacementChar = 0x0000FFFD;
    constexpr const char32_t Unicode_MaxBmp = 0x0000FFFF;
    constexpr const char32_t Unicode_MaxUTF16 = 0x0010FFFF;
    //constexpr const char32_t Unicode_MaxUTF32 = 0x7FFFFFFF;
    constexpr const char32_t Unicode_MaxLegalUTF32 = 0x0010FFFF;
    constexpr const size_t Unicode_MaxUTF8BytesPerCodeUnit = 4;
    //constexpr const char16_t Unicode_UTF16ByteOrderMarkNative = 0xFEFF;
    //constexpr const char16_t Unicode_UTF16ByteOrderMarkSwapped = 0xFFFE;

    static const uint8_t TrailingBytesForUTF8[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5
    };

    static const char32_t OffsetsFromUTF8[6] = {
        0x00000000, 0x00003080, 0x000E2080,
        0x03C82080, 0xFA082080, 0x82082080
    };

    static const char8_t FirstByteMark[7] = {
        0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
    };
}

namespace Graphyte::Text
{
    ConversionResult ConvertUTF32ToUTF16(
        const char32_t** source_start,
        const char32_t* source_end,
        char16_t** target_start,
        char16_t* target_end,
        ConversionType type
    ) noexcept
    {
        ConversionResult result = ConversionResult::Success;
        const char32_t* source = *source_start;
        char16_t* target = *target_start;

        while (source < source_end)
        {
            if (target >= target_end)
            {
                result = ConversionResult::TargetExhausted;
                break;
            }

            char32_t ch = (*source++);

            if (ch <= Impl::Unicode_MaxBmp)
            {
                if (ch >= Impl::SurrogateHighStart && ch <= Impl::SurrogateLowEnd)
                {
                    if (type == ConversionType::Strict)
                    {
                        --source;
                        result = ConversionResult::SourceIllegal;
                        break;
                    }
                    else
                    {
                        (*target++) = static_cast<char16_t>(Impl::Unicode_ReplacementChar);
                    }
                }
                else
                {
                    (*target++) = static_cast<char16_t>(ch);
                }
            }
            else if (ch > Impl::Unicode_MaxLegalUTF32)
            {
                if (type == ConversionType::Strict)
                {
                    result = ConversionResult::SourceIllegal;
                }
                else
                {
                    (*target++) = static_cast<char16_t>(Impl::Unicode_ReplacementChar);
                }
            }
            else
            {
                if ((target + 1) >= target_end)
                {
                    --source;
                    result = ConversionResult::TargetExhausted;
                    break;
                }

                ch -= Impl::HalfBase;

                (*target++) = static_cast<char16_t>((ch >> Impl::HalfShift) + Impl::SurrogateHighStart);
                (*target++) = static_cast<char16_t>((ch & Impl::HalfMask) + Impl::SurrogateLowStart);
            }
        }

        (*source_start) = source;
        (*target_start) = target;

        return result;
    }

    ConversionResult ConvertUTF16ToUTF32(
        const char16_t** source_start,
        const char16_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type
    ) noexcept
    {
        ConversionResult result = ConversionResult::Success;

        const char16_t* source = (*source_start);
        char32_t* target = (*target_start);

        while (source < source_end)
        {
            const char16_t* old_source = source;

            char32_t ch = (*source++);

            if (ch >= Impl::SurrogateHighStart && ch <= Impl::SurrogateHighEnd)
            {
                if (source < source_end)
                {
                    char32_t ch2 = (*source);

                    if (ch2 >= Impl::SurrogateLowStart && ch2 <= Impl::SurrogateLowEnd)
                    {
                        ch = ((ch - Impl::SurrogateHighStart) << Impl::HalfShift) + (ch2 - Impl::SurrogateLowStart) + Impl::HalfBase;
                        ++source;
                    }
                    else if (type == ConversionType::Strict)
                    {
                        --source;
                        result = ConversionResult::SourceIllegal;
                        break;
                    }
                }
                else
                {
                    --source;
                    result = ConversionResult::SourceExhausted;
                    break;
                }
            }
            else if (type == ConversionType::Strict)
            {
                if (ch >= Impl::SurrogateLowStart && ch <= Impl::SurrogateLowEnd)
                {
                    --source;
                    result = ConversionResult::SourceIllegal;
                    break;
                }
            }
            
            if (target >= target_end)
            {
                source = old_source;
                result = ConversionResult::TargetExhausted;
                break;
            }

            (*target++) = ch;
        }

        (*source_start) = source;
        (*target_start) = target;

        return result;
    }

    ConversionResult ConvertUTF16ToUTF8(
        const char16_t** source_start,
        const char16_t* source_end,
        char8_t** target_start,
        char8_t* target_end,
        ConversionType type
    ) noexcept
    {
        ConversionResult result = ConversionResult::Success;
        const char16_t* source = (*source_start);
        char8_t* target = (*target_start);

        while (source < source_end)
        {
            const char32_t byte_mask = 0xBF;
            const char32_t byte_mark = 0x80;
            const char16_t* old_source = source;

            char32_t ch = (*source++);

            if (ch >= Impl::SurrogateHighStart && ch <= Impl::SurrogateHighEnd)
            {
                if (source < source_end)
                {
                    char32_t ch2 = (*source);

                    if (ch2 >= Impl::SurrogateLowStart && ch2 <= Impl::SurrogateLowEnd)
                    {
                        ch = ((ch - Impl::SurrogateHighStart) << Impl::HalfShift) + (ch2 - Impl::SurrogateLowStart) + Impl::HalfBase;
                        ++source;
                    }
                    else if (type == ConversionType::Strict)
                    {
                        --source;
                        result = ConversionResult::SourceIllegal;
                        break;
                    }
                }
                else
                {
                    --source;
                    result = ConversionResult::SourceExhausted;
                    break;
                }
            }
            else if (type == ConversionType::Strict)
            {
                if (ch >= Impl::SurrogateLowStart && ch <= Impl::SurrogateLowEnd)
                {
                    --source;
                    result = ConversionResult::SourceIllegal;
                    break;
                }
            }

            size_t bytes_to_write = 0;
            if (ch <= static_cast<char32_t>(0x80))
            {
                bytes_to_write = 1;
            }
            else if (ch <= static_cast<char32_t>(0x800))
            {
                bytes_to_write = 2;
            }
            else if (ch <= static_cast<char32_t>(0x10000))
            {
                bytes_to_write = 3;
            }
            else if (ch <= static_cast<char32_t>(0x110000))
            {
                bytes_to_write = 4;
            }
            else
            {
                bytes_to_write = 3;
                ch = Impl::Unicode_ReplacementChar;
            }

            target += bytes_to_write;

            if (target > target_end)
            {
                source = old_source;
                target -= bytes_to_write;
                result = ConversionResult::TargetExhausted;
                break;
            }

            switch (bytes_to_write)
            {
            case 4:
                (*--target) = static_cast<char8_t>((ch | byte_mark) & byte_mask);
                ch >>= 6;
                [[fallthrough]];
            case 3:
                (*--target) = static_cast<char8_t>((ch | byte_mark) & byte_mask);
                ch >>= 6;
                [[fallthrough]];
            case 2:
                (*--target) = static_cast<char8_t>((ch | byte_mark) & byte_mask);
                ch >>= 6;
                [[fallthrough]];
            case 1:
                (*--target) = static_cast<char8_t>(ch | Impl::FirstByteMark[bytes_to_write]);
                break;
            }

            target += bytes_to_write;
        }

        (*source_start) = source;
        (*target_start) = target;

        return result;
    }

    ConversionResult ConvertUTF32ToUTF8(
        const char32_t** source_start,
        const char32_t* source_end,
        char8_t** target_start,
        char8_t* target_end,
        ConversionType type
    ) noexcept
    {
        ConversionResult result = ConversionResult::Success;
        const char32_t* source = (*source_start);
        char8_t* target = (*target_start);

        while (source < source_end)
        {
            const char32_t byte_mask = 0xBF;
            const char32_t byte_mark = 0x80;

            char32_t ch = (*source++);

            if (type == ConversionType::Strict)
            {
                if (ch >= Impl::SurrogateHighStart && ch <= Impl::SurrogateLowEnd)
                {
                    --source;
                    result = ConversionResult::SourceIllegal;
                    break;
                }
            }

            size_t bytes_to_write = 0;
            if (ch <= static_cast<char32_t>(0x80))
            {
                bytes_to_write = 1;
            }
            else if (ch <= static_cast<char32_t>(0x800))
            {
                bytes_to_write = 2;
            }
            else if (ch <= static_cast<char32_t>(0x10000))
            {
                bytes_to_write = 3;
            }
            else if (ch <= Impl::Unicode_MaxLegalUTF32)
            {
                bytes_to_write = 4;
            }
            else
            {
                bytes_to_write = 3;
                ch = Impl::Unicode_ReplacementChar;
                result = ConversionResult::SourceIllegal;
            }

            target += bytes_to_write;

            if (target > target_end)
            {
                --source;
                target -= bytes_to_write;
                result = ConversionResult::TargetExhausted;
                break;
            }

            switch (bytes_to_write)
            {
            case  4:
                (*--target) = static_cast<char8_t>((ch | byte_mark) & byte_mask);
                ch >>= 6;
                [[fallthrough]];
            case 3:
                (*--target) = static_cast<char8_t>((ch | byte_mark) & byte_mask);
                ch >>= 6;
                [[fallthrough]];
            case 2:
                (*--target) = static_cast<char8_t>((ch | byte_mark) & byte_mask);
                ch >>= 6;
                [[fallthrough]];
            case 1:
                (*--target) = static_cast<char8_t>(ch | Impl::FirstByteMark[bytes_to_write]);
                break;
            }

            target += bytes_to_write;
        }

        (*source_start) = source;
        (*target_start) = target;

        return result;
    }

    static bool IsLegalUTF8(
        const char8_t* source,
        size_t length
    ) noexcept
    {
        const char8_t* end = source + length;
        char8_t a;

        switch (length)
        {
        default:
            return false;
        case 4:
            if ((a = (*--end)) < 0x80 || a > 0xBF)
            {
                return false;
            }
            [[fallthrough]];
        case 3:
            if ((a = (*--end)) < 0x80 || a > 0xBF)
            {
                return false;
            }
            [[fallthrough]];
        case 2:
            if ((a = (*--end)) < 0x80 || a > 0xBF)
            {
                return false;
            }

            switch (*source)
            {
            case 0xE0:
                if (a < 0xA0)
                {
                    return false;
                }
                break;
            case 0xED:
                if (a > 0x9F)
                {
                    return false;
                }
                break;
            case 0xF0:
                if (a < 0x90)
                {
                    return false;
                }
                break;
            case 0xF4:
                if (a > 0x8F)
                {
                    return false;
                }
                break;
            default:
                if (a < 0x80)
                {
                    return false;
                }
                break;
            }

            [[fallthrough]];
        case 1:
            if (*source >= 0x80 && *source < 0xC2)
            {
                return false;
            }
            break;
        }

        if (*source > 0xF4)
        {
            return false;
        }

        return true;
    }

    bool IsLegalUTF8Sequence(
        const char8_t* source_start,
        const char8_t* source_end
    ) noexcept
    {
        size_t length = static_cast<size_t>(Impl::TrailingBytesForUTF8[*source_start]) + 1;

        if (static_cast<ptrdiff_t>(length) > (source_end - source_start))
        {
            return false;
        }

        return IsLegalUTF8(source_start, length);
    }

    static size_t FindMaximalSubpartOfIllformedUTF8Sequence(
        const char8_t* source_start,
        const char8_t* source_end
    ) noexcept
    {
        GX_ASSERT(!IsLegalUTF8Sequence(source_start, source_end));

        if (source_start == source_end)
        {
            return 0;
        }

        char8_t b1 = (*source_start);

        ++source_start;

        if (b1 >= 0xC2 && b1 <= 0xDF)
        {
            return 1;
        }

        if (source_start == source_end)
        {
            return 1;
        }

        char8_t b2 = (*source_start);
        ++source_start;

        if (b1 == 0xE0)
        {
            return static_cast<size_t>((b2 >= 0xA0 && b2 <= 0xBF) ? 2 : 1);
        }

        if (b1 >= 0xE1 && b1 <= 0xEC)
        {
            return static_cast<size_t>((b2 >= 0x80 && b2 <= 0xBF) ? 2 : 1);
        }

        if (b1 == 0xED)
        {
            return static_cast<size_t>((b2 >= 0x80 && b2 <= 0x9F) ? 2 : 1);
        }

        if (b1 >= 0xEE && b1 <= 0xEF)
        {
            return static_cast<size_t>((b2 >= 0x80 && b2 <= 0xBF) ? 2 : 1);
        }

        char8_t b3 = 0;

        if (b1 == 0xF0)
        {
            if (b2 >= 0x90 && b2 <= 0xBF)
            {
                if (source_start == source_end)
                {
                    return 2;
                }

                b3 = (*source_start);
                return static_cast<size_t>((b3 >= 0x80 && b3 <= 0xBF) ? 3 : 2);
            }

            return 1;
        }

        if (b1 >= 0xF1 && b1 <= 0xF3)
        {
            if (b2 >= 0x80 && b2 <= 0xBF)
            {
                if (source_start == source_end)
                {
                    return 2;
                }

                b3 = (*source_start);
                return static_cast<size_t>((b3 >= 0x80 && b3 <= 0xBF) ? 3 : 2);
            }
            return 1;
        }

        if (b1 == 0xF4)
        {
            if (b2 >= 0x80 && b2 <= 0xBF)
            {
                if (source_start == source_end)
                {
                    return 2;
                }

                b3 = (*source_start);
                return static_cast<size_t>((b3 >= 0x80 && b3 <= 0xBF) ? 3 : 2);
            }
            return 1;
        }

        GX_ASSERT((b1 >= 0x80 && b1 <= 0xC1) || b1 >= 0xF5);
        return 1;
    }

    size_t GetBytesCountForUTF8(
        char8_t leading_byte
    ) noexcept
    {
        return static_cast<size_t>(Impl::TrailingBytesForUTF8[leading_byte]) + 1;
    }

    bool IsLegalUTF8String(
        const char8_t** source_start,
        const char8_t* source_end
    ) noexcept
    {
        while (*source_start != source_end)
        {
            size_t length = static_cast<size_t>(Impl::TrailingBytesForUTF8[**source_start]) + 1;

            if (static_cast<ptrdiff_t>(length) > (source_end - *source_start) || !IsLegalUTF8(*source_start, length))
            {
                return false;
            }

            (*source_start) += length;
        }
        return true;
    }

    ConversionResult ConvertUTF8ToUTF16(
        const char8_t** source_start,
        const char8_t* source_end,
        char16_t** target_start,
        char16_t* target_end,
        ConversionType type
    ) noexcept
    {
        ConversionResult result = ConversionResult::Success;

        const char8_t* source = (*source_start);
        char16_t* target = (*target_start);

        while (source < source_end)
        {
            char32_t ch = 0;

            size_t extra_bytes_to_read = Impl::TrailingBytesForUTF8[*source];

            if (static_cast<ptrdiff_t>(extra_bytes_to_read) >= (source_end - source))
            {
                result = ConversionResult::SourceExhausted;
                break;
            }

            if (!IsLegalUTF8(source, extra_bytes_to_read + 1))
            {
                result = ConversionResult::SourceIllegal;
                break;
            }

            switch (extra_bytes_to_read)
            {
            case 5:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 4:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 3:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 2:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 1:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 0:
                ch += (*source++);
                break;
            }

            ch -= Impl::OffsetsFromUTF8[extra_bytes_to_read];

            if (target >= target_end)
            {
                source -= (extra_bytes_to_read + 1);
                result = ConversionResult::TargetExhausted;
                break;
            }

            if (ch <= Impl::Unicode_MaxBmp)
            {
                if (ch >= Impl::SurrogateHighStart && ch <= Impl::SurrogateLowEnd)
                {
                    if (type == ConversionType::Strict)
                    {
                        source -= (extra_bytes_to_read + 1);
                        result = ConversionResult::SourceIllegal;
                        break;
                    }
                    else
                    {
                        (*target++) = Impl::Unicode_ReplacementChar;
                    }
                }
                else
                {
                    (*target++) = static_cast<char16_t>(ch);
                }
            }
            else if (ch > Impl::Unicode_MaxUTF16)
            {
                if (type == ConversionType::Strict)
                {
                    result = ConversionResult::SourceIllegal;
                    source -= (extra_bytes_to_read + 1);
                    break;
                }
                else
                {
                    (*target++) = Impl::Unicode_ReplacementChar;
                }
            }
            else
            {
                if ((target + 1) >= target_end)
                {
                    source -= (extra_bytes_to_read + 1);
                    result = ConversionResult::TargetExhausted;
                    break;
                }

                ch -= Impl::HalfBase;
                (*target++) = static_cast<char16_t>((ch >> Impl::HalfShift) + Impl::SurrogateHighStart);
                (*target++) = static_cast<char16_t>((ch & Impl::HalfMask) + Impl::SurrogateLowStart);
            }
        }

        (*source_start) = source;
        (*target_start) = target;

        return result;
    }

    static ConversionResult ConvertUTF8ToUTF32Impl(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type,
        bool input_is_partial
    ) noexcept
    {
        ConversionResult result = ConversionResult::Success;
        const char8_t* source = (*source_start);
        char32_t* target = (*target_start);

        while (source < source_end)
        {
            char32_t ch = 0;

            size_t extra_bytes_to_read = Impl::TrailingBytesForUTF8[*source];

            if (static_cast<ptrdiff_t>(extra_bytes_to_read) >= (source_end - source))
            {
                if (type == ConversionType::Strict || input_is_partial)
                {
                    result = ConversionResult::SourceExhausted;
                    break;
                }
                else
                {
                    result = ConversionResult::SourceIllegal;

                    source += FindMaximalSubpartOfIllformedUTF8Sequence(source, source_end);
                    (*target++) = Impl::Unicode_ReplacementChar;
                    continue;
                }
            }

            if (target >= target_end)
            {
                result = ConversionResult::TargetExhausted;
                break;
            }

            if (!IsLegalUTF8(source, extra_bytes_to_read + 1))
            {
                result = ConversionResult::SourceIllegal;
                if (type == ConversionType::Strict)
                {
                    break;
                }
                else
                {
                    source += FindMaximalSubpartOfIllformedUTF8Sequence(source, source_end);
                    (*target++) = Impl::Unicode_ReplacementChar;
                    continue;
                }
            }

            switch (extra_bytes_to_read)
            {
            case 5:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 4:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 3:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 2:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 1:
                ch += (*source++);
                ch <<= 6;
                [[fallthrough]];
            case 0:
                ch += (*source++);
                break;
            }

            ch -= Impl::OffsetsFromUTF8[extra_bytes_to_read];

            if (ch <= Impl::Unicode_MaxLegalUTF32)
            {
                if (ch >= Impl::SurrogateHighStart && ch <= Impl::SurrogateLowEnd)
                {
                    if (type == ConversionType::Strict)
                    {
                        source -= (extra_bytes_to_read + 1);
                        result = ConversionResult::SourceIllegal;
                        break;
                    }
                    else
                    {
                        (*target++) = Impl::Unicode_ReplacementChar;
                    }
                }
                else
                {
                    (*target++) = ch;
                }
            }
            else
            {
                result = ConversionResult::SourceIllegal;
                (*target++) = Impl::Unicode_ReplacementChar;
            }
        }

        (*source_start) = source;
        (*target_start) = target;
        return result;
    }

    ConversionResult ConvertUTF8ToUTF32Partial(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type
    ) noexcept
    {
        return ConvertUTF8ToUTF32Impl(source_start, source_end, target_start, target_end, type, true);
    }

    ConversionResult ConvertUTF8ToUTF32(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t** target_start,
        char32_t* target_end,
        ConversionType type
    ) noexcept
    {
        return ConvertUTF8ToUTF32Impl(source_start, source_end, target_start, target_end, type, false);
    }
}

namespace Graphyte::Text
{
    ConversionResult ConvertUTF8Sequence(
        const char8_t** source_start,
        const char8_t* source_end,
        char32_t* target,
        ConversionType type
    ) noexcept
    {
        if (*source_start == source_end)
        {
            return ConversionResult::SourceExhausted;
        }

        size_t const size = GetBytesCountForUTF8(**source_start);

        if (static_cast<ptrdiff_t>(size) > (source_end - *source_start))
        {
            return ConversionResult::SourceExhausted;
        }

        return ConvertUTF8ToUTF32(source_start, *source_start + size, &target, target + 1, type);
    }

    ConversionResult ConvertUTF8Sequence(
        char32_t character,
        char8_t** target_start,
        char8_t* target_end,
        ConversionType type
    ) noexcept
    {
        char32_t source[] = { character };
        const char32_t* source_start = &source[0];
        const char32_t* source_end = source_start + 1;

        return ConvertUTF32ToUTF8(&source_start, source_end, target_start, target_end, type);
    }

    ConversionResult ConvertString(
        std::string_view source,
        std::wstring& result,
        ConversionType type
    ) noexcept
    {
        const char8_t* source_start = reinterpret_cast<const char8_t*>(source.data());
        const char8_t* source_end = source_start + source.length();

        ConversionResult conversion_result = ConversionResult::Success;

        result.resize(source.length() + 1);

        if constexpr (sizeof(wchar_t) == sizeof(char16_t))
        {
            char16_t* const target_begin = reinterpret_cast<char16_t*>(result.data());
            char16_t* target_start = target_begin;
            char16_t* const target_end = target_start + result.length();

            conversion_result = ConvertUTF8ToUTF16(&source_start, source_end, &target_start, target_end, type);

            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }
        else
        {
            char32_t* const target_begin = reinterpret_cast<char32_t*>(result.data());
            char32_t* target_start = target_begin;
            char32_t* const target_end = target_start + result.length();

            conversion_result = ConvertUTF8ToUTF32(&source_start, source_end, &target_start, target_end, type);

            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }

        result.shrink_to_fit();

        return conversion_result;
    }

    ConversionResult ConvertString(
        std::wstring_view source,
        std::string& result,
        ConversionType type
    ) noexcept
    {
        result.resize(source.length() * Impl::Unicode_MaxUTF8BytesPerCodeUnit + 1);

        char8_t* const target_begin = reinterpret_cast<char8_t*>(result.data());
        char8_t* target_start = target_begin;
        char8_t* const target_end = target_start + result.length();

        ConversionResult conversion_result = ConversionResult::Success;

        if constexpr (sizeof(wchar_t) == sizeof(char16_t))
        {
            const char16_t* source_start = reinterpret_cast<const char16_t*>(source.data());
            const char16_t* const source_end = source_start + source.length();

            conversion_result = ConvertUTF16ToUTF8(&source_start, source_end, &target_start, target_end, type);
        }
        else
        {
            const char32_t* source_start = reinterpret_cast<const char32_t*>(source.data());
            const char32_t* const source_end = source_start + source.length();

            conversion_result = ConvertUTF32ToUTF8(&source_start, source_end, &target_start, target_end, type);
        }

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }


    ConversionResult ConvertString(
        std::string_view source,
        std::u16string& result,
        ConversionType type
    ) noexcept
    {
        const char8_t* source_start = reinterpret_cast<const char8_t*>(source.data());
        const char8_t* const source_end = source_start + source.length();

        result.resize(source.length() + 1);

        char16_t* const target_begin = reinterpret_cast<char16_t*>(result.data());
        char16_t* target_start = target_begin;
        char16_t* const target_end = target_start + result.length();

        ConversionResult conversion_result = ConvertUTF8ToUTF16(&source_start, source_end, &target_start, target_end, type);

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }

    ConversionResult ConvertString(
        std::string_view source,
        std::u32string& result,
        ConversionType type
    ) noexcept
    {
        const char8_t* source_start = reinterpret_cast<const char8_t*>(source.data());
        const char8_t* const source_end = source_start + source.length();

        result.resize(source.length() + 1);

        char32_t* const target_begin = reinterpret_cast<char32_t*>(result.data());
        char32_t* target_start = target_begin;
        char32_t* const target_end = target_start + result.length();

        ConversionResult conversion_result = ConvertUTF8ToUTF32(&source_start, source_end, &target_start, target_end, type);

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }

    ConversionResult ConvertString(
        std::u16string_view source,
        std::string& result,
        ConversionType type
    ) noexcept
    {
        result.resize(source.length() * Impl::Unicode_MaxUTF8BytesPerCodeUnit + 1);

        char8_t* const target_begin = reinterpret_cast<char8_t*>(result.data());
        char8_t* target_start = target_begin;
        char8_t* const target_end = target_start + result.length();

        const char16_t* source_start = reinterpret_cast<const char16_t*>(source.data());
        const char16_t* const source_end = source_start + source.length();

        ConversionResult conversion_result = ConvertUTF16ToUTF8(&source_start, source_end, &target_start, target_end, type);

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }

    ConversionResult ConvertString(
        std::u32string_view source,
        std::string& result,
        ConversionType type
    ) noexcept
    {
        result.resize(source.length() * Impl::Unicode_MaxUTF8BytesPerCodeUnit + 1);

        char8_t* const target_begin = reinterpret_cast<char8_t*>(result.data());
        char8_t* target_start = target_begin;
        char8_t* const target_end = target_start + result.length();

        const char32_t* source_start = reinterpret_cast<const char32_t*>(source.data());
        const char32_t* const source_end = source_start + source.length();

        ConversionResult conversion_result = ConvertUTF32ToUTF8(&source_start, source_end, &target_start, target_end, type);

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }

    ConversionResult ConvertString(
        std::u16string_view source,
        std::u32string& result,
        ConversionType type
    ) noexcept
    {
        // Resize to about same size - surrogate pairs may shrink into single code points at most.
        result.resize(source.length());

        char32_t* const target_begin = result.data();
        char32_t* target_start = target_begin;
        char32_t* const target_end = target_start + result.length();

        const char16_t* source_start = source.data();
        const char16_t* const source_end = source_start + source.length();

        ConversionResult conversion_result = ConvertUTF16ToUTF32(&source_start, source_end, &target_start, target_end, type);

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }

    ConversionResult ConvertString(
        std::u32string_view source,
        std::u16string& result,
        ConversionType type
    ) noexcept
    {
        result.resize(source.length() * 2);

        char16_t* const target_begin = result.data();
        char16_t* target_start = target_begin;
        char16_t* const target_end = target_start + result.length();

        const char32_t* source_start = source.data();
        const char32_t* const source_end = source_start + source.length();

        ConversionResult conversion_result = ConvertUTF32ToUTF16(&source_start, source_end, &target_start, target_end, type);

        if (conversion_result != ConversionResult::Success)
        {
            result.clear();
        }
        else
        {
            size_t const length = static_cast<size_t>(target_start - target_begin);
            result.resize(length);
        }

        result.shrink_to_fit();

        return conversion_result;
    }
}
