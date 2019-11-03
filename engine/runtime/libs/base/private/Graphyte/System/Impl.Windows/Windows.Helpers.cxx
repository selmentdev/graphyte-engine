#include "Base.pch.hxx"
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::System::Impl
{
    BASE_API HINSTANCE GInstanceHandle{};

    BASE_API bool IsSystemVersion(
        uint32_t major,
        uint32_t minor
    ) noexcept
    {
        OSVERSIONINFOEXW osie{
            .dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW),
            .dwMajorVersion = static_cast<DWORD>(major),
            .dwMinorVersion = static_cast<DWORD>(minor),
        };

        ULONGLONG conditionMask = 0;
        conditionMask = VerSetConditionMask(conditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
        conditionMask = VerSetConditionMask(conditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);

        return VerifyVersionInfoW(&osie, VER_MAJORVERSION | VER_MINORVERSION, conditionMask) != FALSE;
    }

    BASE_API bool QueryRegistry(
        HKEY key,
        const wchar_t* subkey,
        const wchar_t* name,
        std::string& result
    ) noexcept
    {
        GX_ASSERT(subkey != nullptr);
        GX_ASSERT(name != nullptr);

        bool succeeded = false;

        const uint32_t key_flags[] = {
            KEY_WOW64_32KEY,
            KEY_WOW64_64KEY
        };

        for (auto const key_flag : key_flags)
        {
            if (succeeded)
            {
                continue;
            }

            HKEY current = nullptr;

            if (RegOpenKeyExW(key, subkey, 0, KEY_READ | key_flag, &current) == ERROR_SUCCESS)
            {
                DWORD dw_size = 0;

                if (RegQueryValueExW(current, name, nullptr, nullptr, nullptr, &dw_size) == ERROR_SUCCESS)
                {
                    size_t const chars_count = static_cast<size_t>(dw_size / sizeof(wchar_t));

                    if (chars_count != 0)
                    {
                        //
                        // Storage for key value.
                        //
                        std::wstring data(chars_count - 1, L' ');

                        if (RegQueryValueExW(current, name, nullptr, nullptr, reinterpret_cast<LPBYTE>(data.data()), &dw_size) == ERROR_SUCCESS)
                        {
                            result = Impl::ConvertString(data);
                            succeeded = true;
                        }
                    }
                }

                RegCloseKey(current);
            }
        }

        return succeeded;
    }

    BASE_API std::string ConvertString(
        std::wstring_view value
    ) noexcept
    {
        std::string result{};

        if (!value.empty())
        {
            int const length = static_cast<int>(value.length()); // XXX: Check for overflow

            int const converted1 = WideCharToMultiByte(CP_UTF8, 0, &value[0], length, nullptr, 0, nullptr, nullptr);

            result.resize(static_cast<size_t>(converted1), '\0');

            int const converted2 = WideCharToMultiByte(CP_UTF8, 0, &value[0], length, &result[0], converted1, nullptr, nullptr);

            GX_ASSERT(converted1 == converted2);
        }

        return result;
    }

    BASE_API std::wstring ConvertString(
        std::string_view value
    ) noexcept
    {
        std::wstring result{};

        if (!value.empty())
        {
            int const length = static_cast<int>(value.length()); // XXX: Check for overflow

            int const converted1 = MultiByteToWideChar(CP_UTF8, 0, &value[0], length, nullptr, 0);

            result.resize(static_cast<size_t>(converted1), L'\0');

            int const converted2 = MultiByteToWideChar(CP_UTF8, 0, &value[0], length, &result[0], converted1);

            GX_ASSERT(converted1 == converted2);
        }

        return result;
    }

    BASE_API size_t ConvertString(
        wchar_t* buffer,
        size_t buffer_size,
        std::string_view value
    ) noexcept
    {
        size_t const result = static_cast<size_t>(MultiByteToWideChar(
            CP_UTF8,
            0,
            value.data(),
            static_cast<int>(value.length()),
            buffer,
            static_cast<int>(buffer_size)
        ));

        return result;
    }

    BASE_API size_t ConvertString(
        char* buffer,
        size_t buffer_size,
        std::wstring_view value
    ) noexcept
    {
        size_t const result = static_cast<size_t>(WideCharToMultiByte(
            CP_UTF8,
            0,
            value.data(),
            static_cast<int>(value.length()),
            buffer,
            static_cast<int>(buffer_size),
            nullptr,
            nullptr
        ));

        return result;
    }

    BASE_API bool ConvertPath(
        WindowsPath& result,
        std::string_view value
    ) noexcept
    {
        int const length = static_cast<int>(value.length()); // XXX: Check for overflow

        return MultiByteToWideChar(CP_UTF8, 0, value.data(), length, result.data(), static_cast<int>(result.size())) != 0;
    }
}
