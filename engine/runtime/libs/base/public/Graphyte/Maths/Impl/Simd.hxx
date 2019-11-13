#pragma once
#include <Graphyte/Base.module.hxx>

// =================================================================================================
//
// AVX support headers.
//

#if GRAPHYTE_HW_AVX
#include <xmmintrin.h>
#include <emmintrin.h>
#endif

// =================================================================================================
//
// ARM64 NEON support headers.
//

#if GRAPHYTE_HW_NEON && GRAPHYTE_COMPILER_MSVC
#if defined(_M_ARM)
#include <arm_neon.h>
#elif defined(_M_ARM64)
#include <arm64_neon.h>
#endif
#endif


// =================================================================================================
//
// `mathcall` definition
//

#if GRAPHYTE_HAVE_VECTORCALL
#define mathcall __vectorcall
#elif GRAPHYTE_COMPILER_MSVC
#define mathcall __fastcall
#else
#define mathcall
#endif


// =================================================================================================
//
// `mathinline` and `mathconst` definitions
//

#if GRAPHYTE_COMPILER_MSVC
#define mathinline __forceinline
// XXX: Check when we may make it `constexpr const` instead
#define mathconst extern const __declspec(selectany)
#elif GRAPHYTE_COMPILER_CLANG
#define mathinline inline __attribute__((__always_inline__)) 
#define mathconst constexpr const
#else
#define mathinline inline __attribute__((__artificial__, __always_inline__)) 
#define mathconst constexpr const
#endif

// =================================================================================================
//
// Native vector type.
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct VectorFloat4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
#elif GRAPHYTE_HW_NEON
    using VectorFloat4 = float32x4_t;
#elif GRAPHYTE_HW_AVX
    using VectorFloat4 = __m128;
#else
#error Unknown architecture
#endif
}


// =================================================================================================
//
// Native dual vector type
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct VectorFloat4x2 final
#else
    struct alignas(16) VectorFloat4x2 final
#endif
    {
    public:
#if GRAPHYTE_MATH_NO_INTRINSICS
        union
        {
            struct
            {
                VectorFloat4 R;
                VectorFloat4 D;
            };
            struct
            {
                float RX, RY, RZ, RW;
                float DX, DY, DZ, DW;
            };
            float M[2][4];
        };
#else
        VectorFloat4 R;
        VectorFloat4 D;
#endif
    };
}



// =================================================================================================
//
// Native matrix type
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct MatrixFloat4x4 final
#else
    struct alignas(16) MatrixFloat4x4 final
#endif
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        union
        {
            VectorFloat4 R[4];
            struct
            {
                float M11, M12, M13, M14;
                float M21, M22, M23, M24;
                float M31, M32, M33, M34;
                float M41, M42, M43, M44;
            };
            float M[4][4];
            float F[16];
        };
#else
        VectorFloat4 R[4];
#endif
    };
}

// =================================================================================================
//
// Type traits
//


namespace Graphyte::Maths::Impl
{
    // SIMD Vector
    // supports vector operations
    template <typename T, typename = void>
    constexpr bool IsSimdVector = false;

    template <typename T>
    constexpr bool IsSimdVector<T, std::void_t<typename T::IsSimdVector>> = true;


    // SIMD Dual Vector
    // supports dual vector operations
    template <typename T, typename = void>
    constexpr bool IsSimdDualVector = false;

    template <typename T>
    constexpr bool IsSimdDualVector<T, std::void_t<typename T::IsSimdDualVector>> = true;

    // SIMD Matrix
    // supports matrix operations
    template <typename T, typename = void>
    constexpr bool IsSimdMatrix = false;

    template <typename T>
    constexpr bool IsSimdMatrix<T, std::void_t<typename T::IsSimdMatrix>> = true;

    // SIMD Mask Value
    // supports bitwise masking operations
    template <typename T, typename = void>
    constexpr bool IsSimdMask = false;

    template <typename T>
    constexpr bool IsSimdMask<T, std::void_t<typename T::IsSimdMask>> = true;

    // SIMD Equal Comparable
    // supports `==` and `!= ` comparison operations
    template <typename T, typename = void>
    constexpr bool IsSimdEqualComparable = false;

    template <typename T>
    constexpr bool IsSimdEqualComparable<T, std::void_t<typename T::IsSimdEqualComparable>> = true;

