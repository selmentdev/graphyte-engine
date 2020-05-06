#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Storage
{
    struct BinarySignature final
    {
        uint64_t Value;

        BinarySignature() noexcept = default;

        explicit constexpr BinarySignature(
            uint64_t value
        ) noexcept
            : Value{ value }
        {
        }

        constexpr bool operator == (
            const BinarySignature& other
        ) const noexcept
        {
            return this->Value == other.Value;
        }

        constexpr bool operator != (
            const BinarySignature& other
        ) const noexcept
        {
            return this->Value != other.Value;
        }

        friend inline Archive& operator << (
            Archive& archive,
            BinarySignature& signature
        ) noexcept
        {
            return archive << signature.Value;
        }
    };
    static_assert(sizeof(BinarySignature) == 8);

    struct BinaryFormatVersion final
    {
        uint16_t Major;
        uint16_t Minor;

        BinaryFormatVersion() noexcept = default;

        constexpr BinaryFormatVersion(
            uint16_t major,
            uint16_t minor
        ) noexcept
            : Major{ major }
            , Minor{ minor }
        {
        }

        constexpr bool operator == (
            const BinaryFormatVersion& other
        ) const noexcept
        {
            return this->Major == other.Major
                && this->Minor == other.Minor;
        }

        friend inline Archive& operator << (
            Archive& archive,
            BinaryFormatVersion& version
        ) noexcept
        {
            return archive
                << version.Major
                << version.Minor;
        }
    };
    static_assert(sizeof(BinaryFormatVersion) == 4);

    struct BinaryBlockHeader final
    {
        BinarySignature Signature;
        uint64_t Size;
        uint64_t Offset;

        friend inline Archive& operator << (
            Archive& archive,
            BinaryBlockHeader& header
        ) noexcept
        {
            return archive
                << header.Signature
                << header.Size
                << header.Offset;
        }
    };
    static_assert(sizeof(BinaryBlockHeader) == 24);

    struct BinaryFormatHeader final
    {
        BinarySignature Signature;
        BinaryFormatVersion Version;
        ByteEncoding Encoding;
        uint64_t CustomFlags;
        uint64_t FileSize;
        uint64_t OffsetToFirstBlock;

        friend inline Archive& operator << (
            Archive& archive,
            BinaryFormatHeader& header
        ) noexcept
        {
            return archive
                << header.Signature
                << header.Version
                << header.Encoding
                << header.CustomFlags
                << header.FileSize
                << header.OffsetToFirstBlock;
        }
    };
    static_assert(sizeof(BinaryFormatHeader) == 40);
}
