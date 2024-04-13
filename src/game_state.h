#pragma once

#include "map.h"
#include "rng.h"
#include "rpg_arena.h"
#include "wave_function.h"

#include <array>

struct Reward;

struct PlayerParty
{
    int food = 0;
    int gold = 0;
    int resources = 0;
    std::vector<RPG::Character> units;

    double getPartyLevel() const;
};

struct BattleState
{
    RPG::Force playerForce;
    RPG::Force otherForce;

    int variety = 0;
    int difficulty = 0;
};

struct GameState
{
    PlayerParty player;
    BattleState battle;

    WaveMap map;

    double sessionTime = 0;
    int64_t gameTime = 34 * 60 * 60; // in seconds; starting at Day 1 10:00

    GameState();

    void update( float delta );

    void recieveReward( const Reward & reward );
};
