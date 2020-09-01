#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Storage/IFileSystem.hxx>

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
            std::string_view path,
            bool share = false) noexcept override;

        virtual Status OpenWrite(
            std::unique_ptr<IStream>& result,
            std::string_view path,
            bool append = false,
            bool share  = false) noexcept override;

    public:
        virtual Status IsReadonly(
            bool& result,
            std::string_view path) noexcept override;

        virtual Status SetReadonly(
            std::string_view path,
            bool value) noexcept override;

        virtual Status GetFileInfo(
            FileInfo& result,
            std::string_view path) noexcept override;

        virtual Status GetFileSize(
            int64_t& result,
            std::string_view path) noexcept override;

        virtual Status Exists(
            std::string_view path) noexcept override;

    public:
        virtual Status FileCopy(
            std::string_view destination,
            std::string_view source) noexcept override;

        virtual Status FileMove(
            std::string_view destination,
            std::string_view source) noexcept override;

        virtual Status FileDelete(
            std::string_view path) noexcept override;

    public:
        virtual Status DirectoryCreate(
            std::string_view path) noexcept override;

        virtual Status DirectoryDelete(
            std::string_view path) noexcept override;

    public:
        virtual Status Enumerate(
            std::string_view path,
            IDirectoryVisitor& visitor) noexcept override;

        virtual Status Enumerate(
            std::string_view path,
            IDirectoryInfoVisitor& visitor) noexcept override;
    };
}
