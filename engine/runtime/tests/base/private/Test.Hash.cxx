#include <catch2/catch.hpp>
#include <GxBase/Hash/XXHash.hxx>
#include <GxBase/Crypto/HashAlgorithm.hxx>
#include <GxBase/Hash/Crc.hxx>

TEST_CASE("Crc hashes")
{
    std::array<std::uint8_t, 8> buffer{
        { 0, 1, 2, 3, 4, 5, 6, 7 }
    };

    auto const view = notstd::as_bytes(notstd::span<std::uint8_t>{ buffer });

    SECTION("Crc32")
    {
        SECTION("Whole buffer")
        {
            uint32_t const result = Graphyte::Crc32(view, 1, true);

            REQUIRE(result == 0x953CFF39u);
        }

        SECTION("Partial buffer")
        {
            uint32_t const r0 = Graphyte::Crc32(view.subspan<0, 1>(), 1, false);
            uint32_t const r1 = Graphyte::Crc32(view.subspan<1, 1>(), r0, false);
            uint32_t const r2 = Graphyte::Crc32(view.subspan<2, 1>(), r1, false);
            uint32_t const r3 = Graphyte::Crc32(view.subspan<3, 1>(), r2, false);
            uint32_t const r4 = Graphyte::Crc32(view.subspan<4, 1>(), r3, false);
            uint32_t const r5 = Graphyte::Crc32(view.subspan<5, 1>(), r4, false);
            uint32_t const r6 = Graphyte::Crc32(view.subspan<6, 1>(), r5, false);
            uint32_t const r7 = Graphyte::Crc32(view.subspan<7, 1>(), r6, true);

            REQUIRE(r7 == 0x953CFF39u);
        }
    }

    SECTION("Crc64")
    {
        SECTION("Whole buffer")
        {
            uint64_t const result = Graphyte::Crc64(view, 1, true);

            REQUIRE(result == 0x1F25FACEF3B30EA0u);
        }

        SECTION("Partial buffer")
        {
            uint64_t const r0 = Graphyte::Crc64(view.subspan<0, 1>(), 1, false);
            uint64_t const r1 = Graphyte::Crc64(view.subspan<1, 1>(), r0, false);
            uint64_t const r2 = Graphyte::Crc64(view.subspan<2, 1>(), r1, false);
            uint64_t const r3 = Graphyte::Crc64(view.subspan<3, 1>(), r2, false);
            uint64_t const r4 = Graphyte::Crc64(view.subspan<4, 1>(), r3, false);
            uint64_t const r5 = Graphyte::Crc64(view.subspan<5, 1>(), r4, false);
            uint64_t const r6 = Graphyte::Crc64(view.subspan<6, 1>(), r5, false);
            uint64_t const r7 = Graphyte::Crc64(view.subspan<7, 1>(), r6, true);

            REQUIRE(r7 == 0x1F25FACEF3B30EA0u);
        }
    }
}

