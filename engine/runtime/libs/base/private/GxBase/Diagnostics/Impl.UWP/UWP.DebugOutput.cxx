#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    void DebugOutput(
        [[maybe_unused]] LogLevel level,
        const char* text) noexcept
    {
        OutputDebugStringA(text);
    }
}
