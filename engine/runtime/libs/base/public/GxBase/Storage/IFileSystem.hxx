#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/DateTime.hxx>
#include <GxBase/Storage/IStream.hxx>
#include <GxBase/Status.hxx>

namespace Graphyte::Storage
{
    //! \brief Represents file informations.
    struct FileInfo final
    {
        DateTime CreationTime;
        DateTime AccessTime;
        DateTime ModificationTime;
        int64_t FileSize;
        bool IsDirectory;
        bool IsReadonly;
        bool IsValid;
    };

    //! \brief Provides base interface for directory visitor.
    struct IDirectoryVisitor
    {
    public:
        //! \brief This method is invoked for each matching file or directory.
        //!
        //! \param path         Provides path to file or directory.
        //! \param is_directory Specifies whether path points to directory.
        //!
        //! \return The status code.
        //!
        //! \todo Change \p is_directory to file type enum.
        virtual Status Visit(
            const std::string& path,
            bool is_directory) noexcept = 0;
    };

    //! \brief Provides base interface for directory visitor with full file info.
    struct IDirectoryInfoVisitor
    {
    public:
        //! \brief This method is invoked for each matching file or directory.
        //!
        //! \param path Provides path to file or directory.
        //! \param info Provides file information.
        //!
        //! \return The status code.
        //!
        //! \todo Change \p is_directory to file type enum.
        virtual Status Visit(
            const std::string& path,
            const FileInfo& info) noexcept = 0;
    };

    //! \brief Provides interface for file system acccess.
    //!
    //! \note These APIs should use return status code instead of bool. Sometimes it's unclear
    //! whether property status is \c false or function failed.
    struct BASE_API IFileSystem
    {
    public:
        IFileSystem() noexcept;
        virtual ~IFileSystem() noexcept;

    public:
        //! \brief Gets native file system object.
        static IFileSystem& GetPlatformNative() noexcept;

    public:
        //! \brief Opens file for read.
        //!
        //! \param path  Provides file path to open.
        //! \param share Provides value indicating whether file may be shared.
        //!
        //! \return The status code.
        virtual Status OpenRead(
            std::unique_ptr<IStream>& result,
            const std::string& path,
            bool share = false) noexcept = 0;

        //! \brief Opens file for write.
        //!
        //! \param path   Provides file path to open.
        //! \param append Provides value indicating whether file is opened for appending.
        //! \param share  Provides value indicating whether file may be shared.
        //!
        //! \return The status code.
        virtual Status OpenWrite(
            std::unique_ptr<IStream>& result,
            const std::string& path,
            bool append = false,
            bool share  = false) noexcept = 0;

    public:
        //! \brief Checks whether specified file is marked as read only.
        //!
        //! \param path Provides file path.
        //!
        //! \return The status code.
        virtual Status IsReadonly(
            bool& result,
            const std::string& path) noexcept = 0;

        //! \brief Sets file read only flag.
        //!
        //! \param path  Provides file path.
        //! \param value Provides new flag value.
        //!
        //! \return The status code.
        virtual Status SetReadonly(
            const std::string& path,
            bool value) noexcept = 0;

        //! \brief Gets file info for specified path.
        //!
        //! \param result Returns file information.
        //! \param path   Provides file path.
        //!
        //! \return The status code.
        virtual Status GetFileInfo(
            FileInfo& result,
            const std::string& path) noexcept = 0;

        //! \brief Gets file size.
        //!
        //! \param result Returns file size.
        //! \param path   Provides file path.
        //!
        //! \return The status code.
        virtual Status GetFileSize(
            int64_t& result,
            const std::string& path) noexcept = 0;

        //! \brief Determines whether file at specified path exists.
        //!
        //! \param path Provides path to file.
        //!
        //! \return The status code.
        virtual Status Exists(
            const std::string& path) noexcept = 0;

    public:
        //! \brief Copies file contents from source path to destination path.
        //!
        //! \param destination Provides path to destination file.
        //! \param source      Provides path to source file.
        //!
        //! \return The status code.
        virtual Status FileCopy(
            const std::string& destination,
            const std::string& source) noexcept;

