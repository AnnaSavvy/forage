#include "logger.h"
#include "unit_villager.h"
#include "village.h"

#include <iostream>

uint32_t getInventoryID( Villager::Task task )
{
    switch ( task ) {
    case Villager::Task::Logging:
        return ResourceCategory::Wood;
    case Villager::Task::Mining:
        return ResourceCategory::Stone;
    case Villager::Task::Harvesting:
        return ResourceCategory::Clay;
    case Villager::Task::Foraging:
        return ResourceCategory::Forage;
    case Villager::Task::Hunting:
        return ResourceCategory::Animal;
    case Villager::Task::Farming:
        return ResourceCategory::Farming;
    case Villager::Task::Cooking:
        return ResourceCategory::Stone;
    default:
        break;
    }
    return 0;
}

Villager::Villager( Village * reference )
    : home( reference )
    , target( nullptr )
{}

void Villager::printStatus() const
{
    std::cout << "  - " << name;
    if ( task == Task::None ) {
        std::cout << " is not working!";
    }
    else {
        std::cout << " is " << GetTaskName( task );
    }
    std::cout << " Health: " << health << ", morale: " << morale << ", expirience: " << exp << std::endl;
}

std::string Villager::GetTaskName( Villager::Task task )
{
    switch ( task ) {
    case Villager::Task::Logging:
        return "felling trees";
    case Villager::Task::Mining:
        return "mining";
    case Villager::Task::Harvesting:
        return "harvesting clay";
    case Villager::Task::Foraging:
        return "foraging";
    case Villager::Task::Hunting:
        return "hunting";
    case Villager::Task::Farming:
        return "farming";
    case Villager::Task::Cooking:
        return "cooking";
    case Villager::Task::Crafting:
        return "crafting";
    case Villager::Task::Building:
        return "building";
    case Villager::Task::Resting:
        return "resting";
    case Villager::Task::Eating:
        return "eating";
    default:
        break;
    }
    return "nothing";
}

const std::string & Villager::getName() const
{
    return name;
}

void Villager::update()
{
    home->_inventory[getInventoryID(task)]++;
    morale--;
}
