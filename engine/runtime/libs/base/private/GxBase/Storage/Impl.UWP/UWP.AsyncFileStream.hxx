#pragma once
#include <GxBase/Storage/IStream.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>

namespace Graphyte::Storage
{
    class WindowsAsyncFileStream final
        : public IStream
    {
    private:
        static constexpr const DWORD DefaultBufferSize = 64 * 1024;

    private:
        HANDLE m_Handle;
        OVERLAPPED m_Async;
        int64_t m_Size;
        int64_t m_Position;
        uint64_t m_AsyncPosition;
        std::unique_ptr<std::byte[]> m_Buffers[2];
        size_t m_SerializePosition;
        int32_t m_SerializeBuffer;
        int32_t m_StreamBuffer;
        int32_t m_CurrentAsyncReadBuffer;
        bool m_IsEOF;
        bool m_IsReading;

    private:
        bool Close() noexcept
        {
            if (this->IsValidHandle())
            {
                CloseHandle(this->m_Handle);
                this->m_Handle = nullptr;
            }

            return true;
        }

        __forceinline void SwapBuffers() noexcept
        {
            this->m_StreamBuffer ^= 0b1;

            this->m_SerializeBuffer ^= 0b1;
            this->m_SerializePosition = 0;
        }

        __forceinline void UpdateAsync() noexcept
        {
            ULARGE_INTEGER li{};
            li.QuadPart              = this->m_AsyncPosition;
            this->m_Async.Offset     = li.LowPart;
            this->m_Async.OffsetHigh = li.HighPart;
        }

        void UpdateFileOffsetAfterRead(DWORD processed) noexcept
        {
            this->m_IsReading = false;
            this->m_AsyncPosition += processed;

            this->UpdateAsync();

            if (this->m_AsyncPosition >= static_cast<uint64_t>(this->m_Size))
            {
                this->m_IsEOF = true;
            }
        }

        bool WaitForAsyncRead() noexcept
        {
            if (this->m_IsEOF || !this->m_IsReading)
            {
                return true;
            }

            DWORD dwProcessed{};

            if (GetOverlappedResult(this->m_Handle, &this->m_Async, &dwProcessed, TRUE) != FALSE)
            {
                this->UpdateFileOffsetAfterRead(dwProcessed);
                return true;
            }
            else if (GetLastError() == ERROR_HANDLE_EOF)
            {
                this->m_IsEOF = true;
                return true;
            }

            return false;
        }

        void StartAsyncRead(
            int32_t buffer) noexcept
        {
            if (!this->m_IsEOF)
            {
                this->m_IsReading              = true;
                this->m_CurrentAsyncReadBuffer = buffer;

                DWORD dwProcessed{};

                if (ReadFile(this->m_Handle, this->m_Buffers[buffer].get(), DefaultBufferSize, &dwProcessed, &this->m_Async) != FALSE)
                {
                    this->UpdateFileOffsetAfterRead(dwProcessed);
                }
                else
                {
                    DWORD dwError = GetLastError();

                    if (dwError != ERROR_IO_PENDING)
                    {
                        this->m_IsEOF     = true;
                        this->m_IsReading = false;
                    }
                }
            }
        }

        __forceinline void StartStreamBufferRead() noexcept
        {
            this->StartAsyncRead(m_StreamBuffer);
        }

        __forceinline void StartSerializeBufferRead() noexcept
        {
            this->StartAsyncRead(m_SerializeBuffer);
        }

        __forceinline bool IsValidHandle() const noexcept
        {
            return this->m_Handle != nullptr
                   && this->m_Handle != INVALID_HANDLE_VALUE;
        }

    public:
        WindowsAsyncFileStream(
            HANDLE handle) noexcept
            : m_Handle{ handle }
            , m_Async{}
            , m_Size{}
            , m_Position{}
            , m_AsyncPosition{}
            , m_Buffers{}
            , m_SerializePosition{}
            , m_SerializeBuffer{}
            , m_StreamBuffer{ 1 }
            , m_CurrentAsyncReadBuffer{}
            , m_IsEOF{ false }
            , m_IsReading{ false }
        {
            GX_ASSERT(this->IsValidHandle());

            LARGE_INTEGER li{};
            GetFileSizeEx(this->m_Handle, &li);

            this->m_Size = li.QuadPart;

            this->m_Buffers[0] = std::make_unique<std::byte[]>(DefaultBufferSize);
            this->m_Buffers[1] = std::make_unique<std::byte[]>(DefaultBufferSize);

            this->StartSerializeBufferRead();
        }

        virtual ~WindowsAsyncFileStream() noexcept
        {
            this->WaitForAsyncRead();
            this->Close();
        }

    public:
        virtual Status Flush() noexcept final override
        {
            return Status::Success;
        }

        virtual Status Read(
            std::span<std::byte> buffer,
            size_t& processed) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            processed = 0;

            if (buffer.empty())
            {
                return Status::Success;
            }

            if (this->m_Position >= this->m_Size)
            {
                //
                // Already saw EOF.
                //

                return Status::EndOfStream;
            }

            if (this->m_CurrentAsyncReadBuffer == this->m_SerializeBuffer)
            {
                if (!this->WaitForAsyncRead())
                {
                    return Status::ReadFault;
                }

                this->StartStreamBufferRead();
            }

            while (!buffer.empty())
            {
                int64_t requested = std::min<int64_t>({ static_cast<int64_t>(buffer.size()),
                    static_cast<int64_t>(DefaultBufferSize - m_SerializePosition),
                    static_cast<int64_t>(m_Size - m_Position) });

                GX_ASSERT(requested <= DefaultBufferSize);

                if (requested > 0)
                {
                    size_t to_copy = static_cast<size_t>(requested);

                    std::memcpy(
                        buffer.data(),
                        &m_Buffers[m_SerializeBuffer][m_SerializePosition],
                        to_copy);

                    m_SerializePosition += to_copy;
                    GX_ASSERT(m_SerializePosition <= DefaultBufferSize);

                    m_Position += to_copy;
                    GX_ASSERT(m_Position <= m_Size);

                    processed += to_copy;

                    buffer.remove_prefix(to_copy);

                    GX_ASSERT(m_Position <= m_Size);

                    if (m_Position >= m_Size)
                    {
                        break;
                    }
                }
                else
                {
                    if (!this->WaitForAsyncRead())
                    {
                        return Status::ReadFault;
                    }

                    this->SwapBuffers();
                    this->StartStreamBufferRead();
                }
            }

            if (!buffer.empty())
            {
                return Status::EndOfStream;
            }

            return Status::Success;
        }

