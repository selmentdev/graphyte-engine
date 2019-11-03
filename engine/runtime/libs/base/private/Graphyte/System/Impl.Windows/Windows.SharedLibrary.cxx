#include "Base.pch.hxx"
#include <Graphyte/System/SharedLibrary.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::System
{
    Status SharedLibrary::Load(
        SharedLibraryHandle& handle,
        const char* path
    ) noexcept
    {
        System::Impl::WindowsPath wpath{};
        System::Impl::ConvertPath(wpath, path);

        HMODULE native = LoadLibraryW(wpath.data());

        if (native != nullptr)
        {
            handle.Value = native;
            return Status::Success;
        }

        handle.Value = nullptr;

        return Diagnostics::GetStatusFromSystemError();
    }

    Status SharedLibrary::Unload(
        SharedLibraryHandle handle
    ) noexcept
    {
        if (!handle.IsValid())
        {
            return Status::InvalidArgument;
        }

        if (FreeLibrary(handle.Value) != FALSE)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    void* SharedLibrary::GetSymbol(
        SharedLibraryHandle handle,
        const char* name
    ) noexcept
    {
        return reinterpret_cast<void*>(GetProcAddress(handle.Value, name));
    }
}
