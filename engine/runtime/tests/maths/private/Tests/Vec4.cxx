#include "Test.Maths.pch.hxx"
#include <Graphyte/Maths.hxx>

TEST_CASE("Maths / LoadStore")
{
    using namespace Graphyte::Maths;

    Float4A const f1{ 1.0F, 2.0F, 3.0F, 4.0F };
    Vector4 const v1 = Load<Vector4>(&f1);

    CHECK(GetX(v1) == 1.0F);
    CHECK(GetY(v1) == 2.0F);
    CHECK(GetZ(v1) == 3.0F);
    CHECK(GetW(v1) == 4.0F);

    Float3A f2{};
    Store<Vector4>(&f2, v1);

    CHECK(f2.X == 1.0F);
    CHECK(f2.Y == 2.0F);
    CHECK(f2.Z == 3.0F);

    Plane const p1 = Load<Plane>(&f1);
    Float2A f3{};
    Store<Plane>(&f3, p1);

    CHECK(f3.X == 1.0F);
    CHECK(f3.Y == 2.0F);
}

TEST_CASE("Maths / Vector4 / Cross Product")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 5.0F, 3.0F, 4.0F);
    Vector4 const b = Make<Vector4>(7.0F, 7.0F, 9.0F, 10.0F);
    Vector4 const c = Make<Vector4>(3.0F, 7.0F, 4.0F, -1.0F);

    Vector4 const abc = Cross(a, b, c);

    Graphyte::Maths::Impl::ConstFloat32x4 cc;
    cc.V = abc.V;

    CHECK(cc.F[0] == -154.0F);
    CHECK(cc.F[1] == -66.0F);
    CHECK(cc.F[2] == 220.0F);
    CHECK(cc.F[3] == -44.0F);
}

TEST_CASE("Maths / Vector4 / Dot Product")
{
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 5.0F, 3.0F, 4.0F);
    Vector4 const b = Make<Vector4>(7.0F, 7.0F, 9.0F, 10.0F);
    Vector4 const c = Make<Vector4>(3.0F, 7.0F, 4.0F, -1.0F);

    //Vector4 Dot(a, b);
}

