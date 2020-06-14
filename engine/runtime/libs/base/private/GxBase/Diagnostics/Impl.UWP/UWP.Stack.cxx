#include <GxBase/Diagnostics.hxx>
#include <GxBase/Span.hxx>

#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics
{
    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames) noexcept
    {
        (void)frames;
        return Status::NotImplemented;
    }

    BASE_API Status GetStackTrace(
        std::vector<StackFrame>& frames,
        [[maybe_unused]] const CONTEXT& context) noexcept
    {
        (void)frames;
        (void)context;
        return Status::NotImplemented;
    }
}
