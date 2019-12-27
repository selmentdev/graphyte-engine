#pragma once
#include <Graphyte/Maths/Scalar.hxx>

namespace Graphyte::Maths::Interpolation
{
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
}
