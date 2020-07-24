#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Constants.hxx>
#include <GxBase/Maths/Arithmetic.hxx>
#include <GxBase/Maths/Comparizon.hxx>


// =================================================================================================
//
// Select/control
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SelectControl(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        GX_ASSERT(x < 2);
        GX_ASSERT(y < 2);
        GX_ASSERT(z < 2);
        GX_ASSERT(w < 2);

        uint32_t const control[2]{ Impl::SELECT_0, Impl::SELECT_1 };

        Impl::ConstUInt32x4 const result{ { {
            control[x],
            control[y],
            control[z],
            control[w],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const xyzw = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
            static_cast<int>(y),
            static_cast<int>(x));
        __m128i const zero    = _mm_setzero_si128();
        __m128i const control = _mm_cmpgt_epi32(xyzw, zero);
        __m128 const result   = _mm_castsi128_ps(control);
        return { result };
#elif GRAPHYTE_HW_NEON
        int32x2_t const xy     = vcreate_s32(static_cast<uint64_t>(x) | static_cast<uint64_t>(y) << 32);
        int32x2_t const zw     = vcreate_s32(static_cast<uint64_t>(z) | static_cast<uint64_t>(w) << 32);
        int32x4_t const xyzw   = vcombine_s32(xy, zw);
        int32x4_t const zero   = vdupq_n_s32(0);
        int32x4_t const result = vcgtq_s32(xyzw, zero);
        return { vreinterpretq_f32_s32(result) };
#endif
    }

    template <typename T>
    mathinline T mathcall Select(T a, T b, typename T::MaskType control) noexcept
        requires(T::Components >= 1 && T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            (a.V.U[0] & ~control.V.U[0]) | (b.V.U[0] & control.V.U[0]),
            (a.V.U[1] & ~control.V.U[1]) | (b.V.U[1] & control.V.U[1]),
            (a.V.U[2] & ~control.V.U[2]) | (b.V.U[2] & control.V.U[2]),
            (a.V.U[3] & ~control.V.U[3]) | (b.V.U[3] & control.V.U[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_blendv_ps(a.V, b.V, control.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vbslq_f32(
            vreinterpretq_u32_f32(control.V),
            b.V,
            a.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Select(T a, T b, T control) noexcept
        requires(std::floating_point<T>)
    {
        return (control >= 0) ? a : b;
    }
}


// =================================================================================================
//
// Permutations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Permute(T a, T b, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(x < 8);
        GX_ASSERT(y < 8);
        GX_ASSERT(z < 8);
        GX_ASSERT(w < 8);

#if GRAPHYTE_MATH_NO_INTRINSICS
        uint32_t const* vptrs[2]{
            reinterpret_cast<uint32_t const*>(&a.V),
            reinterpret_cast<uint32_t const*>(&b.V),
        };

        uint32_t const ix = (x & 3);
        uint32_t const iy = (y & 3);
        uint32_t const iz = (z & 3);
        uint32_t const iw = (w & 3);

        uint32_t const vx = (x >> 2);
        uint32_t const vy = (y >> 2);
        uint32_t const vz = (z >> 2);
        uint32_t const vw = (w >> 2);

        uint32_t const rx = vptrs[vx][ix];
        uint32_t const ry = vptrs[vy][iy];
        uint32_t const rz = vptrs[vz][iz];
        uint32_t const rw = vptrs[vw][iw];

        Impl::ConstUInt32x4 const result{ { {
            rx,
            ry,
            rz,
            rw,
        } } };


        return { result.V };
#elif GRAPHYTE_HW_AVX
        static Impl::ConstUInt32x4 const threes{ { {
            3,
            3,
            3,
            3,
        } } };

        alignas(__m128) uint32_t elements[4]{ x, y, z, w };

        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&elements[0]));

        __m128i const select      = _mm_cmpgt_epi32(control, _mm_castps_si128(threes.V));
        __m128i const permutation = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(control), threes.V));


        __m128 const shuffle1 = _mm_permutevar_ps(a.V, permutation);
        __m128 const shuffle2 = _mm_permutevar_ps(b.V, permutation);

        __m128 const masked1 = _mm_andnot_ps(_mm_castsi128_ps(select), shuffle1);
        __m128 const masked2 = _mm_and_ps(_mm_castsi128_ps(select), shuffle2);

        __m128 const result = _mm_or_ps(masked1, masked2);

        return { result };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_permute(a.V, b.V, x, y, z, w) };
#endif
    }

    template <size_t X, size_t Y, size_t Z, size_t W, typename T>
    mathinline T mathcall Permute(T a, T b) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && (X < 8) && (Y < 8) && (Z < 8) && (W < 8))
    {

        if constexpr (X == 0 && Y == 1 && Z == 2 && W == 3)
        {
            return a;
        }
        else if constexpr (X == 4 && Y == 5 && Z == 6 && W == 7)
        {
            return b;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            return Permute(a, b, X, Y, Z, W);
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_permute<X, Y, Z, W>(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_permute<X, Y, Z, W>(a.V, b.V) };
#endif
        }
    }
}


// =================================================================================================
//
// Swizzling
//

