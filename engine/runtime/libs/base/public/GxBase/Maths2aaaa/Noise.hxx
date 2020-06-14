#pragma once
#include <GxBase/Maths2/Vector.hxx>
#include <GxBase/Maths/Scalar.hxx>

namespace Graphyte::Maths::Noises::Impl
{
    mathinline float mathcall Mod289(float x) noexcept
    {
        return x - Floor(x * (1.0F / 289.0F)) * 289.0F;
    }

    mathinline Vec2 mathcall Mod289(Vec2 x) noexcept
    {
        return Sub(x, Mul(Floor(Mul(x, (1.0F / 289.0F))), 289.0F));
    }

    mathinline Vec3 mathcall Mod289(Vec3 x) noexcept
    {
        return Sub(x, Mul(Floor(Mul(x, (1.0F / 289.0F))), 289.0F));
    }

    mathinline Vec4 mathcall Mod289(Vec4 x) noexcept
    {
        return Sub(x, Mul(Floor(Mul(x, (1.0F / 289.0F))), 289.0F));
    }

    mathinline Vec3 mathcall Mod7(Vec3 x) noexcept
    {
        return Sub(x, Mul(Floor(Mul(x, (1.0F / 7.0F))), 7.0F));
    }

    mathinline Vec4 mathcall Mod7(Vec4 x) noexcept
    {
        return Sub(x, Mul(Floor(Mul(x, (1.0F / 7.0F))), 7.0F));
    }

    mathinline float mathcall Permute(float x) noexcept
    {
        return Mod289((34.0F * x + 1.0F) * x);
    }

    mathinline Vec3 mathcall Permute(Vec3 x) noexcept
    {
        return Mod289(Mul(MulAdd(Make<Vec3>(34.0F), x, One<Vec3>()), x));
    }

    mathinline Vec4 mathcall Permute(Vec4 x) noexcept
    {
        return Mod289(Mul(MulAdd(Make<Vec4>(34.0F), x, One<Vec4>()), x));
    }

    mathinline float mathcall TaylorInvSqrt(float r) noexcept
    {
        return 1.79284291400159F - 0.85373472095314F * r;
    }

    mathinline Vec4 mathcall TaylorInvSqrt(Vec4 r) noexcept
    {
        return NegMulAdd(Make<Vec4>(0.85373472095314F), r, Make<Vec4>(1.79284291400159));
    }

    mathinline Vec2 mathcall Fade(Vec2 t) noexcept
    {
        Vec2 const t1 = MulSub(t, Make<Vec2>(6.0F), Make<Vec2>(15.0F));
        Vec2 const t2 = MulAdd(t, t1, Make<Vec2>(10.0F));
        Vec2 const t3 = Mul(t, t);
        Vec2 const t4 = Mul(t, t2);
        Vec2 const r  = Mul(t3, t4);
        return r;
    }

    mathinline Vec3 mathcall Fade(Vec3 t) noexcept
    {
        Vec3 const t1 = MulSub(t, Make<Vec3>(6.0F), Make<Vec3>(15.0F));
        Vec3 const t2 = MulAdd(t, t1, Make<Vec3>(10.0F));
        Vec3 const t3 = Mul(t, t);
        Vec3 const t4 = Mul(t, t2);
        Vec3 const r  = Mul(t3, t4);
        return r;
    }

    mathinline Vec4 mathcall Fade(Vec4 t) noexcept
    {
        Vec4 const t1 = MulSub(t, Make<Vec4>(6.0F), Make<Vec4>(15.0F));
        Vec4 const t2 = MulAdd(t, t1, Make<Vec4>(10.0F));
        Vec4 const t3 = Mul(t, t);
        Vec4 const t4 = Mul(t, t2);
        Vec4 const r  = Mul(t3, t4);
        return r;
    }

    mathinline Vec4 mathcall Grad4(float j, Vec4 ip) noexcept
    {
        Vec4 const ones    = Make<Vec4>(1.0F, 1.0F, 1.0F, -1.0F);
        Vec3 const fjip    = Floor(Mul(Frac(Mul(Make<Vec3>(j), ToVec3(ip))), 7.0F));
        Vec3 const pxyz    = MulSub(fjip, ToVec3(SplatZ(ip)), One<Vec3>());
        Vec4 const pw      = Sub(Make<Vec4>(1.5F), Dot(Abs(pxyz), ToVec3(ones)));
        Vec4 const p       = Maths::Permute<0, 1, 2, 4>(ToVec4(pxyz), pw);
        Bool4 const cmpneg = Maths::CmpLt(p, Zero<Vec4>());
        Vec4 const s       = Select(Zero<Vec4>(), One<Vec4>(), cmpneg);
        Vec4 const sxyz    = MulSub(s, Make<Vec4>(2.0F), Make<Vec4>(1.0F));
        Vec4 const rs      = MulAdd(p, sxyz, SplatW(s));
        Vec4 const r       = Select(p, rs, { Maths::Impl::VEC4_MASK_COMPONENTS_3.V });
        return r;
    }


