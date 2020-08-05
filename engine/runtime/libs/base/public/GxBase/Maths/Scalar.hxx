#pragma once
#include <GxBase/Maths/Base.hxx>
#include <GxBase/Maths/Constants.hxx>
#include <GxBase/Ieee754.hxx>


// =================================================================================================
// Scalar constants

namespace Graphyte::Maths
{
    template <typename T>
    constexpr T mathcall E() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_E<T>;
    }

    template <typename T>
    constexpr T mathcall Log2E() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Log2E<T>;
    }

    template <typename T>
    constexpr T mathcall Log10E() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Log10E<T>;
    }

    template <typename T>
    constexpr T mathcall Ln2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Ln2<T>;
    }

    template <typename T>
    constexpr T mathcall Ln10() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Ln10<T>;
    }

    template <typename T>
    constexpr T mathcall Pi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Pi<T>;
    }

    template <typename T>
    constexpr T mathcall Pi2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Pi2<T>;
    }

    template <typename T>
    constexpr T mathcall InvPi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvPi<T>;
    }

    template <typename T>
    constexpr T mathcall InvPi2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvPi2<T>;
    }

    template <typename T>
    constexpr T mathcall InvSqrtPi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrtPi<T>;
    }

    template <typename T>
    constexpr T mathcall Sqrt2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Sqrt2<T>;
    }

    template <typename T>
    constexpr T mathcall Sqrt3() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Sqrt3<T>;
    }

    template <typename T>
    constexpr T mathcall Sqrt5() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Sqrt5<T>;
    }

    template <typename T>
    constexpr T mathcall InvSqrt2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrt2<T>;
    }

    template <typename T>
    constexpr T mathcall InvSqrt3() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrt3<T>;
    }

    template <typename T>
    constexpr T mathcall InvSqrt5() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_InvSqrt5<T>;
    }

    template <typename T>
    constexpr T mathcall Phi() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Phi<T>;
    }

    template <typename T>
    constexpr T mathcall Gamma() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Gamma<T>;
    }

    template <typename T>
    constexpr T mathcall PiDiv2() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv2<T>;
    }

    template <typename T>
    constexpr T mathcall PiDiv3() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv3<T>;
    }

    template <typename T>
    constexpr T mathcall PiDiv4() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv4<T>;
    }

    template <typename T>
    constexpr T mathcall PiDiv6() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv6<T>;
    }

    template <typename T>
    constexpr T mathcall PiDiv8() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_PiDiv8<T>;
    }

    template <typename T>
    constexpr T mathcall EpsilonAngular() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_EpsilonAngular<T>;
    }

    template <typename T>
    constexpr T mathcall EpsilonLow() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_EpsilonLow<T>;
    }

    template <typename T>
    constexpr T mathcall Epsilon() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_Epsilon<T>;
    }

    template <typename T>
    constexpr T mathcall EpsilonHigh() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_EpsilonHigh<T>;
    }

    template <typename T>
    constexpr T mathcall RoundingError() noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Impl::g_Const_RoundingError<T>;
    }
}

// =================================================================================================
// Select/masking

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Select(T a, T b, T control) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (control >= 0) ? a : b;
    }
}


// =================================================================================================
// Bit specific functions

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall CopySign(T number, T sign) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return copysign(number, sign);
    }

    template <typename T>
    mathinline T mathcall Sign(T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const gt_zero = ((T(0.0) < x) ? T(1.0) : T(0.0));
        T const lt_zero = ((x < T(0.0)) ? T(1.0) : T(0.0));
        return gt_zero - lt_zero;
    }

    template <typename T>
    mathinline T mathcall NearbyInt(T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return nearbyint(x);
    }

    template <typename T>
    mathinline T mathcall NextToward(T value, T to) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return nexttoward(value, to);
    }

    template <typename T>
    mathinline T mathcall NextAfter(T value, T to) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return nextafter(value, to);
    }
}


// =================================================================================================
// Comparison

namespace Graphyte::Maths
{
    template <typename T>
    mathinline bool mathcall IsZero(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v == T(0.0);
    }

