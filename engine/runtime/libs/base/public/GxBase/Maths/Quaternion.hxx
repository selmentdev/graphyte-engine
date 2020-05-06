#pragma once
#include <Graphyte/Maths/Base.hxx>
#include <Graphyte/Maths/Vector4.hxx>


// =================================================================================================
//
// Type construction functions.
//

namespace Graphyte::MathsX
{
    template <>
    mathinline Quaternion mathcall Make<Quaternion, float>(float x, float y, float z, float w) noexcept
    {
        return { Make<Vector4, float>(x, y, z, w).V };
    }
}


// =================================================================================================
//
// Vector conversion functions.
//

namespace Graphyte::MathsX
{
    template <>
    mathinline Quaternion mathcall Make<Quaternion, Vector4>(Vector4 v) noexcept
    {
        return { v.V };
    }

    template <>
    mathinline Vector4 mathcall Make<Vector4, Quaternion>(Quaternion v) noexcept
    {
        return { v.V };
    }
}
