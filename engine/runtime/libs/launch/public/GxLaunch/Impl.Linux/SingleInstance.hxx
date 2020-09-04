// =================================================================================================
// Single instance support - currently unavailable on this platform

namespace Graphyte::Launch::Impl
{
    constexpr void SingleInstance_Acquire() noexcept
    {
        // Empty implementation - removed by compiler
    }

    constexpr void SingleInstance_Release() noexcept
    {
        // Empty implementation - removed by compiler
    }
}
