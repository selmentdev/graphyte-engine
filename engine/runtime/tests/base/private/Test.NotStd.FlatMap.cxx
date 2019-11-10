#include "Test.Base.pch.hxx"
#include <Graphyte/FlatContainers.hxx>

TEST_CASE("notstd::flat_map")
{
    REQUIRE(notstd::flat_map<int, int>{}.empty());

    notstd::flat_map<int, int> items{
        {
            {1, 2},
            {3, 4},
            {5, 6}
        }
    };

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 3);
    REQUIRE(items.capacity() >= items.size());
    REQUIRE(items[1] == 2);
    REQUIRE(items[3] == 4);
    REQUIRE(items[5] == 6);

    items.insert(std::make_pair(7, 8));

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 4);
    REQUIRE(items.capacity() >= items.size());
    REQUIRE(items[7] == 8);

    items.emplace(9, 10);

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 5);
    REQUIRE(items.capacity() >= items.size());
    REQUIRE(items[9] == 10);

    items.clear();

    REQUIRE(items.empty());
    REQUIRE(items.size() == 0);
    REQUIRE(items.capacity() >= items.size());

    items[11] = 12;

    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 1);
    REQUIRE(items.capacity() >= items.size());

    items.reserve(20);

    REQUIRE(items[11] == 12);
    REQUIRE_FALSE(items.empty());
    REQUIRE(items.size() == 1);
    REQUIRE(items.capacity() == 20);

    items.shrink_to_fit();

    REQUIRE(items.size() == 1);
    REQUIRE(items.capacity() >= 1);
    REQUIRE_FALSE(items.empty());

    items.clear();
    items.reserve(20);

    int total_keys = 0;
    int total_values = 0;

    for (int i = 0; i < 20; ++i)
    {
        const auto current_key = i * 2 + 0;
        const auto current_value = i * 2 + 1;

        total_keys += current_key;
        total_values += current_value;

        items.emplace(current_key, current_value);
    }

    REQUIRE(items.size() == items.capacity());

    int accum_keys = 0;
    int accum_values = 0;

    for (auto [k, v] : items)
    {
        accum_keys += k;
        accum_values += v;
    }

    REQUIRE(accum_keys == total_keys);
    REQUIRE(accum_values == total_values);
}
