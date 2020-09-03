#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>

namespace Graphyte::System
{
    struct FileDialogFilter final
    {
        std::string_view Display;
        std::string_view Filter;
    };

    BASE_API Status OpenFile(
        std::string& out_path,
        std::span<FileDialogFilter> filters = {},
        std::string_view title              = {}) noexcept;

    BASE_API Status OpenFile(
        std::vector<std::string>& out_paths,
        std::span<FileDialogFilter> filters = {},
        std::string_view title              = {}) noexcept;

    BASE_API Status SaveFile(
        std::string& out_path,
        std::span<FileDialogFilter> filters = {},
        std::string_view title              = {}) noexcept;
}
