#pragma once
#include <Graphyte/Base.module.hxx>

namespace Graphyte::Maths
{
    class BASE_API SimplexNoise final
    {
    public:
        static float Normal(float x) noexcept;
        static float Normal(float x, float y) noexcept;
        static float Normal(float x, float y, float z) noexcept;
        static float Normal(float x, float y, float z, float w) noexcept;
    };
}
