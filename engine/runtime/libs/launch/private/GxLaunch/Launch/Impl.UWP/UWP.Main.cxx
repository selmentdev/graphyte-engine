#include <GxBase/Application.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>


// =================================================================================================
//
// Application descriptor defined in app project.
//

extern Graphyte::Application::ApplicationDescriptor GraphyteApp;


// =================================================================================================
//
// Main entry point.
//

namespace Graphyte::Launch
{
    extern int MainWrapper(int argc, char** argv) noexcept;

    int Main(int argc, char** argv) noexcept
    {
        //System::Impl::g_InstanceHandle = GetModuleHandleW(nullptr);
        Graphyte::Application::Impl::g_ApplicationDescriptor = GraphyteApp;

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
                Graphyte::Application::RequestExit(true);
            }
        }
#endif

        return result;
    }
}
