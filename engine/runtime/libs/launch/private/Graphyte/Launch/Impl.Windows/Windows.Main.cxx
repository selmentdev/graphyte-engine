#include <Graphyte/Application.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>


// =================================================================================================
//
// Application descriptor defined in app project.
//

extern Graphyte::Application::ApplicationDescriptor GraphyteApp;


// =================================================================================================
//
// Handling single instance.
//

namespace Graphyte::Launch::Impl::Windows
{
    HANDLE GSingleInstanceMutex{};

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

        GSingleInstanceMutex = CreateMutexW(
            nullptr,
            TRUE,
            System::Impl::WidenString(name).c_str()
        );

        if (GSingleInstanceMutex != nullptr)
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

                ReleaseMutex(GSingleInstanceMutex);

                GSingleInstanceMutex = nullptr;
            }
            else if (dwError == ERROR_ACCESS_DENIED)
            {
                GX_ABORT("Cannot create mutex ({}). Insufficient access rights.", name);
            }
        }

        Graphyte::Application::Impl::GIsFirstInstance = first;
    }

    void ReleaseSingleInstance() noexcept
    {
        if (GSingleInstanceMutex != nullptr)
        {
           ReleaseMutex(GSingleInstanceMutex);
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
        System::Impl::GInstanceHandle = GetModuleHandleW(nullptr);
        Graphyte::Application::Impl::GApplicationDescriptor = GraphyteApp;

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
            __except(Diagnostics::OnCrash(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
            {
                Graphyte::Application::RequestExit(true);
            }
        }
#endif

        Impl::Windows::ReleaseSingleInstance();

        return result;
    }
}