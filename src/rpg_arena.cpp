#include "rpg_arena.h"

#include <cassert>
#include <iostream>
#include <queue>

namespace RPG
{
    bool Force::add( CharacterRef character, bool isDefender, Position pos )
    {
        BattleUnit newUnit = { character, isDefender };
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

    void Arena::newTurn()
    {
        initiativeList = getInitiativeList();
        currentUnit = initiativeList.begin();
    }

    bool Arena::executeTurn()
    {
        executeAction( *currentUnit, currentUnit->get().getAction() );
        ++currentUnit;

        if ( currentUnit == initiativeList.end() ) {
            newTurn();
            if ( initiativeList.empty() ) {
                return false;
            }
        }
        else if ( currentUnit->get().isDead() ) {
            ++currentUnit;
        }

        return complete ? false : true;
    }

    bool Arena::executeAction( BattleUnit & currentUnit, Action action )
    {
        // check if still possible
        if ( currentUnit.isDead() ) {
            return false;
        }

        RPG::Force & targets = currentUnit.rightSide ? attackers : defenders;

        switch ( action.type ) {
        case Action::MELEE:
        case Action::SKILL: {
            auto list = targets.modifyCharacters( Force::Position::ALL );
            if ( !list.empty() ) {
                const int damage = currentUnit.getWeaponDamage();
                list.front().get().recieveDamage( AttackSource::PHYSICAL, damage );
                std::cout << "Melee attack! " << list.front().get().getId() << " takes " << damage << std::endl;
            }
            break;
        }
        case Action::RANGED: {
            auto list = targets.modifyCharacters( Force::Position::ALL );
            if ( !list.empty() ) {
                const int damage = currentUnit.getWeaponDamage();
                list.front().get().recieveDamage( AttackSource::PHYSICAL, damage );
                std::cout << "Ranged attack! " << list.front().get().getId() << " takes " << damage << std::endl;
            }
            break;
        }
        case Action::SPELL: {
            auto list = targets.modifyCharacters( Force::Position::ALL );
            if ( !list.empty() ) {
                const int damage = currentUnit.getMagicDamage();
                list.front().get().recieveDamage( AttackSource::MAGIC, damage );
                std::cout << "Spell effect " << list.front().get().getId() << " takes " << damage << std::endl;
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

    BattleUnit * Arena::getCurrentUnit()
    {
        // treat this as assert
        return &currentUnit->get();
    }

    BattleUnit * Arena::getUnitByIndex( int index )
    {
        if ( index < 0 ) {
            return &currentUnit->get();
        }
        const std::vector<Force::Position> dLayout = { Force::Position::BACK,  Force::Position::CENTER, Force::Position::SIDE,   Force::Position::FRONT,
                                                       Force::Position::FRONT, Force::Position::SIDE,   Force::Position::CENTER, Force::Position::BACK };

        if ( index < 4 ) {
            const std::vector<BattleUnitRef> & list = attackers.modifyCharacters( dLayout[index] );
            return list.empty() ? nullptr : &list.front().get();
        }
        else if ( index < dLayout.size() ) {
            const std::vector<BattleUnitRef> & list = defenders.modifyCharacters( dLayout[index] );
            return list.empty() ? nullptr : &list.front().get();
        }
        return nullptr;
    }

    BattleUnit::BattleUnit( CharacterRef unit, bool isDefender )
        : Character( unit )
        , rightSide( isDefender )
    {}

    void BattleUnit::update( float deltaTime )
    {
        _animTimer += deltaTime;

        if ( _animTimer > 0.3 ) {
            _frame = ( _frame + 1 ) % 2;
            _animTimer = 0;
        }
    }

    Action BattleUnit::getAction() const
    {
        switch ( getClass() ) {
        case CharacterClass::MARTIAL_STR:
            return Action();
        case CharacterClass::MARTIAL_AGI:
            return Action( Action::RANGED );
        case CharacterClass::MAGICAL_NATURE:
            return Action( Action::SPELL );
        }
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