TEST_CASE("Hashing functions")
{
    SECTION("XXHash")
    {
        using Graphyte::Hash::XXHash64;


        SECTION("Data hash")
        {
            std::string_view data{ "I want an unsigned 64-bit seed!" };
            CHECK(XXHash64::Hash(data.data(), data.size(), 0) == 0xd4cb0a70a2b8c7c1U);
            CHECK(XXHash64::Hash(data.data(), data.size(), 1) == 0xce5087f12470d961U);
        }

        SECTION("Streaming")
        {
            std::string_view data{ "Graphyte" };
            XXHash64 hash{ 0 };

            hash.Update(data.data() + 0, 1);
            CHECK(hash.GetValue() == 0x69c9af6156370960);
            hash.Update(data.data() + 1, 1);
            CHECK(hash.GetValue() == 0xe4d3913c559ae2f6);
            hash.Update(data.data() + 2, 1);
            CHECK(hash.GetValue() == 0x3cf86a901cca5057);
            hash.Update(data.data() + 3, 1);
            CHECK(hash.GetValue() == 0x304656a8a7439ec6);
            hash.Update(data.data() + 4, 1);
            CHECK(hash.GetValue() == 0x869957a316c893c8);
            hash.Update(data.data() + 5, 1);
            CHECK(hash.GetValue() == 0x6ea5a2151e77b7c0);
            hash.Update(data.data() + 6, 1);
            CHECK(hash.GetValue() == 0x5ea41b5e8343ee52);
            hash.Update(data.data() + 7, 1);
            CHECK(hash.GetValue() == 0x5536a31c8c8c2280);

            CHECK(hash.GetValue() == XXHash64::Hash(data.data(), data.size(), 0));
        }
    }

    SECTION("SHA1")
    {
        SECTION("Empty string")
        {
            std::array<std::byte, 20> expected{
                {
                    std::byte{ 0xda }, std::byte{ 0x39 }, std::byte{ 0xa3 }, std::byte{ 0xee },
                    std::byte{ 0x5e }, std::byte{ 0x6b }, std::byte{ 0x4b }, std::byte{ 0x0d },
                    std::byte{ 0x32 }, std::byte{ 0x55 }, std::byte{ 0xbf }, std::byte{ 0xef },
                    std::byte{ 0x95 }, std::byte{ 0x60 }, std::byte{ 0x18 }, std::byte{ 0x90 },
                    std::byte{ 0xaf }, std::byte{ 0xd8 }, std::byte{ 0x07 }, std::byte{ 0x09 },
                }
            };

            std::string_view sv{ "" };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA1,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }

        SECTION("String 1")
        {
            std::array<std::byte, 20> expected{
                {
                    std::byte{ 0x6b }, std::byte{ 0xa9 }, std::byte{ 0xd7 }, std::byte{ 0x79 },
                    std::byte{ 0xdd }, std::byte{ 0xe6 }, std::byte{ 0x04 }, std::byte{ 0xa3 },
                    std::byte{ 0x1c }, std::byte{ 0xa0 }, std::byte{ 0xed }, std::byte{ 0x2b },
                    std::byte{ 0x70 }, std::byte{ 0x41 }, std::byte{ 0x8a }, std::byte{ 0xe6 },
                    std::byte{ 0x3f }, std::byte{ 0x19 }, std::byte{ 0xf2 }, std::byte{ 0xea },
                }
            };

            std::string_view sv{ "Graphyte Engine" };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA1,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }

        SECTION("String 2")
        {
            std::array<std::byte, 20> expected{
                {
                    std::byte{ 0xa4 }, std::byte{ 0x9b }, std::byte{ 0x24 }, std::byte{ 0x46 },
                    std::byte{ 0xa0 }, std::byte{ 0x2c }, std::byte{ 0x64 }, std::byte{ 0x5b },
                    std::byte{ 0xf4 }, std::byte{ 0x19 }, std::byte{ 0xf9 }, std::byte{ 0x95 },
                    std::byte{ 0xb6 }, std::byte{ 0x70 }, std::byte{ 0x91 }, std::byte{ 0x25 },
                    std::byte{ 0x3a }, std::byte{ 0x04 }, std::byte{ 0xa2 }, std::byte{ 0x59 },
                }
            };

            std::string_view sv{
                "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
                "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
            };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA1,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }
    }

    SECTION("SHA256")
    {
        SECTION("Empty string")
        {
            std::array<std::byte, 32> expected{
                {
                    std::byte{ 0xe3 }, std::byte{ 0xb0 }, std::byte{ 0xc4 }, std::byte{ 0x42 },
                    std::byte{ 0x98 }, std::byte{ 0xfc }, std::byte{ 0x1c }, std::byte{ 0x14 },
                    std::byte{ 0x9a }, std::byte{ 0xfb }, std::byte{ 0xf4 }, std::byte{ 0xc8 },
                    std::byte{ 0x99 }, std::byte{ 0x6f }, std::byte{ 0xb9 }, std::byte{ 0x24 },
                    std::byte{ 0x27 }, std::byte{ 0xae }, std::byte{ 0x41 }, std::byte{ 0xe4 },
                    std::byte{ 0x64 }, std::byte{ 0x9b }, std::byte{ 0x93 }, std::byte{ 0x4c },
                    std::byte{ 0xa4 }, std::byte{ 0x95 }, std::byte{ 0x99 }, std::byte{ 0x1b },
                    std::byte{ 0x78 }, std::byte{ 0x52 }, std::byte{ 0xb8 }, std::byte{ 0x55 },
                }
            };

            std::string_view sv{ "" };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA256,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }

        SECTION("String 1")
        {
            std::array<std::byte, 32> expected{
                {
                    std::byte{ 0x55 }, std::byte{ 0x8b }, std::byte{ 0xf1 }, std::byte{ 0x1d },
                    std::byte{ 0x65 }, std::byte{ 0xb0 }, std::byte{ 0x09 }, std::byte{ 0x79 },
                    std::byte{ 0x14 }, std::byte{ 0xa4 }, std::byte{ 0xa1 }, std::byte{ 0x6e },
                    std::byte{ 0xaf }, std::byte{ 0xce }, std::byte{ 0x8d }, std::byte{ 0x7d },
                    std::byte{ 0xc6 }, std::byte{ 0x4c }, std::byte{ 0xd4 }, std::byte{ 0xd4 },
                    std::byte{ 0xad }, std::byte{ 0x4a }, std::byte{ 0x8c }, std::byte{ 0xc7 },
                    std::byte{ 0x29 }, std::byte{ 0xce }, std::byte{ 0x13 }, std::byte{ 0x36 },
                    std::byte{ 0xea }, std::byte{ 0xe5 }, std::byte{ 0xc7 }, std::byte{ 0x66 },
                }
            };

            std::string_view sv{ "Graphyte Engine" };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA256,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }

        SECTION("String 2")
        {
            std::array<std::byte, 32> expected{
                {
                    std::byte{ 0xcf }, std::byte{ 0x5b }, std::byte{ 0x16 }, std::byte{ 0xa7 },
                    std::byte{ 0x78 }, std::byte{ 0xaf }, std::byte{ 0x83 }, std::byte{ 0x80 },
                    std::byte{ 0x03 }, std::byte{ 0x6c }, std::byte{ 0xe5 }, std::byte{ 0x9e },
                    std::byte{ 0x7b }, std::byte{ 0x04 }, std::byte{ 0x92 }, std::byte{ 0x37 },
                    std::byte{ 0x0b }, std::byte{ 0x24 }, std::byte{ 0x9b }, std::byte{ 0x11 },
                    std::byte{ 0xe8 }, std::byte{ 0xf0 }, std::byte{ 0x7a }, std::byte{ 0x51 },
                    std::byte{ 0xaf }, std::byte{ 0xac }, std::byte{ 0x45 }, std::byte{ 0x03 },
                    std::byte{ 0x7a }, std::byte{ 0xfe }, std::byte{ 0xe9 }, std::byte{ 0xd1 },
                }
            };

            std::string_view sv{
                "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
                "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
            };

            {
                std::vector<std::byte> hash{};

                REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                    Graphyte::Crypto::HashType::SHA256,
                    hash,
                    notstd::as_bytes(notstd::span<const char>{sv})
                ));

                REQUIRE(std::equal(
                    std::begin(hash),
                    std::end(hash),
                    std::begin(expected),
                    std::end(expected)
                ));
            }

            {
                auto algorithm = Graphyte::Crypto::HashAlgorithm::Create(
                    Graphyte::Crypto::HashType::SHA256
                );

                REQUIRE(algorithm != nullptr);

                algorithm->Initialize();

                for (auto ch : sv)
                {
                    std::byte bytes[] = { (std::byte)ch };

                    algorithm->Update({ bytes });
                }

                std::vector<std::byte> hash{};
                algorithm->Finish(hash);

                REQUIRE(std::equal(
                    std::begin(hash),
                    std::end(hash),
                    std::begin(expected),
                    std::end(expected)
                ));
            }
        }
    }

    SECTION("SHA512")
    {
        SECTION("Empty string")
        {
            std::array<std::byte, 64> expected{
                {
                    std::byte{ 0xcf }, std::byte{ 0x83 }, std::byte{ 0xe1 }, std::byte{ 0x35 },
                    std::byte{ 0x7e }, std::byte{ 0xef }, std::byte{ 0xb8 }, std::byte{ 0xbd },
                    std::byte{ 0xf1 }, std::byte{ 0x54 }, std::byte{ 0x28 }, std::byte{ 0x50 },
                    std::byte{ 0xd6 }, std::byte{ 0x6d }, std::byte{ 0x80 }, std::byte{ 0x07 },
                    std::byte{ 0xd6 }, std::byte{ 0x20 }, std::byte{ 0xe4 }, std::byte{ 0x05 },
                    std::byte{ 0x0b }, std::byte{ 0x57 }, std::byte{ 0x15 }, std::byte{ 0xdc },
                    std::byte{ 0x83 }, std::byte{ 0xf4 }, std::byte{ 0xa9 }, std::byte{ 0x21 },
                    std::byte{ 0xd3 }, std::byte{ 0x6c }, std::byte{ 0xe9 }, std::byte{ 0xce },
                    std::byte{ 0x47 }, std::byte{ 0xd0 }, std::byte{ 0xd1 }, std::byte{ 0x3c },
                    std::byte{ 0x5d }, std::byte{ 0x85 }, std::byte{ 0xf2 }, std::byte{ 0xb0 },
                    std::byte{ 0xff }, std::byte{ 0x83 }, std::byte{ 0x18 }, std::byte{ 0xd2 },
                    std::byte{ 0x87 }, std::byte{ 0x7e }, std::byte{ 0xec }, std::byte{ 0x2f },
                    std::byte{ 0x63 }, std::byte{ 0xb9 }, std::byte{ 0x31 }, std::byte{ 0xbd },
                    std::byte{ 0x47 }, std::byte{ 0x41 }, std::byte{ 0x7a }, std::byte{ 0x81 },
                    std::byte{ 0xa5 }, std::byte{ 0x38 }, std::byte{ 0x32 }, std::byte{ 0x7a },
                    std::byte{ 0xf9 }, std::byte{ 0x27 }, std::byte{ 0xda }, std::byte{ 0x3e },
                }
            };

            std::string_view sv{ "" };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA512,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }

        SECTION("String 1")
        {
            std::array<std::byte, 64> expected{
                {
                    std::byte{ 0x27 }, std::byte{ 0x91 }, std::byte{ 0x06 }, std::byte{ 0x4d },
                    std::byte{ 0x2e }, std::byte{ 0x64 }, std::byte{ 0x60 }, std::byte{ 0x9b },
                    std::byte{ 0xe1 }, std::byte{ 0x1b }, std::byte{ 0x6b }, std::byte{ 0x0f },
                    std::byte{ 0x1f }, std::byte{ 0x39 }, std::byte{ 0x36 }, std::byte{ 0xb5 },
                    std::byte{ 0xfd }, std::byte{ 0xa1 }, std::byte{ 0xcc }, std::byte{ 0x3c },
                    std::byte{ 0x6a }, std::byte{ 0x0c }, std::byte{ 0xba }, std::byte{ 0x97 },
                    std::byte{ 0x8e }, std::byte{ 0xaa }, std::byte{ 0xd6 }, std::byte{ 0x6a },
                    std::byte{ 0x1e }, std::byte{ 0xfa }, std::byte{ 0xad }, std::byte{ 0xa4 },
                    std::byte{ 0x10 }, std::byte{ 0x90 }, std::byte{ 0xcd }, std::byte{ 0x44 },
                    std::byte{ 0xbb }, std::byte{ 0xfa }, std::byte{ 0xbc }, std::byte{ 0x27 },
                    std::byte{ 0x35 }, std::byte{ 0xbb }, std::byte{ 0x65 }, std::byte{ 0x3a },
                    std::byte{ 0xfe }, std::byte{ 0x6b }, std::byte{ 0x68 }, std::byte{ 0x86 },
                    std::byte{ 0x65 }, std::byte{ 0xb7 }, std::byte{ 0xc6 }, std::byte{ 0x1c },
                    std::byte{ 0x86 }, std::byte{ 0x81 }, std::byte{ 0x63 }, std::byte{ 0xf9 },
                    std::byte{ 0x59 }, std::byte{ 0x09 }, std::byte{ 0x34 }, std::byte{ 0x04 },
                    std::byte{ 0xcd }, std::byte{ 0x1e }, std::byte{ 0x98 }, std::byte{ 0x3a },
                }
            };

            std::string_view sv{ "Graphyte Engine" };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA512,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }

        SECTION("String 2")
        {
            std::array<std::byte, 64> expected{
                {
                    std::byte{ 0x8e }, std::byte{ 0x95 }, std::byte{ 0x9b }, std::byte{ 0x75 },
                    std::byte{ 0xda }, std::byte{ 0xe3 }, std::byte{ 0x13 }, std::byte{ 0xda },
                    std::byte{ 0x8c }, std::byte{ 0xf4 }, std::byte{ 0xf7 }, std::byte{ 0x28 },
                    std::byte{ 0x14 }, std::byte{ 0xfc }, std::byte{ 0x14 }, std::byte{ 0x3f },
                    std::byte{ 0x8f }, std::byte{ 0x77 }, std::byte{ 0x79 }, std::byte{ 0xc6 },
                    std::byte{ 0xeb }, std::byte{ 0x9f }, std::byte{ 0x7f }, std::byte{ 0xa1 },
                    std::byte{ 0x72 }, std::byte{ 0x99 }, std::byte{ 0xae }, std::byte{ 0xad },
                    std::byte{ 0xb6 }, std::byte{ 0x88 }, std::byte{ 0x90 }, std::byte{ 0x18 },
                    std::byte{ 0x50 }, std::byte{ 0x1d }, std::byte{ 0x28 }, std::byte{ 0x9e },
                    std::byte{ 0x49 }, std::byte{ 0x00 }, std::byte{ 0xf7 }, std::byte{ 0xe4 },
                    std::byte{ 0x33 }, std::byte{ 0x1b }, std::byte{ 0x99 }, std::byte{ 0xde },
                    std::byte{ 0xc4 }, std::byte{ 0xb5 }, std::byte{ 0x43 }, std::byte{ 0x3a },
                    std::byte{ 0xc7 }, std::byte{ 0xd3 }, std::byte{ 0x29 }, std::byte{ 0xee },
                    std::byte{ 0xb6 }, std::byte{ 0xdd }, std::byte{ 0x26 }, std::byte{ 0x54 },
                    std::byte{ 0x5e }, std::byte{ 0x96 }, std::byte{ 0xe5 }, std::byte{ 0x5b },
                    std::byte{ 0x87 }, std::byte{ 0x4b }, std::byte{ 0xe9 }, std::byte{ 0x09 },
                }
            };

            std::string_view sv{
                "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
                "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
            };

            std::vector<std::byte> hash{};

            REQUIRE(Graphyte::Crypto::HashAlgorithm::ComputeHash(
                Graphyte::Crypto::HashType::SHA512,
                hash,
                notstd::as_bytes(notstd::span<const char>{sv})
            ));

            REQUIRE(std::equal(
                std::begin(hash),
                std::end(hash),
                std::begin(expected),
                std::end(expected)
            ));
        }
    }
}
