#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>

namespace Graphyte::Storage
{
    struct BASE_API WindowsFileSystem final
        : public IFileSystem
    {
    public:
        virtual ~WindowsFileSystem() noexcept;

    public:
        virtual Status OpenRead(
            std::unique_ptr<IStream>& result,
            const std::string& path,
            bool share = false
        ) noexcept override;

        virtual Status OpenWrite(
            std::unique_ptr<IStream>& result,
            const std::string& path,
            bool append = false,
            bool share = false
        ) noexcept override;

    public:
        virtual Status IsReadonly(
            bool& result,
            const std::string& path
        ) noexcept override;

        virtual Status SetReadonly(
            const std::string& path,
            bool value
        ) noexcept override;

        virtual Status GetFileInfo(
            FileInfo& result,
            const std::string& path
        ) noexcept override;

        virtual Status GetFileSize(
            int64_t& result,
            const std::string& path
        ) noexcept override;

        virtual Status Exists(
            const std::string& path
        ) noexcept override;

    public:
        virtual Status FileCopy(
            const std::string& destination,
            const std::string& source
        ) noexcept override;

        virtual Status FileMove(
            const std::string& destination,
            const std::string& source
        ) noexcept override;

        virtual Status FileDelete(
            const std::string& path
        ) noexcept override;

    public:
        virtual Status DirectoryCreate(
            const std::string& path
        ) noexcept override;

        virtual Status DirectoryDelete(
            const std::string& path
        ) noexcept override;

    public:
        virtual Status Enumerate(
            const std::string& path,
            IDirectoryVisitor& visitor
        ) noexcept override;

        virtual Status Enumerate(
            const std::string& path,
            IDirectoryInfoVisitor& visitor
        ) noexcept override;
    };
}
