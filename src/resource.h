#pragma once

#include <string>
#include <vector>

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
