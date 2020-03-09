#include <Graphyte/System/Pipe.hxx>

namespace Graphyte::System
{
    bool Pipe::Create(
        PipeHandle& read,
        PipeHandle& write
    ) noexcept
    {
        SECURITY_ATTRIBUTES security_attributes{
            .nLength = sizeof(SECURITY_ATTRIBUTES),
            .lpSecurityDescriptor = nullptr,
            .bInheritHandle = TRUE,
        };

        if (CreatePipe(
            &read.Handle,
            &write.Handle,
            &security_attributes,
            0) == FALSE)
        {
            return false;
        }

        //if (SetHandleInformation(read.Handle, HANDLE_FLAG_INHERIT, 0) == FALSE)
        //{
        //    return false;
        //}

        return true;
    }

    void Pipe::Close(
        PipeHandle& read,
        PipeHandle& write
    ) noexcept
    {
        if (read.Handle != nullptr && read.Handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(read.Handle);
        }

        if (write.Handle != nullptr && write.Handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(write.Handle);
        }
    }

    std::string Pipe::ReadString(
        PipeHandle& handle
    ) noexcept
    {
        std::string output{};

        DWORD dw_available{};

        if (PeekNamedPipe(handle.Handle, nullptr, 0, nullptr, &dw_available, nullptr) != FALSE)
        {
            if (dw_available != 0)
            {
                auto buffer = std::make_unique<char[]>(dw_available + 1);

                DWORD dw_read{};

                if (ReadFile(handle.Handle, buffer.get(), dw_available, &dw_read, nullptr) != FALSE)
                {
                    if (dw_read != 0)
                    {
                        buffer[dw_read] = '\0';
                        output += buffer.get();
                    }
                }
            }
        }

        return output;
    }

    std::vector<uint8_t> Pipe::ReadBytes(
        PipeHandle& handle
    ) noexcept
    {
        DWORD dw_available{ 0 };

        std::vector<uint8_t> result{};

        if (PeekNamedPipe(handle.Handle, nullptr, 0, nullptr, &dw_available, nullptr) != FALSE)
        {
            if (dw_available != 0)
            {
                result.resize(dw_available);
                DWORD dw_read{ 0 };

                if (ReadFile(handle.Handle, std::data(result), dw_available, &dw_read, nullptr) != FALSE)
                {
                    if (dw_read < dw_available)
                    {
                        result.resize(dw_read);
                    }
                }
                else
                {
                    result.clear();
                }
            }
        }

        return result;
    }

    bool Pipe::WriteString(
        PipeHandle& handle,
        std::string_view value
    ) noexcept
    {
        if (handle.Handle == nullptr || value.length() == 0)
        {
            return false;
        }

        std::string buffer{ value };
        buffer.append(1, '\n');
        
        size_t processed{};
        bool result = Pipe::WriteBytes(handle, std::data(buffer), std::size(buffer), &processed);

        return result && (processed == std::size(buffer));
    }

    bool Pipe::WriteBytes(
        PipeHandle& handle,
        const void* buffer,
        size_t buffer_size,
        size_t* processed
    ) noexcept
    {
        if (handle.Handle == nullptr || buffer_size == 0)
        {
            return false;
        }

        DWORD dw_written{ 0 };

        bool result = WriteFile(handle.Handle, buffer, static_cast<DWORD>(buffer_size), &dw_written, nullptr) != FALSE;

        if (processed != nullptr)
        {
            (*processed) = dw_written;
        }

        return result;
    }

    void Pipe::Read(
        std::string* strings[],
        PipeHandle pipes[],
        size_t count
    ) noexcept
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (strings[i] != nullptr && pipes[i].Handle != nullptr)
            {
                (*strings[i]) += Pipe::ReadString(pipes[i]);
            }
        }
    }
}
