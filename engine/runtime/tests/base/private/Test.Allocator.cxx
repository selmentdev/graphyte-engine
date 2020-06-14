#include <catch2/catch.hpp>

namespace
{
    class SampleClass
    {
    public:
        uint64_t m_Value1    = 1337;
        float m_Value2       = 21.37F;
        std::string m_Value3 = "Hello World!";
    };
}

TEST_CASE("Allocator Test")
{
    SECTION("Allocator")
    {
        //auto* object = Graphyte::Platform::New<SampleClass>();
        //REQUIRE(object != nullptr);
        //REQUIRE(object->m_Value1 == uint64_t{ 1337 });
        //REQUIRE(object->m_Value2 == 21.37F);
        //REQUIRE(object->m_Value3 == "Hello World!");
        //REQUIRE(Graphyte::Platform::Allocator::GInstance.Validate());
        //Graphyte::Platform::Delete(object);
        //REQUIRE(Graphyte::Platform::Allocator::GInstance.Validate());
    }

    SECTION("Fail with OOM")
    {
        //Graphyte::Platform::Memory::Initialize();
        //void* pointer = Graphyte::Platform::Memory::OSVirtualAlloc(4 << 20);
        //REQUIRE(pointer != nullptr);
        //uint64_t volatile* data = reinterpret_cast<uint64_t volatile*>(pointer);
        //*data = 1337;
        //REQUIRE(*data == uint64_t{ 1337 });
        //Graphyte::Platform::Memory::OSVirtualFree(pointer, 4 << 20);
    }
}

//TEST_CASE("String allocator")
//{
//    SECTION("Empty string")
//    {
//        Graphyte::string s{};
//        auto const usage = Graphyte::Platform::MemoryTracker::GetUsage(Graphyte::Platform::MemoryPoolTag::Strings);
//        REQUIRE(usage == uint64_t{ 0 });
//    }
//
//    SECTION("Very large string")
//    {
//        Graphyte::string s{ "this string is initialized with kinda large string. It should be allocated on heap anyway." };
//        auto const usage = Graphyte::Platform::MemoryTracker::GetUsage(Graphyte::Platform::MemoryPoolTag::Strings);
//        REQUIRE(usage != uint64_t{ 0 });
//    }
//}
