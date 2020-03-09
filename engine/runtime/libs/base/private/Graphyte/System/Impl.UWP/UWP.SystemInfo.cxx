#include <Graphyte/System.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/Storage/Path.hxx>

#include <ShlObj.h>
#include <IPHlpApi.h>

namespace Graphyte::System
{
    BASE_API std::string GetUserDirectory() noexcept
    {
        return {};
    }

    BASE_API std::string GetUserDocumentsDirectory() noexcept
    {
        return {};
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
        return {};
    }

    BASE_API std::string GetApplicationCommonDataDirectory() noexcept
    {
        return {};
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
        return {};
    }

    BASE_API std::string GetSystemVersion() noexcept
    {
        return {};
    }

    BASE_API std::string GetSystemId() noexcept
    {
        return {};
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
        return {};
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
        return {};
    }

    BASE_API bool IsMouseWheelPresent() noexcept
    {
        return {};
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
    }
}
