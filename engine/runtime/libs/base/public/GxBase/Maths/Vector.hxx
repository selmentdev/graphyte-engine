#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Constants.hxx>
#include <GxBase/Maths/Arithmetic.hxx>
#include <GxBase/Maths/Comparizon.hxx>
#include <GxBase/Maths/Scalar.hxx>



// =================================================================================================
//
// Vector conversion.
//

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
            vreinterpretq_u32_f32(Impl::VEC4_MASK_SELECT_1110.V)));
        return { r2 };
#elif GRAPHYTE_HW_AVX
        // = [_, vy, vz, _]
        __m128 const r0 = _mm_permute_ps(yz.V, _MM_SHUFFLE(1, 1, 0, 0));
        // = [x, vy, vz, _]
        __m128 const r1 = _mm_insert_ps(r0, _mm_set_ps1(x), 0x00);
        // = [x, vy, vz, 0]
        __m128 const r2 = _mm_and_ps(r1, Impl::VEC4_MASK_SELECT_1110.V);
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
//
// Constants.
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall UnitX() noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_POSITIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall UnitY() noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_POSITIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall UnitZ() noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_POSITIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall UnitW() noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitX() noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitY() noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitZ() noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitW() noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        return { Impl::VEC4_NEGATIVE_UNIT_W.V };
    }

    template <typename T>
    mathinline T mathcall Zero() noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_ZERO_4.V };
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
        return { Impl::VEC4_ONE_4.V };
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
        return { Impl::VEC4_INFINITY.V };
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
            FloatTraits<float>::QNan,
            FloatTraits<float>::QNan,
            FloatTraits<float>::QNan,
            FloatTraits<float>::QNan,
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { Impl::VEC4_QNAN.V };
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
        return { Impl::VEC4_EPSILON.V };
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
        return { Impl::g_Const_E_Vec4.V };
    }
}


