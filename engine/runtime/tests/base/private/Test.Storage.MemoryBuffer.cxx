#include "Test.Base.pch.hxx"
#include <Graphyte/Storage/ArchiveMemoryReader.hxx>
#include <Graphyte/Storage/ArchiveMemoryWriter.hxx>
#include <Graphyte/Maths/Types.hxx>
#if false
TEST_CASE("Memory reader and writer")
{
    std::vector<std::byte> buffer{};

    SECTION("Serializing simple types")
    {
        using namespace Graphyte::Storage;

        {
            ArchiveMemoryWriter writer{ buffer };
            REQUIRE(writer.GetPosition() == 0);

            uint32_t u32{ 1337 };
            std::string str{ "Sample text" };
            Graphyte::Maths::float3x3a mtx{ 1.0F, 2.0F, 3.0F, 4.0F, 5.0F, 6.0F, 7.0F, 8.0F, 9.0F };

            writer << u32;
            writer << str;
            writer << mtx;

            REQUIRE(buffer.size() == 67);
            REQUIRE(writer.GetSize() == 67);
            REQUIRE(writer.GetPosition() == 67);
            REQUIRE(writer.IsError() == false);
            REQUIRE(writer.IsSaving() == true);
            REQUIRE(writer.IsLoading() == false);
        }

        {
            ArchiveMemoryReader reader{ buffer };
            REQUIRE(reader.GetPosition() == 0);

            uint32_t u32{};
            std::string str{};
            Graphyte::Maths::float3x3a mtx{};

            reader << u32;
            reader << str;
            reader << mtx;

            REQUIRE(buffer.size() == 67);
            REQUIRE(reader.GetSize() == 67);
            REQUIRE(reader.GetPosition() == 67);
            REQUIRE(reader.IsError() == false);
            REQUIRE(reader.IsSaving() == false);
            REQUIRE(reader.IsLoading() == true);

            REQUIRE(u32 == static_cast<uint32_t>(1337));
            REQUIRE(str == "Sample text");

            REQUIRE(mtx.M11 == 1.0F);
            REQUIRE(mtx.M12 == 2.0F);
            REQUIRE(mtx.M13 == 3.0F);
            REQUIRE(mtx.M21 == 4.0F);
            REQUIRE(mtx.M22 == 5.0F);
            REQUIRE(mtx.M23 == 6.0F);
            REQUIRE(mtx.M31 == 7.0F);
            REQUIRE(mtx.M32 == 8.0F);
            REQUIRE(mtx.M33 == 9.0F);
        }
    }
}
#endif
