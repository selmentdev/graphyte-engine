#include "Base.pch.hxx"
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/String.hxx>
#include <Graphyte/Uuid.hxx>

namespace Graphyte::Storage
{
    namespace Impl
    {
        // TODO: replace with string_view
        static const char GFolderSeparators[] = {
            Path::DirectorySeparator,
            Path::AlternativeDirectorySeparator,
            0
        };
    }

    void Path::Append(
        std::string& path,
        std::string_view subpath
    ) noexcept
    {
        if (!subpath.empty())
        {
            if (!Path::IsDirectorySeparator(subpath[0]))
            {
                Path::AddDirectorySeparator(path);
            }

            path.append(subpath);
        }
    }

    std::string Path::Combine(
        std::string_view path1,
        std::string_view path2
    ) noexcept
    {
        std::string result{ path1 };

        Path::Append(result, path2);

        return result;
    }

    std::string Path::Combine(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3
    ) noexcept
    {
        std::string result{ path1 };

        Path::Append(result, path2);
        Path::Append(result, path3);

        return result;
    }

    std::string Path::Combine(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4
    ) noexcept
    {
        std::string result{ path1 };

        Path::Append(result, path2);
        Path::Append(result, path3);
        Path::Append(result, path4);

        return result;
    }

    std::string Path::Combine(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4,
        std::string_view path5
    ) noexcept
    {
        std::string result{ path1 };

        Path::Append(result, path2);
        Path::Append(result, path3);
        Path::Append(result, path4);
        Path::Append(result, path5);

        return result;
    }

    std::string Path::Combine(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4,
        std::string_view path5,
        std::string_view path6
    ) noexcept
    {
        std::string result{ path1 };

        Path::Append(result, path2);
        Path::Append(result, path3);
        Path::Append(result, path4);
        Path::Append(result, path5);
        Path::Append(result, path6);

        return result;
    }

    void Path::AddDirectorySeparator(
        std::string& path
    ) noexcept
    {
        if (!path.empty())
        {
            if (!Path::IsDirectorySeparator(path.back()))
            {
                path.append(1, Path::DirectorySeparator);
            }
        }
    }

    void Path::RemoveDirectorySeparator(
        std::string& path
    ) noexcept
    {
        if (!path.empty())
        {
            if (Path::IsDirectorySeparator(path.back()))
            {
                path.pop_back();
            }
        }
    }

    void Path::ChangeExtension(
        std::string& path,
        std::string_view extension
    ) noexcept
    {
        size_t const separator_position = path.find_last_of(Path::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            path.resize(separator_position);
        }

        if (!extension.empty())
        {
            if (!Path::IsExtensionSeparator(extension[0]))
            {
                path.append(1, Path::ExtensionSeparator);
            }

            path.append(extension);
        }
    }

    void Path::ChangeFilename(
        std::string& path,
        std::string_view filename
    ) noexcept
    {
        size_t const separator_position = path.find_last_of(Impl::GFolderSeparators);

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

    std::string Path::GetExtension(
        std::string_view path,
        bool include_separator
    ) noexcept
    {
        std::string result{};

        size_t separator_position = path.find_last_of(Path::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            if (!include_separator)
            {
                ++separator_position;
            }

            result.assign(path.substr(separator_position));
        }

        return result;
    }

    std::string Path::GetFilename(
        std::string_view path
    ) noexcept
    {
        std::string result{};

        size_t separator_position = path.find_last_of(Impl::GFolderSeparators);

        if (separator_position != std::string::npos)
        {
            ++separator_position;
            result.assign(path.substr(separator_position));
        }
        else
        {
            result.assign(path);
        }

        return result;
    }

    std::string Path::GetBaseFilename(
        std::string_view path
    ) noexcept
    {
        std::string result{ Path::GetFilename(path) };

        size_t const separator_position = result.find_last_of(Path::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            result.resize(separator_position);
        }

        return result;
    }

    std::string Path::GetPath(
        std::string_view path
    ) noexcept
    {
        std::string result{};

        size_t separator_position = path.find_last_of(Impl::GFolderSeparators);

        if (separator_position != std::string::npos)
        {
            ++separator_position;
            result.assign(path.substr(0, separator_position));
        }

        return result;
    }

    std::string Path::GetScheme(
        std::string_view path
    ) noexcept
    {
        std::string result{};

        size_t separator_position = path.rfind("://");

        if (separator_position != std::string::npos)
        {
            result.assign(path.substr(0, separator_position));
        }

        return result;
    }

    std::string_view Path::GetExtensionRef(
        std::string_view path,
        bool include_separator
    ) noexcept
    {
        std::string_view result{};

        size_t separator_position = path.find_last_of(Path::ExtensionSeparator);

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

    std::string_view Path::GetFilenameRef(
        std::string_view path
    ) noexcept
    {
        std::string_view result{};

        size_t separator_position = path.find_last_of(Impl::GFolderSeparators);

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

    std::string_view Path::GetBaseFilenameRef(
        std::string_view path
    ) noexcept
    {
        std::string_view result{ Path::GetFilenameRef(path) };

        size_t const separator_position = result.find_last_of(Path::ExtensionSeparator);

        if (separator_position != std::string::npos)
        {
            result = result.substr(0, separator_position);
        }

        return result;
    }

    std::string_view Path::GetPathRef(
        std::string_view path
    ) noexcept
    {
        std::string_view result{};

        size_t separator_position = path.find_last_of(Impl::GFolderSeparators);

        if (separator_position != std::string::npos)
        {
            ++separator_position;
            result = path.substr(0, separator_position);
        }

        return result;
    }

    std::string_view Path::GetSchemeRef(
        std::string_view path
    ) noexcept
    {
        std::string_view result{};

        size_t const separator_position = path.rfind("://");

        if (separator_position != std::string::npos)
        {
            result = path.substr(0, separator_position);
        }

        return result;
    }

    void Path::Split(
        std::string_view path,
        std::string& path_part,
        std::string& filename_part,
        std::string& extension_part
    ) noexcept
    {
        path_part = Path::GetPath(path);
        filename_part = Path::GetBaseFilename(path);
        extension_part = Path::GetExtension(path, false);
    }

    void Path::Normalize(
        std::string& path
    ) noexcept
    {
        for (char& c : path)
        {
            if (c == Path::AlternativeDirectorySeparator)
            {
                c = Path::DirectorySeparator;
            }
        }
    }

    std::string Path::Normalized(
        std::string_view path
    ) noexcept
    {
        std::string result{ path };

        Path::Normalize(result);

        return result;
    }

    bool Path::Canonicalize(
        std::string& path
    ) noexcept
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

    bool Path::Relative(
        std::string& result,
        std::string_view source,
        std::string_view target
    ) noexcept
    {
        std::string normalized_source = Path::Normalized(source);
        std::string normalized_target = Path::Normalized(target);

        Path::Canonicalize(normalized_source);
        Path::Canonicalize(normalized_target);

        auto parts_source = Graphyte::Split(normalized_source, Path::DirectorySeparator);
        auto parts_target = Graphyte::Split(normalized_target, Path::DirectorySeparator);

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

    std::string Path::CreateTempFilename(
        std::string_view path,
        std::string_view prefix,
        std::string_view extension
    ) noexcept
    {
        std::string unique{};

        do
        {
            auto const id = Uuid::Create();
            auto const filename = fmt::format("{}{:016x}{:016x}{}", prefix, id.Low, id.High, extension);

            unique = Path::Combine(path, filename);
        } while (Storage::IFileSystem::GetPlatformNative().Exists(unique) == Status::Success);

        return unique;
    }
}
