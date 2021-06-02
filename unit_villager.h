#pragma once
#include "unit.h"

#include <string>
#include <vector>

class Village;

struct Task
{
    std::string name;
    std::vector<std::pair<uint32_t, int> > input;
    std::vector<std::pair<uint32_t, int> > output;
    int energyCost;
};

class Villager : public Unit
{
public:
    enum class Task
    {
        Logging,
        Mining,
        Harvesting,
        Foraging,
        Hunting,
        Farming,
        Cooking,
        Crafting,
        Building,
        Resting,
        Eating,
        None
    };

    Task task = Task::None;
    GameObject * target;
    std::string name = "Pupa";
    Village * home;

    Villager( Village * reference );

    void update();
    void printStatus() const;
    virtual const std::string & getName() const;
    static std::string GetTaskName( Task task );
};
