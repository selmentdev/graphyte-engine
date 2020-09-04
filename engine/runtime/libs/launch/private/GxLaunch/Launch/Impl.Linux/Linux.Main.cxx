#include <GxBase/Application.hxx>


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
        Graphyte::Application::Impl::g_ApplicationDescriptor = GraphyteApp;

        Graphyte::Application::Impl::g_IsFirstInstance = true;

        return MainWrapper(argc, argv);
    }
}
