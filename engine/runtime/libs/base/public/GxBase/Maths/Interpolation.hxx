#pragma once
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Lerp(T a, T b, T t) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Lerp(T a, T b, T t) noexcept
        requires(std::floating_point<T>)
    {
        return a + (b - a) * t;
    }

    template <typename T>
    mathinline T mathcall LerpPrecise(T a, T b, T t) noexcept
        requires(std::floating_point<T>)
    {
        return ((T(1) - t) * a) + (t * b);
    }

    template <typename T>
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, float t) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
        requires(Impl::IsSimdFloat4<T>)
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
        __m128 const ty      = _mm_and_ps(t.V, Impl::VEC4_MASK_COMPONENT_Y.V);
        __m128 const t2t3ty  = _mm_add_ps(t2t3_ma, ty);
        __m128 const tfinal  = _mm_add_ps(t2t3ty, Impl::VEC4_POSITIVE_UNIT_X.V);

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
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, T t) noexcept
        requires(std::floating_point<T>)
    {
        T const t2 = t * t;
        T const t3 = t * t2;

        T const p0 = (T(2.0) * t3 - T(3.0) * t2 + T(1.0));
        T const t0 = (t3 - T(2.0) * t2 + t);
        T const p1 = (T(-2.0) * t3 + T(3.0) * t2);
        T const t1 = (t3 - t2);

        T const r0 = (p0 * position0);
        T const r1 = (t0 * tangent0) + r0;
        T const r2 = (p1 * position1) + r1;
        T const r3 = (t1 * tangent1) + r2;

        return r3;
    }

    template <typename T>
    mathinline T mathcall Barycentric(T a, T b, T c, float f, float g) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
        requires(std::floating_point<T>)
    {
        T const pba    = b - a;
        T const pca    = c - a;
        T const accum  = (pba * f) + a;
        T const result = (pca * g) + accum;
        return result;
    }

    template <typename T>
    mathinline T mathcall Barycentric(T a, T b, T c, T f, T g) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
        requires(Impl::IsSimdFloat4<T>)
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
        requires(Impl::IsSimdFloat4<T>)
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
        result = _mm_mul_ps(result, Impl::VEC4_ONE_HALF_4.V);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall CatmullRom(T p0, T p1, T p2, T p3, T t) noexcept
        requires(std::floating_point<T>)
    {
        float const t2 = t * t;
        float const t3 = t * t2;

        float const f0 = (-t3 + T(2.0) * t2 - t) * T(0.5);
        float const f1 = (T(3.0) * t3 - T(5.0) * t2 + T(2.0)) * T(0.5);
        float const f2 = (T(-3.0) * t3 + T(4.0) * t2 + t) * T(0.5);
        float const f3 = (t3 - t2) * T(0.5);

        float const r0 = (f0 * p0);
        float const r1 = (f1 * p1) + r0;
        float const r2 = (f2 * p2) + r1;
        float const r3 = (f3 * p3) + r2;

        return r3;
    }

    template <typename T>
    mathinline T mathcall Remap(T value, T from_min, T from_max, T to_min, T to_max) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Remap(T value, T from_min, T from_max, T to_min, T to_max) noexcept
        requires(std::floating_point<T>)
    {
        T const from_abs     = (value - from_min);
        T const from_max_abs = (from_max - from_min);

        T const normal = (from_abs / from_max_abs);

        T const to_max_abs = (to_max - to_min);
        T const to_abs     = (to_max_abs * normal);

        T const to = (to_abs + to_min);

        return to;
    }

    template <typename T>
    mathinline T mathcall Unlerp(T value, T min, T max) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Unlerp(T value, T min, T max) noexcept
        requires(std::floating_point<T>)
    {
        T const base   = (value - min);
        T const range  = (max - min);
        T const result = (base / range);
        return result;
    }

    template <typename T>
    mathinline T mathcall Bezier(T a, T b, T c, T t) noexcept
        requires(std::floating_point<T>)
    {
        T const t2  = t * t;
        T const t1  = T(1.0) - t;
        T const t12 = t1 * t1;
        return (a * t12) + (T(2.0) * b * t1 * t) + (c * t2);
    }

    template <typename T>
    mathinline T mathcall Bezier(T a, T b, T c, T d, T t) noexcept
        requires(std::floating_point<T>)
    {
        T const t1  = T(1.0) - t;
        T const t13 = t1 * t1 * t1;
        T const t3  = t * t * t;

        return (t13 * a) + (T(3.0) * t * t1 * t1 * b) + (T(3.0) * t * t * t1 * c) + (t3 * d);
    }

    template <typename T>
    mathinline T mathcall Cubic(T a, T b, T c, T d, T t) noexcept
        requires(std::floating_point<T>)
    {
        T const t2 = t * t;
        T const a2 = (T(-0.5) * b) + (T(1.5) * a) - (T(1.5) * d) + (T(0.5) * c);
        T const a1 = b - (T(2.5) * a) + (T(2.0) * d) - (T(0.5) * c);
        T const a0 = (T(-0.5) * b) + (T(0.5) * d);

        T const result = (a2 * t * t2) + (a1 * t2) + (a0 * t) + a;
    }

    // Vector1, Vector2, Vector3, Vector4
    template <typename T>
    mathinline T mathcall SmoothStep(T a, T b, T x) noexcept
        requires(Impl::IsVector<T>)
    {
        T const length = Subtract(x, a);
        T const base = Subtract(b, a);
        T const t = Divide(length, base);
        T const r0 = NegativeMultiplyAdd(t, Replicate<T>(2.0f), Replicate<T>(3.0f));
        T const r1 = Multiply(r0, t);
        T const r2 = Multiply(r1, t);
        return r2;
    }

    template <typename T>
    mathinline T mathcall SmoothStep(T a, T b, float x) noexcept
        requires(Impl::IsVector<T>)
    {
        return SmoothStep(a, b, Replicate<T>(x));
    }

    template <typename T>
    mathinline T mathcall SmoothStep(T a, T b, T x) noexcept
        requires(std::floating_point<T>)
    {
        float const t = Saturate((x - a) / (b - a));
        float const result = t * (t * NegateMultiplyAdd(t, 2.0f, 3.0f));
        return result;
    }

    template <typename T>
    mathinline T mathcall Cosine(T a, T b, T t) noexcept
        requires(std::floating_point<T>)
    {
        float const t0 = (T(1.0) - Cos(t * Impl::g_Const_Pi<T>)) * T(0.5);
        return Lerp(a, b, t0);
    }

    template <typename T>
    mathinline T mathcall EaseSmoothC2(T x) noexcept
        requires(std::floating_point<T>)
    {
        return (x * x * x) * (x * ((x * T(6.0)) - T(15.0)) + T(10.0));
    }

    template <typename T>
    mathinline T mathcall Smooth(T min, T max, T x) noexcept
        requires(std::floating_point<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const xx = (x - min) / (max - min);
        T const result = (xx * (xx * (T(3.0) - (T(2.0) * x)));
        return result;
    }

    template <typename T>
    mathinline T mathcall SmoothSquared(T min, T max, T x) noexcept
        requires(std::floating_point<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const xx = (x * x);
        return Lerp<T>(min, max, xx);
    }

    template <typename T>
    mathinline T mathcall SmoothInvSquared(T min, T max, T x) noexcept
        requires(std::floating_point<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const ox = T(1.0) - x;
        T const oxox = ox * ox;
        T const xx = T(1.0) - oxox;
        return Lerp<T>(min, max, xx);
    }

    template <typename T>
    mathinline T mathcall SmoothCubed(T min, T max, T x) noexcept
        requires(std::floating_point<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const xx = (x * x * x);
        return Lerp<T>(min, max, xx);
    }

    template <typename T>
    mathinline T mathcall SmoothInvCubed(T min, T max, T x) noexcept
        requires(std::floating_point<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const ox = T(1.0) - x;
        T const oxoxox = (ox * ox * ox);
        T const xx = T(1.0) - oxoxox;
        return Lerp<T>(min, max, xx);
    }

    template <typename T>
    mathinline T mathcall Trapezoid(T a, T b, T c, T d, T t) noexcept
    {
        if (t <= a)
        {
            return T{};
        }
        else if (t < b)
        {
            return (t - a) / (b - a);
        }
        else if (t < c)
        {
            return T(1.0);
        }
        else if (t < d)
        {
            return T(1.0) - ((t - c) / (d - c));
        }

        return T{};
    }

    template <typename T>
    mathinline T mathcall Trapezoid(T a, T b, T c, T d, T t, T min, T max) noexcept
    {
        return Lerp<T>(min, max, Trapezoid(a, b, c, d, t));
    }
}
