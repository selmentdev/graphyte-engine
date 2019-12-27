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

}
