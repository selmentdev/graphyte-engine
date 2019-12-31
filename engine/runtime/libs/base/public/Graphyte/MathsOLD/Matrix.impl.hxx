    mathinline Matrix mathcall Matrix::Load(const float4x3a* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix m;
        m.M.R[0].F[0] = source->M[0][0];
        m.M.R[0].F[1] = source->M[0][1];
        m.M.R[0].F[2] = source->M[0][2];
        m.M.R[0].F[3] = 0.0F;

        m.M.R[1].F[0] = source->M[1][0];
        m.M.R[1].F[1] = source->M[1][1];
        m.M.R[1].F[2] = source->M[1][2];
        m.M.R[1].F[3] = 0.0F;

        m.M.R[2].F[0] = source->M[2][0];
        m.M.R[2].F[1] = source->M[2][1];
        m.M.R[2].F[2] = source->M[2][2];
        m.M.R[2].F[3] = 0.0F;

        m.M.R[3].F[0] = source->M[3][0];
        m.M.R[3].F[1] = source->M[3][1];
        m.M.R[3].F[2] = source->M[3][2];
        m.M.R[3].F[3] = 1.0F;
        return m;
#elif GRAPHYTE_HW_AVX
        auto v_t1 = _mm_load_ps(&source->M[0][0]);
        auto v_t2 = _mm_load_ps(&source->M[1][1]);
        auto v_t4 = _mm_load_ps(&source->M[2][2]);
        auto v_t3 = _mm_shuffle_ps(v_t2, v_t4, _MM_SHUFFLE(0, 0, 3, 2));
        v_t2 = _mm_shuffle_ps(v_t2, v_t1, _MM_SHUFFLE(3, 3, 1, 0));
        v_t2 = _mm_permute_ps(v_t2, _MM_SHUFFLE(1, 1, 0, 2));
        v_t1 = _mm_and_ps(v_t1, Detail::VEC4_MASK_COMPONENTS_3);
        v_t2 = _mm_and_ps(v_t2, Detail::VEC4_MASK_COMPONENTS_3);
        v_t3 = _mm_and_ps(v_t3, Detail::VEC4_MASK_COMPONENTS_3);
        auto v_temp_i = _mm_srli_si128(_mm_castps_si128(v_t4), 32 / 8);
        v_temp_i = _mm_or_si128(v_temp_i, Detail::VEC4_POSITIVE_UNIT_Z.ToM128I());
        Matrix m;
        m.M.R[0] = v_t1;
        m.M.R[1] = v_t2;
        m.M.R[2] = v_t3;
        m.M.R[3] = _mm_castsi128_ps(v_temp_i);
        return m;
#endif
    }

    mathinline Matrix mathcall Matrix::Load(const float3x4a* source) noexcept
    {
        GX_ASSERT(source != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(source), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix m;
        m.M.R[0].F[0] = source->M[0][0];
        m.M.R[0].F[1] = source->M[1][0];
        m.M.R[0].F[2] = source->M[2][0];
        m.M.R[0].F[3] = 0.0F;

        m.M.R[1].F[0] = source->M[0][1];
        m.M.R[1].F[1] = source->M[1][1];
        m.M.R[1].F[2] = source->M[2][1];
        m.M.R[1].F[3] = 0.0F;

        m.M.R[2].F[0] = source->M[0][2];
        m.M.R[2].F[1] = source->M[1][2];
        m.M.R[2].F[2] = source->M[2][2];
        m.M.R[2].F[3] = 0.0F;

        m.M.R[3].F[0] = source->M[0][3];
        m.M.R[3].F[1] = source->M[1][3];
        m.M.R[3].F[2] = source->M[2][3];
        m.M.R[3].F[3] = 1.0F;
        return m;
#elif GRAPHYTE_HW_AVX

        auto v_r0 = _mm_load_ps(&source->M[0][0]);
        auto v_r1 = _mm_load_ps(&source->M[1][0]);
        auto v_r2 = _mm_load_ps(&source->M[2][0]);
        auto v_r3 = Detail::VEC4_POSITIVE_UNIT_W.V;

        auto v_t0 = _mm_shuffle_ps(v_r0, v_r1, _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t2 = _mm_shuffle_ps(v_r0, v_r1, _MM_SHUFFLE(3, 2, 3, 2));
        auto v_t1 = _mm_shuffle_ps(v_r2, v_r3, _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t3 = _mm_shuffle_ps(v_r2, v_r3, _MM_SHUFFLE(3, 2, 3, 2));

        Matrix m;
        m.M.R[0] = _mm_shuffle_ps(v_t0, v_t1, _MM_SHUFFLE(2, 0, 2, 0));
        m.M.R[1] = _mm_shuffle_ps(v_t0, v_t1, _MM_SHUFFLE(3, 1, 3, 1));
        m.M.R[2] = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(2, 0, 2, 0));
        m.M.R[3] = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(3, 1, 3, 1));
        return m;
#endif
    }

    mathinline Matrix mathcall Matrix::Load(const float4x4* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix m;
        m.M.R[0].F[0] = source->M[0][0];
        m.M.R[0].F[1] = source->M[0][1];
        m.M.R[0].F[2] = source->M[0][2];
        m.M.R[0].F[3] = source->M[0][3];

        m.M.R[1].F[0] = source->M[1][0];
        m.M.R[1].F[1] = source->M[1][1];
        m.M.R[1].F[2] = source->M[1][2];
        m.M.R[1].F[3] = source->M[1][3];

        m.M.R[2].F[0] = source->M[2][0];
        m.M.R[2].F[1] = source->M[2][1];
        m.M.R[2].F[2] = source->M[2][2];
        m.M.R[2].F[3] = source->M[2][3];

        m.M.R[3].F[0] = source->M[3][0];
        m.M.R[3].F[1] = source->M[3][1];
        m.M.R[3].F[2] = source->M[3][2];
        m.M.R[3].F[3] = source->M[3][3];
        return m;
#elif GRAPHYTE_HW_AVX
        Matrix m;
        m.M.R[0] = _mm_loadu_ps(&source->M[0][0]);
        m.M.R[1] = _mm_loadu_ps(&source->M[1][0]);
        m.M.R[2] = _mm_loadu_ps(&source->M[2][0]);
        m.M.R[3] = _mm_loadu_ps(&source->M[3][0]);
        return m;
#endif
    }

    mathinline Matrix mathcall Matrix::Load(const float4x3* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix m;
        m.M.R[0].F[0] = source->M[0][0];
        m.M.R[0].F[1] = source->M[0][1];
        m.M.R[0].F[2] = source->M[0][2];
        m.M.R[0].F[3] = 0.0F;

        m.M.R[1].F[0] = source->M[1][0];
        m.M.R[1].F[1] = source->M[1][1];
        m.M.R[1].F[2] = source->M[1][2];
        m.M.R[1].F[3] = 0.0F;

        m.M.R[2].F[0] = source->M[2][0];
        m.M.R[2].F[1] = source->M[2][1];
        m.M.R[2].F[2] = source->M[2][2];
        m.M.R[2].F[3] = 0.0F;

        m.M.R[3].F[0] = source->M[3][0];
        m.M.R[3].F[1] = source->M[3][1];
        m.M.R[3].F[2] = source->M[3][2];
        m.M.R[3].F[3] = 1.0F;
        return m;
#elif GRAPHYTE_HW_AVX
        auto v_t1 = _mm_loadu_ps(&source->M[0][0]);
        auto v_t2 = _mm_loadu_ps(&source->M[1][1]);
        auto v_t4 = _mm_loadu_ps(&source->M[2][2]);
        auto v_t3 = _mm_shuffle_ps(v_t2, v_t4, _MM_SHUFFLE(0, 0, 3, 2));
        v_t2 = _mm_shuffle_ps(v_t2, v_t1, _MM_SHUFFLE(3, 3, 1, 0));
        v_t2 = _mm_permute_ps(v_t2, _MM_SHUFFLE(1, 1, 0, 2));
        v_t1 = _mm_and_ps(v_t1, Detail::VEC4_MASK_COMPONENTS_3);
        v_t2 = _mm_and_ps(v_t2, Detail::VEC4_MASK_COMPONENTS_3);
        v_t3 = _mm_and_ps(v_t3, Detail::VEC4_MASK_COMPONENTS_3);
        auto v_temp_i = _mm_srli_si128(_mm_castps_si128(v_t4), 32 / 8);
        v_temp_i = _mm_or_si128(v_temp_i, Detail::VEC4_POSITIVE_UNIT_W.ToM128I());
        Matrix m;
        m.M.R[0] = v_t1;
        m.M.R[1] = v_t2;
        m.M.R[2] = v_t3;
        m.M.R[3] = _mm_castsi128_ps(v_temp_i);
        return m;
#endif
    }

    mathinline Matrix mathcall Matrix::Load(const float3x4* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix m;
        m.M.R[0].F[0] = source->M[0][0];
        m.M.R[0].F[1] = source->M[1][0];
        m.M.R[0].F[2] = source->M[2][0];
        m.M.R[0].F[3] = 0.0F;

        m.M.R[1].F[0] = source->M[0][1];
        m.M.R[1].F[1] = source->M[1][1];
        m.M.R[1].F[2] = source->M[2][1];
        m.M.R[1].F[3] = 0.0F;

        m.M.R[2].F[0] = source->M[0][2];
        m.M.R[2].F[1] = source->M[1][2];
        m.M.R[2].F[2] = source->M[2][2];
        m.M.R[2].F[3] = 0.0F;

        m.M.R[3].F[0] = source->M[0][3];
        m.M.R[3].F[1] = source->M[1][3];
        m.M.R[3].F[2] = source->M[2][3];
        m.M.R[3].F[3] = 0.0F;
        return m;
#elif GRAPHYTE_HW_AVX
        auto v_r0 = _mm_loadu_ps(&source->M[0][0]);
        auto v_r1 = _mm_loadu_ps(&source->M[1][0]);
        auto v_r2 = _mm_loadu_ps(&source->M[2][0]);
        auto v_r3 = Detail::VEC4_POSITIVE_UNIT_W.V;

        auto v_t0 = _mm_shuffle_ps(v_r0, v_r1, _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t2 = _mm_shuffle_ps(v_r0, v_r1, _MM_SHUFFLE(3, 2, 3, 2));
        auto v_t1 = _mm_shuffle_ps(v_r2, v_r3, _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t3 = _mm_shuffle_ps(v_r2, v_r3, _MM_SHUFFLE(3, 2, 3, 2));

        Matrix m;
        m.M.R[0] = _mm_shuffle_ps(v_t0, v_t1, _MM_SHUFFLE(2, 0, 2, 0));
        m.M.R[1] = _mm_shuffle_ps(v_t0, v_t1, _MM_SHUFFLE(3, 1, 3, 1));
        m.M.R[2] = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(2, 0, 2, 0));
        m.M.R[3] = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(3, 1, 3, 1));
        return m;
#endif
    }

    mathinline Matrix mathcall Matrix::Load(const float3x3* source) noexcept
    {
        GX_ASSERT(source != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        Matrix m;
        m.M.R[0].F[0] = source->M[0][0];
        m.M.R[0].F[1] = source->M[0][1];
        m.M.R[0].F[2] = source->M[0][2];
        m.M.R[0].F[3] = 0.0F;

        m.M.R[1].F[0] = source->M[1][0];
        m.M.R[1].F[1] = source->M[1][1];
        m.M.R[1].F[2] = source->M[1][2];
        m.M.R[1].F[3] = 0.0F;

        m.M.R[2].F[0] = source->M[2][0];
        m.M.R[2].F[1] = source->M[2][1];
        m.M.R[2].F[2] = source->M[2][2];
        m.M.R[2].F[3] = 0.0F;

        m.M.R[3].F[0] = 0.0F;
        m.M.R[3].F[1] = 0.0F;
        m.M.R[3].F[2] = 0.0F;
        m.M.R[3].F[3] = 1.0F;
        return m;
#elif GRAPHYTE_HW_AVX
        auto v_z = _mm_setzero_ps();
        auto v_v1 = _mm_loadu_ps(&source->M[0][0]);
        auto v_v2 = _mm_loadu_ps(&source->M[1][1]);
        auto v_v3 = _mm_load_ss(&source->M[2][2]);

        auto v_t1 = _mm_unpackhi_ps(v_v1, v_z);
        auto v_t2 = _mm_unpacklo_ps(v_v2, v_z);
        auto v_t3 = _mm_shuffle_ps(v_v3, v_t2, _MM_SHUFFLE(0, 1, 0, 0));
        auto v_t4 = _mm_movehl_ps(v_t2, v_t3);
        auto v_t5 = _mm_movehl_ps(v_z, v_t1);

        Matrix m;
        m.M.R[0] = _mm_movelh_ps(v_v1, v_t1);
        m.M.R[1] = _mm_add_ps(v_t4, v_t5);
        m.M.R[2] = _mm_shuffle_ps(v_v2, v_v3, _MM_SHUFFLE(1, 0, 3, 2));
        m.M.R[3] = Detail::VEC4_POSITIVE_UNIT_W.V;
        return m;
#endif
    }

    mathinline void mathcall Matrix::Store(float4x3a* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];

        destination->M[3][0] = m.M.R[3].F[0];
        destination->M[3][1] = m.M.R[3].F[1];
        destination->M[3][2] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        auto v_t1 = m.M.R[0];
        auto v_t2 = m.M.R[1];
        auto v_t3 = m.M.R[2];
        auto v_t4 = m.M.R[3];
        auto v_t2x = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(1, 0, 2, 1));
        v_t2 = _mm_shuffle_ps(v_t2, v_t1, _MM_SHUFFLE(2, 2, 0, 0));
        v_t1 = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(0, 2, 1, 0));
        v_t3 = _mm_shuffle_ps(v_t3, v_t4, _MM_SHUFFLE(0, 0, 2, 2));
        v_t3 = _mm_shuffle_ps(v_t3, v_t4, _MM_SHUFFLE(2, 1, 2, 0));
        _mm_store_ps(&destination->M[0][0], v_t1);
        _mm_store_ps(&destination->M[1][1], v_t2x);
        _mm_store_ps(&destination->M[2][2], v_t3);
