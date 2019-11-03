#include "Base.pch.hxx"
#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    AssertResult ReportAssertion(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept
    {
        GX_ASSERT_NOT_IMPLEMENTED();
        return AssertResult::Abort;
    }
}