namespace Graphyte::Maths
{
    template <size_t X, size_t Y, size_t Z, size_t W, typename T>
    mathinline T mathcall Swizzle(T v) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && (X < 4) && (Y < 4) && (Z < 4) && (W < 4))
    {
        if constexpr (X == 0 && Y == 1 && Z == 2 && W == 3)
        {
            return v;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const result{ { {
                v.V.F[X],
                v.V.F[Y],
                v.V.F[Z],
                v.V.F[W],
            } } };
            return { result.V };
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_swizzle<X, Y, Z, W>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_swizzle<X, Y, Z, W>(v.V) };
#endif
        }
    }

    template <size_t X, size_t Y, size_t Z, typename T>
    mathinline T mathcall Swizzle(T v) noexcept
        requires(T::Components == 3 && Impl::IsSimdFloat4<T> && (X < 3) && (Y < 3) && (Z < 3))
    {
        if constexpr (X == 0 && Y == 1 && Z == 2)
        {
            return v;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const result{ { {
                v.V.F[X],
                v.V.F[Y],
                v.V.F[Z],
                v.V.F[Y],
            } } };
            return { result.V };
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_swizzle<X, Y, Z, Y>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_swizzle<X, Y, Z, Y>(v.V) };
#endif
        }
    }

    template <size_t X, size_t Y, typename T>
    mathinline T mathcall Swizzle(T v) noexcept
        requires(T::Components == 2 && Impl::IsSimdFloat4<T> && (X < 2) && (Y < 2))
    {
        if constexpr (X == 0 && Y == 1)
        {
            return v;
        }
        else
        {
#if GRAPHYTE_MATH_NO_INTRINSICS
            Impl::ConstFloat32x4 const result{ { {
                v.V.F[X],
                v.V.F[Y],
                v.V.F[X],
                v.V.F[Y],
            } } };
            return { result.V };
#elif GRAPHYTE_HW_AVX
            return { Impl::avx_swizzle<X, Y, X, Y>(v.V) };
#elif GRAPHYTE_HW_NEON
            return { Impl::neon_swizzle<X, Y, X, Y>(v.V) };
#endif
        }
    }

    template <typename T>
    mathinline T mathcall Swizzle(T v, uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT((x < 4) && (y < 4) && (z < 4) && (w < 4));
        GX_COMPILER_ASSUME((x < 4) && (y < 4) && (z < 4) && (w < 4));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[x],
            v.V.F[y],
            v.V.F[z],
            v.V.F[w],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        alignas(__m128i) uint32_t indices[4]{
            x,
            y,
            z,
            w,
        };

        __m128i const control = _mm_load_si128(reinterpret_cast<__m128i const*>(&indices[0]));
        __m128 const result   = _mm_permutevar_ps(v.V, control);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { Impl::neon_swizzle(v.V, x, y, z, w) };
#endif
    }

    template <typename R, typename T>
    mathinline R mathcall MergeXY(T a, T b) noexcept
        requires(R::Components == 4 && T::Components >= 2 && Impl::IsSimdFloat4<R> && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            a.V.U[0],
            b.V.U[0],
            a.V.U[1],
            b.V.U[1],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_unpacklo_ps(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vzipq_f32(a.V, b.V).val[0];
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall MergeZW(T a, T b) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            a.V.U[2],
            b.V.U[2],
            a.V.U[3],
            b.V.U[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_unpackhi_ps(a.V, b.V);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const result = vzipq_f32(a.V, b.V).val[1];
        return { result };
#endif
    }

    template <uint32_t Count, typename T>
    mathinline T mathcall ShiftLeft(T a, T b) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && Count < 4)
    {
        return Permute<Count + 0, Count + 1, Count + 2, Count + 3>(a, b);
    }

    template <typename T>
    mathinline T mathcall ShiftLeft(T a, T b, uint32_t count) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(count < 4);
        return Permute(a, b, count + 0, count + 1, count + 2, count + 3);
    }

    template <uint32_t Count, typename T>
    mathinline T mathcall RotateLeft(T v) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && Count < 4)
    {
        return Swizzle<(Count + 0) & 0b11, (Count + 1) & 0b11, (Count + 2) & 0b11, (Count + 3) & 0b11>(v);
    }

    template <typename T>
    mathinline T mathcall RotateLeft(T v, uint32_t count) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(count < 4);

        return Swizzle(v, (count + 0) & 0b11, (count + 1) & 0b11, (count + 2) & 0b11, (count + 3) & 0b11);
    }

    template <uint32_t Count, typename T>
    mathinline T mathcall RotateRight(T v) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T> && Count < 4)
    {
        return Swizzle<(4 - Count) & 0b11, (5 - Count) & 0b11, (6 - Count) & 0b11, (7 - Count) & 0b11>(v);
    }

    template <typename T>
    mathinline T mathcall RotateRight(T v, uint32_t count) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(count < 4);
        return Swizzle(v, (4 - count) & 0b11, (5 - count) & 0b11, (6 - count) & 0b11, (7 - count) & 0b11);
    }
}


// =================================================================================================
//
// Vector insert
//

namespace Graphyte::Maths
{
    template <bool X, bool Y, bool Z, bool W, typename T>
    mathinline T mathcall Insert(T a, T b) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        constexpr uint32_t const index_x = 0 + (X ? 4 : 0);
        constexpr uint32_t const index_y = 1 + (Y ? 4 : 0);
        constexpr uint32_t const index_z = 2 + (Z ? 4 : 0);
        constexpr uint32_t const index_w = 3 + (W ? 4 : 0);
        return Permute<index_x, index_y, index_z, index_w>(a, b);
    }

    template <typename T>
    mathinline T mathcall Insert(T a, T b, bool x, bool y, bool z, bool w) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        typename T::MaskComponent const control = SelectControl<typename T::MaskComponent>(
            x ? 1 : 0,
            y ? 1 : 0,
            z ? 1 : 0,
            w ? 1 : 0);
        return Select(a, b, control);
    }

    template <typename T>
    mathinline T mathcall Insert(T a, T b, uint32_t rotate_left_count, bool x, bool y, bool z, bool w) noexcept
        requires(T::Components == 4 && Impl::IsSimdFloat4<T>)
    {
        typename T::MaskComponent const control = SelectControl<typename T::MaskComponent>(
            x ? 1 : 0,
            y ? 1 : 0,
            z ? 1 : 0,
            w ? 1 : 0);
        return Select(a, RotateLeft(b, rotate_left_count), control);
    }
}


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
// Load / store operations
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Load(Float4A const* source) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            source->X,
            source->Y,
            source->Z,
            source->W,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps(reinterpret_cast<float const*>(source)) };