#endif
    }

    mathinline void mathcall Matrix::Store(float3x4a* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
        GX_ASSERT(IsAligned(reinterpret_cast<const void*>(destination), std::align_val_t{ 16 }));
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[1].F[0];
        destination->M[0][2] = m.M.R[2].F[0];
        destination->M[0][3] = m.M.R[3].F[0];

        destination->M[1][0] = m.M.R[0].F[1];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[2].F[1];
        destination->M[1][3] = m.M.R[3].F[1];

        destination->M[2][0] = m.M.R[0].F[2];
        destination->M[2][1] = m.M.R[1].F[2];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        auto v_t1 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t3 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        auto v_t2 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t4 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));
        auto v_r0 = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(2, 0, 2, 0));
        auto v_r1 = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(3, 1, 3, 1));
        auto v_r2 = _mm_shuffle_ps(v_t3, v_t4, _MM_SHUFFLE(2, 0, 2, 0));
        _mm_store_ps(&destination->M[0][0], v_r0);
        _mm_store_ps(&destination->M[1][0], v_r1);
        _mm_store_ps(&destination->M[2][0], v_r2);
#endif
    }

    mathinline void mathcall Matrix::Store(float4x4* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];
        destination->M[0][3] = m.M.R[0].F[3];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];
        destination->M[1][3] = m.M.R[1].F[3];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[2].F[3];

        destination->M[3][0] = m.M.R[3].F[0];
        destination->M[3][1] = m.M.R[3].F[1];
        destination->M[3][2] = m.M.R[3].F[2];
        destination->M[3][3] = m.M.R[3].F[3];
