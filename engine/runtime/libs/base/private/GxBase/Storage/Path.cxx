#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/String.hxx>
#include <GxBase/Uuid.hxx>

namespace Graphyte::Storage::Impl
{
    static constexpr const char g_FolderSeparators[] = {
        Storage::DirectorySeparator,
        Storage::AlternativeDirectorySeparator,
        0,
    };
}

namespace Graphyte::Storage
{
    void AppendPath(
        std::string& path,
        std::string_view subpath) noexcept
    {
        if (!subpath.empty())
        {
            if (!Storage::IsDirectorySeparator(subpath[0]))
            {
                Storage::AddDirectorySeparator(path);
            }

            path.append(subpath);
        }
    }

    std::string CombinePath(
        std::string_view path1,
        std::string_view path2) noexcept
    {
        std::string result{ path1 };

        Storage::AppendPath(result, path2);

        return result;
    }

    std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3) noexcept
    {
        std::string result{ path1 };

        Storage::AppendPath(result, path2);
        Storage::AppendPath(result, path3);

        return result;
    }

    std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4) noexcept
    {
        std::string result{ path1 };

        Storage::AppendPath(result, path2);
        Storage::AppendPath(result, path3);
        Storage::AppendPath(result, path4);

        return result;
    }

    std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4,
        std::string_view path5) noexcept
    {
        std::string result{ path1 };

        Storage::AppendPath(result, path2);
        Storage::AppendPath(result, path3);
        Storage::AppendPath(result, path4);
        Storage::AppendPath(result, path5);

        return result;
    }

    std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4,
        std::string_view path5,
        std::string_view path6) noexcept
    {
        std::string result{ path1 };

        Storage::AppendPath(result, path2);
        Storage::AppendPath(result, path3);
        Storage::AppendPath(result, path4);
        Storage::AppendPath(result, path5);
        Storage::AppendPath(result, path6);

        return result;
    }

    void AddDirectorySeparator(
        std::string& path) noexcept
    {
        if (!path.empty())
        {
            if (!Storage::IsDirectorySeparator(path.back()))
            {
                path.append(1, Storage::DirectorySeparator);
            }
        }
    }

    void RemoveDirectorySeparator(
        std::string& path) noexcept
    {
        if (!path.empty())
        {
            if (Storage::IsDirectorySeparator(path.back()))
            {
                path.pop_back();
            }
        }
    }

    void ChangeExtension(
        std::string& path,
        std::string_view extension) noexcept
    {
        std::size_t const separator_position = path.find_last_of(Storage::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            path.resize(separator_position);
        }

        if (!extension.empty())
        {
            if (!Storage::IsExtensionSeparator(extension[0]))
            {
                path.append(1, Storage::ExtensionSeparator);
            }

            path.append(extension);
        }
    }

    void ChangeFilename(
        std::string& path,
        std::string_view filename) noexcept
    {
        std::size_t const separator_position = path.find_last_of(Impl::g_FolderSeparators);

        if (separator_position != std::string::npos)
        {
            // #optimization: npos = -1, +1 == 0 -> resize(0)?
            path.resize(separator_position + 1);
        }
        else
        {
            path.clear();
        }

        if (!filename.empty())
        {
            path.append(filename);
        }
    }

    std::string_view GetExtension(
        std::string_view path,
        bool include_separator) noexcept
    {
        std::string_view result{};

        std::size_t separator_position = path.find_last_of(Storage::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            if (!include_separator)
            {
                ++separator_position;
            }

            result = path.substr(separator_position);
        }

        return result;
    }

    std::string_view GetFilename(
        std::string_view path) noexcept
    {
        std::string_view result{};

        std::size_t separator_position = path.find_last_of(Impl::g_FolderSeparators);

        if (separator_position != std::string::npos)
        {
            ++separator_position;
            result = path.substr(separator_position);
        }
        else
        {
            result = path;
        }

        return result;
    }

    std::string_view GetBaseFilename(
        std::string_view path) noexcept
    {
        std::string_view result{ Storage::GetFilename(path) };

        std::size_t const separator_position = result.find_last_of(Storage::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            result = result.substr(0, separator_position);
        }

        return result;
    }

    std::string_view GetPath(
        std::string_view path) noexcept
    {
        std::string_view result{};

        std::size_t separator_position = path.find_last_of(Impl::g_FolderSeparators);

        if (separator_position != std::string::npos)
        {
            ++separator_position;
            result = path.substr(0, separator_position);
        }

        return result;
    }

    extern BASE_API std::string_view GetScheme(
        std::string_view path) noexcept
    {
        std::string_view result{};

        std::size_t const separator_position = path.rfind("://");

        if (separator_position != std::string::npos)
        {
            result = path.substr(0, separator_position);
        }

        return result;
    }

    void SplitPath(
        std::string_view path,
        std::string_view& path_part,
        std::string_view& filename_part,
        std::string_view& extension_part) noexcept
    {
        path_part      = Storage::GetPath(path);
        filename_part  = Storage::GetBaseFilename(path);
        extension_part = Storage::GetExtension(path, false);
    }

    void NormalizePath(
        std::string& path) noexcept
    {
        for (char& c : path)
        {
            if (c == Storage::AlternativeDirectorySeparator)
            {
                c = Storage::DirectorySeparator;
            }
        }
    }

    std::string NormalizedPath(
        std::string_view path) noexcept
    {
        std::string result{ path };

        Storage::NormalizePath(result);

        return result;
    }

    bool CanonicalizePath(
        std::string& path) noexcept
    {
        static std::string_view parent{ "/.." };

        while (true)
        {
            if (path.empty())
            {
                break;
            }

            if (path.compare(0, 2, "..") == 0 || path.compare(0, parent.length(), parent) == 0)
            {
                return false;
            }

            size_t const index = path.find(parent);

            if (index == std::string_view::npos)
            {
                break;
            }

            size_t previous_index = index;

            while (true)
            {
                previous_index = path.rfind('/', previous_index - 1);

                if (previous_index == std::string_view::npos || previous_index == 0)
                {
                    break;
                }

                if ((index - previous_index) > 1 && (path[previous_index + 1] != '.' || path[previous_index + 2] != '/'))
                {
                    break;
                }
            }

            size_t const colon = path.find(':', previous_index);

            if (colon != 0 && colon < index)
            {
                return false;
            }

            if (previous_index == std::string_view::npos)
            {
                break;
            }

            path.erase(previous_index, index - previous_index + parent.length());
        }

        ReplaceAll(path, "./", "");

        return true;
    }

    bool RelativePath(
        std::string& result,
        std::string_view source,
        std::string_view target) noexcept
    {
        std::string normalized_source = Storage::NormalizedPath(source);
        std::string normalized_target = Storage::NormalizedPath(target);

        Storage::CanonicalizePath(normalized_source);
        Storage::CanonicalizePath(normalized_target);

        auto parts_source = Graphyte::Split(normalized_source, Storage::DirectorySeparator);
        auto parts_target = Graphyte::Split(normalized_target, Storage::DirectorySeparator);

        if (!parts_source.empty() && !parts_target.empty())
        {
            auto const& first_source = parts_source[0];
            auto const& first_target = parts_target[0];

            if (first_source.size() > 1 && first_target.size() > 1)
            {
                if (first_source[1] == ':' && first_target[1] == ':')
                {
                    if (std::tolower(first_source[0]) != std::tolower(first_target[0]))
                    {
                        return false;
                    }
                }
            }
        }

        while (!parts_source.empty() && !parts_target.empty() && parts_source[0] == parts_target[0])
        {
            parts_source.erase(parts_source.begin());
            parts_target.erase(parts_target.begin());
        }


        result.clear();

        for (size_t i = 0; i < parts_source.size(); ++i)
        {
            result += "../";
        }

        for (size_t i = 0; i < parts_target.size(); ++i)
        {
            result += parts_target[i];

            size_t const next = i + 1;

            if (next < parts_target.size())
            {
                result += '/';
            }
        }

        return true;
    }

    std::string CreateTemporaryFilePath(
        std::string_view path,
        std::string_view prefix,
        std::string_view suffix) noexcept
    {
        std::string result{};

        do
        {
            Uuid const unique    = Uuid::Create();
            std::string filename = fmt::format("{}{}{}", prefix, unique, suffix);
            result               = Storage::CombinePath(path, filename);
        } while (Storage::IFileSystem::GetPlatformNative().Exists(result) == Status::Success);

        return result;
    }

    std::string CreateTemporaryFilePath(
        Random::RandomState& state,
        std::string_view path,
        std::string_view prefix,
        std::string_view suffix) noexcept
    {
        //
        // Generate string with random characters.
        //

        static constexpr const size_t random_count = 16;

        std::array<char, random_count> random_chars;

        Random::GenerateReadableString(state, { random_chars.data(), random_chars.size() });


        //
        // Final filename.
        //

        fmt::memory_buffer filename{};
        fmt::format_to(filename, "{}{}{}",
            prefix,
            std::string_view{ random_chars.data(), random_chars.size() },
            suffix);


        //
        // Combine path with random filename.
        //

        return Storage::CombinePath(
            path,
            std::string_view{ filename.data(), filename.size() });
    }

    [[nodiscard]] extern BASE_API std::string CreateRandomFilename(
        Random::RandomState& state,
        std::string_view prefix,
        std::string_view suffix) noexcept
    {
        static constexpr const size_t random_count = 16;
        std::array<char, random_count> random_chars;
        Random::GenerateReadableString(state, { random_chars.data(), random_chars.size() });

        return fmt::format("{}{}{}",
            prefix,
            std::string_view{ random_chars.data(), random_chars.size() },
            suffix);
    }
}
