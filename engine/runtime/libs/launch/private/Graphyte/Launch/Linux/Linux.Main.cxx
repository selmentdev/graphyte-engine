#include <Graphyte/Application.hxx>


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
        Graphyte::Application::Impl::GApplicationDescriptor = GraphyteApp;
        Graphyte::Application::Impl::GIsFirstInstance = true;

        return MainWrapper(argc, argv);
    }
}
