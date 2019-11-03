#include "Base.pch.hxx"
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Span.hxx>
#include <Graphyte/Application.hxx>

#include "Diagnostics.Impl.hxx"

#if GRAPHYTE_PLATFORM_WINDOWS
#   include <io.h>
#endif

namespace Graphyte::Diagnostics::Impl
{
#if !defined(NDEBUG)
    BASE_API LogLevel GLogLevel{ LogLevel::Trace };
#else
    BASE_API LogLevel GLogLevel{ LogLevel::Warn };
#endif
}

namespace Graphyte::Diagnostics
{
    BASE_API bool LogDispatchArgs(
        LogLevel level,
        std::string_view category,
        std::string_view format,
        fmt::format_args args
    ) noexcept
    {
        fmt::memory_buffer buffer{};

        constexpr bool outputLogLevelAndCategory = false;

        if constexpr (outputLogLevelAndCategory)
        {
            //
            // Format log to buffer.
            //

            fmt::format_to(buffer, "[{}][{:1}] ", category, static_cast<int>(level));
        }

        fmt::vformat_to(buffer, format, args);

        if (buffer.size() != 0)
        {
            //
            // Forward log to terminal.
            //

            bool const is_error = (level == LogLevel::Error || level == LogLevel::Fatal);
            bool const is_terminal = Application::GetDescriptor().Type == Application::ApplicationType::ConsoleTool;

            if (Impl::GLogOutputTerminal && is_error && is_terminal)
            {
                std::fwrite(buffer.data(), buffer.size(), 1, stderr);
            }


            //
            // Forward to file.
            //

            if (Impl::GLogOutputFile != nullptr)
            {
                size_t processed{};

                [[maybe_unused]] auto status = Impl::GLogOutputFile->Write(
                    { reinterpret_cast<const std::byte*>(buffer.data()), buffer.size() },
                    processed
                );
            }


            //
            // Forward log message to debugger first.
            //

            if (Impl::GLogOutputDebugger)
            {
                // Guarantee nul character at end.
                buffer.push_back(0);

                Impl::DebugOutput(level, buffer.data());
            }

            return true;
        }

        return false;
    }
}