    template <typename T>
    mathinline bool mathcall IsZero(T v, T epsilon) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return fabs(v) <= epsilon;
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a == b);
    }

    template <typename T>
    mathinline bool mathcall IsEqual(T a, T b, T epsilon) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (fabs(a - b) <= epsilon);
    }

    template <typename T>
    mathinline bool mathcall IsNearEqual(T a, T b, int32_t tolerance) noexcept
        requires(std::is_floating_point_v<T>)
    {
        if (IsZero(a - b))
        {
            return true;
        }

        auto const ia = FloatTraits<T>::ToBits(a);
        auto const ib = FloatTraits<T>::ToBits(b);

        if ((ia < 0) != (ib < 0))
        {
            return false;
        }

        auto const ulp = abs(ia - ib);
        return ulp <= tolerance;
    }

    template <typename T>
    mathinline bool mathcall IsNearEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        static constexpr const int32_t tolerance{ 4 };
        return IsNearEqual<T>(a, b, tolerance);
    }

    template <typename T>
    mathinline bool mathcall IsNotEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a != b);
    }

    template <typename T>
    mathinline bool mathcall IsNearEqualSquared(T a, T b, T tolerance) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const diff         = (b - a);
        T const diff_sq      = diff * diff;
        T const tolerance_sq = tolerance * tolerance;

        return diff_sq <= tolerance_sq;
    }

    template <typename T>
    mathinline bool mathcall IsNearEqualSquared(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return IsNearEqualSquared(a, b, Epsilon<T>());
    }

    template <typename T>
    mathinline bool mathcall IsGreater(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return isgreater(a, b);
    }

    template <typename T>
    mathinline bool mathcall IsGreaterEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return isgreaterequal(a, b);
    }

    template <typename T>
    mathinline bool mathcall IsLess(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return isless(a, b);
    }

    template <typename T>
    mathinline bool mathcall IsLessEqual(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return islessequal(a, b);
    }

    template <typename T>
    mathinline bool mathcall IsLessGreater(T a, T b) noexcept
    {
        return islessgreater(a, b);
    }

    template <typename T>
    mathinline bool mathcall InBounds(T v, T bounds) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (-bounds <= v) && (v <= bounds);
    }

    template <typename T>
    mathinline bool mathcall InRange(T v, T min, T max) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (min <= v) && (v < max);
    }

    template <typename T>
    mathinline bool mathcall InRangeInclusive(T v, T min, T max) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (min <= v) && (v <= max);
    }

    template <typename T>
    mathinline bool mathcall IsNan(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return FloatTraits<T>::IsNan(v);
    }

    template <typename T>
    mathinline bool mathcall IsInfinity(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return FloatTraits<T>::IsInf(v);
    }

    template <typename T>
    mathinline bool mathcall IsNormal(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return isnormal(v);
    }

    template <typename T>
    mathinline bool mathcall IsUnordered(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return isunordered(a, b);
    }
}

