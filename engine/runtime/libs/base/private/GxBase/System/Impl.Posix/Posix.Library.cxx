#include <GxBase/System.hxx>
#include <GxBase/System/Library.hxx>
#include <GxBase/Diagnostics.hxx>

#include <dlfcn.h>

namespace Graphyte::System
{
    Status Library::Load(std::string_view path) noexcept
    {
        std::string const spath{ path };

        void* const native = dlopen(spath.c_str(), RTLD_LAZY);

        if (native != nullptr)
        {
            m_Handle = { native };
            return Status::Success;
        }

        m_Handle = {};
        return Diagnostics::GetStatusFromErrno(errno);
    }

    Status Library::Unload() noexcept
    {
        if (!m_Handle.IsValid())
        {
            return Status::NotFound;
        }

        if (dlclose(m_Handle.Value) == 0)
        {
            return Status::Success;
        }

        auto const error = errno;
        GX_LOG(LogPlatform, Error, "Failed to unload library. Errno = {}, `{}`",
            error,
            dlerror());

        return Diagnostics::GetStatusFromErrno(error);
    }

    void* Library::Resolve(const char* name) const noexcept
    {
        return dlsym(m_Handle.Value, name);
    }
}
