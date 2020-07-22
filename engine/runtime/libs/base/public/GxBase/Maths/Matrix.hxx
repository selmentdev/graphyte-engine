#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte
{
    struct Matrix final
    {
        Impl::NativeFloat32x4x4 M;

        static constexpr const size_t Components = 16;
        static constexpr const size_t Rows       = 4;
        static constexpr const size_t Columns    = 4;

        using ComponentType = float;
    };
}
