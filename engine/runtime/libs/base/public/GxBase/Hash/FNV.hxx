#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Hash
{
    struct HashFnv1A32 final
    {
        using hash_type = uint32_t;

        static constexpr const hash_type Prime   = 0x01000193;
        static constexpr const hash_type Initial = 0x811C9DC5;

        [[nodiscard]] static constexpr hash_type FromString(const char* s, hash_type initial) noexcept
        {
            hash_type result = initial;

            while (*s != '\0')
            {
                hash_type value = static_cast<uint8_t>(*s++);

                result = result ^ value;
                result *= Prime;
            }

            return result;
        }

        [[nodiscard]] static constexpr hash_type FromString(const char* s) noexcept
        {
            return FromString(s, Initial);
        }

        [[nodiscard]] static constexpr hash_type FromBuffer(const char* buffer, size_t size, hash_type initial) noexcept
        {
            hash_type result = initial;

            for (size_t i = 0; i < size; ++i)
            {
                hash_type value = static_cast<uint8_t>(buffer[i]);

                result = result ^ value;
                result *= Prime;
            }

            return result;
        }

        [[nodiscard]] static constexpr hash_type FromBuffer(const char* buffer, size_t size) noexcept
        {
            return FromBuffer(buffer, size, Initial);
        }
    };

    struct HashFnv1A64 final
    {
        using hash_type = uint64_t;

        static constexpr const hash_type Prime   = 0x00000100000001B3;
        static constexpr const hash_type Initial = 0xCBF29CE484222325;

        [[nodiscard]] static constexpr hash_type FromString(const char* s, hash_type initial) noexcept
        {
            hash_type result = initial;

            while (*s != '\0')
            {
                hash_type value = static_cast<uint8_t>(*s++);

                result = result ^ value;
                result *= Prime;
            }

            return result;
        }

        [[nodiscard]] static constexpr hash_type FromString(const char* s) noexcept
        {
            return FromString(s, Initial);
        }

        [[nodiscard]] static constexpr hash_type FromBuffer(const std::byte* buffer, size_t size, hash_type initial) noexcept
        {
            hash_type result = initial;

            for (size_t i = 0; i < size; ++i)
            {
                hash_type value = static_cast<uint8_t>(buffer[i]);

                result = result ^ value;
                result *= Prime;
            }

            return result;
        }
        [[nodiscard]] static constexpr hash_type FromBuffer(const std::byte* buffer, size_t size) noexcept
        {
            return FromBuffer(buffer, size, Initial);
        }
    };
}
