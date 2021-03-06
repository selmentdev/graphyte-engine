#include <GxBase/Diagnostics.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/System.hxx>

#include "Diagnostics.Impl.hxx"

#if GX_PLATFORM_LINUX
#include <syslog.h>
#endif

namespace Graphyte::Diagnostics::Impl
{
    static bool g_IsAborting{ false };
}

namespace Graphyte::Diagnostics
{
    BASE_API bool IsAborting() noexcept
    {
        return Impl::g_IsAborting;
    }

    BASE_API bool OnAbortArgs(
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        fmt::format_args args) noexcept
    {
        //
        // Acquire global diagnostics reporting lock.
        //

        Threading::ScopedLock<Threading::CriticalSection> lock{ Impl::GetDiagnosticsLock() };

        if (Impl::g_IsAborting)
        {
            GX_LOG_ERROR(LogPlatform, "Aborting is not reentrant\n");

            Diagnostics::FailFast();
        }

        Impl::g_IsAborting = true;

        fmt::memory_buffer content_buffer{};

#if GX_BUILD_TYPE_RETAIL

        (void)file;
        (void)line;
        (void)condition;
        (void)function;

        std::string message = fmt::vformat(format, args);

        GX_LOG_ERROR(LogPlatform, "Application aborted:\n{}", message);

        if (Diagnostics::Impl::ReportAbort("Graphyte Engine", message, ""))
        {
            Impl::g_IsAborting = false;
            return true;
        }

#else
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

        GX_LOG_ERROR(LogPlatform,
            "Application aborted:\n{}"
            "Stack Trace:\n{}",
            content,
            stacktrace);

        if (Diagnostics::Impl::ReportAbort(
                "Graphyte Engine",
                content,
                stacktrace))
        {
            Impl::g_IsAborting = false;
            return true;
        }
#endif


        //
        // Report that event to system log.
        //

#if GX_PLATFORM_WINDOWS

        if (Impl::g_SystemEventLog != nullptr)
        {
            content_buffer.push_back('\0');

            LPCSTR pszStrings = content_buffer.data();

            constexpr DWORD event_id = 0xc000'0001;

            ReportEventA(
                Impl::g_SystemEventLog,
                EVENTLOG_ERROR_TYPE,
                0,
                event_id,
                nullptr,
                1,
                0,
                &pszStrings,
                nullptr);
        }

#elif GX_PLATFORM_POSIX

        content_buffer.push_back('\0');

        syslog(LOG_CRIT, "%s", content_buffer.data());

#endif

        Impl::g_IsAborting = false;

        //
        // User requested exit from abort message.
        //
        // Do fail-fast since application may hang on DLL unloading.
        //

        Diagnostics::FailFast();

        return false;
    }
}
