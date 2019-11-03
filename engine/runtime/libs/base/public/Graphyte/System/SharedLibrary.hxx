#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Status.hxx>

namespace Graphyte::System
{
    struct SharedLibraryHandle final
    {
#if GRAPHYTE_PLATFORM_WINDOWS
        HMODULE Value;
#elif GRAPHYTE_PLATFORM_POSIX
        void* Value;
#endif

        bool IsValid() const noexcept
        {
            return this->Value != nullptr;
        }
    };

    struct BASE_API SharedLibrary final
    {
        static Status Load(
            SharedLibraryHandle& handle,
            const char* path
        ) noexcept;

        static Status Unload(
            SharedLibraryHandle handle
        ) noexcept;

        static void* GetSymbol(
            SharedLibraryHandle handle,
            const char* name
        ) noexcept;

        template <typename T>
        static T Get(
            SharedLibraryHandle handle,
            const char* name
        ) noexcept
        {
            return reinterpret_cast<T>(GetSymbol(handle, name));
        }
    };
}
