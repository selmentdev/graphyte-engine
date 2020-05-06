#pragma once
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Storage/IStream.hxx>

namespace Graphyte::Storage
{
    class BASE_API ArchiveFileWriter : public Archive
    {
    private:
        static constexpr const size_t BufferSize = 1 * 4096;
        std::unique_ptr<IStream> m_Stream;
        int64_t m_Position;
        size_t m_BufferCount;
        std::array<std::byte, BufferSize> m_Buffer;

    public:
        ArchiveFileWriter(
            std::unique_ptr<IStream> stream,
            int64_t position = 0
        ) noexcept;

        virtual ~ArchiveFileWriter() noexcept;

    public:
        virtual void Serialize(
            void* buffer,
            size_t size
        ) noexcept override;

        virtual int64_t GetPosition() noexcept override;

        virtual int64_t GetSize() noexcept override;

        virtual void SetPosition(
            int64_t position
        ) noexcept override;

        virtual void Flush() noexcept override;
    };
}
