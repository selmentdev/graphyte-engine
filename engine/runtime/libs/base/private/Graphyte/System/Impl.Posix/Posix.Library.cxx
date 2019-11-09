#include "Base.pch.hxx"
#include <Graphyte/System/Library.hxx>
#include <Graphyte/Diagnostics.hxx>

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

        return Diagnostics::GetStatusFromErrno(errno);
    }

    void* Library::Resolve(const char* name) const noexcept
    {
        return dlsym(m_Handle.Value, name);
    }
}