#endif
    }

    template <typename T>
    mathinline T mathcall Store(Float4A* destination, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float4 const* source) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            source->X,
            source->Y,
            source->Z,
            source->W,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_loadu_ps(reinterpret_cast<float const*>(source)) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float4* destination, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(reinterpret_cast<float*>(destination), v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3A const* source) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            source->X,
            source->Y,
            source->Z,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xyzn   = _mm_load_ps(reinterpret_cast<float const*>(source));
        __m128 const result = _mm_and_ps(xyzn, Impl::VEC4_MASK_COMPONENTS_3.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3A* destination, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(&destination->Z, zzzz);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float3 const* source) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            source->X,
            source->Y,
            source->Z,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_x   = _mm_load_ss(&source->X);
        __m128 const v_y   = _mm_load_ss(&source->Y);
        __m128 const v_z   = _mm_load_ss(&source->Z);
        __m128 const v_xy  = _mm_unpacklo_ps(v_x, v_y);
        __m128 const v_xyz = _mm_movelh_ps(v_xy, v_z);
        return { v_xyz };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float3* destination, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        __m128 const zzzz = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, yyyy);
        _mm_store_ss(&destination->Z, zzzz);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2A const* source) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void const*>(source), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            source->X,
            source->Y,
            0.0F,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const v_xy = _mm_loadl_epi64(reinterpret_cast<__m128i const*>(source));
        return { _mm_castsi128_ps(v_xy) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2A* destination, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<void*>(destination), std::align_val_t{ 16 }));

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Float2 const* source) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            source->X,
            source->Y,
            0.0F,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const v_x    = _mm_load_ss(&source->X);
        __m128 const v_y    = _mm_load_ss(&source->Y);
        __m128 const result = _mm_unpacklo_ps(v_x, v_y);
        return { result };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Float2* destination, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(float const* source) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            *source,
            0.0F,
            0.0F,
            0.0F,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ss(source) };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(float* destination, T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*destination) = v.V.F[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(destination, v.V);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Half4 const* source) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
            FromHalf(source->X),
            FromHalf(source->Y),
            FromHalf(source->Z),
            FromHalf(source->W),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_loadl_epi64(reinterpret_cast<__m128i const*>(source));
        __m128 const h1 = _mm_cvtph_ps(_mm_castps_si128(h0));
        return { h1 };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Half4* destination, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const components{
            .V = v.V
        };

        destination->X = ToHalf(components.F[0]);
        destination->Y = ToHalf(components.F[1]);
        destination->Z = ToHalf(components.F[2]);
        destination->W = ToHalf(components.F[3]);
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_cvtps_ph(v.V, _MM_FROUND_TO_NEAREST_INT);
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), h0);
#endif
    }

    template <typename T>
    mathinline T mathcall Load(Half2 const* source) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(source != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const result{ { {
            FromHalf(source->X),
            FromHalf(source->Y),
            0.0f,
            0.0f,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_load_ss(reinterpret_cast<float const*>(source));
        __m128 const h1 = _mm_cvtph_ps(_mm_castps_si128(h0));
        return { h1 };
#endif
    }

    template <typename T>
    mathinline void mathcall Store(Half2* destination, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(destination != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_AVX || GRAPHYTE_HW_NEON
        Impl::ConstFloat32x4 const components{
            .V = v.V
        };

        destination->X = ToHalf(components.F[0]);
        destination->Y = ToHalf(components.F[1]);
#elif GRAPHYTE_HW_AVX2
        __m128 const h0 = _mm_cvtps_ph(v.V, _MM_FROUND_TO_NEAREST_INT);
        __m128 const h1 = _mm_castsi128_ps(h0);
        _mm_store_ss(reinterpret_cast<float*>(destination), h1);
#endif
    }
}


// =================================================================================================
//
// Vector splatting
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall SplatX(T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[0];
        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcastss_ps(v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_low_f32(v.V), 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatY(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[1];
        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_low_f32(v.V), 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatZ(T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[2];
        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_high_f32(v.V), 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SplatW(T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const value = v.V.F[3];
        Impl::ConstFloat32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3)) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_lane_f32(vget_high_f32(v.V), 1) };
#endif
    }
}


// =================================================================================================
//
// Float lane accessors
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline float mathcall GetByIndex(T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[index];
#else
        Impl::ConstFloat32x4 result;
        result.V = v.V;
        return result.F[index];
#endif
    }

    template <typename T>
    mathinline T mathcall SetByIndex(T v, float value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V        = v.V;
        result.F[index] = value;
        return { result.V };
    }

    template <typename T>
    mathinline void mathcall GetByIndex(float* result, T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(result != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[index];
#else
        Impl::ConstFloat32x4 r;
        r.V       = v.V;
        (*result) = r.F[index];
#endif
    }

    template <typename T>
    mathinline T mathcall SetByIndex(T v, float const* value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstFloat32x4 result;
        result.V        = v.V;
        result.F[index] = (*value);
        return { result.V };
    }

    template <typename T>
    mathinline float mathcall GetX(T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 0);
#endif
    }

    template <typename T>
    mathinline float mathcall GetY(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 1);
#endif
    }

    template <typename T>
    mathinline float mathcall GetZ(T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 2);
#endif
    }

    template <typename T>
    mathinline float mathcall GetW(T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        __m128 const result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(result);
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_f32(v.V, 3);
#endif
    }

    template <typename T>
    mathinline void mathcall GetX(float* result, T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[0];
#elif GRAPHYTE_HW_NEON
        (*result)           = vgetq_lane_f32(v.V, 0);
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(result, v.V);
#endif
    }

    template <typename T>
    mathinline void mathcall GetY(float* result, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[1];
#elif GRAPHYTE_HW_NEON
        (*result)           = vgetq_lane_f32(v.V, 1);
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 1);
#endif
    }

    template <typename T>
    mathinline void mathcall GetZ(float* result, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[2];
#elif GRAPHYTE_HW_NEON
        (*result)           = vgetq_lane_f32(v.V, 2);
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 2);
#endif
    }

    template <typename T>
    mathinline void mathcall GetW(float* result, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.F[3];
#elif GRAPHYTE_HW_NEON
        (*result)           = vgetq_lane_f32(v.V, 3);
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(result)) = _mm_extract_ps(v.V, 3);
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, float value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            value,
            v.V.F[1],
            v.V.F[2],
            v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx   = _mm_set_ss(value);
        __m128 const result = _mm_move_ss(v.V, xxxx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0],
            value,
            v.V.F[2],
            v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yyyy   = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, yyyy, 0x10);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0],
            v.V.F[1],
            value,
            v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zzzz   = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, zzzz, 0x20);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0],
            v.V.F[1],
            v.V.F[2],
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wwww   = _mm_set_ss(value);
        __m128 const result = _mm_insert_ps(v.V, wwww, 0x30);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_f32(value, v.V, 3) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, float const* value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            *value,
            v.V.F[1],
            v.V.F[2],
            v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const xxxx   = _mm_load_ss(value);
        __m128 const result = _mm_move_ss(v.V, xxxx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, float const* value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0],
            *value,
            v.V.F[2],
            v.V.F[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_yxzw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const yyyy   = _mm_load_ss(value);
        __m128 const n_yxzw = _mm_move_ss(o_yxzw, yyyy);
        __m128 const xyzw   = _mm_permute_ps(n_yxzw, _MM_SHUFFLE(3, 2, 0, 1));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, float const* value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0],
            v.V.F[1],
            *value,
            v.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_zyxw = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const zzzz   = _mm_load_ss(value);
        __m128 const n_zyxw = _mm_move_ss(o_zyxw, zzzz);
        __m128 const xyzw   = _mm_permute_ps(n_zyxw, _MM_SHUFFLE(3, 0, 1, 2));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, float const* value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            v.V.F[0],
            v.V.F[1],
            v.V.F[2],
            *value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const o_wyzx = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        __m128 const wwww   = _mm_load_ss(value);
        __m128 const n_wyzx = _mm_move_ss(o_wyzx, wwww);
        __m128 const xyzw   = _mm_permute_ps(n_wyzx, _MM_SHUFFLE(0, 2, 1, 3));
        return { xyzw };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_f32(value, v.V, 3) };
