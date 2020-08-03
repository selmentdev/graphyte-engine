#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Status.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte::Storage
{
    /// @brief Represents seek origin.
    enum struct SeekOrigin : uint32_t
    {
        /// Set position relative to beginning of stream.
        Begin,

        /// Set position relative to current position of stream.
        Current,

        /// Set position relative to end of stream.
        End,
    };

    /// @brief This interface represents concept of data stream.
    struct IStream
    {
        virtual ~IStream() noexcept = default;

        /// @brief Flushes internal buffers.
        ///
        /// @return The status code.
        virtual Status Flush() noexcept = 0;

        /// @brief Reads data to buffer.
        ///
        /// @param buffer    Returns data readed from stream
        /// @param processed Returns number of bytes read.
        ///
        /// @return The status code.
        virtual Status Read(
            notstd::span<std::byte> buffer,
            size_t& processed) noexcept = 0;

        /// @brief Writes data from buffer.
        ///
        /// @param buffer    Provides buffer with data to write.
        /// @param processed Returns number of bytes written.
        ///
        /// @return The status code.
        virtual Status Write(
            notstd::span<const std::byte> buffer,
            size_t& processed) noexcept = 0;

        /// @brief Gets size of stream.
        virtual int64_t GetSize() noexcept = 0;

        /// @brief Gets current position.
        virtual int64_t GetPosition() noexcept = 0;

        /// @brief Sets relative position in stream.
        ///
        /// @param value  Provides new position.
        /// @param origin Specifies how current position should be updated.
        ///
        /// @return The status code.
        virtual Status SetPosition(
            int64_t value,
            SeekOrigin origin) noexcept = 0;

        /// @brief Sets absolute position in stream.
        ///
        /// @param value Provides new absolute position.
        ///
        /// @return The status code.
        virtual Status SetPosition(
            int64_t value) noexcept = 0;
    };
}
