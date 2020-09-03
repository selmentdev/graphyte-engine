#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    [[nodiscard]] mathinline Vector4 mathcall Dot(
        Vector4 xs1,
        Vector4 ys1,
        Vector4 zs1,
        Vector4 ws1,
        Vector4 xs2,
        Vector4 ys2,
        Vector4 zs2,
        Vector4 ws2) noexcept
    {
        Vector4 r0 = Multiply(xs1, xs2);
        Vector4 r1 = MultiplyAdd(ys1, ys2, r0);
        Vector4 r2 = MultiplyAdd(zs1, zs2, r1);
        Vector4 r3 = MultiplyAdd(ws1, ws2, r2);
        return r3;
    }

    [[nodiscard]] mathinline Vector4 mathcall Dot(
        Vector4 xs1,
        Vector4 ys1,
        Vector4 zs1,
        Vector4 xs2,
        Vector4 ys2,
        Vector4 zs2) noexcept
    {
        Vector4 const r0 = Multiply(xs1, xs2);
        Vector4 const r1 = MultiplyAdd(ys1, ys2, r0);
        Vector4 const r2 = MultiplyAdd(zs1, zs2, r1);
        return r2;
    }

    [[nodiscard]] mathinline Vector4 mathcall Dot(
        Vector4 xs1,
        Vector4 ys1,
        Vector4 xs2,
        Vector4 ys2) noexcept
    {
        Vector4 const r0 = Multiply(xs1, xs2);
        Vector4 const r1 = MultiplyAdd(ys1, ys2, r0);
        return r1;
    }
}
