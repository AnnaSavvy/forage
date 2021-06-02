#include "logger.h"
#include "static.h"
#include "unit_villager.h"
#include "village.h"

#include <iostream>
#include <string>

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
    const auto & tasksData = getStaticData()["tasks"];
    const size_t taskID = static_cast<size_t>( task );

    if ( taskID >= tasksData.size() ) {
        return;
    }
    const auto & taskEntry = tasksData[taskID];

    for ( const auto & res : taskEntry["input"].items() ) {
        const int key = std::stoi( res.key() );
        const int value = res.value().get<int>();
        home->_resources[key] -= value;
    }
    for ( const auto & res : taskEntry["output"].items() ) {
        const int key = std::stoi( res.key() );
        const int value = res.value().get<int>();
        home->_resources[key] += value;
    }
    morale -= taskEntry["energyCost"].get<int>();
}
