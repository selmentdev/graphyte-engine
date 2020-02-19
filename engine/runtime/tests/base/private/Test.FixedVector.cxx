#include <catch2/catch.hpp>
#include <Graphyte/FixedVector.hxx>

#include <algorithm>
#include <numeric>

TEST_CASE("Fixed vector")
{
    notstd::fixed_vector<int, 4> items{};


    //
    // Assert empty vector.
    //

    REQUIRE(items.capacity() == 4);
    REQUIRE(items.size() == 0);
    REQUIRE(items.empty());
    REQUIRE_FALSE(items.full());

    REQUIRE(items.data() != nullptr);


    //
    // Push back one item.
    //

    items.push_back(42);

    REQUIRE(items.size() == 1);
    REQUIRE_FALSE(items.full());
    REQUIRE_FALSE(items.empty());
    REQUIRE(items[0] == 42);
    REQUIRE(items.front() == 42);
    REQUIRE(items.back() == 42);


    //
    // Resize number of items to 3 and mutate them.
    //

    items.resize(3);

    items[1] = 13;
    items[2] = 911;

    REQUIRE(items.size() == 3);
    REQUIRE_FALSE(items.full());
    REQUIRE_FALSE(items.empty());
    REQUIRE(items[0] == 42);
    REQUIRE(items[1] == 13);
    REQUIRE(items[2] == 911);
    REQUIRE(items.front() == 42);
    REQUIRE(items.back() == 911);


    //
    // Emplace back one element.
    //

    items.emplace_back(2137);

    REQUIRE(items.size() == 4);
    REQUIRE(items.full());
    REQUIRE_FALSE(items.empty());
    REQUIRE(items[0] == 42);
    REQUIRE(items[1] == 13);
    REQUIRE(items[2] == 911);
    REQUIRE(items[3] == 2137);
    REQUIRE(items.front() == 42);
    REQUIRE(items.back() == 2137);

    {
        //
        // Create copy of data.
        //

        notstd::fixed_vector<int, 4> copy{ items };


        //
        // Swap first and last item.
        //

        {
            std::swap(items.front(), items.back());

            REQUIRE(items.size() == 4);
            REQUIRE(items.full());
            REQUIRE_FALSE(items.empty());
            REQUIRE(items[0] == 2137);
            REQUIRE(items[1] == 13);
            REQUIRE(items[2] == 911);
            REQUIRE(items[3] == 42);
            REQUIRE(items.front() == 2137);
            REQUIRE(items.back() == 42);
        }


        //
        // Resize back to 1 element.
        //

        {
            items.resize(1);

            REQUIRE(items.size() == 1);
            REQUIRE_FALSE(items.full());
            REQUIRE_FALSE(items.empty());
            REQUIRE(items[0] == 2137);
            REQUIRE(items.front() == 2137);
            REQUIRE(items.back() == 2137);
        }


        //
        // Pop back last element.
        //

        {
            items.pop_back();

            REQUIRE(items.size() == 0);
            REQUIRE_FALSE(items.full());
            REQUIRE(items.empty());
        }


        //
        // Emplace one element and check it after clear.
        //

        {
            items.emplace_back(1337);

            REQUIRE(items.size() == 1);
            REQUIRE_FALSE(items.full());
            REQUIRE_FALSE(items.empty());
            REQUIRE(items[0] == 1337);
            REQUIRE(items.front() == 1337);
            REQUIRE(items.back() == 1337);

            items.clear();

            REQUIRE(items.size() == 0);
            REQUIRE(items.empty());
        }


        //
        // Assert that copied element did not mutate.
        //

        REQUIRE(copy.size() == 4);
        REQUIRE(copy.full());
        REQUIRE_FALSE(copy.empty());
        REQUIRE(copy[0] == 42);
        REQUIRE(copy[1] == 13);
        REQUIRE(copy[2] == 911);
        REQUIRE(copy[3] == 2137);
        REQUIRE(copy.front() == 42);
        REQUIRE(copy.back() == 2137);


        //
        // Create another vector by using iterators ctor.
        //

        {
            notstd::fixed_vector<int, 2> smoler{ copy.begin(), copy.end() };

            REQUIRE(smoler.size() == 2);
            REQUIRE_FALSE(smoler.empty());
            REQUIRE(smoler.full());
            REQUIRE(smoler[0] == 42);
            REQUIRE(smoler[1] == 13);
            REQUIRE(smoler.front() == 42);
            REQUIRE(smoler.back() == 13);
        }

        {
            notstd::fixed_vector<int, 2> smoler{ copy.crbegin(), copy.crend() };

            REQUIRE(smoler.size() == 2);
            REQUIRE_FALSE(smoler.empty());
            REQUIRE(smoler.full());
            REQUIRE(smoler[0] == 2137);
            REQUIRE(smoler[1] == 911);
            REQUIRE(smoler.front() == 2137);
            REQUIRE(smoler.back() == 911);
        }

        {
            notstd::fixed_vector<int, 8> larger{ copy.begin(), copy.end() };

            REQUIRE(larger.size() == 4);
            REQUIRE_FALSE(larger.empty());
            REQUIRE_FALSE(larger.full());
            REQUIRE(larger[0] == 42);
            REQUIRE(larger[1] == 13);
            REQUIRE(larger[2] == 911);
            REQUIRE(larger[3] == 2137);
            REQUIRE(larger.front() == 42);
            REQUIRE(larger.back() == 2137);
        }

        {
            notstd::fixed_vector<int, 8> reverse{ copy.crbegin(), copy.crend() };

            REQUIRE(reverse.size() == 4);
            REQUIRE_FALSE(reverse.empty());
            REQUIRE_FALSE(reverse.full());
            REQUIRE(reverse[0] == 2137);
            REQUIRE(reverse[1] == 911);
            REQUIRE(reverse[2] == 13);
            REQUIRE(reverse[3] == 42);
            REQUIRE(reverse.front() == 2137);
            REQUIRE(reverse.back() == 42);
        }


        //
        // Move copy to another variable.
        //

        notstd::fixed_vector<int, 4> moved{ std::move(copy) };

        REQUIRE(moved.size() == 4);
        REQUIRE(moved.full());
        REQUIRE_FALSE(moved.empty());
        REQUIRE(moved[0] == 42);
        REQUIRE(moved[1] == 13);
        REQUIRE(moved[2] == 911);
        REQUIRE(moved[3] == 2137);
        REQUIRE(moved.front() == 42);
        REQUIRE(moved.back() == 2137);

        //
        // Assert that original element is empty now.
        //

        REQUIRE(copy.size() == 0);
        REQUIRE(copy.empty());
    }
}
