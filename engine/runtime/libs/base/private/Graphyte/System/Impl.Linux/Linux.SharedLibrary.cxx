#include "Base.pch.hxx"
#include <Graphyte/Platform/SharedLibrary.hxx>
#include <Graphyte/Diagnostics.hxx>

#include <dlfcn.h>

namespace Graphyte::Platform
{
    Status SharedLibrary::Load(
        SharedLibraryHandle& handle,
        const char* path
    ) noexcept
    {
        auto native = dlopen(path, RTLD_LAZY);

        if (native != nullptr)
        {
            handle.Value = native;
            return Status::Success;
        }

        handle.Value = nullptr;

        return Diagnostics::GetStatusFromErrno(errno);
    }
    
    Status SharedLibrary::Unload(
        SharedLibraryHandle handle
    ) noexcept
    {
        if (handle.Value == nullptr)
        {
            return Status::NotFound;
        }

        if (dlclose(handle.Value) == 0)
        {
            return Status::Success;
        }

        return Diagnostics::GetStatusFromErrno(errno);
    }

    void* SharedLibrary::GetSymbol(
        SharedLibraryHandle handle,
        const char* name
    ) noexcept
    {
        return dlsym(handle.Value, name);
    }
}
