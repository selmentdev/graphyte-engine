#include <catch2/catch.hpp>
#if false
#include <Graphyte/Maths/Vector4.hxx>

TEST_CASE("Math / Vector4 / Construction", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Vector4 / Make Float + GetX/Y/Z/W Float")
    {
        const auto v1 = Vector4::Make(1.0F);
        CHECK(Vector4::GetX(v1) == Approx(1.0F));
        CHECK(Vector4::GetY(v1) == Approx(1.0F));
        CHECK(Vector4::GetZ(v1) == Approx(1.0F));
        CHECK(Vector4::GetW(v1) == Approx(1.0F));

        const auto v2 = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);
        CHECK(Vector4::GetX(v2) == Approx(1.0F));
        CHECK(Vector4::GetY(v2) == Approx(2.0F));
        CHECK(Vector4::GetZ(v2) == Approx(3.0F));
        CHECK(Vector4::GetW(v2) == Approx(4.0F));

        const float value = 5.0F;
        const auto v3 = Vector4::Make(&value);
        CHECK(Vector4::GetX(v3) == Approx(5.0F));
        CHECK(Vector4::GetY(v3) == Approx(5.0F));
        CHECK(Vector4::GetZ(v3) == Approx(5.0F));
        CHECK(Vector4::GetW(v3) == Approx(5.0F));
    }

    SECTION("Vector / MakeUInt + GetX/Y/Z/W UInt")
    {
        const auto v1 = Vector4::MakeUInt(1);
        CHECK(Vector4::GetUIntX(v1) == 1);
        CHECK(Vector4::GetUIntY(v1) == 1);
        CHECK(Vector4::GetUIntZ(v1) == 1);
        CHECK(Vector4::GetUIntW(v1) == 1);

        const auto v2 = Vector4::MakeUInt(1, 2, 3, 4);
        CHECK(Vector4::GetUIntX(v2) == 1);
        CHECK(Vector4::GetUIntY(v2) == 2);
        CHECK(Vector4::GetUIntZ(v2) == 3);
        CHECK(Vector4::GetUIntW(v2) == 4);

        const uint32_t value = 5;
        const auto v3 = Vector4::MakeUInt(&value);
        CHECK(Vector4::GetUIntX(v3) == 5);
        CHECK(Vector4::GetUIntY(v3) == 5);
        CHECK(Vector4::GetUIntZ(v3) == 5);
        CHECK(Vector4::GetUIntW(v3) == 5);
    }

    SECTION("Vector4 / Load Store / float variant")
    {
        const float unaligned1 = 1.0F;
        const float2 unaligned2 = { 2.0F, 3.0F };
        const float3 unaligned3 = { 4.0F, 5.0F, 6.0F };
        const float4 unaligned4 = { 8.0F, 9.0F, 10.0F, 11.0F };

        const float2a aligned2 = { 12.0F, 13.0F };
        const float3a aligned3 = { 14.0F, 15.0F, 16.0F };
        const float4a aligned4 = { 17.0F, 18.0F, 19.0F, 20.0F };

        SECTION("Unaligned - 1")
        {
            const auto v = Vector4::Load(&unaligned1);
            CHECK(Vector4::GetX(v) == 1.0F);
            CHECK(Vector4::GetY(v) == 0.0F);
            CHECK(Vector4::GetZ(v) == 0.0F);
            CHECK(Vector4::GetW(v) == 0.0F);

            float stored{};
            Vector4::Store(&stored, v);

            CHECK(stored == unaligned1);
        }

        SECTION("Unaligned - 2")
        {
            const auto v = Vector4::LoadPacked(&unaligned2);
            CHECK(Vector4::GetX(v) == 2.0F);
            CHECK(Vector4::GetY(v) == 3.0F);
            CHECK(Vector4::GetZ(v) == 0.0F);
            CHECK(Vector4::GetW(v) == 0.0F);

            float2 stored{};
            Vector4::StorePacked(&stored, v);

            CHECK(stored.X == unaligned2.X);
            CHECK(stored.Y == unaligned2.Y);
        }

        SECTION("Unaligned - 3")
        {
            const auto v = Vector4::LoadPacked(&unaligned3);
            CHECK(Vector4::GetX(v) == 4.0F);
            CHECK(Vector4::GetY(v) == 5.0F);
            CHECK(Vector4::GetZ(v) == 6.0F);
            CHECK(Vector4::GetW(v) == 0.0F);

            float3 stored{};
            Vector4::StorePacked(&stored, v);

            CHECK(stored.X == unaligned3.X);
            CHECK(stored.Y == unaligned3.Y);
            CHECK(stored.Z == unaligned3.Z);
        }

        SECTION("Unaligned - 4")
        {
            const auto v = Vector4::LoadPacked(&unaligned4);
            CHECK(Vector4::GetX(v) == 8.0F);
            CHECK(Vector4::GetY(v) == 9.0F);
            CHECK(Vector4::GetZ(v) == 10.0F);
            CHECK(Vector4::GetW(v) == 11.0F);

            float4 stored{};
            Vector4::StorePacked(&stored, v);

            CHECK(stored.X == unaligned4.X);
            CHECK(stored.Y == unaligned4.Y);
            CHECK(stored.Z == unaligned4.Z);
            CHECK(stored.W == unaligned4.W);
        }

        SECTION("Aligned - 2")
        {
            const auto v = Vector4::Load(&aligned2);
            CHECK(Vector4::GetX(v) == 12.0F);
            CHECK(Vector4::GetY(v) == 13.0F);
            CHECK(Vector4::GetZ(v) == 0.0F);
            CHECK(Vector4::GetW(v) == 0.0F);

            float2a stored{};
            Vector4::Store(&stored, v);

            CHECK(stored.X == aligned2.X);
            CHECK(stored.Y == aligned2.Y);
        }

        SECTION("Aligned - 3")
        {
            const auto v = Vector4::Load(&aligned3);
            CHECK(Vector4::GetX(v) == 14.0F);
            CHECK(Vector4::GetY(v) == 15.0F);
            CHECK(Vector4::GetZ(v) == 16.0F);
            CHECK(Vector4::GetW(v) == 0.0F);

            float3a stored{};
            Vector4::Store(&stored, v);

            CHECK(stored.X == aligned3.X);
            CHECK(stored.Y == aligned3.Y);
            CHECK(stored.Z == aligned3.Z);
        }

        SECTION("Aligned - 4")
        {
            const auto v = Vector4::Load(&aligned4);
            CHECK(Vector4::GetX(v) == 17.0F);
            CHECK(Vector4::GetY(v) == 18.0F);
            CHECK(Vector4::GetZ(v) == 19.0F);
            CHECK(Vector4::GetW(v) == 20.0F);

            float4a stored{};
            Vector4::Store(&stored, v);

            CHECK(stored.X == aligned4.X);
            CHECK(stored.Y == aligned4.Y);
            CHECK(stored.Z == aligned4.Z);
            CHECK(stored.W == aligned4.W);
        }
    }
}

TEST_CASE("Math / Vector4 / Splatting", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);

    SECTION("Splatting X")
    {
        const auto vx = Vector4::SplatX(v);
        float4a stored{};
        Vector4::Store(&stored, vx);

        CHECK(stored.X == Approx(1.0F));
        CHECK(stored.Y == Approx(1.0F));
        CHECK(stored.Z == Approx(1.0F));
        CHECK(stored.W == Approx(1.0F));
    }

    SECTION("Splatting Y")
    {
        const auto vx = Vector4::SplatY(v);
        float4a stored{};
        Vector4::Store(&stored, vx);

        CHECK(stored.X == Approx(2.0F));
        CHECK(stored.Y == Approx(2.0F));
        CHECK(stored.Z == Approx(2.0F));
        CHECK(stored.W == Approx(2.0F));
    }

    SECTION("Splatting Z")
    {
        const auto vx = Vector4::SplatZ(v);
        float4a stored{};
        Vector4::Store(&stored, vx);

        CHECK(stored.X == Approx(3.0F));
        CHECK(stored.Y == Approx(3.0F));
        CHECK(stored.Z == Approx(3.0F));
        CHECK(stored.W == Approx(3.0F));
    }

    SECTION("Splatting W")
    {
        const auto vx = Vector4::SplatW(v);
        float4a stored{};
        Vector4::Store(&stored, vx);

        CHECK(stored.X == Approx(4.0F));
        CHECK(stored.Y == Approx(4.0F));
        CHECK(stored.Z == Approx(4.0F));
        CHECK(stored.W == Approx(4.0F));
    }
}

TEST_CASE("Math / Vector4 / Accessing vector members / float", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);

    SECTION("Get by value+index")
    {
        CHECK(Vector4::GetByIndex(v, 0) == Approx(1.0F));
        CHECK(Vector4::GetByIndex(v, 1) == Approx(2.0F));
        CHECK(Vector4::GetByIndex(v, 2) == Approx(3.0F));
        CHECK(Vector4::GetByIndex(v, 3) == Approx(4.0F));
    }

    SECTION("Get by pointer+index")
    {
        float stored{};

        Vector4::GetByIndex(&stored, v, 0);
        CHECK(stored == Approx(1.0F));

        Vector4::GetByIndex(&stored, v, 1);
        CHECK(stored == Approx(2.0F));

        Vector4::GetByIndex(&stored, v, 2);
        CHECK(stored == Approx(3.0F));

        Vector4::GetByIndex(&stored, v, 3);
        CHECK(stored == Approx(4.0F));
    }

    SECTION("Get by value")
    {
        CHECK(Vector4::GetX(v) == Approx(1.0F));
        CHECK(Vector4::GetY(v) == Approx(2.0F));
        CHECK(Vector4::GetZ(v) == Approx(3.0F));
        CHECK(Vector4::GetW(v) == Approx(4.0F));
    }

    SECTION("Get by pointer")
    {
        float stored{};

        Vector4::GetX(&stored, v);
        CHECK(stored == Approx(1.0F));

        Vector4::GetY(&stored, v);
        CHECK(stored == Approx(2.0F));

        Vector4::GetZ(&stored, v);
        CHECK(stored == Approx(3.0F));

        Vector4::GetW(&stored, v);
        CHECK(stored == Approx(4.0F));
    }

    SECTION("Set by value + index")
    {
        auto vv = Vector4::SetByIndex(v, 5.0F, 0);
        vv = Vector4::SetByIndex(vv, 6.0F, 1);
        vv = Vector4::SetByIndex(vv, 7.0F, 2);
        vv = Vector4::SetByIndex(vv, 8.0F, 3);

        CHECK(Vector4::GetX(vv) == Approx(5.0F));
        CHECK(Vector4::GetY(vv) == Approx(6.0F));
        CHECK(Vector4::GetZ(vv) == Approx(7.0F));
        CHECK(Vector4::GetW(vv) == Approx(8.0F));
    }

    SECTION("Set by pointer + index")
    {
        const float data[] { 5.0F, 6.0F, 7.0F, 8.0F };
        auto vv = Vector4::SetByIndex(v, &data[0], 0);
        vv = Vector4::SetByIndex(vv, &data[1], 1);
        vv = Vector4::SetByIndex(vv, &data[2], 2);
        vv = Vector4::SetByIndex(vv, &data[3], 3);

        CHECK(Vector4::GetX(vv) == Approx(5.0F));
        CHECK(Vector4::GetY(vv) == Approx(6.0F));
        CHECK(Vector4::GetZ(vv) == Approx(7.0F));
        CHECK(Vector4::GetW(vv) == Approx(8.0F));
    }

    SECTION("Set by value")
    {
        auto vv = Vector4::SetX(v, 5.0F);
        vv = Vector4::SetY(vv, 6.0F);
        vv = Vector4::SetZ(vv, 7.0F);
        vv = Vector4::SetW(vv, 8.0F);

        CHECK(Vector4::GetX(vv) == Approx(5.0F));
        CHECK(Vector4::GetY(vv) == Approx(6.0F));
        CHECK(Vector4::GetZ(vv) == Approx(7.0F));
        CHECK(Vector4::GetW(vv) == Approx(8.0F));
    }

    SECTION("Set by pointer")
    {
        const float data[] { 5.0F, 6.0F, 7.0F, 8.0F };
        auto vv = Vector4::SetX(v, &data[0]);
        vv = Vector4::SetY(vv, &data[1]);
        vv = Vector4::SetZ(vv, &data[2]);
        vv = Vector4::SetW(vv, &data[3]);

        CHECK(Vector4::GetX(vv) == Approx(5.0F));
        CHECK(Vector4::GetY(vv) == Approx(6.0F));
        CHECK(Vector4::GetZ(vv) == Approx(7.0F));
        CHECK(Vector4::GetW(vv) == Approx(8.0F));
    }
}

TEST_CASE("Math / Vector4 / Accessing vector members / uint", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v = Vector4::MakeUInt(1, 2, 3, 4);

    SECTION("Get by value+index")
    {
        CHECK(Vector4::GetUIntByIndex(v, 0) == 1);
        CHECK(Vector4::GetUIntByIndex(v, 1) == 2);
        CHECK(Vector4::GetUIntByIndex(v, 2) == 3);
        CHECK(Vector4::GetUIntByIndex(v, 3) == 4);
    }

    SECTION("Get by pointer+index")
    {
        uint32_t stored{};

        Vector4::GetUIntByIndex(&stored, v, 0);
        CHECK(stored == 1);

        Vector4::GetUIntByIndex(&stored, v, 1);
        CHECK(stored == 2);

        Vector4::GetUIntByIndex(&stored, v, 2);
        CHECK(stored == 3);

        Vector4::GetUIntByIndex(&stored, v, 3);
        CHECK(stored == 4);
    }

    SECTION("Get by value")
    {
        CHECK(Vector4::GetUIntX(v) == 1);
        CHECK(Vector4::GetUIntY(v) == 2);
        CHECK(Vector4::GetUIntZ(v) == 3);
        CHECK(Vector4::GetUIntW(v) == 4);
    }

    SECTION("Get by pointer")
    {
        uint32_t stored{};

        Vector4::GetUIntX(&stored, v);
        CHECK(stored == 1);

        Vector4::GetUIntY(&stored, v);
        CHECK(stored == 2);

        Vector4::GetUIntZ(&stored, v);
        CHECK(stored == 3);

        Vector4::GetUIntW(&stored, v);
        CHECK(stored == 4);
    }

    SECTION("Set by value + index")
    {
        auto vv = Vector4::SetUIntByIndex(v, 5, 0);
        vv = Vector4::SetUIntByIndex(vv, 6, 1);
        vv = Vector4::SetUIntByIndex(vv, 7, 2);
        vv = Vector4::SetUIntByIndex(vv, 8, 3);

        CHECK(Vector4::GetUIntX(vv) == 5);
        CHECK(Vector4::GetUIntY(vv) == 6);
        CHECK(Vector4::GetUIntZ(vv) == 7);
        CHECK(Vector4::GetUIntW(vv) == 8);
    }

    SECTION("Set by pointer + index")
    {
        const uint32_t data[] { 5, 6, 7, 8 };
        auto vv = Vector4::SetUIntByIndex(v, &data[0], 0);
        vv = Vector4::SetUIntByIndex(vv, &data[1], 1);
        vv = Vector4::SetUIntByIndex(vv, &data[2], 2);
        vv = Vector4::SetUIntByIndex(vv, &data[3], 3);

        CHECK(Vector4::GetUIntX(vv) == 5);
        CHECK(Vector4::GetUIntY(vv) == 6);
        CHECK(Vector4::GetUIntZ(vv) == 7);
        CHECK(Vector4::GetUIntW(vv) == 8);
    }

    SECTION("Set by value")
    {
        auto vv = Vector4::SetUIntX(v, 5);
        vv = Vector4::SetUIntY(vv, 6);
        vv = Vector4::SetUIntZ(vv, 7);
        vv = Vector4::SetUIntW(vv, 8);

        CHECK(Vector4::GetUIntX(vv) == 5);
        CHECK(Vector4::GetUIntY(vv) == 6);
        CHECK(Vector4::GetUIntZ(vv) == 7);
        CHECK(Vector4::GetUIntW(vv) == 8);
    }

    SECTION("Set by pointer")
    {
        const uint32_t data[] { 5, 6, 7, 8 };
        auto vv = Vector4::SetUIntX(v, &data[0]);
        vv = Vector4::SetUIntY(vv, &data[1]);
        vv = Vector4::SetUIntZ(vv, &data[2]);
        vv = Vector4::SetUIntW(vv, &data[3]);

        CHECK(Vector4::GetUIntX(vv) == 5);
        CHECK(Vector4::GetUIntY(vv) == 6);
        CHECK(Vector4::GetUIntZ(vv) == 7);
        CHECK(Vector4::GetUIntW(vv) == 8);
    }
}

