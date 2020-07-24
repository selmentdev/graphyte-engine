#pragma once

// =================================================================================================
//
// This module implements NEON specific helper functions
//

namespace Graphyte::Maths::Impl
{
    mathinline float32x4_t mathcall neon_permute(
        float32x4_t a,
        float32x4_t b,
        size_t x,
        size_t y,
        size_t z,
        size_t w) noexcept
    {
        static uint32_t const indices[8]{
            0x03020100u, // XA
            0x07060504u, // YA
            0x0B0A0908u, // ZA
            0x0F0E0D0Cu, // WA
            0x13121110u, // XB
            0x17161514u, // YB
            0x1B1A1918u, // ZB
            0x1F1E1D1Cu, // WB
        };

        uint8x8x4_t lookup;
        lookup.val[0] = vreinterpretq_u8_f32(vget_low_f32(a));
        lookup.val[1] = vreinterpretq_u8_f32(vget_high_f32(a));
        lookup.val[2] = vreinterpretq_u8_f32(vget_low_f32(b));
        lookup.val[3] = vreinterpretq_u8_f32(vget_high_f32(b));

        uint32x2_t const index_lo = vcreate_u32(
            static_cast<uint64_t>(indices[x]) | (static_cast<uint64_t>(indices[y]) << 32));

        uint32x2_t const index_hi = vcreate_u32(
            static_cast<uint64_t>(indices[z]) | (static_cast<uint64_t>(indices[w]) << 32));

        uint8x8_t const result_lo = vtbl4_u8(lookup, vreinterpret_u8_u32(index_lo));
        uint8x8_t const result_hi = vtbl4_u8(lookup, vreinterpret_u8_u32(index_hi));

        float32x4_t const result = vcombine_f32(
            vreinterpret_f32_u8(result_lo),
            vreinterpret_f32_u8(result_hi));

        return result;
    }

    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline float32x4_t mathcall neon_permute(float32x4_t a, float32x4_t b) noexcept
    {
        static_assert((X < 8) and (Y < 8) and (Z < 8) and (W < 8));

        if constexpr (X == 0 and Y == 1 and Z == 2 and W == 3)
        {
            return a;
        }
        else if constexpr (X == 4 and Y == 5 and Z == 6 and W == 7)
        {
            return b;
        }
        else if constexpr (X == 0 and Y == 1 and Z == 4 and W == 5)
        {
            return vcombine_f32(vget_low_f32(a), vget_low_f32(b));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 4 and W == 5)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(a)), vget_low_f32(b));
        }
        else if constexpr (X == 0 and Y == 1 and Z == 5 and W == 4)
        {
            return vcombine_f32(vget_low_f32(a), vrev64_f32(vget_low_f32(b)));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 5 and W == 4)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(a)), vrev64_f32(vget_low_f32(b)));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 6 and W == 7)
        {
            return vcombine_f32(vget_high_f32(a), vget_high_f32(b));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 6 and W == 7)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(a)), vget_high_f32(b));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 7 and W == 6)
        {
            return vcombine_f32(vget_high_f32(a), vrev64_f32(vget_high_f32(b)));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 7 and W == 6)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(a)), vrev64_f32(vget_high_f32(b)));
        }
        else if constexpr (X == 0 and Y == 1 and Z == 6 and W == 7)
        {
            return vcombine_f32(vget_low_f32(a), vget_high_f32(b));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 6 and W == 7)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(a)), vget_high_f32(b));
        }
        else if constexpr (X == 0 and Y == 1 and Z == 7 and W == 6)
        {
            return vcombine_f32(vget_low_f32(a), vrev64_f32(vget_high_f32(b)));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 7 and W == 6)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(a)), vrev64_f32(vget_high_f32(b)));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 4 and W == 5)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(a)), vget_low_f32(b));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 5 and W == 4)
        {
            return vcombine_f32(vget_high_f32(a), vrev64_f32(vget_low_f32(b)));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 5 and W == 4)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(a)), vrev64_f32(vget_low_f32(b)));
        }
        else if constexpr (X == 0 and Y == 4 and Z == 2 and W == 6)
        {
            return vtrnq_f32(a, b).val[0];
        }
        else if constexpr (X == 1 and Y == 5 and Z == 3 and W == 7)
        {
            return vtrnq_f32(a, b).val[1];
        }
        else if constexpr (X == 0 and Y == 4 and Z == 1 and W == 5)
        {
            return vzipq_f32(a, b).val[0];
        }
        else if constexpr (X == 2 and Y == 6 and Z == 3 and W == 7)
        {
            return vzipq_f32(a, b).val[1];
        }
        else if constexpr (X == 0 and Y == 2 and Z == 4 and W == 6)
        {
            return vuzpq_f32(a, b).val[0];
        }
        else if constexpr (X == 1 and Y == 3 and Z == 5 and W == 7)
        {
            return vuzpq_f32(a, b).val[1];
        }
        else if constexpr (X == 1 and Y == 2 and Z == 3 and W == 4)
        {
            return vextq_f32(a, b, 1);
        }
        else if constexpr (X == 2 and Y == 3 and Z == 4 and W == 5)
        {
            return vextq_f32(a, b, 2);
        }
        else if constexpr (X == 3 and Y == 4 and Z == 5 and W == 6)
        {
            return vextq_f32(a, b, 3);
        }
        else
        {
            return neon_permute(a, b, X, Y, Z, W);
        }
    }

    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline float32x4_t mathcall neon_shuffle(float32x4_t a, float32x4_t b) noexcept
    {
        static_assert((X < 4) and (Y < 4) and (Z < 4) and (W < 4));

        if constexpr (X == 0 and Y == 0 and Z == 0 and W == 0)
        {
            return vcombine_f32(vdup_lane_f32(vget_low_f32(a), 0), vdup_lane_f32(vget_low_f32(b), 0));
        }
        else if constexpr (X == 1 and Y == 1 and Z == 1 and W == 1)
        {
            return vcombine_f32(vdup_lane_f32(vget_low_f32(a), 1), vdup_lane_f32(vget_low_f32(b), 1));
        }
        else if constexpr (X == 2 and Y == 2 and Z == 2 and W == 2)
        {
            return vcombine_f32(vdup_lane_f32(vget_high_f32(a), 0), vdup_lane_f32(vget_high_f32(b), 0));
        }
        else if constexpr (X == 3 and Y == 3 and Z == 3 and W == 3)
        {
            return vcombine_f32(vdup_lane_f32(vget_high_f32(a), 1), vdup_lane_f32(vget_high_f32(b), 1));
        }
        else if constexpr (X == 0 and Y == 0 and Z == 1 and W == 1)
        {
            return vzipq_f32(a, b).val[0];
        }
        else if constexpr (X == 2 and Y == 2 and Z == 3 and W == 3)
        {
            return vzipq_f32(a, b).val[1];
        }
        else if constexpr (X == 0 and Y == 0 and Z == 2 and W == 2)
        {
            return vtrnq_f32(a, b).val[0];
        }
        else if constexpr (X == 1 and Y == 1 and Z == 3 and W == 3)
        {
            return vtrnq_f32(a, b).val[1];
        }
        else if constexpr (X == 0 and Y == 2 and Z == 0 and W == 2)
        {
            return vuzpq_f32(a, b).val[0];
        }
        else if constexpr (X == 1 and Y == 3 and Z == 1 and W == 3)
        {
            return vuzpq_f32(a, b).val[1];
        }
        else if constexpr (X == 0 and Y == 1 and Z == 0 and W == 1)
        {
            return vcombine_f32(vget_low_f32(a), vget_low_f32(b));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 2 and W == 3)
        {
            return vcombine_f32(vget_high_f32(a), vget_high_f32(b));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 2 and W == 3)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(a)), vget_high_f32(b));
        }
        else if constexpr (X == 0 and Y == 1 and Z == 2 and W == 3)
        {
            return vcombine_f32(vget_low_f32(a), vget_high_f32(b));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 3 and W == 2)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(a)), vrev64_f32(vget_high_f32(b)));
        }
        else if constexpr (X == 0 and Y == 1 and Z == 3 and W == 2)
        {
            return vcombine_f32(vget_low_f32(a), vrev64_f32(vget_high_f32(b)));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 1 and W == 0)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(a)), vrev64_f32(vget_low_f32(b)));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 0 and W == 1)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(a)), vget_low_f32(b));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 1 and W == 0)
        {
            return vcombine_f32(vget_high_f32(a), vrev64_f32(vget_low_f32(b)));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 0 and W == 1)
        {
            return vcombine_f32(vget_high_f32(a), vget_low_f32(b));
        }
        else
        {
            float32x4_t const r_Xnnn = vmovq_n_f32(vgetq_lane_f32(a, X));
            float32x4_t const r_XYnn = vsetq_lane_f32(vgetq_lane_f32(a, Y), r_Xnnn, 1);
            float32x4_t const r_XYZn = vsetq_lane_f32(vgetq_lane_f32(b, Z), r_XYnn, 2);
            float32x4_t const r_XYZW = vsetq_lane_f32(vgetq_lane_f32(b, W), r_XYZn, 3);
            return r_XYZW;
        }
    }

    mathinline float32x4_t mathcall neon_swizzle(
        float32x4_t v,
        size_t x,
        size_t y,
        size_t z,
        size_t w) noexcept
    {
        static uint32_t const indices[4]{
            0x03020100, // X
            0x07060504, // Y
            0x0B0A0908, // Z
            0x0F0E0D0C, // W
        };

        uint8x8x2_t lookup;
        lookup.val[0] = vreinterpret_u8_f32(vget_low_f32(v));
        lookup.val[1] = vreinterpret_u8_f32(vget_high_f32(v));

        uint32x2_t const index_lo = vcreate_u32(static_cast<uint64_t>(indices[x]) | (static_cast<uint64_t>(indices[y]) << 32));
        uint32x2_t const index_hi = vcreate_u32(static_cast<uint64_t>(indices[z]) | (static_cast<uint64_t>(indices[w]) << 32));

        uint8x8_t const result_lo = vtbl2_u8(lookup, vreinterpret_u8_u32(index_lo));
        uint8x8_t const result_hi = vtbl2_u8(lookup, vreinterpret_u8_u32(index_hi));

        float32x4_t const result = vcombine_f32(vreinterpret_f32_u8(result_lo), vreinterpret_f32_u8(result_hi));
        return result;
    }

    template <size_t X, size_t Y, size_t Z, size_t W>
    mathinline float32x4_t mathcall neon_swizzle(float32x4_t v) noexcept
    {
        static_assert((X < 4) and (Y < 4) and (Z < 4) and (W < 4));

        if constexpr (X == 0 and Y == 1 and Z == 2 and W == 3)
        {
            return v;
        }
        else if constexpr (X == 0 and Y == 0 and Z == 0 and W == 0)
        {
            return vdupq_lane_f32(vget_low_f32(v), 0);
        }
        else if constexpr (X == 1 and Y == 1 and Z == 1 and W == 1)
        {
            return vdupq_lane_f32(vget_low_f32(v), 1);
        }
        else if constexpr (X == 2 and Y == 2 and Z == 2 and W == 2)
        {
            return vdupq_lane_f32(vget_high_f32(v), 0);
        }
        else if constexpr (X == 3 and Y == 3 and Z == 3 and W == 3)
        {
            return vdupq_lane_f32(vget_high_f32(v), 1);
        }
        else if constexpr (X == 1 and Y == 0 and Z == 3 and W == 2)
        {
            return vrev64q_f32(v);
        }
        else if constexpr (X == 0 and Y == 1 and Z == 0 and W == 1)
        {
            float32x2_t vt = vget_low_f32(v);
            return vcombine_f32(vt, vt);
        }
        else if constexpr (X == 2 and Y == 3 and Z == 2 and W == 3)
        {
            float32x2_t vt = vget_high_f32(v);
            return vcombine_f32(vt, vt);
        }
        else if constexpr (X == 1 and Y == 0 and Z == 1 and W == 0)
        {
            float32x2_t vt = vrev64_f32(vget_low_f32(v));
            return vcombine_f32(vt, vt);
        }
        else if constexpr (X == 3 and Y == 2 and Z == 3 and W == 2)
        {
            float32x2_t vt = vrev64_f32(vget_high_f32(v));
            return vcombine_f32(vt, vt);
        }
        else if constexpr (X == 0 and Y == 1 and Z == 3 and W == 2)
        {
            return vcombine_f32(vget_low_f32(v), vrev64_f32(vget_high_f32(v)));
        }
        else if constexpr (X == 1 and Y == 0 and Z == 2 and W == 3)
        {
            return vcombine_f32(vrev64_f32(vget_low_f32(v)), vget_high_f32(v));
        }
        else if constexpr (X == 2 and Y == 3 and Z == 1 and W == 0)
        {
            return vcombine_f32(vget_high_f32(v), vrev64_f32(vget_low_f32(v)));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 0 and W == 1)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(v)), vget_low_f32(v));
        }
        else if constexpr (X == 3 and Y == 2 and Z == 1 and W == 0)
        {
            return vcombine_f32(vrev64_f32(vget_high_f32(v)), vrev64_f32(vget_low_f32(v)));
        }
        else if constexpr (X == 0 and Y == 0 and Z == 2 and W == 2)
        {
            return vtrnq_f32(v, v).val[0];
        }
        else if constexpr (X == 1 and Y == 1 and Z == 3 and W == 3)
        {
            return vtrnq_f32(v, v).val[1];
        }
        else if constexpr (X == 0 and Y == 0 and Z == 1 and W == 1)
        {
            return vzipq_f32(v, v).val[0];
        }
        else if constexpr (X == 2 and Y == 2 and Z == 3 and W == 3)
        {
            return vzipq_f32(v, v).val[1];
        }
        else if constexpr (X == 0 and Y == 2 and Z == 0 and W == 2)
        {
            return vuzpq_f32(v, v).val[0];
        }
        else if constexpr (X == 1 and Y == 3 and Z == 1 and W == 3)
        {
            return vuzpq_f32(v, v).val[1];
        }
        else if constexpr (X == 1 and Y == 2 and Z == 3 and W == 0)
        {
            return vextq_f32(v, v, 1);
        }
        else if constexpr (X == 2 and Y == 3 and Z == 0 and W == 1)
        {
            return vextq_f32(v, v, 2);
        }
        else if constexpr (X == 3 and Y == 0 and Z == 1 and W == 2)
        {
            return vextq_f32(v, v, 3);
        }
        else
        {
            return neon_swizzle(v, X, Y, Z, W);
        }
    }
}

