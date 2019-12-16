
#if false

template <int X, int Y, int Z, int W> vec4 mathcall swizzle(vec4 v) noexcept { return { _mm_permute_ps(v.V, _MM_SHUFFLE(W, Z, Y, X)) }; }
template<> vec4 mathcall swizzle<0, 1, 2, 3>(vec4 v) noexcept { return v; }

template<> vec4 mathcall swizzle<0, 1, 0, 1>(vec4 v) noexcept { return { _mm_movelh_ps(v.V, v.V) }; }
template<> vec4 mathcall swizzle<2, 3, 2, 3>(vec4 v) noexcept { return { _mm_movehl_ps(v.V, v.V) }; }
template<> vec4 mathcall swizzle<0, 0, 1, 1>(vec4 v) noexcept { return { _mm_unpacklo_ps(v.V, v.V) }; }
template<> vec4 mathcall swizzle<2, 2, 3, 3>(vec4 v) noexcept { return { _mm_unpackhi_ps(v.V, v.V) }; }
template<> vec4 mathcall swizzle<0, 0, 2, 2>(vec4 v) noexcept { return { _mm_moveldup_ps(v.V) }; }
template<> vec4 mathcall swizzle<1, 1, 3, 3>(vec4 v) noexcept { return { _mm_movehdup_ps(v.V) }; }

bool4 mathcall cmpnan(vec4 v) noexcept { return { _mm_cmpneq_ps(v.V, v.V) }; }
bool3 mathcall cmpnan(vec3 v) noexcept { return { _mm_cmpneq_ps(v.V, v.V) }; }
bool2 mathcall cmpnan(vec2 v) noexcept { return { _mm_cmpneq_ps(v.V, v.V) }; }

vec4 mathcall rcp(vec4 v) noexcept { return { _mm_div_ps(v.V, const_vec4_one_4.V) }; }
vec3 mathcall rcp(vec3 v) noexcept { return { _mm_div_ps(v.V, const_vec4_one_4.V) }; }
vec2 mathcall rcp(vec2 v) noexcept { return { _mm_div_ps(v.V, const_vec4_one_4.V) }; }

vec4 mathcall min(vec4 v1, vec4 v2) noexcept { return { _mm_min_ps(v1.V, v2.V) }; }
vec4 mathcall max(vec4 v1, vec4 v2) noexcept { return { _mm_max_ps(v1.V, v2.V) }; }

vec4 mathcall round(vec4 v) noexcept { return { _mm_round_ps(v.V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC) }; }
vec4 mathcall trunc(vec4 v) noexcept { return { _mm_round_ps(v.V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC) }; }
vec4 mathcall floor(vec4 v) noexcept { return { _mm_floor_ps(v.V) }; }
vec4 mathcall ceil(vec4 v) noexcept { return { _mm_ceil_ps(v.V) }; }
vec4 mathcall fract(vec4 v) noexcept {
    __m128 vtemp = _mm_floor_ps(v.V);
    __m128 vresult = _mm_sub_ps(v.V, vtemp);
    return { vresult };
}
vec4 mathcall clamp(vec4 v, vec4 min, vec4 max) noexcept {
    __m128 vresult = _mm_max_ps(min.V, max.V);
    vresult = _mm_min_ps(max.V, vresult);
    return { vresult };
}

template <> quat mathcall identity<quat>() noexcept { return { const_vec4_positive_unit_w.V }; }
template <> matrix mathcall identity<matrix>() noexcept {
    return { {
        const_vec4_positive_unit_x.V,
        const_vec4_positive_unit_y.V,
        const_vec4_positive_unit_z.V,
        const_vec4_positive_unit_w.V,
    } };
}

vec4 mathcall cmpbounds(vec4 v, vec4 bounds) noexcept {
        auto v_temp1 = _mm_cmple_ps(v.V, bounds.V);
        auto v_temp2 = _mm_mul_ps(bounds.V, const_vec4_negative_one_4.V);
        v_temp2 = _mm_cmple_ps(v_temp2, v.V);
        v_temp1 = _mm_and_ps(v_temp1, v_temp2);
        return { v_temp1 };
}

vec3 mathcall cmpbounds(vec3 v, vec3 bounds) noexcept {
    return tovec3(cmpbounds(tovec4(v), tovec4(bounds)));
}

vec2 mathcall cmpbounds(vec2 v, vec2 bounds) noexcept {
    return tovec2(cmpbounds(tovec4(v), tovec4(bounds)));
}

bool any_true(bool3 v) noexcept { return _mm_movemask_ps(v.V) != 0; }
bool any_false(bool3 v) noexcept { return _mm_movemask_ps(v.V) != 0b0111; }
bool all_true(bool3 v) noexcept { return _mm_movemask_ps(v.V) == 0b0111; }
bool all_false(bool3 v) noexcept { return _mm_movemask_ps(v.V) == 0; }

