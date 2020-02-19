#include <Graphyte/Storage/FileManager.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/Application.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Storage/ArchiveFileReader.hxx>
#include <Graphyte/Storage/ArchiveFileWriter.hxx>

namespace Graphyte::Storage
{
    std::string FileManager::GetRootDirectory() noexcept
    {
        static std::string result{};

        if (result.empty())
        {
            result = System::GetBaseDirectory();
            Storage::Path::Append(result, "../../../");
            Storage::Path::Canonicalize(result);
        }

        return result;
    }

    std::string FileManager::GetLaunchDirectory() noexcept
    {
        return System::GetBaseDirectory();
    }

    std::string FileManager::GetEngineDirectory() noexcept
    {
        return "../../../engine/";
    }

    std::string FileManager::GetEngineContentDirectory() noexcept
    {
        return GetEngineDirectory() + "content/";
    }

    std::string FileManager::GetEngineConfigDirectory() noexcept
    {
        return GetEngineDirectory() + "config/";
    }

    std::string FileManager::GetEngineSourceDirectory() noexcept
    {
        return GetEngineDirectory() + "source/";
    }

    std::string FileManager::GetEngineUserDirectory() noexcept
    {
        // TODO: Fix this.

        //if (System::Application::IsInstalled())
        //{
        //    return System::GetUserSettingsDirectory();
        //}
        //else
        //{
            return GetEngineDirectory();
        //}
    }

    std::string FileManager::GetEngineIntermediateDirectory() noexcept
    {
        return GetEngineDirectory() + "intermediate/";
    }

    std::string FileManager::GetEngineSavedDirectory() noexcept
    {
        return GetEngineUserDirectory() + "saved/";
    }

    std::string FileManager::GetProjectDirectory() noexcept
    {
        static std::string result{};
        if (result.empty())
        {
            Storage::Path::Append(result, "../../../game/");
        }

        return result;
    }

    std::string FileManager::GetProjectContentDirectory() noexcept
    {
        return GetProjectDirectory() + "content/";
    }

    std::string FileManager::GetProjectConfigDirectory() noexcept
    {
        return GetProjectDirectory() + "config/";
    }

    std::string FileManager::GetProjectSourceDirectory() noexcept
    {
        return GetProjectDirectory() + "source/";
    }

    std::string FileManager::GetProjectUserDirectory() noexcept
    {
        // TODO: Fix this

        //if (System::Application::IsInstalled())
        //{
        //    return System::GetUserSettingsDirectory();
        //}
        //else
        //{
            return GetProjectDirectory();
        //}
    }

    std::string FileManager::GetProjectIntermediateDirectory() noexcept
    {
        return GetProjectDirectory() + "intermediate/";
    }

    std::string FileManager::GetProjectSavedDirectory() noexcept
    {
        return GetProjectUserDirectory() + "saved/";
    }

    std::string FileManager::GetScreenshotsDirectory() noexcept
    {
        return GetProjectUserDirectory() + "screenshots/";
    }

    std::string FileManager::GetCacheDirectory() noexcept
    {
        return GetProjectUserDirectory() + "cache/";
    }

    std::string FileManager::GetLogsDirectory() noexcept
    {
        return GetProjectUserDirectory() + "logs/";
    }

    std::string FileManager::GetCrashdumpDirectory() noexcept
    {
        return GetProjectUserDirectory() + "crashdump/";
    }

    std::string FileManager::GetDeveloperDirectory() noexcept
    {
        return GetProjectUserDirectory() + "developer/";
    }

    std::string FileManager::GetBugReportDirectory() noexcept
    {
        return GetProjectUserDirectory() + "bugreport/";
    }

    std::string FileManager::GetProfilingDirectory() noexcept
    {
        return GetProjectUserDirectory() + "profiling/";
    }

    std::string FileManager::GetUserSettingsDirectory() noexcept
    {
        std::string result = System::GetUserSettingsDirectory();

        Storage::Path::Normalize(result);
        Storage::Path::Append(result, Application::GetDescriptor().Company);
        Storage::Path::Append(result, Application::GetDescriptor().Name);
        Storage::Path::AddDirectorySeparator(result);

        return result;
    }

    std::string FileManager::GetApplicationCommonDataDirectory() noexcept
    {
        std::string result = System::GetApplicationCommonDataDirectory();

        Storage::Path::Normalize(result);
        Storage::Path::Append(result, Application::GetDescriptor().Company);
        Storage::Path::Append(result, Application::GetDescriptor().Name);
        Storage::Path::AddDirectorySeparator(result);

        return result;
    }

    Status FileManager::OpenRead(
        std::unique_ptr<IStream>& result,
        const std::string& path,
        bool share
    ) noexcept
    {
        return IFileSystem::GetPlatformNative().OpenRead(
            result,
            path,
            share
        );
    }
    
