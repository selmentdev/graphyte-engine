#include "Test.Base.pch.hxx"
#if false
#include <Graphyte/Maths/Vector4.hxx>

TEST_CASE("Math / Matrix", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Transpose")
    {
        float4x4a f4x4{
            0.0F, 1.0F, 2.0F, 3.0F,
            4.0F, 5.0F, 6.0F, 7.0F,
            8.0F, 9.0F, 10.0F, 11.0F,
            12.0F, 13.0F, 14.0F, 15.0F,
        };
        float4x4a f4x4t{};
        float4x4a f4x4a{};

        auto m1 = Matrix::Load(&f4x4);
        auto m2 = Matrix::Transpose(m1);

        Matrix::Store(&f4x4t, m2);

        CHECK(f4x4t.M[0][0] == Approx(0.0F));
        CHECK(f4x4t.M[1][0] == Approx(1.0F));
        CHECK(f4x4t.M[2][0] == Approx(2.0F));
        CHECK(f4x4t.M[3][0] == Approx(3.0F));
        CHECK(f4x4t.M[0][1] == Approx(4.0F));
        CHECK(f4x4t.M[1][1] == Approx(5.0F));
        CHECK(f4x4t.M[2][1] == Approx(6.0F));
        CHECK(f4x4t.M[3][1] == Approx(7.0F));
        CHECK(f4x4t.M[0][2] == Approx(8.0F));
        CHECK(f4x4t.M[1][2] == Approx(9.0F));
        CHECK(f4x4t.M[2][2] == Approx(10.0F));
        CHECK(f4x4t.M[3][2] == Approx(11.0F));
        CHECK(f4x4t.M[0][3] == Approx(12.0F));
        CHECK(f4x4t.M[1][3] == Approx(13.0F));
        CHECK(f4x4t.M[2][3] == Approx(14.0F));
        CHECK(f4x4t.M[3][3] == Approx(15.0F));

        auto m3 = Matrix::Transpose(m2);

        Matrix::Store(&f4x4a, m3);

        CHECK(f4x4a.M[0][0] == Approx(f4x4.M[0][0]));
        CHECK(f4x4a.M[0][1] == Approx(f4x4.M[0][1]));
        CHECK(f4x4a.M[0][2] == Approx(f4x4.M[0][2]));
        CHECK(f4x4a.M[0][3] == Approx(f4x4.M[0][3]));
        CHECK(f4x4a.M[1][0] == Approx(f4x4.M[1][0]));
        CHECK(f4x4a.M[1][1] == Approx(f4x4.M[1][1]));
        CHECK(f4x4a.M[1][2] == Approx(f4x4.M[1][2]));
        CHECK(f4x4a.M[1][3] == Approx(f4x4.M[1][3]));
        CHECK(f4x4a.M[2][0] == Approx(f4x4.M[2][0]));
        CHECK(f4x4a.M[2][1] == Approx(f4x4.M[2][1]));
        CHECK(f4x4a.M[2][2] == Approx(f4x4.M[2][2]));
        CHECK(f4x4a.M[2][3] == Approx(f4x4.M[2][3]));
        CHECK(f4x4a.M[3][0] == Approx(f4x4.M[3][0]));
        CHECK(f4x4a.M[3][1] == Approx(f4x4.M[3][1]));
        CHECK(f4x4a.M[3][2] == Approx(f4x4.M[3][2]));
        CHECK(f4x4a.M[3][3] == Approx(f4x4.M[3][3]));
    }

    SECTION("Multiply * Transpose")
    {
        float4x4a f4x4a{
            0.0F, 1.0F, 2.0F, 3.0F,
            4.0F, 5.0F, 6.0F, 7.0F,
            8.0F, 9.0F, 10.0F, 11.0F,
            12.0F, 13.0F, 14.0F, 15.0F,
        };

        float4x4a f4x4b{
            0.0F, 4.0F, 8.0F, 12.0F,
            1.0F, 5.0F, 9.0F, 13.0F,
            2.0F, 6.0F, 10.0F, 14.0F,
            3.0F, 7.0F, 11.0F, 15.0F,
        };

        auto m1 = Matrix::Load(&f4x4a);
        auto m2 = Matrix::Load(&f4x4b);
        auto m3 = Matrix::Multiply(m1, m2);

        float4x4a f4x4_out{};
        Matrix::Store(&f4x4_out, m3);

        CHECK(f4x4_out.M[0][0] == Approx(14.0F));
        CHECK(f4x4_out.M[0][1] == Approx(38.0F));
        CHECK(f4x4_out.M[0][2] == Approx(62.0F));
        CHECK(f4x4_out.M[0][3] == Approx(86.0F));
        CHECK(f4x4_out.M[1][0] == Approx(38.0F));
        CHECK(f4x4_out.M[1][1] == Approx(126.0F));
        CHECK(f4x4_out.M[1][2] == Approx(214.0F));
        CHECK(f4x4_out.M[1][3] == Approx(302.0F));
        CHECK(f4x4_out.M[2][0] == Approx(62.0F));
        CHECK(f4x4_out.M[2][1] == Approx(214.0F));
        CHECK(f4x4_out.M[2][2] == Approx(366.0F));
        CHECK(f4x4_out.M[2][3] == Approx(518.0F));
        CHECK(f4x4_out.M[3][0] == Approx(86.0F));
        CHECK(f4x4_out.M[3][1] == Approx(302.0F));
        CHECK(f4x4_out.M[3][2] == Approx(518.0F));
        CHECK(f4x4_out.M[3][3] == Approx(734.0F));



        auto m4 = Matrix::Transpose(m3);
        float4x4a f4x4tt_out{};
        Matrix::Store(&f4x4tt_out, m4);

        CHECK(f4x4tt_out.M[0][0] == Approx(14.0F));
        CHECK(f4x4tt_out.M[0][1] == Approx(38.0F));
        CHECK(f4x4tt_out.M[0][2] == Approx(62.0F));
        CHECK(f4x4tt_out.M[0][3] == Approx(86.0F));
        CHECK(f4x4tt_out.M[1][0] == Approx(38.0F));
        CHECK(f4x4tt_out.M[1][1] == Approx(126.0F));
        CHECK(f4x4tt_out.M[1][2] == Approx(214.0F));
        CHECK(f4x4tt_out.M[1][3] == Approx(302.0F));
        CHECK(f4x4tt_out.M[2][0] == Approx(62.0F));
        CHECK(f4x4tt_out.M[2][1] == Approx(214.0F));
        CHECK(f4x4tt_out.M[2][2] == Approx(366.0F));
        CHECK(f4x4tt_out.M[2][3] == Approx(518.0F));
        CHECK(f4x4tt_out.M[3][0] == Approx(86.0F));
        CHECK(f4x4tt_out.M[3][1] == Approx(302.0F));
        CHECK(f4x4tt_out.M[3][2] == Approx(518.0F));
        CHECK(f4x4tt_out.M[3][3] == Approx(734.0F));


        auto m5 = Matrix::MultiplyTranspose(m1, m2);

        float4x4a f4x4t_out{};
        Matrix::Store(&f4x4t_out, m5);

        CHECK(f4x4t_out.M[0][0] == Approx(14.0F));
        CHECK(f4x4t_out.M[0][1] == Approx(38.0F));
        CHECK(f4x4t_out.M[0][2] == Approx(62.0F));
        CHECK(f4x4t_out.M[0][3] == Approx(86.0F));
        CHECK(f4x4t_out.M[1][0] == Approx(38.0F));
        CHECK(f4x4t_out.M[1][1] == Approx(126.0F));
        CHECK(f4x4t_out.M[1][2] == Approx(214.0F));
        CHECK(f4x4t_out.M[1][3] == Approx(302.0F));
        CHECK(f4x4t_out.M[2][0] == Approx(62.0F));
        CHECK(f4x4t_out.M[2][1] == Approx(214.0F));
        CHECK(f4x4t_out.M[2][2] == Approx(366.0F));
        CHECK(f4x4t_out.M[2][3] == Approx(518.0F));
        CHECK(f4x4t_out.M[3][0] == Approx(86.0F));
        CHECK(f4x4t_out.M[3][1] == Approx(302.0F));
        CHECK(f4x4t_out.M[3][2] == Approx(518.0F));
        CHECK(f4x4t_out.M[3][3] == Approx(734.0F));
    }


    SECTION("Invertible matrix")
    {
        float4x4a f4x4{
            1.0F, 0.0F, 0.0F, 0.0F,
            0.0F, 0.0F, 1.0F, 0.0F,
            0.0F, 1.0F, 0.0F, 0.0F,
            4.0F, 3.0F, 2.0F, 1.0F,
        };

        auto m1 = Matrix::Load(&f4x4);

        Vector4 determinant{};
        auto m2 = Matrix::Inverse(&determinant, m1);

        CHECK(Vector4::GetX(determinant) == Approx(-1.0F));
        CHECK(Vector4::GetY(determinant) == Approx(-1.0F));
        CHECK(Vector4::GetZ(determinant) == Approx(-1.0F));
        CHECK(Vector4::GetW(determinant) == Approx(-1.0F));

        float4x4a f4x4inv{};
        Matrix::Store(&f4x4inv, m2);

        CHECK(f4x4inv.M[0][0] == Approx(1.0F));
        CHECK(f4x4inv.M[0][1] == Approx(0.0F));
        CHECK(f4x4inv.M[0][2] == Approx(0.0F));
        CHECK(f4x4inv.M[0][3] == Approx(0.0F));
        CHECK(f4x4inv.M[1][0] == Approx(0.0F));
        CHECK(f4x4inv.M[1][1] == Approx(0.0F));
        CHECK(f4x4inv.M[1][2] == Approx(1.0F));
        CHECK(f4x4inv.M[1][3] == Approx(0.0F));
        CHECK(f4x4inv.M[2][0] == Approx(0.0F));
        CHECK(f4x4inv.M[2][1] == Approx(1.0F));
        CHECK(f4x4inv.M[2][2] == Approx(0.0F));
        CHECK(f4x4inv.M[2][3] == Approx(0.0F));
        CHECK(f4x4inv.M[3][0] == Approx(-4.0F));
        CHECK(f4x4inv.M[3][1] == Approx(-2.0F));
        CHECK(f4x4inv.M[3][2] == Approx(-3.0F));
        CHECK(f4x4inv.M[3][3] == Approx(1.0F));

        auto m3 = Matrix::Multiply(m1, m2);

        float4x4a f4x4_out{};
        Matrix::Store(&f4x4_out, m3);

        CHECK(f4x4_out.M[0][0] == Approx(1.0F));
        CHECK(f4x4_out.M[0][1] == Approx(0.0F));
        CHECK(f4x4_out.M[0][2] == Approx(0.0F));
        CHECK(f4x4_out.M[0][3] == Approx(0.0F));
        CHECK(f4x4_out.M[1][0] == Approx(0.0F));
        CHECK(f4x4_out.M[1][1] == Approx(1.0F));
        CHECK(f4x4_out.M[1][2] == Approx(0.0F));
        CHECK(f4x4_out.M[1][3] == Approx(0.0F));
        CHECK(f4x4_out.M[2][0] == Approx(0.0F));
        CHECK(f4x4_out.M[2][1] == Approx(0.0F));
        CHECK(f4x4_out.M[2][2] == Approx(1.0F));
        CHECK(f4x4_out.M[2][3] == Approx(0.0F));
        CHECK(f4x4_out.M[3][0] == Approx(0.0F));
        CHECK(f4x4_out.M[3][1] == Approx(0.0F));
        CHECK(f4x4_out.M[3][2] == Approx(0.0F));
        CHECK(f4x4_out.M[3][3] == Approx(1.0F));

        CHECK(Matrix::IsIdentity(m3));
    }
}
#endif
