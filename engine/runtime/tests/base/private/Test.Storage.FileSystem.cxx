#include <catch2/catch.hpp>
#include <GxBase/Storage/IFileSystem.hxx>
#include <GxBase/Storage/Path.hxx>
#include <GxBase/Application.hxx>
#include <GxBase/System.hxx>
#include <GxBase/Storage/FileManager.hxx>
//#include <Graphyte/Crypto/HashAlgorithm.hxx>

TEST_CASE("Checking if commmon paths exist")
{
    SECTION("Global system paths")
    {
        REQUIRE(Graphyte::Storage::IFileSystem::GetPlatformNative().Exists(Graphyte::System::GetBaseDirectory()) == Graphyte::Status::Success);
        REQUIRE(Graphyte::Storage::IFileSystem::GetPlatformNative().Exists(Graphyte::System::GetUserDirectory()) == Graphyte::Status::Success);
        REQUIRE(Graphyte::Storage::IFileSystem::GetPlatformNative().Exists(Graphyte::System::GetUserDocumentsDirectory()) == Graphyte::Status::Success);
        REQUIRE(Graphyte::Storage::IFileSystem::GetPlatformNative().Exists(Graphyte::System::GetUserTemporaryDirectory()) == Graphyte::Status::Success);
    }

    SECTION("Engine specific paths")
    {
        CHECK(Graphyte::Storage::IFileSystem::GetPlatformNative().Exists(Graphyte::Storage::GetEngineDirectory()) == Graphyte::Status::Success);
        CHECK(Graphyte::Storage::IFileSystem::GetPlatformNative().Exists(Graphyte::Storage::GetEngineUserDirectory()) == Graphyte::Status::Success);
    }
}