    Status FileManager::OpenWrite(
        std::unique_ptr<IStream>& result,
        const std::string& path,
        bool append,
        bool share
    ) noexcept
    {
        return IFileSystem::GetPlatformNative().OpenWrite(
            result,
            path,
            append,
            share
        );
    }

    Status FileManager::CreateReader(
        std::unique_ptr<Archive>& archive,
        const std::string& path,
        bool share
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        auto const status = IFileSystem::GetPlatformNative().OpenRead(
            handle,
            path,
            share
        );

        if (status == Status::Success && handle != nullptr)
        {
            archive = std::make_unique<ArchiveFileReader>(std::move(handle));
            return Status::Success;
        }

        return status;
    }

    Status FileManager::CreateWriter(
        std::unique_ptr<Archive>& archive,
        const std::string& path,
        bool append,
        bool share
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        auto const status = IFileSystem::GetPlatformNative().OpenWrite(
            handle,
            path,
            append,
            share
        );

        if (status == Status::Success && handle != nullptr)
        {
            archive = std::make_unique<ArchiveFileWriter>(std::move(handle));
            return Status::Success;
        }

        return status;
    }

    Status FileManager::ReadText(
        std::string& content,
        const std::string& path
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        Status status = IFileSystem::GetPlatformNative().OpenRead(
            handle,
            path
        );

        if (status == Status::Success && handle != nullptr)
        {
            int64_t size = handle->GetSize();

            if (size < 0)
            {
                return Status::InvalidFile;
            }

            if (static_cast<uint64_t>(size) != static_cast<uint64_t>(static_cast<size_t>(size)))
            {
                return Status::NotEnoughMemory;
            }

            content.resize(static_cast<size_t>(size));

            size_t processed{};
            return handle->Read({ reinterpret_cast<std::byte*>(content.data()), content.size() }, processed);
        }

        return Status::InvalidPath;
    }

    Status FileManager::WriteText(
        std::string_view content,
        const std::string& path
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        Status status = IFileSystem::GetPlatformNative().OpenWrite(
            handle,
            path
        );

        if (status == Status::Success && handle != nullptr)
        {
            size_t processed{};
            return handle->Write({ reinterpret_cast<const std::byte*>(content.data()), content.size() }, processed);
        }

        return Status::InvalidPath;
    }

    Status FileManager::ReadBinary(
        std::vector<std::byte>& content,
        const std::string& path
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        Status status = IFileSystem::GetPlatformNative().OpenRead(
            handle,
            path
        );

        if (status == Status::Success && handle != nullptr)
        {
            int64_t size = handle->GetSize();

            if (size < 0)
            {
                return Status::InvalidFile;
            }

            if (static_cast<uint64_t>(size) != static_cast<uint64_t>(static_cast<size_t>(size)))
            {
                return Status::NotEnoughMemory;
            }

            content.resize(static_cast<size_t>(size));

            size_t processed{};

            return handle->Read({ content.data(), content.size() }, processed);
        }

        return Status::InvalidPath;
    }

    Status FileManager::WriteBinary(
        const std::vector<std::byte>& content,
        const std::string& path
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        Status status = IFileSystem::GetPlatformNative().OpenWrite(
            handle,
            path
        );

        if (status == Status::Success && handle != nullptr)
        {
            size_t processed{};

            return handle->Write({ content.data(), content.size() }, processed);
        }

        return Status::InvalidPath;
    }

    Status FileManager::ReadBinary(
        std::unique_ptr<std::byte[]>& contents,
        size_t& size,
        const std::string& path
    ) noexcept
    {
        size = 0;
        std::unique_ptr<IStream> handle{};

        Status status = IFileSystem::GetPlatformNative().OpenRead(
            handle,
            path
        );

        if (status == Status::Success && handle != nullptr)
        {
            int64_t file_size = handle->GetSize();

            if (file_size < 0)
            {
                return Status::InvalidFile;
            }

            if (static_cast<uint64_t>(file_size) != static_cast<uint64_t>(static_cast<size_t>(file_size)))
            {
                return Status::NotEnoughMemory;
            }

            size = static_cast<size_t>(file_size);

            contents = std::make_unique<std::byte[]>(size);

            size_t processed{};

            return handle->Read({ contents.get(), size }, processed);
        }

        return Status::InvalidPath;
    }

    Status FileManager::WriteBinary(
        const std::unique_ptr<std::byte[]>& contents,
        size_t size,
        const std::string& path
    ) noexcept
    {
        std::unique_ptr<IStream> handle{};

        Status status = IFileSystem::GetPlatformNative().OpenWrite(
            handle,
            path
        );

        if (status == Status::Success && handle != nullptr)
        {
            size_t processed{};

            return handle->Write({ contents.get(), size }, processed);
        }

        return Status::InvalidPath;
    }
}
