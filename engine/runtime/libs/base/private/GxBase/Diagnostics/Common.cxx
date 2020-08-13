#include <GxBase/Diagnostics.hxx>
#include <GxBase/System.hxx>
#include <GxBase/App.hxx>
#include <GxBase/CommandLine.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include "Diagnostics.Impl.hxx"

#if GRAPHYTE_PLATFORM_POSIX
#include <syslog.h>
#endif

#if GRAPHYTE_PLATFORM_LINUX
#include <sys/types.h>
#include <signal.h>
#endif

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
#include <io.h>
#endif

#if (GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP) && GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS
#include <DbgHelp.h>
#endif

namespace Graphyte::Diagnostics::Impl
{
    extern Threading::CriticalSection& GetDiagnosticsLock() noexcept
    {
        static Threading::CriticalSection s_DiagnosticsLock;
        return s_DiagnosticsLock;
    }

    ErrorReporting GErrorReporting{ ErrorReporting::Interactive };

    bool GStackTraceSymbolInfo{ false };

    bool GLogOutputTerminal{ false };
    bool GLogOutputDebugger{ false };
    std::unique_ptr<Storage::IStream> GLogOutputFile{};

#if GRAPHYTE_PLATFORM_WINDOWS

    HANDLE GSystemEventLog{};

#endif

    void FinishLogOutput() noexcept
    {
        //
        // Flush file log.
        //

        if (Impl::GLogOutputFile != nullptr)
        {
            [[maybe_unused]] auto status = Impl::GLogOutputFile->Flush();
            Impl::GLogOutputFile.reset();
        }


        //
        // Flush terminal output.
        //

        if (Impl::GLogOutputTerminal)
        {
            fflush(stdout);
            fflush(stderr);
        }
    }
}

namespace Graphyte::Diagnostics
{
    BASE_API void Initialize() noexcept
    {
        //
        // Check whether application has debugger attached.
        //

        Impl::GLogOutputDebugger = Diagnostics::IsDebuggerAttached();


        //
        // Enable debug symbols access for stacktrace.
        //

#if GRAPHYTE_PLATFORM_WINDOWS && GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS


        //
        // Try to initialize symbol handler.
        //
        // Due to some internal race-condition, this function may not initialize properly when
        // debugger is attached.
        //

        constexpr const DWORD win32_STATUS_INFO_LENGTH_MISMATCH = 0xc0000004;

        HANDLE const process = GetCurrentProcess();

        for (size_t i = 0; i < 16; ++i)
        {
            if (!!SymInitialize(process, nullptr, TRUE))
            {
                SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_FAIL_CRITICAL_ERRORS);
                Impl::GStackTraceSymbolInfo = true;
                break;
            }

            DWORD error = ::GetLastError();

            if (error == win32_STATUS_INFO_LENGTH_MISMATCH)
            {
                continue;
            }
            else
            {
                GX_LOG(LogPlatform, Error, "Failed to initialize symbols handler: {}", Diagnostics::GetMessageFromSystemError(error));
                break;
            }
        }

#endif

#if GRAPHYTE_PLATFORM_POSIX && GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS

        //
        // Posix systems have symbols always enabled.
        //

        Impl::GStackTraceSymbolInfo = true;

#endif


        GX_LOG(LogPlatform, Info, "Stack trace enabled: {}\n", Impl::GStackTraceSymbolInfo);


        //
        // Check for syslog output.
        //

#if GRAPHYTE_PLATFORM_WINDOWS

        DWORD process_id = GetCurrentProcessId();

        std::wstring event_source{ L"pid-" };
        event_source += std::to_wstring(process_id);

        Impl::GSystemEventLog = RegisterEventSourceW(nullptr, event_source.c_str());

        if (Impl::GSystemEventLog == nullptr)
        {
            GX_LOG(LogPlatform, Error, "Cannot open event log: {}\n", Diagnostics::GetMessageFromSystemError());
        }

#elif GRAPHYTE_PLATFORM_POSIX

        openlog(nullptr, LOG_ODELAY, LOG_USER);

#endif


        //
        // Check if we want to output log to terminal.
        //

        if (App::GetDescriptor().Type == App::ApplicationType::ConsoleTool)
        {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
            if (_isatty(_fileno(stdout)))
#endif
            {
                Impl::GLogOutputTerminal = true;
            }
        }


