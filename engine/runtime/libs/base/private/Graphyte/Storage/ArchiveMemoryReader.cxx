#include "Base.pch.hxx"
#include <Graphyte/Storage/ArchiveMemoryReader.hxx>

namespace Graphyte::Storage
{
    ArchiveMemoryReader::ArchiveMemoryReader(
        const std::vector<std::byte>& buffer,
        bool persistent
    ) noexcept
        : Archive{}
        , m_Offset{ 0 }
        , m_Buffer{ buffer }
    {
        m_IsLoading = true;
        m_Persistent = persistent;
    }

    ArchiveMemoryReader::~ArchiveMemoryReader() noexcept
    {
    }

    void ArchiveMemoryReader::Serialize(
        void* buffer,
        size_t size
    ) noexcept
    {
        if (size != 0 && !m_Error)
        {
            if ((m_Offset + static_cast<int64_t>(size)) <= GetSize())
            {
                std::memcpy(buffer, &m_Buffer[static_cast<size_t>(m_Offset)], size);
                m_Offset += size;
            }
            else
            {
                m_Error = true;
            }
        }
    }

    int64_t ArchiveMemoryReader::GetPosition() noexcept
    {
        return m_Offset;
    }

    int64_t ArchiveMemoryReader::GetSize() noexcept
    {
        return static_cast<int64_t>(m_Buffer.size());
    }

    void ArchiveMemoryReader::SetPosition(int64_t position) noexcept
    {
        GX_ASSERT(position >= 0);
        GX_ASSERT(position <= GetSize());
        m_Offset = position;
    }
}
