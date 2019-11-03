#include "Base.pch.hxx"
#include <Graphyte/Storage/ArchiveFileWriter.hxx>
#include <Graphyte/Storage/IStream.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Bitwise.hxx>

namespace Graphyte::Storage
{
    ArchiveFileWriter::ArchiveFileWriter(
        std::unique_ptr<IStream> stream,
        int64_t position
    ) noexcept
        : Archive()
        , m_Stream{ std::move(stream) }
        , m_Position{ position }
        , m_BufferCount{ 0 }
        , m_Buffer{}
    {
        GX_ASSERT(m_Stream != nullptr);
        m_IsSaving = true;
    }

    ArchiveFileWriter::~ArchiveFileWriter() noexcept
    {
        Flush();
    }

    void ArchiveFileWriter::Serialize(
        void* buffer,
        size_t size
    ) noexcept
    {
        m_Position += size;

        if (size > m_Buffer.size())
        {
            Flush();
            size_t processed{};

            if (m_Stream->Write({ reinterpret_cast<std::byte*>(buffer), size }, processed) != Status::Success)
            {
                GX_LOG(LogStorage, Error, "Write failure: request = {}, processed = {}\n", size, processed);
                m_Error = true;
            }
        }
        else
        {
            size_t copied;

            while (size > (copied = (m_Buffer.size() - m_BufferCount)))
            {
                std::memcpy(m_Buffer.data() + m_BufferCount, buffer, copied);
                m_BufferCount += copied;

                GX_ASSERT(m_BufferCount <= m_Buffer.size());

                size -= copied;
                buffer = AdvancePointer(buffer, static_cast<ptrdiff_t>(copied));
                Flush();
            }

            if (size != 0)
            {
                std::memcpy(m_Buffer.data() + m_BufferCount, buffer, size);
                m_BufferCount += size;

                GX_ASSERT(m_BufferCount <= m_Buffer.size());
            }
        }
    }

    int64_t ArchiveFileWriter::GetPosition() noexcept
    {
        return m_Position;
    }

    int64_t ArchiveFileWriter::GetSize() noexcept
    {
        Flush();
        return m_Stream->GetSize();
    }

    void ArchiveFileWriter::SetPosition(
        int64_t value
    ) noexcept
    {
        Flush();
        if (m_Stream->SetPosition(value) != Status::Success)
        {
            GX_LOG(LogStorage, Error, "Set position failed: position = {}\n", value);
            m_Error = true;
        }

        m_Position = value;
    }

    void ArchiveFileWriter::Flush() noexcept
    {
        if (m_BufferCount != 0)
        {
            GX_ASSERT(0 < m_BufferCount);
            GX_ASSERT(m_BufferCount <= m_Buffer.size());

            size_t processed{};

            if (m_Stream->Write({ &m_Buffer[0], m_BufferCount }, processed) != Status::Success)
            {
                GX_LOG(LogStorage, Error, "Flush failure\n");
                m_Error = true;
            }

            m_BufferCount = 0;
        }

        if (m_Stream != nullptr)
        {
            [[maybe_unused]] auto status = m_Stream->Flush();
        }
    }
}
