#pragma once
#include <GxBase/Base.module.hxx>
#include <GxBase/Diagnostics.hxx>
#include <GxBase/TypeTraits.hxx>
#include <GxBase/Ieee754.hxx>

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
#define mathconst  constexpr const
#else
#define mathinline inline __attribute__((__artificial__, __always_inline__))
#define mathconst  constexpr const
#endif


// =================================================================================================
//
// Native vector type.
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) NativeFloat32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
    struct alignas(16) NativeUInt32x4 final
    {
        union
        {
            float F[4];
            uint32_t U[4];
            int32_t I[4];
        };
    };
#elif GRAPHYTE_HW_NEON
    using NativeFloat32x4 = float32x4_t;
    using NativeUInt32x4  = uint32x4_t;
#elif GRAPHYTE_HW_AVX
    using NativeFloat32x4 = __m128;
    using NativeUInt32x4  = __m128i;
#else
#error Unknown architecture
#endif

    static_assert(alignof(NativeFloat32x4) == 16);
    static_assert(sizeof(NativeFloat32x4) == 16);

    static_assert(alignof(NativeUInt32x4) == 16);
    static_assert(sizeof(NativeUInt32x4) == 16);
}


// =================================================================================================
//
// Native matrix type
//

namespace Graphyte::Maths::Impl
{
#if GRAPHYTE_MATH_NO_INTRINSICS
    struct alignas(16) NativeFloat32x4x4 final
    {
        union
        {
            NativeFloat32x4 R[4];
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
    };

#else
    struct alignas(16) NativeFloat32x4x4 final
    {
        NativeFloat32x4 R[4];
    };
#endif

    static_assert(alignof(NativeFloat32x4x4) == 16);
    static_assert(sizeof(NativeFloat32x4x4) == 64);
}


// =================================================================================================
//
// Constant types
//

namespace Graphyte::Maths::Impl
{
    struct alignas(16) ConstFloat32x4 final
    {
        union
        {
            alignas(16) float F[4];
            NativeFloat32x4 V;
        };
    };

    static_assert(std::is_trivially_copyable_v<ConstFloat32x4>);
    static_assert(std::is_standard_layout_v<ConstFloat32x4>);
    static_assert(alignof(ConstFloat32x4) == 16);
    static_assert(sizeof(ConstFloat32x4) == 16);

    struct alignas(16) ConstInt32x4 final
    {
        union
        {
            alignas(16) int32_t I[4];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };

    static_assert(std::is_trivially_copyable_v<ConstInt32x4>);
    static_assert(std::is_standard_layout_v<ConstInt32x4>);
    static_assert(alignof(ConstInt32x4) == 16);
    static_assert(sizeof(ConstInt32x4) == 16);

    struct alignas(16) ConstUInt32x4 final
    {
        union
        {
            alignas(16) uint32_t U[4];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };
    static_assert(std::is_trivially_copyable_v<ConstUInt32x4>);
    static_assert(std::is_standard_layout_v<ConstUInt32x4>);
    static_assert(alignof(ConstUInt32x4) == 16);
    static_assert(sizeof(ConstUInt32x4) == 16);

    struct alignas(16) ConstUInt8x16 final
    {
        union
        {
            alignas(16) uint8_t U[16];
            NativeFloat32x4 V;
            NativeUInt32x4 UV;
        };
    };
    static_assert(std::is_trivially_copyable_v<ConstUInt8x16>);
    static_assert(std::is_standard_layout_v<ConstUInt8x16>);
    static_assert(alignof(ConstUInt8x16) == 16);
    static_assert(sizeof(ConstUInt8x16) == 16);
}


// =================================================================================================
//
// Include some internal specific implementation details.
//

#if !GRAPHYTE_MATH_NO_INTRINSICS
#if GRAPHYTE_HW_AVX
#include <GxBase/Maths/Impl/Avx.impl.hxx>
#elif GRAPHYTE_HW_NEON
#include <GxBase/Maths/Impl/Neon.impl.hxx>
#endif
#endif


// =================================================================================================
//
// Concepts
//

namespace Graphyte::Maths::Impl
{
    template <typename T, typename = std::void_t<T::IsSimdFloat4>>
    inline constexpr bool IsSimdFloat4 = false;

    template <typename T>
    inline constexpr bool IsSimdFloat4<T, void> = true;

    template <typename T, typename = std::void_t<T::IsSimdUInt4>>
    inline constexpr bool IsSimdUInt4 = false;

    template <typename T>
    inline constexpr bool IsSimdUInt4<T, void> = true;

    template <typename T, typename = std::void_t<T::IsVector>>
    inline constexpr bool IsVector = false;

    template <typename T>
    inline constexpr bool IsVector<T, void> = true;
}


// =================================================================================================
//
// Standard math types
//

namespace Graphyte::Maths
{
    struct Bool4 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 4;

        using ComponentType = uint32_t;
        using MaskType = Bool4;
    };

    struct Bool3 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 3;

        using ComponentType = uint32_t;
        using MaskType = Bool3;
    };

    struct Bool2 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 2;

        using ComponentType = uint32_t;
        using MaskType = Bool2;
    };

    struct Bool1 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdUInt4 = void;

        static constexpr const size_t Components = 1;

        using ComponentType = uint32_t;
        using MaskType = Bool1;
    };

    struct Vector4 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector = void;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Vector3 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector = void;

        static constexpr const size_t Components = 3;

        using ComponentType = float;
        using MaskType = Bool3;
    };

    struct Vector2 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector = void;

        static constexpr const size_t Components = 2;

        using ComponentType = float;
        using MaskType = Bool2;
    };

    struct Vector1 final
    {
        Impl::NativeFloat32x4 V;

        using IsSimdFloat4 = void;
        using IsVector = void;

        static constexpr const size_t Components = 1;

        using ComponentType = float;
        using MaskType = Bool1;
    };

    struct Color final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Matrix final
    {
        Impl::NativeFloat32x4x4 M;

        static constexpr const size_t Components = 16;
        static constexpr const size_t Rows = 4;
        static constexpr const size_t Columns = 4;

        using ComponentType = float;
    };

    struct Plane final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Quaternion final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType = Bool4;
    };

    struct Sphere final
    {
        Impl::NativeFloat32x4 V;

        static constexpr const size_t Components = 4;

        using ComponentType = float;
        using MaskType = Bool4;
    };
}