// =================================================================================================
// Arithmetic

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Cos(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return cos(v);
    }

    template <typename T>
    mathinline T mathcall Sin(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return sin(v);
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
        requires(std::is_floating_point_v<T>)
    {
        return tan(v);
    }

    template <typename T>
    mathinline T mathcall Asin(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return asin(v);
    }

    template <typename T>
    mathinline T mathcall Acos(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return acos(v);
    }

    template <typename T>
    mathinline T mathcall Atan(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return atan(v);
    }

    template <typename T>
    mathinline T mathcall Atan2(T y, T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return atan2(y, x);
    }

    template <typename T>
    mathinline T mathcall Sinh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return sinh(v);
    }

    template <typename T>
    mathinline T mathcall Cosh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return cosh(v);
    }

    template <typename T>
    mathinline T mathcall Tanh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return tanh(v);
    }

    template <typename T>
    mathinline T mathcall Asinh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return asinh(v);
    }

    template <typename T>
    mathinline T mathcall Acosh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return acosh(v);
    }

    template <typename T>
    mathinline T mathcall Atanh(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return atanh(v);
    }

    template <typename T>
    mathinline T mathcall Log(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log(v);
    }

    template <typename T>
    mathinline T mathcall Log(T base, T value) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log(value) / log(base);
    }

    template <typename T>
    mathinline T mathcall Log10(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log10(v);
    }

    template <typename T>
    mathinline T mathcall Log2(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return log2(v);
    }

    template <typename T>
    mathinline T mathcall Exp(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return exp(v);
    }

    template <typename T>
    mathinline T mathcall Exp10(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return pow(T(10), v);
    }

    template <typename T>
    mathinline T mathcall Exp2(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return exp2(v);
    }

    template <typename T>
    mathinline T mathcall Power(T x, T y) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return pow(x, y);
    }

    template <typename T>
    mathinline T mathcall Power(T x, int y) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return pow(x, y);
    }

    template <typename T>
    mathinline T mathcall Hypot(T x, T y) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return hypot(x, y);
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
        requires(std::is_floating_point_v<T>)
    {
        return cbrt(v);
    }

    template <typename T>
    mathinline T mathcall InvCbrt(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return T(1) / cbrt(v);
    }

    template <typename T>
    mathinline T mathcall Abs(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return fabs(v);
    }

    template <typename T>
    mathinline T mathcall Negate(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return -v;
    }

    template <typename T>
    mathinline T mathcall Add(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a + b;
    }

    template <typename T>
    mathinline T mathcall Subtract(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a - b;
    }

    template <typename T>
    mathinline T mathcall Multiply(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a * b;
    }

    template <typename T>
    mathinline T mathcall Reciprocal(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return T(1) / v;
    }

    template <typename T>
    mathinline T mathcall Divide(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a / b;
    }

    template <typename T>
    mathinline T mathcall MultiplyAdd(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a * b) + c;
    }

    template <typename T>
    mathinline T mathcall MultiplySubtract(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a * b) - c;
    }

    template <typename T>
    mathinline T mathcall NegateMultiplyAdd(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return -(a * b) + c;
    }

    template <typename T>
    mathinline T mathcall NegateMultiplySubtract(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return -(a * b) - c;
    }

    template <typename T>
    mathinline T mathcall Square(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v * v;
    }

    template <typename T>
    mathinline T mathcall SignedSquare(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v * fabs(v);
    }

    template <typename T>
    mathinline T mathcall Cube(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return v * v * v;
    }
}


// =================================================================================================
// Interpolation

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Lerp(T a, T b, T t) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return a + (b - a) * t;
    }

    template <typename T>
    mathinline T mathcall LerpPrecise(T a, T b, T t) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return ((T(1) - t) * a) + (t * b);
    }

    template <typename T>
    mathinline T mathcall Hermite(T position0, T tangent0, T position1, T tangent1, T t) noexcept
        requires(std::is_floating_point_v<T>)
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
    mathinline T mathcall Barycentric(T a, T b, T c, T f, T g) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const pba    = b - a;
        T const pca    = c - a;
        T const accum  = (pba * f) + a;
        T const result = (pca * g) + accum;
        return result;
    }

    template <typename T>
    mathinline T mathcall CatmullRom(T p0, T p1, T p2, T p3, T t) noexcept
        requires(std::is_floating_point_v<T>)
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
        requires(std::is_floating_point_v<T>)
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
        requires(std::is_floating_point_v<T>)
    {
        T const base   = (value - min);
        T const range  = (max - min);
        T const result = (base / range);
        return result;
    }

    template <typename T>
    mathinline T mathcall Bezier(T a, T b, T c, T t) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const t2  = t * t;
        T const t1  = T(1.0) - t;
        T const t12 = t1 * t1;
        return (a * t12) + (T(2.0) * b * t1 * t) + (c * t2);
    }

    template <typename T>
    mathinline T mathcall Bezier(T a, T b, T c, T d, T t) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const t1  = T(1.0) - t;
        T const t13 = t1 * t1 * t1;
        T const t3  = t * t * t;

        return (t13 * a) + (T(3.0) * t * t1 * t1 * b) + (T(3.0) * t * t * t1 * c) + (t3 * d);
    }

    template <typename T>
    mathinline T mathcall Cubic(T a, T b, T c, T d, T t) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const t2 = t * t;
        T const a2 = (T(-0.5) * b) + (T(1.5) * a) - (T(1.5) * d) + (T(0.5) * c);
        T const a1 = b - (T(2.5) * a) + (T(2.0) * d) - (T(0.5) * c);
        T const a0 = (T(-0.5) * b) + (T(0.5) * d);

        T const result = (a2 * t * t2) + (a1 * t2) + (a0 * t) + a;
    }

    template <typename T>
    mathinline T mathcall SmoothStep(T a, T b, T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        float const t      = Saturate((x - a) / (b - a));
        float const result = t * (t * NegateMultiplyAdd(t, 2.0f, 3.0f));
        return result;
    }

    template <typename T>
    mathinline T mathcall Cosine(T a, T b, T t) noexcept
        requires(std::is_floating_point_v<T>)
    {
        float const t0 = (T(1.0) - Cos(t * Impl::g_Const_Pi<T>)) * T(0.5);
        return Lerp(a, b, t0);
    }

    template <typename T>
    mathinline T mathcall EaseSmoothC2(T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (x * x * x) * (x * ((x * T(6.0)) - T(15.0)) + T(10.0));
    }

    template <typename T>
    mathinline T mathcall Smooth(T min, T max, T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const xx     = (x - min) / (max - min);
        T const result = (xx * (xx * (T(3.0) - (T(2.0) * x))));
        return result;
    }

    template <typename T>
    mathinline T mathcall SmoothSquared(T min, T max, T x) noexcept
        requires(std::is_floating_point_v<T>)
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
        requires(std::is_floating_point_v<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const ox   = T(1.0) - x;
        T const oxox = ox * ox;
        T const xx   = T(1.0) - oxox;
        return Lerp<T>(min, max, xx);
    }

    template <typename T>
    mathinline T mathcall SmoothCubed(T min, T max, T x) noexcept
        requires(std::is_floating_point_v<T>)
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
        requires(std::is_floating_point_v<T>)
    {
        if (x <= min)
        {
            return min;
        }
        else if (x >= max)
        {
            return max;
        }

        T const ox     = T(1.0) - x;
        T const oxoxox = (ox * ox * ox);
        T const xx     = T(1.0) - oxoxox;
        return Lerp<T>(min, max, xx);
    }

    template <typename T>
    mathinline T mathcall Trapezoid(T a, T b, T c, T d, T t) noexcept
        requires(std::is_floating_point_v<T>)
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
        requires(std::is_floating_point_v<T>)
    {
        return Lerp<T>(min, max, Trapezoid(a, b, c, d, t));
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
}