        virtual Status Write(
            [[maybe_unused]] std::span<const std::byte> buffer,
            [[maybe_unused]] size_t& processed) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            processed = 0;

            GX_ASSERT_NOT_IMPLEMENTED();
            return Status::NotImplemented;
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
            SeekOrigin origin) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());

            switch (origin)
            {
                case SeekOrigin::Begin:
                {
                    return this->SetPosition(value);
                }

                case SeekOrigin::Current:
                {
                    return this->SetPosition(this->m_Position + value);
                }

                case SeekOrigin::End:
                {
                    return this->SetPosition(m_Size - value);
                }
            }

            GX_ASSERT(false);
            return Status::InvalidArgument;
        }

        virtual Status SetPosition(
            int64_t value) noexcept final override
        {
            GX_ASSERT(this->IsValidHandle());
            GX_ASSERT(value >= 0);
            GX_ASSERT(value <= m_Size);

            int64_t delta = value - m_Position;

            if (delta == 0)
            {
                return Status::Success;
            }

            if (!this->WaitForAsyncRead())
            {
                return Status::Failure;
            }

            m_Position = value;

            bool in_range = ((delta < 0) && ((static_cast<int64_t>(m_SerializePosition) - std::abs(delta)) >= 0))
                            || ((delta > 0) && ((delta + m_SerializePosition) < DefaultBufferSize));

            if (in_range)
            {
                m_SerializePosition += static_cast<size_t>(delta);
            }
            else
            {
                GX_ASSERT(value >= 0);

                m_IsEOF         = true;
                m_AsyncPosition = static_cast<uint64_t>(value);
                UpdateAsync();
                m_CurrentAsyncReadBuffer = m_SerializeBuffer;
                m_SerializePosition      = 0;
                StartSerializeBufferRead();
            }

            return Status::Success;
        }
    };
}
