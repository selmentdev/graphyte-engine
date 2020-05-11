#pragma once
#include <GxBase/Maths/Scalar.hxx>

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
}
