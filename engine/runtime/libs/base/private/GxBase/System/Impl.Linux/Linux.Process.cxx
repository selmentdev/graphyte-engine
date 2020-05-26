#include <GxBase/System.hxx>
#include <GxBase/System/Process.hxx>
#include <GxBase/String.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Storage/FileManager.hxx>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Threading/Thread.hxx>
#include <GxBase/Diagnostics.hxx>

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <wordexp.h>
#include <spawn.h>
#include <link.h>

namespace Graphyte::System
{
    ProcessHandle Process::Create(
        const char* path,
        const char* params,
        const char* working_directory,
        CreateProcessFlags flags,
        ProcessId* id,
        PipeHandle* pipe_stdin,
        PipeHandle* pipe_stdout,
        PipeHandle* pipe_stderr
    ) noexcept
    {
        std::string full_path{ path };

        if (!Storage::IsAbsolutePath(full_path))
        {
            // XXX: Convert to absolute path.
        }

        if (Storage::IFileSystem::GetPlatformNative().Exists(full_path) == Status::Success)
        {
            GX_ASSERTF(false, "File `{}` doesnt exist!\n", path);
            return {};
        }

        std::string full_params = (params != nullptr)
            ? fmt::format("\"{}\" {}", full_path.c_str(), params)
            : fmt::format("\"{}\"", full_path.c_str());

        wordexp_t exp_status{};

        int exp_result = wordexp(full_params.c_str(), &exp_status, 0);

        if (exp_result != 0)
        {
            GX_LOG(LogPlatform, Error, "Failed to expand command line: {}\n", exp_result);
            return {};
        }

        pid_t process_id{};

        posix_spawnattr_t spawn_attributes{};
        posix_spawnattr_init(&spawn_attributes);

        short spawn_flags{};

        sigset_t empty_sigset{};
        sigemptyset(&empty_sigset);
        posix_spawnattr_setsigmask(&spawn_attributes, &empty_sigset);

        spawn_flags |= POSIX_SPAWN_SETSIGMASK;

        sigset_t default_sigset{};
        sigemptyset(&default_sigset);

        for (int i = SIGRTMIN; i < SIGRTMAX; ++i)
        {
            sigaddset(&default_sigset, i);
        }

        posix_spawnattr_setsigdefault(&spawn_attributes, &default_sigset);

        spawn_flags |= POSIX_SPAWN_SETSIGDEF;

        int spawn_result = -1;

        if (pipe_stdout != nullptr || pipe_stdin != nullptr || pipe_stderr != nullptr)
        {
            posix_spawn_file_actions_t files{};
            posix_spawn_file_actions_init(&files);

            if (pipe_stdout != nullptr)
            {
                posix_spawn_file_actions_adddup2(
                    &files,
                    pipe_stdout->Descriptor,
                    STDOUT_FILENO
                );
            }

            if (pipe_stdin != nullptr)
            {
                posix_spawn_file_actions_adddup2(
                    &files,
                    pipe_stdin->Descriptor,
                    STDIN_FILENO
                );
            }

            if (pipe_stderr != nullptr)
            {
                posix_spawn_file_actions_adddup2(
                    &files,
                    pipe_stderr->Descriptor,
                    STDERR_FILENO
                );
            }

            posix_spawnattr_setflags(&spawn_attributes, spawn_flags);

            spawn_result = posix_spawn(
                &process_id,
                full_path.c_str(),
                &files,
                &spawn_attributes,
                exp_status.we_wordv,
                environ
            );

            posix_spawn_file_actions_destroy(&files);
        }
        else
        {
            spawn_flags |= POSIX_SPAWN_USEVFORK;

            posix_spawnattr_setflags(&spawn_attributes, spawn_flags);

            spawn_result = posix_spawn(
                &process_id,
                full_path.c_str(),
                nullptr,
                &spawn_attributes,
                exp_status.we_wordv,
                environ
            );
        }

        if (spawn_result != 0)
        {
            GX_LOG(LogPlatform, Error, "posix_spawn: {}, pid: {}\n", spawn_result, process_id);
        }

        wordfree(&exp_status);

        (void)path;
        (void)params;
        (void)working_directory;
        (void)flags;
        (void)id;

        return { process_id };
    }

    void Process::Close(
        ProcessHandle& handle
    ) noexcept
    {
        handle.ProcessID = 0;
    }

