#include <GxBase/Crypto/Random.hxx>

#include <sys/random.h>

namespace Graphyte::Crypto
{
    BASE_API Status GetRandomBytes(notstd::span<std::byte> buffer) noexcept
    {
        if (!buffer.empty())
        {
            ssize_t size = getrandom(
                buffer.data(),
                buffer.size(),
                GRND_RANDOM);

            if (size < 0)
            {
                return Status::Failure;
            }

            if (static_cast<size_t>(size) == buffer.size())
            {
                return Status::Success;
            }
        }

        return Status::EndOfStream;
    }
}