TEST_CASE("File stream reading and writing")
{
    using namespace Graphyte;

    {
        auto temp_dir  = System::GetUserTemporaryDirectory();
        auto temp_file = Storage::CreateTemporaryFilePath(temp_dir, "test.base", ".bin");

        {
            //
            // Prepare test data.
            //

            const std::array<const std::byte, 32> original_buffer{ {
                // clang-format off
                std::byte{ 11 }, std::byte{ 12 }, std::byte{ 13 }, std::byte{ 14 }, std::byte{ 15 }, std::byte{ 16 }, std::byte{ 17 }, std::byte{ 18 },
                std::byte{ 21 }, std::byte{ 22 }, std::byte{ 23 }, std::byte{ 24 }, std::byte{ 25 }, std::byte{ 26 }, std::byte{ 27 }, std::byte{ 28 },
                std::byte{ 31 }, std::byte{ 32 }, std::byte{ 33 }, std::byte{ 34 }, std::byte{ 35 }, std::byte{ 36 }, std::byte{ 37 }, std::byte{ 38 },
                std::byte{ 41 }, std::byte{ 42 }, std::byte{ 43 }, std::byte{ 44 }, std::byte{ 45 }, std::byte{ 46 }, std::byte{ 47 }, std::byte{ 48 },
                // clang-format on
            } };
            auto original_buffer_view = notstd::as_bytes(notstd::span<const std::byte>{ original_buffer });

            SECTION("Small files check")
            {
                {
                    std::unique_ptr<Storage::IStream> file{};


                    //
                    // We can open file for write. It must be empty.
                    //

                    REQUIRE(Storage::OpenWrite(file, temp_file) == Status::Success);
                    REQUIRE(file->GetPosition() == 0);
                    REQUIRE(file->GetSize() == 0);


                    //
                    // Write all data successfully.
                    //

                    size_t processed{};
                    REQUIRE(file->Write(original_buffer_view, processed) == Status::Success);
                    REQUIRE(processed == 32);
                    REQUIRE(file->GetPosition() == 32);
                    REQUIRE(file->GetSize() == 32);
                }

                {
                    std::unique_ptr<Storage::IStream> file{};

                    //
                    // We can open file for read.
                    //

                    REQUIRE(Storage::OpenRead(file, temp_file) == Status::Success);
                    REQUIRE(file->GetPosition() == 0);
                    REQUIRE(file->GetSize() == 32);

                    std::array<std::byte, 32> read_buffer{};
                    auto read_buffer_view = notstd::as_writable_bytes(notstd::span<std::byte>{ read_buffer });

                    //
                    // Read data first time.
                    //

                    size_t processed{};
                    CHECK(file->Read(read_buffer_view, processed) == Status::Success);
                    REQUIRE(processed == 32);
                    REQUIRE(file->GetPosition() == 32);
                    REQUIRE(file->GetSize() == 32);

                    for (size_t i = 0; i < read_buffer_view.size(); ++i)
                    {
                        REQUIRE(read_buffer_view[i] == original_buffer_view[i]);
                    }


                    //
                    // Second read should return EndOfStream and don't modify file stream.
                    //

                    processed = {};

                    REQUIRE(file->Read(read_buffer_view, processed) == Status::EndOfStream);
                    REQUIRE(processed == 0);
                    REQUIRE(file->GetPosition() == 32);
                    REQUIRE(file->GetSize() == 32);


                    //
                    // Do an partial read
                    //

                    {
                        REQUIRE(file->SetPosition(16) == Status::Success);
                        REQUIRE(file->GetPosition() == 16);

                        std::array<std::byte, 32> partial_buffer{};
                        auto partial_buffer_view = notstd::as_writable_bytes(notstd::span<std::byte>{ partial_buffer });


                        //
                        // Read partial buffer.
                        //

                        processed = {};

                        REQUIRE(file->Read(partial_buffer_view, processed) == Status::EndOfStream);
                        REQUIRE(processed == 16);
                        REQUIRE(file->GetPosition() == 32);
                        REQUIRE(file->GetSize() == 32);

                        for (size_t i = 0; i < 16; ++i)
                        {
                            REQUIRE(partial_buffer_view[i] == original_buffer_view[i + 16]);
                        }

                        for (size_t i = 0; i < 16; ++i)
                        {
                            REQUIRE(partial_buffer_view[i + 16] == std::byte{});
                        }
                    }
                }
            }

            SECTION("Handling larger files")
            {
                constexpr size_t Count = 27055;

                // Write large file
                {
                    std::unique_ptr<Storage::IStream> file{};

                    REQUIRE(Storage::OpenWrite(file, temp_file) == Status::Success);
                    REQUIRE(file->GetPosition() == 0);
                    REQUIRE(file->GetSize() == 0);

                    for (size_t i = 0; i < Count; ++i)
                    {
                        size_t processed{};
                        REQUIRE(file->Write(original_buffer_view, processed) == Status::Success);
                        REQUIRE(processed == original_buffer_view.size());
                    }

                    REQUIRE(file->GetPosition() == static_cast<int64_t>(Count * original_buffer_view.size()));
                    REQUIRE(file->GetPosition() == file->GetSize());

                    auto copy = original_buffer_view;
                    copy.remove_suffix(16);

                    size_t processed{};
                    REQUIRE(file->Write(copy, processed) == Status::Success);
                    REQUIRE(processed == 16);

                    REQUIRE(file->GetPosition() == static_cast<int64_t>(Count * original_buffer_view.size() + 16));
                    REQUIRE(file->GetPosition() == file->GetSize());
                }

                // Reading large file part by part
                {
                    std::unique_ptr<Storage::IStream> file{};

                    REQUIRE(Storage::OpenRead(file, temp_file) == Status::Success);
                    REQUIRE(file->GetPosition() == 0);
                    REQUIRE(file->GetSize() == static_cast<int64_t>(Count * original_buffer_view.size() + 16));


                    for (size_t i = 0; i < Count; ++i)
                    {
                        std::array<std::byte, 32> read_buffer{};
                        auto read_buffer_view = notstd::as_writable_bytes(notstd::span<std::byte>{ read_buffer });

                        size_t processed{};
                        REQUIRE(file->Read(read_buffer_view, processed) == Status::Success);
                        REQUIRE(processed == read_buffer_view.size());

                        for (size_t j = 0; j < read_buffer_view.size(); ++j)
                        {
                            REQUIRE(read_buffer_view[j] == original_buffer_view[j]);
                        }
                    }

                    std::array<std::byte, 32> read_buffer{};
                    auto partial_buffer_view = notstd::as_writable_bytes(notstd::span<std::byte>{ read_buffer });

                    size_t processed{};
                    REQUIRE(file->Read(partial_buffer_view, processed) == Status::EndOfStream);
                    REQUIRE(processed == 16);

                    for (size_t i = 0; i < 16; ++i)
                    {
                        REQUIRE(partial_buffer_view[i] == original_buffer_view[i]);
                    }

                    for (size_t i = 0; i < 16; ++i)
                    {
                        REQUIRE(partial_buffer_view[i + 16] == std::byte{});
                    }

                    REQUIRE(file->GetPosition() == static_cast<int64_t>(Count * original_buffer_view.size() + 16));
                    REQUIRE(file->GetPosition() == file->GetSize());
                }
            }
        }
    }
}

