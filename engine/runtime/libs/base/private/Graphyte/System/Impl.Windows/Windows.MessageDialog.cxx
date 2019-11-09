#include "Base.pch.hxx"
#include <Graphyte/System.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include "../Platform.impl.hxx"

namespace Graphyte::System::Impl
{
    static const TASKDIALOG_BUTTON GMessageDialogButtonOk         { IDOK,       L"&OK" };
    static const TASKDIALOG_BUTTON GMessageDialogButtonCancel     { IDCANCEL,   L"&Cancel" };
    static const TASKDIALOG_BUTTON GMessageDialogButtonYes        { IDYES,      L"&Yes" };
    static const TASKDIALOG_BUTTON GMessageDialogButtonNo         { IDNO,       L"&No" };
    static const TASKDIALOG_BUTTON GMessageDialogButtonTry        { IDTRYAGAIN, L"&Try" };
    static const TASKDIALOG_BUTTON GMessageDialogButtonContinue   { IDCONTINUE, L"&Continue" };
}

namespace Graphyte::System
{
    BASE_API MessageDialogResult ShowMessageDialog(
        std::string_view title,
        std::string_view message,
        MessageDialogType type,
        MessageDialogImage image
    ) noexcept
    {
        std::wstring const wszTitle = System::Impl::WidenString(title);
        std::wstring const wszMessage = System::Impl::WidenString(message);

        std::vector<TASKDIALOG_BUTTON> buttons{};

        TASKDIALOGCONFIG config{
            .cbSize = sizeof(config),
            .hwndParent = nullptr,
            .hInstance = System::Impl::GInstanceHandle,
            .dwFlags = TDF_ALLOW_DIALOG_CANCELLATION,
            .dwCommonButtons = 0,
            .pszWindowTitle = wszTitle.c_str(),
            .pszMainInstruction = wszTitle.c_str(),
            .pszContent = wszMessage.c_str(),
        };

        switch (image)
        {
        case MessageDialogImage::None:
            {
                break;
            }
        case MessageDialogImage::Error:
            {
                config.pszMainIcon = TD_ERROR_ICON;
                break;
            }
        case MessageDialogImage::Warning:
            {
                config.pszMainIcon = TD_WARNING_ICON;
                break;
            }
        default:
        case MessageDialogImage::Information:
            {
                config.pszMainIcon = TD_INFORMATION_ICON;
                break;
            }
        }

        switch (type)
        {
        case MessageDialogType::Ok:
            {
                buttons.push_back(Impl::GMessageDialogButtonOk);
                break;
            }
        case MessageDialogType::OkCancel:
            {
                buttons.push_back(Impl::GMessageDialogButtonOk);
                buttons.push_back(Impl::GMessageDialogButtonCancel);
                break;
            }
        case MessageDialogType::YesNo:
            {
                buttons.push_back(Impl::GMessageDialogButtonYes);
                buttons.push_back(Impl::GMessageDialogButtonNo);
                break;
            }
        case MessageDialogType::YesNoCancel:
            {
                buttons.push_back(Impl::GMessageDialogButtonYes);
                buttons.push_back(Impl::GMessageDialogButtonNo);
                buttons.push_back(Impl::GMessageDialogButtonCancel);
                break;
            }
        case MessageDialogType::CancelTryContinue:
            {
                buttons.push_back(Impl::GMessageDialogButtonCancel);
                buttons.push_back(Impl::GMessageDialogButtonTry);
                buttons.push_back(Impl::GMessageDialogButtonContinue);
                break;
            }
        default:
            {
                break;
            }
        }


        config.cButtons = static_cast<UINT>(std::size(buttons));
        config.pButtons = std::data(buttons);
        config.nDefaultButton = buttons[0].nButtonID;

        INT result{};

        if (HRESULT hr = TaskDialogIndirect(&config, &result, nullptr, nullptr); SUCCEEDED(hr))
        {
            switch (result)
            {
            case IDOK:
                {
                    return MessageDialogResult::Ok;
                }
            case IDYES:
                {
                    return MessageDialogResult::Yes;
                }
            case IDNO:
                {
                    return MessageDialogResult::No;
                }
            case IDCANCEL:
                {
                    return MessageDialogResult::Cancel;
                }
            case IDTRYAGAIN:
                {
                    return MessageDialogResult::Try;
                }
            case IDCONTINUE:
                {
                    return MessageDialogResult::Continue;
                }
            default:
                {
                    GX_ASSERTF(false, "Invalid result from message box: {}", result);
                    return MessageDialogResult::None;
                }
            }
        }
        else
        {
            GX_ASSERTF(false, "Failed to show message dialog: {}", Diagnostics::GetMessageFromHRESULT(hr));
            return MessageDialogResult::None;
        }
    }
}
