#pragma once
#include <Graphyte/Maths/Vector4.hxx>
#include <Graphyte/Maths/Constants.hxx>
#include <Graphyte/Maths/Scalar.hxx>
#include <Graphyte/Maths/Matrix.hxx>
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Diagnostics.hxx>
#include <Graphyte/Bitwise.hxx>
#include <Graphyte/Half.hxx>

namespace Graphyte::Maths::Simd
{
#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS

    mathinline __m128i mathcall simd_multi_sll_epi32(__m128i value, __m128i count) noexcept
    {
        auto v = _mm_shuffle_epi32(value, _MM_SHUFFLE(0, 0, 0, 0));
        auto c = _mm_shuffle_epi32(count, _MM_SHUFFLE(0, 0, 0, 0));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r0 = _mm_sll_epi32(v, c);

        v = _mm_shuffle_epi32(value, _MM_SHUFFLE(1, 1, 1, 1));
        c = _mm_shuffle_epi32(count, _MM_SHUFFLE(1, 1, 1, 1));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r1 = _mm_sll_epi32(v, c);

        v = _mm_shuffle_epi32(value, _MM_SHUFFLE(2, 2, 2, 2));
        c = _mm_shuffle_epi32(count, _MM_SHUFFLE(2, 2, 2, 2));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r2 = _mm_sll_epi32(v, c);

        v = _mm_shuffle_epi32(value, _MM_SHUFFLE(3, 3, 3, 3));
        c = _mm_shuffle_epi32(count, _MM_SHUFFLE(3, 3, 3, 3));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r3 = _mm_sll_epi32(v, c);

        auto r01 = _mm_shuffle_ps(_mm_castsi128_ps(r0), _mm_castsi128_ps(r1), _MM_SHUFFLE(0, 0, 0, 0));
        auto r23 = _mm_shuffle_ps(_mm_castsi128_ps(r2), _mm_castsi128_ps(r3), _MM_SHUFFLE(0, 0, 0, 0));
        auto result = _mm_shuffle_ps(r01, r23, _MM_SHUFFLE(2, 0, 2, 0));
        return _mm_castps_si128(result);
    }

    mathinline __m128i mathcall simd_multi_srl_epi32(__m128i value, __m128i count) noexcept
    {
        auto v = _mm_shuffle_epi32(value, _MM_SHUFFLE(0, 0, 0, 0));
        auto c = _mm_shuffle_epi32(count, _MM_SHUFFLE(0, 0, 0, 0));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r0 = _mm_srl_epi32(v, c);

        v = _mm_shuffle_epi32(value, _MM_SHUFFLE(1, 1, 1, 1));
        c = _mm_shuffle_epi32(count, _MM_SHUFFLE(1, 1, 1, 1));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r1 = _mm_srl_epi32(v, c);

        v = _mm_shuffle_epi32(value, _MM_SHUFFLE(2, 2, 2, 2));
        c = _mm_shuffle_epi32(count, _MM_SHUFFLE(2, 2, 2, 2));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r2 = _mm_srl_epi32(v, c);

        v = _mm_shuffle_epi32(value, _MM_SHUFFLE(3, 3, 3, 3));
        c = _mm_shuffle_epi32(count, _MM_SHUFFLE(3, 3, 3, 3));
        c = _mm_and_si128(c, Detail::VEC4_MASK_COMPONENT_X.ToM128I());
        auto r3 = _mm_srl_epi32(v, c);

        // (r0,r0,r1,r1)
        auto r01 = _mm_shuffle_ps(_mm_castsi128_ps(r0), _mm_castsi128_ps(r1), _MM_SHUFFLE(0, 0, 0, 0));
        // (r2,r2,r3,r3)
        auto r23 = _mm_shuffle_ps(_mm_castsi128_ps(r2), _mm_castsi128_ps(r3), _MM_SHUFFLE(0, 0, 0, 0));
        // (r0,r1,r2,r3)
        auto result = _mm_shuffle_ps(r01, r23, _MM_SHUFFLE(2, 0, 2, 0));
        return _mm_castps_si128(result);
    }

    mathinline __m128i mathcall GetLeadingBit(const __m128i value) noexcept
    {
        static const Detail::Vector4S32 g_XM0000FFFF = { { { 0x0000FFFF, 0x0000FFFF, 0x0000FFFF, 0x0000FFFF } } };
        static const Detail::Vector4S32 g_XM000000FF = { { { 0x000000FF, 0x000000FF, 0x000000FF, 0x000000FF } } };
        static const Detail::Vector4S32 g_XM0000000F = { { { 0x0000000F, 0x0000000F, 0x0000000F, 0x0000000F } } };
        static const Detail::Vector4S32 g_XM00000003 = { { { 0x00000003, 0x00000003, 0x00000003, 0x00000003 } } };

        __m128i v = value, r, c, b, s;

        c = _mm_cmpgt_epi32(v, g_XM0000FFFF.ToM128I());   // c = (v > 0xFFFF)
        b = _mm_srli_epi32(c, 31);              // b = (c ? 1 : 0)
        r = _mm_slli_epi32(b, 4);               // r = (b << 4)
        v = simd_multi_srl_epi32(v, r);         // v = (v >> r)

        c = _mm_cmpgt_epi32(v, g_XM000000FF.ToM128I());   // c = (v > 0xFF)
        b = _mm_srli_epi32(c, 31);              // b = (c ? 1 : 0)
        s = _mm_slli_epi32(b, 3);               // s = (b << 3)
        v = simd_multi_srl_epi32(v, s);         // v = (v >> s)
        r = _mm_or_si128(r, s);                 // r = (r | s)

        c = _mm_cmpgt_epi32(v, g_XM0000000F.ToM128I());   // c = (v > 0xF)
        b = _mm_srli_epi32(c, 31);              // b = (c ? 1 : 0)
        s = _mm_slli_epi32(b, 2);               // s = (b << 2)
        v = simd_multi_srl_epi32(v, s);              // v = (v >> s)
        r = _mm_or_si128(r, s);                 // r = (r | s)

        c = _mm_cmpgt_epi32(v, g_XM00000003.ToM128I());   // c = (v > 0x3)
        b = _mm_srli_epi32(c, 31);              // b = (c ? 1 : 0)
        s = _mm_slli_epi32(b, 1);               // s = (b << 1)
        v = simd_multi_srl_epi32(v, s);         // v = (v >> s)
        r = _mm_or_si128(r, s);                 // r = (r | s)

        s = _mm_srli_epi32(v, 1);
        r = _mm_or_si128(r, s);
        return r;
    }
#endif
}

