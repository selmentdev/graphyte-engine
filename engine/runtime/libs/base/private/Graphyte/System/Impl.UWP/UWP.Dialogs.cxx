#include <Graphyte/System/Dialogs.hxx>

namespace Graphyte::System
{
    BASE_API Status OpenFile(
        std::string& out_path,
        notstd::span<FileDialogFilter> filters,
        std::string_view title
    ) noexcept
    {
        (void)out_path;
        (void)filters;
        (void)title;
        return Status::NotImplemented;
    }

    BASE_API Status OpenFile(
        std::vector<std::string>& out_paths,
        notstd::span<FileDialogFilter> filters,
        std::string_view title
    ) noexcept
    {
        (void)out_paths;
        (void)filters;
        (void)title;
        return Status::NotImplemented;
    }

    BASE_API Status SaveFile(
        std::string& out_path,
        notstd::span<FileDialogFilter> filters,
        std::string_view title
    ) noexcept
    {
        (void)out_path;
        (void)filters;
        (void)title;
        return Status::NotImplemented;
    }
}
