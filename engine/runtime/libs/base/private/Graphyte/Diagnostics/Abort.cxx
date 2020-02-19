#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Storage/Path.hxx>
#include <Graphyte/Status.hxx>
#include <Graphyte/System.hxx>

#include "Diagnostics.Impl.hxx"

#if GRAPHYTE_PLATFORM_LINUX
#   include <syslog.h>
#endif

namespace Graphyte::Diagnostics::Impl
{
    static bool GIsAborting{ false };
}

namespace Graphyte::Diagnostics
{
    BASE_API bool IsAborting() noexcept
    {
        return Impl::GIsAborting;
    }
    
    BASE_API bool OnAbortArgs(
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        fmt::format_args args
    ) noexcept
    {
        //
        // Acquire global diagnostics reporting lock.
        //

        Threading::ScopedLock<Threading::CriticalSection> lock{ Impl::GetDiagnosticsLock() };

        if (Impl::GIsAborting)
        {
            GX_LOG(LogPlatform, Error, "Aborting is not reentrant\n");

            Diagnostics::FailFast();
        }

        Impl::GIsAborting = true;

        fmt::memory_buffer content_buffer{};

        //
        // Format message.
        //

        if (!format.empty())
        {
            fmt::memory_buffer message{};
            fmt::vformat_to(message, format, args);
            fmt::format_to(content_buffer, "Message: {}\n", std::string_view{ message.data(), message.size() });
        }


        //
        // Format location.
        //

        if (!condition.empty())
        {
            fmt::format_to(content_buffer, "Condition: {}\n", condition);
        }

        if (!file.empty())
        {
            fmt::format_to(content_buffer, "Location: {}({})\n", file, line);
        }

        if (!function.empty())
        {
            fmt::format_to(content_buffer, "Function: {}\n", function);
        }

        std::string_view content{ content_buffer.data(), content_buffer.size() };


        //
        // Format stacktrace.
        //

        fmt::memory_buffer stacktrace_buffer{};
        std::vector<StackFrame> trace{};

        if (auto const status = GetStackTrace(trace); status == Status::Success)
        {
            for (const auto& frame : trace)
            {
                fmt::format_to(stacktrace_buffer, "{}\n", ToString(frame, StackFrameFormat::Extended));
            }
        }
        else
        {
            fmt::format_to(stacktrace_buffer, "-- no stack trace available --\n");
        }

        std::string_view stacktrace{ stacktrace_buffer.data(), stacktrace_buffer.size() };

        GX_LOG(LogPlatform, Error,
            "Application aborted:\n{}"
            "Stack Trace:\n{}",
            content,
            stacktrace
        );

        if (Diagnostics::Impl::ReportAbort(
            "Graphyte Engine",
            content,
            stacktrace))
        {
            Impl::GIsAborting = false;
            return true;
        }


        //
        // Report that event to system log.
        //

#if GRAPHYTE_PLATFORM_WINDOWS

        if (Impl::GSystemEventLog != nullptr)
        {
            content_buffer.push_back('\0');

            LPCSTR pszStrings = content_buffer.data();

            constexpr DWORD event_id = 0xc000'0001;

            ReportEventA(
                Impl::GSystemEventLog,
                EVENTLOG_ERROR_TYPE,
                0,
                event_id,
                nullptr,
                1,
                0,
                &pszStrings,
                nullptr
            );
        }

#elif GRAPHYTE_PLATFORM_POSIX

        content_buffer.push_back('\0');

        syslog(LOG_CRIT, "%s", content_buffer.data());

#endif

        Impl::GIsAborting = false;

        //
        // User requested exit from abort message.
        //
        // Do fail-fast since application may hang on DLL unloading.
        //

        Diagnostics::FailFast();

        return false;
    }
}