    // SIMD Order Comparable:
    // supports `<`, `<=`, `>`, `>=` comparison operations.
    template <typename T, typename = void>
    constexpr bool IsSimdOrderComparable = false;

    template <typename T>
    constexpr bool IsSimdOrderComparable<T, std::void_t<typename T::IsSimdOrderComparable>> = true;

    // Concepts qualification:
    // vector + equal + order -> algebraic
    // mask + equal ->  bool masks
    // matrix + equal -> matrices
    // color + equal -> color spaces
    // plane + equal -> geometric
    // sphere + equal -> geometric


    // types:
    // Bool4: mask + equal
    // Bool3: mask + equal
    // Bool2: mask + equal
    // Vec4: vector + equal + order
    // Vec3: vector + equal + order
    // Vec2: vector + equal + order
    // Quat: equal + order
    // Matrix: matrix + equal
    // Color: color + equal
    // Plane: geometric + equal + components==4
    // Sphere: geometric + equal + components==4
    // Ray:
    // DualVector:
    // DualQuaternion:
}


// =================================================================================================
//
// Concepts
//

namespace Graphyte::Maths
{
    template <typename T>
    concept SimdVectorType = Maths::Impl::IsSimdVector<T>;

    template <typename T>
    concept SimdDualVectorType = Maths::Impl::IsSimdDualVector<T>;

    template <typename T>
    concept SimdVectorMatrixType = Maths::Impl::IsSimdMatrix<T>;

    template <typename T>
    concept SimdMaskType = Maths::Impl::IsSimdMask<T>;

    template <typename T>
    concept SimdVectorMaskable = Maths::Impl::IsSimdVector<T>
        and Maths::Impl::IsSimdMask<typename T::MaskType>;

    template <typename T>
    concept SimdEqualComparable = Maths::Impl::IsSimdEqualComparable<T>;

    template <typename T>
    concept SimdOrderComparable = Maths::Impl::IsSimdOrderComparable<T>;

    template <typename T>
    concept SimdComparable = Maths::Impl::IsSimdOrderComparable<T>
        and Maths::Impl::IsSimdEqualComparable<T>;

    template <typename T>
    concept SimdAlgebraicVector = Maths::Impl::IsSimdVector<T>
        and (T::Components > 1)
        and (T::Compoennts <= 4);
}

// =================================================================================================
//
// Constant types
//

namespace Graphyte::Maths::Impl
{
    struct alignas(16) Vec4F32 final
    {
        union
        {
            alignas(16) float F[4];
            VectorFloat4 V;
        };
    };

    static_assert(std::is_pod_v<Vec4F32>);

    struct alignas(16) Vec4S32 final
    {
        union
        {
            alignas(16) int32_t I[4];
            VectorFloat4 V;
        };
    };
    static_assert(std::is_pod_v<Vec4S32>);

    struct alignas(16) Vec4U32 final
    {
        union
        {
            alignas(16) uint32_t U[4];
            VectorFloat4 V;
        };
    };
    static_assert(std::is_pod_v<Vec4U32>);

    struct alignas(16) Vec16U8 final
    {
        union
        {
            alignas(16) uint8_t U[16];
            VectorFloat4 V;
        };
    };
    static_assert(std::is_pod_v<Vec16U8>);
}


// =================================================================================================
//
// Common enum types
//

namespace Graphyte::Maths
{
    enum class SelectMask : uint32_t
    {
        Select0 = UINT32_C(0x00000000),
        Select1 = UINT32_C(0xffffffff),
    };

    enum class InsertMask : uint8_t
    {
        _0000 = 0b0000,
        _0001 = 0b0001,
        _0010 = 0b0010,
        _0011 = 0b0011,
        _0100 = 0b0100,
        _0101 = 0b0101,
        _0110 = 0b0110,
        _0111 = 0b0111,
        _1000 = 0b1000,
        _1001 = 0b1001,
        _1010 = 0b1010,
        _1011 = 0b1011,
        _1100 = 0b1100,
        _1101 = 0b1101,
        _1110 = 0b1110,
        _1111 = 0b1111,
    };

