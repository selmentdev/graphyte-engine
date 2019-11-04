#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Storage/IFileSystem.hxx>
#include <Graphyte/Threading/Sync.hxx>

// =================================================================================================
//
// Internals API.
//

namespace Graphyte::Diagnostics::Impl
{
    enum class AssertResult
    {
        Abort,
        Retry,
        Ignore,
        IgnoreAlways,
    };

    extern AssertResult ReportAssertion(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept;

    extern bool ReportAbort(
        std::string_view title,
        std::string_view content,
        std::string_view stacktrace
    ) noexcept;

    /*!
     * \brief   Writes text to debugger output.
     *
     * \param   level       Provides log level for this message.
     * \param   text        Provides text to write.
     *
     * \note    This function is thread-safe.
     *
     * \remarks This function interfaces with native debugger APIs, which in most cases use regular
     *          C string as one and only paramter. We just assume that log implementation guarantees
     *          that this parameter is valid raw C string.
     */
    extern void DebugOutput(LogLevel level, const char* text) noexcept;

    extern Threading::CriticalSection& GetDiagnosticsLock() noexcept;
}


// =================================================================================================
//
// Internals state.
//

namespace Graphyte::Diagnostics::Impl
{
    extern bool GLogOutputDebugger;

    extern bool GLogOutputTerminal;
    extern bool GStackTraceSymbolInfo;

    extern std::unique_ptr<Storage::IStream> GLogOutputFile;

#if GRAPHYTE_PLATFORM_WINDOWS

    extern HANDLE GSystemEventLog;

#endif
}
