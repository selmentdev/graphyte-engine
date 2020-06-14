#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/Path.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API Status GetClipboardContent(
        std::string& content) noexcept
    {
        content = {};
        return Status::NotImplemented;
    }

    BASE_API Status SetClipboardContent(
        [[maybe_unused]] std::string_view content) noexcept
    {
        return Status::NotImplemented;
    }

    BASE_API Status GetEnvironmentVariable(
        std::string& result,
        const char* name) noexcept
    {
        GX_ASSERT(name != nullptr);

        std::wstring const wname = Impl::WidenString(name);

        DWORD dwLength = GetEnvironmentVariableW(wname.c_str(), nullptr, 0);

        if (dwLength != 0)
        {
            //
            // Variable is available. Allocate temp buffer for its content and store it.
            //
            std::wstring wbuffer(static_cast<size_t>(dwLength - 1), 0);

            GX_ASSERT(wbuffer.capacity() >= static_cast<size_t>(dwLength));

            //
            // Get actual variable content.
            //
            DWORD dwResult = GetEnvironmentVariableW(wname.c_str(), &wbuffer[0], dwLength) + 1;

            if (dwResult != 0 && dwResult == dwLength)
            {
                result = Impl::NarrowString(wbuffer);
                return Status::Success;
            }
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status SetEnvironmentVariable(
        const char* name,
        const char* value) noexcept
    {
        GX_ASSERT(name != nullptr);
        GX_ASSERT(value != nullptr);

        std::wstring const wname  = Impl::WidenString(name);
        std::wstring const wvalue = Impl::WidenString(value);

        BOOL bResult = SetEnvironmentVariableW(
            wname.c_str(),
            wvalue.c_str());

        if (bResult != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status RemoveEnvironmentVariable(
        const char* name) noexcept
    {
        GX_ASSERT(name != nullptr);

        std::wstring const wname = Impl::WidenString(name);

        BOOL bResult = SetEnvironmentVariableW(
            wname.c_str(),
            nullptr);

        if (bResult != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status SetCurrentDirectory(
        const std::string& value) noexcept
    {
        std::wstring const wpath = System::Impl::WidenString(value);

        BOOL status = SetCurrentDirectoryW(wpath.c_str());

        if (status != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status GetCurrentDirectory(
        std::string& result) noexcept
    {
        std::wstring wszPath{};

        DWORD dwRequired = GetCurrentDirectoryW(0, nullptr);
        GX_ASSERT(dwRequired != 0);

        if (dwRequired == 0)
        {
            return Diagnostics::GetStatusFromSystemError();
        }

        wszPath.resize(dwRequired - 1);

        DWORD dwLength = GetCurrentDirectoryW(dwRequired, std::data(wszPath));
        GX_ASSERT(dwLength != 0);

        if (dwLength == 0)
        {
            return Diagnostics::GetStatusFromSystemError();
        }

        result = System::Impl::NarrowString(wszPath);
        Storage::NormalizePath(result);

        return Status::Success;
    }

    BASE_API std::string GetExecutablePath() noexcept
    {
        std::string result{};

        System::Impl::WindowsPath wpath{};

        DWORD dwLength = GetModuleFileNameW(
            System::Impl::GInstanceHandle,
            std::data(wpath),
            static_cast<DWORD>(std::size(wpath)));

        if (dwLength != 0)
        {
            result = System::Impl::NarrowString(
                std::wstring_view{
                    std::data(wpath),
                    dwLength });

            Storage::NormalizePath(result);
            Storage::CanonicalizePath(result);
        }

        return result;
    }

    BASE_API std::string GetExecutableName() noexcept
    {
        std::string path = System::GetExecutablePath();
        return std::string{ Storage::GetFilename(path) };
    }

    BASE_API std::string GetBaseDirectory() noexcept
    {
        std::string result = System::GetExecutablePath();


        //
        // Remove file name and ensure that path to directory ends with `/`.
        //

        Storage::ChangeFilename(result, {});
        Storage::AddDirectorySeparator(result);

        return result;
    }

    BASE_API Status Execute(
        [[maybe_unused]] const char* type,
        [[maybe_unused]] const char* command,
        [[maybe_unused]] const char* params) noexcept
    {
        return Status::NotImplemented;
    }

    BASE_API Status Explore(
        [[maybe_unused]] const char* path) noexcept
    {
        return Status::NotImplemented;
    }
}
