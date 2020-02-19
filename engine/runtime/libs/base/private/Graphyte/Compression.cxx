#include <Graphyte/Compression.hxx>
#include <Graphyte/System.hxx>
#include <Graphyte/Diagnostics.hxx>

#include <lz4.h>
#include <lz4hc.h>

#if GRAPHYTE_SDKS_WITH_ZLIB
#include <zlib.h>
#endif


#if GRAPHYTE_SDKS_WITH_ZLIB
namespace Graphyte
{
    struct ZlibHelper final
    {
        static constexpr int DEFAULT_BIT_WINDOW = 15;

        static void* Alloc(
            [[maybe_unused]] void* context,
            unsigned int size,
            unsigned int count
        ) noexcept
        {
            return malloc(static_cast<size_t>(size) * static_cast<size_t>(count));
        }

        static void Free(
            [[maybe_unused]] void* context,
            void* pointer
        ) noexcept
        {
            return free(pointer);
        }

        static bool CompressMemory(
            void* compressed_buffer,
            size_t& compressed_size,
            const void* decompressed_buffer,
            size_t decompressed_size,
            size_t bit_window
        ) noexcept
        {
            auto z_compressed_size   = static_cast<uLongf>(compressed_size);
            auto z_decompressed_size = static_cast<uLongf>(decompressed_size);
            bool result = false;

            if (bit_window == ZlibHelper::DEFAULT_BIT_WINDOW)
            {
                result = compress(
                    reinterpret_cast<Bytef*>(compressed_buffer),
                    &z_compressed_size,
                    reinterpret_cast<const Bytef*>(decompressed_buffer),
                    z_decompressed_size
                ) == Z_OK;
            }
            else
            {
                z_stream stream{
                    .next_in   = const_cast<z_const Bytef*>(reinterpret_cast<const Bytef*>(decompressed_buffer)),
                    .avail_in  = static_cast<uInt>(z_decompressed_size),
                    .next_out  = reinterpret_cast<Bytef*>(compressed_buffer),
                    .avail_out = static_cast<uInt>(z_compressed_size),
                    .zalloc    = &ZlibHelper::Alloc,
                    .zfree     = &ZlibHelper::Free,
                    .opaque    = nullptr,
                };

                int status = deflateInit2_(
                    &stream,
                    Z_DEFAULT_COMPRESSION,
                    Z_DEFLATED,
                    static_cast<int>(bit_window),
                    MAX_MEM_LEVEL,
                    Z_DEFAULT_STRATEGY,
                    ZLIB_VERSION,
                    static_cast<int>(sizeof(z_stream))
                );

                if (status == Z_OK)
                {
                    status = deflate(&stream, Z_FINISH);

                    if (status == Z_STREAM_END)
                    {
                        z_compressed_size = stream.total_out;

                        status = deflateEnd(&stream);

                        if (status == Z_OK)
                        {
                            result = true;
                        }
                        else
                        {
                            GX_ASSERTF(false, "Failed to decompress memory");
                        }
                    }
                    else
                    {
                        GX_ASSERTF(false, "Failed to decompress memory");
                        deflateEnd(&stream);
                    }
                }
                else
                {
                    GX_ASSERTF(false, "Cannot compress memory");
                }
            }

            compressed_size = static_cast<size_t>(z_compressed_size);
            return result;
        }

        static bool DecompressMemory(
            void* decompressed_buffer,
            size_t decompressed_size,
            const void* compressed_buffer,
            size_t compressed_size,
            size_t bit_window
        ) noexcept
        {
            auto z_compressed_size   = static_cast<uLongf>(compressed_size);
            auto z_decompressed_size = static_cast<uLongf>(decompressed_size);

            z_stream stream{
                .next_in   = const_cast<z_const Bytef*>(reinterpret_cast<const Bytef*>(compressed_buffer)),
                .avail_in  = static_cast<uInt>(z_compressed_size),
                .next_out  = reinterpret_cast<Bytef*>(decompressed_buffer),
                .avail_out = static_cast<uInt>(z_decompressed_size),
                .zalloc    = &ZlibHelper::Alloc,
                .zfree     = &ZlibHelper::Free,
                .opaque    = nullptr,
            };

            int result = inflateInit2_(
                &stream,
                static_cast<int>(bit_window),
                ZLIB_VERSION,
                static_cast<int>(sizeof(z_stream))
            );

            if (result != Z_OK)
            {
                return false;
            }

            result = inflate(&stream, Z_FINISH);

            if (result == Z_STREAM_END)
            {
                z_decompressed_size = stream.total_out;
            }

            result = inflateEnd(&stream);

            //GX_LOG_WHEN(result == Z_MEM_ERROR, Log)
            GX_ASSERT(result != Z_MEM_ERROR);
            GX_ASSERT(result != Z_BUF_ERROR);
            GX_ASSERT(result != Z_DATA_ERROR);

            bool success = (result == Z_OK);

            GX_ASSERT(decompressed_size == static_cast<size_t>(z_decompressed_size));

            return success;
        }
    };
}
#endif

namespace Graphyte
{
#if GRAPHYTE_SDKS_WITH_ZLIB
    constexpr const int BitWindow = ZlibHelper::DEFAULT_BIT_WINDOW;
#endif