TEST_CASE("Maths / Vector / Rounding")
{
    using namespace Graphyte::Maths;

    Vector4 const v1 = Make<Vector4>(0.1F, 0.4F, 0.6F, 0.9F);
    Vector4 const v2 = Make<Vector4>(-0.1F, 0.5F, -0.5F, -0.9F);

    Vector4 const v3 = Make<Vector4>(10.1F, 3330.4F, 5510.6F, 124420.9F);
    Vector4 const v4 = Make<Vector4>(-20.1F, 44444440.5F, -1120.5F, -512520.9F);

    SECTION("Round")
    {
        Vector4 const r1 = Round(v1);
        Vector4 const r2 = Round(v2);
        Vector4 const r3 = Round(v3);
        Vector4 const r4 = Round(v4);

        CHECK(GetX(r1) == Approx{ 0.0F });
        CHECK(GetY(r1) == Approx{ 0.0F });
        CHECK(GetZ(r1) == Approx{ 1.0F });
        CHECK(GetW(r1) == Approx{ 1.0F });

        CHECK(GetX(r2) == Approx{ 0.0F });
        CHECK(GetY(r2) == Approx{ 0.0F });
        CHECK(GetZ(r2) == Approx{ 0.0F });
        CHECK(GetW(r2) == Approx{ -1.0F });

        CHECK(GetX(r3) == Approx{ 10.0F });
        CHECK(GetY(r3) == Approx{ 3330.0F });
        CHECK(GetZ(r3) == Approx{ 5511.0F });
        CHECK(GetW(r3) == Approx{ 124421.0F });

        CHECK(GetX(r4) == Approx{ -20.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1120.0F });
        CHECK(GetW(r4) == Approx{ -512521.0F });

        CHECK(Round(0.1F) == Approx{ 0.0F });
        CHECK(Round(0.4F) == Approx{ 0.0F });
        CHECK(Round(0.6F) == Approx{ 1.0F });
        CHECK(Round(0.9F) == Approx{ 1.0F });
        CHECK(Round(-0.1F) == Approx{ 0.0F });
        CHECK(Round(0.5F) == Approx{ 1.0F });
        CHECK(Round(-0.5F) == Approx{ -1.0F });
        CHECK(Round(-0.9F) == Approx{ -1.0F });
    }

    SECTION("Truncate")
    {
        Vector4 const r1 = Truncate(v1);
        Vector4 const r2 = Truncate(v2);
        Vector4 const r3 = Truncate(v3);
        Vector4 const r4 = Truncate(v4);

        CHECK(GetX(r1) == Approx{ 0.0F });
        CHECK(GetY(r1) == Approx{ 0.0F });
        CHECK(GetZ(r1) == Approx{ 0.0F });
        CHECK(GetW(r1) == Approx{ 0.0F });

        CHECK(GetX(r2) == Approx{ 0.0F });
        CHECK(GetY(r2) == Approx{ 0.0F });
        CHECK(GetZ(r2) == Approx{ 0.0F });
        CHECK(GetW(r2) == Approx{ 0.0F });

        CHECK(GetX(r3) == Approx{ 10.0F });
        CHECK(GetY(r3) == Approx{ 3330.0F });
        CHECK(GetZ(r3) == Approx{ 5510.0F });
        CHECK(GetW(r3) == Approx{ 124420.0F });

        CHECK(GetX(r4) == Approx{ -20.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1120.0F });
        CHECK(GetW(r4) == Approx{ -512520.0F });

        CHECK(Truncate(0.1F) == Approx{ 0.0F });
        CHECK(Truncate(0.4F) == Approx{ 0.0F });
        CHECK(Truncate(0.6F) == Approx{ 0.0F });
        CHECK(Truncate(0.9F) == Approx{ 0.0F });
        CHECK(Truncate(-0.1F) == Approx{ 0.0F });
        CHECK(Truncate(0.5F) == Approx{ 0.0F });
        CHECK(Truncate(-0.5F) == Approx{ -0.0F });
        CHECK(Truncate(-0.9F) == Approx{ -0.0F });
    }

    SECTION("Floor")
    {
        Vector4 const r1 = Floor(v1);
        Vector4 const r2 = Floor(v2);
        Vector4 const r3 = Floor(v3);
        Vector4 const r4 = Floor(v4);

        CHECK(GetX(r1) == Approx{ 0.0F });
        CHECK(GetY(r1) == Approx{ 0.0F });
        CHECK(GetZ(r1) == Approx{ 0.0F });
        CHECK(GetW(r1) == Approx{ 0.0F });

        CHECK(GetX(r2) == Approx{ -1.0F });
        CHECK(GetY(r2) == Approx{ 0.0F });
        CHECK(GetZ(r2) == Approx{ -1.0F });
        CHECK(GetW(r2) == Approx{ -1.0F });

        CHECK(GetX(r3) == Approx{ 10.0F });
        CHECK(GetY(r3) == Approx{ 3330.0F });
        CHECK(GetZ(r3) == Approx{ 5510.0F });
        CHECK(GetW(r3) == Approx{ 124420.0F });

        CHECK(GetX(r4) == Approx{ -21.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1121.0F });
        CHECK(GetW(r4) == Approx{ -512520.0F });

        CHECK(Floor(0.1F) == Approx{ 0.0F });
        CHECK(Floor(0.4F) == Approx{ 0.0F });
        CHECK(Floor(0.6F) == Approx{ 0.0F });
        CHECK(Floor(0.9F) == Approx{ 0.0F });
        CHECK(Floor(-0.1F) == Approx{ -1.0F });
        CHECK(Floor(0.5F) == Approx{ 0.0F });
        CHECK(Floor(-0.5F) == Approx{ -1.0F });
        CHECK(Floor(-0.9F) == Approx{ -1.0F });
    }

    SECTION("Ceiling")
    {
        Vector4 const r1 = Ceiling(v1);
        Vector4 const r2 = Ceiling(v2);
        Vector4 const r3 = Ceiling(v3);
        Vector4 const r4 = Ceiling(v4);

        CHECK(GetX(r1) == Approx{ 1.0F });
        CHECK(GetY(r1) == Approx{ 1.0F });
        CHECK(GetZ(r1) == Approx{ 1.0F });
        CHECK(GetW(r1) == Approx{ 1.0F });

        CHECK(GetX(r2) == Approx{ 0.0F });
        CHECK(GetY(r2) == Approx{ 1.0F });
        CHECK(GetZ(r2) == Approx{ 0.0F });
        CHECK(GetW(r2) == Approx{ 0.0F });

        CHECK(GetX(r3) == Approx{ 11.0F });
        CHECK(GetY(r3) == Approx{ 3331.0F });
        CHECK(GetZ(r3) == Approx{ 5511.0F });
        CHECK(GetW(r3) == Approx{ 124420.0F });

        CHECK(GetX(r4) == Approx{ -20.0F });
        CHECK(GetY(r4) == Approx{ 44444440.0F });
        CHECK(GetZ(r4) == Approx{ -1120.0F });
        CHECK(GetW(r4) == Approx{ -512520.0F });

        CHECK(Ceiling(0.1F) == Approx{ 1.0F });
        CHECK(Ceiling(0.4F) == Approx{ 1.0F });
        CHECK(Ceiling(0.6F) == Approx{ 1.0F });
        CHECK(Ceiling(0.9F) == Approx{ 1.0F });
        CHECK(Ceiling(-0.1F) == Approx{ 0.0F });
        CHECK(Ceiling(0.5F) == Approx{ 1.0F });
        CHECK(Ceiling(-0.5F) == Approx{ -0.0F });
        CHECK(Ceiling(-0.9F) == Approx{ -0.0F });
    }

    SECTION("Fraction")
    {
        Vector4 const r1 = Fraction(v1, One<Vector4>());
        Vector4 const r2 = Fraction(v2, One<Vector4>());
        Vector4 const r3 = Fraction(v3, One<Vector4>());
        Vector4 const r4 = Fraction(v4, One<Vector4>());

        CHECK(GetX(r1) == Approx{ 0.1F });
        CHECK(GetY(r1) == Approx{ 0.4F });
        CHECK(GetZ(r1) == Approx{ 0.6F });
        CHECK(GetW(r1) == Approx{ 0.9F });

        CHECK(GetX(r2) == Approx{ -0.1F });
        CHECK(GetY(r2) == Approx{ 0.5F });
        CHECK(GetZ(r2) == Approx{ -0.5F });
        CHECK(GetW(r2) == Approx{ -0.9F });

        CHECK(GetX(r3) == Approx{ 0.1F });
        CHECK(GetY(r3) == Approx{ 0.4F }.margin(0.01F));
        CHECK(GetZ(r3) == Approx{ 0.6F }.margin(0.01F));
        CHECK(GetW(r3) == Approx{ 0.9F }.margin(0.01F));

        CHECK(GetX(r4) == Approx{ -0.1F });
        CHECK(GetY(r4) == Approx{ 0.0F }.margin(0.01F));
        CHECK(GetZ(r4) == Approx{ -0.5F });
        CHECK(GetW(r4) == Approx{ -0.9F }.margin(0.01F));

        CHECK(Fraction(0.1F, 1.0F) == Approx{ 0.1F });
        CHECK(Fraction(0.4F, 1.0F) == Approx{ 0.4F });
        CHECK(Fraction(0.6F, 1.0F) == Approx{ 0.6F });
        CHECK(Fraction(0.9F, 1.0F) == Approx{ 0.9F });
        CHECK(Fraction(-0.1F, 1.0F) == Approx{ -0.1F });
        CHECK(Fraction(0.5F, 1.0F) == Approx{ 0.5F });
        CHECK(Fraction(-0.5F, 1.0F) == Approx{ -0.5F });
        CHECK(Fraction(-0.9F, 1.0F) == Approx{ -0.9F });
    }
}

