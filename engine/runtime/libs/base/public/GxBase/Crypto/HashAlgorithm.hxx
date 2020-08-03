#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Span.hxx>

/// @todo Scrap this implementation. We need specific algorithms available as always compiled API.
namespace Graphyte::Crypto
{
    /// @brief This enum provides set of available crypto hash types.
    enum struct HashType : uint32_t
    {
        MD5,
        SHA1,
        SHA256,
        SHA512,
    };

    /// @brief This class provides hash alogirhtm functionality.
    class HashAlgorithm
    {
    protected:
        HashAlgorithm() noexcept = default;

        HashAlgorithm(const HashAlgorithm&) = delete;

        HashAlgorithm& operator=(const HashAlgorithm&) = delete;

    public:
        virtual ~HashAlgorithm() noexcept = default;

    public:
        /// @brief Creates new instance of hash algorithm of specified type.
        ///
        /// @param hashType Provies algorithm type.
        ///
        /// @return The instance of hash algorithm.
        BASE_API static std::unique_ptr<HashAlgorithm> Create(
            HashType hashType) noexcept;

        /// @brief Computes hash of specified data.
        ///
        /// @param hashType Provides algorithm type.
        /// @param output   Returns computed hash.
        /// @param input    Provides data bytes.
        ///
        /// @return \c true when successful, \c false otherwise.
        BASE_API static bool ComputeHash(
            HashType hashType,
            std::vector<std::byte>& output,
            notstd::span<const std::byte> input) noexcept;

    public:
        /// @brief Initializes hashing.
        ///
        /// @return \c true when successful, \c false otherwise.
        virtual bool Initialize() noexcept = 0;

        /// @brief Updates instance with new data.
        ///
        /// @param data Provides data to hash.
        ///
        /// @return \c true when successful, \c false otherwise.
        virtual bool Update(
            notstd::span<const std::byte> data) noexcept = 0;

        /// @brief Finishes hashing and returns hash.
        ///
        /// @param output Returns computed hash value.
        ///
        /// @return \c true when successful, \c false otherwise.
        virtual bool Finish(
            std::vector<std::byte>& output) noexcept = 0;

        virtual size_t GetHashSize() const noexcept = 0;
    };
}
