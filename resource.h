#pragma once

#include <string>
#include <vector>

namespace Resource
{
    enum NodeLocation
    {
        Village,
        Farm,
        Plains,
        Forest,
        Swamp,
        River,
        Lake,
        Cave,
        Mine
    };

    enum ResourceNode
    {

    };
}

enum ResourceCategory
{
    // Primary
    Wood,
    Stone,
    Clay,
    Forage,
    Animal,
    Farming,
    // Secondary
    Food,
    Metal,
    Fuel,
    // Always at the end
    All,
    None
};

enum class ResourceSubtype
{
    // Primary
    Logs,
    Boards,
    Stone,
    Ore,
    Clay,
    Berries,
    Plants,
    Bones,
    Hides,
    MeatRaw,
    Seeds,
    Fiber,
    // Secondary
    Fish,
    MeatDish,
    Baked,
    Drinks,
    MetalSoft,
    MetalHard,
    MetalPrecious,
    Charcoal,
    Coal,
    // Always at the end
    All,
    None
};

const std::vector<ResourceCategory> resAllCategories{ ResourceCategory::Wood,   ResourceCategory::Stone,  ResourceCategory::Clay,
                                                      ResourceCategory::Forage, ResourceCategory::Animal, ResourceCategory::Farming,
                                                      ResourceCategory::Food,   ResourceCategory::Metal,  ResourceCategory::Fuel };

std::string getCategoryName( ResourceCategory category );
ResourceCategory getCategory( ResourceSubtype resourceType );