#elif GRAPHYTE_HW_AVX
        _mm_storeu_ps(&destination->M[0][0], m.M.R[0]);
        _mm_storeu_ps(&destination->M[1][0], m.M.R[1]);
        _mm_storeu_ps(&destination->M[2][0], m.M.R[2]);
        _mm_storeu_ps(&destination->M[3][0], m.M.R[3]);
#endif
    }

    mathinline void mathcall Matrix::Store(float4x3* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];

        destination->M[3][0] = m.M.R[3].F[0];
        destination->M[3][1] = m.M.R[3].F[1];
        destination->M[3][2] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        auto v_t1 = m.M.R[0];
        auto v_t2 = m.M.R[1];
        auto v_t3 = m.M.R[2];
        auto v_t4 = m.M.R[3];
        auto v_t2x = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(1, 0, 2, 1));
        v_t2 = _mm_shuffle_ps(v_t2, v_t1, _MM_SHUFFLE(2, 2, 0, 0));
        v_t1 = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(0, 2, 1, 0));
        v_t3 = _mm_shuffle_ps(v_t3, v_t4, _MM_SHUFFLE(0, 0, 2, 2));
        v_t3 = _mm_shuffle_ps(v_t3, v_t4, _MM_SHUFFLE(2, 1, 2, 0));
        _mm_storeu_ps(&destination->M[0][0], v_t1);
        _mm_storeu_ps(&destination->M[1][1], v_t2x);
        _mm_storeu_ps(&destination->M[2][2], v_t3);
#endif
    }

    mathinline void mathcall Matrix::Store(float3x4* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[1].F[0];
        destination->M[0][2] = m.M.R[2].F[0];
        destination->M[0][3] = m.M.R[3].F[0];

        destination->M[1][0] = m.M.R[0].F[1];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[2].F[1];
        destination->M[1][3] = m.M.R[3].F[1];

        destination->M[2][0] = m.M.R[0].F[2];
        destination->M[2][1] = m.M.R[1].F[2];
        destination->M[2][2] = m.M.R[2].F[2];
        destination->M[2][3] = m.M.R[3].F[2];
#elif GRAPHYTE_HW_AVX
        auto v_t1 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t3 = _mm_shuffle_ps(m.M.R[0], m.M.R[1], _MM_SHUFFLE(3, 2, 3, 2));
        auto v_t2 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(1, 0, 1, 0));
        auto v_t4 = _mm_shuffle_ps(m.M.R[2], m.M.R[3], _MM_SHUFFLE(3, 2, 3, 2));
        auto v_r0 = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(2, 0, 2, 0));
        auto v_r1 = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(3, 1, 3, 1));
        auto v_r2 = _mm_shuffle_ps(v_t3, v_t4, _MM_SHUFFLE(2, 0, 2, 0));
        _mm_storeu_ps(&destination->M[0][0], v_r0);
        _mm_storeu_ps(&destination->M[1][0], v_r1);
        _mm_storeu_ps(&destination->M[2][0], v_r2);
