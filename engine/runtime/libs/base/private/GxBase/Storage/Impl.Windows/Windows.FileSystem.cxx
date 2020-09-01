#include <GxBase/Storage/IFileSystem.hxx>
//#include <GxBase/ByteAccess.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System/Impl.Windows/Windows.Types.hxx>
#include <GxBase/System.hxx>
#include "Windows.AsyncFileStream.hxx"
#include "Windows.FileStream.hxx"
#include "Windows.FileSystem.hxx"

namespace Graphyte::Storage
{
    IFileSystem& IFileSystem::GetPlatformNative() noexcept
    {
        static WindowsFileSystem s_Instance{};
        return s_Instance;
    }

    WindowsFileSystem::~WindowsFileSystem() noexcept = default;

    Status WindowsFileSystem::OpenRead(
        std::unique_ptr<IStream>& result,
        std::string_view path,
        bool share_write) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        DWORD dwAccess = static_cast<DWORD>(GENERIC_READ);
        DWORD dwShare  = static_cast<DWORD>(FILE_SHARE_READ | (share_write ? FILE_SHARE_WRITE : 0));
        DWORD dwCreate = static_cast<DWORD>(OPEN_EXISTING);

        HANDLE handle = CreateFileW(
            wpath.data(),
            dwAccess,
            dwShare,
            nullptr,
            dwCreate,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);

        if (handle != INVALID_HANDLE_VALUE)
        {
            result = std::make_unique<WindowsAsyncFileStream>(handle);
            return Status::Success;
        }

        result = nullptr;

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::OpenWrite(
        std::unique_ptr<IStream>& result,
        std::string_view path,
        bool append,
        bool share_read) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        DWORD dwAccess = static_cast<DWORD>(GENERIC_WRITE);
        DWORD dwShare  = static_cast<DWORD>(share_read ? FILE_SHARE_READ : 0);
        DWORD dwCreate = static_cast<DWORD>(append ? OPEN_ALWAYS : CREATE_ALWAYS);

        HANDLE handle = CreateFileW(
            wpath.data(),
            dwAccess,
            dwShare,
            nullptr,
            dwCreate,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);

        if (handle != INVALID_HANDLE_VALUE)
        {
            result = std::make_unique<WindowsFileStream>(handle);
            return Status::Success;
        }

