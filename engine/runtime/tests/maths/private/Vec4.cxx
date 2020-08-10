#include <catch2/catch.hpp>
#include <GxBase/Maths/Vector.hxx>

TEST_CASE("Graphyte::Maths::To")
{
    using namespace Graphyte::Maths;

    Vector1 const v1  = Make<Vector1>(1.0f);
    Vector2 const v2a = Make<Vector2>(1.0f, 2.0f);
    Vector2 const v2b = Make<Vector2>(3.0f, 4.0f);
    Vector3 const v3  = Make<Vector3>(1.0f, 2.0f, 3.0f);

    SECTION("f32 | vec3 = vec4")
    {
        Vector4 const r = To(-1.0f, v3);
        REQUIRE(GetX(r) == -1.0f);
        REQUIRE(GetY(r) == 1.0f);
        REQUIRE(GetZ(r) == 2.0f);
        REQUIRE(GetW(r) == 3.0f);
    }

    SECTION("vec3 | f32 = vec4")
    {
        Vector4 const r = To(v3, -1.0f);
        REQUIRE(GetX(r) == 1.0f);
        REQUIRE(GetY(r) == 2.0f);
        REQUIRE(GetZ(r) == 3.0f);
        REQUIRE(GetW(r) == -1.0f);
    }

    SECTION("f32 | f32 | vec2 = vec4")
    {
        Vector4 const r = To(-1.0f, -2.0f, v2a);
        REQUIRE(GetX(r) == -1.0f);
        REQUIRE(GetY(r) == -2.0f);
        REQUIRE(GetZ(r) == 1.0f);
        REQUIRE(GetW(r) == 2.0f);
    }

    SECTION("f32 | vec2 | f32 = vec4")
    {
        Vector4 const r = To(-1.0f, v2a, -2.0f);
        REQUIRE(GetX(r) == -1.0f);
        REQUIRE(GetY(r) == 1.0f);
        REQUIRE(GetZ(r) == 2.0f);
        REQUIRE(GetW(r) == -2.0f);
    }

    SECTION("vec2 | vec2 = vec4")
    {
        Vector4 const r = To(v2a, v2b);
        REQUIRE(GetX(r) == 1.0f);
        REQUIRE(GetY(r) == 2.0f);
        REQUIRE(GetZ(r) == 3.0f);
        REQUIRE(GetW(r) == 4.0f);
    }

    SECTION("f32 | vec2 = vec3")
    {
        Vector3 const r = To(-1.0f, v2a);
        REQUIRE(GetX(r) == -1.0f);
        REQUIRE(GetY(r) == 1.0f);
        REQUIRE(GetZ(r) == 2.0f);
        //REQUIRE(GetW(r) == 0.0f);
    }

    SECTION("vec2 | f32 = vec3")
    {
        Vector3 const r = To(v2a, -1.0f);
        REQUIRE(GetX(r) == 1.0f);
        REQUIRE(GetY(r) == 2.0f);
        REQUIRE(GetZ(r) == -1.0f);
        //REQUIRE(GetW(r) == 0.0f);
    }
}

TEST_CASE("Graphyte::Maths / all components / comparisons")
{
    using namespace Graphyte::Maths;

    static constexpr float values[4][2]{
        {
            -1.0f,
            -1.0f,
        },
        {
            -1.0f,
            1.0f,
        },
        {
            1.0f,
            -1.0f,
        },
        {
            1.0f,
            1.0f,
        },
    };

    for (auto [lx, rx] : values)
    {
        INFO("lx: " << lx << ", rx: " << rx);

        Vector1 const v1l = Make<Vector1>(lx);
        Vector1 const v1r = Make<Vector1>(rx);

        for (auto [ly, ry] : values)
        {
            INFO("ly: " << ly << ", ry: " << ry);

            Vector2 const v2l = Make<Vector2>(lx, ly);
            Vector2 const v2r = Make<Vector2>(rx, ry);

            for (auto [lz, rz] : values)
            {
                INFO("lz: " << lz << ", rz: " << rz);

                Vector3 const v3l = Make<Vector3>(lx, ly, lz);
                Vector3 const v3r = Make<Vector3>(rx, ry, rz);

                for (auto [lw, rw] : values)
                {
                    INFO("lw: " << lw << ", rw: " << rw);

                    Vector4 const v4l = Make<Vector4>(lx, ly, lz, lw);
                    Vector4 const v4r = Make<Vector4>(rx, ry, rz, rw);

                    CHECK(IsEqual(v4l, v4r) == (lx == rx && ly == ry && lz == rz && lw == rw));
                    CHECK(IsNotEqual(v4l, v4r) == (lx != rx || ly != ry || lz != rz || lw != rw));
                    CHECK(IsGreater(v4l, v4r) == (lx > rx && ly > ry && lz > rz && lw > rw));
                    CHECK(IsGreaterEqual(v4l, v4r) == (lx >= rx && ly >= ry && lz >= rz && lw >= rw));
                    CHECK(IsLess(v4l, v4r) == (lx < rx && ly < ry && lz < rz && lw < rw));
                    CHECK(IsLessEqual(v4l, v4r) == (lx <= rx && ly <= ry && lz <= rz && lw <= rw));
                }

                CHECK(IsEqual(v3l, v3r) == (lx == rx && ly == ry && lz == rz));
                CHECK(IsNotEqual(v3l, v3r) == (lx != rx || ly != ry || lz != rz));
                CHECK(IsGreater(v3l, v3r) == (lx > rx && ly > ry && lz > rz));
                CHECK(IsGreaterEqual(v3l, v3r) == (lx >= rx && ly >= ry && lz >= rz));
                CHECK(IsLess(v3l, v3r) == (lx < rx && ly < ry && lz < rz));
                CHECK(IsLessEqual(v3l, v3r) == (lx <= rx && ly <= ry && lz <= rz));
            }

            CHECK(IsEqual(v2l, v2r) == (lx == rx && ly == ry));
            CHECK(IsNotEqual(v2l, v2r) == (lx != rx || ly != ry));
            CHECK(IsGreater(v2l, v2r) == (lx > rx && ly > ry));
            CHECK(IsGreaterEqual(v2l, v2r) == (lx >= rx && ly >= ry));
            CHECK(IsLess(v2l, v2r) == (lx < rx && ly < ry));
            CHECK(IsLessEqual(v2l, v2r) == (lx <= rx && ly <= ry));
        }

        CHECK(IsEqual(v1l, v1r) == (lx == rx));
        CHECK(IsNotEqual(v1l, v1r) == (lx != rx));
        CHECK(IsGreater(v1l, v1r) == (lx > rx));
        CHECK(IsGreaterEqual(v1l, v1r) == (lx >= rx));
        CHECK(IsLess(v1l, v1r) == (lx < rx));
        CHECK(IsLessEqual(v1l, v1r) == (lx <= rx));
    }
}

TEST_CASE("Graphyte::Maths / near equal")
{
    using namespace Graphyte::Maths;

    Vector1 const c1 = Make<Vector1>(1.0f);
    Vector2 const c2 = Make<Vector2>(1.0f, 2.0f);
    Vector3 const c3 = Make<Vector3>(1.0f, 2.0f, 3.0f);
    Vector4 const c4 = Make<Vector4>(1.0f, 2.0f, 3.0f, 4.0f);

    Vector1 const a1 = Make<Vector1>(1.1f);
    Vector2 const a2 = Make<Vector2>(1.1f, 2.1f);
    Vector3 const a3 = Make<Vector3>(1.1f, 2.1f, 3.1f);
    Vector4 const a4 = Make<Vector4>(1.1f, 2.1f, 3.1f, 4.1f);

    Vector1 const ea1 = Replicate<Vector1>(0.2f);
    Vector2 const ea2 = Replicate<Vector2>(0.2f);
    Vector3 const ea3 = Replicate<Vector3>(0.2f);
    Vector4 const ea4 = Replicate<Vector4>(0.2f);

    Vector1 const eb1 = Replicate<Vector1>(0.02f);
    Vector2 const eb2 = Replicate<Vector2>(0.02f);
    Vector3 const eb3 = Replicate<Vector3>(0.02f);
    Vector4 const eb4 = Replicate<Vector4>(0.02f);

    CHECK(IsEqual(c1, c1, ea1));
    CHECK(IsEqual(c2, c2, ea2));
    CHECK(IsEqual(c3, c3, ea3));
    CHECK(IsEqual(c4, c4, ea4));

    CHECK(IsEqual(c1, a1, ea1));
    CHECK(IsEqual(c2, a2, ea2));
    CHECK(IsEqual(c3, a3, ea3));
    CHECK(IsEqual(c4, a4, ea4));

    CHECK(IsEqual(c1, c1, eb1));
    CHECK(IsEqual(c2, c2, eb2));
    CHECK(IsEqual(c3, c3, eb3));
    CHECK(IsEqual(c4, c4, eb4));

    CHECK(!IsEqual(c1, a1, eb1));
    CHECK(!IsEqual(c2, a2, eb2));
    CHECK(!IsEqual(c3, a3, eb3));
    CHECK(!IsEqual(c4, a4, eb4));
}

TEST_CASE("Graphyte::Maths / in bounds")
{
    using namespace Graphyte::Maths;

    Vector1 const c1 = Make<Vector1>(0.2f);
    Vector2 const c2 = Make<Vector2>(0.2f, 1.0f);
    Vector3 const c3 = Make<Vector3>(0.2f, 1.0f, -0.5f);
    Vector4 const c4 = Make<Vector4>(0.2f, 1.0f, -0.5f, -0.2f);

    Vector1 const b1a = Replicate<Vector1>(0.5f);
    Vector2 const b2a = Replicate<Vector2>(0.5f);
    Vector3 const b3a = Replicate<Vector3>(0.5f);
    Vector4 const b4a = Replicate<Vector4>(0.5f);

    Vector1 const b1b = Replicate<Vector1>(1.5f);
    Vector2 const b2b = Replicate<Vector2>(1.5f);
    Vector3 const b3b = Replicate<Vector3>(1.5f);
    Vector4 const b4b = Replicate<Vector4>(1.5f);

    CHECK(InBounds(c1, b1a));
    CHECK_FALSE(InBounds(c2, b2a));
    CHECK_FALSE(InBounds(c3, b3a));
    CHECK_FALSE(InBounds(c4, b4a));

    CHECK(InBounds(c1, b1b));
    CHECK(InBounds(c2, b2b));
    CHECK(InBounds(c3, b3b));
    CHECK(InBounds(c4, b4b));
}

TEST_CASE("Graphyte::Maths / dot product")
{
    using namespace Graphyte::Maths;

    Vector1 const c1 = Make<Vector1>(1.0f);
    Vector2 const c2 = Make<Vector2>(1.0f, 2.0f);
    Vector3 const c3 = Make<Vector3>(1.0f, 2.0f, 3.0f);
    Vector4 const c4 = Make<Vector4>(1.0f, 2.0f, 3.0f, 4.0f);

    Vector1 const d1 = Dot(c1, c1);
    CHECK(GetX(d1) == 1.0f);

    
    Vector2 const d2 = Dot(c2, c2);
    CHECK(GetX(d2) == 5.0f);


    Vector3 const d3 = Dot(c3, c3);
    CHECK(GetX(d3) == 14.0f);


    Vector4 const d4 = Dot(c4, c4);
    CHECK(GetX(d4) == 30.0f);
}

TEST_CASE("Graphyte::Maths / lengths")
{
    using namespace Graphyte::Maths;

    Vector1 const c1 = Make<Vector1>(2.0f);
    Vector2 const c2 = Make<Vector2>(0.0f, 2.0f);
    Vector3 const c3 = Make<Vector3>(0.0f, 0.0f, 2.0f);
    Vector4 const c4 = Make<Vector4>(0.0f, 0.0f, 0.0f, 2.0f);

    Vector1 const l1 = Length(c1);
    CHECK(GetX(l1) == 2.0f);

    Vector2 const l2 = Length(c2);
    CHECK(GetX(l2) == 2.0f);

    Vector3 const l3 = Length(c3);
    CHECK(GetX(l3) == 2.0f);

    Vector4 const l4 = Length(c4);
    CHECK(GetX(l4) == 2.0f);

    
    Vector1 const s1 = LengthSquared(c1);
    CHECK(GetX(s1) == 4.0f);

    Vector2 const s2 = LengthSquared(c2);
    CHECK(GetX(s2) == 4.0f);

    Vector3 const s3 = LengthSquared(c3);
    CHECK(GetX(s3) == 4.0f);

    Vector4 const s4 = LengthSquared(c4);
    CHECK(GetX(s4) == 4.0f);


    Vector1 const el1 = LengthEst(c1);
    CHECK(GetX(el1) == Approx{ 2.0f });

    Vector2 const el2 = LengthEst(c2);
    CHECK(GetX(el2) == Approx{ 2.0f });

    Vector3 const el3 = LengthEst(c3);
    CHECK(GetX(el3) == Approx{ 2.0f });

    Vector4 const el4 = LengthEst(c4);
    CHECK(GetX(el4) == Approx{ 2.0f });


    Vector1 const rl1 = ReciprocalLength(c1);
    CHECK(GetX(rl1) == Approx{ 0.5f });

    Vector2 const rl2 = ReciprocalLength(c2);
    CHECK(GetX(rl2) == Approx{ 0.5f });

    Vector3 const rl3 = ReciprocalLength(c3);
    CHECK(GetX(rl3) == Approx{ 0.5f });

    Vector4 const rl4 = ReciprocalLength(c4);
    CHECK(GetX(rl4) == Approx{ 0.5f });


    Vector1 const rle1 = ReciprocalLengthEst(c1);
    CHECK(GetX(rle1) == Approx{ 0.5f }.margin(0.01f));

    Vector2 const rle2 = ReciprocalLengthEst(c2);
    CHECK(GetX(rle2) == Approx{ 0.5f }.margin(0.01f));

    Vector3 const rle3 = ReciprocalLengthEst(c3);
    CHECK(GetX(rle3) == Approx{ 0.5f }.margin(0.01f));

    Vector4 const rle4 = ReciprocalLengthEst(c4);
    CHECK(GetX(rle4) == Approx{ 0.5f }.margin(0.01f));
}

