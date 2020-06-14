#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>

#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    bool ReportAbort(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace) noexcept
    {
        (void)title;
        (void)content;
        (void)stacktrace;
        return true;
    }
}
