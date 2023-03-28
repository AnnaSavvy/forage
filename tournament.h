#pragma once
#include <vector>

class Army
{
public:
    int strength = 0;
    Army( int str )
        : strength( str )
    {}

    bool fight( const Army & other ) const
    {
        return strength > other.strength;
    }
};

struct MatchResult
{
    int winner = -1;
    int loser = -1;
    int score = 0;
};

class BracketRound
{
public:
    std::vector<int> sideA;
    std::vector<int> sideB;
    std::vector<MatchResult> results;
    size_t matchesCount = 0;
    BracketRound * winnersRound = nullptr;
    BracketRound * losersRound = nullptr;

    bool isValid();
};

class TournamentBracket
{
    bool completed = false;
    std::vector<BracketRound> upperBracket;
    std::vector<BracketRound> lowerBracket;

public:
    bool setup();
    bool validateStructure();
    bool run();
    void printResults();
};