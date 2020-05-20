#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/String.hxx>

//
// Missing features:
//
//  - explicitly create directory if cannot create file
//  - explicit flags for file operations: fail when cannot create file
//  - file copy/move directory copy/move with progress with cancellation
//

namespace Graphyte::Storage
{
    IFileSystem::IFileSystem() noexcept = default;

    IFileSystem::~IFileSystem() noexcept = default;

    Status IFileSystem::FileCopy(
        const std::string& destination,
        const std::string& source
    ) noexcept
    {
        constexpr size_t BufferSize = 1024 * 1024;

        std::unique_ptr<IStream> file_source{};

        if (OpenRead(file_source, source, false) != Status::Success || file_source == nullptr)
        {
            return Status::Failure;
        }

        int64_t size = file_source->GetSize();

        if (size < 0)
        {
            GX_ASSERT(size == 0);
            return Status::Failure;
        }

        std::unique_ptr<IStream> file_destination{};

        if (OpenWrite(file_destination, destination, false, false) != Status::Success || file_destination == nullptr)
        {
            return Status::Failure;
        }

        size_t const buffer_size = static_cast<size_t>(std::min<int64_t>(BufferSize, size));
        
        GX_ASSERT(buffer_size != 0);
        GX_ASSERT(buffer_size <= static_cast<size_t>(std::numeric_limits<int32_t>::max()));

        auto buffer = std::make_unique<std::byte[]>(buffer_size);

        GX_ASSERT(buffer != nullptr);

        while (size != 0)
        {
            size_t part_size = static_cast<size_t>(std::min<int64_t>(static_cast<int64_t>(buffer_size), size));

            GX_ASSERT(buffer_size != 0);
            GX_ASSERT(buffer_size <= BufferSize);

            size_t processed{};

            if (file_source->Read({ buffer.get(), part_size }, processed) != Status::Success)
            {
                GX_ASSERTF(false, "Cannot read from file");
            }

            if (file_destination->Write({ buffer.get(), part_size }, processed) != Status::Success)
            {
                GX_ASSERTF(false, "Cannot write to file");
            }

            size -= part_size;
        }

        return Status::Success;
    }

    Status IFileSystem::EnumerateRecursive(
        const std::string& path,
        IDirectoryVisitor& visitor
    ) noexcept
    {
        class Recursive : public IDirectoryVisitor
        {
        private:
            IFileSystem& m_FileSystem;
            IDirectoryVisitor& m_Visitor;

        public:
            Recursive(
                IFileSystem& filesystem,
                IDirectoryVisitor& visitor
            ) noexcept
                : m_FileSystem{ filesystem }
                , m_Visitor{ visitor }
            {
            }

            virtual Status Visit(
                const std::string& path,
                bool is_directory
            ) noexcept override
            {
                Status result = m_Visitor.Visit(path, is_directory);

                if (result == Status::Success && is_directory)
                {
                    result = m_FileSystem.Enumerate(path, *this);
                }

                return result;
            }
        };

        Recursive recursive{ *this, visitor };

        return Enumerate(path, recursive);
    }

    Status IFileSystem::EnumerateRecursive(
        const std::string& path,
        IDirectoryInfoVisitor& visitor
    ) noexcept
    {
        class Recursive : public IDirectoryInfoVisitor
        {
        private:
            IFileSystem & m_FileSystem;
            IDirectoryInfoVisitor& m_Visitor;

        public:
            Recursive(
                IFileSystem& filesystem,
                IDirectoryInfoVisitor& visitor
            ) noexcept
                : m_FileSystem{ filesystem }
                , m_Visitor{ visitor }
            {
            }

            virtual Status Visit(
                const std::string& path,
                const FileInfo& info
            ) noexcept override
            {
                Status result = m_Visitor.Visit(path, info);

                if (result == Status::Success && info.IsDirectory)
                {
                    result = m_FileSystem.Enumerate(path, *this);
                }

                return result;
            }
        };

        Recursive recursive{ *this, visitor };

        return Enumerate(path, recursive);
    }

    Status IFileSystem::DirectoryTreeCreate(
        const std::string& path
    ) noexcept
    {
        GX_ASSERT(Storage::IsValidPath(path));

        size_t position = 0;

        std::string_view path_view{ path };

        std::string full{};

        while (position != std::string_view::npos)
        {
            position = path_view.find_first_of("/\\", position + 1);
            full.assign(path_view.substr(0, position));

            if (DirectoryCreate(full) != Status::Success && Exists(full) != Status::Success)
            {
                // XXX: Change this - DirectoryCreate may return AlreadyExists
                break;
            }
        }

        return Exists(path);
    }