// =================================================================================================
//
// Vector specific operations
//

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
                    fdot, } } };

            return result;
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
                    fdot, } } };

            return result;
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
                    fdot, } } };

            return result;
        }
        else if constexpr (T::Components == 1)
        {
            float const fdot
                = (a.V.F[0] * b.V.F[0]);

            Impl::ConstFloat32x4 const result{ { {
                    fdot,
                    fdot,
                    fdot,
                    fdot, } } };

            return result;
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
        T const length = Sqrt<T>(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    template <typename T>
    mathinline T mathcall LengthEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared<T>(v);
        T const length = SqrtEst<T>(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length = _mm_sqrt_ps(length_squared);
        return { length };
#endif
    }

    template <typename T>
    mathinline T mathcall ReciprocalLength(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared(v);
        T const length = InvSqrt(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;
        __m128 const one = Impl::VEC4_ONE_4.V;
        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length = _mm_sqrt_ps(length_squared);
        __m128 const result = _mm_div_ps(one, length);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall ReciprocalLengthEst(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const length_squared = LengthSquared<T>(v);
        T const length = InvSqrtEst<T>(length_squared);
        return length;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;

        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        return { length };
#endif
    }

    template <typename T>
    mathinline T mathcall Distance(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const difference = Subtract(b, a);
        T const result = Length(difference);
        return result;
    }

    template <typename T>
    mathinline T mathcall DistanceSquared(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const difference = Subtract(b, a);
        T const result = LengthSquared(difference);
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

        return IsLess(absdiff, T{ Impl::VEC4_UNIT_EPSILON.V });
    }

    template <typename T>
    mathinline T mathcall Normalize(T v) noexcept
        requires(Impl::IsVector<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const length = Length(v).V.F[0];
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
        __m128 const length = _mm_sqrt_ps(length_squared);

        __m128 const zero = _mm_setzero_ps();
        __m128 const mask_length_zero = _mm_cmpneq_ps(zero, length);
        __m128 const mask_length_inf = _mm_cmpneq_ps(length_squared, Impl::VEC4_INFINITY.V);

        __m128 const normalized = _mm_div_ps(v.V, length);
        __m128 const normalized_masked_zero = _mm_and_ps(normalized, mask_length_zero);
        __m128 const select_qnan = _mm_andnot_ps(mask_length_inf, Impl::VEC4_QNAN.V);
        __m128 const select_inf = _mm_and_ps(normalized_masked_zero, mask_length_inf);

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
        T const result = Multiply(v, rcp_length);
        return result;
#elif GRAPHYTE_HW_AVX
        constexpr int dp_mask = Impl::avx_mm_dp_mask<T::Components>;

        __m128 const length_squared = _mm_dp_ps(v.V, v.V, dp_mask);
        __m128 const length = _mm_rsqrt_ps(length_squared);
        __m128 const result = _mm_mul_ps(length, v.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall ClampLength(T v, Vector4 min, Vector4 max) noexcept = delete;

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
        T const dot = Dot(incident, normal);
        T const dot2 = Add(dot, dot);
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

        T const one{ Impl::VEC4_ONE_4.V };

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
        requires(Impl::IsVector<T> && T::Components >= 2 && T::Components <= 3)
    {
        T const dot0 = Dot(reference, incident);
        T const sign0 = Sign(dot0);
        T const r0 = Multiply(sign0, Replicate<T>(-1.0f));
        T const r1 = Multiply(normal, r0);
        return r1;
    }

    template <typename T>
    mathinline T mathcall MoveTowards(T current, T target, float max_distance) noexcept
        requires(Impl::IsVector<T>)
    {
        T const diff = Subtract(target, current);
        T const length = Length(diff);
        T const vmax = Replicate<T>(max_distance);

        if (IsLessEqual(length, vmax) || IsZero(length))
        {
            return target;
        }

        return MultiplyAdd(current, Divide(diff, length), vmax);
    }

    template <typename T>
    mathinline T mathcall MoveTowards(T current, T target, T max_distance) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const distance = (target - current);

        if (Abs(distance) <= max_distance)
        {
            return target;
        }

        return current + Sign(distance) * max_distance;
    }

    template <typename T>
    mathinline T mathcall AngleBetweenNormals(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const cos_angle = Dot(a, b);

        // Clamp to acos range
        T const cos_angle_clamped = Clamp<T>(cos_angle, T{ Impl::VEC4_NEGATIVE_ONE_4.V }, T{ Impl::VEC4_ONE_4.V });
        T const angle = Acos<T>(cos_angle_clamped);

        return angle;
    }

    template <typename T>
    mathinline T mathcall AngleBetweenVectors(T a, T b) noexcept
        requires(Impl::IsVector<T>)
    {
        T const rcp_length_a = ReciprocalLength(a);
        T const rcp_length_b = ReciprocalLength(b);

        T const a_dot_b = Dot(a, b);
        T const rcp_len_ab_sq = Multiply(rcp_length_a, rcp_length_b);
        T const cos_angle = Multiply(a_dot_b, rcp_len_ab_sq);

        // Clamp to acos range
        T const cos_angle_clamped = Clamp(cos_angle, T{ Impl::VEC4_NEGATIVE_ONE_4.V }, T{ Impl::VEC4_ONE_4.V });
        T const angle = Acos(cos_angle_clamped);

        return angle;
    }
}


// =================================================================================================
//
// Vector4 operations
//

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall FresnelTerm(Vector4 cos_incident_angle, Vector4 refraction_index) noexcept
    {
        // c = cos_incident_angle
        // g = sqrt(c^2 + refraction_index^2 - 1)
        // r = 0.5f * (g - c)^2 / (g + c)^2 * ((c * (g + c) - 1)^2 / (c * (g - c) + 1)^2 + 1)

        GX_ASSERT(!IsInfinity(cos_incident_angle));

#if GRAPHYTE_MATH_NO_INTRINSICS

        // = refraction_index^2 - 1
        Vector4 const g0 = MultiplyAdd(refraction_index, refraction_index, Vector4{ Impl::VEC4_NEGATIVE_ONE_4.V });

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
        Vector4 const rcp_s1 = Reciprocal(s1);
        Vector4 const half_d1 = Multiply(Vector4{ Impl::VEC4_HALF_4.V }, d1);
        Vector4 const r0 = Multiply(half_d1, rcp_s1);

        // = (c * (g + c) - 1)^2
        Vector4 const ca0 = MultiplyAdd(cos_incident_angle, s0, Vector4{ Impl::VEC4_NEGATIVE_ONE_4.V });
        Vector4 const ca1 = Multiply(ca0, ca0);

        // = (c * (g - c) + 1)^2
        Vector4 const cb0 = MultiplyAdd(cos_incident_angle, d0, Vector4{ Impl::VEC4_ONE_4.V });
        Vector4 const cb1 = Multiply(cb0, cb0);
        Vector4 const cb2 = Reciprocal(cb1);

        Vector4 const r1 = MultiplyAdd(ca1, cb2, Vector4{ Impl::VEC4_ONE_4.V });
        Vector4 const r2 = Multiply(r0, r1);
        Vector4 const r3 = Saturate(r2);

        return r3;

#elif GRAPHYTE_HW_AVX

        __m128 const one = Impl::VEC4_ONE_4.V;

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
        __m128 const half_d1 = _mm_mul_ps(d1, Impl::VEC4_ONE_HALF_4.V);
        __m128 const r0 = _mm_div_ps(half_d1, s1);

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

        __m128 const zwxy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 0, 3, 2));
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
        __m128 const r0 = _mm_mul_ps(wwww, m.M.R[3]);
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r1 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], r0);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r2 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r1);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r3 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r2);
        return { r3 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const x = vmulq_lane_f32(m.M.R[0], xy, 0);
        float32x4_t const y = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x2_t const zw = vget_high_f32(v.V);
        float32x4_t const z = vmlaq_lane_f32(y, m.M.R[2], zw, 0);
        float32x4_t const w = vmlaq_lane_f32(z, m.M.R[3], zw, 1);
        return { w };
#endif
    }
}


