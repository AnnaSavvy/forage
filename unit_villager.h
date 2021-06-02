#pragma once
#include "unit.h"
#include "json.hpp"

#include <string>

class Village;

struct Task
{

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
