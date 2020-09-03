#include <GxBase/System/Library.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>

namespace Graphyte::System
{
    Status Library::Load(std::string_view path) noexcept
    {
        System::Impl::WindowsPath wpath{};
        if (System::Impl::WidenStringPath(wpath, path))
        {
            HMODULE const native = LoadLibraryExW(wpath.data(), nullptr, 0);

            if (native != nullptr)
            {
                m_Handle = { native };
                return Status::Success;
            }

            m_Handle = {};

            return Diagnostics::GetStatusFromSystemError();
        }

        return Status::InvalidArgument;
    }

    Status Library::Unload() noexcept
    {
        if (!m_Handle.IsValid())
        {
            return Status::NotFound;
        }

        if (FreeLibrary(m_Handle.Value) != FALSE)
        {
            m_Handle = {};
            return Status::Success;
        }

        return Diagnostics::GetStatusFromSystemError();
    }

    void* Library::Resolve(const char* name) const noexcept
    {
        return reinterpret_cast<void*>(GetProcAddress(m_Handle.Value, name));
    }
}