namespace Graphyte::Maths::Impl
{
    // (a * b) + c
    mathinline float32x4_t mathcall neon_fmadd_f32x4(
        float32x4_t a,
        float32x4_t b,
        float32x4_t c) noexcept
    {
        return vfmaq_f32(c, a, b);
    }

    // (a * b) - c
    mathinline float32x4_t mathcall neon_fmsub_f32x4(
        float32x4_t a,
        float32x4_t b,
        float32x4_t c) noexcept
    {
        float32x4_t const ab = vmulq_f32(a, b);
        return vsubq_f32(ab, c);
    }

    // -(a * b) + c
    mathinline float32x4_t mathcall neon_fnmadd_f32x4(
        float32x4_t a,
        float32x4_t b,
        float32x4_t c) noexcept
    {
        return vfmsq_f32(c, a, b);
    }

    // -(a * b) - c
    mathinline float32x4_t mathcall neon_fnmsub_f32x4(
        float32x4_t a,
        float32x4_t b,
        float32x4_t c) noexcept
    {
        float32x4_t const ab = vmulq_f32(a, b);
        return vsubq_f32(vnegq_f32(ab), c);
    }
}

namespace Graphyte::Maths::Impl
{
    template <size_t Components>
    float32x4_t neon_dp(float32x4_t a, float32x4_t b) = delete;

