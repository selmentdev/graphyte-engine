#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::System
{
    struct PipeHandle final
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
        HANDLE Handle;
#elif GX_PLATFORM_POSIX
        int Descriptor;
#endif
    };

    class BASE_API Pipe final
    {
    public:
        /// @brief Creates new pipe
        ///
        /// @param read  Returns pipe handle for reading.
        /// @param write Returns pipe handle for writing.
        ///
        /// @return @c true when successeded, @c false otherwise.
        static bool Create(
            PipeHandle& read,
            PipeHandle& write) noexcept;

        /// @brief Closes pipe handles.
        ///
        /// @param read  Provides pipe handle for reading.
        /// @param write Provides pipe handle for writing.
        static void Close(
            PipeHandle& read,
            PipeHandle& write) noexcept;

        static std::string ReadString(
            PipeHandle& handle) noexcept;

        static std::vector<uint8_t> ReadBytes(
            PipeHandle& handle) noexcept;

        static bool WriteString(
            PipeHandle& handle,
            std::string_view value) noexcept;

        static bool WriteBytes(
            PipeHandle& handle,
            const void* buffer,
            size_t buffer_size,
            size_t* processed) noexcept;

        static void Read(
            std::string* strings[],
            PipeHandle pipes[],
            size_t count) noexcept;
    };
}
