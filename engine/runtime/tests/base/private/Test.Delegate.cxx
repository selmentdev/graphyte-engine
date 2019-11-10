#include "Test.Base.pch.hxx"
#include <Graphyte/Delegate.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Delegate.hxx>

namespace
{
    static int testfn(int a, int b, int c) noexcept
    {
        return a + b + c;
    }

    struct teststrct
    {
        int member(int a, int b, int c) noexcept
        {
            return a + b - c * 2;
        }
        static int stmem(int a, int b, int c) noexcept
        {
            return a - b + c;
        }
    };

    using cb_delegate = Graphyte::Delegate<int(int, int, int)>;

    GX_NOINLINE int callit(const cb_delegate& g, int a, int b, int c) noexcept
    {
        return g(a, b, c);
    }

    void do_callback([[maybe_unused]] int a, [[maybe_unused]] int b)
    {
    }

    struct demobj
    {
        void member([[maybe_unused]] int a, [[maybe_unused]] int b)
        {
        }

        static void static_fn([[maybe_unused]] int a, [[maybe_unused]] int b)
        {
        }
    };

    struct someobj
    {
        void member([[maybe_unused]] int a, [[maybe_unused]] int b)
        {
        }

        static void static_fn([[maybe_unused]] int a, [[maybe_unused]] int b)
        {
        }
    };
}

TEST_CASE("Delegates")
{
    SECTION("Main test")
    {
        cb_delegate dg = cb_delegate::Make<testfn>();
        CHECK(dg(1, 2, 3) == 6);
    }

    SECTION("Object memberz")
    {
        teststrct sss{};

        cb_delegate dg1 = cb_delegate::Make<teststrct::stmem>();

        CHECK(dg1(1, 2, 3) == 2);
        static_assert(sizeof(dg1) == (sizeof(void*) * 2));

        cb_delegate dg2 = cb_delegate::Make<teststrct, &teststrct::member>(&sss);
        CHECK(dg2(1, 2, 3) == -3);

        CHECK(callit(dg1, 2, 3, 4) == 3);
        CHECK(callit(dg2, 2, 3, 4) == -3);
    }
}

TEST_CASE("Events")
{
    SECTION("Event")
    {
        using cb_event = Graphyte::Event<void(int, int)>;
        cb_event evt{};
        demobj demobjx{};
        someobj someobjx{};

        evt += cb_event::DelegateType::Make<&do_callback>();
        evt += cb_event::DelegateType::Make<demobj, &demobj::member>(&demobjx);
        evt += cb_event::DelegateType::Make<&demobj::static_fn>();
        evt += cb_event::DelegateType::Make<someobj, &someobj::member>(&someobjx);
        evt += cb_event::DelegateType::Make<&someobj::static_fn>();

        evt.Invoke(2, 4);

        evt -= cb_event::DelegateType::Make<&demobj::static_fn>();
        evt -= cb_event::DelegateType::Make<someobj, &someobj::member>(&someobjx);

        evt.Invoke(2, 4);
    }
}
