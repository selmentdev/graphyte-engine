#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include "../Platform.impl.hxx"

namespace Graphyte::System
{
    BASE_API MessageDialogResult ShowMessageDialog(
        [[maybe_unused]] std::string_view title,
        [[maybe_unused]] std::string_view message,
        [[maybe_unused]] MessageDialogType type,
        [[maybe_unused]] MessageDialogImage image) noexcept
    {
        return MessageDialogResult::None;
    }
}
