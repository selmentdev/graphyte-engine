#include <GxBase/Diagnostics.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>

#include <shellapi.h>
#include <ShlObj.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <DbgHelp.h>

namespace Graphyte::Diagnostics
{
    BASE_API std::vector<std::string> GetModules() noexcept
    {
        return {};
    }
}