        //! \brief Moves file from source to destination.
        //!
        //! \param destination Provides path to destination file.
        //! \param source      Provides path to source file.
        //!
        //! \return The status code.
        virtual Status FileMove(
            const std::string& destination,
            const std::string& source) noexcept = 0;

        //! \brief Deletes file at specified path.
        //!
        //! \param path Provides path to file.
        //!
        //! \return  The status code.
        virtual Status FileDelete(
            const std::string& path) noexcept = 0;

    public:
        //! \brief Creates directory at specified path.
        //!
        //! \param path Provides path to directory.
        //!
        //! \return \c true when successful, \c false otherwise.
        virtual Status DirectoryCreate(
            const std::string& path) noexcept = 0;

        //! \brief Deletes directory at specified path.
        //!
        //! \param path Provides path to directory.
        //!
        //! \return The status code.
        virtual Status DirectoryDelete(
            const std::string& path) noexcept = 0;

    public:
        //! \brief Enumerates contents of directory at specified path.
        //!
        //! \param path    Provides path to directory to enumerate.
        //! \param visitor Provides object which will be notified about directory contents.
        //!
        //! \return The status code.
        virtual Status Enumerate(
            const std::string& path,
            IDirectoryVisitor& visitor) noexcept = 0;

        //! \brief Enumerates contents of directory at specified path.
        //!
        //! \param path    Provides path to directory to enumerate.
        //! \param visitor Provides object which will be notified about directory contents.
        //!
        //! \return The status code.
        virtual Status Enumerate(
            const std::string& path,
            IDirectoryInfoVisitor& visitor) noexcept = 0;

    public:
        //! \brief Enumerates contents of directory at specified path recursively.
        //!
        //! \param path    Provides path to directory to enumerate.
        //! \param visitor Provides object which will be notified about directory contents.
        //!
        //! \return The status code.
        virtual Status EnumerateRecursive(
            const std::string& path,
            IDirectoryVisitor& visitor) noexcept;

        //! \brief Enumerates contents of directory at specified path recursively.
        //!
        //! \param path    Provides path to directory to enumerate.
        //! \param visitor Provides object which will be notified about directory contents.
        //!
        //! \return The status code.
        virtual Status EnumerateRecursive(
            const std::string& path,
            IDirectoryInfoVisitor& visitor) noexcept;

    public:
        //! \brief Creates directory tree for specified path.
        //!
        //! \param path Provides path to directory tree to create.
        //!
        //! \return The status code.
        virtual Status DirectoryTreeCreate(
            const std::string& path) noexcept;

        //! \brief Deletes directory tree recursively for specified path.
        //!
        //! \param path Provides path to directory tree to delete.
        //!
        //! \return The status code.
        virtual Status DirectoryTreeDelete(
            const std::string& path) noexcept;

        //! \brief Copies directory tree recursively.
        //!
        //! \param destination Provides path to destination directory.
        //! \param source      Provides path to source directory.
        //! \param overwrite   Specifies whether content of destination directory should be
        //!                    overwritten.
        //!
        //! \return The status code.
        virtual Status DirectoryTreeCopy(
            const std::string& destination,
            const std::string& source,
            bool overwrite) noexcept;

    public:
        //! \brief Finds files at specified path, matching provided extension.
        //!
        //! \param result    Returns list of matching files.
        //! \param path      Provides path to directory.
        //! \param extension Provides extension to search for.
        //!
        //! \return \c true when successful, \c false otherwise.
        virtual Status FindFiles(
            std::vector<std::string>& result,
            const std::string& path,
            std::string_view extension) noexcept;

        //! \brief Finds files recursively at specified path, matching provided extension.
        //!
        //! \param result    Returns list of matching files.
        //! \param path      Provides path to directory.
        //! \param extension Provides extension to search for.
        //!
        //! \return \c true when successful, \c false otherwise.
        virtual Status FindFilesRecursive(
            std::vector<std::string>& result,
            const std::string& path,
            std::string_view extension) noexcept;
    };
}
