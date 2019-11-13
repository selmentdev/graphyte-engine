#include "Test.Base.pch.hxx"
#if false
#include <Graphyte/Maths/Vector3.hxx>

#include <random>

TEST_CASE("Math / Vector3 / Common functions", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Comparison")
    {
        auto v1 = Vector3::Make(0.0F, 1.0F, 2.0F);
        auto v2 = Vector3::Make(1.0F, 2.0F, 3.0F);
        auto v3 = Vector3::Make(-1.0F, 0.0F, 1.0F);
        auto v4 = Vector3::Make(0.001F, 1.001F, 2.001F);

        // Checking equal
        CHECK(Vector3::IsEqual(v1, v1));
        CHECK(!Vector3::IsEqual(v1, v2));
        CHECK(!Vector3::IsEqual(v1, v3));
        CHECK(Vector3::IsEqual(v1, v4, Vector4::Make(0.005F)));

        // Checking not equal
        CHECK(!Vector3::IsNotEqual(v1, v1));
        CHECK(Vector3::IsNotEqual(v1, v2));
        CHECK(Vector3::IsNotEqual(v1, v3));
        CHECK(Vector3::IsNotEqual(v1, v4));

        // Checking greater
        CHECK(!Vector3::IsGreater(v1, v1));
        CHECK(!Vector3::IsGreater(v1, v2));
        CHECK(Vector3::IsGreater(v1, v3));
        CHECK(!Vector3::IsGreater(v1, v4));

        // Checking greater equal
        CHECK(Vector3::IsGreaterEqual(v1, v1));
        CHECK(!Vector3::IsGreaterEqual(v1, v2));
        CHECK(Vector3::IsGreaterEqual(v1, v3));
        CHECK(!Vector3::IsGreaterEqual(v1, v4));

        // Checking less
        CHECK(!Vector3::IsLess(v1, v1));
        CHECK(Vector3::IsLess(v1, v2));
        CHECK(!Vector3::IsLess(v1, v3));
        CHECK(Vector3::IsLess(v1, v4));

        // Checking less equal
        CHECK(Vector3::IsLessEqual(v1, v1));
        CHECK(Vector3::IsLessEqual(v1, v2));
        CHECK(!Vector3::IsLessEqual(v1, v3));
        CHECK(Vector3::IsLessEqual(v1, v4));

        // Checking in bounds
        CHECK(Vector3::InBounds(v1, v1));
        CHECK(Vector3::InBounds(v1, v2));
        CHECK(!Vector3::InBounds(v1, v3));
        CHECK(Vector3::InBounds(v1, v4));
    }

    SECTION("Compare UInts")
    {
        auto v1 = Vector3::MakeUInt(0xFFFF'FFFF, 0xFFFF'FFFF, 0xFFFF'FFFF);
        auto v2 = Vector3::MakeUInt(0xFFFF'FFFF, 0xFFFF'FFFF, 0x0000'0000);
        auto v3 = Vector3::MakeUInt(0x0000'0000, 0x0000'0000, 0x0000'0000);

        CHECK(Vector3::IsEqualUInt(v1, v1));
        CHECK(!Vector3::IsEqualUInt(v1, v2));
        CHECK(!Vector3::IsEqualUInt(v1, v3));
        CHECK(!Vector3::IsEqualUInt(v2, v3));

        CHECK(!Vector3::IsNotEqualUInt(v1, v1));
        CHECK(Vector3::IsNotEqualUInt(v1, v2));
        CHECK(Vector3::IsNotEqualUInt(v1, v3));
        CHECK(Vector3::IsNotEqualUInt(v2, v3));
    }

    SECTION("Checking nan / inf")
    {
        auto vnan_all = Vector3::Make(std::numeric_limits<float>::quiet_NaN());
        auto vnan_single = Vector3::Make(std::numeric_limits<float>::quiet_NaN(), 0.0F, 0.0F);

        CHECK(Vector3::IsNaN(vnan_all));
        CHECK(Vector3::IsNaN(vnan_single));

        auto vinf_all = Vector3::Make(std::numeric_limits<float>::infinity());
        auto vinf_single = Vector3::Make(std::numeric_limits<float>::infinity(), 0.0F, 0.0F);

        CHECK(Vector3::IsInfinite(vinf_all));
        CHECK(Vector3::IsInfinite(vinf_single));
    }

    SECTION("Vector3 specific functions")
    {
        auto v_one = Vector3::One();
        auto v_zero = Vector3::Zero();
        auto v_inf = Vector3::Infinity();
        auto v_nan = Vector3::NaN();
        auto v_unit_x = Vector3::UnitX();
        auto v_unit_y = Vector3::UnitY();
        auto v_unit_z = Vector3::UnitZ();
        auto v_two = Vector3::Make(2.0F, 0.0F, 0.0F);

        std::ranlux48 generator{ 0xdeadc0dedeadbeef };
        std::uniform_real_distribution<float> sampler{};

        std::uniform_real_distribution<float>::param_type range_small{ 0.0001F, 1.0F };
        std::uniform_real_distribution<float>::param_type range_large{ 1.0F, 10.0F };


        SECTION("Dot product")
        {
            auto v_d_1 = Vector3::Dot(v_one, v_one);

            CHECK(Vector4::GetX(v_d_1) == Approx(3.0F));

            auto v_d_2 = Vector3::Dot(v_one, v_zero);

            CHECK(Vector4::GetX(v_d_2) == Approx(0.0F));

            auto v_d_z_xy = Vector3::Dot(v_unit_x, v_unit_y);

            CHECK(Vector4::GetX(v_d_z_xy) == Approx(0.0F));

            auto v_d_z_xz = Vector3::Dot(v_unit_x, v_unit_z);

            CHECK(Vector4::GetX(v_d_z_xz) == Approx(0.0F));

            auto v_d_z_yz = Vector3::Dot(v_unit_y, v_unit_z);

            CHECK(Vector4::GetX(v_d_z_yz) == Approx(0.0F));

            auto v_d_z_yy = Vector3::Dot(v_unit_y, v_unit_y);

            CHECK(Vector4::GetX(v_d_z_yy) == Approx(1.0F));

            auto v_d_inf = Vector3::Dot(v_inf, v_one);

            CHECK(std::isinf(Vector4::GetX(v_d_inf)));
        }

        SECTION("Cross product")
        {
            auto v_x_1_2 = Vector3::Cross(v_one, v_two);

            CHECK(Vector4::GetX({ v_x_1_2.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_1_2.V }) == Approx(2.0F));
            CHECK(Vector4::GetZ({ v_x_1_2.V }) == Approx(-2.0F));

            auto v_x_1_1 = Vector3::Cross(v_one, v_one);

            CHECK(Vector4::GetX({ v_x_1_1.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_1_1.V }) == Approx(0.0F));
            CHECK(Vector4::GetZ({ v_x_1_1.V }) == Approx(0.0F));

            auto v_x_1_0 = Vector3::Cross(v_one, v_zero);

            CHECK(Vector4::GetX({ v_x_1_0.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_1_0.V }) == Approx(0.0F));
            CHECK(Vector4::GetZ({ v_x_1_0.V }) == Approx(0.0F));

            auto v_x_xx = Vector3::Cross(v_unit_x, v_unit_x);

            CHECK(Vector4::GetX({ v_x_xx.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_xx.V }) == Approx(0.0F));
            CHECK(Vector4::GetZ({ v_x_xx.V }) == Approx(0.0F));

            auto v_x_xy = Vector3::Cross(v_unit_x, v_unit_y);

            CHECK(Vector4::GetX({ v_x_xy.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_xy.V }) == Approx(0.0F));
            CHECK(Vector4::GetZ({ v_x_xy.V }) == Approx(1.0F));

            auto v_x_xz = Vector3::Cross(v_unit_x, v_unit_z);

            CHECK(Vector4::GetX({ v_x_xz.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_xz.V }) == Approx(-1.0F));
            CHECK(Vector4::GetZ({ v_x_xz.V }) == Approx(0.0F));

            auto v_x_zx = Vector3::Cross(v_unit_z, v_unit_x);

            CHECK(Vector4::GetX({ v_x_zx.V }) == Approx(0.0F));
            CHECK(Vector4::GetY({ v_x_zx.V }) == Approx(1.0F));
            CHECK(Vector4::GetZ({ v_x_zx.V }) == Approx(0.0F));

            auto v_x_yz = Vector3::Cross(v_unit_y, v_unit_z);

            CHECK(Vector4::GetX({ v_x_yz.V }) == Approx(1.0F));
            CHECK(Vector4::GetY({ v_x_yz.V }) == Approx(0.0F));
            CHECK(Vector4::GetZ({ v_x_yz.V }) == Approx(0.0F));

            auto v_x_inf_x = Vector3::Cross(v_inf, v_unit_x);

            CHECK(std::isnan(Vector4::GetX({ v_x_inf_x.V })));
            CHECK(std::isnan(Vector4::GetY({ v_x_inf_x.V })));
            CHECK(std::isnan(Vector4::GetZ({ v_x_inf_x.V })));

            auto v_x_nan_x = Vector3::Cross(v_nan, v_unit_x);

            CHECK(std::isnan(Vector4::GetX({ v_x_nan_x.V })));
            CHECK(std::isnan(Vector4::GetY({ v_x_nan_x.V })));
            CHECK(std::isnan(Vector4::GetZ({ v_x_nan_x.V })));
        }

        SECTION("Length")
        {
            CHECK(Vector4::GetX(Vector3::LengthSquared(v_one)) == Approx(3.0F));
            CHECK(Vector4::GetX(Vector3::LengthSquared(v_unit_x)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::LengthSquared(v_unit_z)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::LengthSquared(v_two)) == Approx(4.0F));
            CHECK(std::isnan(Vector4::GetX(Vector3::LengthSquared(v_nan))));
            CHECK(std::isinf(Vector4::GetX(Vector3::LengthSquared(v_inf))));

            CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v_one)) == Approx(0.57735F).epsilon(0.001F));
            CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v_unit_x)) == Approx(1.0F).epsilon(0.001F));
            CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v_unit_z)) == Approx(1.0F).epsilon(0.001F));
            CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v_two)) == Approx(0.5F).epsilon(0.001F));
            CHECK(std::isnan(Vector4::GetX(Vector3::ReciprocalLengthEst(v_nan))));
            CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v_inf)) == Approx(0.0F));

            CHECK(Vector4::GetX(Vector3::ReciprocalLength(v_one)) == Approx(0.57735F));
            CHECK(Vector4::GetX(Vector3::ReciprocalLength(v_unit_x)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::ReciprocalLength(v_unit_z)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::ReciprocalLength(v_two)) == Approx(0.5F));
            CHECK(std::isnan(Vector4::GetX(Vector3::ReciprocalLength(v_nan))));
            CHECK(Vector4::GetX(Vector3::ReciprocalLength(v_inf)) == Approx(0.0F));

            CHECK(Vector4::GetX(Vector3::LengthEst(v_one)) == Approx(1.73205F));
            CHECK(Vector4::GetX(Vector3::LengthEst(v_unit_x)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::LengthEst(v_unit_z)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::LengthEst(v_two)) == Approx(2.0F));
            CHECK(std::isnan(Vector4::GetX(Vector3::LengthEst(v_nan))));
            CHECK(std::isinf(Vector4::GetX(Vector3::LengthEst(v_inf))));

            CHECK(Vector4::GetX(Vector3::Length(v_one)) == Approx(1.73205F));
            CHECK(Vector4::GetX(Vector3::Length(v_unit_x)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::Length(v_unit_z)) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector3::Length(v_two)) == Approx(2.0F));
            CHECK(std::isnan(Vector4::GetX(Vector3::Length(v_nan))));
            CHECK(std::isinf(Vector4::GetX(Vector3::Length(v_inf))));

            for (size_t i = 0; i < 50; ++i)
            {
                auto f_pl = sampler(generator, range_large);
                auto f_ps = sampler(generator, range_small);
                auto f_nl = -sampler(generator, range_large);
                auto f_ns = -sampler(generator, range_small);

                auto v1 = Vector3::Make(f_pl, f_ps, f_nl);
                auto v2 = Vector3::Make(f_ps, f_nl, f_ns);

                CHECK(Vector4::GetX(Vector3::LengthSquared(v1)) == Approx(
                    f_pl * f_pl + f_ps * f_ps + f_nl * f_nl
                ));
                CHECK(Vector4::GetX(Vector3::LengthSquared(v2)) == Approx(
                    f_ps * f_ps + f_nl * f_nl + f_ns * f_ns
                ));

                CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v1)) == Approx(
                    1.0F / sqrtf(f_pl * f_pl + f_ps * f_ps + f_nl * f_nl)
                ).epsilon(0.001F));
                CHECK(Vector4::GetX(Vector3::ReciprocalLengthEst(v2)) == Approx(
                    1.0F / sqrtf(f_ps * f_ps + f_nl * f_nl + f_ns * f_ns)
                ).epsilon(0.001F));

                CHECK(Vector4::GetX(Vector3::ReciprocalLength(v1)) == Approx(
                    1.0F / sqrtf(f_pl * f_pl + f_ps * f_ps + f_nl * f_nl)
                ));
                CHECK(Vector4::GetX(Vector3::ReciprocalLength(v2)) == Approx(
                    1.0F / sqrtf(f_ps * f_ps + f_nl * f_nl + f_ns * f_ns)
                ));

                CHECK(Vector4::GetX(Vector3::LengthEst(v1)) == Approx(
                    sqrtf(f_pl * f_pl + f_ps * f_ps + f_nl * f_nl)
                ));
                CHECK(Vector4::GetX(Vector3::LengthEst(v2)) == Approx(
                    sqrtf(f_ps * f_ps + f_nl * f_nl + f_ns * f_ns)
                ));

                CHECK(Vector4::GetX(Vector3::Length(v1)) == Approx(
                    sqrtf(f_pl * f_pl + f_ps * f_ps + f_nl * f_nl)
                ));
                CHECK(Vector4::GetX(Vector3::Length(v2)) == Approx(
                    sqrtf(f_ps * f_ps + f_nl * f_nl + f_ns * f_ns)
                ));
            }
        }

        SECTION("Normalization")
        {
            SECTION("Normalize")
            {
                auto n_zero = Vector3::Normalize(v_zero);
                CHECK(Vector4::GetX({ n_zero.V }) == Approx(0.0F));
                CHECK(Vector4::GetY({ n_zero.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_zero.V }) == Approx(0.0F));
                CHECK(Vector4::GetW({ n_zero.V }) == Approx(0.0F));

                auto n_one = Vector3::Normalize(v_one);
                CHECK(Vector4::GetX({ n_one.V }) == Approx(0.577350259F));
                CHECK(Vector4::GetY({ n_one.V }) == Approx(0.577350259F));
                CHECK(Vector4::GetZ({ n_one.V }) == Approx(0.577350259F));
                CHECK(Vector4::GetW({ n_one.V }) == Approx(0.577350259F));

                auto n_unit_x = Vector3::Normalize(v_unit_x);
                CHECK(Vector4::GetX({ n_unit_x.V }) == Approx(1.0F));
                CHECK(Vector4::GetY({ n_unit_x.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_unit_x.V }) == Approx(0.0F));
                CHECK(Vector4::GetW({ n_unit_x.V }) == Approx(0.0F));

                auto n_unit_z = Vector3::Normalize(v_unit_z);
                CHECK(Vector4::GetX({ n_unit_z.V }) == Approx(0.0F));
                CHECK(Vector4::GetY({ n_unit_z.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_unit_z.V }) == Approx(1.0F));
                CHECK(Vector4::GetW({ n_unit_z.V }) == Approx(0.0F));

                auto n_two = Vector3::Normalize(v_two);
                CHECK(Vector4::GetX({ n_two.V }) == Approx(1.0F));
                CHECK(Vector4::GetY({ n_two.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_two.V }) == Approx(0.0F));
                CHECK(Vector4::GetW({ n_two.V }) == Approx(0.0F));

                auto n_nan = Vector3::Normalize(v_nan);
                CHECK(std::isnan(Vector4::GetX({ n_nan.V })));
                CHECK(std::isnan(Vector4::GetY({ n_nan.V })));
                CHECK(std::isnan(Vector4::GetZ({ n_nan.V })));
                CHECK(std::isnan(Vector4::GetW({ n_nan.V })));

                auto n_inf = Vector3::Normalize(v_inf);
                CHECK(std::isnan(Vector4::GetX({ n_inf.V })));
                CHECK(std::isnan(Vector4::GetY({ n_inf.V })));
                CHECK(std::isnan(Vector4::GetZ({ n_inf.V })));
                CHECK(std::isnan(Vector4::GetW({ n_inf.V })));


                for (size_t i = 0; i < 50; ++i)
                {
                    auto f_pl = sampler(generator, range_large);
                    auto f_ps = sampler(generator, range_small);
                    auto f_nl = -sampler(generator, range_large);
                    auto f_ns = -sampler(generator, range_small);

                    auto v1 = Vector3::Make(f_pl, f_ps, f_nl);
                    auto v2 = Vector3::Make(f_ps, f_nl, f_ns);

                    auto n1 = Vector3::Normalize(v1);
                    auto n2 = Vector3::Normalize(v2);

                    auto f_len1 = sqrtf(f_pl * f_pl + f_ps * f_ps + f_nl * f_nl);
                    auto f_len2 = sqrtf(f_ps * f_ps + f_nl * f_nl + f_ns * f_ns);

                    CHECK(Vector4::GetX({ n1.V }) == Approx(f_pl / f_len1));
                    CHECK(Vector4::GetY({ n1.V }) == Approx(f_ps / f_len1));
                    CHECK(Vector4::GetZ({ n1.V }) == Approx(f_nl / f_len1));

                    CHECK(Vector4::GetX({ n2.V }) == Approx(f_ps / f_len2));
                    CHECK(Vector4::GetY({ n2.V }) == Approx(f_nl / f_len2));
                    CHECK(Vector4::GetZ({ n2.V }) == Approx(f_ns / f_len2));
                }
            }

            SECTION("NormalizeEst")
            {
                auto n_zero = Vector3::NormalizeEst(v_zero);
#if false
                CHECK(Vector4::GetX({ n_zero.V }) == Approx(0.0F));
                CHECK(Vector4::GetY({ n_zero.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_zero.V }) == Approx(0.0F));
                CHECK(Vector4::GetW({ n_zero.V }) == Approx(0.0F));
#else
                CHECK(std::isnan(Vector4::GetX({ n_zero.V })));
                CHECK(std::isnan(Vector4::GetY({ n_zero.V })));
                CHECK(std::isnan(Vector4::GetZ({ n_zero.V })));
                CHECK(std::isnan(Vector4::GetW({ n_zero.V })));
#endif

                auto n_one = Vector3::NormalizeEst(v_one);
                CHECK(Vector4::GetX({ n_one.V }) == Approx(0.577350259F).epsilon(0.001F));
                CHECK(Vector4::GetY({ n_one.V }) == Approx(0.577350259F).epsilon(0.001F));
                CHECK(Vector4::GetZ({ n_one.V }) == Approx(0.577350259F).epsilon(0.001F));
                CHECK(Vector4::GetW({ n_one.V }) == Approx(0.577350259F).epsilon(0.001F));

                auto n_unit_x = Vector3::NormalizeEst(v_unit_x);
                CHECK(Vector4::GetX({ n_unit_x.V }) == Approx(1.0F).epsilon(0.001F));
                CHECK(Vector4::GetY({ n_unit_x.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_unit_x.V }) == Approx(0.0F));
                CHECK(Vector4::GetW({ n_unit_x.V }) == Approx(0.0F));

                auto n_unit_z = Vector3::NormalizeEst(v_unit_z);
                CHECK(Vector4::GetX({ n_unit_z.V }) == Approx(0.0F));
                CHECK(Vector4::GetY({ n_unit_z.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_unit_z.V }) == Approx(1.0F).epsilon(0.001F));
                CHECK(Vector4::GetW({ n_unit_z.V }) == Approx(0.0F));

                auto n_two = Vector3::NormalizeEst(v_two);
                CHECK(Vector4::GetX({ n_two.V }) == Approx(1.0F).epsilon(0.001F));
                CHECK(Vector4::GetY({ n_two.V }) == Approx(0.0F));
                CHECK(Vector4::GetZ({ n_two.V }) == Approx(0.0F));
                CHECK(Vector4::GetW({ n_two.V }) == Approx(0.0F));

                auto n_nan = Vector3::NormalizeEst(v_nan);
                CHECK(std::isnan(Vector4::GetX({ n_nan.V })));
                CHECK(std::isnan(Vector4::GetY({ n_nan.V })));
                CHECK(std::isnan(Vector4::GetZ({ n_nan.V })));
                CHECK(std::isnan(Vector4::GetW({ n_nan.V })));

                auto n_inf = Vector3::NormalizeEst(v_inf);
                CHECK(std::isnan(Vector4::GetX({ n_inf.V })));
                CHECK(std::isnan(Vector4::GetY({ n_inf.V })));
                CHECK(std::isnan(Vector4::GetZ({ n_inf.V })));
                CHECK(std::isnan(Vector4::GetW({ n_inf.V })));


                for (size_t i = 0; i < 50; ++i)
                {
                    auto f_pl = sampler(generator, range_large);
                    auto f_ps = sampler(generator, range_small);
                    auto f_nl = -sampler(generator, range_large);
                    auto f_ns = -sampler(generator, range_small);

                    auto v1 = Vector3::Make(f_pl, f_ps, f_nl);
                    auto v2 = Vector3::Make(f_ps, f_nl, f_ns);

                    auto n1 = Vector3::NormalizeEst(v1);
                    auto n2 = Vector3::NormalizeEst(v2);

                    auto f_len1 = sqrtf(f_pl * f_pl + f_ps * f_ps + f_nl * f_nl);
                    auto f_len2 = sqrtf(f_ps * f_ps + f_nl * f_nl + f_ns * f_ns);

                    CHECK(Vector4::GetX({ n1.V }) == Approx(f_pl / f_len1).epsilon(0.001F));
                    CHECK(Vector4::GetY({ n1.V }) == Approx(f_ps / f_len1).epsilon(0.001F));
                    CHECK(Vector4::GetZ({ n1.V }) == Approx(f_nl / f_len1).epsilon(0.001F));

                    CHECK(Vector4::GetX({ n2.V }) == Approx(f_ps / f_len2).epsilon(0.001F));
                    CHECK(Vector4::GetY({ n2.V }) == Approx(f_nl / f_len2).epsilon(0.001F));
                    CHECK(Vector4::GetZ({ n2.V }) == Approx(f_ns / f_len2).epsilon(0.001F));
                }
            }
        }
    }
}
#endif
