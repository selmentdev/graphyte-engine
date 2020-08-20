#include <GxBase/System/Dialogs.hxx>

namespace Graphyte::System
{
    BASE_API Status OpenFile(
        [[maybe_unused]] std::string& out_path,
        [[maybe_unused]] std::span<FileDialogFilter> filters,
        [[maybe_unused]] std::string_view title) noexcept
    {
        return Status::NotImplemented;
    }

    BASE_API Status OpenFile(
        [[maybe_unused]] std::vector<std::string>& out_paths,
        [[maybe_unused]] std::span<FileDialogFilter> filters,
        [[maybe_unused]] std::string_view title) noexcept
    {
        return Status::NotImplemented;
    }

    BASE_API Status SaveFile(
        [[maybe_unused]] std::string& out_path,
        [[maybe_unused]] std::span<FileDialogFilter> filters,
        [[maybe_unused]] std::string_view title) noexcept
    {
        return Status::NotImplemented;
    }
}
