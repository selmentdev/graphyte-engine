#include <GxBase/Status.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/FileManager.hxx>

#include <DbgHelp.h>

namespace Graphyte::Diagnostics
{
    Status CreateCoreDump(
        EXCEPTION_POINTERS* exception) noexcept
    {
        (void)exception;
        return Status::NotImplemented;
    }
}
