#include <catch2/catch.hpp>
#include <GxBase/IntrusiveList.hxx>

struct Item
{
    uint64_t Index{};
    Graphyte::IntrusiveListNode<Item> GlobalListLink;
    Graphyte::IntrusiveListNode<Item> SharedListLink;
};

TEST_CASE("Intrusive lists")
{
    Graphyte::IntrusiveList<Item, &Item::GlobalListLink> globalList{};
    Graphyte::IntrusiveList<Item, &Item::SharedListLink> sharedList{};

    REQUIRE(globalList.IsEmpty() == true);
    REQUIRE(sharedList.IsEmpty() == true);

    std::vector<Item*> oddItems{};
    std::vector<Item*> evenItems{};
    std::vector<Item*> allItems{};

    uint64_t expectedGlobalCount{};
    uint64_t expectedSharedCount{};

    for (uint64_t i = 1; i <= 100; ++i)
    {
        auto* item = new Item();
        item->Index = i;

        expectedGlobalCount += i;

        allItems.push_back(item);

        if ((i & 0b1) == 0)
        {
            evenItems.push_back(item);

            sharedList.InsertTail(item);
            expectedSharedCount += i;
        }
        else
        {
            oddItems.push_back(item);
        }

        globalList.InsertTail(item);
    }

    REQUIRE(oddItems.size() == 50);
    REQUIRE(evenItems.size() == 50);
    REQUIRE(allItems.size() == 100);

    REQUIRE(globalList.IsEmpty() == false);
    REQUIRE(sharedList.IsEmpty() == false);

    uint64_t globalCount{};
    uint64_t sharedCount{};

    for (auto item = globalList.GetHead(); item != nullptr; item = globalList.Next(item))
    {
        globalCount += item->Index;
    }

    REQUIRE(globalCount == expectedGlobalCount);

    for (auto item = sharedList.GetHead(); item != nullptr; item = sharedList.Next(item))
    {
        sharedCount += item->Index;
    }

    REQUIRE(sharedCount == expectedSharedCount);

    for (auto item = sharedList.GetHead(); item != nullptr; item = sharedList.Remove(item))
    {
        ;
    }

    for (auto item = globalList.GetHead(); item != nullptr; item = globalList.Remove(item))
    {
        ;
    }

    REQUIRE(globalList.IsEmpty() == true);
    REQUIRE(sharedList.IsEmpty() == true);

    for (auto& item : allItems)
    {
        delete item;
    }
}
