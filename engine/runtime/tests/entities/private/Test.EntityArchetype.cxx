#include <catch2/catch.hpp>
#include <GxBase/Base.module.hxx>
//#include <Graphyte/Entities.hxx>

TEST_CASE("Entity store allocation")
{
    //auto* store = Graphyte::Entities::AllocateEntityStore();
    //auto* data = store->GetData();
    //CHECK(reinterpret_cast<uintptr_t>(data) == reinterpret_cast<uintptr_t>(store + 1));
    //Graphyte::Entities::DeallocateEntityStore(store);
}

#if false
#include <Graphyte/Entities/EntityArchetype.hxx>
#include <Graphyte/Entities/ComponentSystem.hxx>

struct Vehicle final
{
    static constexpr Graphyte::Entities::ComponentType ID{ "Vehicle" };

    uint32_t Wheels[4];
};

struct FunkyVehicleTag final
{
    static constexpr Graphyte::Entities::ComponentType ID{ "FunkyVehicleTag" };
};

struct SomeNotAvailableTag final
{
    static constexpr Graphyte::Entities::ComponentType ID{ "SomeNotAvailableTag" };
};

class VehicleSystem : public Graphyte::Entities::ComponentSystem<Vehicle, FunkyVehicleTag>
{
public:
    void Update(
        [[maybe_unused]] Graphyte::Entities::Entity entity,
        [[maybe_unused]] Vehicle& vehicle,
        [[maybe_unused]] FunkyVehicleTag& funky
    ) noexcept override
    {
        ;
    }
};

TEST_CASE("Entity archetype checks")
{
    auto* archetype = Graphyte::Entities::EntityArchetype::Create<
        Graphyte::Entities::Parent,
        Graphyte::Entities::WorldTransform,
        FunkyVehicleTag,
        Graphyte::Entities::BoundingSphere,
        Graphyte::Entities::LocalTransform,
        Vehicle
    >();

    REQUIRE(archetype != nullptr);

    auto components = archetype->GetComponents();
    REQUIRE(!components.empty());
    REQUIRE(components.size() == 7);

    CHECK(components[0].Type == Graphyte::Entities::Entity::ID);
    CHECK(components[0].Type.Name == std::string{ "Entity" });
    CHECK(components[0].Offset == 0);
    CHECK(components[0].IsEmpty == false);

    CHECK(components[1].Type == Graphyte::Entities::Parent::ID);
    CHECK(components[1].Type.Name == std::string{ "Parent" });
    CHECK(components[1].Offset == 8);
    CHECK(components[1].IsEmpty == false);

    CHECK(components[2].Type == Graphyte::Entities::WorldTransform::ID);
    CHECK(components[2].Type.Name == std::string{ "WorldTransform" });
    CHECK(components[2].Offset == 16);
    CHECK(components[2].IsEmpty == false);

    CHECK(components[3].Type == FunkyVehicleTag::ID);
    CHECK(components[3].Type.Name == std::string{ "FunkyVehicleTag" });
    CHECK(components[3].Offset == 80);
    CHECK(components[3].IsEmpty == true);

    CHECK(components[4].Type == Graphyte::Entities::BoundingSphere::ID);
    CHECK(components[4].Type.Name == std::string{ "BoundingSphere" });
    CHECK(components[4].Offset == 80);
    CHECK(components[4].IsEmpty == false);

    CHECK(components[5].Type == Graphyte::Entities::LocalTransform::ID);
    CHECK(components[5].Type.Name == std::string{ "LocalTransform" });
    CHECK(components[5].Offset == 96);
    CHECK(components[5].IsEmpty == false);

    CHECK(components[6].Type == Vehicle::ID);
    CHECK(components[6].Type.Name == std::string{ "Vehicle" });
    CHECK(components[6].Offset == 160);
    CHECK(components[6].IsEmpty == false);

    CHECK(archetype->IsCompatible(Graphyte::Entities::GetArchetypeSignature<>()) == true);
    CHECK(archetype->IsCompatible(Graphyte::Entities::GetArchetypeSignature<Graphyte::Entities::Parent>()) == true);
    CHECK(archetype->IsCompatible(Graphyte::Entities::GetArchetypeSignature<Graphyte::Entities::WorldTransform, Graphyte::Entities::LocalTransform>()) == true);
    CHECK(archetype->IsCompatible(Graphyte::Entities::GetArchetypeSignature<Vehicle, FunkyVehicleTag>()) == true);

    CHECK(archetype->IsCompatible(Graphyte::Entities::GetArchetypeSignature<Graphyte::Entities::WorldTransform, SomeNotAvailableTag>()) == false);

    VehicleSystem vs{};
    vs.OnUpdate();

    delete archetype;
}

#endif
