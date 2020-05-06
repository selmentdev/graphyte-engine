#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Intrinsics
{
    // ShiftLeftLogical
    template <typename T> constexpr T shll(T x, int s) noexcept
    {
        return T(typename std::make_unsigned<T>::type(x) << s);
    }
    // ShiftRightLogical
    template <typename T> constexpr T shlr(T x, int s) noexcept
    {
        return T(typename std::make_unsigned<T>::type(x) >> s);
    }
    // ShiftLeftArithmetic
    template <typename T> constexpr T shal(T x, int s) noexcept
    {
        return shll(x, s);
    }
    // ShiftRightArithmetic
    template <typename T> constexpr T shar(T x, int s) noexcept
    {
        return T(typename std::make_signed<T>::type(x) >> s);
    }
    // RotateLeft
    template <typename T> constexpr T rotl(T x, int s) noexcept
    {
        return (x << s) | shlr(x, (sizeof(T) * CHAR_BIT - s));
    }
    // RotateRight
    template <typename T> constexpr T rotr(T x, int s) noexcept
    {
        return shlr(x, s) | (x << (sizeof(T) * CHAR_BIT - s));
    }
    // CountTrailingZeros
    template <typename T> constexpr int cntt0(T x) noexcept
    {
        constexpr int nbits = int(sizeof(T) * CHAR_BIT);
        if (x == 0)
        {
            return nbits;
        }

        T n = 0;
        if (sizeof(T) > 1)
        {
            if (sizeof(T) > 2)
            {
                if (sizeof(T) > 4)
                {
                    if ((x & T(0xFFFFFFFFUL)) == 0)
                    {
                        n = n + 32; x = shlr(x, 32);
                    }
                }
                if ((x & T(0xFFFFUL)) == 0)
                {
                    n = n + 16; x = shlr(x, 16);
                }
            }
            if ((x & T(0xFFUL)) == 0)
            {
                n = n + 8; x = shlr(x, 8);
            }
        }
        if ((x & T(0xFUL)) == 0)
        {
            n = n + 4; x = shlr(x, 4);
        }
        if ((x & T(0x3UL)) == 0)
        {
            n = n + 2; x = shlr(x, 2);
        }
        return static_cast<int>(n - (x & 1));
    }
    // CountLeadingZeros
    template <typename T> constexpr int cntl0(T x) noexcept
    {
        constexpr int nbits = int(sizeof(T) * CHAR_BIT);
        if (x == 0)
        {
            return nbits;
        }
        T n = 1;
        if (sizeof(T) > 1)
        {
            if (sizeof(T) > 2)
            {
                if (sizeof(T) > 4)
                {
                    if ((shlr(x, nbits - 32)) == 0)
                    {
                        n = n + 32; x = x << 32;
                    }
                }
                if ((shlr(x, nbits - 16)) == 0)
                {
                    n = n + 16; x = x << 16;
                }
            }
            if ((shlr(x, nbits - 8)) == 0)
            {
                n = n + 8; x = x << 8;
            }
        }
        if ((shlr(x, nbits - 4)) == 0)
        {
            n = n + 4; x = x << 4;
        }
        if ((shlr(x, nbits - 2)) == 0)
        {
            n = n + 2; x = x << 2;
        }
        n = n - (shlr(x, 31));
        return static_cast<int>(n);
    }
    // CountTrailingOnes
    template <typename T> constexpr int cntl1(T x) noexcept
    {
        return cntl0(~x);
    }
    // CountLeadingOnes
    template <typename T> constexpr int cntt1(T x) noexcept
    {
        return cntt0(~x);
    }
    // CountBits
    template <typename T> constexpr int popcount(T x) noexcept
    {
        x = (x & T(0x5555555555555555UL)) + (shlr(x, 1) & T(0x5555555555555555UL));
        x = (x & T(0x3333333333333333UL)) + (shlr(x, 2) & T(0x3333333333333333UL));
        x = (x & T(0x0F0F0F0F0F0F0F0FUL)) + (shlr(x, 4) & T(0x0F0F0F0F0F0F0F0FUL));
        if (sizeof(T) > 1)
        {
            x = (x & T(0x00FF00FF00FF00FFUL)) + (shlr(x, 8) & T(0x00FF00FF00FF00FFUL));
            if (sizeof(T) > 2)
            {
                x = (x & T(0x0000FFFF0000FFFFUL)) + (shlr(x, 16) & T(0x0000FFFF0000FFFFUL));
                if (sizeof(T) > 4)
                {
                    x = (x & T(0x00000000FFFFFFFFUL)) + (shlr(x, 32) & T(0x00000000FFFFFFFFUL));
                }
            }
        }
        return x;
    }
    // Parity
    template <typename T> constexpr int parity(T x) noexcept
    {
        x = x ^ shlr(x, 1);
        x = x ^ shlr(x, 2);
        x = x ^ shlr(x, 4);
        if (sizeof(T) > 1)
        {
            x = x ^ shlr(x, 8);
            if (sizeof(T) > 2)
            {
                x = x ^ shlr(x, 16);
                if (sizeof(T) > 4)
                {
                    x = x ^ shlr(x, 32);
                }
            }
        }
        return x;
    }

    template <typename T> constexpr T rstls1b(T x)
    {
        return x & (x - 1);
    }

    template <typename T> constexpr T setls0b(T x)
    {
        return x | (x + 1);
    }

    template <typename T> constexpr T isols1b(T x)
    {
        return x & -x;
    }

    template <typename T> constexpr T isols0b(T x)
    {
        return (~x) & (x + 1);
    }

    template <typename T> constexpr T rstt1(T x)
    {
        return x & (x + 1);
    }

    template <typename T> constexpr T sett0(T x)
    {
        return x | (x - 1);
    }

    template <typename T> constexpr T maskt0(T x)
    {
        return (~x) & (x - 1);
    }

    template <typename T> constexpr T maskt1(T x)
    {
        return ~((~x) | (x + 1));
    }

    template <typename T> constexpr T maskt0ls1b(T x)
    {
        return (x - 1) ^ x;
    }

    template <typename T> constexpr T maskt1ls0b(T x)
    {
        return x ^ (x + 1);
    }
    // ReverseBits
    template <typename T> constexpr auto reverse_bits(T x, int subword_bits = 1, int group_subwords = 1) noexcept
        -> std::enable_if_t<std::is_unsigned_v<T>, T>
    {
        int group_sz = int(sizeof(T) * CHAR_BIT) / group_subwords;
        int k = group_sz - subword_bits;
        if (k & 1) x = shll(x & T(0x5555555555555555UL), 1) | shlr(x & T(0xAAAAAAAAAAAAAAAAUL), 1);
        if (k & 2) x = shll(x & T(0x3333333333333333UL), 2) | shlr(x & T(0xCCCCCCCCCCCCCCCCUL), 2);
        if (k & 4) x = shll(x & T(0x0F0F0F0F0F0F0F0FUL), 4) | shlr(x & T(0xF0F0F0F0F0F0F0F0UL), 4);
        //sizeof comparisons added to help compiler remove these checks for small integers
        if (sizeof(T) > 1 && k & 8) x = shll(x & T(0x00FF00FF00FF00FFUL), 8) | shlr(x & T(0xFF00FF00FF00FF00UL), 8);
        if (sizeof(T) > 2 && k & 16) x = shll(x & T(0x0000FFFF0000FFFFUL), 16) | shlr(x & T(0xFFFF0000FFFF0000UL), 16);
        if (sizeof(T) > 4 && k & 32) x = shll(x & T(0x00000000FFFFFFFFUL), 32) | shlr(x & T(0xFFFFFFFF00000000UL), 32);
        return x;
    }
    // ReverseBits
    template <typename T> constexpr auto reverse_bits(T x, int subword_bits = 1, int group_subwords = 1) noexcept
        -> std::enable_if_t<std::is_signed_v<T>, T>
    {
        return T(reverse_bits(typename std::make_unsigned<T>::type(x), subword_bits, group_subwords));
    }

    template <typename T> constexpr T reverse_bytes(T x, int bytes_per_block = 1, int blocks_per_group = sizeof(T)) noexcept
    {
        return reverse_bits(x, CHAR_BIT * bytes_per_block, blocks_per_group);
    }

    template <typename T> constexpr T setbit(T x, int b) noexcept
    {
        return x | (T(1) << b);
    }

    template <typename T> constexpr T rstbit(T x, int b) noexcept
    {
        return x & ~(T(1) << b);
    }

    template <typename T> constexpr T flipbit(T x, int b) noexcept
    {
        return x ^ (T(1) << b);
    }

    template <typename T> constexpr bool testbit(T x, int b) noexcept
    {
        return x & (T(1) << b);
    }

    template <typename T> constexpr T rstbitsge(T x, int b) noexcept
    {
        return x & ((T(1) << b) - 1);
    }

    template <typename T> constexpr T rstbitsle(T x, int b) noexcept
    {
        return x & ~((T(1) << (b + 1)) - 1);
    }

    template <typename T> constexpr T setbitsge(T x, int b) noexcept
    {
        return x | ~((T(1) << b) - 1);
    }

    template <typename T> constexpr T setbitsle(T x, int b) noexcept
    {
        return x | ((T(1) << (b + 1)) - 1);
    }

    template <typename T> constexpr T flipbitsge(T x, int b) noexcept
    {
        return x ^ ~((T(1) << b) - 1);
    }

    template <typename T> constexpr T flipbitsle(T x, int b) noexcept
    {
        return x ^ ((T(1) << (b + 1)) - 1);
    }

    // IsPowerOf2
    template <typename T> constexpr bool ispow2(T x) noexcept
    {
        return x > 0 && (x & (x - 1)) == 0;
    }
    // CeilPowerOf2
    template <typename T> constexpr T ceilp2(T x) noexcept
    {
        x = x - 1;
        x |= shlr(x, 1);
        x |= shlr(x, 2);
        x |= shlr(x, 4);

        if (sizeof(T) > 1)
        {
            x |= shlr(x, 8);
            if (sizeof(T) > 2)
            {
                x |= shlr(x, 16);
                if (sizeof(T) > 4)
                {
                    x |= shlr(x, 32);
                }
            }
        }
        return x + 1;
    }
    // FloorPowerOf2
    template <typename T> constexpr T floorp2(T x) noexcept
    {
        x |= shlr(x, 1);
        x |= shlr(x, 2);
        x |= shlr(x, 4);

        if (sizeof(T) > 1)
        {
            x |= shlr(x, 8);
            if (sizeof(T) > 2)
            {
                x |= shlr(x, 16);
                if (sizeof(T) > 4)
                {
                    x |= shlr(x, 32);
                }
            }
        }
        return x - shlr(x, 1);
    }

    template <typename TL, typename TR> constexpr auto satadd(TL l, TR r) noexcept -> decltype(l + r)
    {
        typedef decltype(l + r) LR;
        return (LR(l) > (std::numeric_limits<LR>::max() - LR(r)))
            ? std::numeric_limits<LR>::max()
            : l + r;
    }

    template <typename TL, typename TR> constexpr auto satsub(TL l, TR r) noexcept -> decltype(l - r)
    {
        typedef decltype(l + r) LR;
        return (LR(l) < (std::numeric_limits<LR>::min() + LR(r)))
            ? std::numeric_limits<LR>::min()
            : l - r;
    }

    // IsAligned
    template <typename T> constexpr bool is_aligned(T t, size_t a) noexcept
    {
        return ((t & (a - 1)) == 0);
    }
    // IsAligned
    inline bool is_aligned(void* t, size_t a) noexcept
    {
        return is_aligned(uintptr_t(t), a);
    }
    // AlignUp
    template <typename T> constexpr T align_up(T val, size_t a) noexcept
    {
        return ((val + (a - 1)) & static_cast<size_t>(-static_cast<std::make_signed_t<size_t>>(a)));
    }
    // AlignUp
    inline void* align_up(void* val, size_t a) noexcept
    {
        return reinterpret_cast<void*>(align_up(uintptr_t(val), a));
    }
    // AlignDown
    template <typename T> constexpr T align_down(T val, size_t a) noexcept
    {
        return val & static_cast<size_t>(-static_cast<std::make_signed_t<size_t>>(a));
    }
    // AlignDown
    inline void* align_down(void* val, size_t a) noexcept
    {
        return reinterpret_cast<void*>(align_down(uintptr_t(val), a));
    }

    template <typename T> constexpr T outer_pshuffle(T x) noexcept
    {
        T t = 0;
        if (sizeof(T) > 4)
        {
            t = (x ^ shlr(x, 16)) & T(0x00000000FFFF0000UL);
            x = x ^ t ^ shll(t, 16);
        }
        if (sizeof(T) > 2)
        {
            t = (x ^ shlr(x, 8)) & T(0x0000FF000000FF00UL);
            x = x ^ t ^ shll(t, 8);
        }
        if (sizeof(T) > 1)
        {
            t = (x ^ shlr(x, 4)) & T(0x00F000F000F000F0UL);
            x = x ^ t ^ shll(t, 4);
        }
        t = (x ^ shlr(x, 2)) & T(0x0C0C0C0C0C0C0C0CUL);
        x = x ^ t ^ shll(t, 2);
        t = (x ^ shlr(x, 1)) & T(0x2222222222222222UL);
        x = x ^ t ^ shll(t, 1);
        return x;
    }

    template <typename T> constexpr T outer_punshuffle(T x) noexcept
    {
        T t = 0;
        t = (x ^ shlr(x, 1)) & T(0x2222222222222222UL);
        x = x ^ t ^ shll(t, 1);
        t = (x ^ shlr(x, 2)) & T(0x0C0C0C0C0C0C0C0CUL);
        x = x ^ t ^ shll(t, 2);
        if (sizeof(T) > 1)
        {
            t = (x ^ shlr(x, 4)) & T(0x00F000F000F000F0UL);
            x = x ^ t ^ shll(t, 4);
        }
        if (sizeof(T) > 2)
        {
            t = (x ^ shlr(x, 8)) & T(0x0000FF000000FF00UL);
            x = x ^ t ^ shll(t, 8);
        }
        if (sizeof(T) > 4)
        {
            t = (x ^ shlr(x, 16)) & T(0x00000000FFFF0000UL);
            x = x ^ t ^ shll(t, 16);
        }
        return x;
    }

    template <typename T> constexpr T inner_pshuffle(T x) noexcept
    {
        return outer_pshuffle(reverse_bits(x, sizeof(T) * CHAR_BIT / 2, 2));
    }

    template <typename T> constexpr T inner_punshuffle(T x) noexcept
    {
        return reverse_bits(outer_punshuffle(x), sizeof(T) * CHAR_BIT / 2, 2);
    }

    template <typename T> constexpr T deposit_bits(T x, T mask)
    {
        T res = 0;
        for (T bb = 1; mask != 0; bb += bb)
        {
            if (x & bb)
            {
                res |= mask & (-mask);
            }
            mask &= (mask - 1);
        }
        return res;
    }

    template <typename T> constexpr T extract_bits(T x, T mask)
    {
        T res = 0;
        for (T bb = 1; mask != 0; bb += bb)
        {
            if (x & mask & -mask)
            {
                res |= bb;
            }
            mask &= (mask - 1);
        }
        return res;
    }
}

