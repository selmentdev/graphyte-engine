#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>

#include "../Diagnostics.Impl.hxx"

#include <CommCtrl.h>

namespace Graphyte::Diagnostics::Impl
{
    AssertResult ReportAssertion(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace) noexcept
    {
        if (GetErrorReporting() != ErrorReporting::Interactive)
        {
            return AssertResult::Abort;
        }

        std::array<TASKDIALOG_BUTTON, 4> buttons{
            {
                {
                    .nButtonID     = static_cast<int>(AssertResult::Abort),
                    .pszButtonText = L"&Abort",
                },
                {
                    .nButtonID     = static_cast<int>(AssertResult::Retry),
                    .pszButtonText = L"&Retry",
                },
                {
                    .nButtonID     = static_cast<int>(AssertResult::Ignore),
                    .pszButtonText = L"&Ignore",
                },
                {
                    .nButtonID     = static_cast<int>(AssertResult::IgnoreAlways),
                    .pszButtonText = L"I&gnore Always",
                },
            }
        };

        std::wstring wtitle   = System::Impl::WidenString(title);
        std::wstring wcontent = System::Impl::WidenString(content);

#if GX_ENABLE_STACKTRACE
        std::wstring wstacktrace = System::Impl::WidenString(stacktrace);
#else
        (void)stacktrace;
#endif

        TASKDIALOGCONFIG config
        {
            .cbSize             = sizeof(TASKDIALOGCONFIG),
            .hwndParent         = nullptr,
            .hInstance          = System::Impl::g_InstanceHandle,
            .dwFlags            = TDF_ALLOW_DIALOG_CANCELLATION,
            .dwCommonButtons    = 0,
            .pszWindowTitle     = wtitle.c_str(),
            .pszMainIcon        = TD_ERROR_ICON,
            .pszMainInstruction = L"Assertion failed",
            .pszContent         = wcontent.c_str(),
            .cButtons           = static_cast<UINT>(std::size(buttons)),
            .pButtons           = std::data(buttons),
            .nDefaultButton     = static_cast<int>(AssertResult::Retry),

#if GX_ENABLE_STACKTRACE
            .pszExpandedInformation  = wstacktrace.c_str(),
            .pszExpandedControlText  = L"Hide Stack Trace",
            .pszCollapsedControlText = L"Show Stack Trace",
#else
            .pszExpandedInformation  = nullptr,
            .pszExpandedControlText  = nullptr,
            .pszCollapsedControlText = nullptr,
#endif
        };

        System::RestoreSystemUI();

        INT result{};

        if (FAILED(TaskDialogIndirect(&config, &result, nullptr, nullptr)))
        {
            return AssertResult::Ignore;
        }

        return static_cast<AssertResult>(result);
    }
}