#if false

mathinline Graphyte::Maths::Vec4 ToVec4(float x, Graphyte::Maths::Vec2 v, float w) noexcept
{
    Graphyte::Maths::Vec4 const v_xwxw = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x, w, x, w);
    return Graphyte::Maths::Permute<0, 4, 5, 1>(v_xwxw, { v.V });
}

mathinline Graphyte::Maths::Vec4 ToVec4(float x, float y, Graphyte::Maths::Vec2 v) noexcept
{
    Graphyte::Maths::Vec4 const v_xyxy = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x, y, x, y);
    return Graphyte::Maths::Permute<0, 1, 4, 5>(v_xyxy, { v.V });
}

mathinline Graphyte::Maths::Vec4 ToVec4(Graphyte::Maths::Vec2 v, float z, float w) noexcept
{
    Graphyte::Maths::Vec4 const v_zwzw = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(z, w, z, w);
    return Graphyte::Maths::Permute<4, 5, 0, 1>(v_zwzw, { v.V });
}

mathinline Graphyte::Maths::Vec4 ToVec4(float x, Graphyte::Maths::Vec3 v) noexcept
{
    Graphyte::Maths::Vec4 const v_xxxx = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x);
    return Graphyte::Maths::Permute<4, 0, 1, 2>({ v.V }, v_xxxx);
}