TEST_CASE("Graphyte::Maths / normalize")
{
    using namespace Graphyte::Maths;

    Vector1 const c1 = Make<Vector1>(2.0f);
    Vector2 const c2 = Make<Vector2>(0.5f, 2.0f);
    Vector3 const c3 = Make<Vector3>(0.5f, 0.5f, 2.0f);
    Vector4 const c4 = Make<Vector4>(0.5f, 0.5f, 0.5f, 2.0f);

    CHECK_FALSE(IsUnit(c1));
    CHECK_FALSE(IsUnit(c2));
    CHECK_FALSE(IsUnit(c3));
    CHECK_FALSE(IsUnit(c4));

    Vector1 const n1 = Normalize(c1);
    Vector2 const n2 = Normalize(c2);
    Vector3 const n3 = Normalize(c3);
    Vector4 const n4 = Normalize(c4);

    CHECK(IsUnit(n1));
    CHECK(IsUnit(n2));
    CHECK(IsUnit(n3));
    CHECK(IsUnit(n4));

    Vector1 const ne1 = NormalizeEst(c1);
    Vector2 const ne2 = NormalizeEst(c2);
    Vector3 const ne3 = NormalizeEst(c3);
    Vector4 const ne4 = NormalizeEst(c4);

    CHECK(GetX(Length(ne1)) == Approx{ 1.0f }.margin(0.01f));
    CHECK(GetX(Length(ne2)) == Approx{ 1.0f }.margin(0.01f));
    CHECK(GetX(Length(ne3)) == Approx{ 1.0f }.margin(0.01f));
    CHECK(GetX(Length(ne4)) == Approx{ 1.0f }.margin(0.01f));
}

TEST_CASE("Graphyte::Maths / arithmetic")
{
    using namespace Graphyte::Maths;

    Vector1 const a1 = Make<Vector1>(1.0f);
    Vector2 const a2 = Make<Vector2>(1.0f, -1.0f);
    Vector3 const a3 = Make<Vector3>(1.0f, -1.0f, 0.1f);
    Vector4 const a4 = Make<Vector4>(1.0f, -1.0f, 0.1f, -0.23f);

    Vector1 const b1 = Make<Vector1>(0.5f);
    Vector2 const b2 = Make<Vector2>(0.5f, 0.1f);
    Vector3 const b3 = Make<Vector3>(0.5f, 0.1f, -0.13f);
    Vector4 const b4 = Make<Vector4>(0.5f, 0.1f, -0.13f, 0.8f);

    Vector1 const c1 = Make<Vector1>(-0.4f);
    Vector2 const c2 = Make<Vector2>(0.3f, 0.1f);
    Vector3 const c3 = Make<Vector3>(0.2f, -0.3f, 0.15f);
    Vector4 const c4 = Make<Vector4>(-0.15f, 0.2f, -0.23f, -0.67f);

    Vector1 const d1 = Make<Vector1>(1.4f);
    Vector2 const d2 = Make<Vector2>(1.3f, 1.1f);
    Vector3 const d3 = Make<Vector3>(1.2f, 1.3f, 1.15f);
    Vector4 const d4 = Make<Vector4>(1.15f, 1.2f, 1.23f, 1.67f);

    SECTION("cos")
    {
        CHECK(GetX(Cos(a1)) == Approx{ cos(GetX(a1)) });

        CHECK(GetX(Cos(a2)) == Approx{ cos(GetX(a2)) });
        CHECK(GetY(Cos(a2)) == Approx{ cos(GetY(a2)) });

        CHECK(GetX(Cos(a3)) == Approx{ cos(GetX(a3)) });
        CHECK(GetY(Cos(a3)) == Approx{ cos(GetY(a3)) });
        CHECK(GetZ(Cos(a3)) == Approx{ cos(GetZ(a3)) });

        CHECK(GetX(Cos(a4)) == Approx{ cos(GetX(a4)) });
        CHECK(GetY(Cos(a4)) == Approx{ cos(GetY(a4)) });
        CHECK(GetZ(Cos(a4)) == Approx{ cos(GetZ(a4)) });
        CHECK(GetW(Cos(a4)) == Approx{ cos(GetW(a4)) });
    }

    SECTION("sin")
    {
        CHECK(GetX(Sin(a1)) == Approx{ sin(GetX(a1)) });

        CHECK(GetX(Sin(a2)) == Approx{ sin(GetX(a2)) });
        CHECK(GetY(Sin(a2)) == Approx{ sin(GetY(a2)) });

        CHECK(GetX(Sin(a3)) == Approx{ sin(GetX(a3)) });
        CHECK(GetY(Sin(a3)) == Approx{ sin(GetY(a3)) });
        CHECK(GetZ(Sin(a3)) == Approx{ sin(GetZ(a3)) });

        CHECK(GetX(Sin(a4)) == Approx{ sin(GetX(a4)) });
        CHECK(GetY(Sin(a4)) == Approx{ sin(GetY(a4)) });
        CHECK(GetZ(Sin(a4)) == Approx{ sin(GetZ(a4)) });
        CHECK(GetW(Sin(a4)) == Approx{ sin(GetW(a4)) });
    }

    SECTION("sincos")
    {
        Vector1 rs1{}, rc1{};
        Vector2 rs2{}, rc2{};
        Vector3 rs3{}, rc3{};
        Vector4 rs4{}, rc4{};

        SinCos(rs1, rc1, a1);
        SinCos(rs2, rc2, a2);
        SinCos(rs3, rc3, a3);
        SinCos(rs4, rc4, a4);

        CHECK(GetX(rs1) == Approx{ sin(GetX(a1)) });

        CHECK(GetX(rs2) == Approx{ sin(GetX(a2)) });
        CHECK(GetY(rs2) == Approx{ sin(GetY(a2)) });

        CHECK(GetX(rs3) == Approx{ sin(GetX(a3)) });
        CHECK(GetY(rs3) == Approx{ sin(GetY(a3)) });
        CHECK(GetZ(rs3) == Approx{ sin(GetZ(a3)) });

        CHECK(GetX(rs4) == Approx{ sin(GetX(a4)) });
        CHECK(GetY(rs4) == Approx{ sin(GetY(a4)) });
        CHECK(GetZ(rs4) == Approx{ sin(GetZ(a4)) });
        CHECK(GetW(rs4) == Approx{ sin(GetW(a4)) });

        CHECK(GetX(rc1) == Approx{ cos(GetX(a1)) });

        CHECK(GetX(rc2) == Approx{ cos(GetX(a2)) });
        CHECK(GetY(rc2) == Approx{ cos(GetY(a2)) });

        CHECK(GetX(rc3) == Approx{ cos(GetX(a3)) });
        CHECK(GetY(rc3) == Approx{ cos(GetY(a3)) });
        CHECK(GetZ(rc3) == Approx{ cos(GetZ(a3)) });

        CHECK(GetX(rc4) == Approx{ cos(GetX(a4)) });
        CHECK(GetY(rc4) == Approx{ cos(GetY(a4)) });
        CHECK(GetZ(rc4) == Approx{ cos(GetZ(a4)) });
        CHECK(GetW(rc4) == Approx{ cos(GetW(a4)) });
    }

    SECTION("tan")
    {
        CHECK(GetX(Tan(a1)) == Approx{ tan(GetX(a1)) });

        CHECK(GetX(Tan(a2)) == Approx{ tan(GetX(a2)) });
        CHECK(GetY(Tan(a2)) == Approx{ tan(GetY(a2)) });

        CHECK(GetX(Tan(a3)) == Approx{ tan(GetX(a3)) });
        CHECK(GetY(Tan(a3)) == Approx{ tan(GetY(a3)) });
        CHECK(GetZ(Tan(a3)) == Approx{ tan(GetZ(a3)) });

        CHECK(GetX(Tan(a4)) == Approx{ tan(GetX(a4)) });
        CHECK(GetY(Tan(a4)) == Approx{ tan(GetY(a4)) });
        CHECK(GetZ(Tan(a4)) == Approx{ tan(GetZ(a4)) });
        CHECK(GetW(Tan(a4)) == Approx{ tan(GetW(a4)) });
    }

    SECTION("asin")
    {
        CHECK(GetX(Asin(b1)) == Approx{ asin(GetX(b1)) });

        CHECK(GetX(Asin(b2)) == Approx{ asin(GetX(b2)) });
        CHECK(GetY(Asin(b2)) == Approx{ asin(GetY(b2)) });

        CHECK(GetX(Asin(b3)) == Approx{ asin(GetX(b3)) });
        CHECK(GetY(Asin(b3)) == Approx{ asin(GetY(b3)) });
        CHECK(GetZ(Asin(b3)) == Approx{ asin(GetZ(b3)) });

        CHECK(GetX(Asin(b4)) == Approx{ asin(GetX(b4)) });
        CHECK(GetY(Asin(b4)) == Approx{ asin(GetY(b4)) });
        CHECK(GetZ(Asin(b4)) == Approx{ asin(GetZ(b4)) });
        CHECK(GetW(Asin(b4)) == Approx{ asin(GetW(b4)) });
    }

    SECTION("acos")
    {
        CHECK(GetX(Acos(b1)) == Approx{ acos(GetX(b1)) });

        CHECK(GetX(Acos(b2)) == Approx{ acos(GetX(b2)) });
        CHECK(GetY(Acos(b2)) == Approx{ acos(GetY(b2)) });

        CHECK(GetX(Acos(b3)) == Approx{ acos(GetX(b3)) });
        CHECK(GetY(Acos(b3)) == Approx{ acos(GetY(b3)) });
        CHECK(GetZ(Acos(b3)) == Approx{ acos(GetZ(b3)) });

        CHECK(GetX(Acos(b4)) == Approx{ acos(GetX(b4)) });
        CHECK(GetY(Acos(b4)) == Approx{ acos(GetY(b4)) });
        CHECK(GetZ(Acos(b4)) == Approx{ acos(GetZ(b4)) });
        CHECK(GetW(Acos(b4)) == Approx{ acos(GetW(b4)) });
    }

    SECTION("atan")
    {
        CHECK(GetX(Atan(b1)) == Approx{ atan(GetX(b1)) });

        CHECK(GetX(Atan(b2)) == Approx{ atan(GetX(b2)) });
        CHECK(GetY(Atan(b2)) == Approx{ atan(GetY(b2)) });

        CHECK(GetX(Atan(b3)) == Approx{ atan(GetX(b3)) });
        CHECK(GetY(Atan(b3)) == Approx{ atan(GetY(b3)) });
        CHECK(GetZ(Atan(b3)) == Approx{ atan(GetZ(b3)) });

        CHECK(GetX(Atan(b4)) == Approx{ atan(GetX(b4)) });
        CHECK(GetY(Atan(b4)) == Approx{ atan(GetY(b4)) });
        CHECK(GetZ(Atan(b4)) == Approx{ atan(GetZ(b4)) });
        CHECK(GetW(Atan(b4)) == Approx{ atan(GetW(b4)) });
    }

    SECTION("atan2")
    {
        CHECK(GetX(Atan2(b4, c4)) == Approx{ atan2(GetX(b4), GetX(c4)) });
        CHECK(GetY(Atan2(b4, c4)) == Approx{ atan2(GetY(b4), GetY(c4)) });
        CHECK(GetZ(Atan2(b4, c4)) == Approx{ atan2(GetZ(b4), GetZ(c4)) });
        CHECK(GetW(Atan2(b4, c4)) == Approx{ atan2(GetW(b4), GetW(c4)) });
    }

    SECTION("sinh")
    {
        CHECK(GetX(Sinh(b1)) == Approx{ sinh(GetX(b1)) });

        CHECK(GetX(Sinh(b2)) == Approx{ sinh(GetX(b2)) });
        CHECK(GetY(Sinh(b2)) == Approx{ sinh(GetY(b2)) });

        CHECK(GetX(Sinh(b3)) == Approx{ sinh(GetX(b3)) });
        CHECK(GetY(Sinh(b3)) == Approx{ sinh(GetY(b3)) });
        CHECK(GetZ(Sinh(b3)) == Approx{ sinh(GetZ(b3)) });

        CHECK(GetX(Sinh(b4)) == Approx{ sinh(GetX(b4)) });
        CHECK(GetY(Sinh(b4)) == Approx{ sinh(GetY(b4)) });
        CHECK(GetZ(Sinh(b4)) == Approx{ sinh(GetZ(b4)) });
        CHECK(GetW(Sinh(b4)) == Approx{ sinh(GetW(b4)) });
    }

    SECTION("cosh")
    {
        CHECK(GetX(Cosh(b1)) == Approx{ cosh(GetX(b1)) });

        CHECK(GetX(Cosh(b2)) == Approx{ cosh(GetX(b2)) });
        CHECK(GetY(Cosh(b2)) == Approx{ cosh(GetY(b2)) });

        CHECK(GetX(Cosh(b3)) == Approx{ cosh(GetX(b3)) });
        CHECK(GetY(Cosh(b3)) == Approx{ cosh(GetY(b3)) });
        CHECK(GetZ(Cosh(b3)) == Approx{ cosh(GetZ(b3)) });

        CHECK(GetX(Cosh(b4)) == Approx{ cosh(GetX(b4)) });
        CHECK(GetY(Cosh(b4)) == Approx{ cosh(GetY(b4)) });
        CHECK(GetZ(Cosh(b4)) == Approx{ cosh(GetZ(b4)) });
        CHECK(GetW(Cosh(b4)) == Approx{ cosh(GetW(b4)) });
    }

    SECTION("tanh")
    {
        CHECK(GetX(Tanh(b1)) == Approx{ tanh(GetX(b1)) });

        CHECK(GetX(Tanh(b2)) == Approx{ tanh(GetX(b2)) });
        CHECK(GetY(Tanh(b2)) == Approx{ tanh(GetY(b2)) });

        CHECK(GetX(Tanh(b3)) == Approx{ tanh(GetX(b3)) });
        CHECK(GetY(Tanh(b3)) == Approx{ tanh(GetY(b3)) });
        CHECK(GetZ(Tanh(b3)) == Approx{ tanh(GetZ(b3)) });

        CHECK(GetX(Tanh(b4)) == Approx{ tanh(GetX(b4)) });
        CHECK(GetY(Tanh(b4)) == Approx{ tanh(GetY(b4)) });
        CHECK(GetZ(Tanh(b4)) == Approx{ tanh(GetZ(b4)) });
        CHECK(GetW(Tanh(b4)) == Approx{ tanh(GetW(b4)) });
    }

    SECTION("asinh")
    {
        CHECK(GetX(Asinh(b1)) == Approx{ asinh(GetX(b1)) });

        CHECK(GetX(Asinh(b2)) == Approx{ asinh(GetX(b2)) });
        CHECK(GetY(Asinh(b2)) == Approx{ asinh(GetY(b2)) });

        CHECK(GetX(Asinh(b3)) == Approx{ asinh(GetX(b3)) });
        CHECK(GetY(Asinh(b3)) == Approx{ asinh(GetY(b3)) });
        CHECK(GetZ(Asinh(b3)) == Approx{ asinh(GetZ(b3)) });

        CHECK(GetX(Asinh(b4)) == Approx{ asinh(GetX(b4)) });
        CHECK(GetY(Asinh(b4)) == Approx{ asinh(GetY(b4)) });
        CHECK(GetZ(Asinh(b4)) == Approx{ asinh(GetZ(b4)) });
        CHECK(GetW(Asinh(b4)) == Approx{ asinh(GetW(b4)) });
    }

    SECTION("acosh")
    {
        CHECK(GetX(Acosh(d1)) == Approx{ acosh(GetX(d1)) });

        CHECK(GetX(Acosh(d2)) == Approx{ acosh(GetX(d2)) });
        CHECK(GetY(Acosh(d2)) == Approx{ acosh(GetY(d2)) });

        CHECK(GetX(Acosh(d3)) == Approx{ acosh(GetX(d3)) });
        CHECK(GetY(Acosh(d3)) == Approx{ acosh(GetY(d3)) });
        CHECK(GetZ(Acosh(d3)) == Approx{ acosh(GetZ(d3)) });

        CHECK(GetX(Acosh(d4)) == Approx{ acosh(GetX(d4)) });
        CHECK(GetY(Acosh(d4)) == Approx{ acosh(GetY(d4)) });
        CHECK(GetZ(Acosh(d4)) == Approx{ acosh(GetZ(d4)) });
        CHECK(GetW(Acosh(d4)) == Approx{ acosh(GetW(d4)) });
    }

    SECTION("atanh")
    {
        CHECK(GetX(Atanh(b1)) == Approx{ atanh(GetX(b1)) });

        CHECK(GetX(Atanh(b2)) == Approx{ atanh(GetX(b2)) });
        CHECK(GetY(Atanh(b2)) == Approx{ atanh(GetY(b2)) });

        CHECK(GetX(Atanh(b3)) == Approx{ atanh(GetX(b3)) });
        CHECK(GetY(Atanh(b3)) == Approx{ atanh(GetY(b3)) });
        CHECK(GetZ(Atanh(b3)) == Approx{ atanh(GetZ(b3)) });

        CHECK(GetX(Atanh(b4)) == Approx{ atanh(GetX(b4)) });
        CHECK(GetY(Atanh(b4)) == Approx{ atanh(GetY(b4)) });
        CHECK(GetZ(Atanh(b4)) == Approx{ atanh(GetZ(b4)) });
        CHECK(GetW(Atanh(b4)) == Approx{ atanh(GetW(b4)) });
    }
}


