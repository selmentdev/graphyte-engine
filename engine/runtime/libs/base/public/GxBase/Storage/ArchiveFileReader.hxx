#pragma once
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Storage/IStream.hxx>

namespace Graphyte::Storage
{
    class BASE_API ArchiveFileReader : public Archive
    {
    private:
        static constexpr const size_t BufferSize = 4 * 4096;

    private:
        std::unique_ptr<IStream> m_Stream;
        int64_t m_Position;
        int64_t m_Size;
        int64_t m_BufferBase;
        size_t m_BufferCount;
        std::array<std::byte, BufferSize> m_Buffer;

    public:
        ArchiveFileReader(
            std::unique_ptr<IStream> stream
        ) noexcept;

        virtual ~ArchiveFileReader() noexcept;

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

    private:
        bool PrecacheImpl(
            int64_t offset,
            int64_t size
        ) noexcept;
    };
}
