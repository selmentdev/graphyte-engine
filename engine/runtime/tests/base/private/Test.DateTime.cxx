#include <catch2/catch.hpp>
#include <GxBase/DateTime.hxx>

TEST_CASE("DateTime")
{
    SECTION("Create simple time")
    {
        using namespace Graphyte;

        auto dt = DateTime::Create(2020, 5, 26, 7, 52, 11, 115);

        CalendarTime ct;
        dt.ToCalendar(ct);

        REQUIRE(ct.Year == 2020);
        REQUIRE(ct.Month == 5);
        REQUIRE(ct.Day == 26);
        REQUIRE(ct.Hour == 7);
        REQUIRE(ct.Minute == 52);
        REQUIRE(ct.Second == 11);
        REQUIRE(ct.Millisecond == 115);
        REQUIRE(ct.DayOfWeek == 2);
        REQUIRE(ct.DayOfYear == 147);
    }

    SECTION("ToString")
    {
        using namespace Graphyte;

        auto dt = DateTime::Create(2017, 12, 13, 17, 41, 25);

        std::string as_string{};
        REQUIRE(ToString(as_string, dt));

        CHECK(as_string == "2017-12-13 17:41:25");
        CHECK(dt.Value == 636487836850000000);

        CalendarTime members{};
        REQUIRE(dt.ToCalendar(members));

        CHECK(members.Year == 2017);
        CHECK(members.Month == 12);
        CHECK(members.Day == 13);
        CHECK(members.Hour == 17);
        CHECK(members.Minute == 41);
        CHECK(members.Second == 25);
        CHECK(members.Millisecond == 0);
        CHECK(members.DayOfWeek == 3);
        CHECK(members.DayOfYear == 347);
    }

    SECTION("Parsing ISO format")
    {
        using namespace Graphyte;

        // Fast check mast formats.
        {
            DateTime result{};
            CHECK(FromString(result, "1989-11-03T23:45:59"));
            CHECK(FromString(result, "2019-01-19T18:39:31.018"));
            CHECK(FromString(result, "2019-01-19T18:39:31+02:00"));
            CHECK(FromString(result, "2019-01-19T18:39:31-10:15"));
        }

        // Checking not full formats
        {
            DateTime result{};
            CHECK_FALSE(FromString(result, ""));
            CHECK_FALSE(FromString(result, "2"));
            CHECK_FALSE(FromString(result, "20"));
            CHECK_FALSE(FromString(result, "201"));
            CHECK_FALSE(FromString(result, "2019"));
            CHECK_FALSE(FromString(result, "2019-"));
            CHECK_FALSE(FromString(result, "2019-0"));
            CHECK_FALSE(FromString(result, "2019-01"));
            CHECK_FALSE(FromString(result, "2019-01-"));
            CHECK_FALSE(FromString(result, "2019-01-1"));
            CHECK(FromString(result, "2019-01-19"));
            CHECK_FALSE(FromString(result, "2019-01-19T"));
            CHECK_FALSE(FromString(result, "2019-01-19T1"));
            CHECK_FALSE(FromString(result, "2019-01-19T18"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:3"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:3"));
            CHECK(FromString(result, "2019-01-19T18:39:31"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:31+"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:31+0"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:31+02"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:31+02:"));
            CHECK_FALSE(FromString(result, "2019-01-19T18:39:31+02:0"));
            CHECK(FromString(result, "2019-01-19T18:39:31+02:00"));
        }

        {
            DateTime result{};
            CHECK(FromString(result, "1989-11-03T23:45:59"));

            CalendarTime time{};
            CHECK(result.ToCalendar(time));

            CHECK(time.Year == 1989);
            CHECK(time.Month == 11);
            CHECK(time.Day == 03);
            CHECK(time.Hour == 23);
            CHECK(time.Minute == 45);
            CHECK(time.Second == 59);
            CHECK(time.Millisecond == 0);
            CHECK(time.DayOfWeek == 5);
            CHECK(time.DayOfYear == 307);
        }
        {
            DateTime result{};
            CHECK(FromString(result, "2019-01-19T18:39:31.018"));

            CalendarTime time{};
            CHECK(result.ToCalendar(time));

            CHECK(time.Year == 2019);
            CHECK(time.Month == 1);
            CHECK(time.Day == 19);
            CHECK(time.Hour == 18);
            CHECK(time.Minute == 39);
            CHECK(time.Second == 31);
            CHECK(time.Millisecond == 18);
            CHECK(time.DayOfWeek == 6);
            CHECK(time.DayOfYear == 19);
        }
        {
            DateTime result{};
            CHECK(FromString(result, "2019-01-19T18:39:31+00:00"));

            CalendarTime time{};
            CHECK(result.ToCalendar(time));

            CHECK(time.Year == 2019);
            CHECK(time.Month == 1);
            CHECK(time.Day == 19);
            CHECK(time.Hour == 18);
            CHECK(time.Minute == 39);
            CHECK(time.Second == 31);
            CHECK(time.Millisecond == 0);
            CHECK(time.DayOfWeek == 6);
            CHECK(time.DayOfYear == 19);
        }
        {
            DateTime result{};
            CHECK(FromString(result, "2019-01-19T18:39:31.018+04:15"));

            CalendarTime time{};
            CHECK(result.ToCalendar(time));

            CHECK(time.Year == 2019);
            CHECK(time.Month == 1);
            CHECK(time.Day == 19);
            CHECK(time.Hour == 14);
            CHECK(time.Minute == 24);
            CHECK(time.Second == 31);
            CHECK(time.Millisecond == 18);
            CHECK(time.DayOfWeek == 6);
            CHECK(time.DayOfYear == 19);
        }
        {
            DateTime result{};
            CHECK(FromString(result, "2019-12-31T21:39:31.018-04:15"));

            CalendarTime time{};
            CHECK(result.ToCalendar(time));

            CHECK(time.Year == 2020);
            CHECK(time.Month == 1);
            CHECK(time.Day == 1);
            CHECK(time.Hour == 1);
            CHECK(time.Minute == 54);
            CHECK(time.Second == 31);
            CHECK(time.Millisecond == 18);
            CHECK(time.DayOfWeek == 3);
            CHECK(time.DayOfYear == 1);
        }
    }

    SECTION("Custom format")
    {
        using namespace Graphyte;

        auto dt = DateTime::Create(2018, 2, 10, 21, 24, 12, 4012);
        std::string as_string{};

        CHECK(ToString(as_string, dt, "%h%a_%h%A_(%y_%Y_%d) D%Y-%m-%dT%H:%M:%S.%s"));
        CHECK(as_string == "09pm_09PM_(18_2018_10) D2018-02-10T21:24:16.012");

        CHECK(ToString(as_string, dt, DateTimeFormat::Date));
        CHECK(as_string == "2018-02-10");

        CHECK(ToString(as_string, dt, DateTimeFormat::DateIso8601));
        CHECK(as_string == "2018-02-10");

        CHECK(ToString(as_string, dt, DateTimeFormat::DateTime));
        CHECK(as_string == "2018-02-10 21:24:16");

        CHECK(ToString(as_string, dt, DateTimeFormat::DateTimeIso8601));
        CHECK(as_string == "2018-02-10 21:24:16");

        CHECK(ToString(as_string, dt, DateTimeFormat::FileSafe));
        CHECK(as_string == "2018.02.10-21.24.16");

        CHECK(ToString(as_string, dt, DateTimeFormat::Time));
        CHECK(as_string == "21:24:16");

        CHECK(ToString(as_string, dt, DateTimeFormat::TimeStamp));
        CHECK(as_string == "2018.02.10-21.24.16.012");
    }

    SECTION("Adding time span")
    {
        using namespace Graphyte;

        DateTime dt = DateTime::Create(2017, 12, 13, 17, 41, 25);
        TimeSpan ts = TimeSpan::Create(31, 22, 15, 21, 204);
        dt += ts;

        std::string as_string{};
        REQUIRE(ToString(as_string, dt));

        CHECK(as_string == "2018-01-14 15:56:46");
        CHECK(dt.Value == 636515422062040000);

        CalendarTime members{};
        CHECK(dt.ToCalendar(members));

        CHECK(members.Year == 2018);
        CHECK(members.Month == 1);
        CHECK(members.Day == 14);
        CHECK(members.Hour == 15);
        CHECK(members.Minute == 56);
        CHECK(members.Second == 46);
        CHECK(members.Millisecond == 204);
        CHECK(members.DayOfWeek == 0);
        CHECK(members.DayOfYear == 14);
    }

    SECTION("Adding timespans")
    {
        using namespace Graphyte;

        TimeSpan ts1 = TimeSpan::Create(11, 14, 30);
        TimeSpan ts2 = TimeSpan::Create(12, 44, 29);
        TimeSpan ts3 = TimeSpan::Create(0, 1, 22);

        TimeSpan dts1 = ts1 + ts2;
        TimeSpan dts2 = ts2 + ts3;
        TimeSpan tts = ts1 + ts2 + ts3;

        std::string as_string{};
        CHECK(ToString(as_string, ts1));
        CHECK(as_string == "11:14:30.000");

        CHECK(ToString(as_string, ts2));
        CHECK(as_string == "12:44:29.000");

        CHECK(ToString(as_string, ts3));
        CHECK(as_string == "00:01:22.000");

        CHECK(ToString(as_string, dts1));
        CHECK(as_string == "23:58:59.000");

        CHECK(ToString(as_string, dts2));
        CHECK(as_string == "12:45:51.000");

        CHECK(ToString(as_string, tts));
        CHECK(as_string == "1.00:00:21.000");

        TimeSpanMembers members{};
        ts1.ToMembers(members);
        CHECK(members.Days == 0);
        CHECK(members.Hours == 11);
        CHECK(members.Minutes == 14);
        CHECK(members.Seconds == 30);
        CHECK(members.Milliseconds == 0);

        CHECK(static_cast<int64_t>(ts1.GetTotalDays()) == 0);
        CHECK(static_cast<int64_t>(ts1.GetTotalHours()) == 11);
        CHECK(static_cast<int64_t>(ts1.GetTotalMinutes()) == 674);
        CHECK(static_cast<int64_t>(ts1.GetTotalSeconds()) == 40470);
        CHECK(static_cast<int64_t>(ts1.GetTotalMilliseconds()) == 40470000);

        ts2.ToMembers(members);
        CHECK(members.Days == 0);
        CHECK(members.Hours == 12);
        CHECK(members.Minutes == 44);
        CHECK(members.Seconds == 29);
        CHECK(members.Milliseconds == 0);

        CHECK(static_cast<int64_t>(ts2.GetTotalDays()) == 0);
        CHECK(static_cast<int64_t>(ts2.GetTotalHours()) == 12);
        CHECK(static_cast<int64_t>(ts2.GetTotalMinutes()) == 764);
        CHECK(static_cast<int64_t>(ts2.GetTotalSeconds()) == 45869);
        CHECK(static_cast<int64_t>(ts2.GetTotalMilliseconds()) == 45869000);

        ts3.ToMembers(members);
        CHECK(members.Days == 0);
        CHECK(members.Hours == 0);
        CHECK(members.Minutes == 1);
        CHECK(members.Seconds == 22);
        CHECK(members.Milliseconds == 0);

        CHECK(static_cast<int64_t>(ts3.GetTotalDays()) == 0);
        CHECK(static_cast<int64_t>(ts3.GetTotalHours()) == 0);
        CHECK(static_cast<int64_t>(ts3.GetTotalMinutes()) == 1);
        CHECK(static_cast<int64_t>(ts3.GetTotalSeconds()) == 82);
        CHECK(static_cast<int64_t>(ts3.GetTotalMilliseconds()) == 82000);

        dts1.ToMembers(members);
        CHECK(members.Days == 0);
        CHECK(members.Hours == 23);
        CHECK(members.Minutes == 58);
        CHECK(members.Seconds == 59);
        CHECK(members.Milliseconds == 0);

        CHECK(static_cast<int64_t>(dts1.GetTotalDays()) == 0);
        CHECK(static_cast<int64_t>(dts1.GetTotalHours()) == 23);
        CHECK(static_cast<int64_t>(dts1.GetTotalMinutes()) == 1438);
        CHECK(static_cast<int64_t>(dts1.GetTotalSeconds()) == 86339);
        CHECK(static_cast<int64_t>(dts1.GetTotalMilliseconds()) == 86339000);

        dts2.ToMembers(members);
        CHECK(members.Days == 0);
        CHECK(members.Hours == 12);
        CHECK(members.Minutes == 45);
        CHECK(members.Seconds == 51);
        CHECK(members.Milliseconds == 0);

        CHECK(static_cast<int64_t>(dts2.GetTotalDays()) == 0);
        CHECK(static_cast<int64_t>(dts2.GetTotalHours()) == 12);
        CHECK(static_cast<int64_t>(dts2.GetTotalMinutes()) == 765);
        CHECK(static_cast<int64_t>(dts2.GetTotalSeconds()) == 45951);
        CHECK(static_cast<int64_t>(dts2.GetTotalMilliseconds()) == 45951000);

        tts.ToMembers(members);
        CHECK(members.Days == 1);
        CHECK(members.Hours == 0);
        CHECK(members.Minutes == 0);
        CHECK(members.Seconds == 21);
        CHECK(members.Milliseconds == 0);

        CHECK(static_cast<int64_t>(tts.GetTotalDays()) == 1);
        CHECK(static_cast<int64_t>(tts.GetTotalHours()) == 24);
        CHECK(static_cast<int64_t>(tts.GetTotalMinutes()) == 1440);
        CHECK(static_cast<int64_t>(tts.GetTotalSeconds()) == 86421);
        CHECK(static_cast<int64_t>(tts.GetTotalMilliseconds()) == 86421000);
    }
}
