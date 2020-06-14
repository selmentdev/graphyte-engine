#pragma once
#include <GxBase/Storage/Archive.hxx>

namespace Graphyte::Storage
{
    class BASE_API ArchiveMemoryWriter final : public Archive
    {
    private:
        static constexpr const size_t BufferSize = 4 * 4096;

    private:
        int64_t m_Offset;
        std::vector<std::byte>& m_Buffer;

    public:
        ArchiveMemoryWriter(
            std::vector<std::byte>& buffer,
            bool persistent = false) noexcept;

        virtual ~ArchiveMemoryWriter() noexcept;

    public:
        virtual void Serialize(
            void* buffer,
            size_t size) noexcept override;

        virtual int64_t GetPosition() noexcept override;

        virtual int64_t GetSize() noexcept override;

        virtual void SetPosition(
            int64_t position) noexcept override;
    };
}
