#include <GxBase/System.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include "../Platform.impl.hxx"

#include <CommCtrl.h>

namespace Graphyte::System::Impl
{
    static const TASKDIALOG_BUTTON g_MessageDialogButtonOk{ IDOK, L"&OK" };
    static const TASKDIALOG_BUTTON g_MessageDialogButtonCancel{ IDCANCEL, L"&Cancel" };
    static const TASKDIALOG_BUTTON g_MessageDialogButtonYes{ IDYES, L"&Yes" };
    static const TASKDIALOG_BUTTON g_MessageDialogButtonNo{ IDNO, L"&No" };
    static const TASKDIALOG_BUTTON g_MessageDialogButtonTry{ IDTRYAGAIN, L"&Try" };
    static const TASKDIALOG_BUTTON g_MessageDialogButtonContinue{ IDCONTINUE, L"&Continue" };
}

namespace Graphyte::System
{
    BASE_API MessageDialogResult ShowMessageDialog(
        std::string_view title,
        std::string_view message,
        MessageDialogType type,
        MessageDialogImage image) noexcept
    {
        std::wstring const wszTitle   = System::Impl::WidenString(title);
        std::wstring const wszMessage = System::Impl::WidenString(message);

        std::array<TASKDIALOG_BUTTON, 3> buttons{};
        UINT buttonsCount = 0;

        TASKDIALOGCONFIG config{
            .cbSize             = sizeof(config),
            .hwndParent         = nullptr,
            .hInstance          = System::Impl::g_InstanceHandle,
            .dwFlags            = TDF_ALLOW_DIALOG_CANCELLATION,
            .dwCommonButtons    = 0,
            .pszWindowTitle     = wszTitle.c_str(),
            .pszMainInstruction = wszTitle.c_str(),
            .pszContent         = wszMessage.c_str(),
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
            default:
                GX_ASSERTF(false, "Invalid button type for Message Dialog. Defaulting to [OK]");
                [[fallthrough]];

            case MessageDialogType::Ok:
            {
                buttons[0] = Impl::g_MessageDialogButtonOk;
                buttonsCount = 1;
                break;
            }
            case MessageDialogType::OkCancel:
            {
                buttons[0] = Impl::g_MessageDialogButtonOk;
                buttons[1] = Impl::g_MessageDialogButtonCancel;
                buttonsCount = 2;
                break;
            }
            case MessageDialogType::YesNo:
            {
                buttons[0] = Impl::g_MessageDialogButtonYes;
                buttons[1] = Impl::g_MessageDialogButtonNo;
                buttonsCount = 2;
                break;
            }
            case MessageDialogType::YesNoCancel:
            {
                buttons[0] = Impl::g_MessageDialogButtonYes;
                buttons[1] = Impl::g_MessageDialogButtonNo;
                buttons[2] = Impl::g_MessageDialogButtonCancel;
                buttonsCount = 3;
                break;
            }
            case MessageDialogType::CancelTryContinue:
            {
                buttons[0] = Impl::g_MessageDialogButtonCancel;
                buttons[1] = Impl::g_MessageDialogButtonTry;
                buttons[2] = Impl::g_MessageDialogButtonContinue;
                buttonsCount = 3;
                break;
            }
        }


        config.cButtons       = static_cast<UINT>(buttonsCount);
        config.pButtons       = std::data(buttons);
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