    bool Process::IsRunning(
        ProcessHandle& handle,
        int32_t& exit_code
    ) noexcept
    {
        auto kill_status = kill(handle.ProcessID, 0);
        auto is_running = (kill_status == 0) || (kill_status == -1 && errno == EPERM);

        exit_code = 0;

        if (is_running)
        {
            for (;;)
            {
                siginfo_t signal_info{};
                signal_info.si_pid = 0;

                if (waitid(
                    P_PID,
                    static_cast<id_t>(handle.ProcessID),
                    &signal_info,
                    WEXITED | WNOHANG | WNOWAIT
                    ) != 0
                )
                {
                    auto error = errno;
                    if (error == ECHILD)
                    {
                        //
                        // Child process exited.
                        //
                        is_running = false;
                        break;
                    }
                    else if (error != EINTR)
                    {
                        //
                        // Wait failed due to other reasons.
                        //
                        GX_LOG(LogPlatform, Error,
                            "Wait for process failed: {} ({}: `{}`)\n",
                            handle.ProcessID,
                            error,
                            strerror(error)
                        );

                        break;
                    }
                }
                else
                {
                    //
                    // Check whether signal points to waited pid.
                    //

                    is_running = (signal_info.si_pid != handle.ProcessID);
                    break;
                }
            }

            if (!is_running)
            {
                //
                // Try to wait anyway.
                //
                Wait(handle, exit_code);
            }
        }

        return is_running;
    }

    bool Process::Wait(
        ProcessHandle& handle,
        int32_t& exit_code
    ) noexcept
    {
        for (;;)
        {
            siginfo_t status{};

            if (waitid(P_PID, static_cast<id_t>(handle.ProcessID), &status, WEXITED) != 0)
            {
                auto error = errno;

                if (error == ECHILD)
                {
                    //
                    // Other wait operation succeeded before us / process already exited.
                    //
    
                    exit_code = 0;
                    return true;
                }
                else if (error != EINTR)
                {
                    GX_LOG(LogPlatform, Error, "Failed to wait for process: {}\n", strerror(error));
                    exit_code = -1;
                    return false;
                }
            }
            else
            {
                GX_ASSERT(status.si_pid == handle.ProcessID);
                exit_code = (status.si_code == CLD_EXITED) ? status.si_status : -1;
                return true;
            }
        }
    }

    void Process::Terminate(
        ProcessHandle& handle,
        bool tree
    ) noexcept
    {
        if (tree)
        {
            GX_LOG(LogPlatform, Error, "Killing process children is not supported right now\n");
        }

        kill(handle.ProcessID, SIGTERM);
    }
        
    ProcessResult Process::Execute(
        const char* path,
        const char* params,
        const char* working_directory,
        std::string* out_stdout,
        std::string* out_stderr
    ) noexcept
    {
        std::array<PipeHandle, 2> pipe_read{};
        std::array<PipeHandle, 2> pipe_write{};

        const auto redirect_output = (out_stdout != nullptr || out_stderr != nullptr);

        if (redirect_output)
        {
            for (size_t i = 0; i < std::size(pipe_read); ++i)
            {
                if (!Pipe::Create(pipe_read[i], pipe_write[i]))
                {
                    GX_ASSERTF(false, "CAnnot create pipe");
                }
            }
        }

        auto&& handle = Process::Create(
            path,
            params,
            working_directory,
            CreateProcessFlags::None,
            nullptr,
            nullptr,
            &pipe_write[0],
            &pipe_write[1]
        );

        ProcessResult result;
        int32_t exit_code;

        if (handle.IsValid())
        {
            if (redirect_output)
            {
                std::array<std::string*, 2> outputs{{out_stdout, out_stderr}};

                do
                {
                    Pipe::Read(outputs.data(), pipe_read.data(), 2);
                    Threading::YieldThread();
                } while (Process::IsRunning(handle, exit_code));

                Pipe::Read(outputs.data(), pipe_read.data(), 2);
            }
            else
            {
                Process::Wait(handle, exit_code);
            }

            Close(handle);

            result.StatusCode = Status::Success;
            result.ExitCode = exit_code;
        }
        else
        {
            if (out_stdout != nullptr)
            {
                out_stdout->clear();
            }

            if (out_stderr != nullptr)
            {
                out_stderr->clear();
            }

            GX_LOG(LogPlatform, Error, "Cannot create process: `{}`\n", path);

            result.ExitCode = 0;
            result.StatusCode = Diagnostics::GetStatusFromErrno(errno);
        }

        if (redirect_output)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                Pipe::Close(pipe_read[i], pipe_write[i]);
            }
        }

        return result;
    }

    DateTime Process::GetLinkTime() noexcept
    {
        return DateTime::Create(1970, 1, 1);
    }

    ProcessId Process::GetCurrent() noexcept
    {
        return {
            getpid()
        };
    }
}