    Status IFileSystem::DirectoryTreeDelete(
        const std::string& path
    ) noexcept
    {
        class Recursive final : public IDirectoryVisitor
        {
        private:
            IFileSystem & m_FileSystem;

        public:
            Recursive(
                IFileSystem& filesystem
            ) noexcept
                : m_FileSystem{ filesystem }
            {
            }

            virtual Status Visit(
                const std::string& path,
                bool is_directory
            ) noexcept override
            {
                if (is_directory)
                {
                    Status status = m_FileSystem.Enumerate(path, *this);

                    if (status == Status::Success)
                    {
                        status = m_FileSystem.DirectoryDelete(path);
                    }

                    return status;
                }
                else
                {
                    Status status = m_FileSystem.SetReadonly(path, false);

                    if (status == Status::Success)
                    {
                        status = m_FileSystem.FileDelete(path);
                    }

                    return status;
                }
            }
        };

        Recursive recursive{ *this };
        Status status = recursive.Visit(path, true);

        if (status == Status::Success)
        {
            status = this->Exists(path);
        }

        return status;
    }

    Status IFileSystem::DirectoryTreeCopy(
        const std::string& destination,
        const std::string& source,
        bool overwrite
    ) noexcept
    {
        GX_ASSERT(IsValidPath(destination));
        GX_ASSERT(IsValidPath(source));

        if (Exists(source) != Status::Success)
        {
            // XXX: Change this
            return Status::Failure;
        }

        if (Exists(destination) != Status::Success)
        {
            // XXX: Change this
            return Status::Failure;
        }


        class CopyRecursive final : public IDirectoryVisitor
        {
        private:
            IFileSystem & m_FileSystem;
            const std::string& m_Source;
            const std::string& m_Destination;
            bool m_Overwrite;

        public:
            CopyRecursive(
                IFileSystem& filesystem,
                const std::string& source,
                const std::string& destination,
                bool overwrite
            ) noexcept
                : m_FileSystem{ filesystem }
                , m_Source{ source }
                , m_Destination{ destination }
                , m_Overwrite{ overwrite }
            {
            }

            virtual Status Visit(
                const std::string& path,
                bool is_directory
            ) noexcept
            {
                std::string new_path{ path };
                new_path.replace(0, m_Source.length(), m_Destination);

                if (is_directory)
                {
                    return m_FileSystem.DirectoryTreeCreate(new_path);
                }
                else
                {
                    if (m_FileSystem.Exists(new_path) == Status::Success && m_Overwrite)
                    {
                        if (m_FileSystem.FileDelete(new_path) != Status::Success)
                        {
                            return Status::Failure;
                        }
                    }

                    if (m_FileSystem.FileCopy(new_path, path) != Status::Success)
                    {
                        return Status::Failure;
                    }
                }

                return Status::Success;
            }
        };

        std::string path_source{ source };
        std::string path_destination{ destination };

        Storage::AddDirectorySeparator(path_source);
        Storage::AddDirectorySeparator(path_destination);

        CopyRecursive copy_recursive{ *this, path_source, path_destination, overwrite };

        return EnumerateRecursive(path_source, copy_recursive);
    }

    namespace Impl
    {
        class FindFilesVisitor final : public IDirectoryVisitor
        {
        private:
            IFileSystem& m_FileSystem;
            std::vector<std::string>& m_Result;
            std::string_view m_Extension;

        public:
            FindFilesVisitor(
                IFileSystem& filesystem,
                std::vector<std::string>& result,
                std::string_view extension
            ) noexcept
                : m_FileSystem{ filesystem }
                , m_Result{ result }
                , m_Extension{ extension }
            {
                (void)m_FileSystem;
            }

        public:
            virtual Status Visit(
                const std::string& path,
                bool is_directory
            ) noexcept override
            {
                if (!is_directory)
                {
                    if (!m_Extension.empty())
                    {
                        std::string_view const path_view{ path };
                        std::string_view const path_extension = Storage::GetExtension(path_view, false);
                        std::string_view const sanitized = Storage::GetExtension(m_Extension, false);

                        if (path_extension != sanitized)
                        {
                            return Status::Failure;
                        }
                    }

                    m_Result.push_back(path);
                }

                return Status::Success;
            }
        };
    }

    Status IFileSystem::FindFiles(
        std::vector<std::string>& result,
        const std::string& path,
        std::string_view extension
    ) noexcept
    {
        Impl::FindFilesVisitor visitor{ *this, result, extension };

        return Enumerate(path, visitor);
    }

    Status IFileSystem::FindFilesRecursive(
        std::vector<std::string>& result,
        const std::string& path,
        std::string_view extension
    ) noexcept
    {
        Impl::FindFilesVisitor visitor{ *this, result, extension };

        return EnumerateRecursive(path, visitor);
    }
}
