#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte::System::Impl
{
    BASE_API HINSTANCE g_InstanceHandle{};

    BASE_API bool IsSystemVersion(
        [[maybe_unused]] uint32_t major,
        [[maybe_unused]] uint32_t minor) noexcept
    {
        return false;
    }

    BASE_API bool QueryRegistry(
        [[maybe_unused]] HKEY key,
        [[maybe_unused]] const wchar_t* subkey,
        [[maybe_unused]] const wchar_t* name,
        [[maybe_unused]] std::string& result) noexcept
    {
        return false;
    }

    BASE_API std::string NarrowString(
        std::wstring_view value) noexcept
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

    BASE_API std::wstring WidenString(
        std::string_view value) noexcept
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

    BASE_API size_t NarrowString(
        char* buffer,
        size_t buffer_size,
        std::wstring_view value) noexcept
    {
        size_t const result = static_cast<size_t>(WideCharToMultiByte(
            CP_UTF8,
            0,
            value.data(),
            static_cast<int>(value.length()),
            buffer,
            static_cast<int>(buffer_size),
            nullptr,
            nullptr));

        return result;
    }

    BASE_API size_t WidenString(
        wchar_t* buffer,
        size_t buffer_size,
        std::string_view value) noexcept
    {
        size_t const result = static_cast<size_t>(MultiByteToWideChar(
            CP_UTF8,
            0,
            value.data(),
            static_cast<int>(value.length()),
            buffer,
            static_cast<int>(buffer_size)));

        return result;
    }

    BASE_API bool WidenStringPath(
        WindowsPath& result,
        std::string_view value) noexcept
    {
        int const length = static_cast<int>(value.length()); // XXX: Check for overflow

        return MultiByteToWideChar(CP_UTF8, 0, value.data(), length, result.data(), static_cast<int>(result.size())) != 0;
    }
}
