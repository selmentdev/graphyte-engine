#include "Base.pch.hxx"
#include <Graphyte/Maths/Noise/SimplexNoise.hxx>
#include <Graphyte/Maths/Scalar.hxx>
#include <Graphyte/Maths/Interpolation.hxx>
#include <Graphyte/Maths/Noise/CommonNoise.hxx>

namespace Graphyte::Maths
{
    namespace Common
    {
        static const uint8_t GSimplex[64][4] = {
            { 0, 1, 2, 3 }, { 0, 1, 3, 2 }, { 0, 0, 0, 0 }, { 0, 2, 3, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 2, 3, 0 },
            { 0, 2, 1, 3 }, { 0, 0, 0, 0 }, { 0, 3, 1, 2 }, { 0, 3, 2, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 3, 2, 0 },
            { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
            { 1, 2, 0, 3 }, { 0, 0, 0, 0 }, { 1, 3, 0, 2 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 2, 3, 0, 1 }, { 2, 3, 1, 0 },
            { 1, 0, 2, 3 }, { 1, 0, 3, 2 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 2, 0, 3, 1 }, { 0, 0, 0, 0 }, { 2, 1, 3, 0 },
            { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 },
            { 2, 0, 1, 3 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 3, 0, 1, 2 }, { 3, 0, 2, 1 }, { 0, 0, 0, 0 }, { 3, 1, 2, 0 },
            { 2, 1, 0, 3 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 3, 1, 0, 2 }, { 0, 0, 0, 0 }, { 3, 2, 0, 1 }, { 3, 2, 1, 0 },
        };

        static constexpr inline float Gradient(uint32_t hash, float x) noexcept
        {
            uint32_t h = hash & 0xF;
            auto gradient = 1.0F + static_cast<float>(h & 0x7);
            if (h & 0x8)
            {
                gradient = -gradient;
            }

            return gradient * x;
        }

        static constexpr inline float Gradient(uint32_t hash, float x, float y) noexcept
        {
            uint32_t h = hash & 0x7;
            auto u = h < 4 ? x : y;
            auto v = h < 4 ? y : x;

            return ((h & 0x1) ? -u : u) + ((h & 0x2) ? -2.0F * v : 2.0F * v);
        }

        static constexpr inline float Gradient(uint32_t hash, float x, float y, float z) noexcept
        {
            uint32_t h = hash & 0xF;
            auto u = h < 8 ? x : y;
            auto v = h < 4 ? y : ((h == 12 || h == 14) ? x : z);

            return ((h & 0x1) ? -u : u) + ((h & 0x2) ? -v : v);
        }

        static constexpr inline float Gradient(uint32_t hash, float x, float y, float z, float w) noexcept
        {
            uint32_t h = hash & 0x1F;
            auto u = h < 24 ? x : y;
            auto v = h < 16 ? y : z;
            auto t = h < 8 ? z : w;

            return ((h & 0x1) ? -u : u) + ((h & 0x2) ? -v : v) + ((h & 0x4) ? -t : t);
        }
    }

    float SimplexNoise::Normal(float x) noexcept
    {
        auto i0 = FastFloor(x);
        auto i1 = i0 + 1;

        auto x0 = x - static_cast<float>(i0);
        auto x1 = x0 - 1.0F;

        auto t0 = 1.0F - x0 * x0;
        t0 *= t0;

        auto n0 = t0 * t0 * Common::Gradient(CommonNoise::GPermutations[i0 & 0xFF], x0);

        auto t1 = 1.0F - x1 * x1;
        t1 *= t1;

        auto n1 = t1 * t1 * Common::Gradient(CommonNoise::GPermutations[i1 & 0xFF], x1);

        return 0.25F * (n0 + n1);
    }