    //static float4 grad4(float j, float4 ip)
    //{
    //    float4 ones = float4(1.0f, 1.0f, 1.0f, -1.0f);
    //    float3 pxyz = floor(frac(float3(j) * ip.xyz) * 7.0f) * ip.z - 1.0f;
    //    float  pw = 1.5f - dot(abs(pxyz), ones.xyz);
    //    float4 p = float4(pxyz, pw); // permute
    //    float4 s = float4(p < 0.0f); // select
    //    p.xyz = p.xyz + (s.xyz * 2.0f - 1.0f) * s.www;
    //    return p;
    //}


    mathinline Vec2 mathcall Rgrad2(Vec2 p, float rot) noexcept
    {
        float const u = Permute(Permute(GetX(p)) + GetY(p)) * 0.0243902439f + rot;
        float const v = Frac(u) * PI2<float>;
        return Make<Vec2>(Cos(v), Sin(v));
    }
}

namespace Graphyte::Maths::Noises
{
    mathinline float mathcall snoise(Vec2 v) noexcept
    {
        Maths::Impl::Vec4F32 s_C{
            0.211324865405187f,  // (3.0-math.sqrt(3.0))/6.0
            0.366025403784439f,  // 0.5*(math.sqrt(3.0)-1.0)
            -0.577350269189626f, // -1.0 + 2.0 * C.x
            0.024390243902439f,  // 1.0 / 41.0
        };

        Vec4 const c{ s_C.V };

        // First corner
        Vec2 i  = Floor(Add(v, ToVec2(Dot(v, ToVec2(SplatY(c))))));
        Vec2 x0 = Sub(v, Add(i, ToVec2(Dot(i, ToVec2(SplatX(c))))));

        Vec2 i1 = GetX(x0) > GetY(x0) ? UnitX<Vec2>() : UnitY<Vec2>();

        Vec4 x12 = Add(Swizzle<SwizzleMask::XYXY>(ToVec4(x0)), Swizzle<SwizzleMask::XXZZ>(c));

        //x12.xy -= i1;
        x12 = Select(x12, ToVec4(Sub(ToVec2(x12), i1)), Bool4{ Maths::Impl::VEC4_MASK_SELECT_1100.V });

        i = Impl::Mod289(i);

        auto p = Impl::Permute(
            Add(
                Add(
                    Impl::Permute(
                        Add(ToVec3(SplatY(ToVec4(i))), Make<Vec3>(0.0F, GetY(i1), 1.0F))),
                    ToVec3(SplatX(ToVec4(i)))),
                Make<Vec3>(0.0F, GetX(i1), 1.0F)));

        Vec3 m = Max(Sub(Make<Vec3>(0.5F), Make<Vec3>(
                                               GetX(Dot(x0, x0)),
                                               GetX(Dot(ToVec2(Swizzle<SwizzleMask::XYXY>(x12)), ToVec2(Swizzle<SwizzleMask::XYXY>(x12)))),
                                               GetX(Dot(ToVec2(Swizzle<SwizzleMask::ZWZW>(x12)), ToVec2(Swizzle<SwizzleMask::ZWZW>(x12)))))),
            Zero<Vec3>());
        m      = Mul(m, m);
        m      = Mul(m, m);

        Vec3 x  = MulSub(Make<Vec3>(2.0F), Frac(Mul(p, ToVec3(SplatW(c)))), One<Vec3>());
        Vec3 h  = Sub(Abs(x), Make<Vec3>(0.5F));
        Vec3 ox = Floor(Add(x, Make<Vec3>(0.5F)));
        Vec3 a0 = Sub(x, ox);

        m = Mul(m, NegMulAdd(Make<Vec3>(0.85373472095314), Add(Mul(a0, a0), Mul(h, h)), Make<Vec3>(1.79284291400159)));

        float gx = GetX(a0) * GetX(a0) + GetX(h) * GetY(x0);
        Vec2 gyz = ToVec2(
            Add(
                Mul(
                    Swizzle<SwizzleMask::YZYZ>(ToVec4(a0)),
                    Swizzle<SwizzleMask::XZXZ>(x12)),
                Mul(
                    Swizzle<SwizzleMask::YZYZ>(ToVec4(h)),
                    Swizzle<SwizzleMask::YWYW>(x12))));

        Vec3 g = Make<Vec3>(gx, GetX(gyz), GetY(gyz));

        return 130.0F * GetX(Dot(m, g));
    }
}
