#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>

namespace Graphyte::Diagnostics
{
    BASE_API std::vector<StackFrame> GetStackTrace() noexcept
    {
        GX_ASSERT_NOT_IMPLEMENTED();
        return {};
    }
}
