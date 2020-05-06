#include <GxBase/Storage/ArchiveMemoryWriter.hxx>

namespace Graphyte::Storage
{
    ArchiveMemoryWriter::ArchiveMemoryWriter(
        std::vector<std::byte>& buffer,
        bool persistent
    ) noexcept
        : Archive{}
        , m_Offset{ 0 }
        , m_Buffer{ buffer }
    {
        m_IsSaving = true;
        m_Persistent = persistent;
    }

    ArchiveMemoryWriter::~ArchiveMemoryWriter() noexcept
    {
    }

    void ArchiveMemoryWriter::Serialize(
        void* buffer,
        size_t size
    ) noexcept
    {
        const int64_t required = m_Offset + static_cast<int64_t>(size) - GetSize();
        if (required > 0)
        {
            const int64_t new_size = GetSize() + required;
            GX_ASSERT(new_size >= 0);

            if (new_size >= std::numeric_limits<int32_t>::max())
            {
                GX_ASSERTF(false, "Buffer size exceeds 2 GiB");
            }

            m_Buffer.resize(static_cast<size_t>(new_size));
        }

        GX_ASSERT((m_Offset + static_cast<int64_t>(size)) <= GetSize());

        if (size != 0)
        {
            std::memcpy(&m_Buffer[static_cast<size_t>(m_Offset)], buffer, size);
            m_Offset += size;
        }
    }

    int64_t ArchiveMemoryWriter::GetPosition() noexcept
    {
        return m_Offset;
    }

    int64_t ArchiveMemoryWriter::GetSize() noexcept
    {
        return static_cast<int64_t>(m_Buffer.size());
    }

    void ArchiveMemoryWriter::SetPosition(int64_t position) noexcept
    {
        GX_ASSERT(position >= 0);
        GX_ASSERT(position <= GetSize());
        m_Offset = position;
    }
}