TEST_CASE("Math / Vector4 / Swizzling", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);

    SECTION("By swizzle mask")
    {
        SECTION("Variant 1")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::XXXX>(v);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(1.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 2")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::WZYX>(v);
            CHECK(Vector4::GetX(vv) == Approx(4.0));
            CHECK(Vector4::GetY(vv) == Approx(3.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 3")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::XXYW>(v);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 4")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::WZZX>(v);
            CHECK(Vector4::GetX(vv) == Approx(4.0));
            CHECK(Vector4::GetY(vv) == Approx(3.0));
            CHECK(Vector4::GetZ(vv) == Approx(3.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 5")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::ZYXW>(v);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(2.0));
            CHECK(Vector4::GetZ(vv) == Approx(1.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 6")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::ZWZY>(v);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(4.0));
            CHECK(Vector4::GetZ(vv) == Approx(3.0));
            CHECK(Vector4::GetW(vv) == Approx(2.0));
        }

        SECTION("Variant 7")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::ZYYW>(v);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(2.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 8")
        {
            const auto vv = Vector4::Swizzle<SwizzleMask::XXYZ>(v);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(3.0));
        }
    }

    SECTION("By swizzle indices")
    {
        SECTION("Variant 1")
        {
            const auto vv = Vector4::Swizzle<0, 0, 0, 0>(v);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(1.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 2")
        {
            const auto vv = Vector4::Swizzle<3, 2, 1, 0>(v);
            CHECK(Vector4::GetX(vv) == Approx(4.0));
            CHECK(Vector4::GetY(vv) == Approx(3.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 3")
        {
            const auto vv = Vector4::Swizzle<0, 0, 1, 3>(v);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 4")
        {
            const auto vv = Vector4::Swizzle<3, 2, 2, 0>(v);
            CHECK(Vector4::GetX(vv) == Approx(4.0));
            CHECK(Vector4::GetY(vv) == Approx(3.0));
            CHECK(Vector4::GetZ(vv) == Approx(3.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 5")
        {
            const auto vv = Vector4::Swizzle<2, 1, 0, 3>(v);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(2.0));
            CHECK(Vector4::GetZ(vv) == Approx(1.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 6")
        {
            const auto vv = Vector4::Swizzle<2, 3, 2, 1>(v);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(4.0));
            CHECK(Vector4::GetZ(vv) == Approx(3.0));
            CHECK(Vector4::GetW(vv) == Approx(2.0));
        }

        SECTION("Variant 7")
        {
            const auto vv = Vector4::Swizzle<2, 1, 1, 3>(v);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(2.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 8")
        {
            const auto vv = Vector4::Swizzle<0, 0, 1, 2>(v);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(3.0));
        }
    }

    SECTION("By swizzle indices at runtime")
    {
        SECTION("Variant 1")
        {
            const auto vv = Vector4::Swizzle(v, 0, 0, 0, 0);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(1.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 2")
        {
            const auto vv = Vector4::Swizzle(v, 3, 2, 1, 0);
            CHECK(Vector4::GetX(vv) == Approx(4.0));
            CHECK(Vector4::GetY(vv) == Approx(3.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 3")
        {
            const auto vv = Vector4::Swizzle(v, 0, 0, 1, 3);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 4")
        {
            const auto vv = Vector4::Swizzle(v, 3, 2, 2, 0);
            CHECK(Vector4::GetX(vv) == Approx(4.0));
            CHECK(Vector4::GetY(vv) == Approx(3.0));
            CHECK(Vector4::GetZ(vv) == Approx(3.0));
            CHECK(Vector4::GetW(vv) == Approx(1.0));
        }

        SECTION("Variant 5")
        {
            const auto vv = Vector4::Swizzle(v, 2, 1, 0, 3);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(2.0));
            CHECK(Vector4::GetZ(vv) == Approx(1.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 6")
        {
            const auto vv = Vector4::Swizzle(v, 2, 3, 2, 1);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(4.0));
            CHECK(Vector4::GetZ(vv) == Approx(3.0));
            CHECK(Vector4::GetW(vv) == Approx(2.0));
        }

        SECTION("Variant 7")
        {
            const auto vv = Vector4::Swizzle(v, 2, 1, 1, 3);
            CHECK(Vector4::GetX(vv) == Approx(3.0));
            CHECK(Vector4::GetY(vv) == Approx(2.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(4.0));
        }

        SECTION("Variant 8")
        {
            const auto vv = Vector4::Swizzle(v, 0, 0, 1, 2);
            CHECK(Vector4::GetX(vv) == Approx(1.0));
            CHECK(Vector4::GetY(vv) == Approx(1.0));
            CHECK(Vector4::GetZ(vv) == Approx(2.0));
            CHECK(Vector4::GetW(vv) == Approx(3.0));
        }
    }

    SECTION("Vector4 / Permute")
    {
        const auto v1 = Vector4::Make(0.0F, 1.0F, 2.0F, 3.0F);
        const auto v2 = Vector4::Make(4.0F, 5.0F, 6.0F, 7.0F);

        SECTION("By template params")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::Permute<0, 1, 6, 7>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(0.0F));
                CHECK(Vector4::GetY(vv) == Approx(1.0F));
                CHECK(Vector4::GetZ(vv) == Approx(6.0F));
                CHECK(Vector4::GetW(vv) == Approx(7.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::Permute<0, 0, 0, 0>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(0.0F));
                CHECK(Vector4::GetY(vv) == Approx(0.0F));
                CHECK(Vector4::GetZ(vv) == Approx(0.0F));
                CHECK(Vector4::GetW(vv) == Approx(0.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::Permute<0, 7, 5, 3>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(0.0F));
                CHECK(Vector4::GetY(vv) == Approx(7.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(3.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::Permute<1, 3, 5, 0>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(0.0F));
            }
        }

        SECTION("By function arguments")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::Permute(v1, v2, 0, 1, 6, 7);
                CHECK(Vector4::GetX(vv) == Approx(0.0F));
                CHECK(Vector4::GetY(vv) == Approx(1.0F));
                CHECK(Vector4::GetZ(vv) == Approx(6.0F));
                CHECK(Vector4::GetW(vv) == Approx(7.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::Permute(v1, v2, 0, 0, 0, 0);
                CHECK(Vector4::GetX(vv) == Approx(0.0F));
                CHECK(Vector4::GetY(vv) == Approx(0.0F));
                CHECK(Vector4::GetZ(vv) == Approx(0.0F));
                CHECK(Vector4::GetW(vv) == Approx(0.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::Permute(v1, v2, 0, 7, 5, 3);
                CHECK(Vector4::GetX(vv) == Approx(0.0F));
                CHECK(Vector4::GetY(vv) == Approx(7.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(3.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::Permute(v1, v2, 1, 3, 5, 0);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(0.0F));
            }
        }
    }

    SECTION("Select fields")
    {
        const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);
        const auto v2 = Vector4::Make(5.0F, 6.0F, 7.0F, 8.0F);

        SECTION("Variant 1")
        {
            const auto select = Vector4::SelectControl(1, 0, 0, 1);
            const auto vv = Vector4::Select(v1, v2, select);

            CHECK(Vector4::GetX(vv) == Approx(5.0F));
            CHECK(Vector4::GetY(vv) == Approx(2.0F));
            CHECK(Vector4::GetZ(vv) == Approx(3.0F));
            CHECK(Vector4::GetW(vv) == Approx(8.0F));
        }

        SECTION("Variant 2")
        {
            const auto select = Vector4::SelectControl(1, 1, 1, 1);
            const auto vv = Vector4::Select(v1, v2, select);

            CHECK(Vector4::GetX(vv) == Approx(5.0F));
            CHECK(Vector4::GetY(vv) == Approx(6.0F));
            CHECK(Vector4::GetZ(vv) == Approx(7.0F));
            CHECK(Vector4::GetW(vv) == Approx(8.0F));
        }

        SECTION("Variant 3")
        {
            const auto select = Vector4::SelectControl(0, 0, 1, 1);
            const auto vv = Vector4::Select(v1, v2, select);

            CHECK(Vector4::GetX(vv) == Approx(1.0F));
            CHECK(Vector4::GetY(vv) == Approx(2.0F));
            CHECK(Vector4::GetZ(vv) == Approx(7.0F));
            CHECK(Vector4::GetW(vv) == Approx(8.0F));
        }

        SECTION("Variant 4")
        {
            const auto select = Vector4::SelectControl(0, 1, 0, 1);
            const auto vv = Vector4::Select(v1, v2, select);

            CHECK(Vector4::GetX(vv) == Approx(1.0F));
            CHECK(Vector4::GetY(vv) == Approx(6.0F));
            CHECK(Vector4::GetZ(vv) == Approx(3.0F));
            CHECK(Vector4::GetW(vv) == Approx(8.0F));
        }
    }

    SECTION("Merge XY / ZW")
    {
        const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);
        const auto v2 = Vector4::Make(5.0F, 6.0F, 7.0F, 8.0F);

        SECTION("Variant 1")
        {
            const auto vv = Vector4::MergeXY(v1, v2);

            CHECK(Vector4::GetX(vv) == Approx(1.0F));
            CHECK(Vector4::GetY(vv) == Approx(5.0F));
            CHECK(Vector4::GetZ(vv) == Approx(2.0F));
            CHECK(Vector4::GetW(vv) == Approx(6.0F));
        }

        SECTION("Variant 2")
        {
            const auto vv = Vector4::MergeXY(v2, v1);

            CHECK(Vector4::GetX(vv) == Approx(5.0F));
            CHECK(Vector4::GetY(vv) == Approx(1.0F));
            CHECK(Vector4::GetZ(vv) == Approx(6.0F));
            CHECK(Vector4::GetW(vv) == Approx(2.0F));
        }
        SECTION("Variant 3")
        {
            const auto vv = Vector4::MergeZW(v1, v2);

            CHECK(Vector4::GetX(vv) == Approx(3.0F));
            CHECK(Vector4::GetY(vv) == Approx(7.0F));
            CHECK(Vector4::GetZ(vv) == Approx(4.0F));
            CHECK(Vector4::GetW(vv) == Approx(8.0F));
        }

        SECTION("Variant 4")
        {
            const auto vv = Vector4::MergeZW(v2, v1);

            CHECK(Vector4::GetX(vv) == Approx(7.0F));
            CHECK(Vector4::GetY(vv) == Approx(3.0F));
            CHECK(Vector4::GetZ(vv) == Approx(8.0F));
            CHECK(Vector4::GetW(vv) == Approx(4.0F));
        }
    }

    SECTION("Shift and rotations")
    {
        const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);
        const auto v2 = Vector4::Make(5.0F, 6.0F, 7.0F, 8.0F);

        SECTION("Shift left - by template param")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::ShiftLeft<0>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::ShiftLeft<1>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(2.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(4.0F));
                CHECK(Vector4::GetW(vv) == Approx(5.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::ShiftLeft<2>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(3.0F));
                CHECK(Vector4::GetY(vv) == Approx(4.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(6.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::ShiftLeft<3>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(4.0F));
                CHECK(Vector4::GetY(vv) == Approx(5.0F));
                CHECK(Vector4::GetZ(vv) == Approx(6.0F));
                CHECK(Vector4::GetW(vv) == Approx(7.0F));
            }
        }

        SECTION("Shift left - by argument")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::ShiftLeft(v1, v2, 0);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::ShiftLeft(v1, v2, 1);
                CHECK(Vector4::GetX(vv) == Approx(2.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(4.0F));
                CHECK(Vector4::GetW(vv) == Approx(5.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::ShiftLeft(v1, v2, 2);
                CHECK(Vector4::GetX(vv) == Approx(3.0F));
                CHECK(Vector4::GetY(vv) == Approx(4.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(6.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::ShiftLeft(v1, v2, 3);
                CHECK(Vector4::GetX(vv) == Approx(4.0F));
                CHECK(Vector4::GetY(vv) == Approx(5.0F));
                CHECK(Vector4::GetZ(vv) == Approx(6.0F));
                CHECK(Vector4::GetW(vv) == Approx(7.0F));
            }
        }

        SECTION("Rotate left - by template param")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::RotateLeft<0>(v1);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::RotateLeft<1>(v1);
                CHECK(Vector4::GetX(vv) == Approx(2.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(4.0F));
                CHECK(Vector4::GetW(vv) == Approx(1.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::RotateLeft<2>(v1);
                CHECK(Vector4::GetX(vv) == Approx(3.0F));
                CHECK(Vector4::GetY(vv) == Approx(4.0F));
                CHECK(Vector4::GetZ(vv) == Approx(1.0F));
                CHECK(Vector4::GetW(vv) == Approx(2.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::RotateLeft<3>(v1);
                CHECK(Vector4::GetX(vv) == Approx(4.0F));
                CHECK(Vector4::GetY(vv) == Approx(1.0F));
                CHECK(Vector4::GetZ(vv) == Approx(2.0F));
                CHECK(Vector4::GetW(vv) == Approx(3.0F));
            }
        }

        SECTION("Rotate left - by argument")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::RotateLeft(v1, 0);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::RotateLeft(v1, 1);
                CHECK(Vector4::GetX(vv) == Approx(2.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(4.0F));
                CHECK(Vector4::GetW(vv) == Approx(1.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::RotateLeft(v1, 2);
                CHECK(Vector4::GetX(vv) == Approx(3.0F));
                CHECK(Vector4::GetY(vv) == Approx(4.0F));
                CHECK(Vector4::GetZ(vv) == Approx(1.0F));
                CHECK(Vector4::GetW(vv) == Approx(2.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::RotateLeft(v1, 3);
                CHECK(Vector4::GetX(vv) == Approx(4.0F));
                CHECK(Vector4::GetY(vv) == Approx(1.0F));
                CHECK(Vector4::GetZ(vv) == Approx(2.0F));
                CHECK(Vector4::GetW(vv) == Approx(3.0F));
            }
        }

        SECTION("Rotate right - by template param")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::RotateRight<0>(v1);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::RotateRight<1>(v1);
                CHECK(Vector4::GetX(vv) == Approx(4.0F));
                CHECK(Vector4::GetY(vv) == Approx(1.0F));
                CHECK(Vector4::GetZ(vv) == Approx(2.0F));
                CHECK(Vector4::GetW(vv) == Approx(3.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::RotateRight<2>(v1);
                CHECK(Vector4::GetX(vv) == Approx(3.0F));
                CHECK(Vector4::GetY(vv) == Approx(4.0F));
                CHECK(Vector4::GetZ(vv) == Approx(1.0F));
                CHECK(Vector4::GetW(vv) == Approx(2.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::RotateRight<3>(v1);
                CHECK(Vector4::GetX(vv) == Approx(2.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(4.0F));
                CHECK(Vector4::GetW(vv) == Approx(1.0F));
            }
        }

        SECTION("Rotate right - by argument")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::RotateRight(v1, 0);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::RotateRight(v1, 1);
                CHECK(Vector4::GetX(vv) == Approx(4.0F));
                CHECK(Vector4::GetY(vv) == Approx(1.0F));
                CHECK(Vector4::GetZ(vv) == Approx(2.0F));
                CHECK(Vector4::GetW(vv) == Approx(3.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::RotateRight(v1, 2);
                CHECK(Vector4::GetX(vv) == Approx(3.0F));
                CHECK(Vector4::GetY(vv) == Approx(4.0F));
                CHECK(Vector4::GetZ(vv) == Approx(1.0F));
                CHECK(Vector4::GetW(vv) == Approx(2.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::RotateRight(v1, 3);
                CHECK(Vector4::GetX(vv) == Approx(2.0F));
                CHECK(Vector4::GetY(vv) == Approx(3.0F));
                CHECK(Vector4::GetZ(vv) == Approx(4.0F));
                CHECK(Vector4::GetW(vv) == Approx(1.0F));
            }
        }
    }

    SECTION("Insertion")
    {
        const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);
        const auto v2 = Vector4::Make(5.0F, 6.0F, 7.0F, 8.0F);

        SECTION("By template mask")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert<InsertMask::_1010>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(5.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(7.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 2")
            {
                const auto vv = Vector4::Insert<InsertMask::_0000>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 3")
            {
                const auto vv = Vector4::Insert<InsertMask::_0101>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(6.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(8.0F));
            }

            SECTION("Variant 4")
            {
                const auto vv = Vector4::Insert<InsertMask::_1111>(v1, v2);
                CHECK(Vector4::GetX(vv) == Approx(5.0F));
                CHECK(Vector4::GetY(vv) == Approx(6.0F));
                CHECK(Vector4::GetZ(vv) == Approx(7.0F));
                CHECK(Vector4::GetW(vv) == Approx(8.0F));
            }
        }

        SECTION("By by arguments")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 1, 0, 1, 0);
                CHECK(Vector4::GetX(vv) == Approx(5.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(7.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 0, 0, 0, 0);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 0, 1, 0, 1);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(6.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(8.0F));
            }

            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 1, 1, 1, 1);
                CHECK(Vector4::GetX(vv) == Approx(5.0F));
                CHECK(Vector4::GetY(vv) == Approx(6.0F));
                CHECK(Vector4::GetZ(vv) == Approx(7.0F));
                CHECK(Vector4::GetW(vv) == Approx(8.0F));
            }
        }

        SECTION("By by arguments with rotate")
        {
            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 0, 1, 0, 1, 0);
                CHECK(Vector4::GetX(vv) == Approx(5.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(7.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 3, 0, 0, 0, 0);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(2.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(4.0F));
            }

            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 1, 0, 1, 0, 1);
                CHECK(Vector4::GetX(vv) == Approx(1.0F));
                CHECK(Vector4::GetY(vv) == Approx(7.0F));
                CHECK(Vector4::GetZ(vv) == Approx(3.0F));
                CHECK(Vector4::GetW(vv) == Approx(5.0F));
            }

            SECTION("Variant 1")
            {
                const auto vv = Vector4::Insert(v1, v2, 2, 1, 1, 1, 1);
                CHECK(Vector4::GetX(vv) == Approx(7.0F));
                CHECK(Vector4::GetY(vv) == Approx(8.0F));
                CHECK(Vector4::GetZ(vv) == Approx(5.0F));
                CHECK(Vector4::GetW(vv) == Approx(6.0F));
            }
        }
    }
}

TEST_CASE("Math / Vector4 / Generic comparison functions", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, 1.0F);
    const auto v2 = Vector4::Make(3.0F, 2.0F, 1.0F, 2.0F);
    const auto eps = Vector4::Make(1.5F);

    SECTION("Compare Equal")
    {
        const auto vv = Vector4::CompareEqual(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

        CHECK(Vector4::IsEqual(v1, v2) == false);
    }

    SECTION("Compare Equal Epsilon")
    {
        const auto vv = Vector4::CompareEqual(v1, v2, eps);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntW(vv) == 0xFFFF'FFFF);

        CHECK(Vector4::IsEqual(v1, v2, eps) == false);
    }

    SECTION("Compare Not Equal")
    {
        const auto vv = Vector4::CompareNotEqual(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntZ(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntW(vv) == 0xFFFF'FFFF);

        CHECK(Vector4::IsNotEqual(v1, v2) == true);
    }

    SECTION("Compare Greater")
    {
        const auto vv = Vector4::CompareGreater(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntZ(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

        CHECK(Vector4::IsGreater(v1, v2) == false);
    }

    SECTION("Compare Greater Equal")
    {
        const auto vv = Vector4::CompareGreaterEqual(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntZ(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

        CHECK(Vector4::IsGreaterEqual(v1, v2) == false);
    }

    SECTION("Compare Less")
    {
        const auto vv = Vector4::CompareLess(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntW(vv) == 0xFFFF'FFFF);

        CHECK(Vector4::IsLess(v1, v2) == false);
    }

    SECTION("Compare Less Equal")
    {
        const auto vv = Vector4::CompareLessEqual(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntW(vv) == 0xFFFF'FFFF);

        CHECK(Vector4::IsLessEqual(v1, v2) == false);
    }

    SECTION("Compare in bounds")
    {
        const auto vv = Vector4::CompareInBounds(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntW(vv) == 0xFFFF'FFFF);

        CHECK(Vector4::InBounds(v1, v2) == false);
    }

    SECTION("Mask Compare Equal")
    {
        const auto vv = Vector4::MaskCompareEqual(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

        CHECK(Vector4::IsEqualUInt(v1, v2) == false);
    }

    SECTION("Mask Compare Not Equal")
    {
        const auto vv = Vector4::MaskCompareNotEqual(v1, v2);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::GetUIntX(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
        CHECK(Vector4::GetUIntZ(vv) == 0xFFFF'FFFF);
        CHECK(Vector4::GetUIntW(vv) == 0xFFFF'FFFF);

        CHECK(Vector4::IsNotEqualUInt(v1, v2) == true);
    }
}

TEST_CASE("Math / Vector4 / Compare nan / inf checking", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v1 = Vector4::Make(1.0F, std::numeric_limits<float>::infinity(), 3.0F, 1.0F);
    const auto v2 = Vector4::Make(3.0F, 2.0F, std::numeric_limits<float>::quiet_NaN(), 2.0F);
    const auto v3 = Vector4::Make(3.0F, 2.0F, 3.0F, 2.0F);

    SECTION("Checking if QNaN")
    {
        SECTION("Variant 1")
        {
            const auto vv = Vector4::CompareIsNaN(v1);

            CHECK(Vector4::AnyTrue(vv) == false);
            CHECK(Vector4::AnyFalse(vv) == true);
            CHECK(Vector4::AllTrue(vv) == false);
            CHECK(Vector4::AllFalse(vv) == true);

            CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

            CHECK(Vector4::IsNaN(v1) == false);
        }

        SECTION("Variant 2")
        {
            const auto vv = Vector4::CompareIsNaN(v2);

            CHECK(Vector4::AnyTrue(vv) == true);
            CHECK(Vector4::AnyFalse(vv) == true);
            CHECK(Vector4::AllTrue(vv) == false);
            CHECK(Vector4::AllFalse(vv) == false);

            CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntZ(vv) == 0xFFFF'FFFF);
            CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

            CHECK(Vector4::IsNaN(v2) == true);
        }

        SECTION("Variant 3")
        {
            const auto vv = Vector4::CompareIsNaN(v3);

            CHECK(Vector4::AnyTrue(vv) == false);
            CHECK(Vector4::AnyFalse(vv) == true);
            CHECK(Vector4::AllTrue(vv) == false);
            CHECK(Vector4::AllFalse(vv) == true);

            CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

            CHECK(Vector4::IsNaN(v3) == false);
        }
    }

    SECTION("Checking if inf")
    {
        SECTION("Variant 1")
        {
            const auto vv = Vector4::CompareIsInfinite(v1);

            CHECK(Vector4::AnyTrue(vv) == true);
            CHECK(Vector4::AnyFalse(vv) == true);
            CHECK(Vector4::AllTrue(vv) == false);
            CHECK(Vector4::AllFalse(vv) == false);

            CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntY(vv) == 0xFFFF'FFFF);
            CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

            CHECK(Vector4::IsInfinite(v1) == true);
        }

        SECTION("Variant 2")
        {
            const auto vv = Vector4::CompareIsInfinite(v2);

            CHECK(Vector4::AnyTrue(vv) == false);
            CHECK(Vector4::AnyFalse(vv) == true);
            CHECK(Vector4::AllTrue(vv) == false);
            CHECK(Vector4::AllFalse(vv) == true);

            CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

            CHECK(Vector4::IsInfinite(v2) == false);
        }

        SECTION("Variant 3")
        {
            const auto vv = Vector4::CompareIsInfinite(v3);

            CHECK(Vector4::AnyTrue(vv) == false);
            CHECK(Vector4::AnyFalse(vv) == true);
            CHECK(Vector4::AllTrue(vv) == false);
            CHECK(Vector4::AllFalse(vv) == true);

            CHECK(Vector4::GetUIntX(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntY(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntZ(vv) == 0x0000'0000);
            CHECK(Vector4::GetUIntW(vv) == 0x0000'0000);

            CHECK(Vector4::IsInfinite(v3) == false);
        }
    }
}

TEST_CASE("Math / Vector4 / Checking predefined constants", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    CHECK(Vector4::GetX(Vector4::Zero()) == Approx(0.0F));
    CHECK(Vector4::GetY(Vector4::Zero()) == Approx(0.0F));
    CHECK(Vector4::GetZ(Vector4::Zero()) == Approx(0.0F));
    CHECK(Vector4::GetW(Vector4::Zero()) == Approx(0.0F));

    CHECK(Vector4::GetX(Vector4::One()) == Approx(1.0F));
    CHECK(Vector4::GetY(Vector4::One()) == Approx(1.0F));
    CHECK(Vector4::GetZ(Vector4::One()) == Approx(1.0F));
    CHECK(Vector4::GetW(Vector4::One()) == Approx(1.0F));

    CHECK(Vector4::IsInfinite(Vector4::Infinity()));

    CHECK(Vector4::IsNaN(Vector4::NaN()));

    CHECK(Vector4::GetX(Vector4::Epsilon()) == Approx(0.0F).margin(0.001F));
    CHECK(Vector4::GetY(Vector4::Epsilon()) == Approx(0.0F).margin(0.001F));
    CHECK(Vector4::GetZ(Vector4::Epsilon()) == Approx(0.0F).margin(0.001F));
    CHECK(Vector4::GetW(Vector4::Epsilon()) == Approx(0.0F).margin(0.001F));

    CHECK(Vector4::GetUIntX(Vector4::SignMask()) == 0x8000'0000);
    CHECK(Vector4::GetUIntY(Vector4::SignMask()) == 0x8000'0000);
    CHECK(Vector4::GetUIntZ(Vector4::SignMask()) == 0x8000'0000);
    CHECK(Vector4::GetUIntW(Vector4::SignMask()) == 0x8000'0000);

    CHECK(Vector4::GetX(Vector4::UnitX()) == Approx(1.0F));
    CHECK(Vector4::GetY(Vector4::UnitX()) == Approx(0.0F));
    CHECK(Vector4::GetZ(Vector4::UnitX()) == Approx(0.0F));
    CHECK(Vector4::GetW(Vector4::UnitX()) == Approx(0.0F));

    CHECK(Vector4::GetX(Vector4::UnitY()) == Approx(0.0F));
    CHECK(Vector4::GetY(Vector4::UnitY()) == Approx(1.0F));
    CHECK(Vector4::GetZ(Vector4::UnitY()) == Approx(0.0F));
    CHECK(Vector4::GetW(Vector4::UnitY()) == Approx(0.0F));

    CHECK(Vector4::GetX(Vector4::UnitZ()) == Approx(0.0F));
    CHECK(Vector4::GetY(Vector4::UnitZ()) == Approx(0.0F));
    CHECK(Vector4::GetZ(Vector4::UnitZ()) == Approx(1.0F));
    CHECK(Vector4::GetW(Vector4::UnitZ()) == Approx(0.0F));

    CHECK(Vector4::GetX(Vector4::UnitW()) == Approx(0.0F));
    CHECK(Vector4::GetY(Vector4::UnitW()) == Approx(0.0F));
    CHECK(Vector4::GetZ(Vector4::UnitW()) == Approx(0.0F));
    CHECK(Vector4::GetW(Vector4::UnitW()) == Approx(1.0F));
}

TEST_CASE("Math / Vector4 / bitwise operations", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v1 = Vector4::MakeUInt(0xFFFF'FFFF, 0x0000'0000, 0xFFFF'FFFF, 0x0000'0000);
    const auto v2 = Vector4::MakeUInt(0x0000'0000, 0xFFFF'FFFF, 0x0000'0000, 0xFFFF'FFFF);
    const auto v3 = Vector4::MakeUInt(0xFFFF'FFFF, 0xFFFF'FFFF, 0x0000'0000, 0xFFFF'FFFF);

    SECTION("and 1")
    {
        const auto vv = Vector4::MaskAndUInt(v1, v3);
        const auto ex = Vector4::MakeUInt(0xFFFF'FFFF, 0x0000'0000, 0x0000'0000, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
    SECTION("and 2")
    {
        const auto vv = Vector4::MaskAndUInt(v2, v3);
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0xFFFF'FFFF, 0x0000'0000, 0xFFFF'FFFF);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }

    SECTION("andc 1")
    {
        const auto vv = Vector4::MaskAndCUInt(v1, v3);
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0x0000'0000, 0xFFFF'FFFF, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
    SECTION("andc 2")
    {
        const auto vv = Vector4::MaskAndCUInt(v2, v3);
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0x0000'0000, 0x0000'0000, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == false);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == true);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }

    SECTION("or 1")
    {
        const auto vv = Vector4::MaskOrUInt(v1, v3);
        const auto ex = Vector4::MakeUInt(0xFFFF'FFFF, 0xFFFF'FFFF, 0xFFFF'FFFF, 0xFFFF'FFFF);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == false);
        CHECK(Vector4::AllTrue(vv) == true);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
    SECTION("or 2")
    {
        const auto vv = Vector4::MaskOrUInt(v2, v3);
        const auto ex = Vector4::MakeUInt(0xFFFF'FFFF, 0xFFFF'FFFF, 0x0000'0000, 0xFFFF'FFFF);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }

    SECTION("nor 1")
    {
        const auto vv = Vector4::MaskNorUInt(v1, v3);
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0x0000'0000, 0x0000'0000, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == false);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == true);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
    SECTION("nor 2")
    {
        const auto vv = Vector4::MaskNorUInt(v2, v3);
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0x0000'0000, 0xFFFF'FFFF, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }

    SECTION("xor 1")
    {
        const auto vv = Vector4::MaskXorUInt(v1, v3);
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0xFFFF'FFFF, 0xFFFF'FFFF, 0xFFFF'FFFF);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
    SECTION("xor 2")
    {
        const auto vv = Vector4::MaskXorUInt(v2, v3);
        const auto ex = Vector4::MakeUInt(0xFFFF'FFFF, 0x0000'0000, 0x0000'0000, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }

    SECTION("true")
    {
        const auto vv = Vector4::MaskTrue();
        const auto ex = Vector4::MakeUInt(0xFFFF'FFFF, 0xFFFF'FFFF, 0xFFFF'FFFF, 0xFFFF'FFFF);

        CHECK(Vector4::AnyTrue(vv) == true);
        CHECK(Vector4::AnyFalse(vv) == false);
        CHECK(Vector4::AllTrue(vv) == true);
        CHECK(Vector4::AllFalse(vv) == false);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
    SECTION("false")
    {
        const auto vv = Vector4::MaskFalse();
        const auto ex = Vector4::MakeUInt(0x0000'0000, 0x0000'0000, 0x0000'0000, 0x0000'0000);

        CHECK(Vector4::AnyTrue(vv) == false);
        CHECK(Vector4::AnyFalse(vv) == true);
        CHECK(Vector4::AllTrue(vv) == false);
        CHECK(Vector4::AllFalse(vv) == true);

        CHECK(Vector4::IsEqualUInt(vv, ex));
    }
}

TEST_CASE("Math / Vector4 / Common operations", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, 4.0F);
    const auto v2 = Vector4::Make(4.0F, 3.0F, 1.0F, 2.0F);
    const auto v3 = Vector4::Make(5.0F, 1.0F, 2.0F, 6.0F);

    SECTION("Min")
    {
        const auto vv1 = Vector4::Min(v1, v2);
        const auto vv2 = Vector4::Min(v1, v3);
        const auto vv3 = Vector4::Min(v2, v3);

        CHECK(Vector4::GetX(vv1) == Approx(1.0F));
        CHECK(Vector4::GetY(vv1) == Approx(2.0F));
        CHECK(Vector4::GetZ(vv1) == Approx(1.0F));
        CHECK(Vector4::GetW(vv1) == Approx(2.0F));

        CHECK(Vector4::GetX(vv2) == Approx(1.0F));
        CHECK(Vector4::GetY(vv2) == Approx(1.0F));
        CHECK(Vector4::GetZ(vv2) == Approx(2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(4.0F));

        CHECK(Vector4::GetX(vv3) == Approx(4.0F));
        CHECK(Vector4::GetY(vv3) == Approx(1.0F));
        CHECK(Vector4::GetZ(vv3) == Approx(1.0F));
        CHECK(Vector4::GetW(vv3) == Approx(2.0F));
    }

    SECTION("Max")
    {
        const auto vv1 = Vector4::Max(v1, v2);
        const auto vv2 = Vector4::Max(v1, v3);
        const auto vv3 = Vector4::Max(v2, v3);

        CHECK(Vector4::GetX(vv1) == Approx(4.0F));
        CHECK(Vector4::GetY(vv1) == Approx(3.0F));
        CHECK(Vector4::GetZ(vv1) == Approx(3.0F));
        CHECK(Vector4::GetW(vv1) == Approx(4.0F));

        CHECK(Vector4::GetX(vv2) == Approx(5.0F));
        CHECK(Vector4::GetY(vv2) == Approx(2.0F));
        CHECK(Vector4::GetZ(vv2) == Approx(3.0F));
        CHECK(Vector4::GetW(vv2) == Approx(6.0F));

        CHECK(Vector4::GetX(vv3) == Approx(5.0F));
        CHECK(Vector4::GetY(vv3) == Approx(3.0F));
        CHECK(Vector4::GetZ(vv3) == Approx(2.0F));
        CHECK(Vector4::GetW(vv3) == Approx(6.0F));
    }

    SECTION("Quitient operations")
    {
        const auto vsource = Vector4::Make(1.1F, 1.9F, -0.1F, -0.6F);

        const auto vround = Vector4::Round(vsource);

        CHECK(Vector4::GetX(vround) == Approx(1.0F));
        CHECK(Vector4::GetY(vround) == Approx(2.0F));
        CHECK(Vector4::GetZ(vround) == Approx(-0.0F));
        CHECK(Vector4::GetW(vround) == Approx(-1.0F));

        const auto vtruncate = Vector4::Truncate(vsource);

        CHECK(Vector4::GetX(vtruncate) == Approx(1.0F));
        CHECK(Vector4::GetY(vtruncate) == Approx(1.0F));
        CHECK(Vector4::GetZ(vtruncate) == Approx(-0.0F));
        CHECK(Vector4::GetW(vtruncate) == Approx(-0.0F));

        const auto vfloor = Vector4::Floor(vsource);

        CHECK(Vector4::GetX(vfloor) == Approx(1.0F));
        CHECK(Vector4::GetY(vfloor) == Approx(1.0F));
        CHECK(Vector4::GetZ(vfloor) == Approx(-1.0F));
        CHECK(Vector4::GetW(vfloor) == Approx(-1.0F));

        const auto vceil = Vector4::Ceiling(vsource);

        CHECK(Vector4::GetX(vceil) == Approx(2.0F));
        CHECK(Vector4::GetY(vceil) == Approx(2.0F));
        CHECK(Vector4::GetZ(vceil) == Approx(-0.0F));
        CHECK(Vector4::GetW(vceil) == Approx(-0.0F));
    }

    SECTION("Clamping")
    {
        const auto vv1 = Vector4::Clamp(v1, v2, v3);

        CHECK(Vector4::GetX(vv1) == Approx(4.0F));
        CHECK(Vector4::GetY(vv1) == Approx(1.0F));
        CHECK(Vector4::GetZ(vv1) == Approx(2.0F));
        CHECK(Vector4::GetW(vv1) == Approx(4.0F));

        const auto vv2 = Vector4::Clamp(v1, v3, v2);

        CHECK(Vector4::GetX(vv2) == Approx(4.0F));
        CHECK(Vector4::GetY(vv2) == Approx(2.0F));
        CHECK(Vector4::GetZ(vv2) == Approx(1.0F));
        CHECK(Vector4::GetW(vv2) == Approx(2.0F));

        const auto vv3 = Vector4::Clamp(v3, v2, v1);

        CHECK(Vector4::GetX(vv3) == Approx(1.0F));
        CHECK(Vector4::GetY(vv3) == Approx(2.0F));
        CHECK(Vector4::GetZ(vv3) == Approx(2.0F));
        CHECK(Vector4::GetW(vv3) == Approx(4.0F));

        const auto vv4 = Vector4::Clamp(v3, v1, v2);

        CHECK(Vector4::GetX(vv4) == Approx(4.0F));
        CHECK(Vector4::GetY(vv4) == Approx(2.0F));
        CHECK(Vector4::GetZ(vv4) == Approx(1.0F));
        CHECK(Vector4::GetW(vv4) == Approx(2.0F));

        const auto vv5 = Vector4::Clamp(v2, v3, v1);

        CHECK(Vector4::GetX(vv5) == Approx(1.0F));
        CHECK(Vector4::GetY(vv5) == Approx(2.0F));
        CHECK(Vector4::GetZ(vv5) == Approx(2.0F));
        CHECK(Vector4::GetW(vv5) == Approx(4.0F));

        const auto vv6 = Vector4::Clamp(v2, v1, v3);

        CHECK(Vector4::GetX(vv6) == Approx(4.0F));
        CHECK(Vector4::GetY(vv6) == Approx(1.0F));
        CHECK(Vector4::GetZ(vv6) == Approx(2.0F));
        CHECK(Vector4::GetW(vv6) == Approx(4.0F));
    }

    SECTION("Saturate")
    {
        const auto vv = Vector4::Make(-0.5F, 0.5F, 1.1F, std::numeric_limits<float>::infinity());
        const auto vvx = Vector4::Saturate(vv);

        CHECK(Vector4::GetX(vvx) == Approx(0.0F));
        CHECK(Vector4::GetY(vvx) == Approx(0.5F));
        CHECK(Vector4::GetZ(vvx) == Approx(1.0F));
        CHECK(Vector4::GetW(vvx) == Approx(1.0F));
    }
}

TEST_CASE("Math / Vector4 / Arithmetic operations", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, -4.0F);
    const auto v2 = Vector4::Make(4.0F, -3.0F, 1.0F, 2.0F);
    const auto v3 = Vector4::Make(5.0F, 1.0F, -2.0F, 6.0F);

    SECTION("Negate")
    {
        const auto vv1 = Vector4::Negate(v1);

        CHECK(Vector4::GetX(vv1) == Approx(-1.0F));
        CHECK(Vector4::GetY(vv1) == Approx(-2.0F));
        CHECK(Vector4::GetZ(vv1) == Approx(-3.0F));
        CHECK(Vector4::GetW(vv1) == Approx(4.0F));

        const auto vv2 = Vector4::Negate(v2);

        CHECK(Vector4::GetX(vv2) == Approx(-4.0F));
        CHECK(Vector4::GetY(vv2) == Approx(3.0F));
        CHECK(Vector4::GetZ(vv2) == Approx(-1.0F));
        CHECK(Vector4::GetW(vv2) == Approx(-2.0F));

        const auto vv3 = Vector4::Negate(v3);

        CHECK(Vector4::GetX(vv3) == Approx(-5.0F));
        CHECK(Vector4::GetY(vv3) == Approx(-1.0F));
        CHECK(Vector4::GetZ(vv3) == Approx(2.0F));
        CHECK(Vector4::GetW(vv3) == Approx(-6.0F));
    }

    SECTION("Add")
    {
        const auto vv1 = Vector4::Add(v1, v2);

        CHECK(Vector4::GetX(vv1) == Approx( 1.0F +  4.0F));
        CHECK(Vector4::GetY(vv1) == Approx( 2.0F + -3.0F));
        CHECK(Vector4::GetZ(vv1) == Approx( 3.0F +  1.0F));
        CHECK(Vector4::GetW(vv1) == Approx(-4.0F +  2.0F));

        const auto vv2 = Vector4::Add(v1, v3);

        CHECK(Vector4::GetX(vv2) == Approx( 1.0F +  5.0F));
        CHECK(Vector4::GetY(vv2) == Approx( 2.0F +  1.0F));
        CHECK(Vector4::GetZ(vv2) == Approx( 3.0F + -2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(-4.0F +  6.0F));

        const auto vv3 = Vector4::Add(v2, v3);

        CHECK(Vector4::GetX(vv3) == Approx( 4.0F +  5.0F));
        CHECK(Vector4::GetY(vv3) == Approx(-3.0F +  1.0F));
        CHECK(Vector4::GetZ(vv3) == Approx( 1.0F + -2.0F));
        CHECK(Vector4::GetW(vv3) == Approx( 2.0F +  6.0F));
    }

    SECTION("Sum")
    {
        const auto vv1 = Vector4::Sum(v1);

        CHECK(Vector4::GetX(vv1) == Approx(1.0F + 2.0F + 3.0F + -4.0F));
        CHECK(Vector4::GetY(vv1) == Approx(1.0F + 2.0F + 3.0F + -4.0F));
        CHECK(Vector4::GetZ(vv1) == Approx(1.0F + 2.0F + 3.0F + -4.0F));
        CHECK(Vector4::GetW(vv1) == Approx(1.0F + 2.0F + 3.0F + -4.0F));

        const auto vv2 = Vector4::Sum(v2);

        CHECK(Vector4::GetX(vv2) == Approx(4.0F + -3.0F + 1.0F + 2.0F));
        CHECK(Vector4::GetY(vv2) == Approx(4.0F + -3.0F + 1.0F + 2.0F));
        CHECK(Vector4::GetZ(vv2) == Approx(4.0F + -3.0F + 1.0F + 2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(4.0F + -3.0F + 1.0F + 2.0F));

        const auto vv3 = Vector4::Sum(v3);

        CHECK(Vector4::GetX(vv3) == Approx(5.0F + 1.0F + -2.0F + 6.0F));
        CHECK(Vector4::GetY(vv3) == Approx(5.0F + 1.0F + -2.0F + 6.0F));
        CHECK(Vector4::GetZ(vv3) == Approx(5.0F + 1.0F + -2.0F + 6.0F));
        CHECK(Vector4::GetW(vv3) == Approx(5.0F + 1.0F + -2.0F + 6.0F));
    }

    SECTION("Subtract")
    {
        const auto vv1 = Vector4::Subtract(v1, v2);

        CHECK(Vector4::GetX(vv1) == Approx( 1.0F -  4.0F));
        CHECK(Vector4::GetY(vv1) == Approx( 2.0F - -3.0F));
        CHECK(Vector4::GetZ(vv1) == Approx( 3.0F -  1.0F));
        CHECK(Vector4::GetW(vv1) == Approx(-4.0F -  2.0F));

        const auto vv2 = Vector4::Subtract(v1, v3);

        CHECK(Vector4::GetX(vv2) == Approx( 1.0F -  5.0F));
        CHECK(Vector4::GetY(vv2) == Approx( 2.0F -  1.0F));
        CHECK(Vector4::GetZ(vv2) == Approx( 3.0F - -2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(-4.0F -  6.0F));

        const auto vv3 = Vector4::Subtract(v2, v3);

        CHECK(Vector4::GetX(vv3) == Approx( 4.0F -  5.0F));
        CHECK(Vector4::GetY(vv3) == Approx(-3.0F -  1.0F));
        CHECK(Vector4::GetZ(vv3) == Approx( 1.0F - -2.0F));
        CHECK(Vector4::GetW(vv3) == Approx( 2.0F -  6.0F));
    }

    SECTION("Multiply")
    {
        const auto vv1 = Vector4::Multiply(v1, v2);

        CHECK(Vector4::GetX(vv1) == Approx( 1.0F *  4.0F));
        CHECK(Vector4::GetY(vv1) == Approx( 2.0F * -3.0F));
        CHECK(Vector4::GetZ(vv1) == Approx( 3.0F *  1.0F));
        CHECK(Vector4::GetW(vv1) == Approx(-4.0F *  2.0F));

        const auto vv2 = Vector4::Multiply(v1, v3);

        CHECK(Vector4::GetX(vv2) == Approx( 1.0F *  5.0F));
        CHECK(Vector4::GetY(vv2) == Approx( 2.0F *  1.0F));
        CHECK(Vector4::GetZ(vv2) == Approx( 3.0F * -2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(-4.0F *  6.0F));

        const auto vv3 = Vector4::Multiply(v2, v3);

        CHECK(Vector4::GetX(vv3) == Approx( 4.0F *  5.0F));
        CHECK(Vector4::GetY(vv3) == Approx(-3.0F *  1.0F));
        CHECK(Vector4::GetZ(vv3) == Approx( 1.0F * -2.0F));
        CHECK(Vector4::GetW(vv3) == Approx( 2.0F *  6.0F));
    }

    SECTION("Divide")
    {
        const auto vv1 = Vector4::Divide(v1, v2);

        CHECK(Vector4::GetX(vv1) == Approx( 1.0F /  4.0F));
        CHECK(Vector4::GetY(vv1) == Approx( 2.0F / -3.0F));
        CHECK(Vector4::GetZ(vv1) == Approx( 3.0F /  1.0F));
        CHECK(Vector4::GetW(vv1) == Approx(-4.0F /  2.0F));

        const auto vv2 = Vector4::Divide(v1, v3);

        CHECK(Vector4::GetX(vv2) == Approx( 1.0F /  5.0F));
        CHECK(Vector4::GetY(vv2) == Approx( 2.0F /  1.0F));
        CHECK(Vector4::GetZ(vv2) == Approx( 3.0F / -2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(-4.0F /  6.0F));

        const auto vv3 = Vector4::Divide(v2, v3);

        CHECK(Vector4::GetX(vv3) == Approx( 4.0F /  5.0F));
        CHECK(Vector4::GetY(vv3) == Approx(-3.0F /  1.0F));
        CHECK(Vector4::GetZ(vv3) == Approx( 1.0F / -2.0F));
        CHECK(Vector4::GetW(vv3) == Approx( 2.0F /  6.0F));
    }

    SECTION("MultiplyAdd")
    {
        const auto vv1 = Vector4::MultiplyAdd(v1, v2, v3);

        CHECK(Vector4::GetX(vv1) == Approx( 1.0F *  4.0F +  5.0F));
        CHECK(Vector4::GetY(vv1) == Approx( 2.0F * -3.0F +  1.0F));
        CHECK(Vector4::GetZ(vv1) == Approx( 3.0F *  1.0F + -2.0F));
        CHECK(Vector4::GetW(vv1) == Approx(-4.0F *  2.0F +  6.0F));

        const auto vv2 = Vector4::MultiplyAdd(v2, v3, v1);

        CHECK(Vector4::GetX(vv2) == Approx( 4.0F *  5.0F +  1.0F));
        CHECK(Vector4::GetY(vv2) == Approx(-3.0F *  1.0F +  2.0F));
        CHECK(Vector4::GetZ(vv2) == Approx( 1.0F * -2.0F +  3.0F));
        CHECK(Vector4::GetW(vv2) == Approx( 2.0F *  6.0F + -4.0F));

        const auto vv3 = Vector4::MultiplyAdd(v3, v1, v2);

        CHECK(Vector4::GetX(vv3) == Approx( 5.0F *  1.0F +  4.0F));
        CHECK(Vector4::GetY(vv3) == Approx( 1.0F *  2.0F + -3.0F));
        CHECK(Vector4::GetZ(vv3) == Approx(-2.0F *  3.0F +  1.0F));
        CHECK(Vector4::GetW(vv3) == Approx( 6.0F * -4.0F +  2.0F));
    }

    SECTION("NegativeMultiplySubtract")
    {
        const auto vv1 = Vector4::NegativeMultiplySubtract(v1, v2, v3);

        CHECK(Vector4::GetX(vv1) == Approx( 5.0F -  1.0F *  4.0F));
        CHECK(Vector4::GetY(vv1) == Approx( 1.0F -  2.0F * -3.0F));
        CHECK(Vector4::GetZ(vv1) == Approx(-2.0F -  3.0F *  1.0F));
        CHECK(Vector4::GetW(vv1) == Approx( 6.0F - -4.0F *  2.0F));

        const auto vv2 = Vector4::NegativeMultiplySubtract(v2, v3, v1);

        CHECK(Vector4::GetX(vv2) == Approx( 1.0F -  4.0F *  5.0F));
        CHECK(Vector4::GetY(vv2) == Approx( 2.0F - -3.0F *  1.0F));
        CHECK(Vector4::GetZ(vv2) == Approx( 3.0F -  1.0F * -2.0F));
        CHECK(Vector4::GetW(vv2) == Approx(-4.0F -  2.0F *  6.0F));

        const auto vv3 = Vector4::NegativeMultiplySubtract(v3, v1, v2);

        CHECK(Vector4::GetX(vv3) == Approx( 4.0F -  5.0F *  1.0F));
        CHECK(Vector4::GetY(vv3) == Approx(-3.0F -  1.0F *  2.0F));
        CHECK(Vector4::GetZ(vv3) == Approx( 1.0F - -2.0F *  3.0F));
        CHECK(Vector4::GetW(vv3) == Approx( 2.0F -  6.0F * -4.0F));
    }

    SECTION("Scale")
    {
        const auto vv1 = Vector4::Scale(v1, 0.5F);

        CHECK(Vector4::GetX(vv1) == Approx( 1.0F * 0.5F));
        CHECK(Vector4::GetY(vv1) == Approx( 2.0F * 0.5F));
        CHECK(Vector4::GetZ(vv1) == Approx( 3.0F * 0.5F));
        CHECK(Vector4::GetW(vv1) == Approx(-4.0F * 0.5F));

        const auto vv2 = Vector4::Scale(v2, 1.5F);

        CHECK(Vector4::GetX(vv2) == Approx( 4.0F * 1.5F));
        CHECK(Vector4::GetY(vv2) == Approx(-3.0F * 1.5F));
        CHECK(Vector4::GetZ(vv2) == Approx( 1.0F * 1.5F));
        CHECK(Vector4::GetW(vv2) == Approx( 2.0F * 1.5F));

        const auto vv3 = Vector4::Scale(v3, -0.5F);

        CHECK(Vector4::GetX(vv3) == Approx( 5.0F * -0.5F));
        CHECK(Vector4::GetY(vv3) == Approx( 1.0F * -0.5F));
        CHECK(Vector4::GetZ(vv3) == Approx(-2.0F * -0.5F));
        CHECK(Vector4::GetW(vv3) == Approx( 6.0F * -0.5F));
    }
}

#include <random>

TEST_CASE("Math / Vector4 / Standard functions", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    std::ranlux48 generator{ 0xdeadc0dedeadbeef };
    std::uniform_real_distribution<float> sampler{};

    std::uniform_real_distribution<float>::param_type range_small{ 0.0001F, 1.0F };
    std::uniform_real_distribution<float>::param_type range_large{ 1.0F, 10.0F };

    SECTION("Reciprocal")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);

            auto v = Vector4::Make(x, y, z, w);

            auto vr1 = Vector4::ReciprocalEst(v);

            CHECK(Vector4::GetX(vr1) == Approx(1.0F / x).epsilon(0.001F));
            CHECK(Vector4::GetY(vr1) == Approx(1.0F / y).epsilon(0.0005F));
            CHECK(Vector4::GetZ(vr1) == Approx(1.0F / z).epsilon(0.001F));
            CHECK(Vector4::GetW(vr1) == Approx(1.0F / w).epsilon(0.0005F));

            auto vr2 = Vector4::Reciprocal(v);

            CHECK(Vector4::GetX(vr2) == Approx(1.0F / x));
            CHECK(Vector4::GetY(vr2) == Approx(1.0F / y));
            CHECK(Vector4::GetZ(vr2) == Approx(1.0F / z));
            CHECK(Vector4::GetW(vr2) == Approx(1.0F / w));
        }

        auto v = Vector4::Make(-1.0F, -0.0F, +0.0F, +1.0F);

        auto vr3 = Vector4::ReciprocalEst(v);

        CHECK(Vector4::GetX(vr3) == Approx(-1.0F).epsilon(0.001F));
        CHECK(std::isinf(Vector4::GetY(vr3)));
        CHECK(std::isinf(Vector4::GetZ(vr3)));
        CHECK(Vector4::GetW(vr3) == Approx(1.0F).epsilon(0.001F));

        auto vr4 = Vector4::Reciprocal(v);

        CHECK(Vector4::GetX(vr4) == Approx(-1.0F));
        CHECK(std::isinf(Vector4::GetY(vr4)));
        CHECK(std::isinf(Vector4::GetZ(vr4)));
        CHECK(Vector4::GetW(vr4) == Approx(1.0F));
    }

    SECTION("Sqrt")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);

            auto v = Vector4::Make(x, y, z, w);

            auto vr1 = Vector4::SqrtEst(v);

            CHECK(Vector4::GetX(vr1) == Approx(std::sqrt(x)).epsilon(0.001F));
            CHECK(Vector4::GetY(vr1) == Approx(std::sqrt(y)).epsilon(0.001F));
            CHECK(std::isnan(Vector4::GetZ(vr1)));
            CHECK(std::isnan(Vector4::GetW(vr1)));

            auto vr2 = Vector4::Sqrt(v);

            CHECK(Vector4::GetX(vr2) == Approx(std::sqrt(x)).epsilon(0.001F));
            CHECK(Vector4::GetY(vr2) == Approx(std::sqrt(y)).epsilon(0.001F));
            CHECK(std::isnan(Vector4::GetZ(vr2)));
            CHECK(std::isnan(Vector4::GetW(vr2)));
        }

        auto v = Vector4::Make(-1.0F, -0.0F, +0.0F, +1.0F);

        auto vr3 = Vector4::SqrtEst(v);

        CHECK(std::isnan(Vector4::GetX(vr3)));
        CHECK(Vector4::GetY(vr3) == Approx(-0.0F));
        CHECK(Vector4::GetZ(vr3) == Approx(0.0F));
        CHECK(Vector4::GetW(vr3) == Approx(1.0F));

        auto vr4 = Vector4::Sqrt(v);

        CHECK(std::isnan(Vector4::GetX(vr4)));
        CHECK(Vector4::GetY(vr4) == Approx(-0.0F));
        CHECK(Vector4::GetZ(vr4) == Approx(0.0F));
        CHECK(Vector4::GetW(vr4) == Approx(1.0F));
    }

    SECTION("ReciprocalSqrt")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);

            auto v = Vector4::Make(x, y, z, w);

            auto vr1 = Vector4::ReciprocalSqrtEst(v);

            CHECK(Vector4::GetX(vr1) == Approx(1.0F / std::sqrt(x)).epsilon(0.001F));
            CHECK(Vector4::GetY(vr1) == Approx(1.0F / std::sqrt(y)).epsilon(0.001F));
            CHECK(std::isnan(Vector4::GetZ(vr1)));
            CHECK(std::isnan(Vector4::GetW(vr1)));

            auto vr2 = Vector4::ReciprocalSqrt(v);

            CHECK(Vector4::GetX(vr2) == Approx(1.0F / std::sqrt(x)).epsilon(0.001F));
            CHECK(Vector4::GetY(vr2) == Approx(1.0F / std::sqrt(y)).epsilon(0.001F));
            CHECK(std::isnan(Vector4::GetZ(vr2)));
            CHECK(std::isnan(Vector4::GetW(vr2)));
        }

        auto v = Vector4::Make(-1.0F, -0.0F, +0.0F, +1.0F);

        auto vr3 = Vector4::ReciprocalSqrtEst(v);

        CHECK(std::isnan(Vector4::GetX(vr3)));
        CHECK(std::isinf(Vector4::GetY(vr3)));
        CHECK(std::isinf(Vector4::GetZ(vr3)));
        CHECK(Vector4::GetW(vr3) == Approx(1.0F).epsilon(0.001F));

        auto vr4 = Vector4::ReciprocalSqrt(v);

        CHECK(std::isnan(Vector4::GetX(vr4)));
        CHECK(std::isinf(Vector4::GetY(vr4)));
        CHECK(std::isinf(Vector4::GetZ(vr4)));
        CHECK(Vector4::GetW(vr4) == Approx(1.0F));
    }

    SECTION("Exp")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);


            auto v = Vector4::Make(x, y, z, w);

            auto v_exp_2 = Vector4::Exp2(v);
            auto v_exp_e = Vector4::ExpE(v);
            auto v_exp = Vector4::Exp(v);

            CHECK(Vector4::GetX(v_exp_2) == Approx(std::exp2(x)));
            CHECK(Vector4::GetY(v_exp_2) == Approx(std::exp2(y)));
            CHECK(Vector4::GetZ(v_exp_2) == Approx(std::exp2(z)));
            CHECK(Vector4::GetW(v_exp_2) == Approx(std::exp2(w)));

            CHECK(Vector4::GetX(v_exp_e) == Approx(std::exp(x)));
            CHECK(Vector4::GetY(v_exp_e) == Approx(std::exp(y)));
            CHECK(Vector4::GetZ(v_exp_e) == Approx(std::exp(z)));
            CHECK(Vector4::GetW(v_exp_e) == Approx(std::exp(w)));

            CHECK(Vector4::GetX(v_exp) == Approx(std::exp2(x)));
            CHECK(Vector4::GetY(v_exp) == Approx(std::exp2(y)));
            CHECK(Vector4::GetZ(v_exp) == Approx(std::exp2(z)));
            CHECK(Vector4::GetW(v_exp) == Approx(std::exp2(w)));
        }

        auto x = -1.0F;
        auto y = -0.0F;
        auto z = +0.0F;
        auto w = +1.0F;

        auto v = Vector4::Make(x, y, z, w);

        auto v_exp_2 = Vector4::Exp2(v);

        CHECK(Vector4::GetX(v_exp_2) == Approx(std::exp2(x)));
        CHECK(Vector4::GetY(v_exp_2) == Approx(std::exp2(y)));
        CHECK(Vector4::GetZ(v_exp_2) == Approx(std::exp2(z)));
        CHECK(Vector4::GetW(v_exp_2) == Approx(std::exp2(w)));

        auto v_exp_e = Vector4::ExpE(v);

        CHECK(Vector4::GetX(v_exp_e) == Approx(std::exp(x)));
        CHECK(Vector4::GetY(v_exp_e) == Approx(std::exp(y)));
        CHECK(Vector4::GetZ(v_exp_e) == Approx(std::exp(z)));
        CHECK(Vector4::GetW(v_exp_e) == Approx(std::exp(w)));

        auto v_exp = Vector4::Exp(v);

        CHECK(Vector4::GetX(v_exp) == Approx(std::exp2(x)));
        CHECK(Vector4::GetY(v_exp) == Approx(std::exp2(y)));
        CHECK(Vector4::GetZ(v_exp) == Approx(std::exp2(z)));
        CHECK(Vector4::GetW(v_exp) == Approx(std::exp2(w)));
    }

    SECTION("Exp")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);


            auto v = Vector4::Make(x, y, z, w);

            auto v_log_2 = Vector4::Log2(v);
            auto v_log_e = Vector4::LogE(v);
            auto v_log = Vector4::Log(v);

            CHECK(Vector4::GetX(v_log_2) == Approx(std::log2(x)).epsilon(0.0005F));
            CHECK(Vector4::GetY(v_log_2) == Approx(std::log2(y)).epsilon(0.0005F));
            CHECK(std::isnan(Vector4::GetZ(v_log_2)));
            CHECK(std::isnan(Vector4::GetW(v_log_2)));

            CHECK(Vector4::GetX(v_log_e) == Approx(std::log(x)).epsilon(0.0005F));
            CHECK(Vector4::GetY(v_log_e) == Approx(std::log(y)).epsilon(0.0005F));
            CHECK(std::isnan(Vector4::GetZ(v_log_e)));
            CHECK(std::isnan(Vector4::GetW(v_log_e)));

            CHECK(Vector4::GetX(v_log) == Approx(std::log2(x)).epsilon(0.0005F));
            CHECK(Vector4::GetY(v_log) == Approx(std::log2(y)).epsilon(0.0005F));
            CHECK(std::isnan(Vector4::GetZ(v_log)));
            CHECK(std::isnan(Vector4::GetW(v_log)));
        }

        auto x = -1.0F;
        auto y = -0.0F;
        auto z = +0.0F;
        auto w = +1.0F;

        auto v = Vector4::Make(x, y, z, w);

        auto v_log_2 = Vector4::Log2(v);

        CHECK(std::isnan(Vector4::GetX(v_log_2)));
        CHECK(std::isinf(Vector4::GetY(v_log_2)));
        CHECK(std::isinf(Vector4::GetZ(v_log_2)));
        CHECK(Vector4::GetW(v_log_2) == Approx(std::log2(w)));

        auto v_log_e = Vector4::LogE(v);

        CHECK(std::isnan(Vector4::GetX(v_log_e)));
        CHECK(std::isinf(Vector4::GetY(v_log_e)));
        CHECK(std::isinf(Vector4::GetZ(v_log_e)));
        CHECK(Vector4::GetW(v_log_e) == Approx(std::log(w)));

        auto v_log = Vector4::Log(v);

        CHECK(std::isnan(Vector4::GetX(v_log)));
        CHECK(std::isinf(Vector4::GetY(v_log)));
        CHECK(std::isinf(Vector4::GetZ(v_log)));
        CHECK(Vector4::GetW(v_log) == Approx(std::log2(w)));
    }

    SECTION("Pow")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);

            auto v1 = Vector4::Make(x, y, z, w);
            auto v2 = Vector4::Make(w, y, x, z);

            auto v_pow_1 = Vector4::Pow(v1, v2);
            auto v_pow_2 = Vector4::Pow(v2, v1);
            auto v_pow_3 = Vector4::Pow(v1, v1);

            CHECK(Vector4::GetX(v_pow_1) == Approx(std::pow(x, w)));
            CHECK(Vector4::GetY(v_pow_1) == Approx(std::pow(y, y)));
            CHECK(std::isnan(Vector4::GetZ(v_pow_1)));
            CHECK(std::isnan(Vector4::GetW(v_pow_1)));

            CHECK(std::isnan(Vector4::GetX(v_pow_2)));
            CHECK(Vector4::GetY(v_pow_2) == Approx(std::pow(y, y)));
            CHECK(Vector4::GetZ(v_pow_2) == Approx(std::pow(x, z)));
            CHECK(std::isnan(Vector4::GetW(v_pow_2)));

            CHECK(Vector4::GetX(v_pow_3) == Approx(std::pow(x, x)));
            CHECK(Vector4::GetY(v_pow_3) == Approx(std::pow(y, y)));
            CHECK(std::isnan(Vector4::GetZ(v_pow_3)));
            CHECK(std::isnan(Vector4::GetW(v_pow_3)));
        }

        auto x = -1.0F;
        auto y = -0.0F;
        auto z = +0.0F;
        auto w = +1.0F;

        auto v1 = Vector4::Make(x, y, z, w);
        auto v2 = Vector4::Make(w, y, x, z);

        auto v_pow_1 = Vector4::Pow(v1, v2);
        auto v_pow_2 = Vector4::Pow(v2, v1);
        auto v_pow_3 = Vector4::Pow(v1, v1);

        CHECK(Vector4::GetX(v_pow_1) == Approx(std::pow(x, w)));
        CHECK(Vector4::GetY(v_pow_1) == Approx(std::pow(y, y)));
        CHECK(std::isinf(Vector4::GetZ(v_pow_1)));
        CHECK(Vector4::GetW(v_pow_1) == Approx(std::pow(w, z)));

        CHECK(Vector4::GetX(v_pow_2) == Approx(std::pow(w, x)));
        CHECK(Vector4::GetY(v_pow_2) == Approx(std::pow(y, y)));
        CHECK(Vector4::GetZ(v_pow_2) == Approx(std::pow(x, z)));
        CHECK(Vector4::GetW(v_pow_2) == Approx(std::pow(z, w)));

        CHECK(Vector4::GetX(v_pow_3) == Approx(std::pow(x, x)));
        CHECK(Vector4::GetY(v_pow_3) == Approx(std::pow(y, y)));
        CHECK(Vector4::GetZ(v_pow_3) == Approx(std::pow(z, z)));
        CHECK(Vector4::GetW(v_pow_3) == Approx(std::pow(w, w)));
    }

    SECTION("Abs")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);

            auto v = Vector4::Make(x, y, z, w);

            auto vv = Vector4::Abs(v);

            CHECK(Vector4::GetX(vv) == Approx(std::abs(x)));
            CHECK(Vector4::GetY(vv) == Approx(std::abs(y)));
            CHECK(Vector4::GetZ(vv) == Approx(std::abs(z)));
            CHECK(Vector4::GetW(vv) == Approx(std::abs(w)));
        }
    }

    SECTION("Mod")
    {
        for (size_t i = 0; i < 50; ++i)
        {
            float x = sampler(generator, range_small);
            float y = sampler(generator, range_large);
            float z = -sampler(generator, range_small);
            float w = -sampler(generator, range_large);

            auto v1 = Vector4::Make(x, y, z, w);
            auto v2 = Vector4::Make(w, y, x, z);

            auto v_mod_1 = Vector4::Mod(v1, v2);
            auto v_mod_2 = Vector4::Mod(v2, v1);
            auto v_mod_3 = Vector4::Mod(v1, v1);

            CHECK(Vector4::GetX(v_mod_1) == Approx(fmodf(x, w)).epsilon(0.001F));
            CHECK(Vector4::GetY(v_mod_1) == Approx(fmodf(y, y)).epsilon(0.001F));
            CHECK(Vector4::GetZ(v_mod_1) == Approx(fmodf(z, x)).epsilon(0.001F));
            CHECK(Vector4::GetW(v_mod_1) == Approx(fmodf(w, z)).epsilon(0.001F));

            CHECK(Vector4::GetX(v_mod_2) == Approx(fmodf(w, x)).epsilon(0.001F));
            CHECK(Vector4::GetY(v_mod_2) == Approx(fmodf(y, y)).epsilon(0.001F));
            CHECK(Vector4::GetZ(v_mod_2) == Approx(fmodf(x, z)).epsilon(0.001F));
            CHECK(Vector4::GetW(v_mod_2) == Approx(fmodf(z, w)).epsilon(0.001F));

            CHECK(Vector4::GetX(v_mod_3) == Approx(fmodf(x, x)).epsilon(0.001F));
            CHECK(Vector4::GetY(v_mod_3) == Approx(fmodf(y, y)).epsilon(0.001F));
            CHECK(Vector4::GetZ(v_mod_3) == Approx(fmodf(z, z)).epsilon(0.001F));
            CHECK(Vector4::GetW(v_mod_3) == Approx(fmodf(w, w)).epsilon(0.001F));
        }

        auto x = -1.0F;
        auto y = -0.0F;
        auto z = +0.0F;
        auto w = +1.0F;

        auto v1 = Vector4::Make(x, y, z, w);
        auto v2 = Vector4::Make(w, y, x, z);

        auto v_mod_1 = Vector4::Mod(v1, v2);
        auto v_mod_2 = Vector4::Mod(v2, v1);
        auto v_mod_3 = Vector4::Mod(v1, v1);

        CHECK(Vector4::GetX(v_mod_1) == Approx(fmodf(x, w)).epsilon(0.001F));
        CHECK(std::isnan(Vector4::GetY(v_mod_1)));
        CHECK(Vector4::GetZ(v_mod_1) == Approx(fmodf(z, x)).epsilon(0.001F));
        CHECK(std::isnan(Vector4::GetW(v_mod_1)));

        CHECK(Vector4::GetX(v_mod_2) == Approx(fmodf(w, x)).epsilon(0.001F));
        CHECK(std::isnan(Vector4::GetY(v_mod_2)));
        CHECK(std::isnan(Vector4::GetZ(v_mod_2)));
        CHECK(Vector4::GetW(v_mod_2) == Approx(fmodf(z, w)).epsilon(0.001F));

        CHECK(Vector4::GetX(v_mod_3) == Approx(fmodf(x, x)).epsilon(0.001F));
        CHECK(std::isnan(Vector4::GetY(v_mod_3)));
        CHECK(std::isnan(Vector4::GetZ(v_mod_3)));
        CHECK(Vector4::GetW(v_mod_3) == Approx(fmodf(w, w)).epsilon(0.001F));
    }
}

TEST_CASE("Math / Vector4 / Trigonometric", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    SECTION("Sin / Cos")
    {
        const auto range_begin = -Graphyte::Maths::PI2<float>;
        const auto range_end = Graphyte::Maths::PI2<float>;
        const auto range_increment = 0.01F;
        const auto fmargin = 0.000001F;
        const auto fmargin_est = 0.00001F;

        for (auto a = range_begin; a <= range_end; a += range_increment)
        {
            const auto x = -PI<float> +a;
            const auto y = -ONE_OVER_PI<float> +a;
            const auto z = PI_OVER_6<float> +a;
            const auto w = ONE_OVER_PI2<float> +a;

            auto v = Vector4::Make(x, y, z, w);

            auto vsin = Vector4::Sin(v);

            CHECK(Vector4::GetX(vsin) == Approx(std::sin(x)).margin(fmargin));
            CHECK(Vector4::GetY(vsin) == Approx(std::sin(y)).margin(fmargin));
            CHECK(Vector4::GetZ(vsin) == Approx(std::sin(z)).margin(fmargin));
            CHECK(Vector4::GetW(vsin) == Approx(std::sin(w)).margin(fmargin));

            auto vcos = Vector4::Cos(v);

            CHECK(Vector4::GetX(vcos) == Approx(std::cos(x)).margin(fmargin));
            CHECK(Vector4::GetY(vcos) == Approx(std::cos(y)).margin(fmargin));
            CHECK(Vector4::GetZ(vcos) == Approx(std::cos(z)).margin(fmargin));
            CHECK(Vector4::GetW(vcos) == Approx(std::cos(w)).margin(fmargin));

            Vector4 vsinout{};
            Vector4 vcosout{};

            Vector4::SinCos(&vsinout, &vcosout, v);

            CHECK(Vector4::GetX(vsinout) == Approx(std::sin(x)).margin(fmargin));
            CHECK(Vector4::GetY(vsinout) == Approx(std::sin(y)).margin(fmargin));
            CHECK(Vector4::GetZ(vsinout) == Approx(std::sin(z)).margin(fmargin));
            CHECK(Vector4::GetW(vsinout) == Approx(std::sin(w)).margin(fmargin));

            CHECK(Vector4::GetX(vcosout) == Approx(std::cos(x)).margin(fmargin));
            CHECK(Vector4::GetY(vcosout) == Approx(std::cos(y)).margin(fmargin));
            CHECK(Vector4::GetZ(vcosout) == Approx(std::cos(z)).margin(fmargin));
            CHECK(Vector4::GetW(vcosout) == Approx(std::cos(w)).margin(fmargin));


            //
            // Estimated functions.
            //

            vsin = Vector4::SinEst(v);

            CHECK(Vector4::GetX(vsin) == Approx(std::sin(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vsin) == Approx(std::sin(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vsin) == Approx(std::sin(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vsin) == Approx(std::sin(w)).margin(fmargin_est));

            vcos = Vector4::CosEst(v);

            CHECK(Vector4::GetX(vcos) == Approx(std::cos(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vcos) == Approx(std::cos(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vcos) == Approx(std::cos(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vcos) == Approx(std::cos(w)).margin(fmargin_est));

            Vector4::SinCosEst(&vsinout, &vcosout, v);

            CHECK(Vector4::GetX(vsinout) == Approx(std::sin(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vsinout) == Approx(std::sin(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vsinout) == Approx(std::sin(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vsinout) == Approx(std::sin(w)).margin(fmargin_est));

            CHECK(Vector4::GetX(vcosout) == Approx(std::cos(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vcosout) == Approx(std::cos(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vcosout) == Approx(std::cos(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vcosout) == Approx(std::cos(w)).margin(fmargin_est));

            auto vsinh = Vector4::SinH(v);

            CHECK(Vector4::GetX(vsinh) == Approx(std::sinh(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vsinh) == Approx(std::sinh(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vsinh) == Approx(std::sinh(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vsinh) == Approx(std::sinh(w)).margin(fmargin_est));

            auto vcosh = Vector4::CosH(v);

            CHECK(Vector4::GetX(vcosh) == Approx(std::cosh(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vcosh) == Approx(std::cosh(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vcosh) == Approx(std::cosh(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vcosh) == Approx(std::cosh(w)).margin(fmargin_est));
        }
    }

    SECTION("ASin / ACos")
    {
        const auto range_begin = 0.0F;
        const auto range_end = 1.0F;
        const auto range_increment = 0.001F;
        const auto fmargin = 0.000001F;
        const auto fmargin_est = 0.0001F;

        for (auto a = range_begin; a <= range_end; a += range_increment)
        {
            const auto x = fmodf(PI<float> +a, 1.0F) * 2.0F - 1.0F;
            const auto y = fmodf(ONE_OVER_PI<float> +a, 1.0F) * 2.0F - 1.0F;
            const auto z = fmodf(PI_OVER_6<float> +a, 1.0F) * 2.0F - 1.0F;
            const auto w = fmodf(ONE_OVER_PI2<float> +a, 1.0F) * 2.0F - 1.0F;

            auto v = Vector4::Make(x, y, z, w);

            auto vsin = Vector4::ASin(v);

            CHECK(Vector4::GetX(vsin) == Approx(std::asin(x)).margin(fmargin));
            CHECK(Vector4::GetY(vsin) == Approx(std::asin(y)).margin(fmargin));
            CHECK(Vector4::GetZ(vsin) == Approx(std::asin(z)).margin(fmargin));
            CHECK(Vector4::GetW(vsin) == Approx(std::asin(w)).margin(fmargin));

            auto vcos = Vector4::ACos(v);

            CHECK(Vector4::GetX(vcos) == Approx(std::acos(x)).margin(fmargin));
            CHECK(Vector4::GetY(vcos) == Approx(std::acos(y)).margin(fmargin));
            CHECK(Vector4::GetZ(vcos) == Approx(std::acos(z)).margin(fmargin));
            CHECK(Vector4::GetW(vcos) == Approx(std::acos(w)).margin(fmargin));


            //
            // Estimated functions.
            //

            vsin = Vector4::ASinEst(v);

            CHECK(Vector4::GetX(vsin) == Approx(std::asin(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vsin) == Approx(std::asin(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vsin) == Approx(std::asin(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vsin) == Approx(std::asin(w)).margin(fmargin_est));

            vcos = Vector4::ACosEst(v);

            CHECK(Vector4::GetX(vcos) == Approx(std::acos(x)).margin(fmargin_est));
            CHECK(Vector4::GetY(vcos) == Approx(std::acos(y)).margin(fmargin_est));
            CHECK(Vector4::GetZ(vcos) == Approx(std::acos(z)).margin(fmargin_est));
            CHECK(Vector4::GetW(vcos) == Approx(std::acos(w)).margin(fmargin_est));
        }
    }

    SECTION("Tan / ATan")
    {
        const auto fmargin = 0.0005F;
        const auto fmargin_est = 0.005F;

        auto v1 = Vector4::Make(-1.0F, -0.0F, +0.0F, 1.0F);
        auto v2 = Vector4::Make(0.5F, -0.5F, -0.25F, +0.25F);

        auto v_tan_1 = Vector4::Tan(v1);

        CHECK(Vector4::GetX(v_tan_1) == Approx(std::tan(Vector4::GetX(v1))).margin(fmargin));
        CHECK(Vector4::GetY(v_tan_1) == Approx(std::tan(Vector4::GetY(v1))).margin(fmargin));
        CHECK(Vector4::GetZ(v_tan_1) == Approx(std::tan(Vector4::GetZ(v1))).margin(fmargin));
        CHECK(Vector4::GetW(v_tan_1) == Approx(std::tan(Vector4::GetW(v1))).margin(fmargin));

        auto v_tan_2 = Vector4::Tan(v2);

        CHECK(Vector4::GetX(v_tan_2) == Approx(std::tan(Vector4::GetX(v2))).margin(fmargin));
        CHECK(Vector4::GetY(v_tan_2) == Approx(std::tan(Vector4::GetY(v2))).margin(fmargin));
        CHECK(Vector4::GetZ(v_tan_2) == Approx(std::tan(Vector4::GetZ(v2))).margin(fmargin));
        CHECK(Vector4::GetW(v_tan_2) == Approx(std::tan(Vector4::GetW(v2))).margin(fmargin));

        auto v_tan_est_1 = Vector4::TanEst(v1);

        CHECK(Vector4::GetX(v_tan_est_1) == Approx(std::tan(Vector4::GetX(v1))).margin(fmargin_est));
        CHECK(Vector4::GetY(v_tan_est_1) == Approx(std::tan(Vector4::GetY(v1))).margin(fmargin_est));
        CHECK(Vector4::GetZ(v_tan_est_1) == Approx(std::tan(Vector4::GetZ(v1))).margin(fmargin_est));
        CHECK(Vector4::GetW(v_tan_est_1) == Approx(std::tan(Vector4::GetW(v1))).margin(fmargin_est));

        auto v_tan_est_2 = Vector4::TanEst(v2);

        CHECK(Vector4::GetX(v_tan_est_2) == Approx(std::tan(Vector4::GetX(v2))).margin(fmargin_est));
        CHECK(Vector4::GetY(v_tan_est_2) == Approx(std::tan(Vector4::GetY(v2))).margin(fmargin_est));
        CHECK(Vector4::GetZ(v_tan_est_2) == Approx(std::tan(Vector4::GetZ(v2))).margin(fmargin_est));
        CHECK(Vector4::GetW(v_tan_est_2) == Approx(std::tan(Vector4::GetW(v2))).margin(fmargin_est));

        auto v_tanh_1 = Vector4::TanH(v1);

        CHECK(Vector4::GetX(v_tanh_1) == Approx(std::tanh(Vector4::GetX(v1))).margin(fmargin));
        CHECK(Vector4::GetY(v_tanh_1) == Approx(std::tanh(Vector4::GetY(v1))).margin(fmargin));
        CHECK(Vector4::GetZ(v_tanh_1) == Approx(std::tanh(Vector4::GetZ(v1))).margin(fmargin));
        CHECK(Vector4::GetW(v_tanh_1) == Approx(std::tanh(Vector4::GetW(v1))).margin(fmargin));

        auto v_tanh_2 = Vector4::TanH(v2);

        CHECK(Vector4::GetX(v_tanh_2) == Approx(std::tanh(Vector4::GetX(v2))).margin(fmargin));
        CHECK(Vector4::GetY(v_tanh_2) == Approx(std::tanh(Vector4::GetY(v2))).margin(fmargin));
        CHECK(Vector4::GetZ(v_tanh_2) == Approx(std::tanh(Vector4::GetZ(v2))).margin(fmargin));
        CHECK(Vector4::GetW(v_tanh_2) == Approx(std::tanh(Vector4::GetW(v2))).margin(fmargin));

        auto v_atan_1 = Vector4::ATan(v1);

        CHECK(Vector4::GetX(v_atan_1) == Approx(std::atan(Vector4::GetX(v1))).margin(fmargin));
        CHECK(Vector4::GetY(v_atan_1) == Approx(std::atan(Vector4::GetY(v1))).margin(fmargin));
        CHECK(Vector4::GetZ(v_atan_1) == Approx(std::atan(Vector4::GetZ(v1))).margin(fmargin));
        CHECK(Vector4::GetW(v_atan_1) == Approx(std::atan(Vector4::GetW(v1))).margin(fmargin));

        auto v_atan_2 = Vector4::ATan(v2);

        CHECK(Vector4::GetX(v_atan_2) == Approx(std::atan(Vector4::GetX(v2))).margin(fmargin));
        CHECK(Vector4::GetY(v_atan_2) == Approx(std::atan(Vector4::GetY(v2))).margin(fmargin));
        CHECK(Vector4::GetZ(v_atan_2) == Approx(std::atan(Vector4::GetZ(v2))).margin(fmargin));
        CHECK(Vector4::GetW(v_atan_2) == Approx(std::atan(Vector4::GetW(v2))).margin(fmargin));

        auto v_atan_est_1 = Vector4::ATanEst(v1);

        CHECK(Vector4::GetX(v_atan_est_1) == Approx(std::atan(Vector4::GetX(v1))).margin(fmargin_est));
        CHECK(Vector4::GetY(v_atan_est_1) == Approx(std::atan(Vector4::GetY(v1))).margin(fmargin_est));
        CHECK(Vector4::GetZ(v_atan_est_1) == Approx(std::atan(Vector4::GetZ(v1))).margin(fmargin_est));
        CHECK(Vector4::GetW(v_atan_est_1) == Approx(std::atan(Vector4::GetW(v1))).margin(fmargin_est));

        auto v_atan_est_2 = Vector4::ATanEst(v2);

        CHECK(Vector4::GetX(v_atan_est_2) == Approx(std::atan(Vector4::GetX(v2))).margin(fmargin_est));
        CHECK(Vector4::GetY(v_atan_est_2) == Approx(std::atan(Vector4::GetY(v2))).margin(fmargin_est));
        CHECK(Vector4::GetZ(v_atan_est_2) == Approx(std::atan(Vector4::GetZ(v2))).margin(fmargin_est));
        CHECK(Vector4::GetW(v_atan_est_2) == Approx(std::atan(Vector4::GetW(v2))).margin(fmargin_est));

        auto v_atan2_1 = Vector4::ATan2(v1, v2);

        CHECK(Vector4::GetX(v_atan2_1) == Approx(std::atan2(Vector4::GetX(v1), Vector4::GetX(v2))).margin(fmargin));
        CHECK(Vector4::GetY(v_atan2_1) == Approx(std::atan2(Vector4::GetY(v1), Vector4::GetY(v2))).margin(fmargin));
        CHECK(Vector4::GetZ(v_atan2_1) == Approx(std::atan2(Vector4::GetZ(v1), Vector4::GetZ(v2))).margin(fmargin));
        CHECK(Vector4::GetW(v_atan2_1) == Approx(std::atan2(Vector4::GetW(v1), Vector4::GetW(v2))).margin(fmargin));

        auto v_atan2_2 = Vector4::ATan2(v2, v1);

        CHECK(Vector4::GetX(v_atan2_2) == Approx(std::atan2(Vector4::GetX(v2), Vector4::GetX(v1))).margin(fmargin));
        CHECK(Vector4::GetY(v_atan2_2) == Approx(std::atan2(Vector4::GetY(v2), Vector4::GetY(v1))).margin(fmargin));
        CHECK(Vector4::GetZ(v_atan2_2) == Approx(std::atan2(Vector4::GetZ(v2), Vector4::GetZ(v1))).margin(fmargin));
        CHECK(Vector4::GetW(v_atan2_2) == Approx(std::atan2(Vector4::GetW(v2), Vector4::GetW(v1))).margin(fmargin));

        auto v_atan2_est_1 = Vector4::ATan2Est(v1, v2);

        CHECK(Vector4::GetX(v_atan2_est_1) == Approx(std::atan2(Vector4::GetX(v1), Vector4::GetX(v2))).margin(fmargin));
        CHECK(Vector4::GetY(v_atan2_est_1) == Approx(std::atan2(Vector4::GetY(v1), Vector4::GetY(v2))).margin(fmargin));
        CHECK(Vector4::GetZ(v_atan2_est_1) == Approx(std::atan2(Vector4::GetZ(v1), Vector4::GetZ(v2))).margin(fmargin));
        CHECK(Vector4::GetW(v_atan2_est_1) == Approx(std::atan2(Vector4::GetW(v1), Vector4::GetW(v2))).margin(fmargin));

        auto v_atan2_est_2 = Vector4::ATan2Est(v2, v1);

        CHECK(Vector4::GetX(v_atan2_est_2) == Approx(std::atan2(Vector4::GetX(v2), Vector4::GetX(v1))).margin(fmargin_est));
        CHECK(Vector4::GetY(v_atan2_est_2) == Approx(std::atan2(Vector4::GetY(v2), Vector4::GetY(v1))).margin(fmargin_est));
        CHECK(Vector4::GetZ(v_atan2_est_2) == Approx(std::atan2(Vector4::GetZ(v2), Vector4::GetZ(v1))).margin(fmargin_est));
        CHECK(Vector4::GetW(v_atan2_est_2) == Approx(std::atan2(Vector4::GetW(v2), Vector4::GetW(v1))).margin(fmargin_est));
    }
}

TEST_CASE("Math / Vector4 / Interpolation", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto p0 = Vector4::Make(-1.0F, 1.0F, 2.0F, 3.0F);
    const auto p1 = Vector4::Make(-2.0F, 2.0F, 3.0F, 4.0F);
    const auto p2 = Vector4::Make(1.0F, -2.0F, -3.0F, 2.0F);
    const auto p3 = Vector4::Make(2.0F, -1.0F, 3.0F, 1.0F);

    SECTION("Lerp")
    {
        const auto t_0_00 = Vector4::Lerp(p0, p3, 0.0F);
        const auto t_0_25 = Vector4::Lerp(p0, p3, 0.25F);
        const auto t_0_50 = Vector4::Lerp(p0, p3, 0.5F);
        const auto t_0_75 = Vector4::Lerp(p0, p3, 0.75F);
        const auto t_1_00 = Vector4::Lerp(p0, p3, 1.0F);

        CHECK(Vector4::GetX(t_0_00) == Approx(-1.0F));
        CHECK(Vector4::GetY(t_0_00) == Approx( 1.0F));
        CHECK(Vector4::GetZ(t_0_00) == Approx( 2.0F));
        CHECK(Vector4::GetW(t_0_00) == Approx( 3.0F));

        CHECK(Vector4::GetX(t_0_25) == Approx(-0.25F));
        CHECK(Vector4::GetY(t_0_25) == Approx(0.5F));
        CHECK(Vector4::GetZ(t_0_25) == Approx(2.25F));
        CHECK(Vector4::GetW(t_0_25) == Approx(2.5F));

        CHECK(Vector4::GetX(t_0_50) == Approx(0.5F));
        CHECK(Vector4::GetY(t_0_50) == Approx(0.0F));
        CHECK(Vector4::GetZ(t_0_50) == Approx(2.5F));
        CHECK(Vector4::GetW(t_0_50) == Approx(2.0F));

        CHECK(Vector4::GetX(t_0_75) == Approx(1.25F));
        CHECK(Vector4::GetY(t_0_75) == Approx(-0.5F));
        CHECK(Vector4::GetZ(t_0_75) == Approx(2.75F));
        CHECK(Vector4::GetW(t_0_75) == Approx(1.5F));

        CHECK(Vector4::GetX(t_1_00) == Approx(2.0F));
        CHECK(Vector4::GetY(t_1_00) == Approx(-1.0F));
        CHECK(Vector4::GetZ(t_1_00) == Approx(3.0F));
        CHECK(Vector4::GetW(t_1_00) == Approx(1.0F));
    }

    SECTION("Hermite")
    {
        const auto t_0_00 = Vector4::Hermite(p0, p1, p2, p3, 0.0F);
        const auto t_0_25 = Vector4::Hermite(p0, p1, p2, p3, 0.25F);
        const auto t_0_50 = Vector4::Hermite(p0, p1, p2, p3, 0.5F);
        const auto t_0_75 = Vector4::Hermite(p0, p1, p2, p3, 0.75F);
        const auto t_1_00 = Vector4::Hermite(p0, p1, p2, p3, 1.0F);

        CHECK(Vector4::GetX(t_0_00) == Approx(-1.0F));
        CHECK(Vector4::GetY(t_0_00) == Approx(1.0F));
        CHECK(Vector4::GetZ(t_0_00) == Approx(2.0F));
        CHECK(Vector4::GetW(t_0_00) == Approx(3.0F));

        CHECK(Vector4::GetX(t_0_25) == Approx(-1.0625F));
        CHECK(Vector4::GetY(t_0_25) == Approx(0.85938F));
        CHECK(Vector4::GetZ(t_0_25) == Approx(1.5F));
        CHECK(Vector4::GetW(t_0_25) == Approx(3.35938F));

        CHECK(Vector4::GetX(t_0_50) == Approx(-0.5F));
        CHECK(Vector4::GetY(t_0_50) == Approx(-0.125F));
        CHECK(Vector4::GetZ(t_0_50) == Approx(-0.5F));
        CHECK(Vector4::GetW(t_0_50) == Approx(2.875F));

        CHECK(Vector4::GetX(t_0_75) == Approx(0.3125F));
        CHECK(Vector4::GetY(t_0_75) == Approx(-1.29688F));
        CHECK(Vector4::GetZ(t_0_75) == Approx(-2.5F));
        CHECK(Vector4::GetW(t_0_75) == Approx(2.20313F));

        CHECK(Vector4::GetX(t_1_00) == Approx(1.0F));
        CHECK(Vector4::GetY(t_1_00) == Approx(-2.0F));
        CHECK(Vector4::GetZ(t_1_00) == Approx(-3.0F));
        CHECK(Vector4::GetW(t_1_00) == Approx(2.0F));
    }

    SECTION("CatmullRom")
    {
        const auto t_0_00 = Vector4::CatmullRom(p0, p1, p2, p3, 0.0F);
        const auto t_0_25 = Vector4::CatmullRom(p0, p1, p2, p3, 0.25F);
        const auto t_0_50 = Vector4::CatmullRom(p0, p1, p2, p3, 0.5F);
        const auto t_0_75 = Vector4::CatmullRom(p0, p1, p2, p3, 0.75F);
        const auto t_1_00 = Vector4::CatmullRom(p0, p1, p2, p3, 1.0F);

        CHECK(Vector4::GetX(t_0_00) == Approx(-2.0F));
        CHECK(Vector4::GetY(t_0_00) == Approx(2.0F));
        CHECK(Vector4::GetZ(t_0_00) == Approx(3.0F));
        CHECK(Vector4::GetW(t_0_00) == Approx(4.0F));

        CHECK(Vector4::GetX(t_0_25) == Approx(-1.48438F));
        CHECK(Vector4::GetY(t_0_25) == Approx(1.23438F));
        CHECK(Vector4::GetZ(t_0_25) == Approx(1.71094F));
        CHECK(Vector4::GetW(t_0_25) == Approx(3.6875F));

        CHECK(Vector4::GetX(t_0_50) == Approx(-0.625F));
        CHECK(Vector4::GetY(t_0_50) == Approx(0.0F));
        CHECK(Vector4::GetZ(t_0_50) == Approx(-0.3125F));
        CHECK(Vector4::GetW(t_0_50) == Approx(3.125F));

        CHECK(Vector4::GetX(t_0_75) == Approx(0.296875F));
        CHECK(Vector4::GetY(t_0_75) == Approx(-1.23438F));
        CHECK(Vector4::GetZ(t_0_75) == Approx(-2.17969F));
        CHECK(Vector4::GetW(t_0_75) == Approx(2.5F));

        CHECK(Vector4::GetX(t_1_00) == Approx(1.0F));
        CHECK(Vector4::GetY(t_1_00) == Approx(-2.0F));
        CHECK(Vector4::GetZ(t_1_00) == Approx(-3.0F));
        CHECK(Vector4::GetW(t_1_00) == Approx(2.0F));
    }

    SECTION("Barycentric")
    {
        const auto t_0_00 = Vector4::Barycentric(p0, p1, p3, 0.0F, 0.0F);
        const auto t_0_25 = Vector4::Barycentric(p0, p1, p3, 0.25F, 0.75F);
        const auto t_0_50 = Vector4::Barycentric(p0, p1, p3, 0.5F, 0.5F);
        const auto t_0_75 = Vector4::Barycentric(p0, p1, p3, 0.75F, 0.25F);
        const auto t_1_00 = Vector4::Barycentric(p0, p1, p3, 1.0F, 1.0F);

        CHECK(Vector4::GetX(t_0_00) == Approx(-1.0F));
        CHECK(Vector4::GetY(t_0_00) == Approx(1.0F));
        CHECK(Vector4::GetZ(t_0_00) == Approx(2.0F));
        CHECK(Vector4::GetW(t_0_00) == Approx(3.0F));

        CHECK(Vector4::GetX(t_0_25) == Approx(1.0F));
        CHECK(Vector4::GetY(t_0_25) == Approx(-0.25F));
        CHECK(Vector4::GetZ(t_0_25) == Approx(3.0F));
        CHECK(Vector4::GetW(t_0_25) == Approx(1.75F));

        CHECK(Vector4::GetX(t_0_50) == Approx(0.0F));
        CHECK(Vector4::GetY(t_0_50) == Approx(0.5F));
        CHECK(Vector4::GetZ(t_0_50) == Approx(3.0F));
        CHECK(Vector4::GetW(t_0_50) == Approx(2.5F));

        CHECK(Vector4::GetX(t_0_75) == Approx(-1.0F));
        CHECK(Vector4::GetY(t_0_75) == Approx(1.25F));
        CHECK(Vector4::GetZ(t_0_75) == Approx(3.0F));
        CHECK(Vector4::GetW(t_0_75) == Approx(3.25F));

        CHECK(Vector4::GetX(t_1_00) == Approx(1.0F));
        CHECK(Vector4::GetY(t_1_00) == Approx(0.0F));
        CHECK(Vector4::GetZ(t_1_00) == Approx(4.0F));
        CHECK(Vector4::GetW(t_1_00) == Approx(2.0F));
    }
}

TEST_CASE("Math / Vector4 / Vector4 Specific operations", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, -4.0F);
    const auto v2 = Vector4::Make(4.0F, -3.0F, 1.0F, 2.0F);
    const auto v3 = Vector4::Make(5.0F, 1.0F, -2.0F, 6.0F);

    SECTION("Dot")
    {
        const auto dot_1 = Vector4::Dot(Vector4::UnitX(), Vector4::UnitY());
        CHECK(Vector4::GetX(dot_1) == Vector4::GetY(dot_1));
        CHECK(Vector4::GetX(dot_1) == Vector4::GetZ(dot_1));
        CHECK(Vector4::GetX(dot_1) == Vector4::GetW(dot_1));
        CHECK(Vector4::GetX(dot_1) == Approx(0.0F));

        const auto dot_2 = Vector4::Dot(Vector4::UnitX(), Vector4::UnitX());
        CHECK(Vector4::GetX(dot_2) == Vector4::GetY(dot_2));
        CHECK(Vector4::GetX(dot_2) == Vector4::GetZ(dot_2));
        CHECK(Vector4::GetX(dot_2) == Vector4::GetW(dot_2));
        CHECK(Vector4::GetX(dot_2) == Approx(1.0F));

        const auto dot_3 = Vector4::Dot(v1, v2);
        CHECK(Vector4::GetX(dot_3) == Vector4::GetY(dot_3));
        CHECK(Vector4::GetX(dot_3) == Vector4::GetZ(dot_3));
        CHECK(Vector4::GetX(dot_3) == Vector4::GetW(dot_3));
        CHECK(Vector4::GetX(dot_3) == Approx(-7.0F));
    }

    SECTION("Cross")
    {
        const auto cross_1 = Vector4::Cross(Vector4::UnitX(), Vector4::UnitY(), Vector4::UnitZ());
        CHECK(Vector4::GetX(cross_1) == Approx(0.0F));
        CHECK(Vector4::GetY(cross_1) == Approx(0.0F));
        CHECK(Vector4::GetZ(cross_1) == Approx(0.0F));
        CHECK(Vector4::GetW(cross_1) == Approx(-1.0F));

        const auto cross_2 = Vector4::Cross(v1, v2, v3);
        CHECK(Vector4::GetX(cross_2) == Approx(60.0F));
        CHECK(Vector4::GetY(cross_2) == Approx(-20.0F));
        CHECK(Vector4::GetZ(cross_2) == Approx(-124.0F));
        CHECK(Vector4::GetW(cross_2) == Approx(-88.0F));
    }

    SECTION("Lengths")
    {
        SECTION("Length")
        {
            const auto len_1 = Vector4::Length(v1);
            CHECK(Vector4::GetX(len_1) == Vector4::GetY(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetZ(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetW(len_1));
            CHECK(Vector4::GetX(len_1) == Approx(5.47722578F));

            const auto len_2 = Vector4::Length(v2);
            CHECK(Vector4::GetX(len_2) == Vector4::GetY(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetZ(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetW(len_2));
            CHECK(Vector4::GetX(len_2) == Approx(5.47722578F));

            const auto len_3 = Vector4::Length(v3);
            CHECK(Vector4::GetX(len_3) == Vector4::GetY(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetZ(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetW(len_3));
            CHECK(Vector4::GetX(len_3) == Approx(8.12403870F));

            const auto len_4 = Vector4::Length(Vector4::UnitZ());
            CHECK(Vector4::GetX(len_4) == Vector4::GetY(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetZ(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetW(len_4));
            CHECK(Vector4::GetX(len_4) == Approx(1.0F));

            const auto len_5 = Vector4::Length(Vector4::Zero());
            CHECK(Vector4::GetX(len_5) == Vector4::GetY(len_5));
            CHECK(Vector4::GetX(len_5) == Vector4::GetZ(len_5));
            CHECK(Vector4::GetX(len_5) == Vector4::GetW(len_5));
            CHECK(Vector4::GetX(len_5) == Approx(0.0F));

            const auto len_6 = Vector4::Length(Vector4::One());
            CHECK(Vector4::GetX(len_6) == Vector4::GetY(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetZ(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetW(len_6));
            CHECK(Vector4::GetX(len_6) == Approx(2.0F));

            const auto len_7 = Vector4::Length(Vector4::Infinity());
            CHECK(std::isinf(Vector4::GetX(len_7)));
            CHECK(std::isinf(Vector4::GetY(len_7)));
            CHECK(std::isinf(Vector4::GetZ(len_7)));
            CHECK(std::isinf(Vector4::GetW(len_7)));

            const auto len_8 = Vector4::Length(Vector4::NaN());
            CHECK(std::isnan(Vector4::GetX(len_8)));
            CHECK(std::isnan(Vector4::GetY(len_8)));
            CHECK(std::isnan(Vector4::GetZ(len_8)));
            CHECK(std::isnan(Vector4::GetW(len_8)));
        }

        SECTION("LengthEst")
        {
            const auto len_1 = Vector4::LengthEst(v1);
            CHECK(Vector4::GetX(len_1) == Vector4::GetY(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetZ(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetW(len_1));
            CHECK(Vector4::GetX(len_1) == Approx(5.47722578F));

            const auto len_2 = Vector4::LengthEst(v2);
            CHECK(Vector4::GetX(len_2) == Vector4::GetY(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetZ(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetW(len_2));
            CHECK(Vector4::GetX(len_2) == Approx(5.47722578F));

            const auto len_3 = Vector4::LengthEst(v3);
            CHECK(Vector4::GetX(len_3) == Vector4::GetY(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetZ(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetW(len_3));
            CHECK(Vector4::GetX(len_3) == Approx(8.12403870F));

            const auto len_4 = Vector4::LengthEst(Vector4::UnitZ());
            CHECK(Vector4::GetX(len_4) == Vector4::GetY(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetZ(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetW(len_4));
            CHECK(Vector4::GetX(len_4) == Approx(1.0F));

            const auto len_5 = Vector4::LengthEst(Vector4::Zero());
            CHECK(Vector4::GetX(len_5) == Vector4::GetY(len_5));
            CHECK(Vector4::GetX(len_5) == Vector4::GetZ(len_5));
            CHECK(Vector4::GetX(len_5) == Vector4::GetW(len_5));
            CHECK(Vector4::GetX(len_5) == Approx(0.0F));

            const auto len_6 = Vector4::LengthEst(Vector4::One());
            CHECK(Vector4::GetX(len_6) == Vector4::GetY(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetZ(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetW(len_6));
            CHECK(Vector4::GetX(len_6) == Approx(2.0F));

            const auto len_7 = Vector4::LengthEst(Vector4::Infinity());
            CHECK(std::isinf(Vector4::GetX(len_7)));
            CHECK(std::isinf(Vector4::GetY(len_7)));
            CHECK(std::isinf(Vector4::GetZ(len_7)));
            CHECK(std::isinf(Vector4::GetW(len_7)));

            const auto len_8 = Vector4::LengthEst(Vector4::NaN());
            CHECK(std::isnan(Vector4::GetX(len_8)));
            CHECK(std::isnan(Vector4::GetY(len_8)));
            CHECK(std::isnan(Vector4::GetZ(len_8)));
            CHECK(std::isnan(Vector4::GetW(len_8)));
        }

        SECTION("LengthSquared")
        {
            const auto len_1 = Vector4::LengthSquared(v1);
            CHECK(Vector4::GetX(len_1) == Vector4::GetY(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetZ(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetW(len_1));
            CHECK(Vector4::GetX(len_1) == Approx(30.0F));

            const auto len_2 = Vector4::LengthSquared(v2);
            CHECK(Vector4::GetX(len_2) == Vector4::GetY(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetZ(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetW(len_2));
            CHECK(Vector4::GetX(len_2) == Approx(30.0F));

            const auto len_3 = Vector4::LengthSquared(v3);
            CHECK(Vector4::GetX(len_3) == Vector4::GetY(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetZ(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetW(len_3));
            CHECK(Vector4::GetX(len_3) == Approx(66.0F));

            const auto len_4 = Vector4::LengthSquared(Vector4::UnitZ());
            CHECK(Vector4::GetX(len_4) == Vector4::GetY(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetZ(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetW(len_4));
            CHECK(Vector4::GetX(len_4) == Approx(1.0F));

            const auto len_5 = Vector4::LengthSquared(Vector4::Zero());
            CHECK(Vector4::GetX(len_5) == Vector4::GetY(len_5));
            CHECK(Vector4::GetX(len_5) == Vector4::GetZ(len_5));
            CHECK(Vector4::GetX(len_5) == Vector4::GetW(len_5));
            CHECK(Vector4::GetX(len_5) == Approx(0.0F));

            const auto len_6 = Vector4::LengthSquared(Vector4::One());
            CHECK(Vector4::GetX(len_6) == Vector4::GetY(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetZ(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetW(len_6));
            CHECK(Vector4::GetX(len_6) == Approx(4.0F));

            const auto len_7 = Vector4::LengthSquared(Vector4::Infinity());
            CHECK(std::isinf(Vector4::GetX(len_7)));
            CHECK(std::isinf(Vector4::GetY(len_7)));
            CHECK(std::isinf(Vector4::GetZ(len_7)));
            CHECK(std::isinf(Vector4::GetW(len_7)));

            const auto len_8 = Vector4::LengthSquared(Vector4::NaN());
            CHECK(std::isnan(Vector4::GetX(len_8)));
            CHECK(std::isnan(Vector4::GetY(len_8)));
            CHECK(std::isnan(Vector4::GetZ(len_8)));
            CHECK(std::isnan(Vector4::GetW(len_8)));
        }

        SECTION("ReciprocalLengthEst")
        {
            const auto len_1 = Vector4::ReciprocalLengthEst(v1);
            CHECK(Vector4::GetX(len_1) == Vector4::GetY(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetZ(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetW(len_1));
            CHECK(Vector4::GetX(len_1) == Approx(0.18257F).margin(0.001F));

            const auto len_2 = Vector4::ReciprocalLengthEst(v2);
            CHECK(Vector4::GetX(len_2) == Vector4::GetY(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetZ(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetW(len_2));
            CHECK(Vector4::GetX(len_2) == Approx(0.18257F).margin(0.001F));

            const auto len_3 = Vector4::ReciprocalLengthEst(v3);
            CHECK(Vector4::GetX(len_3) == Vector4::GetY(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetZ(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetW(len_3));
            CHECK(Vector4::GetX(len_3) == Approx(0.12309F).margin(0.001F));

            const auto len_4 = Vector4::ReciprocalLengthEst(Vector4::UnitZ());
            CHECK(Vector4::GetX(len_4) == Vector4::GetY(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetZ(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetW(len_4));
            CHECK(Vector4::GetX(len_4) == Approx(1.0F).margin(0.001F));

            const auto len_5 = Vector4::ReciprocalLengthEst(Vector4::Zero());
            CHECK(std::isinf(Vector4::GetX(len_5)));
            CHECK(std::isinf(Vector4::GetY(len_5)));
            CHECK(std::isinf(Vector4::GetZ(len_5)));
            CHECK(std::isinf(Vector4::GetW(len_5)));

            const auto len_6 = Vector4::ReciprocalLengthEst(Vector4::One());
            CHECK(Vector4::GetX(len_6) == Vector4::GetY(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetZ(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetW(len_6));
            CHECK(Vector4::GetX(len_6) == Approx(0.5F).margin(0.001F));

            const auto len_7 = Vector4::ReciprocalLengthEst(Vector4::Infinity());
            CHECK(Vector4::GetX(len_7) == Vector4::GetY(len_7));
            CHECK(Vector4::GetX(len_7) == Vector4::GetZ(len_7));
            CHECK(Vector4::GetX(len_7) == Vector4::GetW(len_7));
            CHECK(Vector4::GetX(len_7) == Approx(0.0F));

            const auto len_8 = Vector4::ReciprocalLengthEst(Vector4::NaN());
            CHECK(std::isnan(Vector4::GetX(len_8)));
            CHECK(std::isnan(Vector4::GetY(len_8)));
            CHECK(std::isnan(Vector4::GetZ(len_8)));
            CHECK(std::isnan(Vector4::GetW(len_8)));
        }

        SECTION("ReciprocalLength")
        {
            const auto len_1 = Vector4::ReciprocalLength(v1);
            CHECK(Vector4::GetX(len_1) == Vector4::GetY(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetZ(len_1));
            CHECK(Vector4::GetX(len_1) == Vector4::GetW(len_1));
            CHECK(Vector4::GetX(len_1) == Approx(0.182574183F));

            const auto len_2 = Vector4::ReciprocalLength(v2);
            CHECK(Vector4::GetX(len_2) == Vector4::GetY(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetZ(len_2));
            CHECK(Vector4::GetX(len_2) == Vector4::GetW(len_2));
            CHECK(Vector4::GetX(len_2) == Approx(0.182574183F));

            const auto len_3 = Vector4::ReciprocalLength(v3);
            CHECK(Vector4::GetX(len_3) == Vector4::GetY(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetZ(len_3));
            CHECK(Vector4::GetX(len_3) == Vector4::GetW(len_3));
            CHECK(Vector4::GetX(len_3) == Approx(0.123091489F));

            const auto len_4 = Vector4::ReciprocalLength(Vector4::UnitZ());
            CHECK(Vector4::GetX(len_4) == Vector4::GetY(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetZ(len_4));
            CHECK(Vector4::GetX(len_4) == Vector4::GetW(len_4));
            CHECK(Vector4::GetX(len_4) == Approx(1.0F));

            const auto len_5 = Vector4::ReciprocalLength(Vector4::Zero());
            CHECK(std::isinf(Vector4::GetX(len_5)));
            CHECK(std::isinf(Vector4::GetY(len_5)));
            CHECK(std::isinf(Vector4::GetZ(len_5)));
            CHECK(std::isinf(Vector4::GetW(len_5)));

            const auto len_6 = Vector4::ReciprocalLength(Vector4::One());
            CHECK(Vector4::GetX(len_6) == Vector4::GetY(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetZ(len_6));
            CHECK(Vector4::GetX(len_6) == Vector4::GetW(len_6));
            CHECK(Vector4::GetX(len_6) == Approx(0.5F));

            const auto len_7 = Vector4::ReciprocalLength(Vector4::Infinity());
            CHECK(Vector4::GetX(len_7) == Vector4::GetY(len_7));
            CHECK(Vector4::GetX(len_7) == Vector4::GetZ(len_7));
            CHECK(Vector4::GetX(len_7) == Vector4::GetW(len_7));
            CHECK(Vector4::GetX(len_7) == Approx(0.0F));

            const auto len_8 = Vector4::ReciprocalLength(Vector4::NaN());
            CHECK(std::isnan(Vector4::GetX(len_8)));
            CHECK(std::isnan(Vector4::GetY(len_8)));
            CHECK(std::isnan(Vector4::GetZ(len_8)));
            CHECK(std::isnan(Vector4::GetW(len_8)));
        }

        SECTION("Normalize")
        {
            const auto n1 = Vector4::Normalize(v1);
            CHECK(Vector4::GetX(n1) == Approx(0.18257F).margin(0.001F));
            CHECK(Vector4::GetY(n1) == Approx(0.36515F).margin(0.001F));
            CHECK(Vector4::GetZ(n1) == Approx(0.54772F).margin(0.001F));
            CHECK(Vector4::GetW(n1) == Approx(-0.7303F).margin(0.001F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n1)) == Approx(1.0F));

            const auto n2 = Vector4::Normalize(v2);
            CHECK(Vector4::GetX(n2) == Approx(0.7303F).margin(0.001F));
            CHECK(Vector4::GetY(n2) == Approx(-0.54772F).margin(0.001F));
            CHECK(Vector4::GetZ(n2) == Approx(0.18257F).margin(0.001F));
            CHECK(Vector4::GetW(n2) == Approx(0.36515F).margin(0.001F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n2)) == Approx(1.0F));

            const auto n3 = Vector4::Normalize(v3);
            CHECK(Vector4::GetX(n3) == Approx(0.61546F).margin(0.001F));
            CHECK(Vector4::GetY(n3) == Approx(0.12309F).margin(0.001F));
            CHECK(Vector4::GetZ(n3) == Approx(-0.24618F).margin(0.001F));
            CHECK(Vector4::GetW(n3) == Approx(0.73855F).margin(0.001F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n3)) == Approx(1.0F));

            const auto n4 = Vector4::Normalize(Vector4::Zero());
            CHECK(Vector4::GetX(n4) == Approx(0.0F).margin(0.001F));
            CHECK(Vector4::GetY(n4) == Approx(0.0F).margin(0.001F));
            CHECK(Vector4::GetZ(n4) == Approx(0.0F).margin(0.001F));
            CHECK(Vector4::GetW(n4) == Approx(0.0F).margin(0.001F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n4)) == Approx(0.0F));

            const auto n5 = Vector4::Normalize(Vector4::Infinity());
            CHECK(std::isnan(Vector4::GetX(n5)));
            CHECK(std::isnan(Vector4::GetY(n5)));
            CHECK(std::isnan(Vector4::GetZ(n5)));
            CHECK(std::isnan(Vector4::GetW(n5)));
            CHECK(std::isnan(Vector4::GetX(Vector4::LengthSquared(n5))));

            const auto n6 = Vector4::Normalize(Vector4::NaN());
            CHECK(std::isnan(Vector4::GetX(n6)));
            CHECK(std::isnan(Vector4::GetY(n6)));
            CHECK(std::isnan(Vector4::GetZ(n6)));
            CHECK(std::isnan(Vector4::GetW(n6)));
            CHECK(std::isnan(Vector4::GetX(Vector4::LengthSquared(n6))));

            const auto n7 = Vector4::Normalize(Vector4::UnitX());
            CHECK(Vector4::GetX(n7) == Approx(1.0F));
            CHECK(Vector4::GetY(n7) == Approx(0.0F));
            CHECK(Vector4::GetZ(n7) == Approx(0.0F));
            CHECK(Vector4::GetW(n7) == Approx(0.0F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n7)) == Approx(1.0F));

            const auto n8 = Vector4::Normalize(Vector4::UnitY());
            CHECK(Vector4::GetX(n8) == Approx(0.0F));
            CHECK(Vector4::GetY(n8) == Approx(1.0F));
            CHECK(Vector4::GetZ(n8) == Approx(0.0F));
            CHECK(Vector4::GetW(n8) == Approx(0.0F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n8)) == Approx(1.0F));

            const auto n9 = Vector4::Normalize(Vector4::UnitZ());
            CHECK(Vector4::GetX(n9) == Approx(0.0F));
            CHECK(Vector4::GetY(n9) == Approx(0.0F));
            CHECK(Vector4::GetZ(n9) == Approx(1.0F));
            CHECK(Vector4::GetW(n9) == Approx(0.0F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(n9)) == Approx(1.0F));

            const auto nA = Vector4::Normalize(Vector4::UnitW());
            CHECK(Vector4::GetX(nA) == Approx(0.0F));
            CHECK(Vector4::GetY(nA) == Approx(0.0F));
            CHECK(Vector4::GetZ(nA) == Approx(0.0F));
            CHECK(Vector4::GetW(nA) == Approx(1.0F));
            CHECK(Vector4::GetX(Vector4::LengthSquared(nA)) == Approx(1.0F));
        }

        SECTION("ClampLength")
        {
            const auto n1 = Vector4::ClampLength(v1, 0.1F, 0.6F);
            CHECK(Vector4::GetX(n1) == Approx(0.10954F).margin(0.001F));
            CHECK(Vector4::GetY(n1) == Approx(0.21909F));
            CHECK(Vector4::GetZ(n1) == Approx(0.32863F));
            CHECK(Vector4::GetW(n1) == Approx(-0.43818F));
            CHECK(Vector4::GetX(Vector4::Length(n1)) == Approx(0.6F));

            const auto n2 = Vector4::ClampLength(v2, 0.5F, 14.9F);
            CHECK(Vector4::GetX(n2) == Approx(4.0F).margin(0.001F));
            CHECK(Vector4::GetY(n2) == Approx(-3.0F));
            CHECK(Vector4::GetZ(n2) == Approx(1.0F));
            CHECK(Vector4::GetW(n2) == Approx(2.0F));
            CHECK(Vector4::GetX(Vector4::Length(n2)) == Approx(5.47723F).margin(0.001F));

            const auto n3 = Vector4::ClampLength(v3, 10.1F, 18.4F);
            CHECK(Vector4::GetX(n3) == Approx(6.21612F));
            CHECK(Vector4::GetY(n3) == Approx(1.24322F));
            CHECK(Vector4::GetZ(n3) == Approx(-2.48645F));
            CHECK(Vector4::GetW(n3) == Approx(7.45934F));
            CHECK(Vector4::GetX(Vector4::Length(n3)) == Approx(10.1F));
        }
    }

    SECTION("Refract & reflect")
    {
        /*
        static Vector4 mathcall Reflect(Vector4 incident, Vector4 normal) noexcept;
        static Vector4 mathcall Refract(Vector4 incident, Vector4 normal, float refraction_index) noexcept;
        static Vector4 mathcall Refract(Vector4 incident, Vector4 normal, Vector4 refraction_index) noexcept;
        */
    }

    SECTION("Orthogonals")
    {
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::UnitX()), Vector4::NegativeUnitZ(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::UnitY()), Vector4::NegativeUnitW(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::UnitZ()), Vector4::UnitX(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::UnitW()), Vector4::UnitY(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::NegativeUnitX()), Vector4::UnitZ(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::NegativeUnitY()), Vector4::UnitW(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::NegativeUnitZ()), Vector4::NegativeUnitX(), Vector4::Epsilon()));
        CHECK(Vector4::IsEqual(Vector4::Orthogonal(Vector4::NegativeUnitW()), Vector4::NegativeUnitY(), Vector4::Epsilon()));
    }

    SECTION("Angles")
    {
        SECTION("Normals / Angles is splatted / X / Y")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitX(), Vector4::UnitY());
            CHECK(Vector4::GetX(a) == Vector4::GetY(a));
            CHECK(Vector4::GetX(a) == Vector4::GetZ(a));
            CHECK(Vector4::GetX(a) == Vector4::GetW(a));
            CHECK(Vector4::GetX(a) == Approx(PI_OVER_2<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitX(), Vector4::UnitY());
            CHECK(Vector4::GetX(b) == Vector4::GetY(b));
            CHECK(Vector4::GetX(b) == Vector4::GetZ(b));
            CHECK(Vector4::GetX(b) == Vector4::GetW(b));
            CHECK(Vector4::GetX(b) == Approx(PI_OVER_2<float>).margin(0.001F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitX(), Vector4::UnitY());
            CHECK(Vector4::GetX(c) == Vector4::GetY(c));
            CHECK(Vector4::GetX(c) == Vector4::GetZ(c));
            CHECK(Vector4::GetX(c) == Vector4::GetW(c));
            CHECK(Vector4::GetX(c) == Approx(PI_OVER_2<float>));
        }

        SECTION("Normals / X / X")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitX(), Vector4::UnitX());
            CHECK(Vector4::GetX(a) == Approx(0.0F));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitX(), Vector4::UnitX());
            CHECK(Vector4::GetX(b) == Approx(0.0F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitX(), Vector4::UnitX());
            CHECK(Vector4::GetX(c) == Approx(0.0F));
        }

        SECTION("Normals / X / Z")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitX(), Vector4::UnitZ());
            CHECK(Vector4::GetX(a) == Approx(PI_OVER_2<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitX(), Vector4::UnitZ());
            CHECK(Vector4::GetX(b) == Approx(PI_OVER_2<float>).margin(0.001F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitX(), Vector4::UnitZ());
            CHECK(Vector4::GetX(c) == Approx(PI_OVER_2<float>));

        }

        SECTION("Normals / X / W")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitX(), Vector4::UnitW());
            CHECK(Vector4::GetX(a) == Approx(PI_OVER_2<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitX(), Vector4::UnitW());
            CHECK(Vector4::GetX(b) == Approx(PI_OVER_2<float>).margin(0.001F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitX(), Vector4::UnitW());
            CHECK(Vector4::GetX(c) == Approx(PI_OVER_2<float>));
        }

        SECTION("Normals / Y / X")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitY(), Vector4::UnitX());
            CHECK(Vector4::GetX(a) == Approx(PI_OVER_2<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitY(), Vector4::UnitX());
            CHECK(Vector4::GetX(b) == Approx(PI_OVER_2<float>).margin(0.001F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitY(), Vector4::UnitX());
            CHECK(Vector4::GetX(c) == Approx(PI_OVER_2<float>));
        }

        SECTION("Normals / Z / X")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitZ(), Vector4::UnitX());
            CHECK(Vector4::GetX(a) == Approx(PI_OVER_2<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitZ(), Vector4::UnitX());
            CHECK(Vector4::GetX(b) == Approx(PI_OVER_2<float>).margin(0.001F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitZ(), Vector4::UnitX());
            CHECK(Vector4::GetX(c) == Approx(PI_OVER_2<float>));
        }

        SECTION("Normals / Z / W")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitZ(), Vector4::UnitW());
            CHECK(Vector4::GetX(a) == Approx(PI_OVER_2<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitZ(), Vector4::UnitW());
            CHECK(Vector4::GetX(b) == Approx(PI_OVER_2<float>).margin(0.001F));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitZ(), Vector4::UnitW());
            CHECK(Vector4::GetX(c) == Approx(PI_OVER_2<float>));
        }

        SECTION("Normals / Z / -Z")
        {
            const auto a = Vector4::AngleBetweenNormals(Vector4::UnitZ(), Vector4::NegativeUnitZ());
            CHECK(Vector4::GetX(a) == Approx(PI<float>));

            const auto b = Vector4::AngleBetweenNormalsEst(Vector4::UnitZ(), Vector4::NegativeUnitZ());
            CHECK(Vector4::GetX(b) == Approx(PI<float>));

            const auto c = Vector4::AngleBetweenVectors(Vector4::UnitZ(), Vector4::NegativeUnitZ());
            CHECK(Vector4::GetX(c) == Approx(PI<float>));
        }
    }

    SECTION("Transforms")
    {
        auto m = Matrix::Translation(1.0F, 2.0F, 3.0F);
        auto v = Vector4::Make(3.0F, 2.0F, 1.0F, 1.0F);
        auto vt = Vector4::Transform(v, m);

        CHECK(Vector4::GetX(vt) == Approx(4.0F));
        CHECK(Vector4::GetY(vt) == Approx(4.0F));
        CHECK(Vector4::GetZ(vt) == Approx(4.0F));
        CHECK(Vector4::GetW(vt) == Approx(1.0F));
    }
}


TEST_CASE("Math / Vector4 / int-float and uint-float conversion functions", "[math]")
{
    using namespace Graphyte;
    using namespace Graphyte::Maths;

    //const auto v1 = Vector4::Make(1.0F, 2.0F, 3.0F, -4.0F);
    //const auto v2 = Vector4::Make(4.0F, -3.0F, 1.0F, 2.0F);
    //const auto v3 = Vector4::Make(5.0F, 1.0F, -2.0F, 6.0F);

    /*
    static Vector4 mathcall ConvertIntToFloat(Vector4 vint, uint32_t div_exponent) noexcept;
    static Vector4 mathcall ConvertFloatToInt(Vector4 vfloat, uint32_t mul_exponent) noexcept;
    static Vector4 mathcall ConvertUIntToFloat(Vector4 vuint, uint32_t div_exponent) noexcept;
    static Vector4 mathcall ConvertFloatToUInt(Vector4 vfloat, uint32_t mul_exponent) noexcept;
    */
}
#endif