#endif
    }

}


// =================================================================================================
//
// UInt lane accessors
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline uint32_t mathcall GetByIndex(T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[index];
#elif GRAPHYTE_HW_AVX
        Impl::ConstUInt32x4 result;
        result.V = v.V;
        return result.U[index];
#endif
    }

    template <typename T>
    mathinline T mathcall SetByIndex(T v, uint32_t value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstUInt32x4 result;
        result.V        = v.V;
        result.U[index] = value;
        return { result.V };
    }

    template <typename T>
    mathinline void mathcall GetByIndex(uint32_t* result, T v, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[index];
#elif GRAPHYTE_HW_AVX
        Impl::ConstUInt32x4 r;
        r.V       = v.V;
        (*result) = r.U[index];
#endif
    }

    template <typename T>
    mathinline void mathcall SetByIndex(T v, uint32_t const* value, size_t index) noexcept
        requires(T::Components <= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Impl::ConstUInt32x4 result;
        result.V        = v.V;
        result.U[index] = (*value);
        return { result.V };
    }

    template <typename T>
    mathinline uint32_t mathcall GetX(T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[0];
#elif GRAPHYTE_HW_AVX
        return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(v.V)));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 0);
#endif
    }

    template <typename T>
    mathinline uint32_t mathcall GetY(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[1];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(r, 1));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 1);
#endif
    }

    template <typename T>
    mathinline uint32_t mathcall GetZ(T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[2];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(r, 2));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 2);
#endif
    }

    template <typename T>
    mathinline uint32_t mathcall GetW(T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[3];
#elif GRAPHYTE_HW_AVX
        __m128i const r = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(r, 3));
#elif GRAPHYTE_HW_NEON
        return vgetq_lane_u32(v.V, 3);
#endif
    }

    template <typename T>
    mathinline void mathcall GetX(uint32_t* result, T v) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(reinterpret_cast<float*>(result), v.V);
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 0);
#endif
    }

    template <typename T>
    mathinline void mathcall GetY(uint32_t* result, T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[1];
#elif GRAPHYTE_HW_AVX
        __m128i const r     = _mm_castps_si128(v.V);
        (*result)           = static_cast<uint32_t>(_mm_extract_epi32(r, 1));
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 1);
#endif
    }

    template <typename T>
    mathinline void mathcall GetZ(uint32_t* result, T v) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[2];
#elif GRAPHYTE_HW_AVX
        __m128i const r     = _mm_castps_si128(v.V);
        (*result)           = static_cast<uint32_t>(_mm_extract_epi32(r, 2));
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 2);
#endif
    }

    template <typename T>
    mathinline void mathcall GetW(uint32_t* result, T v) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(result != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        (*result) = v.V.U[3];
#elif GRAPHYTE_HW_AVX
        __m128i const r     = _mm_castps_si128(v.V);
        (*result)           = static_cast<uint32_t>(_mm_extract_epi32(r, 3));
#elif GRAPHYTE_HW_NEON
        vst1q_lane_u32(result, vreinterpretq_u32_f32(v.V), 3);
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, uint32_t value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            value,
            v.V.U[1],
            v.V.U[2],
            v.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const xxxx  = _mm_cvtsi32_si128(static_cast<int>(value));
        __m128 const result = _mm_move_ss(v.V, _mm_castsi128_ps(xxxx));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, uint32_t value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            v.V.U[0],
            value,
            v.V.U[2],
            v.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const vu    = _mm_castps_si128(v.V);
        __m128i const vy    = _mm_insert_epi32(vu, static_cast<int>(value), 1);
        __m128 const result = _mm_castsi128_ps(vy);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, uint32_t value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            v.V.U[0],
            v.V.U[1],
            value,
            v.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const vu    = _mm_castps_si128(v.V);
        __m128i const vz    = _mm_insert_epi32(vu, static_cast<int>(value), 2);
        __m128 const result = _mm_castsi128_ps(vz);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, uint32_t value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            v.V.U[0],
            v.V.U[1],
            v.V.U[2],
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const vu    = _mm_castps_si128(v.V);
        __m128i const vw    = _mm_insert_epi32(vu, static_cast<int>(value), 3);
        __m128 const result = _mm_castsi128_ps(vw);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vsetq_lane_u32(value, v.V, 3) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetX(T v, uint32_t const* value) noexcept
        requires(T::Components >= 1 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            *value,
            v.V.U[1],
            v.V.U[2],
            v.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const vx     = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const result = _mm_move_ss(v.V, vx);
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 0) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetY(T v, uint32_t const* value) noexcept
        requires(T::Components >= 2 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            v.V.U[0],
            *value,
            v.V.U[2],
            v.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const yxzw   = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        __m128 const yyyy   = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const x_yxzw = _mm_move_ss(yxzw, yyyy);
        __m128 const result = _mm_permute_ps(x_yxzw, _MM_SHUFFLE(3, 2, 0, 1));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 1) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetZ(T v, uint32_t const* value) noexcept
        requires(T::Components >= 3 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            v.V.U[0],
            v.V.U[1],
            *value,
            v.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const zyxw   = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        __m128 const zzzz   = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const z_zyxw = _mm_move_ss(zyxw, zzzz);
        __m128 const result = _mm_permute_ps(z_zyxw, _MM_SHUFFLE(3, 0, 1, 2));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 2) };
