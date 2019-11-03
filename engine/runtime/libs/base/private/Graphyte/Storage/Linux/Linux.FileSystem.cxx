#include "Base.pch.hxx"
#include <Graphyte/Platform/Impl.Posix/Posix.Types.hxx>
#include <Graphyte/ByteAccess.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Storage/Path.hxx>
#include "Linux.FileSystem.hxx"
#include "Linux.FileStream.hxx"

#include <sys/file.h>
#include <sys/types.h>
#include <dirent.h>

namespace Graphyte::Storage
{
    IFileSystem& IFileSystem::GetPlatformNative() noexcept
    {
        static LinuxFileSystem s_Instance{};
        return s_Instance;
    }

    LinuxFileSystem::~LinuxFileSystem() noexcept = default;
    
    Status LinuxFileSystem::OpenRead(
        std::unique_ptr<IStream>& result,
        const std::string& path,
        bool share_write
    ) noexcept
    {
        int flags = O_CLOEXEC;
        if (share_write)
        {
            flags |= O_RDWR;
        }
        else
        {
            flags |= O_RDONLY;
        }

        int32_t handle = open(path.c_str(), flags);
        if (handle != -1)
        {
            result = std::make_unique<LinuxFileStream>(handle, path.c_str(), false);
            return Status::Success;
        }
        
        result = nullptr;
        return Status::Failure;
    }

