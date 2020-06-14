#include <catch2/catch.hpp>
#include <GxBase/FlatContainers.hxx>

TEST_CASE("notstd::flat_set")
{
    REQUIRE(notstd::flat_set<int>{}.empty());

    std::array<int, 5> src_items{ { 1, 2, 3, 4, 5 } };
    notstd::flat_set<int> items(src_items.begin(), src_items.end());

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 5);
    REQUIRE(items.capacity() >= items.size());

    REQUIRE(items.count(0) == 0);
    REQUIRE(items.count(1) == 1);
    REQUIRE(items.count(2) == 1);
    REQUIRE(items.count(3) == 1);
    REQUIRE(items.count(4) == 1);
    REQUIRE(items.count(5) == 1);
    REQUIRE(items.count(6) == 0);

    items.insert(7);

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 6);
    REQUIRE(items.capacity() >= items.size());


    REQUIRE(items.count(7) == 1);

    items.erase(4);

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 5);
    REQUIRE(items.capacity() >= items.size());

    REQUIRE(items.count(4) == 0);

    items.emplace(2137);

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 6);
    REQUIRE(items.capacity() >= items.size());

    REQUIRE(items.count(2136) == 0);
    REQUIRE(items.count(2137) == 1);
    REQUIRE(items.count(2138) == 0);

    items.emplace(2137);

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 6);
    REQUIRE(items.capacity() >= items.size());

    REQUIRE(items.count(2136) == 0);
    REQUIRE(items.count(2137) == 1);
    REQUIRE(items.count(2138) == 0);

    items.emplace(2137);

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 6);
    REQUIRE(items.capacity() >= items.size());

    REQUIRE(items.count(2136) == 0);
    REQUIRE(items.count(2137) == 1);
    REQUIRE(items.count(2138) == 0);

    items.shrink_to_fit();

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() <= items.capacity());
    REQUIRE(items.size() == 6);

    items.clear();

    REQUIRE(items.empty());
    REQUIRE(items.size() == 0);
    REQUIRE(items.capacity() >= items.size());

    items.reserve(20);

    REQUIRE(items.empty());
    REQUIRE(items.size() == 0);
    REQUIRE(items.capacity() == 20);


    int total = 0;

    for (int i = 0; i < 20; ++i)
    {
        total += i;
        items.insert(i);
    }

    int accum = 0;

    for (auto i : items)
    {
        accum += i;
    }

    REQUIRE(items.size() == 20);
    REQUIRE(items.capacity() == 20);
    REQUIRE(accum == total);
}
