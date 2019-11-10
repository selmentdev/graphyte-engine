#pragma once
#include <Graphyte/Base.module.hxx>
#include <Graphyte/Maths2/Impl/Simd.hxx>

#if GRAPHYTE_HW_AVX
#if GRAPHYTE_HW_AVX
#   define sse_sfence()
#else
#   define sse_sfence() _mm_sfence()
#endif

#if GRAPHYTE_HW_FMA4
#   define fma_madd_ps(v1, v2, v3)          _mm_macc_ps(v1, v2, v3)
#   define fma_nmadd_ps(v1, v2, v3)         _mm_nmacc_ps(v1, v2, v3)
#elif GRAPHYTE_HW_FMA3
#   define fma_madd_ps(v1, v2, v3)          _mm_fmadd_ps(v1, v2, v3)
#   define fma_nmadd_ps(v1, v2, v3)         _mm_fnmadd_ps(v1, v2, v3)
#endif

#define sse_unpack_3to4(l1,l2,l3) \
    auto V3 = _mm_shuffle_ps(l2,l3,_MM_SHUFFLE(0,0,3,2));\
    auto V2 = _mm_shuffle_ps(l2,l1,_MM_SHUFFLE(3,3,1,0));\
    V2 = _mm_permute_ps(V2,_MM_SHUFFLE(1,1,0,2));\
    auto V4 = _mm_castsi128_ps( _mm_srli_si128(_mm_castps_si128(L3),32/8) );

#define sse_unpack_4to3(v2x) \
    v2x = _mm_shuffle_ps(V2,V3,_MM_SHUFFLE(1,0,2,1));\
    V2 = _mm_shuffle_ps(V2,V1,_MM_SHUFFLE(2,2,0,0));\
    V1 = _mm_shuffle_ps(V1,V2,_MM_SHUFFLE(0,2,1,0));\
    V3 = _mm_shuffle_ps(V3,V4,_MM_SHUFFLE(0,0,2,2));\
    V3 = _mm_shuffle_ps(V3,V4,_MM_SHUFFLE(2,1,2,0));\

#elif GRAPHYTE_HW_NEON
#if defined(_MSC_VER) && (_MSC_FULL_VER != 170051221) && (_MSC_FULL_VER < 170065500)
#   define neon_vmulq_n_f32( a, b ) vmulq_f32( (a), vdupq_n_f32( (b) ) )
#   define neon_vmlaq_n_f32( a, b, c ) vmlaq_f32( (a), (b), vdupq_n_f32( (c) ) )
#   define neon_vmuLq_lane_f32( a, b, c ) vmulq_f32( (a), vdupq_lane_f32( (b), (c) ) )
#   define neon_vmlAq_lane_f32( a, b, c, d ) vmlaq_f32( (a), (b), vdupq_lane_f32( (c), (d) ) )
#else
#   define neon_vmulq_n_f32( a, b ) vmulq_n_f32( (a), (b) )
#   define neon_vmlaq_n_f32( a, b, c ) vmlaq_n_f32( (a), (b), (c) )
#   define neon_vmulq_lane_f32( a, b, c ) vmulq_lane_f32( (a), (b), (c) )
#   define neon_vmlaq_lane_f32( a, b, c, d ) vmlaq_lane_f32( (a), (b), (c), (d) )
#endif
#endif

namespace Graphyte::Maths
{
    //
    // Vector type
    //
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

    //
    // Dual vector type
    //
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct VectorFloat8 final
#else
    struct alignas(16) VectorFloat8 final
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

    //
    // Matrix type
    //
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct MatrixFloat4x4 final
#else
    struct alignas(16) MatrixFloat4x4 final
#endif
    {
    public:
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

    public:
        MatrixFloat4x4() noexcept = default;
        constexpr MatrixFloat4x4(VectorFloat4 r0, VectorFloat4 r1, VectorFloat4 r2, VectorFloat4 r3)
            : R{ r0, r1, r2, r3 }
        {
        }
        MatrixFloat4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44) noexcept;
        explicit MatrixFloat4x4(const float* components) noexcept;
    };
    static_assert(std::is_pod_v<MatrixFloat4x4> == true);
}


namespace Graphyte::Maths::Detail
{
    //
    // Constant types.
    //
    struct alignas(16) Vector4F32 final
    {
    public:
        union
        {
            float F[4];
            VectorFloat4 V;
        };
    public:
        mathinline mathcall operator VectorFloat4() const noexcept
        {
            return V;
        }
        mathinline mathcall operator float const*() const noexcept
        {
            return F;
        }

    public:
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_AVX
        mathinline __m128i mathcall ToM128I() const noexcept
        {
            return _mm_castps_si128(V);
        }
        mathinline __m128d mathcall ToM128D() const noexcept
        {
            return _mm_castps_pd(V);
        }
#endif
    };
    static_assert(std::is_pod_v<Vector4F32> == true);

    struct alignas(16) Vector4S32 final
    {
    public:
        union
        {
            int32_t I[4];
            VectorFloat4 V;
        };

    public:
        mathinline mathcall operator VectorFloat4() const noexcept
        {
            return V;
        }
        mathinline mathcall operator int32_t const*() const noexcept
        {
            return I;
        }

    public:
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_AVX
        mathinline __m128i mathcall ToM128I() const noexcept
        {
            return _mm_castps_si128(V);
        }
        mathinline __m128d mathcall ToM128D() const noexcept
        {
            return _mm_castps_pd(V);
        }
#endif
    };
    static_assert(std::is_pod_v<Vector4S32> == true);

    struct alignas(16) Vector4U32 final
    {
    public:
        union
        {
            uint32_t U[4];
            VectorFloat4 V;
        };

    public:
        mathinline mathcall operator VectorFloat4() const noexcept
        {
            return V;
        }
        mathinline mathcall operator uint32_t const*() const noexcept
        {
            return U;
        }

    public:
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_AVX
        mathinline __m128i mathcall ToM128I() const noexcept
        {
            return _mm_castps_si128(V);
        }
        mathinline __m128d mathcall ToM128D() const noexcept
        {
            return _mm_castps_pd(V);
        }
#endif
    };
    static_assert(std::is_pod_v<Vector4U32> == true);

    struct alignas(16) Vector16U8 final
    {
    public:
        union
        {
            uint8_t U[16];
            VectorFloat4 V;
        };

    public:
        mathinline mathcall operator VectorFloat4() const noexcept
        {
            return V;
        }
        mathinline mathcall operator uint8_t const*() const noexcept
        {
            return U;
        }

    public:
#if !GRAPHYTE_MATH_NO_INTRINSICS && GRAPHYTE_HW_AVX
        mathinline __m128i mathcall ToM128I() const noexcept
        {
            return _mm_castps_si128(V);
        }
        mathinline __m128d mathcall ToM128D() const noexcept
        {
            return _mm_castps_pd(V);
        }
#endif
    };
    static_assert(std::is_pod_v<Vector16U8> == true);
}

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
