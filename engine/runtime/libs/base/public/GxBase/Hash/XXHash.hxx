#pragma once
#include <GxBase/Base.module.hxx>

//
// Implementation based on:
// https://github.com/Cyan4973/xxHash/
//

namespace Graphyte::Hash
{
    struct BASE_API XXHash64 final
    {
    private:
        static constexpr const uint64_t Prime1 = 11400714785074694791u;
        static constexpr const uint64_t Prime2 = 14029467366897019727u;
        static constexpr const uint64_t Prime3 = 1609587929392839161u;
        static constexpr const uint64_t Prime4 = 9650029242287828579u;
        static constexpr const uint64_t Prime5 = 2870177450012600261u;

        static constexpr const size_t MaxBufferSize = 32;

    private:
        uint64_t m_State[4];
        uint8_t m_Buffer[MaxBufferSize];
        size_t m_BufferSize;
        uint64_t m_Length;

    public:
        explicit XXHash64(uint64_t seed) noexcept;
        XXHash64() = delete;

    public:
        bool Update(const void* input, size_t input_size) noexcept;
        uint64_t GetValue() const noexcept;

    public:
        static uint64_t Hash(const void* buffer, size_t buffer_size, uint64_t seed) noexcept;

    private:
        static uint64_t ProcessSingle(uint64_t previous, uint64_t input) noexcept;
        static void ProcessBlock(const void* block, uint64_t& state0, uint64_t& state1, uint64_t& state2, uint64_t& state3) noexcept;
    };
}
