#pragma once
#include <GxBase/Base.module.hxx>

#if !(GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP)
#error "This header is usable only for Windows platform"
#endif

namespace Graphyte::System::Impl
{
    constexpr const ULONG_PTR IDI_MAIN_ICON = 2137;

    extern BASE_API HINSTANCE g_InstanceHandle;

    [[nodiscard]] extern BASE_API bool IsSystemVersion(
        uint32_t major,
        uint32_t minor) noexcept;

    extern BASE_API bool QueryRegistry(
        HKEY key,
        const wchar_t* subkey,
        const wchar_t* name,
        std::string& result) noexcept;

    [[nodiscard]] extern BASE_API std::string NarrowString(
        std::wstring_view value) noexcept;

    [[nodiscard]] extern BASE_API std::wstring WidenString(
        std::string_view value) noexcept;

    [[nodiscard]] extern BASE_API size_t NarrowString(
        char* buffer,
        size_t buffer_size,
        std::wstring_view value) noexcept;

    [[nodiscard]] extern BASE_API size_t WidenString(
        wchar_t* buffer,
        size_t buffer_size,
        std::string_view value) noexcept;

    using WindowsPath = std::array<wchar_t, MAX_PATH>;

    [[nodiscard]] extern BASE_API bool WidenStringPath(
        WindowsPath& result,
        std::string_view value) noexcept;
}
