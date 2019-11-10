#pragma once
#include <Graphyte/Maths2/Types.hxx>

namespace Graphyte::Maths
{
    template <typename T> constexpr const T PI = T(3.14159265358979323846264338327950288419716939937510);
    template <typename T> constexpr const T PI2 = T(6.28318530717958647692528676655900576839433879875021);
    template <typename T> constexpr const T ONE_OVER_PI = T(0.31830988618379067153776752674502872406891929148091);
    template <typename T> constexpr const T ONE_OVER_PI2 = T(0.15915494309189533576888376337251436203445964574046);
    template <typename T> constexpr const T PI_OVER_2 = T(1.57079632679489661923132169163975144209858469968755);
    template <typename T> constexpr const T PI_OVER_3 = T(1.04719755119659774615421446109316762806572313312504);
    template <typename T> constexpr const T PI_OVER_4 = T(0.78539816339744830961566084581987572104929234984378);
    template <typename T> constexpr const T PI_OVER_6 = T(0.52359877559829887307710723054658381403286156656252);
    template <typename T> constexpr const T PI_OVER_8 = T(0.39269908169872415480783042290993786052464617492189);
    template <typename T> constexpr const T E = T(2.71828182845904523536028747135266249775724709369996);
    template <typename T> constexpr const T LOG_2_E = T(1.44269504088896340735992468100189213742664595415299);
    template <typename T> constexpr const T LOG_10_E = T(0.43429448190325182765112891891660508229439700580367);
    template <typename T> constexpr const T LN_2 = T(0.69314718055994530941723212145817656807550013436026);
    template <typename T> constexpr const T LN_10 = T(2.30258509299404568401799145468436420760110148862877);
    template <typename T> constexpr const T ONE_OVER_LN_2 = T(1.44269504088896340735992468100189213742664595415299);
    template <typename T> constexpr const T PHI = T(1.61803398874989484820458683436563811772030917980576);
    template <typename T> constexpr const T GAMMA = T(0.57721566490153286060651209008240243104215933593992);
    template <typename T> constexpr const T SQRT_OF_2 = T(1.41421356237309504880168872420969807856967187537695);
    template <typename T> constexpr const T SQRT_OF_3 = T(1.73205080756887729352744634150587236694280525381038);
    template <typename T> constexpr const T SQRT_OF_5 = T(2.23606797749978969640917366873127623544061835961153);
    template <typename T> constexpr const T ONE_OVER_SQRT_OF_2 = T(0.70710678118654752440084436210484903928483593768847);
    template <typename T> constexpr const T ONE_OVER_SQRT_OF_3 = T(0.57735026918962576450914878050195745564760175127013);
    template <typename T> constexpr const T ONE_OVER_SQRT_OF_5 = T(0.44721359549995793928183473374625524708812367192231);

    template <typename T> constexpr const T EPSILON_ANGULAR = T(0.001);
    template <typename T> constexpr const T EPSILON_LOW = T(0.0002);
    template <typename T> constexpr const T EPSILON = T(0.000035);
    template <typename T> constexpr const T EPSILON_HIGH = T(0.0000005);

    template <typename T> constexpr const T TAU = PI2<T>;

    constexpr const uint32_t ROUNDING_ERROR_U32 = UINT32_C(0);
    constexpr const uint64_t ROUNDING_ERROR_U64 = UINT64_C(0);
    constexpr const int32_t ROUNDING_ERROR_I32 = INT32_C(0);
    constexpr const int64_t ROUNDING_ERROR_I64 = INT64_C(0);
    constexpr const float ROUNDING_ERROR_F32 = 0.000001F;
    constexpr const double ROUNDING_ERROR_F64 = 0.00000001;

    constexpr const uint32_t SELECT_0 = 0x00000000U;
    constexpr const uint32_t SELECT_1 = 0xffffffffU;
    constexpr const size_t CACHE_LINE_SIZE = 64;
}

#include <Graphyte/Maths2/Impl/SimdConsts.hxx>

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall UnitX() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 1);
        return { Impl::VEC4_POSITIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall UnitY() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 2);
        return { Impl::VEC4_POSITIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall UnitZ() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 3);
        return { Impl::VEC4_POSITIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall UnitW() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 4);
        return { Impl::VEC4_POSITIVE_UNIT_W.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitX() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 1);
        return { Impl::VEC4_NEGATIVE_UNIT_X.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitY() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 2);
        return { Impl::VEC4_NEGATIVE_UNIT_Y.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitZ() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 3);
        return { Impl::VEC4_NEGATIVE_UNIT_Z.V };
    }

    template <typename T>
    mathinline T mathcall NegativeUnitW() noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 4);
        return { Impl::VEC4_NEGATIVE_UNIT_W.V };
    }

    template <typename T>
    mathinline T mathcall Zero() noexcept
    {
        static_assert(Impl::IsVector<T>);
#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_ZERO_4.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#endif
    }

    template <typename T>
    mathinline T mathcall One() noexcept
    {
        static_assert(Impl::IsVector<T>);

        return { Impl::VEC4_ONE_4.V };
    }

    template <typename T>
    mathinline T mathcall Infinity() noexcept
    {
        static_assert(Impl::IsVector<T>);

        return { Impl::VEC4_INFINITY.V };
    }

    template <typename T>
    mathinline T mathcall NaN() noexcept
    {
        static_assert(Impl::IsVector<T>);

        return { Impl::VEC4_QNAN.V };
    }

    template <typename T>
    mathinline T mathcall Epsilon() noexcept
    {
        static_assert(Impl::IsVector<T>);

        return { Impl::VEC4_EPSILON.V };
    }

    template <typename T>
    mathinline T mathcall SignMask() noexcept
    {
        static_assert(Impl::IsVector<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return { Impl::VEC4_NEGATIVE_ZERO.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set1_epi32(static_cast<int>(0x80000000));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }
}


//
// Common constructors.
//

namespace Graphyte::Maths
{
    template <typename T>
    mathinline T mathcall Make(float value) noexcept
    {
        static_assert(Impl::IsVector<T>);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y) noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 2);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, 0.0F, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, 0.0F, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z) noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components >= 3);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, z, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(0.0F, z, y, x) };
#endif
    }

    template <typename T>
    mathinline T mathcall Make(float x, float y, float z, float w) noexcept
    {
        static_assert(Impl::IsVector<T>);
        static_assert(T::Components == 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4F32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#endif
    }

    mathinline Vec4 mathcall MakeMask(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_epi32(static_cast<int32_t>(w), static_cast<int32_t>(z), static_cast<int32_t>(y), static_cast<int32_t>(x));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vec4 mathcall MakeMask(uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Impl::Vec4U32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        const auto v_temp = _mm_set1_epi32(static_cast<int32_t>(value));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }
}
