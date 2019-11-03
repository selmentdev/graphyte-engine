#pragma once
#include <Graphyte/Maths/Scalar.hxx>

namespace Graphyte::Maths::Interpolation
{
    mathinline float mathcall Lerp(float a, float b, float t) noexcept
    {
        //return a + ((b - a) * t);
        return (1.0F - t) * a + t * b;
    }

    mathinline float mathcall Cosine(float a, float b, float t) noexcept
    {
        auto const t0 = (1.0F - Cos(t * PI<float>)) * 0.5F;
        return Lerp(a, b, t0);
    }

    mathinline float mathcall Cubic(float a, float b, float c, float d, float t) noexcept
    {
        auto const t2 = Square(t);
        auto const a0 = (-0.5F * b) + (1.5F * a) - (1.5F * d) + (0.5F * c);
        auto const a1 = b - (2.5F * a) + (2.0F * d) - (0.5F * c);
        auto const a2 = (-0.5F * b) + (0.5F * d);

        return a0 * t * t2 + a1 * t2 + a2 * t + a;
    }

    mathinline float mathcall Hermite(float a, float b, float c, float d, float t, float tension, float bias) noexcept
    {
        auto t2 = Square(t);
        auto t3 = t * t2;

        auto t0 = (b - a) * (1.0F + bias) * (1.0F - tension) * 0.5F;
        t0 += (c - b) * (1.0F - bias) * (1.0F - tension) * 0.5F;
        auto t1 = (c - b) * (1.0F + bias) * (1.0F - tension) * 0.5F;
        t1 += (d - c) * (1.0F - bias) * (1.0F - tension) * 0.5F;

        auto a0 = 2.0F * t3 - 3.0F * t2 + 1.0F;
        auto a1 = t3 - 2.0F * t2 + t;
        auto a2 = t3 - t2;
        auto a3 = -2.0F * t3 + 3.0F * t2;

        return (a0 * a + a1 * t0 + a2 * t1 + a3 * c);
    }

    mathinline float mathcall Bezier(float a, float b, float c, float t) noexcept
    {
        auto t2 = t * t;
        auto t1 = 1.0F - t;
        auto t12 = t1 * t1;
        return (a * t12) + (2.0F * b * t1  * t) + (c * t2);
    }

    mathinline float mathcall Bezier(float a, float b, float c, float d, float t) noexcept
    {
        auto t1 = 1.0F - t;
        auto t13 = Cube(t1);
        auto t3 = Cube(t);

        return (t13 * a) + (3.0F * t * t1 * t1 * b) + (3.0F * t * t * t1 * c) + (t3 * d);
    }

    mathinline float mathcall CatmullRom(float a, float b, float c, float d, float t) noexcept
    {
        auto t2 = Square(t);
        auto t3 = t * t2;

        auto m0 = 2.0F * b;
        auto m1 = -a + c;
        auto m2 = (2.0F * a) - (5.0F * b) + (4.0F * c) - d;
        auto m3 = -a + (3.0F * b) - (3.0F * c) + d;

        return 0.5F * (m0 + m1 * t + m2 * t2 + m3 * t3);
    }

    mathinline float mathcall SmoothStep(float x) noexcept
    {
        return x * x * (3.0F - 2.0F * x);
    }

    mathinline float mathcall EaseSmoothC2(float x) noexcept
    {
        return x * x * x * (x * (x * 6.0F - 15.0F) + 10.0F);
    }

    mathinline float mathcall Smooth(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        auto xx = (x - min) / (max - min);
        return xx * xx * (3.0F - 2.0F * x);
    }

    mathinline float mathcall SmoothSquared(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        auto xx = (x * x);
        return Lerp(min, max, xx);
    }

    mathinline float mathcall SmoothInvSquared(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        auto xx = 1.0F - (1.0F - x) * (1.0F - x);
        return Lerp(min, max, xx);
    }

    mathinline float mathcall SmoothCubed(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        auto xx = (x * x * x);
        return Lerp(min, max, xx);
    }

    mathinline float mathcall SmoothInvCubed(float min, float max, float x) noexcept
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        auto xx = 1.0F - (1.0F - x) * (1.0F - x) * (1.0F - x);
        return Lerp(min, max, xx);
    }

    mathinline float mathcall Trapezoid(float a, float b, float c, float d, float t) noexcept
    {
        if (t <= a)
        {
            return 0.0F;
        }
        else if (t < b)
        {
            return (t - a) / (b - a);
        }
        else if (t < c)
        {
            return 1.0F;
        }
        else if (t < d)
        {
            return 1.0F - (t - c) / (d - c);
        }

        return 0.0F;
    }

    mathinline float mathcall Trapezoid(float a, float b, float c, float d, float t, float min, float max) noexcept
    {
        return Lerp(min, max, Trapezoid(a, b, c, d, t));
    }
}
