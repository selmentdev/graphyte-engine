#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte
{
    struct Plane final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType      = Bool4;
    };
}
