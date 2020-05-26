#include <catch2/catch.hpp>
#include <GxBase/Base.module.hxx>
#include <GxBase/System.hxx>
#include <GxBase/ObjectPool.hxx>

#include <random>

TEST_CASE("Page memory allocator")
{
    const size_t ElementsCount = 1024;
    const size_t BlockSize = ElementsCount * sizeof(uint64_t);

    uint64_t* block = static_cast<uint64_t*>(Graphyte::System::OsVirtualAlloc(BlockSize));

    for (size_t i = 0; i < ElementsCount; ++i)
    {
        block[i] = static_cast<uint64_t>(i);
    }

    Graphyte::System::OsVirtualFree(block, BlockSize);
}

TEST_CASE("Object pool")
{
    struct SomeObject final
    {
        uint32_t Items[2];
    };

    using SomeObjectPool = Graphyte::PoolContainer<SomeObject, 1024>;

    SomeObjectPool pool{};

    SECTION("Predictable results")
    {
        CHECK(pool.GetCount() == 0);
        CHECK(pool.GetCapacity() == 0);

        auto object1 = pool.Allocate();

        CHECK(pool.GetCount() == 1);
        CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

        auto object2 = pool.Allocate();

        CHECK(pool.GetCount() == 2);
        CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

        pool.Deallocate(object1);

        CHECK(pool.GetCount() == 1);
        CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

        auto object3 = pool.Allocate();

        CHECK(pool.GetCount() == 2);
        CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

        pool.Deallocate(object2);

        CHECK(pool.GetCount() == 1);
        CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

        pool.Deallocate(object3);

        CHECK(pool.GetCount() == 0);
        CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

        {
            auto item1 = pool.Allocate();

            CHECK(pool.GetCount() == 1);
            CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

            auto item2 = pool.Allocate();

            CHECK(pool.GetCount() == 2);
            CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

            pool.Deallocate(item1);

            CHECK(pool.GetCount() == 1);
            CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);

            pool.Deallocate(item2);

            CHECK(pool.GetCount() == 0);
            CHECK(pool.GetCapacity() == SomeObjectPool::PoolCapacity);
        }
    }

    static constexpr const size_t AllocsCount = 512;

    SECTION("Random alloc/dealloc")
    {
        std::mt19937 random{};
        std::set<SomeObject*> allocations{};

        for (size_t j = 0; j < 4; ++j)
        {
            //
            // Allocate items.
            //

            for (size_t i = 0; i < (10 * AllocsCount); ++i)
            {
                auto object = pool.Allocate();
                allocations.insert(object);

                CHECK(pool.GetCount() == allocations.size());
                CHECK(pool.GetCount() <= pool.GetCapacity());
            }


            //
            // Deallocate in random order.
            //

            while (!allocations.empty())
            {
                std::uniform_int_distribution<ptrdiff_t> sample{ 0, static_cast<ptrdiff_t>(allocations.size() - 1) };
                auto it = allocations.begin();
                auto distance = sample(random);

                std::advance(it, distance);

                pool.Deallocate(*it);
                allocations.erase(it);

                CHECK(pool.GetCount() == allocations.size());
            }
        }

        CHECK(pool.GetCount() == 0);
        CHECK(allocations.empty());
    }

    SECTION("Random alloc/dealloc with interleaving allocations")
    {
        std::mt19937 random{};
        std::set<SomeObject*> allocations{};

        for (size_t j = 0; j < 4; ++j)
        {
            //
            // Allocate items.
            //

            for (size_t i = 0; i < (10 * AllocsCount); ++i)
            {
                auto object = pool.Allocate();
                allocations.insert(object);

                CHECK(pool.GetCount() == allocations.size());
                CHECK(pool.GetCount() <= pool.GetCapacity());
            }


            //
            // Deallocate in random order.
            //

            for (size_t i = 0; i < (5 * AllocsCount); ++i)
            {
                std::uniform_int_distribution<ptrdiff_t> sample{ 0, static_cast<ptrdiff_t>(allocations.size() - 1) };
                auto it = allocations.begin();
                auto distance = sample(random);

                std::advance(it, distance);

                pool.Deallocate(*it);
                allocations.erase(it);

                CHECK(pool.GetCount() == allocations.size());
            }
        }

        for (size_t j = 0; j < 4; ++j)
        {
            for (size_t i = 0; i < (5 * AllocsCount); ++i)
            {
                auto it = allocations.begin();
                std::uniform_int_distribution<ptrdiff_t> sample{ 0, static_cast<ptrdiff_t>(allocations.size() - 1) };
                auto distance = sample(random);

                std::advance(it, distance);

                pool.Deallocate(*it);
                allocations.erase(it);

                CHECK(pool.GetCount() == allocations.size());
            }
        }

        CHECK(pool.GetCount() == 0);
        CHECK(allocations.empty());
    }
}
