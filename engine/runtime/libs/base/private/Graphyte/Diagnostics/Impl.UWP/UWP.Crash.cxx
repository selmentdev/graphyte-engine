#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/System.hxx>

#include <ErrorRep.h>

namespace Graphyte::Diagnostics
{
    BASE_API void OnCrash(
        EXCEPTION_POINTERS* exception
    ) noexcept
    {
        (void)exception;
        Diagnostics::FailFast();
    }
}
