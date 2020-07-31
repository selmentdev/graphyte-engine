#pragma once
#include <GxBase/TypeTraits.hxx>


// =================================================================================================
//
// Bit casting support.
//

namespace Graphyte
{
    //! \brief Performs safe bit casting between two types.
    //!
    //! # Examples
    //!
    //! ```
    //! float f = BitCast<float>(0x3F800000);
    //! GX_ASSERT(f == 1.0f);
    //! ```
    template <typename TTo, typename TFrom>
    [[nodiscard]] constexpr TTo BitCast(TFrom const& source) noexcept
        requires std::conjunction_v<
            std::bool_constant<sizeof(TTo) == sizeof(TFrom)>,
            std::is_trivially_copyable<TTo>,
            std::is_trivially_copyable<TFrom>>
    {
#if (defined(_MSC_VER) && (_MSC_VER >= 1926)) || (defined(__clang__) && (__clang_major__ >= 10))
        return __builtin_bit_cast(TTo, source);
#else
        TTo result;
        memcpy(&result, &source, sizeof(result));
        return result;
#endif
    }
}


// =================================================================================================
//
// Byte encoding definition.
//

namespace Graphyte
{
    enum class ByteEncoding : uint32_t
    {
        LittleEndian = 0x01020304,
        BigEndian    = 0x04030201,

        Network = BigEndian,
#if GRAPHYTE_ENDIAN_LITTLE
        Host = LittleEndian,
#elif GRAPHYTE_ENDIAN_BIG
        Host = BigEndian,
#else
#error "Unknown endianess"
#endif
    };
}


// =================================================================================================
//
// Byte swapping
//