    Status LinuxFileSystem::OpenWrite(
        std::unique_ptr<IStream>& result,
        const std::string& path,
        bool append,
        bool share_read
    ) noexcept
    {
        int flags = O_CREAT | O_CLOEXEC;

        if (share_read)
        {
            flags |= O_RDWR;
        }
        else
        {
            flags |= O_WRONLY;
        }

        int32_t handle = open(path.c_str(), flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (handle != -1)
        {
            if (flock(handle, LOCK_EX | LOCK_NB) == -1)
            {
                bool failed{ false };
                
                if (EAGAIN == errno)
                {
                    failed = true;
                }

                if (EWOULDBLOCK == errno)
                {
                    failed = true;
                }

                if (failed)
                {
                    close(handle);
                    return Status::Failure;
                }
            }

            if (!append)
            {
                if (ftruncate(handle, 0) != 0)
                {
                    //auto error = errno;
                    close(handle);
                    return Status::Failure;
                }
            }

            result = std::make_unique<LinuxFileStream>(handle, path.c_str(), true);
            
            if (append)
            {
                return result->SetPosition(0, SeekOrigin::End);
            }

            return Status::Success;
        }

        return Status::Failure;
    }

    Status LinuxFileSystem::IsReadonly(
        bool& result,
        const std::string& path
    ) noexcept
    {
        bool failed = access(path.c_str(), W_OK) == -1;
        error_t error = errno;
        
        if (failed)
        {
            if (error == EACCES)
            {
                //
                // Failed to access file with write.
                //
                
                result = false;
                return Status::Success;
            }
            
            //
            // Failed due to different reasons.
            //
            
            result = false;
            return Status::Failure; // XXX: Match errno
        }
        
        //
        // Write access available.
        //
        
        result = true;
        return Status::Success;
    }

    Status LinuxFileSystem::SetReadonly(
        const std::string& path,
        bool value
    ) noexcept
    {
        struct stat fileinfo{};
        if (stat(path.c_str(), &fileinfo) == 0)
        {
            if (value)
            {
                fileinfo.st_mode &= ~static_cast<uint32_t>(S_IWUSR);
            }
            else
            {
                fileinfo.st_mode |= S_IWUSR;
            }

            if (chmod(path.c_str(), fileinfo.st_mode) == 0)
            {
                return Status::Success;
            }
        }

        return Status::Failure; // XXX: Match
    }

    Status LinuxFileSystem::GetFileInfo(
        FileInfo& result,
        const std::string& path
    ) noexcept
    {
        struct stat fileinfo{};
        if (stat(path.c_str(), &fileinfo) == -1)
        {
            result.CreationTime = Platform::DateTime::FromUnixTimestamp(fileinfo.st_ctime);
            result.AccessTime = Platform::DateTime::FromUnixTimestamp(fileinfo.st_atime);
            result.ModificationTime = Platform::DateTime::FromUnixTimestamp(fileinfo.st_mtime);
            result.FileSize = static_cast<int64_t>(fileinfo.st_size);
            result.IsDirectory = S_ISDIR(fileinfo.st_mode);
            result.IsValid = true;
            return IsReadonly(result.IsReadonly, path);
        }

        return Status::Failure;
    }

    Status LinuxFileSystem::GetFileSize(
        int64_t& result,
        const std::string& path
    ) noexcept
    {
        struct stat fileinfo{};
        fileinfo.st_size = -1;
        
        if (stat(path.c_str(), &fileinfo) != -1)
        {
            if (S_ISDIR(fileinfo.st_mode))
            {
                fileinfo.st_size = -1;
            }

            result = fileinfo.st_size;
            return Status::Success;
        }

        return Status::Failure;
    }

    Status LinuxFileSystem::FileMove(
        const std::string& destination,
        const std::string& source
    ) noexcept
    {
        int const result = rename(source.c_str(), destination.c_str());
        if (result == -1 && errno == EXDEV)
        {
            Status const status = FileCopy(destination, source);
            
            if (status == Status::Success)
            {
                return FileDelete(source);
            }
            
            return status;
        }

        return result != -1 ? Status::Success : Status::Failure;
    }

    Status LinuxFileSystem::FileDelete(
        const std::string& path
    ) noexcept
    {
        if (unlink(path.c_str()) == 0)
        {
            return Status::Success;
        }
        
        return Status::Failure; // XXX: Map
    }

    Status LinuxFileSystem::Exists(
        const std::string& path
    ) noexcept
    {
        struct stat fileinfo{};
        if (stat(path.c_str(), &fileinfo) != -1)
        {
            return (S_ISREG(fileinfo.st_mode) || S_ISDIR(fileinfo.st_mode))
                ? Status::Success
                : Status::Failure;
        }

        return Status::Failure;
    }

    Status LinuxFileSystem::DirectoryCreate(
        const std::string& path
    ) noexcept
    {
        if (mkdir(path.c_str(), 0755) == 0)
        {
            return Status::Success;
        }

        return Status::Failure; // XXX
    }

    Status LinuxFileSystem::DirectoryDelete(
        const std::string& path
    ) noexcept
    {
        if (rmdir(path.c_str()) == 0)
        {
            return Status::Success;
        }

        return Status::Failure; // XXX
    }

    Status LinuxFileSystem::Enumerate(
        const std::string& path,
        IDirectoryVisitor& visitor
    ) noexcept
    {
        bool result = true;
        DIR* handle = opendir(path.c_str());
        if (handle != nullptr)
        {
            struct dirent* entry{};

            while ((entry = readdir(handle)) != nullptr && result)
            {
                std::string_view filename{ entry->d_name };

                if (filename != "." && filename != "..")
                {
                    std::string const report_path = Path::Combine(path, filename);
                    bool const is_directory = entry->d_type == DT_DIR;
                    
                    result = visitor.Visit(report_path, is_directory) == Status::Success;
                }
            }

            closedir(handle);
        }

        return result ? Status::Success : Status::Failure;
    }

    Status LinuxFileSystem::Enumerate(
        const std::string& path,
        IDirectoryInfoVisitor& visitor
    ) noexcept
    {
        bool result = true;
        DIR* handle = opendir(path.c_str());
        if (handle != nullptr)
        {
            struct dirent* entry{};

            while ((entry = readdir(handle)) != nullptr && result)
            {
                std::string_view filename{ entry->d_name };

                if (filename != "." && filename != "..")
                {
                    std::string const report_path = Path::Combine(path, filename);
                    
                    FileInfo fileinfo{};
                    if (GetFileInfo(fileinfo, report_path) != Status::Success)
                    {
                        GX_ASSERTF(false, "Failed to get file info for {}", path);
                    }

                    result = visitor.Visit(report_path, fileinfo) == Status::Success;
                }
            }

            closedir(handle);
        }

        return result ? Status::Success : Status::Failure;
    }
}
