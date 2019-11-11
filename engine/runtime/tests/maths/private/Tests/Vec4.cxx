#include "Test.Maths.pch.hxx"
#include <Graphyte/Maths2/Vector.hxx>
#include <Graphyte/Maths2/Bool4.hxx>

TEST_CASE("Vec4 Operations")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::UnitX<M::Vec4>();
    M::Vec4 const v2 = M::UnitY<M::Vec4>();
    M::Vec4 const v3 = M::Add(v1, v2);

    CHECK(M::GetX(v3) == Approx{ 1.0F });
    CHECK(M::GetY(v3) == Approx{ 1.0F });
    CHECK(M::GetZ(v3) == Approx{ 0.0F });
    CHECK(M::GetW(v3) == Approx{ 0.0F });

    M::Vec4 const v4 = M::Make<M::Vec4>(2.0F, 3.0F);

    CHECK(M::GetX(v4) == Approx{ 2.0F });
    CHECK(M::GetY(v4) == Approx{ 3.0F });
    CHECK(M::GetZ(v4) == Approx{ 0.0F });
    CHECK(M::GetW(v4) == Approx{ 0.0F });

    M::Vec4 const v5 = M::SplatX(v4);

    CHECK(M::GetX(v5) == Approx{ 2.0F });
    CHECK(M::GetY(v5) == Approx{ 2.0F });
    CHECK(M::GetZ(v5) == Approx{ 2.0F });
    CHECK(M::GetW(v5) == Approx{ 2.0F });

    M::Vec4 const v6 = M::Mul(M::Add(v1, v2), M::Sub(v3, v4));

    CHECK(M::GetX(v6) == Approx{ -1.0F });
    CHECK(M::GetY(v6) == Approx{ -2.0F });
    CHECK(M::GetZ(v6) == Approx{ 0.0F });
    CHECK(M::GetW(v6) == Approx{ 0.0F });
}

TEST_CASE("Fused Multiply Add / Sub operations")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::Make<M::Vec4>(1.0F, 2.0F, 3.0F, 4.0F);
    M::Vec4 const v2 = M::Make<M::Vec4>(4.0F, 5.0F, 6.0F, 7.0F);
    M::Vec4 const v3 = M::Make<M::Vec4>(3.0F, 5.0F, 7.0F, 9.0F);

    SECTION("mul-add")
    {
        M::Vec4 const r = M::MulAdd(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ 7.0F });
        CHECK(M::GetY(r) == Approx{ 15.0F });
        CHECK(M::GetZ(r) == Approx{ 25.0F });
        CHECK(M::GetW(r) == Approx{ 37.0F });
    }

    SECTION("mul-sub")
    {
        M::Vec4 const r = M::MulSub(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ 1.0F });
        CHECK(M::GetY(r) == Approx{ 5.0F });
        CHECK(M::GetZ(r) == Approx{ 11.0F });
        CHECK(M::GetW(r) == Approx{ 19.0F });
    }

    SECTION("neg-mul-add")
    {
        M::Vec4 const r = M::NegMulAdd(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ -1.0F });
        CHECK(M::GetY(r) == Approx{ -5.0F });
        CHECK(M::GetZ(r) == Approx{ -11.0F });
        CHECK(M::GetW(r) == Approx{ -19.0F });
    }

    SECTION("neg-mul-sub")
    {
        M::Vec4 const r = M::NegMulSub(v1, v2, v3);

        CHECK(M::GetX(r) == Approx{ -7.0F });
        CHECK(M::GetY(r) == Approx{ -15.0F });
        CHECK(M::GetZ(r) == Approx{ -25.0F });
        CHECK(M::GetW(r) == Approx{ -37.0F });
    }
}

