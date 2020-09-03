#pragma once
#include <GxBase/Types.hxx>
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall RevolutionsToDegrees(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(360.0f);
        T const result = Multiply<T>(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RevolutionsToDegrees(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * T(360.0);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RevolutionsToRadians(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier{ Impl::c_V4_F32_Pi.V };
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RevolutionsToRadians(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * Maths::Impl::ConstPi<T>;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RevolutionsToGradians(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(400.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RevolutionsToGradians(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * T(400.0);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall DegreesToRevolutions(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(1.0f / 360.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall DegreesToRevolutions(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value / T(360.0);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RadiansToRevolutions(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(1.0 / Maths::Impl::ConstPi2<float>);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RadiansToRevolutions(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value / Maths::Impl::ConstPi2<T>;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall GradiansToRevolutions(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(1.0f / 400.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall GradiansToRevolutions(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value / T(400.0);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RadiansToGradians(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(200.0f / Maths::Impl::ConstPi<float>);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RadiansToGradians(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * (T(200.0) / Maths::Impl::ConstPi<T>);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall GradiansToRadians(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(Maths::Impl::ConstPi<float> / 200.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall GradiansToRadians(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * (Maths::Impl::ConstPi<T> / T(200.0));
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RadiansToDegrees(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(180.0f / Maths::Impl::ConstPi<float>);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall RadiansToDegrees(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * (T(180.0) / Maths::Impl::ConstPi<T>);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall DegreesToRadians(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(Maths::Impl::ConstPi<float> / 180.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall DegreesToRadians(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * (Maths::Impl::ConstPi<T> / T(180.0));
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall GradiansToDegrees(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(9.0f / 10.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall GradiansToDegrees(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * (T(9.0) / T(10.0));
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall DegreesToGradians(T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        T const multiplier = Replicate<T>(10.0f / 9.0f);
        T const result = Multiply(value, multiplier);
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall DegreesToGradians(T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return value * (T(10.0) / T(9.0));
    }

    [[nodiscard]] mathinline Float3A mathcall CartesianToSpherical(const Float3A& value) noexcept
    {
        float const radius = Sqrt(
            value.X * value.X + value.Y * value.Y + value.Z * value.Z);
        float const theta = Acos(
            value.Z / radius);
        float const phi = Atan(
            value.Y / value.X);

        return { radius, theta, phi };
    }

    [[nodiscard]] mathinline Float3A mathcall SphericalToCartesian(const Float3A& value) noexcept
    {
        float sin_theta;
        float cos_theta;
        float sin_phi;
        float cos_phi;
        float const radius = value.X;
        SinCos(sin_theta, cos_theta, value.Y);
        SinCos(sin_phi, cos_phi, value.Z);

        float const partial = radius * sin_theta;

        return { partial * cos_phi, partial * sin_phi, radius * cos_theta };
    }

    [[nodiscard]] mathinline Float3A mathcall CartesianToCylindrical(const Float3A& value) noexcept
    {
        float const radius = Sqrt(
            value.X * value.X + value.Y * value.Y);
        float const angle = Atan(
            value.Y / value.X);
        float const elevation = value.Z;

        return { radius, angle, elevation };
    }

    [[nodiscard]] mathinline Float3A mathcall CylindricalToCartesian(const Float3A& value) noexcept
    {
        float const radius = value.X;
        float const angle = value.Y;
        float const elevation = value.Z;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        return { radius * cos_angle, radius * sin_angle, elevation };
    }

    [[nodiscard]] mathinline Float2A mathcall PolarToCartesian(const Float2A& value) noexcept
    {
        float const radius = value.X;
        float const angle = value.Y;

        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        float const x = radius * cos_angle;
        float const y = radius * sin_angle;

        return { x, y };
    }

    [[nodiscard]] mathinline Float2A mathcall CartesianToPolar(const Float2A& value) noexcept
    {
        float const radius = Sqrt(
            value.X * value.X + value.Y * value.Y);
        float const angle = Atan2(value.Y, value.X);

        return { radius, angle };
    }
}