bool any_true(bool2 v) noexcept { return _mm_movemask_ps(v.V) != 0; }
bool any_false(bool2 v) noexcept { return _mm_movemask_ps(v.V) != 0b0011; }
bool all_true(bool2 v) noexcept { return _mm_movemask_ps(v.V) == 0b0011; }
bool all_false(bool2 v) noexcept { return _mm_movemask_ps(v.V) == 0; }

vec4 mathcall convert_int_to_float(vec4 vint, uint32_t exponent) noexcept {
    auto v_result = _mm_cvtepi32_ps(_mm_castps_si128(vint.V));
    auto v_scale = _mm_set1_epi32(static_cast<int32_t>(0x3F800000U - (exponent << 23)));
    v_result = _mm_mul_ps(v_result, _mm_castsi128_ps(v_scale));
    return { v_result };
}
vec4 mathcall convert_float_to_int(vec4 vfloat, uint32_t mul_exponent) noexcept {
    auto v_result   = _mm_set_ps1(static_cast<float>(1U << mul_exponent));
    v_result        = _mm_mul_ps(v_result, vfloat.V);
    auto v_overflow = _mm_cmpgt_ps(v_result, const_vec4_intmax.V);
    auto v_result_i = _mm_cvttps_epi32(v_result);
    v_result        = _mm_and_ps(v_overflow, const_vec4_mask_abs.V);
    v_overflow      = _mm_andnot_ps(v_overflow, _mm_castsi128_ps(v_result_i));
    v_overflow      = _mm_or_ps(v_overflow, v_result);
    return { v_overflow };
}

vec4 mathcall convert_uint_to_float(vec4 vuint, uint32_t div_exponent) noexcept {
    auto v_mask    = _mm_and_ps(vuint.V, const_vec4_negative_zero.V);
    auto v_result  = _mm_xor_ps(vuint.V, v_mask);
    v_result       = _mm_cvtepi32_ps(_mm_castps_si128(v_result));
    auto v_i_mask  = _mm_srai_epi32(_mm_castps_si128(v_mask), 31);
    v_mask         = _mm_and_ps(_mm_castsi128_ps(v_i_mask), const_vec4_unsigned_fix.V);
    v_result       = _mm_add_ps(v_result, v_mask);
    uint32_t scale = 0x3F800000U - (div_exponent << 23);
    v_i_mask       = _mm_set1_epi32(static_cast<int>(scale));
    v_result       = _mm_mul_ps(v_result, _mm_castsi128_ps(v_i_mask));
    return { v_result };
}

vec4 mathcall convert_float_to_uint(vec4 vfloat, uint32_t mul_exponent) noexcept {
    auto v_result   = _mm_set_ps1(static_cast<float>(1U << mul_exponent));
    v_result        = _mm_mul_ps(v_result, vfloat.V);
    v_result        = _mm_max_ps(v_result, _mm_setzero_ps());
    auto v_overflow = _mm_cmpgt_ps(v_result, const_vec4_uintmax.V);
    auto v_value    = const_vec4_unsigned_fix.V;
    auto v_mask     = _mm_cmpge_ps(v_result, v_value);
    v_value         = _mm_and_ps(v_value, v_mask);
    v_result        = _mm_sub_ps(v_result, v_value);
    auto v_result_i = _mm_cvttps_epi32(v_result);
    v_mask          = _mm_and_ps(v_mask, const_vec4_negative_zero.V);
    v_result        = _mm_xor_ps(_mm_castsi128_ps(v_result_i), v_mask);
    v_result        = _mm_or_ps(v_result, v_overflow);
    return { v_result };
}

matrix mathcall transpose(matrix m) noexcept {
    __m128 v_temp1 = _mm_shuffle_ps(m.R[0], m.R[1], _MM_SHUFFLE(1, 0, 1, 0));
    __m128 v_temp3 = _mm_shuffle_ps(m.R[0], m.R[1], _MM_SHUFFLE(3, 2, 3, 2));
    __m128 v_temp2 = _mm_shuffle_ps(m.R[2], m.R[3], _MM_SHUFFLE(1, 0, 1, 0));
    __m128 v_temp4 = _mm_shuffle_ps(m.R[2], m.R[3], _MM_SHUFFLE(3, 2, 3, 2));

    return matrix{ {
        _mm_shuffle_ps(v_temp1, v_temp2, _MM_SHUFFLE(2, 0, 2, 0)),
        _mm_shuffle_ps(v_temp1, v_temp2, _MM_SHUFFLE(3, 1, 3, 1)),
        _mm_shuffle_ps(v_temp3, v_temp4, _MM_SHUFFLE(2, 0, 2, 0)),
        _mm_shuffle_ps(v_temp3, v_temp4, _MM_SHUFFLE(3, 1, 3, 1)),
    } };
}

