#pragma once
#include "object.h"

enum class UnitType
{
    Animal,
    Villager,
    Raider,
    // Always at the end
    All,
    None
};

class Unit : public GameObject {
public:
    UnitType type = UnitType::Villager;
    int health = 100;
    int morale = 100;
    int exp = 0;

    virtual void printStatus() const = 0;
};
