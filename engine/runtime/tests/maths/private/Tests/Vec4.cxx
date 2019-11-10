#include "Test.Maths.pch.hxx"
#include <Graphyte/Maths2/Vector.hxx>

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