    float SimplexNoise::Normal(float x, float y) noexcept
    {
        static constexpr const auto F2 = 0.366025403F; // F2 = 0.5*(sqrt(3.0)-1.0)
        static constexpr const auto G2 = 0.211324865F; // G2 = (3.0-Math.sqrt(3.0))/6.0

        auto s = (x + y) * F2;
        auto xs = x + s;
        auto ys = y + s;
        auto i = FastFloor(xs);
        auto j = FastFloor(ys);

        auto t = static_cast<float>(i + j) * G2;

        auto x0 = static_cast<float>(i) - t;
        auto y0 = static_cast<float>(j) - t;
        x0 = x - x0;
        y0 = y - y0;

        int i1;
        int j1;

        if (x0 > y0)
        {
            i1 = 1;
            j1 = 0;
        }
        else
        {
            i1 = 0;
            j1 = 1;
        }

        auto x1 = x0 - static_cast<float>(i1) + G2;
        auto y1 = y0 - static_cast<float>(j1) + G2;
        auto x2 = x0 - 1.0F + 2.0F * G2;
        auto y2 = y0 - 1.0F + 2.0F * G2;

        auto ii = i & 0xFF;
        auto jj = j & 0xFF;

        auto t0 = 0.5F - x0 * x0 - y0 * y0;
        float n0;

        if (t0 < 0.0F)
        {
            n0 = 0.0F;
        }
        else
        {
            t0 *= t0;
            n0 = t0 * t0 * Common::Gradient(CommonNoise::GPermutations[ii + CommonNoise::GPermutations[jj]], x0, y0);
        }

        auto t1 = 0.5F - x1 * x1 - y1 * y1;
        float n1;

        if (t1 < 0.0F)
        {
            n1 = 0.0F;
        }
        else
        {
            t1 *= t1;
            n1 = t1 * t1 * Common::Gradient(CommonNoise::GPermutations[ii + i1 + CommonNoise::GPermutations[jj + j1]], x1, y1);
        }

        auto t2 = 0.5F - x2 * x2 - y2 * y2;
        float n2;

        if (t2 < 0.0F)
        {
            n2 = 0.0F;
        }
        else
        {
            t2 *= t2;
            n2 = t2 * t2 * Common::Gradient(CommonNoise::GPermutations[ii + 1 + CommonNoise::GPermutations[jj + 1]], x2, y2);
        }

        return 40.0F * (n0 + n1 + n2);
    }

    float SimplexNoise::Normal(float x, float y, float z) noexcept
    {
        static constexpr const auto F3 = 0.333333333F;
        static constexpr const auto G3 = 0.166666667F;

        auto s = (x + y + z) * F3;
        auto xs = x + s;
        auto ys = y + s;
        auto zs = z + s;

        auto i = FastFloor(xs);
        auto j = FastFloor(ys);
        auto k = FastFloor(zs);

        auto t = static_cast<float>(i + j + k) * G3;
        auto x0 = static_cast<float>(i) - t;
        auto y0 = static_cast<float>(j) - t;
        auto z0 = static_cast<float>(k) - t;
        x0 = x - x0;
        y0 = y - y0;
        z0 = z - z0;

        int i1, j1, k1;
        int i2, j2, k2;

        if (x0 >= y0)
        {
            if (y0 >= z0)
            {
                i1 = 1;
                j1 = 0;
                k1 = 0;
                i2 = 1;
                j2 = 1;
                k2 = 0;
            }
            else if (x0 >= z0)
            {
                i1 = 1;
                j1 = 0;
                k1 = 0;
                i2 = 1;
                j2 = 0;
                k2 = 1;
            }
            else
            {
                i1 = 0;
                j1 = 0;
                k1 = 1;
                i2 = 1;
                j2 = 0;
                k2 = 1;
            }
        }
        else
        {
            if (y0 < z0)
            {
                i1 = 0;
                j1 = 0;
                k1 = 1;
                i2 = 0;
                j2 = 1;
                k2 = 1;
            }
            else if (x0 < z0)
            {
                i1 = 0;
                j1 = 1;
                k1 = 0;
                i2 = 0;
                j2 = 1;
                k2 = 1;
            }
            else
            {
                i1 = 0;
                j1 = 1;
                k1 = 0;
                i2 = 1;
                j2 = 1;
                k2 = 0;
            }
        }

        auto x1 = x0 - static_cast<float>(i1) + G3;
        auto y1 = y0 - static_cast<float>(j1) + G3;
        auto z1 = z0 - static_cast<float>(k1) + G3;
        auto x2 = x0 - static_cast<float>(i2) + 2.0F * G3;
        auto y2 = y0 - static_cast<float>(j2) + 2.0F * G3;
        auto z2 = z0 - static_cast<float>(k2) + 2.0F * G3;
        auto x3 = x0 - 1.0F + 3.0F * G3;
        auto y3 = y0 - 1.0F + 3.0F * G3;
        auto z3 = z0 - 1.0F + 3.0F * G3;

        int ii = i & 0xFF;
        int jj = j & 0xFF;
        int kk = k & 0xFF;

        auto t0 = 0.6F - x0 * x0 - y0 * y0 - z0 * z0;
        float n0;

        if (t0 < 0.0F)
        {
            n0 = 0.0F;
        }
        else
        {
            t0 *= t0;
            n0 = t0 * t0 * Common::Gradient(CommonNoise::GPermutations[ii + CommonNoise::GPermutations[jj + CommonNoise::GPermutations[kk]]], x0, y0, z0);
        }

        auto t1 = 0.6F - x1 * x1 - y1 * y1 - z1 * z1;
        float n1;

        if (t1 < 0.0F)
        {
            n1 = 0.0F;
        }
        else
        {
            t1 *= t1;
            n1 = t1 * t1 *Common::Gradient(CommonNoise::GPermutations[ii + i1 + CommonNoise::GPermutations[jj + j1 + CommonNoise::GPermutations[kk + k1]]], x1, y1, z1);
        }

        auto t2 = 0.6F - x2 * x2 - y2 * y2 - z2 * z2;
        float n2;

        if (t2 < 0.0F)
        {
            n2 = 0.0F;
        }
        else
        {
            t2 *= t2;
            n2 = t2 * t2 * Common::Gradient(CommonNoise::GPermutations[ii + i2 + CommonNoise::GPermutations[jj + j2 + CommonNoise::GPermutations[kk + k2]]], x2, y2, z2);
        }

        auto t3 = 0.6F - x3 * x3 - y3 * y3 - z3 * z3;
        float n3;

        if (t3 < 0.0F)
        {
            n3 = 0.0F;
        }
        else
        {
            t3 *= t3;
            n3 = t3 * t3 * Common::Gradient(CommonNoise::GPermutations[ii + 1 + CommonNoise::GPermutations[jj + 1 + CommonNoise::GPermutations[kk + 1]]], x3, y3, z3);
        }

        return 32.0F * (n0 + n1 + n2 + n3);
    }

