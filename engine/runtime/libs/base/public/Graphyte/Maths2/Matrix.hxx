#pragma once
#include <Graphyte/Maths2/Consts.hxx>

namespace Graphyte::Maths
{
    mathinline Vec4 mathcall BaseX(Mtx44 m) noexcept
    {
        return { m.M.R[0] };
    }

    mathinline Vec4 mathcall BaseY(Mtx44 m) noexcept
    {
        return { m.M.R[1] };
    }

    mathinline Vec4 mathcall BaseZ(Mtx44 m) noexcept
    {
        return { m.M.R[2] };
    }

    mathinline Vec4 mathcall BaseW(Mtx44 m) noexcept
    {
        return { m.M.R[3] };
    }
}
