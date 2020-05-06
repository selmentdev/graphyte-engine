#pragma once
#include <GxBase/Storage/IStream.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>

namespace Graphyte::Storage
{
    class WindowsFileStream final
        : public IStream
    {
    private:
        static constexpr const size_t BufferSize = 1 * 1024 * 1024;

    private:
        HANDLE m_Handle;
        OVERLAPPED m_Async;
        std::int64_t m_Position;
        std::int64_t m_Size;

    private:
        __forceinline bool IsValidHandle() const noexcept
        {
            return this->m_Handle != nullptr
                && this->m_Handle != INVALID_HANDLE_VALUE;
        }

        __forceinline void UpdatePosition() noexcept
        {
            auto position = System::TypeConverter<ULARGE_INTEGER>::ConvertInt64(this->m_Position);
            this->m_Async.Offset = position.LowPart;
            this->m_Async.OffsetHigh = position.HighPart;
        }

        __forceinline void UpdateSize() noexcept
        {
            LARGE_INTEGER li{};
            GetFileSizeEx(this->m_Handle, &li);
            this->m_Size = li.QuadPart;
        }

    public:
        WindowsFileStream(
            HANDLE handle
        ) noexcept
            : m_Handle{ handle }
            , m_Async{}
            , m_Position{}
            , m_Size{}
        {
            GX_ASSERT(this->IsValidHandle());

            if (this->IsValidHandle())
            {
                this->UpdateSize();
            }
        }

        virtual ~WindowsFileStream() noexcept
        {
            GX_ASSERT(this->IsValidHandle());

            CloseHandle(this->m_Handle);
        }

    public:
        virtual Status Flush() noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            if (FlushFileBuffers(this->m_Handle) != FALSE)
            {
                return Status::Success;
            }

            return Status::Failure;
        }

        virtual Status Read(
            notstd::span<std::byte> buffer,
            size_t& processed
        ) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            processed = 0;

            while (!buffer.empty())
            {
                DWORD dwRequested = static_cast<DWORD>(std::min<size_t>(BufferSize, buffer.size()));
                DWORD dwProcessed = 0;

                if (ReadFile(this->m_Handle, buffer.data(), dwRequested, &dwProcessed, &this->m_Async) == FALSE)
                {
                    DWORD dwError = GetLastError();

                    if (dwError == ERROR_HANDLE_EOF)
                    {
                        //
                        // Note: ReadFile returns EOF only when no more bytes are available.
                        //       It still returns TRUE when read was partial.
                        //

                        return Status::EndOfStream;
                    }
                    else if (dwError != ERROR_IO_PENDING)
                    {
                        return Status::ReadFault;
                    }

                    dwProcessed = 0;

                    if (GetOverlappedResult(this->m_Handle, &this->m_Async, &dwProcessed, TRUE) == FALSE)
                    {
                        return Status::ReadFault;
                    }
                }

                processed += dwProcessed;

                buffer.remove_prefix(dwProcessed);

                this->m_Position += dwProcessed;
                this->UpdatePosition();
            }

            return Status::Success;
        }

        virtual Status Write(
            notstd::span<const std::byte> buffer,
            size_t& processed
        ) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            while (!buffer.empty())
            {
                DWORD dwRequested = static_cast<DWORD>(std::min<size_t>(BufferSize, buffer.size()));
                DWORD dwProcessed = 0;

                if (WriteFile(this->m_Handle, buffer.data(), dwRequested, &dwProcessed, &this->m_Async) == FALSE)
                {
                    DWORD dwError = GetLastError();

                    if (dwError != ERROR_HANDLE_EOF)
                    {
                        return Status::EndOfStream;
                    }
                    else if (dwError != ERROR_IO_PENDING)
                    {
                        return Status::WriteFault;
                    }

                    dwProcessed = 0;

                    if (GetOverlappedResult(this->m_Handle, &this->m_Async, &dwProcessed, TRUE) == false)
                    {
                        return Status::WriteFault;
                    }
                }

                buffer.remove_prefix(dwProcessed);

                processed += dwProcessed;
                m_Position += dwProcessed;

                this->UpdatePosition();
                this->UpdateSize();
            }

            return Status::Success;
        }

        virtual int64_t GetSize() noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            return this->m_Size;
        }

        virtual int64_t GetPosition() noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            return this->m_Position;
        }

        virtual Status SetPosition(
            int64_t value,
            SeekOrigin origin
        ) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            int64_t current = this->m_Position;

            switch (origin)
            {
            case SeekOrigin::Begin:
                {
                    GX_ASSERT(value >= 0);

                    current = value;
                    break;
                }

            case SeekOrigin::Current:
                {
                    current += value;
                    break;
                }

            case SeekOrigin::End:
                {
                    current = this->m_Size - value;
                    break;
                }

            default:
                {
                    GX_ASSERT(false);
                    return Status::InvalidArgument;
                }
            }

            GX_ASSERT(current >= 0);
            GX_ASSERT(current < this->m_Size);

            this->m_Position = current;

            this->UpdatePosition();

            return Status::Success;
        }

        virtual Status SetPosition(
            int64_t value
        ) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());
            GX_ASSERT(value >= 0);
            GX_ASSERT(value < m_Size);

            this->m_Position = value;

            this->UpdatePosition();

            return Status::Success;
        }
    };
}