#if false
#include <GxBase/Maths.hxx>


TEST_CASE("Maths / Quaternion / q mul conj(q) = identity")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector3 const axis = Make<Vector3>(1.0f, 2.0f, -3.0f);

    Quaternion const q  = CreateFromAxisAngle<Quaternion>(axis, DegreesToRadians(30.0f));
    Quaternion const qc = Conjugate(q);

    Quaternion const r = Multiply(q, qc);

    CHECK(IsIdentity(r, Epsilon<Vector4>()));
}

TEST_CASE("Maths / Vector / Clamp")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector2 va2 = Make<Vector2>(1.0f, -2.0f);
    Vector2 ra2 = Clamp(va2, Replicate<Vector2>(-0.1f), Replicate<Vector2>(0.875f));
    CHECK(GetX(ra2) == Approx{ 0.875f });
    CHECK(GetY(ra2) == Approx{ -0.1f });
}

TEST_CASE("Maths / Vectors / Dot Product")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        Vector2 const a = Make<Vector2>(1.0f, -1.0f);
        Vector2 const b = Make<Vector2>(2.0f, 1.5f);

        Vector4 const r = Dot(a, b);

        CHECK(GetX(r) == Approx{ 0.5f });
        CHECK(GetY(r) == Approx{ 0.5f });
        CHECK(GetZ(r) == Approx{ 0.5f });
        CHECK(GetW(r) == Approx{ 0.5f });
    }

    SECTION("Vector3")
    {
        Vector3 const a = Make<Vector3>(1.0f, -1.0f, 3.0f);
        Vector3 const b = Make<Vector3>(2.0f, 1.5f, 1.25f);

        Vector4 const r = Dot(a, b);

        CHECK(GetX(r) == Approx{ 4.25f });
        CHECK(GetY(r) == Approx{ 4.25f });
        CHECK(GetZ(r) == Approx{ 4.25f });
        CHECK(GetW(r) == Approx{ 4.25f });
    }

    SECTION("Vector4")
    {
        Vector4 const a = Make<Vector4>(1.0f, -1.0f, 3.0f, -1.5f);
        Vector4 const b = Make<Vector4>(2.0f, 1.5f, 1.25f, 2.25f);

        Vector4 const r = Dot(a, b);

        CHECK(GetX(r) == Approx{ 0.875f });
        CHECK(GetY(r) == Approx{ 0.875f });
        CHECK(GetZ(r) == Approx{ 0.875f });
        CHECK(GetW(r) == Approx{ 0.875f });
    }
}

