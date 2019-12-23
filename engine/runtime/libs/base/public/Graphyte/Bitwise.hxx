#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte
{
    template <typename TValue, typename TBits>
    constexpr TValue FromBits(TBits bits) noexcept = delete;

    template <typename TValue, typename TBits>
    constexpr TBits ToBits(TValue value) noexcept = delete;

    template <>
    constexpr float FromBits<float, uint32_t>(uint32_t bits) noexcept
    {
        return Impl::Ieee754::FloatBits{ .AsUInt32 = bits }.AsFloat32;
    }

    template <>
    constexpr double FromBits<double, uint64_t>(uint64_t bits) noexcept
    {
        return Impl::Ieee754::DoubleBits{ .AsUInt64 = bits }.AsFloat64;
    }

    template <>
    constexpr uint32_t ToBits<float, uint32_t>(float value) noexcept
    {
        return Impl::Ieee754::FloatBits{ .AsFloat32 = value }.AsUInt32;
    }

    template <>
    constexpr uint64_t ToBits<double, uint64_t>(double value) noexcept
    {
        return Impl::Ieee754::DoubleBits{ .AsFloat64 = value }.AsUInt64;
    }
}

namespace Graphyte
{
    enum struct ByteEncoding : uint32_t
    {
        LittleEndian = 0x01020304,
        BigEndian = 0x04030201,

#if GRAPHYTE_ENDIAN_LITTLE
        Current = LittleEndian,
#elif GRAPHYTE_ENDIAN_BIG
        Current = BigEndian,
#else
#   error "Unknown endianess"
#endif
    };

    //
    // Float conversion.
    //

    constexpr __forceinline float ToFloat32(uint32_t value) noexcept
    {
        Impl::Ieee754::FloatBits pun{};
        pun.AsUInt32 = value;
        return pun.AsFloat32;
    }

    constexpr __forceinline double ToFloat64(uint64_t value) noexcept
    {
        Impl::Ieee754::DoubleBits pun{};
        pun.AsUInt64 = value;
        return pun.AsFloat64;
    }

    constexpr __forceinline uint32_t FromFloat32(float value) noexcept
    {
        Impl::Ieee754::FloatBits pun{};
        pun.AsFloat32 = value;
        return pun.AsUInt32;
    }

    constexpr __forceinline uint64_t FromFloat64(double value) noexcept
    {
        Impl::Ieee754::DoubleBits pun{};
        pun.AsFloat64 = value;
        return pun.AsUInt64;
    }


    //
    // Unaligned access.
    //