        //
        // Check if application wants to output data to log file.
        //

        if (!CommandLine::Get("--force-no-log").has_value())
        {
            std::string log_path = Storage::GetLogsDirectory();

            if (Storage::IFileSystem::GetPlatformNative().DirectoryTreeCreate(log_path) == Status::Success)
            {
                std::string const& executable = System::GetExecutableName();
                std::string timestamp{};
                ToString(timestamp, DateTime::Now(), DateTimeFormat::FileSafe);

                Storage::AppendPath(log_path, fmt::format("{}-{}.txt", executable, timestamp));

                Status status = Storage::IFileSystem::GetPlatformNative().OpenWrite(
                    Impl::GLogOutputFile,
                    log_path,
                    false,
                    true);

                GX_ABORT_UNLESS(status == Status::Success, "Failed to initialize output log {}", log_path);
            }
        }
    }

    BASE_API void Finalize() noexcept
    {
        //
        // This is regular way of terminating application. Flush any log outputs.
        //

        Impl::FinishLogOutput();


        //
        // Cleanup syslog.
        //

#if GRAPHYTE_PLATFORM_WINDOWS

        GX_ASSERT(Impl::GSystemEventLog != nullptr);

        if (Impl::GSystemEventLog != nullptr)
        {
            DeregisterEventSource(Impl::GSystemEventLog);
        }

#elif GRAPHYTE_PLATFORM_POSIX

        closelog();

#endif


#if GRAPHYTE_PLATFORM_WINDOWS && GRAPHYTE_ENABLE_STACKTRACE_SYMBOLS

        if (SymCleanup(GetCurrentProcess()) == FALSE)
        {
            GX_ABORT("Failed to cleanup symbol handler");
        }

#endif
    }

    BASE_API bool IsDebuggerAttached() noexcept
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        return IsDebuggerPresent() != FALSE;

#elif GRAPHYTE_PLATFORM_LINUX

        int fd = open("/proc/self/status", O_RDONLY);

        if (fd != -1)
        {
            std::array<char, 1024> buffer{};

            ssize_t length = read(fd, buffer.data(), buffer.size());

            close(fd);

            if (length > 0)
            {
                std::string_view buffer_view{ buffer.data(), static_cast<size_t>(length) };
                std::string_view match{ "TracerPid:\t" };

                if (auto position = buffer_view.find(match); position != std::string_view::npos)
                {
                    auto value = buffer_view.substr(position + match.length(), 1);

                    return value != "0";
                }
            }
        }

        return false;

#else
        // https://developer.apple.com/library/archive/qa/qa1361/_index.html
#error "Unimplemented"

#endif
    }

    [[noreturn]] BASE_API void Exit(int32_t exitCode) noexcept
    {
        //
        // Exiting from application in unusual but expected way.
        //

        GX_LOG(LogPlatform, Warn, "Exiting from application in unusual way: exit = {}\n", exitCode);


        //
        // There will be no way of flushing log outputs anytime.
        //

        Impl::FinishLogOutput();

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        ExitProcess(static_cast<UINT>(exitCode));

#elif GRAPHYTE_PLATFORM_LINUX

        exit(exitCode);

#else
#error "Not implemented"
#endif
    }

    [[noreturn]] BASE_API void FailFast() noexcept
    {
        //
        // Exiting from application due to fast-fail is unexpected.
        //

        GX_LOG(LogPlatform, Error, "Exiting from application due to fast-fail\n");


        //
        // Flush any log outputs.
        //

        Impl::FinishLogOutput();


        //
        // And fail application.
        //

#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP

        RaiseFailFastException(nullptr, nullptr, 0);
        TerminateProcess(GetCurrentProcess(), 1);

#elif GRAPHYTE_PLATFORM_LINUX

        kill(getpid(), SIGKILL);


        //
        // Well, this is noreturn...
        //

        for (;;)
        {
            ;
        }

#else
#error "Not implemented"
#endif
    }

    BASE_API ErrorReporting GetErrorReporting() noexcept
    {
        return Impl::GErrorReporting;
    }

    BASE_API void SetErrorReporting(
        ErrorReporting value) noexcept
    {
        Impl::GErrorReporting = value;
    }
}
