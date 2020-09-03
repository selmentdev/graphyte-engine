#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Vector.hxx>
#include <GxBase/Maths/Quaternion.hxx>
#include <GxBase/Maths/Scalar.hxx>

// Make matrix
namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall Make(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;
        result.M.M[0][0] = m00;
        result.M.M[0][1] = m01;
        result.M.M[0][2] = m02;
        result.M.M[0][3] = m03;

        result.M.M[1][0] = m10;
        result.M.M[1][1] = m11;
        result.M.M[1][2] = m12;
        result.M.M[1][3] = m13;

        result.M.M[2][0] = m20;
        result.M.M[2][1] = m21;
        result.M.M[2][2] = m22;
        result.M.M[2][3] = m23;

        result.M.M[3][0] = m30;
        result.M.M[3][1] = m31;
        result.M.M[3][2] = m32;
        result.M.M[3][3] = m33;

        return result;
#elif GRAPHYTE_HW_AVX
        Matrix result;
        result.M.R[0] = _mm_set_ps(m03, m02, m01, m00);
        result.M.R[1] = _mm_set_ps(m13, m12, m11, m10);
        result.M.R[2] = _mm_set_ps(m23, m22, m21, m20);
        result.M.R[3] = _mm_set_ps(m33, m32, m31, m30);
        return result;
#endif
    }
}

// Load/Store operations
namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float4x4A const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.R[0].F[0] = source->M[0][0];
        result.M.R[0].F[1] = source->M[0][1];
        result.M.R[0].F[2] = source->M[0][2];
        result.M.R[0].F[3] = source->M[0][3];

        result.M.R[1].F[0] = source->M[1][0];
        result.M.R[1].F[1] = source->M[1][1];
        result.M.R[1].F[2] = source->M[1][2];
        result.M.R[1].F[3] = source->M[1][3];

        result.M.R[2].F[0] = source->M[2][0];
        result.M.R[2].F[1] = source->M[2][1];
        result.M.R[2].F[2] = source->M[2][2];
        result.M.R[2].F[3] = source->M[2][3];

        result.M.R[3].F[0] = source->M[3][0];
        result.M.R[3].F[1] = source->M[3][1];
        result.M.R[3].F[2] = source->M[3][2];
        result.M.R[3].F[3] = source->M[3][3];

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;

        result.M.R[0] = _mm_load_ps(&source->M11);
        result.M.R[1] = _mm_load_ps(&source->M21);
        result.M.R[2] = _mm_load_ps(&source->M31);
        result.M.R[3] = _mm_load_ps(&source->M41);

        return result;

#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Store(Float4x4A* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];
        destination->M[0][3] = m.M.R[0].F[3];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];
        destination->M[1][3] = m.M.R[1].F[3];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[2].F[3];

        destination->M[3][0] = m.M.R[3].F[0];
        destination->M[3][1] = m.M.R[3].F[1];
        destination->M[3][2] = m.M.R[3].F[2];
        destination->M[3][3] = m.M.R[3].F[3];

#elif GRAPHYTE_HW_AVX

        _mm_store_ps(&destination->M11, m.M.R[0]);
        _mm_store_ps(&destination->M21, m.M.R[1]);
        _mm_store_ps(&destination->M31, m.M.R[2]);
        _mm_store_ps(&destination->M41, m.M.R[3]);

#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float4x3A const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[3][0];
        result.M.M[3][1] = source->M[3][1];
        result.M.M[3][2] = source->M[3][2];
        result.M.M[3][3] = 1.0f;

        return result;
#elif GRAPHYTE_HW_AVX
        // = [r0.xyz, r1.x]
        __m128 const r0 = _mm_load_ps(&source->M[0][0]);
        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_load_ps(&source->M[1][1]);
        // = [r2.z, r3.xyz]
        __m128 const t2 = _mm_load_ps(&source->M[2][2]);

        // = [r2.xyzz]
        __m128 const r2 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(0, 0, 3, 2));
        // = [r1.yzxx]
        __m128 const t1 = _mm_shuffle_ps(t0, r0, _MM_SHUFFLE(3, 3, 1, 0));
        // = [r1.xyzz]
        __m128 const r1 = _mm_permute_ps(t1, _MM_SHUFFLE(1, 1, 0, 2));

        // = [r0.xyz, 0]
        __m128 const m0 = _mm_and_ps(r0, Impl::c_V4_U32_Mask_1110.V);
        // = [r1.xyz, 0]
        __m128 const m1 = _mm_and_ps(r1, Impl::c_V4_U32_Mask_1110.V);
        // = [r2.xyz, 0]
        __m128 const m2 = _mm_and_ps(r2, Impl::c_V4_U32_Mask_1110.V);

        // = [r2.z, r3.xyz] >> 4 bytes = [r3.xyz]
        __m128i const t3 = _mm_srli_si128(_mm_castps_si128(t2), 32 / 8);
        // = [r3.xyz, 1]
        __m128 const m3 = _mm_castsi128_ps(_mm_or_si128(t3, _mm_castps_si128(Impl::c_V4_F32_PositiveUnitW.V)));

        Matrix result;
        result.M.R[0] = m0;
        result.M.R[1] = m1;
        result.M.R[2] = m2;
        result.M.R[3] = m3;
        return result;
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4x3A* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];

        destination->M[3][0] = m.M.M[3][0];
        destination->M[3][1] = m.M.M[3][1];
        destination->M[3][2] = m.M.M[3][2];
#elif GRAPHYTE_HW_AVX
        // = [r0.xyzw]
        __m128 const r0 = m.M.R[0];
        // = [r1.xyzw]
        __m128 const r1 = m.M.R[1];
        // = [r2.xyzw]
        __m128 const r2 = m.M.R[2];
        // = [r3.xyzw]
        __m128 const r3 = m.M.R[3];

        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 2, 1));
        // = [r1.xx, r0.zz]
        __m128 const t1 = _mm_shuffle_ps(r1, r0, _MM_SHUFFLE(2, 2, 0, 0));
        // = [r0.xyz, r1.x]
        __m128 const t2 = _mm_shuffle_ps(r0, t1, _MM_SHUFFLE(0, 2, 1, 0));
        // = [r2.zz, r3.xx]
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(0, 0, 2, 2));
        // = [r2.z, r3.xyz]
        __m128 const t4 = _mm_shuffle_ps(t3, r3, _MM_SHUFFLE(2, 1, 2, 0));

        // = [r0.xyz, r1.x]
        _mm_store_ps(&destination->M[0][0], t2);
        // = [r1.yz, r2.xy]
        _mm_store_ps(&destination->M[1][1], t0);
        // = [r2.z, r3.xyz]
        _mm_store_ps(&destination->M[2][2], t4);
#endif
    }

    /// \note   Float3x4 is stored as transposed Float4x3
    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float3x4A const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[1][0];
        result.M.M[0][2] = source->M[2][0];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[0][1];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[2][1];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[0][2];
        result.M.M[2][1] = source->M[1][2];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[0][3];
        result.M.M[3][1] = source->M[1][3];
        result.M.M[3][2] = source->M[2][3];
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        // = []
        __m128 const r0 = _mm_load_ps(&source->M[0][0]);
        __m128 const r1 = _mm_load_ps(&source->M[1][0]);
        __m128 const r2 = _mm_load_ps(&source->M[2][0]);
        __m128 const r3 = Impl::c_V4_F32_PositiveUnitW.V;

        __m128 const t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t2 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t1 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(3, 2, 3, 2));

        Matrix result;
        result.M.R[0] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[1] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(3, 1, 3, 1));
        result.M.R[2] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[3] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 1, 3, 1));
        return result;
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3x4A* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[1].F[0];
        destination->M[0][2] = m.M.R[2].F[0];
        destination->M[0][3] = m.M.R[3].F[0];

        destination->M[1][0] = m.M.R[0].F[1];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[2].F[1];
        destination->M[1][3] = m.M.R[3].F[1];

        destination->M[2][0] = m.M.R[0].F[2];
        destination->M[2][1] = m.M.R[1].F[2];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        // load & transpose
        __m128 const t1 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t2 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t4 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const r0 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const r2 = _mm_shuffle_ps(t3, t4, _MM_SHUFFLE(2, 0, 2, 0));

        _mm_store_ps(&destination->M[0][0], r0);
        _mm_store_ps(&destination->M[1][0], r1);
        _mm_store_ps(&destination->M[2][0], r2);
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float4x4 const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = source->M[0][3];

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = source->M[1][3];

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = source->M[2][3];

        result.M.M[3][0] = source->M[3][0];
        result.M.M[3][1] = source->M[3][1];
        result.M.M[3][2] = source->M[3][2];
        result.M.M[3][3] = source->M[3][3];

        return result;
#elif GRAPHYTE_HW_AVX
        Matrix result;

        result.M.R[0] = _mm_loadu_ps(&source->M[0][0]);
        result.M.R[1] = _mm_loadu_ps(&source->M[1][0]);
        result.M.R[2] = _mm_loadu_ps(&source->M[2][0]);
        result.M.R[3] = _mm_loadu_ps(&source->M[3][0]);

        return result;
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4x4* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];
        destination->M[0][3] = m.M.M[0][3];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];
        destination->M[1][3] = m.M.M[1][3];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];
        destination->M[2][3] = m.M.M[2][3];

        destination->M[3][0] = m.M.M[3][0];
        destination->M[3][1] = m.M.M[3][1];
        destination->M[3][2] = m.M.M[3][2];
        destination->M[3][3] = m.M.M[3][3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(&destination->M[0][0], m.M.R[0]);
        _mm_storeu_ps(&destination->M[1][0], m.M.R[1]);
        _mm_storeu_ps(&destination->M[2][0], m.M.R[2]);
        _mm_storeu_ps(&destination->M[3][0], m.M.R[3]);
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float4x3 const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[3][0];
        result.M.M[3][1] = source->M[3][1];
        result.M.M[3][2] = source->M[3][2];
        result.M.M[3][3] = 1.0f;

        return result;
#elif GRAPHYTE_HW_AVX
        // = [r0.xyz, r1.x]
        __m128 const r0 = _mm_loadu_ps(&source->M[0][0]);
        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_loadu_ps(&source->M[1][1]);
        // = [r2.z, r3.xyz]
        __m128 const t2 = _mm_loadu_ps(&source->M[2][2]);

        // = [r2.xyzz]
        __m128 const r2 = _mm_shuffle_ps(t0, t2, _MM_SHUFFLE(0, 0, 3, 2));
        // = [r1.yzxx]
        __m128 const t1 = _mm_shuffle_ps(t0, r0, _MM_SHUFFLE(3, 3, 1, 0));
        // = [r1.xyzz]
        __m128 const r1 = _mm_permute_ps(t1, _MM_SHUFFLE(1, 1, 0, 2));

        // = [r0.xyz, 0]
        __m128 const m0 = _mm_and_ps(r0, Impl::c_V4_U32_Mask_1110.V);
        // = [r1.xyz, 0]
        __m128 const m1 = _mm_and_ps(r1, Impl::c_V4_U32_Mask_1110.V);
        // = [r2.xyz, 0]
        __m128 const m2 = _mm_and_ps(r2, Impl::c_V4_U32_Mask_1110.V);

        // = [r2.z, r3.xyz] >> 4 bytes = [r3.xyz]
        __m128i const t3 = _mm_srli_si128(_mm_castps_si128(t2), 32 / 8);
        // = [r3.xyz, 1]
        __m128 const m3 = _mm_castsi128_ps(_mm_or_si128(t3, _mm_castps_si128(Impl::c_V4_F32_PositiveUnitW.V)));

        Matrix result;
        result.M.R[0] = m0;
        result.M.R[1] = m1;
        result.M.R[2] = m2;
        result.M.R[3] = m3;
        return result;
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4x3* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];

        destination->M[3][0] = m.M.M[3][0];
        destination->M[3][1] = m.M.M[3][1];
        destination->M[3][2] = m.M.M[3][2];
#elif GRAPHYTE_HW_AVX
        // = [r0.xyzw]
        __m128 const r0 = m.M.R[0];
        // = [r1.xyzw]
        __m128 const r1 = m.M.R[1];
        // = [r2.xyzw]
        __m128 const r2 = m.M.R[2];
        // = [r3.xyzw]
        __m128 const r3 = m.M.R[3];

        // = [r1.yz, r2.xy]
        __m128 const t0 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 2, 1));
        // = [r1.xx, r0.zz]
        __m128 const t1 = _mm_shuffle_ps(r1, r0, _MM_SHUFFLE(2, 2, 0, 0));
        // = [r0.xyz, r1.x]
        __m128 const t2 = _mm_shuffle_ps(r0, t1, _MM_SHUFFLE(0, 2, 1, 0));
        // = [r2.zz, r3.xx]
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(0, 0, 2, 2));
        // = [r2.z, r3.xyz]
        __m128 const t4 = _mm_shuffle_ps(t3, r3, _MM_SHUFFLE(2, 1, 2, 0));

        // = [r0.xyz, r1.x]
        _mm_storeu_ps(&destination->M[0][0], t2);
        // = [r1.yz, r2.xy]
        _mm_storeu_ps(&destination->M[1][1], t0);
        // = [r2.z, r3.xyz]
        _mm_storeu_ps(&destination->M[2][2], t4);
