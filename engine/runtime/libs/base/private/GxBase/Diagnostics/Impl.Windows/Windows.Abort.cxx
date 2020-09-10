#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>

#include <CommCtrl.h>
#include "../Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    bool ReportAbort(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace) noexcept
    {
        if (GetErrorReporting() != ErrorReporting::Interactive)
        {
            return false;
        }

        std::wstring wtitle      = System::Impl::WidenString(title);
        std::wstring wcontent    = System::Impl::WidenString(content);

#if GX_ENABLE_STACKTRACE
        std::wstring wstacktrace = System::Impl::WidenString(stacktrace);
#else
        (void)stacktrace;
#endif

        TASKDIALOGCONFIG config{
            .cbSize                  = sizeof(TASKDIALOGCONFIG),
            .hwndParent              = nullptr,
            .hInstance               = System::Impl::g_InstanceHandle,
            .dwFlags                 = TDF_ALLOW_DIALOG_CANCELLATION | TDF_SIZE_TO_CONTENT,
            .dwCommonButtons         = TDCBF_CLOSE_BUTTON,
            .pszWindowTitle          = wtitle.c_str(),
            .pszMainIcon             = TD_ERROR_ICON,
            .pszMainInstruction      = L"Abort",
            .pszContent              = wcontent.c_str(),

#if GX_ENABLE_STACKTRACE
            .pszExpandedInformation = wstacktrace.c_str(),
            .pszExpandedControlText = L"Hide Stack Trace",
            .pszCollapsedControlText = L"Show Stack Trace",
#else
            .pszExpandedInformation = nullptr,
            .pszExpandedControlText = nullptr,
            .pszCollapsedControlText = nullptr,
#endif
        };

#if !GX_BUILD_TYPE_RETAIL

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
