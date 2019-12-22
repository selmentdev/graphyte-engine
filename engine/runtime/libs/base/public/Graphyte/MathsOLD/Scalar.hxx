#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Maths/Constants.hxx>

namespace Graphyte::Maths
{
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
