#include "rpg_arena.h"

#include <iostream>
#include <queue>

namespace RPG
{
    bool Force::add( CharacterRef character, Position pos )
    {
        BattleUnit newUnit = { character };
        units.emplace_back( pos, newUnit );
        return true;
    }

    bool Force::switchPosition( const CharacterRef character, Position to )
    {
        size_t swapIdx;
        for ( swapIdx = 0; swapIdx < units.size(); ++swapIdx ) {
            if ( units[swapIdx].first == to ) {
                break;
            }
        }

        for ( auto & [position, unit] : units ) {
            if ( unit.getId() == character.get().getId() ) {
                if ( swapIdx < units.size() ) {
                    units[swapIdx].first = position;
                }
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
            if ( character.isDead() ) {
                continue;
            }

            if ( pos == Force::ALL || pos == position ) {
                retval.push_back( character );
            }
        }
        return retval;
    }

    std::vector<BattleUnitConst> Force::getCharacters( Position pos ) const
    {
        std::vector<BattleUnitConst> retval;
        for ( auto & [position, character] : units ) {
            if ( character.isDead() ) {
                continue;
            }

            if ( pos == Force::ALL || pos == position ) {
                retval.emplace_back( character );
            }
        }
        return retval;
    }

    bool Arena::executeTurn()
    {
        auto list = getInitiativeList();
        if ( list.empty() ) {
            return false;
        }

        for ( BattleUnitRef unit : list ) {
            executeAction( unit, unit.get().getAction() );
            if ( complete ) {
                return false;
            }
        }

        return true;
    }

    bool Arena::executeAction( BattleUnit & currentUnit, Action action )
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
        case Action::SPELL: {
            auto list = defenders.modifyCharacters( Force::Position::ALL );
            if ( !list.empty() ) {
                const int damage = currentUnit.getAttackDamage( false );
                list.front().get().recieveDamage( AttackSource::PHYSICAL, damage );
                std::cout << "Action! " << list.front().get().getId() << " takes " << damage << std::endl;
            }
            break;
        }
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
        return !attackers.isAnyAlive() || !defenders.isAnyAlive();
    }

    BattleUnit::BattleUnit( CharacterRef unit )
        : Character( unit )
    {}

    void BattleUnit::update( float deltaTime )
    {
        _animTimer += deltaTime;

        if ( ( (int)_animTimer ) % 2 ) {
            _frame = ( _frame + 1 ) % 2;
            _animTimer = 0;
        }
    }

    Action BattleUnit::getAction() const
    {
        return Action();
    }

    std::string BattleUnit::getSprite() const
    {
        std::string spriteName = "assets/char_";
        switch ( getClass() ) {
        case CharacterClass::MARTIAL_STR:
            spriteName.append( "orc" );
            break;
        case CharacterClass::MAGICAL_NATURE:
            spriteName.append( "druid" );
            break;
        default:
            break;
        }
        spriteName.append( std::to_string( _frame ) );
        spriteName.append( ".png" );
        return spriteName;
    }
}