namespace Graphyte::Intrinsics
{
    template <typename T> constexpr T unsigned_negate(T x) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const nx = -x;
        return nx;
    }

    template <typename T> constexpr T unsigned_not(T x) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const nx = ~x;
        return nx;
    }

    template <typename T> constexpr T unsigned_extend(T x) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const result = static_cast<T>(static_cast<std::make_signed_t<T>>(x) >> ((CHAR_BIT * sizeof(T)) - 1));
        return result;
    }

    template <typename T> constexpr T unsigned_nor(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const xy = x | y;
        T const nxy = ~xy;
        return nxy;
    }

    template <typename T> constexpr T unsigned_andnot(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const ny = ~y;
        T const xny = x & ny;
        return xny;
    }

    template <typename T> constexpr T unsigned_and(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const xy = x & y;
        return xy;
    }

    template <typename T> constexpr T unsigned_xor(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const xy = x ^ y;
        return xy;
    }

    template <typename T> constexpr T unsigned_or(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const xy = x | y;
        return xy;
    }

    template <typename T> constexpr T unsigned_or(T x, T y, T z) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const xyz = x | y | z;
        return xyz;
    }

    template <typename T> constexpr T unsigned_select(T mask, T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const x_masked = unsigned_and<T>(x, mask);
        T const y_masked = unsigned_andnot<T>(y, mask);
        T const xy = unsigned_or<T>(x_masked, y_masked);
        return xy;
    }

    template <typename T> constexpr T unsigned_cmp_lt(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        using Ts = std::make_signed_t<T>;

        T const result = static_cast<T>(static_cast<Ts>(x - y) >> ((CHAR_BIT * sizeof(T)) - 1));
        return result;
    }

    template <typename T> constexpr T unsigned_cmp_ge(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return ~unsigned_cmp_lt<T>(x, y);
    }

    template <typename T> constexpr T unsigned_cmp_gt(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        using Ts = std::make_signed_t<T>;

        T const result = static_cast<T>(static_cast<Ts>(y - x) >> ((CHAR_BIT * sizeof(T)) - 1));
        return result;
    }

    template <typename T> constexpr T unsigned_cmp_le(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return ~unsigned_cmp_gt<T>(x, y);
    }

    template <typename T> constexpr T unsigned_nez(T x) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        using Ts = std::make_signed_t<T>;

        T const result = static_cast<T>(static_cast<Ts>(x | -x) >> ((CHAR_BIT * sizeof(T)) - 1));
        return result;
    }

    template <typename T> constexpr T unsigned_nezp(T x) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        T const result = static_cast<T>(static_cast<T>(x | -x) >> ((CHAR_BIT * sizeof(T)) - 1));
        return result;
    }

    template <typename T> constexpr T unsigned_eqz(T x) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return ~unsigned_nez<T>(x);
    }

    template <typename T> constexpr T unsigned_cmp_eq(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return ~unsigned_nez<T>(x - y);
    }

    template <typename T> constexpr T unsigned_cmp_neq(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return unsigned_nez<T>(x - y);
    }

    template <typename T> constexpr T unsigned_srl(T x, T bits) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return x >> bits;
    }

    template <typename T> constexpr T unsigned_sll(T x, T bits) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return x << bits;
    }

    template <typename T> constexpr T unsigned_add(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return x + y;
    }

    template <typename T> constexpr T unsigned_sub(T x, T y) noexcept
    {
        static_assert(std::is_unsigned_v<T>);
        return x - y;
    }
}
