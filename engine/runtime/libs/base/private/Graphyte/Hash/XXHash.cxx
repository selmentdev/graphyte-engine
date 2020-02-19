#include <Graphyte/Hash/XXHash.hxx>
#include <Graphyte/ByteAccess.hxx>

namespace Graphyte::Hash
{
    XXHash64::XXHash64(
        uint64_t seed
    ) noexcept
        : m_State{}
        , m_Buffer{}
        , m_BufferSize{}
        , m_Length{}
    {
        m_State[0] = seed + Prime1 + Prime2;
        m_State[1] = seed + Prime2;
        m_State[2] = seed;
        m_State[3] = seed - Prime1;
    }

    bool XXHash64::Update(
        const void* input,
        size_t input_size
    ) noexcept
    {
        if (input == nullptr || input_size == 0)
        {
            return false;
        }

        m_Length += input_size;

        auto data = reinterpret_cast<uint8_t const*>(input);

        if ((m_BufferSize + input_size) < MaxBufferSize)
        {
            while (input_size-- > 0)
            {
                m_Buffer[m_BufferSize++] = (*data++);
            }

            return true;
        }

        uint8_t const* stop = data + input_size;
        uint8_t const* stop_block = stop - MaxBufferSize;

        if (m_BufferSize > 0)
        {
            while (m_BufferSize < MaxBufferSize)
            {
                m_Buffer[m_BufferSize++] = (*data++);
            }

            ProcessBlock(m_Buffer, m_State[0], m_State[1], m_State[2], m_State[3]);
        }

        uint64_t s0 = m_State[0];
        uint64_t s1 = m_State[1];
        uint64_t s2 = m_State[2];
        uint64_t s3 = m_State[3];

        while (data <= stop_block)
        {
            ProcessBlock(data, s0, s1, s2, s3);
            data += sizeof(uint64_t) * 4;
        }

        m_State[0] = s0;
        m_State[1] = s1;
        m_State[2] = s2;
        m_State[3] = s3;

        m_BufferSize = static_cast<size_t>(stop - data);

        for (size_t i = 0; i < m_BufferSize; ++i)
        {
            m_Buffer[i] = data[i];
        }

        return true;
    }

    uint64_t XXHash64::GetValue() const noexcept
    {
        uint64_t result{};

        if (m_Length >= MaxBufferSize)
        {
            result
                = RotateLeft<uint64_t>(m_State[0], 1)
                + RotateLeft<uint64_t>(m_State[1], 7)
                + RotateLeft<uint64_t>(m_State[2], 12)
                + RotateLeft<uint64_t>(m_State[3], 18);

            result = (result ^ ProcessSingle(0, m_State[0])) * Prime1 + Prime4;
            result = (result ^ ProcessSingle(0, m_State[1])) * Prime1 + Prime4;
            result = (result ^ ProcessSingle(0, m_State[2])) * Prime1 + Prime4;
            result = (result ^ ProcessSingle(0, m_State[3])) * Prime1 + Prime4;
        }
        else
        {
            result = m_State[2] + Prime5;
        }

        result += m_Length;

        uint8_t const* data = m_Buffer;
        uint8_t const* stop = data + m_BufferSize;

        for (; (data + 8) <= stop; data += 8)
        {
            result = RotateLeft<uint64_t>(result ^ ProcessSingle(0, *reinterpret_cast<const uint64_t*>(data)), 27) * Prime1 + Prime4;
        }

        if ((data + 4) <= stop)
        {
            result = RotateLeft<uint64_t>(result ^ *reinterpret_cast<const uint32_t*>(data) * Prime1, 23) * Prime2 + Prime3;
            data += 4;
        }

        while (data != stop)
        {
            result = RotateLeft(result ^ (*data++) * Prime5, 11) * Prime1;
        }

        result ^= result >> 33;
        result *= Prime2;
        result ^= result >> 29;
        result *= Prime3;
        result ^= result >> 32;

        return result;
    }

    uint64_t XXHash64::Hash(
        const void* buffer,
        size_t buffer_size,
        uint64_t seed
    ) noexcept
    {
        XXHash64 hash{ seed };
        hash.Update(buffer, buffer_size);
        return hash.GetValue();
    }

    uint64_t XXHash64::ProcessSingle(
        uint64_t previous,
        uint64_t input
    ) noexcept
    {
        return RotateLeft<uint64_t>(previous + input * Prime2, 31) * Prime1;
    }

    void XXHash64::ProcessBlock(
        const void* block,
        uint64_t& state0,
        uint64_t& state1,
        uint64_t& state2,
        uint64_t& state3
    ) noexcept
    {
        auto as_uint64 = reinterpret_cast<const uint64_t*>(block);
        state0 = ProcessSingle(state0, as_uint64[0]);
        state1 = ProcessSingle(state1, as_uint64[1]);
        state2 = ProcessSingle(state2, as_uint64[2]);
        state3 = ProcessSingle(state3, as_uint64[3]);
    }
}
