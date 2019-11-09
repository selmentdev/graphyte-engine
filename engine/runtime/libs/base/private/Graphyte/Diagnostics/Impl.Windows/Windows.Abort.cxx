#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/System.hxx>

#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    bool ReportAbort(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept
    {
        if (GetErrorReporting() != ErrorReporting::Interactive)
        {
            return false;
        }

        std::wstring wtitle = System::Impl::WidenString(title);
        std::wstring wcontent = System::Impl::WidenString(content);
        std::wstring wstacktrace = System::Impl::WidenString(stacktrace);

        TASKDIALOGCONFIG config{
            .cbSize                  = sizeof(TASKDIALOGCONFIG),
            .hwndParent              = nullptr,
            .hInstance               = System::Impl::GInstanceHandle,
            .dwFlags                 = TDF_ALLOW_DIALOG_CANCELLATION | TDF_SIZE_TO_CONTENT,
            .dwCommonButtons         = TDCBF_CLOSE_BUTTON,
            .pszWindowTitle          = wtitle.c_str(),
            .pszMainIcon             = TD_ERROR_ICON,
            .pszMainInstruction      = L"Abort",
            .pszContent              = wcontent.c_str(),
            .pszExpandedInformation  = wstacktrace.c_str(),
            .pszExpandedControlText  = L"Hide Stack Trace",
            .pszCollapsedControlText = L"Show Stack Trace",
        };

#if !defined(NDEBUG)

        //
        // Debug builds has additional retry button which surpasses abort.
        //

        config.dwCommonButtons |= TDCBF_RETRY_BUTTON;

#endif

        System::RestoreSystemUI();

        INT result = IDCLOSE;

        if (FAILED(TaskDialogIndirect(&config, &result, nullptr, nullptr)))
        {
            GX_ASSERTF(false, "Cannot present abort dialog");
        }

        return (result == IDRETRY);
    }
}
