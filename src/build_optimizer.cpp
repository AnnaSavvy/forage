#include "build_optimizer.h"

#include <sstream>

#include <iostream>

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
        case BuildOrder::Stables:
        case BuildOrder::Armory:
            return 80;
        case BuildOrder::Sawmill:
        case BuildOrder::Marketplace:
        case BuildOrder::Farmers:
        case BuildOrder::Shrine:
            return 100;
        case BuildOrder::Sages:
            return 120;
        case BuildOrder::Foresters:
        case BuildOrder::Temple:
        case BuildOrder::Figthers:
            return 200;
        case BuildOrder::Bank:
        case BuildOrder::Alchemists:
            return 250;
        case BuildOrder::Miners:
        case BuildOrder::University:
        case BuildOrder::Animists:
            return 300;
        case BuildOrder::Parthenon:
        case BuildOrder::Armorers:
            return 400;
        case BuildOrder::Mechanicians:
            return 600;
        case BuildOrder::Cathedral:
            return 800;
        case BuildOrder::Wizards:
            return 1000;
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
        case BuildOrder::Shrine:
            return 1;
        case BuildOrder::Sawmill:
        case BuildOrder::Farmers:
        case BuildOrder::Sages:
        case BuildOrder::Foresters:
        case BuildOrder::Temple:
        case BuildOrder::Stables:
        case BuildOrder::Armory:
            return 2;
        case BuildOrder::Bank:
        case BuildOrder::Miners:
        case BuildOrder::University:
        case BuildOrder::Parthenon:
        case BuildOrder::Alchemists:
        case BuildOrder::Figthers:
            return 3;
        case BuildOrder::Cathedral:
        case BuildOrder::Armorers:
            return 4;
        case BuildOrder::Mechanicians:
        case BuildOrder::Wizards:
        case BuildOrder::Animists:
            return 5;
        default:
            break;
        }
        return 0;
    }

    std::vector<Building> City::GetBuildingPrerequisites( Building building )
    {
        switch ( building ) {
        case BuildOrder::Foresters:
            return { BuildOrder::Sawmill };
        case BuildOrder::Granary:
        case BuildOrder::Library:
        case BuildOrder::Miners:
        case BuildOrder::Shrine:
            return { BuildOrder::Builders };
        case BuildOrder::Stables:
        case BuildOrder::Armory:
        case BuildOrder::Marketplace:
            return { BuildOrder::Smithy };
        case BuildOrder::Farmers:
            return { BuildOrder::Granary, BuildOrder::Marketplace };
        case BuildOrder::Sages:
            return { BuildOrder::Library };
        case BuildOrder::Alchemists:
        case BuildOrder::University:
            return { BuildOrder::Sages };
        case BuildOrder::Temple:
            return { BuildOrder::Shrine };
        case BuildOrder::Parthenon:
            return { BuildOrder::Temple };
        case BuildOrder::Cathedral:
            return { BuildOrder::Parthenon };
        case BuildOrder::Bank:
            return { BuildOrder::University, BuildOrder::Marketplace };
        case BuildOrder::Mechanicians:
            return { BuildOrder::University, BuildOrder::Miners };
        case BuildOrder::Wizards:
            return { BuildOrder::University, BuildOrder::Alchemists };
        case BuildOrder::Animists:
            return { BuildOrder::Stables, BuildOrder::Sages };
        case BuildOrder::Figthers:
            return { BuildOrder::Armory };
        case BuildOrder::Armorers:
            return { BuildOrder::Figthers };
        case BuildOrder::Sawmill:
        case BuildOrder::Smithy:
        case BuildOrder::Builders:
            // none
            break;
        }
        return std::vector<Building>();
    }

    std::string City::GetBuildingName( Building building )
    {
        switch ( building ) {
        case BuildOrder::Sawmill:
            return "Sawmill";
        case BuildOrder::Foresters:
            return "Foresters";
        case BuildOrder::Smithy:
            return "Smithy";
        case BuildOrder::Marketplace:
            return "Marketplace";
        case BuildOrder::Builders:
            return "Builders";
        case BuildOrder::Miners:
            return "Miners";
        case BuildOrder::Granary:
            return "Granary";
        case BuildOrder::Farmers:
            return "Farmers";
        case BuildOrder::Library:
            return "Library";
        case BuildOrder::Sages:
            return "Sages";
        case BuildOrder::University:
            return "University";
        case BuildOrder::Mechanicians:
            return "Mechanicians";
        case BuildOrder::Bank:
            return "Bank";
        case BuildOrder::Shrine:
            return "Shrine";
        case BuildOrder::Temple:
            return "Temple";
        case BuildOrder::Parthenon:
            return "Parthenon";
        case BuildOrder::Cathedral:
            return "Cathedral";
        case BuildOrder::Alchemists:
            return "Alchemists";
        case BuildOrder::Wizards:
            return "Wizards";
        case BuildOrder::Stables:
            return "Stables";
        case BuildOrder::Animists:
            return "Animists";
        case BuildOrder::Armory:
            return "Armory";
        case BuildOrder::Figthers:
            return "Figthers";
        case BuildOrder::Armorers:
            return "Armorers";
        }
        return "Unknown";
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

    int City::getExactPopulation() const
    {
        return population * 1000 + overflowGrowth;
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
        return std::max( 0, ( ceilDivision( getMaxPopulation() - population, 2 ) + bonus ) * 10 );
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
        const int foodPerFarmer = hasBuilding( Animists ) ? 3 : 2;
        const int farmers = ( bonusFood > population ) ? 0 : ceilDivision( population - bonusFood, foodPerFarmer );
        const int workers = std::max( 0, population - farmers - getUnrest() );
        const int baseProduction = ceilDivision( farmers, 2 ) + workers * 2;

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
        if ( hasBuilding( Shrine ) ) {
            power += 1;
        }
        if ( hasBuilding( Temple ) ) {
            power += 2;
        }
        if ( hasBuilding( Parthenon ) ) {
            power += 3;
        }
        if ( hasBuilding( Cathedral ) ) {
            power += 4;
        }
        if ( hasBuilding( Alchemists ) ) {
            power += 3;
        }
        if ( hasBuilding( Wizards ) ) {
            power += 5;
        }
        return power;
    }

    int City::getUnrest() const
    {
        int unrestReduction = 2; // garrison or spells
        if ( hasBuilding( Shrine ) ) {
            unrestReduction += 1;
        }
        if ( hasBuilding( Temple ) ) {
            unrestReduction += 1;
        }
        if ( hasBuilding( Parthenon ) ) {
            unrestReduction += 1;
        }
        if ( hasBuilding( Cathedral ) ) {
            unrestReduction += 1;
        }
        if ( hasBuilding( Animists ) ) {
            unrestReduction += 1;
        }

        int taxModifier = taxCollectionMode * 10;
        if ( taxModifier > 3 ) {
            taxModifier += ( taxCollectionMode - 3 ) * 5;
        }
        const int unrest = population * taxModifier / 100 - unrestReduction;

        return std::max( 0, unrest );
    }

    std::vector<Building> City::getAvailableBuildings() const
    {
        std::vector<Building> list;

        for ( int index = Sawmill; index <= Armorers; index++ ) {
            Building building = static_cast<Building>( index );
            if ( hasBuilding( building ) ) {
                continue;
            }

            bool canBuild = true;
            for ( auto prereq : GetBuildingPrerequisites( building ) ) {
                if ( !hasBuilding( prereq ) ) {
                    canBuild = false;
                    break;
                }
            }

            if ( canBuild ) {
                list.push_back( building );
            }
        }

        return list;
    }

    HistoryRecord::HistoryRecord( City city )
    {
        buildings = city.buildings;
        exactPopulation = city.getExactPopulation();
        growthRate = city.getGrowthRate();
        productionRate = city.getProductionRate();
        income = city.getGoldIncome();
        power = city.getPowerIncome();
    }

    HistoryRecord::HistoryRecord( City city, const HistoryRecord & previous )
        : HistoryRecord( city )
    {
        turn = previous.turn;
        totalProduction = previous.totalProduction;
        totalIncome = previous.totalIncome;
        totalPower = previous.totalPower;
        lostProduction = previous.lostProduction;
    }

    std::string HistoryRecord::toString() const
    {
        std::ostringstream os;
        if ( buildCompleted ) {
            os << "Building " << City::GetBuildingName( currentOrder ) << " complete!" << std::endl;
        }
        else {
            os << "City growth event!" << std::endl;
        }

        os << "turn      : " << turn << std::endl
           << "population: " << exactPopulation << " (+" << growthRate << ")" << std::endl
           << "unrest    : " << lostProduction << " (" << unrest << ")" << std::endl
           << "progress  : " << productionProgress << "/" << City::GetBuildingCost( currentOrder ) << std::endl
           << "totalProd : " << totalProduction << " (+" << productionRate << ")" << std::endl
           << "totalGold : " << totalIncome << " (" << income << ")" << std::endl
           << "totalPower: " << totalPower << " (" << power << ")" << std::endl;

        return os.str();
    }

    HistoryRecord Optimizer::nextEvent( City & target, Building nextOrder, const HistoryRecord & previous )
    {
        HistoryRecord record( target, previous );
        record.currentOrder = nextOrder;

        if ( target.hasBuilding( nextOrder ) ) {
            record.buildCompleted = true;
            return record;
        }

        const int buildingCost = City::GetBuildingCost( nextOrder ) - target.overflowProduction;
        const int productivity = target.getProductionRate();
        const int turnsToCompletion = ceilDivision( buildingCost, productivity );

        const int growth = target.getGrowthRate();
        const int popRequired = std::max( 0, 1000 - target.overflowGrowth );
        const int turnsToGrow = ceilDivision( popRequired, growth );

        const int turnsPassed = std::min( turnsToCompletion, turnsToGrow );
        const int produced = productivity * turnsPassed;

        // Save global statistics
        record.turn += turnsPassed;
        record.totalProduction += produced;
        record.lostProduction += target.getUnrest() * 2 * turnsPassed;
        record.totalIncome += target.getGoldIncome() * turnsPassed;
        record.totalPower += target.getPowerIncome() * turnsPassed;

        target.overflowGrowth += turnsPassed * growth;
        // Check if city population increases
        while ( target.overflowGrowth >= 1000 ) {
            target.overflowGrowth -= 1000;
            target.population++;
        }

        // Complete the building construction
        if ( produced >= buildingCost ) {
            record.buildCompleted = true;
            record.buildings = target.buildings;
            target.buildings.emplace_back( nextOrder );
            // does not carry over to the next order
            target.overflowProduction = 0;
        }
        else {
            target.overflowProduction += produced;
        }

        record.exactPopulation = target.getExactPopulation();
        record.growthRate = target.getGrowthRate();
        record.productionProgress = target.overflowProduction;
        record.productionRate = target.getProductionRate();
        record.income = target.getGoldIncome();
        record.power = target.getPowerIncome();
        record.unrest = target.getUnrest();

        return record;
    }

    std::vector<HistoryRecord> Optimizer::executeBuildOrder( const City & target, std::vector<Building> buildOrder )
    {
        City city = target;
        HistoryRecord startEvent( city );

        std::vector<HistoryRecord> history = { startEvent };

        auto currentOrder = buildOrder.begin();
        while ( currentOrder != buildOrder.end() ) {
            auto event = nextEvent( city, *currentOrder, history.back() );
            history.emplace_back( event );

            if ( event.buildCompleted && event.currentOrder == *currentOrder ) {
                currentOrder++;
            }
        }

        return history;
    }

    std::vector<HistoryRecord> Optimizer::findBestBuild( const City & target, const HistoryRecord & previous )
    {
        static int globalCallNumber = 0;
        int currentCall = globalCallNumber++;
        std::vector<HistoryRecord> history;
        std::vector<HistoryRecord> bestBuild;
        int bestTurn = INT_MAX;

        history.push_back( previous );

        auto available = target.getAvailableBuildings();
        std::cout << "Call #" << currentCall << ": starting at turn " << previous.turn << " build options " << available.size() << std::endl;

        for ( auto build : available ) {
            City city = target;

            auto event = nextEvent( city, build, previous );
            while ( !event.buildCompleted ) {
                event = nextEvent( city, build, event );
            }
            //std::cout << ">> Call #" << currentCall << ": completed " << City::GetBuildingName( event.currentOrder ) << "; city buildings: " << city.buildings.size() << std::endl;

            auto extra = findBestBuild( city, event );
            if ( previous.turn == 1 ) {
                std::cout << std::endl;
            }

            //std::cout << ">> Call #" << currentCall << ": city buildings: " << city.buildings.size() << std::endl;
            if ( !extra.empty() && extra.back().turn < bestTurn ) {
                bestTurn = extra.back().turn;
                bestBuild = extra;
            }
        }

        //std::cout << "Call #" << currentCall << ": collapsing, got " << bestBuild.size() << " events" << std::endl;

        if ( !bestBuild.empty() ) {
            history.insert( history.end(), bestBuild.begin(), bestBuild.end() );
        }

        return history;
    }

    void Optimizer::PrintFullHistory( const std::vector<HistoryRecord> & history )
    {
        for ( auto record : history ) {
            std::cout << "==================================" << std::endl;
            std::cout << record.toString() << std::endl;
        }
    }

    void Optimizer::PrintResult( const std::vector<HistoryRecord> & history )
    {
        std::cout << history.back().toString() << std::endl;
    }
}
