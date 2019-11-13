#include "Test.Maths.pch.hxx"

// Simd Types
struct Vec4F
{
    __m128 v;
    using IsVectorType = void;
    using IsFloatType = void;
};

struct Vec4D
{
    __m256d v;
    using IsVectorType = void;
    using IsDoubleType = void;
};

// Type Traits
template <typename T, typename = void>
constexpr bool IsVectorType = false;

template <typename T>
constexpr bool IsVectorType<T, std::void_t<typename T::IsVectorType>> = true;

template <typename T, typename = void>
constexpr bool IsFloatType = false;

template <typename T>
constexpr bool IsFloatType<T, std::void_t<typename T::IsFloatType>> = true;

template <typename T, typename = void>
constexpr bool IsDoubleType = false;

template <typename T>
constexpr bool IsDoubleType<T, std::void_t<typename T::IsDoubleType>> = true;

// Concepts
template <typename T>
concept VectorType = IsVectorType<T>;

template <typename T>
concept SimdVectorFloat4Type = IsVectorType<T> && IsFloatType<T>;

template <typename T>
concept SimdVectorDouble4Type = IsVectorType<T> && IsDoubleType<T>;

// Trait Implementation - kinda Rusty :)
template <typename T>
T MulAdd(T a, T b, T c) requires(SimdVectorFloat4Type<T>)
{
    return { _mm_fmadd_ps(a.v, b.v, c.v) };
}

template <typename T>
T MulAdd(T a, T b, T c) requires(SimdVectorDouble4Type<T>)
{
    return { _mm256_fmadd_pd(a.v, b.v, c.v) };
}

template <typename T>
T MulAdd(T a, T b, T c)
{
    return (a * b) + c;
}

template <typename T>
bool operator==(T a, T b) noexcept requires(SimdVectorFloat4Type<T>)
{
    return _mm_movemask_ps(_mm_cmpeq_ps(a.v, b.v)) == 0b1111;
}

template <typename T>
bool operator==(T a, T b) noexcept requires(SimdVectorDouble4Type<T>)
{
    return _mm256_movemask_pd(_mm256_cmp_pd(a.v, b.v, _CMP_EQ_OQ)) == 0b1111;
}

// <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3

// vfmadd132ss
float f(float a, float b, float c)
{
    return MulAdd(a, b, c);
}
// vfmadd132sd
double f(double a, double b, double c)
{
    return MulAdd(a, b, c);
}
// vfmadd132ps
Vec4F f(Vec4F a, Vec4F b, Vec4F c)
{
    return MulAdd(a, b, c);
}
// vfmadd132pd
Vec4D f(Vec4D a, Vec4D b, Vec4D c)
{
    return MulAdd(a, b, c);
}

TEST_CASE("ff")
{
    REQUIRE(f(float{}, float{}, float{}) == float{});
    REQUIRE(f(double{}, double{}, double{}) == double{});
    REQUIRE(f(Vec4F{}, Vec4F{}, Vec4F{}) == Vec4F{});
    REQUIRE(f(Vec4D{}, Vec4D{}, Vec4D{}) == Vec4D{});
}