    BASE_API size_t Compression::MemoryBound(
        CompressionMethod method,
        size_t size
    ) noexcept
    {
        switch (method)
        {
        case CompressionMethod::LZ4:
        case CompressionMethod::LZ4HC:
            {
                if (size <= static_cast<size_t>(LZ4_MAX_INPUT_SIZE))
                {
                    return static_cast<size_t>(LZ4_compressBound(static_cast<int>(size)));
                }

                break;
            }
#if GRAPHYTE_SDKS_WITH_ZLIB
        case CompressionMethod::Zlib:
            {
                if constexpr (BitWindow == ZlibHelper::DEFAULT_BIT_WINDOW)
                {
                    return static_cast<size_t>(compressBound(static_cast<uLong>(size)));
                }
                else
                {
                    return size + ((size + 7U) >> 3U) + ((size + 63U) >> 6U) + 5U + 6U;
                }
            }
#endif
        default:
            {
                GX_LOG(LogPlatform, Error, "Unknown compression method: {}\n", static_cast<int32_t>(method));
                break;
            }
        }

        return 0;
    }

    BASE_API bool Compression::CompressBlock(
        CompressionMethod method,
        void* output_buffer,
        size_t& output_size,
        const void* input_buffer,
        size_t input_size
    ) noexcept
    {
        switch (method)
        {
        case CompressionMethod::LZ4HC:
        case CompressionMethod::LZ4:
            {
                if (output_size > static_cast<size_t>(LZ4_MAX_INPUT_SIZE) || input_size > static_cast<size_t>(LZ4_MAX_INPUT_SIZE))
                {
                    return false;
                }

                int result{};

                if (method == CompressionMethod::LZ4HC)
                {
                    result = LZ4_compress_HC(
                        static_cast<const char*>(input_buffer),
                        static_cast<char*>(output_buffer),
                        static_cast<int>(input_size),
                        static_cast<int>(output_size),
                        LZ4HC_CLEVEL_OPT_MIN
                    );
                }
                else
                {
                    result = LZ4_compress_default(
                        static_cast<const char*>(input_buffer),
                        static_cast<char*>(output_buffer),
                        static_cast<int>(input_size),
                        static_cast<int>(output_size)
                    );
                }

                if (result > 0)
                {
                    output_size = static_cast<size_t>(result);
                    return true;
                }

                break;
            }
#if GRAPHYTE_SDKS_WITH_ZLIB
        case CompressionMethod::Zlib:
            {
                return ZlibHelper::CompressMemory(
                    output_buffer,
                    output_size,
                    input_buffer,
                    input_size,
                    BitWindow
                );
            }
#endif
        default:
            {
                GX_LOG(LogPlatform, Error, "Unknown compression method: {}\n", static_cast<int32_t>(method));
                break;
            }
        }

        output_size = 0;
        return false;
    }

    BASE_API bool Compression::DecompressBlock(
        CompressionMethod method,
        void* output_buffer,
        size_t output_size,
        const void* input_buffer,
        size_t input_size
    ) noexcept
    {
        switch (method)
        {
        case CompressionMethod::LZ4HC:
        case CompressionMethod::LZ4:
            {
                if (output_size > static_cast<size_t>(LZ4_MAX_INPUT_SIZE) || input_size > static_cast<size_t>(LZ4_MAX_INPUT_SIZE))
                {
                    return false;
                }

                int result = LZ4_decompress_safe(
                    static_cast<const char*>(input_buffer),
                    static_cast<char*>(output_buffer),
                    static_cast<int>(input_size),
                    static_cast<int>(output_size)
                );

                if (result > 0 && static_cast<size_t>(static_cast<unsigned int>(result)) == output_size)
                {
                    return true;
                }

                break;
            }
#if GRAPHYTE_SDKS_WITH_ZLIB
        case CompressionMethod::Zlib:
            {
                return ZlibHelper::DecompressMemory(
                    output_buffer,
                    output_size,
                    input_buffer,
                    input_size,
                    BitWindow
                );
            }
#endif
        default:
            {
                GX_LOG(LogPlatform, Error, "Unknown compression method: {}\n", static_cast<int32_t>(method));
                break;
            }
        }

        return false;
    }

    BASE_API bool Compression::CompressBlock(
        CompressionMethod method,
        std::vector<std::byte>& output,
        notstd::span<const std::byte> input
    ) noexcept
    {
        if (input.empty())
        {
            return false;
        }

        size_t required = Compression::MemoryBound(method, std::size(input));
        output.resize(required);

        bool result = Compression::CompressBlock(
            method,
            std::data(output),
            required,
            std::data(input),
            std::size(input)
        );

        if (result)
        {
            output.resize(required);
        }
        else
        {
            output.clear();
        }

        output.shrink_to_fit();

        return result;
    }

    BASE_API bool Compression::DecompressBlock(
        CompressionMethod method,
        std::vector<std::byte>& output,
        notstd::span<const std::byte> input
    ) noexcept
    {
        if (input.empty())
        {
            return false;
        }

        return Compression::DecompressBlock(
            method,
            std::data(output),
            std::size(output),
            std::data(input),
            std::size(input)
        );
    }

    BASE_API bool Compression::CompressString(
        CompressionMethod method,
        std::vector<std::byte>& output,
        std::string_view input
    ) noexcept
    {
        size_t size = MemoryBound(method, input.size());
        output.resize(size);

        bool result = Compression::CompressBlock(
            method,
            std::data(output),
            size,
            std::data(input),
            std::size(input)
        );

        if (result)
        {
            output.resize(size);
        }
        else
        {
            output.clear();
        }

        return result;
    }

    BASE_API bool Compression::DecompressString(
        CompressionMethod method,
        std::string& output,
        const std::vector<std::byte>& input
    ) noexcept
    {
        if (input.empty())
        {
            return false;
        }

        return Compression::DecompressBlock(
            method,
            std::data(output),
            std::size(output),
            std::data(input),
            std::size(input)
        );
    }
}
