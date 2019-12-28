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
