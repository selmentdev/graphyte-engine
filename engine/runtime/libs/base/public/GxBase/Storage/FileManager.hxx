#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Storage/IStream.hxx>
#include <GxBase/Status.hxx>

namespace Graphyte::Storage
{
    extern BASE_API std::string GetRootDirectory() noexcept;
    extern BASE_API std::string GetLaunchDirectory() noexcept;

    extern BASE_API std::string GetEngineDirectory() noexcept;
    extern BASE_API std::string GetEngineContentDirectory() noexcept;
    extern BASE_API std::string GetEngineConfigDirectory() noexcept;
    extern BASE_API std::string GetEngineSourceDirectory() noexcept;
    extern BASE_API std::string GetEngineUserDirectory() noexcept;
    extern BASE_API std::string GetEngineIntermediateDirectory() noexcept;
    extern BASE_API std::string GetEngineSavedDirectory() noexcept;

    extern BASE_API std::string GetProjectDirectory() noexcept;
    extern BASE_API std::string GetProjectContentDirectory() noexcept;
    extern BASE_API std::string GetProjectConfigDirectory() noexcept;
    extern BASE_API std::string GetProjectSourceDirectory() noexcept;
    extern BASE_API std::string GetProjectUserDirectory() noexcept;
    extern BASE_API std::string GetProjectIntermediateDirectory() noexcept;
    extern BASE_API std::string GetProjectSavedDirectory() noexcept;

    extern BASE_API std::string GetScreenshotsDirectory() noexcept;
    extern BASE_API std::string GetCacheDirectory() noexcept;
    extern BASE_API std::string GetLogsDirectory() noexcept;
    extern BASE_API std::string GetCrashdumpDirectory() noexcept;
    extern BASE_API std::string GetDeveloperDirectory() noexcept;
    extern BASE_API std::string GetBugReportDirectory() noexcept;
    extern BASE_API std::string GetProfilingDirectory() noexcept;

    extern BASE_API std::string GetUserSettingsDirectory() noexcept;
    extern BASE_API std::string GetApplicationCommonDataDirectory() noexcept;

    extern BASE_API Status OpenRead(
        std::unique_ptr<IStream>& result,
        const std::string& path,
        bool share = false) noexcept;

    extern BASE_API Status OpenWrite(
        std::unique_ptr<IStream>& result,
        const std::string& path,
        bool append = false,
        bool share  = false) noexcept;

    extern BASE_API Status CreateReader(
        std::unique_ptr<Archive>& archive,
        const std::string& path,
        bool share = false) noexcept;

    extern BASE_API Status CreateWriter(
        std::unique_ptr<Archive>& archive,
        const std::string& path,
        bool append = false,
        bool share  = false) noexcept;

    extern BASE_API Status ReadText(
        std::string& content,
        const std::string& path) noexcept;

    extern BASE_API Status WriteText(
        std::string_view content,
        const std::string& path) noexcept;

    extern BASE_API Status ReadBinary(
        std::vector<std::byte>& content,
        const std::string& path) noexcept;

    extern BASE_API Status WriteBinary(
        const std::vector<std::byte>& content,
        const std::string& path) noexcept;

    extern BASE_API Status ReadBinary(
        std::unique_ptr<std::byte[]>& contents,
        size_t& size,
        const std::string& path) noexcept;

    extern BASE_API Status WriteBinary(
        const std::unique_ptr<std::byte[]>& contents,
        size_t size,
        const std::string& path) noexcept;

    extern BASE_API Status WriteBinary(
        std::span<const std::byte> content,
        const std::string& path) noexcept;
}
