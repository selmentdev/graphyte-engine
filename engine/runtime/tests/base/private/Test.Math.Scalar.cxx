#include "Test.Base.pch.hxx"
#if false
#include <Graphyte/Maths/Scalar.hxx>

TEST_CASE("Math / Scalar / Fused Multiply Add", "[math]")
{
    namespace math = Graphyte::Maths;

    SECTION("Multiply Add")
    {
        CHECK(math::MultiplyAdd( 2.0F,  3.0F,  4.0F) == Approx( 10.0F));
        CHECK(math::MultiplyAdd(-2.0F,  3.0F,  4.0F) == Approx( -2.0F));
        CHECK(math::MultiplyAdd( 2.0F, -3.0F,  4.0F) == Approx( -2.0F));
        CHECK(math::MultiplyAdd(-2.0F, -3.0F,  4.0F) == Approx( 10.0F));
        CHECK(math::MultiplyAdd( 2.0F,  3.0F, -4.0F) == Approx(  2.0F));
        CHECK(math::MultiplyAdd(-2.0F,  3.0F, -4.0F) == Approx(-10.0F));
        CHECK(math::MultiplyAdd( 2.0F, -3.0F, -4.0F) == Approx(-10.0F));
        CHECK(math::MultiplyAdd(-2.0F, -3.0F, -4.0F) == Approx(  2.0F));
    }

    SECTION("Multiply Sub")
    {
        CHECK(math::MultiplySub( 2.0F,  3.0F,  4.0F) == Approx(  2.0F));
        CHECK(math::MultiplySub(-2.0F,  3.0F,  4.0F) == Approx(-10.0F));
        CHECK(math::MultiplySub( 2.0F, -3.0F,  4.0F) == Approx(-10.0F));
        CHECK(math::MultiplySub(-2.0F, -3.0F,  4.0F) == Approx(  2.0F));
        CHECK(math::MultiplySub( 2.0F,  3.0F, -4.0F) == Approx( 10.0F));
        CHECK(math::MultiplySub(-2.0F,  3.0F, -4.0F) == Approx( -2.0F));
        CHECK(math::MultiplySub( 2.0F, -3.0F, -4.0F) == Approx( -2.0F));
        CHECK(math::MultiplySub(-2.0F, -3.0F, -4.0F) == Approx( 10.0F));
    }

    SECTION("Negative Multiply Add")
    {
        CHECK(math::NegativeMultiplyAdd( 2.0F,  3.0F,  4.0F) == Approx( -2.0F));
        CHECK(math::NegativeMultiplyAdd(-2.0F,  3.0F,  4.0F) == Approx( 10.0F));
        CHECK(math::NegativeMultiplyAdd( 2.0F, -3.0F,  4.0F) == Approx( 10.0F));
        CHECK(math::NegativeMultiplyAdd(-2.0F, -3.0F,  4.0F) == Approx( -2.0F));
        CHECK(math::NegativeMultiplyAdd( 2.0F,  3.0F, -4.0F) == Approx(-10.0F));
        CHECK(math::NegativeMultiplyAdd(-2.0F,  3.0F, -4.0F) == Approx(  2.0F));
        CHECK(math::NegativeMultiplyAdd( 2.0F, -3.0F, -4.0F) == Approx(  2.0F));
        CHECK(math::NegativeMultiplyAdd(-2.0F, -3.0F, -4.0F) == Approx(-10.0F));
    }

    SECTION("Negative Multiply Sub")
    {
        CHECK(math::NegativeMultiplySub( 2.0F,  3.0F,  4.0F) == Approx(-10.0F));
        CHECK(math::NegativeMultiplySub(-2.0F,  3.0F,  4.0F) == Approx(  2.0F));
        CHECK(math::NegativeMultiplySub( 2.0F, -3.0F,  4.0F) == Approx(  2.0F));
        CHECK(math::NegativeMultiplySub(-2.0F, -3.0F,  4.0F) == Approx(-10.0F));
        CHECK(math::NegativeMultiplySub( 2.0F,  3.0F, -4.0F) == Approx( -2.0F));
        CHECK(math::NegativeMultiplySub(-2.0F,  3.0F, -4.0F) == Approx( 10.0F));
        CHECK(math::NegativeMultiplySub( 2.0F, -3.0F, -4.0F) == Approx( 10.0F));
        CHECK(math::NegativeMultiplySub(-2.0F, -3.0F, -4.0F) == Approx( -2.0F));
    }
}

