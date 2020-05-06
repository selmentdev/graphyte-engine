#include <GxBase/System/Dialogs.hxx>

#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <wrl/client.h>
#include <shobjidl.h>

namespace Graphyte::System::Impl
{
    HRESULT SetDialogFilters(
        IFileDialog& dialog,
        notstd::span<FileDialogFilter> filters
    ) noexcept
    {
        std::vector<std::pair<std::wstring, std::wstring>> wfilters{};
        wfilters.reserve(filters.size());

        for (auto const& filter : filters)
        {
            wfilters.emplace_back(
                Graphyte::System::Impl::WidenString(filter.Display),
                Graphyte::System::Impl::WidenString(filter.Filter)
            );
        }

        std::vector<COMDLG_FILTERSPEC> dialog_filters{};
        dialog_filters.reserve(wfilters.size());

        for (auto const& filter : wfilters)
        {
            dialog_filters.emplace_back(
                COMDLG_FILTERSPEC{
                    .pszName = filter.first.c_str(),
                    .pszSpec = filter.second.c_str(),
                }
            );
        }

        return dialog.SetFileTypes(
            static_cast<UINT>(dialog_filters.size()),
            dialog_filters.data()
        );
    }

    HRESULT GetResult(
        IFileDialog& dialog,
        std::string& out_path
    ) noexcept
    {
        Microsoft::WRL::ComPtr<IShellItem> item{};

        HRESULT hr = dialog.GetResult(item.GetAddressOf());

        wchar_t* wpath{};

        if (SUCCEEDED(hr))
        {
            hr = item->GetDisplayName(SIGDN_FILESYSPATH, &wpath);

            out_path = Impl::NarrowString(wpath);
            CoTaskMemFree(wpath);
        }
        else
        {
            out_path.clear();
        }

        return hr;
    }

    HRESULT GetResult(
        IFileOpenDialog& dialog,
        std::vector<std::string>& out_paths
    ) noexcept
    {
        Microsoft::WRL::ComPtr<IShellItemArray> items{};
        HRESULT hr = dialog.GetResults(items.GetAddressOf());

        DWORD dwCount{};

        if (SUCCEEDED(hr))
        {
            hr = items->GetCount(&dwCount);
        }

        if (SUCCEEDED(hr))
        {
            out_paths.reserve(hr);
        }

        for (DWORD i = 0; i < dwCount; ++i)
        {
            Microsoft::WRL::ComPtr<IShellItem> item{};
            wchar_t* wpath{};

            hr = items->GetItemAt(i, item.GetAddressOf());

            if (SUCCEEDED(hr))
            {
                hr = item->GetDisplayName(SIGDN_FILESYSPATH, &wpath);
                out_paths.emplace_back(Impl::NarrowString(wpath));

                CoTaskMemFree(wpath);
            }
            else
            {
                break;
            }
        }

        if (FAILED(hr))
        {
            out_paths.clear();
        }

        return hr;
    }
}

namespace Graphyte::System
{
    BASE_API Status OpenFile(
        std::string& out_path,
        notstd::span<FileDialogFilter> filters,
        std::string_view title
    ) noexcept
    {
        Microsoft::WRL::ComPtr<IFileOpenDialog> dialog{};

        HRESULT hr = CoCreateInstance(
            CLSID_FileOpenDialog,
            nullptr,
            CLSCTX_ALL,
            IID_IFileOpenDialog,
            (void**)dialog.GetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            hr = Impl::SetDialogFilters(*dialog.Get(), filters);
        }

        if (SUCCEEDED(hr) && !title.empty())
        {
            hr = dialog->SetTitle(Impl::WidenString(title).c_str());
        }

        if (SUCCEEDED(hr))
        {
            hr = dialog->Show(nullptr);
        }

        hr = Impl::GetResult(*dialog.Get(), out_path);

        return SUCCEEDED(hr)
            ? Status::Success
            : Status::Failure;
    }

    BASE_API Status OpenFile(
        std::vector<std::string>& out_paths,
        notstd::span<FileDialogFilter> filters,
        std::string_view title
    ) noexcept
    {
        Microsoft::WRL::ComPtr<IFileOpenDialog> dialog{};
        HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, (void**)dialog.GetAddressOf());

        if (SUCCEEDED(hr))
        {
            hr = Impl::SetDialogFilters(*dialog.Get(), filters);
        }

        if (SUCCEEDED(hr) && !title.empty())
        {
            hr = dialog->SetTitle(Impl::WidenString(title).c_str());
        }

        if (SUCCEEDED(hr))
        {
            FILEOPENDIALOGOPTIONS options{};
            hr = dialog->GetOptions(&options);

            if (SUCCEEDED(hr))
            {
                options |= FOS_ALLOWMULTISELECT;
                hr = dialog->SetOptions(options);
            }
        }

        if (SUCCEEDED(hr))
        {
            hr = dialog->Show(nullptr);
        }

        if (SUCCEEDED(hr))
        {
            hr = Impl::GetResult(*dialog.Get(), out_paths);
        }

        return SUCCEEDED(hr)
            ? Status::Success
            : Status::Failure;
    }

    BASE_API Status SaveFile(
        std::string& out_path,
        notstd::span<FileDialogFilter> filters,
        std::string_view title
    ) noexcept
    {
        Microsoft::WRL::ComPtr<IFileSaveDialog> dialog{};

        HRESULT hr = CoCreateInstance(
            CLSID_FileSaveDialog,
            nullptr,
            CLSCTX_ALL,
            IID_IFileSaveDialog,
            (void**)dialog.GetAddressOf()
        );

        if (SUCCEEDED(hr))
        {
            hr = Impl::SetDialogFilters(*dialog.Get(), filters);
        }

        if (SUCCEEDED(hr) && !title.empty())
        {
            hr = dialog->SetTitle(Impl::WidenString(title).c_str());
        }

        if (SUCCEEDED(hr))
        {
            hr = dialog->Show(nullptr);
        }

        hr = Impl::GetResult(*dialog.Get(), out_path);

        return SUCCEEDED(hr)
            ? Status::Success
            : Status::Failure;
    }
}