#endif
    }

    /// \note   Float3x4 is stored as transposed Float4x3
    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float3x4 const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[1][0];
        result.M.M[0][2] = source->M[2][0];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[0][1];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[2][1];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[0][2];
        result.M.M[2][1] = source->M[1][2];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = source->M[0][3];
        result.M.M[3][1] = source->M[1][3];
        result.M.M[3][2] = source->M[2][3];
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        // = []
        __m128 const r0 = _mm_loadu_ps(&source->M[0][0]);
        __m128 const r1 = _mm_loadu_ps(&source->M[1][0]);
        __m128 const r2 = _mm_loadu_ps(&source->M[2][0]);
        __m128 const r3 = Impl::c_V4_F32_PositiveUnitW.V;

        __m128 const t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t2 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t1 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(r2, r3, _MM_SHUFFLE(3, 2, 3, 2));

        Matrix result;
        result.M.R[0] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[1] = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(3, 1, 3, 1));
        result.M.R[2] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(2, 0, 2, 0));
        result.M.R[3] = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 1, 3, 1));
        return result;
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3x4* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[1].F[0];
        destination->M[0][2] = m.M.R[2].F[0];
        destination->M[0][3] = m.M.R[3].F[0];

        destination->M[1][0] = m.M.R[0].F[1];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[2].F[1];
        destination->M[1][3] = m.M.R[3].F[1];

        destination->M[2][0] = m.M.R[0].F[2];
        destination->M[2][1] = m.M.R[1].F[2];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        // load & transpose
        __m128 const t1 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t3 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const t2 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const t4 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const r0 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const r1 = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const r2 = _mm_shuffle_ps(t3, t4, _MM_SHUFFLE(2, 0, 2, 0));

        _mm_storeu_ps(&destination->M[0][0], r0);
        _mm_storeu_ps(&destination->M[1][0], r1);
        _mm_storeu_ps(&destination->M[2][0], r2);
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Load(Float3x3 const* source) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        result.M.M[0][0] = source->M[0][0];
        result.M.M[0][1] = source->M[0][1];
        result.M.M[0][2] = source->M[0][2];
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = source->M[1][0];
        result.M.M[1][1] = source->M[1][1];
        result.M.M[1][2] = source->M[1][2];
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = source->M[2][0];
        result.M.M[2][1] = source->M[2][1];
        result.M.M[2][2] = source->M[2][2];
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const zero = _mm_setzero_ps();

        __m128 const t0 = _mm_loadu_ps(&source->M[0][0]);
        __m128 const t1 = _mm_loadu_ps(&source->M[1][1]);
        __m128 const t2 = _mm_load_ss(&source->M[2][2]);

        __m128 const t3 = _mm_unpackhi_ps(t0, zero);
        __m128 const t4 = _mm_unpacklo_ps(t1, zero);
        __m128 const t5 = _mm_shuffle_ps(t2, t4, _MM_SHUFFLE(0, 1, 0, 0));
        __m128 const t6 = _mm_movehl_ps(t4, t5);
        __m128 const t7 = _mm_movehl_ps(zero, t3);

        Matrix result;
        result.M.R[0] = _mm_movelh_ps(t0, t3);
        result.M.R[1] = _mm_add_ps(t6, t7);
        result.M.R[2] = _mm_shuffle_ps(t1, t2, _MM_SHUFFLE(1, 0, 3, 2));
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3x3* destination, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.M[0][0];
        destination->M[0][1] = m.M.M[0][1];
        destination->M[0][2] = m.M.M[0][2];

        destination->M[1][0] = m.M.M[1][0];
        destination->M[1][1] = m.M.M[1][1];
        destination->M[1][2] = m.M.M[1][2];

        destination->M[2][0] = m.M.M[2][0];
        destination->M[2][1] = m.M.M[2][1];
        destination->M[2][2] = m.M.M[2][2];
#elif GRAPHYTE_HW_AVX
        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const t0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(0, 0, 2, 2));
        __m128 const m0 = _mm_shuffle_ps(r0, t0, _MM_SHUFFLE(2, 0, 1, 0));
        _mm_storeu_ps(&destination->M[0][0], m0);
        __m128 const m1 = _mm_shuffle_ps(r1, r2, _MM_SHUFFLE(1, 0, 2, 1));
        _mm_storeu_ps(&destination->M[1][1], m1);
        __m128 const m2 = _mm_permute_ps(r2, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->M[2][2], m2);
#endif
    }
}

// Nan, Infinity, Identity
namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall Nan() noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
        result.M.R[0] = Impl::c_V4_F32_Positive_QNan.V;
        result.M.R[1] = Impl::c_V4_F32_Positive_QNan.V;
        result.M.R[2] = Impl::c_V4_F32_Positive_QNan.V;
        result.M.R[3] = Impl::c_V4_F32_Positive_QNan.V;
        return result;
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(push)
#pragma float_control(precise, on)
#endif

    template <typename T>
    [[nodiscard]] mathinline bool mathcall IsNan(Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        size_t count = 16u;

        uint32_t const* item = reinterpret_cast<uint32_t const*>(&m.M.F[0]);

        do
        {
            uint32_t const value = (*item);
            if (FloatTraits<float>::BitIsNan(value))
            {
                break;
            }

            ++item;
        } while (--count != 0);

        return count != 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const eq_r0 = _mm_cmpneq_ps(r0, r0);
        __m128 const eq_r1 = _mm_cmpneq_ps(r1, r1);
        __m128 const eq_r2 = _mm_cmpneq_ps(r2, r2);
        __m128 const eq_r3 = _mm_cmpneq_ps(r3, r3);

        __m128 const eq_r0r1 = _mm_or_ps(eq_r0, eq_r1);
        __m128 const eq_r2r3 = _mm_or_ps(eq_r2, eq_r3);

        __m128 const eq_r0r1r2r3 = _mm_or_ps(eq_r0r1, eq_r2r3);

        return _mm_movemask_ps(eq_r0r1r2r3) != 0;

#endif
    }

#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_COMPILER_MSVC
#pragma float_control(pop)
#endif

    template <typename T>
    [[nodiscard]] mathinline T mathcall Infinity() noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;

        result.M.R[0] = Impl::c_V4_F32_Positive_Infinity.V;
        result.M.R[1] = Impl::c_V4_F32_Positive_Infinity.V;
        result.M.R[2] = Impl::c_V4_F32_Positive_Infinity.V;
        result.M.R[3] = Impl::c_V4_F32_Positive_Infinity.V;

        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline bool mathcall IsInfinity(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        size_t count = 16;

        uint32_t const* item = reinterpret_cast<uint32_t const*>(&m.M.F[0]);

        do
        {
            uint32_t const value = (*item);

            if (FloatTraits<float>::BitIsInf(value))
            {
                break;
            }

            ++item;
        } while (--count != 0);

        return count != 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const abs = Impl::c_V4_U32_Mask_MaskAbs.V;

        __m128 const abs_r0 = _mm_and_ps(r0, abs);
        __m128 const abs_r1 = _mm_and_ps(r1, abs);
        __m128 const abs_r2 = _mm_and_ps(r2, abs);
        __m128 const abs_r3 = _mm_and_ps(r3, abs);

        __m128 const inf = Impl::c_V4_F32_Positive_Infinity.V;

        __m128 const inf_r0 = _mm_cmpeq_ps(abs_r0, inf);
        __m128 const inf_r1 = _mm_cmpeq_ps(abs_r1, inf);
        __m128 const inf_r2 = _mm_cmpeq_ps(abs_r2, inf);
        __m128 const inf_r3 = _mm_cmpeq_ps(abs_r3, inf);

        __m128 const inf_r0r1 = _mm_or_ps(inf_r0, inf_r1);
        __m128 const inf_r2r3 = _mm_or_ps(inf_r2, inf_r3);

        __m128 const inf_r0r1r2r3 = _mm_or_ps(inf_r0r1, inf_r2r3);

        return _mm_movemask_ps(inf_r0r1r2r3) != 0;

#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Identity() noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
        result.M.R[0] = Impl::c_V4_F32_PositiveUnitX.V;
        result.M.R[1] = Impl::c_V4_F32_PositiveUnitY.V;
        result.M.R[2] = Impl::c_V4_F32_PositiveUnitZ.V;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline bool mathcall IsIdentity(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        uint32_t const* items = reinterpret_cast<uint32_t const*>(&m.M.M[0][0]);

        uint32_t one = items[0] ^ 0x3f80'0000;
        uint32_t zero = items[1];
        zero |= items[2];
        zero |= items[3];

        zero |= items[4];
        one |= items[5];
        zero |= items[6];
        zero |= items[7];

        zero |= items[8];
        zero |= items[9];
        one |= items[10];
        zero |= items[11];

        zero |= items[12];
        zero |= items[13];
        zero |= items[14];
        one |= items[15] ^ 0x3f80'0000;

        // clear sign mask
        zero &= 0x7fff'ffff;
        one |= zero;

        return one == 0;

#elif GRAPHYTE_HW_AVX

        __m128 const r0 = m.M.R[0];
        __m128 const r1 = m.M.R[1];
        __m128 const r2 = m.M.R[2];
        __m128 const r3 = m.M.R[3];

        __m128 const m0 = _mm_cmpeq_ps(r0, Impl::c_V4_F32_PositiveUnitX.V);
        __m128 const m1 = _mm_cmpeq_ps(r1, Impl::c_V4_F32_PositiveUnitY.V);
        __m128 const m2 = _mm_cmpeq_ps(r2, Impl::c_V4_F32_PositiveUnitZ.V);
        __m128 const m3 = _mm_cmpeq_ps(r3, Impl::c_V4_F32_PositiveUnitW.V);

        __m128 const m1_0 = _mm_and_ps(m0, m1);
        __m128 const m1_1 = _mm_and_ps(m2, m3);

        __m128 const m2_final = _mm_and_ps(m1_0, m1_1);

        return _mm_movemask_ps(m2_final) == 0b1111;
#endif
    }

    [[nodiscard]] mathinline Vector4 mathcall GetBaseX(Matrix m) noexcept
    {
        return { m.M.R[0] };
    }

    [[nodiscard]] mathinline Vector4 mathcall GetBaseY(Matrix m) noexcept
    {
        return { m.M.R[1] };
    }

    [[nodiscard]] mathinline Vector4 mathcall GetBaseZ(Matrix m) noexcept
    {
        return { m.M.R[2] };
    }

    [[nodiscard]] mathinline Vector4 mathcall GetBaseW(Matrix m) noexcept
    {
        return { m.M.R[3] };
    }
}


// Arithmetic
namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall OuterProduct(Vector4 c, Vector4 r) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(c, SplatX<Vector4>(r)).V;
        result.M.R[1] = Multiply(c, SplatY<Vector4>(r)).V;
        result.M.R[2] = Multiply(c, SplatZ<Vector4>(r)).V;
        result.M.R[3] = Multiply(c, SplatW<Vector4>(r)).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vmulq_f32(c.V, vdupq_lane_f32(vget_low_f32(r.V), 0));
        result.M.R[1] = vmulq_f32(c.V, vdupq_lane_f32(vget_low_f32(r.V), 1));
        result.M.R[2] = vmulq_f32(c.V, vdupq_lane_f32(vget_high_f32(r.V), 0));
        result.M.R[3] = vmulq_f32(c.V, vdupq_lane_f32(vget_high_f32(r.V), 1));
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(0, 0, 0, 0)));
        result.M.R[1] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(1, 1, 1, 1)));
        result.M.R[2] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(2, 2, 2, 2)));
        result.M.R[3] = _mm_mul_ps(c.V, _mm_permute_ps(r.V, _MM_SHUFFLE(3, 3, 3, 3)));
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline Vector4 mathcall Diagnoal(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            m.M.M[0][0],
            m.M.M[1][1],
            m.M.M[2][2],
            m.M.M[3][3],
        } } };
        return { result.V };

#elif GRAPHYTE_HW_NEON
        uint32x4_t const t0_x = vandq_u32(vreinterpretq_u32_f32(m.M.R[0]), vreinterpretq_u32_f32(Impl::c_V4_U32_Mask_1000.V));
        uint32x4_t const t0_y = vandq_u32(vreinterpretq_u32_f32(m.M.R[1]), vreinterpretq_u32_f32(Impl::c_V4_U32_Mask_0100.V));
        uint32x4_t const t0_z = vandq_u32(vreinterpretq_u32_f32(m.M.R[2]), vreinterpretq_u32_f32(Impl::c_V4_U32_Mask_0010.V));
        uint32x4_t const t0_w = vandq_u32(vreinterpretq_u32_f32(m.M.R[3]), vreinterpretq_u32_f32(Impl::c_V4_U32_Mask_0001.V));

        uint32x4_t const t1_xy = vorq_u32(t0_x, t0_y);
        uint32x4_t const t1_zw = vorq_u32(t0_z, t0_w);

        uint32x4_t const t2_xyzw = vorq_u32(t1_xy, t1_zw);

        return { vreinterpret_f32_u32(t2_xyzw) };

