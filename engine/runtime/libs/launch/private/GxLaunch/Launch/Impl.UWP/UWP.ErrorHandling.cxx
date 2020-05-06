#include <GxBase/Diagnostics.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/Application.hxx>

#pragma warning(push)
#pragma warning(disable : 4715)

#include <winrt/Windows.Foundation.h>

namespace Graphyte::Launch
{
    void InitializeErrorHandling() noexcept
    {
        winrt::init_apartment();
    }
}

#pragma warning(pop)
