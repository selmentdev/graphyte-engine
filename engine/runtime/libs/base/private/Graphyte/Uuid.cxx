#include "Base.pch.hxx"
#include <Graphyte/Uuid.hxx>

namespace Graphyte
{
    BASE_API Uuid Uuid::Create() noexcept
    {
        Uuid result;

#if GRAPHYTE_PLATFORM_WINDOWS

        static_assert(sizeof(Uuid) == sizeof(GUID));

        GUID guid;

        [[maybe_unused]] HRESULT hr = CoCreateGuid(&guid);
        //GX_ABORT_UNLESS(SUCCEEDED(hr), "Failed to generate random UUID");

        std::memcpy(&result, &guid, sizeof(Uuid));

#elif GRAPHYTE_PLATFORM_LINUX

        uuid_t uuid;
        uuid_generate(uuid);

        std::memcpy(result.AsU8, uuid, sizeof(Uuid));

#else
#error Not implemented
#endif

        return result;
    }


    BASE_API bool Converter<Uuid>::ToString(std::string& result, Uuid const& value) noexcept
    {
        char buffer[32];

        //
        // Buffer iterators.
        //

        char* beg = buffer;
        char* mid = beg + 16;
        char* end = mid + 16;


        //
        // Convert to chars separately.
        //

        auto [ptr0, ecc0] = std::to_chars(beg, mid, value.Low, 16);
        auto [ptr1, ecc1] = std::to_chars(mid, end, value.High, 16);


        //
        // Validate.
        //

        bool const part0_valid = (ecc0 == std::errc{}) && (ptr0 == mid);
        bool const part1_valid = (ecc1 == std::errc{}) && (ptr1 == end);

        if (part0_valid && part1_valid)
        {
            result.assign(beg, end);
            return true;
        }

        result.clear();
        return false;
    }

    BASE_API bool Converter<Uuid>::FromString(Uuid& result, std::string_view value) noexcept
    {
        if (value.size() == 32)
        {
            //
            // Split string into two parts.
            //

            auto const* beg = value.data();
            auto const* mid = beg + 16;
            auto const* end = mid + 16;

            uint64_t part0{};
            uint64_t part1{};


            //
            // Parse each part separately.
            //

            auto [part0_end, ecc0] = std::from_chars(beg, mid, part0, 16);
            auto [part1_end, ecc1] = std::from_chars(mid, end, part1, 16);


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
