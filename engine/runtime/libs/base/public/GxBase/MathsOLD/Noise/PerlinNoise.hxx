#pragma once
#include <GxBase/Base.module.hxx>

namespace Graphyte::Maths
{
    class BASE_API PerlinNoise final
    {
    public:
        static float Normal(float x) noexcept;
        static float Normal(float x, float y) noexcept;
        static float Normal(float x, float y, float z) noexcept;
        static float Normal(float x, float y, float z, float w) noexcept;

        static float Periodic(float x, int period_x) noexcept;
        static float Periodic(float x, float y, int period_x, int period_y) noexcept;
        static float Periodic(float x, float y, float z, int period_x, int period_y, int period_z) noexcept;
        static float Periodic(float x, float y, float z, float w, int period_x, int period_y, int period_z, int period_w) noexcept;
    };
}