#endif
    }

    mathinline void mathcall Matrix::Store(float3x3* destination, Matrix m) noexcept
    {
        GX_ASSERT(destination != nullptr);
#if GRAPHYTE_MATH_NO_INTRINSICS
        destination->M[0][0] = m.M.R[0].F[0];
        destination->M[0][1] = m.M.R[0].F[1];
        destination->M[0][2] = m.M.R[0].F[2];

        destination->M[1][0] = m.M.R[1].F[0];
        destination->M[1][1] = m.M.R[1].F[1];
        destination->M[1][2] = m.M.R[1].F[2];

        destination->M[2][0] = m.M.R[2].F[0];
        destination->M[2][1] = m.M.R[2].F[1];
        destination->M[2][2] = m.M.R[2].F[2];
#elif GRAPHYTE_HW_AVX
        auto v_t1 = m.M.R[0];
        auto v_t2 = m.M.R[1];
        auto v_t3 = m.M.R[2];
        auto v_work = _mm_shuffle_ps(v_t1, v_t2, _MM_SHUFFLE(0, 0, 2, 2));
        v_t1 = _mm_shuffle_ps(v_t1, v_work, _MM_SHUFFLE(2, 0, 1, 0));
        _mm_storeu_ps(&destination->M[0][0], v_t1);
        v_t2 = _mm_shuffle_ps(v_t2, v_t3, _MM_SHUFFLE(1, 0, 2, 1));
        _mm_storeu_ps(&destination->M[1][1], v_t2);
        v_t3 = _mm_permute_ps(v_t3, _MM_SHUFFLE(2, 2, 2, 2));
        _mm_store_ss(&destination->M[2][2], v_t3);
#endif
    }

#define MATH_RANK_DECOMPOSE(a, b, c, x, y, z) \
    if((x) < (y)) \
    { \
        if((y) < (z)) \
        { \
            (a) = 2; \
            (b) = 1; \
            (c) = 0; \
        } \
        else \
        { \
            (a) = 1; \
            if((x) < (z)) \
            { \
                (b) = 2; \
                (c) = 0; \
            } \
            else \
            { \
                (b) = 0; \
                (c) = 2; \
            } \
        } \
    } \
    else \
    { \
        if((x) < (z)) \
        { \
            (a) = 2; \
            (b) = 0; \
            (c) = 1; \
        } \
        else \
        { \
            (a) = 0; \
            if((y) < (z)) \
            { \
                (b) = 2; \
                (c) = 1; \
            } \
            else \
            { \
                (b) = 1; \
                (c) = 2; \
            } \
        } \
    }



    mathinline bool mathcall Matrix::Decompose(Vector4* out_scale, Quaternion* out_rotation, Vector4* out_translation, Matrix m) noexcept
    {
        constexpr const auto DecomposeEpsilon = 0.0001F;

        GX_ASSERT(out_scale != nullptr);
        GX_ASSERT(out_rotation != nullptr);
        GX_ASSERT(out_translation != nullptr);

        static const VectorFloat4* canonical_basis[3] = {
            &Detail::VEC4_POSITIVE_UNIT_X.V,
            &Detail::VEC4_POSITIVE_UNIT_Y.V,
            &Detail::VEC4_POSITIVE_UNIT_Z.V,
        };

        out_translation[0] = { m.M.R[3] };

        Matrix temp;
        VectorFloat4* basis[3] = {
            &temp.M.R[0],
            &temp.M.R[1],
            &temp.M.R[2],
        };

        temp.M.R[0] = m.M.R[0];
        temp.M.R[1] = m.M.R[1];
        temp.M.R[2] = m.M.R[2];
        temp.M.R[3] = Detail::VEC4_POSITIVE_UNIT_W;

        auto f_scales = reinterpret_cast<float*>(out_scale);

        size_t a, b, c;

        Vector4::GetX(&f_scales[0], Vector3::Length({ basis[0][0] }));
        Vector4::GetX(&f_scales[1], Vector3::Length({ basis[1][0] }));
        Vector4::GetX(&f_scales[2], Vector3::Length({ basis[2][0] }));
        f_scales[3] = 0.0F;

        MATH_RANK_DECOMPOSE(a, b, c, f_scales[0], f_scales[1], f_scales[2]);

        if (f_scales[a] < DecomposeEpsilon)
        {
            basis[a][0] = canonical_basis[a][0];
        }

        basis[a][0] = Vector3::Normalize({ basis[a][0] }).V;

        if (f_scales[b] < DecomposeEpsilon)
        {
            auto f_abs_x = fabsf(Vector4::GetX({ basis[a][0] }));
            auto f_abs_y = fabsf(Vector4::GetY({ basis[a][0] }));
            auto f_abs_z = fabsf(Vector4::GetZ({ basis[a][0] }));

            size_t aa, bb, cc;
            MATH_RANK_DECOMPOSE(aa, bb, cc, f_abs_x, f_abs_y, f_abs_z);

            basis[b][0] = Vector3::Cross({ basis[a][0] }, { canonical_basis[cc][0] }).V;
        }

        basis[b][0] = Vector3::Normalize({ basis[b][0] }).V;

        if (f_scales[c] < DecomposeEpsilon)
        {
            basis[c][0] = Vector3::Cross({ basis[a][0] }, { basis[b][0] }).V;
        }

        basis[c][0] = Vector3::Normalize({ basis[c][0] }).V;

        auto f_det = Vector4::GetX(Matrix::Determinant(temp));

        if (f_det < 0.0F)
        {
            f_scales[a] = -f_scales[a];
            basis[a][0] = Vector4::Negate({ basis[a][0] }).V;
            f_det = -f_det;
        }

        f_det -= 1.0F;
        f_det *= f_det;

        if (DecomposeEpsilon < f_det)
        {
            return false;
        }

        out_rotation[0] = Quaternion::RotationMatrix(temp);
        return true;
    }

