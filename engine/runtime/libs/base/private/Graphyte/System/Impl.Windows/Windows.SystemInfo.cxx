#include <Graphyte/System.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/Storage/Path.hxx>

#include <ShlObj.h>
#include <IPHlpApi.h>

namespace Graphyte::System
{
    BASE_API std::string GetUserDirectory() noexcept
    {
        std::string result{};

        System::Impl::WindowsPath wszPath{};

        HRESULT hr = SHGetFolderPathW(
            nullptr,
            CSIDL_PROFILE,
            nullptr,
            SHGFP_TYPE_CURRENT,
            wszPath.data()
        );

        if (SUCCEEDED(hr))
        {
            result = Impl::NarrowString(wszPath.data());

            Storage::Path::Normalize(result);
            Storage::Path::AddDirectorySeparator(result);
        }

        return result;
    }

    BASE_API std::string GetUserDocumentsDirectory() noexcept
    {
        std::string result{};

        System::Impl::WindowsPath wszPath{};

        HRESULT hr = SHGetFolderPathW(
            nullptr,
            CSIDL_PERSONAL,
            nullptr,
            SHGFP_TYPE_CURRENT,
            wszPath.data()
        );

        if (SUCCEEDED(hr))
        {
            //
            // Convert to engine type.
            //

            result = Impl::NarrowString(wszPath.data());

            Storage::Path::Normalize(result);
            Storage::Path::AddDirectorySeparator(result);
        }

        return result;
    }

    BASE_API std::string GetUserTemporaryDirectory() noexcept
    {
        std::string result{};

        //
        // Get path.
        //

        Impl::WindowsPath wszPath{};

        DWORD dwLength = GetTempPathW(
            static_cast<DWORD>(wszPath.size()),
            wszPath.data()
        );


        //
        // Expand it to full path
        //

        Impl::WindowsPath wszFullPath{};

        dwLength = GetLongPathNameW(
            wszPath.data(),
            wszFullPath.data(),
            static_cast<DWORD>(wszFullPath.size())
        );

        if (dwLength != 0)
        {
            //
            // Convert to engine type.
            //

            result = Impl::NarrowString(wszFullPath.data());

            Storage::Path::Normalize(result);
            Storage::Path::AddDirectorySeparator(result);

        }

        return result;
    }

    BASE_API std::string GetUserSettingsDirectory() noexcept
    {
        std::string result{};

        Impl::WindowsPath wszPath{};

        HRESULT hr = SHGetFolderPathW(
            nullptr,
            CSIDL_LOCAL_APPDATA,
            nullptr,
            SHGFP_TYPE_CURRENT,
            wszPath.data()
        );

        if (SUCCEEDED(hr))
        {
            result = Impl::NarrowString(wszPath.data());

            Storage::Path::Normalize(result);
            Storage::Path::AddDirectorySeparator(result);
        }

        return result;
    }

    BASE_API std::string GetApplicationCommonDataDirectory() noexcept
    {
        std::string result{};

        Impl::WindowsPath wszPath{};

        HRESULT hr = SHGetFolderPathW(
            nullptr,
            CSIDL_COMMON_APPDATA,
            nullptr,
            SHGFP_TYPE_CURRENT,
            wszPath.data()
        );

        if (SUCCEEDED(hr))
        {
            result = Impl::NarrowString(wszPath.data());

            Storage::Path::Normalize(result);
            Storage::Path::AddDirectorySeparator(result);
        }

        return result;
    }

    BASE_API std::string GetUserDomain() noexcept
    {
        std::array<wchar_t, MAX_COMPUTERNAME_LENGTH + 1> wszName{};

        DWORD dwSize = static_cast<DWORD>(wszName.size());

        GetComputerNameW(wszName.data(), &dwSize);

        return Impl::NarrowString(wszName.data());
    }

    BASE_API std::string GetUserName() noexcept
    {
        std::array<wchar_t, UNLEN + 1> wszName{};

        DWORD dwSize = static_cast<DWORD>(wszName.size());

        GetUserNameW(wszName.data(), &dwSize);

        return Impl::NarrowString(wszName.data());
    }

