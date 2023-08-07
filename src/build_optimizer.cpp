#include "build_optimizer.h"

namespace BuildOrder
{
    int ceilDivision( int dividend, int divisor )
    {
        if ( divisor == 0 ) {
            return dividend;
        }
        return ( dividend + divisor - 1 ) / divisor;
    }

    int City::GetBuildingCost( Building building )
    {
        switch ( building ) {
        case BuildOrder::Smithy:
        case BuildOrder::Granary:
            return 40;
        case BuildOrder::Builders:
        case BuildOrder::Library:
            return 60;
        case BuildOrder::Sawmill:
        case BuildOrder::Marketplace:
        case BuildOrder::Farmers:
            return 100;
        case BuildOrder::Sages:
            return 120;
        case BuildOrder::Foresters:
            return 200;
        case BuildOrder::Bank:
            return 250;
        case BuildOrder::Miners:
        case BuildOrder::University:
            return 300;
        case BuildOrder::Mechanicians:
            return 600;
        default:
            break;
        }
        return 0;
    }

    int City::GetBuildingMaintanence( Building building )
    {
        switch ( building ) {
        case BuildOrder::Smithy:
        case BuildOrder::Granary:
        case BuildOrder::Builders:
        case BuildOrder::Library:
        case BuildOrder::Marketplace:
            return 1;
        case BuildOrder::Sawmill:
        case BuildOrder::Farmers:
        case BuildOrder::Sages:
        case BuildOrder::Foresters:
            return 2;
        case BuildOrder::Bank:
        case BuildOrder::Miners:
        case BuildOrder::University:
            return 3;
        case BuildOrder::Mechanicians:
            return 5;
        default:
            break;
        }
        return 0;
    }

    bool City::hasBuilding( Building requirement ) const
    {
        for ( auto build : buildings ) {
            if ( build == requirement ) {
                return true;
            }
        }
        return false;
    }

    int City::getMaxPopulation() const
    {
        int max = landPopulation;
        if ( hasBuilding( Granary ) ) {
            max += 2;
        }
        if ( hasBuilding( Farmers ) ) {
            max += 3;
        }
        return max;
    }

    int City::getGrowthRate() const
    {
        int bonus = racialGrowth;
        if ( hasBuilding( Granary ) ) {
            bonus += 2;
        }
        if ( hasBuilding( Farmers ) ) {
            bonus += 3;
        }
        return ceilDivision( getMaxPopulation() - population, 2 ) + bonus;
    }

    int City::getProductionRate() const
    {
        int bonusFood = 0;
        if ( hasBuilding( Granary ) ) {
            bonusFood += 2;
        }
        if ( hasBuilding( Farmers ) ) {
            bonusFood += 3;
        }
        if ( hasBuilding( Foresters ) ) {
            bonusFood += 2;
        }
        // subsistence farming only; can't be negative
        const int farmers = ( bonusFood > population ) ? 0 : ceilDivision( population - bonusFood, 2 );
        const int baseProduction = ceilDivision( farmers, 2 ) + ( population - farmers ) * 2;

        int modifier = 100 + landProduction;
        if ( hasBuilding( Sawmill ) ) {
            modifier += 25;
        }
        if ( hasBuilding( Foresters ) ) {
            modifier += 25;
        }
        if ( hasBuilding( Miners ) ) {
            modifier += 50;
        }
        if ( hasBuilding( Mechanicians ) ) {
            modifier += 50;
        }

        return baseProduction * modifier / 100;
    }

    int City::getGoldIncome() const
    {
        const int baseProduction = ceilDivision( population * taxCollectionMode, 2 );

        int modifier = 100 + landGold;
        if ( hasBuilding( Marketplace ) ) {
            modifier += 50;
        }
        if ( hasBuilding( Bank ) ) {
            modifier += 50;
        }

        int maintanence = 0;
        for ( auto build : buildings ) {
            maintanence += GetBuildingMaintanence( build );
        }

        return baseProduction * modifier / 100 - maintanence;
    }

    int City::getPowerIncome() const
    {
        int power = 0;
        if ( hasBuilding( Library ) ) {
            power += 2;
        }
        if ( hasBuilding( Sages ) ) {
            power += 3;
        }
        if ( hasBuilding( University ) ) {
            power += 5;
        }
        return power;
    }

    HistoryRecord::HistoryRecord( const HistoryRecord & previous, City city )
    {
        turn = previous.turn;
        totalProduction = previous.totalProduction;
        totalIncome = previous.totalIncome;
        totalPower = previous.totalPower;

        buildings = city.buildings;
        population = city.population;
        production = city.getProductionRate();
        income = city.getGoldIncome();
        power = city.getPowerIncome();
    }

    HistoryRecord Optimizer::nextEvent( Building nextOrder, const HistoryRecord & previous )
    {
        HistoryRecord record( previous, city );
        if ( city.hasBuilding( nextOrder ) ) {
            record.completed = nextOrder;
            return record;
        }

        const int buildingCost = City::GetBuildingCost( nextOrder ) - city.overflowProduction;
        const int productivity = city.getProductionRate();
        const int turnsToCompletion = ceilDivision( buildingCost, productivity );

        const int growth = city.getGrowthRate() * 10;
        const int popRequired = std::max( 0, 1000 - city.overflowGrowth );
        const int turnsToGrow = ceilDivision( popRequired, growth );

        const int turnsPassed = std::min( turnsToCompletion, turnsToGrow );
        const int produced = productivity * turnsPassed;

        // Save global statistics
        record.turn += turnsToCompletion;
        record.totalProduction += produced;
        record.totalIncome = city.getGoldIncome() * turnsPassed;
        record.totalPower = city.getPowerIncome() * turnsPassed;

        city.overflowGrowth += turnsPassed * growth;
        // Check if city population increases
        while ( city.overflowGrowth >= 1000 ) {
            city.overflowGrowth -= 1000;
            city.population++;
        }

        // Complete the building construction
        if ( city.overflowProduction >= produced ) {
            record.completed = nextOrder;
            record.buildings = city.buildings;
            city.buildings.emplace_back( nextOrder );
            // does not carry over to the next order
            city.overflowProduction = 0;
        }
        else {
            city.overflowProduction += produced;
        }

        record.production = city.getProductionRate();
        record.income = city.getGoldIncome();
        record.power = city.getPowerIncome();

        return record;
    }

    std::vector<HistoryRecord> Optimizer::executeBuildOrder( std::vector<Building> buildOrder )
    {
        HistoryRecord startEvent;
        std::vector<HistoryRecord> history = { startEvent };

        auto currentOrder = buildOrder.begin();
        while ( currentOrder != buildOrder.end() ) {
            auto event = nextEvent( *currentOrder, history.back() );
            history.emplace_back( event );

            if ( event.completed == *currentOrder ) {
                currentOrder++;
            }
        }

        return history;
    }
}
