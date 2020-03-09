#include <Graphyte/System/Dialogs.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>

#pragma warning(push)
#pragma warning(disable : 4715)

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/windows.Storage.Pickers.h>

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
        //winrt::Windows::Storage::Pickers::FileOpenPicker picker{};
        //picker.FileTypeFilter().Append(L".txt");
        //auto asc = picker.PickMultipleFilesAsync();
        //auto result = asc.get();
        //for (auto item : result)
        //{
        //    out_paths.emplace_back(Graphyte::System::Impl::NarrowString(item.Path().c_str()));
        //}



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

#pragma warning(pop)