    template <size_t Components>
    float32x4_t neon_dp(float32x4_t v) = delete;

    template <>
    mathinline float32x4_t mathcall neon_dp<4>(float32x4_t a, float32x4_t b) noexcept
    {
        // {r0}[x, y, z, w] = {a,b}[x1*x2, y1*y2, z1*z2, w1*w2]
        float32x4_t const r0 = vmulq_f32(a, b);

        // {r1}[x, y] = {r0}[x, y]
        float32x2_t const r1 = vget_low_f32(r0);

        // {r2}[x, y] = {r0}[z, w]
        float32x2_t const r2 = vget_high_f32(r0);

        // {r3}[x, y] = {r1,r2}[x1+x2, y1+y2] == (a.xy * b.xy) + (a.zw * b.zw) = [x1*x2 + z1*z2, y1*y2 + w1*w2]
        float32x2_t const r3 = vadd_f32(r1, r2);

        // {r4}[x, y] = {r3,r3}[x+y, x+y] = (x1*x2 + y1*y2 + z1*z2 + w1*w2)
        float32x2_t const r4 = vpadd_f32(r3, r3);

        float32x4_t const result = vcombine_f32(r4, r4);
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<4>(float32x4_t v) noexcept
    {
        return neon_dp<4>(v, v);
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<3>(float32x4_t a, float32x4_t b) noexcept
    {
        // {r0}[x, y, z, w] = {a,b}[x1*x2, y1*y2, z1*z2, w1*w2]
        float32x4_t const r0 = vmulq_f32(a, b);

        // {r0_xy}[x, y] = {r0}[x, y]
        float32x2_t const r0_xy = vget_low_f32(r0);
        // {r0_zw}[x, y] = {r0}[z, w]
        float32x2_t const r0_zw = vget_high_f32(r0);

        // {r1_xy}[x, y] = {r0_xy}[x+y, x+y]
        float32x2_t const r1_xy = vpadd_f32(r0_xy, r0_xy);

        // {r1_zz}[x, y] = {r0_zw}[z, z]
        float32x2_t const r1_zz = vdup_lane_f32(r0_zw, 0);

        // {r_xyz}[x, y] = {r1_xy, r1_zz}[x1+x2, y1+y2] = [x+y+z, x+y+z]
        float32x2_t const r_xyz = vadd_f32(r1_xy, r1_zz);

        float32x4_t const result = vcombine_f32(r_xyz, r_xyz);
        return result;
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<3>(float32x4_t v) noexcept
    {
        return neon_dp<3>(v, v);
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<2>(float32x4_t a, float32x4_t b) noexcept
    {
        // {r0}[x, y] = {a}[x, y]
        float32x2_t const r0 = vget_low_f32(a);

        // {r1}[x, y] = {a}[x, y]
        float32x2_t const r1 = vget_low_f32(b);

        // {r2}[x, y] = {r0,r1}[x1*x2, y1*y2]
        float32x2_t const r2 = vmul_f32(r0, r1);

        // {r3}[x, y] = {r2,r2}[x1+x2, y1+y2] = [x1*x2 + y1*y2, ...]
        float32x2_t const r3 = vpadd_f32(r2, r2);

        // {result}[x, y, z, w] = {r3,r3}[x1, y1, x2, y2]
        float32x4_t const result = vcombine_f32(r3, r3);
        return result;
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<2>(float32x4_t v) noexcept
    {
        // {r0}[x, y] = {v}[x, y]
        float32x2_t const r0 = vget_low_f32(v);

        // {r1}[x, y] = {r0, r0}[x*x, y*y]
        float32x2_t const r1 = vmul_f32(r0, r0);

        // {r2}[x, y] = {r1, r1}{x*x + y*y, ...]
        float32x2_t const r2 = vpadd_f32(r1, r1);

        // {result}[x, y, z, w] = {r2, r2}{x1, y1, x1, y1]
        float32x4_t const result = vcombine_f32(r2, r2);

        return result;
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<1>(float32x4_t a, float32x4_t b) noexcept
    {
        float32x4_t const axxxx = vdupq_lane_f32(a, 0);
        float32x4_t const bxxxx = vdupq_lane_f32(b, 0);
        float32x4_t const result = vmulq_f32(axxxx, bxxxx);
        return result;
    }

    template <>
    mathinline float32x4_t mathcall neon_dp<1>(float32x4_t v) noexcept
    {
        float32x4_t const vxxxx = vdupq_lane_f32(v, 0);
        float32x4_t const result = vmulq_f32(vxxxx, vxxxx);
        return result;
    }
}
