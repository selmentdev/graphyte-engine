#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Ieee754.hxx>
#include <GxBase/TypeTraits.hxx>

namespace Graphyte::Impl
{
    template <typename T>
    inline constexpr bool IsStandardUnsignedType = IsAnyOfType<
        std::remove_cv_t<T>,
        unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long
    >;
}

namespace Graphyte
{
    /// Performs safe bit casting between two types.
    ///
    /// # Examples
    ///
    /// ```
    /// float f = BitCast(0x3F80'0000);
    /// GX_ASSERT(f == 1.0F);
    /// ```
    template <
        typename TTo,
        typename TFrom,
        std::enable_if_t<sizeof(TTo) == sizeof(TFrom) && std::is_trivially_copyable_v<TTo> && std::is_trivially_constructible_v<TFrom>, int> = 0
    >
    [[nodiscard]] inline TTo BitCast(const TFrom& source)
    {
        TTo result;
        memcpy(&result, &source, sizeof(result));
        return result;
    }
}

namespace Graphyte
{
    enum struct ByteEncoding : uint32_t
    {
        LittleEndian = 0x01020304,
        BigEndian = 0x04030201,

        Network = BigEndian,
#if GRAPHYTE_ENDIAN_LITTLE
        Host = LittleEndian,
#elif GRAPHYTE_ENDIAN_BIG
        Host = BigEndian,
#else
#   error "Unknown endianess"
#endif
    };

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr T ByteSwap(T value) noexcept
    {
        if (std::is_constant_evaluated())
        {
            if constexpr (sizeof(T) == 1)
            {
                return value;
            }
            else if constexpr (sizeof(T) == 2)
            {
                return static_cast<uint16_t>(
                    ((value & static_cast<uint16_t>(0x00ff)) << 8) |
                    ((value & static_cast<uint16_t>(0xff00)) >> 8)
                    );
            }
            else if constexpr (sizeof(T) == 4)
            {
                return static_cast<uint32_t>(
                    ((value & static_cast<uint32_t>(0x0000'00ff)) << 24) |
                    ((value & static_cast<uint32_t>(0x0000'ff00)) << 8) |
                    ((value & static_cast<uint32_t>(0x00ff'0000)) >> 8) |
                    ((value & static_cast<uint32_t>(0xff00'0000)) >> 24)
                    );
            }
            else if constexpr (sizeof(T) == 8)
            {
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

    template <
        ByteEncoding Encoding,
        typename T,
        std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0
    >
    constexpr T ByteSwap(T value) noexcept
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



    //
    // Network endian support.
    //

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T NetworkToHost(T value) noexcept
    {
        return ByteSwap<ByteEncoding::Network>(value);
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T HostToNetwork(T value) noexcept
    {
        return ByteSawp<ByteEncoding::Network>(value);
    }


    //
    // Generic endian support.
    //

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T ToBigEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::BigEndian>(value);
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T FromBigEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::BigEndian>(value);
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T ToLittleEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::LittleEndian>(value);
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T FromLittleEndian(T value) noexcept
    {
        return ByteSwap<ByteEncoding::LittleEndian>(value);
    }


    //
    // Alignment intrinsics.
    //

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline bool IsAligned(T value, T alignment) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return (value & (alignment - 1)) == 0;
    }

    __forceinline bool IsAligned(const void* pointer, std::align_val_t alignment) noexcept
    {
        return IsAligned<uintptr_t>(reinterpret_cast<uintptr_t>(pointer), static_cast<uintptr_t>(alignment));
    }


    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T AlignUp(T value, T alignment) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return (value + (alignment - 1)) & (~(alignment - 1));
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    constexpr __forceinline T AlignDown(T value, T alignment) noexcept
    {
        return value & (~(alignment - 1));
    }

    __forceinline void* AlignUp(void* pointer, std::align_val_t alignment) noexcept
    {
        return reinterpret_cast<void*>(AlignUp<uintptr_t>(reinterpret_cast<uintptr_t>(pointer), static_cast<uintptr_t>(alignment)));
    }

    __forceinline void* AlignDown(void* pointer, std::align_val_t alignment) noexcept
    {
        return reinterpret_cast<void*>(AlignDown<uintptr_t>(reinterpret_cast<uintptr_t>(pointer), static_cast<uintptr_t>(alignment)));
    }

    template <typename T>
    __forceinline T* AdvancePointer(T* value, ptrdiff_t offset) noexcept
    {
        return reinterpret_cast<T*>(reinterpret_cast<std::byte*>(value) + offset);
    }

    template <typename T>
    __forceinline const T* AdvancePointer(const T* value, ptrdiff_t offset) noexcept
    {
        return reinterpret_cast<const T*>(reinterpret_cast<const std::byte*>(value) + offset);
    }

    //
    // Integer parts access.
    //

    template <typename T, typename S> constexpr __forceinline T HighPart(S value) noexcept = delete;

    template <> constexpr __forceinline uint8_t HighPart<uint8_t, uint16_t>(uint16_t value) noexcept
    {
        return static_cast<uint8_t>(value >> 8);
    }
    template <> constexpr __forceinline uint16_t HighPart<uint16_t, uint32_t>(uint32_t value) noexcept
    {
        return static_cast<uint16_t>(value >> 16);
    }
    template <> constexpr __forceinline uint32_t HighPart<uint32_t, uint64_t>(uint64_t value) noexcept
    {
        return static_cast<uint32_t>(value >> 32);
    }

    template <typename T, typename S> constexpr __forceinline T LowPart(S value) noexcept = delete;

    template <> constexpr __forceinline uint8_t LowPart<uint8_t, uint16_t>(uint16_t value) noexcept
    {
        return static_cast<uint8_t>(value);
    }

    template <> constexpr __forceinline uint16_t LowPart<uint16_t, uint32_t>(uint32_t value) noexcept
    {
        return static_cast<uint16_t>(value);
    }

    template <> constexpr __forceinline uint32_t LowPart<uint32_t, uint64_t>(uint64_t value) noexcept
    {
        return static_cast<uint32_t>(value);
    }


    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T RotateLeft(T value, int bits) noexcept
    {
        return static_cast<T>(
            static_cast<T>(value << bits) |
            static_cast<T>(value >> (std::numeric_limits<T>::digits - bits))
        );
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T RotateRight(T value, int bits) noexcept
    {
        return static_cast<T>(
            static_cast<T>(value >> bits) |
            static_cast<T>(value << (std::numeric_limits<T>::digits - bits))
        );
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int CountLeadingZeros(T value) noexcept
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

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int CountTrailingZeros(T value) noexcept
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

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int CountLeadingOnes(T value) noexcept
    {
        return CountLeadingZero(static_cast<T>(~value));
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int CountTrailingOnes(T value) noexcept
    {
        return CountTrailingZero(static_cast<T>(~value));
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr int CountBits(T value) noexcept
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

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr size_t BitWidth(T value) noexcept
    {
        return std::numeric_limits<T>::digits - CountLeadingZeros(value);
    }


    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr bool IsPowerOf2(T value) noexcept
    {
        return value != 0
            && (value & (value - 1)) == 0;
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T BitCeil(T value) noexcept
    {
        if (value == 0)
        {
            return 1;
        }

        return static_cast<T>(T{ 1 } << (std::numeric_limits<T>::digits - CountLeadingZeros(static_cast<T>(value - 1))));
    }

    template <typename T, std::enable_if_t<Impl::IsStandardUnsignedType<T>, int> = 0>
    [[nodiscard]] constexpr T BitFloor(T value) noexcept
    {
        if (value == 0)
        {
            return 0;
        }

        return static_cast<T>(T{ 1 } << (std::numeric_limits<T>::digits - 1 - CountLeadingZeros(value)));
    }
}
