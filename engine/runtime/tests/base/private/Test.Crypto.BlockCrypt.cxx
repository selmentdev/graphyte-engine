#include "Test.Base.pch.hxx"
#include <Graphyte/Base.module.hxx>

TEST_CASE("Crypto / CryptoTransform algorithm")
{

#if false

    auto info = mbedtls_cipher_info_from_type(MBEDTLS_CIPHER_AES_256_ECB);
    mbedtls_cipher_context_t context;
    mbedtls_cipher_init(&context);
    mbedtls_cipher_setup(&context, info);
    mbedtls_cipher_setkey(&context, (const unsigned char*)"12345678123456781234567812345678", 256, MBEDTLS_ENCRYPT);
    mbedtls_cipher_set_padding_mode(&context, MBEDTLS_PADDING_ONE_AND_ZEROS);
    mbedtls_cipher_set_iv(&context, (const unsigned char*)"iv", 2);

    std::array<unsigned char, 16> input{};
    std::array<unsigned char, 16> output{};

    size_t written{};

    mbedtls_cipher_update(
        &context,
        std::data(input),
        std::size(input),
        std::data(output),
        &written
    );

    mbedtls_cipher_finish(&context, std::data(output), &written);
    mbedtls_cipher_free(&context);

#endif
}
