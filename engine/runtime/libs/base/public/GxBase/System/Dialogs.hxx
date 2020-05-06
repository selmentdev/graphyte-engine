#pragma once
#include <gxBase/Base.module.hxx>
#include <gxBase/Span.hxx>
#include <gxBase/Status.hxx>

namespace Graphyte::System
{
    struct FileDialogFilter final
    {
        std::string_view Display;
        std::string_view Filter;
    };

    BASE_API Status OpenFile(
        std::string& out_path,
        notstd::span<FileDialogFilter> filters = {},
        std::string_view title = {}
    ) noexcept;

    BASE_API Status OpenFile(
        std::vector<std::string>& out_paths,
        notstd::span<FileDialogFilter> filters = {},
        std::string_view title = {}
    ) noexcept;

    BASE_API Status SaveFile(
        std::string& out_path,
        notstd::span<FileDialogFilter> filters = {},
        std::string_view title = {}
    ) noexcept;
}
