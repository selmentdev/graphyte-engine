#include <GxBase/Crypto/HashAlgorithm.hxx>

#if GX_PLATFORM_UWP
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.Storage.Streams.h>

#pragma warning(push)
#pragma warning(disable : 4715)
#endif

#if !GX_PLATFORM_UWP

#include <mbedtls/md.h>

namespace Graphyte::Crypto::MbedtlsHelpers::Impl
{
    constexpr static mbedtls_md_type_t GetType(HashType hashType) noexcept
    {
        switch (hashType)
        {
            case HashType::MD5:
                return MBEDTLS_MD_MD5;

            case HashType::SHA1:
                return MBEDTLS_MD_SHA1;

            case HashType::SHA256:
                return MBEDTLS_MD_SHA256;

            case HashType::SHA512:
                return MBEDTLS_MD_SHA512;

            default:
                break;
        }

        return MBEDTLS_MD_NONE;
    }
}

namespace Graphyte::Crypto
{
    class MbedtlsCryptoProvider final : public HashAlgorithm
    {
    private:
        const mbedtls_md_info_t* m_Info;
        mbedtls_md_context_t m_Context;

    public:
        explicit MbedtlsCryptoProvider(const mbedtls_md_info_t* info) noexcept
            : m_Info{ info }
            , m_Context{}
        {
            GX_ASSERT(m_Info != nullptr);
        }

        virtual ~MbedtlsCryptoProvider() noexcept
        {
            mbedtls_md_free(&m_Context);
        }

    public:
        virtual bool Initialize() noexcept override
        {
            GX_ASSERT(m_Info != nullptr);

            mbedtls_md_init(&m_Context);

            int const status_setup = mbedtls_md_setup(
                &m_Context,
                m_Info,
                0);

            int const status_starts = mbedtls_md_starts(
                &m_Context);

            return status_setup == 0
                   && status_starts == 0;
        }

        virtual bool Update(
            std::span<const std::byte> data) noexcept override
        {
            GX_ASSERT(m_Info != nullptr);

            int const status = mbedtls_md_update(
                &m_Context,
                reinterpret_cast<const unsigned char*>(std::data(data)),
                std::size(data));

            return status == 0;
        }

        virtual bool Finish(
            std::vector<std::byte>& output) noexcept override
        {
            GX_ASSERT(m_Info != nullptr);

            std::array<std::byte, MBEDTLS_MD_MAX_SIZE> hash{};

            int const status = mbedtls_md_finish(
                &m_Context,
                reinterpret_cast<unsigned char*>(std::data(hash)));

            if (status == 0)
            {
                size_t hashSize = mbedtls_md_get_size(m_Info);

                output.assign(
                    std::data(hash),
                    std::data(hash) + hashSize);
            }

            mbedtls_md_free(&m_Context);

            return status == 0;
        }

        virtual size_t GetHashSize() const noexcept override
        {
            GX_ASSERT(m_Info != nullptr);

            return mbedtls_md_get_size(m_Info);
        }
    };
}

#endif

namespace Graphyte::Crypto
{
    std::unique_ptr<HashAlgorithm> HashAlgorithm::Create(
        [[maybe_unused]] HashType hashType) noexcept
    {
#if !GX_PLATFORM_UWP
        mbedtls_md_type_t const type        = MbedtlsHelpers::Impl::GetType(hashType);
        const mbedtls_md_info_t* const info = mbedtls_md_info_from_type(type);

        if (info == nullptr)
        {
            return nullptr;
        }

        return std::make_unique<MbedtlsCryptoProvider>(info);
#else
        return {};
#endif
    }

    bool HashAlgorithm::ComputeHash(
        [[maybe_unused]] HashType hashType,
        [[maybe_unused]] std::vector<std::byte>& output,
        [[maybe_unused]] std::span<const std::byte> input) noexcept
    {
#if GX_PLATFORM_UWP

        using winrt::Windows::Security::Cryptography::CryptographicBuffer;
        using winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames;
        using winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider;
        using winrt::Windows::Storage::Streams::IBuffer;

        winrt::hstring algorithm_name{};

        switch (hashType)
        {
            case HashType::MD5:
                algorithm_name = HashAlgorithmNames::Md5();
                break;
            case HashType::SHA1:
                algorithm_name = HashAlgorithmNames::Sha1();
                break;
            case HashType::SHA256:
                algorithm_name = HashAlgorithmNames::Sha256();
                break;
            case HashType::SHA512:
                algorithm_name = HashAlgorithmNames::Sha512();
                break;
        }


        HashAlgorithmProvider provider = HashAlgorithmProvider::OpenAlgorithm(algorithm_name);

        winrt::array_view<uint8_t const> input_view{
            reinterpret_cast<uint8_t const*>(input.data()),
            reinterpret_cast<uint8_t const*>(input.data() + input.size())
        };

        IBuffer input_buffer = CryptographicBuffer::CreateFromByteArray(input_view);

        IBuffer hash_buffer = provider.HashData(input_buffer);

        output.assign(
            reinterpret_cast<std::byte*>(hash_buffer.data()),
            reinterpret_cast<std::byte*>(hash_buffer.data() + hash_buffer.Length()));

        return true;
#else
        mbedtls_md_type_t const type        = MbedtlsHelpers::Impl::GetType(hashType);
        const mbedtls_md_info_t* const info = mbedtls_md_info_from_type(type);

        if (info != nullptr)
        {
            std::array<std::byte, MBEDTLS_MD_MAX_SIZE> hash{};

            int const status = mbedtls_md(
                info,
                reinterpret_cast<const unsigned char*>(std::data(input)),
                std::size(input),
                reinterpret_cast<unsigned char*>(std::data(hash)));

            if (status == 0)
            {
                size_t const size = mbedtls_md_get_size(info);

                output.assign(
                    std::data(hash),
                    std::data(hash) + size);

                return true;
            }
        }

        return false;
#endif
    }
}

#if GX_PLATFORM_UWP
#pragma warning(pop)
#endif
