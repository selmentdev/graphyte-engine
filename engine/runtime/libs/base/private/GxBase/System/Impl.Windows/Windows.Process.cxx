#include <GxBase/System/Process.hxx>
#include <GxBase/System/Pipe.hxx>
#include <GxBase/String.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/Flags.hxx>
#include <GxBase/Threading/Thread.hxx>
#include <GxBase/System/Impl.Windows/Windows.Helpers.hxx>

#include <shellapi.h>
#include <ShlObj.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <DbgHelp.h>

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
        SECURITY_ATTRIBUTES security_attributes{
            .nLength              = sizeof(SECURITY_ATTRIBUTES),
            .lpSecurityDescriptor = nullptr,
            .bInheritHandle       = TRUE,
        };

        DWORD dw_create_flags = NORMAL_PRIORITY_CLASS;

        if (Flags::Has(flags, CreateProcessFlags::Detached))
        {
            dw_create_flags |= DETACHED_PROCESS;
        }

        DWORD dw_flags = 0;
        WORD w_show_window_flags = SW_HIDE;

        if (Flags::Has(flags, CreateProcessFlags::Hidden))
        {
            dw_flags = STARTF_USESHOWWINDOW;
        }
        else if (Flags::Has(flags, CreateProcessFlags::Minimized))
        {
            dw_flags = STARTF_USESHOWWINDOW;
            w_show_window_flags = SW_SHOWMINNOACTIVE;
        }

        HANDLE native_stdin_pipe{ nullptr };
        HANDLE native_stdout_pipe{ nullptr };
        HANDLE native_stderr_pipe{ nullptr };

        if (pipe_stdin != nullptr && pipe_stdout != nullptr && pipe_stderr != nullptr)
        {
            dw_flags |= STARTF_USESTDHANDLES;
            native_stdin_pipe = pipe_stdin->Handle;
            native_stdout_pipe = pipe_stdout->Handle;
            native_stderr_pipe = pipe_stderr->Handle;
        }

        STARTUPINFOW startup_info{
            .cb              = sizeof(startup_info),
            .lpReserved      = nullptr,
            .lpDesktop       = nullptr,
            .lpTitle         = nullptr,
            .dwX             = static_cast<DWORD>(CW_USEDEFAULT),
            .dwY             = static_cast<DWORD>(CW_USEDEFAULT),
            .dwXSize         = static_cast<DWORD>(CW_USEDEFAULT),
            .dwYSize         = static_cast<DWORD>(CW_USEDEFAULT),
            .dwXCountChars   = 0,
            .dwYCountChars   = 0,
            .dwFillAttribute = 0,
            .dwFlags         = dw_flags,
            .wShowWindow     = w_show_window_flags,
            .cbReserved2     = 0,
            .lpReserved2     = nullptr,
            .hStdInput       = native_stdin_pipe,
            .hStdOutput      = native_stdout_pipe,
            .hStdError       = native_stderr_pipe,
        };

        PROCESS_INFORMATION process_information{};

        BOOL created = CreateProcessW(
            path != nullptr ? System::Impl::WidenString(path).data() : nullptr,
            params != nullptr ? System::Impl::WidenString(params).data() : nullptr,
            &security_attributes,
            &security_attributes,
            TRUE,
            dw_create_flags,
            nullptr,
            working_directory != nullptr ? System::Impl::WidenString(working_directory).data() : nullptr,
            &startup_info,
            &process_information
        );

        if (created == FALSE)
        {
            GX_ASSERTF(false, "Failed to create process: {}", Diagnostics::GetMessageFromSystemError());

            if (id != nullptr)
            {
                (*id) = ProcessId{};
            }

            return ProcessHandle{};
        }

        if (id != nullptr)
        {
            (*id) = ProcessId{ process_information.dwProcessId };
        }

        CloseHandle(process_information.hThread);

        return ProcessHandle{ process_information.hProcess };
    }

    void Process::Close(
        ProcessHandle& handle
    ) noexcept
    {
        if (handle.Handle != nullptr)
        {
            CloseHandle(handle.Handle);
            handle.Handle = nullptr;
        }
    }

    bool Process::IsRunning(
        ProcessHandle& handle,
        int32_t& exit_code
    ) noexcept
    {
        DWORD result = WaitForSingleObject(handle.Handle, 0);

        if (result == WAIT_OBJECT_0)
        {
            DWORD code{};

            bool active = !!GetExitCodeProcess(handle.Handle, &code);

            if (active && code != STILL_ACTIVE)
            {
                exit_code = static_cast<int32_t>(code);
                return false;
            }
        }

        exit_code = 0;
        bool running = (result == WAIT_TIMEOUT);
        return running;
    }

    bool Process::Wait(
        ProcessHandle& handle,
        int32_t& exit_code
    ) noexcept
    {
        DWORD result = WaitForSingleObject(handle.Handle, INFINITE);

        if (result == WAIT_OBJECT_0)
        {
            DWORD code{};

            bool active = !!GetExitCodeProcess(handle.Handle, &code);

            if (active && code != STILL_ACTIVE)
            {
                exit_code = static_cast<int32_t>(code);
                return true;
            }
        }

        exit_code = -1;
        return false;
    }


    void Process::Terminate(
        ProcessHandle& handle,
        bool tree
    ) noexcept
    {
        if (tree)
        {
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

            if (snapshot != INVALID_HANDLE_VALUE)
            {
                DWORD process_id = GetProcessId(handle.Handle);

                PROCESSENTRY32 entry{
                    .dwSize = sizeof(PROCESSENTRY32),
                };

                if (Process32First(snapshot, &entry) != FALSE)
                {
                    do
                    {
                        if (entry.th32ParentProcessID == process_id)
                        {
                            HANDLE child_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

                            if (child_handle != nullptr)
                            {
                                ProcessHandle child{ child_handle };
                                Terminate(child, tree);
                            }
                        }
                    } while (Process32Next(snapshot, &entry) != FALSE);
                }

                CloseHandle(snapshot);
            }
        }

        TerminateProcess(handle.Handle, 0);
    }

    ProcessResult Process::Execute(
        const char* path,
        const char* params,
        const char* working_directory,
        std::string* out_stdout,
        std::string* out_stderr
    ) noexcept
    {
        SECURITY_ATTRIBUTES security_attributes{
            .nLength              = sizeof(SECURITY_ATTRIBUTES),
            .lpSecurityDescriptor = nullptr,
            .bInheritHandle       = TRUE,
        };

        DWORD dw_create_flags = NORMAL_PRIORITY_CLASS | DETACHED_PROCESS;

        DWORD dw_flags = STARTF_USESHOWWINDOW;
        WORD w_show_window_flags = SW_SHOWMINNOACTIVE;

        std::array<PipeHandle, 2> pipe_read{};
        std::array<PipeHandle, 2> pipe_write{};

        bool const redirect_output = (out_stdout != nullptr || out_stderr != nullptr);

        if (redirect_output)
        {
            dw_flags |= STARTF_USESTDHANDLES;

            for (size_t i = 0; i < std::size(pipe_read); ++i)
            {
                CreatePipe(&pipe_read[i].Handle, &pipe_write[i].Handle, &security_attributes, 0);
                SetHandleInformation(pipe_read[i].Handle, HANDLE_FLAG_INHERIT, 0);
            }
        }

        ProcessResult result;

        STARTUPINFOW startup_info{
            .cb              = sizeof(startup_info),
            .lpReserved      = nullptr,
            .lpDesktop       = nullptr,
            .lpTitle         = nullptr,
            .dwX             = static_cast<DWORD>(CW_USEDEFAULT),
            .dwY             = static_cast<DWORD>(CW_USEDEFAULT),
            .dwXSize         = static_cast<DWORD>(CW_USEDEFAULT),
            .dwYSize         = static_cast<DWORD>(CW_USEDEFAULT),
            .dwXCountChars   = 0,
            .dwYCountChars   = 0,
            .dwFillAttribute = 0,
            .dwFlags         = dw_flags,
            .wShowWindow     = w_show_window_flags,
            .cbReserved2     = 0,
            .lpReserved2     = nullptr,
            .hStdInput       = GetStdHandle(STD_INPUT_HANDLE),
            .hStdOutput      = pipe_write[0].Handle,
            .hStdError       = pipe_write[1].Handle,
        };

        PROCESS_INFORMATION process_information{};

        if (CreateProcessW(
            path != nullptr ? System::Impl::WidenString(path).data() : nullptr,
            params != nullptr ? System::Impl::WidenString(params).data() : nullptr,
            &security_attributes,
            &security_attributes,
            TRUE,
            dw_create_flags,
            nullptr,
            working_directory != nullptr ? System::Impl::WidenString(working_directory).data() : nullptr,
            &startup_info,
            &process_information
        ))
        {
            if (redirect_output)
            {
                std::array<std::string*, 2> outputs{ {
                    out_stdout,
                    out_stderr
                } };

                ProcessHandle handle{ process_information.hProcess };

                int32_t exit_code{};

                do
                {
                    Pipe::Read(outputs.data(), pipe_read.data(), 2);
                    Threading::YieldThread();
                } while (Process::IsRunning(handle, exit_code));

                Pipe::Read(outputs.data(), pipe_read.data(), 2);
            }
            else
            {
                WaitForSingleObject(process_information.hProcess, INFINITE);
            }

            DWORD dw_exit_code{};
            GetExitCodeProcess(process_information.hProcess, &dw_exit_code);


            CloseHandle(process_information.hProcess);
            CloseHandle(process_information.hThread);

            result.StatusCode = Status::Success;
            result.ExitCode = static_cast<int32_t>(dw_exit_code);
        }
        else
        {

            if (redirect_output)
            {
                for (size_t i = 0; i < std::size(pipe_write); ++i)
                {
                    CloseHandle(pipe_write[i].Handle);
                }
            }

            result.ExitCode = 0;
            result.StatusCode = Diagnostics::GetStatusFromSystemError();
        }

        if (redirect_output)
        {
            for (size_t i = 0; i < std::size(pipe_read); ++i)
            {
                CloseHandle(pipe_read[i].Handle);
            }
        }

        return result;
    }

    DateTime Process::GetLinkTime() noexcept
    {
        HMODULE handle = GetModuleHandleW(nullptr);
        IMAGE_NT_HEADERS* header = ImageNtHeader(handle);

        GX_ASSERT(header != nullptr);
        if (header != nullptr)
        {
            return DateTime::FromUnixTimestamp(header->FileHeader.TimeDateStamp);
        }

        return {};
    }

    ProcessId Process::GetCurrent() noexcept
    {
        return {
            GetCurrentProcessId()
        };
    }
}
