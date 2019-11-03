#include "Base.pch.hxx"
#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    bool ReportAbort(
        [[maybe_unused]] std::string_view title,
        [[maybe_unused]] std::string_view content,
        [[maybe_unused]] std::string_view stacktrace
    ) noexcept
    {
        GX_ASSERT_NOT_IMPLEMENTED();
        return false;
    }
}
