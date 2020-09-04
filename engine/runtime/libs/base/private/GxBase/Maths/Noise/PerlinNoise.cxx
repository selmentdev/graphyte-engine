#if false
#include <Graphyte/Maths/Noise/PerlinNoise.hxx>
#include <Graphyte/Maths/Scalar.hxx>
#include <Graphyte/Maths/Interpolation.hxx>
#include <Graphyte/Maths/Noise/CommonNoise.hxx>

namespace Graphyte::Maths
{
    namespace Detail
    {
        constexpr inline float Fade(float t) noexcept
        {
            return t * t * t * (t * (t * 6.0F - 15.0F) + 10.0F);
        }

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

    float PerlinNoise::Normal(float x) noexcept
    {
        auto ix0 = FastFloor(x);
        auto fx0 = x - static_cast<float>(ix0);
        auto fx1 = fx0 - 1.0F;
        auto ix1 = (ix0 + 1) & 0xFF;
        ix0 = ix0 & 0xFF;

        auto s = Detail::Fade(fx0);

        auto n0 = Detail::Gradient(CommonNoise::g_Permutations[ix0], fx0);
        auto n1 = Detail::Gradient(CommonNoise::g_Permutations[ix1], fx1);

        return 0.188F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Normal(float x, float y) noexcept
    {
        auto ix0 = FastFloor(x);
        auto iy0 = FastFloor(y);

        auto fx0 = x - static_cast<float>(ix0);
        auto fy0 = y - static_cast<float>(iy0);
        auto fx1 = fx0 - 1.0F;
        auto fy1 = fy0 - 1.0F;
        auto ix1 = (ix0 + 1) & 0xFF;
        auto iy1 = (iy0 + 1) & 0xFF;
        ix0 = ix0 & 0xFF;
        iy0 = iy0 & 0xFF;

        auto t = Detail::Fade(fy0);
        auto s = Detail::Fade(fx0);

        auto nx0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0]], fx0, fy0);
        auto nx1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1]], fx0, fy1);

        auto n0 = Interpolation::Lerp(nx0, nx1, t);

        nx0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0]], fx1, fy0);
        nx1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1]], fx1, fy1);

        auto n1 = Interpolation::Lerp(nx0, nx1, t);

        return 0.507F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Normal(float x, float y, float z) noexcept
    {
        auto ix0 = FastFloor(x);
        auto iy0 = FastFloor(y);
        auto iz0 = FastFloor(z);

        auto fx0 = x - static_cast<float>(ix0);
        auto fy0 = y - static_cast<float>(iy0);
        auto fz0 = z - static_cast<float>(iz0);

        auto fx1 = fx0 - 1.0F;
        auto fy1 = fy0 - 1.0F;
        auto fz1 = fz0 - 1.0F;

        auto ix1 = (ix0 + 1) & 0xFF;
        auto iy1 = (iy0 + 1) & 0xFF;
        auto iz1 = (iz0 + 1) & 0xFF;

        ix0 = ix0 & 0xFF;
        iy0 = iy0 & 0xFF;
        iz0 = iz0 & 0xFF;

        auto r = Detail::Fade(fz0);
        auto t = Detail::Fade(fy0);
        auto s = Detail::Fade(fx0);

        auto nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0]]], fx0, fy0, fz0);
        auto nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1]]], fx0, fy0, fz1);

        auto nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0]]], fx0, fy1, fz0);
        nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1]]], fx0, fy1, fz1);

        auto nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        auto n0 = Interpolation::Lerp(nx0, nx1, t);

        nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0]]], fx1, fy0, fz0);
        nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1]]], fx1, fy0, fz1);

        nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0]]], fx1, fy1, fz0);
        nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1]]], fx1, fy1, fz1);

        nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        auto n1 = Interpolation::Lerp(nx0, nx1, t);

        return 0.936F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Normal(float x, float y, float z, float w) noexcept
    {
        auto ix0 = FastFloor(x);
        auto iy0 = FastFloor(y);
        auto iz0 = FastFloor(z);
        auto iw0 = FastFloor(w);

        auto fx0 = x - static_cast<float>(ix0);
        auto fy0 = y - static_cast<float>(iy0);
        auto fz0 = z - static_cast<float>(iz0);
        auto fw0 = w - static_cast<float>(iw0);

        auto fx1 = fx0 - 1.0F;
        auto fy1 = fy0 - 1.0F;
        auto fz1 = fz0 - 1.0F;
        auto fw1 = fw0 - 1.0F;

        auto ix1 = (ix0 + 1) & 0xFF;
        auto iy1 = (iy0 + 1) & 0xFF;
        auto iz1 = (iz0 + 1) & 0xFF;
        auto iw1 = (iw0 + 1) & 0xFF;

        ix0 = ix0 & 0xff;
        iy0 = iy0 & 0xff;
        iz0 = iz0 & 0xff;
        iw0 = iw0 & 0xff;

        auto q = Detail::Fade(fw0);
        auto r = Detail::Fade(fz0);
        auto t = Detail::Fade(fy0);
        auto s = Detail::Fade(fx0);

        float nxyz0;
        float nxyz1;

        float nxy0;
        float nxy1;

        float nx0;
        float nx1;

        float n0;
        float n1;

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx0, fy0, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx0, fy0, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx0, fy0, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx0, fy0, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx0, fy1, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx0, fy1, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx0, fy1, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx0, fy1, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        n0 = Interpolation::Lerp(nx0, nx1, t);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx1, fy0, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx1, fy0, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx1, fy0, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx1, fy0, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx1, fy1, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx1, fy1, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx1, fy1, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx1, fy1, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        n1 = Interpolation::Lerp(nx0, nx1, t);

        return 0.87F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Periodic(float x, int period_x) noexcept
    {
        auto ix0 = FastFloor(x);
        auto fx0 = x - static_cast<float>(ix0);
        auto fx1 = fx0 - 1.0F;
        auto ix1 = ((ix0 + 1) % period_x) & 0xFF;
        ix0 = (ix0 % period_x) & 0xFF;

        auto s = Detail::Fade(fx0);

        auto n0 = Detail::Gradient(CommonNoise::g_Permutations[ix0], fx0);
        auto n1 = Detail::Gradient(CommonNoise::g_Permutations[ix1], fx1);

        return 0.188F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Periodic(float x, float y, int period_x, int period_y) noexcept
    {
        auto ix0 = FastFloor(x);
        auto iy0 = FastFloor(y);
        auto fx0 = x - static_cast<float>(ix0);
        auto fy0 = y - static_cast<float>(iy0);
        auto fx1 = fx0 - 1.0F;
        auto fy1 = fy0 - 1.0F;
        auto ix1 = ((ix0 + 1) % period_x) & 0xFF;
        auto iy1 = ((iy0 + 1) % period_y) & 0xFF;
        ix0 = (ix0 % period_x) & 0xFF;
        iy0 = (iy0 % period_y) & 0xFF;

        auto t = Detail::Fade(fy0);
        auto s = Detail::Fade(fx0);

        auto nx0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0]], fx0, fy0);
        auto nx1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1]], fx0, fy1);

        auto n0 = Interpolation::Lerp(nx0, nx1, t);

        nx0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0]], fx1, fy0);
        nx1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1]], fx1, fy1);

        auto n1 = Interpolation::Lerp(nx0, nx1, t);

        return 0.507F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Periodic(float x, float y, float z, int period_x, int period_y, int period_z) noexcept
    {
        auto ix0 = FastFloor(x);
        auto iy0 = FastFloor(y);
        auto iz0 = FastFloor(z);

        auto fx0 = x - static_cast<float>(ix0);
        auto fy0 = y - static_cast<float>(iy0);
        auto fz0 = z - static_cast<float>(iz0);

        auto fx1 = fx0 - 1.0F;
        auto fy1 = fy0 - 1.0F;
        auto fz1 = fz0 - 1.0F;

        auto ix1 = ((ix0 + 1) % period_x) & 0xFF;
        auto iy1 = ((iy0 + 1) % period_y) & 0xFF;
        auto iz1 = ((iz0 + 1) % period_z) & 0xFF;

        ix0 = (ix0 % period_x) & 0xFF;
        iy0 = (iy0 % period_y) & 0xFF;
        iz0 = (iz0 % period_z) & 0xFF;

        auto r = Detail::Fade(fz0);
        auto t = Detail::Fade(fy0);
        auto s = Detail::Fade(fx0);

        auto nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0]]], fx0, fy0, fz0);
        auto nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1]]], fx0, fy0, fz1);

        auto nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0]]], fx0, fy1, fz0);
        nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1]]], fx0, fy1, fz1);

        auto nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        auto n0 = Interpolation::Lerp(nx0, nx1, t);

        nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0]]], fx1, fy0, fz0);
        nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1]]], fx1, fy0, fz1);

        nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxy0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0]]], fx1, fy1, fz0);
        nxy1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1]]], fx1, fy1, fz1);

        nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        auto n1 = Interpolation::Lerp(nx0, nx1, t);

        return 0.936F * Interpolation::Lerp(n0, n1, s);
    }

    float PerlinNoise::Periodic(float x, float y, float z, float w, int period_x, int period_y, int period_z, int period_w) noexcept
    {
        auto ix0 = FastFloor(x);
        auto iy0 = FastFloor(y);
        auto iz0 = FastFloor(z);
        auto iw0 = FastFloor(w);

        auto fx0 = x - static_cast<float>(ix0);
        auto fy0 = y - static_cast<float>(iy0);
        auto fz0 = z - static_cast<float>(iz0);
        auto fw0 = w - static_cast<float>(iw0);

        auto fx1 = fx0 - 1.0F;
        auto fy1 = fy0 - 1.0F;
        auto fz1 = fz0 - 1.0F;
        auto fw1 = fw0 - 1.0F;

        auto ix1 = ((ix0 + 1) % period_x) & 0xFF;
        auto iy1 = ((iy0 + 1) % period_y) & 0xFF;
        auto iz1 = ((iz0 + 1) % period_z) & 0xFF;
        auto iw1 = ((iw0 + 1) % period_w) & 0xFF;

        ix0 = (ix0 % period_x) & 0xff;
        iy0 = (iy0 % period_y) & 0xff;
        iz0 = (iz0 % period_z) & 0xff;
        iw0 = (iw0 % period_w) & 0xff;

        auto q = Detail::Fade(fw0);
        auto r = Detail::Fade(fz0);
        auto t = Detail::Fade(fy0);
        auto s = Detail::Fade(fx0);

        float nxyz0;
        float nxyz1;

        float nxy0;
        float nxy1;

        float nx0;
        float nx1;

        float n0;
        float n1;

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx0, fy0, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx0, fy0, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx0, fy0, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx0, fy0, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx0, fy1, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx0, fy1, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx0, fy1, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix0 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx0, fy1, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        n0 = Interpolation::Lerp(nx0, nx1, t);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx1, fy0, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx1, fy0, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx1, fy0, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy0 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx1, fy0, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx0 = Interpolation::Lerp(nxy0, nxy1, r);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw0]]]], fx1, fy1, fz0, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz0 + CommonNoise::g_Permutations[iw1]]]], fx1, fy1, fz0, fw1);

        nxy0 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nxyz0 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw0]]]], fx1, fy1, fz1, fw0);
        nxyz1 = Detail::Gradient(CommonNoise::g_Permutations[ix1 + CommonNoise::g_Permutations[iy1 + CommonNoise::g_Permutations[iz1 + CommonNoise::g_Permutations[iw1]]]], fx1, fy1, fz1, fw1);

        nxy1 = Interpolation::Lerp(nxyz0, nxyz1, q);

        nx1 = Interpolation::Lerp(nxy0, nxy1, r);

        n1 = Interpolation::Lerp(nx0, nx1, t);

        return 0.87F * Interpolation::Lerp(n0, n1, s);
    }
}
#endif
