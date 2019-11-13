#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Maths/Constants.hxx>

namespace Graphyte::Maths
{
    template <typename T> mathinline T mathcall MultiplyAdd(T a, T b, T c) noexcept
    {
        return (a * b) + c;
    }
    template <typename T> mathinline T mathcall MultiplySub(T a, T b, T c) noexcept
    {
        return (a * b) - c;
    }
    template <typename T> mathinline T mathcall NegativeMultiplyAdd(T a, T b, T c) noexcept
    {
        return -(a * b) + c;
    }
    template <typename T> mathinline T mathcall NegativeMultiplySub(T a, T b, T c) noexcept
    {
        return -(a * b) - c;
    }
}

namespace Graphyte::Maths
{
    mathinline float mathcall Abs(float value) noexcept
    {
        return std::abs(value);
    }
    mathinline float mathcall Square(float value) noexcept
    {
        return value * value;
    }
    mathinline float mathcall SignedSquare(float value) noexcept
    {
        return value * std::abs(value);
    }
    mathinline float mathcall Cube(float value) noexcept
    {
        return value * value * value;
    }
    mathinline float mathcall Sqrt(float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS && GRAPHYTE_HW_AVX
        auto s = _mm_sqrt_ss(_mm_set_ss(value));
        float result;
        _mm_store_ss(&result, s);
        return result;
#else
        return std::sqrt(value);
#endif
    }
    mathinline float mathcall SqrtEst(float value) noexcept
    {
#if GRAPHYTE_HW_AVX
        auto s = _mm_rcp_ss(_mm_rsqrt_ss(_mm_set_ss(value)));
        float result;
        _mm_store_ss(&result, s);
        return result;
#else
        return std::sqrt(value);
#endif
    }
    mathinline float mathcall Rsqrt(float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS && GRAPHYTE_HW_AVX
        auto r = _mm_set_ss(value);
        r = _mm_rsqrt_ss(r);
        float result;
        _mm_store_ss(&result, r);
        return result;
#else
        return 1.0F / std::sqrt(value);
#endif
    }
    mathinline float mathcall RsqrtEst(float value) noexcept
    {
#if GRAPHYTE_HW_AVX
        auto r = _mm_set_ss(value);
        r = _mm_rsqrt_ss(r);
        float result;
        _mm_store_ss(&result, r);
        return result;
#else
        return 1.0F / std::sqrt(value);
#endif
    }
    mathinline float mathcall Cbrt(float value) noexcept
    {
        return std::cbrt(value);
    }
    mathinline float mathcall Rcbrt(float value) noexcept
    {
        return 1.0F / std::cbrt(value);
    }
    mathinline float mathcall Ceil(float value) noexcept
    {
        return std::ceil(value);
    }
    mathinline float mathcall Floor(float value) noexcept
    {
        return std::floor(value);
    }
    mathinline int mathcall FastFloor(float value) noexcept
    {
        return (value > 0.0F)
            ? static_cast<int>(value)
            : (static_cast<int>(value) - 1);
    }
    mathinline float mathcall Truncate(float value) noexcept
    {
        return std::trunc(value);
    }
    mathinline float mathcall Round(float value) noexcept
    {
        return std::round(value);
    }
    mathinline float mathcall RoundToNearest(float value) noexcept
    {
        const auto i = Maths::Floor(value);
        value -= i;

        if (value < 0.5F)
        {
            return i;
        }

        if (value > 0.5F)
        {
            return i + 1.0F;
        }

        float int_part;

        (void)modff(i / 2.0F, &int_part);

        if ((2.0F * int_part) == i)
        {
            return i;
        }

        return i + 1.0F;
    }
    mathinline float mathcall Frac(float value) noexcept
    {
        return value - Floor(value);
    }
    mathinline float mathcall Modulo(float a, float b) noexcept
    {
        return std::fmod(a, b);
    }
    mathinline int32_t mathcall CeilI32(float value) noexcept
    {
        return -(static_cast<int32_t>(-0.5F - (value + value)) >> 1);
    }
    mathinline float mathcall CeilF32(float value) noexcept
    {
        return static_cast<float>(CeilI32(value));
    }
    mathinline int32_t mathcall FloorI32(float value) noexcept
    {
        return static_cast<int32_t>(value + value - 0.5F) >> 1;
    }
    mathinline float mathcall FloorF32(float value) noexcept
    {
        return static_cast<float>(FloorI32(value));
    }
    mathinline int32_t mathcall TruncateI32(float value) noexcept
    {
        return static_cast<int32_t>(value);
    }
    mathinline float mathcall TruncateF32(float value) noexcept
    {
        return static_cast<float>(TruncateI32(value));
    }
    mathinline int32_t mathcall RoundI32(float value) noexcept
    {
        return static_cast<int32_t>(value + value + 0.5F) >> 1;
    }
    mathinline float mathcall RoundF32(float value) noexcept
    {
        return static_cast<float>(RoundI32(value));
    }
    mathinline float mathcall Pow(float x, float y) noexcept
    {
        return std::pow(x, y);
    }
    mathinline float mathcall Pow(float x, int y) noexcept
    {
        return std::pow(x, static_cast<float>(y));
    }
    mathinline float mathcall Exp(float value) noexcept
    {
        return std::exp(value);
    }
    mathinline float mathcall Exp2(float value) noexcept
    {
        return std::pow(2.0F, value);
    }
    mathinline float mathcall Log(float base, float value) noexcept
    {
        return std::log(value) / std::log(base);
    }
    mathinline float mathcall Log(float value) noexcept
    {
        return std::log(value);
    }
    mathinline float mathcall Log2(float value) noexcept
    {
        return std::log2(value);
    }
    mathinline float mathcall Log10(float value) noexcept
    {
        return std::log10(value);
    }
    mathinline float mathcall Sign(float value) noexcept
    {
        return (value >= 0.0F)
            ? 1.0F
            : -1.0F;
    }
    mathinline float mathcall CopySign(float value, float sign) noexcept
    {
        return std::copysign(value, sign);
    }
    mathinline float mathcall NearbyInt(float value) noexcept
    {
        return std::nearbyint(value);
    }
    mathinline float mathcall NextToward(float value, float to) noexcept
    {
        return std::nexttoward(value, static_cast<long double>(to));
    }
    mathinline float mathcall NextAfter(float value, float to) noexcept
    {
        return std::nextafter(value, to);
    }
    mathinline float mathcall Min(float a, float b) noexcept
    {
        return b < a
            ? b
            : a;
    }
    mathinline float mathcall Max(float a, float b) noexcept
    {
        return a < b
            ? b
            : a;
    }
    mathinline float mathcall Min(float a, float b, float c) noexcept
    {
        return Min(Min(a, b), c);
    }
    mathinline float mathcall Max(float a, float b, float c) noexcept
    {
        return Max(Max(a, b), c);
    }
    mathinline float mathcall Min(float a, float b, float c, float d) noexcept
    {
        return Min(Min(Min(a, b), c), d);
    }
    mathinline float mathcall Max(float a, float b, float c, float d) noexcept
    {
        return Max(Max(Max(a, b), c), d);
    }
    mathinline float mathcall Select(float comperand, float above_or_zero, float below_zero) noexcept
    {
        return comperand >= 0.0F
            ? above_or_zero
            : below_zero;
    }
    mathinline float mathcall Clamp(float value, float min, float max) noexcept
    {
        return Min(Max(value, min), max);
    }
    mathinline float mathcall ClampRoll(float value, float min, float max) noexcept
    {
        if (value > max)
        {
            return min;
        }
        else if (value < min)
        {
            return max;
        }

        return value;
    }
    mathinline float mathcall Wrap(float value, float min, float max) noexcept
    {
        const auto range = max - min;
        const auto progress = value - min;
        return min + progress - (range * Floor(progress / range));
    }
    mathinline float mathcall Saturate(float value) noexcept
    {
        return Clamp(value, 0.0F, 1.0F);
    }
    mathinline float mathcall Reciprocal(float value) noexcept
    {
        return 1.0F / value;
    }
    mathinline float mathcall Acos(float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS
        const auto positive = (value >= 0.0F);
        const auto x = Abs(value);
        auto mx = Max(1.0F - x, 0.0F);

        if (mx < 0.0F)
        {
            mx = 0.0F;
        }

        const auto root = Maths::Sqrt(mx);

        const auto temp1 = MultiplyAdd(-0.0012624911F, x, 0.0066700901F);
        const auto temp2 = MultiplySub(temp1, x, 0.0170881256F);
        const auto temp3 = MultiplyAdd(temp2, x, 0.0308918810F);
        const auto temp4 = MultiplySub(temp3, x, 0.0501743046F);
        const auto temp5 = MultiplyAdd(temp4, x, 0.0889789874F);
        const auto temp6 = MultiplySub(temp5, x, 0.2145988016F);
        const auto temp7 = MultiplyAdd(temp6, x, 1.5707963050F);

        auto result = temp7;

#if false
        auto result2 = (((((((-0.0012624911F
            ) * x + 0.0066700901F
            ) * x - 0.0170881256F
            ) * x + 0.0308918810F
            ) * x - 0.0501743046F
            ) * x + 0.0889789874F
            ) * x - 0.2145988016F
            ) * x + 1.5707963050F;
#endif

        result *= root;

        return positive
            ? (result)
            : (Maths::PI<float> -result);
#else
        return std::acos(value);
#endif
    }
    mathinline float mathcall AcosEst(float value) noexcept
    {
        const auto positive = (value >= 0.0F);
        const auto x = Abs(value);
        auto mx = 1.0F - x;

        if (mx < 0.0F)
        {
            mx = 0.0F;
        }

        const auto root = Maths::Sqrt(mx);

        const auto temp1 = MultiplyAdd(-0.0187293F, x, 0.0742610F);
        const auto temp2 = MultiplySub(temp1, x, 0.2121144F);
        const auto temp3 = MultiplyAdd(temp2, x, 1.5707288F);

        auto result = temp3;

#if false
        auto result = (((-0.0187293F
            ) * x + 0.0742610F
            ) * x - 0.2121144F
            ) * x + 1.5707288F;
#endif

        result *= root;

        return positive
            ? (result)
            : (Maths::PI<float> -result);
    }
    mathinline float mathcall Acosh(float value) noexcept
    {
        return std::acosh(value);
    }
    mathinline float mathcall Asin(float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS
        const auto positive = (value >= 0.0F);
        const auto x = Abs(value);
        auto mx = 1.0F - x;

        if (mx < 0.0F)
        {
            mx = 0.0F;
        }

        const auto root = Maths::Sqrt(mx);

        const auto temp1 = MultiplyAdd(-0.0012624911F, x, 0.0066700901F);
        const auto temp2 = MultiplySub(temp1, x, 0.0170881256F);
        const auto temp3 = MultiplyAdd(temp2, x, 0.0308918810F);
        const auto temp4 = MultiplySub(temp3, x, 0.0501743046F);
        const auto temp5 = MultiplyAdd(temp4, x, 0.0889789874F);
        const auto temp6 = MultiplySub(temp5, x, 0.2145988016F);
        const auto temp7 = MultiplyAdd(temp6, x, 1.5707963050F);

        auto result = temp7;

#if false
        auto result = (((((((-0.0012624911F
            ) * x + 0.0066700901F
            ) * x - 0.0170881256F
            ) * x + 0.0308918810F
            ) * x - 0.0501743046F
            ) * x + 0.0889789874F
            ) * x - 0.2145988016F
            ) * x + 1.5707963050F;
#endif

        result *= root;

        return positive
            ? (Maths::PI_OVER_2<float> -result)
            : (result - Maths::PI_OVER_2<float>);
#else
        return std::asin(value);
#endif
    }
    mathinline float mathcall AsinEst(float value) noexcept
    {
        const auto positive = (value >= 0.0F);
        const auto x = Abs(value);
        auto mx = 1.0F - x;

        if (mx < 0.0F)
        {
            mx = 0.0F;
        }

        const auto root = Sqrt(mx);

        const auto temp1 = MultiplyAdd(-0.0187293F, x, 0.0742610F);
        const auto temp2 = MultiplySub(temp1, x, 0.2121144F);
        const auto temp3 = MultiplyAdd(temp2, x, 1.5707288F);

        auto result = temp3;

#if false
        auto result = (((-0.0187293F
            ) * x + 0.0742610F
            ) * x - 0.2121144F
            ) * x + 1.5707288F;
#endif

        result *= root;

        return positive
            ? (Maths::PI_OVER_2<float> -result)
            : (result - Maths::PI_OVER_2<float>);
    }
    mathinline float mathcall Asinh(float value) noexcept
    {
        return std::asinh(value);
    }
    mathinline float mathcall Atan(float value) noexcept
    {
        return std::atan(value);
    }
    mathinline float mathcall Atan2(float y, float x) noexcept
    {
        return std::atan2(y, x);
    }
    mathinline float mathcall Atanh(float value) noexcept
    {
        return std::atanh(value);
    }
    mathinline float mathcall Cos(float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS
        auto q = Maths::ONE_OVER_PI2<float> * value;

        if (value >= 0.0F)
        {
            q = static_cast<float>(static_cast<int32_t>(q + 0.5F));
        }
        else
        {
            q = static_cast<float>(static_cast<int32_t>(q - 0.5F));
        }

        auto y = value - Maths::PI2<float> * q;

        float sign;

        if (y >= Maths::PI_OVER_2<float>)
        {
            y = Maths::PI<float> -y;
            sign = -1.0F;
        }
        else if (y < -Maths::PI_OVER_2<float>)
        {
            y = -Maths::PI<float> -y;
            sign = -1.0F;
        }
        else
        {
            sign = 1.0F;
        }

        const auto y2 = y * y;

        const auto temp1 = MultiplyAdd(-2.6051615E-07F, y2, 2.4760495E-05F);
        const auto temp2 = MultiplySub(temp1, y2, 0.0013888378F);
        const auto temp3 = MultiplyAdd(temp2, y2, 0.041666638F);
        const auto temp4 = MultiplySub(temp3, y2, 0.5F);
        const auto temp5 = MultiplyAdd(temp4, y2, 1.0F);

        const auto p = temp5;

#if false
        const auto p = (((((-2.6051615E-07F
            ) * y2 + 2.4760495E-05F
            ) * y2 - 0.0013888378F
            ) * y2 + 0.041666638F
            ) * y2 - 0.5F
            ) * y2 + 1.0F;
#endif

        return sign * p;
#else
        return std::cos(value);
#endif
    }
    mathinline float mathcall CosEst(float value) noexcept
    {
        auto q = Maths::ONE_OVER_PI2<float> * value;

        if (value >= 0.0F)
        {
            q = static_cast<float>(static_cast<int32_t>(q + 0.5F));
        }
        else
        {
            q = static_cast<float>(static_cast<int32_t>(q - 0.5F));
        }

        auto y = value - Maths::PI2<float> * q;

        float sign;

        if (y > Maths::PI_OVER_2<float>)
        {
            y = Maths::PI<float> -y;
            sign = -1.0F;
        }
        else if (y < -Maths::PI_OVER_2<float>)
        {
            y = -Maths::PI<float> -y;
            sign = -1.0F;
        }
        else
        {
            sign = 1.0F;
        }

        const auto y2 = y * y;

        const auto temp1 = MultiplyAdd(-0.0012712436F, y2, 0.041493919F);
        const auto temp2 = MultiplySub(temp1, y2, 0.49992746F);
        const auto temp3 = MultiplyAdd(temp2, y2, 1.0F);

        const auto p = temp3;

#if false
        const auto p = (((-0.0012712436F
            ) * y2 + 0.041493919F
            ) * y2 - 0.49992746F
            ) * y2 + 1.0F;
#endif

        return sign * p;
    }
    mathinline float mathcall Cosh(float value) noexcept
    {
        return std::cosh(value);
    }
    mathinline float mathcall Sin(float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS
        auto q = Maths::ONE_OVER_PI2<float> * value;

        if (value >= 0.0F)
        {
            q = static_cast<float>(static_cast<int32_t>(q + 0.5F));
        }
        else
        {
            q = static_cast<float>(static_cast<int32_t>(q - 0.5F));
        }

        auto y = value - Maths::PI2<float> * q;

        if (y >= Maths::PI_OVER_2<float>)
        {
            y = Maths::PI<float> -y;
        }
        else if (y < -Maths::PI_OVER_2<float>)
        {
            y = -Maths::PI<float> -y;
        }

        const auto y2 = y * y;

        const auto temp1 = MultiplyAdd(-2.3889859E-08F, y2, 2.7525562E-06F);
        const auto temp2 = MultiplySub(temp1, y2, 0.00019840874F);
        const auto temp3 = MultiplyAdd(temp2, y2, 0.0083333310F);
        const auto temp4 = MultiplySub(temp3, y2, 0.16666667F);
        const auto temp5 = MultiplyAdd(temp4, y2, 1.0F);

        const auto result = temp5 * y;

        return result;

#if false
        return ((((((-2.3889859E-08F
            ) * y2 + 2.7525562E-06F
            ) * y2 - 0.00019840874F
            ) * y2 + 0.0083333310F
            ) * y2 - 0.16666667F
            ) * y2 + 1.0F
            ) * y;
#endif

#else
        return std::sin(value);
#endif
    }
    mathinline float mathcall SinEst(float value) noexcept
    {
        auto q = Maths::ONE_OVER_PI2<float> * value;

        if (value >= 0.0F)
        {
            q = static_cast<float>(static_cast<int32_t>(q + 0.5F));
        }
        else
        {
            q = static_cast<float>(static_cast<int32_t>(q - 0.5F));
        }

        auto y = value - Maths::PI2<float> * q;

        if (y >= Maths::PI_OVER_2<float>)
        {
            y = Maths::PI<float> -y;
        }
        else if (y < -Maths::PI_OVER_2<float>)
        {
            y = -Maths::PI<float> -y;
        }

        const auto y2 = y * y;

        const auto temp1 = MultiplyAdd(-0.00018524670F, y2, 0.0083139502F);
        const auto temp2 = MultiplySub(temp1, y2, 0.16665852F);
        const auto temp3 = MultiplyAdd(temp2, y2, 1.0F);

        const auto result = temp3 * y;

        return result;

#if false
        return ((((-0.00018524670F
            ) * y2 + 0.0083139502F
            ) * y2 - 0.16665852F
            ) * y2 + 1.0F
            ) * y;
#endif
    }
    mathinline float mathcall Sinh(float value) noexcept
    {
        return std::sinh(value);
    }
    mathinline float mathcall Tan(float value) noexcept
    {
        return std::tan(value);
    }
    mathinline float mathcall Tanh(float value) noexcept
    {
        return std::tanh(value);
    }
    mathinline void mathcall SinCos(float& sin_value, float& cos_value, float value) noexcept
    {
#if GRAPHYTE_MATH_FAST_FUNCTIONS
        auto q = Maths::ONE_OVER_PI2<float> * value;

        if (value >= 0.0F)
        {
            q = static_cast<float>(static_cast<int32_t>(q + 0.5F));
        }
        else
        {
            q = static_cast<float>(static_cast<int32_t>(q - 0.5F));
        }

        auto y = value - Maths::PI2<float> * q;

        float sign;

        if (y > Maths::PI_OVER_2<float>)
        {
            y = Maths::PI<float> -y;
            sign = -1.0F;
        }
        else if (y < -Maths::PI_OVER_2<float>)
        {
            y = -Maths::PI<float> -y;
            sign = -1.0F;
        }
        else
        {
            sign = 1.0F;
        }

        const auto y2 = y * y;


        //
        // Compute sin value.
        //

        const auto stemp1 = MultiplyAdd(-2.3889859e-08F, y2, 2.7525562e-06F);
        const auto stemp2 = MultiplySub(stemp1, y2, 0.00019840874F);
        const auto stemp3 = MultiplyAdd(stemp2, y2, 0.0083333310F);
        const auto stemp4 = MultiplySub(stemp3, y2, 0.16666667F);
        const auto stemp5 = MultiplyAdd(stemp4, y2, 1.0F);

        const auto sin_result = stemp5 * y;

        sin_value = sin_result;


        //
        // Compute cos value.
        //

        const auto ctemp1 = MultiplyAdd(-2.6051615e-07F, y2, 2.4760495e-05F);
        const auto ctemp2 = MultiplySub(ctemp1, y2, 0.0013888378F);
        const auto ctemp3 = MultiplyAdd(ctemp2, y2, 0.041666638F);
        const auto ctemp4 = MultiplySub(ctemp3, y2, 0.5F);
        const auto ctemp5 = MultiplyAdd(ctemp4, y2, 1.0F);

        const auto cos_result = sign * ctemp5;

        cos_value = cos_result;

#if false
        sin_value = ((((((-2.3889859e-08F
            ) * y2 + 2.7525562e-06F
            ) * y2 - 0.00019840874F
            ) * y2 + 0.0083333310F
            ) * y2 - 0.16666667F
            ) * y2 + 1.0F
            ) * y;

        const auto p = (((((-2.6051615e-07F
            ) * y2 + 2.4760495e-05F
            ) * y2 - 0.0013888378F
            ) * y2 + 0.041666638F
            ) * y2 - 0.5F
            ) * y2 + 1.0F;

        cos_value = sign * p;
#endif

#else
        sin_value = std::sin(value);
        cos_value = std::cos(value);
#endif
    }
    mathinline void mathcall SinCosEst(float& out_sin, float& out_cos, float value) noexcept
    {
        auto q = Maths::ONE_OVER_PI2<float> * value;

        if (value >= 0.0F)
        {
            q = static_cast<float>(static_cast<int32_t>(q + 0.5F));
        }
        else
        {
            q = static_cast<float>(static_cast<int32_t>(q - 0.5F));
        }

        auto y = value - Maths::PI2<float> * q;

        float sign;

        if (y > Maths::PI_OVER_2<float>)
        {
            y = Maths::PI<float> -y;
            sign = -1.0F;
        }
        else if (y < -Maths::PI_OVER_2<float>)
        {
            y = -Maths::PI<float> -y;
            sign = -1.0F;
        }
        else
        {
            sign = 1.0F;
        }

        const auto y2 = y * y;


        //
        // Compute sin value.
        //

        const auto stemp1 = MultiplyAdd(-0.00018524670F, y2, 0.0083139502F);
        const auto stemp2 = MultiplySub(stemp1, y2, 0.16665852F);
        const auto stemp3 = MultiplyAdd(stemp2, y2, 1.0F);
        const auto sin_value = stemp3 * y;

        out_sin = sin_value;


        //
        // Compute cos value.
        //

        const auto ctemp1 = MultiplyAdd(-0.0012712436F, y2, 0.041493919F);
        const auto ctemp2 = MultiplySub(ctemp1, y2, 0.49992746F);
        const auto ctemp3 = MultiplyAdd(ctemp2, y2, 1.0F);

        const auto cos_value = sign * ctemp3;

        out_cos = cos_value;

#if false
        out_sin = ((((-0.00018524670F
            ) * y2 + 0.0083139502F
            ) * y2 - 0.16665852F
            ) * y2 + 1.0F
            ) * y;

        const auto p = (((-0.0012712436F
            ) * y2 + 0.041493919F
            ) * y2 - 0.49992746F
            ) * y2 + 1.0F;

        out_cos = sign * p;
#endif
    }
    mathinline bool mathcall IsValid(float value) noexcept
    {
        return (value > -std::numeric_limits<float>::max()) && (value < +std::numeric_limits<float>::max());
    }
    mathinline bool mathcall IsInfinite(float value) noexcept
    {
        return std::isinf(value);
    }
    mathinline bool mathcall IsFinite(float value) noexcept
    {
        return std::isfinite(value);
    }
    mathinline bool mathcall IsNaN(float value) noexcept
    {
        return std::isnan(value);
    }
    mathinline bool mathcall IsNormal(float value) noexcept
    {
        return std::isnormal(value);
    }
    mathinline bool mathcall IsUnordered(float value1, float value2) noexcept
    {
        return std::isunordered(value1, value2);
    }
    mathinline bool mathcall IsLess(float value1, float value2) noexcept
    {
        return std::isless(value1, value2);
    }
    mathinline bool mathcall IsLessEqual(float value1, float value2) noexcept
    {
        return std::islessequal(value1, value2);
    }
    mathinline bool mathcall IsGreater(float value1, float value2) noexcept
    {
        return std::isgreater(value1, value2);
    }
    mathinline bool mathcall IsGreaterEqual(float value1, float value2) noexcept
    {
        return std::isgreaterequal(value1, value2);
    }
    mathinline bool mathcall IsLessGreater(float value1, float value2) noexcept
    {
        return std::islessgreater(value1, value2);
    }
    mathinline bool mathcall IsZero(float value, float tolerance) noexcept
    {
        return std::abs(value) <= tolerance;
    }
    mathinline bool mathcall IsZero(float value) noexcept
    {
        return value == 0.0F;
    }
    mathinline bool mathcall IsEqual(float value1, float value2, float tolerance) noexcept
    {
        return std::abs(value1 - value2) <= tolerance;
    }
    mathinline bool mathcall IsEqual(float value1, float value2) noexcept
    {
        return value1 == value2;
    }
    mathinline bool mathcall IsNearEqual(float value1, float value2, int32_t tolerance) noexcept
    {
        if (IsZero(value1 - value2))
        {
            return true;
        }

        Graphyte::Impl::Ieee754::FloatBits u[2];
        u[0].AsFloat = value1;
        u[1].AsFloat = value2;

        const auto as_int_0 = u[0].AsInt32;
        const auto as_int_1 = u[1].AsInt32;

        if ((as_int_0 < 0) != (as_int_1 < 0))
        {
            return false;
        }

        const auto ulp = std::abs(as_int_0 - as_int_1);

        return ulp <= tolerance;
    }
    mathinline bool mathcall IsNearEqual(float value1, float value2) noexcept
    {
        static constexpr const int32_t tolerance{ 4 };
        return IsNearEqual(value1, value2, tolerance);
    }
    mathinline bool mathcall IsNearEqualSquared(float value1, float value2, float tolerance) noexcept
    {
        return Square(value1 - value2) <= Square(tolerance);
    }
    mathinline bool mathcall IsNearEqualSquared(float value1, float value2) noexcept
    {
        return IsNearEqualSquared(value1, value2, std::numeric_limits<float>::epsilon());
    }
    mathinline bool mathcall IsInRange(float value, float min, float max) noexcept
    {
        return (value >= min) && (value < max);
    }
    mathinline bool mathcall IsInRangeInclusive(float value, float min, float max) noexcept
    {
        return (value >= min) && (value <= max);
    }
    mathinline float mathcall Distance(float value1, float value2) noexcept
    {
        return Maths::Abs(value1 - value2);
    }
    mathinline float mathcall WrapAngle(float value) noexcept
    {
        const auto raw = value + Maths::PI<float>;
        auto abs = Abs(raw);

        const auto scaled = static_cast<float>(static_cast<int32_t>(abs / Maths::PI<float>));

        abs -= Maths::PI<float> * scaled;
        abs -= Maths::PI<float>;

        if (raw < 0.0F)
        {
            abs = -abs;
        }

        return abs;
    }
    mathinline float mathcall DiffAngle(float angle1, float angle2) noexcept
    {
        const auto r1 = angle2 - angle1;
        const auto r2 = r1 - Maths::PI2<float>;
        const auto r3 = r1 + Maths::PI2<float>;

        const auto a1 = Abs(r1);
        const auto a2 = Abs(r2);
        const auto a3 = Abs(r3);

        if ((a1 < a2) && (a1 < a3))
        {
            return r1;
        }
        else if (a2 < a3)
        {
            return r2;
        }

        return r3;
    }
    mathinline float mathcall RevolutionsToDegrees(float value) noexcept
    {
        return value * 360.0F;
    }
    mathinline float mathcall RevolutionsToRadians(float value) noexcept
    {
        return value * Maths::PI<float>;
    }
    mathinline float mathcall RevolutionsToGradians(float value) noexcept
    {
        return value * 400.0F;
    }
    mathinline float mathcall DegreesToRevolutions(float value) noexcept
    {
        return value / 360.0F;
    }
    mathinline float mathcall RadiansToRevolutions(float value) noexcept
    {
        return value / Maths::PI2<float>;
    }
    mathinline float mathcall GradiansToRevolutions(float value) noexcept
    {
        return value / 400.0F;
    }
    mathinline float mathcall RadiansToGradians(float value) noexcept
    {
        return value * (200.0F / Maths::PI<float>);
    }
    mathinline float mathcall GradiansToRadians(float value) noexcept
    {
        return value * (Maths::PI<float> / 200.0F);
    }
    mathinline float mathcall RadiansToDegrees(float value) noexcept
    {
        return value * (180.0F / Maths::PI<float>);
    }
    mathinline float mathcall DegreesToRadians(float value) noexcept
    {
        return value * (Maths::PI<float> / 180.0F);
    }
    mathinline float mathcall GradiansToDegrees(float value) noexcept
    {
        return value * (9.0F / 10.0F);
    }
    mathinline float mathcall DegreesToGradians(float value) noexcept
    {
        return value * (10.0F / 9.0F);
    }
    mathinline float mathcall UnwindRadians(float value) noexcept
    {
        // Note: possible infinite loop when value is sufficiently large.
        while (value > Maths::PI<float>)
        {
            value -= Maths::PI2<float>;
        }

        while (value < -Maths::PI<float>)
        {
            value += Maths::PI2<float>;
        }

        return value;
    }
    mathinline float mathcall UnwindDegrees(float value) noexcept
    {
        while (value > 180.0F)
        {
            value -= 360.0F;
        }

        while (value < -180.0F)
        {
            value += 360.0F;
        }

        return value;
    }
    mathinline float mathcall UnwindGradians(float value) noexcept
    {
        while (value > 200.0F)
        {
            value -= 400.0F;
        }

        while (value < -200.0F)
        {
            value += 400.0F;
        }

        return value;
    }
    mathinline float mathcall UnwindRevolutions(float value) noexcept
    {
        return Frac(value);
    }
    mathinline float mathcall Gain(float value, float gain) noexcept
    {
        const auto g = -Log2(1.0F - gain);
        const auto c = Pow(value, gain);
        return c / (c + Pow(1.0F - value, g));
    }
    mathinline float mathcall Bias(float value, float base) noexcept
    {
        return Pow(value, -Log2(base));
    }
    mathinline float mathcall Step(float value1, float value2) noexcept
    {
        return (value1 <= value2)
            ? 0.0F
            : 1.0F;
    }
    mathinline float mathcall Map(float value, float to_min, float to_max, float from_min, float from_max) noexcept
    {
        const auto to_range = to_max - to_min;
        const auto from_range = from_max - from_min;
        const auto value_scaled = (value - from_min) / from_range;
        const auto result = to_min + (value_scaled * to_range);
        return result;
    }
    mathinline int mathcall QuadricEquation(float a, float b, float c, float& out_x1, float& out_x2) noexcept
    {
        const auto delta = (b * b) - (4.0F * a * c);

        if (delta < 0.0F)
        {
            out_x1 = out_x2 = std::numeric_limits<float>::infinity();
            return 0;
        }
        else if (IsZero(delta))
        {
            out_x1 = out_x2 = (-b / (2.0F * a));
            return 1;
        }

        const auto denominator = 1.0F / (2.0F * a);
        const auto delta_sqrt = Sqrt(delta);

        out_x1 = (-b - delta_sqrt) * denominator;
        out_x2 = (-b + delta_sqrt) * denominator;

        return 2;
    }
    mathinline float mathcall SnapToGrid(float value, float grid_size) noexcept
    {
        if (grid_size == 0.0F)
        {
            return value;
        }
        else
        {
            return Floor((value + 0.5F * grid_size) / grid_size) * grid_size;
        }
    }
}