#endif
    }

    template <typename T>
    mathinline T mathcall SetW(T v, uint32_t const* value) noexcept
        requires(T::Components >= 4 && Impl::IsSimdUInt4<T>)
    {
        GX_ASSERT(value != nullptr);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            v.V.U[0],
            v.V.U[1],
            v.V.U[2],
            *value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const wyzx   = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        __m128 const wwww   = _mm_load_ss(reinterpret_cast<float const*>(value));
        __m128 const w_wyzx = _mm_move_ss(wyzx, wwww);
        __m128 const result = _mm_permute_ps(w_wyzx, _MM_SHUFFLE(0, 2, 1, 3));
        return { result };
#elif GRAPHYTE_HW_NEON
        return { vld1q_lane_u32(value, vreinterpretq_u32_f32(v.V), 3) };
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

    // TODO: More constants
}


// =================================================================================================
//
// Constructors
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Make(float x, float y, float z, float w) noexcept
        requires(T::Components >= 4 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z) noexcept
        requires(T::Components >= 3 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Make(float x, float y) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Make(float x) noexcept
        requires(T::Components >= 1 && Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Replicate(float value) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Replicate(float const* source) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Make(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            x,
            y,
            z,
            w,
        } } };
#elif GRAPHYTE_HW_AVX
        __m128i const ivec = _mm_set_epi32(
            static_cast<int>(w),
            static_cast<int>(z),
            static_cast<int>(y),
            static_cast<int>(x));

        return { _mm_castsi128_ps(ivec) };
#elif GRAPHYTE_HW_NEON
        uint32x2_t const r0_xy = vcreate_u32(static_cast<uint64_t>(x) | (static_cast<uint64_t>(y) << 32));
        uint32x2_t const r0_zw = vcreate_u32(static_cast<uint64_t>(z) | (static_cast<uint64_t>(w) << 32));

        float32x4_t const result = vreinterpretq_f32_u32(
            vcombine_u32(r0_xy, r0_zw));

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Replicate(uint32_t value) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const ivec = _mm_set1_epi32(static_cast<int>(value));
        return { _mm_castsi128_ps(ivec) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(value) };
