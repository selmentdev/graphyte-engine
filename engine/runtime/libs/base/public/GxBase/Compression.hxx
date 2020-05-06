#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Span.hxx>

namespace Graphyte
{
    /**
     * @brief   Compression method available in engine.
     */
    enum class CompressionMethod : uint32_t
    {
        LZ4,                //!< LZ4 compressor.
        LZ4HC,              //!< LZ4HC compressor.
        Zlib,               //!< ZLIB compressor.
        Default = LZ4,      //!< Default compressor.
    };

    class Compression final
    {
    public:
        /**
         * @brief       Computes memory bound for given buffer size and compression method.
         *
         * @param[in]   method  Provides a compression method.
         * @param[in]   size    Provides size of uncompressed data.
         *
         * @return      The minimum number of bytes required to compress data of specified size.
         */
        BASE_API static size_t MemoryBound(
            CompressionMethod method,
            size_t size
        ) noexcept;

        /**
         * @brief       Compresses memory block.
         *
         * @param[in]   method          Provides a compression method.
         * @param[in]   output_buffer   Points to output buffer for compressed data.
         * @param[in]   output_size     Provides size of output buffer.
         * @param[in]   input_buffer    Points to input buffer to compress.
         * @param[in]   input_size      Provides size of input buffer.
         *
         * @return      Value indicating whether memory block was decompressed successfully.
         */
        BASE_API static bool CompressBlock(
            CompressionMethod method,
            void* output_buffer,
            size_t& output_size,
            const void* input_buffer,
            size_t input_size
        ) noexcept;

        /**
         * @brief       Decompresses memory block.
         *
         * @param[in]   method          Provides a compression method.
         * @param[in]   output_buffer   Points to output buffer for decompressed data.
         * @param[in]   output_size     Provides size of output buffer.
         * @param[in]   input_buffer    Points to input buffer to decompress.
         * @param[in]   input_size      Provides size of input buffer.
         *
         * @return      Value indicating whether memory block was decompressed successfully.
         *
         * @pre
         *              - output_buffer and input_buffer must not be nullptr
         *              - output_size and input_size must be valid
         */
        BASE_API static bool DecompressBlock(
            CompressionMethod method,
            void* output_buffer,
            size_t output_size,
            const void* input_buffer,
            size_t input_size
        ) noexcept;

        /**
         * @brief       Compresses byte vector.
         *
         * @param[in]   method      Provides a compression method.
         * @param[out]  output      Provides output vector for compressed data.
         * @param[in]   input       Provides input vector data to compress.
         *
         * @return      Value indicating whether memory block was compressed successfully.
         */
        static bool CompressBlock(
            CompressionMethod method,
            std::vector<std::byte>& output,
            const std::vector<std::byte>& input
        ) noexcept
        {
            return Compression::CompressBlock(
                method,
                output,
                notstd::span<const std::byte>(input)
            );
        }

        /**
         * @brief       Decompresses byte vector.
         * @param[in]   method      Provides a compression method.
         * @param[out]  output      Provides output vector for decompressed data.
         * @param[in]   input       Provides input vector data to decompress.
         *
         * @return      Value indicating whether memory block was decompressed successfully.
         *
         * @pre         Output vector must contain enough place for decompressed data.
         */
        static bool DecompressBlock(
            CompressionMethod method,
            std::vector<std::byte>& output,
            const std::vector<std::byte>& input
        ) noexcept
        {
            return Compression::DecompressBlock(
                method,
                output,
                notstd::span<const std::byte>(input)
            );
        }

        BASE_API static bool CompressBlock(
            CompressionMethod method,
            std::vector<std::byte>& output,
            notstd::span<const std::byte> input
        ) noexcept;

        BASE_API static bool DecompressBlock(
            CompressionMethod method,
            std::vector<std::byte>& output,
            notstd::span<const std::byte> input
        ) noexcept;

        BASE_API static bool CompressString(
            CompressionMethod method,
            std::vector<std::byte>& output,
            std::string_view input
        ) noexcept;

        BASE_API static bool DecompressString(
            CompressionMethod method,
            std::string& output,
            const std::vector<std::byte>& input
        ) noexcept;
    };
}
