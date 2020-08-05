#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Constants.hxx>
#include <GxBase/Maths/Scalar.hxx>


// =================================================================================================
// Vector conversion.

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall To(float x, Vector3 yzw) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            yzw.V.F[0],
            yzw.V.F[1],
            yzw.V.F[2],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [_, vx, vy, vz]
        float32x4_t const wxyz = Impl::neon_swizzle<3, 0, 1, 2>(yzw.V);
        // = [x, vx, vy, vz]
        float32x4_t const result = vsetq_lane_f32(x, wxyz, 0);
        return { result };
#elif GRAPHYTE_HW_AVX
        // = [_, vx, vy, vz]
        __m128 const wxyz = _mm_permute_ps(yzw.V, _MM_SHUFFLE(2, 1, 0, 3));
        // = [x, _, _, _]
        __m128 const xxxx = _mm_set_ss(x);
        // = [x, vx, vy, vz]
        __m128 const result = _mm_move_ss(wxyz, xxxx);
        return { result };
#endif
    }

    mathinline Vector4 mathcall To(Vector3 xyz, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            xyz.V.F[0],
            xyz.V.F[1],
            xyz.V.F[2],
            w,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const xyzw = vsetq_lane_f32(w, xyz.V, 3);
        return { xyzw };
#elif GRAPHYTE_HW_AVX
        // = [w, _, _, _]
        __m128 const wwww = _mm_set_ss(w);
        // = [vx, vy, vz, w]
        __m128 const result = _mm_insert_ps(xyz.V, wwww, 0x30);
        return { result };
#endif
    }

    mathinline Vector4 mathcall To(float x, float y, Vector2 zw) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            y,
            zw.V.F[0],
            zw.V.F[1],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [x, y]
        float32x2_t const r0 = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&x)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&y)) << 32));
        // = [vx, vy]
        float32x4_t const r1 = vget_high_f32(zw.V);
        // = [x, y, vx, vy]
        return { vcombine_f32(r0, r1) };
#elif GRAPHYTE_HW_AVX
        // = [x, y, 0, 0]
        __m128 const r0 = _mm_set_ps(0.0f, 0.0f, y, x);
        // = [x, y, vx, vy]
        __m128 const r1 = _mm_shuffle_ps(r0, zw.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { r1 };
#endif
    }

    mathinline Vector4 mathcall To(float x, Vector2 yz, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            yz.V.F[0],
            yz.V.F[1],
            w,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [_, vx, vy, _]
        float32x4_t const r0 = Impl::neon_swizzle<0, 0, 1, 3>(yz.V);
        // = [x, vx, vy, _]
        float32x4_t const r1 = vsetq_lane_f32(x, r0, 0);
        // = [x, vx, vy, w]
        float32x4_t const r2 = vsetq_lane_f32(w, r1, 3);
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [_, vx, vy, _]
        __m128 const r0 = _mm_permute_ps(yz.V, _MM_SHUFFLE(3, 1, 0, 0));
        // = [x, vx, vy, _]
        __m128 const r1 = _mm_insert_ps(r0, _mm_set_ps1(x), 0x00);
        // = [x, vx, vy, w]
        __m128 const r2 = _mm_insert_ps(r1, _mm_set_ps1(w), 0x30);
        return { r2 };
#endif
    }

    mathinline Vector4 mathcall To(Vector2 xy, float z, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            xy.V.F[0],
            xy.V.F[1],
            z,
            w,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [vx, vy]
        float32x2_t const r0 = vget_low_f32(xy.V);

        // = [z, w]
        float32x2_t const r1 = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)) | (static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&w)) << 32));

        // = [vx, vy, z, w]
        return { vcombine_f32(r0, r1) };
#elif GRAPHYTE_HW_AVX
        // = [z, w, _, _]
        __m128 const r0 = _mm_set_ps(0.0f, 0.0f, w, z);
        // = [vx, vy, z, w]
        __m128 const r1 = _mm_shuffle_ps(r0, xy.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { r1 };
#endif
    }

    mathinline Vector4 mathcall To(Vector2 xy, Vector2 zw) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            xy.V.F[0],
            xy.V.F[1],
            zw.V.F[0],
            zw.V.F[1],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [vx, vy]
        float32x2_t const r0 = vget_low_f32(xy.V);
        // = [vz, vw]
        float32x2_t const r1 = vget_low_f32(zw.V);
        // = [vx, vy, vz, vw]
        float32x4_t const r2 = vcombine_f32(r0, r1);
        return { r2 };
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = _mm_shuffle_ps(xy.V, zw.V, _MM_SHUFFLE(1, 0, 1, 0));
        return { r0 };
#endif
    }

    mathinline Vector3 mathcall To(float x, Vector2 yz) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            x,
            yz.V.F[0],
            yz.V.F[1],
            0.0f,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [_, vy, vz, _]
        float32x4_t const r0 = Impl::neon_swizzle<0, 0, 1, 1>(yz.V);
        // = [x, vy, vz, _]
        float32x4_t const r1 = vsetq_lane_f32(x, r0, 0);
        // = [x, vy, vz, 0]
        float32x4_t const r2 = vreinterpretq_f32_u32(vandq_u32(
            vreinterpretq_u32_f32(r1),
            vreinterpretq_u32_f32(Impl::c_V4_U32_Mask_1110.V)));
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [_, vy, vz, _]
        __m128 const r0 = _mm_permute_ps(yz.V, _MM_SHUFFLE(1, 1, 0, 0));
        // = [x, vy, vz, _]
        __m128 const r1 = _mm_insert_ps(r0, _mm_set_ps1(x), 0x00);
        // = [x, vy, vz, 0]
        __m128 const r2 = _mm_and_ps(r1, Impl::c_V4_U32_Mask_1110.V);
        return { r2 };
#endif
    }

    mathinline Vector3 mathcall To(Vector2 xy, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            xy.V.F[0],
            xy.V.F[1],
            z,
            0.0f,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [vx, vy]
        float32x2_t const r0 = vget_low_f32(xy.V);
        // = [z, 0]
        float32x2_t const r1 = vcreate_f32(
            static_cast<uint64_t>(*reinterpret_cast<uint32_t const*>(&z)));
        // = [vx, vy, z, 0]
        float32x4_t const r2 = vcombine_f32(r0, r1);
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [z, 0, 0, 0]
        __m128 const r0 = _mm_set_ps1(z);
        // = [vx, vy, z, 0]
        __m128 const r1 = _mm_shuffle_ps(xy.V, r0, _MM_SHUFFLE(1, 0, 1, 0));
        return { r1 };
#endif
    }
}


// =================================================================================================
// Constants.

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall UnitX() noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_PositiveUnitX.V };
    }

    template <typename T>
    mathinline T mathcall UnitY() noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_PositiveUnitY.V };
    }

    template <typename T>
    mathinline T mathcall UnitZ() noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_PositiveUnitZ.V };
    }

    template <typename T>
    mathinline T mathcall UnitW() noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_PositiveUnitW.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitX() noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_NegativeUnitX.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitY() noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_NegativeUnitY.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitZ() noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_NegativeUnitZ.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitW() noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_NegativeUnitW.V };
    }

    template <typename T>
    mathinline T mathcall Zero() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::c_V4_F32_Zero.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(0.0F) };
#endif
    }

    template <typename T>
    mathinline T mathcall One() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F,
            1.0F,
            1.0F,
            1.0F,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::c_V4_F32_One.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_f32(1.0F) };
#endif
    }

    template <typename T>
    mathinline T mathcall Infinity() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
            FloatTraits<float>::Infinity,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::c_V4_F32_Positive_Infinity.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(FloatTraits<float>::Infinity) };
#endif
    }

    template <typename T>
    mathinline T mathcall Nan() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
            FloatTraits<float>::QNaN,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::c_V4_F32_Positive_QNan.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(FloatTraits<float>::QNan) };
#endif
    }

    template <typename T>
    mathinline T mathcall Epsilon() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            FloatTraits<float>::Epsilon,
            FloatTraits<float>::Epsilon,
            FloatTraits<float>::Epsilon,
            FloatTraits<float>::Epsilon,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::c_V4_F32_Epsilon.V };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(FloatTraits<float>::Epsilon) };
#endif
    }

    template <typename T>
    mathinline T mathcall SignMask() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            0x80000000U,
            0x80000000U,
            0x80000000U,
            0x80000000U,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_castsi128_ps(_mm_set1_epi32(static_cast<int>(0x80000000))) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0x80000000U) };
#endif
    }

    template <typename T>
    mathinline T mathcall E() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        return { Impl::c_V4_F32_E.V };
    }
}


// =================================================================================================
// Comparisons

