#include "build_optimizer.h"

namespace BuildOrder
{

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
        return ( getMaxPopulation() - population + 1 ) / 2 + bonus;
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
        const int farmers = ( bonusFood > population ) ? 0 : ( population - bonusFood + 1 ) / 2;
        const int baseProduction = ( farmers + 1 ) / 2 + ( population - farmers ) * 2;

        int modifier = landProduction;
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
        const int baseProduction = ( population * taxCollectionMode + 1 ) / 2;

        int modifier = landProduction;
        if ( hasBuilding( Marketplace ) ) {
            modifier += 50;
        }
        if ( hasBuilding( Bank ) ) {
            modifier += 50;
        }
        return baseProduction * modifier / 100;
    }

    HistoryRecord Optimizer::nextEvent( Building nextOrder )
    {
        HistoryRecord record;
        if ( city.hasBuilding( nextOrder ) ) {
            record.completed = nextOrder;
            record.turn = currentTurn;
            return record;
        }

        int timeToCompletion;
        int nextPop;

        return record;
    }

    std::vector<HistoryRecord> Optimizer::executeBuildOrder( std::vector<Building> buildOrder )
    {
        return std::vector<HistoryRecord>();
    }
}