// =================================================================================================
//
// Vector3 functions
//

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
        uint32x4_t const m2 = veorq_u32(vreinterpretq_u32_f32(m1), Impl::VEC4_MASK_FLIP_Y);

        uint32x4_t const m3 = vandq_u32(m2, Impl::VEC4_MASK_SELECT_1110.V);

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
        __m128 const r0 = _mm_sub_ps(m0, m1);
        __m128 const result = _mm_and_ps(r0, Impl::VEC4_MASK_COMPONENTS_3.V);
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
        Vector3 const scale = Dot(v, n);
        Vector3 const parallel = Multiply(n, scale);

        out_parallel = parallel;
        out_perpendicular = Subtract(v, parallel);
    }

    mathinline Vector3 mathcall Transform(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0 = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1 = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2 = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return Vector3{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        __m128 const r2 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        return { r2 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x2_t const zn = vget_high_f32(v.V);
        float32x4_t const x = vmlaq_lane_f32(m.M.R[3], m.M.R[0], xy, 0);
        float32x4_t const y = vmlaq_lane_f32(x, m.M.R[1], xy, 1);
        float32x4_t const z = vmlaq_lane_f32(y, m.M.R[2], zn, 0);
        return { z };
#endif
    }

    mathinline Vector3 mathcall TransformCoord(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0 = MultiplyAdd(zzzz, Vector4{ m.M.R[2] }, Vector4{ m.M.R[3] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1 = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2 = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        Vector4 const wwww = SplatW<Vector4>(r2);
        Vector4 const result = Divide(r2, wwww);
        return Vector3{ result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[2], m.M.R[3]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r2 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r1);
        __m128 const wwww = _mm_permute_ps(r2, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r3 = _mm_div_ps(r2, wwww);
        return { r3 };
#endif
    }

    mathinline Vector3 mathcall TransformNormal(Vector3 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const zzzz = SplatZ<Vector4>(v4);
        Vector4 const r0 = Multiply(zzzz, Vector4{ m.M.R[2] });
        Vector4 const yyyy = SplatY<Vector4>(v4);
        Vector4 const r1 = MultiplyAdd(yyyy, Vector4{ m.M.R[1] }, r0);
        Vector4 const xxxx = SplatX<Vector4>(v4);
        Vector4 const r2 = MultiplyAdd(xxxx, Vector4{ m.M.R[0] }, r1);
        return Vector3{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        __m128 const r0 = _mm_mul_ps(xxxx, m.M.R[2]);
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r1 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], r0);
        __m128 const zzzz = _mm_broadcastss_ps(v.V);
        __m128 const r2 = Impl::avx_fmadd_f32x4(zzzz, m.M.R[0], r1);
        return { r2 };
#endif
    }
}


// =================================================================================================
//
// Vector2 functions
//

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
        __m128 const b_yx = _mm_permute_ps(b.V, _MM_SHUFFLE(0, 1, 0, 1));
        __m128 const b_yx_mul_a_xy = _mm_mul_ps(b_yx, a.V);

        __m128 const bx_mul_ay = _mm_permute_ps(b_yx_mul_a_xy, _MM_SHUFFLE(1, 1, 1, 1));
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
        __m128 const result = _mm_mul_ps(partial, Impl::VEC4_NEGATE_X.V);
        return { result };
#endif
    }

    mathinline Vector2 mathcall Transform(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0 = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1 = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return Vector2{ r1.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#elif GRAPHYTE_HW_NEON
        float32x2_t const xy = vget_low_f32(v.V);
        float32x4_t const y = vmlaq_lane_f32(m.M.R[3], m.M.R[1], xy, 1);
        float32x4_t const x = vmlaq_lane_f32(y, m.M.R[0], xy, 0);
        return { x };
#endif
    }

    mathinline Vector2 mathcall TransformCoord(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0 = MultiplyAdd(yyyy, { m.M.R[1] }, { m.M.R[3] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1 = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        Vector4 const wwww = SplatW(r1);
        Vector4 const r2 = Divide(r1, wwww);
        return Vector2{ r2.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0 = Impl::avx_fmadd_f32x4(yyyy, m.M.R[1], m.M.R[3]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        __m128 const wwww = _mm_permute_ps(r1, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 const r2 = _mm_div_ps(r1, wwww);
        return { r2 };
#endif
    }

    mathinline Vector2 mathcall TransformNormal(Vector2 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const v4{ v.V };
        Vector4 const yyyy = SplatY(v4);
        Vector4 const r0 = Multiply(yyyy, { m.M.R[1] });
        Vector4 const xxxx = SplatX(v4);
        Vector4 const r1 = MultiplyAdd(xxxx, { m.M.R[0] }, r0);
        return Vector2{ r1.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const r0 = _mm_mul_ps(yyyy, m.M.R[1]);
        __m128 const xxxx = _mm_broadcastss_ps(v.V);
        __m128 const r1 = Impl::avx_fmadd_f32x4(xxxx, m.M.R[0], r0);
        return { r1 };
#endif
    }
}