TEST_CASE("Maths / Vectors / Angles")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Angle between vectors")
    {
        SECTION("Vector2")
        {
            Vector2 const x = UnitX<Vector2>();
            Vector2 const y = UnitY<Vector2>();

            CHECK(GetX(AngleBetweenVectors(x, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(y, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(x, x)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenVectors(y, y)) == Approx{ DegreesToRadians(0.0f) });
        }

        SECTION("Vector3")
        {
            Vector3 const x = UnitX<Vector3>();
            Vector3 const y = UnitY<Vector3>();
            Vector3 const z = UnitZ<Vector3>();

            CHECK(GetX(AngleBetweenVectors(x, x)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenVectors(x, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(x, z)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenVectors(y, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(y, y)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenVectors(y, z)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenVectors(z, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(z, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(z, z)) == Approx{ DegreesToRadians(0.0f) });
        }

        SECTION("Vector4")
        {
            Vector4 const x = UnitX<Vector4>();
            Vector4 const y = UnitY<Vector4>();
            Vector4 const z = UnitZ<Vector4>();
            Vector4 const w = UnitW<Vector4>();

            CHECK(GetX(AngleBetweenVectors(x, x)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenVectors(x, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(x, z)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(x, w)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenVectors(y, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(y, y)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenVectors(y, z)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(y, w)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenVectors(z, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(z, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(z, z)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenVectors(z, w)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenVectors(w, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(w, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(w, z)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenVectors(w, w)) == Approx{ DegreesToRadians(0.0f) });
        }
    }

    SECTION("Angle between normals")
    {
        SECTION("Vector2")
        {
            Vector2 const x = UnitX<Vector2>();
            Vector2 const y = UnitY<Vector2>();

            CHECK(GetX(AngleBetweenNormals(x, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(y, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(x, x)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenNormals(y, y)) == Approx{ DegreesToRadians(0.0f) });
        }

        SECTION("Vector3")
        {
            Vector3 const x = UnitX<Vector3>();
            Vector3 const y = UnitY<Vector3>();
            Vector3 const z = UnitZ<Vector3>();

            CHECK(GetX(AngleBetweenNormals(x, x)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenNormals(x, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(x, z)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenNormals(y, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(y, y)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenNormals(y, z)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenNormals(z, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(z, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(z, z)) == Approx{ DegreesToRadians(0.0f) });
        }

        SECTION("Vector4")
        {
            Vector4 const x = UnitX<Vector4>();
            Vector4 const y = UnitY<Vector4>();
            Vector4 const z = UnitZ<Vector4>();
            Vector4 const w = UnitW<Vector4>();

            CHECK(GetX(AngleBetweenNormals(x, x)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenNormals(x, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(x, z)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(x, w)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenNormals(y, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(y, y)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenNormals(y, z)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(y, w)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenNormals(z, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(z, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(z, z)) == Approx{ DegreesToRadians(0.0f) });
            CHECK(GetX(AngleBetweenNormals(z, w)) == Approx{ DegreesToRadians(90.0f) });

            CHECK(GetX(AngleBetweenNormals(w, x)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(w, y)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(w, z)) == Approx{ DegreesToRadians(90.0f) });
            CHECK(GetX(AngleBetweenNormals(w, w)) == Approx{ DegreesToRadians(0.0f) });
        }
    }
}

TEST_CASE("Maths / Transforms")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Affine Transforms")
    {
        SECTION("2D")
        {
            Vector2 const scaling         = Make<Vector2>(1.3f, -3.4f);
            Vector2 const rotation_origin = Make<Vector2>(3.4f, 1.7f);
            float const rotation          = DegreesToRadians(-60.0f);
            Vector2 const translation     = Make<Vector2>(-2.3f, 3.3f);

            Matrix const m = CreateAffineTransform2D(
                scaling,
                rotation_origin,
                rotation,
                translation);

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.649999917f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -1.12583303f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -2.94448662f });
            CHECK(GetY(GetBaseY(m)) == Approx{ -1.69999981f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ -2.07224298f });
            CHECK(GetY(GetBaseW(m)) == Approx{ 7.09448671f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }

        SECTION("3D")
        {
            Vector3 const scaling         = Make<Vector3>(1.1f, 1.1f, 1.1f);
            Vector3 const rotation_origin = Make<Vector3>(3.4f, 1.7f, -2.3f);
            Quaternion const rotation     = CreateFromAxisAngle<Quaternion>(Make<Vector3>(2.1f, 1.1f, -3.3f), DegreesToRadians(-60.0f));
            Vector3 const translation     = Make<Vector3>(3.3f, -1.3f, 2.1f);

            Matrix const m = CreateAffineTransform(
                scaling,
                rotation_origin,
                rotation,
                translation);

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.696910977f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.850637615f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0270346422f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.696730852f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.590308905f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.613271236f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.488754869f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.371417761f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.912780166f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 4.60073566f });
            CHECK(GetY(GetBaseW(m)) == Approx{ -2.36493826f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 2.57276130f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }
    }

    SECTION("Transforms")
    {
        SECTION("2D")
        {
            Vector2 const scaling_origin    = Make<Vector2>(-2.1f, 1.3f);
            float const scaling_orientation = DegreesToRadians(45.0f);
            Vector2 const scaling           = Make<Vector2>(1.1f, 1.1f);
            Vector2 const rotation_origin   = Make<Vector2>(3.4f, 1.7f);
            float const rotation            = DegreesToRadians(-60.0f);
            Vector2 const translation       = Make<Vector2>(3.3f, -1.3f);

            Matrix const m = CreateTransform2D(
                scaling_origin,
                scaling_orientation,
                scaling,
                rotation_origin,
                rotation,
                translation);

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.549999893f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.952627897f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.952627897f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.549999893f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 3.52017379f });
            CHECK(GetY(GetBaseW(m)) == Approx{ 2.24762177f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }

        SECTION("3D")
        {
            Vector3 const scaling_origin         = Make<Vector3>(-2.1f, 1.3f, -3.4f);
            Quaternion const scaling_orientation = CreateFromAxisAngle<Quaternion>(Make<Vector3>(-2.1f, 1.1f, 2.3f), DegreesToRadians(45.0f));
            Vector3 const scaling                = Make<Vector3>(1.1f, 1.1f, 1.1f);
            Vector3 const rotation_origin        = Make<Vector3>(3.4f, 1.7f, -2.3f);
            Quaternion const rotation            = CreateFromAxisAngle<Quaternion>(Make<Vector3>(2.1f, 1.1f, -3.3f), DegreesToRadians(-60.0f));
            Vector3 const translation            = Make<Vector3>(3.3f, -1.3f, 2.1f);

            Matrix const m = CreateTransform(
                scaling_origin,
                scaling_orientation,
                scaling,
                rotation_origin,
                rotation,
                translation);

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.696911037f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.850637555f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0270346627f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.696730852f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.590308845f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.613271236f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.488754809f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.371417731f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.912780046f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 4.66505337f });
            CHECK(GetY(GetBaseW(m)) == Approx{ -2.15750575f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 2.93253255f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }
    }
}

TEST_CASE("Maths / Rotations / Matrix rotations around arbitrary axis")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Case 1")
    {
        Vector3 const axis = Make<Vector3>(1.0f, -2.0f, 3.0f);

        Matrix m = CreateFromAxisAngle<Matrix>(axis, DegreesToRadians(45.0f));

        CHECK(GetX(GetBaseX(m)) == Approx{ 0.7280276f });
        CHECK(GetY(GetBaseX(m)) == Approx{ 0.5251047f });
        CHECK(GetZ(GetBaseX(m)) == Approx{ 0.44072793f });
        CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseY(m)) == Approx{ -0.608788610f });
        CHECK(GetY(GetBaseY(m)) == Approx{ 0.790790498f });
        CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0634565353f });
        CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseZ(m)) == Approx{ -0.315201640f });
        CHECK(GetY(GetBaseZ(m)) == Approx{ -0.31507931f }.margin(0.001f));
        CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.895395219f });
        CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetY(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
    }

    SECTION("Case 2")
    {
        Vector3 const axis = Make<Vector3>(-1.0f, 3.0f, -3.0f);

        Matrix m = CreateFromAxisAngle<Matrix>(axis, DegreesToRadians(60.0f));

        CHECK(GetX(GetBaseX(m)) == Approx{ 0.526315749f });
        CHECK(GetY(GetBaseX(m)) == Approx{ -0.674986959f });
        CHECK(GetZ(GetBaseX(m)) == Approx{ -0.517092228f });
        CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseY(m)) == Approx{ 0.517092228f });
        CHECK(GetY(GetBaseY(m)) == Approx{ 0.736842036f });
        CHECK(GetZ(GetBaseY(m)) == Approx{ -0.43552199f });
        CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseZ(m)) == Approx{ 0.674986959f });
        CHECK(GetY(GetBaseZ(m)) == Approx{ -0.0381622612f });
        CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.736842036 });
        CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

        CHECK(GetX(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetY(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
        CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
    }
}

TEST_CASE("Maths / Rotations / Matrix <-> Quaternion")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    constexpr float const angle_step = 5.0f;

    Vector3 const v = Make<Vector3>(1.0f, -2.0f, 3.0f);

    SECTION("Rotation X")
    {
        Vector3 const axis = UnitX<Vector3>();

        for (float angle = -360.0f; angle <= 360.0f; angle += angle_step)
        {
            float const radians = DegreesToRadians(angle);
            Matrix const m      = CreateRotationX(radians);
            Quaternion const q  = CreateFromNormalAngle<Quaternion>(axis, radians);

            //
            // Check if quaternion rotates vector as well as matrix.
            //

            Vector3 const vm = Transform(v, m);
            Vector3 const vq = Rotate(v, q);

            CHECK(GetX(vm) == Approx{ GetX(vq) });
            CHECK(GetY(vm) == Approx{ GetY(vq) }.margin(0.00001f));
            CHECK(GetZ(vm) == Approx{ GetZ(vq) });


            //
            // Convert quaternion back to matrix and check whether rotation will match.
            //

            Quaternion const mq = CreateFromMatrix(m);
            Vector3 const vmq   = Rotate(v, mq);

            CHECK(GetX(vmq) == Approx{ GetX(vq) });
            CHECK(GetY(vmq) == Approx{ GetY(vq) }.margin(0.00001f));
            CHECK(GetZ(vmq) == Approx{ GetZ(vq) });

            Matrix const qm   = CreateFromQuaternion(q);
            Vector3 const vqm = Transform(v, qm);

            CHECK(GetX(vqm) == Approx{ GetX(vq) });
            CHECK(GetY(vqm) == Approx{ GetY(vq) });
            CHECK(GetZ(vqm) == Approx{ GetZ(vq) });
        }
    }

    SECTION("Rotation Y")
    {
        Vector3 const axis = UnitY<Vector3>();

        for (float angle = -360.0f; angle <= 360.0f; angle += angle_step)
        {
            float const radians = DegreesToRadians(angle);
            Matrix const m      = CreateRotationY(radians);
            Quaternion const q  = CreateFromNormalAngle<Quaternion>(axis, radians);

            //
            // Check if quaternion rotates vector as well as matrix.
            //

            Vector3 const vm = Transform(v, m);
            Vector3 const vq = Rotate(v, q);

            CHECK(GetX(vm) == Approx{ GetX(vq) });
            CHECK(GetY(vm) == Approx{ GetY(vq) });
            CHECK(GetZ(vm) == Approx{ GetZ(vq) });


            //
            // Convert quaternion back to matrix and check whether rotation will match.
            //

            Quaternion const mq = CreateFromMatrix(m);
            Vector3 const vmq   = Rotate(v, mq);

            CHECK(GetX(vmq) == Approx{ GetX(vq) });
            CHECK(GetY(vmq) == Approx{ GetY(vq) });
            CHECK(GetZ(vmq) == Approx{ GetZ(vq) });

            Matrix const qm   = CreateFromQuaternion(q);
            Vector3 const vqm = Transform(v, qm);

            CHECK(GetX(vqm) == Approx{ GetX(vq) });
            CHECK(GetY(vqm) == Approx{ GetY(vq) });
            CHECK(GetZ(vqm) == Approx{ GetZ(vq) });
        }
    }

    SECTION("Rotation Z")
    {
        Vector3 const axis = UnitZ<Vector3>();

        for (float angle = -360.0f; angle <= 360.0f; angle += angle_step)
        {
            float const radians = DegreesToRadians(angle);
            Matrix const m      = CreateRotationZ(radians);
            Quaternion const q  = CreateFromNormalAngle<Quaternion>(axis, radians);

            //
            // Check if quaternion rotates vector as well as matrix.
            //

            Vector3 const vm = Transform(v, m);
            Vector3 const vq = Rotate(v, q);

            CHECK(GetX(vm) == Approx{ GetX(vq) });
            CHECK(GetY(vm) == Approx{ GetY(vq) });
            CHECK(GetZ(vm) == Approx{ GetZ(vq) });


            //
            // Convert quaternion back to matrix and check whether rotation will match.
            //

            Quaternion const mq = CreateFromMatrix(m);
            Vector3 const vmq   = Rotate(v, mq);

            CHECK(GetX(vmq) == Approx{ GetX(vq) });
            CHECK(GetY(vmq) == Approx{ GetY(vq) });
            CHECK(GetZ(vmq) == Approx{ GetZ(vq) });

            Matrix const qm   = CreateFromQuaternion(q);
            Vector3 const vqm = Transform(v, qm);

            CHECK(GetX(vqm) == Approx{ GetX(vq) });
            CHECK(GetY(vqm) == Approx{ GetY(vq) });
            CHECK(GetZ(vqm) == Approx{ GetZ(vq) });
        }
    }
}

TEST_CASE("Maths / Matrix / Rotations")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Rotation X")
    {
        SECTION("angle = 0 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(0.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -30 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.5F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.5F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 30 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.5f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.5f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -45 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 45 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -90 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ -1.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 90 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -1.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -135 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(-135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 135 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }
    }

    SECTION("Rotation Y")
    {
        SECTION("angle = 0 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(0.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -30 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.5F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.5f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 30 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ -0.5f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.5f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.866025f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -45 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 45 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -90 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -1.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 90 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ -1.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -135 deg")
        {
            Matrix const m = CreateRotationY(DegreesToRadians(-135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 135 deg")
        {
            Matrix const m = CreateRotationX(DegreesToRadians(135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ -0.7071067f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }
    }

    SECTION("Rotation Z")
    {
        SECTION("angle = 0 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(0.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0F });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -30 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.5F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.5F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 30 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(30.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.866025f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.5F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.5F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.866025f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -45 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 45 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(45.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -90 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ -1.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 1.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 90 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(90.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ 0.0F }.margin(0.001f));
            CHECK(GetY(GetBaseX(m)) == Approx{ 1.0F });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ -1.0F });
            CHECK(GetY(GetBaseY(m)) == Approx{ 0.0f }.margin(0.001f));
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = -135 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(-135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseY(m)) == Approx{ 0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0F });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0F });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0F });
        }

        SECTION("angle = 135 deg")
        {
            Matrix const m = CreateRotationZ(DegreesToRadians(135.0f));

            CHECK(GetX(GetBaseX(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseX(m)) == Approx{ 0.7071067f });
            CHECK(GetZ(GetBaseX(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseX(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetY(GetBaseY(m)) == Approx{ -0.7071067f });
            CHECK(GetZ(GetBaseY(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseY(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseZ(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseZ(m)) == Approx{ 1.0f });
            CHECK(GetW(GetBaseZ(m)) == Approx{ 0.0f });

            CHECK(GetX(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetY(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetZ(GetBaseW(m)) == Approx{ 0.0f });
            CHECK(GetW(GetBaseW(m)) == Approx{ 1.0f });
        }
    }
}


TEST_CASE("Maths / Vector4 / Vector4 Cross Product")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector4 v0 = Make<Vector4>(1.0F, 2.0F, 1.0F, 3.0F);
    Vector4 v1 = Make<Vector4>(3.0F, 1.0F, 3.0F, 5.0F);
    Vector4 v2 = Make<Vector4>(2.0F, 2.0F, 3.0F, 2.0F);
    Vector4 v3 = Make<Vector4>(-2.0F, 2.0F, -3.0F, 2.0F);

    SECTION("cross(v0, v1, v2)")
    {
        Vector4 r = Cross(v0, v1, v2);

        CHECK(GetX(r) == -19.0F);
        CHECK(GetY(r) == -4.0F);
        CHECK(GetZ(r) == 12.0F);
        CHECK(GetW(r) == 5.0F);
    }

    SECTION("cross(v1, v0, v2)")
    {
        Vector4 r = Cross(v1, v0, v2);

        CHECK(GetX(r) == 19.0F);
        CHECK(GetY(r) == 4.0F);
        CHECK(GetZ(r) == -12.0F);
        CHECK(GetW(r) == -5.0F);
    }

    SECTION("cross(v1, v2, v3)")
    {
        Vector4 r = Cross(v1, v2, v3);

        CHECK(GetX(r) == -48.0F);
        CHECK(GetY(r) == -12.0F);
        CHECK(GetZ(r) == 32.0F);
        CHECK(GetW(r) == 12.0F);
    }

    SECTION("cross(v2, v3, v0)")
    {
        Vector4 r = Cross(v2, v3, v0);

        CHECK(GetX(r) == -12.0F);
        CHECK(GetY(r) == -4.0F);
        CHECK(GetZ(r) == 8.0F);
        CHECK(GetW(r) == 4.0F);
    }
}


TEST_CASE("BitCast between floating type")
{
    using namespace Graphyte;
    using namespace Graphyte;

    CHECK(BitCast<uint32_t>(1.0f) == 0x3f800000u);
    CHECK(BitCast<uint32_t>(12.5f) == 0x41480000u);
    CHECK(BitCast<uint32_t>(1337.0f) == 0x44a72000u);
    CHECK(BitCast<uint32_t>(-14.25f) == 0xc1640000u);

    CHECK(BitCast<float>(0x3f800000u) == 1.0f);
    CHECK(BitCast<float>(0x41480000u) == 12.5f);
    CHECK(BitCast<float>(0x44a72000u) == 1337.0f);
    CHECK(BitCast<float>(0xc1640000u) == -14.25f);
}


TEST_CASE("Maths / Vector / Copy Sign")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector4 const vn = Make<Vector4>(-1.0F, 2.0F, 3.0F, -4.0F);
    Vector4 const vs = Make<Vector4>(1.0F, 1.0F, -1.0F, -1.0F);
    Vector4 const vc = CopySign(vn, vs);

    CHECK(GetX(vc) == 1.0F);
    CHECK(GetY(vc) == 2.0F);
    CHECK(GetZ(vc) == -3.0F);
    CHECK(GetW(vc) == -4.0F);

    float const sn = -1.0F;
    float const ss = 1.0F;
    float const sc = CopySign(sn, ss);

    CHECK(sc == 1.0F);
}

TEST_CASE("Maths / Matrix Invertability")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    auto test = [](Float4x4A const& src, Vector4 cdet1, Vector4 cdet2, Vector4 epsilon) {
        Vector4 det1{};
        Vector4 det2{};

        Float4x4A work{};
        Matrix original = Load<Matrix>(&src);

        Matrix inverted = Inverse(original, &det1);
        Store(&work, inverted);

        CHECK(IsEqual(det1, cdet1, epsilon));


        Matrix reconstructed = Inverse(inverted, &det2);
        Store(&work, reconstructed);

        CHECK(IsEqual(det2, cdet2, epsilon));

        CHECK(IsEqual(GetBaseX(reconstructed), GetBaseX(original), epsilon));
        CHECK(IsEqual(GetBaseY(reconstructed), GetBaseY(original), epsilon));
        CHECK(IsEqual(GetBaseZ(reconstructed), GetBaseZ(original), epsilon));
        CHECK(IsEqual(GetBaseW(reconstructed), GetBaseW(original), epsilon));
    };

    test(
        Float4x4A{ { {
            // clang-format off
            2.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 1.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 1.0F, 0.0F,
            0.0F, 0.0F, 0.0F, 1.0F,
            // clang-format on
        } } },
        Replicate<Vector4>(2.0F),
        Replicate<Vector4>(0.5F),
        Epsilon<Vector4>());

    test(
        Float4x4A{ { {
            // clang-format off
            1.0F, 3.0F, 1.0F, 4.0F,
            3.0F, 9.0F, 5.0F, 15.0F,
            0.0F, 2.0F, 1.0F, 1.0F,
            0.0F, 4.0F, 2.0F, 3.0F,
            // clang-format on
        } } },
        Replicate<Vector4>(-4.0F),
        Replicate<Vector4>(-0.25F),
        Epsilon<Vector4>());

    test(
        Float4x4A{ { {
            // clang-format off
            5.0F, -7.0F, 2.0F, 2.0F,
            0.0F, 3.0F, 0.0F, -4.0F,
            -5.0F, -8.0F, 0.0F, 3.0F,
            0.0F, 5.0F, 0.0F, -6.0F,
            // clang-format on
        } } },
        Replicate<Vector4>(20.0F),
        Replicate<Vector4>(0.05F),
        Replicate<Vector4>(0.01F));
}

TEST_CASE("Maths / Fresnel Term")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("index = 0.5")
    {
        Vector4 const r0a = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(0.0F),
                DegreesToRadians(30.0F),
                DegreesToRadians(45.0F),
                DegreesToRadians(60.0F))),
            Replicate<Vector4>(0.5F));

        CHECK(GetX(r0a) == Approx{ 0.111111112F }.margin(0.001F));
        CHECK(GetY(r0a) == Approx{ 1.0F }.margin(0.01F));
        CHECK(GetZ(r0a) == Approx{ 0.0151518816F }.margin(0.001F));
        CHECK(GetW(r0a) == Approx{ 0.0166181885F }.margin(0.001F));

        Vector4 const r0b = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(90.0F),
                DegreesToRadians(135.0F),
                DegreesToRadians(180.0F),
                DegreesToRadians(225.0F))),
            Replicate<Vector4>(0.5F));

        CHECK(GetX(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetW(r0b) == Approx{ 1.0F }.margin(0.001F));

        Vector4 const r0c = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(-30.0F),
                DegreesToRadians(-45.0F),
                DegreesToRadians(-60.0F),
                DegreesToRadians(-90.0F))),
            Replicate<Vector4>(0.5F));

        CHECK(GetX(r0c) == Approx{ 1.0F }.margin(0.01F));
        CHECK(GetY(r0c) == Approx{ 0.0151518816F }.margin(0.001F));
        CHECK(GetZ(r0c) == Approx{ 0.0166181885F }.margin(0.001F));
        CHECK(GetW(r0c) == Approx{ 1.0F }.margin(0.001F));
    }

    SECTION("index = 1")
    {
        Vector4 const r0a = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(0.0F),
                DegreesToRadians(30.0F),
                DegreesToRadians(45.0F),
                DegreesToRadians(60.0F))),
            Replicate<Vector4>(1.0F));

        CHECK(GetX(r0a) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r0a) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetZ(r0a) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetW(r0a) == Approx{ 0.0F }.margin(0.001F));

        Vector4 const r0b = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(90.0F),
                DegreesToRadians(135.0F),
                DegreesToRadians(180.0F),
                DegreesToRadians(225.0F))),
            Replicate<Vector4>(1.0F));

        CHECK(GetX(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetW(r0b) == Approx{ 1.0F }.margin(0.001F));

        Vector4 const r0c = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(-30.0F),
                DegreesToRadians(-45.0F),
                DegreesToRadians(-60.0F),
                DegreesToRadians(-90.0F))),
            Replicate<Vector4>(1.0F));

        CHECK(GetX(r0c) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r0c) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetZ(r0c) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetW(r0c) == Approx{ 1.0F }.margin(0.001F));
    }

    SECTION("index = 1.5")
    {
        Vector4 const r0a = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(0.0F),
                DegreesToRadians(30.0F),
                DegreesToRadians(45.0F),
                DegreesToRadians(60.0F))),
            Replicate<Vector4>(1.5F));

        CHECK(GetX(r0a) == Approx{ 0.0399999991F }.margin(0.001F));
        CHECK(GetY(r0a) == Approx{ 0.0415226296F }.margin(0.01F));
        CHECK(GetZ(r0a) == Approx{ 0.0502399169F }.margin(0.001F));
        CHECK(GetW(r0a) == Approx{ 0.0891867429F }.margin(0.001F));

        Vector4 const r0b = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(90.0F),
                DegreesToRadians(135.0F),
                DegreesToRadians(180.0F),
                DegreesToRadians(225.0F))),
            Replicate<Vector4>(1.5F));

        CHECK(GetX(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r0b) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetW(r0b) == Approx{ 1.0F }.margin(0.001F));

        Vector4 const r0c = FresnelTerm(
            Cos(Make<Vector4>(
                DegreesToRadians(-30.0F),
                DegreesToRadians(-45.0F),
                DegreesToRadians(-60.0F),
                DegreesToRadians(-90.0F))),
            Replicate<Vector4>(1.5F));

        CHECK(GetX(r0c) == Approx{ 0.0415226296F }.margin(0.01F));
        CHECK(GetY(r0c) == Approx{ 0.0502399169F }.margin(0.001F));
        CHECK(GetZ(r0c) == Approx{ 0.0891867429F }.margin(0.001F));
        CHECK(GetW(r0c) == Approx{ 1.0F }.margin(0.001F));
    }
}


