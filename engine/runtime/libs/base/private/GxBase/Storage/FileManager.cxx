#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Application.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/ArchiveFileReader.hxx>
#include <GxBase/Storage/ArchiveFileWriter.hxx>

namespace Graphyte::Storage
{
    std::string GetRootDirectory() noexcept
    {
        static std::string result{};

        if (result.empty())
        {
            result = System::GetBaseDirectory();
            Storage::AppendPath(result, "../../../");
            Storage::CanonicalizePath(result);
        }

        return result;
    }

    std::string GetLaunchDirectory() noexcept
    {
        return System::GetBaseDirectory();
    }

    std::string GetEngineDirectory() noexcept
    {
        return "../../../engine/";
    }

    std::string GetEngineContentDirectory() noexcept
    {
        return GetEngineDirectory() + "content/";
    }

    std::string GetEngineConfigDirectory() noexcept
    {
        return GetEngineDirectory() + "config/";
    }

    std::string GetEngineSourceDirectory() noexcept
    {
        return GetEngineDirectory() + "source/";
    }

    std::string GetEngineUserDirectory() noexcept
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

    std::string GetEngineIntermediateDirectory() noexcept
    {
        return GetEngineDirectory() + "intermediate/";
    }

    std::string GetEngineSavedDirectory() noexcept
    {
        return GetEngineUserDirectory() + "saved/";
    }

    std::string GetProjectDirectory() noexcept
    {
        static std::string result{};
        if (result.empty())
        {
            Storage::AppendPath(result, "../../../game/");
        }

        return result;
    }

    std::string GetProjectContentDirectory() noexcept
    {
        return GetProjectDirectory() + "content/";
    }

    std::string GetProjectConfigDirectory() noexcept
    {
        return GetProjectDirectory() + "config/";
    }

    std::string GetProjectSourceDirectory() noexcept
    {
        return GetProjectDirectory() + "source/";
    }

    std::string GetProjectUserDirectory() noexcept
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

    std::string GetProjectIntermediateDirectory() noexcept
    {
        return GetProjectDirectory() + "intermediate/";
    }

    std::string GetProjectSavedDirectory() noexcept
    {
        return GetProjectUserDirectory() + "saved/";
    }

    std::string GetScreenshotsDirectory() noexcept
    {
        return GetProjectUserDirectory() + "screenshots/";
    }

    std::string GetCacheDirectory() noexcept
    {
        return GetProjectUserDirectory() + "cache/";
    }

    std::string GetLogsDirectory() noexcept
    {
        return GetProjectUserDirectory() + "logs/";
    }

    std::string GetCrashdumpDirectory() noexcept
    {
        return GetProjectUserDirectory() + "crashdump/";
    }

    std::string GetDeveloperDirectory() noexcept
    {
        return GetProjectUserDirectory() + "developer/";
    }

    std::string GetBugReportDirectory() noexcept
    {
        return GetProjectUserDirectory() + "bugreport/";
    }

    std::string GetProfilingDirectory() noexcept
    {
        return GetProjectUserDirectory() + "profiling/";
    }

    std::string GetUserSettingsDirectory() noexcept
    {
        std::string result = System::GetUserSettingsDirectory();

        Storage::NormalizePath(result);
        Storage::AppendPath(result, Application::GetDescriptor().Company);
        Storage::AppendPath(result, Application::GetDescriptor().Name);
        Storage::AddDirectorySeparator(result);

        return result;
    }

    std::string GetApplicationCommonDataDirectory() noexcept
    {
        std::string result = System::GetApplicationCommonDataDirectory();

        Storage::NormalizePath(result);
        Storage::AppendPath(result, Application::GetDescriptor().Company);
        Storage::AppendPath(result, Application::GetDescriptor().Name);
        Storage::AddDirectorySeparator(result);

        return result;
    }

    Status OpenRead(
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
    
    Status OpenWrite(
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

    Status CreateReader(
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

    Status CreateWriter(
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

    Status ReadText(
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

    Status WriteText(
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

    Status ReadBinary(
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

    Status WriteBinary(
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

    Status ReadBinary(
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

    Status WriteBinary(
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