#endif
    }

    template <typename T>
    mathinline T mathcall Replicate(uint32_t const* source) noexcept
        requires(T::Components == 4 && Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        uint32_t const value = (*source);

        Impl::ConstUInt32x4 const result{ { {
            value,
            value,
            value,
            value,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(reinterpret_cast<float const*>(source)) };
#elif GRAPHYTE_HW_NEON
        return { vld1q_dup_u32(source) };
#endif
    }
}


// =================================================================================================
//
// Boolean support
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall True() noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            0xFFFF'FFFFU,
            0xFFFF'FFFFU,
            0xFFFF'FFFFU,
            0xFFFF'FFFFU,
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_set1_epi32(-1);
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0xFFFFFFFFu) };
#endif
    }

    template <typename T>
    mathinline T mathcall False() noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result = { { { 0.0F,
            0.0F,
            0.0F,
            0.0F } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#elif GRAPHYTE_HW_NEON
        return { vdupq_n_u32(0u) };
#endif
    }

    template <typename T>
    mathinline T mathcall And(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            a.V.U[0] & b.V.U[0],
            a.V.U[1] & b.V.U[1],
            a.V.U[2] & b.V.U[2],
            a.V.U[3] & b.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_and_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vandq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall AndNot(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result = { { {
            a.V.U[0] & ~b.V.U[0],
            a.V.U[1] & ~b.V.U[1],
            a.V.U[2] & ~b.V.U[2],
            a.V.U[3] & ~b.V.U[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_andnot_si128(_mm_castps_si128(b.V), _mm_castps_si128(a.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vbicq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall Or(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            a.V.U[0] | b.V.U[0],
            a.V.U[1] | b.V.U[1],
            a.V.U[2] | b.V.U[2],
            a.V.U[3] | b.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_or_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vorrq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall Xor(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            a.V.U[0] ^ b.V.U[0],
            a.V.U[1] ^ b.V.U[1],
            a.V.U[2] ^ b.V.U[2],
            a.V.U[3] ^ b.V.U[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const result = _mm_xor_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            veorq_u32(
                vreinterpretq_u32_f32(a.V),
                vreinterpretq_u32_f32(b.V)));
#endif
    }

    template <typename T>
    mathinline T mathcall Nor(T a, T b) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            ~(a.V.U[0] | b.V.U[0]),
            ~(a.V.U[1] | b.V.U[1]),
            ~(a.V.U[2] | b.V.U[2]),
            ~(a.V.U[3] | b.V.U[3]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128i const partial = _mm_or_si128(_mm_castps_si128(a.V), _mm_castps_si128(b.V));
        __m128i const result  = _mm_andnot_si128(partial, _mm_castps_si128(Impl::VEC4_MASK_NEGATIVE_ONE.V));
        return { _mm_castsi128_ps(result) };
#elif GRAPHYTE_HW_NEON
        uint32x4_t const partial = vorrq_u32(
            vreinterpretq_u32_f32(a.V),
            vreinterpretq_u32_f32(b.V));

        return vreinterpretq_f32_u32(vmvnq_u32(partial));
#endif
    }

    template <typename T>
    mathinline T mathcall Not(T v) noexcept
        requires(Impl::IsSimdUInt4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstUInt32x4 const result{ { {
            ~(v.V.U[0]),
            ~(v.V.U[1]),
            ~(v.V.U[2]),
            ~(v.V.U[3]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const fullbits = _mm_castsi128_ps(_mm_set1_epi32(-1));
        __m128 const result   = _mm_xor_ps(v.V, fullbits);
        return { result };
#elif GRAPHYTE_HW_NEON
        return vreinterpretq_f32_u32(
            vmvnq_u32(vreinterpretq_u32_f32(v.V)));
#endif
    }
}


// =================================================================================================
//
// Common vector functions
//

namespace Graphyte::Maths::Impl
{
    mathinline float RoundToNearest(float value) noexcept
    {
        float const integral = floorf(value);
        float const fraction = value - integral;

        if (fraction < 0.5f)
        {
            return integral;
        }

        if (fraction > 0.5f)
        {
            return integral + 1.0f;
        }

        float integral_part;

        (void)modff(integral / 2.0f, &integral_part);

        if ((2.0f * integral_part) == integral)
        {
            return integral;
        }

        return integral + 1.0f;
    }

    mathinline double RoundToNearest(double value) noexcept
    {
        double const integral = floor(value);
        double const fraction = value - integral;

        if (fraction < 0.5)
        {
            return integral;
        }

        if (fraction > 0.5)
        {
            return integral + 1.0;
        }

        double integral_part;

        (void)modf(integral / 2.0, &integral_part);

        if ((2.0 * integral_part) == integral)
        {
            return integral;
        }

        return integral + 1.0;
    }
}

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall CopySign(T number, T sign) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
            copysignf(number.V.F[0], sign.V.F[0]),
            copysignf(number.V.F[1], sign.V.F[1]),
            copysignf(number.V.F[2], sign.V.F[2]),
            copysignf(number.V.F[3], sign.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        __m128 const mask       = _mm_castsi128_ps(_mm_set1_epi32(static_cast<int>(0x80000000)));
        __m128 const sign_mask  = _mm_and_ps(sign.V, mask);
        __m128 const abs_number = _mm_andnot_ps(mask, number.V);
        __m128 const result     = _mm_or_ps(abs_number, sign_mask);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall CopySign(T number, T sign) noexcept
        requires(std::floating_point<T>)
    {
        return copysign(number, sign);
    }

    template <typename T>
    mathinline T mathcall Sign(T x) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            Sign(x.V.F[0]),
            Sign(x.V.F[1]),
            Sign(x.V.F[2]),
            Sign(x.V.F[3]),
        } } };
        return { result.V };
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero   = vdupq_n_f32(0.0f);
        uint32x4_t const pos_one = vreinterpretq_u32_f32(vdupq_n_f32(1.0f));
        uint32x4_t const neg_one = vreinterpretq_u32_f32(vdupq_n_f32(-1.0f));
        uint32x4_t const lt_zero = vcltq_f32(x.V, zero);
        uint32x4_t const gt_zero = vcgtq_f32(x.V, zero);
        uint32x4_t const lt_sign = vandq_u32(lt_zero, neg_one);
        uint32x4_t const gt_sign = vandq_u32(gt_zero, pos_one);
        float32x4_t const result = vreinterpretq_f32_u32(vorq_u32(lt_sign, gt_sign));
        return { result };
#elif GRAPHYTE_HW_AVX
        __m128 const zero    = _mm_setzero_ps();
        __m128 const pos_one = _mm_set1_ps(1.0f);
        __m128 const neg_one = _mm_set1_ps(-1.0f);
        __m128 const lt_zero = _mm_cmplt_ps(x.V, zero);
        __m128 const gt_zero = _mm_cmpgt_ps(x.V, zero);
        __m128 const lt_sign = _mm_and_ps(lt_zero, neg_one);
        __m128 const gt_sign = _mm_and_ps(gt_zero, pos_one);
        __m128 const result  = _mm_or_ps(lt_sign, gt_sign);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Sign(T x) noexcept
        requires(std::floating_point<T>)
    {
        T const gt_zero = ((T(0.0) < x) ? T(1.0) : T(0.0));
        T const lt_zero = ((x < T(0.0)) ? T(1.0) : T(0.0));
        return gt_zero - lt_zero;
    }

    template <typename T>
    mathinline T mathcall Ceiling(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result{ { {
            ceilf(v.V.F[0]),
            ceilf(v.V.F[1]),
            ceilf(v.V.F[2]),
            ceilf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_ceil_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        return { vrndpq_f32(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Ceiling(T v) noexcept
        requires(std::floating_point<T>)
    {
        return ceil(v);
    }

    template <typename T>
    mathinline T mathcall Floor(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            floorf(v.V.F[0]),
            floorf(v.V.F[1]),
            floorf(v.V.F[2]),
            floorf(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_floor_ps(v.V) };
#elif GRAPHYTE_HW_NEON
        return { vrndmq_f32(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Floor(T v) noexcept
        requires(std::floating_point<T>)
    {
        return floor(v);
    }

    template <typename T>
    mathinline T mathcall Truncate(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 result;

        for (size_t i = 0; i < 4; ++i)
        {
            if (FloatTraits<float>::BitIsNan(v.V.U[i]))
            {
                result.V.U[i] = 0x7fc00000U;
            }
            else if (fabsf(v.V.F[i]) < 8388608.0F)
            {
                result.V.F[i] = static_cast<float>(static_cast<int32_t>(v.V.F[i]));
            }
            else
            {
                result.V.F[i] = v.V.F[i];
            }
        }

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
#elif GRAPHYTE_HW_NEON
        return { vrndq_f32(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Truncate(T v) noexcept
        requires(std::floating_point<T>)
    {
        return trunc(v);
    }

    template <typename T>
    mathinline T mathcall Round(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            Impl::RoundToNearest(v.V.F[0]),
            Impl::RoundToNearest(v.V.F[1]),
            Impl::RoundToNearest(v.V.F[2]),
            Impl::RoundToNearest(v.V.F[3]),
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
#elif GRAPHYTE_HW_NEON
        return { vrndnq_f32(v.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Round(T v) noexcept
        requires(std::floating_point<T>)
    {
        return round(v);
    }

    template <typename T>
    mathinline T mathcall Remainder(T x, T y) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            fmodf(x.V.F[0], y.V.F[0]),
            fmodf(x.V.F[1], y.V.F[1]),
            fmodf(x.V.F[2], y.V.F[2]),
            fmodf(x.V.F[3], y.V.F[3]),
        } } };
        return { result.V };
#elif GRAPHYTE_MATH_SVML
        return { _mm_fmod_ps(x.V, y.V) };
#elif GRAPHYTE_HW_AVX
        __m128 const q      = _mm_div_ps(x.V, y.V);
        __m128 const t      = _mm_round_ps(q, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
        __m128 const c      = _mm_cvtepi32_ps(_mm_cvttps_epi32(t));
        __m128 const result = Impl::avx_fnmadd_f32x4(c, y.V, x.V);
        return { result };
#else
        Impl::ConstFloat32x4 const components_x{ .V = x.V };
        Impl::ConstFloat32x4 const components_y{ .V = y.V };
        Impl::ConstFloat32x4 const result{ { {
            fmodf(components_x.F[0], components_y.F[0]),
            fmodf(components_x.F[1], components_y.F[1]),
            fmodf(components_x.F[2], components_y.F[2]),
            fmodf(components_x.F[3], components_y.F[3]),
        } } };

        return { result.V };
#endif
    }

    template <typename T>
    mathinline T mathcall Remainder(T x, T y) noexcept
        requires(std::floating_point<T>)
    {
        return fmod(x, y);
    }

    template <typename T>
    mathinline T mathcall Fraction(T x) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        return Subtract(x, Floor(x));
    }

    template <typename T>
    mathinline T mathcall Fraction(T x) noexcept
        requires(std::floating_point<T>)
    {
        return x - Floor(x);
    }
}


// =================================================================================================
//
// Componentwise functions
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Min(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (a.V.F[0] < b.V.F[0]) ? a.V.F[0] : b.V.F[0],
            (a.V.F[1] < b.V.F[1]) ? a.V.F[1] : b.V.F[1],
            (a.V.F[2] < b.V.F[2]) ? a.V.F[2] : b.V.F[2],
            (a.V.F[3] < b.V.F[3]) ? a.V.F[3] : b.V.F[3],
        } } };
        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_min_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vminq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Min(T a, T b) noexcept
        requires(std::floating_point<T>)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
    mathinline T mathcall Max(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::ConstFloat32x4 const result{ { {
            (a.V.F[0] < b.V.F[0]) ? b.V.F[0] : a.V.F[0],
            (a.V.F[1] < b.V.F[1]) ? b.V.F[1] : a.V.F[1],
            (a.V.F[2] < b.V.F[2]) ? b.V.F[2] : a.V.F[2],
            (a.V.F[3] < b.V.F[3]) ? b.V.F[3] : a.V.F[3],
        } } };

        return { result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_max_ps(a.V, b.V) };
#elif GRAPHYTE_HW_NEON
        return { vmaxq_f32(a.V, b.V) };
#endif
    }

    template <typename T>
    mathinline T mathcall Max(T a, T b) noexcept
        requires(std::floating_point<T>)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
        GX_ASSERT(IsLessEqual(min, max));

#if GRAPHYTE_MATH_NO_INTRINSICS
        T const below  = Max(min, v);
        T const result = Min(max, below);
        return result;
#elif GRAPHYTE_HW_AVX
        __m128 const below  = _mm_max_ps(min.V, v.V);
        __m128 const result = _mm_min_ps(max.V, below);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const below  = vmaxq_f32(min.V, v.V);
        float32x4_t const result = vminq_f32(max.V, below);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
        requires(std::floating_point<T>)
    {
        T const below  = Max(min, v);
        T const result = Min(max, below);
        return result;
    }

    template <typename T>
    mathinline T mathcall Saturate(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        T const zero = Zero<T>();
        T const one  = One<T>();
        return Clamp(v, zero, one);
#elif GRAPHYTE_HW_AVX
        __m128 const zero   = _mm_setzero_ps();
        __m128 const one    = Impl::VEC4_ONE_4.V;
        __m128 const below  = _mm_max_ps(v.V, zero);
        __m128 const result = _mm_min_ps(below, one);
        return { result };
#elif GRAPHYTE_HW_NEON
        float32x4_t const zero   = vdupq_n_f32(0.0F);
        float32x4_t const one    = vdupq_n_f32(1.0F);
        float32x4_t const below  = vmaxq_f32(v.V, zero);
        float32x4_t const result = vminq_f32(below, one);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Saturate(T v) noexcept
        requires(std::floating_point<T>)
    {
        T const below  = Max(T(0.0), v);
        T const result = Min(T(1.0), below);
        return result;
    }

    template <typename T>
    mathinline T mathcall Wrap(T v, T min, T max) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        float const range0 = (max.V.F[0] - min.V.F[0]);
        float const range1 = (max.V.F[1] - min.V.F[1]);
        float const range2 = (max.V.F[2] - min.V.F[2]);
        float const range3 = (max.V.F[3] - min.V.F[3]);

        float const progress0 = (v.V.F[0] - min.V.F[0]);
        float const progress1 = (v.V.F[1] - min.V.F[1]);
        float const progress2 = (v.V.F[2] - min.V.F[2]);
        float const progress3 = (v.V.F[3] - min.V.F[3]);

        Impl::ConstFloat32x4 const result{ { {
            min.V.F[0] + progress0 + (range0 * floorf(progress0 / range0)),
            min.V.F[1] + progress1 + (range1 * floorf(progress1 / range1)),
            min.V.F[2] + progress2 + (range2 * floorf(progress2 / range2)),
            min.V.F[3] + progress3 + (range3 * floorf(progress3 / range3)),
        } } };
#elif GRAPHYTE_HW_AVX
        __m128 const range    = _mm_sub_ps(max.V, min.V);
        __m128 const progress = _mm_sub_ps(v.V, min.V);

        __m128 const ratio = _mm_div_ps(progress, range);

        __m128 const base = _mm_floor_ps(ratio);

        __m128 const addend = Impl::avx_fmadd_f32x4(range, base, progress);

        __m128 const result = _mm_add_ps(min.V, addend);

        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall Wrap(T v, T min, T max) noexcept
        requires(std::floating_point<T>)
    {
        T const range    = (max - min);
        T const progress = (v - min);
        return min + progress + (range * floorf(progress / range));
    }

    template <typename T>
    mathinline T mathcall Hmin(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const c0 = Min(v.V.F[0], v.V.F[1]);
            float const c1 = Min(v.V.F[2], v.V.F[3]);
            float const c2 = Min(c0, c1);

            Impl::ConstFloat32x4 const result{ { {
                c2,
                c2,
                c2,
                c2,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 3)
        {
            float const c0 = Min(v.V.F[0], v.V.F[1]);
            float const c1 = Min(v.V.F[2], c0);

            Impl::ConstFloat32x4 const result{ { {
                c1,
                c1,
                c1,
                c1,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const c0 = Min(v.V.F[0], v.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                c0,
                c0,
                c0,
                c0,
            } } };
            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
            // {z,w, ...}
            __m128 const low_23 = _mm_movehl_ps(v.V, v.V);
            // {min(x,z), min(y,w), ...}
            __m128 const min_01_23 = _mm_min_ps(low_23, v.V);
            // {min(y,w)...}
            __m128 const min_11_11 = _mm_permute_ps(min_01_23, _MM_SHUFFLE(1, 1, 1, 1));
            // {min(min(x,z), min(y,w)}
            __m128 const min = _mm_min_ps(min_01_23, min_11_11);
            // {}.xxxx
            __m128 const result = _mm_permute_ps(min, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
        else if constexpr (T::Components == 3)
        {
            __m128 const xyzz      = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 1, 0));
            __m128 const zzzz      = _mm_movehl_ps(xyzz, xyzz);
            __m128 const min_xz_yz = _mm_min_ps(xyzz, zzzz);
            __m128 const min_yz    = _mm_permute_ps(min_xz_yz, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const min       = _mm_min_ps(min_xz_yz, min_yz);
            __m128 const result    = _mm_permute_ps(min, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
        else if constexpr (T::Components == 2)
        {
            __m128 const xy        = v.V;
            __m128 const yy        = _mm_permute_ps(xy, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const min_xy_yy = _mm_min_ps(xy, yy);
            __m128 const result    = _mm_permute_ps(min_xy_yy, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
#endif
    }

    template <typename T>
    mathinline T mathcall Hmax(T v) noexcept
        requires(T::Components >= 2 && Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const c0 = Max(v.V.F[0], v.V.F[1]);
            float const c1 = Max(v.V.F[2], v.V.F[3]);
            float const c2 = Max(c0, c1);

            Impl::ConstFloat32x4 const result{ { {
                c2,
                c2,
                c2,
                c2,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 3)
        {
            float const c0 = Max(v.V.F[0], v.V.F[1]);
            float const c1 = Max(v.V.F[2], c0);

            Impl::ConstFloat32x4 const result{ { {
                c1,
                c1,
                c1,
                c1,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const c0 = Max(v.V.F[0], v.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                c0,
                c0,
                c0,
                c0,
            } } };
            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
            // {z,w, ...}
            __m128 const low_23 = _mm_movehl_ps(v.V, v.V);
            // {max(x,z), max(y,w), ...}
            __m128 const max_01_23 = _mm_max_ps(low_23, v.V);
            // {min(y,w)...}
            __m128 const max_11_11 = _mm_permute_ps(max_01_23, _MM_SHUFFLE(1, 1, 1, 1));
            // {min(min(x,z), min(y,w)}
            __m128 const max = _mm_max_ps(max_01_23, max_11_11);
            // {}.xxxx
            __m128 const result = _mm_permute_ps(max, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
        else if constexpr (T::Components == 3)
        {
            __m128 const xyzz      = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 1, 0));
            __m128 const zzzz      = _mm_movehl_ps(xyzz, xyzz);
            __m128 const max_xz_yz = _mm_max_ps(xyzz, zzzz);
            __m128 const max_yz    = _mm_permute_ps(max_xz_yz, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const max       = _mm_max_ps(max_xz_yz, max_yz);
            __m128 const result    = _mm_permute_ps(max, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
        else if constexpr (T::Components == 2)
        {
            __m128 const xy        = v.V;
            __m128 const yy        = _mm_permute_ps(xy, _MM_SHUFFLE(1, 1, 1, 1));
            __m128 const max_xy_yy = _mm_max_ps(xy, yy);
            __m128 const result    = _mm_permute_ps(max_xy_yy, _MM_SHUFFLE(0, 0, 0, 0));
            return { result };
        }
#endif
    }

    template <typename T>
    mathinline T mathcall Hsum(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        if constexpr (T::Components == 4)
        {
            float const c = (v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);

            Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 3)
        {
            float const c = (v.V.F[0] + v.V.F[1] + v.V.F[2]);

            Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
            return { result.V };
        }
        else if constexpr (T::Components == 2)
        {
            float const c = (v.V.F[0] + v.V.F[1]);

            Impl::ConstFloat32x4 const result{ { {
                c,
                c,
                c,
                c,
            } } };
            return { result.V };
        }
#elif GRAPHYTE_HW_AVX
        if constexpr (T::Components == 4)
        {
            __m128 const xy_zw  = _mm_hadd_ps(v.V, v.V);
            __m128 const result = _mm_hadd_ps(xy_zw, xy_zw);
            return { result };
        }
        else if constexpr (T::Components == 3)
        {
            __m128 const xyz0   = _mm_and_ps(v.V, Impl::VEC4_MASK_SELECT_1110.V);
            __m128 const xy_zz  = _mm_hadd_ps(xyz0, xyz0);
            __m128 const result = _mm_hadd_ps(xy_zz, xy_zz);
        }
        else if constexpr (T::Components == 2)
        {
            __m128 const yx     = _mm_movelh_ps(v.V, v.V);
            __m128 const result = _mm_hadd_ps(yx, yx);
            return { result };
        }
#endif
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
        requires(std::floating_point<T>)
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