// =================================================================================================
// Fixed point representation

namespace Graphyte::Maths
{
    template <typename T>
    constexpr T mathcall FixedToFixed(T value, size_t n, size_t p) noexcept
        requires(std::is_unsigned_v<T>)
    {
        if (n > p)
        {
            value >>= (n - p);
        }
        else if (n < p)
        {
            if (value == (static_cast<uint32_t>(1) << n) - 1)
            {
                value = static_cast<uint32_t>((1 << p) - 1);
            }
            else
            {
                value = static_cast<uint32_t>((value * (1 << p)) / ((1 << n) - 1));
            }
        }

        return value;
    }

    template <typename TFixed, typename TFloat>
    constexpr TFixed mathcall FloatToFixed(TFloat value, size_t bits) noexcept
        requires(std::is_unsigned_v<TFixed> && std::is_floating_point_v<TFloat>)
    {
        if (value <= TFloat(0.0))
        {
            return {};
        }
        else if (value >= TFloat(1.0))
        {
            return static_cast<TFixed>((1 << bits) - 1);
        }


        return static_cast<TFixed>(value * static_cast<TFloat>(TFixed{ 1 } << bits));
    }

    template <typename TFloat, typename TFixed>
    constexpr TFloat mathcall FixedToFloat(TFixed value, size_t bits) noexcept
        requires(std::is_unsigned_v<TFixed> && std::is_floating_point_v<TFloat>)
    {
        return static_cast<TFloat>(value) / static_cast<TFloat>((TFixed{ 1 } << bits) - 1);
    }
}


