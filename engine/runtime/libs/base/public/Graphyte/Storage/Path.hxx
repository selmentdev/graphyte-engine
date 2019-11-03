#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/String.hxx>

namespace Graphyte::Storage
{
    class BASE_API Path final
    {
    public:
        static constexpr const size_t MaxPath = 260;
        static constexpr const size_t MaxDirectoryPath = 248;
        static constexpr const char VolumeSeparator = ':';
        static constexpr const char ExtensionSeparator = '.';
        static constexpr const char DirectorySeparator = '/';
        static constexpr const char AlternativeDirectorySeparator = '\\';
        static constexpr const char PathSeparator = ';';

    public:
        static bool IsDirectorySeparator(
            char character
        ) noexcept
        {
            return character == Path::DirectorySeparator
                || character == Path::AlternativeDirectorySeparator;
        }

        static bool IsVolumeSeparator(
            char character
        ) noexcept
        {
            return character == Path::VolumeSeparator;
        }

        static bool IsExtensionSeparator(
            char character
        ) noexcept
        {
            return character == Path::ExtensionSeparator;
        }

        static bool IsDirectoryOrVolumeSeparator(
            char character
        ) noexcept
        {
            return Path::IsDirectorySeparator(character)
                || Path::IsVolumeSeparator(character);
        }

        static bool IsPathSeparator(
            char character
        ) noexcept
        {
            return character == Path::PathSeparator;
        }

    public:
        static void Append(
            std::string& path,
            std::string_view subpath
        ) noexcept;

        static std::string Combine(
            std::string_view path1,
            std::string_view path2
        ) noexcept;

        static std::string Combine(
            std::string_view path1,
            std::string_view path2,
            std::string_view path3
        ) noexcept;

        static std::string Combine(
            std::string_view path1,
            std::string_view path2,
            std::string_view path3,
            std::string_view path4
        ) noexcept;

        static std::string Combine(
            std::string_view path1,
            std::string_view path2,
            std::string_view path3,
            std::string_view path4,
            std::string_view path5
        ) noexcept;

        static std::string Combine(
            std::string_view path1,
            std::string_view path2,
            std::string_view path3,
            std::string_view path4,
            std::string_view path5,
            std::string_view path6
        ) noexcept;

        static void AddDirectorySeparator(
            std::string& path
        ) noexcept;

        static void RemoveDirectorySeparator(
            std::string& path
        ) noexcept;

        static void ChangeExtension(
            std::string& path,
            std::string_view extension
        ) noexcept;

        static void ChangeFilename(
            std::string& path,
            std::string_view filename
        ) noexcept;
        
        static std::string GetExtension(
            std::string_view path,
            bool include_separator = false
        ) noexcept;

        static std::string GetFilename(
            std::string_view path
        ) noexcept;

        static std::string GetBaseFilename(
            std::string_view path
        ) noexcept;

        static std::string GetPath(
            std::string_view path
        ) noexcept;

        static std::string GetScheme(
            std::string_view path
        ) noexcept;

        static std::string_view GetExtensionRef(
            std::string_view path,
            bool include_separator = false
        ) noexcept;

        static std::string_view GetFilenameRef(
            std::string_view path
        ) noexcept;

        static std::string_view GetBaseFilenameRef(
            std::string_view path
        ) noexcept;

        static std::string_view GetPathRef(
            std::string_view path
        ) noexcept;

        static std::string_view GetSchemeRef(
            std::string_view path
        ) noexcept;

        // TODO: This could return string_view as well.
        static void Split(
            std::string_view path,
            std::string& path_part,
            std::string& filename_part,
            std::string& extension_part
        ) noexcept;

        static void Normalize(
            std::string& path
        ) noexcept;

        static std::string Normalized(
            std::string_view path
        ) noexcept;

        static bool Canonicalize(
            std::string& path
        ) noexcept;

        static bool Relative(
            std::string& result,
            std::string_view source,
            std::string_view target
        ) noexcept;

        static std::string CreateTempFilename(
            std::string_view path,
            std::string_view prefix,
            std::string_view extension
        ) noexcept;

        static bool IsAbsolute(
            std::string_view path
        ) noexcept
        {
            if (!path.empty())
            {
                return IsDirectorySeparator(path[0]);
            }

            return false;
        }

        static bool IsValid(
            std::string_view path
        ) noexcept
        {
            return path.find(AlternativeDirectorySeparator) == std::string_view::npos;
        }

        static std::vector<std::string_view> Split(
            std::string_view path
        ) noexcept
        {
            return Graphyte::Split(path, "/\\");
        }
    };
}
