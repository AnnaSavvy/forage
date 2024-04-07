#include "game_state.h"
#include "dialog.h"

GameState::GameState()
    : map( 32 )
{
    const std::array positions{ RPG::Force::FRONT, RPG::Force::SIDE, RPG::Force::CENTER, RPG::Force::BACK };

    for ( int i = 0; i < 8; ++i ) {
        const int maximum = static_cast<int>( RPG::CharacterPreset::MONSTER );
        units.emplace_back( static_cast<RPG::CharacterPreset>( RandomGenerator::Get().next( 0, maximum ) ) );

        if ( i < 4 ) {
            battle.playerForce.add( units[i], false, positions[i % 4] );
        }
        else {
            battle.otherForce.add( units[i], true, positions[i % 4] );
        }
    }
}

void GameState::update( float delta )
{
    sessionTime += delta;
}

void GameState::recieveReward( const Reward & reward )
{
    switch ( reward.type ) {
    case Reward::Type::RESOURCES:
        player.gold += reward.value;
        break;
    default:
        break;
    }
}