        result = nullptr;
        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::IsReadonly(
        bool& result,
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        DWORD dwFileAttributes = GetFileAttributesW(wpath.data());

        if (dwFileAttributes != INVALID_FILE_ATTRIBUTES)
        {
            result = ((dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0);
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::SetReadonly(
        std::string_view path,
        bool value) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        DWORD dwFileAttributes = static_cast<DWORD>(value ? FILE_ATTRIBUTE_READONLY : FILE_ATTRIBUTE_NORMAL);

        if (SetFileAttributesW(wpath.data(), dwFileAttributes) != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::GetFileInfo(
        FileInfo& result,
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        WIN32_FILE_ATTRIBUTE_DATA wfad{};

        if (GetFileAttributesExW(wpath.data(), GetFileExInfoStandard, &wfad))
        {
            ULARGE_INTEGER li_file_size{};
            li_file_size.LowPart  = wfad.nFileSizeLow;
            li_file_size.HighPart = wfad.nFileSizeHigh;

            result.CreationTime     = System::TypeConverter<FILETIME>::ConvertDateTime(wfad.ftCreationTime);
            result.AccessTime       = System::TypeConverter<FILETIME>::ConvertDateTime(wfad.ftLastAccessTime);
            result.ModificationTime = System::TypeConverter<FILETIME>::ConvertDateTime(wfad.ftLastWriteTime);
            result.FileSize         = System::TypeConverter<ULARGE_INTEGER>::ConvertInt64(li_file_size);
            result.IsDirectory      = (wfad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
            result.IsReadonly       = (wfad.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0;
            result.IsValid          = true;
            return Status::Success;
        }

        result = {};
        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::GetFileSize(
        int64_t& result,
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        WIN32_FILE_ATTRIBUTE_DATA wfad{};

        if (GetFileAttributesExW(wpath.data(), GetFileExInfoStandard, &wfad))
        {
            ULARGE_INTEGER li_file_size{};
            li_file_size.LowPart  = wfad.nFileSizeLow;
            li_file_size.HighPart = wfad.nFileSizeHigh;

            result = System::TypeConverter<ULARGE_INTEGER>::ConvertInt64(li_file_size);
            return Status::Success;
        }

        result = -1;
        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::Exists(
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        DWORD dwFileAttributes = GetFileAttributesW(wpath.data());
        DWORD dwLastError      = GetLastError();

        if (dwFileAttributes != INVALID_FILE_ATTRIBUTES)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError(dwLastError);
    }

    Status WindowsFileSystem::FileCopy(
        std::string_view destination,
        std::string_view source) noexcept
    {
        System::Impl::WindowsPath wdestination{};
        System::Impl::WidenStringPath(wdestination, destination);
        System::Impl::WindowsPath wsource{};
        System::Impl::WidenStringPath(wsource, source);

        if (CopyFileW(wsource.data(), wdestination.data(), TRUE) != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::FileMove(
        std::string_view destination,
        std::string_view source) noexcept
    {
        System::Impl::WindowsPath wdestination{};
        System::Impl::WidenStringPath(wdestination, destination);
        System::Impl::WindowsPath wsource{};
        System::Impl::WidenStringPath(wsource, source);

        if (MoveFileW(wsource.data(), wdestination.data()) != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::FileDelete(
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        if (DeleteFileW(wpath.data()) != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::DirectoryCreate(
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        BOOL created      = CreateDirectoryW(wpath.data(), nullptr);
        DWORD dwLastError = GetLastError();

        if (created != FALSE || dwLastError == ERROR_ALREADY_EXISTS)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError(dwLastError);
    }

    Status WindowsFileSystem::DirectoryDelete(
        std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, path);

        if (RemoveDirectoryW(wpath.data()) != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    Status WindowsFileSystem::Enumerate(
        std::string_view path,
        IDirectoryVisitor& visitor) noexcept
    {
        std::string const wildcard = Storage::CombinePath(path, "*.*");

        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, wildcard);

        WIN32_FIND_DATAW wfd{};

        HANDLE hFindFile = FindFirstFileW(wpath.data(), &wfd);

        if (hFindFile != INVALID_HANDLE_VALUE)
        {
            Status status{};

            do
            {
                std::wstring_view filename{ wfd.cFileName };

                if (filename != L"." && filename != L"..")
                {
                    std::string const report_path = Storage::CombinePath(path, System::Impl::NarrowString(filename));
                    bool const is_directory       = !!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

                    status = visitor.Visit(report_path, is_directory);
                }
            } while (status == Status::Success && FindNextFileW(hFindFile, &wfd) != FALSE);

            FindClose(hFindFile);

            return status;
        }

        return Status::Failure;
    }

    Status WindowsFileSystem::Enumerate(
        std::string_view path,
        IDirectoryInfoVisitor& visitor) noexcept
    {
        std::string const wildcard = Storage::CombinePath(path, "*.*");

        System::Impl::WindowsPath wpath{};
        System::Impl::WidenStringPath(wpath, wildcard);

        WIN32_FIND_DATAW wfd{};

        HANDLE hFindFile = FindFirstFileW(wpath.data(), &wfd);

        if (hFindFile != INVALID_HANDLE_VALUE)
        {
            Status status{};

            do
            {
                std::wstring_view filename{ wfd.cFileName };

                if (filename != L"." && filename != L"..")
                {
                    std::string const report_path = Storage::CombinePath(path, System::Impl::NarrowString(filename));

                    ULARGE_INTEGER li_file_size{};
                    li_file_size.LowPart  = wfd.nFileSizeLow;
                    li_file_size.HighPart = wfd.nFileSizeHigh;

                    FileInfo file_info{
                        .CreationTime     = System::TypeConverter<FILETIME>::ConvertDateTime(wfd.ftCreationTime),
                        .AccessTime       = System::TypeConverter<FILETIME>::ConvertDateTime(wfd.ftLastAccessTime),
                        .ModificationTime = System::TypeConverter<FILETIME>::ConvertDateTime(wfd.ftLastWriteTime),
                        .FileSize         = System::TypeConverter<ULARGE_INTEGER>::ConvertInt64(li_file_size),
                        .IsDirectory      = (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0,
                        .IsReadonly       = (wfd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0,
                        .IsValid          = true,
                    };

                    status = visitor.Visit(report_path, file_info);
                }
            } while (status == Status::Success && FindNextFileW(hFindFile, &wfd) != FALSE);

            FindClose(hFindFile);

            return status;
        }

        return Status::Failure;
    }
}
