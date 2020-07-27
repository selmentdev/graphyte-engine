#pragma once
#include <GxBase/Maths/Vector.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Cos(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Cos(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return cos(v);
    }

    template <typename T>
    mathinline T mathcall Sin(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Sin(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return sin(v);
    }

    template <typename T>
    mathinline void mathcall SinCos(T& out_sin, T& out_cos, T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline void mathcall SinCos(T& out_sin, T& out_cos, T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        out_sin = sin(v);
        out_cos = cos(v);
    }

    template <typename T>
    mathinline T mathcall Tan(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Tan(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return tan(v);
    }

    template <typename T>
    mathinline T mathcall Asin(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Asin(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return asin(v);
    }

    template <typename T>
    mathinline T mathcall Acos(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Acos(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return acos(v);
    }

    template <typename T>
    mathinline T mathcall Atan(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Atan(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return atan(v);
    }

    template <typename T>
    mathinline T mathcall Atan2(T y, T x) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Atan2(T y, T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return atan2(y, x);
    }

    template <typename T>
    mathinline T mathcall Sinh(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Sinh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return sinh(v);
    }

    template <typename T>
    mathinline T mathcall Cosh(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Cosh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return cosh(v);
    }

    template <typename T>
    mathinline T mathcall Tanh(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Tanh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return tanh(v);
    }

    template <typename T>
    mathinline T mathcall Asinh(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Asinh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return asinh(v);
    }

    template <typename T>
    mathinline T mathcall Acosh(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Acosh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return acosh(v);
    }

    template <typename T>
    mathinline T mathcall Atanh(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Atanh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return atanh(v);
    }

    template <typename T>
    mathinline T mathcall Log(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Log(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log(v);
    }

    template <typename T>
    mathinline T mathcall Log(T base, T value) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Log(T base, T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log(value) / log(base);
    }

    template <typename T>
    mathinline T mathcall Log10(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Log10(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log10(v);
    }

    template <typename T>
    mathinline T mathcall Log2(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Log2(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log2(v);
    }

    template <typename T>
    mathinline T mathcall Exp(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Exp(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return exp(v);
    }

    template <typename T>
    mathinline T mathcall Exp10(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Exp10(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return pow(T(10), v);
    }

    template <typename T>
    mathinline T mathcall Exp2(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Exp2(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return exp2(v);
    }

    template <typename T>
    mathinline T mathcall Power(T x, T y) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Power(T x, T y) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return pow(x, y);
    }

    template <typename T>
    mathinline T mathcall Hypot(T x, T y) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Hypot(T x, T y) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return hypot(x, y);
    }

    template <typename T>
    mathinline T mathcall Sqrt(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Sqrt(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_sqrt_ss(_mm_set_ss(v));
        float result;
        _mm_store_ss(&result, s);
        return result;
#endif
    }

    template <typename T>
    mathinline T mathcall SqrtEst(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall SqrtEst(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const s = _mm_rcp_ss(_mm_rsqrt_ss(_mm_set_ss(v)));
        float result;
        _mm_store_ss(&result, s);
        return result;
#endif
    }

    template <typename T>
    mathinline T mathcall InvSqrt(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
        __m128 const result  = _mm_div_ps(Impl::VEC4_ONE_4.V, partial);
        return { result };
#endif
    }

    template <typename T>
    mathinline T mathcall InvSqrt(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return 1.0F / sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const vv = _mm_set_ss(v);
        __m128 const rv = _mm_rsqrt_ss(vv);
        float result;
        _mm_store_ss(&result, rv);
        return result;
#endif
    }

    template <typename T>
    mathinline T mathcall InvSqrtEst(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall InvSqrtEst(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
#if GRAPHYTE_MATH_NO_INTRINSICS || GRAPHYTE_HW_NEON
        return 1.0F / sqrtf(v);
#elif GRAPHYTE_HW_AVX
        __m128 const vv = _mm_set_ss(v);
        __m128 const rv = _mm_rsqrt_ss(vv);
        float result;
        _mm_store_ss(&result, rv);
        return result;
#endif
    }

    template <typename T>
    mathinline T mathcall Cbrt(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Cbrt(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return cbrt(v);
    }

    template <typename T>
    mathinline T mathcall InvCbrt(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall InvCbrt(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return T(1) / cbrt(v);
    }

    template <typename T>
    mathinline T mathcall Abs(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Abs(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return fabs(v);
    }

    template <typename T>
    mathinline T mathcall Negate(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Negate(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return -v;
    }

    template <typename T>
    mathinline T mathcall Add(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Add(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a + b;
    }

    template <typename T>
    mathinline T mathcall Subtract(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Subtract(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a - b;
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
    mathinline T mathcall Multiply(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a * b;
    }

    template <typename T>
    mathinline T mathcall Reciprocal(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Reciprocal(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return T(1) / v;
    }

    template <typename T>
    mathinline T mathcall Divide(T a, T b) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Divide(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a / b;
    }

    // (a * b) + c
    template <typename T>
    mathinline T mathcall MultiplyAdd(T a, T b, T c) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall MultiplyAdd(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a * b) + c;
    }

    // (a * b) - c
    template <typename T>
    mathinline T mathcall MultiplySubtract(T a, T b, T c) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall MultiplySubtract(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a * b) - c;
    }

    // -(a * b) + c
    template <typename T>
    mathinline T mathcall NegateMultiplyAdd(T a, T b, T c) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall NegateMultiplyAdd(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return -(a * b) + c;
    }

    // -(a * b) - c
    template <typename T>
    mathinline T mathcall NegateMultiplySubtract(T a, T b, T c) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall NegateMultiplySubtract(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return -(a * b) - c;
    }

    template <typename T>
    mathinline T mathcall Square(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall Square(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v * v;
    }

    template <typename T>
    mathinline T mathcall SignedSquare(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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
    mathinline T mathcall SignedSquare(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v * fabs(v);
    }

    template <typename T>
    mathinline T mathcall Cube(T v) noexcept
        requires(Impl::IsSimdFloat4<T>)
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

    template <typename T>
    mathinline T mathcall Cube(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v * v * v;
    }
}