    template <typename T> __forceinline T FromUnaligned(const void* source) noexcept
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
        return *reinterpret_cast<const T*>(source);
    }

    template <typename T> __forceinline void FromUnaligned(T& value, const void* source) noexcept
    {
        value = FromUnaligned<T>(source);
    }

    template <typename T> __forceinline void ToUnaligned(void* destination, T value) noexcept
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
        *reinterpret_cast<T*>(destination) = value;
    }


    //
    // Byte swapping intrinsics.
    //

    template <typename T> constexpr T ByteSwap(T value) noexcept = delete;

    template <> constexpr __forceinline uint8_t ByteSwap<uint8_t>(uint8_t value) noexcept
    {
        return value;
    }

    template <> constexpr __forceinline uint16_t ByteSwap<uint16_t>(uint16_t value) noexcept
    {
        return static_cast<uint16_t>(
            ((value & static_cast<uint16_t>(0x00ff)) << 8) |
            ((value & static_cast<uint16_t>(0xff00)) >> 8));
    }

    template <> constexpr __forceinline uint32_t ByteSwap<uint32_t>(uint32_t value) noexcept
    {
        return static_cast<uint32_t>(
            ((value & static_cast<uint32_t>(0x0000'00ff)) << 24) |
            ((value & static_cast<uint32_t>(0x0000'ff00)) << 8) |
            ((value & static_cast<uint32_t>(0x00ff'0000)) >> 8) |
            ((value & static_cast<uint32_t>(0xff00'0000)) >> 24));
    }

    template <> constexpr __forceinline uint64_t ByteSwap<uint64_t>(uint64_t value) noexcept
    {
        return static_cast<uint64_t>(
            ((value & static_cast<uint64_t>(0x0000'0000'0000'00ff)) << 56) |
            ((value & static_cast<uint64_t>(0x0000'0000'0000'ff00)) << 40) |
            ((value & static_cast<uint64_t>(0x0000'0000'00ff'0000)) << 24) |
            ((value & static_cast<uint64_t>(0x0000'0000'ff00'0000)) << 8) |
            ((value & static_cast<uint64_t>(0x0000'00ff'0000'0000)) >> 8) |
            ((value & static_cast<uint64_t>(0x0000'ff00'0000'0000)) >> 24) |
            ((value & static_cast<uint64_t>(0x00ff'0000'0000'0000)) >> 40) |
            ((value & static_cast<uint64_t>(0xff00'0000'0000'0000)) >> 56));
    }

#if GRAPHYTE_HW_AVX
    template <> __forceinline __m128i ByteSwap<__m128i>(__m128i value) noexcept
    {
        return _mm_shuffle_epi8(value, _mm_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15));
    }
#endif

    //
    // Network endian support.
    //

    template <typename T> constexpr __forceinline T NetworkToHost(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
#if GRAPHYTE_ENDIAN_LITTLE
        return ByteSwap<T>(value);
#else
        return value;
#endif
    }

    template <typename T> constexpr __forceinline T HostToNetwork(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
#if GRAPHYTE_ENDIAN_LITTLE
        return ByteSwap<T>(value);
#else
        return value;
#endif
    }


    //
    // Generic endian support.
    //

    template <typename T> constexpr __forceinline T ToBigEndian(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
#if GRAPHYTE_ENDIAN_LITTLE
        return ByteSwap<T>(value);
#else
        return value;
#endif
    }

    template <typename T> constexpr __forceinline T FromBigEndian(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
#if GRAPHYTE_ENDIAN_LITTLE
        return ByteSwap<T>(value);
#else
        return value;
#endif
    }

    template <typename T> constexpr __forceinline T ToLittleEndian(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
#if GRAPHYTE_ENDIAN_LITTLE
        return value;
#else
        return ByteSwap<T>(value);
#endif
    }

    template <typename T> constexpr __forceinline T FromLittleEndian(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
#if GRAPHYTE_ENDIAN_LITTLE
        return value;
#else
        return ByteSwap<T>(value);
#endif
    }


    //
    // Load / store endian intrinsics.
    //

    template <typename T> __forceinline T ReadLittleEndian(const void* source) noexcept
    {
        return FromLittleEndian<T>(FromUnaligned<T>(source));
    }

    template <typename T> __forceinline T ReadBigEndian(const void* source) noexcept
    {
        return FromBigEndian<T>(FromUnaligned<T>(source));
    }

    template <typename T> __forceinline void ReadLittleEndian(T& value, const void* source) noexcept
    {
        value = ToLittleEndian<T>(FromUnaligned<T>(source));
    }

    template <typename T> __forceinline void ReadBigEndian(T& value, const void* source) noexcept
    {
        value = ToBigEndian<T>(FromUnaligned<T>(source));
    }

    template <typename T> __forceinline void WriteLittleEndian(void* destination, T value) noexcept
    {
        ToUnaligned<T>(destination, ToLittleEndian<T>(value));
    }
    
    template <typename T> __forceinline void WriteBigEndian(void* destination, T value) noexcept
    {
        ToUnaligned<T>(destination, ToBigEndian<T>(value));
    }

    //
    // Endian function specialization for float types.
    //

    template <> __forceinline float ReadLittleEndian<float>(const void* source) noexcept
    {
        return ToFloat32(FromLittleEndian<uint32_t>(FromUnaligned<uint32_t>(source)));
    }

    template <> __forceinline float ReadBigEndian<float>(const void* source) noexcept
    {
        return ToFloat32(FromBigEndian<uint32_t>(FromUnaligned<uint32_t>(source)));
    }

    template <> __forceinline void ReadLittleEndian<float>(float& value, const void* source) noexcept
    {
        value = ToFloat32(FromLittleEndian<uint32_t>(FromUnaligned<uint32_t>(source)));
    }

    template <> __forceinline void ReadBigEndian<float>(float& value, const void* source) noexcept
    {
        value = ToFloat32(FromBigEndian<uint32_t>(FromUnaligned<uint32_t>(source)));
    }

    template <> __forceinline void WriteLittleEndian<float>(void* destination, float value) noexcept
    {
        ToUnaligned<uint32_t>(destination, ToLittleEndian<uint32_t>(FromFloat32(value)));
    }

    template <> __forceinline void WriteBigEndian<float>(void* destination, float value) noexcept
    {
        ToUnaligned<uint32_t>(destination, ToBigEndian<uint32_t>(FromFloat32(value)));
    }

    //
    // Endian function specialization for float types.
    //

    template <> __forceinline double ReadLittleEndian<double>(const void* source) noexcept
    {
        return ToFloat64(FromLittleEndian<uint64_t>(FromUnaligned<uint64_t>(source)));
    }

    template <> __forceinline double ReadBigEndian<double>(const void* source) noexcept
    {
        return ToFloat64(FromBigEndian<uint64_t>(FromUnaligned<uint64_t>(source)));
    }

    template <> __forceinline void ReadLittleEndian<double>(double& value, const void* source) noexcept
    {
        value = ToFloat64(FromLittleEndian<uint64_t>(FromUnaligned<uint64_t>(source)));
    }

    template <> __forceinline void ReadBigEndian<double>(double& value, const void* source) noexcept
    {
        value = ToFloat64(FromBigEndian<uint64_t>(FromUnaligned<uint64_t>(source)));
    }

    template <> __forceinline void WriteLittleEndian<double>(void* destination, double value) noexcept
    {
        ToUnaligned<uint64_t>(destination, ToLittleEndian<uint64_t>(FromFloat64(value)));
    }

    template <> __forceinline void WriteBigEndian<double>(void* destination, double value) noexcept
    {
        ToUnaligned<uint64_t>(destination, ToBigEndian<uint64_t>(FromFloat64(value)));
    }

    //
    // Alignment intrinsics.
    //

    template <typename T> constexpr __forceinline bool IsAligned(T value, T alignment) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return (value & (alignment - 1)) == 0;
    }

    __forceinline bool IsAligned(const void* pointer, std::align_val_t alignment) noexcept
    {
        return IsAligned<uintptr_t>(reinterpret_cast<uintptr_t>(pointer), static_cast<uintptr_t>(alignment));
    }


    template <typename T> constexpr __forceinline T AlignUp(T value, T alignment) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return (value + (alignment - 1)) & (~(alignment - 1));
    }

    template <typename T> constexpr __forceinline T AlignDown(T value, T alignment) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
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



    template <typename T> constexpr __forceinline bool IsPowerOf2(T value) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return value > 0 &&  (value & (value - 1)) == 0;
    }

    template <typename T> constexpr __forceinline T CeilPowerOf2(T value) noexcept
    {
        value = value - 1;
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;

        if constexpr (sizeof(T) > 1)
        {
            value |= value >> 8;

            if constexpr (sizeof(T) > 2)
            {
                value |= value >> 16;

                if constexpr (sizeof(T) > 4)
                {
                    value |= value >> 32;
                }
            }
        }

        return value + 1;
    }

    template <typename T> constexpr __forceinline T FloorPowerOf2(T value) noexcept
    {
        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;

        if constexpr (sizeof(T) > 1)
        {
            value |= value >> 8;

            if constexpr (sizeof(T) > 2)
            {
                value |= value >> 16;

                if constexpr (sizeof(T) > 4)
                {
                    value |= value >> 32;
                }
            }
        }

        return value - (value >> 1);
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


    //
    // Rotate bits.
    //

    template <typename T>
    constexpr T RotateLeft(T value, int bits) noexcept
    {
        static_assert(std::is_integral_v<T>);
        using UnsignedT = std::make_unsigned_t<T>;

        return static_cast<T>((static_cast<UnsignedT>(value) << bits) | (static_cast<UnsignedT>(value) >> ((CHAR_BIT * sizeof(T)) - static_cast<unsigned>(bits))));
    }

    template <typename T>
    constexpr T RotateRight(T value, int bits) noexcept
    {
        static_assert(std::is_integral_v<T>);
        using UnsignedT = std::make_unsigned_t<T>;
        return static_cast<T>((static_cast<UnsignedT>(value) >> bits) | (static_cast<UnsignedT>(value) << ((CHAR_BIT * sizeof(T)) - static_cast<unsigned>(bits))));
    }

    template <typename T>
    constexpr T ShiftLeftLogical(T value, int bits) noexcept
    {
        static_assert(std::is_integral_v<T>);
        return static_cast<T>(static_cast<std::make_unsigned_t<T>>(value) << bits);
    }

    template <typename T>
    constexpr T ShiftRightLogical(T value, int bits) noexcept
    {
        static_assert(std::is_integral_v<T>);
        return static_cast<T>(static_cast<std::make_unsigned_t<T>>(value) >> bits);
    }

    template <typename T>
    constexpr T ShiftLeftArithmetic(T value, int bits) noexcept
    {
        return ShiftLeftLogical<T>(value, bits);
    }

    template <typename T>
    constexpr T ShiftRightArithmetic(T value, int bits) noexcept
    {
        static_assert(std::is_integral_v<T>);
        return static_cast<T>(static_cast<std::make_signed_t<T>>(value) >> bits);
    }

    template <typename T>
    constexpr int CountLeadingZeros(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
        static_assert(std::is_unsigned_v<T>);
        static_assert(sizeof(T) >= sizeof(int));
        static_assert(sizeof(T) <= sizeof(long long));

#if GRAPHYTE_COMPILER_MSVC && (GRAPHYTE_CPU_X86_64)
        if constexpr (sizeof(T) == sizeof(long long))
        {
            return static_cast<int>(_lzcnt_u64(value));
        }
        else
        {
            return static_cast<int>(_lzcnt_u32(value));
        }
#elif GRAPHYTE_COMPILER_CLANG || GRAPHYTE_COMPILER_GCC
        if (value != 0)
        {
            if constexpr (sizeof(T) == sizeof(long long))
            {
                return static_cast<int>(__builtin_clzll(value));
            }
            else
            {
                return static_cast<int>(__builtin_clz(value));
            }
        }

        return std::numeric_limits<T>::digits;
#else
        constexpr size_t nbits = std::numeric_limits<T>::digits;

        if (value == 0)
        {
            return nbits;
        }

        T n = 1;
        if constexpr (sizeof(T) > 1)
        {
            if constexpr (sizeof(T) > 2)
            {
                if constexpr (sizeof(T) > 4)
                {
                    if (ShiftRightLogical(value, nbits - 32) == 0)
                    {
                        n = n + 32;
                        value = value << 32;
                    }
                }

                if (ShiftRightLogical(value, nbits - 16) == 0)
                {
                    n = n + 16;
                    value = value << 16;
                }
            }

            if (ShiftRightLogical(value, nbits - 8) == 0)
            {
                n = n + 8;
                value = value << 8;
            }
        }

        if (ShiftRightLogical(value, nbits - 4) == 0)
        {
            n = n + 4;
            value = value << 4;
        }

        if (ShiftRightLogical(value, nbits - 2) == 0)
        {
            n = n + 2;
            value = value << 2;
        }

        n = n - (ShiftRightLogical(value, 31));

        return static_cast<int>(n);
#endif
    }

    template <typename T>
    constexpr int CountLeadingOnes(T value) noexcept
    {
        return CountLeadingZeros<T>(~value);
    }

    template <typename T>
    constexpr int CountTrailingZeros(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
        static_assert(sizeof(T) >= sizeof(int));
        static_assert(sizeof(T) <= sizeof(long long));

#if GRAPHYTE_COMPILER_MSVC && (GRAPHYTE_CPU_X86_64)
        if constexpr (sizeof(T) == sizeof(long long))
        {
            return static_cast<int>(_tzcnt_u64(value));
        }
        else
        {
            return static_cast<int>(_tzcnt_u32(value));
        }
#elif GRAPHYTE_COMPILER_CLANG || GRAPHYTE_COMPILER_GCC
        if (value != 0)
        {
            if constexpr (sizeof(T) == sizeof(long long))
            {
                return static_cast<int>(__builtin_ctzll(value));
            }
            else
            {
                return static_cast<int>(__builtin_ctz(value));
            }
        }

        return std::numeric_limits<T>::digits;
#else
        constexpr int nbits = std::numeric_limits<T>::digits;

        if (value == 0)
        {
            return nbits;
        }

        T n = 0;

        if constexpr (sizeof(T) > 1)
        {
            if constexpr (sizeof(T) > 2)
            {
                if constexpr (sizeof(T) > 4)
                {
                    if ((value & T(0xFFFF'FFFFULL)) == 0)
                    {
                        n = n + 32;
                        value = ShiftRightLogical(value, 32);
                    }
                }

                if ((value & T(0xFFFFULL)) == 0)
                {
                    n = n + 16;
                    value = ShiftRightLogical(value, 16);
                }
            }

            if ((value & T(0xFFUL)) == 0)
            {
                n = n + 8;
                value = ShiftRightLogical(value, 8);
            }
        }

        if ((value & T(0xFUL)) == 0)
        {
            n = n + 4;
            value = ShiftRightLogical(value, 4);
        }

        if ((value & T(0x3UL)) == 0)
        {
            n = n + 2;
            value = ShiftRightLogical(value, 2);
        }

        return static_cast<int>(n - (value & 1));
#endif
    }

    template <typename T>
    constexpr int CountTrailingOnes(T value) noexcept
    {
        return CountTrailingZeros<T>(~value);
    }

    template <typename T>
    constexpr int CountBits(T value) noexcept
    {
#if GRAPHYTE_COMPILER_MSVC && (GRAPHYTE_CPU_X86_64)
        if constexpr (sizeof(T) == sizeof(long long))
        {
            return static_cast<int>(__popcnt64(value));
        }
        else
        {
            return static_cast<int>(__popcnt(value));
        }
#elif GRAPHYTE_COMPILER_CLANG || GRAPHYTE_COMPILER_GCC
        if constexpr (sizeof(T) == sizeof(long long))
        {
            return static_cast<int>(__builtin_popcountll(value));
        }
        else
        {
            return static_cast<int>(__builtin_popcount(value));
        }
#else
        value = static_cast<T>((value & 0x5555555555555555ULL)) + static_cast<T>((ShiftRightLogical(value, 1) & 0x5555555555555555ULL));
        value = static_cast<T>((value & 0x3333333333333333ULL)) + static_cast<T>((ShiftRightLogical(value, 2) & 0x3333333333333333ULL));
        value = static_cast<T>((value & 0x0F0F0F0F0F0F0F0FULL)) + static_cast<T>((ShiftRightLogical(value, 4) & 0x0F0F0F0F0F0F0F0FULL));

        if constexpr (sizeof(T) > 1)
        {
            value = static_cast<T>((value & 0x00FF00FF00FF00FFULL)) + static_cast<T>((ShiftRightLogical(value, 8) & 0x00FF00FF00FF00FFULL));
            if constexpr (sizeof(T) > 2)
            {
                value = static_cast<T>((value & 0x0000FFFF0000FFFFULL)) + static_cast<T>((ShiftRightLogical(value, 16) & 0x0000FFFF0000FFFFULL));
                if constexpr (sizeof(T) > 4)
                {
                    value = static_cast<T>((value & 0x00000000FFFFFFFFULL)) + static_cast<T>((ShiftRightLogical(value, 32) & 0x00000000FFFFFFFFULL));
                }
            }
        }

        return static_cast<int>(value);
#endif
    }

    template <typename T>
    constexpr int Parity(T value) noexcept
    {
        value = value ^ ShiftLeftLogical(value, 1);
        value = value ^ ShiftLeftLogical(value, 2);
        value = value ^ ShiftLeftLogical(value, 4);

        if constexpr (sizeof(T) > 1)
        {
            value = value ^ ShiftLeftLogical(value, 8);

            if constexpr (sizeof(T) > 2)
            {
                value = value ^ ShiftLeftLogical(value, 16);

                if constexpr (sizeof(T) > 4)
                {
                    value = value ^ ShiftLeftLogical(value, 32);
                }
            }
        }

        return static_cast<int>(value);
    }

    template <typename T>
    constexpr auto ReverseBits(T value, int subword_bits = 1, int group_subwords = 1) noexcept
        -> std::enable_if_t<std::is_unsigned_v<T>>
    {
        int group_size = std::numeric_limits<T>::digits / group_subwords;
        int k = group_size - subword_bits;

        if (k & 1)
        {
            value = ShiftLeftLogical<T>(value & 0x5555555555555555U, 1) | ShiftRightLogical(value & 0xAAAAAAAAAAAAAAAAU, 1);
        }

        if (k & 2)
        {
            value = ShiftLeftLogical<T>(value & 0x3333333333333333U, 2) | ShiftRightLogical(value & 0xCCCCCCCCCCCCCCCCU, 2);
        }

        if (k & 4)
        {
            value = ShiftLeftLogical<T>(value & 0x0F0F0F0F0F0F0F0FU, 4) | ShiftRightLogical(value & 0xF0F0F0F0F0F0F0F0U, 4);
        }


        if constexpr (sizeof(T) > 1)
        {
            if (k & 8)
            {
                value = ShiftLeftLogical(value & 0x00FF00FF00FF00FFU, 8) | ShiftRightLogical(value & 0xFF00FF00FF00FF00U, 8);
            }
        }

        if constexpr (sizeof(T) > 2)
        {
            if (k & 16)
            {
                value = ShiftLeftLogical(value & 0x0000FFFF0000FFFFU, 16) | ShiftRightLogical(value & 0xFFFF0000FFFF0000U, 16);
            }
        }

        if constexpr (sizeof(T) > 4)
        {
            if (k & 32)
            {
                value = ShiftLeftLogical(value & 0x00000000FFFFFFFFU, 32) | ShiftRightLogical(value & 0xFFFFFFFF00000000U, 32);
            }
        }

        return value;
    }

    template <typename T>
    constexpr auto ReverseBits(T value, int subword_bits = 1, int group_subwords = 1) noexcept
        -> std::enable_if_t<std::is_signed_v<T>>
    {
        return static_cast<T>(ReverseBits(std::make_unsigned_t<T>(value), subword_bits, group_subwords));
    }

    template <typename T>
    constexpr int MostSignificantBit(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
        static_assert(std::is_unsigned_v<T>);
        static_assert(std::numeric_limits<T>::radix == 2);

        return (value == 0) ? -1 : CountLeadingZeros(value);
    }

    template <typename T>
    constexpr int LeastSignificantBit(T value) noexcept
    {
        static_assert(std::is_integral_v<T>);
        static_assert(std::is_unsigned_v<T>);
        return (value == 0) ? -1 : CountTrailingZeros(value);
    }
}
