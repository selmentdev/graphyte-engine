#include "Base.pch.hxx"
#include <Graphyte/Platform.hxx>
#include <Graphyte/Platform/Pipe.hxx>

namespace Graphyte::Platform
{
    bool Pipe::Create(
        PipeHandle& read,
        PipeHandle& write
    ) noexcept
    {
        int native_handles[2];

        if (pipe(native_handles) == -1)
        {
            GX_LOG(LogPlatform, Error, "Cannot create pipe: errno = {}, message = `{}`\n", errno, strerror(errno));

            return false;
        }

        read.Descriptor = native_handles[0];
        write.Descriptor = native_handles[1];

        return true;
    }
        
    void Pipe::Close(
        PipeHandle& read,
        PipeHandle& write
    ) noexcept
    {
        if (read.Descriptor != 0)
        {
            close(read.Descriptor);
        }

        if (write.Descriptor != 0)
        {
            close(write.Descriptor);
        }
    }
        
    std::string Pipe::ReadString(
        PipeHandle& handle
    ) noexcept
    {
        std::string result{};

        int n_available{};
    
        if (ioctl(handle.Descriptor, FIONREAD, &n_available) == 0)
        {
            if (n_available > 0)
            {
                result.resize(static_cast<size_t>(n_available));

                [[maybe_unused]] ssize_t processed = read(
                    handle.Descriptor,
                    std::data(result),
                    std::size(result)
                );
            }
        }
        else
        {
            GX_LOG(LogPlatform, Error, "Cannot read string from pipe\n");
        }

        return result;
    }
        
    std::vector<uint8_t> Pipe::ReadBytes(
        PipeHandle& handle
    ) noexcept
    {
        std::vector<uint8_t> result{};

        int n_available{};

        if (ioctl(handle.Descriptor, FIONREAD, &n_available) == 0)
        {
            if (n_available > 0)
            {
                result.resize(static_cast<size_t>(n_available));
                [[maybe_unused]] ssize_t processed = read(
                    handle.Descriptor,
                    std::data(result),
                    std::size(result)
                );
            }
        }
        else
        {
            GX_LOG(LogPlatform, Error, "Cannot read data from pipe\n");
        }

        return result;
    }
        
    bool Pipe::WriteString(
        PipeHandle& handle,
        std::string_view value
    ) noexcept
    {
        if (handle.Descriptor == 0 || value.length() == 0)
        {
            return false;
        }

        std::string buffer{ value };
        buffer.append(1, '\n');

        ssize_t written = write(
            handle.Descriptor,
            buffer.data(),
            buffer.size()
        );

        return static_cast<size_t>(written) == buffer.size();
    }
        
    bool Pipe::WriteBytes(
        PipeHandle& handle,
        const void* buffer,
        size_t buffer_size,
        size_t* processed
    ) noexcept
    {
        if (handle.Descriptor == 0 || buffer_size == 0)
        {
            return false;
        }

        ssize_t written = write(handle.Descriptor, buffer, buffer_size);

        if (processed != nullptr)
        {
            (*processed) = static_cast<size_t>(written);
        }

        return static_cast<size_t>(written) == buffer_size;
    }
        
    void Pipe::Read(
        std::string* strings[],
        PipeHandle pipes[],
        size_t count
    ) noexcept
    {
        for (size_t i = 0; i < count; ++i)
        {
            if (strings[i] != nullptr && pipes[i].Descriptor != 0)
            {
                (*strings[i]) += Pipe::ReadString(pipes[i]);
            }
        }
    }
}