TEST_CASE("Vec / rounding")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::Make<M::Vec4>(0.25F, 0.5F, 0.75F, 1.0F);
    M::Vec4 const v2 = M::Make<M::Vec4>(0.15F, 0.55F, 0.65F, 1.1F);

    SECTION("min(v1,v2)")
    {
        M::Vec4 const r = M::Min(v1, v2);

        CHECK(M::GetX(r) == Approx{ 0.15F });
        CHECK(M::GetY(r) == Approx{ 0.5F });
        CHECK(M::GetZ(r) == Approx{ 0.65F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("max(v1,v2)")
    {
        M::Vec4 const r = M::Max(v1, v2);

        CHECK(M::GetX(r) == Approx{ 0.25F });
        CHECK(M::GetY(r) == Approx{ 0.55F });
        CHECK(M::GetZ(r) == Approx{ 0.75F });
        CHECK(M::GetW(r) == Approx{ 1.1F });
    }

    SECTION("round(v1)")
    {
        M::Vec4 const r = M::Round(v1);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("round(v2)")
    {
        M::Vec4 const r = M::Round(v2);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 1.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("truncate(v1)")
    {
        M::Vec4 const r = M::Truncate(v1);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("truncate(v2)")
    {
        M::Vec4 const r = M::Truncate(v2);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("floor(v1)")
    {
        M::Vec4 const r = M::Floor(v1);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("floor(v2)")
    {
        M::Vec4 const r = M::Floor(v2);

        CHECK(M::GetX(r) == Approx{ 0.0F });
        CHECK(M::GetY(r) == Approx{ 0.0F });
        CHECK(M::GetZ(r) == Approx{ 0.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("ceiling(v1)")
    {
        M::Vec4 const r = M::Ceiling(v1);

        CHECK(M::GetX(r) == Approx{ 1.0F });
        CHECK(M::GetY(r) == Approx{ 1.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 1.0F });
    }

    SECTION("ceiling(v2)")
    {
        M::Vec4 const r = M::Ceiling(v2);

        CHECK(M::GetX(r) == Approx{ 1.0F });
        CHECK(M::GetY(r) == Approx{ 1.0F });
        CHECK(M::GetZ(r) == Approx{ 1.0F });
        CHECK(M::GetW(r) == Approx{ 2.0F });
    }
}

TEST_CASE("Setting vector components")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::Zero<M::Vec4>();

    CHECK(M::GetX(v1) == Approx{ 0.0F });
    CHECK(M::GetY(v1) == Approx{ 0.0F });
    CHECK(M::GetZ(v1) == Approx{ 0.0F });
    CHECK(M::GetW(v1) == Approx{ 0.0F });

    M::Vec4 const v2 = M::SetX(v1, 1.0F);

    CHECK(M::GetX(v2) == Approx{ 1.0F });
    CHECK(M::GetY(v2) == Approx{ 0.0F });
    CHECK(M::GetZ(v2) == Approx{ 0.0F });
    CHECK(M::GetW(v2) == Approx{ 0.0F });

    M::Vec4 const v3 = M::SetY(v2, 2.0F);

    CHECK(M::GetX(v3) == Approx{ 1.0F });
    CHECK(M::GetY(v3) == Approx{ 2.0F });
    CHECK(M::GetZ(v3) == Approx{ 0.0F });
    CHECK(M::GetW(v3) == Approx{ 0.0F });

    M::Vec4 const v4 = M::SetZ(v3, 3.0F);

    CHECK(M::GetX(v4) == Approx{ 1.0F });
    CHECK(M::GetY(v4) == Approx{ 2.0F });
    CHECK(M::GetZ(v4) == Approx{ 3.0F });
    CHECK(M::GetW(v4) == Approx{ 0.0F });

    M::Vec4 const v5 = M::SetW(v4, 4.0F);

    CHECK(M::GetX(v5) == Approx{ 1.0F });
    CHECK(M::GetY(v5) == Approx{ 2.0F });
    CHECK(M::GetZ(v5) == Approx{ 3.0F });
    CHECK(M::GetW(v5) == Approx{ 4.0F });
}

TEST_CASE("Vec4 - length & normalization")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const ux = M::UnitX<M::Vec4>();
    M::Vec4 const uy = M::UnitY<M::Vec4>();
    M::Vec4 const uz = M::UnitZ<M::Vec4>();
    M::Vec4 const uw = M::UnitW<M::Vec4>();

    // double them
    M::Vec4 const uxx = M::Add(ux, ux);
    M::Vec4 const uyy = M::Add(uy, uy);
    M::Vec4 const uzz = M::Add(uz, uz);
    M::Vec4 const uww = M::Add(uw, uw);

    CHECK(M::GetX(M::Length(uxx)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uyy)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uzz)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uww)) == Approx{ 2.0F });

    M::Vec4 const nxx = M::Normalize(uxx);
    M::Vec4 const nyy = M::Normalize(uyy);
    M::Vec4 const nzz = M::Normalize(uzz);
    M::Vec4 const nww = M::Normalize(uww);

    CHECK(M::GetX(M::Length(nxx)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nyy)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nzz)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nww)) == Approx{ 1.0F });

    CHECK(M::GetX(M::Length(M::Zero<M::Vec4>())) == Approx{ 0.0F });
}


TEST_CASE("Vec3 - length & normalization")
{
    namespace M = Graphyte::Maths;

    M::Vec3 const ux = M::UnitX<M::Vec3>();
    M::Vec3 const uy = M::UnitY<M::Vec3>();
    M::Vec3 const uz = M::UnitZ<M::Vec3>();

    // double them
    M::Vec3 const uxx = M::Add(ux, ux);
    M::Vec3 const uyy = M::Add(uy, uy);
    M::Vec3 const uzz = M::Add(uz, uz);

    CHECK(M::GetX(M::Length(uxx)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uyy)) == Approx{ 2.0F });
    CHECK(M::GetX(M::Length(uzz)) == Approx{ 2.0F });

    M::Vec3 const nxx = M::Normalize(uxx);
    M::Vec3 const nyy = M::Normalize(uyy);
    M::Vec3 const nzz = M::Normalize(uzz);

    CHECK(M::GetX(M::Length(nxx)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nyy)) == Approx{ 1.0F });
    CHECK(M::GetX(M::Length(nzz)) == Approx{ 1.0F });

    CHECK(M::GetX(M::Length(M::Zero<M::Vec3>())) == Approx{ 0.0F });
}