namespace Graphyte::Maths
{
    mathinline Vector4 mathcall Vector4::Make(float x, float y, float z, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps(w, z, y, x) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Make(float value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_set_ps1(value) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Make(const float* value) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        const auto x = value[0];
        Detail::Vector4F32 v_result = { { { x, x, x, x } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_broadcast_ss(value) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MakeUInt(uint32_t x, uint32_t y, uint32_t z, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { x, y, z, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_epi32(static_cast<int32_t>(w), static_cast<int32_t>(z), static_cast<int32_t>(y), static_cast<int32_t>(x));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MakeUInt(uint32_t value) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { value, value, value, value } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        const auto v_temp = _mm_set1_epi32(static_cast<int32_t>(value));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MakeUInt(const uint32_t* value) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        const auto x = value[0];
        Detail::Vector4U32 v_result = { { { x, x, x, x } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps1(reinterpret_cast<const float*>(value)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SplatConstant(int32_t constant) noexcept
    {
        GX_ASSERT(constant >= -16 && constant <= 15);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4S32 v_result = { { { constant, constant, constant, constant } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_set1_epi32(constant);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SplatConstant(int32_t constant, uint32_t exponent) noexcept
    {
        GX_ASSERT(constant >= -16 && constant <= 15);
        GX_ASSERT(exponent < 32);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4S32 v = { { { constant, constant, constant, constant } } };
        return Vector4::ConvertIntToFloat({ v.V }, exponent);
#elif GRAPHYTE_HW_AVX
        auto v_scale = _mm_set1_epi32(constant);
        auto v_result = _mm_cvtepi32_ps(v_scale);
        uint32_t u_scale = 0x3F800000U - (exponent << 23);
        v_scale = _mm_set1_epi32(static_cast<int>(u_scale));
        v_result = _mm_mul_ps(v_result, _mm_castsi128_ps(v_scale));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRaw1(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                0,
                0,
                0,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ss(reinterpret_cast<const float*>(source)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRaw2(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                source[1],
                0,
                0,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(source));
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRawPacked2(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                source[1],
                0,
                0,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(reinterpret_cast<const float*>(source + 0));
        auto v_y = _mm_load_ss(reinterpret_cast<const float*>(source + 1));
        return { _mm_unpacklo_ps(v_x, v_y) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRaw3(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                source[1],
                source[2],
                0,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_load_si128(reinterpret_cast<const __m128i*>(source));
        v_v = _mm_and_si128(v_v, Detail::VEC4_MASK_COMPONENTS_3.ToM128I());
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRawPacked3(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                source[1],
                source[2],
                0,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(reinterpret_cast<const float*>(source + 0));
        auto v_y = _mm_load_ss(reinterpret_cast<const float*>(source + 1));
        auto v_z = _mm_load_ss(reinterpret_cast<const float*>(source + 2));
        auto v_xy = _mm_unpacklo_ps(v_x, v_y);
        return { _mm_movelh_ps(v_xy, v_z) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRaw4(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                source[1],
                source[2],
                source[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_load_si128(reinterpret_cast<const __m128i*>(source));
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadRawPacked4(const uint32_t* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                source[0],
                source[1],
                source[2],
                source[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    mathinline void mathcall Vector4::StoreRaw1(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(reinterpret_cast<float*>(destination + 0), v.V);
#endif
    }

    mathinline void mathcall Vector4::StoreRaw2(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
        destination[1] = v.V.U[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    mathinline void mathcall Vector4::StoreRawPacked2(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
        destination[1] = v.V.U[1];
#elif GRAPHYTE_HW_AVX
        auto v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(reinterpret_cast<float*>(destination + 0), v.V);
        _mm_store_ss(reinterpret_cast<float*>(destination + 1), v_y);
#endif
    }

    mathinline void mathcall Vector4::StoreRaw3(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
        destination[1] = v.V.U[1];
        destination[2] = v.V.U[2];
#elif GRAPHYTE_HW_AVX
        auto v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(reinterpret_cast<float*>(destination + 2), v_z);
#endif
    }

    mathinline void mathcall Vector4::StoreRawPacked3(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
        destination[1] = v.V.U[1];
        destination[2] = v.V.U[2];
#elif GRAPHYTE_HW_AVX
        auto v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        auto v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(reinterpret_cast<float*>(destination + 0), v.V);
        _mm_store_ss(reinterpret_cast<float*>(destination + 1), v_y);
        _mm_store_ss(reinterpret_cast<float*>(destination + 2), v_z);
#endif
    }

    mathinline void mathcall Vector4::StoreRaw4(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
        destination[1] = v.V.U[1];
        destination[2] = v.V.U[2];
        destination[3] = v.V.U[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_si128(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    mathinline void mathcall Vector4::StoreRawPacked4(uint32_t* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = v.V.U[0];
        destination[1] = v.V.U[1];
        destination[2] = v.V.U[2];
        destination[3] = v.V.U[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_si128(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const int2* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = static_cast<float>(source->X);
        v_result.V.F[1] = static_cast<float>(source->Y);
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(reinterpret_cast<const float*>(&source->X));
        auto v_y = _mm_load_ss(reinterpret_cast<const float*>(&source->Y));
        auto v_v = _mm_unpacklo_ps(v_x, v_y);
        return { _mm_cvtepi32_ps(_mm_castps_si128(v_v)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const int3* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = static_cast<float>(source->X);
        v_result.V.F[1] = static_cast<float>(source->Y);
        v_result.V.F[2] = static_cast<float>(source->Z);
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(reinterpret_cast<const float*>(&source->X));
        auto v_y = _mm_load_ss(reinterpret_cast<const float*>(&source->Y));
        auto v_z = _mm_load_ss(reinterpret_cast<const float*>(&source->Z));
        auto v_xy = _mm_unpacklo_ps(v_x, v_y);
        auto v_v = _mm_movelh_ps(v_xy, v_z);
        return { _mm_cvtepi32_ps(_mm_castps_si128(v_v)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const int4* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = static_cast<float>(source->X);
        v_result.V.F[1] = static_cast<float>(source->Y);
        v_result.V.F[2] = static_cast<float>(source->Z);
        v_result.V.F[3] = static_cast<float>(source->W);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
        return { _mm_cvtepi32_ps(v_v) };
#endif
    }
    
    mathinline Vector4 mathcall Vector4::Load(const uint2* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = static_cast<float>(source->X);
        v_result.V.F[1] = static_cast<float>(source->Y);
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(reinterpret_cast<const float*>(&source->X));
        auto v_y = _mm_load_ss(reinterpret_cast<const float*>(&source->Y));
        auto v_v = _mm_unpacklo_ps(v_x, v_y);
        auto v_mask = _mm_and_ps(v_v, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_result = _mm_xor_ps(v_v, v_mask);
        v_result = _mm_cvtepi32_ps(_mm_castps_si128(v_result));
        auto i_mask = _mm_srai_epi32(_mm_castps_si128(v_mask), 31);
        v_mask = _mm_and_ps(_mm_castsi128_ps(i_mask), Detail::VEC4_UNSIGNED_FIX.V);
        v_result = _mm_and_ps(v_result, v_mask);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const uint3* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = static_cast<float>(source->X);
        v_result.V.F[1] = static_cast<float>(source->Y);
        v_result.V.F[2] = static_cast<float>(source->Z);
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(reinterpret_cast<const float*>(&source->X));
        auto v_y = _mm_load_ss(reinterpret_cast<const float*>(&source->Y));
        auto v_z = _mm_load_ss(reinterpret_cast<const float*>(&source->Z));
        auto v_xy = _mm_unpacklo_ps(v_x, v_y);
        auto v_v = _mm_movelh_ps(v_xy, v_z);
        auto v_mask = _mm_and_ps(v_v, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_result = _mm_xor_ps(v_v, v_mask);
        v_result = _mm_cvtepi32_ps(_mm_castps_si128(v_result));
        auto i_mask = _mm_srai_epi32(_mm_castps_si128(v_mask), 31);
        v_mask = _mm_and_ps(_mm_castsi128_ps(i_mask), Detail::VEC4_UNSIGNED_FIX.V);
        v_result = _mm_and_ps(v_result, v_mask);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const uint4* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = static_cast<float>(source->X);
        v_result.V.F[1] = static_cast<float>(source->Y);
        v_result.V.F[2] = static_cast<float>(source->Z);
        v_result.V.F[3] = static_cast<float>(source->W);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(source));
        auto v_mask = _mm_and_ps(_mm_castsi128_ps(v_v), Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_result = _mm_xor_ps(_mm_castsi128_ps(v_v), v_mask);
        v_result = _mm_cvtepi32_ps(_mm_castps_si128(v_result));
        auto i_mask = _mm_srai_epi32(_mm_castps_si128(v_mask), 31);
        v_mask = _mm_and_ps(_mm_castsi128_ps(i_mask), Detail::VEC4_UNSIGNED_FIX.V);
        v_result = _mm_and_ps(v_result, v_mask);
        return { v_result };
#endif
    }

    mathinline void mathcall Vector4::Store(int2* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = static_cast<int32_t>(v.V.F[0]);
        destination->Y = static_cast<int32_t>(v.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_overflow = _mm_cmpgt_ps(v.V, Detail::VEC4_INTMAX.V);
        auto i_result = _mm_cvttps_epi32(v.V);
        auto v_result = _mm_and_ps(v_overflow, Detail::VEC4_MASK_ABS.V);
        v_overflow = _mm_andnot_ps(v_overflow, _mm_castsi128_ps(i_result));
        v_overflow = _mm_or_ps(v_overflow, v_result);

        auto v_y = _mm_permute_ps(v_overflow, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(reinterpret_cast<float*>(&destination->X), v_overflow);
        _mm_store_ss(reinterpret_cast<float*>(&destination->Y), v_y);
#endif
    }

    mathinline void mathcall Vector4::Store(int3* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = static_cast<int32_t>(v.V.F[0]);
        destination->Y = static_cast<int32_t>(v.V.F[1]);
        destination->Z = static_cast<int32_t>(v.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_overflow = _mm_cmpgt_ps(v.V, Detail::VEC4_INTMAX.V);
        auto i_result = _mm_cvttps_epi32(v.V);
        auto v_result = _mm_and_ps(v_overflow, Detail::VEC4_MASK_ABS.V);
        v_overflow = _mm_andnot_ps(v_overflow, _mm_castsi128_ps(i_result));
        v_overflow = _mm_or_ps(v_overflow, v_result);

        auto v_y = _mm_permute_ps(v_overflow, _MM_SHUFFLE(1, 1, 1, 1));
        auto v_z = _mm_permute_ps(v_overflow, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(reinterpret_cast<float*>(&destination->X), v_overflow);
        _mm_store_ss(reinterpret_cast<float*>(&destination->Y), v_y);
        _mm_store_ss(reinterpret_cast<float*>(&destination->Z), v_z);
#endif
    }

    mathinline void mathcall Vector4::Store(int4* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = static_cast<int32_t>(v.V.F[0]);
        destination->Y = static_cast<int32_t>(v.V.F[1]);
        destination->Z = static_cast<int32_t>(v.V.F[2]);
        destination->W = static_cast<int32_t>(v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_overflow = _mm_cmpgt_ps(v.V, Detail::VEC4_INTMAX.V);
        auto i_result = _mm_cvttps_epi32(v.V);
        auto v_result = _mm_and_ps(v_overflow, Detail::VEC4_MASK_ABS.V);
        v_overflow = _mm_andnot_ps(v_overflow, _mm_castsi128_ps(i_result));
        v_overflow = _mm_or_ps(v_overflow, v_result);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v_overflow));
#endif
    }

    mathinline void mathcall Vector4::Store(uint2* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = static_cast<uint32_t>(v.V.F[0]);
        destination->Y = static_cast<uint32_t>(v.V.F[1]);
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_max_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_overflow = _mm_cmpgt_ps(v_result, Detail::VEC4_UINTMAX.V);
        auto v_value = Detail::VEC4_UNSIGNED_FIX.V;
        auto v_mask = _mm_cmpge_ps(v_result, v_value);
        v_value = _mm_and_ps(v_value, v_mask);
        v_result = _mm_sub_ps(v_result, v_value);
        auto i_result = _mm_cvttps_epi32(v_result);
        v_mask = _mm_and_ps(v_mask, Detail::VEC4_NEGATIVE_ZERO.V);
        v_result = _mm_xor_ps(_mm_castsi128_ps(i_result), v_mask);
        v_result = _mm_or_ps(v_result, v_overflow);
        auto v_y = _mm_permute_ps(v_result, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(reinterpret_cast<float*>(&destination->X), v_result);
        _mm_store_ss(reinterpret_cast<float*>(&destination->Y), v_y);
#endif
    }

    mathinline void mathcall Vector4::Store(uint3* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = static_cast<uint32_t>(v.V.F[0]);
        destination->Y = static_cast<uint32_t>(v.V.F[1]);
        destination->Z = static_cast<uint32_t>(v.V.F[2]);
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_max_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_overflow = _mm_cmpgt_ps(v_result, Detail::VEC4_UINTMAX.V);
        auto v_value = Detail::VEC4_UNSIGNED_FIX.V;
        auto v_mask = _mm_cmpge_ps(v_result, v_value);
        v_value = _mm_and_ps(v_value, v_mask);
        v_result = _mm_sub_ps(v_result, v_value);
        auto i_result = _mm_cvttps_epi32(v_result);
        v_mask = _mm_and_ps(v_mask, Detail::VEC4_NEGATIVE_ZERO.V);
        v_result = _mm_xor_ps(_mm_castsi128_ps(i_result), v_mask);
        v_result = _mm_or_ps(v_result, v_overflow);
        auto v_y = _mm_permute_ps(v_result, _MM_SHUFFLE(1, 1, 1, 1));
        auto v_z = _mm_permute_ps(v_result, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(reinterpret_cast<float*>(&destination->X), v_result);
        _mm_store_ss(reinterpret_cast<float*>(&destination->Y), v_y);
        _mm_store_ss(reinterpret_cast<float*>(&destination->Z), v_z);
#endif
    }

    mathinline void mathcall Vector4::Store(uint4* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = static_cast<uint32_t>(v.V.F[0]);
        destination->Y = static_cast<uint32_t>(v.V.F[1]);
        destination->Z = static_cast<uint32_t>(v.V.F[2]);
        destination->W = static_cast<uint32_t>(v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_max_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_overflow = _mm_cmpgt_ps(v_result, Detail::VEC4_UINTMAX.V);
        auto v_value = Detail::VEC4_UNSIGNED_FIX.V;
        auto v_mask = _mm_cmpge_ps(v_result, v_value);
        v_value = _mm_and_ps(v_value, v_mask);
        v_result = _mm_sub_ps(v_result, v_value);
        auto i_result = _mm_cvttps_epi32(v_result);
        v_mask = _mm_and_ps(v_mask, Detail::VEC4_NEGATIVE_ZERO.V);
        v_result = _mm_xor_ps(_mm_castsi128_ps(i_result), v_mask);
        v_result = _mm_or_ps(v_result, v_overflow);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v_result));
#endif
    }


    mathinline Vector4 mathcall Vector4::Load(const float* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source[0];
        v_result.V.F[1] = 0.0F;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ss(source) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const float2a* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(source));
        return { _mm_castsi128_ps(v_v) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadPacked(const float2* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = 0.0F;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(&source->X);
        auto v_y = _mm_load_ss(&source->Y);
        return { _mm_unpacklo_ps(v_x, v_y) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const float3a* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_v = _mm_load_ps(&source->X);
        return { _mm_and_ps(v_v, Detail::VEC4_MASK_COMPONENTS_3) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadPacked(const float3* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = 0.0F;
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_load_ss(&source->X);
        auto v_y = _mm_load_ss(&source->Y);
        auto v_z = _mm_load_ss(&source->Z);
        auto v_xy = _mm_unpacklo_ps(v_x, v_y);
        return { _mm_movelh_ps(v_xy, v_z) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const float4a* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = source->W;
        return v_result;
#elif GRAPHYTE_HW_AVX
        return { _mm_load_ps(&source->X) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LoadPacked(const float4* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 v_result;
        v_result.V.F[0] = source->X;
        v_result.V.F[1] = source->Y;
        v_result.V.F[2] = source->Z;
        v_result.V.F[3] = source->W;
        return v_result;
#elif GRAPHYTE_HW_AVX
        return { _mm_loadu_ps(&source->X) };
#endif
    }

    mathinline void mathcall Vector4::Store(float* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination[0] = Vector4::GetX(v);
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(destination, v.V);
#endif
    }

    mathinline void mathcall Vector4::Store(float2a* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
#endif
    }

    mathinline void mathcall Vector4::StorePacked(float2* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        auto v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
#endif
    }

    mathinline void mathcall Vector4::Store(float3a* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        auto v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), _mm_castps_si128(v.V));
        _mm_store_ss(&destination->Z, v_z);
#endif
    }

    mathinline void mathcall Vector4::StorePacked(float3* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        auto v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        auto v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->X, v.V);
        _mm_store_ss(&destination->Y, v_y);
        _mm_store_ss(&destination->Z, v_z);
#endif
    }

    mathinline void mathcall Vector4::Store(float4a* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_store_ps(&destination->X, v.V);
#endif
    }

    mathinline void mathcall Vector4::StorePacked(float4* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = v.V.F[0];
        destination->Y = v.V.F[1];
        destination->Z = v.V.F[2];
        destination->W = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(&destination->X, v.V);
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const half2* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_HW_F16C
        auto v_v = _mm_load_ss(reinterpret_cast<const float*>(source));
        return { _mm_cvtph_ps(_mm_castps_si128(v_v)) };
#else
        Detail::Vector4F32 v_result = { { {
                FromHalf(source->X),
                FromHalf(source->Y),
                0.0F,
                0.0F,
            } } };
        return { v_result.V };
#endif
    }

    mathinline Vector4 mathcall Vector4::Load(const half4* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_HW_F16C
        auto v_v = _mm_loadl_epi64(reinterpret_cast<const __m128i*>(source));
        return { _mm_cvtph_ps(v_v) };
#else
        Detail::Vector4F32 v_result = { { {
                FromHalf(source->X),
                FromHalf(source->Y),
                FromHalf(source->Z),
                FromHalf(source->W),
            } } };
        return { v_result.V };
#endif
    }

    mathinline void mathcall Vector4::Store(half2* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->X = ToHalf(Vector4::GetX(v));
        destination->Y = ToHalf(Vector4::GetY(v));
#elif GRAPHYTE_HW_AVX || GRAPHYTE_HW_F16C
        auto v_v = _mm_cvtps_ph(v.V, 0);
        _mm_store_ss(reinterpret_cast<float*>(destination), _mm_castsi128_ps(v_v));
#endif
    }

    mathinline void mathcall Vector4::Store(half4* destination, Vector4 v) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        float4a ft;
        Vector4::Store(&ft, v);

        destination->X = ToHalf(ft.X);
        destination->Y = ToHalf(ft.Y);
        destination->Z = ToHalf(ft.Z);
        destination->W = ToHalf(ft.W);
#elif GRAPHYTE_HW_AVX || GRAPHYTE_HW_F16C
        auto v_v = _mm_cvtps_ph(v.V, 0);
        _mm_storel_epi64(reinterpret_cast<__m128i*>(destination), v_v);
#endif
    }

    mathinline Vector4 mathcall Vector4::SplatX(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        const auto x = v.V.F[0];
        Detail::Vector4F32 v_result = { { { x, x, x, x } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX2
        return { _mm_broadcastss_ps(v.V) };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SplatY(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        const auto y = v.V.F[1];
        Detail::Vector4F32 v_result = { { { y, y, y, y } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SplatZ(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        const auto z = v.V.F[2];
        Detail::Vector4F32 v_result = { { { z, z, z, z } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2)) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SplatW(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        const auto w = v.V.F[3];
        Detail::Vector4F32 v_result = { { { w, w, w, w } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3)) };
#endif
    }

    mathinline float mathcall Vector4::GetByIndex(Vector4 v, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[index];
#else
        Detail::Vector4F32 v_temp;
        v_temp.V = v.V;
        return v_temp.F[index];
#endif
    }
    mathinline void mathcall Vector4::GetByIndex(float* value, Vector4 v, size_t index) noexcept
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.F[index];
#else
        Detail::Vector4F32 v_temp;
        v_temp.V = v.V;
        (*value) = v_temp.F[index];
#endif
    }

    mathinline float mathcall Vector4::GetX(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[0];
#elif GRAPHYTE_HW_AVX
        return _mm_cvtss_f32(v.V);
#endif
    }

    mathinline float mathcall Vector4::GetY(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[1];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    mathinline float mathcall Vector4::GetZ(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[2];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    mathinline float mathcall Vector4::GetW(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.F[3];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        return _mm_cvtss_f32(v_temp);
#endif
    }

    mathinline void mathcall Vector4::GetX(float* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.F[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(value, v.V);
#endif
    }

    mathinline void mathcall Vector4::GetY(float* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.F[1];
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(value)) = _mm_extract_ps(v.V, 1);
#endif
    }

    mathinline void mathcall Vector4::GetZ(float* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.F[2];
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(value)) = _mm_extract_ps(v.V, 2);
#endif
    }

    mathinline void mathcall Vector4::GetW(float* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.F[3];
#elif GRAPHYTE_HW_AVX
        (*reinterpret_cast<int*>(value)) = _mm_extract_ps(v.V, 3);
#endif
    }

    mathinline Vector4 mathcall Vector4::SetByIndex(Vector4 v, float value, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Detail::Vector4F32 v_temp;
        v_temp.V = v.V;
        v_temp.F[index] = value;
        return { v_temp.V };
    }

    mathinline Vector4 mathcall Vector4::SetByIndex(Vector4 v, const float* value, size_t index) noexcept
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Detail::Vector4F32 v_temp;
        v_temp.V = v.V;
        v_temp.F[index] = *value;
        return { v_temp.V };
    }

    mathinline Vector4 mathcall Vector4::SetX(Vector4 v, float x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { x, v.V.F[1], v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(x);
        v_temp = _mm_move_ss(v.V, v_temp);
        return { v_temp };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetY(Vector4 v, float y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { v.V.F[0], y, v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(y);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x10);
        return { v_temp };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetZ(Vector4 v, float z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { v.V.F[0], v.V.F[1], z, v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(z);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x20);
        return { v_temp };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetW(Vector4 v, float w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { v.V.F[0], v.V.F[1], v.V.F[2], w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set_ss(w);
        v_temp = _mm_insert_ps(v.V, v_temp, 0x30);
        return { v_temp };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetX(Vector4 v, const float* x) noexcept
    {
        GX_ASSERT(x != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { *x, v.V.F[1], v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_load_ss(x);
        v_result = _mm_move_ss(v.V, v_result);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetY(Vector4 v, const float* y) noexcept
    {
        GX_ASSERT(y != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { v.V.F[0], *y, v.V.F[2], v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        auto v_temp = _mm_load_ss(y);
        v_result = _mm_move_ss(v_result, v_temp);
        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 2, 0, 1));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetZ(Vector4 v, const float* z) noexcept
    {
        GX_ASSERT(z != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { v.V.F[0], v.V.F[1], *z, v.V.F[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        auto v_temp = _mm_load_ss(z);
        v_result = _mm_move_ss(v_result, v_temp);
        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 0, 1, 2));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetW(Vector4 v, const float* w) noexcept
    {
        GX_ASSERT(w != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_temp = { { { v.V.F[0], v.V.F[1], v.V.F[2], *w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        auto v_temp = _mm_load_ss(w);
        v_result = _mm_move_ss(v_result, v_temp);
        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(0, 2, 1, 3));
        return { v_result };
#endif
    }

    mathinline uint32_t mathcall Vector4::GetUIntByIndex(Vector4 v, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[index];
#else
        Detail::Vector4U32 v_temp;
        v_temp.V = v.V;
        return v_temp.U[index];
#endif
    }

    mathinline void mathcall Vector4::GetUIntByIndex(uint32_t* value, Vector4 v, size_t index) noexcept
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.U[index];
#elif GRAPHYTE_HW_AVX
        Detail::Vector4U32 v_temp;
        v_temp.V = v.V;
        (*value) = v_temp.U[index];
#endif
    }

    mathinline uint32_t mathcall Vector4::GetUIntX(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[0];
#elif GRAPHYTE_HW_AVX
        return static_cast<uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(v.V)));
#endif
    }

    mathinline uint32_t mathcall Vector4::GetUIntY(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[1];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(v_temp, 1));
#endif
    }

    mathinline uint32_t mathcall Vector4::GetUIntZ(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[2];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(v_temp, 2));
#endif
    }

    mathinline uint32_t mathcall Vector4::GetUIntW(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return v.V.U[3];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_castps_si128(v.V);
        return static_cast<uint32_t>(_mm_extract_epi32(v_temp, 3));
#endif
    }

    mathinline void mathcall Vector4::GetUIntX(uint32_t* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.U[0];
#elif GRAPHYTE_HW_AVX
        _mm_store_ss(reinterpret_cast<float*>(value), v.V);
#endif
    }

    mathinline void mathcall Vector4::GetUIntY(uint32_t* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.U[1];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_castps_si128(v.V);
        (*value) = static_cast<uint32_t>(_mm_extract_epi32(v_temp, 1));
#endif
    }

    mathinline void mathcall Vector4::GetUIntZ(uint32_t* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.U[2];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_castps_si128(v.V);
        (*value) = static_cast<uint32_t>(_mm_extract_epi32(v_temp, 2));
#endif
    }

    mathinline void mathcall Vector4::GetUIntW(uint32_t* value, Vector4 v) noexcept
    {
        GX_ASSERT(value != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        (*value) = v.V.U[3];
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_castps_si128(v.V);
        (*value) = static_cast<uint32_t>(_mm_extract_epi32(v_temp, 3));
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntByIndex(Vector4 v, uint32_t value, size_t index) noexcept
    {
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Detail::Vector4U32 v_temp;
        v_temp.V = v.V;
        v_temp.U[index] = value;
        return { v_temp.V };
    }

    mathinline Vector4 mathcall Vector4::SetUIntByIndex(Vector4 v, const uint32_t* value, size_t index) noexcept
    {
        GX_ASSERT(value != nullptr);
        GX_ASSERT(index < 4);
        GX_COMPILER_ASSUME(index < 4);

        Detail::Vector4U32 v_temp;
        v_temp.V = v.V;
        v_temp.U[index] = (*value);
        return { v_temp.V };
    }

    mathinline Vector4 mathcall Vector4::SetUIntX(Vector4 v, uint32_t x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { x, v.V.U[1], v.V.U[2], v.V.U[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cvtsi32_si128(static_cast<int32_t>(x));
        auto v_result = _mm_move_ss(v.V, _mm_castsi128_ps(v_temp));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntY(Vector4 v, uint32_t y) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { v.V.U[0], y, v.V.U[2], v.V.U[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_castps_si128(v.V);
        v_result = _mm_insert_epi32(v_result, static_cast<int32_t>(y), 1);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntZ(Vector4 v, uint32_t z) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { v.V.U[0], v.V.U[1], z, v.V.U[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_castps_si128(v.V);
        v_result = _mm_insert_epi32(v_result, static_cast<int32_t>(z), 2);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntW(Vector4 v, uint32_t w) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { v.V.U[0], v.V.U[1], v.V.U[2], w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_castps_si128(v.V);
        v_result = _mm_insert_epi32(v_result, static_cast<int32_t>(w), 3);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntX(Vector4 v, const uint32_t* x) noexcept
    {
        GX_ASSERT(x != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { *x, v.V.U[1], v.V.U[2], v.V.U[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_load_ss(reinterpret_cast<const float*>(x));
        auto v_result = _mm_move_ss(v.V, v_temp);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntY(Vector4 v, const uint32_t* y) noexcept
    {
        GX_ASSERT(y != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { v.V.U[0], *y, v.V.U[2], v.V.U[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 2, 0, 1));
        auto v_temp = _mm_load_ss(reinterpret_cast<const float*>(y));
        v_result = _mm_move_ss(v_result, v_temp);
        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 2, 0, 1));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntZ(Vector4 v, const uint32_t* z) noexcept
    {
        GX_ASSERT(z != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { v.V.U[0], v.V.U[1], *z, v.V.U[3] } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 0, 1, 2));
        auto v_temp = _mm_load_ss(reinterpret_cast<const float*>(z));
        v_result = _mm_move_ss(v_result, v_temp);
        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(3, 0, 1, 2));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::SetUIntW(Vector4 v, const uint32_t* w) noexcept
    {
        GX_ASSERT(w != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_temp = { { { v.V.U[0], v.V.U[1], v.V.U[2], *w } } };
        return { v_temp.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 2, 1, 3));
        auto v_temp = _mm_load_ss(reinterpret_cast<const float*>(w));
        v_result = _mm_move_ss(v_result, v_temp);
        v_result = _mm_permute_ps(v_result, _MM_SHUFFLE(0, 2, 1, 3));
        return { v_result };
#endif
    }


    template <SwizzleMask Mask>
    mathinline Vector4 mathcall Vector4::Swizzle(Vector4 v) noexcept
    {
        return Vector4::Swizzle<
            (static_cast<uint32_t>(Mask) >> 0) & 3,
            (static_cast<uint32_t>(Mask) >> 2) & 3,
            (static_cast<uint32_t>(Mask) >> 4) & 3,
            (static_cast<uint32_t>(Mask) >> 6) & 3>(v);
    }

    template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
    mathinline Vector4 mathcall Vector4::Swizzle(Vector4 v) noexcept
    {
        static_assert(X <= 3, "X out of range");
        static_assert(Y <= 3, "Y out of range");
        static_assert(Z <= 3, "Z out of range");
        static_assert(W <= 3, "W out of range");

#if GRAPHYTE_MATH_NO_INTRINSICS
        return Vector4::Swizzle(v, X, Y, Z, W);
#elif GRAPHYTE_HW_AVX
        return { _mm_permute_ps(v.V, _MM_SHUFFLE(W, Z, Y, X)) };
#endif
    }

    template <> mathinline Vector4 mathcall Vector4::Swizzle<0, 1, 2, 3>(Vector4 v) noexcept
    {
        return v;
    }

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vector4 mathcall Vector4::Swizzle<0, 1, 0, 1>(Vector4 v) noexcept
    {
        return { _mm_movelh_ps(v.V, v.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Swizzle<2, 3, 2, 3>(Vector4 v) noexcept
    {
        return { _mm_movehl_ps(v.V, v.V) };
    }

    template <> mathinline Vector4 mathcall Vector4::Swizzle<0, 0, 1, 1>(Vector4 v) noexcept
    {
        return { _mm_unpacklo_ps(v.V, v.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Swizzle<2, 2, 3, 3>(Vector4 v) noexcept
    {
        return { _mm_unpackhi_ps(v.V, v.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Swizzle<0, 0, 2, 2>(Vector4 v) noexcept
    {
        return { _mm_moveldup_ps(v.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Swizzle<1, 1, 3, 3>(Vector4 v) noexcept
    {
        return { _mm_movehdup_ps(v.V) };
    }
#endif

#if GRAPHYTE_HW_AVX2 && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vector4 mathcall Vector4::Swizzle<0, 0, 0, 0>(Vector4 v) noexcept
    {
        return { _mm_broadcastss_ps(v.V) };
    }
#endif

    mathinline Vector4 mathcall Vector4::Swizzle(Vector4 v, uint32_t element0, uint32_t element1, uint32_t element2, uint32_t element3) noexcept
    {
        GX_ASSERT((element0 < 4) && (element1 < 4) && (element2 < 4) && (element3 < 4));
        GX_COMPILER_ASSUME((element0 < 4) && (element1 < 4) && (element2 < 4) && (element3 < 4));
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { { v.V.F[element0], v.V.F[element1], v.V.F[element2], v.V.F[element3] } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        uint32_t elements[4] = {
            element0,
            element1,
            element2,
            element3
        };
        auto v_control = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&elements[0]));
        return { _mm_permutevar_ps(v.V, v_control) };
#else
        auto mem_ptr = reinterpret_cast<const uint32_t*>(&v.V);

        Vector4 result;
        auto work_ptr = reinterpret_cast<uint32_t*>(&result.V);

        work_ptr[0] = mem_ptr[element0];
        work_ptr[1] = mem_ptr[element1];
        work_ptr[2] = mem_ptr[element2];
        work_ptr[3] = mem_ptr[element3];

        return { result.V };
#endif
    }

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    namespace Detail
    {
        template <uint32_t Shuffle, bool X, bool Y, bool Z, bool W> struct PermuteHelper final
        {
            static Vector4 mathcall Permute(Vector4 v1, Vector4 v2) noexcept
            {
                static const Vector4U32 select_mask = { { {
                        X ? 0xFFFFFFFFU : 0U,
                        Y ? 0xFFFFFFFFU : 0U,
                        Z ? 0xFFFFFFFFU : 0U,
                        W ? 0xFFFFFFFFU : 0U,
                    } } };

                auto v_shuffled1 = _mm_permute_ps(v1.V, Shuffle);
                auto v_shuffled2 = _mm_permute_ps(v2.V, Shuffle);
                auto v_masked1 = _mm_andnot_ps(select_mask.V, v_shuffled1);
                auto v_masked2 = _mm_and_ps(select_mask.V, v_shuffled2);
                return { _mm_or_ps(v_masked1, v_masked2) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, false, false, false, false>
        {
            static Vector4 mathcall Permute(Vector4 v1, [[maybe_unused]] Vector4 v2) noexcept
            {
                return { _mm_permute_ps(v1.V, Shuffle) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, true, true, true, true>
        {
            static Vector4 mathcall Permute([[maybe_unused]] Vector4 v1, Vector4 v2) noexcept
            {
                return { _mm_permute_ps(v2.V, Shuffle) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, false, false, true, true>
        {
            static Vector4 mathcall Permute(Vector4 v1, Vector4 v2) noexcept
            {
                return { _mm_shuffle_ps(v1.V, v2.V, Shuffle) };
            }
        };

        template <uint32_t Shuffle> struct PermuteHelper<Shuffle, true, true, false, false>
        {
            static Vector4 mathcall Permute(Vector4 v1, Vector4 v2) noexcept
            {
                return { _mm_shuffle_ps(v2.V, v1.V, Shuffle) };
            }
        };
    }
#endif

    template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
    mathinline Vector4 mathcall Vector4::Permute(Vector4 v1, Vector4 v2) noexcept
    {
        static_assert(X <= 7, "X template parameter out of range");
        static_assert(Y <= 7, "Y template parameter out of range");
        static_assert(Z <= 7, "Z template parameter out of range");
        static_assert(W <= 7, "W template parameter out of range");

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
        constexpr uint32_t shuffle = _MM_SHUFFLE(W & 3, Z & 3, Y & 3, X & 3);
        constexpr bool x = X > 3;
        constexpr bool y = Y > 3;
        constexpr bool z = Z > 3;
        constexpr bool w = W > 3;
        return Detail::PermuteHelper<shuffle, x, y, z, w>::Permute(v1, v2);
#else
        return Vector4::Permute(v1, v2, X, Y, Z, W);
#endif
    }

    template <> mathinline Vector4 mathcall Vector4::Permute<0, 1, 2, 3>(Vector4 v1, [[maybe_unused]] Vector4 v2) noexcept
    {
        return v1;
    }

    template <> mathinline Vector4 mathcall Vector4::Permute<4, 5, 6, 7>([[maybe_unused]] Vector4 v1, Vector4 v2) noexcept
    {
        return v2;
    }

#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 1, 4, 5>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_movelh_ps(v1.V, v2.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<6, 7, 2, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_movehl_ps(v1.V, v2.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 4, 1, 5>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_unpacklo_ps(v1.V, v2.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<2, 6, 3, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_unpackhi_ps(v1.V, v2.V) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<2, 3, 6, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(v1.V), _mm_castps_pd(v2.V))) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 1, 2, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x1) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 5, 2, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x2) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 5, 2, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x3) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 1, 6, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x4) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 1, 6, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x5) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 5, 6, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x6) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 5, 6, 3>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x7) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 1, 2, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x8) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 1, 2, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0x9) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 5, 2, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xA) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 5, 2, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xB) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 1, 6, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xC) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<4, 1, 6, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xD) };
    }
    template <> mathinline Vector4 mathcall Vector4::Permute<0, 5, 6, 7>(Vector4 v1, Vector4 v2) noexcept
    {
        return { _mm_blend_ps(v1.V, v2.V, 0xE) };
    }
#endif

    mathinline Vector4 mathcall Vector4::Permute(Vector4 v1, Vector4 v2, uint32_t permute_x, uint32_t permute_y, uint32_t permute_z, uint32_t permute_w) noexcept
    {
        GX_ASSERT((permute_x <= 7) && (permute_y <= 7) && (permute_z <= 7) && (permute_w <= 7));
        GX_COMPILER_ASSUME((permute_x <= 7) && (permute_y <= 7) && (permute_z <= 7) && (permute_w <= 7));
#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
        static const Detail::Vector4U32 v_threes = { { { 3, 3, 3, 3 } } };

        alignas(16) uint32_t elements[4] = { permute_x, permute_y, permute_z, permute_w };
        auto v_control = _mm_load_si128(reinterpret_cast<const __m128i*>(&elements[0]));

        auto v_select = _mm_cmpgt_epi32(v_control, v_threes.ToM128I());
        v_control = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(v_control), v_threes.V));

        auto v_shuffled1 = _mm_permutevar_ps(v1.V, v_control);
        auto v_shuffled2 = _mm_permutevar_ps(v2.V, v_control);

        auto v_masked1 = _mm_andnot_ps(_mm_castsi128_ps(v_select), v_shuffled1);
        auto v_masked2 = _mm_and_ps(_mm_castsi128_ps(v_select), v_shuffled2);

        return { _mm_or_ps(v_masked1, v_masked2) };
#else
        const uint32_t* mem_ptr[2];
        mem_ptr[0] = reinterpret_cast<const uint32_t*>(&v1.V);
        mem_ptr[1] = reinterpret_cast<const uint32_t*>(&v2.V);

        Vector4 result;
        auto work_ptr = reinterpret_cast<uint32_t*>(&result.V);

        auto i0 = permute_x & 3;
        auto e0 = permute_x >> 2;
        work_ptr[0] = mem_ptr[e0][i0];

        auto i1 = permute_y & 3;
        auto e1 = permute_y >> 2;
        work_ptr[1] = mem_ptr[e1][i1];

        auto i2 = permute_z & 3;
        auto e2 = permute_z >> 2;
        work_ptr[2] = mem_ptr[e2][i2];

        auto i3 = permute_w & 3;
        auto e3 = permute_w >> 2;
        work_ptr[3] = mem_ptr[e3][i3];

        return result;
#endif
    }

    mathinline Vector4 mathcall Vector4::SelectControl(uint32_t index0, uint32_t index1, uint32_t index2, uint32_t index3) noexcept
    {
#if GRAPHYTE_HW_AVX && !GRAPHYTE_MATH_NO_INTRINSICS
        auto v_temp = _mm_set_epi32(
            static_cast<int>(index3),
            static_cast<int>(index2),
            static_cast<int>(index1),
            static_cast<int>(index0)
        );
        v_temp = _mm_cmpgt_epi32(v_temp, Detail::VEC4_ZERO_4.ToM128I());
        return { _mm_castsi128_ps(v_temp) };
#else
        GX_ASSERT((index0 < 2) && (index1 < 2) && (index2 < 2) && (index3 < 2));
        GX_COMPILER_ASSUME((index0 < 2) && (index1 < 2) && (index2 < 2) && (index3 < 2));

        Vector4 v_control;
        const uint32_t control_elements[] = { Maths::SELECT_0, Maths::SELECT_1 };

        v_control.V.U[0] = control_elements[index0];
        v_control.V.U[1] = control_elements[index1];
        v_control.V.U[2] = control_elements[index2];
        v_control.V.U[3] = control_elements[index3];

        return v_control;
#endif
    }

    mathinline Vector4 mathcall Vector4::Select(Vector4 v1, Vector4 v2, Vector4 control) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                (v1.V.U[0] & ~control.V.U[0]) | (v2.V.U[0] & control.V.U[0]),
                (v1.V.U[1] & ~control.V.U[1]) | (v2.V.U[1] & control.V.U[1]),
                (v1.V.U[2] & ~control.V.U[2]) | (v2.V.U[2] & control.V.U[2]),
                (v1.V.U[3] & ~control.V.U[3]) | (v2.V.U[3] & control.V.U[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
#if true
        return { _mm_blendv_ps(v1.V, v2.V, control.V) };
#else
        auto v_temp1 = _mm_andnot_ps(control.V, v1.V);
        auto v_temp2 = _mm_and_ps(v2.V, control.V);
        return { _mm_or_ps(v_temp1, v_temp2) };
#endif
#endif
    }

    mathinline Vector4 mathcall Vector4::MergeXY(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                v1.V.U[0],
                v2.V.U[0],
                v1.V.U[1],
                v2.V.U[1],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_unpacklo_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MergeZW(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                v1.V.U[2],
                v2.V.U[2],
                v1.V.U[3],
                v2.V.U[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_unpackhi_ps(v1.V, v2.V) };
#endif
    }

    template <uint32_t Elements>
    mathinline Vector4 mathcall Vector4::ShiftLeft(Vector4 v1, Vector4 v2) noexcept
    {
        static_assert(Elements < 4, "Invalid elements count");
        return Vector4::Permute<
            Elements + 0,
            Elements + 1,
            Elements + 2,
            Elements + 3>(v1, v2);
    }

    mathinline Vector4 mathcall Vector4::ShiftLeft(Vector4 v1, Vector4 v2, uint32_t elements) noexcept
    {
        GX_ASSERT(elements < 4);
        GX_COMPILER_ASSUME(elements < 4);
        return Vector4::Permute(v1, v2, elements + 0, elements + 1, elements + 2, elements + 3);
    }


    template <uint32_t Elements>
    mathinline Vector4 mathcall Vector4::RotateLeft(Vector4 v) noexcept
    {
        static_assert(Elements < 4, "Invalid elements count");
        return Vector4::Swizzle<
            (Elements + 0) & 3,
            (Elements + 1) & 3,
            (Elements + 2) & 3,
            (Elements + 3) & 3>(v);
    }


    mathinline Vector4 mathcall Vector4::RotateLeft(Vector4 v, uint32_t elements) noexcept
    {
        GX_ASSERT(elements < 4);
        GX_COMPILER_ASSUME(elements < 4);
        return Vector4::Swizzle(v, elements & 3, (elements + 1) & 3, (elements + 2) & 3, (elements + 3) & 3);
    }


    template <uint32_t Elements>
    mathinline Vector4 mathcall Vector4::RotateRight(Vector4 v) noexcept
    {
        static_assert(Elements < 4, "Invalid elements count");
        return Vector4::Swizzle<
            (4 - Elements) & 3,
            (5 - Elements) & 3,
            (6 - Elements) & 3,
            (7 - Elements) & 3>(v);
    }

    mathinline Vector4 mathcall Vector4::RotateRight(Vector4 v, uint32_t elements) noexcept
    {
        GX_ASSERT(elements < 4);
        GX_COMPILER_ASSUME(elements < 4);
        return Vector4::Swizzle(v, (4 - elements) & 3, (5 - elements) & 3, (6 - elements) & 3, (7 - elements) & 3);
    }


    template <InsertMask Mask>
    mathinline Vector4 mathcall Vector4::Insert(Vector4 destination, Vector4 source)
    {
        static_assert(static_cast<uint32_t>(Mask) <= 0xF, "Permute mask out of range");

        return Permute<
            0 + ((static_cast<uint32_t>(Mask) & (1U << 3)) ? 4 : 0),
            1 + ((static_cast<uint32_t>(Mask) & (1U << 2)) ? 4 : 0),
            2 + ((static_cast<uint32_t>(Mask) & (1U << 1)) ? 4 : 0),
            3 + ((static_cast<uint32_t>(Mask) & (1U << 0)) ? 4 : 0)
        >(destination, source);
    }

    mathinline Vector4 mathcall Vector4::Insert(Vector4 destination, Vector4 source, uint32_t select0, uint32_t select1, uint32_t select2, uint32_t select3) noexcept
    {
        Vector4 control = Vector4::SelectControl(select0 & 1, select1 & 1, select2 & 1, select3 & 1);
        return Vector4::Select(destination, source, control);
    }

    mathinline Vector4 mathcall Vector4::Insert(Vector4 destination, Vector4 source, uint32_t rotate_left_elements, uint32_t select0, uint32_t select1, uint32_t select2, uint32_t select3) noexcept
    {
        Vector4 control = Vector4::SelectControl(select0 & 1, select1 & 1, select2 & 1, select3 & 1);
        return Vector4::Select(destination, Vector4::RotateLeft(source, rotate_left_elements), control);
    }

    mathinline Vector4 mathcall Vector4::CompareEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.F[0] == v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] == v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] == v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] == v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpeq_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareEqual(Vector4 v1, Vector4 v2, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto delta_x = (v1.V.F[0] - v2.V.F[0]);
        auto delta_y = (v1.V.F[1] - v2.V.F[1]);
        auto delta_z = (v1.V.F[2] - v2.V.F[2]);
        auto delta_w = (v1.V.F[3] - v2.V.F[3]);

        delta_x = fabsf(delta_x);
        delta_y = fabsf(delta_y);
        delta_z = fabsf(delta_z);
        delta_w = fabsf(delta_w);

        Detail::Vector4U32 v_control = { { {
                (delta_x <= epsilon.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (delta_y <= epsilon.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (delta_z <= epsilon.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (delta_w <= epsilon.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        auto v_delta = _mm_sub_ps(v1.V, v2.V);
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return { v_temp };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareNotEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.F[0] != v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] != v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] != v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] != v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareGreater(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.F[0] > v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] > v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] > v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] > v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpgt_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareGreaterEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.F[0] >= v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] >= v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] >= v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] >= v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpge_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareLess(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.F[0] < v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] < v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] < v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] < v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmplt_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareLessEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.F[0] <= v2.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[1] <= v2.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[2] <= v2.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.F[3] <= v2.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmple_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareInBounds(Vector4 v, Vector4 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v.V.F[0] <= bounds.V.F[0]) && (v.V.F[0] >= -bounds.V.F[0]) ? 0xFFFFFFFFU : 0U,
                (v.V.F[1] <= bounds.V.F[1]) && (v.V.F[1] >= -bounds.V.F[1]) ? 0xFFFFFFFFU : 0U,
                (v.V.F[2] <= bounds.V.F[2]) && (v.V.F[2] >= -bounds.V.F[2]) ? 0xFFFFFFFFU : 0U,
                (v.V.F[3] <= bounds.V.F[3]) && (v.V.F[3] >= -bounds.V.F[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp1 = _mm_cmple_ps(v.V, bounds.V);
        auto v_temp2 = _mm_mul_ps(bounds.V, Detail::VEC4_NEGATIVE_ONE_4.V);
        v_temp2 = _mm_cmple_ps(v_temp2, v.V);
        v_temp1 = _mm_and_ps(v_temp1, v_temp2);
        return { v_temp1 };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareIsNaN(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                BitIsNaN(v.V.U[0]) ? 0xFFFFFFFFU : 0U,
                BitIsNaN(v.V.U[1]) ? 0xFFFFFFFFU : 0U,
                BitIsNaN(v.V.U[2]) ? 0xFFFFFFFFU : 0U,
                BitIsNaN(v.V.U[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_cmpneq_ps(v.V, v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CompareIsInfinite(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                BitIsInf(v.V.U[0]) ? 0xFFFFFFFFU : 0U,
                BitIsInf(v.V.U[1]) ? 0xFFFFFFFFU : 0U,
                BitIsInf(v.V.U[2]) ? 0xFFFFFFFFU : 0U,
                BitIsInf(v.V.U[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_and_ps(v.V, Detail::VEC4_MASK_ABS.V);
        v_temp = _mm_cmpeq_ps(v_temp, Detail::VEC4_INFINITY);
        return { v_temp };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskCompareEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.U[0] == v2.V.U[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.U[1] == v2.V.U[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.U[2] == v2.V.U[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.U[3] == v2.V.U[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskCompareNotEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_control = { { {
                (v1.V.U[0] != v2.V.U[0]) ? 0xFFFFFFFFU : 0U,
                (v1.V.U[1] != v2.V.U[1]) ? 0xFFFFFFFFU : 0U,
                (v1.V.U[2] != v2.V.U[2]) ? 0xFFFFFFFFU : 0U,
                (v1.V.U[3] != v2.V.U[3]) ? 0xFFFFFFFFU : 0U,
            } } };
        return { v_control.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_xor_ps(_mm_castsi128_ps(v_temp), Detail::VEC4_MASK_NEGATIVE_ONE.V) };
#endif
    }

    mathinline bool mathcall Vector4::IsEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] == v2.V.F[0]) &&
            (v1.V.F[1] == v2.V.F[1]) &&
            (v1.V.F[2] == v2.V.F[2]) &&
            (v1.V.F[3] == v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsEqual(Vector4 v1, Vector4 v2, Vector4 epsilon) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto dx = fabsf(v1.V.F[0] - v2.V.F[0]);
        auto dy = fabsf(v1.V.F[1] - v2.V.F[1]);
        auto dz = fabsf(v1.V.F[2] - v2.V.F[2]);
        auto dw = fabsf(v1.V.F[3] - v2.V.F[3]);

        return
            (dx <= epsilon.V.F[0]) &&
            (dy <= epsilon.V.F[1]) &&
            (dz <= epsilon.V.F[2]) &&
            (dw <= epsilon.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_delta = _mm_sub_ps(v1.V, v2.V);
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_sub_ps(v_temp, v_delta);
        v_temp = _mm_max_ps(v_temp, v_delta);
        v_temp = _mm_cmple_ps(v_temp, epsilon.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsNotEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] != v2.V.F[0]) ||
            (v1.V.F[1] != v2.V.F[1]) ||
            (v1.V.F[2] != v2.V.F[2]) ||
            (v1.V.F[3] != v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpneq_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) != 0b0000;
#endif
    }

    mathinline bool mathcall Vector4::IsGreater(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] > v2.V.F[0]) &&
            (v1.V.F[1] > v2.V.F[1]) &&
            (v1.V.F[2] > v2.V.F[2]) &&
            (v1.V.F[3] > v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpgt_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsGreaterEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] >= v2.V.F[0]) &&
            (v1.V.F[1] >= v2.V.F[1]) &&
            (v1.V.F[2] >= v2.V.F[2]) &&
            (v1.V.F[3] >= v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpge_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsLess(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] < v2.V.F[0]) &&
            (v1.V.F[1] < v2.V.F[1]) &&
            (v1.V.F[2] < v2.V.F[2]) &&
            (v1.V.F[3] < v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmplt_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsLessEqual(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.F[0] <= v2.V.F[0]) &&
            (v1.V.F[1] <= v2.V.F[1]) &&
            (v1.V.F[2] <= v2.V.F[2]) &&
            (v1.V.F[3] <= v2.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmple_ps(v1.V, v2.V);
        return _mm_movemask_ps(v_temp) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::InBounds(Vector4 v, Vector4 bounds) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            ((v.V.F[0] <= bounds.V.F[0]) && (v.V.F[0] >= -bounds.V.F[0])) &&
            ((v.V.F[1] <= bounds.V.F[1]) && (v.V.F[1] >= -bounds.V.F[1])) &&
            ((v.V.F[2] <= bounds.V.F[2]) && (v.V.F[2] >= -bounds.V.F[2])) &&
            ((v.V.F[3] <= bounds.V.F[3]) && (v.V.F[3] >= -bounds.V.F[3]));
#elif GRAPHYTE_HW_AVX
        auto v_temp1 = _mm_cmple_ps(v.V, bounds.V);
        auto v_temp2 = _mm_mul_ps(bounds.V, Detail::VEC4_NEGATIVE_ONE_4.V);
        v_temp2 = _mm_cmple_ps(v_temp2, v.V);
        v_temp1 = _mm_and_ps(v_temp1, v_temp2);
        return _mm_movemask_ps(v_temp1) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsNaN(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            std::isnan(v.V.F[0]) ||
            std::isnan(v.V.F[1]) ||
            std::isnan(v.V.F[2]) ||
            std::isnan(v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpneq_ps(v.V, v.V);
        return _mm_movemask_ps(v_temp) != 0;
#endif
    }

    mathinline bool mathcall Vector4::IsInfinite(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            std::isinf(v.V.F[0]) ||
            std::isinf(v.V.F[1]) ||
            std::isinf(v.V.F[2]) ||
            std::isinf(v.V.F[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_and_ps(v.V, Detail::VEC4_MASK_ABS.V);
        v_temp = _mm_cmpeq_ps(v_temp, Detail::VEC4_INFINITY.V);
        return _mm_movemask_ps(v_temp) != 0;
#endif
    }

    mathinline bool mathcall Vector4::IsEqualUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.U[0] == v2.V.U[0]) &&
            (v1.V.U[1] == v2.V.U[1]) &&
            (v1.V.U[2] == v2.V.U[2]) &&
            (v1.V.U[3] == v2.V.U[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return _mm_movemask_ps(_mm_castsi128_ps(v_temp)) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::IsNotEqualUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v1.V.U[0] != v2.V.U[0]) ||
            (v1.V.U[1] != v2.V.U[1]) ||
            (v1.V.U[2] != v2.V.U[2]) ||
            (v1.V.U[3] != v2.V.U[3]);
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_cmpeq_epi32(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return _mm_movemask_ps(_mm_castsi128_ps(v_temp)) != 0b1111;
#endif
    }

    mathinline Vector4 mathcall Vector4::SwapEndian(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result;
        v_result.V = v.V;

        v_result.U[0] = ByteSwap(v_result.U[0]);
        v_result.U[1] = ByteSwap(v_result.U[1]);
        v_result.U[2] = ByteSwap(v_result.U[2]);
        v_result.U[3] = ByteSwap(v_result.U[3]);

        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4U32 indices = { { { 0x00010203U, 0x04050607U, 0x08090A0BU, 0x0C0D0E0FU } } };

        auto v_result = _mm_shuffle_epi8(_mm_castps_si128(v.V), indices.ToM128I());
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Zero() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { { 0.0F, 0.0F, 0.0F, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#endif
    }

    mathinline Vector4 mathcall Vector4::One() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { { 1.0F, 1.0F, 1.0F, 1.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { Detail::VEC4_ONE_4.V };
#endif
    }

    mathinline Vector4 mathcall Vector4::Infinity() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { 0x7F800000U, 0x7F800000U, 0x7F800000U, 0x7F800000U } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { Detail::VEC4_INFINITY.V };
#endif
    }

    mathinline Vector4 mathcall Vector4::NaN() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { 0x7FC00000U, 0x7FC00000U, 0x7FC00000U, 0x7FC00000U } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { Detail::VEC4_QNAN.V };
#endif
    }

    mathinline Vector4 mathcall Vector4::Epsilon() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { 0x34000000U, 0x34000000U, 0x34000000U, 0x34000000U } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { Detail::VEC4_EPSILON.V };
#endif
    }

    mathinline Vector4 mathcall Vector4::SignMask() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { 0x80000000U, 0x80000000U, 0x80000000U, 0x80000000U } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set1_epi32(static_cast<int>(0x80000000));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::UnitX() noexcept
    {
        return { Detail::VEC4_POSITIVE_UNIT_X.V };
    }

    mathinline Vector4 mathcall Vector4::UnitY() noexcept
    {
        return { Detail::VEC4_POSITIVE_UNIT_Y.V };
    }

    mathinline Vector4 mathcall Vector4::UnitZ() noexcept
    {
        return { Detail::VEC4_POSITIVE_UNIT_Z.V };
    }

    mathinline Vector4 mathcall Vector4::UnitW() noexcept
    {
        return { Detail::VEC4_POSITIVE_UNIT_W.V };
    }

    mathinline Vector4 mathcall Vector4::NegativeUnitX() noexcept
    {
        return { Detail::VEC4_NEGATIVE_UNIT_X.V };
    }

    mathinline Vector4 mathcall Vector4::NegativeUnitY() noexcept
    {
        return { Detail::VEC4_NEGATIVE_UNIT_Y.V };
    }

    mathinline Vector4 mathcall Vector4::NegativeUnitZ() noexcept
    {
        return { Detail::VEC4_NEGATIVE_UNIT_Z.V };
    }

    mathinline Vector4 mathcall Vector4::NegativeUnitW() noexcept
    {
        return { Detail::VEC4_NEGATIVE_UNIT_W.V };
    }

    mathinline Vector4 mathcall Vector4::MaskTrue() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { { 0xFFFF'FFFFU, 0xFFFF'FFFFU, 0xFFFF'FFFFU, 0xFFFF'FFFFU } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_set1_epi32(-1);
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskFalse() noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { { 0.0F, 0.0F, 0.0F, 0.0F } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_setzero_ps() };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskAndUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                v1.V.U[0] & v2.V.U[0],
                v1.V.U[1] & v2.V.U[1],
                v1.V.U[2] & v2.V.U[2],
                v1.V.U[3] & v2.V.U[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_and_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskAndCUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                v1.V.U[0] & ~v2.V.U[0],
                v1.V.U[1] & ~v2.V.U[1],
                v1.V.U[2] & ~v2.V.U[2],
                v1.V.U[3] & ~v2.V.U[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_andnot_si128(_mm_castps_si128(v2.V), _mm_castps_si128(v1.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskOrUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                v1.V.U[0] | v2.V.U[0],
                v1.V.U[1] | v2.V.U[1],
                v1.V.U[2] | v2.V.U[2],
                v1.V.U[3] | v2.V.U[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_or_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskNorUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                ~(v1.V.U[0] | v2.V.U[0]),
                ~(v1.V.U[1] | v2.V.U[1]),
                ~(v1.V.U[2] | v2.V.U[2]),
                ~(v1.V.U[3] | v2.V.U[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_or_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        v_result = _mm_andnot_si128(v_result, Detail::VEC4_MASK_NEGATIVE_ONE.ToM128I());
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MaskXorUInt(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4U32 v_result = { { {
                (v1.V.U[0] ^ v2.V.U[0]),
                (v1.V.U[1] ^ v2.V.U[1]),
                (v1.V.U[2] ^ v2.V.U[2]),
                (v1.V.U[3] ^ v2.V.U[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_xor_si128(_mm_castps_si128(v1.V), _mm_castps_si128(v2.V));
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Min(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                (v1.V.F[0] < v2.V.F[0]) ? v1.V.F[0] : v2.V.F[0],
                (v1.V.F[1] < v2.V.F[1]) ? v1.V.F[1] : v2.V.F[1],
                (v1.V.F[2] < v2.V.F[2]) ? v1.V.F[2] : v2.V.F[2],
                (v1.V.F[3] < v2.V.F[3]) ? v1.V.F[3] : v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_min_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Max(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                (v1.V.F[0] > v2.V.F[0]) ? v1.V.F[0] : v2.V.F[0],
                (v1.V.F[1] > v2.V.F[1]) ? v1.V.F[1] : v2.V.F[1],
                (v1.V.F[2] > v2.V.F[2]) ? v1.V.F[2] : v2.V.F[2],
                (v1.V.F[3] > v2.V.F[3]) ? v1.V.F[3] : v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_max_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Round(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                RoundToNearest(v.V.F[0]),
                RoundToNearest(v.V.F[1]),
                RoundToNearest(v.V.F[2]),
                RoundToNearest(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Truncate(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 result;
        
        result.V.F[0] = 0.0F;

        for (size_t index = 0; index < 4; ++index)
        {
            if (BitIsNaN(v.V.U[index]))
            {
                result.V.U[index] = 0x7FC00000U;
            }
            else if (fabsf(v.V.F[index]) < 8388608.0F)
            {
                result.V.F[index] = static_cast<float>(static_cast<int32_t>(v.V.F[index]));
            }
            else
            {
                result.V.F[index] = v.V.F[index];
            }
        }

        return result;
#elif GRAPHYTE_HW_AVX
        return { _mm_round_ps(v.V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Floor(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                floorf(v.V.F[0]),
                floorf(v.V.F[1]),
                floorf(v.V.F[2]),
                floorf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_floor_ps(v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Ceiling(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                ceilf(v.V.F[0]),
                ceilf(v.V.F[1]),
                ceilf(v.V.F[2]),
                ceilf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_ceil_ps(v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Fract(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v.V.F[0] - floorf(v.V.F[0]),
                v.V.F[1] - floorf(v.V.F[1]),
                v.V.F[2] - floorf(v.V.F[2]),
                v.V.F[3] - floorf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_floor_ps(v.V);
        auto v_result = _mm_sub_ps(v.V, v_temp);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Clamp(Vector4 v, Vector4 min, Vector4 max) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 result = Vector4::Max(min, v);
        result = Vector4::Min(max, result);
        return result;
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_max_ps(min.V, v.V);
        v_result = _mm_min_ps(max.V, v_result);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Saturate(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Vector4 zero = Vector4::Zero();
        return Vector4::Clamp(v, zero, { Detail::VEC4_ONE_4.V });
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_max_ps(v.V, Detail::VEC4_ZERO_4.V);
        return { _mm_min_ps(v_result, Detail::VEC4_ONE_4.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Negate(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                -v.V.F[0],
                -v.V.F[1],
                -v.V.F[2],
                -v.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_zero = _mm_setzero_ps();
        return { _mm_sub_ps(v_zero, v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Add(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v1.V.F[0] + v2.V.F[0],
                v1.V.F[1] + v2.V.F[1],
                v1.V.F[2] + v2.V.F[2],
                v1.V.F[3] + v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_add_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Sum(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result;
        v_result.F[0] = v_result.F[1] = v_result.F[2] = v_result.F[3]
            = (v.V.F[0] + v.V.F[1] + v.V.F[2] + v.V.F[3]);
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_hadd_ps(v.V, v.V);
        return { _mm_hadd_ps(v_temp, v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::AddAngles(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_zero   = Vector4::Zero();
        auto v_result = Vector4::Add(v1, v2);
        auto v_mask   = Vector4::CompareLess(v_result, { Detail::VEC4_NEGATIVE_PI.V });
        auto v_offset = Vector4::Select(v_zero, { Detail::VEC4_2PI.V }, v_mask);
        v_mask        = Vector4::CompareGreaterEqual(v_result, { Detail::VEC4_PI.V });
        v_offset      = Vector4::Select(v_offset, { Detail::VEC4_NEGATIVE_2PI.V }, v_mask);
        v_result      = Vector4::Add(v_result, v_offset);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_add_ps(v1.V, v2.V);
        auto v_offset = _mm_cmplt_ps(v_result, Detail::VEC4_NEGATIVE_PI.V);
        v_offset = _mm_and_ps(v_offset, Detail::VEC4_2PI.V);
        v_result = _mm_add_ps(v_result, v_offset);
        v_offset = _mm_cmpge_ps(v_result, Detail::VEC4_PI.V);
        v_offset = _mm_and_ps(v_offset, Detail::VEC4_2PI.V);
        v_result = _mm_sub_ps(v_result, v_offset);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Subtract(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v1.V.F[0] - v2.V.F[0],
                v1.V.F[1] - v2.V.F[1],
                v1.V.F[2] - v2.V.F[2],
                v1.V.F[3] - v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sub_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SubtractAngles(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_zero = Vector4::Zero();
        auto v_result = Vector4::Subtract(v1, v2);
        auto v_mask = Vector4::CompareLess(v_result, { Detail::VEC4_NEGATIVE_PI.V });
        auto v_offset = Vector4::Select(v_zero, { Detail::VEC4_2PI.V }, v_mask);
        v_mask = Vector4::CompareGreaterEqual(v_result, { Detail::VEC4_PI.V });
        v_offset = Vector4::Select(v_offset, { Detail::VEC4_NEGATIVE_2PI.V }, v_mask);
        v_result = Vector4::Add(v_result, v_offset);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_sub_ps(v1.V, v2.V);
        auto v_offset = _mm_cmplt_ps(v_result, Detail::VEC4_NEGATIVE_2PI.V);
        v_offset = _mm_and_ps(v_offset, Detail::VEC4_2PI.V);
        v_result = _mm_add_ps(v_result, v_offset);
        v_offset = _mm_cmpge_ps(v_result, Detail::VEC4_PI.V);
        v_offset = _mm_and_ps(v_offset, Detail::VEC4_2PI);
        v_result = _mm_sub_ps(v_result, v_offset);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Multiply(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v1.V.F[0] * v2.V.F[0],
                v1.V.F[1] * v2.V.F[1],
                v1.V.F[2] * v2.V.F[2],
                v1.V.F[3] * v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_mul_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::MultiplyAdd(Vector4 v1, Vector4 v2, Vector4 v3) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v1.V.F[0] * v2.V.F[0] + v3.V.F[0],
                v1.V.F[1] * v2.V.F[1] + v3.V.F[1],
                v1.V.F[2] * v2.V.F[2] + v3.V.F[2],
                v1.V.F[3] * v2.V.F[3] + v3.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_FMA3
        return { _mm_fmadd_ps(v1.V, v2.V, v3.V) };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_mul_ps(v1.V, v2.V);
        return { _mm_add_ps(v_result, v3.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Divide(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v1.V.F[0] / v2.V.F[0],
                v1.V.F[1] / v2.V.F[1],
                v1.V.F[2] / v2.V.F[2],
                v1.V.F[3] / v2.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(v1.V, v2.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::NegativeMultiplySubtract(Vector4 v1, Vector4 v2, Vector4 v3) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v3.V.F[0] - (v1.V.F[0] * v2.V.F[0]),
                v3.V.F[1] - (v1.V.F[1] * v2.V.F[1]),
                v3.V.F[2] - (v1.V.F[2] * v2.V.F[2]),
                v3.V.F[3] - (v1.V.F[3] * v2.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_FMA3
        return { _mm_fnmadd_ps(v1.V, v2.V, v3.V) };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_mul_ps(v1.V, v2.V);
        return { _mm_sub_ps(v3.V, v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Scale(Vector4 v, float scale) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v.V.F[0] * scale,
                v.V.F[1] * scale,
                v.V.F[2] * scale,
                v.V.F[3] * scale,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_set_ps1(scale);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::ReciprocalEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                1.0F / v.V.F[0],
                1.0F / v.V.F[1],
                1.0F / v.V.F[2],
                1.0F / v.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rcp_ps(v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Reciprocal(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                1.0F / v.V.F[0],
                1.0F / v.V.F[1],
                1.0F / v.V.F[2],
                1.0F / v.V.F[3],
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_div_ps(Detail::VEC4_ONE_4.V, v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::SqrtEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Sqrt(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                sqrtf(v.V.F[0]),
                sqrtf(v.V.F[1]),
                sqrtf(v.V.F[2]),
                sqrtf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_sqrt_ps(v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::ReciprocalSqrtEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                1.0F / sqrtf(v.V.F[0]),
                1.0F / sqrtf(v.V.F[1]),
                1.0F / sqrtf(v.V.F[2]),
                1.0F / sqrtf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_rsqrt_ps(v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::ReciprocalSqrt(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                1.0F / sqrtf(v.V.F[0]),
                1.0F / sqrtf(v.V.F[1]),
                1.0F / sqrtf(v.V.F[2]),
                1.0F / sqrtf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_sqrt_ps(v.V);
        v_result = _mm_div_ps(Detail::VEC4_ONE_4.V, v_result);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Exp2(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                powf(2.0F, v.V.F[0]),
                powf(2.0F, v.V.F[1]),
                powf(2.0F, v.V.F[2]),
                powf(2.0F, v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_itrunc  = _mm_cvttps_epi32(v.V);
        auto v_ftrunc  = _mm_cvtepi32_ps(v_itrunc);
        auto v_y       = _mm_sub_ps(v.V, v_ftrunc);
        auto v_poly    = _mm_mul_ps(Detail::VEC4_EXP_EST_7.V, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_6.V, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_5.V, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_4.V, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_3.V, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_2.V, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_1.V, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_ONE_4.V, v_poly);
        auto v_biased  = _mm_add_epi32(v_itrunc, Detail::VEC4_EXPONENT_BIAS.ToM128I());
        v_biased       = _mm_slli_epi32(v_biased, 23);
        auto v_result0 = _mm_div_ps(_mm_castsi128_ps(v_biased), v_poly);
        v_biased       = _mm_add_epi32(v_itrunc, Detail::VEC4_VALUE253.ToM128I());
        v_biased       = _mm_slli_epi32(v_biased, 23);
        auto v_result1 = _mm_div_ps(_mm_castsi128_ps(v_biased), v_poly);
        v_result1      = _mm_mul_ps(Detail::VEC4_MIN_NORMAL, v_result1);
        auto v_comp    = _mm_cmplt_epi32(_mm_castps_si128(v.V), Detail::VEC4_BIN_128.ToM128I());
        auto v_select0 = _mm_and_si128(v_comp, _mm_castps_si128(v_result0));
        auto v_select1 = _mm_andnot_si128(v_comp, Detail::VEC4_INFINITY.ToM128I());
        auto v_result2 = _mm_or_si128(v_select0, v_select1);
        v_comp         = _mm_cmplt_epi32(v_itrunc, Detail::VEC4_SUBNORMAL_EXPONENT.ToM128I());
        v_select1      = _mm_and_si128(v_comp, _mm_castps_si128(v_result1));
        v_select0      = _mm_andnot_si128(v_comp, _mm_castps_si128(v_result0));
        auto v_result3 = _mm_or_si128(v_select0, v_select1);
        v_comp         = _mm_cmplt_epi32(_mm_castps_si128(v.V), Detail::VEC4_BIN_NEG_150.ToM128I());
        v_select0      = _mm_and_si128(v_comp, v_result3);
        v_select1      = _mm_andnot_si128(v_comp, Detail::VEC4_ZERO_4.ToM128I());
        auto v_result4 = _mm_or_si128(v_select0, v_select1);
        auto v_sign    = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_NEGATIVE_ZERO.ToM128I());
        v_comp         = _mm_cmpeq_epi32(v_sign, Detail::VEC4_NEGATIVE_ZERO.ToM128I());
        v_select0      = _mm_and_si128(v_comp, v_result4);
        v_select1      = _mm_andnot_si128(v_comp, v_result2);
        auto v_result5 = _mm_or_si128(v_select0, v_select1);
        auto v_t0      = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_t1      = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        v_t0           = _mm_cmpeq_epi32(v_t0, Detail::VEC4_ZERO_4.ToM128I());
        v_t1           = _mm_cmpeq_epi32(v_t1, Detail::VEC4_INFINITY.ToM128I());
        auto v_isnan   = _mm_andnot_si128(v_t0, v_t1);
        v_select0      = _mm_and_si128(v_isnan, Detail::VEC4_QNAN.ToM128I());
        v_select1      = _mm_andnot_si128(v_isnan, v_result5);
        auto v_result  = _mm_or_si128(v_select0, v_select1);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::ExpE(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                expf(v.V.F[0]),
                expf(v.V.F[1]),
                expf(v.V.F[2]),
                expf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_ve      = _mm_mul_ps(Detail::VEC4_LGE.V, v.V);
        auto v_itrunc  = _mm_cvttps_epi32(v_ve);
        auto v_ftrunc  = _mm_cvtepi32_ps(v_itrunc);
        auto v_y       = _mm_sub_ps(v_ve, v_ftrunc);
        auto v_poly    = _mm_mul_ps(Detail::VEC4_EXP_EST_7, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_6, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_5, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_4, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_3, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_2, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_EXP_EST_1, v_poly);
        v_poly         = _mm_mul_ps(v_poly, v_y);
        v_poly         = _mm_add_ps(Detail::VEC4_ONE_4, v_poly);
        auto v_biased  = _mm_add_epi32(v_itrunc, Detail::VEC4_EXPONENT_BIAS.ToM128I());
        v_biased       = _mm_slli_epi32(v_biased, 23);
        auto v_result0 = _mm_div_ps(_mm_castsi128_ps(v_biased), v_poly);
        v_biased       = _mm_add_epi32(v_itrunc, Detail::VEC4_VALUE253.ToM128I());
        v_biased       = _mm_slli_epi32(v_biased, 23);
        auto v_result1 = _mm_div_ps(_mm_castsi128_ps(v_biased), v_poly);
        v_result1      = _mm_mul_ps(Detail::VEC4_MIN_NORMAL, v_result1);
        auto v_comp    = _mm_cmplt_epi32(_mm_castps_si128(v_ve), Detail::VEC4_BIN_128.ToM128I());
        auto v_select0 = _mm_and_si128(v_comp, _mm_castps_si128(v_result0));
        auto v_select1 = _mm_andnot_si128(v_comp, Detail::VEC4_INFINITY.ToM128I());
        auto v_result2 = _mm_or_si128(v_select0, v_select1);
        v_comp         = _mm_cmplt_epi32(v_itrunc, Detail::VEC4_SUBNORMAL_EXPONENT.ToM128I());
        v_select1      = _mm_and_si128(v_comp, _mm_castps_si128(v_result1));
        v_select0      = _mm_andnot_si128(v_comp, _mm_castps_si128(v_result0));
        auto v_result3 = _mm_or_si128(v_select0, v_select1);
        v_comp         = _mm_cmplt_epi32(_mm_castps_si128(v_ve), Detail::VEC4_BIN_NEG_150.ToM128I());
        v_select0      = _mm_and_si128(v_comp, v_result3);
        v_select1      = _mm_andnot_si128(v_comp, Detail::VEC4_ZERO_4.ToM128I());
        auto v_result4 = _mm_or_si128(v_select0, v_select1);
        auto v_sign    = _mm_and_si128(_mm_castps_si128(v_ve), Detail::VEC4_NEGATIVE_ZERO.ToM128I());
        v_comp         = _mm_cmpeq_epi32(v_sign, Detail::VEC4_NEGATIVE_ZERO.ToM128I());
        v_select0      = _mm_and_si128(v_comp, v_result4);
        v_select1      = _mm_andnot_si128(v_comp, v_result2);
        auto v_result5 = _mm_or_si128(v_select0, v_select1);
        auto v_t0      = _mm_and_si128(_mm_castps_si128(v_ve), Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_t1      = _mm_and_si128(_mm_castps_si128(v_ve), Detail::VEC4_INFINITY.ToM128I());
        v_t0           = _mm_cmpeq_epi32(v_t0, Detail::VEC4_ZERO_4.ToM128I());
        v_t1           = _mm_cmpeq_epi32(v_t1, Detail::VEC4_INFINITY.ToM128I());
        auto v_isnan   = _mm_andnot_si128(v_t0, v_t1);
        v_select0      = _mm_and_si128(v_isnan, Detail::VEC4_QNAN.ToM128I());
        v_select1      = _mm_andnot_si128(v_isnan, v_result5);
        auto v_result  = _mm_or_si128(v_select0, v_select1);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Exp(Vector4 v) noexcept
    {
        return Vector4::Exp2(v);
    }

    mathinline Vector4 mathcall Vector4::Log2(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        const float scale = 1.4426950F;
        Detail::Vector4F32 v_result = { { {
                logf(v.V.F[0]) * scale,
                logf(v.V.F[1]) * scale,
                logf(v.V.F[2]) * scale,
                logf(v.V.F[3]) * scale,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_raw_biased       = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        auto v_trailing         = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_is_exponent_zero = _mm_cmpeq_epi32(Detail::VEC4_ZERO_4.ToM128I(), v_raw_biased);
        auto v_biased           = _mm_srli_epi32(v_raw_biased, 23);
        auto v_exponent_nor     = _mm_sub_epi32(v_biased, Detail::VEC4_EXPONENT_BIAS.ToM128I());
        auto v_trailing_nor     = v_trailing;
        auto v_leading          = Simd::GetLeadingBit(v_trailing);
        auto v_shift            = _mm_sub_epi32(Detail::VEC4_NUM_TRAILING.ToM128I(), v_leading);
        auto v_exponent_sub     = _mm_sub_epi32(Detail::VEC4_SUBNORMAL_EXPONENT.ToM128I(), v_shift);
        auto v_trailing_sub     = Simd::simd_multi_sll_epi32(v_trailing, v_shift);
        v_trailing_sub          = _mm_and_si128(v_trailing_sub, Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_select0          = _mm_and_si128(v_is_exponent_zero, v_exponent_sub);
        auto v_select1          = _mm_andnot_si128(v_is_exponent_zero, v_exponent_nor);
        auto v_e                = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_exponent_zero, v_trailing_sub);
        v_select1               = _mm_andnot_si128(v_is_exponent_zero, v_trailing_nor);
        auto v_t                = _mm_or_si128(v_select0, v_select1);
        auto v_tmp              = _mm_or_si128(Detail::VEC4_ONE_4.ToM128I(), v_t);
        auto v_y                = _mm_sub_ps(_mm_castsi128_ps(v_tmp), Detail::VEC4_ONE_4);
        auto v_log2             = _mm_mul_ps(Detail::VEC4_LOG_EST_7, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_6, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_5, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_4, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_3, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_2, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_1, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_0, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(v_log2, _mm_cvtepi32_ps(v_e));
        auto v_is_infinite      = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_MASK_ABS.ToM128I());
        v_is_infinite           = _mm_cmpeq_epi32(v_is_infinite, Detail::VEC4_INFINITY.ToM128I());
        auto v_is_greater_zero  = _mm_cmpgt_epi32(_mm_castps_si128(v.V), Detail::VEC4_ZERO_4.ToM128I());
        auto v_is_not_finite    = _mm_cmpgt_epi32(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        auto v_is_positive      = _mm_andnot_si128(v_is_not_finite, v_is_greater_zero);
        auto v_is_zero          = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_MASK_ABS.ToM128I());
        v_is_zero               = _mm_cmpeq_epi32(v_is_zero, Detail::VEC4_ZERO_4.ToM128I());
        auto v_t0               = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_t1               = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        v_t0                    = _mm_cmpeq_epi32(v_t0, Detail::VEC4_ZERO_4.ToM128I());
        v_t1                    = _mm_cmpeq_epi32(v_t1, Detail::VEC4_INFINITY.ToM128I());
        auto v_is_nan           = _mm_andnot_si128(v_t0, v_t1);
        v_select0               = _mm_and_si128(v_is_infinite, Detail::VEC4_INFINITY.ToM128I());
        v_select1               = _mm_andnot_si128(v_is_infinite, _mm_castps_si128(v_log2));
        auto v_result           = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_zero, Detail::VEC4_NEGATIVE_INFINITY.ToM128I());
        v_select1               = _mm_andnot_si128(v_is_zero, Detail::VEC4_NEGATIVE_QNAN.ToM128I());
        v_tmp                   = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_positive, v_result);
        v_select1               = _mm_andnot_si128(v_is_positive, v_tmp);
        v_result                = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_nan, Detail::VEC4_QNAN.ToM128I());
        v_select1               = _mm_andnot_si128(v_is_nan, v_result);
        v_result                = _mm_or_si128(v_select0, v_select1);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LogE(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                logf(v.V.F[0]),
                logf(v.V.F[1]),
                logf(v.V.F[2]),
                logf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_raw_biased       = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        auto v_trailing         = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_is_exponent_zero = _mm_cmpeq_epi32(Detail::VEC4_ZERO_4.ToM128I(), v_raw_biased);
        auto v_biased           = _mm_srli_epi32(v_raw_biased, 23);
        auto v_exponent_nor     = _mm_sub_epi32(v_biased, Detail::VEC4_EXPONENT_BIAS.ToM128I());
        auto v_trailing_nor     = v_trailing;
        auto v_leading          = Simd::GetLeadingBit(v_trailing);
        auto v_shift            = _mm_sub_epi32(Detail::VEC4_NUM_TRAILING.ToM128I(), v_leading);
        auto v_exponent_sub     = _mm_sub_epi32(Detail::VEC4_SUBNORMAL_EXPONENT.ToM128I(), v_shift);
        auto v_trailing_sub     = Simd::simd_multi_sll_epi32(v_trailing, v_shift);
        v_trailing_sub          = _mm_and_si128(v_trailing_sub, Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_select0          = _mm_and_si128(v_is_exponent_zero, v_exponent_sub);
        auto v_select1          = _mm_andnot_si128(v_is_exponent_zero, v_exponent_nor);
        auto v_e                = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_exponent_zero, v_trailing_sub);
        v_select1               = _mm_andnot_si128(v_is_exponent_zero, v_trailing_nor);
        auto v_t                = _mm_or_si128(v_select0, v_select1);
        auto v_tmp              = _mm_or_si128(Detail::VEC4_ONE_4.ToM128I(), v_t);
        auto v_y                = _mm_sub_ps(_mm_castsi128_ps(v_tmp), Detail::VEC4_ONE_4);
        auto v_log2             = _mm_mul_ps(Detail::VEC4_LOG_EST_7, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_6, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_5, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_4, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_3, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_2, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_1, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(Detail::VEC4_LOG_EST_0, v_log2);
        v_log2                  = _mm_mul_ps(v_log2, v_y);
        v_log2                  = _mm_add_ps(v_log2, _mm_cvtepi32_ps(v_e));
        v_log2                  = _mm_mul_ps(Detail::VEC4_INV_LGE.V, v_log2);
        auto v_is_infinite      = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_MASK_ABS.ToM128I());
        v_is_infinite           = _mm_cmpeq_epi32(v_is_infinite, Detail::VEC4_INFINITY.ToM128I());
        auto v_is_greater_zero  = _mm_cmpgt_epi32(_mm_castps_si128(v.V), Detail::VEC4_ZERO_4.ToM128I());
        auto v_is_not_finite    = _mm_cmpgt_epi32(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        auto v_is_positive      = _mm_andnot_si128(v_is_not_finite, v_is_greater_zero);
        auto v_is_zero          = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_MASK_ABS.ToM128I());
        v_is_zero               = _mm_cmpeq_epi32(v_is_zero, Detail::VEC4_ZERO_4.ToM128I());
        auto v_t0               = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_QNAN_TEST.ToM128I());
        auto v_t1               = _mm_and_si128(_mm_castps_si128(v.V), Detail::VEC4_INFINITY.ToM128I());
        v_t0                    = _mm_cmpeq_epi32(v_t0, Detail::VEC4_ZERO_4.ToM128I());
        v_t1                    = _mm_cmpeq_epi32(v_t1, Detail::VEC4_INFINITY.ToM128I());
        auto v_is_nan           = _mm_andnot_si128(v_t0, v_t1);
        v_select0               = _mm_and_si128(v_is_infinite, Detail::VEC4_INFINITY.ToM128I());
        v_select1               = _mm_andnot_si128(v_is_infinite, _mm_castps_si128(v_log2));
        auto v_result           = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_zero, Detail::VEC4_NEGATIVE_INFINITY.ToM128I());
        v_select1               = _mm_andnot_si128(v_is_zero, Detail::VEC4_NEGATIVE_QNAN.ToM128I());
        v_tmp                   = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_positive, v_result);
        v_select1               = _mm_andnot_si128(v_is_positive, v_tmp);
        v_result                = _mm_or_si128(v_select0, v_select1);
        v_select0               = _mm_and_si128(v_is_nan, Detail::VEC4_QNAN.ToM128I());
        v_select1               = _mm_andnot_si128(v_is_nan, v_result);
        v_result                = _mm_or_si128(v_select0, v_select1);
        return { _mm_castsi128_ps(v_result) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Log(Vector4 v) noexcept
    {
        return Vector4::Log2(v);
    }

    mathinline Vector4 mathcall Vector4::Pow(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                powf(v1.V.F[0], v2.V.F[0]),
                powf(v1.V.F[1], v2.V.F[1]),
                powf(v1.V.F[2], v2.V.F[2]),
                powf(v1.V.F[3], v2.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        alignas(16) float a[4];
        alignas(16) float b[4];
        _mm_store_ps(a, v1.V);
        _mm_store_ps(b, v2.V);
        auto v_result = _mm_setr_ps(
            powf(a[0], b[0]),
            powf(a[1], b[1]),
            powf(a[2], b[2]),
            powf(a[3], b[3]));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Abs(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                fabsf(v.V.F[0]),
                fabsf(v.V.F[1]),
                fabsf(v.V.F[2]),
                fabsf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_setzero_ps();
        v_result = _mm_sub_ps(v_result, v.V);
        v_result = _mm_max_ps(v_result, v.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Mod(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
#if false
        // don't work
        auto quotient = Vector4::Divide(v1, v2);
        quotient = Vector4::Truncate(quotient);
        auto result = Vector4::NegativeMultiplySubtract(v2, quotient, v1);
        return result;
#else
        Detail::Vector4F32 v_result = { { {
                fmodf(v1.V.F[0], v2.V.F[0]),
                fmodf(v1.V.F[1], v2.V.F[1]),
                fmodf(v1.V.F[2], v2.V.F[2]),
                fmodf(v1.V.F[3], v2.V.F[3]),
            } } };
        return { v_result.V };
#endif
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_div_ps(v1.V, v2.V);
        v_result = _mm_round_ps(v_result, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
        v_result = _mm_mul_ps(v_result, v2.V);
        v_result = _mm_sub_ps(v1.V, v_result);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ModAngles(Vector4 angles) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v = Vector4::Multiply(angles, { Detail::VEC4_RECIPROCAL_2PI.V });
        v = Vector4::Round(v);
        auto result = Vector4::NegativeMultiplySubtract({ Detail::VEC4_2PI.V }, v, angles);
        return result;
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_mul_ps(angles.V, Detail::VEC4_RECIPROCAL_2PI.V);
        v_result = _mm_round_ps(v_result, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
        v_result = _mm_mul_ps(v_result, Detail::VEC4_2PI.V);
        v_result = _mm_sub_ps(angles.V, v_result);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Sin(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto x           = Vector4::ModAngles(v);
        auto v_sign      = _mm_and_ps(x.V, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_c         = _mm_or_ps(Detail::VEC4_PI.V, v_sign);
        auto v_absx      = _mm_andnot_ps(v_sign, x.V);
        auto v_rflx      = _mm_sub_ps(v_c, x.V);
        auto v_comp      = _mm_cmple_ps(v_absx, Detail::VEC4_HALF_PI.V);
        auto v_select0   = _mm_and_ps(v_comp, x.V);
        auto v_select1   = _mm_andnot_ps(v_comp, v_rflx);
        x.V              = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(x.V, x.V);
        auto v_sc1       = Detail::VEC4_SIN_COEFFICIENTS_1.V;
        auto v_constants = _mm_permute_ps(v_sc1, _MM_SHUFFLE(0, 0, 0, 0));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        auto v_sc0       = Detail::VEC4_SIN_COEFFICIENTS_0.V;
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(3, 3, 3, 3));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4.V);
        v_result         = _mm_mul_ps(v_result, x.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Cos(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto x           = Vector4::ModAngles(v);
        auto v_sign      = _mm_and_ps(x.V, Detail::VEC4_NEGATIVE_ZERO);
        auto v_c         = _mm_or_ps(Detail::VEC4_PI, v_sign);
        auto v_absx      = _mm_andnot_ps(v_sign, x.V);
        auto v_rflx      = _mm_sub_ps(v_c, x.V);
        auto v_comp      = _mm_cmple_ps(v_absx, Detail::VEC4_HALF_PI);
        auto v_select0   = _mm_and_ps(v_comp, x.V);
        auto v_select1   = _mm_andnot_ps(v_comp, v_rflx);
        x.V              = _mm_or_ps(v_select0, v_select1);
        v_select0        = _mm_and_ps(v_comp, Detail::VEC4_ONE_4);
        v_select1        = _mm_andnot_ps(v_comp, Detail::VEC4_NEGATIVE_ONE_4);
        v_sign           = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(x.V, x.V);
        auto v_cc1       = Detail::VEC4_COS_COEFFICIENTS_1;
        auto v_constants = _mm_permute_ps(v_cc1, _MM_SHUFFLE(0, 0, 0, 0));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        auto v_cc0       = Detail::VEC4_COS_COEFFICIENTS_0;
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(3, 3, 3, 3));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4);
        v_result         = _mm_mul_ps(v_result, v_sign);
        return { v_result };
#endif
    }

    mathinline void mathcall Vector4::SinCos(Vector4* out_sin, Vector4* out_cos, Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_sin = { { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };
        Detail::Vector4F32 v_cos = { { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };

        (*out_sin).V = v_sin.V;
        (*out_cos).V = v_cos.V;
#elif GRAPHYTE_HW_AVX
        auto x           = Vector4::ModAngles(v);
        auto v_sign      = _mm_and_ps(x.V, Detail::VEC4_NEGATIVE_ZERO);
        auto v_c         = _mm_or_ps(Detail::VEC4_PI, v_sign);
        auto v_absx      = _mm_andnot_ps(v_sign, x.V);
        auto v_rflx      = _mm_sub_ps(v_c, x.V);
        auto v_comp      = _mm_cmple_ps(v_absx, Detail::VEC4_HALF_PI);
        auto v_select0   = _mm_and_ps(v_comp, x.V);
        auto v_select1   = _mm_andnot_ps(v_comp, v_rflx);
        x.V              = _mm_or_ps(v_select0, v_select1);
        v_select0        = _mm_and_ps(v_comp, Detail::VEC4_ONE_4);
        v_select1        = _mm_andnot_ps(v_comp, Detail::VEC4_NEGATIVE_ONE_4);
        v_sign           = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(x.V, x.V);
        auto v_sc1       = Detail::VEC4_SIN_COEFFICIENTS_1;
        auto v_constants = _mm_permute_ps(v_sc1, _MM_SHUFFLE(0, 0, 0, 0));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        auto v_sc0       = Detail::VEC4_SIN_COEFFICIENTS_0;
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(3, 3, 3, 3));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sc0, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4);
        v_result         = _mm_mul_ps(v_result, x.V);
        out_sin->V       = v_result;
        auto v_cc1       = Detail::VEC4_COS_COEFFICIENTS_1;
        v_constants      = _mm_permute_ps(v_cc1, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_mul_ps(v_constants, v_x2);
        auto v_cc0       = Detail::VEC4_COS_COEFFICIENTS_0;
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(3, 3, 3, 3));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cc0, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4);
        v_result         = _mm_mul_ps(v_result, v_sign);
        out_cos->V       = v_result;
#endif
    }

    mathinline Vector4 mathcall Vector4::Tan(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                tanf(v.V.F[0]),
                tanf(v.V.F[1]),
                tanf(v.V.F[2]),
                tanf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 TanCoefficients0 = { { {
                1.0F,
                -4.667168334e-1F,
                2.566383229e-2F,
                -3.118153191e-4F
            } } };
        static const Detail::Vector4F32 TanCoefficients1 = { { {
                4.981943399e-7F,
                -1.333835001e-1F,
                3.424887824e-3F,
                -1.786170734e-5F
            } } };
        static const Detail::Vector4F32 TanConstants = { { {
                1.570796371F,
                6.077100628e-11F,
                0.000244140625F,
                0.63661977228F
            } } };
        static const Detail::Vector4U32 Mask = { { {
                0x1,
                0x1,
                0x1,
                0x1
            } } };

        auto v_two_div_pi                     = Vector4::SplatW({ TanConstants.V });
        auto v_zero                           = Vector4::Zero();
        auto v_c0                             = Vector4::SplatX({ TanConstants.V });
        auto v_c1                             = Vector4::SplatY({ TanConstants.V });
        auto v_epsilon                        = Vector4::SplatZ({ TanConstants.V });
        auto v_va                             = Vector4::Multiply(v, v_two_div_pi);
        v_va                                  = Vector4::Round(v_va);
        auto v_vc                             = Vector4::NegativeMultiplySubtract(v_va, v_c0, v);
        auto v_vb                             = Vector4::Abs(v_va);
        v_vc                                  = Vector4::NegativeMultiplySubtract(v_va, v_c1, v_vc);
        reinterpret_cast<__m128i *>(&v_vb.V)[0] = _mm_cvttps_epi32(v_vb.V);
        auto v_vc2                            = Vector4::Multiply(v_vc, v_vc);
        auto v_t7                             = Vector4::SplatW({ TanCoefficients1.V });
        auto v_t6                             = Vector4::SplatZ({ TanCoefficients1.V });
        auto v_t4                             = Vector4::SplatX({ TanCoefficients1.V });
        auto v_t3                             = Vector4::SplatW({ TanCoefficients0.V });
        auto v_t5                             = Vector4::SplatY({ TanCoefficients1.V });
        auto v_t2                             = Vector4::SplatZ({ TanCoefficients0.V });
        auto v_t1                             = Vector4::SplatY({ TanCoefficients0.V });
        auto v_t0                             = Vector4::SplatX({ TanCoefficients0.V });
        auto v_vb_is_even                     = Vector4::MaskAndUInt(v_vb, { Mask.V });
        v_vb_is_even                          = Vector4::MaskCompareEqual(v_vb_is_even, v_zero);
        auto v_n                              = Vector4::MultiplyAdd(v_vc2, v_t7, v_t6);
        auto v_d                              = Vector4::MultiplyAdd(v_vc2, v_t4, v_t3);
        v_n                                   = Vector4::MultiplyAdd(v_vc2, v_n, v_t5);
        v_d                                   = Vector4::MultiplyAdd(v_vc2, v_d, v_t2);
        v_n                                   = Vector4::Multiply(v_vc2, v_n);
        v_d                                   = Vector4::MultiplyAdd(v_vc2, v_d, v_t1);
        v_n                                   = Vector4::MultiplyAdd(v_vc, v_n, v_vc);
        auto v_vc_near_zero                   = Vector4::CompareInBounds(v_vc, v_epsilon);
        v_d                                   = Vector4::MultiplyAdd(v_vc2, v_d, v_t0);
        v_n                                   = Vector4::Select(v_n, v_vc, v_vc_near_zero);
        v_d                                   = Vector4::Select(v_d, { Detail::VEC4_ONE_4.V }, v_vc_near_zero);
        auto v_r0                             = Vector4::Negate(v_n);
        auto v_r1                             = Vector4::Divide(v_n, v_d);
        v_r0                                  = Vector4::Divide(v_d, v_r0);
        auto v_v_is_zero                      = Vector4::CompareEqual(v, v_zero);
        auto v_result                         = Vector4::Select(v_r0, v_r1, v_vb_is_even);
        v_result                              = Vector4::Select(v_result, v_zero, v_v_is_zero);
        return v_result;
#endif
    }

    mathinline Vector4 mathcall Vector4::SinH(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                sinhf(v.V.F[0]),
                sinhf(v.V.F[1]),
                sinhf(v.V.F[2]),
                sinhf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 v_scale = { { {
                1.442695040888963F,
                1.442695040888963F,
                1.442695040888963F,
                1.442695040888963F
            } } };

        auto v_v1 = _mm_mul_ps(v.V, v_scale.V);
        v_v1      = _mm_add_ps(v_v1, Detail::VEC4_NEGATIVE_ONE_4.V);
        auto v_v2 = _mm_mul_ps(v.V, v_scale.V);
        v_v2      = _mm_sub_ps(Detail::VEC4_NEGATIVE_ONE_4.V, v_v2);
        auto v_e1 = Vector4::Exp({ v_v1 }).V;
        auto v_e2 = Vector4::Exp({ v_v2 }).V;

        return { _mm_sub_ps(v_e1, v_e2) };
#endif
    }

    mathinline Vector4 mathcall Vector4::CosH(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                coshf(v.V.F[0]),
                coshf(v.V.F[1]),
                coshf(v.V.F[2]),
                coshf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 v_scale = { { {
                1.442695040888963F,
                1.442695040888963F,
                1.442695040888963F,
                1.442695040888963F
            } } };

        auto v_v1 = _mm_mul_ps(v.V, v_scale.V);
        v_v1      = _mm_add_ps(v_v1, Detail::VEC4_NEGATIVE_ONE_4.V);
        auto v_v2 = _mm_mul_ps(v.V, v_scale.V);
        v_v2      = _mm_sub_ps(Detail::VEC4_NEGATIVE_ONE_4.V, v_v2);
        auto v_e1 = Vector4::Exp({ v_v1 }).V;
        auto v_e2 = Vector4::Exp({ v_v2 }).V;
        return { _mm_add_ps(v_e1, v_e2) };
#endif
    }

    mathinline Vector4 mathcall Vector4::TanH(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                tanhf(v.V.F[0]),
                tanhf(v.V.F[1]),
                tanhf(v.V.F[2]),
                tanhf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 v_scale = { { {
                2.8853900817779268F,
                2.8853900817779268F,
                2.8853900817779268F,
                2.8853900817779268F
            } } };
        auto v_e = _mm_mul_ps(v.V, v_scale.V);
        v_e      = Vector4::Exp({ v_e }).V;
        v_e      = _mm_mul_ps(v_e, Detail::VEC4_ONE_HALF_4.V);
        v_e      = _mm_add_ps(v_e, Detail::VEC4_ONE_HALF_4.V);
        v_e      = _mm_div_ps(Detail::VEC4_ONE_4.V, v_e);
        v_e      = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_e);
        return { v_e };
#endif
    }

    mathinline Vector4 mathcall Vector4::ASin(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                asinf(v.V.F[0]),
                asinf(v.V.F[1]),
                asinf(v.V.F[2]),
                asinf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_nonnegative      = _mm_cmpge_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_mvalue           = _mm_sub_ps(Detail::VEC4_ZERO_4.V, v.V);
        auto v_x                = _mm_max_ps(v.V, v_mvalue);
        auto v_one_mvalue       = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_x);
        auto v_clamp_one_mvalue = _mm_max_ps(Detail::VEC4_ZERO_4.V, v_one_mvalue);
        auto v_root             = _mm_sqrt_ps(v_clamp_one_mvalue);
        auto v_ac1              = Detail::VEC4_ARC_COEFFICIENTS_1.V;
        auto v_constants        = _mm_permute_ps(v_ac1, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_t0               = _mm_mul_ps(v_constants, v_x);
        v_constants             = _mm_permute_ps(v_ac1, _MM_SHUFFLE(2, 2, 2, 2));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac1, _MM_SHUFFLE(1, 1, 1, 1));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac1, _MM_SHUFFLE(0, 0, 0, 0));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        auto v_ac0              = Detail::VEC4_ARC_COEFFICIENTS_0.V;
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(3, 3, 3, 3));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(2, 2, 2, 2));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(1, 1, 1, 1));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(0, 0, 0, 0));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_root);
        auto v_t1               = _mm_sub_ps(Detail::VEC4_PI.V, v_t0);
        v_t0                    = _mm_and_ps(v_nonnegative, v_t0);
        v_t1                    = _mm_andnot_ps(v_nonnegative, v_t1);
        v_t0                    = _mm_or_ps(v_t0, v_t1);
        v_t0                    = _mm_sub_ps(Detail::VEC4_HALF_PI.V, v_t0);
        return { v_t0 };
#endif
    }

    mathinline Vector4 mathcall Vector4::ACos(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                acosf(v.V.F[0]),
                acosf(v.V.F[1]),
                acosf(v.V.F[2]),
                acosf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_nonnegative      = _mm_cmpge_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_mvalue           = _mm_sub_ps(Detail::VEC4_ZERO_4.V, v.V);
        auto v_x                = _mm_max_ps(v.V, v_mvalue);
        auto v_one_mvalue       = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_x);
        auto v_clamp_one_mvalue = _mm_max_ps(Detail::VEC4_ZERO_4.V, v_one_mvalue);
        auto v_root             = _mm_sqrt_ps(v_clamp_one_mvalue);
        auto v_ac1              = Detail::VEC4_ARC_COEFFICIENTS_1.V;
        auto v_constants        = _mm_permute_ps(v_ac1, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_t0               = _mm_mul_ps(v_constants, v_x);
        v_constants             = _mm_permute_ps(v_ac1, _MM_SHUFFLE(2, 2, 2, 2));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac1, _MM_SHUFFLE(1, 1, 1, 1));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac1, _MM_SHUFFLE(0, 0, 0, 0));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        auto v_ac0              = Detail::VEC4_ARC_COEFFICIENTS_0.V;
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(3, 3, 3, 3));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(2, 2, 2, 2));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(1, 1, 1, 1));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_x);
        v_constants             = _mm_permute_ps(v_ac0, _MM_SHUFFLE(0, 0, 0, 0));
        v_t0                    = _mm_add_ps(v_t0, v_constants);
        v_t0                    = _mm_mul_ps(v_t0, v_root);
        auto v_t1               = _mm_sub_ps(Detail::VEC4_PI.V, v_t0);
        v_t0                    = _mm_and_ps(v_nonnegative, v_t0);
        v_t1                    = _mm_andnot_ps(v_nonnegative, v_t1);
        v_t0                    = _mm_or_ps(v_t0, v_t1);
        return { v_t0 };
#endif
    }

    mathinline Vector4 mathcall Vector4::ATan(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                atanf(v.V.F[0]),
                atanf(v.V.F[1]),
                atanf(v.V.F[2]),
                atanf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_abs_v     = Vector4::Abs(v).V;
        auto v_inv_v     = _mm_div_ps(Detail::VEC4_ONE_4.V, v.V);
        auto v_comp      = _mm_cmpgt_ps(v.V, Detail::VEC4_ONE_4.V);
        auto v_select0   = _mm_and_ps(v_comp, Detail::VEC4_ONE_4.V);
        auto v_select1   = _mm_andnot_ps(v_comp, Detail::VEC4_NEGATIVE_ONE_4.V);
        auto v_sign      = _mm_or_ps(v_select0, v_select1);
        v_comp           = _mm_cmple_ps(v_abs_v, Detail::VEC4_ONE_4.V);
        v_select0        = _mm_and_ps(v_comp, Detail::VEC4_ZERO_4.V);
        v_select1        = _mm_andnot_ps(v_comp, v_sign);
        v_sign           = _mm_or_ps(v_select0, v_select1);
        v_select0        = _mm_and_ps(v_comp, v.V);
        v_select1        = _mm_andnot_ps(v_comp, v_inv_v);
        auto v_x         = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(v_x, v_x);
        auto v_tc1       = Detail::VEC4_ATAN_COEFFICIENTS_1.V;
        auto v_constants = _mm_permute_ps(v_tc1, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        v_constants      = _mm_permute_ps(v_tc1, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_tc1, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_tc1, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        auto v_tc0       = Detail::VEC4_ATAN_COEFFICIENTS_0.V;
        v_constants      = _mm_permute_ps(v_tc0, _MM_SHUFFLE(3, 3, 3, 3));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_tc0, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_tc0, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_tc0, _MM_SHUFFLE(0, 0, 0, 0));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4.V);
        v_result         = _mm_mul_ps(v_result, v_x);
        auto v_result1   = _mm_mul_ps(v_sign, Detail::VEC4_HALF_PI.V);
        v_result1        = _mm_sub_ps(v_result1, v_result);
        v_comp           = _mm_cmpeq_ps(v_sign, Detail::VEC4_ZERO_4.V);
        v_select0        = _mm_and_ps(v_comp, v_result);
        v_select1        = _mm_andnot_ps(v_comp, v_result1);
        v_result         = _mm_or_ps(v_select0, v_select1);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ATan2(Vector4 y, Vector4 x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                atan2f(y.V.F[0], x.V.F[0]),
                atan2f(y.V.F[1], x.V.F[1]),
                atan2f(y.V.F[2], x.V.F[2]),
                atan2f(y.V.F[3], x.V.F[3]),
            } } };
        return { v_result.V };
#else
        static const Detail::Vector4F32 v_atan2_constants = { { {
                Maths::PI<float>,
                Maths::PI_OVER_2<float>,
                Maths::PI_OVER_4<float>,
                Maths::PI<float> * 3.0F / 4.0F
            } } };

        auto v_zero               = Vector4::Zero();
        auto v_atan_result_valid  = Vector4::MaskTrue();
        auto v_pi                 = Vector4::SplatX({ v_atan2_constants.V });
        auto v_pi_over_two        = Vector4::SplatY({ v_atan2_constants.V });
        auto v_pi_over_four       = Vector4::SplatZ({ v_atan2_constants.V });
        auto v_three_pi_over_four = Vector4::SplatW({ v_atan2_constants.V });
        auto v_y_equals_zero      = Vector4::CompareEqual(y, v_zero);
        auto v_x_equals_zero      = Vector4::CompareEqual(x, v_zero);
        auto v_x_is_positive      = Vector4::MaskAndUInt(x, { Detail::VEC4_NEGATIVE_ZERO.V });
        v_x_is_positive           = Vector4::MaskCompareEqual(v_x_is_positive, v_zero);
        auto v_y_equals_infinity  = Vector4::CompareIsInfinite(y);
        auto v_x_equals_infinity  = Vector4::CompareIsInfinite(x);
        auto v_y_sign             = Vector4::MaskAndUInt(y, { Detail::VEC4_NEGATIVE_ZERO.V });
        v_pi                      = Vector4::MaskOrUInt(v_pi, v_y_sign);
        v_pi_over_two             = Vector4::MaskOrUInt(v_pi_over_two, v_y_sign);
        v_pi_over_four            = Vector4::MaskOrUInt(v_pi_over_four, v_y_sign);
        v_three_pi_over_four      = Vector4::MaskOrUInt(v_three_pi_over_four, v_y_sign);
        auto v_r1                 = Vector4::Select(v_pi, v_y_sign, v_x_is_positive);
        auto v_r2                 = Vector4::Select(v_atan_result_valid, v_pi_over_two, v_x_equals_zero);
        auto v_r3                 = Vector4::Select(v_r2, v_r1, v_y_equals_zero);
        auto v_r4                 = Vector4::Select(v_three_pi_over_four, v_pi_over_four, v_x_is_positive);
        auto v_r5                 = Vector4::Select(v_pi_over_two, v_r4, v_x_equals_infinity);
        auto v_result             = Vector4::Select(v_r3, v_r5, v_y_equals_infinity);
        v_atan_result_valid       = Vector4::MaskCompareEqual(v_result, v_atan_result_valid);
        auto v_v                  = Vector4::Divide(y, x);
        auto v_r0                 = Vector4::ATan(v_v);
        v_r1                      = Vector4::Select(v_pi, { Detail::VEC4_NEGATIVE_ZERO.V }, v_x_is_positive);
        v_r2                      = Vector4::Add(v_r0, v_r1);
        return Vector4::Select(v_result, v_r2, v_atan_result_valid);
#endif
    }

    mathinline Vector4 mathcall Vector4::SinEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_x         = Vector4::ModAngles(v).V;
        auto v_sign      = _mm_and_ps(v_x, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_c         = _mm_or_ps(Detail::VEC4_PI.V, v_sign);
        auto v_absx      = _mm_andnot_ps(v_sign, v_x);
        auto v_rflx      = _mm_sub_ps(v_c, v_x);
        auto v_comp      = _mm_cmple_ps(v_absx, Detail::VEC4_HALF_PI.V);
        auto v_select0   = _mm_and_ps(v_comp, v_x);
        auto v_select1   = _mm_andnot_ps(v_comp, v_rflx);
        v_x              = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(v_x, v_x);
        auto v_sec       = Detail::VEC4_SIN_COEFFICIENTS_1.V;
        auto v_constants = _mm_permute_ps(v_sec, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        v_constants      = _mm_permute_ps(v_sec, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sec, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4.V);
        v_result         = _mm_mul_ps(v_result, v_x);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::CosEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_x         = Vector4::ModAngles(v).V;
        auto v_sign      = _mm_and_ps(v_x, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_c         = _mm_or_ps(Detail::VEC4_PI.V, v_sign);
        auto v_absx      = _mm_andnot_ps(v_sign, v_x);
        auto v_rflx      = _mm_sub_ps(v_c, v_x);
        auto v_comp      = _mm_cmple_ps(v_absx, Detail::VEC4_HALF_PI.V);
        auto v_select0   = _mm_and_ps(v_comp, v_x);
        auto v_select1   = _mm_andnot_ps(v_comp, v_rflx);
        v_x              = _mm_or_ps(v_select0, v_select1);
        v_select0        = _mm_and_ps(v_comp, Detail::VEC4_ONE_4.V);
        v_select1        = _mm_andnot_ps(v_comp, Detail::VEC4_NEGATIVE_ONE_4.V);
        v_sign           = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(v_x, v_x);
        auto v_cec       = Detail::VEC4_COS_COEFFICIENTS_1.V;
        auto v_constants = _mm_permute_ps(v_cec, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        v_constants      = _mm_permute_ps(v_cec, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cec, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4.V);
        v_result         = _mm_mul_ps(v_result, v_sign);
        return { v_result };
#endif
    }

    mathinline void mathcall Vector4::SinCosEst(Vector4* out_sin, Vector4* out_cos, Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_sin = { { {
                sinf(v.V.F[0]),
                sinf(v.V.F[1]),
                sinf(v.V.F[2]),
                sinf(v.V.F[3]),
            } } };
        Detail::Vector4F32 v_cos = { { {
                cosf(v.V.F[0]),
                cosf(v.V.F[1]),
                cosf(v.V.F[2]),
                cosf(v.V.F[3]),
            } } };

        out_sin->V = v_sin.V;
        out_cos->V = v_cos.V;
#elif GRAPHYTE_HW_AVX
        auto v_x         = Vector4::ModAngles(v).V;
        auto v_sign      = _mm_and_ps(v_x, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_c         = _mm_or_ps(Detail::VEC4_PI.V, v_sign);
        auto v_absx      = _mm_andnot_ps(v_sign, v_x);
        auto v_rflx      = _mm_sub_ps(v_c, v_x);
        auto v_comp      = _mm_cmple_ps(v_absx, Detail::VEC4_HALF_PI.V);
        auto v_select0   = _mm_and_ps(v_comp, v_x);
        auto v_select1   = _mm_andnot_ps(v_comp, v_rflx);
        v_x              = _mm_or_ps(v_select0, v_select1);
        v_select0        = _mm_and_ps(v_comp, Detail::VEC4_ONE_4.V);
        v_select1        = _mm_andnot_ps(v_comp, Detail::VEC4_NEGATIVE_ONE_4.V);
        v_sign           = _mm_or_ps(v_select0, v_select1);
        auto v_x2        = _mm_mul_ps(v_x, v_x);
        auto v_sec       = Detail::VEC4_SIN_COEFFICIENTS_1.V;
        auto v_constants = _mm_permute_ps(v_sec, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_result    = _mm_mul_ps(v_constants, v_x2);
        v_constants      = _mm_permute_ps(v_sec, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_sec, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4.V);
        v_result         = _mm_mul_ps(v_result, v_x);
        out_sin->V       = v_result;
        auto v_cec       = Detail::VEC4_COS_COEFFICIENTS_1.V;
        v_constants      = _mm_permute_ps(v_cec, _MM_SHUFFLE(3, 3, 3, 3));
        v_result         = _mm_mul_ps(v_constants, v_x2);
        v_constants      = _mm_permute_ps(v_cec, _MM_SHUFFLE(2, 2, 2, 2));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_constants      = _mm_permute_ps(v_cec, _MM_SHUFFLE(1, 1, 1, 1));
        v_result         = _mm_add_ps(v_result, v_constants);
        v_result         = _mm_mul_ps(v_result, v_x2);
        v_result         = _mm_add_ps(v_result, Detail::VEC4_ONE_4.V);
        v_result         = _mm_mul_ps(v_result, v_sign);
        out_cos->V       = v_result;
#endif
    }

    mathinline Vector4 mathcall Vector4::TanEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                tanf(v.V.F[0]),
                tanf(v.V.F[1]),
                tanf(v.V.F[2]),
                tanf(v.V.F[3]),
            } } };
        return { v_result.V };
#else
        auto v_one_over_pi = Vector4::SplatW({ Detail::VEC4_TAN_EST_COEFFICIENTS_0.V });
        auto v_v1          = Vector4::Multiply(v, v_one_over_pi);
        v_v1               = Vector4::Round(v_v1);
        v_v1               = Vector4::NegativeMultiplySubtract({ Detail::VEC4_PI.V }, v_v1, v);
        auto v_t0          = Vector4::SplatX({ Detail::VEC4_TAN_EST_COEFFICIENTS_0.V });
        auto v_t1          = Vector4::SplatY({ Detail::VEC4_TAN_EST_COEFFICIENTS_0.V });
        auto v_t2          = Vector4::SplatZ({ Detail::VEC4_TAN_EST_COEFFICIENTS_0.V });
        auto v_v2t2        = Vector4::NegativeMultiplySubtract(v_v1, v_v1, v_t2);
        auto v_v2          = Vector4::Multiply(v_v1, v_v1);
        auto v_v1t0        = Vector4::Multiply(v_v1, v_t0);
        auto v_v1t1        = Vector4::Multiply(v_v1, v_t1);
        auto v_d           = Vector4::ReciprocalEst(v_v2t2);
        auto v_n           = Vector4::MultiplyAdd(v_v2, v_v1t1, v_v1t0);
        return Vector4::Multiply(v_n, v_d);
#endif
    }

    mathinline Vector4 mathcall Vector4::ASinEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                asinf(v.V.F[0]),
                asinf(v.V.F[1]),
                asinf(v.V.F[2]),
                asinf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_nonnegative = _mm_cmpge_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_mvalue = _mm_sub_ps(Detail::VEC4_ZERO_4.V, v.V);
        auto v_x = _mm_max_ps(v.V, v_mvalue);
        auto v_one_mvalue = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_x);
        auto v_clamp_one_mvalue = _mm_max_ps(Detail::VEC4_ZERO_4.V, v_one_mvalue);
        auto v_root = _mm_sqrt_ps(v_clamp_one_mvalue);
        auto v_aec = Detail::VEC4_ARC_EST_COEFFICIENTS_0.V;

        auto v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_t0 = _mm_mul_ps(v_constants, v_x);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(2, 2, 2, 2));
        v_t0 = _mm_add_ps(v_t0, v_constants);
        v_t0 = _mm_mul_ps(v_t0, v_x);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(1, 1, 1, 1));
        v_t0 = _mm_add_ps(v_t0, v_constants);
        v_t0 = _mm_mul_ps(v_t0, v_x);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(0, 0, 0, 0));
        v_t0 = _mm_add_ps(v_t0, v_constants);
        v_t0 = _mm_mul_ps(v_t0, v_root);

        auto v_t1 = _mm_sub_ps(Detail::VEC4_PI.V, v_t0);
        v_t0 = _mm_and_ps(v_nonnegative, v_t0);
        v_t1 = _mm_andnot_ps(v_nonnegative, v_t1);
        v_t0 = _mm_or_ps(v_t0, v_t1);
        v_t0 = _mm_sub_ps(Detail::VEC4_HALF_PI.V, v_t0);
        return { v_t0 };
#endif
    }

    mathinline Vector4 mathcall Vector4::ACosEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                acosf(v.V.F[0]),
                acosf(v.V.F[1]),
                acosf(v.V.F[2]),
                acosf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_nonnegative = _mm_cmpge_ps(v.V, Detail::VEC4_ZERO_4.V);
        auto v_mvalue = _mm_sub_ps(Detail::VEC4_ZERO_4.V, v.V);
        auto v_x = _mm_max_ps(v.V, v_mvalue);

        auto v_one_mvalue = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_x);
        auto v_clamp_one_mvalue = _mm_max_ps(Detail::VEC4_ZERO_4.V, v_one_mvalue);
        auto v_root = _mm_sqrt_ps(v_clamp_one_mvalue);

        auto v_aec = Detail::VEC4_ARC_EST_COEFFICIENTS_0.V;
        auto v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_t0 = _mm_mul_ps(v_constants, v_x);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(2, 2, 2, 2));
        v_t0 = _mm_add_ps(v_t0, v_constants);
        v_t0 = _mm_mul_ps(v_t0, v_x);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(1, 1, 1, 1));
        v_t0 = _mm_add_ps(v_t0, v_constants);
        v_t0 = _mm_mul_ps(v_t0, v_x);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(0, 0, 0, 0));
        v_t0 = _mm_add_ps(v_t0, v_constants);
        v_t0 = _mm_mul_ps(v_t0, v_root);

        auto v_t1 = _mm_sub_ps(Detail::VEC4_PI.V, v_t0);
        v_t0 = _mm_and_ps(v_nonnegative, v_t0);
        v_t1 = _mm_andnot_ps(v_nonnegative, v_t1);
        v_t0 = _mm_or_ps(v_t0, v_t1);
        return { v_t0 };
#endif
    }

    mathinline Vector4 mathcall Vector4::ATanEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                atanf(v.V.F[0]),
                atanf(v.V.F[1]),
                atanf(v.V.F[2]),
                atanf(v.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_absv = Vector4::Abs(v).V;
        auto v_invv = _mm_div_ps(Detail::VEC4_ONE_4.V, v.V);
        auto v_comp = _mm_cmpgt_ps(v.V, Detail::VEC4_ONE_4.V);
        auto v_select0 = _mm_and_ps(v_comp, Detail::VEC4_ONE_4.V);
        auto v_select1 = _mm_andnot_ps(v_comp, Detail::VEC4_NEGATIVE_ONE_4.V);
        auto v_sign = _mm_or_ps(v_select0, v_select1);
        v_comp = _mm_cmple_ps(v_absv, Detail::VEC4_ONE_4.V);
        v_select0 = _mm_and_ps(v_comp, Detail::VEC4_ZERO_4.V);
        v_select1 = _mm_andnot_ps(v_comp, v_sign);
        v_sign = _mm_or_ps(v_select0, v_select1);
        v_select0 = _mm_and_ps(v_comp, v.V);
        v_select1 = _mm_andnot_ps(v_comp, v_invv);
        auto v_x = _mm_or_ps(v_select0, v_select1);

        auto v_x2 = _mm_mul_ps(v_x, v_x);

        auto v_aec = Detail::VEC4_ATAN_EST_COEFFICIENTS_1.V;
        auto v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(3, 3, 3, 3));
        auto v_result = _mm_mul_ps(v_constants, v_x2);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(2, 2, 2, 2));
        v_result = _mm_add_ps(v_result, v_constants);
        v_result = _mm_mul_ps(v_result, v_x2);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(1, 1, 1, 1));
        v_result = _mm_add_ps(v_result, v_constants);
        v_result = _mm_mul_ps(v_result, v_x2);

        v_constants = _mm_permute_ps(v_aec, _MM_SHUFFLE(0, 0, 0, 0));
        v_result = _mm_add_ps(v_result, v_constants);
        v_result = _mm_mul_ps(v_result, v_x2);

        v_result = _mm_add_ps(v_result, Detail::VEC4_ATAN_EST_COEFFICIENTS_0.V);
        v_result = _mm_mul_ps(v_result, v_x);
        auto v_result1 = _mm_mul_ps(v_sign, Detail::VEC4_HALF_PI.V);
        v_result1 = _mm_sub_ps(v_result1, v_result);

        v_comp = _mm_cmpeq_ps(v_sign, Detail::VEC4_ZERO_4.V);
        v_select0 = _mm_and_ps(v_comp, v_result);
        v_select1 = _mm_andnot_ps(v_comp, v_result1);
        v_result = _mm_or_ps(v_select0, v_select1);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ATan2Est(Vector4 y, Vector4 x) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                atan2f(y.V.F[0], x.V.F[0]),
                atan2f(y.V.F[1], x.V.F[1]),
                atan2f(y.V.F[2], x.V.F[2]),
                atan2f(y.V.F[3], x.V.F[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX

        static const Detail::Vector4F32 v_atan2_constants = { { {
                Maths::PI<float>,
                Maths::PI_OVER_2<float>,
                Maths::PI_OVER_4<float>,
                Maths::PI<float> * 3.0F / 4.0F
            } } };

        auto v_zero = Vector4::Zero();
        auto v_atan_result_valid = Vector4::MaskTrue();

        auto v_pi                 = Vector4::SplatX({ v_atan2_constants.V });
        auto v_pi_over_two        = Vector4::SplatY({ v_atan2_constants.V });
        auto v_pi_over_four       = Vector4::SplatZ({ v_atan2_constants.V });
        auto v_three_pi_over_four = Vector4::SplatW({ v_atan2_constants.V });

        auto v_y_equals_zero = Vector4::CompareEqual(y, v_zero);
        auto v_x_equals_zero = Vector4::CompareEqual(x, v_zero);
        auto v_x_is_positive = Vector4::MaskAndUInt(x, { Detail::VEC4_NEGATIVE_ZERO.V });
        v_x_is_positive = Vector4::MaskCompareEqual(v_x_is_positive, v_zero);
        auto v_y_equals_infinity = Vector4::CompareIsInfinite(y);
        auto v_x_equals_infinity = Vector4::CompareIsInfinite(x);

        auto v_y_sign = Vector4::MaskAndUInt(y, { Detail::VEC4_NEGATIVE_ZERO.V });
        v_pi = Vector4::MaskOrUInt(v_pi, v_y_sign);
        v_pi_over_two = Vector4::MaskOrUInt(v_pi_over_two, v_y_sign);
        v_pi_over_four = Vector4::MaskOrUInt(v_pi_over_four, v_y_sign);
        v_three_pi_over_four = Vector4::MaskOrUInt(v_three_pi_over_four, v_y_sign);

        auto v_r1 = Vector4::Select(v_pi, v_y_sign, v_x_is_positive);
        auto v_r2 = Vector4::Select(v_atan_result_valid, v_pi_over_two, v_x_equals_zero);
        auto v_r3 = Vector4::Select(v_r2, v_r1, v_y_equals_zero);
        auto v_r4 = Vector4::Select(v_three_pi_over_four, v_pi_over_four, v_x_is_positive);
        auto v_r5 = Vector4::Select(v_pi_over_two, v_r4, v_x_equals_infinity);
        auto v_result = Vector4::Select(v_r3, v_r5, v_y_equals_infinity);
        v_atan_result_valid = Vector4::MaskCompareEqual(v_result, v_atan_result_valid);

        auto v_reciprocal = Vector4::ReciprocalEst(x);
        auto v_v = Vector4::Multiply(y, v_reciprocal);
        auto v_r0 = Vector4::ATanEst(v_v);

        v_r1 = Vector4::Select(v_pi, { Detail::VEC4_NEGATIVE_ZERO.V }, v_x_is_positive);
        v_r2 = Vector4::Add(v_r0, v_r1);

        v_result = Vector4::Select(v_result, v_r2, v_atan_result_valid);

        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Lerp(Vector4 v0, Vector4 v1, float t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_scale = Vector4::Make(t);
        auto v_length = Vector4::Subtract(v1, v0);
        auto v_result = Vector4::MultiplyAdd(v_length, v_scale, v0);
        return { v_result };
#elif GRAPHYTE_HW_AVX
        auto v_length = _mm_sub_ps(v1.V, v0.V);
        auto v_scale = _mm_set_ps1(t);
        auto v_result = _mm_mul_ps(v_length, v_scale);
        v_result = _mm_add_ps(v_result, v0.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Lerp(Vector4 v0, Vector4 v1, Vector4 t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_length = Vector4::Subtract(v1, v0);
        return Vector4::MultiplyAdd(v_length, t, v0);
#elif GRAPHYTE_HW_AVX
        auto v_length = _mm_sub_ps(v1.V, v0.V);
        auto v_result = _mm_mul_ps(v_length, t.V);
        v_result = _mm_add_ps(v_result, v0.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, float t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto t2 = t * t;
        auto t3 = t * t2;

        auto v_p0 = Vector4::Make(2.0F * t3 - 3.0F * t2 + 1.0F);
        auto v_t0 = Vector4::Make(t3 - 2.0F * t2 + t);
        auto v_p1 = Vector4::Make(-2.0F * t3 + 3.0F * t2);
        auto v_t1 = Vector4::Make(t3 - t2);
        auto v_result = Vector4::Multiply(v_p0, position0);
        v_result = Vector4::MultiplyAdd(v_t0, tangent0, v_result);
        v_result = Vector4::MultiplyAdd(v_p1, position1, v_result);
        v_result = Vector4::MultiplyAdd(v_t1, tangent1, v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto t2 = t * t;
        auto t3 = t * t2;

        auto v_p0 = _mm_set_ps1(2.0F * t3 - 3.0F * t2 + 1.0F);
        auto v_t0 = _mm_set_ps1(t3 - 2.0F * t2 + t);
        auto v_p1 = _mm_set_ps1(-2.0F * t3 + 3.0F * t2);
        auto v_t1 = _mm_set_ps1(t3 - t2);

        auto v_result = _mm_mul_ps(v_p0, position0.V);
        auto v_temp = _mm_mul_ps(v_t0, tangent0.V);
        v_result = _mm_add_ps(v_result, v_temp);
        v_temp = _mm_mul_ps(v_p1, position1.V);
        v_result = _mm_add_ps(v_result, v_temp);
        v_temp = _mm_mul_ps(v_t1, tangent1.V);
        v_result = _mm_add_ps(v_result, v_temp);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Hermite(Vector4 position0, Vector4 tangent0, Vector4 position1, Vector4 tangent1, Vector4 t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_t2 = Vector4::Multiply(t, t);
        auto v_t3 = Vector4::Multiply(v_t2, t);

        auto v_p0 = Vector4::Make(2.0F * v_t3.V.F[0] - 3.0F * v_t2.V.F[0] + 1.0F);
        auto v_t0 = Vector4::Make(v_t3.V.F[1] - 2.0F * v_t2.V.F[1] + t.V.F[1]);
        auto v_p1 = Vector4::Make(-2.0F * v_t3.V.F[2] + 3.0F * v_t2.V.F[2]);
        auto v_t1 = Vector4::Make(v_t3.V.F[3] - v_t2.V.F[3]);

        auto v_result = Vector4::Multiply(v_p0, position0);
        v_result = Vector4::MultiplyAdd(v_t0, tangent0, v_result);
        v_result = Vector4::MultiplyAdd(v_p1, position1, v_result);
        v_result = Vector4::MultiplyAdd(v_t1, tangent1, v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 CatMulT2 = { { { -3.0F, -2.0F, 3.0F, -1.0F } } };
        static const Detail::Vector4F32 CatMulT3 = { { { 2.0F, 1.0F, -2.0F, 1.0F } } };

        auto v_t2 = _mm_mul_ps(t.V, t.V);
        auto v_t3 = _mm_mul_ps(t.V, v_t2);

        v_t2 = _mm_mul_ps(v_t2, CatMulT2.V);
        v_t3 = _mm_mul_ps(v_t3, CatMulT3.V);
        v_t3 = _mm_add_ps(v_t3, v_t2);
        v_t2 = _mm_and_ps(t.V, Detail::VEC4_MASK_COMPONENT_Y.V);
        v_t3 = _mm_add_ps(v_t3, v_t2);
        v_t3 = _mm_add_ps(v_t3, Detail::VEC4_POSITIVE_UNIT_X.V);
        auto v_result = _mm_permute_ps(v_t3, _MM_SHUFFLE(0, 0, 0, 0));
        v_result = _mm_mul_ps(v_result, position0.V);
        v_t2 = _mm_permute_ps(v_t3, _MM_SHUFFLE(1, 1, 1, 1));
        v_t2 = _mm_mul_ps(v_t2, tangent0.V);
        v_result = _mm_add_ps(v_result, v_t2);
        v_t2 = _mm_permute_ps(v_t3, _MM_SHUFFLE(2, 2, 2, 2));
        v_t2 = _mm_mul_ps(v_t2, position1.V);
        v_result = _mm_add_ps(v_result, v_t2);
        v_t3 = _mm_permute_ps(v_t3, _MM_SHUFFLE(3, 3, 3, 3));
        v_t3 = _mm_mul_ps(v_t3, tangent1.V);
        v_result = _mm_add_ps(v_result, v_t3);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::CatmullRom(Vector4 position0, Vector4 position1, Vector4 position2, Vector4 position3, float t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto t2 = t * t;
        auto t3 = t * t2;

        auto v_p0 = Vector4::Make((-t3 + 2.0F * t2 - t) * 0.5F);
        auto v_p1 = Vector4::Make((3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F);
        auto v_p2 = Vector4::Make((-3.0F * t3 + 4.0F * t2 + t) * 0.5F);
        auto v_p3 = Vector4::Make((t3 - t2) * 0.5F);

        auto v_result = Vector4::Multiply(v_p0, position0);
        v_result = Vector4::MultiplyAdd(v_p1, position1, v_result);
        v_result = Vector4::MultiplyAdd(v_p2, position2, v_result);
        v_result = Vector4::MultiplyAdd(v_p3, position3, v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto t2 = t * t;
        auto t3 = t * t2;

        auto v_p0 = _mm_set_ps1((-t3 + 2.0F * t2 - t) * 0.5F);
        auto v_p1 = _mm_set_ps1((3.0F * t3 - 5.0F * t2 + 2.0F) * 0.5F);
        auto v_p2 = _mm_set_ps1((-3.0F * t3 + 4.0F * t2 + t) * 0.5F);
        auto v_p3 = _mm_set_ps1((t3 - t2) * 0.5F);

        v_p0 = _mm_mul_ps(v_p0, position0.V);
        v_p1 = _mm_mul_ps(v_p1, position1.V);
        v_p2 = _mm_mul_ps(v_p2, position2.V);
        v_p3 = _mm_mul_ps(v_p3, position3.V);
        v_p0 = _mm_add_ps(v_p0, v_p1);
        v_p2 = _mm_add_ps(v_p2, v_p3);
        v_p0 = _mm_add_ps(v_p0, v_p2);
        return { v_p0 };
#endif
    }

    mathinline Vector4 mathcall Vector4::CatmullRom(Vector4 position0, Vector4 position1, Vector4 position2, Vector4 position3, Vector4 t) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto fx = t.V.F[0];
        auto fy = t.V.F[1];
        auto fz = t.V.F[2];
        auto fw = t.V.F[3];

        Detail::Vector4F32 v_result = { { {
                0.5F * ((-fx * fx * fx + 2.0F * fx * fx - fx) * position0.V.F[0]
                    + (3.0F * fx * fx * fx - 5.0F * fx * fx + 2.0F) * position1.V.F[0]
                    + (-3.0F * fx * fx * fx + 4.0F * fx * fx + fx) * position2.V.F[0]
                    + (fx * fx * fx - fx * fx) * position3.V.F[0]),

                0.5F * ((-fy * fy * fy + 2.0F * fy * fy - fy) * position0.V.F[1]
                    + (3.0F * fy * fy * fy - 5.0F * fy * fy + 2.0F) * position1.V.F[1]
                    + (-3.0F * fy * fy * fy + 4.0F * fy * fy + fy) * position2.V.F[1]
                    + (fy * fy * fy - fy * fy) * position3.V.F[1]),

                0.5F * ((-fz * fz * fz + 2.0F * fz * fz - fz) * position0.V.F[2]
                    + (3.0F * fz * fz * fz - 5.0F * fz * fz + 2.0F) * position1.V.F[2]
                    + (-3.0F * fz * fz * fz + 4.0F * fz * fz + fz) * position2.V.F[2]
                    + (fz * fz * fz - fz * fz) * position3.V.F[2]),

                0.5F * ((-fw * fw * fw + 2.0F * fw * fw - fw) * position0.V.F[3]
                    + (3.0F * fw * fw * fw - 5.0F * fw * fw + 2.0F) * position1.V.F[3]
                    + (-3.0F * fw * fw * fw + 4.0F * fw * fw + fw) * position2.V.F[3]
                    + (fw * fw * fw - fw * fw) * position3.V.F[3])
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 Catmul2 = { { { 2.0F, 2.0F, 2.0F, 2.0F } } };
        static const Detail::Vector4F32 Catmul3 = { { { 3.0F, 3.0F, 3.0F, 3.0F } } };
        static const Detail::Vector4F32 Catmul4 = { { { 4.0F, 4.0F, 4.0F, 4.0F } } };
        static const Detail::Vector4F32 Catmul5 = { { { 5.0F, 5.0F, 5.0F, 5.0F } } };

        auto v_t2 = _mm_mul_ps(t.V, t.V);
        auto v_t3 = _mm_mul_ps(t.V, v_t2);
        auto v_result = _mm_add_ps(v_t2, v_t2);
        v_result = _mm_sub_ps(v_result, t.V);
        v_result = _mm_sub_ps(v_result, v_t3);
        v_result = _mm_mul_ps(v_result, position0.V);
        auto v_temp = _mm_mul_ps(v_t3, Catmul3.V);
        auto v_temp2 = _mm_mul_ps(v_t2, Catmul5.V);
        v_temp = _mm_sub_ps(v_temp, v_temp2);
        v_temp = _mm_add_ps(v_temp, Catmul2);
        v_temp = _mm_mul_ps(v_temp, position1.V);
        v_result = _mm_add_ps(v_result, v_temp);
        v_temp = _mm_mul_ps(v_t2, Catmul4.V);
        v_temp2 = _mm_mul_ps(v_t3, Catmul3.V);
        v_temp = _mm_sub_ps(v_temp, v_temp2);
        v_temp = _mm_add_ps(v_temp, t.V);
        v_temp = _mm_mul_ps(v_temp, position2.V);
        v_result = _mm_add_ps(v_result, v_temp);
        v_t3 = _mm_sub_ps(v_t3, v_t2);
        v_t3 = _mm_mul_ps(v_t3, position3.V);
        v_result = _mm_add_ps(v_result, v_t3);
        v_result = _mm_mul_ps(v_result, Detail::VEC4_ONE_HALF_4.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Barycentric(Vector4 position0, Vector4 position1, Vector4 position2, float f, float g) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_p10 = Vector4::Subtract(position1, position0);
        auto v_scale_f = Vector4::Make(f);

        auto v_p20 = Vector4::Subtract(position2, position0);
        auto v_scale_g = Vector4::Make(g);

        auto v_result = Vector4::MultiplyAdd(v_p10, v_scale_f, position0);
        v_result = Vector4::MultiplyAdd(v_p20, v_scale_g, v_result);

        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_r1 = _mm_sub_ps(position1.V, position0.V);
        auto v_sf = _mm_set_ps1(f);
        auto v_r2 = _mm_sub_ps(position2.V, position0.V);
        auto v_sg = _mm_set_ps1(g);
        v_r1 = _mm_mul_ps(v_r1, v_sf);
        v_r2 = _mm_mul_ps(v_r2, v_sg);
        v_r1 = _mm_add_ps(v_r1, position0.V);
        v_r1 = _mm_add_ps(v_r1, v_r2);
        return { v_r1 };
#endif
    }

    mathinline Vector4 mathcall Vector4::Barycentric(Vector4 position0, Vector4 position1, Vector4 position2, Vector4 f, Vector4 g) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_p10 = Vector4::Subtract(position1, position0);
        auto v_p20 = Vector4::Subtract(position2, position0);
        auto v_result = Vector4::MultiplyAdd(v_p10, f, position0);
        v_result = Vector4::MultiplyAdd(v_p20, g, v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_r1 = _mm_sub_ps(position1.V, position0.V);
        auto v_r2 = _mm_sub_ps(position2.V, position0.V);
        v_r1 = _mm_mul_ps(v_r1, f.V);
        v_r2 = _mm_mul_ps(v_r2, g.V);
        v_r1 = _mm_add_ps(v_r1, position0.V);
        v_r1 = _mm_add_ps(v_r1, v_r2);
        return { v_r1 };
#endif
    }

    mathinline Vector4 mathcall Vector4::Dot(Vector4 v1, Vector4 v2) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto dot =
            v1.V.F[0] * v2.V.F[0] +
            v1.V.F[1] * v2.V.F[1] +
            v1.V.F[2] * v2.V.F[2] +
            v1.V.F[3] * v2.V.F[3];
        Detail::Vector4F32 v_result = { { { dot, dot, dot, dot } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        return { _mm_dp_ps(v1.V, v2.V, 0xFF) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Cross(Vector4 v1, Vector4 v2, Vector4 v3) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                (((v2.V.F[2] * v3.V.F[3]) - (v2.V.F[3] * v3.V.F[2])) * v1.V.F[1]) - (((v2.V.F[1] * v3.V.F[3]) - (v2.V.F[3] * v3.V.F[1])) * v1.V.F[2]) + (((v2.V.F[1] * v3.V.F[2]) - (v2.V.F[2] * v3.V.F[1])) * v1.V.F[3]),
                (((v2.V.F[3] * v3.V.F[2]) - (v2.V.F[2] * v3.V.F[3])) * v1.V.F[0]) - (((v2.V.F[3] * v3.V.F[0]) - (v2.V.F[0] * v3.V.F[3])) * v1.V.F[2]) + (((v2.V.F[2] * v3.V.F[0]) - (v2.V.F[0] * v3.V.F[2])) * v1.V.F[3]),
                (((v2.V.F[1] * v3.V.F[3]) - (v2.V.F[3] * v3.V.F[1])) * v1.V.F[0]) - (((v2.V.F[0] * v3.V.F[3]) - (v2.V.F[3] * v3.V.F[0])) * v1.V.F[1]) + (((v2.V.F[0] * v3.V.F[1]) - (v2.V.F[1] * v3.V.F[0])) * v1.V.F[3]),
                (((v2.V.F[2] * v3.V.F[1]) - (v2.V.F[1] * v3.V.F[2])) * v1.V.F[0]) - (((v2.V.F[2] * v3.V.F[0]) - (v2.V.F[0] * v3.V.F[2])) * v1.V.F[1]) + (((v2.V.F[1] * v3.V.F[0]) - (v2.V.F[0] * v3.V.F[1])) * v1.V.F[2]),
            }}};
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_permute_ps(v2.V, _MM_SHUFFLE(2, 1, 3, 2));
        auto v_temp3  = _mm_permute_ps(v3.V, _MM_SHUFFLE(1, 3, 2, 3));
        v_result      = _mm_mul_ps(v_result, v_temp3);
        auto v_temp2  = _mm_permute_ps(v2.V, _MM_SHUFFLE(1, 3, 2, 3));
        v_temp3       = _mm_permute_ps(v_temp3, _MM_SHUFFLE(1, 3, 0, 1));
        v_temp2       = _mm_mul_ps(v_temp2, v_temp3);
        v_result      = _mm_sub_ps(v_result, v_temp2);
        auto v_temp1  = _mm_permute_ps(v1.V, _MM_SHUFFLE(0, 0, 0, 1));
        v_result      = _mm_mul_ps(v_result, v_temp1);
        v_temp2       = _mm_permute_ps(v2.V, _MM_SHUFFLE(2, 0, 3, 1));
        v_temp3       = _mm_permute_ps(v3.V, _MM_SHUFFLE(0, 3, 0, 3));
        v_temp3       = _mm_mul_ps(v_temp3, v_temp2);
        v_temp2       = _mm_permute_ps(v_temp2, _MM_SHUFFLE(2, 1, 2, 1));
        v_temp1       = _mm_permute_ps(v3.V, _MM_SHUFFLE(2, 0, 3, 1));
        v_temp2       = _mm_mul_ps(v_temp2, v_temp1);
        v_temp3       = _mm_sub_ps(v_temp3, v_temp2);
        v_temp1       = _mm_permute_ps(v1.V, _MM_SHUFFLE(1, 1, 2, 2));
        v_temp1       = _mm_mul_ps(v_temp1, v_temp3);
        v_result      = _mm_sub_ps(v_result, v_temp1);
        v_temp2       = _mm_permute_ps(v2.V, _MM_SHUFFLE(1, 0, 2, 1));
        v_temp3       = _mm_permute_ps(v3.V, _MM_SHUFFLE(0, 1, 0, 2));
        v_temp3       = _mm_mul_ps(v_temp3, v_temp2);
        v_temp2       = _mm_permute_ps(v_temp2, _MM_SHUFFLE(2, 0, 2, 1));
        v_temp1       = _mm_permute_ps(v3.V, _MM_SHUFFLE(1, 0, 2, 1));
        v_temp1       = _mm_mul_ps(v_temp1, v_temp2);
        v_temp3       = _mm_sub_ps(v_temp3, v_temp1);
        v_temp1       = _mm_permute_ps(v1.V, _MM_SHUFFLE(2, 3, 3, 3));
        v_temp3       = _mm_mul_ps(v_temp3, v_temp1);
        v_result      = _mm_add_ps(v_result, v_temp3);
        return { v_result };
#endif

    }

    mathinline Vector4 mathcall Vector4::LengthSquared(Vector4 v) noexcept
    {
        return Vector4::Dot(v, v);
    }

    mathinline Vector4 mathcall Vector4::ReciprocalLengthEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector4::LengthSquared(v);
        v_result = Vector4::ReciprocalSqrtEst(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
        return { _mm_rsqrt_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::ReciprocalLength(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector4::LengthSquared(v);
        v_result = Vector4::ReciprocalSqrt(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
        auto v_length_sq = _mm_sqrt_ps(v_temp);
        return { _mm_div_ps(Detail::VEC4_ONE_4.V, v_length_sq) };
#endif
    }

    mathinline Vector4 mathcall Vector4::LengthEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector4::LengthSquared(v);
        v_result = Vector4::SqrtEst(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Length(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector4::LengthSquared(v);
        v_result = Vector4::Sqrt(v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
        return { _mm_sqrt_ps(v_temp) };
#endif
    }

    mathinline Vector4 mathcall Vector4::NormalizeEst(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_result = Vector4::ReciprocalLength(v);
        v_result = Vector4::Multiply(v, v_result);
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_temp = _mm_dp_ps(v.V, v.V, 0xFF);
        auto v_result = _mm_rsqrt_ps(v_temp);
        return { _mm_mul_ps(v_result, v.V) };
#endif
    }

    mathinline Vector4 mathcall Vector4::Normalize(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto length = Vector4::Length(v).V.F[0];
        if (length > 0.0F)
        {
            length = 1.0F / length;
        }

        Detail::Vector4F32 v_result = { { {
                v.V.F[0] * length,
                v.V.F[1] * length,
                v.V.F[2] * length,
                v.V.F[3] * length,
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_length_sq = _mm_dp_ps(v.V, v.V, 0xff);
        auto v_result    = _mm_sqrt_ps(v_length_sq);
        auto v_zero_mask = _mm_setzero_ps();
        v_zero_mask      = _mm_cmpneq_ps(v_zero_mask, v_result);
        v_length_sq      = _mm_cmpneq_ps(v_length_sq, Detail::VEC4_INFINITY.V);
        v_result         = _mm_div_ps(v.V, v_result);
        v_result         = _mm_and_ps(v_result, v_zero_mask);
        auto v_temp1     = _mm_andnot_ps(v_length_sq, Detail::VEC4_QNAN.V);
        auto v_temp2     = _mm_and_ps(v_result, v_length_sq);
        v_result         = _mm_or_ps(v_temp1, v_temp2);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ClampLength(Vector4 v, float min, float max) noexcept
    {
        auto v_min = Vector4::Make(min);
        auto v_max = Vector4::Make(max);
        return Vector4::ClampLength(v, v_min, v_max);
    }

    mathinline Vector4 mathcall Vector4::ClampLength(Vector4 v, Vector4 min, Vector4 max) noexcept
    {
        GX_ASSERT(
            (Vector4::GetY(min) == Vector4::GetX(min)) &&
            (Vector4::GetZ(min) == Vector4::GetX(min)) &&
            (Vector4::GetW(min) == Vector4::GetX(min))
        );

        GX_ASSERT(
            (Vector4::GetY(max) == Vector4::GetX(max)) &&
            (Vector4::GetZ(max) == Vector4::GetX(max)) &&
            (Vector4::GetW(max) == Vector4::GetX(max))
        );

        GX_ASSERT(Vector4::IsGreaterEqual(min, Vector4::Zero()));
        GX_ASSERT(Vector4::IsGreaterEqual(max, Vector4::Zero()));
        GX_ASSERT(Vector4::IsGreaterEqual(max, min));

        auto v_length_sq       = Vector4::LengthSquared(v);
        auto v_zero            = Vector4::Zero();
        auto v_rcp_length      = Vector4::ReciprocalSqrt(v_length_sq);
        auto v_infinite_length = Vector4::MaskCompareEqual(v_length_sq, { Detail::VEC4_INFINITY.V });
        auto v_zero_length     = Vector4::CompareEqual(v_length_sq, v_zero);
        auto v_normal          = Vector4::Multiply(v, v_rcp_length);
        auto v_length          = Vector4::Multiply(v_length_sq, v_rcp_length);

        auto v_select = Vector4::MaskCompareEqual(v_infinite_length, v_zero_length);
        v_length      = Vector4::Select(v_length_sq, v_length, v_select);
        v_normal      = Vector4::Select(v_length_sq, v_normal, v_select);

        auto v_control_max = Vector4::CompareGreater(v_length, max);
        auto v_control_min = Vector4::CompareLess(v_length, min);

        auto v_clamp_length = Vector4::Select(v_length, max, v_control_max);
        v_clamp_length      = Vector4::Select(v_clamp_length, min, v_control_min);

        auto v_result = Vector4::Multiply(v_normal, v_clamp_length);

        auto v_control = Vector4::MaskCompareEqual(v_control_max, v_control_min);
        v_result       = Vector4::Select(v_result, v, v_control);
        return v_result;
    }

    mathinline Vector4 mathcall Vector4::Reflect(Vector4 incident, Vector4 normal) noexcept
    {
        auto v_result = Vector4::Dot(incident, normal);
        v_result = Vector4::Add(v_result, v_result);
        v_result = Vector4::NegativeMultiplySubtract(v_result, normal, incident);
        return v_result;
    }

    mathinline Vector4 mathcall Vector4::Refract(Vector4 incident, Vector4 normal, float refraction_index) noexcept
    {
        auto v_index = Vector4::Make(refraction_index);
        return Vector4::Refract(incident, normal, v_index);
    }

    mathinline Vector4 mathcall Vector4::Refract(Vector4 incident, Vector4 normal, Vector4 refraction_index) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_zero = Vector4::Zero();
        auto v_i_dot_n = Vector4::Dot(incident, normal);

        auto v_r = Vector4::NegativeMultiplySubtract(v_i_dot_n, v_i_dot_n, { Detail::VEC4_ONE_4.V });
        v_r = Vector4::Multiply(v_r, refraction_index);
        v_r = Vector4::NegativeMultiplySubtract(v_r, refraction_index, { Detail::VEC4_ONE_4.V });

        if (Vector4::IsLessEqual(v_r, v_zero))
        {
            return v_zero;
        }
        else
        {
            v_r = Vector4::Sqrt(v_r);
            v_r = Vector4::MultiplyAdd(refraction_index, v_i_dot_n, v_r);

            auto v_result = Vector4::Multiply(refraction_index, incident);
            v_result = Vector4::NegativeMultiplySubtract(normal, v_r, v_result);
            return v_result;
        }
#elif GRAPHYTE_HW_AVX
        auto v_i_dot_n = Vector4::Dot(incident, normal).V;
        auto v_r       = _mm_mul_ps(v_i_dot_n, v_i_dot_n);
        v_r            = _mm_sub_ps(Detail::VEC4_ONE_4.V, v_r);
        v_r            = _mm_mul_ps(v_r, refraction_index.V);
        v_r            = _mm_mul_ps(v_r, refraction_index.V);
        v_r            = _mm_sub_ps(v_r, Detail::VEC4_ONE_4.V);

        auto v_result = _mm_cmple_ps(v_r, Detail::VEC4_ZERO_4.V);
        if (_mm_movemask_ps(v_result) == 0b1111)
        {
            v_result = Detail::VEC4_ZERO_4.V;
        }
        else
        {
            v_r      = _mm_sqrt_ps(v_r);
            v_result = _mm_mul_ps(refraction_index.V, v_i_dot_n);
            v_r      = _mm_add_ps(v_r, v_result);
            v_result = _mm_mul_ps(refraction_index.V, incident.V);
            v_r      = _mm_mul_ps(v_r, normal.V);
            v_result = _mm_sub_ps(v_result, v_r);
        }

        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::Orthogonal(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        Detail::Vector4F32 v_result = { { {
                v.V.F[2],
                v.V.F[3],
                -v.V.F[0],
                -v.V.F[1],
            }}};
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        static const Detail::Vector4F32 flipzw = { { { 1.0F, 1.0F, -1.0F, -1.0F } } };
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 0, 3, 2));
        v_result = _mm_mul_ps(v_result, flipzw.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::AngleBetweenNormalsEst(Vector4 n1, Vector4 n2) noexcept
    {
        auto v_result = Vector4::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACosEst(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector4::AngleBetweenNormals(Vector4 n1, Vector4 n2) noexcept
    {
        auto v_result = Vector4::Dot(n1, n2);
        v_result = Vector4::Clamp(v_result, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        v_result = Vector4::ACos(v_result);
        return v_result;
    }

    mathinline Vector4 mathcall Vector4::AngleBetweenVectors(Vector4 v1, Vector4 v2) noexcept
    {
        auto v_l1 = Vector4::ReciprocalLength(v1);
        auto v_l2 = Vector4::ReciprocalLength(v2);
        auto v_dot = Vector4::Dot(v1, v2);

        v_l1 = Vector4::Multiply(v_l1, v_l2);
        
        auto v_cos_angle = Vector4::Multiply(v_dot, v_l1);
        v_cos_angle = Vector4::Clamp(v_cos_angle, { Detail::VEC4_NEGATIVE_ONE_4.V }, { Detail::VEC4_ONE_4.V });
        return Vector4::ACos(v_cos_angle);
    }

    mathinline Vector4 mathcall Vector4::Transform(Vector4 v, Matrix m) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto fx = (m.M.M[0][0] * v.V.F[0]) + (m.M.M[1][0] * v.V.F[1]) + (m.M.M[2][0] * v.V.F[2]) + (m.M.M[3][0] * v.V.F[3]);
        auto fy = (m.M.M[0][1] * v.V.F[0]) + (m.M.M[1][1] * v.V.F[1]) + (m.M.M[2][1] * v.V.F[2]) + (m.M.M[3][1] * v.V.F[3]);
        auto fz = (m.M.M[0][2] * v.V.F[0]) + (m.M.M[1][2] * v.V.F[1]) + (m.M.M[2][2] * v.V.F[2]) + (m.M.M[3][2] * v.V.F[3]);
        auto fw = (m.M.M[0][3] * v.V.F[0]) + (m.M.M[1][3] * v.V.F[1]) + (m.M.M[2][3] * v.V.F[2]) + (m.M.M[3][3] * v.V.F[3]);
        Detail::Vector4F32 v_result = { { { fx, fy, fz, fw } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX2
        auto v_result = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));
        v_result      = _mm_mul_ps(v_result, m.M.R[3]);
        auto v_temp   = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        v_result      = _mm_fmadd_ps(v_temp, m.M.R[2], v_result);
        v_temp        = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        v_result      = _mm_fmadd_ps(v_temp, m.M.R[1], v_result);
        v_temp        = _mm_boardcastss_ps(v.V);
        v_result      = _mm_fmadd_ps(v_temp, m.M.R[0], v_result);
        return { v_result };
#elif GRAPHYTE_HW_AVX
        auto v_x = _mm_permute_ps(v.V, _MM_SHUFFLE(0, 0, 0, 0));
        auto v_y = _mm_permute_ps(v.V, _MM_SHUFFLE(1, 1, 1, 1));
        auto v_z = _mm_permute_ps(v.V, _MM_SHUFFLE(2, 2, 2, 2));
        auto v_w = _mm_permute_ps(v.V, _MM_SHUFFLE(3, 3, 3, 3));

        v_x = _mm_mul_ps(v_x, m.M.R[0]);
        v_y = _mm_mul_ps(v_y, m.M.R[1]);
        v_z = _mm_mul_ps(v_z, m.M.R[2]);
        v_w = _mm_mul_ps(v_w, m.M.R[3]);

        v_x = _mm_add_ps(v_x, v_y);
        v_z = _mm_add_ps(v_z, v_w);
        v_x = _mm_add_ps(v_x, v_z);
        return { v_x };
#endif
    }

    mathinline Vector4 mathcall Vector4::FresnelTerm(Vector4 cos_incident_angle, Vector4 refraction_index) noexcept
    {
        GX_ASSERT(!Vector4::IsInfinite(cos_incident_angle));

#if GRAPHYTE_MATH_NO_INTRINSICS
        auto v_g = Vector4::MultiplyAdd(refraction_index, refraction_index, { Detail::VEC4_NEGATIVE_ONE_4.V });
        v_g = Vector4::MultiplyAdd(cos_incident_angle, cos_incident_angle, v_g);
        v_g = Vector4::Abs(v_g);
        v_g = Vector4::Sqrt(v_g);

        auto v_s = Vector4::Add(v_g, cos_incident_angle);
        auto v_d = Vector4::Subtract(v_g, cos_incident_angle);

        auto v_v0 = Vector4::Multiply(v_d, v_d);
        auto v_v1 = Vector4::Multiply(v_s, v_s);

        v_v1 = Vector4::Reciprocal(v_v1);
        v_v0 = Vector4::Multiply({ Detail::VEC4_ONE_HALF_4.V }, v_v0);
        v_v0 = Vector4::Multiply(v_v0, v_v1);

        auto v_v2 = Vector4::MultiplyAdd(cos_incident_angle, v_s, { Detail::VEC4_NEGATIVE_ONE_4.V });
        auto v_v3 = Vector4::MultiplyAdd(cos_incident_angle, v_d, { Detail::VEC4_ONE_4.V });

        v_v2 = Vector4::Multiply(v_v2, v_v2);
        v_v3 = Vector4::Multiply(v_v3, v_v3);

        v_v3 = Vector4::Reciprocal(v_v3);
        v_v2 = Vector4::MultiplyAdd(v_v2, v_v3, { Detail::VEC4_ONE_4.V });

        auto v_result = Vector4::Multiply(v_v0, v_v2);
        v_result = Vector4::Saturate(v_result);

        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_g = _mm_mul_ps(refraction_index.V, refraction_index.V);
        auto v_temp = _mm_mul_ps(cos_incident_angle.V, cos_incident_angle.V);
        v_g = _mm_sub_ps(v_g, Detail::VEC4_ONE_4.V);
        v_temp = _mm_add_ps(v_temp, v_g);

        v_g = _mm_setzero_ps();
        v_g = _mm_sub_ps(v_g, v_temp);
        v_g = _mm_max_ps(v_g, v_temp);
        v_g = _mm_sqrt_ps(v_g);

        auto v_g_add_c = _mm_add_ps(v_g, cos_incident_angle.V);
        auto v_g_sub_c = _mm_sub_ps(v_g, cos_incident_angle.V);

        auto v_result = _mm_mul_ps(v_g_sub_c, v_g_sub_c);
        v_temp = _mm_mul_ps(v_g_add_c, v_g_add_c);
        v_result = _mm_mul_ps(v_result, Detail::VEC4_ONE_HALF_4.V);
        v_result = _mm_div_ps(v_result, v_temp);

        v_g_add_c = _mm_mul_ps(v_g_add_c, cos_incident_angle.V);
        v_g_sub_c = _mm_mul_ps(v_g_sub_c, cos_incident_angle.V);
        v_g_add_c = _mm_sub_ps(v_g_add_c, Detail::VEC4_ONE_4.V);
        v_g_sub_c = _mm_add_ps(v_g_sub_c, Detail::VEC4_ONE_4.V);
        v_g_add_c = _mm_mul_ps(v_g_add_c, v_g_add_c);
        v_g_sub_c = _mm_mul_ps(v_g_sub_c, v_g_sub_c);
        v_g_add_c = _mm_div_ps(v_g_add_c, v_g_sub_c);
        v_g_add_c = _mm_add_ps(v_g_add_c, Detail::VEC4_ONE_4.V);

        v_result = _mm_mul_ps(v_result, v_g_add_c);

        v_result = _mm_max_ps(v_result, Detail::VEC4_ZERO_4.V);
        v_result = _mm_min_ps(v_result, Detail::VEC4_ONE_4.V);
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ConvertIntToFloat(Vector4 vint, uint32_t div_exponent) noexcept
    {
        GX_ASSERT(div_exponent < 32);
#if GRAPHYTE_MATH_NO_INTRINSICS
        float scale = 1.0F / static_cast<float>(1U << div_exponent);

        Detail::Vector4F32 v_result = { { {
                static_cast<float>(scale * static_cast<int32_t>(vint.V.U[0])),
                static_cast<float>(scale * static_cast<int32_t>(vint.V.U[1])),
                static_cast<float>(scale * static_cast<int32_t>(vint.V.U[2])),
                static_cast<float>(scale * static_cast<int32_t>(vint.V.U[3])),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_result = _mm_cvtepi32_ps(_mm_castps_si128(vint.V));
        auto v_scale = _mm_set1_epi32(static_cast<int32_t>(0x3F800000U - (div_exponent << 23)));
        v_result = _mm_mul_ps(v_result, _mm_castsi128_ps(v_scale));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ConvertFloatToInt(Vector4 vfloat, uint32_t mul_exponent) noexcept
    {
        GX_ASSERT(mul_exponent < 32);
#if GRAPHYTE_MATH_NO_INTRINSICS
        float scale = static_cast<float>(1U << mul_exponent);

        Vector4 v_result;
        for (size_t i = 0; i < 4; ++i)
        {
            int32_t element;
            float temp = vfloat.V.F[i] * scale;
            if (temp <= -(65536.0F * 32768.0F))
            {
                element = (-0x7FFFFFFF) - 1;
            }
            else if (temp > (65536.0F * 32768.0F) - 128.0F)
            {
                element = 0x7FFFFFFF;
            }
            else
            {
                element = static_cast<int32_t>(temp);
            }

            v_result.V.U[i] = static_cast<uint32_t>(element);
        }
        return v_result;
#elif GRAPHYTE_HW_AVX

        auto v_result   = _mm_set_ps1(static_cast<float>(1U << mul_exponent));
        v_result        = _mm_mul_ps(v_result, vfloat.V);
        auto v_overflow = _mm_cmpgt_ps(v_result, Detail::VEC4_INTMAX.V);
        auto v_result_i = _mm_cvttps_epi32(v_result);
        v_result        = _mm_and_ps(v_overflow, Detail::VEC4_MASK_ABS.V);
        v_overflow      = _mm_andnot_ps(v_overflow, _mm_castsi128_ps(v_result_i));
        v_overflow      = _mm_or_ps(v_overflow, v_result);
        return { v_overflow };
#endif
    }

    mathinline Vector4 mathcall Vector4::ConvertUIntToFloat(Vector4 vuint, uint32_t div_exponent) noexcept
    {
        GX_ASSERT(div_exponent < 32);
#if GRAPHYTE_MATH_NO_INTRINSICS
        auto scale = 1.0F / static_cast<float>(1U << div_exponent);
        Detail::Vector4F32 v_result = { { {
                static_cast<float>(scale * vuint.V.U[0]),
                static_cast<float>(scale * vuint.V.U[1]),
                static_cast<float>(scale * vuint.V.U[2]),
                static_cast<float>(scale * vuint.V.U[3]),
            } } };
        return { v_result.V };
#elif GRAPHYTE_HW_AVX
        auto v_mask    = _mm_and_ps(vuint.V, Detail::VEC4_NEGATIVE_ZERO.V);
        auto v_result  = _mm_xor_ps(vuint.V, v_mask);
        v_result       = _mm_cvtepi32_ps(_mm_castps_si128(v_result));
        auto v_i_mask  = _mm_srai_epi32(_mm_castps_si128(v_mask), 31);
        v_mask         = _mm_and_ps(_mm_castsi128_ps(v_i_mask), Detail::VEC4_UNSIGNED_FIX.V);
        v_result       = _mm_add_ps(v_result, v_mask);
        uint32_t scale = 0x3F800000U - (div_exponent << 23);
        v_i_mask       = _mm_set1_epi32(static_cast<int>(scale));
        v_result       = _mm_mul_ps(v_result, _mm_castsi128_ps(v_i_mask));
        return { v_result };
#endif
    }

    mathinline Vector4 mathcall Vector4::ConvertFloatToUInt(Vector4 vfloat, uint32_t mul_exponent) noexcept
    {
        GX_ASSERT(mul_exponent < 32);
#if GRAPHYTE_MATH_NO_INTRINSICS

        auto scale = static_cast<float>(1U << mul_exponent);

        Vector4 v_result;
        for (size_t i = 0; i < 4; ++i)
        {
            uint32_t element;

            auto temp = vfloat.V.F[i] * scale;
            if (temp <= 0.0F)
            {
                element = 0;
            }
            else if (temp >= (65536.0F * 65536.0F))
            {
                element = 0xFFFFFFFFU;
            }
            else
            {
                element = static_cast<uint32_t>(temp);
            }
            v_result.V.U[i] = element;
        }
        return v_result;
#elif GRAPHYTE_HW_AVX
        auto v_result   = _mm_set_ps1(static_cast<float>(1U << mul_exponent));
        v_result        = _mm_mul_ps(v_result, vfloat.V);
        v_result        = _mm_max_ps(v_result, Detail::VEC4_ZERO_4.V);
        auto v_overflow = _mm_cmpgt_ps(v_result, Detail::VEC4_UINTMAX.V);
        auto v_value    = Detail::VEC4_UNSIGNED_FIX.V;
        auto v_mask     = _mm_cmpge_ps(v_result, v_value);
        v_value         = _mm_and_ps(v_value, v_mask);
        v_result        = _mm_sub_ps(v_result, v_value);
        auto v_result_i = _mm_cvttps_epi32(v_result);
        v_mask          = _mm_and_ps(v_mask, Detail::VEC4_NEGATIVE_ZERO.V);
        v_result        = _mm_xor_ps(_mm_castsi128_ps(v_result_i), v_mask);
        v_result        = _mm_or_ps(v_result, v_overflow);
        return { v_result };
#endif
    }

    mathinline bool mathcall Vector4::AnyTrue(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v.V.U[0] != 0) ||
            (v.V.U[1] != 0) ||
            (v.V.U[2] != 0) ||
            (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) != 0;
#endif
    }

    mathinline bool mathcall Vector4::AnyFalse(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v.V.U[0] == 0) ||
            (v.V.U[1] == 0) ||
            (v.V.U[2] == 0) ||
            (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) != 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::AllTrue(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v.V.U[0] != 0) &&
            (v.V.U[1] != 0) &&
            (v.V.U[2] != 0) &&
            (v.V.U[3] != 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) == 0b1111;
#endif
    }

    mathinline bool mathcall Vector4::AllFalse(Vector4 v) noexcept
    {
#if GRAPHYTE_MATH_NO_INTRINSICS
        return
            (v.V.U[0] == 0) &&
            (v.V.U[1] == 0) &&
            (v.V.U[2] == 0) &&
            (v.V.U[3] == 0);
#elif GRAPHYTE_HW_AVX
        return _mm_movemask_ps(v.V) == 0;
#endif
    }
}
