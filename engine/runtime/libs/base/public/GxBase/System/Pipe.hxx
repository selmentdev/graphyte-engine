#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte::System
{
    struct PipeHandle final
    {
#if GRAPHYTE_PLATFORM_WINDOWS || GRAPHYTE_PLATFORM_UWP
        HANDLE Handle;
#elif GRAPHYTE_PLATFORM_POSIX
        int Descriptor;
#endif
    };

    class BASE_API Pipe final
    {
    public:
        static bool Create(
            PipeHandle& read,
            PipeHandle& write
        ) noexcept;

        static void Close(
            PipeHandle& read,
            PipeHandle& write
        ) noexcept;

        static std::string ReadString(
            PipeHandle& handle
        ) noexcept;

        static std::vector<uint8_t> ReadBytes(
            PipeHandle& handle
        ) noexcept;

        static bool WriteString(
            PipeHandle& handle,
            std::string_view value
        ) noexcept;

        static bool WriteBytes(
            PipeHandle& handle,
            const void* buffer,
            size_t buffer_size,
            size_t* processed
        ) noexcept;

        static void Read(
            std::string* strings[],
            PipeHandle pipes[],
            size_t count
        ) noexcept;
    };
}
