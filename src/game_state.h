#pragma once

#include "map.h"
#include "rpg_arena.h"
#include "wave_function.h"
#include "rng.h"

struct GameState
{
    WaveMap map;
    RPG::Force playerForce;
    RPG::Force otherForce;
    std::vector<RPG::Character> units;

    GameState() : map(32) {
        for ( int i = 0; i < 8; ++i ) {
            const int maximum = static_cast<int>( RPG::CharacterPreset::MONSTER );
            units.emplace_back( static_cast<RPG::CharacterPreset>( RandomGenerator::Get().next( 0, maximum ) ) );
        }

        playerForce.add( units[0] );
        playerForce.add( units[1], RPG::Force::SIDE );
        playerForce.add( units[2], RPG::Force::CENTER );
        playerForce.add( units[3], RPG::Force::BACK );

        otherForce.add( units[4] );
        otherForce.add( units[5], RPG::Force::SIDE );
        otherForce.add( units[6], RPG::Force::CENTER );
        otherForce.add( units[7], RPG::Force::BACK );
    }
};