    float SimplexNoise::Normal(float x, float y, float z, float w) noexcept
    {
        static constexpr const auto F4 = 0.309016994F; // F4 = (Math.sqrt(5.0)-1.0)/4.0
        static constexpr const auto G4 = 0.138196601F; // G4 = (5.0-Math.sqrt(5.0))/20.0

        auto s = (x + y + z + w) * F4;
        auto xs = x + s;
        auto ys = y + s;
        auto zs = z + s;
        auto ws = w + s;

        auto i = FastFloor(xs);
        auto j = FastFloor(ys);
        auto k = FastFloor(zs);
        auto l = FastFloor(ws);

        auto t = static_cast<float>(i + j + k + l) * G4;
        auto x0 = static_cast<float>(i) - t;
        auto y0 = static_cast<float>(j) - t;
        auto z0 = static_cast<float>(k) - t;
        auto w0 = static_cast<float>(l) - t;

        x0 = x - x0;
        y0 = y - y0;
        z0 = z - z0;
        w0 = w - w0;

        int c1 = (x0 > y0) ? 32 : 0;
        int c2 = (x0 > z0) ? 16 : 0;
        int c3 = (y0 > z0) ? 8 : 0;
        int c4 = (x0 > w0) ? 4 : 0;
        int c5 = (y0 > w0) ? 2 : 0;
        int c6 = (z0 > w0) ? 1 : 0;
        int c = c1 + c2 + c3 + c4 + c5 + c6;

        int i1 = Common::GSimplex[c][0] >= 3 ? 1 : 0;
        int j1 = Common::GSimplex[c][1] >= 3 ? 1 : 0;
        int k1 = Common::GSimplex[c][2] >= 3 ? 1 : 0;
        int l1 = Common::GSimplex[c][3] >= 3 ? 1 : 0;

        int i2 = Common::GSimplex[c][0] >= 2 ? 1 : 0;
        int j2 = Common::GSimplex[c][1] >= 2 ? 1 : 0;
        int k2 = Common::GSimplex[c][2] >= 2 ? 1 : 0;
        int l2 = Common::GSimplex[c][3] >= 2 ? 1 : 0;

        int i3 = Common::GSimplex[c][0] >= 1 ? 1 : 0;
        int j3 = Common::GSimplex[c][1] >= 1 ? 1 : 0;
        int k3 = Common::GSimplex[c][2] >= 1 ? 1 : 0;
        int l3 = Common::GSimplex[c][3] >= 1 ? 1 : 0;

        auto x1 = x0 - static_cast<float>(i1) + G4;
        auto y1 = y0 - static_cast<float>(j1) + G4;
        auto z1 = z0 - static_cast<float>(k1) + G4;
        auto w1 = w0 - static_cast<float>(l1) + G4;

        auto x2 = x0 - static_cast<float>(i2) + 2.0F * G4;
        auto y2 = y0 - static_cast<float>(j2) + 2.0F * G4;
        auto z2 = z0 - static_cast<float>(k2) + 2.0F * G4;
        auto w2 = w0 - static_cast<float>(l2) + 2.0F * G4;

        auto x3 = x0 - static_cast<float>(i3) + 3.0F * G4;
        auto y3 = y0 - static_cast<float>(j3) + 3.0F * G4;
        auto z3 = z0 - static_cast<float>(k3) + 3.0F * G4;
        auto w3 = w0 - static_cast<float>(l3) + 3.0F * G4;

        auto x4 = x0 - 1.0F + 4.0F * G4;
        auto y4 = y0 - 1.0F + 4.0F * G4;
        auto z4 = z0 - 1.0F + 4.0F * G4;
        auto w4 = w0 - 1.0F + 4.0F * G4;

        auto ii = i & 0xFF;
        auto jj = j & 0xFF;
        auto kk = k & 0xFF;
        auto ll = l & 0xFF;

        auto t0 = 0.6F - x0 * x0 - y0 * y0 - z0 * z0 - w0 * w0;
        float n0;

        if (t0 < 0.0F)
        {
            n0 = 0.0F;
        }
        else
        {
            t0 *= t0;
            n0 = t0 * t0 * Common::Gradient(CommonNoise::GPermutations[ii + CommonNoise::GPermutations[jj + CommonNoise::GPermutations[kk + CommonNoise::GPermutations[ll]]]], x0, y0, z0, w0);
        }

        auto t1 = 0.6F - x1 * x1 - y1 * y1 - z1 * z1 - w1 * w1;
        float n1;

        if (t1 < 0.0F)
        {
            n1 = 0.0F;
        }
        else
        {
            t1 *= t1;
            n1 = t1 * t1 * Common::Gradient(CommonNoise::GPermutations[ii + i1 + CommonNoise::GPermutations[jj + j1 + CommonNoise::GPermutations[kk + k1 + CommonNoise::GPermutations[ll + l1]]]], x1, y1, z1, w1);
        }

        auto t2 = 0.6F - x2 * x2 - y2 * y2 - z2 * z2 - w2 * w2;
        float n2;

        if (t2 < 0.0F)
        {
            n2 = 0.0F;
        }
        else
        {
            t2 *= t2;
            n2 = t2 * t2 * Common::Gradient(CommonNoise::GPermutations[ii + i2 + CommonNoise::GPermutations[jj + j2 + CommonNoise::GPermutations[kk + k2 + CommonNoise::GPermutations[ll + l2]]]], x2, y2, z2, w2);
        }

        auto t3 = 0.6F - x3 * x3 - y3 * y3 - z3 * z3 - w3 * w3;
        float n3;

        if (t3 < 0.0F)
        {
            n3 = 0.0F;
        }
        else
        {
            t3 *= t3;
            n3 = t3 * t3 * Common::Gradient(CommonNoise::GPermutations[ii + i3 + CommonNoise::GPermutations[jj + j3 + CommonNoise::GPermutations[kk + k3 + CommonNoise::GPermutations[ll + l3]]]], x3, y3, z3, w3);
        }

        auto t4 = 0.6F - x4 * x4 - y4 * y4 - z4 * z4 - w4 * w4;
        float n4;

        if (t4 < 0.0F)
        {
            n4 = 0.0F;
        }
        else
        {
            t4 *= t4;
            n4 = t4 * t4 * Common::Gradient(CommonNoise::GPermutations[ii + 1 + CommonNoise::GPermutations[jj + 1 + CommonNoise::GPermutations[kk + 1 + CommonNoise::GPermutations[ll + 1]]]], x4, y4, z4, w4);
        }

        return 27.0F * (n0 + n1 + n2 + n3 + n4);
    }
}