#undef MATH_RANK_DECOMPOSE

    mathinline Matrix mathcall Matrix::Make(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) noexcept
    {
        Matrix m_result;
#if GRAPHYTE_MATH_NO_INTRINSICS
        m_result.M.M[0][0] = m00;
        m_result.M.M[0][1] = m01;
        m_result.M.M[0][2] = m02;
        m_result.M.M[0][3] = m03;
        m_result.M.M[1][0] = m10;
        m_result.M.M[1][1] = m11;
        m_result.M.M[1][2] = m12;
        m_result.M.M[1][3] = m13;
        m_result.M.M[2][0] = m20;
        m_result.M.M[2][1] = m21;
        m_result.M.M[2][2] = m22;
        m_result.M.M[2][3] = m23;
        m_result.M.M[3][0] = m30;
        m_result.M.M[3][1] = m31;
        m_result.M.M[3][2] = m32;
        m_result.M.M[3][3] = m33;
#elif GRAPHYTE_HW_AVX
        m_result.M.R[0] = _mm_set_ps(m03, m02, m01, m00);
        m_result.M.R[1] = _mm_set_ps(m13, m12, m11, m10);
        m_result.M.R[2] = _mm_set_ps(m23, m22, m21, m20);
        m_result.M.R[3] = _mm_set_ps(m33, m32, m31, m30);
#endif
        return m_result;
    }

    mathinline Matrix mathcall Matrix::FromRollPitchYaw(float pitch, float yaw, float roll) noexcept
    {
        auto v_angles = Vector3::Make(pitch, yaw, roll);
        return Matrix::FromRollPitchYaw(v_angles);
    }

    mathinline Matrix mathcall Matrix::FromRollPitchYaw(Vector3 angles) noexcept
    {
        auto q_rotation = Quaternion::RotationFromRollPitchYaw(angles);
        return Matrix::FromRotationQuaternion(q_rotation);
    }

    mathinline Matrix mathcall Matrix::Transformation2D(Vector2 scaling_origin, float scaling_orientation, Vector2 scaling, Vector2 rotation_origin, float rotation, Vector2 translation) noexcept
    {
        auto v_scaling_origin = Vector4::Select({ Detail::VEC4_MASK_SELECT_1100.V }, { scaling_origin.V }, { Detail::VEC4_MASK_SELECT_1100.V });
        auto v_neg_scaling_origin = Vector4::Negate(v_scaling_origin);

        auto m_scaling_origin_i = Matrix::Translation({ v_neg_scaling_origin.V });
        auto m_scaling_orientation = Matrix::RotationZ(scaling_orientation);
        auto m_scaling_orientation_t = Matrix::Transpose(m_scaling_orientation);
        auto v_scaling = Vector4::Select({ Detail::VEC4_ONE_4.V }, { scaling.V }, { Detail::VEC4_MASK_SELECT_1100.V });
        auto m_scaling = Matrix::Scaling(Vector3{ v_scaling.V });
        auto v_rotation_origin = Vector4::Select({ Detail::VEC4_MASK_SELECT_1100.V }, { rotation_origin.V }, { Detail::VEC4_MASK_SELECT_1100.V });
        auto m_rotation = Matrix::RotationZ(rotation);
        auto v_translation = Vector4::Select({ Detail::VEC4_MASK_SELECT_1100.V }, { translation.V }, { Detail::VEC4_MASK_SELECT_1100.V });

        auto m_result = Matrix::Multiply(m_scaling_origin_i, m_scaling_orientation_t);
        m_result = Matrix::Multiply(m_result, m_scaling);
        m_result = Matrix::Multiply(m_result, m_scaling_orientation);
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_scaling_origin).V;
        m_result.M.R[3] = Vector4::Subtract({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result = Matrix::Multiply(m_result, m_rotation);
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_translation).V;

        return m_result;
    }

    mathinline Matrix mathcall Matrix::AffineTransformation2D(Vector2 scaling, Vector2 rotation_origin, float rotation, Vector2 translation) noexcept
    {
        auto v_scaling = Vector4::Select({ Detail::VEC4_ONE_4.V }, { scaling.V }, { Detail::VEC4_MASK_SELECT_1100.V });
        auto m_result = Matrix::Scaling(Vector3{ v_scaling.V });
        auto v_rotation_origin = Vector4::Select({ Detail::VEC4_ONE_4.V }, { rotation_origin.V }, { Detail::VEC4_MASK_SELECT_1100.V });
        auto m_rotation = Matrix::RotationZ(rotation);
        auto v_translation = Vector4::Select({ Detail::VEC4_MASK_SELECT_1100.V }, { translation.V }, { Detail::VEC4_MASK_SELECT_1100.V });

        m_result.M.R[3] = Vector4::Subtract({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result = Matrix::Multiply(m_result, m_rotation);
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_translation).V;

        return m_result;
    }

    mathinline Matrix mathcall Matrix::Transformation(Vector3 scaling_origin, Quaternion scaling_orientation_quaternion, Vector3 scaling, Vector3 rotation_origin, Quaternion rotation_quaternion, Vector3 translation) noexcept
    {
        auto v_scaling_origin = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { scaling_origin.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto v_neg_scaling_origin = Vector4::Negate(v_scaling_origin);

        auto m_scaling_origin_i = Matrix::Translation({ v_neg_scaling_origin.V });
        auto m_scaling_orientation = Matrix::FromRotationQuaternion(scaling_orientation_quaternion);
        auto m_scaling_orientation_t = Matrix::Transpose(m_scaling_orientation);
        auto m_scaling = Matrix::Scaling(scaling);
        auto v_rotation_origin = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { rotation_origin.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto m_rotation = Matrix::FromRotationQuaternion(rotation_quaternion);
        auto v_translation = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { translation.V }, { Detail::VEC4_MASK_SELECT_1110.V });

        Matrix m_result = Matrix::Multiply(m_scaling_origin_i, m_scaling_orientation_t);

        m_result = Matrix::Multiply(m_result, m_scaling);
        m_result = Matrix::Multiply(m_result, m_scaling_orientation);
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_scaling_origin).V;
        m_result.M.R[3] = Vector4::Subtract({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result = Matrix::Multiply(m_result, m_rotation);
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_translation).V;

        return m_result;
    }

    mathinline Matrix mathcall Matrix::AffineTransformation(Vector3 scaling, Vector3 rotation_origin, Quaternion rotation_quaternion, Vector3 translation) noexcept
    {
        auto m_result = Matrix::Scaling(scaling);
        auto v_rotation_origin = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { rotation_origin.V }, { Detail::VEC4_MASK_SELECT_1110.V });
        auto m_rotation = Matrix::FromRotationQuaternion(rotation_quaternion);
        auto v_translation = Vector4::Select({ Detail::VEC4_MASK_SELECT_1110.V }, { translation.V }, { Detail::VEC4_MASK_SELECT_1110.V });

        m_result.M.R[3] = Vector4::Subtract({ m_result.M.R[3] }, v_rotation_origin).V;
        m_result = Matrix::Multiply(m_result, m_rotation);
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, { v_rotation_origin.V }).V;
        m_result.M.R[3] = Vector4::Add({ m_result.M.R[3] }, v_translation).V;

        return m_result;
    }

