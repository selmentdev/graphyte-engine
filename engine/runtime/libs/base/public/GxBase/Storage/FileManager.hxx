#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Storage/Archive.hxx>
#include <GxBase/Storage/IStream.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte::Storage
{
    class BASE_API FileManager final
    {
    public:
        static std::string GetRootDirectory() noexcept;
        static std::string GetLaunchDirectory() noexcept;

    public:
        static std::string GetEngineDirectory() noexcept;
        static std::string GetEngineContentDirectory() noexcept;
        static std::string GetEngineConfigDirectory() noexcept;
        static std::string GetEngineSourceDirectory() noexcept;
        static std::string GetEngineUserDirectory() noexcept;
        static std::string GetEngineIntermediateDirectory() noexcept;
        static std::string GetEngineSavedDirectory() noexcept;

    public:
        static std::string GetProjectDirectory() noexcept;
        static std::string GetProjectContentDirectory() noexcept;
        static std::string GetProjectConfigDirectory() noexcept;
        static std::string GetProjectSourceDirectory() noexcept;
        static std::string GetProjectUserDirectory() noexcept;
        static std::string GetProjectIntermediateDirectory() noexcept;
        static std::string GetProjectSavedDirectory() noexcept;

    public:
        static std::string GetScreenshotsDirectory() noexcept;
        static std::string GetCacheDirectory() noexcept;
        static std::string GetLogsDirectory() noexcept;
        static std::string GetCrashdumpDirectory() noexcept;
        static std::string GetDeveloperDirectory() noexcept;
        static std::string GetBugReportDirectory() noexcept;
        static std::string GetProfilingDirectory() noexcept;

    public:
        static std::string GetUserSettingsDirectory() noexcept;
        static std::string GetApplicationCommonDataDirectory() noexcept;

    public:
        static Status OpenRead(
            std::unique_ptr<IStream>& result,
            const std::string& path,
            bool share = false
        ) noexcept;

        static Status OpenWrite(
            std::unique_ptr<IStream>& result,
            const std::string& path,
            bool append = false,
            bool share = false
        ) noexcept;

    public:
        static Status CreateReader(
            std::unique_ptr<Archive>& archive,
            const std::string& path,
            bool share = false
        ) noexcept;

        static Status CreateWriter(
            std::unique_ptr<Archive>& archive,
            const std::string& path,
            bool append = false,
            bool share = false
        ) noexcept;

    public:
        static Status ReadText(
            std::string& content,
            const std::string& path
        ) noexcept;

        static Status WriteText(
            std::string_view content,
            const std::string& path
        ) noexcept;

    public:
        static Status ReadBinary(
            std::vector<std::byte>& content,
            const std::string& path
        ) noexcept;

        static Status WriteBinary(
            const std::vector<std::byte>& content,
            const std::string& path
        ) noexcept;

    public:
        static Status ReadBinary(
            std::unique_ptr<std::byte[]>& contents,
            size_t& size,
            const std::string& path
        ) noexcept;

        static Status WriteBinary(
            const std::unique_ptr<std::byte[]>& contents,
            size_t size,
            const std::string& path
        ) noexcept;

    public:
        static Status WriteBinary(
            notstd::span<const std::byte> content,
            const std::string& path
        ) noexcept;
    };
}
