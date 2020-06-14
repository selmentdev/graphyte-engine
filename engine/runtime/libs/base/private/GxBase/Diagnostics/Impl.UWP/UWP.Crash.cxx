#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>

#include <ErrorRep.h>

namespace Graphyte::Diagnostics
{
    BASE_API void OnCrash(
        EXCEPTION_POINTERS* exception) noexcept
    {
        (void)exception;
        Diagnostics::FailFast();
    }
}
