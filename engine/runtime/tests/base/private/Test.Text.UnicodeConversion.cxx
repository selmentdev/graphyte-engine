#include <catch2/catch.hpp>
#include <GxBase/Unicode.hxx>

TEST_CASE("Unicode conversion")
{
    using namespace Graphyte::Text;

    SECTION("Codepoint reading - codepoint")
    {
        const char8_t sequence[] = u8"\U0001F601";

        auto source_start = std::begin(sequence);
        auto source_end   = std::end(sequence) - 1;

        char32_t cp1 = 0;
        char32_t cp2 = 0;

        REQUIRE(ConvertUTF8Sequence(&source_start, source_end, &cp1, ConversionType::Strict) == ConversionResult::Success);
        REQUIRE(cp1 == 0x1F601);
        REQUIRE(source_start == source_end);

        REQUIRE(ConvertUTF8Sequence(&source_start, source_end, &cp2, ConversionType::Strict) == ConversionResult::SourceExhausted);
        REQUIRE(cp2 == 0);
        REQUIRE(source_start == source_end);
    }

    SECTION("Codepoint reading - explicit bytes")
    {
        char8_t sequence[5];
        sequence[0] = 0xf0;
        sequence[1] = 0x9f;
        sequence[2] = 0x98;
        sequence[3] = 0x81;
        sequence[4] = 0;
        // { '\xf0', '\x9f', '\x98', '\x81' };

        const char8_t* source_start = std::begin(sequence);
        const char8_t* source_end   = std::end(sequence) - 1;

        char32_t cp1 = 0;
        char32_t cp2 = 0;

        REQUIRE(ConvertUTF8Sequence(&source_start, source_end, &cp1, ConversionType::Strict) == ConversionResult::Success);
        REQUIRE(cp1 == 0x1F601);
        REQUIRE(source_start == source_end);

        REQUIRE(ConvertUTF8Sequence(&source_start, source_end, &cp2, ConversionType::Strict) == ConversionResult::SourceExhausted);
        REQUIRE(cp2 == 0);
        REQUIRE(source_start == source_end);
    }

    SECTION("Codepoint conversion")
    {
        char32_t ch1 = U'\u20AC';

        std::array<char8_t, 8> target{};
        auto start = target.data();
        auto end   = target.data() + target.size();

        REQUIRE(ConvertUTF8Sequence(ch1, &start, end, ConversionType::Strict) == ConversionResult::Success);
        REQUIRE(target[0] == 0xe2);
        REQUIRE(target[1] == 0x82);
        REQUIRE(target[2] == 0xac);
        REQUIRE(target[3] == 0x00);
        REQUIRE(target[4] == 0x00);
    }

    SECTION("string -> wstring")
    {
        std::string source{ "\xf0\x9f\x98\x81" };
        std::wstring target{};

        REQUIRE(ConvertString(source, target, ConversionType::Strict) == ConversionResult::Success);

        if constexpr (sizeof(wchar_t) == sizeof(char16_t))
        {
            REQUIRE(target.length() == 2);
            REQUIRE(target[0] == L'\xD83D');
            REQUIRE(target[1] == L'\xDE01');
        }
#ifndef _MSC_VER
        else
        {
            REQUIRE(target.length() == 1);
            REQUIRE(target[0] == L'\U0001F601');
        }
#endif
    }

    SECTION("wstring -> string")
    {
        if constexpr (sizeof(wchar_t) == sizeof(char16_t))
        {
            std::wstring source{ L"\xD83D\xDE01" };
            std::string target{};

            CHECK(ConvertString(source, target, ConversionType::Strict) == ConversionResult::Success);

            REQUIRE(target.length() == 4);
            REQUIRE(static_cast<char8_t>(target[0]) == static_cast<char8_t>(0xf0));
            REQUIRE(static_cast<char8_t>(target[1]) == static_cast<char8_t>(0x9f));
            REQUIRE(static_cast<char8_t>(target[2]) == static_cast<char8_t>(0x98));
            REQUIRE(static_cast<char8_t>(target[3]) == static_cast<char8_t>(0x81));
        }
#ifndef _MSC_VER
        else
        {
            std::wstring source{ L"\U0001F601" };
            std::string target{};

            REQUIRE(ConvertString(source, target, ConversionType::Strict) == ConversionResult::Success);

            REQUIRE(target.length() == 4);
            REQUIRE(static_cast<char8_t>(target[0]) == static_cast<char8_t>(0xf0));
            REQUIRE(static_cast<char8_t>(target[1]) == static_cast<char8_t>(0x9f));
            REQUIRE(static_cast<char8_t>(target[2]) == static_cast<char8_t>(0x98));
            REQUIRE(static_cast<char8_t>(target[3]) == static_cast<char8_t>(0x81));
        }
#endif
    }

    SECTION("Malformed sequence")
    {
        std::string source{
            "\xD0\xBF\xD0\xBE\xD0\xB2\xD1\x80"
            "\xD0\xB5\xD0\xB6\xD0\xB4\xD0\xB5"
            "\xD0\xBD\xD0\xBD\xD0\xBE\xD0\xB9"
            "\x20\xF0\xBF\xD0\xBE\xD1\x81\xD0"
            "\xBB\xD0\xB5\xD0\xB4\xD0\xBE\xD0"
            "\xB2\xD0\xB0\xD1\x82\xD0\xB5\xD0"
            "\xBB\xD1\x8C\xD0\xBD\xD0\xBE\xD1"
            "\x81\xD1\x82\xD1\x8C\xD1\x8E"
        };

        std::u16string result{};

        REQUIRE(ConvertString(source, result, ConversionType::Strict) == ConversionResult::SourceIllegal);
        REQUIRE(result.empty());
        REQUIRE(result.length() == 0);

        REQUIRE(ConvertString(source, result, ConversionType::Tolerant) == ConversionResult::SourceIllegal);
        REQUIRE(result.empty());
        REQUIRE(result.length() == 0);
    }

    SECTION("Language conversion")
    {
        SECTION("Arabic")
        {
            std::string source_utf8{
                "\xD9\x85\xD8\xAD\xD8\xB1\xD9\x83"
                "\x20\xD8\xA7\xD9\x84\xD8\xB1\xD8"
                "\xB3\xD9\x88\xD9\x85\xD8\xA7\xD8"
                "\xAA\x20\xD9\x85\xD9\x83\xD8\xAA"
                "\xD9\x88\xD8\xA8\xD8\xA9\x20\xD8"
                "\xA8\xD9\x84\xD8\xBA\xD8\xA9\x20"
                "\xD8\xA7\xD9\x84\xD8\xA8\xD8\xB1"
                "\xD9\x85\xD8\xAC\xD8\xA9"
            };
            std::u16string source_utf16{
                u"\u0645\u062D\u0631\u0643\u0020\u0627\u0644\u0631"
                u"\u0633\u0648\u0645\u0627\u062A\u0020\u0645\u0643"
                u"\u062A\u0648\u0628\u0629\u0020\u0628\u0644\u063A"
                u"\u0629\u0020\u0627\u0644\u0628\u0631\u0645\u062C"
                u"\u0629"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Bengali")
        {
            std::string source_utf8{
                "\xE0\xA6\x97\xE0\xA7\x8D\xE0\xA6"
                "\xB0\xE0\xA6\xBE\xE0\xA6\xAB\xE0"
                "\xA6\xBF\xE0\xA6\x95\x20\xE0\xA6"
                "\x87\xE0\xA6\x9E\xE0\xA7\x8D\xE0"
                "\xA6\x9C\xE0\xA6\xBF\xE0\xA6\xA8"
                "\x20\xE0\xA6\x8F\xE0\xA6\x95\xE0"
                "\xA6\x9F\xE0\xA6\xBF\x20\xE0\xA6"
                "\xAA\xE0\xA7\x8D\xE0\xA6\xB0\xE0"
                "\xA7\x8B\xE0\xA6\x97\xE0\xA7\x8D"
                "\xE0\xA6\xB0\xE0\xA6\xBE\xE0\xA6"
                "\xAE\xE0\xA6\xBF\xE0\xA6\x82\x20"
                "\xE0\xA6\xAD\xE0\xA6\xBE\xE0\xA6"
                "\xB7\xE0\xA6\xBE\x20\xE0\xA6\xB2"
                "\xE0\xA7\x87\xE0\xA6\x96\xE0\xA6"
                "\xBE"
            };
            std::u16string source_utf16{
                u"\u0997\u09CD\u09B0\u09BE\u09AB\u09BF\u0995\u0020"
                u"\u0987\u099E\u09CD\u099C\u09BF\u09A8\u0020\u098F"
                u"\u0995\u099F\u09BF\u0020\u09AA\u09CD\u09B0\u09CB"
                u"\u0997\u09CD\u09B0\u09BE\u09AE\u09BF\u0982\u0020"
                u"\u09AD\u09BE\u09B7\u09BE\u0020\u09B2\u09C7\u0996"
                u"\u09BE"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Chinese")
        {
            std::string source_utf8{
                "\xE7\x9F\xB3\xE5\xA2\xA8\xE5\xBC"
                "\x95\xE6\x93\x8E\xE5\xBC\x95\xE8"
                "\x85\xB3\xE5\xAC\xB0\xE5\x85\x92"
            };
            std::u16string source_utf16{
                u"\u77F3\u58A8\u5F15\u64CE\u5F15\u8173\u5B30\u5152"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Japanese")
        {
            std::string source_utf8{
                "\xE3\x83\x97\xE3\x83\xAD\xE3\x82"
                "\xB0\xE3\x83\xA9\xE3\x83\x9F\xE3"
                "\x83\xB3\xE3\x82\xB0\xE8\xA8\x80"
                "\xE8\xAA\x9E\xE3\x81\xA7\xE6\x9B"
                "\xB8\xE3\x81\x8B\xE3\x82\x8C\xE3"
                "\x81\x9F\xE3\x82\xB0\xE3\x83\xA9"
                "\xE3\x83\x95\xE3\x82\xA3\xE3\x83"
                "\x83\xE3\x82\xAF\xE3\x82\xA8\xE3"
                "\x83\xB3\xE3\x82\xB8\xE3\x83\xB3"
            };
            std::u16string source_utf16{
                u"\u30D7\u30ED\u30B0\u30E9\u30DF\u30F3\u30B0\u8A00"
                u"\u8A9E\u3067\u66F8\u304B\u308C\u305F\u30B0\u30E9"
                u"\u30D5\u30A3\u30C3\u30AF\u30A8\u30F3\u30B8\u30F3"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Canada")
        {
            std::string source_utf8{
                "\xE0\xB2\x97\xE0\xB3\x8D\xE0\xB2"
                "\xB0\xE0\xB2\xBE\xE0\xB2\xAB\xE0"
                "\xB2\xBF\xE0\xB2\x95\xE0\xB3\x8D"
                "\x20\xE0\xB2\x8E\xE0\xB2\x82\xE0"
                "\xB2\x9C\xE0\xB2\xBF\xE0\xB2\xA8"
                "\xE0\xB3\x8D\x20\xE0\xB2\xAA\xE0"
                "\xB3\x8D\xE0\xB2\xB0\xE0\xB3\x86"
                "\xE0\xB3\x82\xE0\xB2\x97\xE0\xB3"
                "\x8D\xE0\xB2\xB0\xE0\xB2\xBE\xE0"
                "\xB2\xAE\xE0\xB2\xBF\xE0\xB2\x82"
                "\xE0\xB2\x97\xE0\xB3\x8D\x20\xE0"
                "\xB2\xAD\xE0\xB2\xBE\xE0\xB2\xB7"
                "\xE0\xB3\x86\xE0\xB2\xAF\xE0\xB2"
                "\xB2\xE0\xB3\x8D\xE0\xB2\xB2\xE0"
                "\xB2\xBF\x20\xE0\xB2\xAC\xE0\xB2"
                "\xB0\xE0\xB3\x86\xE0\xB2\xAF\xE0"
                "\xB2\xB2\xE0\xB2\xBE\xE0\xB2\xA6"
            };
            std::u16string source_utf16{
                u"\u0C97\u0CCD\u0CB0\u0CBE\u0CAB\u0CBF\u0C95\u0CCD"
                u"\u0020\u0C8E\u0C82\u0C9C\u0CBF\u0CA8\u0CCD\u0020"
                u"\u0CAA\u0CCD\u0CB0\u0CC6\u0CC2\u0C97\u0CCD\u0CB0"
                u"\u0CBE\u0CAE\u0CBF\u0C82\u0C97\u0CCD\u0020\u0CAD"
                u"\u0CBE\u0CB7\u0CC6\u0CAF\u0CB2\u0CCD\u0CB2\u0CBF"
                u"\u0020\u0CAC\u0CB0\u0CC6\u0CAF\u0CB2\u0CBE\u0CA6"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Korean")
        {
            std::string source_utf8{
                "\xEA\xB7\xB8\xEB\x9E\x98\xED\x94"
                "\xBD\x20\xEC\x97\x94\xEC\xA7\x84"
                "\xEC\x9D\x80\x20\xED\x94\x84\xEB"
                "\xA1\x9C\xEA\xB7\xB8\xEB\x9E\x98"
                "\xEB\xB0\x8D\x20\xEC\x96\xB8\xEC"
                "\x96\xB4\xEB\xA1\x9C\x20\xEC\x9E"
                "\x91\xEC\x84\xB1\xEB\x90\x9C"
            };
            std::u16string source_utf16{
                u"\uADF8\uB798\uD53D\u0020\uC5D4\uC9C4\uC740\u0020"
                u"\uD504\uB85C\uADF8\uB798\uBC0D\u0020\uC5B8\uC5B4"
                u"\uB85C\u0020\uC791\uC131\uB41C"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Lao")
        {
            std::string source_utf8{
                "\xE0\xBB\x88\xE0\xBA\x84\xE0\xBA"
                "\xB7\xE0\xBB\x88\xE0\xBA\xAD\xE0"
                "\xBA\x87\xE0\xBA\x88\xE0\xBA\xB1"
                "\xE0\xBA\x81\xE0\xBB\x83\xE0\xBA"
                "\x99\xE0\xBA\x81\xE0\xBA\xB2\xE0"
                "\xBA\x99\xE0\xBA\xAE\xE0\xBA\xB9"
                "\xE0\xBA\x9A\xE0\xBA\x9E\xE0\xBA"
                "\xB2\xE0\xBA\x9A\xE0\xBA\x82\xE0"
                "\xBA\xBD\xE0\xBA\x99\xE0\xBB\x80"
                "\xE0\xBA\x9B\xE0\xBA\xB1\xE0\xBA"
                "\x99\xE0\xBA\x9E\xE0\xBA\xB2\xE0"
                "\xBA\xAA\xE0\xBA\xB2\xE0\xBA\x81"
                "\xE0\xBA\xB2\xE0\xBA\x99\xE0\xBA"
                "\x82\xE0\xBA\xBD\xE0\xBA\x99\xE0"
                "\xBB\x82\xE0\xBA\x9B\xE0\xBA\xA3"
                "\xE0\xBB\x81\xE0\xBA\x81\xE0\xBA"
                "\xA3\xE0\xBA\xA1"
            };
            std::u16string source_utf16{
                u"\u0EC8\u0E84\u0EB7\u0EC8\u0EAD\u0E87\u0E88\u0EB1"
                u"\u0E81\u0EC3\u0E99\u0E81\u0EB2\u0E99\u0EAE\u0EB9"
                u"\u0E9A\u0E9E\u0EB2\u0E9A\u0E82\u0EBD\u0E99\u0EC0"
                u"\u0E9B\u0EB1\u0E99\u0E9E\u0EB2\u0EAA\u0EB2\u0E81"
                u"\u0EB2\u0E99\u0E82\u0EBD\u0E99\u0EC2\u0E9B\u0EA3"
                u"\u0EC1\u0E81\u0EA3\u0EA1"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Persian")
        {
            std::string source_utf8{
                "\xD9\x85\xD9\x88\xD8\xAA\xD9\x88"
                "\xD8\xB1\x20\xDA\xAF\xD8\xB1\xD8"
                "\xA7\xD9\x81\xDB\x8C\xDA\xA9\xDB"
                "\x8C\x20\xD8\xAF\xD8\xB1\x20\xDB"
                "\x8C\xDA\xA9\x20\xD8\xB2\xD8\xA8"
                "\xD8\xA7\xD9\x86\x20\xD8\xA8\xD8"
                "\xB1\xD9\x86\xD8\xA7\xD9\x85\xD9"
                "\x87\x20\xD9\x86\xD9\x88\xDB\x8C"
                "\xD8\xB3\xDB\x8C\x20\xD9\x86\xD9"
                "\x88\xD8\xB4\xD8\xAA\xD9\x87\x20"
                "\xD8\xB4\xD8\xAF\xD9\x87\x20\xD8"
                "\xA7\xD8\xB3\xD8\xAA"
            };
            std::u16string source_utf16{
                u"\u0645\u0648\u062A\u0648\u0631\u0020\u06AF\u0631"
                u"\u0627\u0641\u06CC\u06A9\u06CC\u0020\u062F\u0631"
                u"\u0020\u06CC\u06A9\u0020\u0632\u0628\u0627\u0646"
                u"\u0020\u0628\u0631\u0646\u0627\u0645\u0647\u0020"
                u"\u0646\u0648\u06CC\u0633\u06CC\u0020\u0646\u0648"
                u"\u0634\u062A\u0647\u0020\u0634\u062F\u0647\u0020"
                u"\u0627\u0633\u062A"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Vietnamese")
        {
            std::string source_utf8{
                "\xC4\x91\xE1\xBB\x93\x20\x68\xE1"
                "\xBB\x8D\x61\x20\x65\x6E\x67\x69"
                "\x6E\x65\x20\xC4\x91\xC6\xB0\xE1"
                "\xBB\xA3\x63\x20\x76\x69\xE1\xBA"
                "\xBF\x74\x20\x74\x72\x6F\x6E\x67"
                "\x20\x6D\xE1\xBB\x99\x74\x20\x6E"
                "\x67\xC3\xB4\x6E\x20\x6E\x67\xE1"
                "\xBB\xAF\x20\x6C\xE1\xBA\xAD\x70"
                "\x20\x74\x72\xC3\xAC\x6E\x68"
            };
            std::u16string source_utf16{
                u"\u0111\u1ED3\u0020\u0068\u1ECD\u0061\u0020\u0065"
                u"\u006E\u0067\u0069\u006E\u0065\u0020\u0111\u01B0"
                u"\u1EE3\u0063\u0020\u0076\u0069\u1EBF\u0074\u0020"
                u"\u0074\u0072\u006F\u006E\u0067\u0020\u006D\u1ED9"
                u"\u0074\u0020\u006E\u0067\u00F4\u006E\u0020\u006E"
                u"\u0067\u1EEF\u0020\u006C\u1EAD\u0070\u0020\u0074"
                u"\u0072\u00EC\u006E\u0068"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Urdu")
        {
            std::string source_utf8{
                "\xDA\xAF\xD8\xB1\xD8\xA7\xD9\x81"
                "\xDA\xA9\x20\xD8\xA7\xD9\x86\xD8"
                "\xAC\xD9\x86\x20\xD8\xA7\xDB\x8C"
                "\xDA\xA9\x20\xD9\xBE\xD8\xB1\xD9"
                "\x88\xDA\xAF\xD8\xB1\xD8\xA7\xD9"
                "\x85\xD9\x86\xDA\xAF\x20\xD8\xB2"
                "\xD8\xA8\xD8\xA7\xD9\x86\x20\xD9"
                "\x85\xDB\x8C\xDA\xBA\x20\xD9\x88"
                "\xD8\xB2\xD9\xB9\xD8\xB1\xD8\xB2"
                "\x20\xDA\xA9\xD8\xA7\x20\xD8\xB1"
                "\xDB\x8C\xDA\xA9\xD8\xA7\xD8\xB1"
                "\xDA\x88\x20\xD8\xB1\xDA\xA9\xDA"
                "\xBE\xD8\xA7\x20\xD8\xAC\xD8\xA7"
                "\xD8\xA6\xDB\x92\x20\xDA\xAF\xD8"
                "\xA7"
            };
            std::u16string source_utf16{
                u"\u06AF\u0631\u0627\u0641\u06A9\u0020\u0627\u0646"
                u"\u062C\u0646\u0020\u0627\u06CC\u06A9\u0020\u067E"
                u"\u0631\u0648\u06AF\u0631\u0627\u0645\u0646\u06AF"
                u"\u0020\u0632\u0628\u0627\u0646\u0020\u0645\u06CC"
                u"\u06BA\u0020\u0648\u0632\u0679\u0631\u0632\u0020"
                u"\u06A9\u0627\u0020\u0631\u06CC\u06A9\u0627\u0631"
                u"\u0688\u0020\u0631\u06A9\u06BE\u0627\u0020\u062C"
                u"\u0627\u0626\u06D2\u0020\u06AF\u0627"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Tamil")
        {
            std::string source_utf8{
                "\xE0\xAE\x95\xE0\xAE\xBF\xE0\xAE"
                "\xB0\xE0\xAE\xBE\xE0\xAE\x83\xE0"
                "\xAE\xAA\xE0\xAE\xBF\xE0\xAE\x95"
                "\xE0\xAF\x8D\x20\xE0\xAE\x87\xE0"
                "\xAE\xAF\xE0\xAE\xA8\xE0\xAF\x8D"
                "\xE0\xAE\xA4\xE0\xAE\xBF\xE0\xAE"
                "\xB0\xE0\xAE\xAE\xE0\xAF\x8D\x20"
                "\xE0\xAE\x92\xE0\xAE\xB0\xE0\xAF"
                "\x81\x20\xE0\xAE\xA8\xE0\xAE\xBF"
                "\xE0\xAE\xB0\xE0\xAE\xB2\xE0\xAE"
                "\xBE\xE0\xAE\x95\xE0\xAF\x8D\xE0"
                "\xAE\x95\x20\xE0\xAE\xAE\xE0\xAF"
                "\x86\xE0\xAE\xBE\xE0\xAE\xB4\xE0"
                "\xAE\xBF\xE0\xAE\xAF\xE0\xAE\xBF"
                "\xE0\xAE\xB2\xE0\xAF\x8D\x20\xE0"
                "\xAE\x8E\xE0\xAE\xB4\xE0\xAF\x81"
                "\xE0\xAE\xA4\xE0\xAE\xAA\xE0\xAF"
                "\x8D\xE0\xAE\xAA\xE0\xAE\x9F\xE0"
                "\xAF\x8D\xE0\xAE\x9F"
            };
            std::u16string source_utf16{
                u"\u0B95\u0BBF\u0BB0\u0BBE\u0B83\u0BAA\u0BBF\u0B95"
                u"\u0BCD\u0020\u0B87\u0BAF\u0BA8\u0BCD\u0BA4\u0BBF"
                u"\u0BB0\u0BAE\u0BCD\u0020\u0B92\u0BB0\u0BC1\u0020"
                u"\u0BA8\u0BBF\u0BB0\u0BB2\u0BBE\u0B95\u0BCD\u0B95"
                u"\u0020\u0BAE\u0BC6\u0BBE\u0BB4\u0BBF\u0BAF\u0BBF"
                u"\u0BB2\u0BCD\u0020\u0B8E\u0BB4\u0BC1\u0BA4\u0BAA"
                u"\u0BCD\u0BAA\u0B9F\u0BCD\u0B9F"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Thai")
        {
            std::string source_utf8{
                "\xE0\xB9\x80\xE0\xB8\x84\xE0\xB8"
                "\xA3\xE0\xB8\xB7\xE0\xB9\x88\xE0"
                "\xB8\xAD\xE0\xB8\x87\xE0\xB8\xA2"
                "\xE0\xB8\x99\xE0\xB8\x95\xE0\xB9"
                "\x8C\xE0\xB8\x81\xE0\xB8\xA3\xE0"
                "\xB8\xB2\xE0\xB8\x9F\xE0\xB8\xB4"
                "\xE0\xB8\x81\xE0\xB8\x97\xE0\xB8"
                "\xB5\xE0\xB9\x88\xE0\xB9\x80\xE0"
                "\xB8\x82\xE0\xB8\xB5\xE0\xB8\xA2"
                "\xE0\xB8\x99\xE0\xB9\x83\xE0\xB8"
                "\x99\xE0\xB8\xA0\xE0\xB8\xB2\xE0"
                "\xB8\xA9\xE0\xB8\xB2\xE0\xB8\x81"
                "\xE0\xB8\xB2\xE0\xB8\xA3\xE0\xB9"
                "\x80\xE0\xB8\x82\xE0\xB8\xB5\xE0"
                "\xB8\xA2\xE0\xB8\x99\xE0\xB9\x82"
                "\xE0\xB8\x9B\xE0\xB8\xA3\xE0\xB9"
                "\x81\xE0\xB8\x81\xE0\xB8\xA3\xE0"
                "\xB8\xA1"
            };
            std::u16string source_utf16{
                u"\u0E40\u0E04\u0E23\u0E37\u0E48\u0E2D\u0E07\u0E22"
                u"\u0E19\u0E15\u0E4C\u0E01\u0E23\u0E32\u0E1f\u0E34"
                u"\u0E01\u0E17\u0E35\u0E48\u0E40\u0E02\u0E35\u0E22"
                u"\u0E19\u0E43\u0E19\u0E20\u0E32\u0E29\u0E32\u0E01"
                u"\u0E32\u0E23\u0E40\u0E02\u0E35\u0E22\u0E19\u0E42"
                u"\u0E1B\u0E23\u0E41\u0E01\u0E23\u0E21"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Russian")
        {
            std::string source_utf8{
                "\xD0\x93\xD1\x80\xD0\xB0\xD1\x84"
                "\xD0\xB8\xD1\x82\x20\xD0\xB4\xD0"
                "\xB2\xD0\xB8\xD0\xB3\xD0\xB0\xD1"
                "\x82\xD0\xB5\xD0\xBB\xD1\x8F"
            };
            std::u16string source_utf16{
                u"\u0413\u0440\u0430\u0444\u0438\u0442\u0020\u0434"
                u"\u0432\u0438\u0433\u0430\u0442\u0435\u043B\u044F"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }

        SECTION("Yiddish")
        {
            std::string source_utf8{
                "\xD7\x92\xD7\xA8\xD7\x90\xD6\xB7"
                "\xD7\xA4\xD7\x99\xD7\x98\xD7\xA2"
                "\x20\xD7\x9E\xD7\x90\xD6\xB8\xD7"
                "\x98\xD7\x90\xD6\xB8\xD7\xA8"
            };
            std::u16string source_utf16{
                u"\u05D2\u05E8\u05D0\u05B7\u05E4\u05D9\u05D8\u05E2"
                u"\u0020\u05DE\u05D0\u05B8\u05D8\u05D0\u05B8\u05E8"
            };

            std::u16string result_utf16{};
            std::string result_utf8{};

            REQUIRE(ConvertString(source_utf8, result_utf16, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf16 == source_utf16);

            REQUIRE(ConvertString(source_utf16, result_utf8, ConversionType::Strict) == ConversionResult::Success);
            REQUIRE(result_utf8 == source_utf8);
        }
    }
}
