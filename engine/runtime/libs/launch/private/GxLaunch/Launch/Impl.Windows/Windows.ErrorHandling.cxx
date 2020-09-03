#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/App.hxx>

namespace Graphyte::Launch::Impl::Windows
{
    static void __cdecl OnTerminate() noexcept
    {
        GX_ABORT("Terminate handler called");
    }

    static void __cdecl OnUnexpected() noexcept
    {
        GX_ABORT("Unexpected handler");
    }

    static void __cdecl OnPureCall() noexcept
    {
        GX_ABORT("Pure function call handler");
    }

    static void __cdecl OnInvalidParam(
        const wchar_t* expression,
        const wchar_t* function,
        const wchar_t* file,
        unsigned int line,
        [[maybe_unused]] uintptr_t reserved) noexcept
    {
        (void)Diagnostics::OnAbort(
            System::Impl::NarrowString(expression),
            System::Impl::NarrowString(function),
            System::Impl::NarrowString(file),
            line,
            "Invalid parameter detected in CRT function");
    }

    static LONG CALLBACK OnUnhandledException(
        EXCEPTION_POINTERS* exception_pointers) noexcept
    {
        if (exception_pointers != nullptr)
        {
            Diagnostics::OnCrash(exception_pointers);
        }

        return EXCEPTION_EXECUTE_HANDLER;
    }

    static BOOL WINAPI OnConsoleCtrlC(
        [[maybe_unused]] DWORD ctrl_type) noexcept
    {
        if (Graphyte::App::IsRequestingExit() == false)
        {
            Graphyte::App::RequestExit();
        }
        else
        {
            Diagnostics::Exit(0);
        }

        return TRUE;
    }
}

namespace Graphyte::Launch
{
    void InitializeErrorHandling() noexcept
    {
#if !defined(NDEBUG) && defined(_MSC_VER)

        //
        // Enable CRT debugging facilities.
        //

        int crtdbg = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
        crtdbg |= _CRTDBG_ALLOC_MEM_DF;
        crtdbg |= _CRTDBG_CHECK_ALWAYS_DF;
        crtdbg |= _CRTDBG_CHECK_CRT_DF;
        crtdbg |= _CRTDBG_DELAY_FREE_MEM_DF;
        crtdbg |= _CRTDBG_LEAK_CHECK_DF;

        if constexpr (true)
        {
            // Enable checking each 1024 allocations
            crtdbg &= ~_CRTDBG_CHECK_ALWAYS_DF;
            crtdbg &= 0x0000FFFF;
            crtdbg |= _CRTDBG_CHECK_EVERY_1024_DF;
        }

        _CrtSetDbgFlag(crtdbg);

        //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#if false
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
        _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
        _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
#endif

#endif

        //
        // Set up error reporting for debug builds.
        //

        UINT errorMode = SetErrorMode(0);
        errorMode |= SEM_FAILCRITICALERRORS;
        errorMode |= SEM_NOGPFAULTERRORBOX;
        errorMode |= SEM_NOOPENFILEERRORBOX;
        errorMode &= ~SEM_NOALIGNMENTFAULTEXCEPT;
        SetErrorMode(errorMode);

        std::set_terminate(Impl::Windows::OnTerminate);

        SetUnhandledExceptionFilter(Impl::Windows::OnUnhandledException);

#if defined(_MSC_VER)
        set_unexpected(Impl::Windows::OnUnexpected);
#endif

        _set_purecall_handler(Impl::Windows::OnPureCall);

        _set_invalid_parameter_handler(Impl::Windows::OnInvalidParam);

        if (Graphyte::App::Impl::g_ApplicationDescriptor.Type == Graphyte::App::ApplicationType::Game)
        {
            if (SetConsoleCtrlHandler(Impl::Windows::OnConsoleCtrlC, TRUE) == FALSE)
            {
                GX_ASSERTF(false, "Cannot set ctrl+c handler: {}", Diagnostics::GetMessageFromSystemError());
            }
        }
    }
}
