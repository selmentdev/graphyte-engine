#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/System/Pipe.hxx>
#include <Graphyte/DateTime.hxx>
#include <Graphyte/Status.hxx>

namespace Graphyte::System
{
    struct ProcessHandle final
    {
#if GRAPHYTE_PLATFORM_WINDOWS
        HANDLE Handle;
#elif GRAPHYTE_PLATFORM_POSIX
        pid_t ProcessID;
#endif

        bool IsValid() const noexcept
        {
#if GRAPHYTE_PLATFORM_WINDOWS
            return Handle != nullptr;
#elif GRAPHYTE_PLATFORM_POSIX
            return ProcessID != 0;
#endif
        }
    };

    struct ProcessId final
    {
#if GRAPHYTE_PLATFORM_WINDOWS
        DWORD Value;
#elif GRAPHYTE_PLATFORM_POSIX
        pid_t Value;
#endif
    };

    struct ProcessResult final
    {
        Status StatusCode;
        int32_t ExitCode;
    };

    enum class CreateProcessFlags
    {
        None = 0,
        Detached = 1 << 0,
        Minimized = 1 << 1,
        Hidden = 1 << 2,
    };

    class BASE_API Process final
    {
    public:
        /*!
         * @brief   Creates new process.
         * 
         * @param   path                Provides path to executable.
         * @param   params              Provides optional params for application.
         * @param   working_directory   Provides optional working directory.
         * @param   flags               Provides additional flags.
         * @param   id                  Returns process ID.
         * @param   pipe_stdin          Returns stdin pipe to spawned process.
         * @param   pipe_stdout         Returns stdout pipe to spawned process.
         * @param   pipe_stderr         Returns stderr pipe to spawned process.
         * 
         * @return  The process handle to spawned process.
         */
        static ProcessHandle Create(
            const char* path,
            const char* params = nullptr,
            const char* working_directory = nullptr,
            CreateProcessFlags flags = CreateProcessFlags::None,
            ProcessId* id = nullptr,
            PipeHandle* pipe_stdin = nullptr,
            PipeHandle* pipe_stdout = nullptr,
            PipeHandle* pipe_stderr = nullptr
        ) noexcept;

        static void Close(
            ProcessHandle& handle
        ) noexcept;

        /*!
         * @brief   Checks whether specified process is still running.
         *
         * @param   handle      Provides handle to process.
         * @param   exit_code   Returns process exit code.
         * 
         * @return  @c true when process is still running, @c false otherwise.
         */
        static bool IsRunning(
            ProcessHandle& handle,
            int32_t& exit_code
        ) noexcept;

        /*!
         * @brief   Waits for specified process to exit.
         *
         * @param   handle      Provides handle to process.
         * @param   exit_code   Returns process exit code.
         * 
         * @return  @c true when successful, @c false otherwise.
         */
        static bool Wait(
            ProcessHandle& handle,
            int32_t& exit_code
        ) noexcept;

        /*!
         * @brief   Terminates process.
         *
         * @param   handle  Provides handle of process to terminate.
         * @param   tree    Provides value indicating whether single process or process tree should
         *                  be terminated.
         */
        static void Terminate(
            ProcessHandle& handle,
            bool tree
        ) noexcept;
            
        /*!
         * @brief   Execute process.
         *
         * @param   path                Provides path to executable.
         * @param   params              Provides optional params for application.
         * @param   working_directory   Provides optional working directory.
         * @param   exit_code           Returns exit code from process.
         * @param   out_stdout          Returns string with process stdout stream content.
         * @param   out_stderr          Returns string with process stderr stream content.
         * 
         * @return  @c true when successful, @c false otherwise.
         */
        static ProcessResult Execute(
            const char* path,
            const char* params = nullptr,
            const char* working_directory = nullptr,
            std::string* out_stdout = nullptr,
            std::string* out_stderr = nullptr
        ) noexcept;


        /*!
         * @brief   Gets link time of current process.
         */
        static DateTime GetLinkTime() noexcept;

        /*!
         * \brief   Gets current process ID.
         */
        static ProcessId GetCurrent() noexcept;
    };
}

template <>
struct fmt::formatter<Graphyte::System::ProcessId>
{
    template <typename ParseContext>
    constexpr auto parse(
        ParseContext& context
    )
    {
        return context.begin();
    }

    template <typename FormatContext>
    auto format(
        Graphyte::System::ProcessId value,
        FormatContext& context
    )
    {
        return format_to(
            context.out(),
            "{:d}",
            value.Value
        );
    }
};
