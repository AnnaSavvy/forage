#include "rpg_arena.h"

#include <iostream>
#include <queue>

namespace RPG
{
    bool Force::add( CharacterRef character, Position pos )
    {
        units.emplace_back( pos, character );
        return true;
    }

    bool Force::switchPosition( const CharacterRef character, Position to )
    {
        for ( auto & [position, unit] : units ) {
            if ( unit.getId() == character.get().getId() ) {
                position = to;
                return true;
            }
        }
        return false;
    }

    bool Force::isAnyAlive() const
    {
        for ( auto & [position, unit] : units ) {
            if ( !unit.isDead() ) {
                return true;
            }
        }
        return false;
    }

    std::vector<BattleUnitRef> Force::modifyCharacters( Position pos )
    {
        std::vector<BattleUnitRef> retval;
        for ( auto & [position, character] : units ) {
            if ( pos == Force::ALL || pos == position ) {
                retval.push_back( character );
            }
        }
        return retval;
    }

    std::vector<std::reference_wrapper<const BattleUnit> > Force::getCharacters( Position pos ) const
    {
        std::vector<std::reference_wrapper<const BattleUnit> > retval;
        for ( auto & [position, character] : units ) {
            if ( pos == Force::ALL || pos == position ) {
                retval.emplace_back( character );
            }
        }
        return retval;
    }

    bool Arena::executeTurn()
    {
        auto list = getInitiativeList();
        if ( list.empty() )
            return false;

        return executeAction( list[0].get().getAction() );
    }

    bool Arena::executeAction( Action action )
    {
        // check if still possible
        if ( false ) {
            // determine the alternative
            // action = fallback;
        }

        switch ( action.type ) {
        case Action::MELEE:
        case Action::RANGED:
        case Action::SKILL:
        case Action::SPELL:
            std::cout << "Action!" << std::endl;
            break;
        default:
            // Unexpected action type!
            assert( false );
            break;
        }

        // move

        if ( checkIfCombatEnded() ) {
            complete = true;
        }

        return true;
    }

    std::vector<BattleUnitRef> Arena::getInitiativeList()
    {
        std::vector<BattleUnitRef> retval;

        auto compare = []( BattleUnitRef a, BattleUnitRef b ) { return a.get().getInitiative() < b.get().getInitiative(); };
        std::priority_queue<BattleUnitRef, std::vector<BattleUnitRef>, decltype( compare )> initiativeList( compare );

        for ( BattleUnitRef atk : attackers.modifyCharacters( Force::ALL ) ) {
            initiativeList.push( atk );
        }
        for ( BattleUnitRef atk : defenders.modifyCharacters( Force::ALL ) ) {
            initiativeList.push( atk );
        }

        while ( !initiativeList.empty() ) {
            retval.push_back( initiativeList.top() );
            initiativeList.pop();
        }

        return retval;
    }

    bool Arena::checkIfCombatEnded() const
    {
        return attackers.isAnyAlive() && defenders.isAnyAlive();
    }

    Action BattleUnit::getAction() const
    {
        return Action();
    }
}