namespace Graphyte::Maths
{

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] == b.V.F[0])
                   && (a.V.F[1] == b.V.F[1])
                   && (a.V.F[2] == b.V.F[2])
                   && (a.V.F[3] == b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] == b.V.F[0])
                   && (a.V.F[1] == b.V.F[1])
                   && (a.V.F[2] == b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] == b.V.F[0])
                   && (a.V.F[1] == b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] == b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpeq_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b, T epsilon) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);
            float const fy = fabsf(a.V.F[1] - b.V.F[1]);
            float const fz = fabsf(a.V.F[2] - b.V.F[2]);
            float const fw = fabsf(a.V.F[3] - b.V.F[3]);

            return (fx <= epsilon.V.F[0])
                   && (fy <= epsilon.V.F[1])
                   && (fz <= epsilon.V.F[2])
                   && (fw <= epsilon.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);
            float const fy = fabsf(a.V.F[1] - b.V.F[1]);
            float const fz = fabsf(a.V.F[2] - b.V.F[2]);

            return (fx <= epsilon.V.F[0])
                   && (fy <= epsilon.V.F[1])
                   && (fz <= epsilon.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);
            float const fy = fabsf(a.V.F[1] - b.V.F[1]);

            return (fx <= epsilon.V.F[0])
                   && (fy <= epsilon.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            float const fx = fabsf(a.V.F[0] - b.V.F[0]);

            return (fx <= epsilon.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        __m128 const dv   = _mm_sub_ps(a.V, b.V);
        __m128 const zero = _mm_setzero_ps();
        __m128 const nv   = _mm_sub_ps(zero, dv);
        __m128 const av   = _mm_max_ps(nv, dv);
        __m128 const mask = _mm_cmple_ps(av, epsilon.V);

        constexpr uint32_t expected = (1u << T::Components) - 1;

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] != b.V.F[0])
                   || (a.V.F[1] != b.V.F[1])
                   || (a.V.F[2] != b.V.F[2])
                   || (a.V.F[3] != b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] != b.V.F[0])
                   || (a.V.F[1] != b.V.F[1])
                   || (a.V.F[2] != b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] != b.V.F[0])
                   || (a.V.F[1] != b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] != b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpneq_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return (_mm_movemask_ps(mask) != 0);
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) != expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreater(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] > b.V.F[0])
                   && (a.V.F[1] > b.V.F[1])
                   && (a.V.F[2] > b.V.F[2])
                   && (a.V.F[3] > b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] > b.V.F[0])
                   && (a.V.F[1] > b.V.F[1])
                   && (a.V.F[2] > b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] > b.V.F[0])
                   && (a.V.F[1] > b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] > b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpgt_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsGreaterEqual(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] >= b.V.F[0])
                   && (a.V.F[1] >= b.V.F[1])
                   && (a.V.F[2] >= b.V.F[2])
                   && (a.V.F[3] >= b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] >= b.V.F[0])
                   && (a.V.F[1] >= b.V.F[1])
                   && (a.V.F[2] >= b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] >= b.V.F[0])
                   && (a.V.F[1] >= b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] >= b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmpge_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLess(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] < b.V.F[0])
                   && (a.V.F[1] < b.V.F[1])
                   && (a.V.F[2] < b.V.F[2])
                   && (a.V.F[3] < b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] < b.V.F[0])
                   && (a.V.F[1] < b.V.F[1])
                   && (a.V.F[2] < b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] < b.V.F[0])
                   && (a.V.F[1] < b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] < b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmplt_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool mathcall IsLessEqual(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return (a.V.F[0] <= b.V.F[0])
                   && (a.V.F[1] <= b.V.F[1])
                   && (a.V.F[2] <= b.V.F[2])
                   && (a.V.F[3] <= b.V.F[3]);
        }
        else if constexpr (T::Components == 3)
        {
            return (a.V.F[0] <= b.V.F[0])
                   && (a.V.F[1] <= b.V.F[1])
                   && (a.V.F[2] <= b.V.F[2]);
        }
        else if constexpr (T::Components == 2)
        {
            return (a.V.F[0] <= b.V.F[0])
                   && (a.V.F[1] <= b.V.F[1]);
        }
        else if constexpr (T::Components == 1)
        {
            return (a.V.F[0] <= b.V.F[0]);
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask = _mm_cmple_ps(a.V, b.V);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }

    template <typename T>
    mathinline bool InBounds(T v, T bounds) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                   && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
                   && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]))
                   && ((-bounds.V.F[3] <= v.V.F[3]) && (v.V.F[3] <= bounds.V.F[3]));
        }
        else if constexpr (T::Components == 3)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                   && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]))
                   && ((-bounds.V.F[2] <= v.V.F[2]) && (v.V.F[2] <= bounds.V.F[2]));
        }
        else if constexpr (T::Components == 2)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]))
                   && ((-bounds.V.F[1] <= v.V.F[1]) && (v.V.F[1] <= bounds.V.F[1]));
        }
        else if constexpr (T::Components == 1)
        {
            return ((-bounds.V.F[0] <= v.V.F[0]) && (v.V.F[0] <= bounds.V.F[0]));
        }
#elif GRAPHYTE_HW_AVX
        constexpr uint32_t expected = (1u << T::Components) - 1;

        __m128 const mask_le    = _mm_cmple_ps(v.V, bounds.V);
        __m128 const neg_bounds = _mm_mul_ps(bounds.V, Impl::c_V4_F32_Negative_One.V);
        __m128 const mask_ge    = _mm_cmple_ps(neg_bounds, v.V);
        __m128 const mask       = _mm_and_ps(mask_le, mask_ge);

        if constexpr (T::Components == 4)
        {
            return _mm_movemask_ps(mask) == expected;
        }
        else
        {
            return (_mm_movemask_ps(mask) & expected) == expected;
        }
#endif
    }
}