TEST_CASE("Maths / Vector / Line - point distance")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector3 const p0 = Make<Vector3>(-1.0F, -1.0F, -1.0F);
    Vector3 const p7 = Make<Vector3>(+1.0F, +1.0F, +1.0F);

    Vector3 const p1 = Make<Vector3>(+1.0F, -1.0F, -1.0F);
    Vector3 const p2 = Make<Vector3>(-1.0F, +1.0F, -1.0F);
    Vector3 const p3 = Make<Vector3>(+1.0F, +1.0F, -1.0F);
    Vector3 const p4 = Make<Vector3>(-1.0F, -1.0F, +1.0F);
    Vector3 const p5 = Make<Vector3>(+1.0F, -1.0F, +1.0F);
    Vector3 const p6 = Make<Vector3>(-1.0F, +1.0F, +1.0F);

    Vector4 const r0 = LinePointDistance(p0, p7, p0);
    Vector4 const r1 = LinePointDistance(p0, p7, p1);
    Vector4 const r2 = LinePointDistance(p0, p7, p2);
    Vector4 const r3 = LinePointDistance(p0, p7, p3);
    Vector4 const r4 = LinePointDistance(p0, p7, p4);
    Vector4 const r5 = LinePointDistance(p0, p7, p5);
    Vector4 const r6 = LinePointDistance(p0, p7, p6);
    Vector4 const r7 = LinePointDistance(p0, p7, p7);

    CHECK(GetX(r0) == Approx{ 0.0F });
    CHECK(GetX(r1) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r2) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r3) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r4) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r5) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r6) == Approx{ 1.6329931618554518F });
    CHECK(GetX(r7) == Approx{ 0.0F });
}

TEST_CASE("Maths / Vector / Refraction")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        Vector2 const n = Normalize(Make<Vector2>(1.0F, 1.0F));
        Vector2 const i = NegativeUnitY<Vector2>();

        SECTION("index = 0.5")
        {
            Vector2 const r = Refract(i, n, 0.5F);

            CHECK(GetX(r) == Approx{ -0.411437869F });
            CHECK(GetY(r) == Approx{ -0.911437869F });
        }

        SECTION("index = 1")
        {
            Vector2 const r = Refract(i, n, 1.0F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ -1.0F });
        }

        SECTION("index = 1.2")
        {
            Vector2 const r = Refract(i, n, 1.2F);

            CHECK(GetX(r) == Approx{ 0.225834280F });
            CHECK(GetY(r) == Approx{ -0.974165797F });
        }

        SECTION("index = 1.4")
        {
            Vector2 const r = Refract(i, n, 1.4F);

            CHECK(GetX(r) == Approx{ 0.599999845F });
            CHECK(GetY(r) == Approx{ -0.800000131F });
        }

        SECTION("index = 1.5")
        {
            Vector2 const r = Refract(i, n, 1.5F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
        }
    }

    SECTION("Vector3")
    {
        Vector3 const n = Normalize(Make<Vector3>(1.0F, 1.0F, 1.0F));
        Vector3 const i = NegativeUnitY<Vector3>();

        SECTION("index = 0.5")
        {
            Vector3 const r = Refract(i, n, 0.5F);

            CHECK(GetX(r) == Approx{ -0.360379606F });
            CHECK(GetY(r) == Approx{ -0.860379577F });
            CHECK(GetZ(r) == Approx{ -0.360379606F });
        }

        SECTION("index = 1")
        {
            Vector3 const r = Refract(i, n, 1.0F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ -1.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.2")
        {
            Vector3 const r = Refract(i, n, 1.2F);

            CHECK(GetX(r) == Approx{ 0.284530073F });
            CHECK(GetY(r) == Approx{ -0.915470004F });
            CHECK(GetZ(r) == Approx{ 0.284530073F });
        }

        SECTION("index = 1.4")
        {
            Vector3 const r = Refract(i, n, 1.4F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.5")
        {
            Vector3 const r = Refract(i, n, 1.5F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
        }
    }

    SECTION("Vector4")
    {
        Vector4 const n = Normalize(Make<Vector4>(1.0F, 1.0F, 1.0F, 1.0F));
        Vector4 const i = NegativeUnitY<Vector4>();

        SECTION("index = 0.5")
        {
            Vector4 const r = Refract(i, n, 0.5F);

            CHECK(GetX(r) == Approx{ -0.325693905F });
            CHECK(GetY(r) == Approx{ -0.825693905F });
            CHECK(GetZ(r) == Approx{ -0.325693905F });
            CHECK(GetW(r) == Approx{ -0.325693905F });
        }

        SECTION("index = 1")
        {
            Vector4 const r = Refract(i, n, 1.0F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ -1.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.2")
        {
            Vector4 const r = Refract(i, n, 1.2F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.4")
        {
            Vector4 const r = Refract(i, n, 1.4F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }

        SECTION("index = 1.5")
        {
            Vector4 const r = Refract(i, n, 1.5F);

            CHECK(GetX(r) == Approx{ 0.0F });
            CHECK(GetY(r) == Approx{ 0.0F });
            CHECK(GetZ(r) == Approx{ 0.0F });
            CHECK(GetW(r) == Approx{ 0.0F });
        }
    }
}

TEST_CASE("Maths / Vector / Reflection")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("-45 deg Z reflection")
    {
        Vector3 const n = Normalize(Make<Vector3>(1.0F, 1.0F, 0.0f));
        Vector3 const i = NegativeUnitX<Vector3>();
        Vector3 const r = Reflect(i, n);

        CHECK(GetX(r) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r) == Approx{ 0.0F }.margin(0.001F));
    }

    SECTION("incident perpendicular to normal - not reflected")
    {
        Vector3 const n = Normalize(Make<Vector3>(0.0F, 1.0F, 0.0f));
        Vector3 const i = UnitX<Vector3>();
        Vector3 const r = Reflect(i, n);

        CHECK(GetX(r) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetY(r) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetZ(r) == Approx{ 0.0F }.margin(0.001F));
    }

    SECTION("parallel to normal reflection")
    {
        Vector3 const n = UnitY<Vector3>();
        Vector3 const i = NegativeUnitY<Vector3>();
        Vector3 const r = Reflect(i, n);

        CHECK(GetX(r) == Approx{ 0.0F }.margin(0.001F));
        CHECK(GetY(r) == Approx{ 1.0F }.margin(0.001F));
        CHECK(GetZ(r) == Approx{ 0.0F }.margin(0.001F));
    }
}

TEST_CASE("Maths / Vector / Plane Intersection")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("+X -> point")
    {
        Plane const p   = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitX<Vector3>());
        Vector3 const a = Make<Vector3>(-5.0F, 1.0F, 1.0F);
        Vector3 const b = Make<Vector3>(5.0F, 1.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(GetX(r) == Approx{ 1.0F });
        CHECK(GetY(r) == Approx{ 1.0F });
        CHECK(GetZ(r) == Approx{ 1.0F });
    }

    SECTION("+X -> nan")
    {
        Plane const p   = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitX<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, -5.0F, 1.0F);
        Vector3 const b = Make<Vector3>(1.0F, 5.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(std::isnan(GetX(r)));
        CHECK(std::isnan(GetY(r)));
        CHECK(std::isnan(GetZ(r)));
    }

    SECTION("+Y -> point")
    {
        Plane const p   = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitY<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, -5.0F, 1.0F);
        Vector3 const b = Make<Vector3>(1.0F, 5.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(GetX(r) == Approx{ 1.0F });
        CHECK(GetY(r) == Approx{ 1.0F });
        CHECK(GetZ(r) == Approx{ 1.0F });
    }

    SECTION("+Y -> nan")
    {
        Plane const p   = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitY<Vector3>());
        Vector3 const a = Make<Vector3>(-5.0F, 1.0F, 1.0F);
        Vector3 const b = Make<Vector3>(5.0F, 1.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(std::isnan(GetX(r)));
        CHECK(std::isnan(GetY(r)));
        CHECK(std::isnan(GetZ(r)));
    }

    SECTION("+Z -> point")
    {
        Plane const p   = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitZ<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, 1.0F, -5.0F);
        Vector3 const b = Make<Vector3>(1.0F, 1.0F, 5.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(GetX(r) == Approx{ 1.0F });
        CHECK(GetY(r) == Approx{ 1.0F });
        CHECK(GetZ(r) == Approx{ 1.0F });
    }

    SECTION("+Z -> nan")
    {
        Plane const p   = CreateFromPointNormal(Make<Vector3>(1.0F, 1.0F, 1.0F), UnitZ<Vector3>());
        Vector3 const a = Make<Vector3>(1.0F, -5.0F, 1.0F);
        Vector3 const b = Make<Vector3>(1.0F, 5.0F, 1.0F);

        Vector3 const r = LinePlaneIntersection(p, a, b);

        CHECK(std::isnan(GetX(r)));
        CHECK(std::isnan(GetY(r)));
        CHECK(std::isnan(GetZ(r)));
    }
}

TEST_CASE("Maths / Vector / Clamp length")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        for (float x = -5.0F; x <= 5.0F; x += 1.0F)
        {
            for (float y = -5.0F; y <= 5.0F; y += 1.0F)
            {
                if (IsZero(x, 0.001F) && IsZero(y, 0.001F))
                {
                    continue;
                }

                Vector2 const v = Make<Vector2>(x, y);
                Vector2 const c = ClampLength(v, 0.5F, 1.5F);

                // Normalize vector and get original length
                Vector2 const n = Normalize(v);
                Vector4 const l = Length(v);

                // Compute clamped expected length
                Vector4 const cl = Clamp(l, Replicate<Vector4>(0.5F), Replicate<Vector4>(1.5F));

                // And expected vector
                Vector2 const e{ Multiply(Vector4{ n.V }, cl).V };

                CHECK(IsEqual(c, e, Replicate<Vector4>(0.001F)));
            }
        }
    }

    SECTION("Vector3")
    {
        for (float x = -5.0F; x <= 5.0F; x += 1.0F)
        {
            for (float y = -5.0F; y <= 5.0F; y += 1.0F)
            {
                for (float z = -5.0F; z <= 5.0F; z += 1.0F)
                {
                    if (IsZero(x, 0.001F) && IsZero(y, 0.001F) && IsZero(z, 0.001F))
                    {
                        continue;
                    }

                    Vector3 const v = Make<Vector3>(x, y, z);
                    Vector3 const c = ClampLength(v, 0.5F, 1.5F);

                    // Normalize vector and get original length
                    Vector3 const n = Normalize(v);
                    Vector4 const l = Length(v);

                    // Compute clamped expected length
                    Vector4 const cl = Clamp(l, Replicate<Vector4>(0.5F), Replicate<Vector4>(1.5F));

                    // And expected vector
                    Vector3 const e{ Multiply(Vector4{ n.V }, cl).V };

                    CHECK(IsEqual(c, e, Replicate<Vector4>(0.001F)));
                }
            }
        }
    }

    SECTION("Vector4")
    {
        for (float x = -5.0F; x <= 5.0F; x += 1.0F)
        {
            for (float y = -5.0F; y <= 5.0F; y += 1.0F)
            {
                for (float z = -5.0F; z <= 5.0F; z += 1.0F)
                {
                    for (float w = -5.0F; w <= 5.0F; w += 1.0F)
                    {
                        if (IsZero(x, 0.001F) && IsZero(y, 0.001F) && IsZero(z, 0.001F) && IsZero(w, 0.001F))
                        {
                            continue;
                        }

                        Vector4 const v = Make<Vector4>(x, y, z, w);
                        Vector4 const c = ClampLength(v, 0.5F, 1.5F);

                        // Normalize vector and get original length
                        Vector4 const n = Normalize(v);
                        Vector4 const l = Length(v);

                        // Compute clamped expected length
                        Vector4 const cl = Clamp(l, Replicate<Vector4>(0.5F), Replicate<Vector4>(1.5F));

                        // And expected vector
                        Vector4 const e = Multiply(n, cl);

                        CHECK(IsEqual(c, e, Replicate<Vector4>(0.001F)));
                    }
                }
            }
        }
    }
}

TEST_CASE("Maths / Quaternion / Rotate vector by quaternion")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Unit X")
    {
        Vector3 const x0 = UnitX<Vector3>();

        SECTION("Around X")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x0) == Approx{ GetX(x1) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x1) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x1) }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x0) == Approx{ GetX(x2) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x2) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x2) }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x0) == Approx{ GetX(x3) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x3) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x3) }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x0) == Approx{ GetX(x4) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x4) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x4) }.margin(0.001F));
        }

        SECTION("Around Y")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 1.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }

        SECTION("Around Z")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }
    }

    SECTION("Unit Y")
    {
        Vector3 const x0 = UnitY<Vector3>();

        SECTION("Around X")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 1.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }

        SECTION("Around Y")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x0) == Approx{ GetX(x1) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x1) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x1) }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x0) == Approx{ GetX(x2) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x2) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x2) }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x0) == Approx{ GetX(x3) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x3) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x3) }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x0) == Approx{ GetX(x4) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x4) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x4) }.margin(0.001F));
        }

        SECTION("Around Z")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 0.0F }.margin(0.001F));
        }
    }

    SECTION("Unit Z")
    {
        Vector3 const x0 = UnitZ<Vector3>();

        SECTION("Around X")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 1.0F }.margin(0.001F));
        }

        SECTION("Around Y")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x1) == Approx{ 1.0F }.margin(0.001F));
            CHECK(GetY(x1) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x1) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x2) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x2) == Approx{ -1.0F }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x3) == Approx{ -1.0F }.margin(0.001F));
            CHECK(GetY(x3) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x3) == Approx{ 0.0F }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetY(x4) == Approx{ 0.0F }.margin(0.001F));
            CHECK(GetZ(x4) == Approx{ 1.0F }.margin(0.001F));
        }

        SECTION("Around Z")
        {
            Quaternion const q = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(90.0F));
            Vector3 const x1   = Rotate(x0, q);

            CHECK(GetX(x0) == Approx{ GetX(x1) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x1) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x1) }.margin(0.001F));

            Vector3 const x2 = Rotate(x1, q);

            CHECK(GetX(x0) == Approx{ GetX(x2) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x2) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x2) }.margin(0.001F));

            Vector3 const x3 = Rotate(x2, q);

            CHECK(GetX(x0) == Approx{ GetX(x3) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x3) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x3) }.margin(0.001F));

            Vector3 const x4 = Rotate(x3, q);

            CHECK(GetX(x0) == Approx{ GetX(x4) }.margin(0.001F));
            CHECK(GetY(x0) == Approx{ GetY(x4) }.margin(0.001F));
            CHECK(GetZ(x0) == Approx{ GetZ(x4) }.margin(0.001F));
        }
    }
}

