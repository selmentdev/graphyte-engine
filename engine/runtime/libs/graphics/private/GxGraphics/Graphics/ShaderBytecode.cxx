#include <GxGraphics/Graphics/ShaderBytecode.hxx>
#include <GxBase/Hash/XXHash.hxx>
#include <GxBase/Compression.hxx>
#include <GxBase/Storage/BinaryFormat.hxx>

namespace Graphyte::Graphics
{
    GRAPHICS_API Storage::Archive& operator<<(Storage::Archive& archive, ShaderBytecode& bytecode) noexcept
    {
        constexpr const Compression::CompressionMethod CompressUsing = Compression::CompressionMethod::LZ4HC;

        Storage::BinaryFormatHeader header{
            .Signature = Storage::BinarySignature{ 0xb084f8149e928dd6 },
            .Version   = Storage::BinaryFormatVersion{ 0, 0 },
            .Encoding  = ByteEncoding::LittleEndian,
        };

        archive << header;

        GX_ASSERT(header.Signature == Storage::BinarySignature{ 0xb084f8149e928dd6 });
        GX_ASSERT(header.Version == (Storage::BinaryFormatVersion{ 0, 0 }));
        GX_ASSERT(header.Encoding == ByteEncoding::LittleEndian);
        GX_ASSERT(header.CustomFlags == 0);
        GX_ASSERT(header.FileSize == 0);
        GX_ASSERT(header.OffsetToFirstBlock == 0);

        Compression::CompressionMethod compression_method = CompressUsing;
        archive << compression_method;
        GX_ASSERT(compression_method == CompressUsing);

        archive << bytecode.Platform;
        archive << bytecode.RenderAPI;
        archive << bytecode.Profile;
        archive << bytecode.Stage;
        archive << bytecode.Flags;

        uint64_t bytecode_checksum{};
        Hash::XXHash64 hash{ 0 };

        uint64_t bytecode_size{};

        std::vector<std::byte> data{};

        if (archive.IsLoading())
        {
            archive << bytecode_checksum;
            archive << bytecode_size;
            archive << data;

            bytecode.Bytecode.resize(static_cast<size_t>(bytecode_size));

            [[maybe_unused]] bool result = Compression::DecompressBlock(
                CompressUsing,
                bytecode.Bytecode,
                data);

            GX_ASSERT(result);

            hash.Update(std::data(bytecode.Bytecode), std::size(bytecode.Bytecode));

            uint64_t computed_checksum{ hash.GetValue() };
            (void)computed_checksum;

            GX_ASSERT(computed_checksum == bytecode_checksum);
        }
        else
        {
            hash.Update(std::data(bytecode.Bytecode), std::size(bytecode.Bytecode));
            bytecode_checksum = hash.GetValue();

            bytecode_size = static_cast<uint64_t>(std::size(bytecode.Bytecode));

            [[maybe_unused]] bool result = Compression::CompressBlock(
                CompressUsing,
                data,
                bytecode.Bytecode);

            GX_ASSERT(result);

            archive << bytecode_checksum;
            archive << bytecode_size;
            archive << data;
        }

        GX_ASSERT(archive.GetSize() == archive.GetPosition());

        return archive;
    }
}