#elif GRAPHYTE_HW_AVX
        __m128 const t0_x = _mm_and_ps(m.M.R[0], Impl::c_V4_U32_Mask_1000.V);
        __m128 const t0_y = _mm_and_ps(m.M.R[1], Impl::c_V4_U32_Mask_0100.V);
        __m128 const t0_z = _mm_and_ps(m.M.R[2], Impl::c_V4_U32_Mask_0010.V);
        __m128 const t0_w = _mm_and_ps(m.M.R[3], Impl::c_V4_U32_Mask_0001.V);

        __m128 const t1_xy = _mm_or_ps(t0_x, t0_y);
        __m128 const t1_zw = _mm_or_ps(t0_z, t0_w);

        __m128 const t2_xyzw = _mm_or_ps(t1_xy, t1_zw);
        return { t2_xyzw };
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline Vector4 mathcall Trace(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector4 const diagnoal = Diagnoal(m);
        return Hsum(diagnoal);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Add(T m1, T m2) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Add(Vector4{ m1.M.R[0] }, Vector4{ m2.M.R[0] }).V;
        result.M.R[1] = Add(Vector4{ m1.M.R[1] }, Vector4{ m2.M.R[1] }).V;
        result.M.R[2] = Add(Vector4{ m1.M.R[2] }, Vector4{ m2.M.R[2] }).V;
        result.M.R[3] = Add(Vector4{ m1.M.R[3] }, Vector4{ m2.M.R[3] }).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vaddq_f32(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = vaddq_f32(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = vaddq_f32(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = vaddq_f32(m1.M.R[3], m2.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_add_ps(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = _mm_add_ps(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = _mm_add_ps(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = _mm_add_ps(m1.M.R[3], m2.M.R[3]);
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Subtract(T m1, T m2) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Subtract(Vector4{ m1.M.R[0] }, Vector4{ m2.M.R[0] }).V;
        result.M.R[1] = Subtract(Vector4{ m1.M.R[1] }, Vector4{ m2.M.R[1] }).V;
        result.M.R[2] = Subtract(Vector4{ m1.M.R[2] }, Vector4{ m2.M.R[2] }).V;
        result.M.R[3] = Subtract(Vector4{ m1.M.R[3] }, Vector4{ m2.M.R[3] }).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vsubq_f32(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = vsubq_f32(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = vsubq_f32(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = vsubq_f32(m1.M.R[3], m2.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_sub_ps(m1.M.R[0], m2.M.R[0]);
        result.M.R[1] = _mm_sub_ps(m1.M.R[1], m2.M.R[1]);
        result.M.R[2] = _mm_sub_ps(m1.M.R[2], m2.M.R[2]);
        result.M.R[3] = _mm_sub_ps(m1.M.R[3], m2.M.R[3]);
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Negate(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
        result.M.R[0] = Negate(Vector4{ m.M.R[0] }).V;
        result.M.R[1] = Negate(Vector4{ m.M.R[1] }).V;
        result.M.R[2] = Negate(Vector4{ m.M.R[2] }).V;
        result.M.R[3] = Negate(Vector4{ m.M.R[3] }).V;
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Multiply(float s, T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(Vector4{ m.M.R[0] }, s).V;
        result.M.R[1] = Multiply(Vector4{ m.M.R[1] }, s).V;
        result.M.R[2] = Multiply(Vector4{ m.M.R[2] }, s).V;
        result.M.R[3] = Multiply(Vector4{ m.M.R[3] }, s).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0] = vmulq_f32(m.M.R[0], sv);
        result.M.R[1] = vmulq_f32(m.M.R[1], sv);
        result.M.R[2] = vmulq_f32(m.M.R[2], sv);
        result.M.R[3] = vmulq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0] = _mm_mul_ps(m.M.R[0], sv);
        result.M.R[1] = _mm_mul_ps(m.M.R[1], sv);
        result.M.R[2] = _mm_mul_ps(m.M.R[2], sv);
        result.M.R[3] = _mm_mul_ps(m.M.R[3], sv);
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Multiply(T m, float s) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(Vector4{ m.M.R[0] }, s).V;
        result.M.R[1] = Multiply(Vector4{ m.M.R[1] }, s).V;
        result.M.R[2] = Multiply(Vector4{ m.M.R[2] }, s).V;
        result.M.R[3] = Multiply(Vector4{ m.M.R[3] }, s).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0] = vmulq_f32(m.M.R[0], sv);
        result.M.R[1] = vmulq_f32(m.M.R[1], sv);
        result.M.R[2] = vmulq_f32(m.M.R[2], sv);
        result.M.R[3] = vmulq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0] = _mm_mul_ps(m.M.R[0], sv);
        result.M.R[1] = _mm_mul_ps(m.M.R[1], sv);
        result.M.R[2] = _mm_mul_ps(m.M.R[2], sv);
        result.M.R[3] = _mm_mul_ps(m.M.R[3], sv);
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Divide(T m, float s) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const sv = Replicate<Vector4>(s);
        result.M.R[0] = Divide(Vector4{ m.M.R[0] }, sv).V;
        result.M.R[1] = Divide(Vector4{ m.M.R[1] }, sv).V;
        result.M.R[2] = Divide(Vector4{ m.M.R[2] }, sv).V;
        result.M.R[3] = Divide(Vector4{ m.M.R[3] }, sv).V;
#elif GRAPHYTE_HW_NEON
        float32x4_t const sv = vdupq_n_f32(s);
        result.M.R[0] = vdivq_f32(m.M.R[0], sv);
        result.M.R[1] = vdivq_f32(m.M.R[1], sv);
        result.M.R[2] = vdivq_f32(m.M.R[2], sv);
        result.M.R[3] = vdivq_f32(m.M.R[3], sv);
#elif GRAPHYTE_HW_AVX
        __m128 const sv = _mm_set1_ps(s);
        result.M.R[0] = _mm_div_ps(m.M.R[0], sv);
        result.M.R[1] = _mm_div_ps(m.M.R[1], sv);
        result.M.R[2] = _mm_div_ps(m.M.R[2], sv);
        result.M.R[3] = _mm_div_ps(m.M.R[3], sv);
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall ComponentMultiply(T a, T b) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.R[0] = Multiply(Vector4{ a.M.R[0] }, Vector4{ b.M.R[0] }).V;
        result.M.R[1] = Multiply(Vector4{ a.M.R[1] }, Vector4{ b.M.R[1] }).V;
        result.M.R[2] = Multiply(Vector4{ a.M.R[2] }, Vector4{ b.M.R[2] }).V;
        result.M.R[3] = Multiply(Vector4{ a.M.R[3] }, Vector4{ b.M.R[3] }).V;
#elif GRAPHYTE_HW_NEON
        result.M.R[0] = vmulq_f32(a.M.R[0], b.M.R[0]);
        result.M.R[1] = vmulq_f32(a.M.R[1], b.M.R[1]);
        result.M.R[2] = vmulq_f32(a.M.R[2], b.M.R[2]);
        result.M.R[3] = vmulq_f32(a.M.R[3], b.M.R[3]);
#elif GRAPHYTE_HW_AVX
        result.M.R[0] = _mm_mul_ps(a.M.R[0], b.M.R[0]);
        result.M.R[1] = _mm_mul_ps(a.M.R[1], b.M.R[1]);
        result.M.R[2] = _mm_mul_ps(a.M.R[2], b.M.R[2]);
        result.M.R[3] = _mm_mul_ps(a.M.R[3], b.M.R[3]);
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Multiply(T a, T b) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        {
            float const x = a.M.M[0][0];
            float const y = a.M.M[0][1];
            float const z = a.M.M[0][2];
            float const w = a.M.M[0][3];

            result.M.M[0][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[0][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[0][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[0][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[1][0];
            float const y = a.M.M[1][1];
            float const z = a.M.M[1][2];
            float const w = a.M.M[1][3];

            result.M.M[1][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[1][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[1][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[1][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[2][0];
            float const y = a.M.M[2][1];
            float const z = a.M.M[2][2];
            float const w = a.M.M[2][3];

            result.M.M[2][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[2][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[2][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[2][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        {
            float const x = a.M.M[3][0];
            float const y = a.M.M[3][1];
            float const z = a.M.M[3][2];
            float const w = a.M.M[3][3];

            result.M.M[3][0] = (b.M.M[0][0] * x) + (b.M.M[1][0] * y) + (b.M.M[2][0] * z) + (b.M.M[3][0] * w);
            result.M.M[3][1] = (b.M.M[0][1] * x) + (b.M.M[1][1] * y) + (b.M.M[2][1] * z) + (b.M.M[3][1] * w);
            result.M.M[3][2] = (b.M.M[0][2] * x) + (b.M.M[1][2] * y) + (b.M.M[2][2] * z) + (b.M.M[3][2] * w);
            result.M.M[3][3] = (b.M.M[0][3] * x) + (b.M.M[1][3] * y) + (b.M.M[2][3] * z) + (b.M.M[3][3] * w);
        }

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;

#if GRAPHYTE_HW_AVX2
        __m128 const m_r0 = a.M.R[0];
        __m128 const x_r0 = _mm_broadcastss_ps(m_r0);
        __m128 const y_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);
#endif

        __m128 const abx_r0 = _mm_mul_ps(x_r0, b.M.R[0]);
        __m128 const aby_r0 = Impl::avx_fmadd_f32x4(y_r0, b.M.R[1], abx_r0);
        __m128 const abz_r0 = Impl::avx_fmadd_f32x4(z_r0, b.M.R[2], aby_r0);
        __m128 const abw_r0 = Impl::avx_fmadd_f32x4(w_r0, b.M.R[3], abz_r0);


#if GRAPHYTE_HW_AVX2
        __m128 const m_r1 = a.M.R[1];
        __m128 const x_r1 = _mm_broadcastss_ps(m_r1);
        __m128 const y_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);
#endif

        __m128 const abx_r1 = _mm_mul_ps(x_r1, b.M.R[0]);
        __m128 const aby_r1 = Impl::avx_fmadd_f32x4(y_r1, b.M.R[1], abx_r1);
        __m128 const abz_r1 = Impl::avx_fmadd_f32x4(z_r1, b.M.R[2], aby_r1);
        __m128 const abw_r1 = Impl::avx_fmadd_f32x4(w_r1, b.M.R[3], abz_r1);


#if GRAPHYTE_HW_AVX2
        __m128 const m_r2 = a.M.R[2];
        __m128 const x_r2 = _mm_broadcastss_ps(m_r2);
        __m128 const y_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);
#endif

        __m128 const abx_r2 = _mm_mul_ps(x_r2, b.M.R[0]);
        __m128 const aby_r2 = Impl::avx_fmadd_f32x4(y_r2, b.M.R[1], abx_r2);
        __m128 const abz_r2 = Impl::avx_fmadd_f32x4(z_r2, b.M.R[2], aby_r2);
        __m128 const abw_r2 = Impl::avx_fmadd_f32x4(w_r2, b.M.R[3], abz_r2);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r3 = a.M.R[3];
        __m128 const x_r3 = _mm_broadcastss_ps(m_r3);
        __m128 const y_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);
#endif

        __m128 const abx_r3 = _mm_mul_ps(x_r3, b.M.R[0]);
        __m128 const aby_r3 = Impl::avx_fmadd_f32x4(y_r3, b.M.R[1], abx_r3);
        __m128 const abz_r3 = Impl::avx_fmadd_f32x4(z_r3, b.M.R[2], aby_r3);
        __m128 const abw_r3 = Impl::avx_fmadd_f32x4(w_r3, b.M.R[3], abz_r3);

        result.M.R[0] = abw_r0;
        result.M.R[1] = abw_r1;
        result.M.R[2] = abw_r2;
        result.M.R[3] = abw_r3;

        return result;

#elif GRAPHYTE_HW_NEON

        // rNc0 = (b.r0 * a.rN.xxxx)
        float32x4_t const r0c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[0], 0);
        float32x4_t const r1c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[1], 0);
        float32x4_t const r2c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[2], 0);
        float32x4_t const r3c0 = vmulq_laneq_f32(b.M.R[0], a.M.R[3], 0);

        // rNc1 = (b.r1 * a.rN.yyyy) + rNc0
        float32x4_t const r0c1 = vmlaq_laneq_f32(r0c0, b.M.R[1], a.M.R[0], 1);
        float32x4_t const r1c1 = vmlaq_laneq_f32(r1c0, b.M.R[1], a.M.R[1], 1);
        float32x4_t const r2c1 = vmlaq_laneq_f32(r2c0, b.M.R[1], a.M.R[2], 1);
        float32x4_t const r3c1 = vmlaq_laneq_f32(r3c0, b.M.R[1], a.M.R[3], 1);

        // rNc2 = (b.r2 * a.rN.zzzz) + rNc1
        float32x4_t const r0c2 = vmlaq_laneq_f32(r0c1, b.M.R[2], a.M.R[0], 2);
        float32x4_t const r1c2 = vmlaq_laneq_f32(r1c1, b.M.R[2], a.M.R[1], 2);
        float32x4_t const r2c2 = vmlaq_laneq_f32(r2c1, b.M.R[2], a.M.R[2], 2);
        float32x4_t const r3c2 = vmlaq_laneq_f32(r3c1, b.M.R[2], a.M.R[3], 2);

        // rNc3 = (b.r3 * a.rN.wwww) + rNc2
        float32x4_t const r0c3 = vmlaq_laneq_f32(r0c2, b.M.R[3], a.M.R[0], 3);
        float32x4_t const r1c3 = vmlaq_laneq_f32(r1c2, b.M.R[3], a.M.R[1], 3);
        float32x4_t const r2c3 = vmlaq_laneq_f32(r2c2, b.M.R[3], a.M.R[2], 3);
        float32x4_t const r3c3 = vmlaq_laneq_f32(r3c2, b.M.R[3], a.M.R[3], 3);

        Matrix result;
        result.M.R[0] = r0c3;
        result.M.R[1] = r1c3;
        result.M.R[2] = r2c3;
        result.M.R[3] = r3c3;
        return result;

#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall MultiplyTranspose(T a, T b) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS

        Matrix result;

        {
            float const x = b.M.M[0][0];
            float const y = b.M.M[0][1];
            float const z = b.M.M[0][2];
            float const w = b.M.M[0][3];

            result.M.M[0][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[0][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[0][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[0][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[1][0];
            float const y = b.M.M[1][1];
            float const z = b.M.M[1][2];
            float const w = b.M.M[1][3];

            result.M.M[1][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[1][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[1][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[1][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[2][0];
            float const y = b.M.M[2][1];
            float const z = b.M.M[2][2];
            float const w = b.M.M[2][3];

            result.M.M[2][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[2][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[2][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[2][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        {
            float const x = b.M.M[3][0];
            float const y = b.M.M[3][1];
            float const z = b.M.M[3][2];
            float const w = b.M.M[3][3];

            result.M.M[3][0] = (a.M.M[0][0] * x) + (a.M.M[0][1] * y) + (a.M.M[0][2] * z) + (a.M.M[0][3] * w);
            result.M.M[3][1] = (a.M.M[1][0] * x) + (a.M.M[1][1] * y) + (a.M.M[1][2] * z) + (a.M.M[1][3] * w);
            result.M.M[3][2] = (a.M.M[2][0] * x) + (a.M.M[2][1] * y) + (a.M.M[2][2] * z) + (a.M.M[2][3] * w);
            result.M.M[3][3] = (a.M.M[3][0] * x) + (a.M.M[3][1] * y) + (a.M.M[3][2] * z) + (a.M.M[3][3] * w);
        }

        return result;

#elif GRAPHYTE_HW_AVX
        Matrix result;


#if GRAPHYTE_HW_AVX2
        __m128 const m_r0 = a.M.R[0];
        __m128 const x_r0 = _mm_broadcastss_ps(m_r0);
        __m128 const y_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r0 = _mm_permute_ps(m_r0, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 0);
        __m128 const y_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 1);
        __m128 const z_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 2);
        __m128 const w_r0 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[0]) + 3);
#endif

        __m128 const abx_r0 = _mm_mul_ps(x_r0, b.M.R[0]);
        __m128 const aby_r0 = Impl::avx_fmadd_f32x4(y_r0, b.M.R[1], abx_r0);
        __m128 const abz_r0 = Impl::avx_fmadd_f32x4(z_r0, b.M.R[2], aby_r0);
        __m128 const abw_r0 = Impl::avx_fmadd_f32x4(w_r0, b.M.R[3], abz_r0);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r1 = a.M.R[1];
        __m128 const x_r1 = _mm_broadcastss_ps(m_r1);
        __m128 const y_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r1 = _mm_permute_ps(m_r1, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 0);
        __m128 const y_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 1);
        __m128 const z_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 2);
        __m128 const w_r1 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[1]) + 3);
#endif

        __m128 const abx_r1 = _mm_mul_ps(x_r1, b.M.R[0]);
        __m128 const aby_r1 = Impl::avx_fmadd_f32x4(y_r1, b.M.R[1], abx_r1);
        __m128 const abz_r1 = Impl::avx_fmadd_f32x4(z_r1, b.M.R[2], aby_r1);
        __m128 const abw_r1 = Impl::avx_fmadd_f32x4(w_r1, b.M.R[3], abz_r1);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r2 = a.M.R[2];
        __m128 const x_r2 = _mm_broadcastss_ps(m_r2);
        __m128 const y_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r2 = _mm_permute_ps(m_r2, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 0);
        __m128 const y_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 1);
        __m128 const z_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 2);
        __m128 const w_r2 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[2]) + 3);
#endif

        __m128 const abx_r2 = _mm_mul_ps(x_r2, b.M.R[0]);
        __m128 const aby_r2 = Impl::avx_fmadd_f32x4(y_r2, b.M.R[1], abx_r2);
        __m128 const abz_r2 = Impl::avx_fmadd_f32x4(z_r2, b.M.R[2], aby_r2);
        __m128 const abw_r2 = Impl::avx_fmadd_f32x4(w_r2, b.M.R[3], abz_r2);

#if GRAPHYTE_HW_AVX2
        __m128 const m_r3 = a.M.R[3];
        __m128 const x_r3 = _mm_broadcastss_ps(m_r3);
        __m128 const y_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(1, 1, 1, 1);
        __m128 const z_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(2, 2, 2, 2);
        __m128 const w_r3 = _mm_permute_ps(m_r3, _MM_SHUFFLE(3, 3, 3, 3);
#else
        __m128 const x_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 0);
        __m128 const y_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 1);
        __m128 const z_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 2);
        __m128 const w_r3 = _mm_broadcast_ss(reinterpret_cast<float const*>(&a.M.R[3]) + 3);
#endif

        __m128 const abx_r3 = _mm_mul_ps(x_r3, b.M.R[0]);
        __m128 const aby_r3 = Impl::avx_fmadd_f32x4(y_r3, b.M.R[1], abx_r3);
        __m128 const abz_r3 = Impl::avx_fmadd_f32x4(z_r3, b.M.R[2], aby_r3);
        __m128 const abw_r3 = Impl::avx_fmadd_f32x4(w_r3, b.M.R[3], abz_r3);

        __m128 const trn_r0 = _mm_shuffle_ps(abw_r0, abw_r1, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trn_r2 = _mm_shuffle_ps(abw_r0, abw_r1, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const trn_r1 = _mm_shuffle_ps(abw_r2, abw_r3, _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trn_r3 = _mm_shuffle_ps(abw_r2, abw_r3, _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const final_r0 = _mm_shuffle_ps(trn_r0, trn_r1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const final_r1 = _mm_shuffle_ps(trn_r0, trn_r1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const final_r2 = _mm_shuffle_ps(trn_r2, trn_r3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const final_r3 = _mm_shuffle_ps(trn_r2, trn_r3, _MM_SHUFFLE(3, 1, 3, 1));

        result.M.R[0] = final_r0;
        result.M.R[1] = final_r1;
        result.M.R[2] = final_r2;
        result.M.R[3] = final_r3;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Transpose(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = m.M.M[0][0];
        result.M.M[0][1] = m.M.M[1][0];
        result.M.M[0][2] = m.M.M[2][0];
        result.M.M[0][3] = m.M.M[3][0];

        result.M.M[1][0] = m.M.M[0][1];
        result.M.M[1][1] = m.M.M[1][1];
        result.M.M[1][2] = m.M.M[2][1];
        result.M.M[1][3] = m.M.M[3][1];

        result.M.M[2][0] = m.M.M[0][2];
        result.M.M[2][1] = m.M.M[1][2];
        result.M.M[2][2] = m.M.M[2][2];
        result.M.M[2][3] = m.M.M[3][2];

        result.M.M[3][0] = m.M.M[0][3];
        result.M.M[3][1] = m.M.M[1][3];
        result.M.M[3][2] = m.M.M[2][3];
        result.M.M[3][3] = m.M.M[3][3];

        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const trx_r0 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trx_r2 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const trx_r1 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        __m128 const trx_r3 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));

        __m128 const res_r0 = _mm_shuffle_ps(trx_r0, trx_r1, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const res_r1 = _mm_shuffle_ps(trx_r0, trx_r1, _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const res_r2 = _mm_shuffle_ps(trx_r2, trx_r3, _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const res_r3 = _mm_shuffle_ps(trx_r2, trx_r3, _MM_SHUFFLE(3, 1, 3, 1));

        Matrix result;
        result.M.R[0] = res_r0;
        result.M.R[1] = res_r1;
        result.M.R[2] = res_r2;
        result.M.R[3] = res_r3;
        return result;
#elif GRAPHYTE_HW_NEON
        float32x4x2_t const t0 = vzipq_f32(m.M.R[0], m.M.R[2]);
        float32x4x2_t const t1 = vzipq_f32(m.M.R[1], m.M.R[3]);
        float32x4x2_t const r0 = vzipq_f32(t0.val[0], t1.val[0]);
        float32x4x2_t const r1 = vzipq_f32(t0.val[1], t1.val[1]);

        Matrix result;
        result.M.R[0] = r0.val[0];
        result.M.R[1] = r0.val[1];
        result.M.R[2] = r1.val[0];
        result.M.R[3] = r1.val[1];
        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall Inverse(T m, Vector4* determinant = nullptr) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix const mt = Transpose(m);

        Vector4 const ca0 = Swizzle<0, 0, 1, 1>(Vector4{ mt.M.R[2] });
        Vector4 const ca1 = Swizzle<2, 3, 2, 3>(Vector4{ mt.M.R[3] });
        Vector4 const cb0 = Swizzle<0, 0, 1, 1>(Vector4{ mt.M.R[0] });
        Vector4 const cb1 = Swizzle<2, 3, 2, 3>(Vector4{ mt.M.R[1] });
        Vector4 const cc0 = Permute<0, 2, 4, 6>(Vector4{ mt.M.R[2] }, Vector4{ mt.M.R[0] });
        Vector4 const cc1 = Permute<1, 3, 5, 7>(Vector4{ mt.M.R[3] }, Vector4{ mt.M.R[1] });

        Vector4 const ra0 = Multiply(ca0, ca1);
        Vector4 const rb0 = Multiply(cb0, cb1);
        Vector4 const rc0 = Multiply(cc0, cc1);

        Vector4 const da0 = Swizzle<2, 3, 2, 3>(Vector4{ mt.M.R[2] });
        Vector4 const da1 = Swizzle<0, 0, 1, 1>(Vector4{ mt.M.R[3] });
        Vector4 const db0 = Swizzle<2, 3, 2, 3>(Vector4{ mt.M.R[0] });
        Vector4 const db1 = Swizzle<0, 0, 1, 1>(Vector4{ mt.M.R[1] });
        Vector4 const dc0 = Permute<1, 3, 5, 7>(Vector4{ mt.M.R[2] }, Vector4{ mt.M.R[0] });
        Vector4 const dc1 = Permute<0, 2, 4, 6>(Vector4{ mt.M.R[3] }, Vector4{ mt.M.R[1] });

        Vector4 const ra1 = NegateMultiplyAdd(da0, da1, ra0);
        Vector4 const rb1 = NegateMultiplyAdd(db0, db1, rb0);
        Vector4 const rc1 = NegateMultiplyAdd(dc0, dc1, rc0);

        Vector4 const ea0 = Swizzle<1, 2, 0, 1>(Vector4{ mt.M.R[1] });
        Vector4 const ea1 = Permute<5, 1, 3, 0>(ra1, rc1);
        Vector4 const eb0 = Swizzle<2, 0, 1, 0>(Vector4{ mt.M.R[0] });
        Vector4 const eb1 = Permute<3, 5, 1, 2>(ra1, rc1);
        Vector4 const ec0 = Swizzle<1, 2, 0, 1>(Vector4{ mt.M.R[3] });
        Vector4 const ec1 = Permute<7, 1, 3, 0>(rb1, rc1);
        Vector4 const ed0 = Swizzle<2, 0, 1, 0>(Vector4{ mt.M.R[2] });
        Vector4 const ed1 = Permute<3, 7, 1, 2>(rb1, rc1);

        Vector4 const fa0 = Multiply(ea0, ea1);
        Vector4 const fb0 = Multiply(eb0, eb1);
        Vector4 const fc0 = Multiply(ec0, ec1);
        Vector4 const fd0 = Multiply(ed0, ed1);

        Vector4 const ga0 = Swizzle<2, 3, 1, 2>(Vector4{ mt.M.R[1] });
        Vector4 const ga1 = Permute<3, 0, 1, 4>(ra1, rc1);
        Vector4 const gb0 = Swizzle<3, 2, 3, 1>(Vector4{ mt.M.R[0] });
        Vector4 const gb1 = Permute<2, 1, 4, 0>(ra1, rc1);
        Vector4 const gc0 = Swizzle<2, 3, 1, 2>(Vector4{ mt.M.R[3] });
        Vector4 const gc1 = Permute<3, 0, 1, 6>(rb1, rc1);
        Vector4 const gd0 = Swizzle<3, 2, 3, 1>(Vector4{ mt.M.R[2] });
        Vector4 const gd1 = Permute<2, 1, 6, 0>(rb1, rc1);

        Vector4 const fa1 = NegateMultiplyAdd(ga0, ga1, fa0);
        Vector4 const fb1 = NegateMultiplyAdd(gb0, gb1, fb0);
        Vector4 const fc1 = NegateMultiplyAdd(gc0, gc1, fc0);
        Vector4 const fd1 = NegateMultiplyAdd(gd0, gd1, fd0);

        Vector4 const ha0 = Swizzle<3, 0, 3, 0>(Vector4{ mt.M.R[1] });
        Vector4 const ha1 = Permute<2, 5, 4, 2>(ra1, rc1);
        Vector4 const hb0 = Swizzle<1, 3, 0, 2>(Vector4{ mt.M.R[0] });
        Vector4 const hb1 = Permute<5, 0, 3, 4>(ra1, rc1);
        Vector4 const hc0 = Swizzle<3, 0, 3, 0>(Vector4{ mt.M.R[3] });
        Vector4 const hc1 = Permute<2, 7, 6, 2>(rb1, rc1);
        Vector4 const hd0 = Swizzle<1, 3, 0, 2>(Vector4{ mt.M.R[2] });
        Vector4 const hd1 = Permute<7, 0, 3, 6>(rb1, rc1);

        Vector4 const r1 = NegateMultiplyAdd(ha0, ha1, fa1);
        Vector4 const r0 = MultiplyAdd(ha0, ha1, fa1);
        Vector4 const r3 = MultiplyAdd(hb0, hb1, fb1);
        Vector4 const r2 = NegateMultiplyAdd(hb0, hb1, fb1);
        Vector4 const r5 = NegateMultiplyAdd(hc0, hc1, fc1);
        Vector4 const r4 = MultiplyAdd(hc0, hc1, fc1);
        Vector4 const r7 = MultiplyAdd(hd0, hd1, fd1);
        Vector4 const r6 = NegateMultiplyAdd(hd0, hd1, fd1);

        // Transpose matrix
        Matrix partial;
        partial.M.R[0] = Select(r0, r1, Bool4{ Impl::c_V4_U32_Mask_0101.V }).V;
        partial.M.R[1] = Select(r2, r3, Bool4{ Impl::c_V4_U32_Mask_0101.V }).V;
        partial.M.R[2] = Select(r4, r5, Bool4{ Impl::c_V4_U32_Mask_0101.V }).V;
        partial.M.R[3] = Select(r6, r7, Bool4{ Impl::c_V4_U32_Mask_0101.V }).V;

        Vector4 const det = Dot(Vector4{ partial.M.R[0] }, Vector4{ mt.M.R[0] });

        if (determinant != nullptr)
        {
            (*determinant) = det;
        }

        Vector4 const rcp_det = Reciprocal(det);

        Matrix result;
        result.M.R[0] = Multiply(Vector4{ partial.M.R[0] }, rcp_det).V;
        result.M.R[1] = Multiply(Vector4{ partial.M.R[1] }, rcp_det).V;
        result.M.R[2] = Multiply(Vector4{ partial.M.R[2] }, rcp_det).V;
        result.M.R[3] = Multiply(Vector4{ partial.M.R[3] }, rcp_det).V;

        return result;
#elif GRAPHYTE_HW_AVX

        Matrix mt = Transpose(m);

        __m128 const ca0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const ca1 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const cb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const cb1 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const cc0 = _mm_shuffle_ps(mt.M.R[2], mt.M.R[0], _MM_SHUFFLE(2, 0, 2, 0));
        __m128 const cc1 = _mm_shuffle_ps(mt.M.R[3], mt.M.R[1], _MM_SHUFFLE(3, 1, 3, 1));

        __m128 const ra0 = _mm_mul_ps(ca0, ca1);
        __m128 const rb0 = _mm_mul_ps(cb0, cb1);
        __m128 const rc0 = _mm_mul_ps(cc0, cc1);

        __m128 const da0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const da1 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const db0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const db1 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(1, 1, 0, 0));
        __m128 const dc0 = _mm_shuffle_ps(mt.M.R[2], mt.M.R[0], _MM_SHUFFLE(3, 1, 3, 1));
        __m128 const dc1 = _mm_shuffle_ps(mt.M.R[3], mt.M.R[1], _MM_SHUFFLE(2, 0, 2, 0));

        __m128 const ra1 = Impl::avx_fnmadd_f32x4(da0, da1, ra0);
        __m128 const rb1 = Impl::avx_fnmadd_f32x4(db0, db1, rb0);
        __m128 const rc1 = Impl::avx_fnmadd_f32x4(dc0, dc1, rc0);


        __m128 const tmp1 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 1, 3, 1));
        __m128 const tmp2 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 3, 3, 1));
        __m128 const ea0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const ea1 = _mm_shuffle_ps(tmp1, ra1, _MM_SHUFFLE(0, 3, 0, 2));
        __m128 const eb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const eb1 = _mm_shuffle_ps(tmp1, ra1, _MM_SHUFFLE(2, 1, 2, 1));
        __m128 const ec0 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(1, 0, 2, 1));
        __m128 const ec1 = _mm_shuffle_ps(tmp2, rb1, _MM_SHUFFLE(0, 3, 0, 2));
        __m128 const ed0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(0, 1, 0, 2));
        __m128 const ed1 = _mm_shuffle_ps(tmp2, rb1, _MM_SHUFFLE(2, 1, 2, 1));

        __m128 const fa0 = _mm_mul_ps(ea0, ea1);
        __m128 const fb0 = _mm_mul_ps(eb0, eb1);
        __m128 const fc0 = _mm_mul_ps(ec0, ec1);
        __m128 const fd0 = _mm_mul_ps(ed0, ed1);

        __m128 const tmp3 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(0, 0, 1, 0));
        __m128 const ga0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const ga1 = _mm_shuffle_ps(ra1, tmp3, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const gb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const gb1 = _mm_shuffle_ps(ra1, tmp3, _MM_SHUFFLE(0, 2, 1, 2));

        __m128 const tmp4 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(2, 2, 1, 0));
        __m128 const gc0 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(2, 1, 3, 2));
        __m128 const gc1 = _mm_shuffle_ps(rb1, tmp4, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const gd0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(1, 3, 2, 3));
        __m128 const gd1 = _mm_shuffle_ps(rb1, tmp4, _MM_SHUFFLE(0, 2, 1, 2));

        __m128 const fa1 = Impl::avx_fnmadd_f32x4(ga0, ga1, fa0);
        __m128 const fb1 = Impl::avx_fnmadd_f32x4(gb0, gb1, fb0);
        __m128 const fc1 = Impl::avx_fnmadd_f32x4(gc0, gc1, fc0);
        __m128 const fd1 = Impl::avx_fnmadd_f32x4(gd0, gd1, fd0);

        __m128 const ha0 = _mm_permute_ps(mt.M.R[1], _MM_SHUFFLE(0, 3, 0, 3));

        __m128 const tmp5 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 0, 2, 2));
        __m128 const ha1 = _mm_permute_ps(tmp5, _MM_SHUFFLE(0, 2, 3, 0));
        __m128 const hb0 = _mm_permute_ps(mt.M.R[0], _MM_SHUFFLE(2, 0, 3, 1));

        __m128 const tmp6 = _mm_shuffle_ps(ra1, rc1, _MM_SHUFFLE(1, 0, 3, 0));
        __m128 const hb1 = _mm_permute_ps(tmp6, _MM_SHUFFLE(2, 1, 0, 3));
        __m128 const hc0 = _mm_permute_ps(mt.M.R[3], _MM_SHUFFLE(0, 3, 0, 3));

        __m128 const tmp7 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 2, 2, 2));
        __m128 const hc1 = _mm_permute_ps(tmp7, _MM_SHUFFLE(0, 2, 3, 0));
        __m128 const hd0 = _mm_permute_ps(mt.M.R[2], _MM_SHUFFLE(2, 0, 3, 1));

        __m128 const tmp8 = _mm_shuffle_ps(rb1, rc1, _MM_SHUFFLE(3, 2, 3, 0));
        __m128 const hd1 = _mm_permute_ps(tmp8, _MM_SHUFFLE(2, 1, 0, 3));

        __m128 const k0 = _mm_mul_ps(ha0, ha1);
        __m128 const k1 = _mm_mul_ps(hb0, hb1);
        __m128 const k2 = _mm_mul_ps(hc0, hc1);
        __m128 const k3 = _mm_mul_ps(hd0, hd1);

        __m128 const t1 = _mm_sub_ps(fa1, k0);
        __m128 const t0 = _mm_add_ps(fa1, k0);
        __m128 const t3 = _mm_add_ps(fb1, k1);
        __m128 const t2 = _mm_sub_ps(fb1, k1);
        __m128 const t5 = _mm_sub_ps(fc1, k2);
        __m128 const t4 = _mm_add_ps(fc1, k2);
        __m128 const t7 = _mm_add_ps(fd1, k3);
        __m128 const t6 = _mm_sub_ps(fd1, k3);

        __m128 const w0 = _mm_shuffle_ps(t0, t1, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const w2 = _mm_shuffle_ps(t2, t3, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const w4 = _mm_shuffle_ps(t4, t5, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const w6 = _mm_shuffle_ps(t6, t7, _MM_SHUFFLE(3, 1, 2, 0));

        __m128 const r0 = _mm_permute_ps(w0, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const r2 = _mm_permute_ps(w2, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const r4 = _mm_permute_ps(w4, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const r6 = _mm_permute_ps(w6, _MM_SHUFFLE(3, 1, 2, 0));

        // determinant
        __m128 const det = _mm_dp_ps(r0, mt.M.R[0], 0xFF);

        if (determinant != nullptr)
        {
            determinant->V = det;
        }

        __m128 const rcp_det = _mm_div_ps(Impl::c_V4_F32_One.V, det);

        Matrix result;
        result.M.R[0] = _mm_mul_ps(r0, rcp_det);
        result.M.R[1] = _mm_mul_ps(r2, rcp_det);
        result.M.R[2] = _mm_mul_ps(r4, rcp_det);
        result.M.R[3] = _mm_mul_ps(r6, rcp_det);
        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline Vector4 mathcall Determinant(T m) noexcept
        requires(Impl::IsMatrix<T>)
    {
        static Impl::ConstFloat32x4 const sign{ { { 1.0f,
            -1.0f,
            1.0f,
            -1.0f } } };

        Vector4 const r2_yxxx = Swizzle<1, 0, 0, 0>(Vector4{ m.M.R[2] });
        Vector4 const r3_zzyy = Swizzle<2, 2, 1, 1>(Vector4{ m.M.R[3] });
        Vector4 const r3_wwwz = Swizzle<3, 3, 3, 2>(Vector4{ m.M.R[3] });
        Vector4 const r2_zzyy = Swizzle<2, 2, 1, 1>(Vector4{ m.M.R[2] });

        Vector4 const pa0 = Multiply(r2_yxxx, r3_zzyy);
        Vector4 const pa1 = Multiply(r2_yxxx, r3_wwwz);
        Vector4 const pa2 = Multiply(r2_zzyy, r3_wwwz);

        Vector4 const r3_yxxx = Swizzle<1, 0, 0, 0>(Vector4{ m.M.R[3] });
        Vector4 const r2_wwwz = Swizzle<3, 3, 3, 2>(Vector4{ m.M.R[2] });

        Vector4 const pb0 = NegateMultiplyAdd(r2_zzyy, r3_yxxx, pa0);
        Vector4 const pb1 = NegateMultiplyAdd(r2_wwwz, r3_yxxx, pa1);
        Vector4 const pb2 = NegateMultiplyAdd(r2_wwwz, r3_zzyy, pa2);

        Vector4 const r1_wwwz = Swizzle<3, 3, 3, 2>(Vector4{ m.M.R[1] });
        Vector4 const r1_zzyy = Swizzle<2, 2, 1, 1>(Vector4{ m.M.R[1] });
        Vector4 const r1_yxxx = Swizzle<1, 0, 0, 0>(Vector4{ m.M.R[1] });

        Vector4 const s0 = Multiply(Vector4{ m.M.R[0] }, Vector4{ sign.V });
        Vector4 const t0 = Multiply(r1_wwwz, pb0);
        Vector4 const t1 = NegateMultiplyAdd(r1_zzyy, pb1, t0);
        Vector4 const t2 = MultiplyAdd(r1_yxxx, pb2, t1);

        return Dot(s0, t2);
    }

#if false
    [[nodiscard]] mathinline bool mathcall Decompopse(Vector4& out_scale, Quaternion& out_rotation, Vector4& out_translation, Matrix m) noexcept
    {
        constexpr float const DecomposeEpsilon = 0.0001f;

        constexpr Impl::NativeFloat32x4 const* canonical_basis[3]{
            &Impl::c_V4_F32_PositiveUnitX.V,
            &Impl::c_V4_F32_PositiveUnitY.V,
            &Impl::c_V4_F32_PositiveUnitZ.V,
        };

        out_translation.V = m.M.R[3];

        Matrix temp;
        temp.M.R[0] = m.M.R[0];
        temp.M.R[1] = m.M.R[1];
        temp.M.R[2] = m.M.R[2];
        temp.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        Impl::NativeFloat32x4* basis[3]{
            &temp.M.R[0],
            &temp.M.R[1],
            &temp.M.R[2],
        };

        float* scales = reinterpret_cast<float*>(&out_scale.V);
        GetX(&scales[0], Length(Vector3{ *basis[0] }));
        GetX(&scales[1], Length(Vector3{ *basis[1] }));
        GetX(&scales[2], Length(Vector3{ *basis[2] }));
        scales[3] = 0.0f;

        auto decompose_rank_abc = [](size_t& a, size_t& b, size_t& c, float x, float y, float z)
        {
            if (x < y)
            {
                if (y < z)
                {
                    a = 2;
                    b = 1;
                    c = 0;
                }
                else
                {
                    a = 1;

                    if (x < z)
                    {
                        b = 2;
                        c = 0;
                    }
                    else
                    {
                        b = 0;
                        c = 2;
                    }
                }
            }
            else
            {
                if (x < z)
                {
                    a = 2;
                    b = 0;
                    c = 1;
                }
                else
                {
                    a = 0;

                    if (y < z)
                    {
                        b = 2;
                        c = 1;
                    }
                    else
                    {
                        b = 1;
                        c = 2;
                    }
                }
            }
        };

        size_t a;
        size_t b;
        size_t c;

        decompose_rank_abc(a, b, c, scales[0], scales[1], scales[2]);

        if (scales[a] < DecomposeEpsilon)
        {
            (*basis[a]) = (*canonical_basis[a]);
        }

        (*basis[a]) = Normalize(Vector3{ *basis[a] }).V;

        if (scales[b] < DecomposeEpsilon)
        {
            float const absx = fabsf(GetX(Vector4{ *basis[a] }));
            float const absy = fabsf(GetY(Vector4{ *basis[a] }));
            float const absz = fabsf(GetZ(Vector4{ *basis[a] }));

            size_t const cc = [](float x, float y, float z) -> size_t
            {
                if (x < y)
                {
                    if ((y < z) || (x < z))
                    {
                        return 0;
                    }
                    else
                    {
                        return 2;
                    }
                }
                else
                {
                    if ((x < z) || (y < z))
                    {
                        return 1;
                    }
                    else
                    {
                        return 2;
                    }
                }
            }(absx, absy, absz);

            (*basis[b]) = Cross(Vector3{ *basis[a] }, Vector3{ *canonical_basis[cc] }).V;
        }

        (*basis[b]) = Normalize(Vector3{ *basis[b] }).V;

        if (scales[c] < DecomposeEpsilon)
        {
            (*basis[c]) = Cross(Vector3{ *basis[a] }, Vector3{ *basis[b] }).V;
        }

        (*basis[c]) = Normalize(Vector3{ *basis[c] }).V;

        float det = GetX(Determinant(temp));

        if (det < 0.0f)
        {
            scales[a] = -scales[a];
            (*basis[a]) = Negate(Vector4{ *basis[a] }).V;
            det = -det;
        }

        det -= 1.0f;
        det *= det;

        if (DecomposeEpsilon < det)
        {
            return false;
        }

        out_rotation = CreateFromMatrix(temp);
        return true;
    }
#endif
}


// Rotations

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateFromNormalAngle(Vector3 normal, float angle) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        float sin_angle;
        float cos_angle;

        SinCos(sin_angle, cos_angle, angle);

        Vector4 const a = Make<Vector4>(sin_angle, cos_angle, 1.0f - cos_angle, 0.0f);

        Vector4 const c0 = SplatX(a);
        Vector4 const c1 = SplatY(a);
        Vector4 const c2 = SplatZ(a);

        Vector4 const n0 = Swizzle<1, 2, 0, 3>(Vector4{ normal.V });
        Vector4 const n1 = Swizzle<2, 0, 1, 3>(Vector4{ normal.V });

        Vector4 const g0 = Multiply(c2, n0);
        Vector4 const g1 = Multiply(g0, n1);

        Vector4 const h0 = Multiply(c2, Vector4{ normal.V });
        Vector4 const h1 = MultiplyAdd(h0, Vector4{ normal.V }, c1);

        Vector4 const i0 = MultiplyAdd(c0, Vector4{ normal.V }, g1);
        Vector4 const i1 = NegateMultiplyAdd(c0, Vector4{ normal.V }, g1);

        Vector4 const r0 = Select(a, h1, Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Vector4 const r1 = Permute<2, 5, 6, 0>(i0, i1);
        Vector4 const r2 = Permute<1, 4, 1, 4>(i0, i1);

        Matrix result;
        result.M.R[0] = Permute<0, 4, 5, 3>(r0, r1).V;
        result.M.R[1] = Permute<6, 1, 7, 3>(r0, r1).V;
        result.M.R[2] = Permute<4, 5, 2, 3>(r0, r2).V;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;
        return result;
#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;

        SinCos(sin_angle, cos_angle, angle);

        __m128 const c0 = _mm_set_ps1(sin_angle);
        __m128 const c1 = _mm_set_ps1(cos_angle);
        __m128 const c2 = _mm_set_ps1(1.0f - cos_angle);

        __m128 const n0 = _mm_permute_ps(normal.V, _MM_SHUFFLE(3, 0, 2, 1));
        __m128 const n1 = _mm_permute_ps(normal.V, _MM_SHUFFLE(3, 1, 0, 2));

        __m128 const g0 = _mm_mul_ps(c2, n0);
        __m128 const g1 = _mm_mul_ps(g0, n1);

        __m128 const h0 = _mm_mul_ps(c2, normal.V);

        __m128 const i0 = Impl::avx_fmadd_f32x4(h0, normal.V, c1);
        __m128 const i1 = Impl::avx_fmadd_f32x4(c0, normal.V, g1);
        __m128 const i2 = Impl::avx_fnmadd_f32x4(c0, normal.V, g1);

        __m128 const r0 = _mm_and_ps(i0, Impl::c_V4_U32_Mask_1110.V);

        __m128 const t0 = _mm_shuffle_ps(i1, i2, _MM_SHUFFLE(2, 1, 2, 0));
        __m128 const r1 = _mm_permute_ps(t0, _MM_SHUFFLE(0, 3, 2, 1));

        __m128 const t1 = _mm_shuffle_ps(i1, i2, _MM_SHUFFLE(0, 0, 1, 1));
        __m128 const r2 = _mm_permute_ps(t1, _MM_SHUFFLE(2, 0, 2, 0));

        __m128 const t2 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(1, 0, 3, 0));
        __m128 const r3 = _mm_permute_ps(t2, _MM_SHUFFLE(1, 3, 2, 0));

        Matrix result;
        result.M.R[0] = r3;

        __m128 const t3 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 2, 3, 1));
        __m128 const r4 = _mm_permute_ps(t3, _MM_SHUFFLE(1, 3, 0, 2));

        result.M.R[1] = r4;

        __m128 const r5 = _mm_shuffle_ps(r2, r0, _MM_SHUFFLE(3, 2, 1, 0));
        result.M.R[2] = r5;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateFromAxisAngle(Vector3 axis, float angle) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(!IsEqual(axis, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(axis));

        Vector3 const normal = Normalize(axis);
        return CreateFromNormalAngle<Matrix>(normal, angle);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateFromQuaternion(Quaternion q) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 const q_xyzw{ q.V };

        Vector4 const q0 = Add(q_xyzw, q_xyzw);
        Vector4 const q1 = Multiply(q_xyzw, q0);

        Vector4 const q1_yxx_1 = Permute<1, 0, 0, 7>(q1, Vector4{ Impl::c_V3_F32_One.V });
        Vector4 const q1_zzy_1 = Permute<2, 2, 1, 7>(q1, Vector4{ Impl::c_V3_F32_One.V });
        Vector4 const o0 = Subtract(Vector4{ Impl::c_V3_F32_One.V }, q1_yxx_1);
        Vector4 const s0 = Subtract(o0, q1_zzy_1);

        Vector4 const q_xxyw = Swizzle<0, 0, 1, 3>(q_xyzw);
        Vector4 const q0_zyzw = Swizzle<2, 1, 2, 3>(q0);
        Vector4 const m0 = Multiply(q_xxyw, q0_zyzw);

        Vector4 const q_wwww = SplatW(q_xyzw);
        Vector4 const q0_yzxw = Swizzle<1, 2, 0, 3>(q0);
        Vector4 const m1 = Multiply(q_wwww, q0_yzxw);

        Vector4 const r0 = Add(m0, m1);
        Vector4 const r1 = Subtract(m0, m1);

        Vector4 const r2 = Permute<1, 4, 5, 2>(r0, r1);
        Vector4 const r3 = Permute<0, 6, 0, 6>(r0, r1);

        Matrix result;
        result.M.R[0] = Permute<0, 4, 5, 3>(s0, r2).V;
        result.M.R[1] = Permute<6, 1, 7, 3>(s0, r2).V;
        result.M.R[2] = Permute<4, 5, 2, 3>(s0, r3).V;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;
        return result;

#elif GRAPHYTE_HW_AVX
        static Impl::ConstFloat32x4 const Constant1110 = { { { 1.0f, 1.0f, 1.0f, 0.0f } } };

        __m128 Q0 = _mm_add_ps(q.V, q.V);
        __m128 Q1 = _mm_mul_ps(q.V, Q0);

        __m128 V0 = _mm_permute_ps(Q1, _MM_SHUFFLE(3, 0, 0, 1));
        V0 = _mm_and_ps(V0, Impl::c_V4_U32_Mask_1110.V);
        __m128 V1 = _mm_permute_ps(Q1, _MM_SHUFFLE(3, 1, 2, 2));
        V1 = _mm_and_ps(V1, Impl::c_V4_U32_Mask_1110.V);
        __m128 R0 = _mm_sub_ps(Constant1110.V, V0);
        R0 = _mm_sub_ps(R0, V1);

        V0 = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 1, 0, 0));
        V1 = _mm_permute_ps(Q0, _MM_SHUFFLE(3, 2, 1, 2));
        V0 = _mm_mul_ps(V0, V1);

        V1 = _mm_permute_ps(q.V, _MM_SHUFFLE(3, 3, 3, 3));
        __m128 V2 = _mm_permute_ps(Q0, _MM_SHUFFLE(3, 0, 2, 1));
        V1 = _mm_mul_ps(V1, V2);

        __m128 R1 = _mm_add_ps(V0, V1);
        __m128 R2 = _mm_sub_ps(V0, V1);

        V0 = _mm_shuffle_ps(R1, R2, _MM_SHUFFLE(1, 0, 2, 1));
        V0 = _mm_permute_ps(V0, _MM_SHUFFLE(1, 3, 2, 0));
        V1 = _mm_shuffle_ps(R1, R2, _MM_SHUFFLE(2, 2, 0, 0));
        V1 = _mm_permute_ps(V1, _MM_SHUFFLE(2, 0, 2, 0));

        Q1 = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(1, 0, 3, 0));
        Q1 = _mm_permute_ps(Q1, _MM_SHUFFLE(1, 3, 2, 0));

        Matrix m;
        m.M.R[0] = Q1;

        Q1 = _mm_shuffle_ps(R0, V0, _MM_SHUFFLE(3, 2, 3, 1));
        Q1 = _mm_permute_ps(Q1, _MM_SHUFFLE(1, 3, 0, 2));
        m.M.R[1] = Q1;

        Q1 = _mm_shuffle_ps(V1, R0, _MM_SHUFFLE(3, 2, 1, 0));
        m.M.R[2] = Q1;
        m.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;
        return m;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateFromEuler(Vector3 angles) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Quaternion const q = CreateFromEuler<Quaternion>(angles);
        return CreateFromQuaternion<T>(q);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateFromEuler(float x, float y, float z) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const v = Make<Vector3>(x, y, z);
        return CreateFromEuler<Matrix>(v);
    }
}


// Transforms

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateTranslation(float x, float y, float z) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = 1.0F;
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = 1.0F;
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = 1.0F;
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = x;
        result.M.M[3][1] = y;
        result.M.M[3][2] = z;
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;
        result.M.R[0] = Impl::c_V4_F32_PositiveUnitX.V;
        result.M.R[1] = Impl::c_V4_F32_PositiveUnitY.V;
        result.M.R[2] = Impl::c_V4_F32_PositiveUnitZ.V;
        result.M.R[3] = _mm_set_ps(1.0F, z, y, x);

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateTranslation(Vector3 translation) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = 1.0F;
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = 1.0F;
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = 1.0F;
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = translation.V.F[0];
        result.M.M[3][1] = translation.V.F[1];
        result.M.M[3][2] = translation.V.F[2];
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON

        Matrix result;
        result.M.R[0] = Impl::c_V4_F32_PositiveUnitX.V;
        result.M.R[1] = Impl::c_V4_F32_PositiveUnitY.V;
        result.M.R[2] = Impl::c_V4_F32_PositiveUnitZ.V;
        result.M.R[3] = Select(
            Vector4{ Impl::c_V4_F32_PositiveUnitW.V },
            Vector4{ translation.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V })
            .V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateScaling(float x, float y, float z) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = x;
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = y;
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = z;
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = 0.0F;
        result.M.M[3][1] = 0.0F;
        result.M.M[3][2] = 0.0F;
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;
        result.M.R[0] = _mm_set_ps(0.0F, 0.0F, 0.0F, x);
        result.M.R[1] = _mm_set_ps(0.0F, 0.0F, y, 0.0F);
        result.M.R[2] = _mm_set_ps(0.0F, z, 0.0F, 0.0F);
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateScaling(Vector3 scale) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix result;

        result.M.M[0][0] = scale.V.F[0];
        result.M.M[0][1] = 0.0F;
        result.M.M[0][2] = 0.0F;
        result.M.M[0][3] = 0.0F;

        result.M.M[1][0] = 0.0F;
        result.M.M[1][1] = scale.V.F[1];
        result.M.M[1][2] = 0.0F;
        result.M.M[1][3] = 0.0F;

        result.M.M[2][0] = 0.0F;
        result.M.M[2][1] = 0.0F;
        result.M.M[2][2] = scale.V.F[2];
        result.M.M[2][3] = 0.0F;

        result.M.M[3][0] = 0.0F;
        result.M.M[3][1] = 0.0F;
        result.M.M[3][2] = 0.0F;
        result.M.M[3][3] = 1.0F;

        return result;

#elif GRAPHYTE_HW_AVX

        Matrix result;
        result.M.R[0] = _mm_and_ps(scale.V, Impl::c_V4_U32_Mask_1000.V);
        result.M.R[1] = _mm_and_ps(scale.V, Impl::c_V4_U32_Mask_0100.V);
        result.M.R[2] = _mm_and_ps(scale.V, Impl::c_V4_U32_Mask_0010.V);
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateRotationX(float angle) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        Matrix result;
        result.M.M[0][0] = 1.0f;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = cos_angle;
        result.M.M[1][2] = sin_angle;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = -sin_angle;
        result.M.M[2][2] = cos_angle;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        __m128 const ssin = _mm_set_ss(sin_angle);
        __m128 const scos = _mm_set_ss(cos_angle);

        __m128 const vcos = _mm_shuffle_ps(scos, ssin, _MM_SHUFFLE(3, 0, 0, 3));

        Matrix result;
        result.M.R[0] = Impl::c_V4_F32_PositiveUnitX.V;
        result.M.R[1] = vcos;

        __m128 const temp = _mm_permute_ps(vcos, _MM_SHUFFLE(3, 1, 2, 0));
        __m128 const vsin = _mm_mul_ps(temp, Impl::c_V4_F32_Negate_Y.V);

        result.M.R[2] = vsin;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateRotationY(float angle) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        Matrix result;
        result.M.M[0][0] = cos_angle;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = -sin_angle;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = 1.0f;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = sin_angle;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = cos_angle;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        __m128 const ssin = _mm_set_ss(sin_angle);
        __m128 const scos = _mm_set_ss(cos_angle);

        __m128 const vsin = _mm_shuffle_ps(ssin, scos, _MM_SHUFFLE(3, 0, 3, 0));

        Matrix result;
        result.M.R[2] = vsin;
        result.M.R[1] = Impl::c_V4_F32_PositiveUnitY.V;

        __m128 const temp = _mm_permute_ps(vsin, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const vcos = _mm_mul_ps(temp, Impl::c_V4_F32_Negate_Z.V);

        result.M.R[0] = vcos;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateRotationZ(float angle) noexcept
        requires(Impl::IsMatrix<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        Matrix result;
        result.M.M[0][0] = cos_angle;
        result.M.M[0][1] = sin_angle;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = -sin_angle;
        result.M.M[1][1] = cos_angle;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = 1.0f;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = 0.0f;
        result.M.M[3][3] = 1.0f;

        return result;

#elif GRAPHYTE_HW_AVX
        float sin_angle;
        float cos_angle;
        SinCos(sin_angle, cos_angle, angle);

        __m128 const ssin = _mm_set_ss(sin_angle);
        __m128 const scos = _mm_set_ss(cos_angle);

        __m128 const vcos = _mm_unpacklo_ps(scos, ssin);

        Matrix result;
        result.M.R[0] = vcos;

        __m128 const temp = _mm_permute_ps(vcos, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const vsin = _mm_mul_ps(temp, Impl::c_V4_F32_Negate_X.V);

        result.M.R[1] = vsin;
        result.M.R[2] = Impl::c_V4_F32_PositiveUnitZ.V;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return result;
#endif
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateTransform2D(
        Vector2 scaling_origin,
        float scaling_orientation,
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const v_scaling_origin{ Select(
            Vector4{ Impl::c_V4_U32_Mask_1100.V },
            Vector4{ scaling_origin.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V })
                                            .V };

        // Create scanling origin transform
        Vector3 const v_scaling_origin_negated = Negate(v_scaling_origin);
        Matrix const m_scaling_origin = CreateTranslation<Matrix>(v_scaling_origin_negated);

        // Create scaling orientation transform
        Matrix const m_scaling_orientation = CreateRotationZ<Matrix>(scaling_orientation);
        Matrix const m_scaling_orientation_trn = Transpose(m_scaling_orientation);

        // Create scaling transform
        Vector3 const v_scaling_xy1{ Select(
            Vector4{ Impl::c_V4_F32_One.V },
            Vector4{ scaling.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V })
                                         .V };

        Matrix const m_scaling = CreateScaling<Matrix>(v_scaling_xy1);

        // Create rotation origin
        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::c_V4_U32_Mask_1100.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V });

        // Create rotation transform
        Matrix const m_rotation = CreateRotationZ<Matrix>(rotation);

        // Create translation vector
        Vector4 const v_translation = Select(
            Vector4{ Impl::c_V4_U32_Mask_1100.V },
            Vector4{ translation.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V });

        Matrix const m0 = Multiply(m_scaling_origin, m_scaling_orientation_trn);
        Matrix const m1 = Multiply(m0, m_scaling);

        Matrix m2 = Multiply(m1, m_scaling_orientation);
        m2.M.R[3] = Add(Vector4{ m2.M.R[3] }, Vector4{ v_scaling_origin.V }).V;
        m2.M.R[3] = Subtract(Vector4{ m2.M.R[3] }, v_rotation_origin).V;

        Matrix m3 = Multiply(m2, m_rotation);
        m3.M.R[3] = Add(Vector4{ m3.M.R[3] }, v_rotation_origin).V;
        m3.M.R[3] = Add(Vector4{ m3.M.R[3] }, v_translation).V;

        return m3;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateAffineTransform2D(
        Vector2 scaling,
        Vector2 rotation_origin,
        float rotation,
        Vector2 translation) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const v_scaling{ Select(
            Vector4{ Impl::c_V4_F32_One.V },
            Vector4{ scaling.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V })
                                     .V };

        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::c_V4_U32_Mask_1100.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V });

        Vector4 const v_translation = Select(
            Vector4{ Impl::c_V4_U32_Mask_1100.V },
            Vector4{ translation.V },
            Bool4{ Impl::c_V4_U32_Mask_1100.V });

        Matrix const m_rotation = CreateRotationZ<Matrix>(rotation);

        Matrix result = CreateScaling<Matrix>(v_scaling);
        result.M.R[3] = Subtract(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result = Multiply(result, m_rotation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_translation).V;

        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateTransform(
        Vector3 scaling_origin,
        Quaternion scaling_orientation,
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const v_scaling_origin{ Select(
            Vector4{ Impl::c_V4_U32_Mask_1110.V },
            Vector4{ scaling_origin.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V }).V };

        Vector3 const v_scaling_origin_negated = Negate(v_scaling_origin);

        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::c_V4_U32_Mask_1110.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Vector4 const v_translation = Select(
            Vector4{ Impl::c_V4_U32_Mask_1110.V },
            Vector4{ translation.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Matrix const m_scaling_origin = CreateTranslation<Matrix>(v_scaling_origin_negated);
        Matrix const m_scaling_orientation = CreateFromQuaternion<Matrix>(scaling_orientation);
        Matrix const m_scaling_orientation_trn = Transpose(m_scaling_orientation);
        Matrix const m_scaling = CreateScaling<Matrix>(scaling);
        Matrix const m_rotation = CreateFromQuaternion<Matrix>(rotation);

        Matrix result = Multiply(m_scaling_origin, m_scaling_orientation_trn);
        result = Multiply(result, m_scaling);
        result = Multiply(result, m_scaling_orientation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, Vector4{ v_scaling_origin.V }).V;
        result.M.R[3] = Subtract(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result = Multiply(result, m_rotation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_translation).V;

        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall CreateAffineTransform(
        Vector3 scaling,
        Vector3 rotation_origin,
        Quaternion rotation,
        Vector3 translation) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector4 const v_rotation_origin = Select(
            Vector4{ Impl::c_V4_U32_Mask_1110.V },
            Vector4{ rotation_origin.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Vector4 const v_translation = Select(
            Vector4{ Impl::c_V4_U32_Mask_1110.V },
            Vector4{ translation.V },
            Bool4{ Impl::c_V4_U32_Mask_1110.V });

        Matrix const m_rotation = CreateFromQuaternion<Matrix>(rotation);

        Matrix result = CreateScaling<Matrix>(scaling);
        result.M.R[3] = Subtract(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result = Multiply(result, m_rotation);
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_rotation_origin).V;
        result.M.R[3] = Add(Vector4{ result.M.R[3] }, v_translation).V;

        return result;
    }
}


// View matrices

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall LookToLH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(!IsEqual(eye_direction, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(eye_direction));
        GX_ASSERT(!IsEqual(up_direction, Zero<Vector3>()));
        GX_ASSERT(!IsInfinity(up_direction));

        Vector3 const r2 = Normalize(eye_direction);

        Vector3 const t0 = Cross(up_direction, r2);
        Vector3 const r0 = Normalize(t0);

        Vector3 const r1 = Cross(r2, r0);

        Vector3 const neg_eye_position = Negate(eye_position);

        Vector4 const d0 = Dot(r0, neg_eye_position);
        Vector4 const d1 = Dot(r1, neg_eye_position);
        Vector4 const d2 = Dot(r2, neg_eye_position);

        Matrix result;
        result.M.R[0] = Select(d0, Vector4{ r0.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V }).V;
        result.M.R[1] = Select(d1, Vector4{ r1.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V }).V;
        result.M.R[2] = Select(d2, Vector4{ r2.V }, Bool4{ Impl::c_V4_U32_Mask_1110.V }).V;
        result.M.R[3] = Impl::c_V4_F32_PositiveUnitW.V;

        return Transpose(result);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall LookToRH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const neg_eye_direction = Negate(eye_direction);
        return LookToLH<Matrix>(eye_position, neg_eye_direction, up_direction);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall LookAtLH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const eye_direction = Subtract(eye_position, focus_position);
        return LookToLH<Matrix>(eye_position, eye_direction, up_direction);
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall LookAtRH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
        requires(Impl::IsMatrix<T>)
    {
        Vector3 const eye_direction = Subtract(eye_position, focus_position);
        return LookToRH<Matrix>(eye_position, eye_direction, up_direction);
    }
}


// Projection matrices

namespace Graphyte::Maths
{
    template <typename T>
    [[nodiscard]] mathinline T mathcall PerspectiveLH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.000001f));

        float const z_near_2 = z_near + z_near;
        float const range = z_far / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(z_near_2 / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::c_V4_F32_PositiveUnitW.V, 2);
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 / view_width,
            z_near_2 / view_height,
            range,
            -range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);

        // [range, -range * z_near, 0, 1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::c_V4_F32_PositiveUnitW.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, 1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, -range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall PerspectiveRH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.000001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.000001f));

        float const z_near_2 = z_near + z_near;
        float const range = z_far / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = -1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(z_near_2 / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::c_V4_F32_NegativeUnitW.V, 2);
        result.M.R[3] = vsetq_lane_f32(range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 / view_width,
            z_near_2 / view_height,
            range,
            range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);

        // [range, range * z_near, 0, -1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::c_V4_F32_NegativeUnitW.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, 1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall PerspectiveFovLH(
        float fov_angle_y,
        float aspect_ratio,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(fov_angle_y, 0.0f, 0.00001f * 2.0f));
        GX_ASSERT(!IsEqual(aspect_ratio, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float fov_sin;
        float fov_cos;
        SinCos(fov_sin, fov_cos, 0.5f * fov_angle_y);

        float const height = fov_cos / fov_sin;
        float const width = height / aspect_ratio;
        float const range = z_far / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::c_V4_F32_PositiveUnitW.V, 2);
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            width,
            height,
            range,
            -range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);

        // [range, -range * z_near, 0, 1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::c_V4_F32_PositiveUnitW.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, 1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, -range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall PerspectiveFovRH(
        float fov_angle_y,
        float aspect_ratio,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(fov_angle_y, 0.0f, 0.00001f * 2.0f));
        GX_ASSERT(!IsEqual(aspect_ratio, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float fov_sin;
        float fov_cos;
        SinCos(fov_sin, fov_cos, 0.5f * fov_angle_y);

        float const height = fov_cos / fov_sin;
        float const width = height / aspect_ratio;
        float const range = z_far / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = -1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, Impl::c_V4_F32_NegativeUnitW.V, 2);
        result.M.R[3] = vsetq_lane_f32(range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            width,
            height,
            range,
            range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [x, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, y, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);

        // [range, range * z_near, 0, -1]
        __m128 const values2 = _mm_shuffle_ps(values, Impl::c_V4_F32_NegativeUnitW.V, _MM_SHUFFLE(3, 2, 3, 2));

        // [0, 0, range, -1]
        __m128 const r2_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 0, 0, 0));

        // [0, 0, range * z_near, 0]
        __m128 const r3_y = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_y;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall PerspectiveOffsetLH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far)
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.0001f));

        float const z_near_2 = z_near + z_near;
        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = z_far / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 * rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 * rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = -(view_left + view_right) * rcp_width;
        result.M.M[2][1] = -(view_top + view_bottom) * rcp_height;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(z_near_2 * rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 * rcp_height, zero, 1);
        result.M.R[2] = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range,
            1.0f)
            .V;
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 * rcp_width,
            z_near_2 * rcp_height,
            -range * z_near,
            0.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [z_near_2 * rcp_width, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, z_near_2 * rcp_height, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);

        __m128 const r2_zw = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range,
            1.0f)
            .V;

        // [0, 0, -range * z_near, 0]
        __m128 const r3_z = _mm_and_ps(values, Impl::c_V4_U32_Mask_0010.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_z;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall PerspectiveOffsetRH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far)
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(z_near > 0.0f && z_far > 0.0f);
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.0001f));

        float const z_near_2 = z_near + z_near;
        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = z_far / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = z_near_2 * rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = z_near_2 * rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = (view_left + view_right) * rcp_width;
        result.M.M[2][1] = (view_top + view_bottom) * rcp_height;
        result.M.M[2][2] = range;
        result.M.M[2][3] = -1.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 0.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(z_near_2 * rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(z_near_2 * rcp_height, zero, 1);
        result.M.R[2] = Make<Vector4>(
            (view_left + view_right) * rcp_width,
            (view_top + view_bottom) * rcp_height,
            range,
            -1.0f)
            .V;
        result.M.R[3] = vsetq_lane_f32(-range * z_near, zero, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            z_near_2 * rcp_width,
            z_near_2 * rcp_height,
            range * z_near,
            0.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        // [z_near_2 * rcp_width, 0, 0, 0]
        __m128 const r0_x = _mm_move_ss(zero, values);

        // [0, z_near_2 * rcp_height, 0, 0]
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);

        __m128 const r2_zw = Make<Vector4>(
            (view_left + view_right) * rcp_width,
            (view_top + view_bottom) * rcp_height,
            range,
            -1.0f)
            .V;

        // [0, 0, range * z_near, 0]
        __m128 const r3_z = _mm_and_ps(values, Impl::c_V4_U32_Mask_0010.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_zw;
        result.M.R[3] = r3_z;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall OrthographicLH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const range = 1.0f / (z_far - z_near);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = 2.0f / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = 2.0f / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(2.0f / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(2.0f / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = vsetq_lane_f32(-range * z_near, Impl::c_V4_F32_PositiveUnitW.V, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            2.0f / view_width,
            2.0f / view_height,
            range,
            -range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        __m128 const r0_x = _mm_move_ss(zero, values);
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);
        __m128 const values2 = _mm_shuffle_ps(values, Impl::c_V4_F32_PositiveUnitW.V, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const r2_z = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 0, 0, 0));
        __m128 const r3_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_zw;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall OrthographicRH(
        float view_width,
        float view_height,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(!IsEqual(view_width, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(view_height, 0.0f, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const range = 1.0f / (z_near - z_far);

        Matrix result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = 2.0f / view_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = 2.0f / view_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = 0.0f;
        result.M.M[3][1] = 0.0f;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(2.0f / view_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(2.0f / view_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = vsetq_lane_f32(range * z_near, Impl::c_V4_F32_PositiveUnitW.V, 2);
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            2.0f / view_width,
            2.0f / view_height,
            range,
            range * z_near,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        __m128 const r0_x = _mm_move_ss(zero, values);
        __m128 const r1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);
        __m128 const values2 = _mm_shuffle_ps(values, Impl::c_V4_F32_PositiveUnitW.V, _MM_SHUFFLE(3, 2, 3, 2));
        __m128 const r2_z = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(2, 0, 0, 0));
        __m128 const r3_zw = _mm_shuffle_ps(zero, values2, _MM_SHUFFLE(3, 1, 0, 0));

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_zw;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall OrthographicOffsetLH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = 1.0f / (z_far - z_near);

        Matrix result;

#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = rcp_width + rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = rcp_height + rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = -(view_left + view_right) * rcp_width;
        result.M.M[3][1] = -(view_top + view_bottom) * rcp_height;
        result.M.M[3][2] = -range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(rcp_width + rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(rcp_height + rcp_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            -range * z_near,
            1.0f)
            .V;
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            rcp_width,
            rcp_height,
            range,
            1.0f,
        } } };
        Impl::ConstFloat32x4 const mvalues2{ { {
            -(view_left + view_right),
            -(view_top + view_bottom),
            -z_near,
            1.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        __m128 const t0_x = _mm_move_ss(zero, values);
        __m128 const r0_x = _mm_add_ss(t0_x, t0_x);

        __m128 const t1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);
        __m128 const r1_y = _mm_add_ps(t1_y, t1_y);

        __m128 const r2_z = _mm_and_ps(values, Impl::c_V4_U32_Mask_0010.V);

        __m128 const r3_xyzw = _mm_mul_ps(values, mvalues2.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_xyzw;
#endif
        return result;
    }

    template <typename T>
    [[nodiscard]] mathinline T mathcall OrthographicOffsetRH(
        float view_left,
        float view_right,
        float view_bottom,
        float view_top,
        float z_near,
        float z_far) noexcept
        requires(Impl::IsMatrix<T>)
    {
        GX_ASSERT(!IsEqual(view_right, view_left, 0.00001f));
        GX_ASSERT(!IsEqual(view_top, view_bottom, 0.00001f));
        GX_ASSERT(!IsEqual(z_far, z_near, 0.00001f));

        float const rcp_width = 1.0f / (view_right - view_left);
        float const rcp_height = 1.0f / (view_top - view_bottom);
        float const range = 1.0f / (z_near - z_far);

        Matrix result;

#if GRAPHYTE_MATH_NO_INTRINSICS
        result.M.M[0][0] = rcp_width + rcp_width;
        result.M.M[0][1] = 0.0f;
        result.M.M[0][2] = 0.0f;
        result.M.M[0][3] = 0.0f;

        result.M.M[1][0] = 0.0f;
        result.M.M[1][1] = rcp_height + rcp_height;
        result.M.M[1][2] = 0.0f;
        result.M.M[1][3] = 0.0f;

        result.M.M[2][0] = 0.0f;
        result.M.M[2][1] = 0.0f;
        result.M.M[2][2] = range;
        result.M.M[2][3] = 0.0f;

        result.M.M[3][0] = -(view_left + view_right) * rcp_width;
        result.M.M[3][1] = -(view_top + view_bottom) * rcp_height;
        result.M.M[3][2] = range * z_near;
        result.M.M[3][3] = 1.0f;
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero = vdupq_n_f32(0.0f);
        result.M.R[0] = vsetq_lane_f32(rcp_width + rcp_width, zero, 0);
        result.M.R[1] = vsetq_lane_f32(rcp_height + rcp_height, zero, 1);
        result.M.R[2] = vsetq_lane_f32(range, zero, 2);
        result.M.R[3] = Make<Vector4>(
            -(view_left + view_right) * rcp_width,
            -(view_top + view_bottom) * rcp_height,
            range * z_near,
            1.0f)
            .V;
#elif GRAPHYTE_HW_AVX
        Impl::ConstFloat32x4 const mvalues{ { {
            rcp_width,
            rcp_height,
            range,
            1.0f,
        } } };
        Impl::ConstFloat32x4 const mvalues2{ { {
            -(view_left + view_right),
            -(view_top + view_bottom),
            z_near,
            1.0f,
        } } };

        __m128 const values = mvalues.V;
        __m128 const zero = _mm_setzero_ps();

        __m128 const t0_x = _mm_move_ss(zero, values);
        __m128 const r0_x = _mm_add_ss(t0_x, t0_x);

        __m128 const t1_y = _mm_and_ps(values, Impl::c_V4_U32_Mask_0100.V);
        __m128 const r1_y = _mm_add_ps(t1_y, t1_y);

        __m128 const r2_z = _mm_and_ps(values, Impl::c_V4_U32_Mask_0010.V);

        __m128 const r3_xyzw = _mm_mul_ps(values, mvalues2.V);

        result.M.R[0] = r0_x;
        result.M.R[1] = r1_y;
        result.M.R[2] = r2_z;
        result.M.R[3] = r3_xyzw;
#endif
        return result;
    }
}


// =================================================================================================
//
// Vector projection on viewport
//

namespace Graphyte::Maths
{
    // TODO: make Viewport struct instead of this
    [[nodiscard]] mathinline Vector3 mathcall Project(
        Vector3 v,
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float viewport_min_z,
        float viewport_max_z,
        Matrix projection,
        Matrix view,
        Matrix world) noexcept
    {
        float const half_width = viewport_width * 0.5F;
        float const half_height = viewport_height * 0.5F;

        Vector3 const scale = Make<Vector3>(
            half_width,
            -half_height,
            viewport_max_z - viewport_min_z);

        Vector3 const offset = Make<Vector3>(
            viewport_x + half_width,
            viewport_y + half_height,
            viewport_min_z);

        Matrix const wv = Multiply(world, view);
        Matrix const wvp = Multiply(wv, projection);

        Vector3 const tv = TransformCoord(v, wvp);
        Vector3 const result = MultiplyAdd(tv, scale, offset);
        return result;
    }

    [[nodiscard]] mathinline Vector3 mathcall Unproject(
        Vector3 v,
        float viewport_x,
        float viewport_y,
        float viewport_width,
        float viewport_height,
        float viewport_min_z,
        float viewport_max_z,
        Matrix projection,
        Matrix view,
        Matrix world) noexcept
    {
        static Impl::ConstFloat32x4 const d{ { {
            -1.0F,
            1.0F,
            0.0F,
            0.0F,
        } } };

        Vector3 const scale = Make<Vector3>(
            viewport_width * 0.5F,
            -viewport_height * 0.5F,
            viewport_max_z - viewport_min_z);

        Vector3 const rcp_scale = Reciprocal(scale);

        Vector3 const offset = Make<Vector3>(
            -viewport_x,
            -viewport_y,
            -viewport_min_z);

        Vector3 const projected = MultiplyAdd(rcp_scale, offset, Vector3{ d.V });

        Matrix const mv = Multiply(world, view);
        Matrix const mvp = Multiply(mv, projection);
        Matrix const inv_mvp = Inverse(mvp);

        Vector3 const coord = MultiplyAdd(v, rcp_scale, projected);
        Vector3 const result = TransformCoord(coord, inv_mvp);
        return result;
    }
}