TEST_CASE("Vec4 - order comparable")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::UnitX<M::Vec4>();
    M::Vec4 const v2 = M::UnitY<M::Vec4>();
    M::Vec4 const v3 = M::UnitZ<M::Vec4>();
    M::Vec4 const v4 = M::UnitW<M::Vec4>();

    CHECK_FALSE(M::IsEq(v1, v2));
    CHECK_FALSE(M::IsEq(v2, v3));
    CHECK_FALSE(M::IsEq(v3, v4));
    CHECK_FALSE(M::IsEq(v4, v1));

    CHECK(M::IsNeq(v1, v2));
    CHECK(M::IsNeq(v2, v3));
    CHECK(M::IsNeq(v3, v4));
    CHECK(M::IsNeq(v4, v1));
    
    CHECK_FALSE(M::IsLt(v1, v2));
    CHECK_FALSE(M::IsLt(v2, v3));
    CHECK_FALSE(M::IsLt(v3, v4));
    CHECK_FALSE(M::IsLt(v4, v1));

    CHECK_FALSE(M::IsLe(v1, v2));
    CHECK_FALSE(M::IsLe(v2, v3));
    CHECK_FALSE(M::IsLe(v3, v4));
    CHECK_FALSE(M::IsLe(v4, v1));

    CHECK_FALSE(M::IsGt(v1, v2));
    CHECK_FALSE(M::IsGt(v2, v3));
    CHECK_FALSE(M::IsGt(v3, v4));
    CHECK_FALSE(M::IsGt(v4, v1));

    CHECK_FALSE(M::IsGe(v1, v2));
    CHECK_FALSE(M::IsGe(v2, v3));
    CHECK_FALSE(M::IsGe(v3, v4));
    CHECK_FALSE(M::IsGe(v4, v1));

    CHECK(M::IsEq(M::Infinity<M::Vec4>(), M::Infinity<M::Vec4>()));
    CHECK_FALSE(M::IsNeq(M::Infinity<M::Vec4>(), M::Infinity<M::Vec4>()));

    REQUIRE(M::MulAdd(1.0F, 1.0F, 1.0F) == Approx{ 2.0F });
}

