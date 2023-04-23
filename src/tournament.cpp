#include "tournament.h"

#include <random>

namespace
{
    std::random_device dev;
    std::mt19937 rng( dev() );
}

bool TournamentBracket::setup()
{
    if ( validateStructure() )
        return true;
    return false;
}

bool TournamentBracket::validateStructure()
{
    for ( auto upper : upperBracket ) {
        if ( !upper.isValid() )
            return false;
    }
    for ( auto lower : lowerBracket ) {
        if ( !lower.isValid() )
            return false;
    }
    return true;
}

bool TournamentBracket::run()
{
    int participants = 64;
    std::vector<Army> armies;
    std::vector<std::vector<int> > upperBracket;

    for ( int k = 1000; k < 9999; k += 1000 ) {
        for ( int i = 0; i < 99; i += 10 ) {
            armies.emplace_back( k + i );

            if ( armies.size() == participants )
                break;
        }
        if ( armies.size() == participants )
            break;
    }
    std::shuffle( armies.begin(), armies.end(), rng );

    upperBracket.emplace_back();
    size_t currentRoundID = 0;
    // for ( const Army & army : armies ) {
    //    upperBracket[0].push_back( army.strength );
    //}
    for ( int i = 0; i < armies.size(); i++ )
        upperBracket[0].push_back( i );

    while ( upperBracket[currentRoundID].size() > 1 ) {
        upperBracket.emplace_back();
        auto & winners = upperBracket.back();
        for ( int i = 0; i < upperBracket[currentRoundID].size(); i += 2 ) {
            const int attackerID = upperBracket[currentRoundID][i];
            const int defenderID = upperBracket[currentRoundID][i + 1];
            if ( armies[attackerID].fight( armies[defenderID] ) ) {
                winners.emplace_back( attackerID );
            }
            else {
                winners.emplace_back( defenderID );
            }
        }
        currentRoundID++;
    }
    return false;
}

void TournamentBracket::printResults() {}

bool BracketRound::isValid()
{
    return true;
}
