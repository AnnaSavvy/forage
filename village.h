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
    std::vector<int> _inventory;
    std::vector<int> _resources;
    std::vector<Villager> _villagers;

    Village();
    void printStatus();
    void assignTasks();
    void update();
};