mathinline Graphyte::Maths::Vec4 ToVec4(Graphyte::Maths::Vec3 v, float w) noexcept
{
    Graphyte::Maths::Vec4 const v_wwww = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(w);
    return Graphyte::Maths::Permute<0, 1, 2, 4>({ v.V }, v_wwww);
}

mathinline Graphyte::Maths::Vec3 ToVec3(float x, Graphyte::Maths::Vec2 v) noexcept
{
    Graphyte::Maths::Vec4 const v_xxxx = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(x);
    return { Graphyte::Maths::Permute<4, 0, 1, 4>({ v.V }, v_xxxx).V };
}

mathinline Graphyte::Maths::Vec3 ToVec3(Graphyte::Maths::Vec2 v, float z) noexcept
{
    Graphyte::Maths::Vec4 const v_zzzz = Graphyte::Maths::Make<Graphyte::Maths::Vec4>(z);
    return { Graphyte::Maths::Permute<0, 1, 4, 4>({v.V}, v_zzzz).V };
}

TEST_CASE("Maths / Vector / Get and Set component value")
{
    using namespace Graphyte::Maths;

    Vec4 const v = Zero<Vec4>();

    REQUIRE(GetX(v) == Approx{ 0.0F });
    REQUIRE(GetY(v) == Approx{ 0.0F });
    REQUIRE(GetZ(v) == Approx{ 0.0F });
    REQUIRE(GetW(v) == Approx{ 0.0F });


    Vec4 const va = SetX(v, 1.0F);

    REQUIRE(GetX(va) == Approx{ 1.0F });
    REQUIRE(GetY(va) == Approx{ 0.0F });
    REQUIRE(GetZ(va) == Approx{ 0.0F });
    REQUIRE(GetW(va) == Approx{ 0.0F });

    Vec4 const vb = SetY(v, 1.0F);

    REQUIRE(GetX(vb) == Approx{ 0.0F });
    REQUIRE(GetY(vb) == Approx{ 1.0F });
    REQUIRE(GetZ(vb) == Approx{ 0.0F });
    REQUIRE(GetW(vb) == Approx{ 0.0F });

    Vec4 const vc = SetZ(v, 1.0F);

    REQUIRE(GetX(vc) == Approx{ 0.0F });
    REQUIRE(GetY(vc) == Approx{ 0.0F });
    REQUIRE(GetZ(vc) == Approx{ 1.0F });
    REQUIRE(GetW(vc) == Approx{ 0.0F });

    Vec4 const vd = SetW(v, 1.0F);

    REQUIRE(GetX(vd) == Approx{ 0.0F });
    REQUIRE(GetY(vd) == Approx{ 0.0F });
    REQUIRE(GetZ(vd) == Approx{ 0.0F });
    REQUIRE(GetW(vd) == Approx{ 1.0F });
}