vec4 mathcall dot(vec4 v1, vec4 v2) noexcept { return { _mm_dp_ps(v1.V, v2.V, 0b1111'1111) }; }

template <size_t C> vec4 mathcall rotate_left(vec4 v) noexcept {
    static_assert(C < 4);
    return swizzle<
        (C + 0) & 0b11,
        (C + 1) & 0b11,
        (C + 2) & 0b11,
        (C + 3) & 0b11>(v);
}

vec4 mathcall determinant(matrix m) noexcept
{
    static constexpr const_vec4_f32 sign = { { { 1.0F, -1.0F, 1.0F, -1.0F } } };

    auto v_v0 = swizzle<1,0,0,0>(base_z(m));
    auto v_v1 = swizzle<2,2,1,1>(base_w(m));
    auto v_v2 = swizzle<1,0,0,0>(base_z(m));
    auto v_v3 = swizzle<3,3,3,2>(base_w(m));
    auto v_v4 = swizzle<2,2,1,1>(base_z(m));
    auto v_v5 = swizzle<3,3,3,2>(base_w(m));

    auto v_p0 = mul(v_v0, v_v1);
    auto v_p1 = mul(v_v2, v_v3);
    auto v_p2 = mul(v_v4, v_v5);

    v_v0 = swizzle<2,2,1,1>(base_z(m));
    v_v1 = swizzle<1,0,0,0>(base_w(m));
    v_v2 = swizzle<3,3,3,2>(base_z(m));
    v_v3 = swizzle<1,0,0,0>(base_w(m));
    v_v4 = swizzle<3,3,3,2>(base_z(m));
    v_v5 = swizzle<2,2,1,1>(base_w(m));

    v_p0 = negmulsub(v_v0, v_v1, v_p0);
    v_p1 = negmulsub(v_v2, v_v3, v_p1);
    v_p2 = negmulsub(v_v4, v_v5, v_p2);

    v_v0 = swizzle<3,3,3,2>({ m.R[1] });
    v_v1 = swizzle<2,2,1,1>({ m.R[1] });
    v_v2 = swizzle<1,0,0,0>({ m.R[1] });

    auto v_s = mul(base_x(m), { sign.V });
    auto v_r = mul(v_v0, v_p0);
    v_r = negmulsub(v_v1, v_p1, v_r);
    v_r = muladd(v_v2, v_p2, v_r);

    return dot(v_s, v_r);
}

float mathcall other_test() {
    return get_x(identity<quat>());
}

vec4 mathcall othertest(vec4 v) {
    return mul(v, zero<vec4>());
}


// permute
namespace impl {
    template <uint32_t Shuffle, bool X, bool Y, bool Z, bool W> struct permute_helper final
    {
        static vec4 mathcall permute(vec4 v1, vec4 v2) noexcept
        {
            static constexpr const const_vec4_u32 mask = {{{
                X ? 0xFFFFFFFFU : 0U,
                Y ? 0xFFFFFFFFU : 0U,
                Z ? 0xFFFFFFFFU : 0U,
                W ? 0xFFFFFFFFU : 0U,
            }}};

            __m128 const vshuffled1 = _mm_permute_ps(v1.V, Shuffle);
            __m128 const vshuffled2 = _mm_permute_ps(v2.V, Shuffle);
            __m128 const vmasked1 = _mm_andnot_ps(mask.V, vshuffled1);
            __m128 const vmasked2 = _mm_and_ps(mask.V, vshuffled2);
            __m128 const vresult = _mm_or_ps(vmasked1, vmasked2);
            return { vresult };
        }
    };

    template <uint32_t Shuffle> struct permute_helper<Shuffle, false, false, false, false>
    {
        static vec4 mathcall permute(vec4 v1, [[maybe_unused]] vec4 v2) noexcept
        {
            return { _mm_permute_ps(v1.V, Shuffle) };
        }
    };

    template <uint32_t Shuffle> struct permute_helper<Shuffle, true, true, true, true>
    {
        static vec4 mathcall permute([[maybe_unused]] vec4 v1, vec4 v2) noexcept
        {
            return { _mm_permute_ps(v2.V, Shuffle) };
        }
    };

    template <uint32_t Shuffle> struct permute_helper<Shuffle, false, false, true, true>
    {
        static vec4 mathcall permute(vec4 v1, vec4 v2) noexcept
        {
            return { _mm_shuffle_ps(v1.V, v2.V, Shuffle) };
        }
    };

    template <uint32_t Shuffle> struct permute_helper<Shuffle, true, true, false, false>
    {
        static vec4 mathcall permute(vec4 v1, vec4 v2) noexcept
        {
            return { _mm_shuffle_ps(v2.V, v1.V, Shuffle) };
        }
    };
}

template <uint32_t X, uint32_t Y, uint32_t Z, uint32_t W>
vec4 mathcall permute(vec4 v1, vec4 v2) noexcept
{
    static_assert(X <= 7, "X template parameter out of range");
    static_assert(Y <= 7, "Y template parameter out of range");
    static_assert(Z <= 7, "Z template parameter out of range");
    static_assert(W <= 7, "W template parameter out of range");

    constexpr uint32_t shuffle = _MM_SHUFFLE(W & 3, Z & 3, Y & 3, X & 3);
    constexpr bool x = X > 3;
    constexpr bool y = Y > 3;
    constexpr bool z = Z > 3;
    constexpr bool w = W > 3;
    return impl::permute_helper<shuffle, x, y, z, w>::permute(v1, v2);
}

template<> vec4 mathcall permute<0,1,2,3>(vec4 v1, [[maybe_unused]] vec4 v2) noexcept { return v1; }
template<> vec4 mathcall permute<4,5,6,7>([[maybe_unused]] vec4 v1, vec4 v2) noexcept { return v2; }
template<> vec4 mathcall permute<0,1,4,5>(vec4 v1, vec4 v2) noexcept { return { _mm_movelh_ps(v1.V, v2.V) }; }
template<> vec4 mathcall permute<6,7,2,3>(vec4 v1, vec4 v2) noexcept { return { _mm_movehl_ps(v1.V, v2.V) }; }
template<> vec4 mathcall permute<0, 4, 1, 5>(vec4 v1, vec4 v2) noexcept { return { _mm_unpacklo_ps(v1.V, v2.V) }; }
template <> vec4 mathcall permute<2, 6, 3, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_unpackhi_ps(v1.V, v2.V) }; }
template <> vec4 mathcall permute<2, 3, 6, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(v1.V), _mm_castps_pd(v2.V))) }; }
template <> vec4 mathcall permute<4, 1, 2, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x1) }; }
template <> vec4 mathcall permute<0, 5, 2, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x2) }; }
template <> vec4 mathcall permute<4, 5, 2, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x3) }; }
template <> vec4 mathcall permute<0, 1, 6, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x4) }; }
template <> vec4 mathcall permute<4, 1, 6, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x5) }; }
template <> vec4 mathcall permute<0, 5, 6, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x6) }; }
template <> vec4 mathcall permute<4, 5, 6, 3>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x7) }; }
template <> vec4 mathcall permute<0, 1, 2, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x8) }; }
template <> vec4 mathcall permute<4, 1, 2, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0x9) }; }
template <> vec4 mathcall permute<0, 5, 2, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0xA) }; }
template <> vec4 mathcall permute<4, 5, 2, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0xB) }; }
template <> vec4 mathcall permute<0, 1, 6, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0xC) }; }
template <> vec4 mathcall permute<4, 1, 6, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0xD) }; }
template <> vec4 mathcall permute<0, 5, 6, 7>(vec4 v1, vec4 v2) noexcept { return { _mm_blend_ps(v1.V, v2.V, 0xE) }; }