#if false
    mathinline Matrix mathcall Matrix::Reflect(Plane reflection_plane) noexcept
    {
        GX_ASSERT(!Vector3::IsEqual({ reflection_plane.V }, Vector3::Zero()));
        GX_ASSERT(!Plane::IsInfinite(reflection_plane));

        static const Detail::Vector4F32 negative_two = { { { -2.0F, -2.0F, -2.0F, 0.0F } } };

        auto v_p = Vector4{ Plane::Normalize(reflection_plane).V };
        auto v_s = Vector4::Multiply(v_p, { negative_two.V });

        auto v_a = Vector4::SplatX(v_p);
        auto v_b = Vector4::SplatY(v_p);
        auto v_c = Vector4::SplatZ(v_p);
        auto v_d = Vector4::SplatW(v_p);

        Matrix m_result;

        m_result.M.R[0] = Vector4::MultiplyAdd(v_a, v_s, Vector4::UnitX()).V;
        m_result.M.R[1] = Vector4::MultiplyAdd(v_b, v_s, Vector4::UnitY()).V;
        m_result.M.R[2] = Vector4::MultiplyAdd(v_c, v_s, Vector4::UnitZ()).V;
        m_result.M.R[3] = Vector4::MultiplyAdd(v_d, v_s, Vector4::UnitW()).V;

        return m_result;
    }

    mathinline Matrix mathcall Matrix::Shadow(Plane shadow_plane, Vector4 light_position) noexcept
    {
        GX_ASSERT(!Vector3::IsEqual({ shadow_plane.V }, Vector3::Zero()));
        GX_ASSERT(!Plane::IsInfinite(shadow_plane));

        auto v_p = Plane::Normalize(shadow_plane);
        auto v_dot = Plane::Dot(v_p, { light_position.V });
        auto p_p = Vector4::Negate({ v_p.V });

        auto v_d = Vector4::SplatW(p_p);
        auto v_c = Vector4::SplatZ(p_p);
        auto v_b = Vector4::SplatY(p_p);
        auto v_a = Vector4::SplatX(p_p);

        v_dot = Vector4::Select({ Detail::VEC4_MASK_SELECT_0001.V }, v_dot, { Detail::VEC4_MASK_SELECT_0001.V });

        Matrix m_result;

        m_result.M.R[3] = Vector4::MultiplyAdd(v_d, light_position, v_dot).V;
        v_dot = Vector4::RotateLeft(v_dot, 1);
        m_result.M.R[2] = Vector4::MultiplyAdd(v_c, light_position, v_dot).V;
        v_dot = Vector4::RotateLeft(v_dot, 1);
        m_result.M.R[1] = Vector4::MultiplyAdd(v_b, light_position, v_dot).V;
        v_dot = Vector4::RotateLeft(v_dot, 1);
        m_result.M.R[0] = Vector4::MultiplyAdd(v_a, light_position, v_dot).V;

        return m_result;
    }
