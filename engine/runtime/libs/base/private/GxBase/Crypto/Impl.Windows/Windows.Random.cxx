#include <GxBase/Crypto/Random.hxx>

#include <wincrypt.h>

namespace Graphyte::Crypto
{
    BASE_API Status GetRandomBytes(notstd::span<std::byte> buffer) noexcept
    {
        if (!buffer.empty())
        {
            NTSTATUS status = BCryptGenRandom(
                nullptr,
                reinterpret_cast<UCHAR*>(buffer.data()),
                static_cast<ULONG>(buffer.size()),
                BCRYPT_USE_SYSTEM_PREFERRED_RNG
            );

            if (BCRYPT_SUCCESS(status))
            {
                return Status::Success;
            }
            else
            {
                return Status::Failure;
            }
        }

        return Status::EndOfStream;
    }
}
