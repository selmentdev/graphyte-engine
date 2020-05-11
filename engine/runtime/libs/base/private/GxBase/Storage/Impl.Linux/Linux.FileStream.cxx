#include <GxBase/Bitwise.hxx>
#include "Linux.FileStream.hxx"

namespace Graphyte::Storage
{
    LinuxFileStream::LinuxFileStream(
        int32_t handle,
        const char* name,
        bool writing
    ) noexcept
        : m_FileName{ name }
        , m_Offset{ 0 }
        , m_Size{ 0 }
        , m_Handle{ handle }
        , m_Writing{ writing }
    {
        GX_ASSERT(this->IsValid());
        GX_ASSERT(!m_FileName.empty());

        if (!m_Writing)
        {
            struct stat fileinfo{};
            fstat(m_Handle, &fileinfo);
            m_Size = fileinfo.st_size;
        }
    }

    LinuxFileStream::~LinuxFileStream() noexcept
    {
        GX_ASSERT(IsValid());

        close(m_Handle);
    }

    Status LinuxFileStream::Flush() noexcept
    {
        GX_ASSERT(IsValid());

        if (fsync(m_Handle) == 0)
        {
            return Status::Success;
        }

        return Status::Failure;
    }

    Status LinuxFileStream::Read(
        notstd::span<std::byte> buffer,
        size_t& processed
    ) noexcept
    {
        GX_ASSERT(IsValid());

        processed = 0;


        //
        // Move file to current position.
        //

        if (lseek(m_Handle, m_Offset, SEEK_SET) == -1)
        {
            return Status::ReadFault;
        }

        while (!buffer.empty())
        {
            size_t bytes_requested = std::min<size_t>(BufferSize, buffer.size());

            ssize_t bytes_processed = read(m_Handle, buffer.data(), bytes_requested);

            if (bytes_processed == 0)
            {
                return Status::EndOfStream;
            }
            else if (bytes_processed < 0)
            {
                if (errno == EINTR)
                {
                    continue;
                }

                return Status::ReadFault;
            }

            buffer.remove_prefix(static_cast<size_t>(bytes_processed));
            m_Offset += static_cast<size_t>(bytes_processed);
            processed += static_cast<size_t>(bytes_processed);
        }

        return Status::Success;
    }

    Status LinuxFileStream::Write(
        notstd::span<const std::byte> buffer,
        size_t& processed
    ) noexcept
    {
        GX_ASSERT(IsValid());
        GX_ASSERT(m_Writing);

        while (!buffer.empty())
        {
            size_t bytes_requested = std::min<size_t>(BufferSize, buffer.size());

            ssize_t bytes_processed = write(m_Handle, buffer.data(), bytes_requested);

            if (bytes_processed == 0)
            {
                if (errno == EINTR)
                {
                    continue;
                }

                return Status::WriteFault;
            }

            buffer.remove_prefix(static_cast<size_t>(bytes_processed));
            processed += static_cast<size_t>(bytes_processed);
        }

        return Status::Success;
    }

    int64_t LinuxFileStream::GetSize() noexcept
    {
        GX_ASSERT(IsValid());

        if (m_Writing)
        {
            struct stat fileinfo{};
            fstat(m_Handle, &fileinfo);
            return fileinfo.st_size;
        }
        else
        {
            return m_Size;
        }
    }

    int64_t LinuxFileStream::GetPosition() noexcept
    {
        GX_ASSERT(IsValid());

        if (m_Writing)
        {
            return lseek(m_Handle, 0, SEEK_CUR);
        }
        else
        {
            return m_Offset;
        }
    }

    Status LinuxFileStream::SetPosition(
        int64_t value
    ) noexcept
    {
        GX_ASSERT(IsValid());
        GX_ASSERT(value >= 0);

        if (m_Writing)
        {
            if (lseek(m_Handle, value, SEEK_SET) < 0)
            {
                return Status::Failure;
            }
        }
        else
        {
            m_Offset = (value >= m_Size) ? (m_Size - 1) : value;
        }

        return Status::Success;
    }

    Status LinuxFileStream::SetPosition(
        int64_t value,
        SeekOrigin origin
    ) noexcept
    {
        GX_ASSERT(IsValid());

        if (m_Writing)
        {
            int seek = SEEK_SET;
            if (origin == SeekOrigin::Current)
            {
                seek = SEEK_CUR;
            }
            else if (origin == SeekOrigin::End)
            {
                seek = SEEK_END;
            }

            if (lseek(m_Handle, value, seek) < 0)
            {
                return Status::Failure;
            }
        }
        else
        {
            m_Offset = value;
        }

        return Status::Success;
    }
}
