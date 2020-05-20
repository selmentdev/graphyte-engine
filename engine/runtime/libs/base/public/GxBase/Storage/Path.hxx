#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/String.hxx>


namespace Graphyte::Storage
{
    constexpr const std::size_t MaxPath = 260;
    constexpr const std::size_t MaxDirectoryPath = 248;
    constexpr const char VolumeSeparator = ':';
    constexpr const char ExtensionSeparator = '.';
    constexpr const char DirectorySeparator = '/';
    constexpr const char AlternativeDirectorySeparator = '\\';
    constexpr const char PathSeparator = ';';
}

namespace Graphyte::Storage
{
    constexpr bool IsDirectorySeparator(
        char character
    ) noexcept
    {
        return character == Storage::DirectorySeparator
            || character == Storage::AlternativeDirectorySeparator;
    }

    constexpr bool IsVolumeSeparator(
        char character
    ) noexcept
    {
        return character == Storage::VolumeSeparator;
    }

    constexpr bool IsExtensionSeparator(
        char character
    ) noexcept
    {
        return character == Storage::ExtensionSeparator;
    }

    constexpr bool IsDirectoryOrVolumeSeparator(
        char character
    ) noexcept
    {
        return Storage::IsDirectorySeparator(character)
            || Storage::IsVolumeSeparator(character);
    }

    constexpr bool IsPathSeparator(
        char character
    ) noexcept
    {
        return character == Storage::PathSeparator;
    }
}


namespace Graphyte::Storage
{
    extern BASE_API void AppendPath(
        std::string& path,
        std::string_view subpath
    ) noexcept;

    extern BASE_API std::string CombinePath(
        std::string_view path1,
        std::string_view path2
    ) noexcept;

    extern BASE_API std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3
    ) noexcept;

    extern BASE_API std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4
    ) noexcept;

    extern BASE_API std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4,
        std::string_view path5
    ) noexcept;

    extern BASE_API std::string CombinePath(
        std::string_view path1,
        std::string_view path2,
        std::string_view path3,
        std::string_view path4,
        std::string_view path5,
        std::string_view path6
    ) noexcept;

    extern BASE_API void AddDirectorySeparator(
        std::string& path
    ) noexcept;

    extern BASE_API void RemoveDirectorySeparator(
        std::string& path
    ) noexcept;

    extern BASE_API void ChangeExtension(
        std::string& path,
        std::string_view extension
    ) noexcept;

    extern BASE_API void ChangeFilename(
        std::string& path,
        std::string_view filename
    ) noexcept;
        
    extern BASE_API std::string_view GetExtension(
        std::string_view path,
        bool include_separator = false
    ) noexcept;

    extern BASE_API std::string_view GetFilename(
        std::string_view path
    ) noexcept;

    extern BASE_API std::string_view GetBaseFilename(
        std::string_view path
    ) noexcept;

    extern BASE_API std::string_view GetPath(
        std::string_view path
    ) noexcept;

    extern BASE_API std::string_view GetScheme(
        std::string_view path
    ) noexcept;

    /*!
     * \brief   Splits source path into separate parts.
     *
     * \param   path            Provides source path to split.
     * \param   path_part       Returns path of source.
     * \param   filename_part   Returns file name of source.
     * \param   extension_part  Returns extension of source.
     */
    extern BASE_API void SplitPath(
        std::string_view path,
        std::string_view& path_part,
        std::string_view& filename_part,
        std::string_view& extension_part
    ) noexcept;

    extern BASE_API void NormalizePath(
        std::string& path
    ) noexcept;

    extern BASE_API std::string NormalizedPath(
        std::string_view path
    ) noexcept;

    extern BASE_API bool CanonicalizePath(
        std::string& path
    ) noexcept;

    extern BASE_API bool RelativePath(
        std::string& result,
        std::string_view source,
        std::string_view target
    ) noexcept;

    extern BASE_API std::string CreateTemporaryFilePath(
        std::string_view path,
        std::string_view prefix,
        std::string_view suffix
    ) noexcept;

    constexpr bool IsAbsolutePath(
        std::string_view path
    ) noexcept
    {
        if (!path.empty())
        {
            return IsDirectorySeparator(path[0]);
        }

        return false;
    }

    constexpr bool IsValidPath(
        std::string_view path
    ) noexcept
    {
        return path.find(AlternativeDirectorySeparator) == std::string_view::npos;
    }

    inline std::vector<std::string_view> SplitPath(
        std::string_view path
    ) noexcept
    {
        return Graphyte::Split(path, "/\\");
    }
}
