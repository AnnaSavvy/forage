#pragma once
#include "resource.h"
#include "unit_villager.h"
#include <algorithm>
#include <string>
#include <vector>

class Village
{
public:
    std::string _name;
    int _inventory[static_cast<size_t>( ResourceCategory::All )];
    int _resources[static_cast<size_t>( ResourceSubtype::All )];
    std::vector<Villager> _villagers;

    Village();
    void printStatus();
    void assignTasks();
    void update();
};
