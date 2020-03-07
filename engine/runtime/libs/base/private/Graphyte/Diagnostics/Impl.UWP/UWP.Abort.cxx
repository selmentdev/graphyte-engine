#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/System.hxx>

#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    bool ReportAbort(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept
    {
        (void)title;
        (void)content;
        (void)stacktrace;
        return false;
    }
}
