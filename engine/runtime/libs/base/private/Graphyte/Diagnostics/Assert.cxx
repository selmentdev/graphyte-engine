#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Status.hxx>
#include <Graphyte/System.hxx>

#include "Diagnostics.Impl.hxx"

namespace Graphyte::Diagnostics::Impl
{
    static bool GIsAsserting{ false };
}

namespace Graphyte::Diagnostics
{
    BASE_API bool IsAsserting() noexcept
    {
        return Impl::GIsAsserting;
    }

    BASE_API bool OnAssertArgs(
        bool& always_ignore,
        std::string_view condition,
        std::string_view function,
        std::string_view file,
        std::uint_least32_t line,
        std::string_view format,
        fmt::format_args args
    ) noexcept
    {
        if (always_ignore)
        {
            //
            // Ignore this assert, don't break to debugger.
            //

            return false;
        }


        //
        // Acquire global diagnostics reporting lock.
        //

        Threading::ScopedLock<Threading::CriticalSection> lock{ Impl::GetDiagnosticsLock() };

        if (Impl::GIsAsserting)
        {
            GX_LOG(LogPlatform, Error, "Assertion is not reentrant\n");

            Diagnostics::FailFast();
        }

        Impl::GIsAsserting = true;

        //
        // Format location.
        //

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
            "Assertion failed:\n{}",
            content
        );

        GX_LOG(LogPlatform, Error,
            "Stack Trace:\n{}",
            stacktrace
        );

        auto result = Impl::AssertResult::Abort;

        if (GetErrorReporting() == ErrorReporting::Interactive)
        {
            //
            // Report assertion to user
            //

            result = Diagnostics::Impl::ReportAssertion(
                "Graphyte Engine",
                content,
                stacktrace
            );
        }


        Impl::GIsAsserting = false;

        if (result == Impl::AssertResult::Abort)
        {
            //
            // Abort without hesitation.
            //

            Diagnostics::FailFast();
        }
        else if (result == Impl::AssertResult::IgnoreAlways)
        {
            //
            // Mark this assertion as always-ignore.
            //

            always_ignore = true;
        }


        //
        // Recover from assertion.
        //

        return result == Impl::AssertResult::Retry;
    }
}
