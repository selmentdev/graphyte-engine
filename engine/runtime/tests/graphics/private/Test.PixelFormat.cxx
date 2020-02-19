#include <catch2/catch.hpp>
#include <Graphyte/Graphics/PixelFormat.hxx>

TEST_CASE("Pixel format tests")
{
    using Graphyte::Graphics::PixelFormat;
    using Graphyte::Graphics::PixelFormatProperties;

    SECTION("Getting surface information")
    {
        size_t bytes = 0;
        size_t row_bytes = 0;
        size_t rows = 0;

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::R8G8B8A8_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == (128 * 128 * 4));
        CHECK(row_bytes == (128 * 4));
        CHECK(rows == 128);

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::R32G32B32A32_FLOAT, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == (128 * 128 * 16));
        CHECK(row_bytes == (128 * 16));
        CHECK(rows == 128);

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::D16_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == (128 * 128 * 2));
        CHECK(row_bytes == (128 * 2));
        CHECK(rows == 128);

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::D24_UNORM_S8_UINT, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == (128 * 128 * 4));
        CHECK(row_bytes == (128 * 4));
        CHECK(rows == 128);

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::D32_FLOAT_S8X24_UINT, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == (128 * 128 * 8));
        CHECK(row_bytes == (128 * 8));
        CHECK(rows == 128);

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC1_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 8));
        CHECK(row_bytes == ((128 / 4) * 8));
        CHECK(rows == (128 / 4));

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC2_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 16));
        CHECK(row_bytes == ((128 / 4) * 16));
        CHECK(rows == (128 / 4));

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC3_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 16));
        CHECK(row_bytes == ((128 / 4) * 16));
        CHECK(rows == (128 / 4));

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC4_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 8));
        CHECK(row_bytes == ((128 / 4) * 8));
        CHECK(rows == (128 / 4));

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC5_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 16));
        CHECK(row_bytes == ((128 / 4) * 16));
        CHECK(rows == (128 / 4));

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC6H_UF16, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 16));
        CHECK(row_bytes == ((128 / 4) * 16));
        CHECK(rows == (128 / 4));

        PixelFormatProperties::GetSurfaceInfo(PixelFormat::BC7_UNORM, 128, 128, bytes, row_bytes, rows);
        CHECK(bytes == ((128 / 4) * (128 / 4) * 16));
        CHECK(row_bytes == ((128 / 4) * 16));
        CHECK(rows == (128 / 4));
    }

    SECTION("Getting image dimensions for mipmapped surfaces")
    {
        SECTION("Regular R8_G8_B8_A8")
        {
            auto const format = PixelFormat::R8G8B8A8_UNORM;
            auto const dimension = 64;
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 0, format) == 64);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 1, format) == 32);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 2, format) == 16);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 3, format) == 8);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 4, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 5, format) == 2);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 8, format) == 1);

            CHECK(PixelFormatProperties::GetImageHeight(dimension, 0, format) == 64);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 1, format) == 32);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 2, format) == 16);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 3, format) == 8);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 4, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 5, format) == 2);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 8, format) == 1);

            CHECK(PixelFormatProperties::GetImageDepth(dimension, 0, format) == 64);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 1, format) == 32);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 2, format) == 16);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 3, format) == 8);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 4, format) == 4);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 5, format) == 2);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 8, format) == 1);
        }

        SECTION("Regular R8_G8_B8_A8 - non-power-of-2")
        {
            auto const format = PixelFormat::R8G8B8A8_UNORM;
            auto const dimension = 96;
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 0, format) == 96);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 1, format) == 48);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 2, format) == 24);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 3, format) == 12);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 4, format) == 6);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 5, format) == 3);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 8, format) == 1);

            CHECK(PixelFormatProperties::GetImageHeight(dimension, 0, format) == 96);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 1, format) == 48);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 2, format) == 24);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 3, format) == 12);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 4, format) == 6);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 5, format) == 3);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 8, format) == 1);

            CHECK(PixelFormatProperties::GetImageDepth(dimension, 0, format) == 96);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 1, format) == 48);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 2, format) == 24);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 3, format) == 12);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 4, format) == 6);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 5, format) == 3);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 8, format) == 1);
        }

        SECTION("Compressed BC1")
        {
            auto const format = PixelFormat::BC1_UNORM;
            auto const dimension = 64;
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 0, format) == 64);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 1, format) == 32);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 2, format) == 16);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 3, format) == 8);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 4, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 5, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 6, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 7, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 8, format) == 4);

            CHECK(PixelFormatProperties::GetImageHeight(dimension, 0, format) == 64);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 1, format) == 32);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 2, format) == 16);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 3, format) == 8);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 4, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 5, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 6, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 7, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 8, format) == 4);

            CHECK(PixelFormatProperties::GetImageDepth(dimension, 0, format) == 64);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 1, format) == 32);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 2, format) == 16);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 3, format) == 8);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 4, format) == 4);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 5, format) == 2);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 8, format) == 1);
        }

        SECTION("Compressed BC1 - non-power-of-2")
        {
            auto const format = PixelFormat::BC1_UNORM;
            auto const dimension = 96;
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 0, format) == 96);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 1, format) == 48);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 2, format) == 24);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 3, format) == 12);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 4, format) == 6);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 5, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 6, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 7, format) == 4);
            CHECK(PixelFormatProperties::GetImageWidth(dimension, 8, format) == 4);

            CHECK(PixelFormatProperties::GetImageHeight(dimension, 0, format) == 96);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 1, format) == 48);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 2, format) == 24);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 3, format) == 12);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 4, format) == 6);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 5, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 6, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 7, format) == 4);
            CHECK(PixelFormatProperties::GetImageHeight(dimension, 8, format) == 4);

            CHECK(PixelFormatProperties::GetImageDepth(dimension, 0, format) == 96);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 1, format) == 48);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 2, format) == 24);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 3, format) == 12);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 4, format) == 6);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 5, format) == 3);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 6, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 7, format) == 1);
            CHECK(PixelFormatProperties::GetImageDepth(dimension, 8, format) == 1);
        }
    }

    SECTION("Estimating size of DDS images")
    {
        constexpr const size_t dds_signature_size = 4;
        constexpr const size_t dds_header_size = 124;
        constexpr const size_t dds_dxt10_header_size = 20;

        constexpr const size_t dds_standard_size = dds_signature_size + dds_header_size;
        constexpr const size_t dds_extended_size = dds_signature_size + dds_header_size + dds_dxt10_header_size;


        auto estimate_dds_pixel_buffer_size = [](uint32_t width, uint32_t height, uint32_t depth, uint32_t mips, uint32_t array_size, PixelFormat format) noexcept -> size_t
        {
            size_t size = 0;

            for (uint32_t array_index = 0; array_index < array_size; ++array_index)
            {
                for (uint32_t mip_index = 0; mip_index < mips; ++mip_index)
                {
                    size_t surface_size = PixelFormatProperties::GetStorageSize(format, width, height, depth, mip_index);
                    size += surface_size;
                }
            }

            return size;
        };


        //.\cube.dds
        //        width = 64
        //       height = 64
        //        depth = 1
        //    mipLevels = 7
        //    arraySize = 6
        //       format = BC1_UNORM
        //    dimension = Cube
        //   alpha mode = Unknown
        //       images = 42
        //   pixel size = 16 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 1, 7, 6, PixelFormat::BC1_UNORM) == (16592 - dds_standard_size));

        // .\cube_mip.dds
        //         width = 64
        //        height = 64
        //         depth = 1
        //     mipLevels = 4
        //     arraySize = 6
        //        format = BC1_UNORM
        //     dimension = Cube
        //    alpha mode = Opaque
        //        images = 24
        //    pixel size = 15 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 1, 4, 6, PixelFormat::BC1_UNORM) == (16468 - dds_extended_size));

        // .\cubearray.dds
        //         width = 64
        //        height = 64
        //         depth = 1
        //     mipLevels = 7
        //     arraySize = 18
        //        format = BC1_UNORM
        //     dimension = CubeArray
        //    alpha mode = Unknown
        //        images = 126
        //    pixel size = 48 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 1, 7, 18, PixelFormat::BC1_UNORM) == (49540 - dds_extended_size));

        // .\cubearray_mip.dds
        //         width = 64
        //        height = 64
        //         depth = 1
        //     mipLevels = 4
        //     arraySize = 18
        //        format = BC1_UNORM
        //     dimension = CubeArray
        //    alpha mode = Opaque
        //        images = 72
        //    pixel size = 47 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 1, 4, 18, PixelFormat::BC1_UNORM) == (49108 - dds_extended_size));

        // .\texture2d.DDS
        //         width = 64
        //        height = 64
        //         depth = 1
        //     mipLevels = 7
        //     arraySize = 1
        //        format = BC1_UNORM
        //     dimension = 2D
        //    alpha mode = Opaque
        //        images = 7
        //    pixel size = 2 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 1, 7, 1, PixelFormat::BC1_UNORM) == (2892 - dds_extended_size));

        // .\texture2d_mip.dds
        //         width = 64
        //        height = 64
        //         depth = 1
        //     mipLevels = 4
        //     arraySize = 1
        //        format = BC1_UNORM
        //     dimension = 2D
        //    alpha mode = Opaque
        //        images = 4
        //    pixel size = 2 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 1, 4, 1, PixelFormat::BC1_UNORM) == (2868 - dds_extended_size));

        // .\texture3d.dds
        //         width = 64
        //        height = 64
        //         depth = 18
        //     mipLevels = 1
        //     arraySize = 1
        //        format = BC1_UNORM
        //     dimension =  3D   alpha mode = Opaque
        //        images = 18
        //    pixel size = 36 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 18, 1, 1, PixelFormat::BC1_UNORM) == (37012 - dds_extended_size));

        
        // ASCII.dds
        //         width = 16
        //        height = 16
        //         depth = 128
        //     mipLevels = 1
        //     arraySize = 1
        //        format = B8G8R8A8_UNORM
        //     dimension =  3D   alpha mode = Unknown
        //        images = 128
        //    pixel size = 128 (KB)
        CHECK(estimate_dds_pixel_buffer_size(16, 16, 128, 1, 1, PixelFormat::B8G8R8A8_UNORM) == (131200 - dds_standard_size));

        // BumpyMetal_dxt1.dds
        //         width = 512
        //        height = 512
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = BC1_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 128 (KB)
        CHECK(estimate_dds_pixel_buffer_size(512, 512, 1, 1, 1, PixelFormat::BC1_UNORM) == (131200 - dds_standard_size));

        // BumpyMetal_float16.dds
        //         width = 128
        //        height = 128
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = R16_FLOAT
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 32 (KB)
        CHECK(estimate_dds_pixel_buffer_size(128, 128, 1, 1, 1, PixelFormat::R16_FLOAT) == (32896 - dds_standard_size));

        // BumpyMetal_float32.dds
        //         width = 128
        //        height = 128
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = R32_FLOAT
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 64 (KB)
        CHECK(estimate_dds_pixel_buffer_size(128, 128, 1, 1, 1, PixelFormat::R32_FLOAT) == (65664 - dds_standard_size));

        // circuit.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = BC3_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 64 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 1, 1, PixelFormat::BC3_UNORM) == (65664 - dds_standard_size));

        // dirt_grayrocky_diffusespecular.dds
        //         width = 1024
        //        height = 1024
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = BC3_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 1024 (KB)
        CHECK(estimate_dds_pixel_buffer_size(1024, 1024, 1, 1, 1, PixelFormat::BC3_UNORM) == (1048704 - dds_standard_size));

        // flare_alpha.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 9
        //     arraySize = 1
        //        format = BC2_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 9
        //    pixel size = 85 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 9, 1, PixelFormat::BC2_UNORM) == (87536 - dds_standard_size));

        // grace_cube.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 9
        //     arraySize = 6
        //        format = B8G8R8A8_UNORM
        //     dimension = Cube
        //    alpha mode = Unknown
        //        images = 54
        //    pixel size = 2047 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 9, 6, PixelFormat::B8G8R8A8_UNORM) == (2097272 - dds_standard_size));

        // gras_02_dxt1.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = BC1_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 32 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 1, 1, PixelFormat::BC1_UNORM) == (32896 - dds_standard_size));

        // NoiseVolume.dds
        //         width = 128
        //        height = 128
        //         depth = 128
        //     mipLevels = 1
        //     arraySize = 1
        //        format = R8_UNORM
        //     dimension =  3D   alpha mode = Unknown
        //        images = 128
        //    pixel size = 2048 (KB)
        CHECK(estimate_dds_pixel_buffer_size(128, 128, 128, 1, 1, PixelFormat::R8_UNORM) == (2097280 - dds_standard_size));

        // ogreborderUp_dxt3.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = BC2_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 64 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 1, 1, PixelFormat::BC2_UNORM) == (65664 - dds_standard_size));

        // ogreborderUp_float128.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = R32G32B32A32_FLOAT
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 1024 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 1, 1, PixelFormat::R32G32B32A32_FLOAT) == (1048704 - dds_standard_size));

        // ogreborderUp_float64.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = R16G16B16A16_FLOAT
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 512 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 1, 1, PixelFormat::R16G16B16A16_FLOAT) == (524416 - dds_standard_size));

        // particle.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 1
        //     arraySize = 1
        //        format = B8G8R8A8_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 1
        //    pixel size = 256 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 1, 1, PixelFormat::B8G8R8A8_UNORM) == (262272 - dds_standard_size));

        // Random3D.dds
        //         width = 64
        //        height = 64
        //         depth = 64
        //     mipLevels = 1
        //     arraySize = 1
        //        format = R8_UNORM
        //     dimension =  3D   alpha mode = Unknown
        //        images = 64
        //    pixel size = 256 (KB)
        CHECK(estimate_dds_pixel_buffer_size(64, 64, 64, 1, 1, PixelFormat::R8_UNORM) == (262272 - dds_standard_size));

        // UniqueTexture.dds
        //         width = 256
        //        height = 256
        //         depth = 1
        //     mipLevels = 9
        //     arraySize = 1
        //        format = BC1_UNORM
        //     dimension = 2D
        //    alpha mode = Unknown
        //        images = 9
        //    pixel size = 42 (KB)
        CHECK(estimate_dds_pixel_buffer_size(256, 256, 1, 9, 1, PixelFormat::BC1_UNORM) == (43832 - dds_standard_size));
    }

    SECTION("Computing mip-map levels")
    {
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 0, 0, 0) == 1);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 1, 1, 1) == 1);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 2, 1, 1) == 2);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 3, 1, 1) == 2);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 4, 1, 1) == 3);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 256, 256, 1) == 9);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R8G8B8A8_UNORM, 256, 256, 16) == 9);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::BC1_UNORM, 256, 256, 1) == 7);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::BC1_UNORM, 256, 256, 16) == 7);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::BC7_UNORM, 256, 256, 1) == 7);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::BC7_UNORM, 256, 256, 16) == 7);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R32G32B32A32_FLOAT, 32768, 32768, 1) == 16);
        CHECK(PixelFormatProperties::ComputeMipMapLevels(PixelFormat::R32G32B32A32_FLOAT, 32768, 32768, 0) == 16);
    }
}
