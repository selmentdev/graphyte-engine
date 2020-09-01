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
        std::string_view destination,
        std::string_view source) noexcept
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
        std::string_view path,
        IDirectoryVisitor& visitor) noexcept
    {
        class EnumerateRecursiveVisitor : public IDirectoryVisitor
        {
        private:
            IFileSystem& m_FileSystem;
            IDirectoryVisitor& m_Visitor;

        public:
            EnumerateRecursiveVisitor(
                IFileSystem& filesystem,
                IDirectoryVisitor& visitor) noexcept
                : m_FileSystem{ filesystem }
                , m_Visitor{ visitor }
            {
            }

            virtual Status Visit(
                std::string_view path,
                bool is_directory) noexcept override
            {
                Status result = m_Visitor.Visit(path, is_directory);

                if (result == Status::Success && is_directory)
                {
                    result = m_FileSystem.Enumerate(path, *this);
                }

                return result;
            }
        };

        EnumerateRecursiveVisitor recursive{ *this, visitor };

        return Enumerate(path, recursive);
    }

    Status IFileSystem::EnumerateRecursive(
        std::string_view path,
        IDirectoryInfoVisitor& visitor) noexcept
    {
        class EnumerateRecursiveVisitor : public IDirectoryInfoVisitor
        {
        private:
            IFileSystem& m_FileSystem;
            IDirectoryInfoVisitor& m_Visitor;

        public:
            EnumerateRecursiveVisitor(
                IFileSystem& filesystem,
                IDirectoryInfoVisitor& visitor) noexcept
                : m_FileSystem{ filesystem }
                , m_Visitor{ visitor }
            {
            }

            virtual Status Visit(
                std::string_view path,
                const FileInfo& info) noexcept override
            {
                Status result = m_Visitor.Visit(path, info);

                if (result == Status::Success && info.IsDirectory)
                {
                    result = m_FileSystem.Enumerate(path, *this);
                }

                return result;
            }
        };

        EnumerateRecursiveVisitor recursive{ *this, visitor };

        return Enumerate(path, recursive);
    }

    Status IFileSystem::DirectoryTreeCreate(
        std::string_view path) noexcept
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
        std::string_view path) noexcept
    {
        class DirectoryTreeDeleteVisitor final : public IDirectoryVisitor
        {
        private:
            IFileSystem& m_FileSystem;

        public:
            DirectoryTreeDeleteVisitor(
                IFileSystem& filesystem) noexcept
                : m_FileSystem{ filesystem }
            {
            }

            virtual Status Visit(
                std::string_view path,
                bool is_directory) noexcept override
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

        DirectoryTreeDeleteVisitor recursive{ *this };
        Status status = recursive.Visit(path, true);

        if (status == Status::Success)
        {
            status = this->Exists(path);
        }

        return status;
    }

    Status IFileSystem::DirectoryTreeCopy(
        std::string_view destination,
        std::string_view source,
        bool overwrite) noexcept
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


        class DirectoryTreeCopyVisitor final : public IDirectoryVisitor
        {
        private:
            IFileSystem& m_FileSystem;
            std::string_view m_Source;
            std::string_view m_Destination;
            bool m_Overwrite;

        public:
            DirectoryTreeCopyVisitor(
                IFileSystem& filesystem,
                std::string_view source,
                std::string_view destination,
                bool overwrite) noexcept
                : m_FileSystem{ filesystem }
                , m_Source{ source }
                , m_Destination{ destination }
                , m_Overwrite{ overwrite }
            {
            }

            virtual Status Visit(
                std::string_view path,
                bool is_directory) noexcept
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

        DirectoryTreeCopyVisitor copy_recursive{ *this, path_source, path_destination, overwrite };

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
                std::string_view extension) noexcept
                : m_FileSystem{ filesystem }
                , m_Result{ result }
                , m_Extension{ GetExtension(extension, false) }
            {
                (void)m_FileSystem;
            }

        public:
            virtual Status Visit(
                std::string_view path,
                bool is_directory) noexcept override
            {
                if (!is_directory)
                {
                    if (!m_Extension.empty())
                    {
                        //
                        // Caller provided extension to match. Append path to results only then.
                        //

                        std::string_view const path_extension = Storage::GetExtension(path, false);

                        if (path_extension == m_Extension)
                        {
                            m_Result.emplace_back(path);
                        }
                    }
                    else
                    {
                        //
                        // When caller did not provide proper extension, it means we match all
                        // possible files
                        //

                        m_Result.emplace_back(path);
                    }
                }

                return Status::Success;
            }
        };
    }

    Status IFileSystem::FindFiles(
        std::vector<std::string>& result,
        std::string_view path,
        std::string_view extension) noexcept
    {
        Impl::FindFilesVisitor visitor{ *this, result, extension };

        return Enumerate(path, visitor);
    }

    Status IFileSystem::FindFilesRecursive(
        std::vector<std::string>& result,
        std::string_view path,
        std::string_view extension) noexcept
    {
        Impl::FindFilesVisitor visitor{ *this, result, extension };

        return EnumerateRecursive(path, visitor);
    }
}
