#include <GxBase/String.hxx>
#include <GxBase/Diagnostics.hxx>

namespace Graphyte
{
    BASE_API void ReplaceAll(
        std::string& string,
        std::string_view from,
        std::string_view to
    ) noexcept
    {
        if (!string.empty())
        {
            size_t start_pos = 0;

            while ((start_pos = string.find(from, start_pos)) != std::string::npos)
            {
                string.replace(start_pos, from.length(), to);
                start_pos += to.length();
            }
        }
    }

    BASE_API std::vector<std::string_view> Split(
        std::string_view value,
        std::string_view separator,
        bool removeEmpty
    ) noexcept
    {
        std::vector<std::string_view> result{};

        std::string_view::size_type start = 0;

        size_t pos = value.find_first_of(separator, start);

        while (pos != std::string_view::npos)
        {
            if (pos != start || !removeEmpty)
            {
                result.push_back(value.substr(start, pos - start));
            }

            start = pos + 1;
            pos = value.find_first_of(separator, start);
        }

        // `<=` is used check whether empty element is added too.
        if (start < value.length() || !removeEmpty)
        {
            result.push_back(value.substr(start, value.length() - start));
        }

        return result;
    }

    BASE_API std::vector<std::string_view> Split(
        std::string_view value,
        char separator,
        bool removeEmpty
    ) noexcept
    {
        std::vector<std::string_view> result{};

        std::string_view::size_type start = 0;

        size_t pos = value.find_first_of(separator, start);

        while (pos != std::string_view::npos)
        {
            if (pos != start || !removeEmpty)
            {
                result.push_back(value.substr(start, pos - start));
            }

            start = pos + 1;
            pos = value.find_first_of(separator, start);
        }

        // `<=` is used check whether empty element is added too.
        if (start < value.length() || !removeEmpty)
        {
            result.push_back(value.substr(start, value.length() - start));
        }

        return result;
    }

    BASE_API bool MatchWildcard(
        std::string_view::const_iterator pattern_first,
        std::string_view::const_iterator pattern_last,
        std::string_view::const_iterator value_first,
        std::string_view::const_iterator value_last
    ) noexcept
    {
        std::string_view::const_iterator stored_pattern = pattern_first;
        std::string_view::const_iterator stored_value = value_first;

        bool restartable = false;

        while (value_first != value_last)
        {
            if (pattern_first != pattern_last && *pattern_first == '*')
            {
                if (++pattern_first == pattern_last)
                {
                    //
                    // Exit early if we cannot match next pattern character.
                    //

                    return true;
                }


                //
                // Store pattern and advance value.
                //

                stored_pattern = pattern_first;
                stored_value = value_first + 1;


                //
                // Matching first star enables restartable mode.
                //

                restartable = true;
            }
            else if (pattern_first != pattern_last && (*pattern_first == '?' || tolower(*pattern_first) == tolower(*value_first)))
            {
                //
                // Pattern matches value.
                //

                ++pattern_first;
                ++value_first;
            }
            else if (restartable == false)
            {
                //
                // Only star matching may restart operation.
                //

                return false;
            }
            else
            {
                if (stored_value == value_last)
                {
                    //
                    // Exit, because we can't restart operation.
                    //

                    return false;
                }


                //
                // Restart matching with stored pattern.
                //

                pattern_first = stored_pattern;
                value_first = stored_value++;
            }
        }

        while (pattern_first != pattern_last && *pattern_first == '*')
        {
            //
            // Consume any trailing `*`. Compared value matched succesfully.
            //

            ++pattern_first;
        }

        //
        // Check if pattern exhausted.
        //

        return pattern_first == pattern_last;
    }

    BASE_API bool HexStringToByteStream(
        std::vector<std::byte>& output,
        std::string_view input
    ) noexcept
    {
        if ((input.size() % 2) == 0)
        {
            output.clear();
            output.reserve(input.size() / 2);

            for (size_t i = 0; i < input.size(); i += 2)
            {
                uint8_t value{};

                auto const result = std::from_chars(&input[i], &input[i] + 2, value, 16);

                if (result.ec != std::errc{})
                {
                    return false;
                }

                output.push_back(static_cast<std::byte>(value));
            }

            return true;
        }

        return false;
    }

    BASE_API bool HexStringFromByteStream(
        std::string& output,
        notstd::span<const std::byte> input
    ) noexcept
    {
        std::array<char, 2> buffer{};

        output.resize(input.size() * 2);

        for (size_t i = 0; i < input.size(); ++i)
        {
            uint8_t const value = static_cast<uint8_t>(input[i]);

            auto const result = std::to_chars(buffer.data(), buffer.data() + 2, value, 16);
            
            if (result.ec != std::errc{})
            {
                return false;
            }

            output[i * 2 + 0] = buffer[0];

            if (result.ptr != (buffer.data() + 1))
            {
                output[i * 2 + 1] = buffer[1];
            }
            else
            {
                output[i * 2 + 1] = '0';
            }
        }

        return true;
    }
}