TEST_CASE("Math / Scalar / abs, square, cube and roots", "[math]")
{
    namespace math = Graphyte::Maths;

    SECTION("Abs")
    {
        CHECK(math::Abs( 1.0F) == 1.0F);
        CHECK(math::Abs(-1.0F) == 1.0F);
        CHECK(math::Abs( 0.0F) == 0.0F);
        CHECK(math::Abs(-0.0F) == 0.0F);
    }

    SECTION("Square")
    {
        CHECK(math::Square(-3.0F) == 9.0F);
        CHECK(math::Square(-2.0F) == 4.0F);
        CHECK(math::Square(-1.0F) == 1.0F);
        CHECK(math::Square(-0.0F) == 0.0F);
        CHECK(math::Square( 0.0F) == 0.0F);
        CHECK(math::Square( 1.0F) == 1.0F);
        CHECK(math::Square( 2.0F) == 4.0F);
        CHECK(math::Square( 3.0F) == 9.0F);
    }

    SECTION("Signed Square")
    {
        CHECK(math::SignedSquare(-3.0F) == -9.0F);
        CHECK(math::SignedSquare(-2.0F) == -4.0F);
        CHECK(math::SignedSquare(-1.0F) == -1.0F);
        CHECK(math::SignedSquare(-0.0F) == -0.0F);
        CHECK(math::SignedSquare( 0.0F) ==  0.0F);
        CHECK(math::SignedSquare( 1.0F) ==  1.0F);
        CHECK(math::SignedSquare( 2.0F) ==  4.0F);
        CHECK(math::SignedSquare( 3.0F) ==  9.0F);
    }

    SECTION("Cube")
    {
        CHECK(math::Cube(-3.0F) == -27.0F);
        CHECK(math::Cube(-2.0F) ==  -8.0F);
        CHECK(math::Cube(-1.0F) ==  -1.0F);
        CHECK(math::Cube(-0.0F) ==  -0.0F);
        CHECK(math::Cube( 0.0F) ==   0.0F);
        CHECK(math::Cube( 1.0F) ==   1.0F);
        CHECK(math::Cube( 2.0F) ==   8.0F);
        CHECK(math::Cube( 3.0F) ==  27.0F);
    }
}

TEST_CASE("Math / Scalar / Trigonometric / Asin+Acos+Atan", "[math]")
{
    namespace math = Graphyte::Maths;

    auto value = GENERATE(take(1000, random(0.0F, 1.0F)));

    SECTION("Acos / Asin")
    {
        CHECK(math::Acos(value) == Approx(std::acos(value)).margin(0.00001F));
        CHECK(math::AcosEst(value) == Approx(std::acos(value)).margin(0.001F));

        CHECK(math::Asin(value) == Approx(std::asin(value)).margin(0.00001F));
        CHECK(math::AsinEst(value) == Approx(std::asin(value)).margin(0.001F));

        CHECK(math::Atan(value) == Approx(std::atan(value)));
    }
}

TEST_CASE("Math / Scalar / Trigonometric / Atan2", "[math]")
{
    namespace math = Graphyte::Maths;

    auto x = GENERATE(take(100, random(-1.0F, 1.0F)));

    SECTION("vertical")
    {
        auto y = GENERATE(take(100, random(-1.0F, 1.0F)));

        CHECK(math::Atan2(y, x) == std::atan2(y, x));
    }
}

TEST_CASE("Math / Scalar / Trigonometric / Sin+Cos+Tan", "[math]")
{
    namespace math = Graphyte::Maths;

    auto value = GENERATE(take(1000, random(-math::PI<float>, math::PI<float>)));

    SECTION("Sin / Cos / Tan")
    {
        CAPTURE(value);

        CHECK(math::Cos(value) == Approx(std::cos(value)).margin(0.00001F));
        CHECK(math::CosEst(value) == Approx(std::cos(value)).margin(0.01F));

        CHECK(math::Sin(value) == Approx(std::sin(value)).margin(0.00001F));
        CHECK(math::SinEst(value) == Approx(std::sin(value)).margin(0.01F));

        CHECK(math::Tan(value) == Approx(std::tan(value)));

        {
            float sin_value{};
            float cos_value{};

            math::SinCos(sin_value, cos_value, value);

            CHECK(sin_value == Approx(std::sin(value)).margin(0.00001F));
            CHECK(cos_value == Approx(std::cos(value)).margin(0.00001F));

            math::SinCosEst(sin_value, cos_value, value);

            CHECK(sin_value == Approx(std::sin(value)).margin(0.01F));
            CHECK(cos_value == Approx(std::cos(value)).margin(0.01F));
        }
    }
}

