#include <GxBase/App.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>


// =================================================================================================
//
// Application descriptor defined in app project.
//

extern Graphyte::App::ApplicationDescriptor GraphyteApp;


// =================================================================================================
//
// Handling single instance.
//

namespace Graphyte::Launch::Impl::Windows
{
    HANDLE g_SingleInstanceMutex{};

    //
    // WARN:    Do not move this to RAII idiom. Functions using `__try` and `__except` keywords must
    //          not have any objects with ctor/dtor.
    //

    void AcquireSingleInstance() noexcept
    {
        bool first = true;

        std::string name = fmt::format("graphyte-engine-{}", GraphyteApp.Id);


        //
        // Try to create mutex for current application.
        //

        g_SingleInstanceMutex = CreateMutexW(
            nullptr,
            TRUE,
            System::Impl::WidenString(name).c_str());

        if (g_SingleInstanceMutex != nullptr)
        {
            DWORD dwError = GetLastError();

            if (dwError == ERROR_ALREADY_EXISTS)
            {
                //
                // This mutex was already created by other instance of current application.
                //

                first = false;


                //
                // We don't need this mutex anymore.
                //

                ReleaseMutex(g_SingleInstanceMutex);

                g_SingleInstanceMutex = nullptr;
            }
            else if (dwError == ERROR_ACCESS_DENIED)
            {
                GX_ABORT("Cannot create mutex ({}). Insufficient access rights.", name);
            }
        }

        Graphyte::App::Impl::g_IsFirstInstance = first;
    }

    void ReleaseSingleInstance() noexcept
    {
        if (g_SingleInstanceMutex != nullptr)
        {
            ReleaseMutex(g_SingleInstanceMutex);
        }
    }
}


// =================================================================================================
//
// Main entry point.
//

namespace Graphyte::Launch
{
    extern int MainWrapper(int argc, char** argv) noexcept;

    int Main(int argc, char** argv) noexcept
    {
        System::Impl::g_InstanceHandle = GetModuleHandleW(nullptr);

        Graphyte::App::Impl::g_ApplicationDescriptor = GraphyteApp;

        SetProcessDPIAware();

        Impl::Windows::AcquireSingleInstance();

        int result = 0;

#if GRAPHYTE_PLATFORM_HAVE_SEH_EXCEPTIONS
        if (Diagnostics::IsDebuggerAttached())
#endif
        {
            result = MainWrapper(argc, argv);
        }
#if GRAPHYTE_PLATFORM_HAVE_SEH_EXCEPTIONS
        else
        {
            __try
            {
                result = MainWrapper(argc, argv);
            }
            __except (Diagnostics::OnCrash(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
            {
                Graphyte::App::RequestExit();
            }
        }
#endif

        Impl::Windows::ReleaseSingleInstance();

        return result;
    }
}
