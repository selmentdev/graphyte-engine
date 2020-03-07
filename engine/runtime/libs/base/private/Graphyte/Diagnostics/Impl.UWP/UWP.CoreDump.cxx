#include <Graphyte/Status.hxx>
#include <Graphyte/System/Impl.Windows/Windows.Helpers.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/Storage/FileManager.hxx>

#include <DbgHelp.h>

namespace Graphyte::Diagnostics
{
    Status CreateCoreDump(
        EXCEPTION_POINTERS* exception
    ) noexcept
    {
        (void)exception;
        return Status::NotImplemented;
    }
}