/*
    Acosh
    Asinh
    Atanh
    Cosh
    Sinh
    Tanh
*/

TEST_CASE("Math / Scalar / Float <-> Fixed", "[math]")
{
    namespace math = Graphyte::Maths;

    SECTION("float to fixed")
    {
        CHECK(math::FloatToFixed(-2.0F,   31) == 0x0000'0000U);
        CHECK(math::FloatToFixed(-1.0F,   31) == 0x0000'0000U);
        CHECK(math::FloatToFixed( 0.0F,   31) == 0x0000'0000U);
        CHECK(math::FloatToFixed( 0.1F,   31) == 0x0CCC'CCD0U);
        CHECK(math::FloatToFixed( 0.314F, 31) == 0x2831'2700U);
        CHECK(math::FloatToFixed( 0.5F,   31) == 0x4000'0000U);
        CHECK(math::FloatToFixed( 0.9F,   31) == 0x7333'3300U);
        CHECK(math::FloatToFixed( 1.0F,   31) == 0x7FFF'FFFFU);
        CHECK(math::FloatToFixed( 2.0F,   31) == 0x7FFF'FFFFU);
        
        CHECK(math::FloatToFixed(-2.0F,   27) == 0x0000'0000U);
        CHECK(math::FloatToFixed(-1.0F,   27) == 0x0000'0000U);
        CHECK(math::FloatToFixed( 0.0F,   27) == 0x0000'0000U);
        CHECK(math::FloatToFixed( 0.1F,   27) == 0x00CC'CCCDU);
        CHECK(math::FloatToFixed( 0.314F, 27) == 0x0283'1270U);
        CHECK(math::FloatToFixed( 0.5F,   27) == 0x0400'0000U);
        CHECK(math::FloatToFixed( 0.9F,   27) == 0x0733'3330U);
        CHECK(math::FloatToFixed( 1.0F,   27) == 0x07FF'FFFFU);
        CHECK(math::FloatToFixed( 2.0F,   27) == 0x07FF'FFFFU);
        
        CHECK(math::FloatToFixed(-2.0F,   16) == 0x0000U);
        CHECK(math::FloatToFixed(-1.0F,   16) == 0x0000U);
        CHECK(math::FloatToFixed( 0.0F,   16) == 0x0000U);
        CHECK(math::FloatToFixed( 0.1F,   16) == 0x1999U);
        CHECK(math::FloatToFixed( 0.314F, 16) == 0x5062U);
        CHECK(math::FloatToFixed( 0.5F,   16) == 0x8000U);
        CHECK(math::FloatToFixed( 0.9F,   16) == 0xE666U);
        CHECK(math::FloatToFixed( 1.0F,   16) == 0xFFFFU);
        CHECK(math::FloatToFixed( 2.0F,   16) == 0xFFFFU);
        
        CHECK(math::FloatToFixed(-2.0F,   11) == 0x0000U);
        CHECK(math::FloatToFixed(-1.0F,   11) == 0x0000U);
        CHECK(math::FloatToFixed( 0.0F,   11) == 0x0000U);
        CHECK(math::FloatToFixed( 0.1F,   11) == 0x00ccU);
        CHECK(math::FloatToFixed( 0.314F, 11) == 0x0283U);
        CHECK(math::FloatToFixed( 0.5F,   11) == 0x0400U);
        CHECK(math::FloatToFixed( 0.9F,   11) == 0x0733U);
        CHECK(math::FloatToFixed( 1.0F,   11) == 0x07FFU);
        CHECK(math::FloatToFixed( 2.0F,   11) == 0x07FFU);
        
        CHECK(math::FloatToFixed(-2.0F,   7) == 0x00U);
        CHECK(math::FloatToFixed(-1.0F,   7) == 0x00U);
        CHECK(math::FloatToFixed( 0.0F,   7) == 0x00U);
        CHECK(math::FloatToFixed( 0.1F,   7) == 0x0CU);
        CHECK(math::FloatToFixed( 0.314F, 7) == 0x28U);
        CHECK(math::FloatToFixed( 0.5F,   7) == 0x40U);
        CHECK(math::FloatToFixed( 0.9F,   7) == 0x73U);
        CHECK(math::FloatToFixed( 1.0F,   7) == 0x7FU);
        CHECK(math::FloatToFixed( 2.0F,   7) == 0x7FU);
        
        CHECK(math::FloatToFixed(-2.0F,   4) == 0x0U);
        CHECK(math::FloatToFixed(-1.0F,   4) == 0x0U);
        CHECK(math::FloatToFixed( 0.0F,   4) == 0x0U);
        CHECK(math::FloatToFixed( 0.1F,   4) == 0x1U);
        CHECK(math::FloatToFixed( 0.314F, 4) == 0x5U);
        CHECK(math::FloatToFixed( 0.5F,   4) == 0x8U);
        CHECK(math::FloatToFixed( 0.9F,   4) == 0xEU);
        CHECK(math::FloatToFixed( 1.0F,   4) == 0xFU);
        CHECK(math::FloatToFixed( 2.0F,   4) == 0xFU);
    }

    SECTION("fixed to float")
    {
        CHECK(math::FixedToFloat(0x0000'0000U, 31) == Approx(0.0F));
        CHECK(math::FixedToFloat(0x0CCC'CCD0U, 31) == Approx(0.1F));
        CHECK(math::FixedToFloat(0x2831'2700U, 31) == Approx(0.314F));
        CHECK(math::FixedToFloat(0x4000'0000U, 31) == Approx(0.5F));
        CHECK(math::FixedToFloat(0x7333'3300U, 31) == Approx(0.9F));
        CHECK(math::FixedToFloat(0x7FFF'FFFFU, 31) == Approx(1.0F));
        
        CHECK(math::FixedToFloat(0x0000'0000U, 27) == Approx(0.0F));
        CHECK(math::FixedToFloat(0x00CC'CCCDU, 27) == Approx(0.1F));
        CHECK(math::FixedToFloat(0x0283'1270U, 27) == Approx(0.314F));
        CHECK(math::FixedToFloat(0x0400'0000U, 27) == Approx(0.5F));
        CHECK(math::FixedToFloat(0x0733'3330U, 27) == Approx(0.9F));
        CHECK(math::FixedToFloat(0x07FF'FFFFU, 27) == Approx(1.0F));
        
        CHECK(math::FixedToFloat(0x0000U, 16) == Approx(0.0F));
        CHECK(math::FixedToFloat(0x1999U, 16) == Approx(0.1F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x5062U, 16) == Approx(0.314F));
        CHECK(math::FixedToFloat(0x8000U, 16) == Approx(0.5F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0xE666U, 16) == Approx(0.9F));
        CHECK(math::FixedToFloat(0xFFFFU, 16) == Approx(1.0F));
        
        CHECK(math::FixedToFloat(0x0000U, 11) == Approx(0.0F));
        CHECK(math::FixedToFloat(0x00ccU, 11) == Approx(0.1F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x0283U, 11) == Approx(0.314F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x0400U, 11) == Approx(0.5F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x0733U, 11) == Approx(0.9F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x07FFU, 11) == Approx(1.0F));
        
        CHECK(math::FixedToFloat(0x00U, 7) == Approx(0.0F));
        CHECK(math::FixedToFloat(0x0CU, 7) == Approx(0.095F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x28U, 7) == Approx(0.314F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x40U, 7) == Approx(0.5F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x73U, 7) == Approx(0.9F).epsilon(0.01F));
        CHECK(math::FixedToFloat(0x7FU, 7) == Approx(1.0F));
        
        CHECK(math::FixedToFloat(0x0U, 4) == Approx(0.0F));
        CHECK(math::FixedToFloat(0x1U, 4) == Approx(0.0666667F));
        CHECK(math::FixedToFloat(0x5U, 4) == Approx(0.33333F));
        CHECK(math::FixedToFloat(0x8U, 4) == Approx(0.53333F));
        CHECK(math::FixedToFloat(0xEU, 4) == Approx(0.93333F));
        CHECK(math::FixedToFloat(0xFU, 4) == Approx(1.0F));
    }
}
#endif