TEST_CASE("Vec4 - componentwise comparisons")
{
    namespace M = Graphyte::Maths;

    M::Vec4 const v1 = M::UnitX<M::Vec4>();
    M::Vec4 const v2 = M::UnitY<M::Vec4>();
    M::Vec4 const v3 = M::UnitZ<M::Vec4>();
    M::Vec4 const v4 = M::UnitW<M::Vec4>();

    M::Bool4 const b11 = M::CmpEq(v1, v1);
    M::Bool4 const b12 = M::CmpEq(v1, v2);
    M::Bool4 const b13 = M::CmpEq(v1, v3);
    M::Bool4 const b14 = M::CmpEq(v1, v4);

    M::Bool4 const b21 = M::CmpEq(v2, v1);
    M::Bool4 const b22 = M::CmpEq(v2, v2);
    M::Bool4 const b23 = M::CmpEq(v2, v3);
    M::Bool4 const b24 = M::CmpEq(v2, v4);

    M::Bool4 const b31 = M::CmpEq(v3, v1);
    M::Bool4 const b32 = M::CmpEq(v3, v2);
    M::Bool4 const b33 = M::CmpEq(v3, v3);
    M::Bool4 const b34 = M::CmpEq(v3, v4);

    M::Bool4 const b41 = M::CmpEq(v4, v1);
    M::Bool4 const b42 = M::CmpEq(v4, v2);
    M::Bool4 const b43 = M::CmpEq(v4, v3);
    M::Bool4 const b44 = M::CmpEq(v4, v4);

    CHECK(M::AnyTrue( b11));
    CHECK(M::AllTrue( b11));
    CHECK_FALSE(M::AnyFalse(b11));
    CHECK_FALSE(M::AllFalse(b11));

    CHECK(M::AnyTrue( b12));
    CHECK_FALSE(M::AllTrue( b12));
    CHECK(M::AnyFalse(b12));
    CHECK_FALSE(M::AllFalse(b12));

    CHECK(M::AnyTrue( b13));
    CHECK_FALSE(M::AllTrue( b13));
    CHECK(M::AnyFalse(b13));
    CHECK_FALSE(M::AllFalse(b13));

    CHECK(M::AnyTrue( b14));
    CHECK_FALSE(M::AllTrue( b14));
    CHECK(M::AnyFalse(b14));
    CHECK_FALSE(M::AllFalse(b14));

    CHECK(M::AnyTrue( b21));
    CHECK_FALSE(M::AllTrue( b21));
    CHECK(M::AnyFalse(b21));
    CHECK_FALSE(M::AllFalse(b21));

    CHECK(M::AnyTrue( b22));
    CHECK(M::AllTrue( b22));
    CHECK_FALSE(M::AnyFalse(b22));
    CHECK_FALSE(M::AllFalse(b22));

    CHECK(M::AnyTrue( b23));
    CHECK_FALSE(M::AllTrue( b23));
    CHECK(M::AnyFalse(b23));
    CHECK_FALSE(M::AllFalse(b23));

    CHECK(M::AnyTrue( b24));
    CHECK_FALSE(M::AllTrue( b24));
    CHECK(M::AnyFalse(b24));
    CHECK_FALSE(M::AllFalse(b24));

    CHECK(M::AnyTrue( b11));
    CHECK(M::AllTrue( b11));
    CHECK_FALSE(M::AnyFalse(b11));
    CHECK_FALSE(M::AllFalse(b11));

    CHECK(M::AnyTrue( b32));
    CHECK_FALSE(M::AllTrue( b32));
    CHECK(M::AnyFalse(b32));
    CHECK_FALSE(M::AllFalse(b32));

    CHECK(M::AnyTrue( b33));
    CHECK(M::AllTrue( b33));
    CHECK_FALSE(M::AnyFalse(b33));
    CHECK_FALSE(M::AllFalse(b33));

    CHECK(M::AnyTrue( b34));
    CHECK_FALSE(M::AllTrue( b34));
    CHECK(M::AnyFalse(b34));
    CHECK_FALSE(M::AllFalse(b34));

    CHECK(M::AnyTrue( b41));
    CHECK_FALSE(M::AllTrue( b41));
    CHECK(M::AnyFalse(b41));
    CHECK_FALSE(M::AllFalse(b41));

    CHECK(M::AnyTrue( b42));
    CHECK_FALSE(M::AllTrue( b42));
    CHECK(M::AnyFalse(b42));
    CHECK_FALSE(M::AllFalse(b42));

    CHECK(M::AnyTrue( b43));
    CHECK_FALSE(M::AllTrue( b43));
    CHECK(M::AnyFalse(b43));
    CHECK_FALSE(M::AllFalse(b43));

    CHECK(M::AnyTrue( b44));
    CHECK(M::AllTrue( b44));
    CHECK_FALSE(M::AnyFalse(b44));
    CHECK_FALSE(M::AllFalse(b44));
}
