#include "game_state.h"
#include "dialog.h"
#include "static.h"

GameState::GameState()
    : map( 32 )
{
    const std::array positions{ RPG::Force::FRONT, RPG::Force::SIDE, RPG::Force::CENTER, RPG::Force::BACK };

    const auto presets = Data::GetCharacterPresets();

    for ( int i = 0; i < 8; ++i ) {
        player.units.emplace_back( RandomGenerator::Get().randomElement( presets ) );

        if ( i < 4 ) {
            battle.playerForce.add( player.units[i], false, positions[i % 4] );
        }
        else {
            battle.otherForce.add( player.units[i], true, positions[i % 4] );
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

double PlayerParty::getPartyLevel() const
{
    if ( units.empty() ) {
        return 0;
    }
    double sum = 0.0;
    for ( const auto & unit : units ) {
        sum += unit.getLevel();
    }
    return sum / units.size();
}
