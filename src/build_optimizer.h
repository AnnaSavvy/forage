#pragma once
#include <string>
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
        Bank,
        Shrine,
        Temple,
        Parthenon,
        Cathedral,
        Alchemists,
        Wizards,
        Stables,
        Animists,
        Armory,
        Figthers,
        Armorers,
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
        int overflowGrowth = 0; // 000s
        int overflowProduction = 0;

        bool hasBuilding( Building requirement ) const;
        int getMaxPopulation() const;
        int getExactPopulation() const;
        int getGrowthRate() const;
        int getProductionRate() const;
        int getGoldIncome() const;
        int getPowerIncome() const;
        int getUnrest() const;

        static int GetBuildingCost( Building building );
        static int GetBuildingMaintanence( Building building );
        static std::string GetBuildingName( Building building );
    };

    struct HistoryRecord
    {
        int turn = 1;

        // current state
        bool buildCompleted = false;
        Building currentOrder = None;
        int exactPopulation = 1000;
        int growthRate = 0;
        int productionProgress = 0;
        int productionRate = 0;
        int income = 0;
        int power = 0;
        int unrest = 0;
        int lostProduction = 0;

        // accumulated state
        std::vector<Building> buildings;
        int totalProduction = 0;
        int totalIncome = 0;
        int totalPower = 0;

        HistoryRecord() = delete;
        HistoryRecord( City city );
        HistoryRecord( City city, const HistoryRecord & previous );

        std::string toString() const;
    };

    class Optimizer
    {
    public:
        HistoryRecord nextEvent( City & target, Building nextOrder, const HistoryRecord & previous );
        std::vector<HistoryRecord> executeBuildOrder( const City & target, std::vector<Building> buildOrder );
        std::vector<HistoryRecord> findBestBuild( std::vector<Building> buildOrder, const City & target );

        static void PrintFullHistory( const std::vector<HistoryRecord> & history );
        static void PrintResult( const std::vector<HistoryRecord> & history );
    };
}