// =================================================================================================
// Vector specific functions

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Dot(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const fdot
                = (a.V.F[0] * b.V.F[0])
                  + (a.V.F[1] * b.V.F[1])
                  + (a.V.F[2] * b.V.F[2])
                  + (a.V.F[3] * b.V.F[3]);

            Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

            return { result.V };
        }
        else if constexpr (T::Components == 3)
        {
            float const fdot
                = (a.V.F[0] * b.V.F[0])
                  + (a.V.F[1] * b.V.F[1])
                  + (a.V.F[2] * b.V.F[2]);

            Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const fdot
                = (a.V.F[0] * b.V.F[0])
                  + (a.V.F[1] * b.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

            return { result.V };
        }
        else if constexpr (T::Components == 1)
        {
            float const fdot
                = (a.V.F[0] * b.V.F[0]);

            Impl::ConstFloat32x4 const result{ { {
                fdot,
                fdot,
                fdot,
                fdot,
            } } };

            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;
        return { _mm_dp_ps(a.V, b.V, dp_mask) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_dp<T::Components>(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall LengthSquared(T v) noexcept
        requires(Impl::IsVector<T>)
    {
        return Dot<T>(v, v);
    }

    template <typename T>
    mathinline T mathcall Length(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared<T>(v);
        T const length         = Sqrt<T>(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask       = Impl::avx_mm_dp_mask<T::Components>;
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    template <typename T>
    mathinline T mathcall LengthEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared<T>(v);
        T const length         = SqrtEst<T>(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask       = Impl::avx_mm_dp_mask<T::Components>;
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    template <typename T>
    mathinline T mathcall ReciprocalLength(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared(v);
        T const length         = InvSqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask       = Impl::avx_mm_dp_mask<T::Components>;
        __m128 const one            = Impl::c_V4_F32_One.V;
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length         = _mm_sqrt_ps(length_squared);
        __m128 const result         = _mm_div_ps(one, length);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall ReciprocalLengthEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared<T>(v);
        T const length         = InvSqrtEst<T>(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;

        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    template <typename T>
    mathinline T mathcall Distance(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const difference = Subtract(b, a);
        T const result     = Length(difference);
        return result;
    }

    template <typename T>
    mathinline T mathcall DistanceSquared(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const difference = Subtract(b, a);
        T const result     = LengthSquared(difference);
        return result;
    }

    template <typename T>
    mathinline bool mathcall IsUnit(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        // = |v|
        T const length = Length(v);

        // = |v| - 1
        T const difference = Subtract(length, One<T>());

        // = | |v| - 1 |
        T const absdiff = Abs(difference);

        return IsLess(absdiff, T{ Impl::c_V4_F32_Unit_Epsilon.V });
    }

    template <typename T>
    mathinline T mathcall Normalize(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const length     = Length(v).V.F[0];
        float const rcp_length = (length > 1.0f) ? (1.0f / length) : length;

        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * rcp_length,
            v.V.F[1] * rcp_length,
            v.V.F[2] * rcp_length,
            v.V.F[3] * rcp_length,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;

        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length         = _mm_sqrt_ps(length_squared);

        __m128 const zero             = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf  = _mm_cmpneq_ps(length_squared, Impl::c_V4_F32_Positive_Infinity.V);

        __m128 const normalized             = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan            = _mm_andnot_ps(mask_length_inf, Impl::c_V4_F32_Positive_QNan.V);
        __m128 const select_inf             = _mm_and_ps(normalized_masked_zero, mask_length_inf);

        __m128 const result = _mm_or_ps(select_qnan, select_inf);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall NormalizeEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const rcp_length = ReciprocalLength(v);
        T const result     = Multiply(v, rcp_length);
        return result;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;

        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length         = _mm_rsqrt_ps(length_squared);
        __m128 const result         = _mm_mul_ps(length, v.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall ClampLength(T v, T min, T max) noexcept
        requires(Impl::IsVector<T>)
    {
        GX_ASSERT(GetX(min) == GetX(max));

        if constexpr (T::Components >= 2)
        {
            GX_ASSERT(GetY(min) == GetY(max));
        }

        if constexpr (T::Components >= 3)
        {
            GX_ASSERT(GetZ(min) == GetZ(max));
        }

        if constexpr (T::Components >= 4)
        {
            GX_ASSERT(GetW(min) == GetW(max));
        }

        GX_ASSERT(IsGreaterEqual(min, T{ Impl::c_V4_F32_Zero.V }));
        GX_ASSERT(IsGreaterEqual(max, T{ Impl::c_V4_F32_Zero.V }));
        GX_ASSERT(IsGreaterEqual(max, min));

        T const length_squared = LengthSquared(v);
        T const zero           = Zero<T>();

        T const rcp_length = InvSqrt(length_squared);
        auto const mask_inf_length = BitCompareEqual(length_squared, T{ Impl::c_V4_F32_Positive_Infinity.V });
        auto const mask_zero_length = CompareEqual(length_squared, zero);

        T const normal = Multiply(v, rcp_length);
        T const length = Multiply(length_squared, rcp_length);

        auto const select = CompareEqual(mask_inf_length, mask_zero_length);
        T const select_length = Select(length_squared, length, select);
        T const select_normal = Select(length_squared, normal, select);

        auto const control_max = CompareGreater(select_length, max);
        auto const control_min = CompareLess(select_length, min);

        T const clamp_length_0 = Select(select_length, max, control_max);
        T const clamp_length_1 = Select(clamp_length_0, min, control_min);

        T const clamped = Multiply(select_normal, clamp_length_1);
        auto const control = CompareEqual(control_max, control_min);
        T const result     = Select(clamped, v, control);
        return result;
    }

    template <typename T>
    mathinline T mathcall ClampLength(T v, float min, float max) noexcept
        requires(Impl::IsVector<T>)
    {
        T const vmin = Replicate<T>(min);
        T const vmax = Replicate<T>(max);

        return ClampLength(v, vmin, vmax);
    }

    template <typename T>
    mathinline T mathcall Reflect(T incident, T normal) noexcept
        requires(Impl::IsVector<T>)
    {
        T const dot    = Dot(incident, normal);
        T const dot2   = Add(dot, dot);
        T const result = NegateMultiplyAdd(dot2, normal, incident);
        return result;
    }

    template <typename T>
    mathinline T mathcall Refract(T incident, T normal, T index) noexcept
        requires(Impl::IsVector<T>)
    {
        //
        // k = 1.0 - index * index * (1.0 - dot(N, I) * dot(N, I));
        // if (k < 0.0)
        //     R = T(0.0);
        // else
        //     R = index * I - (index * dot(N, I) + sqrt(k)) * N;
        //

        // r0 = i dot n
        T const i_dot_n = Dot(incident, normal);

        T const one{ Impl::c_V4_F32_One.V };

        // r1 = 1 - (r0 * r0)
        T const r1 = NegateMultiplyAdd(i_dot_n, i_dot_n, one);

        // r2 = r1 * index
        T const r2 = Multiply(r1, index);

        // r3 = 1 - (index * r2)
        T const r3 = NegateMultiplyAdd(r2, index, one);

        // Check for zero
        T const zero = Zero<T>();

        if (IsLessEqual(r3, zero))
        {
            // internal refraction
            return zero;
        }
        else
        {
            // r4 = sqrt(r3)
            T const r4 = Sqrt(r3);

            // r5 = (index * i_dot_n) + r4
            T const r5 = MultiplyAdd(index, i_dot_n, r4);

            // r6 = index * incident
            T const r6 = Multiply(index, incident);

            // r7 = r6 - (normal * r5)
            T const r7 = NegateMultiplyAdd(normal, r5, r6);

            return r7;
        }
    }

    template <typename T>
    mathinline T mathcall Refract(T incident, T normal, float index) noexcept
        requires(Impl::IsVector<T>)
    {
        T const vindex = Replicate<T>(index);
        return Refract<T>(incident, normal, vindex);
    }

    template <typename T>
    mathinline T mathcall FaceForward(T normal, T incident, T reference) noexcept
        requires(Impl::IsVector<T>&& T::Components >= 2 && T::Components <= 3)
    {
        T const dot0  = Dot(reference, incident);
        T const sign0 = Sign(dot0);
        T const r0    = Multiply(sign0, Replicate<T>(-1.0f));
        T const r1    = Multiply(normal, r0);
        return r1;
    }

    template <typename T>
    mathinline T mathcall AngleBetweenNormals(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const cos_angle = Dot(a, b);

        // Clamp to acos range
        T const cos_angle_clamped = Clamp<T>(cos_angle, T{ Impl::c_V4_F32_Negative_One.V }, T{ Impl::c_V4_F32_One.V });
        T const angle             = Acos<T>(cos_angle_clamped);

        return angle;
    }

    template <typename T>
    mathinline T mathcall AngleBetweenVectors(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const rcp_length_a = ReciprocalLength(a);
        T const rcp_length_b = ReciprocalLength(b);

        T const a_dot_b       = Dot(a, b);
        T const rcp_len_ab_sq = Multiply(rcp_length_a, rcp_length_b);
        T const cos_angle     = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to acos range
        T const cos_angle_clamped = Clamp(cos_angle, T{ Impl::c_V4_F32_Negative_One.V }, T{ Impl::c_V4_F32_One.V });
        T const angle             = Acos(cos_angle_clamped);

        return angle;
    }
}

// =================================================================================================
// Vector arithmetic

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Cos(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            cosf(v.V.F[0]),
            cosf(v.V.F[1]),
            cosf(v.V.F[2]),
            cosf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cos_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            cosf(components.F[0]),
            cosf(components.F[1]),
            cosf(components.F[2]),
            cosf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Sin(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            sinf(v.V.F[0]),
            sinf(v.V.F[1]),
            sinf(v.V.F[2]),
            sinf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_sin_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            sinf(components.F[0]),
            sinf(components.F[1]),
            sinf(components.F[2]),
            sinf(components.F[3]),
        } } };
        return { result.V };
#endif
    }

    template <typename T>
    mathinline void mathcall SinCos(T& out_sin, T& out_cos, T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const vsin{ { {
            sinf(v.F[0]),
            sinf(v.F[1]),
            sinf(v.F[2]),
            sinf(v.F[3]),
        } } };

        Impl::ConstFloat32x4 const vcos{ { {
            cosf(v.F[0]),
            cosf(v.F[1]),
            cosf(v.F[2]),
            cosf(v.F[3]),
        } } };

        out_sin.V = vsin.V;
        out_cos.V = vcos.V;
#elif GRAPHYTE_MATH_SVML
        out_sin.V = _mm_sincos_ps(&out_cos.V, v.V);
#else
        Impl::ConstFloat32x4 const components{ .V = v };

        Impl::ConstFloat32x4 const vsin{ { {
            sinf(components.F[0]),
            sinf(components.F[1]),
            sinf(components.F[2]),
            sinf(components.F[3]),
        } } };

        Impl::ConstFloat32x4 const vcos{ { {
            cosf(components.F[0]),
            cosf(components.F[1]),
            cosf(components.F[2]),
            cosf(components.F[3]),
        } } };

        out_sin.V = vsin.V;
        out_cos.V = vcos.V;
#endif
    }

    template <typename T>
    mathinline T mathcall Tan(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            tanf(v.V.F[0]),
            tanf(v.V.F[1]),
            tanf(v.V.F[2]),
            tanf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_tan_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            tanf(components.F[0]),
            tanf(components.F[1]),
            tanf(components.F[2]),
            tanf(components.F[3]),
        } } };
        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Asin(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            asinf(v.V.F[0]),
            asinf(v.V.F[1]),
            asinf(v.V.F[2]),
            asinf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_asin_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            asinf(components.F[0]),
            asinf(components.F[1]),
            asinf(components.F[2]),
            asinf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Acos(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            acosf(v.V.F[0]),
            acosf(v.V.F[1]),
            acosf(v.V.F[2]),
            acosf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_acos_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            acosf(components.F[0]),
            acosf(components.F[1]),
            acosf(components.F[2]),
            acosf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Atan(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            atanf(v.V.F[0]),
            atanf(v.V.F[1]),
            atanf(v.V.F[2]),
            atanf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atan_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            atanf(components.F[0]),
            atanf(components.F[1]),
            atanf(components.F[2]),
            atanf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Atan2(T y, T x) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            atan2f(y.V.F[0], x.V.F[0]),
            atan2f(y.V.F[1], x.V.F[1]),
            atan2f(y.V.F[2], x.V.F[2]),
            atan2f(y.V.F[3], x.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atan2_ps(y.V, x.V) };
#else
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const result{ { {
            atan2f(components_y.F[0], components_x.F[0]),
            atan2f(components_y.F[1], components_x.F[1]),
            atan2f(components_y.F[2], components_x.F[2]),
            atan2f(components_y.F[3], components_x.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Sinh(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            sinhf(v.V.F[0]),
            sinhf(v.V.F[1]),
            sinhf(v.V.F[2]),
            sinhf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_sinh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            sinhf(components.F[0]),
            sinhf(components.F[1]),
            sinhf(components.F[2]),
            sinhf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Cosh(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            coshf(v.V.F[0]),
            coshf(v.V.F[1]),
            coshf(v.V.F[2]),
            coshf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cosh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            coshf(components.F[0]),
            coshf(components.F[1]),
            coshf(components.F[2]),
            coshf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Tanh(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            tanhf(v.V.F[0]),
            tanhf(v.V.F[1]),
            tanhf(v.V.F[2]),
            tanhf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_tanh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            tanhf(components.F[0]),
            tanhf(components.F[1]),
            tanhf(components.F[2]),
            tanhf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Asinh(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            asinhf(v.V.F[0]),
            asinhf(v.V.F[1]),
            asinhf(v.V.F[2]),
            asinhf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_asinh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            asinhf(components.F[0]),
            asinhf(components.F[1]),
            asinhf(components.F[2]),
            asinhf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Acosh(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            acoshf(v.V.F[0]),
            acoshf(v.V.F[1]),
            acoshf(v.V.F[2]),
            acoshf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_acosh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            acoshf(components.F[0]),
            acoshf(components.F[1]),
            acoshf(components.F[2]),
            acoshf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Atanh(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            atanhf(v.V.F[0]),
            atanhf(v.V.F[1]),
            atanhf(v.V.F[2]),
            atanhf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_atanh_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            atanhf(components.F[0]),
            atanhf(components.F[1]),
            atanhf(components.F[2]),
            atanhf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Log(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            logf(v.V.F[0]),
            logf(v.V.F[1]),
            logf(v.V.F[2]),
            logf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            logf(components.F[0]),
            logf(components.F[1]),
            logf(components.F[2]),
            logf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Log(T base, T value) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
            logf(value.V.F[0]) / logf(base.V.F[0]),
            logf(value.V.F[1]) / logf(base.V.F[1]),
            logf(value.V.F[2]) / logf(base.V.F[2]),
            logf(value.V.F[3]) / logf(base.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        __m128 const log_value = _mm_log_ps(value.V);
        __m128 const log_base  = _mm_log_ps(base.V);
        __m128 const result    = _mm_div_ps(log_value, log_base);
        return { result };
#else
        Impl::ConstFloat32x4 const components_base{ .V = base.V };
        Impl::ConstFloat32x4 const components_value{ .V = value.V };
        Impl::ConstFloat32x4 const result{ { {
            logf(components_value.F[0]) / logf(components_base.F[0]),
            logf(components_value.F[1]) / logf(components_base.F[1]),
            logf(components_value.F[2]) / logf(components_base.F[2]),
            logf(components_value.F[3]) / logf(components_base.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Log10(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            log10f(v.V.F[0]),
            log10f(v.V.F[1]),
            log10f(v.V.F[2]),
            log10f(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log10_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            log10f(components.F[0]),
            log10f(components.F[1]),
            log10f(components.F[2]),
            log10f(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Log2(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            log2f(v.V.F[0]),
            log2f(v.V.F[1]),
            log2f(v.V.F[2]),
            log2f(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_log2_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            log2f(components.F[0]),
            log2f(components.F[1]),
            log2f(components.F[2]),
            log2f(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            expf(v.V.F[0]),
            expf(v.V.F[1]),
            expf(v.V.F[2]),
            expf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            expf(components.F[0]),
            expf(components.F[1]),
            expf(components.F[2]),
            expf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp10(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            powf(10.0F, v.V.F[0]),
            powf(10.0F, v.V.F[1]),
            powf(10.0F, v.V.F[2]),
            powf(10.0F, v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp10_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            powf(10.0F, components.F[0]),
            powf(10.0F, components.F[1]),
            powf(10.0F, components.F[2]),
            powf(10.0F, components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Exp2(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            exp2f(v.V.F[0]),
            exp2f(v.V.F[1]),
            exp2f(v.V.F[2]),
            exp2f(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_exp2_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            exp2f(components.F[0]),
            exp2f(components.F[1]),
            exp2f(components.F[2]),
            exp2f(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Power(T x, T y) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            powf(x.V.F[0], y.V.F[0]),
            powf(x.V.F[1], y.V.F[1]),
            powf(x.V.F[2], y.V.F[2]),
            powf(x.V.F[3], y.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_pow_ps(x.V, y.V) };
#else
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const result{ { {
            powf(components_x.F[0], components_y.F[0]),
            powf(components_x.F[1], components_y.F[1]),
            powf(components_x.F[2], components_y.F[2]),
            powf(components_x.F[3], components_y.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Hypot(T x, T y) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            hypotf(x.V.F[0], y.V.F[0]),
            hypotf(x.V.F[1], y.V.F[1]),
            hypotf(x.V.F[2], y.V.F[2]),
            hypotf(x.V.F[3], y.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_hypot_ps(x.V, y.V) };
#else
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const result{ { {
            hypotf(components_x.F[0], components_y.F[0]),
            hypotf(components_x.F[1], components_y.F[1]),
            hypotf(components_x.F[2], components_y.F[2]),
            hypotf(components_x.F[3], components_y.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Sqrt(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            sqrtf(v.V.F[0]),
            sqrtf(v.V.F[1]),
            sqrtf(v.V.F[2]),
            sqrtf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const s0 = vrsqrteq_f32(v);
        float32x4_t const p0 = vmulq_f32(v, s0);
        float32x4_t const r0 = vrsqrtsq_f32(p0, s0);

        float32x4_t const s1 = vmulq_f32(s0, r0);
        float32x4_t const p1 = vmulq_f32(v, s1);
        float32x4_t const r1 = vrsqrtsq_f32(p1, s1);

        float32x4_t const s2 = vmulq_f32(s1, r1);
        float32x4_t const p2 = vmulq_f32(v, s2);
        float32x4_t const r2 = vrsqrtsq_f32(p2, s2);

        float32x4_t const s3 = vmulq_f32(s2, r2);

        uint32x4_t const inf_mask      = vceqq_u32(vreinterpretq_u32_f32(v), vdupq_n_u32(0x7F800000U));
        uint32x4_t const zero_mask     = vceqq_f32(v, vdupq_n_f32(0.0F));
        float32x4_t const result       = vmulq_f32(v, s3);
        uint32x4_t const select_mask   = vceqq_u32(inf_mask, zero_mask);
        float32x4_t const final_result = vbslq_f32(select_mask, result, v);
        return { final_result };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall SqrtEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
            sqrtf(v.V.F[0]),
            sqrtf(v.V.F[1]),
            sqrtf(v.V.F[2]),
            sqrtf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall InvSqrt(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F / sqrtf(v.V.F[0]),
            1.0F / sqrtf(v.V.F[1]),
            1.0F / sqrtf(v.V.F[2]),
            1.0F / sqrtf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        // Newton-Raphson x2
        float32x4_t const s0 = vrsqrteq_f32(v);

        float32x4_t const p0 = vmulq_f32(v, s0);
        float32x4_t const r0 = vrsqrtsq_f32(p0, s0);

        float32x4_t const s1 = vmulq_f32(s0, r0);
        float32x4_t const p1 = vmulq_f32(v, s1);
        float32x4_t const r1 = vrsqrtsq_f32(p1, s1);

        float32x4_t const r = vmulq_f32(s1, r1);
        return { r };
#elif GRAPHYTE_HW_AVX
        __m128 const partial = _mm_sqrt_ps(v.V);
        __m128 const result  = _mm_div_ps(Impl::c_V4_F32_One.V, partial);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall InvSqrtEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F / sqrtf(v.V.F[0]),
            1.0F / sqrtf(v.V.F[1]),
            1.0F / sqrtf(v.V.F[2]),
            1.0F / sqrtf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rsqrt_ps(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Cbrt(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            cbrtf(v.V.F[0]),
            cbrtf(v.V.F[1]),
            cbrtf(v.V.F[2]),
            cbrtf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_cbrt_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            cbrtf(components.F[0]),
            cbrtf(components.F[1]),
            cbrtf(components.F[2]),
            cbrtf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall InvCbrt(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F / cbrtf(v.V.F[0]),
            1.0F / cbrtf(v.V.F[1]),
            1.0F / cbrtf(v.V.F[2]),
            1.0F / cbrtf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_invcbrt_ps(v.V) };
#else
        Impl::ConstFloat32x4 const components{ .V = v.V };
        Impl::ConstFloat32x4 const result{ { {
            1.0F / cbrtf(components.F[0]),
            1.0F / cbrtf(components.F[1]),
            1.0F / cbrtf(components.F[2]),
            1.0F / cbrtf(components.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Abs(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            fabsf(v.V.F[0]),
            fabsf(v.V.F[1]),
            fabsf(v.V.F[2]),
            fabsf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        return { vabsq_f32(v.V) };
#elif GRAPHYTE_HW_AVX
        __m128 const zero     = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const result   = _mm_max_ps(negative, v.V);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Negate(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            -v.V.F[0],
            -v.V.F[1],
            -v.V.F[2],
            -v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zero   = _mm_setzero_ps();
        __m128 const result = _mm_sub_ps(zero, v.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vnegq_f32(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Add(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] + b.V.F[0],
            a.V.F[1] + b.V.F[1],
            a.V.F[2] + b.V.F[2],
            a.V.F[3] + b.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_add_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vaddq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Subtract(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] - b.V.F[0],
            a.V.F[1] - b.V.F[1],
            a.V.F[2] - b.V.F[2],
            a.V.F[3] - b.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vsubq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Multiply(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] * b.V.F[0],
            a.V.F[1] * b.V.F[1],
            a.V.F[2] * b.V.F[2],
            a.V.F[3] * b.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vmulq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Multiply(T a, float b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] * b,
            a.V.F[1] * b,
            a.V.F[2] * b,
            a.V.F[3] * b,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_set_ps1(b);
        return { _mm_mul_ps(a.V, s) };
#elif GRAPHYTE_HW_NEON
        return { vmulq_n_f32(a.V, b) };
#endif
    }

    template <typename T>
    mathinline T mathcall Reciprocal(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            1.0F / v.V.F[0],
            1.0F / v.V.F[1],
            1.0F / v.V.F[2],
            1.0F / v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rcp_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        float32x4_t const one    = vdupq_n_f32(1.0F);
        float32x4_t const result = vdivq_f32(one, v.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Divide(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] / b.V.F[0],
            a.V.F[1] / b.V.F[1],
            a.V.F[2] / b.V.F[2],
            a.V.F[3] / b.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vdivq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Divide(T a, float b) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const invb = 1.0F / b;

        Impl::ConstFloat32x4 const result{ { {
            a.V.F[0] * invb,
            a.V.F[1] * invb,
            a.V.F[2] * invb,
            a.V.F[3] * invb,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        return { vdivq_n_f32(a.V, b) };
#elif GRAPHYTE_HW_AVX
        __m128 const invb = _mm_set_ps1(1.0F / b);
        return { _mm_mul_ps(a.V, invb) };
#endif
    }

    // (a * b) + c
    template <typename T>
    mathinline T mathcall MultiplyAdd(T a, T b, T c) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (a.V.F[0] * b.V.F[0]) + c.V.F[0],
            (a.V.F[1] * b.V.F[1]) + c.V.F[1],
            (a.V.F[2] * b.V.F[2]) + c.V.F[2],
            (a.V.F[3] * b.V.F[3]) + c.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fmadd_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fmadd_f32x4(a.V, b.V, c.V) };
#endif
    }

    // (a * b) - c
    template <typename T>
    mathinline T mathcall MultiplySubtract(T a, T b, T c) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (a.V.F[0] * b.V.F[0]) - c.V.F[0],
            (a.V.F[1] * b.V.F[1]) - c.V.F[1],
            (a.V.F[2] * b.V.F[2]) - c.V.F[2],
            (a.V.F[3] * b.V.F[3]) - c.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fmsub_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fmsub_f32x4(a.V, b.V, c.V) };
#endif
    }

    // -(a * b) + c
    template <typename T>
    mathinline T mathcall NegateMultiplyAdd(T a, T b, T c) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            -(a.V.F[0] * b.V.F[0]) + c.V.F[0],
            -(a.V.F[1] * b.V.F[1]) + c.V.F[1],
            -(a.V.F[2] * b.V.F[2]) + c.V.F[2],
            -(a.V.F[3] * b.V.F[3]) + c.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fnmadd_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fnmadd_f32x4(a.V, b.V, c.V) };
#endif
    }

    // -(a * b) - c
    template <typename T>
    mathinline T mathcall NegateMultiplySubtract(T a, T b, T c) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            -(a.V.F[0] * b.V.F[0]) - c.V.F[0],
            -(a.V.F[1] * b.V.F[1]) - c.V.F[1],
            -(a.V.F[2] * b.V.F[2]) - c.V.F[2],
            -(a.V.F[3] * b.V.F[3]) - c.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::avx_fnmsub_f32x4(a.V, b.V, c.V) };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_fnmsub_f32x4(a.V, b.V, c.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Square(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * v.V.F[0],
            v.V.F[1] * v.V.F[1],
            v.V.F[2] * v.V.F[2],
            v.V.F[3] * v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        return { vmulq_f32(v.V, v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(v.V, v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall SignedSquare(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * fabsf(v.V.F[0]),
            v.V.F[1] * fabsf(v.V.F[1]),
            v.V.F[2] * fabsf(v.V.F[2]),
            v.V.F[3] * fabsf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const r0 = vabsq_f32(v.V);
        float32x4_t const r1 = vmulq_f32(r0, v.V);
        return { r1 };
#elif GRAPHYTE_HW_AVX
        __m128 const zero     = _mm_setzero_ps();
        __m128 const negative = _mm_sub_ps(zero, v.V);
        __m128 const abs      = _mm_max_ps(negative, v.V);
        __m128 const result   = _mm_mul_ps(abs, v.V);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Cube(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0] * v.V.F[0] * v.V.F[0],
            v.V.F[1] * v.V.F[1] * v.V.F[1],
            v.V.F[2] * v.V.F[2] * v.V.F[2],
            v.V.F[3] * v.V.F[3] * v.V.F[3],
        } } };
#elif GRAPHYTE_HW_NEON
        float32x4_t const r0 = vmulq_f32(v.V, v.V);
        float32x4_t const r1 = vmulq_f32(r0, v.V);
        return { r1 };
#elif GRAPHYTE_HW_AVX
        __m128 const v2 = _mm_mul_ps(v.V, v.V);
        __m128 const v3 = _mm_mul_ps(v.V, v2);
        return { v3 };
#endif
    }
}


// =================================================================================================
// Interpolation

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Lerp(T a, T b, T t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const length = Subtract(b, a);
        Vector4 const result = MultiplyAdd(length, t, a);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_sub_ps(b.V, a.V);
        __m128 const result = Impl::avx_fmadd_f32x4(length, t.V, a.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Lerp(T a, T b, float t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const scale  = Replicate<Vector4>(t);
        Vector4 const length = Subtract(b, a);
        Vector4 const result = MultiplyAdd(length, scale, a);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const length = _mm_sub_ps(b.V, a.V);
        __m128 const scale  = _mm_set_ps1(t);
        __m128 const result = Impl::avx_fmadd_f32x4(length, scale, a.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall LerpPrecise(T a, T b, T t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        // r0 = t * b
        T const t_mul_b = Multiply(t, b);
        // r1 = 1 - t
        T const one_minus_t = Subtract(T{ Impl::c_V4_F32_One.V }, t);
        // (r1 * a) + r0 === ((1 - t) * a) + (t * b)
        T const result = MultiplyAdd(one_minus_t, a, t_mul_b);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const t_mul_b     = _mm_mul_ps(t.V, b.V);
        __m128 const one_minus_t = _mm_sub_ps(Impl::c_V4_F32_One.V, t.V);
        __m128 const result      = Impl::avx_fmadd_f32x4(one_minus_t, a.V, t_mul_b);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall LerpPrecise(T a, T b, float t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const t_mul_b = Multiply(Replicate<T>(t), b);
        T const result  = MultiplyAdd(Replicate<T>(1.0f - t), a, t_mul_b);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const vone_minus_t = _mm_set_ps1(1.0f - t);
        __m128 const vt           = _mm_set_ps1(t);

        // (1 - t) * b
        __m128 const t_mul_b = _mm_mul_ps(vt, b.V);
        // ((1 - t) * b) + (t * a)
        __m128 const result = Impl::avx_fmadd_f32x4(vone_minus_t, a.V, t_mul_b);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, float t) noexcept
        requires(Impl::IsVector<T>)
    {
        float const t2 = t * t;
        float const t3 = t * t2;

        T const p0 = Replicate<T>(2.0F * t3 - 3.0F * t2 + 1.0F);
        T const t0 = Replicate<T>(t3 - 2.0F * t2 + t);
        T const p1 = Replicate<T>(-2.0F * t3 + 3.0F * t2);
        T const t1 = Replicate<T>(t3 - t2);

        T const r0 = Multiply(p0, position0);
        T const r1 = MultiplyAdd(t0, tangent0, r0);
        T const r2 = MultiplyAdd(p1, position1, r1);
        T const r3 = MultiplyAdd(t1, tangent1, r2);

        return { r3 };
    }

    template <typename T>
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, T t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const t2 = Multiply(t, t);
        T const t3 = Multiply(t, t2);

        T const p0 = Replicate<T>(2.0F * t3.V.F[0] - 3.0F * t2.V.F[0] + 1.0F);
        T const t0 = Replicate<T>(t3.V.F[1] - 2.0F * t2.V.F[1] + t.V.F[1]);
        T const p1 = Replicate<T>(-2.0F * t3.V.F[2] + 3.0F * t2.V.F[2]);
        T const t1 = Replicate<T>(t3.V.F[2] - t2.V.F[2]);

        T const r0 = Multiply(p0, position0);
        T const r1 = MultiplyAdd(t0, tangent0, r0);
        T const r2 = MultiplyAdd(p1, position1, r1);
        T const r3 = MultiplyAdd(t1, tangent1, r2);

        return { r3 };

#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const catmul_t2{ { {
            -3.0F,
            -2.0F,
            +3.0F,
            -1.0F,
        } } };

        static Impl::ConstFloat32x4 const catmul_t3{ { {
            +2.0F,
            +1.0F,
            -2.0F,
            +1.0F,
        } } };

        __m128 const t2 = _mm_mul_ps(t.V, t.V);
        __m128 const t3 = _mm_mul_ps(t2, t.V);

        __m128 const t2_m = _mm_mul_ps(t2, catmul_t2.V);
        __m128 const t3_m = _mm_mul_ps(t3, catmul_t3.V);

        __m128 const t2t3_ma = _mm_add_ps(t2_m, t3_m);
        __m128 const ty      = _mm_and_ps(t.V, Impl::c_V4_U32_Mask_0100.V);
        __m128 const t2t3ty  = _mm_add_ps(t2t3_ma, ty);
        __m128 const tfinal  = _mm_add_ps(t2t3ty, Impl::c_V4_F32_PositiveUnitX.V);

        __m128 const r0 = _mm_permute_ps(tfinal, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const f0 = _mm_mul_ps(r0, position0.V);

        __m128 const r1 = _mm_permute_ps(tfinal, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const f1 = Impl::avx_fmadd_f32x4(r1, tangent0.V, f0);

        __m128 const r2 = _mm_permute_ps(tfinal, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const f2 = Impl::avx_fmadd_f32x4(r2, position1.V, f1);

        __m128 const r3 = _mm_permute_ps(tfinal, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const f3 = Impl::avx_fmadd_f32x4(r3, tangent1.V, f2);

        return { f3 };
#endif
    }

    template <typename T>
    mathinline T mathcall Barycentric(T a, T b, T c, float f, float g) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const pba    = Subtract(b, a);
        T const pca    = Subtract(c, a);
        T const sf     = Replicate<T>(f);
        T const sg     = Replicate<T>(g);
        T const accum  = MultiplyAdd(pba, sf, a);
        T const result = MultiplyAdd(pca, sg, accum);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const pba = _mm_sub_ps(b.V, a.V);
        __m128 const pca = _mm_sub_ps(c.V, a.V);
        __m128 const sf  = _mm_set_ps1(f);
        __m128 const sg  = _mm_set_ps1(g);

        __m128 const accum  = Impl::avx_fmadd_f32x4(pba, sf, a.V);
        __m128 const result = Impl::avx_fmadd_f32x4(pca, sg, accum);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const pba    = vsubq_f32(b.V, a.V);
        float32x4_t const pca    = vsubq_f32(c.V, a.V);
        float32x4_t const accum  = vmlaq_n_f32(a.V, pba.V, f);
        float32x4_t const result = vmlaq_n_f32(accum, pca, g);
        return { result };
#endif
    }


    template <typename T>
    mathinline T mathcall Barycentric(T a, T b, T c, T f, T g) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const pba    = Subtract(b, a);
        T const pca    = Subtract(c, a);
        T const accum  = MultiplyAdd(pba, f, a);
        T const result = MultiplyAdd(pca, g, accum);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const pba    = _mm_sub_ps(b.V, a.V);
        __m128 const pca    = _mm_sub_ps(c.V, a.V);
        __m128 const accum  = Impl::avx_fmadd_f32x4(pba, f.V, a.V);
        __m128 const result = Impl::avx_fmadd_f32x4(pca, g.V, accum);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const pba    = vsubq_f32(b.V, a.V);
        float32x4_t const pca    = vsubq_f32(c.V, a.V);
        float32x4_t const accum  = vmlaq_f32(a.V, pba, f.V);
        float32x4_t const result = vmlaq_f32(accum, pca, g.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall CatmullRom(T p0, T p1, T p2, T p3, float t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const t2 = t * t;
        float const t3 = t * t2;

        T const f0 = Replicate<T>((-t3 + 2.0F * t2 - t) * 0.5F);
        T const f1 = Replicate<T>((3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F);
        T const f2 = Replicate<T>((-3.0F * t3 + 4.0F * t2 + t) * 0.5F);
        T const f3 = Replicate<T>((t3 - t2) * 0.5F);

        T const r0 = Multiply(f0, p0);
        T const r1 = MultiplyAdd(f1, p1, r0);
        T const r2 = MultiplyAdd(f2, p2, r1);
        T const r3 = MultiplyAdd(f3, p3, r2);

        return r3;
#elif GRAPHYTE_HW_AVX
        float const t2 = t * t;
        float const t3 = t * t2;

        __m128 const f0 = _mm_set_ps1((-t3 + 2.0F * t2 - t) * 0.5F);
        __m128 const f1 = _mm_set_ps1((3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F);
        __m128 const f2 = _mm_set_ps1((-3.0F * t3 + 4.0F * t2 + t) * 0.5F);
        __m128 const f3 = _mm_set_ps1((t3 - t2) * 0.5F);

        __m128 const r0 = _mm_mul_ps(f0, p0.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(f1, p1.V, r0);
        __m128 const r2 = Impl::avx_fmadd_f32x4(f2, p2.V, r1);
        __m128 const r3 = Impl::avx_fmadd_f32x4(f3, p3.V, r2);

        return { r3 };
#endif
    }

    template <typename T>
    mathinline T mathcall CatmullRom(T p0, T p1, T p2, T p3, T t) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = t.V.F[0];
        float const fy = t.V.F[1];
        float const fz = t.V.F[2];
        float const fw = t.V.F[3];

        float const dx
            = 0.5F * ((-fx * fx * fx + 2.0F * fx * fx - fx) * p0.V.F[0] + (3.0F * fx * fx * fx - 5.0F * fx * fx + 2.0F) * p1.V.F[0] + (-3.0F * fx * fx * fx + 4.0F * fx * fx + fx) * p2.V.F[0] + (fx * fx * fx - fx * fx) * p3.V.F[0]);


        float const dy
            = 0.5F * ((-fy * fy * fy + 2.0F * fy * fy - fy) * p0.V.F[1] + (3.0F * fy * fy * fy - 5.0F * fy * fy + 2.0F) * p1.V.F[1] + (-3.0F * fy * fy * fy + 4.0F * fy * fy + fy) * p2.V.F[1] + (fy * fy * fy - fy * fy) * p3.V.F[1]);

        float const dz
            = 0.5F * ((-fz * fz * fz + 2.0F * fz * fz - fz) * p0.V.F[2] + (3.0F * fz * fz * fz - 5.0F * fz * fz + 2.0F) * p1.V.F[2] + (-3.0F * fz * fz * fz + 4.0F * fz * fz + fz) * p2.V.F[2] + (fz * fz * fz - fz * fz) * p3.V.F[2]);

        float const dw
            = 0.5F * ((-fw * fw * fw + 2.0F * fw * fw - fw) * p0.V.F[3] + (3.0F * fw * fw * fw - 5.0F * fw * fw + 2.0F) * p1.V.F[3] + (-3.0F * fw * fw * fw + 4.0F * fw * fw + fw) * p2.V.F[3] + (fw * fw * fw - fw * fw) * p3.V.F[3]);


        Impl::ConstFloat32x4 const result{ { {
            dx,
            dy,
            dz,
            dw,
        } } };

        return { result.V };

#elif GRAPHYTE_HW_AVX

        static Impl::ConstFloat32x4 const catmul2{ { { 2.0F, 2.0F, 2.0F, 2.0F } } };
        static Impl::ConstFloat32x4 const catmul3{ { { 3.0F, 3.0F, 3.0F, 3.0F } } };
        static Impl::ConstFloat32x4 const catmul4{ { { 4.0F, 4.0F, 4.0F, 4.0F } } };
        static Impl::ConstFloat32x4 const catmul5{ { { 5.0F, 5.0F, 5.0F, 5.0F } } };

        __m128 t2 = _mm_mul_ps(t.V, t.V);
        __m128 t3 = _mm_mul_ps(t.V, t2);

        // p0
        __m128 result = _mm_add_ps(t2, t2);
        result        = _mm_sub_ps(result, t.V);
        result        = _mm_sub_ps(result, t3);
        result        = _mm_mul_ps(result, p0.V);

        // p1
        __m128 temp  = _mm_mul_ps(t3, catmul3.V);
        __m128 temp2 = _mm_mul_ps(t2, catmul5.V);
        temp         = _mm_sub_ps(temp, temp2);
        temp         = _mm_add_ps(temp, catmul2.V);
        temp         = _mm_mul_ps(temp, p1.V);
        result       = _mm_add_ps(result, temp);

        // p2
        temp   = _mm_mul_ps(t2, catmul4.V);
        temp2  = _mm_mul_ps(t3, catmul3.V);
        temp   = _mm_sub_ps(temp, temp2);
        temp   = _mm_add_ps(temp, t.V);
        temp   = _mm_mul_ps(temp, p2.V);
        result = _mm_add_ps(result, temp);

        // p3
        t3     = _mm_sub_ps(t3, t2);
        t3     = _mm_mul_ps(t3, p3.V);
        result = _mm_add_ps(result, t3);

        // final result
        result = _mm_mul_ps(result, Impl::c_V4_F32_One_Half.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Remap(T value, T from_min, T from_max, T to_min, T to_max) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const from_abs     = Subtract(value, from_min);
        T const from_max_abs = Subtract(from_max, from_min);

        T const normal = Divide(from_abs, from_max_abs);

        T const to_max_abs = Subtract(to_max, to_min);

        T const to = MultiplyAdd(to_max_abs, normal, to_min);

        return to;
#elif GRAPHYTE_HW_AVX
        __m128 const from_abs     = _mm_sub_ps(value.V, from_min.V);
        __m128 const from_max_abs = _mm_sub_ps(from_max.V, from_min.V);

        __m128 const normal = _mm_div_ps(from_abs, from_max_abs);

        __m128 const to_max_abs = _mm_sub_ps(to_max.V, to_min.V);
        __m128 const to         = Impl::avx_fmadd_f32x4(to_max_abs, normal, to_min.V);

        return { to };
#endif
    }

    template <typename T>
    mathinline T mathcall Unlerp(T value, T min, T max) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const base   = Subtract(value, min);
        T const range  = Subtract(max, min);
        T const result = Divide(base, range);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const base   = _mm_sub_ps(value.V, min.V);
        __m128 const range  = _mm_sub_ps(max.V, min.V);
        __m128 const result = _mm_div_ps(base, range);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall SmoothStep(T a, T b, T x) noexcept
        requires(Impl::IsVector<T>)
    {
        T const length = Subtract(x, a);
        T const base   = Subtract(b, a);
        T const t      = Divide(length, base);
        T const r0     = NegativeMultiplyAdd(t, Replicate<T>(2.0f), Replicate<T>(3.0f));
        T const r1     = Multiply(r0, t);
        T const r2     = Multiply(r1, t);
        return r2;
    }

    template <typename T>
    mathinline T mathcall SmoothStep(T a, T b, float x) noexcept
        requires(Impl::IsVector<T>)
    {
        return SmoothStep(a, b, Replicate<T>(x));
    }

    template <typename T>
    mathinline T mathcall MoveTowards(T current, T target, float max_distance) noexcept
        requires(Impl::IsVector<T>)
    {
        T const diff   = Subtract(target, current);
        T const length = Length(diff);
        T const vmax   = Replicate<T>(max_distance);

        if (IsLessEqual(length, vmax) || IsZero(length))
        {
            return target;
        }

        return MultiplyAdd(current, Divide(diff, length), vmax);
    }
}


// =================================================================================================
// Vector4 functions

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall FresnelTerm(T cos_incident_angle, T refraction_index) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        // c = cos_incident_angle
        // g = sqrt(c^2 + refraction_index^2 - 1)
        // r = 0.5f * (g - c)^2 / (g + c)^2 * ((c * (g + c) - 1)^2 / (c * (g - c) + 1)^2 + 1)

        GX_ASSERT(!IsInfinity(cos_incident_angle));

#if GRAPHYTE_MATH_NO_INTRINSICS

        // = refraction_index^2 - 1
        Vector4 const g0 = MultiplyAdd(refraction_index, refraction_index, Vector4{ Impl::c_V4_F32_Negative_One.V });

        // = c^2 + refraction_index^2 - 1
        Vector4 const g1 = MultiplyAdd(cos_incident_angle, cos_incident_angle, g0);
        Vector4 const g2 = Abs(g1);
        Vector4 const g3 = Sqrt(g2);

        // = (g + c)^2
        Vector4 const s0 = Add(g3, cos_incident_angle);
        Vector4 const s1 = Multiply(s0, s0);

        // = (g - c)^2
        Vector4 const d0 = Subtract(g3, cos_incident_angle);
        Vector4 const d1 = Multiply(d0, d0);

        // = 0.5f * (g - c)^2 / (g + c)^2
        Vector4 const rcp_s1  = Reciprocal(s1);
        Vector4 const half_d1 = Multiply(Vector4{ Impl::c_V4_F32_One_Half.V }, d1);
        Vector4 const r0      = Multiply(half_d1, rcp_s1);

        // = (c * (g + c) - 1)^2
        Vector4 const ca0 = MultiplyAdd(cos_incident_angle, s0, Vector4{ Impl::c_V4_F32_Negative_One.V });
        Vector4 const ca1 = Multiply(ca0, ca0);

        // = (c * (g - c) + 1)^2
        Vector4 const cb0 = MultiplyAdd(cos_incident_angle, d0, Vector4{ Impl::c_V4_F32_One.V });
        Vector4 const cb1 = Multiply(cb0, cb0);
        Vector4 const cb2 = Reciprocal(cb1);

        Vector4 const r1 = MultiplyAdd(ca1, cb2, Vector4{ Impl::c_V4_F32_One.V });
        Vector4 const r2 = Multiply(r0, r1);
        Vector4 const r3 = Saturate(r2);

        return r3;

#elif GRAPHYTE_HW_AVX

        __m128 const one = Impl::c_V4_F32_One.V;

        // NOTE: possible optimization; instead of storing `zero` in register whole time, we may insert it later
        __m128 const zero = _mm_setzero_ps();

        // = c^2 + refraction_index^2 - 1
        __m128 const g0 = Impl::avx_fmsub_f32x4(refraction_index.V, refraction_index.V, one);
        __m128 const g1 = Impl::avx_fmadd_f32x4(cos_incident_angle.V, cos_incident_angle.V, g0);
        __m128 const g2 = _mm_sub_ps(zero, g1);
        __m128 const g3 = _mm_max_ps(g2, g1);
        __m128 const g4 = _mm_sqrt_ps(g3);

        // s = (g + c)^2
        // d = (g - c)^2
        __m128 const s0 = _mm_add_ps(g4, cos_incident_angle.V);
        __m128 const d0 = _mm_sub_ps(g4, cos_incident_angle.V);
        __m128 const s1 = _mm_mul_ps(s0, s0);
        __m128 const d1 = _mm_mul_ps(d0, d0);

        // = 0.5f * (g - c)^2 / (g + c)^2
        __m128 const half_d1 = _mm_mul_ps(d1, Impl::c_V4_F32_One_Half.V);
        __m128 const r0      = _mm_div_ps(half_d1, s1);

        // = (c * (g + c) - 1)^2
        __m128 const ca0 = Impl::avx_fmsub_f32x4(cos_incident_angle.V, s0, one);
        __m128 const ca1 = _mm_mul_ps(ca0, ca0);

        // = (c * (g - c) + 1)^2
        __m128 const cb0 = Impl::avx_fmadd_f32x4(cos_incident_angle.V, d0, one);
        __m128 const cb1 = _mm_mul_ps(cb0, cb0);

        __m128 const r1 = _mm_div_ps(ca1, cb1);
        __m128 const r2 = _mm_add_ps(r1, one);
        __m128 const r3 = _mm_mul_ps(r0, r2);

        __m128 const rmin = _mm_max_ps(r3, zero);
        __m128 const rmax = _mm_min_ps(rmin, one);
        return { rmax };
#endif
    }

    mathinline Vector4 mathcall Cross(Vector4 a, Vector4 b, Vector4 c) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (((b.V.F[2] * c.V.F[3]) - (b.V.F[3] * c.V.F[2])) * a.V.F[1]) - (((b.V.F[1] * c.V.F[3]) - (b.V.F[3] * c.V.F[1])) * a.V.F[2]) + (((b.V.F[1] * c.V.F[2]) - (b.V.F[2] * c.V.F[1])) * a.V.F[3]),
            (((b.V.F[3] * c.V.F[2]) - (b.V.F[2] * c.V.F[3])) * a.V.F[0]) - (((b.V.F[3] * c.V.F[0]) - (b.V.F[0] * c.V.F[3])) * a.V.F[2]) + (((b.V.F[2] * c.V.F[0]) - (b.V.F[0] * c.V.F[2])) * a.V.F[3]),
            (((b.V.F[1] * c.V.F[3]) - (b.V.F[3] * c.V.F[1])) * a.V.F[0]) - (((b.V.F[0] * c.V.F[3]) - (b.V.F[3] * c.V.F[0])) * a.V.F[1]) + (((b.V.F[0] * c.V.F[1]) - (b.V.F[1] * c.V.F[0])) * a.V.F[3]),
            (((b.V.F[2] * c.V.F[1]) - (b.V.F[1] * c.V.F[2])) * a.V.F[0]) - (((b.V.F[2] * c.V.F[0]) - (b.V.F[0] * c.V.F[2])) * a.V.F[1]) + (((b.V.F[1] * c.V.F[0]) - (b.V.F[0] * c.V.F[1])) * a.V.F[2]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        // r0 = ((b.zwyz * c.wzwy) - (b.wzwy * c.zwyz)) * a.yxxx

        __m128 const b0 = _mm_permute_ps(b.V, _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const c0 = _mm_permute_ps(c.V, _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const m0 = _mm_mul_ps(b0, c0);

        __m128 const b1 = _mm_permute_ps(b.V, _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const c1 = _mm_permute_ps(c0, _MM_SHUFFLE(1, 3, 0, 1)); // wzwy -> zwyz
        __m128 const m1 = _mm_mul_ps(b1, c1);

        __m128 const s0 = _mm_sub_ps(m0, m1);
        __m128 const a0 = _mm_permute_ps(a.V, _MM_SHUFFLE(0, 0, 0, 1));
        __m128 const r0 = _mm_mul_ps(s0, a0);

        // r1 = ((b.ywxz * c.wxwx) - (b.wxwx * c.ywxz)) * a.zzyy
        __m128 const b2 = _mm_permute_ps(b.V, _MM_SHUFFLE(2, 0, 3, 1));
        __m128 const c2 = _mm_permute_ps(c.V, _MM_SHUFFLE(0, 3, 0, 3));
        __m128 const m2 = _mm_mul_ps(b2, c2);

        __m128 const b3 = _mm_permute_ps(b2, _MM_SHUFFLE(2, 1, 2, 1)); // ywxz -> wxwx
        __m128 const c3 = _mm_permute_ps(c.V, _MM_SHUFFLE(2, 0, 3, 1));
        __m128 const m3 = _mm_mul_ps(b3, c3);

        __m128 const s1 = _mm_sub_ps(m2, m3);
        __m128 const a1 = _mm_permute_ps(a.V, _MM_SHUFFLE(1, 1, 2, 2));
        __m128 const r1 = _mm_mul_ps(s1, a1);

        // t0 = r0 - r1
        __m128 const t0 = _mm_sub_ps(r0, r1);

        // r2 = ((b.yzxy * c.zxyx) - (b.zxyx * c.yzxy)) * a.wwwz
        __m128 const b4 = _mm_permute_ps(b.V, _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const c4 = _mm_permute_ps(c.V, _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const m4 = _mm_mul_ps(b4, c4);

        // yzxy ->  zxyx
        __m128 const b5 = _mm_permute_ps(b4, _MM_SHUFFLE(2, 0, 2, 1));
        __m128 const c5 = _mm_permute_ps(c.V, _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const m5 = _mm_mul_ps(b5, c5);

        __m128 const s2 = _mm_sub_ps(m4, m5);
        __m128 const a2 = _mm_permute_ps(a.V, _MM_SHUFFLE(2, 3, 3, 3));
        __m128 const r2 = _mm_mul_ps(s2, a2);

        // t1 = t0 + r2
        __m128 const result = _mm_add_ps(t0, r2);

        return { result };
#endif
    }

    mathinline Vector4 mathcall Orthogonal(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[2],
            v.V.F[3],
            -v.V.F[0],
            -v.V.F[1],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const flip_zw{ { {
            1.0F,
            1.0F,
            -1.0F,
            -1.0F,
        } } };

        __m128 const zwxy   = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 0, 3, 2));
        __m128 const result = _mm_mul_ps(zwxy, flip_zw.V);
        return { result };
#endif
    }

    mathinline Vector4 mathcall Transform(Vector4 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const fx = (m.M.M[0][0] * v.V.F[0]) + (m.M.M[1][0] * v.V.F[1]) + (m.M.M[2][0] * v.V.F[2]) + (m.M.M[3][0] * v.V.F[3]);
        float const fy = (m.M.M[0][1] * v.V.F[0]) + (m.M.M[1][1] * v.V.F[1]) + (m.M.M[2][1] * v.V.F[2]) + (m.M.M[3][1] * v.V.F[3]);
        float const fz = (m.M.M[0][2] * v.V.F[0]) + (m.M.M[1][2] * v.V.F[1]) + (m.M.M[2][2] * v.V.F[2]) + (m.M.M[3][2] * v.V.F[3]);
        float const fw = (m.M.M[0][3] * v.V.F[0]) + (m.M.M[1][3] * v.V.F[1]) + (m.M.M[2][3] * v.V.F[2]) + (m.M.M[3][3] * v.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
            fx,
            fy,
            fz,
            fw,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r0   = _mm_mul_ps(wwww, m.M.R[3]);
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r1   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], r0);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r2   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r1);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r3   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r2);
        return { r3 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const x  = vmulq_lane_f32(m.M.R[0], xy, 0);
        float32x4_t const y  = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x2_t const zw = vget_high_f32(v.V);
        float32x4_t const z  = vmlaq_lane_f32(y, m.M.R[2], zw, 0);
        float32x4_t const w  = vmlaq_lane_f32(z, m.M.R[3], zw, 1);
        return { w };
#endif
    }
}


// =================================================================================================
// Vector3 functions

namespace Graphyte::Maths
{
    mathinline Vector3 mathcall Cross(Vector3 a, Vector3 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (a.V.F[1] * b.V.F[2]) - (a.V.F[2] * b.V.F[1]),
            (a.V.F[2] * b.V.F[0]) - (a.V.F[0] * b.V.F[2]),
            (a.V.F[0] * b.V.F[1]) - (a.V.F[1] * b.V.F[0]),
            0.0F,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        // = [x, y]
        float32x2_t const a_xy = vget_low_f32(a.V);
        float32x2_t const b_xy = vget_low_f32(b.V);

        // = [y, x]
        float32x2_t const a_yx = vrev64_f32(a_xy);
        float32x2_t const b_yx = vrev64_f32(b_xy);

        // = [z, z]
        float32x2_t const a_zz = vdup_lane_f32(vget_high_f32(a.V), 0);
        float32x2_t const b_zz = vdup_lane_f32(vget_high_f32(b.V), 0);

        // = [y, x, x, y]
        float32x4_t const a_yxxy = vcombine_f32(a_yx, a_xy);
        float32x4_t const b_yxxy = vcombine_f32(b_yx, b_xy);

        // = [z, z, y, x]
        float32x4_t const b_zzyx = vcombine_f32(b_zz, b_yx);
        float32x4_t const a_zzyx = vcombine_f32(a_zz, a_yx);

        // = [
        //      a.y * b.z,
        //      a.x * b.z,
        //      a.x * b.y,
        //      a.y * b.x
        // ]
        float32x4_t const m0 = vmulq_f32(a_yxxy, b_zzyx);

        // = [
        //      (a.y * b.z) - (a.z * b.y),
        //      (a.x * b.z) - (a.z * b.x),
        //      (a.x * b.y) - (a.y * b.x),
        //      (a.y * b.x) - (a.x * b.y),
        // ]
        float32x4_t const m1 = vmlsq_f32(m0, a_zzyx, b_yxxy);

        // flip: m2.y = m1.y * -1
        // m1: (a.x * b.z) - (a.z * b.x)
        // m2: -(a.x * b.z) + (a.z * b.x) = (a.z * b.x) - (a.x * b.z)
        uint32x4_t const m2 = veorq_u32(vreinterpretq_u32_f32(m1), Impl::c_V4_U32_Sign_0100);

        uint32x4_t const m3 = vandq_u32(m2, Impl::c_V4_U32_Mask_1110.V);

        return { vreinterpretq_f32_u32(m3) };

#elif GRAPHYTE_HW_AVX
        // m0 = (a.yzx * b.zxy)
        __m128 const a0 = _mm_permute_ps(a.V, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const b0 = _mm_permute_ps(b.V, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 const m0 = _mm_mul_ps(a0, b0);

        // m1 = (a.zxy * b.yzx)
        __m128 const a1 = _mm_permute_ps(a0, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const b1 = _mm_permute_ps(b0, _MM_SHUFFLE(3, 1, 0, 2));
        __m128 const m1 = _mm_mul_ps(a1, b1);

        // r0 = m0 - m1
        __m128 const r0     = _mm_sub_ps(m0, m1);
        __m128 const result = _mm_and_ps(r0, Impl::c_V4_U32_Mask_1110.V);
        return { result };
#endif
    }

    mathinline Vector3 mathcall Orthogonal(Vector3 v) noexcept
    {
        Vector3 const zzz = SplatZ(v);
        Vector3 const yzy{ Swizzle<1, 2, 1, 1>(Vector4{ v.V }).V };
        Vector3 const negv = Negate(v);
        Vector3 const zero = Zero<Vector3>();

        Bool3 const cmp_zzz_negative = CompareLess(zzz, zero);
        Bool3 const cmp_yzy_negative = CompareLess(yzy, zero);

        Vector3 const s = Add(yzy, zzz);
        Vector3 const d = Subtract(yzy, zzz);

        Bool3 const select = CompareEqual(cmp_zzz_negative, cmp_yzy_negative);

        Vector4 const r0 = Permute<4, 0, 0, 0>(Vector4{ negv.V }, Vector4{ s.V });
        Vector4 const r1 = Permute<4, 0, 0, 0>(Vector4{ v.V }, Vector4{ d.V });

        Vector4 const result = Select(r1, r0, Bool4{ select.V });

        return Vector3{ result.V };
    }

    mathinline void mathcall ComponentsFromNormal(Vector3& out_parallel, Vector3& out_perpendicular, Vector3 v, Vector3 n) noexcept
    {
        Vector3 const scale    = Dot(v, n);
        Vector3 const parallel = Multiply(n, scale);

        out_parallel      = parallel;
        out_perpendicular = Subtract(v, parallel);
    }

    mathinline Vector3 mathcall Transform(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0   = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1   = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2   = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return Vector3{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const r2   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        return { r2 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x2_t const zn = vget_high_f32(v.V);
        float32x4_t const x  = vmlaq_lane_f32(m.M.R[3], m.M.R[0], xy, 0);
        float32x4_t const y  = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x4_t const z  = vmlaq_lane_f32(y, m.M.R[2], zn, 0);
        return { z };
#endif
    }

    mathinline Vector3 mathcall TransformCoord(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz   = SplatZ<Vector4>(v4);
        Vector4 const r0     = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy   = SplatY<Vector4>(v4);
        Vector4 const r1     = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx   = SplatX<Vector4>(v4);
        Vector4 const r2     = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        Vector4 const wwww   = SplatW<Vector4>(r2);
        Vector4 const result = Divide(r2, wwww);
        return Vector3{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r2   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        __m128 const wwww = _mm_permute_ps(r2, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r3   = _mm_div_ps(r2, wwww);
        return { r3 };
#endif
    }

    mathinline Vector3 mathcall TransformNormal(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0   = Multiply(zzzz, Vector4{ m.M.R[2] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1   = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2   = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return Vector3{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0   = _mm_mul_ps(xxxx, m.M.R[2]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const zzzz = _mm_broadcastss_ps(v.V);
        __m128 const r2   = Impl::avx_fmadd_f32x4(zzzz, m.M.R[0], r1);
        return { r2 };
#endif
    }
}


// =================================================================================================
// Vector2 functions

namespace Graphyte::Maths
{
    mathinline Vector2 mathcall Cross(Vector2 a, Vector2 b) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = (a.V.F[0] * b.V.F[1]) - (a.V.F[1] * b.V.F[0]);

        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        // b.yx * a.xy = [b.y * a.x, b.x * a.y]
        __m128 const b_yx          = _mm_permute_ps(b.V, _MM_SHUFFLE(0, 1, 0, 1));
        __m128 const b_yx_mul_a_xy = _mm_mul_ps(b_yx, a.V);

        __m128 const bx_mul_ay               = _mm_permute_ps(b_yx_mul_a_xy, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const by_mul_ax_sub_bx_mul_ay = _mm_sub_ss(b_yx_mul_a_xy, bx_mul_ay);

        __m128 const result = _mm_permute_ps(by_mul_ax_sub_bx_mul_ay, _MM_SHUFFLE(0, 0, 0, 0));
        return { result };
#endif
    }

    mathinline Vector2 mathcall Orthogonal(Vector2 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            -v.V.F[1],
            v.V.F[0],
            0.0F,
            0.0F,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const partial = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const result  = _mm_mul_ps(partial, Impl::c_V4_F32_Negate_X.V);
        return { result };
#endif
    }

    mathinline Vector2 mathcall Transform(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0   = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1   = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return Vector2{ r1.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const y  = vmlaq_lane_f32(m.M.R[3], m.M.R[1], xy, 1);
        float32x4_t const x  = vmlaq_lane_f32(y, m.M.R[0], xy, 0);
        return { x };
#endif
    }

    mathinline Vector2 mathcall TransformCoord(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0   = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1   = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        Vector4 const wwww = SplatW(r1);
        Vector4 const r2   = Divide(r1, wwww);
        return Vector2{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0   = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        __m128 const wwww = _mm_permute_ps(r1, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r2   = _mm_div_ps(r1, wwww);
        return { r2 };
#endif
    }

    mathinline Vector2 mathcall TransformNormal(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0   = Multiply(yyyy, { m.M.R[1] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1   = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return Vector2{ r1.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0   = _mm_mul_ps(yyyy, m.M.R[1]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1   = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#endif
    }
}
