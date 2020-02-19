#pragma once
#include <Graphyte/Storage/IStream.hxx>

namespace Graphyte::Storage
{
    class BASE_API LinuxFileStream : public IStream
    {
    private:
        std::string m_FileName;
        int64_t m_Offset;
        int64_t m_Size;
        int32_t m_Handle;
        bool m_Writing;

    private:
        static constexpr const size_t BufferSize = SSIZE_MAX;

        __forceinline bool IsValid() const noexcept
        {
            return m_Handle != -1;
        }

        int64_t ReadImpl(notstd::span<std::byte> buffer) noexcept;

    public:
        LinuxFileStream(int32_t handle, const char* name, bool writing) noexcept;
        virtual ~LinuxFileStream() noexcept;

    public:
        virtual Status Flush() noexcept override;
        
        virtual Status Read(
            notstd::span<std::byte> buffer,
            size_t& processed
        ) noexcept override;
        
        virtual Status Write(
            notstd::span<const std::byte> buffer,
            size_t& processed
        ) noexcept override;
        
        virtual int64_t GetSize() noexcept override;
        
        virtual int64_t GetPosition() noexcept override;
        
        virtual Status SetPosition(
            int64_t value,
            SeekOrigin origin
        ) noexcept override;
        
        virtual Status SetPosition(
            int64_t value
        ) noexcept override;
    };
}