#endif

    mathinline Matrix mathcall Matrix::LookAtLH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
    {
        auto v_eye_direction = Vector4::Subtract({ focus_position.V }, { eye_position.V });
        return Matrix::LookToLH(eye_position, { v_eye_direction.V }, up_direction);
    }

    mathinline Matrix mathcall Matrix::LookAtRH(Vector3 eye_position, Vector3 focus_position, Vector3 up_direction) noexcept
    {
        auto v_neg_eye_direction = Vector4::Subtract({ focus_position.V }, { eye_position.V });
        return Matrix::LookToLH(eye_position, { v_neg_eye_direction.V }, up_direction);
    }

    mathinline Matrix mathcall Matrix::LookToLH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
    {
        GX_ASSERT(!Vector3::IsEqual(eye_direction, Vector3::Zero()));
        GX_ASSERT(!Vector3::IsInfinite(eye_direction));
        GX_ASSERT(!Vector3::IsEqual(up_direction, Vector3::Zero()));
        GX_ASSERT(!Vector3::IsInfinite(up_direction));

        auto v_r2 = Vector3::Normalize(eye_direction);
        auto v_r0 = Vector3::Cross(up_direction, v_r2);
        v_r0 = Vector3::Normalize(v_r0);

        auto v_r1 = Vector3::Cross(v_r2, v_r0);

        auto v_neg_eye_position = Vector3{ Vector4::Negate({ eye_position.V }).V };

        auto v_d0 = Vector3::Dot(v_r0, v_neg_eye_position);
        auto v_d1 = Vector3::Dot(v_r1, v_neg_eye_position);
        auto v_d2 = Vector3::Dot(v_r2, v_neg_eye_position);

        Matrix m_result;
        m_result.M.R[0] = Vector4::Select(v_d0, { v_r0.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V;
        m_result.M.R[1] = Vector4::Select(v_d1, { v_r1.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V;
        m_result.M.R[2] = Vector4::Select(v_d2, { v_r2.V }, { Detail::VEC4_MASK_SELECT_1110.V }).V;
        m_result.M.R[3] = Detail::VEC4_POSITIVE_UNIT_W.V;

        m_result = Matrix::Transpose(m_result);

        return m_result;
    }

    mathinline Matrix mathcall Matrix::LookToRH(Vector3 eye_position, Vector3 eye_direction, Vector3 up_direction) noexcept
    {
        auto v_neg_eye_direction = Vector3{ Vector4::Negate({ eye_direction.V }).V };
        return Matrix::LookToLH(eye_position, v_neg_eye_direction, up_direction);
    }

    mathinline Matrix mathcall Matrix::PerspectiveLH(float width, float height, float z_near, float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0F && z_far > 0.0F);
        GX_ASSERT(!Maths::IsEqual(width, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(height, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_two_z_near = z_near + z_near;
        auto f_range = z_far / (z_far - z_near);

        Matrix m_result;

        m_result.M.M[0][0] = f_two_z_near / width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_two_z_near / height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 1.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = -f_range * z_near;
        m_result.M.M[3][3] = 0.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        auto f_two_z_near = z_near + z_near;
        auto f_range = z_far / (z_far - z_near);

        Detail::Vector4F32 v_mem = { { {
                f_two_z_near / width,
                f_two_z_near / height,
                f_range,
                -f_range * z_near,
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);

        Matrix m_result;
        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        v_values = _mm_shuffle_ps(v_values, Detail::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));

        v_temp = _mm_setzero_ps();
        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(3, 0, 0, 0));

        m_result.M.R[2] = v_temp;

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(2, 1, 0, 0));

        m_result.M.R[3] = v_temp;

        return m_result;
#endif
    }

    mathinline Matrix mathcall Matrix::PerspectiveRH(float width, float height, float z_near, float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0F && z_far > 0.0F);
        GX_ASSERT(!Maths::IsEqual(width, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(height, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_two_z_near = z_near + z_near;
        auto f_range = z_far / (z_near - z_far);

        Matrix m_result;

        m_result.M.M[0][0] = f_two_z_near / width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_two_z_near / height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = -1.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = f_range * z_near;
        m_result.M.M[3][3] = 0.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        auto f_two_z_near = z_near + z_near;
        auto f_range = z_far / (z_near - z_far);

        Detail::Vector4F32 v_mem = { { {
                f_two_z_near / width,
                f_two_z_near / height,
                f_range,
                f_range * z_near,
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);

        Matrix m_result;
        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        v_values = _mm_shuffle_ps(v_values, Detail::VEC4_NEGATIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));

        v_temp = _mm_setzero_ps();
        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(3, 0, 0, 0));

        m_result.M.R[2] = v_temp;

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(2, 1, 0, 0));

        m_result.M.R[3] = v_temp;

        return m_result;
#endif
    }

    mathinline Matrix mathcall Matrix::PerspectiveFovLH(float fov_angle_y, float aspect_ratio, float z_near, float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0F && z_far > 0.0F);
        GX_ASSERT(!Maths::IsEqual(fov_angle_y, 0.0F, 0.00001F * 2.0F));
        GX_ASSERT(!Maths::IsEqual(aspect_ratio, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        float f_sin_fov;
        float f_cos_fov;
        SinCos(f_sin_fov, f_cos_fov, fov_angle_y * 0.5F);

        auto f_height = f_cos_fov / f_sin_fov;
        auto f_width = f_height / aspect_ratio;
        auto f_range = z_far / (z_far - z_near);

        Matrix m_result;

        m_result.M.M[0][0] = f_width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 1.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = -f_range * z_near;
        m_result.M.M[3][3] = 0.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        float f_sin_fov;
        float f_cos_fov;
        SinCos(f_sin_fov, f_cos_fov, fov_angle_y * 0.5F);

        auto f_range = z_far / (z_far - z_near);
        auto f_height = f_cos_fov / f_sin_fov;

        Detail::Vector4F32 v_mem = { { {
                f_height / aspect_ratio,
                f_height,
                f_range,
                -f_range * z_near,
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();

        v_temp = _mm_move_ss(v_temp, v_values);

        Matrix m_result;

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        v_temp = _mm_setzero_ps();
        v_values = _mm_shuffle_ps(v_values, Detail::VEC4_POSITIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));
        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(3, 0, 0, 0));

        m_result.M.R[2] = v_temp;

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(2, 1, 0, 0));

        m_result.M.R[3] = v_temp;

        return m_result;

#endif
    }

    mathinline Matrix mathcall Matrix::PerspectiveFovRH(float fov_angle_y, float aspect_ratio, float z_near, float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0F && z_far > 0.0F);
        GX_ASSERT(!Maths::IsEqual(fov_angle_y, 0.0F, 0.00001F * 2.0F));
        GX_ASSERT(!Maths::IsEqual(aspect_ratio, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        float f_sin_fov;
        float f_cos_fov;
        SinCos(f_sin_fov, f_cos_fov, fov_angle_y * 0.5F);

        auto f_height = f_cos_fov / f_sin_fov;
        auto f_width = f_height / aspect_ratio;
        auto f_range = z_far / (z_near - z_far);

        Matrix m_result;

        m_result.M.M[0][0] = f_width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = -1.0F;

        m_result.M.M[3][0] = f_width;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = f_range * z_near;
        m_result.M.M[3][3] = 0.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        float f_sin_fov;
        float f_cos_fov;
        SinCos(f_sin_fov, f_cos_fov, fov_angle_y * 0.5F);

        auto f_range = z_far / (z_near - z_far);
        auto f_height = f_cos_fov / f_sin_fov;

        Detail::Vector4F32 v_mem = { { {
                f_height / aspect_ratio,
                f_height,
                f_range,
                f_range * z_near,
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();

        v_temp = _mm_move_ss(v_temp, v_values);

        Matrix m_result;

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        v_temp = _mm_setzero_ps();
        v_values = _mm_shuffle_ps(v_values, Detail::VEC4_NEGATIVE_UNIT_W.V, _MM_SHUFFLE(3, 2, 3, 2));
        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(3, 0, 0, 0));

        m_result.M.R[2] = v_temp;

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(2, 1, 0, 0));

        m_result.M.R[3] = v_temp;

        return m_result;

#endif
    }

    mathinline Matrix mathcall Matrix::PerspectiveOffCenterLH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0F && z_far > 0.0F);
        GX_ASSERT(!Maths::IsEqual(right, left, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(top, bottom, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_two_z_near = z_near + z_near;
        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = z_far / (z_far - z_near);

        Matrix m_result;

        m_result.M.M[0][0] = f_two_z_near * f_rcp_width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_two_z_near * f_rcp_height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = -(left + right) * f_rcp_width;
        m_result.M.M[2][1] = -(top + bottom) * f_rcp_height;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 1.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = -f_range * z_near;
        m_result.M.M[3][3] = 0.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        auto f_two_z_near = z_near + z_near;
        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = z_far / (z_far - z_near);

        Detail::Vector4F32 v_mem = { { {
                f_two_z_near * f_rcp_width,
                f_two_z_near * f_rcp_height,
                -f_range * z_near,
                0.0F,
            } } };

        Matrix m_result;

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        m_result.M.R[2] = Vector4::Make(
            -(left + right) * f_rcp_width,
            -(top + bottom) * f_rcp_height,
            f_range,
            1.0F
        ).V;


        v_values = _mm_and_ps(v_values, Detail::VEC4_MASK_COMPONENT_Z.V);

        m_result.M.R[3] = v_values;

        return m_result;

#endif
    }

    mathinline Matrix mathcall Matrix::PerspectiveOffCenterRH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept
    {
        GX_ASSERT(z_near > 0.0F && z_far > 0.0F);
        GX_ASSERT(!Maths::IsEqual(right, left, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(top, bottom, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_two_z_near = z_near + z_near;
        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = z_far / (z_near - z_far);

        Matrix m_result;

        m_result.M.M[0][0] = f_two_z_near * f_rcp_width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_two_z_near * f_rcp_height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = (left + right) * f_rcp_width;
        m_result.M.M[2][1] = (top + bottom) * f_rcp_height;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = -1.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = f_range * z_near;
        m_result.M.M[3][3] = 0.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        auto f_two_z_near = z_near + z_near;
        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = z_far / (z_near - z_far);

        Matrix m_result;

        Detail::Vector4F32 v_mem = { { {
                f_two_z_near * f_rcp_width,
                f_two_z_near * f_rcp_height,
                f_range * z_near,
                0.0F,
            } } };

        auto v_values = v_mem.V;

        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        m_result.M.R[2] = Vector4::Make(
            (left + right) * f_rcp_width,
            (top + bottom) * f_rcp_height,
            f_range,
            -1.0F
        ).V;

        v_values = _mm_and_ps(v_values, Detail::VEC4_MASK_COMPONENT_Z.V);

        m_result.M.R[3] = v_values;

        return m_result;
#endif
    }

    mathinline Matrix mathcall Matrix::OrthographicLH(float width, float height, float z_near, float z_far) noexcept
    {
        GX_ASSERT(!Maths::IsEqual(width, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(height, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_range = 1.0F / (z_far - z_near);

        Matrix m_result;

        m_result.M.M[0][0] = 2.0F / width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = 2.0F / height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 0.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = f_range * z_near;
        m_result.M.M[3][3] = 1.0F;

        return m_result;
#elif GRAPHYTE_HW_AVX

        Matrix m_result;

        auto f_range = 1.0F / (z_far - z_near);

        Detail::Vector4F32 v_mem = { { {
                2.0F / width,
                2.0F / height,
                f_range,
                -f_range * z_near
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        v_temp = _mm_setzero_ps();
        v_values = _mm_shuffle_ps(v_values, Detail::VEC4_POSITIVE_UNIT_W, _MM_SHUFFLE(3, 2, 3, 2));

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(2, 0, 0, 0));

        m_result.M.R[2] = v_temp;

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(3, 1, 0, 0));

        m_result.M.R[3] = v_temp;

        return m_result;
#endif
    }

    mathinline Matrix mathcall Matrix::OrthographicRH(float width, float height, float z_near, float z_far) noexcept
    {
        GX_ASSERT(!Maths::IsEqual(width, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(height, 0.0F, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_far, z_near, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_range = 1.0F / (z_near - z_far);

        Matrix m_result;

        m_result.M.M[0][0] = 2.0F / width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = 2.0F / height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 0.0F;

        m_result.M.M[3][0] = 0.0F;
        m_result.M.M[3][1] = 0.0F;
        m_result.M.M[3][2] = f_range * z_near;
        m_result.M.M[3][3] = 1.0F;

        return m_result;
#elif GRAPHYTE_HW_AVX

        Matrix m_result;

        auto f_range = 1.0F / (z_near - z_far);

        Detail::Vector4F32 v_mem = { { {
                2.0F / width,
                2.0F / height,
                f_range,
                f_range * z_near
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);

        m_result.M.R[1] = v_temp;

        v_temp = _mm_setzero_ps();
        v_values = _mm_shuffle_ps(v_values, Detail::VEC4_POSITIVE_UNIT_W, _MM_SHUFFLE(3, 2, 3, 2));

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(2, 0, 0, 0));

        m_result.M.R[2] = v_temp;

        v_temp = _mm_shuffle_ps(v_temp, v_values, _MM_SHUFFLE(3, 1, 0, 0));

        m_result.M.R[3] = v_temp;

        return m_result;
#endif
    }

    mathinline Matrix mathcall Matrix::OrthographicOffCenterLH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept
    {
        GX_ASSERT(!Maths::IsEqual(right, left, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(top, bottom, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_near, z_far, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = 1.0F / (z_far - z_near);

        Matrix m_result;

        m_result.M.M[0][0] = f_rcp_width + f_rcp_width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_rcp_height + f_rcp_height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 0.0F;

        m_result.M.M[3][0] = -(left + right) * f_rcp_width;
        m_result.M.M[3][1] = -(top + bottom) * f_rcp_height;
        m_result.M.M[3][2] = -f_range * z_near;
        m_result.M.M[3][3] = 1.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = 1.0F / (z_far - z_near);

        Detail::Vector4F32 v_mem = { { {
                f_rcp_width,
                f_rcp_height,
                f_range,
                1.0F
            } } };

        Detail::Vector4F32 v_mem2 = { { {
                -(left + right),
                -(top + bottom),
                -z_near,
                1.0F
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);
        v_temp = _mm_add_ss(v_temp, v_temp);

        Matrix m_result;

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);
        v_temp = _mm_add_ps(v_temp, v_temp);

        m_result.M.R[1] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Z.V);

        m_result.M.R[2] = v_temp;

        v_values = _mm_mul_ps(v_values, v_mem2.V);

        m_result.M.R[3] = v_values;

        return m_result;

#endif
    }

    mathinline Matrix mathcall Matrix::OrthographicOffCenterRH(float left, float right, float bottom, float top, float z_near, float z_far) noexcept
    {
        GX_ASSERT(!Maths::IsEqual(right, left, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(top, bottom, 0.00001F));
        GX_ASSERT(!Maths::IsEqual(z_near, z_far, 0.00001F));

#if GRAPHYTE_MATH_NO_INTRINSICS

        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = 1.0F / (z_near - z_far);

        Matrix m_result;
        m_result.M.M[0][0] = f_rcp_width + f_rcp_width;
        m_result.M.M[0][1] = 0.0F;
        m_result.M.M[0][2] = 0.0F;
        m_result.M.M[0][3] = 0.0F;

        m_result.M.M[1][0] = 0.0F;
        m_result.M.M[1][1] = f_rcp_height + f_rcp_height;
        m_result.M.M[1][2] = 0.0F;
        m_result.M.M[1][3] = 0.0F;

        m_result.M.M[2][0] = 0.0F;
        m_result.M.M[2][1] = 0.0F;
        m_result.M.M[2][2] = f_range;
        m_result.M.M[2][3] = 0.0F;

        m_result.M.M[3][0] = -(left + right) * f_rcp_width;
        m_result.M.M[3][1] = -(top + bottom) * f_rcp_height;
        m_result.M.M[3][2] = f_range * z_near;
        m_result.M.M[3][3] = 1.0F;

        return m_result;

#elif GRAPHYTE_HW_AVX

        auto f_rcp_width = 1.0F / (right - left);
        auto f_rcp_height = 1.0F / (top - bottom);
        auto f_range = 1.0F / (z_near - z_far);

        Detail::Vector4F32 v_mem = { { {
                f_rcp_width,
                f_rcp_height,
                f_range,
                1.0F
            } } };

        Detail::Vector4F32 v_mem2 = { { {
                -(left + right),
                -(top + bottom),
                z_near,
                1.0F
            } } };

        auto v_values = v_mem.V;
        auto v_temp = _mm_setzero_ps();
        v_temp = _mm_move_ss(v_temp, v_values);
        v_temp = _mm_add_ss(v_temp, v_temp);

        Matrix m_result;

        m_result.M.R[0] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Y.V);
        v_temp = _mm_add_ps(v_temp, v_temp);

        m_result.M.R[1] = v_temp;

        v_temp = v_values;
        v_temp = _mm_and_ps(v_temp, Detail::VEC4_MASK_COMPONENT_Z.V);

        m_result.M.R[2] = v_temp;

        v_values = _mm_mul_ps(v_values, v_mem2.V);

        m_result.M.R[3] = v_values;

        return m_result;
#endif
    }
}