TEST_CASE("Maths / Quaternion / Rotation from axis angle")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Axis X")
    {
        Quaternion const q000 = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(0.0F));
        Quaternion const q090 = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(90.0F));
        Quaternion const q180 = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(180.0F));
        Quaternion const q270 = CreateFromAxisAngle<Quaternion>(UnitX<Vector3>(), DegreesToRadians(270.0F));

        CHECK(GetX(q000) == Approx{ 0.0F });
        CHECK(GetY(q000) == Approx{ 0.0F });
        CHECK(GetZ(q000) == Approx{ 0.0F });
        CHECK(GetW(q000) == Approx{ 1.0F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q000);

            CHECK(GetX(axis) == 0.0F);
            CHECK(GetY(axis) == 0.0F);
            CHECK(GetZ(axis) == 0.0F);
            CHECK(angle == 0.0F);
        }

        CHECK(GetX(q090) == Approx{ 0.70711F });
        CHECK(GetY(q090) == Approx{ 0.0F });
        CHECK(GetZ(q090) == Approx{ 0.0F });
        CHECK(GetW(q090) == Approx{ 0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q090);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == Approx{ 1.0F });
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(90.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q180) == Approx{ 1.0F });
        CHECK(GetY(q180) == Approx{ 0.0F });
        CHECK(GetZ(q180) == Approx{ 0.0F });
        CHECK(GetW(q180) == Approx{ 0.0F }.margin(0.001F));

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q180);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 1.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(180.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q270) == Approx{ 0.70711F });
        CHECK(GetY(q270) == Approx{ 0.0F });
        CHECK(GetZ(q270) == Approx{ 0.0F });
        CHECK(GetW(q270) == Approx{ -0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q270);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == Approx{ 1.0F });
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(270.0F) }.margin(0.0001F));
        }
    }

    SECTION("Axis Y")
    {
        Quaternion const q000 = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(0.0F));
        Quaternion const q090 = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(90.0F));
        Quaternion const q180 = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(180.0F));
        Quaternion const q270 = CreateFromAxisAngle<Quaternion>(UnitY<Vector3>(), DegreesToRadians(270.0F));

        CHECK(GetX(q000) == Approx{ 0.0F });
        CHECK(GetY(q000) == Approx{ 0.0F });
        CHECK(GetZ(q000) == Approx{ 0.0F });
        CHECK(GetW(q000) == Approx{ 1.0F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q000);

            CHECK(GetX(axis) == 0.0F);
            CHECK(GetY(axis) == 0.0F);
            CHECK(GetZ(axis) == 0.0F);
            CHECK(angle == 0.0F);
        }

        CHECK(GetX(q090) == Approx{ 0.0F });
        CHECK(GetY(q090) == Approx{ 0.70711F });
        CHECK(GetZ(q090) == Approx{ 0.0F });
        CHECK(GetW(q090) == Approx{ 0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q090);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == Approx{ 1.0F });
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(90.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q180) == Approx{ 0.0F });
        CHECK(GetY(q180) == Approx{ 1.0F });
        CHECK(GetZ(q180) == Approx{ 0.0F });
        CHECK(GetW(q180) == Approx{ 0.0F }.margin(0.001F));

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q180);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 1.0F);
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(180.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q270) == Approx{ 0.0F });
        CHECK(GetY(q270) == Approx{ 0.70711F });
        CHECK(GetZ(q270) == Approx{ 0.0F });
        CHECK(GetW(q270) == Approx{ -0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q270);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == Approx{ 1.0F });
            CHECK(GetZ(normal) == 0.0F);
            CHECK(angle == Approx{ DegreesToRadians(270.0F) }.margin(0.0001F));
        }
    }

    SECTION("Axis Z")
    {
        Quaternion const q000 = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(0.0F));
        Quaternion const q090 = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(90.0F));
        Quaternion const q180 = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(180.0F));
        Quaternion const q270 = CreateFromAxisAngle<Quaternion>(UnitZ<Vector3>(), DegreesToRadians(270.0F));

        CHECK(GetX(q000) == Approx{ 0.0F });
        CHECK(GetY(q000) == Approx{ 0.0F });
        CHECK(GetZ(q000) == Approx{ 0.0F });
        CHECK(GetW(q000) == Approx{ 1.0F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q000);

            CHECK(GetX(axis) == 0.0F);
            CHECK(GetY(axis) == 0.0F);
            CHECK(GetZ(axis) == 0.0F);
            CHECK(angle == 0.0F);
        }

        CHECK(GetX(q090) == Approx{ 0.0F });
        CHECK(GetY(q090) == Approx{ 0.0F });
        CHECK(GetZ(q090) == Approx{ 0.70711F });
        CHECK(GetW(q090) == Approx{ 0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q090);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == Approx{ 1.0F });
            CHECK(angle == Approx{ DegreesToRadians(90.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q180) == Approx{ 0.0F });
        CHECK(GetY(q180) == Approx{ 0.0F });
        CHECK(GetZ(q180) == Approx{ 1.0F });
        CHECK(GetW(q180) == Approx{ 0.0F }.margin(0.001F));

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q180);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == 1.0F);
            CHECK(angle == Approx{ DegreesToRadians(180.0F) }.margin(0.0001F));
        }

        CHECK(GetX(q270) == Approx{ 0.0F });
        CHECK(GetY(q270) == Approx{ 0.0F });
        CHECK(GetZ(q270) == Approx{ 0.70711F });
        CHECK(GetW(q270) == Approx{ -0.70711F });

        {
            Vector3 axis;
            float angle;

            ToAxisAngle(axis, angle, q270);

            Vector3 normal = Normalize(axis);

            CHECK(GetX(normal) == 0.0F);
            CHECK(GetY(normal) == 0.0F);
            CHECK(GetZ(normal) == Approx{ 1.0F });
            CHECK(angle == Approx{ DegreesToRadians(270.0F) }.margin(0.0001F));
        }
    }
}


