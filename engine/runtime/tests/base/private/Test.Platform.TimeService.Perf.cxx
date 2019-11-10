#include "Test.Base.pch.hxx"
#include <Graphyte/System.hxx>
#include <Graphyte/Threading/Thread.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Diagnostics/Stopwatch.hxx>

TEST_CASE("Performance Counter Frequency", "[.][performance]")
{
    using namespace Graphyte::Threading;
    using Graphyte::Diagnostics::Stopwatch;

    static constexpr const auto seconds = 3.5F;

    Stopwatch watch{};

    watch.Start();
    {
        SleepThread(static_cast<int64_t>(seconds * 1000));
    }
    watch.Stop();

    auto elapsed = watch.GetElapsedTime();

    REQUIRE(elapsed == Approx(seconds).margin(0.1));
}
