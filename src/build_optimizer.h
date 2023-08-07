#pragma once
#include <vector>

namespace BuildOrder
{
    enum Building
    {
        None,
        Sawmill,
        Foresters,
        Smithy,
        Marketplace,
        Builders,
        Miners,
        Granary,
        Farmers,
        Library,
        Sages,
        University,
        Mechanicians,
        Bank
    };

    struct HistoryRecord
    {
        int turn = 1;

        // current state
        Building completed = None;
        int population = 1;
        int production = 0;
        int income = 0;
        int power = 0;

        // accumulated state
        std::vector<Building> buildings;
        int totalProduction = 0;
        int totalIncome = 0;
        int totalPower = 0;
    };

    struct City
    {
        std::vector<Building> buildings;

        // based on starting conditions (land surveying)
        int landPopulation = 20;
        int landProduction = 0;
        int landGold = 0;
        int racialUnrest = 0; // percentage
        int racialGrowth = 0;
        int taxCollectionMode = 0; // gold per population / 2 with unrest

        int population = 1; // in thousands
        int popOverflow = 0; // 000s
        int maintanence = 0;

        bool hasBuilding( Building requirement ) const;
        int getMaxPopulation() const;
        int getGrowthRate() const;
        int getProductionRate() const;
        int getGoldIncome() const;

        static int GetBuildingCost( Building building );
        static int GetBuildingMaintanence( Building building );
    };

    class Optimizer
    {
        City city;
        int currentTurn = 1;

    public:
        Optimizer( City target )
            : city( target )
        {}

        HistoryRecord nextEvent( Building nextOrder );
        std::vector<HistoryRecord> executeBuildOrder( std::vector<Building> buildOrder );
    };
}