TEST_CASE("Maths / Vector / Making Vec4 form other vectors")
{
    using namespace Graphyte::Maths;

    SECTION("From Vec3")
    {
        Vec3 const xyz = Make<Vec3>(1.0F, 2.0F, 3.0F);

        SECTION("xyz | w")
        {
            Vec4 const r = ToVec4(xyz, 4.0F);

            CHECK(GetX(r) == Approx{ 1.0F });
            CHECK(GetY(r) == Approx{ 2.0F });
            CHECK(GetZ(r) == Approx{ 3.0F });
            CHECK(GetW(r) == Approx{ 4.0F });
        }

        SECTION("w | xyz")
        {
            Vec4 const r = ToVec4(4.0F, xyz);

            CHECK(GetX(r) == Approx{ 4.0F });
            CHECK(GetY(r) == Approx{ 1.0F });
            CHECK(GetZ(r) == Approx{ 2.0F });
            CHECK(GetW(r) == Approx{ 3.0F });
        }
    }

    SECTION("From Vec2")
    {
        Vec2 const xy = Make<Vec2>(1.0F, 2.0F);

        SECTION("xy | z | w")
        {
            Vec4 const r = ToVec4(xy, 3.0F, 4.0F);

            CHECK(GetX(r) == Approx{ 1.0F });
            CHECK(GetY(r) == Approx{ 2.0F });
            CHECK(GetZ(r) == Approx{ 3.0F });
            CHECK(GetW(r) == Approx{ 4.0F });
        }

        SECTION("z | xy | w")
        {
            Vec4 const r = ToVec4(3.0F, xy, 4.0F);

            CHECK(GetX(r) == Approx{ 3.0F });
            CHECK(GetY(r) == Approx{ 1.0F });
            CHECK(GetZ(r) == Approx{ 2.0F });
            CHECK(GetW(r) == Approx{ 4.0F });
        }

        SECTION("z | w | xy")
        {
            Vec4 const r = ToVec4(3.0F, 4.0F, xy);

            CHECK(GetX(r) == Approx{ 3.0F });
            CHECK(GetY(r) == Approx{ 4.0F });
            CHECK(GetZ(r) == Approx{ 1.0F });
            CHECK(GetW(r) == Approx{ 2.0F });
        }
    }
}

TEST_CASE("Maths / Vector / Making Vec3 from other vectors")
{
    using namespace Graphyte::Maths;

    SECTION("From Vec2")
    {
        Vec2 const xy = Make<Vec2>(1.0F, 2.0F);

        SECTION("z | xy")
        {
            Vec3 const r = ToVec3(5.0F, xy);

            CHECK(GetX(r) == Approx{ 5.0F });
            CHECK(GetY(r) == Approx{ 1.0F });
            CHECK(GetZ(r) == Approx{ 2.0F });
        }

        SECTION("xy | z")
        {
            Vec3 const r = ToVec3(xy, 5.0F);

            CHECK(GetX(r) == Approx{ 1.0F });
            CHECK(GetY(r) == Approx{ 2.0F });
            CHECK(GetZ(r) == Approx{ 5.0F });
        }
    }
}

TEST_CASE("Maths / Vector / Select by bool value")
{
}

#if false
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

//TEST_CASE("operators")
//{
//    namespace M = Graphyte::Maths;
//
//    M::Vec4 const v1 = M::Make<M::Vec4>(1.0F);
//    M::Vec4 const v2 = M::Make<M::Vec4>(2.0F);
//    M::Vec4 const v3 = M::Make<M::Vec4>(3.0F);
//
//    REQUIRE(v1 != v2);
//    REQUIRE_FALSE(v1 == v2);
//
//    REQUIRE(M::IsEqEps(v1 + v2, v3, M::Epsilon<M::Vec4>()));
//}

template <typename T>
int check() requires(Graphyte::Maths::EqualComparable<T>)
{
    return 1;
}

template <typename T>
int check() requires(!Graphyte::Maths::EqualComparable<T>)
{
    return 0;
}

TEST_CASE("xxx")
{
    CHECK(check<int>() == 0);
    CHECK(check<Graphyte::Maths::Vec4>() == 1);
}
#endif

#endif
