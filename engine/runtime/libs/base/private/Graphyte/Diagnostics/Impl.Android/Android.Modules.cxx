#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Diagnostics
{
    BASE_API std::vector<std::string> GetModules() noexcept
    {
        GX_ASSERT_NOT_IMPLEMENTED();
        return {};
    }
}