namespace Graphyte
{
    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T ByteSwap(T value) noexcept
    {
        if (std::is_constant_evaluated())
        {
            if constexpr (sizeof(T) == 1)
            {
                return value;
            }
            else if constexpr (sizeof(T) == 2)
            {
                // clang-format off
                return static_cast<uint16_t>(
                    ((value & static_cast<uint16_t>(0x00ff)) << 8) |
                    ((value & static_cast<uint16_t>(0xff00)) >> 8)
                    );
                // clang-format on
            }
            else if constexpr (sizeof(T) == 4)
            {
                // clang-format off
                return static_cast<uint32_t>(
                    ((value & static_cast<uint32_t>(0x0000'00ff)) << 24) |
                    ((value & static_cast<uint32_t>(0x0000'ff00)) << 8) |
                    ((value & static_cast<uint32_t>(0x00ff'0000)) >> 8) |
                    ((value & static_cast<uint32_t>(0xff00'0000)) >> 24)
                    );
                // clang-format on
            }
            else if constexpr (sizeof(T) == 8)
            {
                // clang-format off
                return static_cast<uint64_t>(
                    ((value & static_cast<uint64_t>(0x0000'0000'0000'00ff)) << 56) |
                    ((value & static_cast<uint64_t>(0x0000'0000'0000'ff00)) << 40) |
                    ((value & static_cast<uint64_t>(0x0000'0000'00ff'0000)) << 24) |
                    ((value & static_cast<uint64_t>(0x0000'0000'ff00'0000)) << 8) |
                    ((value & static_cast<uint64_t>(0x0000'00ff'0000'0000)) >> 8) |
                    ((value & static_cast<uint64_t>(0x0000'ff00'0000'0000)) >> 24) |
                    ((value & static_cast<uint64_t>(0x00ff'0000'0000'0000)) >> 40) |
                    ((value & static_cast<uint64_t>(0xff00'0000'0000'0000)) >> 56)
                    );
                // clang-format on
            }
        }
        else
        {
#if GRAPHYTE_COMPILER_MSVC
            if constexpr (sizeof(T) == 1)
            {
                return value;
            }
            else if constexpr (sizeof(T) == 2)
            {
                return _byteswap_ushort(value);
            }
            else if constexpr (sizeof(T) == 4)
            {
                return _byteswap_ulong(value);
            }
            else if constexpr (sizeof(T) == 8)
            {
                return _byteswap_uint64(value);
            }
#else
            if constexpr (sizeof(T) == 1)
            {
                return value;
            }
            else if constexpr (sizeof(T) == 2)
            {
                return __builtin_bswap16(value);
            }
            else if constexpr (sizeof(T) == 4)
            {
                return __builtin_bswap32(value);
            }
            else if constexpr (sizeof(T) == 8)
            {
                return __builtin_bswap64(value);
            }
#endif
        }
    }

    template <ByteEncoding Encoding, typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T ByteSwap(T value) noexcept
    {
        if constexpr (Encoding == ByteEncoding::Host)
        {
            return value;
        }
        else
        {
            return ByteSwap<T>(value);
        }
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T NetworkToHost(T value) noexcept
    {
        return ByteSwap<ByteEncoding::Network, T>(value);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T HostToNetwork(T value) noexcept
    {
        return ByteSwap<ByteEncoding::Network, T>(value);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T ToBigEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::BigEndian, T>(value);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T FromBigEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::BigEndian, T>(value);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T ToLittleEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::LittleEndian, T>(value);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T FromLittleEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::LittleEndian, T>(value);
    }
}


// =================================================================================================
//
// Alignment operations
//

namespace Graphyte
{
    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr bool IsAligned(T value, T alignment) noexcept
    {
        return (value & (alignment - 1)) == 0;
    }

    [[nodiscard]] inline bool IsAligned(const void* pointer, std::align_val_t alignment) noexcept
    {
        return IsAligned<std::uintptr_t>(
            reinterpret_cast<std::uintptr_t>(pointer),
            static_cast<std::uintptr_t>(alignment));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T AlignUp(T value, T alignment) noexcept
    {
        return (value + (alignment - 1)) & (~(alignment - 1));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T AlignDown(T value, T alignment) noexcept
    {
        return (value & (~(alignment)-1));
    }

    template <typename T, std::enable_if_t<std::is_pointer_v<T>, int> = 0>
    [[nodiscard]] inline T AlignUp(T pointer, std::align_val_t alignment) noexcept
    {
        return reinterpret_cast<T>(AlignUp<uintptr_t>(
            reinterpret_cast<uintptr_t>(pointer),
            static_cast<uintptr_t>(alignment)));
    }

    template <typename T, std::enable_if_t<std::is_pointer_v<T>, int> = 0>
    [[nodiscard]] inline T AlignDown(T pointer, std::align_val_t alignment) noexcept
    {
        return reinterpret_cast<T>(AlignDown<std::uintptr_t>(
            reinterpret_cast<std::uintptr_t>(pointer),
            static_cast<std::uintptr_t>(alignment)));
    }

    template <typename T, std::enable_if_t<std::is_pointer_v<T>, int> = 0>
    [[nodiscard]] inline T AdvancePointer(T value, ptrdiff_t offset) noexcept
    {
        if constexpr (std::is_const_v<T>)
        {
            return reinterpret_cast<T>(reinterpret_cast<const std::byte*>(value) + offset);
        }
        else
        {
            return reinterpret_cast<T>(reinterpret_cast<std::byte*>(value) + offset);
        }
    }
}


// =================================================================================================
//
// Bit functions.
//

namespace Graphyte
{
    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T BitRotateLeft(T value, int bits) noexcept
    {
        return static_cast<T>(
            static_cast<T>(value << bits) | static_cast<T>(value >> (std::numeric_limits<T>::digits - bits)));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T BitRotateRight(T value, int bits) noexcept
    {
        return static_cast<T>(
            static_cast<T>(value >> bits) | static_cast<T>(value << (std::numeric_limits<T>::digits - bits)));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int BitCountLeadingZeros(T value) noexcept
    {
        constexpr int digits = std::numeric_limits<T>::digits;

        if (value == 0)
        {
            return digits;
        }

        if constexpr (sizeof(T) <= sizeof(unsigned int))
        {
            return __builtin_clz(value) - (std::numeric_limits<unsigned int>::digits - digits);
        }
        else
        {
            return __builtin_clzll(value) - (std::numeric_limits<unsigned long long>::digits - digits);
        }
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int BitCountTrailingZeros(T value) noexcept
    {
        if (value == 0)
        {
            return std::numeric_limits<T>::digits;
        }

        if constexpr (sizeof(T) <= sizeof(unsigned int))
        {
            return __builtin_ctz(value);
        }
        else
        {
            return __builtin_ctzll(value);
        }
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int BitCountLeadingOnes(T value) noexcept
    {
        return BitCountLeadingZeros(static_cast<T>(~value));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int BitCountTrailingOnes(T value) noexcept
    {
        return BitCountTrailingZeros(static_cast<T>(~value));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int BitCount(T value) noexcept
    {
        if constexpr (sizeof(T) <= sizeof(unsigned int))
        {
            return __builtin_popcount(value);
        }
        else
        {
            return __builtin_popcountll(value);
        }
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr size_t BitWidth(T value) noexcept
    {
        return std::numeric_limits<T>::digits - BitCountLeadingZeros(value);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr bool IsPowerOf2(T value) noexcept
    {
        return (value != 0) && ((value & (value - 1)) == 0);
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T BitCeil(T value) noexcept
    {
        if (value == 0)
        {
            return 1;
        }

        return static_cast<T>(T{ 1 } << (std::numeric_limits<T>::digits - BitCountLeadingZeros(static_cast<T>(value - 1))));
    }

    template <typename T, std::enable_if_t<IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T BitFloor(T value) noexcept
    {
        if (value == 0)
        {
            return 0;
        }

        return static_cast<T>(T{ 1 } << (std::numeric_limits<T>::digits - 1 - BitCountLeadingZeros(value)));
    }
}
