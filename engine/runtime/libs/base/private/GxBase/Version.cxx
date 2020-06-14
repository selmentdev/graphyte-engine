#include <GxBase/Version.hxx>

// =================================================================================================
//
// Version struct implementation.
//

namespace Graphyte
{
    bool Converter<Version>::ToString(std::string& result, Graphyte::Version const& value) noexcept
    {
        char part0[16];
        char part1[16];
        char part2[16];
        char part3[16];

        auto [end0, ecc0] = std::to_chars(std::begin(part0), std::end(part0), value.Major, 10);
        auto [end1, ecc1] = std::to_chars(std::begin(part1), std::end(part1), value.Minor, 10);
        auto [end2, ecc2] = std::to_chars(std::begin(part2), std::end(part2), value.Patch, 10);
        auto [end3, ecc3] = std::to_chars(std::begin(part3), std::end(part3), value.Build, 10);

        bool const valid = (ecc0 == std::errc{}) && (ecc1 == std::errc{}) && (ecc2 == std::errc{}) && (ecc3 == std::errc{});

        if (valid)
        {
            result.assign(part0, end0);
            result.append(1, '.');
            result.append(part1, end1);
            result.append(1, '.');
            result.append(part2, end2);
            result.append(1, '.');
            result.append(part3, end3);

            return true;
        }


        result.clear();
        return false;
    }

    bool Converter<Version>::FromString(Graphyte::Version& result, std::string_view value) noexcept
    {
        if (!value.empty())
        {
            auto* ptr_begin = std::data(value);
            auto* ptr_end   = std::data(value) + std::size(value);

            uint32_t major{};

            auto [dot_1, ecc_1] = std::from_chars(ptr_begin, ptr_end, major, 10);

            if ((dot_1 == ptr_end) || (dot_1 != ptr_end && *dot_1 != '.') || ecc_1 != std::errc{})
            {
                return false;
            }

            uint32_t minor{};

            auto [dot_2, ecc_2] = std::from_chars(dot_1 + 1, ptr_end, minor, 10);

            if ((dot_2 == ptr_end) || (dot_2 != ptr_end && *dot_2 != '.') || ecc_2 != std::errc{})
            {
                return false;
            }

            uint32_t patch{};

            auto [dot_3, ecc_3] = std::from_chars(dot_2 + 1, ptr_end, patch, 10);

            if ((dot_3 == ptr_end) || (dot_3 != ptr_end && *dot_3 != '.') || ecc_3 != std::errc{})
            {
                return false;
            }

            uint32_t build{};

            auto [end_4, ecc_4] = std::from_chars(dot_3 + 1, ptr_end, build, 10);

            if (end_4 != ptr_end || ecc_4 != std::errc{})
            {
                return false;
            }

            result = {
                major,
                minor,
                patch,
                build
            };

            return true;
        }

        result = {};

        return false;
    }

}