    BASE_API std::string GetSystemVersion() noexcept
    {
        static std::string result{};

        if (result.empty())
        {
            //
            // Get path to kernel32.dll as GetVersion[Ex] was deprecated
            //
            // https://docs.microsoft.com/pl-pl/windows/desktop/api/sysinfoapi/nf-sysinfoapi-getversion
            //

            std::wstring wszPath{};

            UINT uLength = GetSystemDirectoryW(nullptr, 0);

            if (uLength != 0)
            {
                wszPath.resize(uLength - 1);

                GetSystemDirectoryW(wszPath.data(), uLength);

                wszPath += L"\\kernel32.dll";
            }

            if (!wszPath.empty())
            {
                //
                // Get how much memory we need to store version info.
                //

                DWORD dwSize = GetFileVersionInfoSizeW(
                    wszPath.data(),
                    0
                );

                if (dwSize != 0)
                {
                    auto vsVersionInfo = std::make_unique<std::uint8_t[]>(dwSize);


                    //
                    // Load actual version info.
                    //

                    if (GetFileVersionInfoW(
                        wszPath.data(),
                        0,
                        dwSize,
                        vsVersionInfo.get()
                    ) != FALSE)
                    {
                        VS_FIXEDFILEINFO* vsFileVersion{};
                        UINT vsLength{};

                        //
                        // Query for default file version info.
                        //

                        if (VerQueryValueW(
                            vsVersionInfo.get(),
                            L"",
                            reinterpret_cast<LPVOID*>(&vsFileVersion),
                            &vsLength
                        ) != FALSE)
                        {
                            //
                            // Compose final version info.
                            //

                            result = fmt::format("Microsoft Windows NT {}.{}.{}.{}",
                                HIWORD(vsFileVersion->dwProductVersionMS),
                                LOWORD(vsFileVersion->dwProductVersionMS),
                                HIWORD(vsFileVersion->dwProductVersionLS),
                                LOWORD(vsFileVersion->dwProductVersionLS)
                            );
                        }
                    }
                }
            }

            if (result.empty())
            {
                //
                // Version info couldn't be read - store default value in order to not invoke this
                // compilcated code again.
                //

                result = "<unknown>";
            }
        }

        return result;
    }

    BASE_API std::string GetSystemId() noexcept
    {
        // http://stackoverflow.com/questions/99880/generating-a-unique-machine-id

        std::string result{};

        Impl::QueryRegistry(
            HKEY_LOCAL_MACHINE,
            L"Software\\Microsoft\\Cryptography",
            L"MachineGuid",
            result
        );

        return result;
    }

    BASE_API std::string GetDefaultLocale() noexcept
    {
        std::array<wchar_t, LOCALE_NAME_MAX_LENGTH> locale{};

        if (GetUserDefaultLocaleName(&locale[0], static_cast<int>(locale.size())))
        {
            return Impl::NarrowString(std::wstring_view(locale.data(), locale.size()));
        }

        return {};
    }

    BASE_API std::string GetDefaultLanguage() noexcept
    {
        if (Impl::IsSystemVersion(6, 2))
        {
            ULONG languages_count{ 0 };
            ULONG buffer_size{ 0 };

            BOOL result = GetUserPreferredUILanguages(
                MUI_LANGUAGE_NAME,
                &languages_count,
                nullptr,
                &buffer_size
            );

            if (result != FALSE)
            {
                std::wstring wbuffer(buffer_size, '\0');

                result = GetUserPreferredUILanguages(
                    MUI_LANGUAGE_NAME,
                    &languages_count,
                    &wbuffer[0],
                    &buffer_size
                );

                if (result != FALSE)
                {
                    return Impl::NarrowString(wbuffer);
                }
            }
        }

        return GetDefaultLocale();
    }

    BASE_API std::string GetLocalCurrencyCode() noexcept
    {
        return {};
    }

    BASE_API std::string GetLocalCurrencySymbol() noexcept
    {
        return {};
    }

    BASE_API bool HasActiveWifiConnection() noexcept
    {
        return true;
    }

    BASE_API bool Is64BitOperatingSystem() noexcept
    {
#if GRAPHYTE_ARCH_64BIT
        return true;
#else
        using LPFN_ISWOW64PROCESS = BOOL(WINAPI*)(HANDLE, PBOOL);

#pragma warning( push )
#pragma warning( disable: 4191 )	// unsafe conversion from 'type of expression' to 'type required'

        HMODULE const handle = GetModuleHandleW(L"Kernel32.dll");
        
        LPFN_ISWOW64PROCESS const fn_iswow64 = reinterpret_cast<LPFN_ISWOW64PROCESS>(
            GetProcAddress(handle, "IsWow64Process")
        );
        
#pragma warning( pop )

        static BOOL is_wow64 = FALSE;

        if (fn_iswow64 != nullptr)
        {
            if (fn_iswow64(GetCurrentProcess(), &is_wow64) != FALSE)
            {
                is_wow64 = FALSE;
            }
        }

        return is_wow64 != FALSE;
#endif

    }

    BASE_API bool Is64BitProcess() noexcept
    {
#if GRAPHYTE_ARCH_64BIT
        return true;
#else
        return false;
#endif
    }

    BASE_API bool IsMousePresent() noexcept
    {
        return GetSystemMetrics(SM_MOUSEPRESENT) != 0;
    }

    BASE_API bool IsMouseWheelPresent() noexcept
    {
        return GetSystemMetrics(SM_MOUSEWHEELPRESENT) != 0;
    }

    BASE_API bool IsLittleEndian() noexcept
    {
#if GRAPHYTE_ENDIAN_LITTLE
        return true;
#else
        return false;
#endif
    }

    BASE_API void* GetHardwareWindow() noexcept
    {
        return nullptr;
    }

    BASE_API void RestoreSystemUI() noexcept
    {
        while (ShowCursor(TRUE) < 0)
        {
            // do nothing
        }

        ReleaseCapture();

        ClipCursor(nullptr);
    }
}
