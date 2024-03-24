#pragma once

#include "map.h"
#include "rng.h"
#include "rpg_arena.h"
#include "wave_function.h"

#include <array>

struct GameState
{
    WaveMap map;
    RPG::Force playerForce;
    RPG::Force otherForce;
    std::vector<RPG::Character> units;

    double sessionTime = 0;
    int64_t gameTime = 34 * 60 * 60; // in seconds; starting at Day 1 10:00

    int food = 0;
    int gold = 0;
    int resources = 0;

    GameState()
        : map( 32 )
    {
        const std::array positions{ RPG::Force::FRONT, RPG::Force::SIDE, RPG::Force::CENTER, RPG::Force::BACK };

        for ( int i = 0; i < 8; ++i ) {
            const int maximum = static_cast<int>( RPG::CharacterPreset::MONSTER );
            units.emplace_back( static_cast<RPG::CharacterPreset>( RandomGenerator::Get().next( 0, maximum ) ) );

            if ( i < 4 ) {
                playerForce.add( units[i], false, positions[i % 4] );
            }
            else {
                otherForce.add( units[i], true, positions[i % 4] );
            }
        }
    }

    void update( float delta )
    {
        sessionTime += delta;
    }
};