TEST_CASE("Maths / Quaternion / Multiply")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Quaternion const qx = UnitX<Quaternion>();
    Quaternion const qy = UnitY<Quaternion>();
    Quaternion const qz = UnitZ<Quaternion>();
    Quaternion const qw = UnitW<Quaternion>();

    SECTION("x*x")
    {
        Quaternion const qq = Multiply(qx, qx);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == -1.0F);
    }

    SECTION("x*y")
    {
        Quaternion const qq = Multiply(qx, qy);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("x*z")
    {
        Quaternion const qq = Multiply(qx, qz);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == -1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("x*w")
    {
        Quaternion const qq = Multiply(qx, qw);
        CHECK(GetX(qq) == 1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("y*x")
    {
        Quaternion const qq = Multiply(qy, qx);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == -1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("y*y")
    {
        Quaternion const qq = Multiply(qy, qy);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == -1.0F);
    }

    SECTION("y*z")
    {
        Quaternion const qq = Multiply(qy, qz);
        CHECK(GetX(qq) == 1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("y*w")
    {
        Quaternion const qq = Multiply(qy, qw);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("z*x")
    {
        Quaternion const qq = Multiply(qz, qx);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("z*y")
    {
        Quaternion const qq = Multiply(qz, qy);
        CHECK(GetX(qq) == -1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("z*z")
    {
        Quaternion const qq = Multiply(qz, qz);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == -1.0F);
    }

    SECTION("z*w")
    {
        Quaternion const qq = Multiply(qz, qw);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*x")
    {
        Quaternion const qq = Multiply(qw, qx);
        CHECK(GetX(qq) == 1.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*y")
    {
        Quaternion const qq = Multiply(qw, qy);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 1.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*z")
    {
        Quaternion const qq = Multiply(qw, qz);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 1.0F);
        CHECK(GetW(qq) == 0.0F);
    }

    SECTION("w*w")
    {
        Quaternion const qq = Multiply(qw, qw);
        CHECK(GetX(qq) == 0.0F);
        CHECK(GetY(qq) == 0.0F);
        CHECK(GetZ(qq) == 0.0F);
        CHECK(GetW(qq) == 1.0F);
    }
}

TEST_CASE("Maths / Plane / Normalized")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Plane const p = CreateFromPoints(
        Add(UnitX<Vector3>(), UnitY<Vector3>()),
        Add(Zero<Vector3>(), UnitY<Vector3>()),
        Add(UnitZ<Vector3>(), UnitY<Vector3>()));

    CHECK(GetX(p) == Approx{ 0.0F });
    CHECK(GetY(p) == Approx{ 1.0F });
    CHECK(GetZ(p) == Approx{ 0.0F });
    CHECK(GetW(p) == Approx{ -1.0F });
}

TEST_CASE("Maths / Vector / Horizontal operations")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;


    SECTION("Vector4")
    {
        Vector4 const v0 = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);
        Vector4 const v1 = Make<Vector4>(4.0F, 1.0F, 2.0F, 3.0F);
        Vector4 const v2 = Make<Vector4>(3.0F, 4.0F, 1.0F, 2.0F);
        Vector4 const v3 = Make<Vector4>(2.0F, 3.0F, 4.0F, 1.0F);

        SECTION("Horizontal min")
        {
            Vector4 const h0 = Hmin(v0);
            Vector4 const h1 = Hmin(v1);
            Vector4 const h2 = Hmin(v2);
            Vector4 const h3 = Hmin(v3);

            CHECK(GetX(h0) == 1.0F);
            CHECK(GetY(h0) == 1.0F);
            CHECK(GetZ(h0) == 1.0F);
            CHECK(GetW(h0) == 1.0F);

            CHECK(GetX(h1) == 1.0F);
            CHECK(GetY(h1) == 1.0F);
            CHECK(GetZ(h1) == 1.0F);
            CHECK(GetW(h1) == 1.0F);

            CHECK(GetX(h2) == 1.0F);
            CHECK(GetY(h2) == 1.0F);
            CHECK(GetZ(h2) == 1.0F);
            CHECK(GetW(h2) == 1.0F);

            CHECK(GetX(h3) == 1.0F);
            CHECK(GetY(h3) == 1.0F);
            CHECK(GetZ(h3) == 1.0F);
            CHECK(GetW(h3) == 1.0F);
        }

        SECTION("Horizontal max")
        {
            Vector4 const h0 = Hmax(v0);
            Vector4 const h1 = Hmax(v1);
            Vector4 const h2 = Hmax(v2);
            Vector4 const h3 = Hmax(v3);

            CHECK(GetX(h0) == 4.0F);
            CHECK(GetY(h0) == 4.0F);
            CHECK(GetZ(h0) == 4.0F);
            CHECK(GetW(h0) == 4.0F);

            CHECK(GetX(h1) == 4.0F);
            CHECK(GetY(h1) == 4.0F);
            CHECK(GetZ(h1) == 4.0F);
            CHECK(GetW(h1) == 4.0F);

            CHECK(GetX(h2) == 4.0F);
            CHECK(GetY(h2) == 4.0F);
            CHECK(GetZ(h2) == 4.0F);
            CHECK(GetW(h2) == 4.0F);

            CHECK(GetX(h3) == 4.0F);
            CHECK(GetY(h3) == 4.0F);
            CHECK(GetZ(h3) == 4.0F);
            CHECK(GetW(h3) == 4.0F);
        }

        SECTION("Horizontal sum")
        {
            Vector4 const h0 = Hsum(v0);
            Vector4 const h1 = Hsum(v1);
            Vector4 const h2 = Hsum(v2);
            Vector4 const h3 = Hsum(v3);

            CHECK(GetX(h0) == 10.0F);
            CHECK(GetY(h0) == 10.0F);
            CHECK(GetZ(h0) == 10.0F);
            CHECK(GetW(h0) == 10.0F);

            CHECK(GetX(h1) == 10.0F);
            CHECK(GetY(h1) == 10.0F);
            CHECK(GetZ(h1) == 10.0F);
            CHECK(GetW(h1) == 10.0F);

            CHECK(GetX(h2) == 10.0F);
            CHECK(GetY(h2) == 10.0F);
            CHECK(GetZ(h2) == 10.0F);
            CHECK(GetW(h2) == 10.0F);

            CHECK(GetX(h3) == 10.0F);
            CHECK(GetY(h3) == 10.0F);
            CHECK(GetZ(h3) == 10.0F);
            CHECK(GetW(h3) == 10.0F);
        }
    }


    SECTION("Horizontal Min / Vector3")
    {
        Vector3 const v0 = Make<Vector3>(1.0F, 2.0F, 3.0F);
        Vector3 const v1 = Make<Vector3>(4.0F, 3.0F, 2.0F);
        Vector3 const v2 = Make<Vector3>(5.0F, 3.0F, 4.0F);

        SECTION("Horizontal min")
        {
            Vector4 const h0 = Hmin(v0);
            Vector4 const h1 = Hmin(v1);
            Vector4 const h2 = Hmin(v2);

            CHECK(GetX(h0) == 1.0F);
            CHECK(GetY(h0) == 1.0F);
            CHECK(GetZ(h0) == 1.0F);
            CHECK(GetW(h0) == 1.0F);

            CHECK(GetX(h1) == 2.0F);
            CHECK(GetY(h1) == 2.0F);
            CHECK(GetZ(h1) == 2.0F);
            CHECK(GetW(h1) == 2.0F);

            CHECK(GetX(h2) == 3.0F);
            CHECK(GetY(h2) == 3.0F);
            CHECK(GetZ(h2) == 3.0F);
            CHECK(GetW(h2) == 3.0F);
        }

        SECTION("Horizontal max")
        {
            Vector4 const h0 = Hmax(v0);
            Vector4 const h1 = Hmax(v1);
            Vector4 const h2 = Hmax(v2);

            CHECK(GetX(h0) == 3.0F);
            CHECK(GetY(h0) == 3.0F);
            CHECK(GetZ(h0) == 3.0F);
            CHECK(GetW(h0) == 3.0F);

            CHECK(GetX(h1) == 4.0F);
            CHECK(GetY(h1) == 4.0F);
            CHECK(GetZ(h1) == 4.0F);
            CHECK(GetW(h1) == 4.0F);

            CHECK(GetX(h2) == 5.0F);
            CHECK(GetY(h2) == 5.0F);
            CHECK(GetZ(h2) == 5.0F);
            CHECK(GetW(h2) == 5.0F);
        }

        SECTION("Horizontal sum")
        {
            Vector4 const h0 = Hsum(v0);
            Vector4 const h1 = Hsum(v1);
            Vector4 const h2 = Hsum(v2);

            CHECK(GetX(h0) == 6.0F);
            CHECK(GetY(h0) == 6.0F);
            CHECK(GetZ(h0) == 6.0F);
            CHECK(GetW(h0) == 6.0F);

            CHECK(GetX(h1) == 9.0F);
            CHECK(GetY(h1) == 9.0F);
            CHECK(GetZ(h1) == 9.0F);
            CHECK(GetW(h1) == 9.0F);

            CHECK(GetX(h2) == 12.0F);
            CHECK(GetY(h2) == 12.0F);
            CHECK(GetZ(h2) == 12.0F);
            CHECK(GetW(h2) == 12.0F);
        }
    }


    SECTION("Horizontal Min / Vector2")
    {
        Vector2 const v0 = Make<Vector2>(1.0F, 2.0F);
        Vector2 const v1 = Make<Vector2>(4.0F, 3.0F);

        SECTION("Horizontal min")
        {
            Vector4 const h0 = Hmin(v0);
            Vector4 const h1 = Hmin(v1);

            CHECK(GetX(h0) == 1.0F);
            CHECK(GetY(h0) == 1.0F);
            CHECK(GetZ(h0) == 1.0F);
            CHECK(GetW(h0) == 1.0F);

            CHECK(GetX(h1) == 3.0F);
            CHECK(GetY(h1) == 3.0F);
            CHECK(GetZ(h1) == 3.0F);
            CHECK(GetW(h1) == 3.0F);
        }

        SECTION("Horizontal max")
        {
            Vector4 const h0 = Hmax(v0);
            Vector4 const h1 = Hmax(v1);

            CHECK(GetX(h0) == 2.0F);
            CHECK(GetY(h0) == 2.0F);
            CHECK(GetZ(h0) == 2.0F);
            CHECK(GetW(h0) == 2.0F);

            CHECK(GetX(h1) == 4.0F);
            CHECK(GetY(h1) == 4.0F);
            CHECK(GetZ(h1) == 4.0F);
            CHECK(GetW(h1) == 4.0F);
        }

        SECTION("Horizontal sum")
        {
            Vector4 const h0 = Hsum(v0);
            Vector4 const h1 = Hsum(v1);

            CHECK(GetX(h0) == 3.0F);
            CHECK(GetY(h0) == 3.0F);
            CHECK(GetZ(h0) == 3.0F);
            CHECK(GetW(h0) == 3.0F);

            CHECK(GetX(h1) == 7.0F);
            CHECK(GetY(h1) == 7.0F);
            CHECK(GetZ(h1) == 7.0F);
            CHECK(GetW(h1) == 7.0F);
        }
    }
}


TEST_CASE("Maths / Quaternion / exp log identity")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Identity quaternion exp+log")
    {
        Quaternion const qi = Make<Quaternion>(1.2F, -2.6F, 3.1F, 6.0F);
        Quaternion const ql = Log(qi);
        Quaternion const qe = Exp(ql);

        CHECK(GetX(ql) == Approx{ 0.174299479F }.margin(0.0005F));
        CHECK(GetY(ql) == Approx{ -0.377526760F }.margin(0.0005F));
        CHECK(GetZ(ql) == Approx{ 0.450128078F }.margin(0.0005F));
        CHECK(GetW(ql) == Approx{ 1.99272966F }.margin(0.0005F));

        CHECK(GetX(qi) == Approx{ GetX(qe) }.margin(0.001F));
        CHECK(GetY(qi) == Approx{ GetY(qe) }.margin(0.001F));
        CHECK(GetZ(qi) == Approx{ GetZ(qe) }.margin(0.001F));
        CHECK(GetW(qi) == Approx{ GetW(qe) }.margin(0.001F));
    }
}

TEST_CASE("Maths / Vector / Interpolation")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;
    constexpr float const DeltaT = 0.1F;


    SECTION("Catmull Rom")
    {
        Vector4 const a = Make<Vector4>(-1.0F, +2.0F, +3.0F, -4.0F);
        Vector4 const b = Make<Vector4>(+4.0F, -3.0F, +7.0F, -11.0F);
        Vector4 const c = Make<Vector4>(+1.0F, -1.0F, -3.0F, +5.0F);
        Vector4 const d = Make<Vector4>(+3.0F, +1.0F, -4.0F, -10.0F);

        SECTION("Linear")
        {
            for (float t = 0.0F; t <= 1.0F; t += DeltaT)
            {
                Vector4 const v = CatmullRom(a, b, c, d, t);

                CHECK(GetX(v) == Approx{ CatmullRom(GetX(a), GetX(b), GetX(c), GetX(d), t) });
                CHECK(GetY(v) == Approx{ CatmullRom(GetY(a), GetY(b), GetY(c), GetY(d), t) });
                CHECK(GetZ(v) == Approx{ CatmullRom(GetZ(a), GetZ(b), GetZ(c), GetZ(d), t) });
                CHECK(GetW(v) == Approx{ CatmullRom(GetW(a), GetW(b), GetW(c), GetW(d), t) });
            }
        }

        SECTION("Vectorized")
        {
            for (float x = 0.0F; x <= 1.0F; x += DeltaT)
            {
                for (float y = 0.0F; y <= 1.0F; y += DeltaT)
                {
                    for (float z = 0.0F; z <= 1.0F; z += DeltaT)
                    {
                        for (float w = 0.0F; w <= 1.0F; w += DeltaT)
                        {
                            Vector4 const t = Make<Vector4>(x, y, z, w);
                            Vector4 const v = CatmullRom(a, b, c, d, t);

                            CHECK(GetX(v) == Approx{ CatmullRom(GetX(a), GetX(b), GetX(c), GetX(d), x) });
                            CHECK(GetY(v) == Approx{ CatmullRom(GetY(a), GetY(b), GetY(c), GetY(d), y) });
                            CHECK(GetZ(v) == Approx{ CatmullRom(GetZ(a), GetZ(b), GetZ(c), GetZ(d), z) });
                            CHECK(GetW(v) == Approx{ CatmullRom(GetW(a), GetW(b), GetW(c), GetW(d), w) });
                        }
                    }
                }
            }
        }
    }

    SECTION("Barycentric")
    {
        Vector4 const a = Make<Vector4>(-1.0F, +2.0F, +3.0F, -4.0F);
        Vector4 const b = Make<Vector4>(+4.0F, -3.0F, +7.0F, -11.0F);
        Vector4 const c = Make<Vector4>(+1.0F, -1.0F, -3.0F, 5.0F);

        SECTION("Linear")
        {
            for (float f = 0.0F; f < 1.0F; f += DeltaT)
            {
                for (float g = 0.0F; g < 1.0F; g += DeltaT)
                {
                    Vector4 v = Barycentric(a, b, c, f, g);

                    CHECK(GetX(v) == Approx{ Barycentric(GetX(a), GetX(b), GetX(c), f, g) }.margin(0.0001F));
                    CHECK(GetY(v) == Approx{ Barycentric(GetY(a), GetY(b), GetY(c), f, g) }.margin(0.0001F));
                    CHECK(GetZ(v) == Approx{ Barycentric(GetZ(a), GetZ(b), GetZ(c), f, g) }.margin(0.0001F));
                    CHECK(GetW(v) == Approx{ Barycentric(GetW(a), GetW(b), GetW(c), f, g) }.margin(0.0001F));
                }
            }
        }

        SECTION("Vectorized")
        {
            for (float f = 0.0F; f < 1.0F; f += DeltaT)
            {
                for (float g = 0.0F; g < 1.0F; g += DeltaT)
                {
                    Vector4 tf = Make<Vector4>(f, f * 0.5F, 1.0F - f, 1.0F - (f * 0.5F));
                    Vector4 tg = Make<Vector4>(g, g * 0.5F, 1.0F - g, 1.0F - (g * 0.5F));

                    Vector4 v = Barycentric(a, b, c, tf, tg);

                    CHECK(GetX(v) == Approx{ Barycentric(GetX(a), GetX(b), GetX(c), GetX(tf), GetX(tg)) }.margin(0.0001F));
                    CHECK(GetY(v) == Approx{ Barycentric(GetY(a), GetY(b), GetY(c), GetY(tf), GetY(tg)) }.margin(0.0001F));
                    CHECK(GetZ(v) == Approx{ Barycentric(GetZ(a), GetZ(b), GetZ(c), GetZ(tf), GetZ(tg)) }.margin(0.0001F));
                    CHECK(GetW(v) == Approx{ Barycentric(GetW(a), GetW(b), GetW(c), GetW(tf), GetW(tg)) }.margin(0.0001F));
                }
            }
        }
    }

    SECTION("Hermite")
    {
        Vector4 const a = Make<Vector4>(-2.0F, +2.0F, -1.0F, +1.0F);
        Vector4 const b = Make<Vector4>(+1.0F, +1.0F, -1.0F, +1.0F);
        Vector4 const c = Make<Vector4>(+2.0F, -2.0F, -2.0F, +1.0F);
        Vector4 const d = Make<Vector4>(-1.0F, +1.0F, -1.0F, -1.0F);

        SECTION("Linear")
        {
            for (float t = 0.0F; t <= 1.0F; t += DeltaT)
            {
                Vector4 const v = Hermite(a, b, c, d, t);

                CHECK(GetX(v) == Approx{ Hermite(GetX(a), GetX(b), GetX(c), GetX(d), t) });
                CHECK(GetY(v) == Approx{ Hermite(GetY(a), GetY(b), GetY(c), GetY(d), t) });
                CHECK(GetZ(v) == Approx{ Hermite(GetZ(a), GetZ(b), GetZ(c), GetZ(d), t) });
                CHECK(GetW(v) == Approx{ Hermite(GetW(a), GetW(b), GetW(c), GetW(d), t) });
            }
        }

        SECTION("Vectorized")
        {
            for (float x = 0.0F; x <= 1.0F; x += DeltaT)
            {
                Vector4 const t = Replicate<Vector4>(x);
                Vector4 const v = Hermite(a, b, c, d, t);

                CHECK(GetX(v) == Approx{ Hermite(GetX(a), GetX(b), GetX(c), GetX(d), x) });
                CHECK(GetY(v) == Approx{ Hermite(GetY(a), GetY(b), GetY(c), GetY(d), x) });
                CHECK(GetZ(v) == Approx{ Hermite(GetZ(a), GetZ(b), GetZ(c), GetZ(d), x) });
                CHECK(GetW(v) == Approx{ Hermite(GetW(a), GetW(b), GetW(c), GetW(d), x) });
            }
        }
    }

    SECTION("Lerp")
    {
        Vector4 const a = Make<Vector4>(-1.0F, 2.0F, 3.0F, -4.0F);
        Vector4 const b = Make<Vector4>(3.0F, 1.0F, -4.0F, -10.0F);

        SECTION("Linear")
        {
            for (float t = 0.0F; t <= 1.0F; t += DeltaT)
            {
                Vector4 const v = Lerp(a, b, t);

                CHECK(GetX(v) == Approx{ Lerp(GetX(a), GetX(b), t) });
                CHECK(GetY(v) == Approx{ Lerp(GetY(a), GetY(b), t) });
                CHECK(GetZ(v) == Approx{ Lerp(GetZ(a), GetZ(b), t) });
                CHECK(GetW(v) == Approx{ Lerp(GetW(a), GetW(b), t) });
            }
        }

        SECTION("Vectorized")
        {
            for (float x = 0.0F; x <= 1.0F; x += DeltaT)
            {
                for (float y = 0.0F; y <= 1.0F; y += DeltaT)
                {
                    for (float z = 0.0F; z <= 1.0F; z += DeltaT)
                    {
                        for (float w = 0.0F; w <= 1.0F; w += DeltaT)
                        {
                            Vector4 const t = Make<Vector4>(x, y, z, w);
                            Vector4 const v = Lerp(a, b, t);

                            CHECK(GetX(v) == Approx{ Lerp(GetX(a), GetX(b), x) });
                            CHECK(GetY(v) == Approx{ Lerp(GetY(a), GetY(b), y) });
                            CHECK(GetZ(v) == Approx{ Lerp(GetZ(a), GetZ(b), z) });
                            CHECK(GetW(v) == Approx{ Lerp(GetW(a), GetW(b), w) });
                        }
                    }
                }
            }
        }
    }
}

TEST_CASE("Maths / Vector / Permute")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);
    Vector4 const b = Make<Vector4>(5.0F, 6.0F, 7.0F, 8.0F);

    for (uint32_t x = 0; x < 8; ++x)
    {
        for (uint32_t y = 0; y < 8; ++y)
        {
            for (uint32_t z = 0; z < 8; ++z)
            {
                for (uint32_t w = 0; w < 8; ++w)
                {
                    Vector4 const expected = Make<Vector4>(
                        static_cast<float>(x + 1),
                        static_cast<float>(y + 1),
                        static_cast<float>(z + 1),
                        static_cast<float>(w + 1));

                    Vector4 const permuted = Permute(a, b, x, y, z, w);

                    CHECK(GetX(expected) == GetX(permuted));
                    CHECK(GetY(expected) == GetY(permuted));
                    CHECK(GetZ(expected) == GetZ(permuted));
                    CHECK(GetW(expected) == GetW(permuted));
                }
            }
        }
    }
}

TEST_CASE("Maths / Vector / Swizzle")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);

    for (uint32_t x = 0; x < 4; ++x)
    {
        for (uint32_t y = 0; y < 4; ++y)
        {
            for (uint32_t z = 0; z < 4; ++z)
            {
                for (uint32_t w = 0; w < 4; ++w)
                {
                    Vector4 const expected = Make<Vector4>(
                        static_cast<float>(x + 1),
                        static_cast<float>(y + 1),
                        static_cast<float>(z + 1),
                        static_cast<float>(w + 1));

                    Vector4 const swizzled = Swizzle(a, x, y, z, w);

                    CHECK(GetX(expected) == GetX(swizzled));
                    CHECK(GetY(expected) == GetY(swizzled));
                    CHECK(GetZ(expected) == GetZ(swizzled));
                    CHECK(GetW(expected) == GetW(swizzled));
                }
            }
        }
    }
}

TEST_CASE("Maths / Vector / Compiled swizzles")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Vector4 const a = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);

    SECTION("Generic case")
    {
        CHECK(IsEqual(Swizzle<3, 2, 1, 0>(a), Make<Vector4>(4.0F, 3.0F, 2.0F, 1.0F)));
        CHECK(IsEqual(Swizzle<0, 1, 2, 3>(a), Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F)));
    }

    SECTION("AVX specializations")
    {
        CHECK(IsEqual(Swizzle<0, 1, 0, 1>(a), Make<Vector4>(1.0F, 2.0F, 1.0F, 2.0F)));
        CHECK(IsEqual(Swizzle<2, 3, 2, 3>(a), Make<Vector4>(3.0F, 4.0F, 3.0F, 4.0F)));
        CHECK(IsEqual(Swizzle<0, 0, 1, 1>(a), Make<Vector4>(1.0F, 1.0F, 2.0F, 2.0F)));
        CHECK(IsEqual(Swizzle<2, 2, 3, 3>(a), Make<Vector4>(3.0F, 3.0F, 4.0F, 4.0F)));
        CHECK(IsEqual(Swizzle<0, 0, 2, 2>(a), Make<Vector4>(1.0F, 1.0F, 3.0F, 3.0F)));
        CHECK(IsEqual(Swizzle<1, 1, 3, 3>(a), Make<Vector4>(2.0F, 2.0F, 4.0F, 4.0F)));
    }

    SECTION("AVX2 specializations")
    {
        CHECK(IsEqual(Swizzle<0, 0, 0, 0>(a), Make<Vector4>(1.0F, 1.0F, 1.0F, 1.0F)));
    }
}


