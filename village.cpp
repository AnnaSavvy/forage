#include "village.h"
#include "logger.h"

#include "static.h"
#include <iostream>

Village::Village()
{
    _name = "Grudinino";

    std::fill( _inventory, _inventory + static_cast<size_t>( ResourceCategory::All ), 0 );
    std::fill( _resources, _resources + static_cast<size_t>( ResourceSubtype::All ), 0 );

    for ( int i = 0; i < 5; i++ ) {
        _villagers.emplace_back( this );
    }

    const nlohmann::json & data = getStaticData();

    std::cout << data["resourceCategory"][0];
    std::cout << data["resourceCategory"][1];
}

void Village::printStatus()
{
    int totalScore = 0;

    printLine( "*** " + _name + " ***" );
    printLine( "Current villagers: " + std::to_string( _villagers.size() ) );
    for ( const auto & unit : _villagers ) {
        unit.printStatus();
    }

    printLine( "Village inventory: " );
    for ( const auto & category : resAllCategories ) {
        std::cout << "  - " << getCategoryName( category ) << ": " << _inventory[static_cast<size_t>( category )] << std::endl;
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
}
