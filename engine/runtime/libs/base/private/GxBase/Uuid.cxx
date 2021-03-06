#include <GxBase/Uuid.hxx>
#include <GxBase/Bitwise.hxx>

#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP
#include <rpc.h>
#elif GX_PLATFORM_LINUX
#include <uuid/uuid.h>
#endif

namespace Graphyte
{
    BASE_API Uuid Uuid::Create() noexcept
    {
#if GX_PLATFORM_WINDOWS || GX_PLATFORM_UWP

        static_assert(sizeof(Uuid) == sizeof(UUID));

        UUID uuid;
        UuidCreateSequential(&uuid);

        return BitCast<Uuid>(uuid);

#elif GX_PLATFORM_LINUX

        static_assert(sizeof(Uuid) == sizeof(uuid_t));

        uuid_t uuid;
        uuid_generate(uuid);

        return BitCast<Uuid>(uuid);
#else
#error Not implemented
#endif
    }


    BASE_API bool Converter<Uuid>::ToString(std::string& result, Uuid const& value) noexcept
    {
        static constexpr const size_t NumberOfCharsInUInt64 = 16;

        std::array<char, NumberOfCharsInUInt64> buffer_low{};
        std::array<char, NumberOfCharsInUInt64> buffer_high{};

        //
        // Convert to chars separately.
        //

        auto [ptr0, ecc0] = std::to_chars(
            buffer_low.data(),
            buffer_low.data() + buffer_low.size(),
            value.Low,
            16);

        auto [ptr1, ecc1] = std::to_chars(
            buffer_high.data(),
            buffer_high.data() + buffer_high.size(),
            value.High,
            16);


        if (ecc0 == std::errc{} && ecc1 == std::errc{})
        {
            result.reserve(32);
            result.assign(buffer_low.size() - static_cast<size_t>(ptr0 - buffer_low.data()), '0');
            result.append(buffer_low.data(), ptr0);

            result.append(buffer_high.size() - static_cast<size_t>(ptr1 - buffer_high.data()), '0');
            result.append(buffer_high.data(), ptr1);
            return true;
        }

        result.clear();
        return false;
    }

    BASE_API bool Converter<Uuid>::FromString(Uuid& result, std::string_view value) noexcept
    {
        static constexpr const size_t NumberOfCharsInUInt64 = 16;
        static constexpr const size_t NumberOfCharsInUuid   = 32;

        if (value.size() == NumberOfCharsInUuid)
        {
            //
            // Split string into two parts.
            //

            auto const* beg = value.data();
            auto const* mid = beg + NumberOfCharsInUInt64;
            auto const* end = mid + NumberOfCharsInUInt64;

            uint64_t part0{};
            uint64_t part1{};


            //
            // Parse each part separately.
            //

            auto [part0_end, ecc0] = std::from_chars(beg, mid, part0, NumberOfCharsInUInt64);
            auto [part1_end, ecc1] = std::from_chars(mid, end, part1, NumberOfCharsInUInt64);


            //
            // Validate parsing.
            //

            bool const part0_valid = (ecc0 == std::errc{}) && (part0_end == mid);
            bool const part1_valid = (ecc1 == std::errc{}) && (part1_end == end);

            if (part0_valid && part1_valid)
            {
                //
                // Both parsed parts are valid.
                //

                result = { part0, part1 };
                return true;
            }
        }

        result = {};

        return false;
    }
}