TEST_CASE("Maths / Vector / Orthogonal")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Vector2")
    {
        Vector2 const o0 = Make<Vector2>(1.0F, 2.0F);
        CHECK(GetX(o0) == 1.0F);
        CHECK(GetY(o0) == 2.0F);

        Vector2 const o1 = Orthogonal(o0);
        CHECK(GetX(o1) == -2.0F);
        CHECK(GetY(o1) == 1.0F);

        Vector2 const o2 = Orthogonal(o1);
        CHECK(GetX(o2) == -1.0F);
        CHECK(GetY(o2) == -2.0F);

        Vector2 const o3 = Orthogonal(o2);
        CHECK(GetX(o3) == 2.0F);
        CHECK(GetY(o3) == -1.0F);

        Vector2 const o4 = Orthogonal(o3);
        CHECK(GetX(o4) == 1.0F);
        CHECK(GetY(o4) == 2.0F);
    }

    SECTION("Vector4")
    {
        Vector4 const o0 = Make<Vector4>(1.0F, 2.0F, 3.0F, 4.0F);
        CHECK(GetX(o0) == 1.0F);
        CHECK(GetY(o0) == 2.0F);
        CHECK(GetZ(o0) == 3.0F);
        CHECK(GetW(o0) == 4.0F);

        Vector4 const o1 = Orthogonal(o0);
        CHECK(GetX(o1) == 3.0F);
        CHECK(GetY(o1) == 4.0F);
        CHECK(GetZ(o1) == -1.0F);
        CHECK(GetW(o1) == -2.0F);

        Vector4 const o2 = Orthogonal(o1);
        CHECK(GetX(o2) == -1.0F);
        CHECK(GetY(o2) == -2.0F);
        CHECK(GetZ(o2) == -3.0F);
        CHECK(GetW(o2) == -4.0F);

        Vector4 const o3 = Orthogonal(o2);
        CHECK(GetX(o3) == -3.0F);
        CHECK(GetY(o3) == -4.0F);
        CHECK(GetZ(o3) == 1.0F);
        CHECK(GetW(o3) == 2.0F);

        Vector4 const o4 = Orthogonal(o3);
        CHECK(GetX(o4) == 1.0F);
        CHECK(GetY(o4) == 2.0F);
        CHECK(GetZ(o4) == 3.0F);
        CHECK(GetW(o4) == 4.0F);
    }
}


TEST_CASE("Maths / Matrix / Transpose")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Float4x4A const values{ { {
        // clang-format off
        0.0F, 1.0F, 2.0F, 3.0F,
        4.0F, 5.0F, 6.0F, 7.0F,
        8.0F, 9.0F, 10.0F, 11.0F,
        12.0F, 13.0F, 14.0F, 15.0F,
        // clang-format on
    } } };

    Matrix const original   = Load<Matrix>(&values);
    Matrix const transposed = Transpose(original);

    Float4x4A stored{};
    Store(&stored, transposed);

    CHECK(stored.M11 == 0.0F);
    CHECK(stored.M12 == 4.0F);
    CHECK(stored.M13 == 8.0F);
    CHECK(stored.M14 == 12.0F);

    CHECK(stored.M21 == 1.0F);
    CHECK(stored.M22 == 5.0F);
    CHECK(stored.M23 == 9.0F);
    CHECK(stored.M24 == 13.0F);

    CHECK(stored.M31 == 2.0F);
    CHECK(stored.M32 == 6.0F);
    CHECK(stored.M33 == 10.0F);
    CHECK(stored.M34 == 14.0F);

    CHECK(stored.M41 == 3.0F);
    CHECK(stored.M42 == 7.0F);
    CHECK(stored.M43 == 11.0F);
    CHECK(stored.M44 == 15.0F);
}

TEST_CASE("Maths / Matrix / Load-Store")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Float4x4A const mm{ { {
        // clang-format off
        1.0F, 2.0F, 3.0F, 4.0F,
        1.5F, 2.5F, 3.5F, 4.5F,
        2.1F, 3.1F, 4.1F, 5.1F,
        3.2F, 4.3F, 5.4F, 6.5F,
        // clang-format on
    } } };

    Matrix const m = Load<Matrix>(&mm);

    Vector4 r0 = GetBaseX(m);
    Vector4 r1 = GetBaseY(m);
    Vector4 r2 = GetBaseZ(m);
    Vector4 r3 = GetBaseW(m);

    CHECK(GetX(r0) == mm.M11);
    CHECK(GetY(r0) == mm.M12);
    CHECK(GetZ(r0) == mm.M13);
    CHECK(GetW(r0) == mm.M14);

    CHECK(GetX(r1) == mm.M21);
    CHECK(GetY(r1) == mm.M22);
    CHECK(GetZ(r1) == mm.M23);
    CHECK(GetW(r1) == mm.M24);

    CHECK(GetX(r2) == mm.M31);
    CHECK(GetY(r2) == mm.M32);
    CHECK(GetZ(r2) == mm.M33);
    CHECK(GetW(r2) == mm.M34);

    CHECK(GetX(r3) == mm.M41);
    CHECK(GetY(r3) == mm.M42);
    CHECK(GetZ(r3) == mm.M43);
    CHECK(GetW(r3) == mm.M44);

    Matrix const mr = Multiply(Identity<Matrix>(), m);

    r0 = GetBaseX(mr);
    r1 = GetBaseY(mr);
    r2 = GetBaseZ(mr);
    r3 = GetBaseW(mr);

    CHECK_FALSE(IsEqual(r0, r1));

    CHECK(GetX(r0) == mm.M11);
    CHECK(GetY(r0) == mm.M12);
    CHECK(GetZ(r0) == mm.M13);
    CHECK(GetW(r0) == mm.M14);

    CHECK(GetX(r1) == mm.M21);
    CHECK(GetY(r1) == mm.M22);
    CHECK(GetZ(r1) == mm.M23);
    CHECK(GetW(r1) == mm.M24);

    CHECK(GetX(r2) == mm.M31);
    CHECK(GetY(r2) == mm.M32);
    CHECK(GetZ(r2) == mm.M33);
    CHECK(GetW(r2) == mm.M34);

    CHECK(GetX(r3) == mm.M41);
    CHECK(GetY(r3) == mm.M42);
    CHECK(GetZ(r3) == mm.M43);
    CHECK(GetW(r3) == mm.M44);
}

TEST_CASE("Maths / LoadStore")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    Float4A const f1{ 1.0F, 2.0F, 3.0F, 4.0F };
    Vector4 const v1 = Load<Vector4>(&f1);

    CHECK(GetX(v1) == 1.0F);
    CHECK(GetY(v1) == 2.0F);
    CHECK(GetZ(v1) == 3.0F);
    CHECK(GetW(v1) == 4.0F);

    Float3A f2{};
    Store(&f2, v1);

    CHECK(f2.X == 1.0F);
    CHECK(f2.Y == 2.0F);
    CHECK(f2.Z == 3.0F);

    Plane const p1 = Load<Plane>(&f1);
    Float4A f3{};
    Store(&f3, p1);

    CHECK(f3.X == 1.0F);
    CHECK(f3.Y == 2.0F);
}

TEST_CASE("Maths / Vector4 / Cross Product")
{
    using namespace Graphyte;
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

TEST_CASE("Maths / Vector / Rounding")
{
    using namespace Graphyte;
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

    SECTION("Remainder")
    {
        Vector4 const r1 = Remainder(v1, One<Vector4>());
        Vector4 const r2 = Remainder(v2, One<Vector4>());
        Vector4 const r3 = Remainder(v3, One<Vector4>());
        Vector4 const r4 = Remainder(v4, One<Vector4>());

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

        CHECK(Remainder(0.1F, 1.0F) == Approx{ 0.1F });
        CHECK(Remainder(0.4F, 1.0F) == Approx{ 0.4F });
        CHECK(Remainder(0.6F, 1.0F) == Approx{ 0.6F });
        CHECK(Remainder(0.9F, 1.0F) == Approx{ 0.9F });
        CHECK(Remainder(-0.1F, 1.0F) == Approx{ -0.1F });
        CHECK(Remainder(0.5F, 1.0F) == Approx{ 0.5F });
        CHECK(Remainder(-0.5F, 1.0F) == Approx{ -0.5F });
        CHECK(Remainder(-0.9F, 1.0F) == Approx{ -0.9F });
    }
}
#endif
