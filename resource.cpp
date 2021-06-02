#include "resource.h"

std::string getCategoryName( ResourceCategory category )
{
    switch ( category ) {
    case ResourceCategory::Wood:
        return "Wood";
    case ResourceCategory::Stone:
        return "Stone";
    case ResourceCategory::Clay:
        return "Clay";
    case ResourceCategory::Forage:
        return "Forageables";
    case ResourceCategory::Animal:
        return "Animal Products";
    case ResourceCategory::Farming:
        return "Farm Produce";
    case ResourceCategory::Food:
        return "Food";
    case ResourceCategory::Metal:
        return "Metal";
    case ResourceCategory::Fuel:
        return "Fuel";
    }
    return "None";
}

ResourceCategory getCategory( ResourceSubtype resourceType )
{
    switch ( resourceType ) {
    case ResourceSubtype::Logs:
    case ResourceSubtype::Boards:
        return ResourceCategory::Wood;
    case ResourceSubtype::Stone:
    case ResourceSubtype::Ore:
        return ResourceCategory::Stone;
    case ResourceSubtype::Clay:
        return ResourceCategory::Clay;
    case ResourceSubtype::Berries:
    case ResourceSubtype::Plants:
        return ResourceCategory::Forage;
    case ResourceSubtype::Bones:
    case ResourceSubtype::Hides:
    case ResourceSubtype::MeatRaw:
        return ResourceCategory::Animal;
    case ResourceSubtype::Seeds:
    case ResourceSubtype::Fiber:
        return ResourceCategory::Farming;
    case ResourceSubtype::Fish:
    case ResourceSubtype::MeatDish:
    case ResourceSubtype::Baked:
    case ResourceSubtype::Drinks:
        return ResourceCategory::Food;
    case ResourceSubtype::MetalSoft:
    case ResourceSubtype::MetalHard:
    case ResourceSubtype::MetalPrecious:
        return ResourceCategory::Metal;
    case ResourceSubtype::Charcoal:
    case ResourceSubtype::Coal:
        return ResourceCategory::Fuel;
    case ResourceSubtype::All:
        return ResourceCategory::All;
    default:
        break;
    }
    return ResourceCategory::None;
}