    enum class SwizzleMask
    {
        XXXX, YXXX, ZXXX, WXXX,
        XYXX, YYXX, ZYXX, WYXX,
        XZXX, YZXX, ZZXX, WZXX,
        XWXX, YWXX, ZWXX, WWXX,
        XXYX, YXYX, ZXYX, WXYX,
        XYYX, YYYX, ZYYX, WYYX,
        XZYX, YZYX, ZZYX, WZYX,
        XWYX, YWYX, ZWYX, WWYX,
        XXZX, YXZX, ZXZX, WXZX,
        XYZX, YYZX, ZYZX, WYZX,
        XZZX, YZZX, ZZZX, WZZX,
        XWZX, YWZX, ZWZX, WWZX,
        XXWX, YXWX, ZXWX, WXWX,
        XYWX, YYWX, ZYWX, WYWX,
        XZWX, YZWX, ZZWX, WZWX,
        XWWX, YWWX, ZWWX, WWWX,

        XXXY, YXXY, ZXXY, WXXY,
        XYXY, YYXY, ZYXY, WYXY,
        XZXY, YZXY, ZZXY, WZXY,
        XWXY, YWXY, ZWXY, WWXY,
        XXYY, YXYY, ZXYY, WXYY,
        XYYY, YYYY, ZYYY, WYYY,
        XZYY, YZYY, ZZYY, WZYY,
        XWYY, YWYY, ZWYY, WWYY,
        XXZY, YXZY, ZXZY, WXZY,
        XYZY, YYZY, ZYZY, WYZY,
        XZZY, YZZY, ZZZY, WZZY,
        XWZY, YWZY, ZWZY, WWZY,
        XXWY, YXWY, ZXWY, WXWY,
        XYWY, YYWY, ZYWY, WYWY,
        XZWY, YZWY, ZZWY, WZWY,
        XWWY, YWWY, ZWWY, WWWY,

        XXXZ, YXXZ, ZXXZ, WXXZ,
        XYXZ, YYXZ, ZYXZ, WYXZ,
        XZXZ, YZXZ, ZZXZ, WZXZ,
        XWXZ, YWXZ, ZWXZ, WWXZ,
        XXYZ, YXYZ, ZXYZ, WXYZ,
        XYYZ, YYYZ, ZYYZ, WYYZ,
        XZYZ, YZYZ, ZZYZ, WZYZ,
        XWYZ, YWYZ, ZWYZ, WWYZ,
        XXZZ, YXZZ, ZXZZ, WXZZ,
        XYZZ, YYZZ, ZYZZ, WYZZ,
        XZZZ, YZZZ, ZZZZ, WZZZ,
        XWZZ, YWZZ, ZWZZ, WWZZ,
        XXWZ, YXWZ, ZXWZ, WXWZ,
        XYWZ, YYWZ, ZYWZ, WYWZ,
        XZWZ, YZWZ, ZZWZ, WZWZ,
        XWWZ, YWWZ, ZWWZ, WWWZ,

        XXXW, YXXW, ZXXW, WXXW,
        XYXW, YYXW, ZYXW, WYXW,
        XZXW, YZXW, ZZXW, WZXW,
        XWXW, YWXW, ZWXW, WWXW,
        XXYW, YXYW, ZXYW, WXYW,
        XYYW, YYYW, ZYYW, WYYW,
        XZYW, YZYW, ZZYW, WZYW,
        XWYW, YWYW, ZWYW, WWYW,
        XXZW, YXZW, ZXZW, WXZW,
        XYZW, YYZW, ZYZW, WYZW,
        XZZW, YZZW, ZZZW, WZZW,
        XWZW, YWZW, ZWZW, WWZW,
        XXWW, YXWW, ZXWW, WXWW,
        XYWW, YYWW, ZYWW, WYWW,
        XZWW, YZWW, ZZWW, WZWW,
        XWWW, YWWW, ZWWW, WWWW,
    };

    constexpr const uint32_t PERMUTE_0X = 0;
    constexpr const uint32_t PERMUTE_0Y = 1;
    constexpr const uint32_t PERMUTE_0Z = 2;
    constexpr const uint32_t PERMUTE_0W = 3;
    constexpr const uint32_t PERMUTE_1X = 4;
    constexpr const uint32_t PERMUTE_1Y = 5;
    constexpr const uint32_t PERMUTE_1Z = 6;
    constexpr const uint32_t PERMUTE_1W = 7;
}
