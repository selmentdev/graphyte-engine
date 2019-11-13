#pragma once
#include <Graphyte/Types.hxx>
#include <Graphyte/Maths/Scalar.hxx>

namespace Graphyte::Maths
{
    mathinline Float3A mathcall CartesianToSpherical(const Float3A& value) noexcept
    {
        const auto radius = Sqrt(
            value.X * value.X +
            value.Y * value.Y +
            value.Z * value.Z
        );
        const auto theta = Acos(
            value.Z / radius
        );
        const auto phi = Atan(
            value.Y / value.X
        );

        return { radius, theta, phi };
    }
    mathinline Float3A mathcall SphericalToCartesian(const Float3A& value) noexcept
    {
        float sin_theta;
        float cos_theta;
        float sin_phi;
        float cos_phi;
        const auto radius = value.X;
        SinCos(sin_theta, cos_theta, value.Y);
        SinCos(sin_phi, cos_phi, value.Z);

        const auto partial = radius * sin_theta;

        return { partial * cos_phi, partial * sin_phi, radius * cos_theta };
    }
    mathinline Float3A mathcall CartesianToCylindrical(const Float3A& value) noexcept
    {
        const auto radius = Sqrt(
            value.X * value.X +
            value.Y * value.Y
        );
        const auto angle = Atan(
            value.Y / value.X
        );
        const auto elevation = value.Z;

        return { radius, angle, elevation };
    }
    mathinline Float3A mathcall CylindricalToCartesian(const Float3A& value) noexcept
    {
        const auto radius = value.X;
        const auto angle = value.Y;
        const auto elevation = value.Z;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        return { radius * cos_angle, radius * sin_angle, elevation };
    }
    mathinline Float2A mathcall PolarToCartesian(const Float2A& value) noexcept
    {
        const auto radius = value.X;
        const auto angle = value.Y;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        const auto x = radius * cos_angle;
        const auto y = radius * sin_angle;

        return { x, y };
    }
    mathinline Float2A mathcall CartesianToPolar(const Float2A& value) noexcept
    {
        const auto radius = Sqrt(
            value.X * value.X +
            value.Y * value.Y
        );
        const auto angle = Atan2(value.Y, value.X);

        return { radius, angle };
    }
}
