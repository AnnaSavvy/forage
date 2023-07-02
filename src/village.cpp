#include "village.h"
#include "logger.h"

#include "static.h"
#include <iostream>

Village::Village()
{
    _name = "Inino";

    const nlohmann::json & data = GetStaticData( DataFileName::PREGEN_NAMES );
    _inventory.resize( data["resourceCategory"].size(), 0 );
    _resources.resize( data["resource"].size(), 0 );

    for ( int i = 0; i < 5; i++ ) {
        _villagers.emplace_back( this );
    }
}

void Village::printStatus()
{
    int totalScore = 0;
    const nlohmann::json & data = GetStaticData( DataFileName::PREGEN_NAMES );

    printLine( "*** " + _name + " ***" );
    printLine( "Current villagers: " + std::to_string( _villagers.size() ) );
    for ( const auto & unit : _villagers ) {
        unit.printStatus();
    }

    printLine( "Village inventory: " );
    size_t id = 0;
    for ( auto & category : data["resourceCategory"] ) {
        std::cout << "  - " << category << ": " << _inventory[id] << std::endl;
        id++;
    }
}

void Village::assignTasks()
{
    auto it = _villagers.begin();
    std::vector<std::pair<uint32_t, Villager::Task> > taskMap
        = { { 0, Villager::Task::Logging }, { 1, Villager::Task::Mining }, { 3, Villager::Task::Foraging }, { 4, Villager::Task::Hunting } };

    for ( auto & assignment : taskMap ) {
        if ( it == _villagers.end() )
            return;

        if ( _inventory[assignment.first] < 1 ) {
            it->task = assignment.second;
            ++it;
        }
    }
}

void Village::update()
{
    assignTasks();

    for ( auto & unit : _villagers ) {
        unit.update();
    }

    // Reset category totals
    for ( auto & inv : _inventory ) {
        inv = 0;
    }

    // Recalculate category totals
    const auto & resourceData = GetStaticData( DataFileName::PREGEN_NAMES )["resource"];
    for ( auto & res : resourceData ) {
        const int id = res["id"].get<int>();
        const int categoryID = res["category"].get<int>();
        _inventory[categoryID] += _resources[id];
    }
}