#if false
TEST_CASE("Reading large files byte by byte; checking file consistency")
{
    using namespace Graphyte;

    auto temp_dir = System::GetUserTemporaryDirectory();
    auto temp_file = Storage::Path::CreateTempFilename(temp_dir, "test.base", ".bin");

    auto original_hash = Crypto::HashAlgorithm::Create(Crypto::HashType::SHA512);
    REQUIRE(original_hash->Initialize());

    constexpr uint64_t Count = 131 * 1024;

    // create file
    {
        std::unique_ptr<Storage::IStream> file{};
        REQUIRE(Storage::OpenWrite(file, temp_file) == Status::Success);

        for (uint64_t i = 0; i < Count; ++i)
        {
            auto buffer = static_cast<std::byte>(i);
            notstd::span<const std::byte> buffer_view{ &buffer, 1 };

            size_t processed{};
            REQUIRE(file->Write(buffer_view, processed) == Status::Success);
            REQUIRE(original_hash->Update(buffer_view));
            REQUIRE(processed == 1);
        }

        REQUIRE(file->GetPosition() == file->GetSize());
        REQUIRE(file->GetSize() == Count);
    }

    std::vector<std::byte> original_hash_value{};
    REQUIRE(original_hash->Finish(original_hash_value));

    auto read_hash = Crypto::HashAlgorithm::Create(Crypto::HashType::SHA512);
    REQUIRE(read_hash->Initialize());

    // read file
    {
        std::unique_ptr<Storage::IStream> file{};
        REQUIRE(Storage::OpenRead(file, temp_file) == Status::Success);

        std::array<std::byte, 187> buffer{};
        notstd::span<std::byte> buffer_view{ buffer };

        auto remainder = Count % buffer.size();

        auto status = Status::Success;
        size_t processed{};

        do
        {
            processed = {};
            status = file->Read(buffer_view, processed);
            read_hash->Update(buffer_view.subspan(0, static_cast<ptrdiff_t>(processed)));

            REQUIRE((status == Status::Success || status == Status::EndOfStream));

            if (status == Status::Success)
            {
                REQUIRE(processed == buffer.size());
            }
            else
            {
                REQUIRE(processed == remainder);
            }
        } while (status == Status::Success);

        REQUIRE(status == Status::EndOfStream);
        REQUIRE(file->GetPosition() == file->GetSize());
        REQUIRE(file->GetSize() == Count);
    }

    std::vector<std::byte> read_hash_value{};
    REQUIRE(read_hash->Finish(read_hash_value));

    REQUIRE(read_hash_value.size() == original_hash_value.size());

    for (size_t i = 0; i < read_hash_value.size(); ++i)
    {
        REQUIRE(read_hash_value[i] == original_hash_value[i]);
    }
}
#endif
