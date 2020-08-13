#include <GxBase/Storage/ArchiveFileReader.hxx>
#include <GxBase/Bitwise.hxx>

namespace Graphyte::Storage
{
    ArchiveFileReader::ArchiveFileReader(
        std::unique_ptr<IStream> stream) noexcept
        : Archive()
        , m_Stream{ std::move(stream) }
        , m_Position{ 0 }
        , m_Size{ 0 }
        , m_BufferBase{ 0 }
        , m_BufferCount{ 0 }
        , m_Buffer{}
    {
        GX_ASSERTF(m_Stream != nullptr, "Invalid file handle provided");
        m_IsLoading = true;

        m_Size = m_Stream->GetSize();
    }

    ArchiveFileReader::~ArchiveFileReader() noexcept
    {
    }

    void ArchiveFileReader::Serialize(
        void* buffer,
        size_t size) noexcept
    {
        if ((m_Position + static_cast<int64_t>(size)) > m_Size)
        {
            m_Error = true;
            return;
        }

        while (size != 0)
        {
            int64_t copy = std::min<int64_t>(
                static_cast<int64_t>(size),
                m_BufferBase + static_cast<int64_t>(m_BufferCount) - m_Position);

            if (copy <= 0)
            {
                if (size >= m_Buffer.size())
                {
                    size_t count     = 0;
                    size_t processed = 0;
                    if (m_Stream->Read({ reinterpret_cast<std::byte*>(buffer), size }, processed) == Status::Success)
                    {
                        count = size;
                    }

                    if (count != size)
                    {
                        GX_LOG_ERROR(LogStorage, "Read failure: request = {}, processed = {}\n", size, count);
                        m_Error = true;
                    }

                    m_Position += size;
                    return;
                }

                if (!PrecacheImpl(m_Position, std::numeric_limits<int32_t>::max()))
                {
                    GX_LOG_ERROR(LogStorage, "Read failure: precaching failed\n");
                    m_Error = true;
                    return;
                }

                copy = std::min<int64_t>(
                    static_cast<int64_t>(size),
                    m_BufferBase + static_cast<int64_t>(m_BufferCount) - m_Position);

                if (copy <= 0)
                {
                    GX_LOG_ERROR(LogStorage, "Read failure: read beyond end of file");
                    m_Error = true;
                }

                if (m_Error)
                {
                    return;
                }
            }

            std::memcpy(
                buffer,
                m_Buffer.data() + m_Position - m_BufferBase,
                static_cast<size_t>(copy));

            m_Position += copy;
            size -= static_cast<size_t>(copy);
            buffer = AdvancePointer(buffer, static_cast<ptrdiff_t>(copy));
        }
    }

    int64_t ArchiveFileReader::GetPosition() noexcept
    {
        return m_Position;
    }

    int64_t ArchiveFileReader::GetSize() noexcept
    {
        return m_Size;
    }

    void ArchiveFileReader::SetPosition(
        int64_t position) noexcept
    {
        [[maybe_unused]] auto status = m_Stream->SetPosition(position);
    }

    void ArchiveFileReader::Flush() noexcept
    {
        [[maybe_unused]] auto status = m_Stream->Flush();
    }

    bool ArchiveFileReader::PrecacheImpl(
        int64_t offset,
        int64_t size) noexcept
    {
        if (m_Position == offset && (m_BufferBase == 0 || m_BufferCount == 0 || m_BufferBase != m_Position))
        {
            m_BufferBase = m_Position;

            int64_t buffer_count = std::min<int64_t>({ size,
                m_Size - m_Position,
                static_cast<int64_t>(
                    static_cast<uint64_t>(m_Buffer.size()) - (static_cast<uint64_t>(m_Position) & static_cast<uint64_t>(m_Buffer.size() - 1))) });

            buffer_count  = std::max<int64_t>(buffer_count, 0);
            m_BufferCount = static_cast<size_t>(buffer_count);

            int64_t count = 0;

            if (m_BufferCount > m_Buffer.size())
            {
                return false;
            }

            size_t processed{};
            if (m_Stream->Read({ reinterpret_cast<std::byte*>(m_Buffer.data()), m_BufferCount }, processed) == Status::Success)
            {
                count = static_cast<int64_t>(m_BufferCount);
                GX_ASSERT(count >= 0);
            }

            if (count != buffer_count)
            {
                m_Error = true;
            }
        }

        return true;
    }
}