vec4 mathcall permute(vec4 v1, vec4 v2, uint32_t permute_x, uint32_t permute_y, uint32_t permute_z, uint32_t permute_w) noexcept
{
    //GX_ASSERT((permute_x <= 7) && (permute_y <= 7) && (permute_z <= 7) && (permute_w <= 7));
    //GX_COMPILER_ASSUME((permute_x <= 7) && (permute_y <= 7) && (permute_z <= 7) && (permute_w <= 7));

    static constexpr const const_vec4_u32 v_threes = { { { 3, 3, 3, 3 } } };

    alignas(16) const uint32_t elements[4] = { permute_x, permute_y, permute_z, permute_w };
    auto v_control = _mm_load_si128(reinterpret_cast<const __m128i*>(&elements[0]));

    auto v_select = _mm_cmpgt_epi32(v_control, _mm_castps_si128(v_threes.V));
    v_control = _mm_castps_si128(_mm_and_ps(_mm_castsi128_ps(v_control), v_threes.V));

    auto v_shuffled1 = _mm_permutevar_ps(v1.V, v_control);
    auto v_shuffled2 = _mm_permutevar_ps(v2.V, v_control);

    auto v_masked1 = _mm_andnot_ps(_mm_castsi128_ps(v_select), v_shuffled1);
    auto v_masked2 = _mm_and_ps(_mm_castsi128_ps(v_select), v_shuffled2);

    return { _mm_or_ps(v_masked1, v_masked2) };
}

#endif
