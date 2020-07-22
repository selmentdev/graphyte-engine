#pragma once
#include <GxBase/Maths/Base.hxx>

// =================================================================================================
//
// Type construction functions.
//

namespace Graphyte::MathsX
{
    template <>
    mathinline Vector4 mathcall Replicate<Vector4, float>(float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(value) };
#endif
    }

    template <>
    mathinline Vector4 mathcall Replicate<Vector4, float>(float const* source) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = (*source);
        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcast_ss(source) };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(source) };
#elif GRAPHYTE_HW_NEON
        return { vld1q_dup_f32(source) };
#endif
    }

    template <>
    mathinline Vector4 mathcall Make<Vector4, float>(float x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            0.0F,
            0.0F,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, 0.0F, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xn = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)));

        float32x2_t const zero = vdup_n_f32(0.0F);

        return { vcombine_f32(xn, zero) };
#endif
    }

    template <>
    mathinline Vector4 mathcall Make<Vector4, float>(float x, float y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            y,
            0.0F,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, y, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));

        float32x2_t const zero = vdup_n_f32(0.0F);

        return { vcombine_f32(xy, zero) };
#endif
    }

    template <>
    mathinline Vector4 mathcall Make<Vector4, float>(float x, float y, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            y,
            z,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, z, y, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));

        float32x2_t const zn = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)));

        return { vcombine_f32(xy, zn) };
#endif
    }

    template <>
    mathinline Vector4 mathcall Make<Vector4, float>(float x, float y, float z, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            y,
            z,
            w,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));

        float32x2_t const zw = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&w)) << 32));

        return { vcombine_f32(xy, zw) };
#endif
    }
}


// =================================================================================================
//
// Type conversion functions.
//

namespace Graphyte::MathsX
{
    template <>
    mathinline Vector4 mathcall To<Vector4, float, Vector3>(float x, Vector3 yzw) noexcept;
}