// =================================================================================================
// Common functions

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Gain(T value, T gain) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const g = -Log2(T(1.0) - gain);
        T const c = Power(value, gain);
        return c / (c + Power(T(1.0) - value, g));
    }

    template <typename T>
    mathinline T mathcall Bias(T value, T base) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Power(value, -Log2(base));
    }

    template <typename T>
    constexpr T mathcall Step(T value1, T value2) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (value1 <= value2)
            ? T(0.0)
            : T(1.0);
    }

    template <typename T>
    mathinline size_t QuadricEquation(T a, T b, T c, T& out_x1, T& out_x2) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const delta = (b * b) - (T(4) * a * c);

        if (delta < T(0))
        {
            out_x1 = out_x2 = std::numeric_limits<T>::infinity();
            return 0;
        }
        else if (IsZero(delta))
        {
            out_x1 = out_x2 = (-b / (T(2) * a));
            return 1;
        }

        T const denominator = T(1) / (T(2) * a);
        T const delta_sqrt = Sqrt(delta);

        out_x1 = (-b - delta_sqrt) * denominator;
        out_x2 = (-b + delta_sqrt) * denominator;

        return 2;
    }

    template <typename T>
    mathinline T mathcall SnapToGrid(T value, T grid) noexcept
        requires(std::is_floating_point_v<T>)
    {
        if (IsZero(grid))
        {
            return value;
        }
        else
        {
            return Floor((value + T(0.5) * grid) / grid) * grid;
        }
    }

    mathinline float mathcall WangHashNoise(uint32_t u, uint32_t v, uint32_t s) noexcept
    {
        uint32_t seed = (u * 1664525U + v) + s;

        seed = (seed ^ 61U) ^ (seed >> 16U);
        seed *= 9U;
        seed = seed ^ (seed >> 4U);
        seed *= 0x27d4eb2d;
        seed = seed ^ (seed >> 15U);

        float value = static_cast<float>(seed);
        value = static_cast<float>(static_cast<double>(value) * (1.0 / 4294967296.0));
        return value;
    }

    mathinline float mathcall WrapAngle(float value) noexcept
    {
        float const raw = value + Maths::Impl::g_Const_Pi<float>;
        float abs = Abs(raw);

        float const scaled = static_cast<float>(static_cast<int32_t>(abs / Impl::g_Const_Pi<float>));

        abs -= Impl::g_Const_Pi<float> * scaled;
        abs -= Impl::g_Const_Pi<float>;

        if (raw < 0.0f)
        {
            abs = -abs;
        }

        return abs;
    }

    template <typename T>
    mathinline T mathcall DiffAngle(T angle1, T angle2) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const r1 = angle2 - angle1;
        T const r2 = r1 - Impl::g_Const_Pi2<T>;
        T const r3 = r1 + Impl::g_Const_Pi2<T>;

        T const a1 = Abs(r1);
        T const a2 = Abs(r2);
        T const a3 = Abs(r3);

        if ((a1 < a2) && (a1 < a3))
        {
            return r1;
        }
        else if (a2 < a3)
        {
            return r2;
        }

        return r3;
    }
}


// =================================================================================================
// Rounding functions

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Ceiling(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return ceil(v);
    }

    template <typename T>
    mathinline T mathcall Floor(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return floor(v);
    }

    template <typename T>
    mathinline T mathcall Truncate(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return trunc(v);
    }

    template <typename T>
    mathinline T mathcall Round(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return round(v);
    }

    template <typename T>
    mathinline T mathcall Remainder(T x, T y) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return fmod(x, y);
    }

    template <typename T>
    mathinline T mathcall Fraction(T x) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return x - Floor(x);
    }

    template <typename T>
    mathinline T mathcall Min(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
    mathinline T mathcall Min(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Min(Min(a, b), c);
    }

    template <typename T>
    mathinline T mathcall Min(T a, T b, T c, T d) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Min(Min(a, b), Min(c, d));
    }

    template <typename T>
    mathinline T mathcall Max(T a, T b) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    mathinline T mathcall Max(T a, T b, T c) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Min(Min(a, b), c);
    }

    template <typename T>
    mathinline T mathcall Max(T a, T b, T c, T d) noexcept
        requires(std::is_floating_point_v<T>)
    {
        return Min(Min(a, b), Min(c, d));
    }

    template <typename T>
    mathinline T mathcall Clamp(T v, T min, T max) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const below = Max(min, v);
        T const result = Min(max, below);
        return result;
    }

    template <typename T>
    mathinline T mathcall ClampRoll(T v, T min, T max) noexcept
        requires(std::is_floating_point_v<T>)
    {
        if (v > max)
        {
            return min;
        }
        else if (v < min)
        {

            return max;
        }

        return v;
    }

    template <typename T>
    mathinline T mathcall Saturate(T v) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const below = Max(T(0.0), v);
        T const result = Min(T(1.0), below);
        return result;
    }

    template <typename T>
    mathinline T mathcall Wrap(T v, T min, T max) noexcept
        requires(std::is_floating_point_v<T>)
    {
        T const range = (max - min);
        T const progress = (v - min);
        return min + progress + (range * floorf(progress / range));
    }
}
