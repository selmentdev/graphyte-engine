#pragma once

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
