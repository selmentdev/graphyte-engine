#include "Test.Maths.pch.hxx"
#include <Graphyte/Maths2/Vector.hxx>
#include <Graphyte/Maths2/Bool4.hxx>

TEST_CASE("Bool4 - logic operations")
{
    namespace M = Graphyte::Maths;

    M::Bool4 const v1 = M::MakeMask(0xFFFF'FFFF, 0x0000'0000, 0x0000'0000, 0x0000'0000);
    M::Bool4 const v2 = M::MakeMask(0x0000'0000, 0xFFFF'FFFF, 0x0000'0000, 0x0000'0000);
    M::Bool4 const v3 = M::MakeMask(0x0000'0000, 0x0000'0000, 0xFFFF'FFFF, 0x0000'0000);
    M::Bool4 const v4 = M::MakeMask(0x0000'0000, 0x0000'0000, 0x0000'0000, 0xFFFF'FFFF);

    // mix all bits
    SECTION("And")
    {
        M::Bool4 const val = M::And(M::And(v1, v2), M::And(v3, v4));
        M::Bool4 const ret = M::CmpEq(val, M::True<M::Bool4>());

        CHECK_FALSE(M::AnyTrue(ret));
        CHECK(M::AnyFalse(ret));
        CHECK_FALSE(M::AllTrue(ret));
        CHECK(M::AllFalse(ret));
    }

    SECTION("Or")
    {
        M::Bool4 const val = M::Or(M::Or(v1, v2), M::Or(v3, v4));
        M::Bool4 const ret = M::CmpEq(val, M::True<M::Bool4>());

        CHECK(M::AnyTrue(ret));
        CHECK_FALSE(M::AnyFalse(ret));
        CHECK(M::AllTrue(ret));
        CHECK_FALSE(M::AllFalse(ret));
    }

    SECTION("AndNot")
    {
        M::Bool4 const val = M::AndNot(M::AndNot(v1, v2), M::AndNot(v3, v4));
        M::Bool4 const ret = M::CmpEq(val, M::True<M::Bool4>());

        CHECK(M::AnyTrue(ret));
        CHECK(M::AnyFalse(ret));
        CHECK_FALSE(M::AllTrue(ret));
        CHECK_FALSE(M::AllFalse(ret));
    }

    SECTION("Xor")
    {
        M::Bool4 const val = M::Xor(M::Xor(v1, v2), M::Xor(v3, v4));
        M::Bool4 const ret = M::CmpEq(val, M::True<M::Bool4>());

        CHECK(M::AnyTrue(ret));
        CHECK_FALSE(M::AnyFalse(ret));
        CHECK(M::AllTrue(ret));
        CHECK_FALSE(M::AllFalse(ret));
    }
}
