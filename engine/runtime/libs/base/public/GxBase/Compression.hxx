#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte::Compression
{
    //! \brief Compression methods available in engine.
    enum class CompressionMethod : uint32_t
    {
        LZ4,
        LZ4HC,
        ZLib,
        Default = LZ4,
    };


    //! \brief Computes memory bound for given buffer size and compression method.
    //!
    //! \param method   Provides a compression method.
    //! \param size     Provides size of uncompressed data.
    //!
    //! \return         The minimum number of bytes required to compress data of specified size.
    extern BASE_API size_t MemoryBound(
        CompressionMethod method,
        size_t size) noexcept;


    //! \brief Compresses memory block.
    //!
    //! \param method           Provides a compression method.
    //! \param output_buffer    Provides output buffer for compressed data.
    //! \param output_size      Provides size of output buffer.
    //! \param input_buffer     Provides input buffer to compress.
    //! \param input_size       Provides size of input buffer.
    //!
    //! \return Value indicating whether memory block was decompressed successfully.
    extern BASE_API bool CompressBlock(
        CompressionMethod method,
        void* output_buffer,
        size_t& output_size,
        const void* input_buffer,
        size_t input_size) noexcept;


    //! \brief Decompresses memory block.
    //!
    //! \param method          Provides a compression method.
    //! \param output_buffer   Points to output buffer for decompressed data.
    //! \param output_size     Provides size of output buffer.
    //! \param input_buffer    Points to input buffer to decompress.
    //! \param input_size      Provides size of input buffer.
    //!
    //! \return Value indicating whether memory block was decompressed successfully.
    extern BASE_API bool DecompressBlock(
        CompressionMethod method,
        void* output_buffer,
        size_t output_size,
        const void* input_buffer,
        size_t input_size) noexcept;

    extern BASE_API bool CompressBlock(
        CompressionMethod method,
        std::vector<std::byte>& output,
        notstd::span<const std::byte> input) noexcept;

    extern BASE_API bool DecompressBlock(
        CompressionMethod method,
        std::vector<std::byte>& output,
        notstd::span<const std::byte> input) noexcept;

    extern BASE_API bool CompressString(
        CompressionMethod method,
        std::vector<std::byte>& output,
        std::string_view input) noexcept;

    extern BASE_API bool DecompressString(
        CompressionMethod method,
        std::string& output,
        const std::vector<std::byte>& input) noexcept;

    //! \brief Compresses byte vector.
    //!
    //! \param method   Provides a compression method.
    //! \param output   Provides output vector for compressed data.
    //! \param input    Provides input vector data to compress.
    //!
    //! \return Value indicating whether memory block was compressed successfully.
    inline bool CompressBlock(
        CompressionMethod method,
        std::vector<std::byte>& output,
        const std::vector<std::byte>& input) noexcept
    {
        return Compression::CompressBlock(
            method,
            output,
            notstd::span<const std::byte>(input));
    }

    //! \brief Decompresses byte vector.
    //! \param method   Provides a compression method.
    //! \param output   Provides output vector for decompressed data.
    //! \param input    Provides input vector data to decompress.
    //!
    //! \return Value indicating whether memory block was decompressed successfully.
    //!
    //! \pre Output vector must contain enough place for decompressed data.
    inline bool DecompressBlock(
        CompressionMethod method,
        std::vector<std::byte>& output,
        const std::vector<std::byte>& input) noexcept
    {
        return Compression::DecompressBlock(
            method,
            output,
            notstd::span<const std::byte>(input));
    }
}
