#include "Base.pch.hxx"
#include <Graphyte/System.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/Storage/Path.hxx>

#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API Status GetClipboardContent(
        std::string& content
    ) noexcept
    {
        bool result{ false };

        if (OpenClipboard(GetActiveWindow()) != FALSE)
        {
            bool is_unicode{ true };
            HGLOBAL memory = GetClipboardData(CF_UNICODETEXT);

            if (memory == nullptr)
            {
                memory = GetClipboardData(CF_TEXT);
            }

            if (memory == nullptr)
            {
                content.clear();
                result = true;
            }
            else
            {
                LPVOID data = GlobalLock(memory);
                GX_ASSERT(data != nullptr);

                if (data != nullptr)
                {
                    if (is_unicode)
                    {
                        content = Impl::ConvertString(reinterpret_cast<wchar_t*>(data));
                    }
                    else
                    {
                        content = reinterpret_cast<char*>(data);
                    }

                    GlobalUnlock(data);
                }
            }

            CloseClipboard();
        }

        if (result)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status SetClipboardContent(
        std::string_view content
    ) noexcept
    {
        bool result = false;

        if (OpenClipboard(GetActiveWindow()) != FALSE)
        {
            EmptyClipboard();

            std::wstring wvalue = Impl::ConvertString(content);

            size_t const length = wvalue.length();
            size_t const buffer_size = sizeof(wchar_t) * (length + 1);

            HGLOBAL memory = GlobalAlloc(GMEM_MOVEABLE, buffer_size);
            GX_ASSERT(memory != nullptr);

            if (memory != nullptr)
            {
                LPVOID data = GlobalLock(memory);
                GX_ASSERT(data != nullptr);

                if (data != nullptr)
                {
                    std::memcpy(data, wvalue.data(), buffer_size);
                    result = true;

                    GlobalUnlock(memory);
                }

                if (SetClipboardData(CF_UNICODETEXT, memory) == nullptr)
                {
                    GX_ASSERTF(false, "Cannot set clipboard data");
                }

                GlobalFree(memory);
            }

            CloseClipboard();
        }

        if (result)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status GetEnvironmentVariable(
        std::string& result,
        const char* name
    ) noexcept
    {
        GX_ASSERT(name != nullptr);

        std::wstring const wname = Impl::ConvertString(name);

        DWORD dwLength = GetEnvironmentVariableW(wname.c_str(), nullptr, 0);

        if (dwLength != 0)
        {
            //
            // Variable is available. Allocate temp buffer for its content and store it.
            //
            std::wstring wbuffer(static_cast<size_t>(dwLength - 1), 0);

            GX_ASSERT(wbuffer.capacity() >= (static_cast<size_t>(dwLength) + 1));

            //
            // Get actual variable content.
            //
            DWORD dwResult = GetEnvironmentVariableW(wname.c_str(), &wbuffer[0], dwLength) + 1;

            if (dwResult != 0 && dwResult == dwLength)
            {
                result = Impl::ConvertString(wbuffer);
                return Status::Success;
            }
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status SetEnvironmentVariable(
        const char* name,
        const char* value
    ) noexcept
    {
        GX_ASSERT(name != nullptr);
        GX_ASSERT(value != nullptr);

        std::wstring const wname = Impl::ConvertString(name);
        std::wstring const wvalue = Impl::ConvertString(value);

        BOOL bResult = SetEnvironmentVariableW(
            wname.c_str(),
            wvalue.c_str()
        );

        if (bResult != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status RemoveEnvironmentVariable(
        const char* name
    ) noexcept
    {
        GX_ASSERT(name != nullptr);

        std::wstring const wname = Impl::ConvertString(name);

        BOOL bResult = SetEnvironmentVariableW(
            wname.c_str(),
            nullptr
        );

        if (bResult != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status SetCurrentDirectory(
        const std::string& value
    ) noexcept
    {
        std::wstring const wpath = System::Impl::ConvertString(value);

        BOOL status = SetCurrentDirectoryW(wpath.c_str());

        if (status != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    BASE_API Status GetCurrentDirectory(
        std::string& result
    ) noexcept
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

        result = System::Impl::ConvertString(wszPath);
        Storage::Path::Normalize(result);

        return Status::Success;
    }

    BASE_API std::string GetExecutablePath() noexcept
    {
        std::string result{};

        System::Impl::WindowsPath wpath{};

        DWORD dwLength = GetModuleFileNameW(
            System::Impl::GInstanceHandle,
            std::data(wpath),
            static_cast<DWORD>(std::size(wpath))
        );

        if (dwLength != 0)
        {
            result = System::Impl::ConvertString(
                std::wstring_view{
                    std::data(wpath),
                    dwLength
                }
            );

            Storage::Path::Normalize(result);
            Storage::Path::Canonicalize(result);
        }

        return result;
    }

    BASE_API std::string GetExecutableName() noexcept
    {
        std::string path = System::GetExecutablePath();

        std::string result = Storage::Path::GetFilename(path);

        return result;
    }

    BASE_API std::string GetBaseDirectory() noexcept
    {
        std::string result = System::GetExecutablePath();


        //
        // Remove file name and ensure that path to directory ends with `/`.
        //

        Storage::Path::ChangeFilename(result, {});
        Storage::Path::AddDirectorySeparator(result);

        return result;
    }

    BASE_API Status Execute(
        const char* type,
        const char* command,
        const char* params
    ) noexcept
    {
        //
        // Convert argument strings.
        //

        std::wstring const wtype = Impl::ConvertString(type);
        std::wstring const wcommand = Impl::ConvertString(command);
        std::wstring const wparams = Impl::ConvertString(params);

        HINSTANCE handle = ShellExecuteW(
            nullptr,
            wtype.c_str(),
            wcommand.c_str(),
            wparams.c_str(),
            nullptr,
            SW_SHOWNORMAL
        );


        //
        // Note:
        //  According to documentation, this function returns value greater than 32 when function succeeds.
        //  https://msdn.microsoft.com/en-us/library/windows/desktop/bb762153%28v=vs.85%29.aspx
        //

        if (handle > reinterpret_cast<HINSTANCE>(32))
        {
            return Status::Success;
        }

        return Status::Failure;
    }

    BASE_API Status Explore(
        const char* path
    ) noexcept
    {
        std::wstring const wpath = Impl::ConvertString(path);

        bool success;

        if (Storage::IFileSystem::GetPlatformNative().Exists(path) == Status::Success)
        {
            success = ShellExecuteW(
                nullptr,
                L"explore",
                wpath.c_str(),
                nullptr,
                nullptr,
                SW_SHOWNORMAL
            ) != nullptr;
        }
        else
        {
            std::wstring params{ L"/select," };
            params += wpath;

            success = ShellExecuteW(
                nullptr,
                L"open",
                L"explorer.exe",
                params.c_str(),
                nullptr,
                SW_SHOWNORMAL
            ) != nullptr;
        }

        return success
            ? Status::Success
            : Status::Failure;
    }
}
