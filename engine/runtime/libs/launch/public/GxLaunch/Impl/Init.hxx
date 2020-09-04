// =================================================================================================
// UWP specific code

#if GRAPHYTE_PLATFORM_UWP

#pragma warning(push)
#pragma warning(disable : 4715)

#include <winrt/Windows.Foundation.h>

#pragma warning(pop)

#endif

namespace Graphyte::Launch
{
    int Main(int argc, char** argv) noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS
        System::Impl::g_InstanceHandle = GetModuleHandleW(nullptr);
#elif GRAPHYTE_PLATFORM_UWP
        winrt::init_apartment();
#endif

        Graphyte::App::Impl::g_ApplicationDescriptor = GraphyteApp;

#if GRAPHYTE_PLATFORM_WINDOWS
        SetProcessDPIAware();
#endif

        Impl::InitializeErrorHandling();

        Impl::SingleInstance_Acquire();

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

        Impl::SingleInstance_Release();

        return result;
    }
}