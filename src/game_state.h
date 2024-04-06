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
};

struct GameState
{
    WaveMap map;
    RPG::Force playerForce;
    RPG::Force otherForce;
    std::vector<RPG::Character> units;

    double sessionTime = 0;
    int64_t gameTime = 34 * 60 * 60; // in seconds; starting at Day 1 10:00

    PlayerParty player;

    GameState();

    void update( float delta );

    void recieveReward( const Reward & reward );
};