namespace Graphyte::Maths
{
    mathinline float mathcall WangHashNoise(uint32_t u, uint32_t v, uint32_t s) noexcept
    {
        uint32_t seed = (u * 1664525U + v) + s;

        seed = (seed ^ 61U) ^ (seed >> 16U);
        seed *= 9U;
        seed = seed ^ (seed >> 4U);
        seed *= 0x27d4eb2d;
        seed = seed ^ (seed >> 15U);

        auto value = static_cast<float>(seed);
        value = static_cast<float>(static_cast<double>(value) * (1.0 / 4294967296.0));
        return value;
    }
}

namespace Graphyte::Maths
{
    mathinline uint32_t mathcall FixedToFixed(uint32_t value, uint32_t n, uint32_t p) noexcept
    {
        if (n > p)
        {
            value >>= (n - p);
        }
        else if (n < p)
        {
            if (value == (static_cast<uint32_t>(1) << n) - 1)
            {
                value = static_cast<uint32_t>((1 << p) - 1);
            }
            else
            {
                value = static_cast<uint32_t>((value * (1 << p)) / ((1 << n) - 1));
            }
        }

        return value;
    }

    mathinline uint32_t mathcall FloatToFixed(float value, uint32_t bits) noexcept
    {
        if (value <= 0.0F)
        {
            return 0;
        }
        else if (value >= 1.0F)
        {
            return static_cast<uint32_t>((1 << bits) - 1);
        }
        

        return static_cast<uint32_t>(value * (1U << bits));
    }

    mathinline float mathcall FixedToFloat(uint32_t value, uint32_t bits) noexcept
    {
        return static_cast<float>(value) / static_cast<float>((1 << bits) - 1);
    }
}
