#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall Make(Vector3 origin, float radius) noexcept
        requires(Impl::IsSphere<T>)
    {
#if GX_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                origin.V.F[0],
                origin.V.F[1],
                origin.V.F[2],
                radius,
            } } };
#elif GX_HW_AVX
        __m128 const vradius = _mm_set_ps1(radius);
        __m128 const vresult = Impl::avx_permute<0, 1, 2, 7>(origin.V, vradius);
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Make(Vector3 origin, Vector1 radius) noexcept
        requires(Impl::IsSphere<T>)
    {
#if GX_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
                origin.V.F[0],
                origin.V.F[1],
                origin.V.F[2],
                radius.V.F[0],
            } } };
#elif GX_HW_AVX
        __m128 const vresult = Impl::avx_permute<0, 1, 2, 5>(origin.V, radius.V);
#endif
    }

    [[nodiscard]] mathinline bool mathcall Contains(Sphere s, Vector3 p) noexcept
    {
        Vector3 const origin{ s.V };
        Vector3 const radius{ SplatW(Vector4{ s.V }).V };
        Vector3 const distance_squared = LengthSquared(Subtract(p, origin));
        Vector3 const radius_squared = Multiply(radius, radius);
        return IsLessEqual(distance_squared, radius_squared);
    }
}
